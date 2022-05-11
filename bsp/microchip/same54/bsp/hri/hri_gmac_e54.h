/**
 * \file
 *
 * \brief SAM GMAC
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAME54_GMAC_COMPONENT_
#ifndef _HRI_GMAC_E54_H_INCLUDED_
#define _HRI_GMAC_E54_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_GMAC_CRITICAL_SECTIONS)
#define GMAC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define GMAC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define GMAC_CRITICAL_SECTION_ENTER()
#define GMAC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_gmac_ae_reg_t;
typedef uint32_t hri_gmac_bcfr_reg_t;
typedef uint32_t hri_gmac_bcft_reg_t;
typedef uint32_t hri_gmac_bfr64_reg_t;
typedef uint32_t hri_gmac_bft64_reg_t;
typedef uint32_t hri_gmac_cse_reg_t;
typedef uint32_t hri_gmac_dcfgr_reg_t;
typedef uint32_t hri_gmac_dtf_reg_t;
typedef uint32_t hri_gmac_ec_reg_t;
typedef uint32_t hri_gmac_efrn_reg_t;
typedef uint32_t hri_gmac_efrsh_reg_t;
typedef uint32_t hri_gmac_efrsl_reg_t;
typedef uint32_t hri_gmac_eftn_reg_t;
typedef uint32_t hri_gmac_eftsh_reg_t;
typedef uint32_t hri_gmac_eftsl_reg_t;
typedef uint32_t hri_gmac_fcse_reg_t;
typedef uint32_t hri_gmac_fr_reg_t;
typedef uint32_t hri_gmac_ft_reg_t;
typedef uint32_t hri_gmac_gtbft1518_reg_t;
typedef uint32_t hri_gmac_hrb_reg_t;
typedef uint32_t hri_gmac_hrt_reg_t;
typedef uint32_t hri_gmac_ihce_reg_t;
typedef uint32_t hri_gmac_imr_reg_t;
typedef uint32_t hri_gmac_ipgs_reg_t;
typedef uint32_t hri_gmac_isr_reg_t;
typedef uint32_t hri_gmac_jr_reg_t;
typedef uint32_t hri_gmac_lc_reg_t;
typedef uint32_t hri_gmac_lffe_reg_t;
typedef uint32_t hri_gmac_man_reg_t;
typedef uint32_t hri_gmac_mcf_reg_t;
typedef uint32_t hri_gmac_mfr_reg_t;
typedef uint32_t hri_gmac_mft_reg_t;
typedef uint32_t hri_gmac_ncfgr_reg_t;
typedef uint32_t hri_gmac_ncr_reg_t;
typedef uint32_t hri_gmac_nsc_reg_t;
typedef uint32_t hri_gmac_nsr_reg_t;
typedef uint32_t hri_gmac_ofr_reg_t;
typedef uint32_t hri_gmac_orhi_reg_t;
typedef uint32_t hri_gmac_orlo_reg_t;
typedef uint32_t hri_gmac_othi_reg_t;
typedef uint32_t hri_gmac_otlo_reg_t;
typedef uint32_t hri_gmac_pefrn_reg_t;
typedef uint32_t hri_gmac_pefrsh_reg_t;
typedef uint32_t hri_gmac_pefrsl_reg_t;
typedef uint32_t hri_gmac_peftn_reg_t;
typedef uint32_t hri_gmac_peftsh_reg_t;
typedef uint32_t hri_gmac_peftsl_reg_t;
typedef uint32_t hri_gmac_pfr_reg_t;
typedef uint32_t hri_gmac_pft_reg_t;
typedef uint32_t hri_gmac_rbqb_reg_t;
typedef uint32_t hri_gmac_rjfml_reg_t;
typedef uint32_t hri_gmac_rlpiti_reg_t;
typedef uint32_t hri_gmac_rlpitr_reg_t;
typedef uint32_t hri_gmac_roe_reg_t;
typedef uint32_t hri_gmac_rpq_reg_t;
typedef uint32_t hri_gmac_rpsf_reg_t;
typedef uint32_t hri_gmac_rre_reg_t;
typedef uint32_t hri_gmac_rse_reg_t;
typedef uint32_t hri_gmac_rsr_reg_t;
typedef uint32_t hri_gmac_sab_reg_t;
typedef uint32_t hri_gmac_samb1_reg_t;
typedef uint32_t hri_gmac_samt1_reg_t;
typedef uint32_t hri_gmac_sat_reg_t;
typedef uint32_t hri_gmac_scf_reg_t;
typedef uint32_t hri_gmac_sch_reg_t;
typedef uint32_t hri_gmac_scl_reg_t;
typedef uint32_t hri_gmac_svlan_reg_t;
typedef uint32_t hri_gmac_ta_reg_t;
typedef uint32_t hri_gmac_tbfr1023_reg_t;
typedef uint32_t hri_gmac_tbfr127_reg_t;
typedef uint32_t hri_gmac_tbfr1518_reg_t;
typedef uint32_t hri_gmac_tbfr255_reg_t;
typedef uint32_t hri_gmac_tbfr511_reg_t;
typedef uint32_t hri_gmac_tbft1023_reg_t;
typedef uint32_t hri_gmac_tbft127_reg_t;
typedef uint32_t hri_gmac_tbft1518_reg_t;
typedef uint32_t hri_gmac_tbft255_reg_t;
typedef uint32_t hri_gmac_tbft511_reg_t;
typedef uint32_t hri_gmac_tbqb_reg_t;
typedef uint32_t hri_gmac_tce_reg_t;
typedef uint32_t hri_gmac_ti_reg_t;
typedef uint32_t hri_gmac_tidm_reg_t;
typedef uint32_t hri_gmac_tisubn_reg_t;
typedef uint32_t hri_gmac_tlpiti_reg_t;
typedef uint32_t hri_gmac_tlpitr_reg_t;
typedef uint32_t hri_gmac_tmxbfr_reg_t;
typedef uint32_t hri_gmac_tn_reg_t;
typedef uint32_t hri_gmac_tpfcp_reg_t;
typedef uint32_t hri_gmac_tpq_reg_t;
typedef uint32_t hri_gmac_tpsf_reg_t;
typedef uint32_t hri_gmac_tsh_reg_t;
typedef uint32_t hri_gmac_tsl_reg_t;
typedef uint32_t hri_gmac_tsr_reg_t;
typedef uint32_t hri_gmac_tssn_reg_t;
typedef uint32_t hri_gmac_tsssl_reg_t;
typedef uint32_t hri_gmac_tur_reg_t;
typedef uint32_t hri_gmac_uce_reg_t;
typedef uint32_t hri_gmac_ufr_reg_t;
typedef uint32_t hri_gmac_ur_reg_t;
typedef uint32_t hri_gmac_wol_reg_t;
typedef uint32_t hri_gmacsa_sab_reg_t;
typedef uint32_t hri_gmacsa_sat_reg_t;

static inline void hri_gmacsa_set_SAB_reg(const void *const hw, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->SAB.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmacsa_get_SAB_reg(const void *const hw, hri_gmac_sab_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSa *)hw)->SAB.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmacsa_write_SAB_reg(const void *const hw, hri_gmac_sab_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->SAB.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_clear_SAB_reg(const void *const hw, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->SAB.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_toggle_SAB_reg(const void *const hw, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->SAB.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmacsa_read_SAB_reg(const void *const hw)
{
	return ((GmacSa *)hw)->SAB.reg;
}

static inline void hri_gmacsa_set_SAT_reg(const void *const hw, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->SAT.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmacsa_get_SAT_reg(const void *const hw, hri_gmac_sat_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSa *)hw)->SAT.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmacsa_write_SAT_reg(const void *const hw, hri_gmac_sat_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->SAT.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_clear_SAT_reg(const void *const hw, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->SAT.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_toggle_SAT_reg(const void *const hw, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->SAT.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmacsa_read_SAT_reg(const void *const hw)
{
	return ((GmacSa *)hw)->SAT.reg;
}

static inline void hri_gmac_set_SAB_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->Sa[submodule_index].SAB.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmac_get_SAB_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_gmac_sab_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->Sa[submodule_index].SAB.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SAB_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->Sa[submodule_index].SAB.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAB_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->Sa[submodule_index].SAB.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAB_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->Sa[submodule_index].SAB.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmac_read_SAB_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Gmac *)hw)->Sa[submodule_index].SAB.reg;
}

static inline void hri_gmac_set_SAT_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->Sa[submodule_index].SAT.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmac_get_SAT_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_gmac_sat_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->Sa[submodule_index].SAT.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SAT_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->Sa[submodule_index].SAT.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAT_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->Sa[submodule_index].SAT.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAT_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->Sa[submodule_index].SAT.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmac_read_SAT_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Gmac *)hw)->Sa[submodule_index].SAT.reg;
}

static inline void hri_gmac_set_IMR_MFS_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_MFS;
}

static inline bool hri_gmac_get_IMR_MFS_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_MFS) >> GMAC_IMR_MFS_Pos;
}

static inline void hri_gmac_write_IMR_MFS_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_MFS;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_MFS;
	}
}

static inline void hri_gmac_clear_IMR_MFS_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_MFS;
}

static inline void hri_gmac_set_IMR_RCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_RCOMP;
}

static inline bool hri_gmac_get_IMR_RCOMP_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_RCOMP) >> GMAC_IMR_RCOMP_Pos;
}

static inline void hri_gmac_write_IMR_RCOMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_RCOMP;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_RCOMP;
	}
}

static inline void hri_gmac_clear_IMR_RCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_RCOMP;
}

static inline void hri_gmac_set_IMR_RXUBR_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_RXUBR;
}

static inline bool hri_gmac_get_IMR_RXUBR_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_RXUBR) >> GMAC_IMR_RXUBR_Pos;
}

static inline void hri_gmac_write_IMR_RXUBR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_RXUBR;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_RXUBR;
	}
}

static inline void hri_gmac_clear_IMR_RXUBR_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_RXUBR;
}

static inline void hri_gmac_set_IMR_TXUBR_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_TXUBR;
}

static inline bool hri_gmac_get_IMR_TXUBR_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_TXUBR) >> GMAC_IMR_TXUBR_Pos;
}

static inline void hri_gmac_write_IMR_TXUBR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_TXUBR;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_TXUBR;
	}
}

static inline void hri_gmac_clear_IMR_TXUBR_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_TXUBR;
}

static inline void hri_gmac_set_IMR_TUR_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_TUR;
}

static inline bool hri_gmac_get_IMR_TUR_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_TUR) >> GMAC_IMR_TUR_Pos;
}

static inline void hri_gmac_write_IMR_TUR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_TUR;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_TUR;
	}
}

static inline void hri_gmac_clear_IMR_TUR_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_TUR;
}

static inline void hri_gmac_set_IMR_RLEX_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_RLEX;
}

static inline bool hri_gmac_get_IMR_RLEX_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_RLEX) >> GMAC_IMR_RLEX_Pos;
}

static inline void hri_gmac_write_IMR_RLEX_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_RLEX;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_RLEX;
	}
}

static inline void hri_gmac_clear_IMR_RLEX_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_RLEX;
}

static inline void hri_gmac_set_IMR_TFC_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_TFC;
}

static inline bool hri_gmac_get_IMR_TFC_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_TFC) >> GMAC_IMR_TFC_Pos;
}

static inline void hri_gmac_write_IMR_TFC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_TFC;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_TFC;
	}
}

static inline void hri_gmac_clear_IMR_TFC_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_TFC;
}

static inline void hri_gmac_set_IMR_TCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_TCOMP;
}

static inline bool hri_gmac_get_IMR_TCOMP_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_TCOMP) >> GMAC_IMR_TCOMP_Pos;
}

static inline void hri_gmac_write_IMR_TCOMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_TCOMP;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_TCOMP;
	}
}

static inline void hri_gmac_clear_IMR_TCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_TCOMP;
}

static inline void hri_gmac_set_IMR_ROVR_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_ROVR;
}

static inline bool hri_gmac_get_IMR_ROVR_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_ROVR) >> GMAC_IMR_ROVR_Pos;
}

static inline void hri_gmac_write_IMR_ROVR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_ROVR;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_ROVR;
	}
}

static inline void hri_gmac_clear_IMR_ROVR_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_ROVR;
}

static inline void hri_gmac_set_IMR_HRESP_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_HRESP;
}

static inline bool hri_gmac_get_IMR_HRESP_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_HRESP) >> GMAC_IMR_HRESP_Pos;
}

static inline void hri_gmac_write_IMR_HRESP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_HRESP;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_HRESP;
	}
}

static inline void hri_gmac_clear_IMR_HRESP_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_HRESP;
}

static inline void hri_gmac_set_IMR_PFNZ_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_PFNZ;
}

static inline bool hri_gmac_get_IMR_PFNZ_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_PFNZ) >> GMAC_IMR_PFNZ_Pos;
}

static inline void hri_gmac_write_IMR_PFNZ_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_PFNZ;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_PFNZ;
	}
}

static inline void hri_gmac_clear_IMR_PFNZ_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_PFNZ;
}

static inline void hri_gmac_set_IMR_PTZ_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_PTZ;
}

static inline bool hri_gmac_get_IMR_PTZ_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_PTZ) >> GMAC_IMR_PTZ_Pos;
}

static inline void hri_gmac_write_IMR_PTZ_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_PTZ;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_PTZ;
	}
}

static inline void hri_gmac_clear_IMR_PTZ_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_PTZ;
}

static inline void hri_gmac_set_IMR_PFTR_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_PFTR;
}

static inline bool hri_gmac_get_IMR_PFTR_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_PFTR) >> GMAC_IMR_PFTR_Pos;
}

static inline void hri_gmac_write_IMR_PFTR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_PFTR;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_PFTR;
	}
}

static inline void hri_gmac_clear_IMR_PFTR_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_PFTR;
}

static inline void hri_gmac_set_IMR_EXINT_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_EXINT;
}

static inline bool hri_gmac_get_IMR_EXINT_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_EXINT) >> GMAC_IMR_EXINT_Pos;
}

static inline void hri_gmac_write_IMR_EXINT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_EXINT;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_EXINT;
	}
}

static inline void hri_gmac_clear_IMR_EXINT_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_EXINT;
}

static inline void hri_gmac_set_IMR_DRQFR_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_DRQFR;
}

static inline bool hri_gmac_get_IMR_DRQFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_DRQFR) >> GMAC_IMR_DRQFR_Pos;
}

static inline void hri_gmac_write_IMR_DRQFR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_DRQFR;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_DRQFR;
	}
}

static inline void hri_gmac_clear_IMR_DRQFR_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_DRQFR;
}

static inline void hri_gmac_set_IMR_SFR_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_SFR;
}

static inline bool hri_gmac_get_IMR_SFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_SFR) >> GMAC_IMR_SFR_Pos;
}

static inline void hri_gmac_write_IMR_SFR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_SFR;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_SFR;
	}
}

static inline void hri_gmac_clear_IMR_SFR_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_SFR;
}

static inline void hri_gmac_set_IMR_DRQFT_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_DRQFT;
}

static inline bool hri_gmac_get_IMR_DRQFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_DRQFT) >> GMAC_IMR_DRQFT_Pos;
}

static inline void hri_gmac_write_IMR_DRQFT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_DRQFT;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_DRQFT;
	}
}

static inline void hri_gmac_clear_IMR_DRQFT_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_DRQFT;
}

static inline void hri_gmac_set_IMR_SFT_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_SFT;
}

static inline bool hri_gmac_get_IMR_SFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_SFT) >> GMAC_IMR_SFT_Pos;
}

static inline void hri_gmac_write_IMR_SFT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_SFT;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_SFT;
	}
}

static inline void hri_gmac_clear_IMR_SFT_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_SFT;
}

static inline void hri_gmac_set_IMR_PDRQFR_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_PDRQFR;
}

static inline bool hri_gmac_get_IMR_PDRQFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_PDRQFR) >> GMAC_IMR_PDRQFR_Pos;
}

static inline void hri_gmac_write_IMR_PDRQFR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_PDRQFR;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_PDRQFR;
	}
}

static inline void hri_gmac_clear_IMR_PDRQFR_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_PDRQFR;
}

static inline void hri_gmac_set_IMR_PDRSFR_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_PDRSFR;
}

static inline bool hri_gmac_get_IMR_PDRSFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_PDRSFR) >> GMAC_IMR_PDRSFR_Pos;
}

static inline void hri_gmac_write_IMR_PDRSFR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_PDRSFR;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_PDRSFR;
	}
}

static inline void hri_gmac_clear_IMR_PDRSFR_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_PDRSFR;
}

static inline void hri_gmac_set_IMR_PDRQFT_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_PDRQFT;
}

static inline bool hri_gmac_get_IMR_PDRQFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_PDRQFT) >> GMAC_IMR_PDRQFT_Pos;
}

static inline void hri_gmac_write_IMR_PDRQFT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_PDRQFT;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_PDRQFT;
	}
}

static inline void hri_gmac_clear_IMR_PDRQFT_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_PDRQFT;
}

static inline void hri_gmac_set_IMR_PDRSFT_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_PDRSFT;
}

static inline bool hri_gmac_get_IMR_PDRSFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_PDRSFT) >> GMAC_IMR_PDRSFT_Pos;
}

static inline void hri_gmac_write_IMR_PDRSFT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_PDRSFT;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_PDRSFT;
	}
}

static inline void hri_gmac_clear_IMR_PDRSFT_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_PDRSFT;
}

static inline void hri_gmac_set_IMR_SRI_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_SRI;
}

static inline bool hri_gmac_get_IMR_SRI_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_SRI) >> GMAC_IMR_SRI_Pos;
}

static inline void hri_gmac_write_IMR_SRI_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_SRI;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_SRI;
	}
}

static inline void hri_gmac_clear_IMR_SRI_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_SRI;
}

static inline void hri_gmac_set_IMR_WOL_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_WOL;
}

static inline bool hri_gmac_get_IMR_WOL_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_WOL) >> GMAC_IMR_WOL_Pos;
}

static inline void hri_gmac_write_IMR_WOL_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_WOL;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_WOL;
	}
}

static inline void hri_gmac_clear_IMR_WOL_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_WOL;
}

static inline void hri_gmac_set_IMR_TSUCMP_bit(const void *const hw)
{
	((Gmac *)hw)->IER.reg = GMAC_IMR_TSUCMP;
}

static inline bool hri_gmac_get_IMR_TSUCMP_bit(const void *const hw)
{
	return (((Gmac *)hw)->IMR.reg & GMAC_IMR_TSUCMP) >> GMAC_IMR_TSUCMP_Pos;
}

static inline void hri_gmac_write_IMR_TSUCMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->IDR.reg = GMAC_IMR_TSUCMP;
	} else {
		((Gmac *)hw)->IER.reg = GMAC_IMR_TSUCMP;
	}
}

static inline void hri_gmac_clear_IMR_TSUCMP_bit(const void *const hw)
{
	((Gmac *)hw)->IDR.reg = GMAC_IMR_TSUCMP;
}

static inline void hri_gmac_set_IMR_reg(const void *const hw, hri_gmac_imr_reg_t mask)
{
	((Gmac *)hw)->IER.reg = mask;
}

static inline hri_gmac_imr_reg_t hri_gmac_get_IMR_reg(const void *const hw, hri_gmac_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->IMR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_imr_reg_t hri_gmac_read_IMR_reg(const void *const hw)
{
	return ((Gmac *)hw)->IMR.reg;
}

static inline void hri_gmac_write_IMR_reg(const void *const hw, hri_gmac_imr_reg_t data)
{
	((Gmac *)hw)->IER.reg = data;
	((Gmac *)hw)->IDR.reg = ~data;
}

static inline void hri_gmac_clear_IMR_reg(const void *const hw, hri_gmac_imr_reg_t mask)
{
	((Gmac *)hw)->IDR.reg = mask;
}

static inline bool hri_gmac_get_NSR_MDIO_bit(const void *const hw)
{
	return (((Gmac *)hw)->NSR.reg & GMAC_NSR_MDIO) >> GMAC_NSR_MDIO_Pos;
}

static inline bool hri_gmac_get_NSR_IDLE_bit(const void *const hw)
{
	return (((Gmac *)hw)->NSR.reg & GMAC_NSR_IDLE) >> GMAC_NSR_IDLE_Pos;
}

static inline hri_gmac_nsr_reg_t hri_gmac_get_NSR_reg(const void *const hw, hri_gmac_nsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->NSR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_nsr_reg_t hri_gmac_read_NSR_reg(const void *const hw)
{
	return ((Gmac *)hw)->NSR.reg;
}

static inline hri_gmac_rpq_reg_t hri_gmac_get_RPQ_RPQ_bf(const void *const hw, hri_gmac_rpq_reg_t mask)
{
	return (((Gmac *)hw)->RPQ.reg & GMAC_RPQ_RPQ(mask)) >> GMAC_RPQ_RPQ_Pos;
}

static inline hri_gmac_rpq_reg_t hri_gmac_read_RPQ_RPQ_bf(const void *const hw)
{
	return (((Gmac *)hw)->RPQ.reg & GMAC_RPQ_RPQ_Msk) >> GMAC_RPQ_RPQ_Pos;
}

static inline hri_gmac_rpq_reg_t hri_gmac_get_RPQ_reg(const void *const hw, hri_gmac_rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->RPQ.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rpq_reg_t hri_gmac_read_RPQ_reg(const void *const hw)
{
	return ((Gmac *)hw)->RPQ.reg;
}

static inline hri_gmac_eftsh_reg_t hri_gmac_get_EFTSH_RUD_bf(const void *const hw, hri_gmac_eftsh_reg_t mask)
{
	return (((Gmac *)hw)->EFTSH.reg & GMAC_EFTSH_RUD(mask)) >> GMAC_EFTSH_RUD_Pos;
}

static inline hri_gmac_eftsh_reg_t hri_gmac_read_EFTSH_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->EFTSH.reg & GMAC_EFTSH_RUD_Msk) >> GMAC_EFTSH_RUD_Pos;
}

static inline hri_gmac_eftsh_reg_t hri_gmac_get_EFTSH_reg(const void *const hw, hri_gmac_eftsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->EFTSH.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_eftsh_reg_t hri_gmac_read_EFTSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->EFTSH.reg;
}

static inline hri_gmac_efrsh_reg_t hri_gmac_get_EFRSH_RUD_bf(const void *const hw, hri_gmac_efrsh_reg_t mask)
{
	return (((Gmac *)hw)->EFRSH.reg & GMAC_EFRSH_RUD(mask)) >> GMAC_EFRSH_RUD_Pos;
}

static inline hri_gmac_efrsh_reg_t hri_gmac_read_EFRSH_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->EFRSH.reg & GMAC_EFRSH_RUD_Msk) >> GMAC_EFRSH_RUD_Pos;
}

static inline hri_gmac_efrsh_reg_t hri_gmac_get_EFRSH_reg(const void *const hw, hri_gmac_efrsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->EFRSH.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_efrsh_reg_t hri_gmac_read_EFRSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->EFRSH.reg;
}

static inline hri_gmac_peftsh_reg_t hri_gmac_get_PEFTSH_RUD_bf(const void *const hw, hri_gmac_peftsh_reg_t mask)
{
	return (((Gmac *)hw)->PEFTSH.reg & GMAC_PEFTSH_RUD(mask)) >> GMAC_PEFTSH_RUD_Pos;
}

static inline hri_gmac_peftsh_reg_t hri_gmac_read_PEFTSH_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->PEFTSH.reg & GMAC_PEFTSH_RUD_Msk) >> GMAC_PEFTSH_RUD_Pos;
}

static inline hri_gmac_peftsh_reg_t hri_gmac_get_PEFTSH_reg(const void *const hw, hri_gmac_peftsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->PEFTSH.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_peftsh_reg_t hri_gmac_read_PEFTSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->PEFTSH.reg;
}

static inline hri_gmac_pefrsh_reg_t hri_gmac_get_PEFRSH_RUD_bf(const void *const hw, hri_gmac_pefrsh_reg_t mask)
{
	return (((Gmac *)hw)->PEFRSH.reg & GMAC_PEFRSH_RUD(mask)) >> GMAC_PEFRSH_RUD_Pos;
}

static inline hri_gmac_pefrsh_reg_t hri_gmac_read_PEFRSH_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->PEFRSH.reg & GMAC_PEFRSH_RUD_Msk) >> GMAC_PEFRSH_RUD_Pos;
}

static inline hri_gmac_pefrsh_reg_t hri_gmac_get_PEFRSH_reg(const void *const hw, hri_gmac_pefrsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->PEFRSH.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pefrsh_reg_t hri_gmac_read_PEFRSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->PEFRSH.reg;
}

static inline hri_gmac_otlo_reg_t hri_gmac_get_OTLO_TXO_bf(const void *const hw, hri_gmac_otlo_reg_t mask)
{
	return (((Gmac *)hw)->OTLO.reg & GMAC_OTLO_TXO(mask)) >> GMAC_OTLO_TXO_Pos;
}

static inline hri_gmac_otlo_reg_t hri_gmac_read_OTLO_TXO_bf(const void *const hw)
{
	return (((Gmac *)hw)->OTLO.reg & GMAC_OTLO_TXO_Msk) >> GMAC_OTLO_TXO_Pos;
}

static inline hri_gmac_otlo_reg_t hri_gmac_get_OTLO_reg(const void *const hw, hri_gmac_otlo_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->OTLO.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_otlo_reg_t hri_gmac_read_OTLO_reg(const void *const hw)
{
	return ((Gmac *)hw)->OTLO.reg;
}

static inline hri_gmac_othi_reg_t hri_gmac_get_OTHI_TXO_bf(const void *const hw, hri_gmac_othi_reg_t mask)
{
	return (((Gmac *)hw)->OTHI.reg & GMAC_OTHI_TXO(mask)) >> GMAC_OTHI_TXO_Pos;
}

static inline hri_gmac_othi_reg_t hri_gmac_read_OTHI_TXO_bf(const void *const hw)
{
	return (((Gmac *)hw)->OTHI.reg & GMAC_OTHI_TXO_Msk) >> GMAC_OTHI_TXO_Pos;
}

static inline hri_gmac_othi_reg_t hri_gmac_get_OTHI_reg(const void *const hw, hri_gmac_othi_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->OTHI.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_othi_reg_t hri_gmac_read_OTHI_reg(const void *const hw)
{
	return ((Gmac *)hw)->OTHI.reg;
}

static inline hri_gmac_ft_reg_t hri_gmac_get_FT_FTX_bf(const void *const hw, hri_gmac_ft_reg_t mask)
{
	return (((Gmac *)hw)->FT.reg & GMAC_FT_FTX(mask)) >> GMAC_FT_FTX_Pos;
}

static inline hri_gmac_ft_reg_t hri_gmac_read_FT_FTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->FT.reg & GMAC_FT_FTX_Msk) >> GMAC_FT_FTX_Pos;
}

static inline hri_gmac_ft_reg_t hri_gmac_get_FT_reg(const void *const hw, hri_gmac_ft_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->FT.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ft_reg_t hri_gmac_read_FT_reg(const void *const hw)
{
	return ((Gmac *)hw)->FT.reg;
}

static inline hri_gmac_bcft_reg_t hri_gmac_get_BCFT_BFTX_bf(const void *const hw, hri_gmac_bcft_reg_t mask)
{
	return (((Gmac *)hw)->BCFT.reg & GMAC_BCFT_BFTX(mask)) >> GMAC_BCFT_BFTX_Pos;
}

static inline hri_gmac_bcft_reg_t hri_gmac_read_BCFT_BFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->BCFT.reg & GMAC_BCFT_BFTX_Msk) >> GMAC_BCFT_BFTX_Pos;
}

static inline hri_gmac_bcft_reg_t hri_gmac_get_BCFT_reg(const void *const hw, hri_gmac_bcft_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->BCFT.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_bcft_reg_t hri_gmac_read_BCFT_reg(const void *const hw)
{
	return ((Gmac *)hw)->BCFT.reg;
}

static inline hri_gmac_mft_reg_t hri_gmac_get_MFT_MFTX_bf(const void *const hw, hri_gmac_mft_reg_t mask)
{
	return (((Gmac *)hw)->MFT.reg & GMAC_MFT_MFTX(mask)) >> GMAC_MFT_MFTX_Pos;
}

static inline hri_gmac_mft_reg_t hri_gmac_read_MFT_MFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->MFT.reg & GMAC_MFT_MFTX_Msk) >> GMAC_MFT_MFTX_Pos;
}

static inline hri_gmac_mft_reg_t hri_gmac_get_MFT_reg(const void *const hw, hri_gmac_mft_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->MFT.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_mft_reg_t hri_gmac_read_MFT_reg(const void *const hw)
{
	return ((Gmac *)hw)->MFT.reg;
}

static inline hri_gmac_pft_reg_t hri_gmac_get_PFT_PFTX_bf(const void *const hw, hri_gmac_pft_reg_t mask)
{
	return (((Gmac *)hw)->PFT.reg & GMAC_PFT_PFTX(mask)) >> GMAC_PFT_PFTX_Pos;
}

static inline hri_gmac_pft_reg_t hri_gmac_read_PFT_PFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->PFT.reg & GMAC_PFT_PFTX_Msk) >> GMAC_PFT_PFTX_Pos;
}

static inline hri_gmac_pft_reg_t hri_gmac_get_PFT_reg(const void *const hw, hri_gmac_pft_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->PFT.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pft_reg_t hri_gmac_read_PFT_reg(const void *const hw)
{
	return ((Gmac *)hw)->PFT.reg;
}

static inline hri_gmac_bft64_reg_t hri_gmac_get_BFT64_NFTX_bf(const void *const hw, hri_gmac_bft64_reg_t mask)
{
	return (((Gmac *)hw)->BFT64.reg & GMAC_BFT64_NFTX(mask)) >> GMAC_BFT64_NFTX_Pos;
}

static inline hri_gmac_bft64_reg_t hri_gmac_read_BFT64_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->BFT64.reg & GMAC_BFT64_NFTX_Msk) >> GMAC_BFT64_NFTX_Pos;
}

static inline hri_gmac_bft64_reg_t hri_gmac_get_BFT64_reg(const void *const hw, hri_gmac_bft64_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->BFT64.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_bft64_reg_t hri_gmac_read_BFT64_reg(const void *const hw)
{
	return ((Gmac *)hw)->BFT64.reg;
}

static inline hri_gmac_tbft127_reg_t hri_gmac_get_TBFT127_NFTX_bf(const void *const hw, hri_gmac_tbft127_reg_t mask)
{
	return (((Gmac *)hw)->TBFT127.reg & GMAC_TBFT127_NFTX(mask)) >> GMAC_TBFT127_NFTX_Pos;
}

static inline hri_gmac_tbft127_reg_t hri_gmac_read_TBFT127_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFT127.reg & GMAC_TBFT127_NFTX_Msk) >> GMAC_TBFT127_NFTX_Pos;
}

static inline hri_gmac_tbft127_reg_t hri_gmac_get_TBFT127_reg(const void *const hw, hri_gmac_tbft127_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFT127.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft127_reg_t hri_gmac_read_TBFT127_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFT127.reg;
}

static inline hri_gmac_tbft255_reg_t hri_gmac_get_TBFT255_NFTX_bf(const void *const hw, hri_gmac_tbft255_reg_t mask)
{
	return (((Gmac *)hw)->TBFT255.reg & GMAC_TBFT255_NFTX(mask)) >> GMAC_TBFT255_NFTX_Pos;
}

static inline hri_gmac_tbft255_reg_t hri_gmac_read_TBFT255_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFT255.reg & GMAC_TBFT255_NFTX_Msk) >> GMAC_TBFT255_NFTX_Pos;
}

static inline hri_gmac_tbft255_reg_t hri_gmac_get_TBFT255_reg(const void *const hw, hri_gmac_tbft255_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFT255.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft255_reg_t hri_gmac_read_TBFT255_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFT255.reg;
}

static inline hri_gmac_tbft511_reg_t hri_gmac_get_TBFT511_NFTX_bf(const void *const hw, hri_gmac_tbft511_reg_t mask)
{
	return (((Gmac *)hw)->TBFT511.reg & GMAC_TBFT511_NFTX(mask)) >> GMAC_TBFT511_NFTX_Pos;
}

static inline hri_gmac_tbft511_reg_t hri_gmac_read_TBFT511_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFT511.reg & GMAC_TBFT511_NFTX_Msk) >> GMAC_TBFT511_NFTX_Pos;
}

static inline hri_gmac_tbft511_reg_t hri_gmac_get_TBFT511_reg(const void *const hw, hri_gmac_tbft511_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFT511.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft511_reg_t hri_gmac_read_TBFT511_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFT511.reg;
}

static inline hri_gmac_tbft1023_reg_t hri_gmac_get_TBFT1023_NFTX_bf(const void *const hw, hri_gmac_tbft1023_reg_t mask)
{
	return (((Gmac *)hw)->TBFT1023.reg & GMAC_TBFT1023_NFTX(mask)) >> GMAC_TBFT1023_NFTX_Pos;
}

static inline hri_gmac_tbft1023_reg_t hri_gmac_read_TBFT1023_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFT1023.reg & GMAC_TBFT1023_NFTX_Msk) >> GMAC_TBFT1023_NFTX_Pos;
}

static inline hri_gmac_tbft1023_reg_t hri_gmac_get_TBFT1023_reg(const void *const hw, hri_gmac_tbft1023_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFT1023.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft1023_reg_t hri_gmac_read_TBFT1023_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFT1023.reg;
}

static inline hri_gmac_tbft1518_reg_t hri_gmac_get_TBFT1518_NFTX_bf(const void *const hw, hri_gmac_tbft1518_reg_t mask)
{
	return (((Gmac *)hw)->TBFT1518.reg & GMAC_TBFT1518_NFTX(mask)) >> GMAC_TBFT1518_NFTX_Pos;
}

static inline hri_gmac_tbft1518_reg_t hri_gmac_read_TBFT1518_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFT1518.reg & GMAC_TBFT1518_NFTX_Msk) >> GMAC_TBFT1518_NFTX_Pos;
}

static inline hri_gmac_tbft1518_reg_t hri_gmac_get_TBFT1518_reg(const void *const hw, hri_gmac_tbft1518_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFT1518.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft1518_reg_t hri_gmac_read_TBFT1518_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFT1518.reg;
}

static inline hri_gmac_gtbft1518_reg_t hri_gmac_get_GTBFT1518_NFTX_bf(const void *const        hw,
                                                                      hri_gmac_gtbft1518_reg_t mask)
{
	return (((Gmac *)hw)->GTBFT1518.reg & GMAC_GTBFT1518_NFTX(mask)) >> GMAC_GTBFT1518_NFTX_Pos;
}

static inline hri_gmac_gtbft1518_reg_t hri_gmac_read_GTBFT1518_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GTBFT1518.reg & GMAC_GTBFT1518_NFTX_Msk) >> GMAC_GTBFT1518_NFTX_Pos;
}

static inline hri_gmac_gtbft1518_reg_t hri_gmac_get_GTBFT1518_reg(const void *const hw, hri_gmac_gtbft1518_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GTBFT1518.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_gtbft1518_reg_t hri_gmac_read_GTBFT1518_reg(const void *const hw)
{
	return ((Gmac *)hw)->GTBFT1518.reg;
}

static inline hri_gmac_tur_reg_t hri_gmac_get_TUR_TXUNR_bf(const void *const hw, hri_gmac_tur_reg_t mask)
{
	return (((Gmac *)hw)->TUR.reg & GMAC_TUR_TXUNR(mask)) >> GMAC_TUR_TXUNR_Pos;
}

static inline hri_gmac_tur_reg_t hri_gmac_read_TUR_TXUNR_bf(const void *const hw)
{
	return (((Gmac *)hw)->TUR.reg & GMAC_TUR_TXUNR_Msk) >> GMAC_TUR_TXUNR_Pos;
}

static inline hri_gmac_tur_reg_t hri_gmac_get_TUR_reg(const void *const hw, hri_gmac_tur_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TUR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tur_reg_t hri_gmac_read_TUR_reg(const void *const hw)
{
	return ((Gmac *)hw)->TUR.reg;
}

static inline hri_gmac_scf_reg_t hri_gmac_get_SCF_SCOL_bf(const void *const hw, hri_gmac_scf_reg_t mask)
{
	return (((Gmac *)hw)->SCF.reg & GMAC_SCF_SCOL(mask)) >> GMAC_SCF_SCOL_Pos;
}

static inline hri_gmac_scf_reg_t hri_gmac_read_SCF_SCOL_bf(const void *const hw)
{
	return (((Gmac *)hw)->SCF.reg & GMAC_SCF_SCOL_Msk) >> GMAC_SCF_SCOL_Pos;
}

static inline hri_gmac_scf_reg_t hri_gmac_get_SCF_reg(const void *const hw, hri_gmac_scf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->SCF.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_scf_reg_t hri_gmac_read_SCF_reg(const void *const hw)
{
	return ((Gmac *)hw)->SCF.reg;
}

static inline hri_gmac_mcf_reg_t hri_gmac_get_MCF_MCOL_bf(const void *const hw, hri_gmac_mcf_reg_t mask)
{
	return (((Gmac *)hw)->MCF.reg & GMAC_MCF_MCOL(mask)) >> GMAC_MCF_MCOL_Pos;
}

static inline hri_gmac_mcf_reg_t hri_gmac_read_MCF_MCOL_bf(const void *const hw)
{
	return (((Gmac *)hw)->MCF.reg & GMAC_MCF_MCOL_Msk) >> GMAC_MCF_MCOL_Pos;
}

static inline hri_gmac_mcf_reg_t hri_gmac_get_MCF_reg(const void *const hw, hri_gmac_mcf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->MCF.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_mcf_reg_t hri_gmac_read_MCF_reg(const void *const hw)
{
	return ((Gmac *)hw)->MCF.reg;
}

static inline hri_gmac_ec_reg_t hri_gmac_get_EC_XCOL_bf(const void *const hw, hri_gmac_ec_reg_t mask)
{
	return (((Gmac *)hw)->EC.reg & GMAC_EC_XCOL(mask)) >> GMAC_EC_XCOL_Pos;
}

static inline hri_gmac_ec_reg_t hri_gmac_read_EC_XCOL_bf(const void *const hw)
{
	return (((Gmac *)hw)->EC.reg & GMAC_EC_XCOL_Msk) >> GMAC_EC_XCOL_Pos;
}

static inline hri_gmac_ec_reg_t hri_gmac_get_EC_reg(const void *const hw, hri_gmac_ec_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->EC.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ec_reg_t hri_gmac_read_EC_reg(const void *const hw)
{
	return ((Gmac *)hw)->EC.reg;
}

static inline hri_gmac_lc_reg_t hri_gmac_get_LC_LCOL_bf(const void *const hw, hri_gmac_lc_reg_t mask)
{
	return (((Gmac *)hw)->LC.reg & GMAC_LC_LCOL(mask)) >> GMAC_LC_LCOL_Pos;
}

static inline hri_gmac_lc_reg_t hri_gmac_read_LC_LCOL_bf(const void *const hw)
{
	return (((Gmac *)hw)->LC.reg & GMAC_LC_LCOL_Msk) >> GMAC_LC_LCOL_Pos;
}

static inline hri_gmac_lc_reg_t hri_gmac_get_LC_reg(const void *const hw, hri_gmac_lc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->LC.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_lc_reg_t hri_gmac_read_LC_reg(const void *const hw)
{
	return ((Gmac *)hw)->LC.reg;
}

static inline hri_gmac_dtf_reg_t hri_gmac_get_DTF_DEFT_bf(const void *const hw, hri_gmac_dtf_reg_t mask)
{
	return (((Gmac *)hw)->DTF.reg & GMAC_DTF_DEFT(mask)) >> GMAC_DTF_DEFT_Pos;
}

static inline hri_gmac_dtf_reg_t hri_gmac_read_DTF_DEFT_bf(const void *const hw)
{
	return (((Gmac *)hw)->DTF.reg & GMAC_DTF_DEFT_Msk) >> GMAC_DTF_DEFT_Pos;
}

static inline hri_gmac_dtf_reg_t hri_gmac_get_DTF_reg(const void *const hw, hri_gmac_dtf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->DTF.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_dtf_reg_t hri_gmac_read_DTF_reg(const void *const hw)
{
	return ((Gmac *)hw)->DTF.reg;
}

static inline hri_gmac_cse_reg_t hri_gmac_get_CSE_CSR_bf(const void *const hw, hri_gmac_cse_reg_t mask)
{
	return (((Gmac *)hw)->CSE.reg & GMAC_CSE_CSR(mask)) >> GMAC_CSE_CSR_Pos;
}

static inline hri_gmac_cse_reg_t hri_gmac_read_CSE_CSR_bf(const void *const hw)
{
	return (((Gmac *)hw)->CSE.reg & GMAC_CSE_CSR_Msk) >> GMAC_CSE_CSR_Pos;
}

static inline hri_gmac_cse_reg_t hri_gmac_get_CSE_reg(const void *const hw, hri_gmac_cse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->CSE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_cse_reg_t hri_gmac_read_CSE_reg(const void *const hw)
{
	return ((Gmac *)hw)->CSE.reg;
}

static inline hri_gmac_orlo_reg_t hri_gmac_get_ORLO_RXO_bf(const void *const hw, hri_gmac_orlo_reg_t mask)
{
	return (((Gmac *)hw)->ORLO.reg & GMAC_ORLO_RXO(mask)) >> GMAC_ORLO_RXO_Pos;
}

static inline hri_gmac_orlo_reg_t hri_gmac_read_ORLO_RXO_bf(const void *const hw)
{
	return (((Gmac *)hw)->ORLO.reg & GMAC_ORLO_RXO_Msk) >> GMAC_ORLO_RXO_Pos;
}

static inline hri_gmac_orlo_reg_t hri_gmac_get_ORLO_reg(const void *const hw, hri_gmac_orlo_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->ORLO.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_orlo_reg_t hri_gmac_read_ORLO_reg(const void *const hw)
{
	return ((Gmac *)hw)->ORLO.reg;
}

static inline hri_gmac_orhi_reg_t hri_gmac_get_ORHI_RXO_bf(const void *const hw, hri_gmac_orhi_reg_t mask)
{
	return (((Gmac *)hw)->ORHI.reg & GMAC_ORHI_RXO(mask)) >> GMAC_ORHI_RXO_Pos;
}

static inline hri_gmac_orhi_reg_t hri_gmac_read_ORHI_RXO_bf(const void *const hw)
{
	return (((Gmac *)hw)->ORHI.reg & GMAC_ORHI_RXO_Msk) >> GMAC_ORHI_RXO_Pos;
}

static inline hri_gmac_orhi_reg_t hri_gmac_get_ORHI_reg(const void *const hw, hri_gmac_orhi_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->ORHI.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_orhi_reg_t hri_gmac_read_ORHI_reg(const void *const hw)
{
	return ((Gmac *)hw)->ORHI.reg;
}

static inline hri_gmac_fr_reg_t hri_gmac_get_FR_FRX_bf(const void *const hw, hri_gmac_fr_reg_t mask)
{
	return (((Gmac *)hw)->FR.reg & GMAC_FR_FRX(mask)) >> GMAC_FR_FRX_Pos;
}

static inline hri_gmac_fr_reg_t hri_gmac_read_FR_FRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->FR.reg & GMAC_FR_FRX_Msk) >> GMAC_FR_FRX_Pos;
}

static inline hri_gmac_fr_reg_t hri_gmac_get_FR_reg(const void *const hw, hri_gmac_fr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->FR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_fr_reg_t hri_gmac_read_FR_reg(const void *const hw)
{
	return ((Gmac *)hw)->FR.reg;
}

static inline hri_gmac_bcfr_reg_t hri_gmac_get_BCFR_BFRX_bf(const void *const hw, hri_gmac_bcfr_reg_t mask)
{
	return (((Gmac *)hw)->BCFR.reg & GMAC_BCFR_BFRX(mask)) >> GMAC_BCFR_BFRX_Pos;
}

static inline hri_gmac_bcfr_reg_t hri_gmac_read_BCFR_BFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->BCFR.reg & GMAC_BCFR_BFRX_Msk) >> GMAC_BCFR_BFRX_Pos;
}

static inline hri_gmac_bcfr_reg_t hri_gmac_get_BCFR_reg(const void *const hw, hri_gmac_bcfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->BCFR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_bcfr_reg_t hri_gmac_read_BCFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->BCFR.reg;
}

static inline hri_gmac_mfr_reg_t hri_gmac_get_MFR_MFRX_bf(const void *const hw, hri_gmac_mfr_reg_t mask)
{
	return (((Gmac *)hw)->MFR.reg & GMAC_MFR_MFRX(mask)) >> GMAC_MFR_MFRX_Pos;
}

static inline hri_gmac_mfr_reg_t hri_gmac_read_MFR_MFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->MFR.reg & GMAC_MFR_MFRX_Msk) >> GMAC_MFR_MFRX_Pos;
}

static inline hri_gmac_mfr_reg_t hri_gmac_get_MFR_reg(const void *const hw, hri_gmac_mfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->MFR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_mfr_reg_t hri_gmac_read_MFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->MFR.reg;
}

static inline hri_gmac_pfr_reg_t hri_gmac_get_PFR_PFRX_bf(const void *const hw, hri_gmac_pfr_reg_t mask)
{
	return (((Gmac *)hw)->PFR.reg & GMAC_PFR_PFRX(mask)) >> GMAC_PFR_PFRX_Pos;
}

static inline hri_gmac_pfr_reg_t hri_gmac_read_PFR_PFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->PFR.reg & GMAC_PFR_PFRX_Msk) >> GMAC_PFR_PFRX_Pos;
}

static inline hri_gmac_pfr_reg_t hri_gmac_get_PFR_reg(const void *const hw, hri_gmac_pfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->PFR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pfr_reg_t hri_gmac_read_PFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->PFR.reg;
}

static inline hri_gmac_bfr64_reg_t hri_gmac_get_BFR64_NFRX_bf(const void *const hw, hri_gmac_bfr64_reg_t mask)
{
	return (((Gmac *)hw)->BFR64.reg & GMAC_BFR64_NFRX(mask)) >> GMAC_BFR64_NFRX_Pos;
}

static inline hri_gmac_bfr64_reg_t hri_gmac_read_BFR64_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->BFR64.reg & GMAC_BFR64_NFRX_Msk) >> GMAC_BFR64_NFRX_Pos;
}

static inline hri_gmac_bfr64_reg_t hri_gmac_get_BFR64_reg(const void *const hw, hri_gmac_bfr64_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->BFR64.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_bfr64_reg_t hri_gmac_read_BFR64_reg(const void *const hw)
{
	return ((Gmac *)hw)->BFR64.reg;
}

static inline hri_gmac_tbfr127_reg_t hri_gmac_get_TBFR127_NFRX_bf(const void *const hw, hri_gmac_tbfr127_reg_t mask)
{
	return (((Gmac *)hw)->TBFR127.reg & GMAC_TBFR127_NFRX(mask)) >> GMAC_TBFR127_NFRX_Pos;
}

static inline hri_gmac_tbfr127_reg_t hri_gmac_read_TBFR127_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFR127.reg & GMAC_TBFR127_NFRX_Msk) >> GMAC_TBFR127_NFRX_Pos;
}

static inline hri_gmac_tbfr127_reg_t hri_gmac_get_TBFR127_reg(const void *const hw, hri_gmac_tbfr127_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFR127.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr127_reg_t hri_gmac_read_TBFR127_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFR127.reg;
}

static inline hri_gmac_tbfr255_reg_t hri_gmac_get_TBFR255_NFRX_bf(const void *const hw, hri_gmac_tbfr255_reg_t mask)
{
	return (((Gmac *)hw)->TBFR255.reg & GMAC_TBFR255_NFRX(mask)) >> GMAC_TBFR255_NFRX_Pos;
}

static inline hri_gmac_tbfr255_reg_t hri_gmac_read_TBFR255_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFR255.reg & GMAC_TBFR255_NFRX_Msk) >> GMAC_TBFR255_NFRX_Pos;
}

static inline hri_gmac_tbfr255_reg_t hri_gmac_get_TBFR255_reg(const void *const hw, hri_gmac_tbfr255_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFR255.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr255_reg_t hri_gmac_read_TBFR255_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFR255.reg;
}

static inline hri_gmac_tbfr511_reg_t hri_gmac_get_TBFR511_NFRX_bf(const void *const hw, hri_gmac_tbfr511_reg_t mask)
{
	return (((Gmac *)hw)->TBFR511.reg & GMAC_TBFR511_NFRX(mask)) >> GMAC_TBFR511_NFRX_Pos;
}

static inline hri_gmac_tbfr511_reg_t hri_gmac_read_TBFR511_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFR511.reg & GMAC_TBFR511_NFRX_Msk) >> GMAC_TBFR511_NFRX_Pos;
}

static inline hri_gmac_tbfr511_reg_t hri_gmac_get_TBFR511_reg(const void *const hw, hri_gmac_tbfr511_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFR511.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr511_reg_t hri_gmac_read_TBFR511_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFR511.reg;
}

static inline hri_gmac_tbfr1023_reg_t hri_gmac_get_TBFR1023_NFRX_bf(const void *const hw, hri_gmac_tbfr1023_reg_t mask)
{
	return (((Gmac *)hw)->TBFR1023.reg & GMAC_TBFR1023_NFRX(mask)) >> GMAC_TBFR1023_NFRX_Pos;
}

static inline hri_gmac_tbfr1023_reg_t hri_gmac_read_TBFR1023_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFR1023.reg & GMAC_TBFR1023_NFRX_Msk) >> GMAC_TBFR1023_NFRX_Pos;
}

static inline hri_gmac_tbfr1023_reg_t hri_gmac_get_TBFR1023_reg(const void *const hw, hri_gmac_tbfr1023_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFR1023.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr1023_reg_t hri_gmac_read_TBFR1023_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFR1023.reg;
}

static inline hri_gmac_tbfr1518_reg_t hri_gmac_get_TBFR1518_NFRX_bf(const void *const hw, hri_gmac_tbfr1518_reg_t mask)
{
	return (((Gmac *)hw)->TBFR1518.reg & GMAC_TBFR1518_NFRX(mask)) >> GMAC_TBFR1518_NFRX_Pos;
}

static inline hri_gmac_tbfr1518_reg_t hri_gmac_read_TBFR1518_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TBFR1518.reg & GMAC_TBFR1518_NFRX_Msk) >> GMAC_TBFR1518_NFRX_Pos;
}

static inline hri_gmac_tbfr1518_reg_t hri_gmac_get_TBFR1518_reg(const void *const hw, hri_gmac_tbfr1518_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBFR1518.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr1518_reg_t hri_gmac_read_TBFR1518_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBFR1518.reg;
}

static inline hri_gmac_tmxbfr_reg_t hri_gmac_get_TMXBFR_NFRX_bf(const void *const hw, hri_gmac_tmxbfr_reg_t mask)
{
	return (((Gmac *)hw)->TMXBFR.reg & GMAC_TMXBFR_NFRX(mask)) >> GMAC_TMXBFR_NFRX_Pos;
}

static inline hri_gmac_tmxbfr_reg_t hri_gmac_read_TMXBFR_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->TMXBFR.reg & GMAC_TMXBFR_NFRX_Msk) >> GMAC_TMXBFR_NFRX_Pos;
}

static inline hri_gmac_tmxbfr_reg_t hri_gmac_get_TMXBFR_reg(const void *const hw, hri_gmac_tmxbfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TMXBFR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tmxbfr_reg_t hri_gmac_read_TMXBFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->TMXBFR.reg;
}

static inline hri_gmac_ufr_reg_t hri_gmac_get_UFR_UFRX_bf(const void *const hw, hri_gmac_ufr_reg_t mask)
{
	return (((Gmac *)hw)->UFR.reg & GMAC_UFR_UFRX(mask)) >> GMAC_UFR_UFRX_Pos;
}

static inline hri_gmac_ufr_reg_t hri_gmac_read_UFR_UFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->UFR.reg & GMAC_UFR_UFRX_Msk) >> GMAC_UFR_UFRX_Pos;
}

static inline hri_gmac_ufr_reg_t hri_gmac_get_UFR_reg(const void *const hw, hri_gmac_ufr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->UFR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ufr_reg_t hri_gmac_read_UFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->UFR.reg;
}

static inline hri_gmac_ofr_reg_t hri_gmac_get_OFR_OFRX_bf(const void *const hw, hri_gmac_ofr_reg_t mask)
{
	return (((Gmac *)hw)->OFR.reg & GMAC_OFR_OFRX(mask)) >> GMAC_OFR_OFRX_Pos;
}

static inline hri_gmac_ofr_reg_t hri_gmac_read_OFR_OFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->OFR.reg & GMAC_OFR_OFRX_Msk) >> GMAC_OFR_OFRX_Pos;
}

static inline hri_gmac_ofr_reg_t hri_gmac_get_OFR_reg(const void *const hw, hri_gmac_ofr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->OFR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ofr_reg_t hri_gmac_read_OFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->OFR.reg;
}

static inline hri_gmac_jr_reg_t hri_gmac_get_JR_JRX_bf(const void *const hw, hri_gmac_jr_reg_t mask)
{
	return (((Gmac *)hw)->JR.reg & GMAC_JR_JRX(mask)) >> GMAC_JR_JRX_Pos;
}

static inline hri_gmac_jr_reg_t hri_gmac_read_JR_JRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->JR.reg & GMAC_JR_JRX_Msk) >> GMAC_JR_JRX_Pos;
}

static inline hri_gmac_jr_reg_t hri_gmac_get_JR_reg(const void *const hw, hri_gmac_jr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->JR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_jr_reg_t hri_gmac_read_JR_reg(const void *const hw)
{
	return ((Gmac *)hw)->JR.reg;
}

static inline hri_gmac_fcse_reg_t hri_gmac_get_FCSE_FCKR_bf(const void *const hw, hri_gmac_fcse_reg_t mask)
{
	return (((Gmac *)hw)->FCSE.reg & GMAC_FCSE_FCKR(mask)) >> GMAC_FCSE_FCKR_Pos;
}

static inline hri_gmac_fcse_reg_t hri_gmac_read_FCSE_FCKR_bf(const void *const hw)
{
	return (((Gmac *)hw)->FCSE.reg & GMAC_FCSE_FCKR_Msk) >> GMAC_FCSE_FCKR_Pos;
}

static inline hri_gmac_fcse_reg_t hri_gmac_get_FCSE_reg(const void *const hw, hri_gmac_fcse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->FCSE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_fcse_reg_t hri_gmac_read_FCSE_reg(const void *const hw)
{
	return ((Gmac *)hw)->FCSE.reg;
}

static inline hri_gmac_lffe_reg_t hri_gmac_get_LFFE_LFER_bf(const void *const hw, hri_gmac_lffe_reg_t mask)
{
	return (((Gmac *)hw)->LFFE.reg & GMAC_LFFE_LFER(mask)) >> GMAC_LFFE_LFER_Pos;
}

static inline hri_gmac_lffe_reg_t hri_gmac_read_LFFE_LFER_bf(const void *const hw)
{
	return (((Gmac *)hw)->LFFE.reg & GMAC_LFFE_LFER_Msk) >> GMAC_LFFE_LFER_Pos;
}

static inline hri_gmac_lffe_reg_t hri_gmac_get_LFFE_reg(const void *const hw, hri_gmac_lffe_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->LFFE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_lffe_reg_t hri_gmac_read_LFFE_reg(const void *const hw)
{
	return ((Gmac *)hw)->LFFE.reg;
}

static inline hri_gmac_rse_reg_t hri_gmac_get_RSE_RXSE_bf(const void *const hw, hri_gmac_rse_reg_t mask)
{
	return (((Gmac *)hw)->RSE.reg & GMAC_RSE_RXSE(mask)) >> GMAC_RSE_RXSE_Pos;
}

static inline hri_gmac_rse_reg_t hri_gmac_read_RSE_RXSE_bf(const void *const hw)
{
	return (((Gmac *)hw)->RSE.reg & GMAC_RSE_RXSE_Msk) >> GMAC_RSE_RXSE_Pos;
}

static inline hri_gmac_rse_reg_t hri_gmac_get_RSE_reg(const void *const hw, hri_gmac_rse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->RSE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rse_reg_t hri_gmac_read_RSE_reg(const void *const hw)
{
	return ((Gmac *)hw)->RSE.reg;
}

static inline hri_gmac_ae_reg_t hri_gmac_get_AE_AER_bf(const void *const hw, hri_gmac_ae_reg_t mask)
{
	return (((Gmac *)hw)->AE.reg & GMAC_AE_AER(mask)) >> GMAC_AE_AER_Pos;
}

static inline hri_gmac_ae_reg_t hri_gmac_read_AE_AER_bf(const void *const hw)
{
	return (((Gmac *)hw)->AE.reg & GMAC_AE_AER_Msk) >> GMAC_AE_AER_Pos;
}

static inline hri_gmac_ae_reg_t hri_gmac_get_AE_reg(const void *const hw, hri_gmac_ae_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->AE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ae_reg_t hri_gmac_read_AE_reg(const void *const hw)
{
	return ((Gmac *)hw)->AE.reg;
}

static inline hri_gmac_rre_reg_t hri_gmac_get_RRE_RXRER_bf(const void *const hw, hri_gmac_rre_reg_t mask)
{
	return (((Gmac *)hw)->RRE.reg & GMAC_RRE_RXRER(mask)) >> GMAC_RRE_RXRER_Pos;
}

static inline hri_gmac_rre_reg_t hri_gmac_read_RRE_RXRER_bf(const void *const hw)
{
	return (((Gmac *)hw)->RRE.reg & GMAC_RRE_RXRER_Msk) >> GMAC_RRE_RXRER_Pos;
}

static inline hri_gmac_rre_reg_t hri_gmac_get_RRE_reg(const void *const hw, hri_gmac_rre_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->RRE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rre_reg_t hri_gmac_read_RRE_reg(const void *const hw)
{
	return ((Gmac *)hw)->RRE.reg;
}

static inline hri_gmac_roe_reg_t hri_gmac_get_ROE_RXOVR_bf(const void *const hw, hri_gmac_roe_reg_t mask)
{
	return (((Gmac *)hw)->ROE.reg & GMAC_ROE_RXOVR(mask)) >> GMAC_ROE_RXOVR_Pos;
}

static inline hri_gmac_roe_reg_t hri_gmac_read_ROE_RXOVR_bf(const void *const hw)
{
	return (((Gmac *)hw)->ROE.reg & GMAC_ROE_RXOVR_Msk) >> GMAC_ROE_RXOVR_Pos;
}

static inline hri_gmac_roe_reg_t hri_gmac_get_ROE_reg(const void *const hw, hri_gmac_roe_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->ROE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_roe_reg_t hri_gmac_read_ROE_reg(const void *const hw)
{
	return ((Gmac *)hw)->ROE.reg;
}

static inline hri_gmac_ihce_reg_t hri_gmac_get_IHCE_HCKER_bf(const void *const hw, hri_gmac_ihce_reg_t mask)
{
	return (((Gmac *)hw)->IHCE.reg & GMAC_IHCE_HCKER(mask)) >> GMAC_IHCE_HCKER_Pos;
}

static inline hri_gmac_ihce_reg_t hri_gmac_read_IHCE_HCKER_bf(const void *const hw)
{
	return (((Gmac *)hw)->IHCE.reg & GMAC_IHCE_HCKER_Msk) >> GMAC_IHCE_HCKER_Pos;
}

static inline hri_gmac_ihce_reg_t hri_gmac_get_IHCE_reg(const void *const hw, hri_gmac_ihce_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->IHCE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ihce_reg_t hri_gmac_read_IHCE_reg(const void *const hw)
{
	return ((Gmac *)hw)->IHCE.reg;
}

static inline hri_gmac_tce_reg_t hri_gmac_get_TCE_TCKER_bf(const void *const hw, hri_gmac_tce_reg_t mask)
{
	return (((Gmac *)hw)->TCE.reg & GMAC_TCE_TCKER(mask)) >> GMAC_TCE_TCKER_Pos;
}

static inline hri_gmac_tce_reg_t hri_gmac_read_TCE_TCKER_bf(const void *const hw)
{
	return (((Gmac *)hw)->TCE.reg & GMAC_TCE_TCKER_Msk) >> GMAC_TCE_TCKER_Pos;
}

static inline hri_gmac_tce_reg_t hri_gmac_get_TCE_reg(const void *const hw, hri_gmac_tce_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TCE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tce_reg_t hri_gmac_read_TCE_reg(const void *const hw)
{
	return ((Gmac *)hw)->TCE.reg;
}

static inline hri_gmac_uce_reg_t hri_gmac_get_UCE_UCKER_bf(const void *const hw, hri_gmac_uce_reg_t mask)
{
	return (((Gmac *)hw)->UCE.reg & GMAC_UCE_UCKER(mask)) >> GMAC_UCE_UCKER_Pos;
}

static inline hri_gmac_uce_reg_t hri_gmac_read_UCE_UCKER_bf(const void *const hw)
{
	return (((Gmac *)hw)->UCE.reg & GMAC_UCE_UCKER_Msk) >> GMAC_UCE_UCKER_Pos;
}

static inline hri_gmac_uce_reg_t hri_gmac_get_UCE_reg(const void *const hw, hri_gmac_uce_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->UCE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_uce_reg_t hri_gmac_read_UCE_reg(const void *const hw)
{
	return ((Gmac *)hw)->UCE.reg;
}

static inline hri_gmac_eftsl_reg_t hri_gmac_get_EFTSL_RUD_bf(const void *const hw, hri_gmac_eftsl_reg_t mask)
{
	return (((Gmac *)hw)->EFTSL.reg & GMAC_EFTSL_RUD(mask)) >> GMAC_EFTSL_RUD_Pos;
}

static inline hri_gmac_eftsl_reg_t hri_gmac_read_EFTSL_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->EFTSL.reg & GMAC_EFTSL_RUD_Msk) >> GMAC_EFTSL_RUD_Pos;
}

static inline hri_gmac_eftsl_reg_t hri_gmac_get_EFTSL_reg(const void *const hw, hri_gmac_eftsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->EFTSL.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_eftsl_reg_t hri_gmac_read_EFTSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->EFTSL.reg;
}

static inline hri_gmac_eftn_reg_t hri_gmac_get_EFTN_RUD_bf(const void *const hw, hri_gmac_eftn_reg_t mask)
{
	return (((Gmac *)hw)->EFTN.reg & GMAC_EFTN_RUD(mask)) >> GMAC_EFTN_RUD_Pos;
}

static inline hri_gmac_eftn_reg_t hri_gmac_read_EFTN_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->EFTN.reg & GMAC_EFTN_RUD_Msk) >> GMAC_EFTN_RUD_Pos;
}

static inline hri_gmac_eftn_reg_t hri_gmac_get_EFTN_reg(const void *const hw, hri_gmac_eftn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->EFTN.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_eftn_reg_t hri_gmac_read_EFTN_reg(const void *const hw)
{
	return ((Gmac *)hw)->EFTN.reg;
}

static inline hri_gmac_efrsl_reg_t hri_gmac_get_EFRSL_RUD_bf(const void *const hw, hri_gmac_efrsl_reg_t mask)
{
	return (((Gmac *)hw)->EFRSL.reg & GMAC_EFRSL_RUD(mask)) >> GMAC_EFRSL_RUD_Pos;
}

static inline hri_gmac_efrsl_reg_t hri_gmac_read_EFRSL_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->EFRSL.reg & GMAC_EFRSL_RUD_Msk) >> GMAC_EFRSL_RUD_Pos;
}

static inline hri_gmac_efrsl_reg_t hri_gmac_get_EFRSL_reg(const void *const hw, hri_gmac_efrsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->EFRSL.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_efrsl_reg_t hri_gmac_read_EFRSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->EFRSL.reg;
}

static inline hri_gmac_efrn_reg_t hri_gmac_get_EFRN_RUD_bf(const void *const hw, hri_gmac_efrn_reg_t mask)
{
	return (((Gmac *)hw)->EFRN.reg & GMAC_EFRN_RUD(mask)) >> GMAC_EFRN_RUD_Pos;
}

static inline hri_gmac_efrn_reg_t hri_gmac_read_EFRN_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->EFRN.reg & GMAC_EFRN_RUD_Msk) >> GMAC_EFRN_RUD_Pos;
}

static inline hri_gmac_efrn_reg_t hri_gmac_get_EFRN_reg(const void *const hw, hri_gmac_efrn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->EFRN.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_efrn_reg_t hri_gmac_read_EFRN_reg(const void *const hw)
{
	return ((Gmac *)hw)->EFRN.reg;
}

static inline hri_gmac_peftsl_reg_t hri_gmac_get_PEFTSL_RUD_bf(const void *const hw, hri_gmac_peftsl_reg_t mask)
{
	return (((Gmac *)hw)->PEFTSL.reg & GMAC_PEFTSL_RUD(mask)) >> GMAC_PEFTSL_RUD_Pos;
}

static inline hri_gmac_peftsl_reg_t hri_gmac_read_PEFTSL_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->PEFTSL.reg & GMAC_PEFTSL_RUD_Msk) >> GMAC_PEFTSL_RUD_Pos;
}

static inline hri_gmac_peftsl_reg_t hri_gmac_get_PEFTSL_reg(const void *const hw, hri_gmac_peftsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->PEFTSL.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_peftsl_reg_t hri_gmac_read_PEFTSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->PEFTSL.reg;
}

static inline hri_gmac_peftn_reg_t hri_gmac_get_PEFTN_RUD_bf(const void *const hw, hri_gmac_peftn_reg_t mask)
{
	return (((Gmac *)hw)->PEFTN.reg & GMAC_PEFTN_RUD(mask)) >> GMAC_PEFTN_RUD_Pos;
}

static inline hri_gmac_peftn_reg_t hri_gmac_read_PEFTN_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->PEFTN.reg & GMAC_PEFTN_RUD_Msk) >> GMAC_PEFTN_RUD_Pos;
}

static inline hri_gmac_peftn_reg_t hri_gmac_get_PEFTN_reg(const void *const hw, hri_gmac_peftn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->PEFTN.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_peftn_reg_t hri_gmac_read_PEFTN_reg(const void *const hw)
{
	return ((Gmac *)hw)->PEFTN.reg;
}

static inline hri_gmac_pefrsl_reg_t hri_gmac_get_PEFRSL_RUD_bf(const void *const hw, hri_gmac_pefrsl_reg_t mask)
{
	return (((Gmac *)hw)->PEFRSL.reg & GMAC_PEFRSL_RUD(mask)) >> GMAC_PEFRSL_RUD_Pos;
}

static inline hri_gmac_pefrsl_reg_t hri_gmac_read_PEFRSL_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->PEFRSL.reg & GMAC_PEFRSL_RUD_Msk) >> GMAC_PEFRSL_RUD_Pos;
}

static inline hri_gmac_pefrsl_reg_t hri_gmac_get_PEFRSL_reg(const void *const hw, hri_gmac_pefrsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->PEFRSL.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pefrsl_reg_t hri_gmac_read_PEFRSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->PEFRSL.reg;
}

static inline hri_gmac_pefrn_reg_t hri_gmac_get_PEFRN_RUD_bf(const void *const hw, hri_gmac_pefrn_reg_t mask)
{
	return (((Gmac *)hw)->PEFRN.reg & GMAC_PEFRN_RUD(mask)) >> GMAC_PEFRN_RUD_Pos;
}

static inline hri_gmac_pefrn_reg_t hri_gmac_read_PEFRN_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->PEFRN.reg & GMAC_PEFRN_RUD_Msk) >> GMAC_PEFRN_RUD_Pos;
}

static inline hri_gmac_pefrn_reg_t hri_gmac_get_PEFRN_reg(const void *const hw, hri_gmac_pefrn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->PEFRN.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pefrn_reg_t hri_gmac_read_PEFRN_reg(const void *const hw)
{
	return ((Gmac *)hw)->PEFRN.reg;
}

static inline hri_gmac_rlpitr_reg_t hri_gmac_get_RLPITR_RLPITR_bf(const void *const hw, hri_gmac_rlpitr_reg_t mask)
{
	return (((Gmac *)hw)->RLPITR.reg & GMAC_RLPITR_RLPITR(mask)) >> GMAC_RLPITR_RLPITR_Pos;
}

static inline hri_gmac_rlpitr_reg_t hri_gmac_read_RLPITR_RLPITR_bf(const void *const hw)
{
	return (((Gmac *)hw)->RLPITR.reg & GMAC_RLPITR_RLPITR_Msk) >> GMAC_RLPITR_RLPITR_Pos;
}

static inline hri_gmac_rlpitr_reg_t hri_gmac_get_RLPITR_reg(const void *const hw, hri_gmac_rlpitr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->RLPITR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rlpitr_reg_t hri_gmac_read_RLPITR_reg(const void *const hw)
{
	return ((Gmac *)hw)->RLPITR.reg;
}

static inline hri_gmac_rlpiti_reg_t hri_gmac_get_RLPITI_RLPITI_bf(const void *const hw, hri_gmac_rlpiti_reg_t mask)
{
	return (((Gmac *)hw)->RLPITI.reg & GMAC_RLPITI_RLPITI(mask)) >> GMAC_RLPITI_RLPITI_Pos;
}

static inline hri_gmac_rlpiti_reg_t hri_gmac_read_RLPITI_RLPITI_bf(const void *const hw)
{
	return (((Gmac *)hw)->RLPITI.reg & GMAC_RLPITI_RLPITI_Msk) >> GMAC_RLPITI_RLPITI_Pos;
}

static inline hri_gmac_rlpiti_reg_t hri_gmac_get_RLPITI_reg(const void *const hw, hri_gmac_rlpiti_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->RLPITI.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rlpiti_reg_t hri_gmac_read_RLPITI_reg(const void *const hw)
{
	return ((Gmac *)hw)->RLPITI.reg;
}

static inline hri_gmac_tlpitr_reg_t hri_gmac_get_TLPITR_TLPITR_bf(const void *const hw, hri_gmac_tlpitr_reg_t mask)
{
	return (((Gmac *)hw)->TLPITR.reg & GMAC_TLPITR_TLPITR(mask)) >> GMAC_TLPITR_TLPITR_Pos;
}

static inline hri_gmac_tlpitr_reg_t hri_gmac_read_TLPITR_TLPITR_bf(const void *const hw)
{
	return (((Gmac *)hw)->TLPITR.reg & GMAC_TLPITR_TLPITR_Msk) >> GMAC_TLPITR_TLPITR_Pos;
}

static inline hri_gmac_tlpitr_reg_t hri_gmac_get_TLPITR_reg(const void *const hw, hri_gmac_tlpitr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TLPITR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tlpitr_reg_t hri_gmac_read_TLPITR_reg(const void *const hw)
{
	return ((Gmac *)hw)->TLPITR.reg;
}

static inline hri_gmac_tlpiti_reg_t hri_gmac_get_TLPITI_TLPITI_bf(const void *const hw, hri_gmac_tlpiti_reg_t mask)
{
	return (((Gmac *)hw)->TLPITI.reg & GMAC_TLPITI_TLPITI(mask)) >> GMAC_TLPITI_TLPITI_Pos;
}

static inline hri_gmac_tlpiti_reg_t hri_gmac_read_TLPITI_TLPITI_bf(const void *const hw)
{
	return (((Gmac *)hw)->TLPITI.reg & GMAC_TLPITI_TLPITI_Msk) >> GMAC_TLPITI_TLPITI_Pos;
}

static inline hri_gmac_tlpiti_reg_t hri_gmac_get_TLPITI_reg(const void *const hw, hri_gmac_tlpiti_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TLPITI.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tlpiti_reg_t hri_gmac_read_TLPITI_reg(const void *const hw)
{
	return ((Gmac *)hw)->TLPITI.reg;
}

static inline void hri_gmac_set_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NCR.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncr_reg_t hri_gmac_get_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->NCR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NCR.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NCR.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NCR.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncr_reg_t hri_gmac_read_NCR_reg(const void *const hw)
{
	return ((Gmac *)hw)->NCR.reg;
}

static inline void hri_gmac_set_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NCFGR.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_get_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->NCFGR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NCFGR.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NCFGR.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NCFGR.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_read_NCFGR_reg(const void *const hw)
{
	return ((Gmac *)hw)->NCFGR.reg;
}

static inline void hri_gmac_set_UR_reg(const void *const hw, hri_gmac_ur_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->UR.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ur_reg_t hri_gmac_get_UR_reg(const void *const hw, hri_gmac_ur_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->UR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_UR_reg(const void *const hw, hri_gmac_ur_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->UR.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_UR_reg(const void *const hw, hri_gmac_ur_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->UR.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_UR_reg(const void *const hw, hri_gmac_ur_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->UR.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ur_reg_t hri_gmac_read_UR_reg(const void *const hw)
{
	return ((Gmac *)hw)->UR.reg;
}

static inline void hri_gmac_set_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->DCFGR.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_get_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->DCFGR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->DCFGR.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->DCFGR.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->DCFGR.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_read_DCFGR_reg(const void *const hw)
{
	return ((Gmac *)hw)->DCFGR.reg;
}

static inline void hri_gmac_set_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSR.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsr_reg_t hri_gmac_get_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TSR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSR.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSR.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSR.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsr_reg_t hri_gmac_read_TSR_reg(const void *const hw)
{
	return ((Gmac *)hw)->TSR.reg;
}

static inline void hri_gmac_set_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RBQB.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqb_reg_t hri_gmac_get_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->RBQB.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RBQB.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RBQB.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RBQB.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqb_reg_t hri_gmac_read_RBQB_reg(const void *const hw)
{
	return ((Gmac *)hw)->RBQB.reg;
}

static inline void hri_gmac_set_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TBQB.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqb_reg_t hri_gmac_get_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TBQB.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TBQB.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TBQB.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TBQB.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqb_reg_t hri_gmac_read_TBQB_reg(const void *const hw)
{
	return ((Gmac *)hw)->TBQB.reg;
}

static inline void hri_gmac_set_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RSR.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rsr_reg_t hri_gmac_get_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->RSR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RSR.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RSR.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RSR.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rsr_reg_t hri_gmac_read_RSR_reg(const void *const hw)
{
	return ((Gmac *)hw)->RSR.reg;
}

static inline void hri_gmac_set_ISR_reg(const void *const hw, hri_gmac_isr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->ISR.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_isr_reg_t hri_gmac_get_ISR_reg(const void *const hw, hri_gmac_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->ISR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_ISR_reg(const void *const hw, hri_gmac_isr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->ISR.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ISR_reg(const void *const hw, hri_gmac_isr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->ISR.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ISR_reg(const void *const hw, hri_gmac_isr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->ISR.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_isr_reg_t hri_gmac_read_ISR_reg(const void *const hw)
{
	return ((Gmac *)hw)->ISR.reg;
}

static inline void hri_gmac_set_MAN_reg(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->MAN.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_get_MAN_reg(const void *const hw, hri_gmac_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->MAN.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_MAN_reg(const void *const hw, hri_gmac_man_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->MAN.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_MAN_reg(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->MAN.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_MAN_reg(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->MAN.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_read_MAN_reg(const void *const hw)
{
	return ((Gmac *)hw)->MAN.reg;
}

static inline void hri_gmac_set_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPQ.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpq_reg_t hri_gmac_get_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TPQ.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPQ.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPQ.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPQ.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpq_reg_t hri_gmac_read_TPQ_reg(const void *const hw)
{
	return ((Gmac *)hw)->TPQ.reg;
}

static inline void hri_gmac_set_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPSF.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpsf_reg_t hri_gmac_get_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TPSF.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPSF.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPSF.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPSF.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpsf_reg_t hri_gmac_read_TPSF_reg(const void *const hw)
{
	return ((Gmac *)hw)->TPSF.reg;
}

static inline void hri_gmac_set_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RPSF.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rpsf_reg_t hri_gmac_get_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->RPSF.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RPSF.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RPSF.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RPSF.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rpsf_reg_t hri_gmac_read_RPSF_reg(const void *const hw)
{
	return ((Gmac *)hw)->RPSF.reg;
}

static inline void hri_gmac_set_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RJFML.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rjfml_reg_t hri_gmac_get_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->RJFML.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RJFML.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RJFML.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->RJFML.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rjfml_reg_t hri_gmac_read_RJFML_reg(const void *const hw)
{
	return ((Gmac *)hw)->RJFML.reg;
}

static inline void hri_gmac_set_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->HRB.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrb_reg_t hri_gmac_get_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->HRB.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->HRB.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->HRB.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->HRB.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrb_reg_t hri_gmac_read_HRB_reg(const void *const hw)
{
	return ((Gmac *)hw)->HRB.reg;
}

static inline void hri_gmac_set_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->HRT.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrt_reg_t hri_gmac_get_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->HRT.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->HRT.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->HRT.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->HRT.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrt_reg_t hri_gmac_read_HRT_reg(const void *const hw)
{
	return ((Gmac *)hw)->HRT.reg;
}

static inline void hri_gmac_set_TIDM_reg(const void *const hw, uint8_t index, hri_gmac_tidm_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TIDM[index].reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm_reg_t hri_gmac_get_TIDM_reg(const void *const hw, uint8_t index, hri_gmac_tidm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TIDM[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TIDM_reg(const void *const hw, uint8_t index, hri_gmac_tidm_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TIDM[index].reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM_reg(const void *const hw, uint8_t index, hri_gmac_tidm_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TIDM[index].reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM_reg(const void *const hw, uint8_t index, hri_gmac_tidm_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TIDM[index].reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm_reg_t hri_gmac_read_TIDM_reg(const void *const hw, uint8_t index)
{
	return ((Gmac *)hw)->TIDM[index].reg;
}

static inline void hri_gmac_set_WOL_reg(const void *const hw, hri_gmac_wol_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->WOL.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_wol_reg_t hri_gmac_get_WOL_reg(const void *const hw, hri_gmac_wol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->WOL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_WOL_reg(const void *const hw, hri_gmac_wol_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->WOL.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_WOL_reg(const void *const hw, hri_gmac_wol_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->WOL.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_WOL_reg(const void *const hw, hri_gmac_wol_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->WOL.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_wol_reg_t hri_gmac_read_WOL_reg(const void *const hw)
{
	return ((Gmac *)hw)->WOL.reg;
}

static inline void hri_gmac_set_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->IPGS.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ipgs_reg_t hri_gmac_get_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->IPGS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->IPGS.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->IPGS.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->IPGS.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ipgs_reg_t hri_gmac_read_IPGS_reg(const void *const hw)
{
	return ((Gmac *)hw)->IPGS.reg;
}

static inline void hri_gmac_set_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SVLAN.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_svlan_reg_t hri_gmac_get_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->SVLAN.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SVLAN.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SVLAN.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SVLAN.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_svlan_reg_t hri_gmac_read_SVLAN_reg(const void *const hw)
{
	return ((Gmac *)hw)->SVLAN.reg;
}

static inline void hri_gmac_set_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPFCP.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpfcp_reg_t hri_gmac_get_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TPFCP.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPFCP.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPFCP.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TPFCP.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpfcp_reg_t hri_gmac_read_TPFCP_reg(const void *const hw)
{
	return ((Gmac *)hw)->TPFCP.reg;
}

static inline void hri_gmac_set_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SAMB1.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samb1_reg_t hri_gmac_get_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->SAMB1.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SAMB1.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SAMB1.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SAMB1.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samb1_reg_t hri_gmac_read_SAMB1_reg(const void *const hw)
{
	return ((Gmac *)hw)->SAMB1.reg;
}

static inline void hri_gmac_set_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SAMT1.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samt1_reg_t hri_gmac_get_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->SAMT1.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SAMT1.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SAMT1.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SAMT1.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samt1_reg_t hri_gmac_read_SAMT1_reg(const void *const hw)
{
	return ((Gmac *)hw)->SAMT1.reg;
}

static inline void hri_gmac_set_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NSC.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_nsc_reg_t hri_gmac_get_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->NSC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NSC.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NSC.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->NSC.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_nsc_reg_t hri_gmac_read_NSC_reg(const void *const hw)
{
	return ((Gmac *)hw)->NSC.reg;
}

static inline void hri_gmac_set_SCL_reg(const void *const hw, hri_gmac_scl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SCL.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_scl_reg_t hri_gmac_get_SCL_reg(const void *const hw, hri_gmac_scl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->SCL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SCL_reg(const void *const hw, hri_gmac_scl_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SCL.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SCL_reg(const void *const hw, hri_gmac_scl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SCL.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SCL_reg(const void *const hw, hri_gmac_scl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SCL.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_scl_reg_t hri_gmac_read_SCL_reg(const void *const hw)
{
	return ((Gmac *)hw)->SCL.reg;
}

static inline void hri_gmac_set_SCH_reg(const void *const hw, hri_gmac_sch_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SCH.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sch_reg_t hri_gmac_get_SCH_reg(const void *const hw, hri_gmac_sch_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->SCH.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SCH_reg(const void *const hw, hri_gmac_sch_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SCH.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SCH_reg(const void *const hw, hri_gmac_sch_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SCH.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SCH_reg(const void *const hw, hri_gmac_sch_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->SCH.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sch_reg_t hri_gmac_read_SCH_reg(const void *const hw)
{
	return ((Gmac *)hw)->SCH.reg;
}

static inline void hri_gmac_set_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TISUBN.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tisubn_reg_t hri_gmac_get_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TISUBN.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TISUBN.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TISUBN.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TISUBN.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tisubn_reg_t hri_gmac_read_TISUBN_reg(const void *const hw)
{
	return ((Gmac *)hw)->TISUBN.reg;
}

static inline void hri_gmac_set_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSH.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsh_reg_t hri_gmac_get_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TSH.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSH.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSH.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSH.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsh_reg_t hri_gmac_read_TSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->TSH.reg;
}

static inline void hri_gmac_set_TSSSL_reg(const void *const hw, hri_gmac_tsssl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSSSL.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsssl_reg_t hri_gmac_get_TSSSL_reg(const void *const hw, hri_gmac_tsssl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TSSSL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TSSSL_reg(const void *const hw, hri_gmac_tsssl_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSSSL.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSSSL_reg(const void *const hw, hri_gmac_tsssl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSSSL.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSSSL_reg(const void *const hw, hri_gmac_tsssl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSSSL.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsssl_reg_t hri_gmac_read_TSSSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->TSSSL.reg;
}

static inline void hri_gmac_set_TSSN_reg(const void *const hw, hri_gmac_tssn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSSN.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tssn_reg_t hri_gmac_get_TSSN_reg(const void *const hw, hri_gmac_tssn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TSSN.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TSSN_reg(const void *const hw, hri_gmac_tssn_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSSN.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSSN_reg(const void *const hw, hri_gmac_tssn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSSN.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSSN_reg(const void *const hw, hri_gmac_tssn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSSN.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tssn_reg_t hri_gmac_read_TSSN_reg(const void *const hw)
{
	return ((Gmac *)hw)->TSSN.reg;
}

static inline void hri_gmac_set_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSL.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsl_reg_t hri_gmac_get_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TSL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSL.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSL.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TSL.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsl_reg_t hri_gmac_read_TSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->TSL.reg;
}

static inline void hri_gmac_set_TN_reg(const void *const hw, hri_gmac_tn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TN.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tn_reg_t hri_gmac_get_TN_reg(const void *const hw, hri_gmac_tn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TN.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TN_reg(const void *const hw, hri_gmac_tn_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TN.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TN_reg(const void *const hw, hri_gmac_tn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TN.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TN_reg(const void *const hw, hri_gmac_tn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TN.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tn_reg_t hri_gmac_read_TN_reg(const void *const hw)
{
	return ((Gmac *)hw)->TN.reg;
}

static inline void hri_gmac_set_TI_reg(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TI.reg |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_get_TI_reg(const void *const hw, hri_gmac_ti_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->TI.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TI_reg(const void *const hw, hri_gmac_ti_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TI.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TI_reg(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TI.reg &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TI_reg(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TI.reg ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_read_TI_reg(const void *const hw)
{
	return ((Gmac *)hw)->TI.reg;
}

static inline void hri_gmac_write_TA_reg(const void *const hw, hri_gmac_ta_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->TA.reg = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_GMAC_E54_H_INCLUDED */
#endif /* _SAME54_GMAC_COMPONENT_ */
