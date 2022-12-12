/**
 * \file
 *
 * \brief SAM GMAC
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

#ifdef _SAME70_GMAC_COMPONENT_
#ifndef _HRI_GMAC_E70B_H_INCLUDED_
#define _HRI_GMAC_E70B_H_INCLUDED_

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
typedef uint32_t hri_gmac_cbscr_reg_t;
typedef uint32_t hri_gmac_cbsisqa_reg_t;
typedef uint32_t hri_gmac_cbsisqb_reg_t;
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
typedef uint32_t hri_gmac_imrpq_reg_t;
typedef uint32_t hri_gmac_ipgs_reg_t;
typedef uint32_t hri_gmac_isr_reg_t;
typedef uint32_t hri_gmac_isrpq_reg_t;
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
typedef uint32_t hri_gmac_rbqbapq_reg_t;
typedef uint32_t hri_gmac_rbsrpq_reg_t;
typedef uint32_t hri_gmac_rjfml_reg_t;
typedef uint32_t hri_gmac_roe_reg_t;
typedef uint32_t hri_gmac_rpq_reg_t;
typedef uint32_t hri_gmac_rpsf_reg_t;
typedef uint32_t hri_gmac_rre_reg_t;
typedef uint32_t hri_gmac_rse_reg_t;
typedef uint32_t hri_gmac_rsr_reg_t;
typedef uint32_t hri_gmac_rxlpi_reg_t;
typedef uint32_t hri_gmac_rxlpitime_reg_t;
typedef uint32_t hri_gmac_sab_reg_t;
typedef uint32_t hri_gmac_samb1_reg_t;
typedef uint32_t hri_gmac_samt1_reg_t;
typedef uint32_t hri_gmac_sat_reg_t;
typedef uint32_t hri_gmac_scf_reg_t;
typedef uint32_t hri_gmac_sch_reg_t;
typedef uint32_t hri_gmac_scl_reg_t;
typedef uint32_t hri_gmac_st1rpq_reg_t;
typedef uint32_t hri_gmac_st2cw0_reg_t;
typedef uint32_t hri_gmac_st2cw1_reg_t;
typedef uint32_t hri_gmac_st2er_reg_t;
typedef uint32_t hri_gmac_st2rpq_reg_t;
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
typedef uint32_t hri_gmac_tbqbapq_reg_t;
typedef uint32_t hri_gmac_tce_reg_t;
typedef uint32_t hri_gmac_ti_reg_t;
typedef uint32_t hri_gmac_tidm1_reg_t;
typedef uint32_t hri_gmac_tidm2_reg_t;
typedef uint32_t hri_gmac_tidm3_reg_t;
typedef uint32_t hri_gmac_tidm4_reg_t;
typedef uint32_t hri_gmac_tisubn_reg_t;
typedef uint32_t hri_gmac_tmxbfr_reg_t;
typedef uint32_t hri_gmac_tn_reg_t;
typedef uint32_t hri_gmac_tpfcp_reg_t;
typedef uint32_t hri_gmac_tpq_reg_t;
typedef uint32_t hri_gmac_tpsf_reg_t;
typedef uint32_t hri_gmac_tsh_reg_t;
typedef uint32_t hri_gmac_tsl_reg_t;
typedef uint32_t hri_gmac_tsr_reg_t;
typedef uint32_t hri_gmac_tur_reg_t;
typedef uint32_t hri_gmac_txlpi_reg_t;
typedef uint32_t hri_gmac_txlpitime_reg_t;
typedef uint32_t hri_gmac_uce_reg_t;
typedef uint32_t hri_gmac_ufr_reg_t;
typedef uint32_t hri_gmac_ur_reg_t;
typedef uint32_t hri_gmac_wol_reg_t;
typedef uint32_t hri_gmacsa_sab_reg_t;
typedef uint32_t hri_gmacsa_sat_reg_t;
typedef uint32_t hri_gmacst2cw_st2cw0_reg_t;
typedef uint32_t hri_gmacst2cw_st2cw1_reg_t;

static inline bool hri_gmac_get_ISR_MFS_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_MFS) >> GMAC_ISR_MFS_Pos;
}

static inline bool hri_gmac_get_ISR_RCOMP_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_RCOMP) >> GMAC_ISR_RCOMP_Pos;
}

static inline bool hri_gmac_get_ISR_RXUBR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_RXUBR) >> GMAC_ISR_RXUBR_Pos;
}

static inline bool hri_gmac_get_ISR_TXUBR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_TXUBR) >> GMAC_ISR_TXUBR_Pos;
}

static inline bool hri_gmac_get_ISR_TUR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_TUR) >> GMAC_ISR_TUR_Pos;
}

static inline bool hri_gmac_get_ISR_RLEX_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_RLEX) >> GMAC_ISR_RLEX_Pos;
}

static inline bool hri_gmac_get_ISR_TFC_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_TFC) >> GMAC_ISR_TFC_Pos;
}

static inline bool hri_gmac_get_ISR_TCOMP_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_TCOMP) >> GMAC_ISR_TCOMP_Pos;
}

static inline bool hri_gmac_get_ISR_ROVR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_ROVR) >> GMAC_ISR_ROVR_Pos;
}

static inline bool hri_gmac_get_ISR_HRESP_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_HRESP) >> GMAC_ISR_HRESP_Pos;
}

static inline bool hri_gmac_get_ISR_PFNZ_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_PFNZ) >> GMAC_ISR_PFNZ_Pos;
}

static inline bool hri_gmac_get_ISR_PTZ_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_PTZ) >> GMAC_ISR_PTZ_Pos;
}

static inline bool hri_gmac_get_ISR_PFTR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_PFTR) >> GMAC_ISR_PFTR_Pos;
}

static inline bool hri_gmac_get_ISR_DRQFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_DRQFR) >> GMAC_ISR_DRQFR_Pos;
}

static inline bool hri_gmac_get_ISR_SFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_SFR) >> GMAC_ISR_SFR_Pos;
}

static inline bool hri_gmac_get_ISR_DRQFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_DRQFT) >> GMAC_ISR_DRQFT_Pos;
}

static inline bool hri_gmac_get_ISR_SFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_SFT) >> GMAC_ISR_SFT_Pos;
}

static inline bool hri_gmac_get_ISR_PDRQFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_PDRQFR) >> GMAC_ISR_PDRQFR_Pos;
}

static inline bool hri_gmac_get_ISR_PDRSFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_PDRSFR) >> GMAC_ISR_PDRSFR_Pos;
}

static inline bool hri_gmac_get_ISR_PDRQFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_PDRQFT) >> GMAC_ISR_PDRQFT_Pos;
}

static inline bool hri_gmac_get_ISR_PDRSFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_PDRSFT) >> GMAC_ISR_PDRSFT_Pos;
}

static inline bool hri_gmac_get_ISR_SRI_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_SRI) >> GMAC_ISR_SRI_Pos;
}

static inline bool hri_gmac_get_ISR_RXLPISBC_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_RXLPISBC) >> GMAC_ISR_RXLPISBC_Pos;
}

static inline bool hri_gmac_get_ISR_WOL_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_WOL) >> GMAC_ISR_WOL_Pos;
}

static inline bool hri_gmac_get_ISR_TSUTIMCOMP_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ISR & GMAC_ISR_TSUTIMCOMP) >> GMAC_ISR_TSUTIMCOMP_Pos;
}

static inline hri_gmac_isr_reg_t hri_gmac_get_ISR_reg(const void *const hw, hri_gmac_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_isr_reg_t hri_gmac_read_ISR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_ISR;
}

static inline bool hri_gmac_get_ISRPQ_RCOMP_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_ISRPQ[index] & GMAC_ISRPQ_RCOMP) >> GMAC_ISRPQ_RCOMP_Pos;
}

static inline bool hri_gmac_get_ISRPQ_RXUBR_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_ISRPQ[index] & GMAC_ISRPQ_RXUBR) >> GMAC_ISRPQ_RXUBR_Pos;
}

static inline bool hri_gmac_get_ISRPQ_RLEX_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_ISRPQ[index] & GMAC_ISRPQ_RLEX) >> GMAC_ISRPQ_RLEX_Pos;
}

static inline bool hri_gmac_get_ISRPQ_TFC_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_ISRPQ[index] & GMAC_ISRPQ_TFC) >> GMAC_ISRPQ_TFC_Pos;
}

static inline bool hri_gmac_get_ISRPQ_TCOMP_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_ISRPQ[index] & GMAC_ISRPQ_TCOMP) >> GMAC_ISRPQ_TCOMP_Pos;
}

static inline bool hri_gmac_get_ISRPQ_ROVR_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_ISRPQ[index] & GMAC_ISRPQ_ROVR) >> GMAC_ISRPQ_ROVR_Pos;
}

static inline bool hri_gmac_get_ISRPQ_HRESP_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_ISRPQ[index] & GMAC_ISRPQ_HRESP) >> GMAC_ISRPQ_HRESP_Pos;
}

static inline hri_gmac_isrpq_reg_t hri_gmac_get_ISRPQ_reg(const void *const hw, uint8_t index,
                                                          hri_gmac_isrpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ISRPQ[index];
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_isrpq_reg_t hri_gmac_read_ISRPQ_reg(const void *const hw, uint8_t index)
{
	return ((Gmac *)hw)->GMAC_ISRPQ[index];
}

static inline void hri_gmac_set_IMR_MFS_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_MFS;
}

static inline bool hri_gmac_get_IMR_MFS_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_MFS) >> GMAC_IMR_MFS_Pos;
}

static inline void hri_gmac_write_IMR_MFS_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_MFS;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_MFS;
	}
}

static inline void hri_gmac_clear_IMR_MFS_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_MFS;
}

static inline void hri_gmac_set_IMR_RCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_RCOMP;
}

static inline bool hri_gmac_get_IMR_RCOMP_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_RCOMP) >> GMAC_IMR_RCOMP_Pos;
}

static inline void hri_gmac_write_IMR_RCOMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_RCOMP;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_RCOMP;
	}
}

static inline void hri_gmac_clear_IMR_RCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_RCOMP;
}

static inline void hri_gmac_set_IMR_RXUBR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_RXUBR;
}

static inline bool hri_gmac_get_IMR_RXUBR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_RXUBR) >> GMAC_IMR_RXUBR_Pos;
}

static inline void hri_gmac_write_IMR_RXUBR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_RXUBR;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_RXUBR;
	}
}

static inline void hri_gmac_clear_IMR_RXUBR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_RXUBR;
}

static inline void hri_gmac_set_IMR_TXUBR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_TXUBR;
}

static inline bool hri_gmac_get_IMR_TXUBR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_TXUBR) >> GMAC_IMR_TXUBR_Pos;
}

static inline void hri_gmac_write_IMR_TXUBR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TXUBR;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_TXUBR;
	}
}

static inline void hri_gmac_clear_IMR_TXUBR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TXUBR;
}

static inline void hri_gmac_set_IMR_TUR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_TUR;
}

static inline bool hri_gmac_get_IMR_TUR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_TUR) >> GMAC_IMR_TUR_Pos;
}

static inline void hri_gmac_write_IMR_TUR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TUR;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_TUR;
	}
}

static inline void hri_gmac_clear_IMR_TUR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TUR;
}

static inline void hri_gmac_set_IMR_RLEX_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_RLEX;
}

static inline bool hri_gmac_get_IMR_RLEX_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_RLEX) >> GMAC_IMR_RLEX_Pos;
}

static inline void hri_gmac_write_IMR_RLEX_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_RLEX;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_RLEX;
	}
}

static inline void hri_gmac_clear_IMR_RLEX_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_RLEX;
}

static inline void hri_gmac_set_IMR_TFC_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_TFC;
}

static inline bool hri_gmac_get_IMR_TFC_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_TFC) >> GMAC_IMR_TFC_Pos;
}

static inline void hri_gmac_write_IMR_TFC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TFC;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_TFC;
	}
}

static inline void hri_gmac_clear_IMR_TFC_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TFC;
}

static inline void hri_gmac_set_IMR_TCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_TCOMP;
}

static inline bool hri_gmac_get_IMR_TCOMP_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_TCOMP) >> GMAC_IMR_TCOMP_Pos;
}

static inline void hri_gmac_write_IMR_TCOMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TCOMP;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_TCOMP;
	}
}

static inline void hri_gmac_clear_IMR_TCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TCOMP;
}

static inline void hri_gmac_set_IMR_ROVR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_ROVR;
}

static inline bool hri_gmac_get_IMR_ROVR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_ROVR) >> GMAC_IMR_ROVR_Pos;
}

static inline void hri_gmac_write_IMR_ROVR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_ROVR;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_ROVR;
	}
}

static inline void hri_gmac_clear_IMR_ROVR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_ROVR;
}

static inline void hri_gmac_set_IMR_HRESP_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_HRESP;
}

static inline bool hri_gmac_get_IMR_HRESP_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_HRESP) >> GMAC_IMR_HRESP_Pos;
}

static inline void hri_gmac_write_IMR_HRESP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_HRESP;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_HRESP;
	}
}

static inline void hri_gmac_clear_IMR_HRESP_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_HRESP;
}

static inline void hri_gmac_set_IMR_PFNZ_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_PFNZ;
}

static inline bool hri_gmac_get_IMR_PFNZ_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_PFNZ) >> GMAC_IMR_PFNZ_Pos;
}

static inline void hri_gmac_write_IMR_PFNZ_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PFNZ;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_PFNZ;
	}
}

static inline void hri_gmac_clear_IMR_PFNZ_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PFNZ;
}

static inline void hri_gmac_set_IMR_PTZ_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_PTZ;
}

static inline bool hri_gmac_get_IMR_PTZ_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_PTZ) >> GMAC_IMR_PTZ_Pos;
}

static inline void hri_gmac_write_IMR_PTZ_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PTZ;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_PTZ;
	}
}

static inline void hri_gmac_clear_IMR_PTZ_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PTZ;
}

static inline void hri_gmac_set_IMR_PFTR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_PFTR;
}

static inline bool hri_gmac_get_IMR_PFTR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_PFTR) >> GMAC_IMR_PFTR_Pos;
}

static inline void hri_gmac_write_IMR_PFTR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PFTR;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_PFTR;
	}
}

static inline void hri_gmac_clear_IMR_PFTR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PFTR;
}

static inline void hri_gmac_set_IMR_EXINT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_EXINT;
}

static inline bool hri_gmac_get_IMR_EXINT_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_EXINT) >> GMAC_IMR_EXINT_Pos;
}

static inline void hri_gmac_write_IMR_EXINT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_EXINT;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_EXINT;
	}
}

static inline void hri_gmac_clear_IMR_EXINT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_EXINT;
}

static inline void hri_gmac_set_IMR_DRQFR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_DRQFR;
}

static inline bool hri_gmac_get_IMR_DRQFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_DRQFR) >> GMAC_IMR_DRQFR_Pos;
}

static inline void hri_gmac_write_IMR_DRQFR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_DRQFR;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_DRQFR;
	}
}

static inline void hri_gmac_clear_IMR_DRQFR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_DRQFR;
}

static inline void hri_gmac_set_IMR_SFR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_SFR;
}

static inline bool hri_gmac_get_IMR_SFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_SFR) >> GMAC_IMR_SFR_Pos;
}

static inline void hri_gmac_write_IMR_SFR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_SFR;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_SFR;
	}
}

static inline void hri_gmac_clear_IMR_SFR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_SFR;
}

static inline void hri_gmac_set_IMR_DRQFT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_DRQFT;
}

static inline bool hri_gmac_get_IMR_DRQFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_DRQFT) >> GMAC_IMR_DRQFT_Pos;
}

static inline void hri_gmac_write_IMR_DRQFT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_DRQFT;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_DRQFT;
	}
}

static inline void hri_gmac_clear_IMR_DRQFT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_DRQFT;
}

static inline void hri_gmac_set_IMR_SFT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_SFT;
}

static inline bool hri_gmac_get_IMR_SFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_SFT) >> GMAC_IMR_SFT_Pos;
}

static inline void hri_gmac_write_IMR_SFT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_SFT;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_SFT;
	}
}

static inline void hri_gmac_clear_IMR_SFT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_SFT;
}

static inline void hri_gmac_set_IMR_PDRQFR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_PDRQFR;
}

static inline bool hri_gmac_get_IMR_PDRQFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_PDRQFR) >> GMAC_IMR_PDRQFR_Pos;
}

static inline void hri_gmac_write_IMR_PDRQFR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PDRQFR;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_PDRQFR;
	}
}

static inline void hri_gmac_clear_IMR_PDRQFR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PDRQFR;
}

static inline void hri_gmac_set_IMR_PDRSFR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_PDRSFR;
}

static inline bool hri_gmac_get_IMR_PDRSFR_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_PDRSFR) >> GMAC_IMR_PDRSFR_Pos;
}

static inline void hri_gmac_write_IMR_PDRSFR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PDRSFR;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_PDRSFR;
	}
}

static inline void hri_gmac_clear_IMR_PDRSFR_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PDRSFR;
}

static inline void hri_gmac_set_IMR_PDRQFT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_PDRQFT;
}

static inline bool hri_gmac_get_IMR_PDRQFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_PDRQFT) >> GMAC_IMR_PDRQFT_Pos;
}

static inline void hri_gmac_write_IMR_PDRQFT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PDRQFT;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_PDRQFT;
	}
}

static inline void hri_gmac_clear_IMR_PDRQFT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PDRQFT;
}

static inline void hri_gmac_set_IMR_PDRSFT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_PDRSFT;
}

static inline bool hri_gmac_get_IMR_PDRSFT_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_PDRSFT) >> GMAC_IMR_PDRSFT_Pos;
}

static inline void hri_gmac_write_IMR_PDRSFT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PDRSFT;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_PDRSFT;
	}
}

static inline void hri_gmac_clear_IMR_PDRSFT_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_PDRSFT;
}

static inline void hri_gmac_set_IMR_SRI_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_SRI;
}

static inline bool hri_gmac_get_IMR_SRI_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_SRI) >> GMAC_IMR_SRI_Pos;
}

static inline void hri_gmac_write_IMR_SRI_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_SRI;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_SRI;
	}
}

static inline void hri_gmac_clear_IMR_SRI_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_SRI;
}

static inline void hri_gmac_set_IMR_RXLPISBC_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_RXLPISBC;
}

static inline bool hri_gmac_get_IMR_RXLPISBC_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_RXLPISBC) >> GMAC_IMR_RXLPISBC_Pos;
}

static inline void hri_gmac_write_IMR_RXLPISBC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_RXLPISBC;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_RXLPISBC;
	}
}

static inline void hri_gmac_clear_IMR_RXLPISBC_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_RXLPISBC;
}

static inline void hri_gmac_set_IMR_WOL_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_WOL;
}

static inline bool hri_gmac_get_IMR_WOL_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_WOL) >> GMAC_IMR_WOL_Pos;
}

static inline void hri_gmac_write_IMR_WOL_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_WOL;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_WOL;
	}
}

static inline void hri_gmac_clear_IMR_WOL_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_WOL;
}

static inline void hri_gmac_set_IMR_TSUTIMCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IER = GMAC_IMR_TSUTIMCOMP;
}

static inline bool hri_gmac_get_IMR_TSUTIMCOMP_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IMR & GMAC_IMR_TSUTIMCOMP) >> GMAC_IMR_TSUTIMCOMP_Pos;
}

static inline void hri_gmac_write_IMR_TSUTIMCOMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TSUTIMCOMP;
	} else {
		((Gmac *)hw)->GMAC_IER = GMAC_IMR_TSUTIMCOMP;
	}
}

static inline void hri_gmac_clear_IMR_TSUTIMCOMP_bit(const void *const hw)
{
	((Gmac *)hw)->GMAC_IDR = GMAC_IMR_TSUTIMCOMP;
}

static inline void hri_gmac_set_IMR_reg(const void *const hw, hri_gmac_imr_reg_t mask)
{
	((Gmac *)hw)->GMAC_IER = mask;
}

static inline hri_gmac_imr_reg_t hri_gmac_get_IMR_reg(const void *const hw, hri_gmac_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_imr_reg_t hri_gmac_read_IMR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_IMR;
}

static inline void hri_gmac_write_IMR_reg(const void *const hw, hri_gmac_imr_reg_t data)
{
	((Gmac *)hw)->GMAC_IER = data;
	((Gmac *)hw)->GMAC_IDR = ~data;
}

static inline void hri_gmac_clear_IMR_reg(const void *const hw, hri_gmac_imr_reg_t mask)
{
	((Gmac *)hw)->GMAC_IDR = mask;
}

static inline void hri_gmac_set_IMRPQ_RCOMP_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_RCOMP;
}

static inline bool hri_gmac_get_IMRPQ_RCOMP_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_IMRPQ[index] & GMAC_IMRPQ_RCOMP) >> GMAC_IMRPQ_RCOMP_Pos;
}

static inline void hri_gmac_write_IMRPQ_RCOMP_bit(const void *const hw, uint8_t index, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_RCOMP;
	} else {
		((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_RCOMP;
	}
}

static inline void hri_gmac_clear_IMRPQ_RCOMP_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_RCOMP;
}

static inline void hri_gmac_set_IMRPQ_RXUBR_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_RXUBR;
}

static inline bool hri_gmac_get_IMRPQ_RXUBR_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_IMRPQ[index] & GMAC_IMRPQ_RXUBR) >> GMAC_IMRPQ_RXUBR_Pos;
}

static inline void hri_gmac_write_IMRPQ_RXUBR_bit(const void *const hw, uint8_t index, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_RXUBR;
	} else {
		((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_RXUBR;
	}
}

static inline void hri_gmac_clear_IMRPQ_RXUBR_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_RXUBR;
}

static inline void hri_gmac_set_IMRPQ_RLEX_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_RLEX;
}

static inline bool hri_gmac_get_IMRPQ_RLEX_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_IMRPQ[index] & GMAC_IMRPQ_RLEX) >> GMAC_IMRPQ_RLEX_Pos;
}

static inline void hri_gmac_write_IMRPQ_RLEX_bit(const void *const hw, uint8_t index, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_RLEX;
	} else {
		((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_RLEX;
	}
}

static inline void hri_gmac_clear_IMRPQ_RLEX_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_RLEX;
}

static inline void hri_gmac_set_IMRPQ_AHB_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_AHB;
}

static inline bool hri_gmac_get_IMRPQ_AHB_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_IMRPQ[index] & GMAC_IMRPQ_AHB) >> GMAC_IMRPQ_AHB_Pos;
}

static inline void hri_gmac_write_IMRPQ_AHB_bit(const void *const hw, uint8_t index, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_AHB;
	} else {
		((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_AHB;
	}
}

static inline void hri_gmac_clear_IMRPQ_AHB_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_AHB;
}

static inline void hri_gmac_set_IMRPQ_TCOMP_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_TCOMP;
}

static inline bool hri_gmac_get_IMRPQ_TCOMP_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_IMRPQ[index] & GMAC_IMRPQ_TCOMP) >> GMAC_IMRPQ_TCOMP_Pos;
}

static inline void hri_gmac_write_IMRPQ_TCOMP_bit(const void *const hw, uint8_t index, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_TCOMP;
	} else {
		((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_TCOMP;
	}
}

static inline void hri_gmac_clear_IMRPQ_TCOMP_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_TCOMP;
}

static inline void hri_gmac_set_IMRPQ_ROVR_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_ROVR;
}

static inline bool hri_gmac_get_IMRPQ_ROVR_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_IMRPQ[index] & GMAC_IMRPQ_ROVR) >> GMAC_IMRPQ_ROVR_Pos;
}

static inline void hri_gmac_write_IMRPQ_ROVR_bit(const void *const hw, uint8_t index, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_ROVR;
	} else {
		((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_ROVR;
	}
}

static inline void hri_gmac_clear_IMRPQ_ROVR_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_ROVR;
}

static inline void hri_gmac_set_IMRPQ_HRESP_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_HRESP;
}

static inline bool hri_gmac_get_IMRPQ_HRESP_bit(const void *const hw, uint8_t index)
{
	return (((Gmac *)hw)->GMAC_IMRPQ[index] & GMAC_IMRPQ_HRESP) >> GMAC_IMRPQ_HRESP_Pos;
}

static inline void hri_gmac_write_IMRPQ_HRESP_bit(const void *const hw, uint8_t index, bool value)
{
	if (value == 0x0) {
		((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_HRESP;
	} else {
		((Gmac *)hw)->GMAC_IERPQ[index] = GMAC_IMRPQ_HRESP;
	}
}

static inline void hri_gmac_clear_IMRPQ_HRESP_bit(const void *const hw, uint8_t index)
{
	((Gmac *)hw)->GMAC_IDRPQ[index] = GMAC_IMRPQ_HRESP;
}

static inline void hri_gmac_set_IMRPQ_reg(const void *const hw, uint8_t index, hri_gmac_imrpq_reg_t mask)
{
	((Gmac *)hw)->GMAC_IERPQ[index] = mask;
}

static inline hri_gmac_imrpq_reg_t hri_gmac_get_IMRPQ_reg(const void *const hw, uint8_t index,
                                                          hri_gmac_imrpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_IMRPQ[index];
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_imrpq_reg_t hri_gmac_read_IMRPQ_reg(const void *const hw, uint8_t index)
{
	return ((Gmac *)hw)->GMAC_IMRPQ[index];
}

static inline void hri_gmac_write_IMRPQ_reg(const void *const hw, uint8_t index, hri_gmac_imrpq_reg_t data)
{
	((Gmac *)hw)->GMAC_IERPQ[index] = data;
	((Gmac *)hw)->GMAC_IDRPQ[index] = ~data;
}

static inline void hri_gmac_clear_IMRPQ_reg(const void *const hw, uint8_t index, hri_gmac_imrpq_reg_t mask)
{
	((Gmac *)hw)->GMAC_IDRPQ[index] = mask;
}

static inline bool hri_gmac_get_NSR_MDIO_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_NSR & GMAC_NSR_MDIO) > 0;
}

static inline bool hri_gmac_get_NSR_IDLE_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_NSR & GMAC_NSR_IDLE) > 0;
}

static inline bool hri_gmac_get_NSR_RXLPIS_bit(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_NSR & GMAC_NSR_RXLPIS) > 0;
}

static inline hri_gmac_nsr_reg_t hri_gmac_get_NSR_reg(const void *const hw, hri_gmac_nsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NSR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_nsr_reg_t hri_gmac_read_NSR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_NSR;
}

static inline hri_gmac_rpq_reg_t hri_gmac_get_RPQ_RPQ_bf(const void *const hw, hri_gmac_rpq_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_RPQ & GMAC_RPQ_RPQ(mask)) >> GMAC_RPQ_RPQ_Pos;
}

static inline hri_gmac_rpq_reg_t hri_gmac_read_RPQ_RPQ_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_RPQ & GMAC_RPQ_RPQ_Msk) >> GMAC_RPQ_RPQ_Pos;
}

static inline hri_gmac_rpq_reg_t hri_gmac_get_RPQ_reg(const void *const hw, hri_gmac_rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RPQ;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rpq_reg_t hri_gmac_read_RPQ_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_RPQ;
}

static inline hri_gmac_eftsh_reg_t hri_gmac_get_EFTSH_RUD_bf(const void *const hw, hri_gmac_eftsh_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_EFTSH & GMAC_EFTSH_RUD(mask)) >> GMAC_EFTSH_RUD_Pos;
}

static inline hri_gmac_eftsh_reg_t hri_gmac_read_EFTSH_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_EFTSH & GMAC_EFTSH_RUD_Msk) >> GMAC_EFTSH_RUD_Pos;
}

static inline hri_gmac_eftsh_reg_t hri_gmac_get_EFTSH_reg(const void *const hw, hri_gmac_eftsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_EFTSH;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_eftsh_reg_t hri_gmac_read_EFTSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_EFTSH;
}

static inline hri_gmac_efrsh_reg_t hri_gmac_get_EFRSH_RUD_bf(const void *const hw, hri_gmac_efrsh_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_EFRSH & GMAC_EFRSH_RUD(mask)) >> GMAC_EFRSH_RUD_Pos;
}

static inline hri_gmac_efrsh_reg_t hri_gmac_read_EFRSH_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_EFRSH & GMAC_EFRSH_RUD_Msk) >> GMAC_EFRSH_RUD_Pos;
}

static inline hri_gmac_efrsh_reg_t hri_gmac_get_EFRSH_reg(const void *const hw, hri_gmac_efrsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_EFRSH;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_efrsh_reg_t hri_gmac_read_EFRSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_EFRSH;
}

static inline hri_gmac_peftsh_reg_t hri_gmac_get_PEFTSH_RUD_bf(const void *const hw, hri_gmac_peftsh_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_PEFTSH & GMAC_PEFTSH_RUD(mask)) >> GMAC_PEFTSH_RUD_Pos;
}

static inline hri_gmac_peftsh_reg_t hri_gmac_read_PEFTSH_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_PEFTSH & GMAC_PEFTSH_RUD_Msk) >> GMAC_PEFTSH_RUD_Pos;
}

static inline hri_gmac_peftsh_reg_t hri_gmac_get_PEFTSH_reg(const void *const hw, hri_gmac_peftsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_PEFTSH;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_peftsh_reg_t hri_gmac_read_PEFTSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_PEFTSH;
}

static inline hri_gmac_pefrsh_reg_t hri_gmac_get_PEFRSH_RUD_bf(const void *const hw, hri_gmac_pefrsh_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_PEFRSH & GMAC_PEFRSH_RUD(mask)) >> GMAC_PEFRSH_RUD_Pos;
}

static inline hri_gmac_pefrsh_reg_t hri_gmac_read_PEFRSH_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_PEFRSH & GMAC_PEFRSH_RUD_Msk) >> GMAC_PEFRSH_RUD_Pos;
}

static inline hri_gmac_pefrsh_reg_t hri_gmac_get_PEFRSH_reg(const void *const hw, hri_gmac_pefrsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_PEFRSH;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pefrsh_reg_t hri_gmac_read_PEFRSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_PEFRSH;
}

static inline hri_gmac_otlo_reg_t hri_gmac_get_OTLO_TXO_bf(const void *const hw, hri_gmac_otlo_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_OTLO & GMAC_OTLO_TXO(mask)) >> GMAC_OTLO_TXO_Pos;
}

static inline hri_gmac_otlo_reg_t hri_gmac_read_OTLO_TXO_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_OTLO & GMAC_OTLO_TXO_Msk) >> GMAC_OTLO_TXO_Pos;
}

static inline hri_gmac_otlo_reg_t hri_gmac_get_OTLO_reg(const void *const hw, hri_gmac_otlo_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_OTLO;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_otlo_reg_t hri_gmac_read_OTLO_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_OTLO;
}

static inline hri_gmac_othi_reg_t hri_gmac_get_OTHI_TXO_bf(const void *const hw, hri_gmac_othi_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_OTHI & GMAC_OTHI_TXO(mask)) >> GMAC_OTHI_TXO_Pos;
}

static inline hri_gmac_othi_reg_t hri_gmac_read_OTHI_TXO_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_OTHI & GMAC_OTHI_TXO_Msk) >> GMAC_OTHI_TXO_Pos;
}

static inline hri_gmac_othi_reg_t hri_gmac_get_OTHI_reg(const void *const hw, hri_gmac_othi_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_OTHI;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_othi_reg_t hri_gmac_read_OTHI_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_OTHI;
}

static inline hri_gmac_ft_reg_t hri_gmac_get_FT_FTX_bf(const void *const hw, hri_gmac_ft_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_FT & GMAC_FT_FTX(mask)) >> GMAC_FT_FTX_Pos;
}

static inline hri_gmac_ft_reg_t hri_gmac_read_FT_FTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_FT & GMAC_FT_FTX_Msk) >> GMAC_FT_FTX_Pos;
}

static inline hri_gmac_ft_reg_t hri_gmac_get_FT_reg(const void *const hw, hri_gmac_ft_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_FT;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ft_reg_t hri_gmac_read_FT_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_FT;
}

static inline hri_gmac_bcft_reg_t hri_gmac_get_BCFT_BFTX_bf(const void *const hw, hri_gmac_bcft_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_BCFT & GMAC_BCFT_BFTX(mask)) >> GMAC_BCFT_BFTX_Pos;
}

static inline hri_gmac_bcft_reg_t hri_gmac_read_BCFT_BFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_BCFT & GMAC_BCFT_BFTX_Msk) >> GMAC_BCFT_BFTX_Pos;
}

static inline hri_gmac_bcft_reg_t hri_gmac_get_BCFT_reg(const void *const hw, hri_gmac_bcft_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_BCFT;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_bcft_reg_t hri_gmac_read_BCFT_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_BCFT;
}

static inline hri_gmac_mft_reg_t hri_gmac_get_MFT_MFTX_bf(const void *const hw, hri_gmac_mft_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_MFT & GMAC_MFT_MFTX(mask)) >> GMAC_MFT_MFTX_Pos;
}

static inline hri_gmac_mft_reg_t hri_gmac_read_MFT_MFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_MFT & GMAC_MFT_MFTX_Msk) >> GMAC_MFT_MFTX_Pos;
}

static inline hri_gmac_mft_reg_t hri_gmac_get_MFT_reg(const void *const hw, hri_gmac_mft_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MFT;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_mft_reg_t hri_gmac_read_MFT_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_MFT;
}

static inline hri_gmac_pft_reg_t hri_gmac_get_PFT_PFTX_bf(const void *const hw, hri_gmac_pft_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_PFT & GMAC_PFT_PFTX(mask)) >> GMAC_PFT_PFTX_Pos;
}

static inline hri_gmac_pft_reg_t hri_gmac_read_PFT_PFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_PFT & GMAC_PFT_PFTX_Msk) >> GMAC_PFT_PFTX_Pos;
}

static inline hri_gmac_pft_reg_t hri_gmac_get_PFT_reg(const void *const hw, hri_gmac_pft_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_PFT;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pft_reg_t hri_gmac_read_PFT_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_PFT;
}

static inline hri_gmac_bft64_reg_t hri_gmac_get_BFT64_NFTX_bf(const void *const hw, hri_gmac_bft64_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_BFT64 & GMAC_BFT64_NFTX(mask)) >> GMAC_BFT64_NFTX_Pos;
}

static inline hri_gmac_bft64_reg_t hri_gmac_read_BFT64_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_BFT64 & GMAC_BFT64_NFTX_Msk) >> GMAC_BFT64_NFTX_Pos;
}

static inline hri_gmac_bft64_reg_t hri_gmac_get_BFT64_reg(const void *const hw, hri_gmac_bft64_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_BFT64;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_bft64_reg_t hri_gmac_read_BFT64_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_BFT64;
}

static inline hri_gmac_tbft127_reg_t hri_gmac_get_TBFT127_NFTX_bf(const void *const hw, hri_gmac_tbft127_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFT127 & GMAC_TBFT127_NFTX(mask)) >> GMAC_TBFT127_NFTX_Pos;
}

static inline hri_gmac_tbft127_reg_t hri_gmac_read_TBFT127_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFT127 & GMAC_TBFT127_NFTX_Msk) >> GMAC_TBFT127_NFTX_Pos;
}

static inline hri_gmac_tbft127_reg_t hri_gmac_get_TBFT127_reg(const void *const hw, hri_gmac_tbft127_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFT127;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft127_reg_t hri_gmac_read_TBFT127_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFT127;
}

static inline hri_gmac_tbft255_reg_t hri_gmac_get_TBFT255_NFTX_bf(const void *const hw, hri_gmac_tbft255_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFT255 & GMAC_TBFT255_NFTX(mask)) >> GMAC_TBFT255_NFTX_Pos;
}

static inline hri_gmac_tbft255_reg_t hri_gmac_read_TBFT255_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFT255 & GMAC_TBFT255_NFTX_Msk) >> GMAC_TBFT255_NFTX_Pos;
}

static inline hri_gmac_tbft255_reg_t hri_gmac_get_TBFT255_reg(const void *const hw, hri_gmac_tbft255_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFT255;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft255_reg_t hri_gmac_read_TBFT255_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFT255;
}

static inline hri_gmac_tbft511_reg_t hri_gmac_get_TBFT511_NFTX_bf(const void *const hw, hri_gmac_tbft511_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFT511 & GMAC_TBFT511_NFTX(mask)) >> GMAC_TBFT511_NFTX_Pos;
}

static inline hri_gmac_tbft511_reg_t hri_gmac_read_TBFT511_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFT511 & GMAC_TBFT511_NFTX_Msk) >> GMAC_TBFT511_NFTX_Pos;
}

static inline hri_gmac_tbft511_reg_t hri_gmac_get_TBFT511_reg(const void *const hw, hri_gmac_tbft511_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFT511;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft511_reg_t hri_gmac_read_TBFT511_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFT511;
}

static inline hri_gmac_tbft1023_reg_t hri_gmac_get_TBFT1023_NFTX_bf(const void *const hw, hri_gmac_tbft1023_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFT1023 & GMAC_TBFT1023_NFTX(mask)) >> GMAC_TBFT1023_NFTX_Pos;
}

static inline hri_gmac_tbft1023_reg_t hri_gmac_read_TBFT1023_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFT1023 & GMAC_TBFT1023_NFTX_Msk) >> GMAC_TBFT1023_NFTX_Pos;
}

static inline hri_gmac_tbft1023_reg_t hri_gmac_get_TBFT1023_reg(const void *const hw, hri_gmac_tbft1023_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFT1023;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft1023_reg_t hri_gmac_read_TBFT1023_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFT1023;
}

static inline hri_gmac_tbft1518_reg_t hri_gmac_get_TBFT1518_NFTX_bf(const void *const hw, hri_gmac_tbft1518_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFT1518 & GMAC_TBFT1518_NFTX(mask)) >> GMAC_TBFT1518_NFTX_Pos;
}

static inline hri_gmac_tbft1518_reg_t hri_gmac_read_TBFT1518_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFT1518 & GMAC_TBFT1518_NFTX_Msk) >> GMAC_TBFT1518_NFTX_Pos;
}

static inline hri_gmac_tbft1518_reg_t hri_gmac_get_TBFT1518_reg(const void *const hw, hri_gmac_tbft1518_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFT1518;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbft1518_reg_t hri_gmac_read_TBFT1518_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFT1518;
}

static inline hri_gmac_gtbft1518_reg_t hri_gmac_get_GTBFT1518_NFTX_bf(const void *const        hw,
                                                                      hri_gmac_gtbft1518_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_GTBFT1518 & GMAC_GTBFT1518_NFTX(mask)) >> GMAC_GTBFT1518_NFTX_Pos;
}

static inline hri_gmac_gtbft1518_reg_t hri_gmac_read_GTBFT1518_NFTX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_GTBFT1518 & GMAC_GTBFT1518_NFTX_Msk) >> GMAC_GTBFT1518_NFTX_Pos;
}

static inline hri_gmac_gtbft1518_reg_t hri_gmac_get_GTBFT1518_reg(const void *const hw, hri_gmac_gtbft1518_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_GTBFT1518;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_gtbft1518_reg_t hri_gmac_read_GTBFT1518_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_GTBFT1518;
}

static inline hri_gmac_tur_reg_t hri_gmac_get_TUR_TXUNR_bf(const void *const hw, hri_gmac_tur_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TUR & GMAC_TUR_TXUNR(mask)) >> GMAC_TUR_TXUNR_Pos;
}

static inline hri_gmac_tur_reg_t hri_gmac_read_TUR_TXUNR_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TUR & GMAC_TUR_TXUNR_Msk) >> GMAC_TUR_TXUNR_Pos;
}

static inline hri_gmac_tur_reg_t hri_gmac_get_TUR_reg(const void *const hw, hri_gmac_tur_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TUR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tur_reg_t hri_gmac_read_TUR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TUR;
}

static inline hri_gmac_scf_reg_t hri_gmac_get_SCF_SCOL_bf(const void *const hw, hri_gmac_scf_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_SCF & GMAC_SCF_SCOL(mask)) >> GMAC_SCF_SCOL_Pos;
}

static inline hri_gmac_scf_reg_t hri_gmac_read_SCF_SCOL_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_SCF & GMAC_SCF_SCOL_Msk) >> GMAC_SCF_SCOL_Pos;
}

static inline hri_gmac_scf_reg_t hri_gmac_get_SCF_reg(const void *const hw, hri_gmac_scf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SCF;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_scf_reg_t hri_gmac_read_SCF_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_SCF;
}

static inline hri_gmac_mcf_reg_t hri_gmac_get_MCF_MCOL_bf(const void *const hw, hri_gmac_mcf_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_MCF & GMAC_MCF_MCOL(mask)) >> GMAC_MCF_MCOL_Pos;
}

static inline hri_gmac_mcf_reg_t hri_gmac_read_MCF_MCOL_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_MCF & GMAC_MCF_MCOL_Msk) >> GMAC_MCF_MCOL_Pos;
}

static inline hri_gmac_mcf_reg_t hri_gmac_get_MCF_reg(const void *const hw, hri_gmac_mcf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MCF;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_mcf_reg_t hri_gmac_read_MCF_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_MCF;
}

static inline hri_gmac_ec_reg_t hri_gmac_get_EC_XCOL_bf(const void *const hw, hri_gmac_ec_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_EC & GMAC_EC_XCOL(mask)) >> GMAC_EC_XCOL_Pos;
}

static inline hri_gmac_ec_reg_t hri_gmac_read_EC_XCOL_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_EC & GMAC_EC_XCOL_Msk) >> GMAC_EC_XCOL_Pos;
}

static inline hri_gmac_ec_reg_t hri_gmac_get_EC_reg(const void *const hw, hri_gmac_ec_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_EC;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ec_reg_t hri_gmac_read_EC_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_EC;
}

static inline hri_gmac_lc_reg_t hri_gmac_get_LC_LCOL_bf(const void *const hw, hri_gmac_lc_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_LC & GMAC_LC_LCOL(mask)) >> GMAC_LC_LCOL_Pos;
}

static inline hri_gmac_lc_reg_t hri_gmac_read_LC_LCOL_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_LC & GMAC_LC_LCOL_Msk) >> GMAC_LC_LCOL_Pos;
}

static inline hri_gmac_lc_reg_t hri_gmac_get_LC_reg(const void *const hw, hri_gmac_lc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_LC;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_lc_reg_t hri_gmac_read_LC_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_LC;
}

static inline hri_gmac_dtf_reg_t hri_gmac_get_DTF_DEFT_bf(const void *const hw, hri_gmac_dtf_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_DTF & GMAC_DTF_DEFT(mask)) >> GMAC_DTF_DEFT_Pos;
}

static inline hri_gmac_dtf_reg_t hri_gmac_read_DTF_DEFT_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_DTF & GMAC_DTF_DEFT_Msk) >> GMAC_DTF_DEFT_Pos;
}

static inline hri_gmac_dtf_reg_t hri_gmac_get_DTF_reg(const void *const hw, hri_gmac_dtf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DTF;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_dtf_reg_t hri_gmac_read_DTF_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_DTF;
}

static inline hri_gmac_cse_reg_t hri_gmac_get_CSE_CSR_bf(const void *const hw, hri_gmac_cse_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_CSE & GMAC_CSE_CSR(mask)) >> GMAC_CSE_CSR_Pos;
}

static inline hri_gmac_cse_reg_t hri_gmac_read_CSE_CSR_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_CSE & GMAC_CSE_CSR_Msk) >> GMAC_CSE_CSR_Pos;
}

static inline hri_gmac_cse_reg_t hri_gmac_get_CSE_reg(const void *const hw, hri_gmac_cse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CSE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_cse_reg_t hri_gmac_read_CSE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_CSE;
}

static inline hri_gmac_orlo_reg_t hri_gmac_get_ORLO_RXO_bf(const void *const hw, hri_gmac_orlo_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_ORLO & GMAC_ORLO_RXO(mask)) >> GMAC_ORLO_RXO_Pos;
}

static inline hri_gmac_orlo_reg_t hri_gmac_read_ORLO_RXO_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ORLO & GMAC_ORLO_RXO_Msk) >> GMAC_ORLO_RXO_Pos;
}

static inline hri_gmac_orlo_reg_t hri_gmac_get_ORLO_reg(const void *const hw, hri_gmac_orlo_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ORLO;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_orlo_reg_t hri_gmac_read_ORLO_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_ORLO;
}

static inline hri_gmac_orhi_reg_t hri_gmac_get_ORHI_RXO_bf(const void *const hw, hri_gmac_orhi_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_ORHI & GMAC_ORHI_RXO(mask)) >> GMAC_ORHI_RXO_Pos;
}

static inline hri_gmac_orhi_reg_t hri_gmac_read_ORHI_RXO_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ORHI & GMAC_ORHI_RXO_Msk) >> GMAC_ORHI_RXO_Pos;
}

static inline hri_gmac_orhi_reg_t hri_gmac_get_ORHI_reg(const void *const hw, hri_gmac_orhi_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ORHI;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_orhi_reg_t hri_gmac_read_ORHI_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_ORHI;
}

static inline hri_gmac_fr_reg_t hri_gmac_get_FR_FRX_bf(const void *const hw, hri_gmac_fr_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_FR & GMAC_FR_FRX(mask)) >> GMAC_FR_FRX_Pos;
}

static inline hri_gmac_fr_reg_t hri_gmac_read_FR_FRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_FR & GMAC_FR_FRX_Msk) >> GMAC_FR_FRX_Pos;
}

static inline hri_gmac_fr_reg_t hri_gmac_get_FR_reg(const void *const hw, hri_gmac_fr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_FR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_fr_reg_t hri_gmac_read_FR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_FR;
}

static inline hri_gmac_bcfr_reg_t hri_gmac_get_BCFR_BFRX_bf(const void *const hw, hri_gmac_bcfr_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_BCFR & GMAC_BCFR_BFRX(mask)) >> GMAC_BCFR_BFRX_Pos;
}

static inline hri_gmac_bcfr_reg_t hri_gmac_read_BCFR_BFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_BCFR & GMAC_BCFR_BFRX_Msk) >> GMAC_BCFR_BFRX_Pos;
}

static inline hri_gmac_bcfr_reg_t hri_gmac_get_BCFR_reg(const void *const hw, hri_gmac_bcfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_BCFR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_bcfr_reg_t hri_gmac_read_BCFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_BCFR;
}

static inline hri_gmac_mfr_reg_t hri_gmac_get_MFR_MFRX_bf(const void *const hw, hri_gmac_mfr_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_MFR & GMAC_MFR_MFRX(mask)) >> GMAC_MFR_MFRX_Pos;
}

static inline hri_gmac_mfr_reg_t hri_gmac_read_MFR_MFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_MFR & GMAC_MFR_MFRX_Msk) >> GMAC_MFR_MFRX_Pos;
}

static inline hri_gmac_mfr_reg_t hri_gmac_get_MFR_reg(const void *const hw, hri_gmac_mfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MFR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_mfr_reg_t hri_gmac_read_MFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_MFR;
}

static inline hri_gmac_pfr_reg_t hri_gmac_get_PFR_PFRX_bf(const void *const hw, hri_gmac_pfr_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_PFR & GMAC_PFR_PFRX(mask)) >> GMAC_PFR_PFRX_Pos;
}

static inline hri_gmac_pfr_reg_t hri_gmac_read_PFR_PFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_PFR & GMAC_PFR_PFRX_Msk) >> GMAC_PFR_PFRX_Pos;
}

static inline hri_gmac_pfr_reg_t hri_gmac_get_PFR_reg(const void *const hw, hri_gmac_pfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_PFR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pfr_reg_t hri_gmac_read_PFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_PFR;
}

static inline hri_gmac_bfr64_reg_t hri_gmac_get_BFR64_NFRX_bf(const void *const hw, hri_gmac_bfr64_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_BFR64 & GMAC_BFR64_NFRX(mask)) >> GMAC_BFR64_NFRX_Pos;
}

static inline hri_gmac_bfr64_reg_t hri_gmac_read_BFR64_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_BFR64 & GMAC_BFR64_NFRX_Msk) >> GMAC_BFR64_NFRX_Pos;
}

static inline hri_gmac_bfr64_reg_t hri_gmac_get_BFR64_reg(const void *const hw, hri_gmac_bfr64_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_BFR64;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_bfr64_reg_t hri_gmac_read_BFR64_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_BFR64;
}

static inline hri_gmac_tbfr127_reg_t hri_gmac_get_TBFR127_NFRX_bf(const void *const hw, hri_gmac_tbfr127_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFR127 & GMAC_TBFR127_NFRX(mask)) >> GMAC_TBFR127_NFRX_Pos;
}

static inline hri_gmac_tbfr127_reg_t hri_gmac_read_TBFR127_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFR127 & GMAC_TBFR127_NFRX_Msk) >> GMAC_TBFR127_NFRX_Pos;
}

static inline hri_gmac_tbfr127_reg_t hri_gmac_get_TBFR127_reg(const void *const hw, hri_gmac_tbfr127_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFR127;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr127_reg_t hri_gmac_read_TBFR127_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFR127;
}

static inline hri_gmac_tbfr255_reg_t hri_gmac_get_TBFR255_NFRX_bf(const void *const hw, hri_gmac_tbfr255_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFR255 & GMAC_TBFR255_NFRX(mask)) >> GMAC_TBFR255_NFRX_Pos;
}

static inline hri_gmac_tbfr255_reg_t hri_gmac_read_TBFR255_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFR255 & GMAC_TBFR255_NFRX_Msk) >> GMAC_TBFR255_NFRX_Pos;
}

static inline hri_gmac_tbfr255_reg_t hri_gmac_get_TBFR255_reg(const void *const hw, hri_gmac_tbfr255_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFR255;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr255_reg_t hri_gmac_read_TBFR255_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFR255;
}

static inline hri_gmac_tbfr511_reg_t hri_gmac_get_TBFR511_NFRX_bf(const void *const hw, hri_gmac_tbfr511_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFR511 & GMAC_TBFR511_NFRX(mask)) >> GMAC_TBFR511_NFRX_Pos;
}

static inline hri_gmac_tbfr511_reg_t hri_gmac_read_TBFR511_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFR511 & GMAC_TBFR511_NFRX_Msk) >> GMAC_TBFR511_NFRX_Pos;
}

static inline hri_gmac_tbfr511_reg_t hri_gmac_get_TBFR511_reg(const void *const hw, hri_gmac_tbfr511_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFR511;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr511_reg_t hri_gmac_read_TBFR511_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFR511;
}

static inline hri_gmac_tbfr1023_reg_t hri_gmac_get_TBFR1023_NFRX_bf(const void *const hw, hri_gmac_tbfr1023_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFR1023 & GMAC_TBFR1023_NFRX(mask)) >> GMAC_TBFR1023_NFRX_Pos;
}

static inline hri_gmac_tbfr1023_reg_t hri_gmac_read_TBFR1023_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFR1023 & GMAC_TBFR1023_NFRX_Msk) >> GMAC_TBFR1023_NFRX_Pos;
}

static inline hri_gmac_tbfr1023_reg_t hri_gmac_get_TBFR1023_reg(const void *const hw, hri_gmac_tbfr1023_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFR1023;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr1023_reg_t hri_gmac_read_TBFR1023_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFR1023;
}

static inline hri_gmac_tbfr1518_reg_t hri_gmac_get_TBFR1518_NFRX_bf(const void *const hw, hri_gmac_tbfr1518_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TBFR1518 & GMAC_TBFR1518_NFRX(mask)) >> GMAC_TBFR1518_NFRX_Pos;
}

static inline hri_gmac_tbfr1518_reg_t hri_gmac_read_TBFR1518_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TBFR1518 & GMAC_TBFR1518_NFRX_Msk) >> GMAC_TBFR1518_NFRX_Pos;
}

static inline hri_gmac_tbfr1518_reg_t hri_gmac_get_TBFR1518_reg(const void *const hw, hri_gmac_tbfr1518_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBFR1518;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tbfr1518_reg_t hri_gmac_read_TBFR1518_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBFR1518;
}

static inline hri_gmac_tmxbfr_reg_t hri_gmac_get_TMXBFR_NFRX_bf(const void *const hw, hri_gmac_tmxbfr_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TMXBFR & GMAC_TMXBFR_NFRX(mask)) >> GMAC_TMXBFR_NFRX_Pos;
}

static inline hri_gmac_tmxbfr_reg_t hri_gmac_read_TMXBFR_NFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TMXBFR & GMAC_TMXBFR_NFRX_Msk) >> GMAC_TMXBFR_NFRX_Pos;
}

static inline hri_gmac_tmxbfr_reg_t hri_gmac_get_TMXBFR_reg(const void *const hw, hri_gmac_tmxbfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TMXBFR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tmxbfr_reg_t hri_gmac_read_TMXBFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TMXBFR;
}

static inline hri_gmac_ufr_reg_t hri_gmac_get_UFR_UFRX_bf(const void *const hw, hri_gmac_ufr_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_UFR & GMAC_UFR_UFRX(mask)) >> GMAC_UFR_UFRX_Pos;
}

static inline hri_gmac_ufr_reg_t hri_gmac_read_UFR_UFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_UFR & GMAC_UFR_UFRX_Msk) >> GMAC_UFR_UFRX_Pos;
}

static inline hri_gmac_ufr_reg_t hri_gmac_get_UFR_reg(const void *const hw, hri_gmac_ufr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_UFR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ufr_reg_t hri_gmac_read_UFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_UFR;
}

static inline hri_gmac_ofr_reg_t hri_gmac_get_OFR_OFRX_bf(const void *const hw, hri_gmac_ofr_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_OFR & GMAC_OFR_OFRX(mask)) >> GMAC_OFR_OFRX_Pos;
}

static inline hri_gmac_ofr_reg_t hri_gmac_read_OFR_OFRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_OFR & GMAC_OFR_OFRX_Msk) >> GMAC_OFR_OFRX_Pos;
}

static inline hri_gmac_ofr_reg_t hri_gmac_get_OFR_reg(const void *const hw, hri_gmac_ofr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_OFR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ofr_reg_t hri_gmac_read_OFR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_OFR;
}

static inline hri_gmac_jr_reg_t hri_gmac_get_JR_JRX_bf(const void *const hw, hri_gmac_jr_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_JR & GMAC_JR_JRX(mask)) >> GMAC_JR_JRX_Pos;
}

static inline hri_gmac_jr_reg_t hri_gmac_read_JR_JRX_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_JR & GMAC_JR_JRX_Msk) >> GMAC_JR_JRX_Pos;
}

static inline hri_gmac_jr_reg_t hri_gmac_get_JR_reg(const void *const hw, hri_gmac_jr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_JR;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_jr_reg_t hri_gmac_read_JR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_JR;
}

static inline hri_gmac_fcse_reg_t hri_gmac_get_FCSE_FCKR_bf(const void *const hw, hri_gmac_fcse_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_FCSE & GMAC_FCSE_FCKR(mask)) >> GMAC_FCSE_FCKR_Pos;
}

static inline hri_gmac_fcse_reg_t hri_gmac_read_FCSE_FCKR_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_FCSE & GMAC_FCSE_FCKR_Msk) >> GMAC_FCSE_FCKR_Pos;
}

static inline hri_gmac_fcse_reg_t hri_gmac_get_FCSE_reg(const void *const hw, hri_gmac_fcse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_FCSE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_fcse_reg_t hri_gmac_read_FCSE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_FCSE;
}

static inline hri_gmac_lffe_reg_t hri_gmac_get_LFFE_LFER_bf(const void *const hw, hri_gmac_lffe_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_LFFE & GMAC_LFFE_LFER(mask)) >> GMAC_LFFE_LFER_Pos;
}

static inline hri_gmac_lffe_reg_t hri_gmac_read_LFFE_LFER_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_LFFE & GMAC_LFFE_LFER_Msk) >> GMAC_LFFE_LFER_Pos;
}

static inline hri_gmac_lffe_reg_t hri_gmac_get_LFFE_reg(const void *const hw, hri_gmac_lffe_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_LFFE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_lffe_reg_t hri_gmac_read_LFFE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_LFFE;
}

static inline hri_gmac_rse_reg_t hri_gmac_get_RSE_RXSE_bf(const void *const hw, hri_gmac_rse_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_RSE & GMAC_RSE_RXSE(mask)) >> GMAC_RSE_RXSE_Pos;
}

static inline hri_gmac_rse_reg_t hri_gmac_read_RSE_RXSE_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_RSE & GMAC_RSE_RXSE_Msk) >> GMAC_RSE_RXSE_Pos;
}

static inline hri_gmac_rse_reg_t hri_gmac_get_RSE_reg(const void *const hw, hri_gmac_rse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RSE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rse_reg_t hri_gmac_read_RSE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_RSE;
}

static inline hri_gmac_ae_reg_t hri_gmac_get_AE_AER_bf(const void *const hw, hri_gmac_ae_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_AE & GMAC_AE_AER(mask)) >> GMAC_AE_AER_Pos;
}

static inline hri_gmac_ae_reg_t hri_gmac_read_AE_AER_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_AE & GMAC_AE_AER_Msk) >> GMAC_AE_AER_Pos;
}

static inline hri_gmac_ae_reg_t hri_gmac_get_AE_reg(const void *const hw, hri_gmac_ae_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_AE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ae_reg_t hri_gmac_read_AE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_AE;
}

static inline hri_gmac_rre_reg_t hri_gmac_get_RRE_RXRER_bf(const void *const hw, hri_gmac_rre_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_RRE & GMAC_RRE_RXRER(mask)) >> GMAC_RRE_RXRER_Pos;
}

static inline hri_gmac_rre_reg_t hri_gmac_read_RRE_RXRER_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_RRE & GMAC_RRE_RXRER_Msk) >> GMAC_RRE_RXRER_Pos;
}

static inline hri_gmac_rre_reg_t hri_gmac_get_RRE_reg(const void *const hw, hri_gmac_rre_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RRE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rre_reg_t hri_gmac_read_RRE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_RRE;
}

static inline hri_gmac_roe_reg_t hri_gmac_get_ROE_RXOVR_bf(const void *const hw, hri_gmac_roe_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_ROE & GMAC_ROE_RXOVR(mask)) >> GMAC_ROE_RXOVR_Pos;
}

static inline hri_gmac_roe_reg_t hri_gmac_read_ROE_RXOVR_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_ROE & GMAC_ROE_RXOVR_Msk) >> GMAC_ROE_RXOVR_Pos;
}

static inline hri_gmac_roe_reg_t hri_gmac_get_ROE_reg(const void *const hw, hri_gmac_roe_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ROE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_roe_reg_t hri_gmac_read_ROE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_ROE;
}

static inline hri_gmac_ihce_reg_t hri_gmac_get_IHCE_HCKER_bf(const void *const hw, hri_gmac_ihce_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_IHCE & GMAC_IHCE_HCKER(mask)) >> GMAC_IHCE_HCKER_Pos;
}

static inline hri_gmac_ihce_reg_t hri_gmac_read_IHCE_HCKER_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_IHCE & GMAC_IHCE_HCKER_Msk) >> GMAC_IHCE_HCKER_Pos;
}

static inline hri_gmac_ihce_reg_t hri_gmac_get_IHCE_reg(const void *const hw, hri_gmac_ihce_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_IHCE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_ihce_reg_t hri_gmac_read_IHCE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_IHCE;
}

static inline hri_gmac_tce_reg_t hri_gmac_get_TCE_TCKER_bf(const void *const hw, hri_gmac_tce_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TCE & GMAC_TCE_TCKER(mask)) >> GMAC_TCE_TCKER_Pos;
}

static inline hri_gmac_tce_reg_t hri_gmac_read_TCE_TCKER_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TCE & GMAC_TCE_TCKER_Msk) >> GMAC_TCE_TCKER_Pos;
}

static inline hri_gmac_tce_reg_t hri_gmac_get_TCE_reg(const void *const hw, hri_gmac_tce_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TCE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_tce_reg_t hri_gmac_read_TCE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TCE;
}

static inline hri_gmac_uce_reg_t hri_gmac_get_UCE_UCKER_bf(const void *const hw, hri_gmac_uce_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_UCE & GMAC_UCE_UCKER(mask)) >> GMAC_UCE_UCKER_Pos;
}

static inline hri_gmac_uce_reg_t hri_gmac_read_UCE_UCKER_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_UCE & GMAC_UCE_UCKER_Msk) >> GMAC_UCE_UCKER_Pos;
}

static inline hri_gmac_uce_reg_t hri_gmac_get_UCE_reg(const void *const hw, hri_gmac_uce_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_UCE;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_uce_reg_t hri_gmac_read_UCE_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_UCE;
}

static inline hri_gmac_eftsl_reg_t hri_gmac_get_EFTSL_RUD_bf(const void *const hw, hri_gmac_eftsl_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_EFTSL & GMAC_EFTSL_RUD(mask)) >> GMAC_EFTSL_RUD_Pos;
}

static inline hri_gmac_eftsl_reg_t hri_gmac_read_EFTSL_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_EFTSL & GMAC_EFTSL_RUD_Msk) >> GMAC_EFTSL_RUD_Pos;
}

static inline hri_gmac_eftsl_reg_t hri_gmac_get_EFTSL_reg(const void *const hw, hri_gmac_eftsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_EFTSL;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_eftsl_reg_t hri_gmac_read_EFTSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_EFTSL;
}

static inline hri_gmac_eftn_reg_t hri_gmac_get_EFTN_RUD_bf(const void *const hw, hri_gmac_eftn_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_EFTN & GMAC_EFTN_RUD(mask)) >> GMAC_EFTN_RUD_Pos;
}

static inline hri_gmac_eftn_reg_t hri_gmac_read_EFTN_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_EFTN & GMAC_EFTN_RUD_Msk) >> GMAC_EFTN_RUD_Pos;
}

static inline hri_gmac_eftn_reg_t hri_gmac_get_EFTN_reg(const void *const hw, hri_gmac_eftn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_EFTN;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_eftn_reg_t hri_gmac_read_EFTN_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_EFTN;
}

static inline hri_gmac_efrsl_reg_t hri_gmac_get_EFRSL_RUD_bf(const void *const hw, hri_gmac_efrsl_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_EFRSL & GMAC_EFRSL_RUD(mask)) >> GMAC_EFRSL_RUD_Pos;
}

static inline hri_gmac_efrsl_reg_t hri_gmac_read_EFRSL_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_EFRSL & GMAC_EFRSL_RUD_Msk) >> GMAC_EFRSL_RUD_Pos;
}

static inline hri_gmac_efrsl_reg_t hri_gmac_get_EFRSL_reg(const void *const hw, hri_gmac_efrsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_EFRSL;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_efrsl_reg_t hri_gmac_read_EFRSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_EFRSL;
}

static inline hri_gmac_efrn_reg_t hri_gmac_get_EFRN_RUD_bf(const void *const hw, hri_gmac_efrn_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_EFRN & GMAC_EFRN_RUD(mask)) >> GMAC_EFRN_RUD_Pos;
}

static inline hri_gmac_efrn_reg_t hri_gmac_read_EFRN_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_EFRN & GMAC_EFRN_RUD_Msk) >> GMAC_EFRN_RUD_Pos;
}

static inline hri_gmac_efrn_reg_t hri_gmac_get_EFRN_reg(const void *const hw, hri_gmac_efrn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_EFRN;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_efrn_reg_t hri_gmac_read_EFRN_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_EFRN;
}

static inline hri_gmac_peftsl_reg_t hri_gmac_get_PEFTSL_RUD_bf(const void *const hw, hri_gmac_peftsl_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_PEFTSL & GMAC_PEFTSL_RUD(mask)) >> GMAC_PEFTSL_RUD_Pos;
}

static inline hri_gmac_peftsl_reg_t hri_gmac_read_PEFTSL_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_PEFTSL & GMAC_PEFTSL_RUD_Msk) >> GMAC_PEFTSL_RUD_Pos;
}

static inline hri_gmac_peftsl_reg_t hri_gmac_get_PEFTSL_reg(const void *const hw, hri_gmac_peftsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_PEFTSL;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_peftsl_reg_t hri_gmac_read_PEFTSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_PEFTSL;
}

static inline hri_gmac_peftn_reg_t hri_gmac_get_PEFTN_RUD_bf(const void *const hw, hri_gmac_peftn_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_PEFTN & GMAC_PEFTN_RUD(mask)) >> GMAC_PEFTN_RUD_Pos;
}

static inline hri_gmac_peftn_reg_t hri_gmac_read_PEFTN_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_PEFTN & GMAC_PEFTN_RUD_Msk) >> GMAC_PEFTN_RUD_Pos;
}

static inline hri_gmac_peftn_reg_t hri_gmac_get_PEFTN_reg(const void *const hw, hri_gmac_peftn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_PEFTN;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_peftn_reg_t hri_gmac_read_PEFTN_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_PEFTN;
}

static inline hri_gmac_pefrsl_reg_t hri_gmac_get_PEFRSL_RUD_bf(const void *const hw, hri_gmac_pefrsl_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_PEFRSL & GMAC_PEFRSL_RUD(mask)) >> GMAC_PEFRSL_RUD_Pos;
}

static inline hri_gmac_pefrsl_reg_t hri_gmac_read_PEFRSL_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_PEFRSL & GMAC_PEFRSL_RUD_Msk) >> GMAC_PEFRSL_RUD_Pos;
}

static inline hri_gmac_pefrsl_reg_t hri_gmac_get_PEFRSL_reg(const void *const hw, hri_gmac_pefrsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_PEFRSL;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pefrsl_reg_t hri_gmac_read_PEFRSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_PEFRSL;
}

static inline hri_gmac_pefrn_reg_t hri_gmac_get_PEFRN_RUD_bf(const void *const hw, hri_gmac_pefrn_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_PEFRN & GMAC_PEFRN_RUD(mask)) >> GMAC_PEFRN_RUD_Pos;
}

static inline hri_gmac_pefrn_reg_t hri_gmac_read_PEFRN_RUD_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_PEFRN & GMAC_PEFRN_RUD_Msk) >> GMAC_PEFRN_RUD_Pos;
}

static inline hri_gmac_pefrn_reg_t hri_gmac_get_PEFRN_reg(const void *const hw, hri_gmac_pefrn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_PEFRN;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_pefrn_reg_t hri_gmac_read_PEFRN_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_PEFRN;
}

static inline hri_gmac_rxlpi_reg_t hri_gmac_get_RXLPI_COUNT_bf(const void *const hw, hri_gmac_rxlpi_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_RXLPI & GMAC_RXLPI_COUNT(mask)) >> GMAC_RXLPI_COUNT_Pos;
}

static inline hri_gmac_rxlpi_reg_t hri_gmac_read_RXLPI_COUNT_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_RXLPI & GMAC_RXLPI_COUNT_Msk) >> GMAC_RXLPI_COUNT_Pos;
}

static inline hri_gmac_rxlpi_reg_t hri_gmac_get_RXLPI_reg(const void *const hw, hri_gmac_rxlpi_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RXLPI;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rxlpi_reg_t hri_gmac_read_RXLPI_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_RXLPI;
}

static inline hri_gmac_rxlpitime_reg_t hri_gmac_get_RXLPITIME_LPITIME_bf(const void *const        hw,
                                                                         hri_gmac_rxlpitime_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_RXLPITIME & GMAC_RXLPITIME_LPITIME(mask)) >> GMAC_RXLPITIME_LPITIME_Pos;
}

static inline hri_gmac_rxlpitime_reg_t hri_gmac_read_RXLPITIME_LPITIME_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_RXLPITIME & GMAC_RXLPITIME_LPITIME_Msk) >> GMAC_RXLPITIME_LPITIME_Pos;
}

static inline hri_gmac_rxlpitime_reg_t hri_gmac_get_RXLPITIME_reg(const void *const hw, hri_gmac_rxlpitime_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RXLPITIME;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_rxlpitime_reg_t hri_gmac_read_RXLPITIME_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_RXLPITIME;
}

static inline hri_gmac_txlpi_reg_t hri_gmac_get_TXLPI_COUNT_bf(const void *const hw, hri_gmac_txlpi_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TXLPI & GMAC_TXLPI_COUNT(mask)) >> GMAC_TXLPI_COUNT_Pos;
}

static inline hri_gmac_txlpi_reg_t hri_gmac_read_TXLPI_COUNT_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TXLPI & GMAC_TXLPI_COUNT_Msk) >> GMAC_TXLPI_COUNT_Pos;
}

static inline hri_gmac_txlpi_reg_t hri_gmac_get_TXLPI_reg(const void *const hw, hri_gmac_txlpi_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TXLPI;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_txlpi_reg_t hri_gmac_read_TXLPI_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TXLPI;
}

static inline hri_gmac_txlpitime_reg_t hri_gmac_get_TXLPITIME_LPITIME_bf(const void *const        hw,
                                                                         hri_gmac_txlpitime_reg_t mask)
{
	return (((Gmac *)hw)->GMAC_TXLPITIME & GMAC_TXLPITIME_LPITIME(mask)) >> GMAC_TXLPITIME_LPITIME_Pos;
}

static inline hri_gmac_txlpitime_reg_t hri_gmac_read_TXLPITIME_LPITIME_bf(const void *const hw)
{
	return (((Gmac *)hw)->GMAC_TXLPITIME & GMAC_TXLPITIME_LPITIME_Msk) >> GMAC_TXLPITIME_LPITIME_Pos;
}

static inline hri_gmac_txlpitime_reg_t hri_gmac_get_TXLPITIME_reg(const void *const hw, hri_gmac_txlpitime_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TXLPITIME;
	tmp &= mask;
	return tmp;
}

static inline hri_gmac_txlpitime_reg_t hri_gmac_read_TXLPITIME_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TXLPITIME;
}

static inline void hri_gmac_set_NCR_LBL_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_LBL;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_LBL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_LBL) >> GMAC_NCR_LBL_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_LBL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_LBL;
	tmp |= value << GMAC_NCR_LBL_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_LBL_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_LBL;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_LBL_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_LBL;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_RXEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_RXEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_RXEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_RXEN) >> GMAC_NCR_RXEN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_RXEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_RXEN;
	tmp |= value << GMAC_NCR_RXEN_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_RXEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_RXEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_RXEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_RXEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_TXEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_TXEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_TXEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_TXEN) >> GMAC_NCR_TXEN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_TXEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_TXEN;
	tmp |= value << GMAC_NCR_TXEN_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_TXEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_TXEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_TXEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_TXEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_MPE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_MPE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_MPE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_MPE) >> GMAC_NCR_MPE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_MPE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_MPE;
	tmp |= value << GMAC_NCR_MPE_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_MPE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_MPE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_MPE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_MPE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_CLRSTAT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_CLRSTAT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_CLRSTAT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_CLRSTAT) >> GMAC_NCR_CLRSTAT_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_CLRSTAT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_CLRSTAT;
	tmp |= value << GMAC_NCR_CLRSTAT_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_CLRSTAT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_CLRSTAT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_CLRSTAT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_CLRSTAT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_INCSTAT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_INCSTAT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_INCSTAT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_INCSTAT) >> GMAC_NCR_INCSTAT_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_INCSTAT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_INCSTAT;
	tmp |= value << GMAC_NCR_INCSTAT_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_INCSTAT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_INCSTAT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_INCSTAT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_INCSTAT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_WESTAT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_WESTAT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_WESTAT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_WESTAT) >> GMAC_NCR_WESTAT_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_WESTAT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_WESTAT;
	tmp |= value << GMAC_NCR_WESTAT_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_WESTAT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_WESTAT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_WESTAT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_WESTAT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_BP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_BP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_BP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_BP) >> GMAC_NCR_BP_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_BP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_BP;
	tmp |= value << GMAC_NCR_BP_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_BP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_BP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_BP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_BP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_TSTART_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_TSTART;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_TSTART_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_TSTART) >> GMAC_NCR_TSTART_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_TSTART_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_TSTART;
	tmp |= value << GMAC_NCR_TSTART_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_TSTART_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_TSTART;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_TSTART_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_TSTART;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_THALT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_THALT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_THALT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_THALT) >> GMAC_NCR_THALT_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_THALT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_THALT;
	tmp |= value << GMAC_NCR_THALT_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_THALT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_THALT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_THALT_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_THALT;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_TXPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_TXPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_TXPF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_TXPF) >> GMAC_NCR_TXPF_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_TXPF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_TXPF;
	tmp |= value << GMAC_NCR_TXPF_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_TXPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_TXPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_TXPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_TXPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_TXZQPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_TXZQPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_TXZQPF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_TXZQPF) >> GMAC_NCR_TXZQPF_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_TXZQPF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_TXZQPF;
	tmp |= value << GMAC_NCR_TXZQPF_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_TXZQPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_TXZQPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_TXZQPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_TXZQPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_SRTSM_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_SRTSM;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_SRTSM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_SRTSM) >> GMAC_NCR_SRTSM_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_SRTSM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_SRTSM;
	tmp |= value << GMAC_NCR_SRTSM_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_SRTSM_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_SRTSM;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_SRTSM_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_SRTSM;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_ENPBPR_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_ENPBPR;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_ENPBPR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_ENPBPR) >> GMAC_NCR_ENPBPR_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_ENPBPR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_ENPBPR;
	tmp |= value << GMAC_NCR_ENPBPR_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_ENPBPR_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_ENPBPR;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_ENPBPR_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_ENPBPR;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_TXPBPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_TXPBPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_TXPBPF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_TXPBPF) >> GMAC_NCR_TXPBPF_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_TXPBPF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_TXPBPF;
	tmp |= value << GMAC_NCR_TXPBPF_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_TXPBPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_TXPBPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_TXPBPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_TXPBPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_FNP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_FNP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_FNP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_FNP) >> GMAC_NCR_FNP_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_FNP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_FNP;
	tmp |= value << GMAC_NCR_FNP_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_FNP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_FNP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_FNP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_FNP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_TXLPIEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= GMAC_NCR_TXLPIEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCR_TXLPIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp = (tmp & GMAC_NCR_TXLPIEN) >> GMAC_NCR_TXLPIEN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCR_TXLPIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= ~GMAC_NCR_TXLPIEN;
	tmp |= value << GMAC_NCR_TXLPIEN_Pos;
	((Gmac *)hw)->GMAC_NCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_TXLPIEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~GMAC_NCR_TXLPIEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_TXLPIEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= GMAC_NCR_TXLPIEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncr_reg_t hri_gmac_get_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCR_reg(const void *const hw, hri_gmac_ncr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCR ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncr_reg_t hri_gmac_read_NCR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_NCR;
}

static inline void hri_gmac_set_NCFGR_SPD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_SPD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_SPD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_SPD) >> GMAC_NCFGR_SPD_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_SPD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_SPD;
	tmp |= value << GMAC_NCFGR_SPD_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_SPD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_SPD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_SPD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_SPD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_FD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_FD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_FD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_FD) >> GMAC_NCFGR_FD_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_FD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_FD;
	tmp |= value << GMAC_NCFGR_FD_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_FD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_FD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_FD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_FD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_DNVLAN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_DNVLAN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_DNVLAN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_DNVLAN) >> GMAC_NCFGR_DNVLAN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_DNVLAN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_DNVLAN;
	tmp |= value << GMAC_NCFGR_DNVLAN_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_DNVLAN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_DNVLAN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_DNVLAN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_DNVLAN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_JFRAME_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_JFRAME;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_JFRAME_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_JFRAME) >> GMAC_NCFGR_JFRAME_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_JFRAME_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_JFRAME;
	tmp |= value << GMAC_NCFGR_JFRAME_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_JFRAME_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_JFRAME;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_JFRAME_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_JFRAME;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_CAF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_CAF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_CAF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_CAF) >> GMAC_NCFGR_CAF_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_CAF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_CAF;
	tmp |= value << GMAC_NCFGR_CAF_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_CAF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_CAF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_CAF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_CAF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_NBC_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_NBC;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_NBC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_NBC) >> GMAC_NCFGR_NBC_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_NBC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_NBC;
	tmp |= value << GMAC_NCFGR_NBC_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_NBC_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_NBC;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_NBC_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_NBC;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_MTIHEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_MTIHEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_MTIHEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_MTIHEN) >> GMAC_NCFGR_MTIHEN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_MTIHEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_MTIHEN;
	tmp |= value << GMAC_NCFGR_MTIHEN_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_MTIHEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_MTIHEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_MTIHEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_MTIHEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_UNIHEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_UNIHEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_UNIHEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_UNIHEN) >> GMAC_NCFGR_UNIHEN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_UNIHEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_UNIHEN;
	tmp |= value << GMAC_NCFGR_UNIHEN_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_UNIHEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_UNIHEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_UNIHEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_UNIHEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_MAXFS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_MAXFS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_MAXFS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_MAXFS) >> GMAC_NCFGR_MAXFS_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_MAXFS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_MAXFS;
	tmp |= value << GMAC_NCFGR_MAXFS_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_MAXFS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_MAXFS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_MAXFS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_MAXFS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_RTY_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_RTY;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_RTY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_RTY) >> GMAC_NCFGR_RTY_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_RTY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_RTY;
	tmp |= value << GMAC_NCFGR_RTY_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_RTY_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_RTY;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_RTY_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_RTY;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_PEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_PEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_PEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_PEN) >> GMAC_NCFGR_PEN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_PEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_PEN;
	tmp |= value << GMAC_NCFGR_PEN_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_PEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_PEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_PEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_PEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_LFERD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_LFERD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_LFERD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_LFERD) >> GMAC_NCFGR_LFERD_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_LFERD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_LFERD;
	tmp |= value << GMAC_NCFGR_LFERD_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_LFERD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_LFERD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_LFERD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_LFERD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_RFCS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_RFCS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_RFCS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_RFCS) >> GMAC_NCFGR_RFCS_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_RFCS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_RFCS;
	tmp |= value << GMAC_NCFGR_RFCS_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_RFCS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_RFCS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_RFCS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_RFCS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_DCPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_DCPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_DCPF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_DCPF) >> GMAC_NCFGR_DCPF_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_DCPF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_DCPF;
	tmp |= value << GMAC_NCFGR_DCPF_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_DCPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_DCPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_DCPF_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_DCPF;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_RXCOEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_RXCOEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_RXCOEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_RXCOEN) >> GMAC_NCFGR_RXCOEN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_RXCOEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_RXCOEN;
	tmp |= value << GMAC_NCFGR_RXCOEN_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_RXCOEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_RXCOEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_RXCOEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_RXCOEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_EFRHD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_EFRHD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_EFRHD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_EFRHD) >> GMAC_NCFGR_EFRHD_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_EFRHD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_EFRHD;
	tmp |= value << GMAC_NCFGR_EFRHD_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_EFRHD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_EFRHD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_EFRHD_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_EFRHD;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_IRXFCS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_IRXFCS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_IRXFCS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_IRXFCS) >> GMAC_NCFGR_IRXFCS_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_IRXFCS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_IRXFCS;
	tmp |= value << GMAC_NCFGR_IRXFCS_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_IRXFCS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_IRXFCS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_IRXFCS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_IRXFCS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_IPGSEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_IPGSEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_IPGSEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_IPGSEN) >> GMAC_NCFGR_IPGSEN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_IPGSEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_IPGSEN;
	tmp |= value << GMAC_NCFGR_IPGSEN_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_IPGSEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_IPGSEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_IPGSEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_IPGSEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_RXBP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_RXBP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_RXBP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_RXBP) >> GMAC_NCFGR_RXBP_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_RXBP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_RXBP;
	tmp |= value << GMAC_NCFGR_RXBP_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_RXBP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_RXBP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_RXBP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_RXBP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_IRXER_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_IRXER;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_NCFGR_IRXER_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_IRXER) >> GMAC_NCFGR_IRXER_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_NCFGR_IRXER_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_IRXER;
	tmp |= value << GMAC_NCFGR_IRXER_Pos;
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_IRXER_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_IRXER;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_IRXER_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_IRXER;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_NCFGR_RXBUFO_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_RXBUFO(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_get_NCFGR_RXBUFO_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_RXBUFO(mask)) >> GMAC_NCFGR_RXBUFO_Pos;
	return tmp;
}

static inline void hri_gmac_write_NCFGR_RXBUFO_bf(const void *const hw, hri_gmac_ncfgr_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_RXBUFO_Msk;
	tmp |= GMAC_NCFGR_RXBUFO(data);
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_RXBUFO_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_RXBUFO(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_RXBUFO_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_RXBUFO(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_read_NCFGR_RXBUFO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_RXBUFO_Msk) >> GMAC_NCFGR_RXBUFO_Pos;
	return tmp;
}

static inline void hri_gmac_set_NCFGR_CLK_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_CLK(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_get_NCFGR_CLK_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_CLK(mask)) >> GMAC_NCFGR_CLK_Pos;
	return tmp;
}

static inline void hri_gmac_write_NCFGR_CLK_bf(const void *const hw, hri_gmac_ncfgr_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_CLK_Msk;
	tmp |= GMAC_NCFGR_CLK(data);
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_CLK_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_CLK(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_CLK_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_CLK(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_read_NCFGR_CLK_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_CLK_Msk) >> GMAC_NCFGR_CLK_Pos;
	return tmp;
}

static inline void hri_gmac_set_NCFGR_DBW_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= GMAC_NCFGR_DBW(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_get_NCFGR_DBW_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_DBW(mask)) >> GMAC_NCFGR_DBW_Pos;
	return tmp;
}

static inline void hri_gmac_write_NCFGR_DBW_bf(const void *const hw, hri_gmac_ncfgr_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= ~GMAC_NCFGR_DBW_Msk;
	tmp |= GMAC_NCFGR_DBW(data);
	((Gmac *)hw)->GMAC_NCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_DBW_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~GMAC_NCFGR_DBW(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_DBW_bf(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= GMAC_NCFGR_DBW(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_read_NCFGR_DBW_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp = (tmp & GMAC_NCFGR_DBW_Msk) >> GMAC_NCFGR_DBW_Pos;
	return tmp;
}

static inline void hri_gmac_set_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_get_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NCFGR;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NCFGR_reg(const void *const hw, hri_gmac_ncfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NCFGR ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ncfgr_reg_t hri_gmac_read_NCFGR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_NCFGR;
}

static inline void hri_gmac_set_UR_RMII_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_UR |= GMAC_UR_RMII;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_UR_RMII_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_UR;
	tmp = (tmp & GMAC_UR_RMII) >> GMAC_UR_RMII_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_UR_RMII_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_UR;
	tmp &= ~GMAC_UR_RMII;
	tmp |= value << GMAC_UR_RMII_Pos;
	((Gmac *)hw)->GMAC_UR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_UR_RMII_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_UR &= ~GMAC_UR_RMII;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_UR_RMII_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_UR ^= GMAC_UR_RMII;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_UR_reg(const void *const hw, hri_gmac_ur_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_UR |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ur_reg_t hri_gmac_get_UR_reg(const void *const hw, hri_gmac_ur_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_UR;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_UR_reg(const void *const hw, hri_gmac_ur_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_UR = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_UR_reg(const void *const hw, hri_gmac_ur_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_UR &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_UR_reg(const void *const hw, hri_gmac_ur_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_UR ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ur_reg_t hri_gmac_read_UR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_UR;
}

static inline void hri_gmac_set_DCFGR_ESMA_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR |= GMAC_DCFGR_ESMA;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_DCFGR_ESMA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_ESMA) >> GMAC_DCFGR_ESMA_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_DCFGR_ESMA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp &= ~GMAC_DCFGR_ESMA;
	tmp |= value << GMAC_DCFGR_ESMA_Pos;
	((Gmac *)hw)->GMAC_DCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_ESMA_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR &= ~GMAC_DCFGR_ESMA;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_ESMA_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR ^= GMAC_DCFGR_ESMA;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_DCFGR_ESPA_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR |= GMAC_DCFGR_ESPA;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_DCFGR_ESPA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_ESPA) >> GMAC_DCFGR_ESPA_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_DCFGR_ESPA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp &= ~GMAC_DCFGR_ESPA;
	tmp |= value << GMAC_DCFGR_ESPA_Pos;
	((Gmac *)hw)->GMAC_DCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_ESPA_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR &= ~GMAC_DCFGR_ESPA;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_ESPA_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR ^= GMAC_DCFGR_ESPA;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_DCFGR_TXPBMS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR |= GMAC_DCFGR_TXPBMS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_DCFGR_TXPBMS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_TXPBMS) >> GMAC_DCFGR_TXPBMS_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_DCFGR_TXPBMS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp &= ~GMAC_DCFGR_TXPBMS;
	tmp |= value << GMAC_DCFGR_TXPBMS_Pos;
	((Gmac *)hw)->GMAC_DCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_TXPBMS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR &= ~GMAC_DCFGR_TXPBMS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_TXPBMS_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR ^= GMAC_DCFGR_TXPBMS;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_DCFGR_TXCOEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR |= GMAC_DCFGR_TXCOEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_DCFGR_TXCOEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_TXCOEN) >> GMAC_DCFGR_TXCOEN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_DCFGR_TXCOEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp &= ~GMAC_DCFGR_TXCOEN;
	tmp |= value << GMAC_DCFGR_TXCOEN_Pos;
	((Gmac *)hw)->GMAC_DCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_TXCOEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR &= ~GMAC_DCFGR_TXCOEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_TXCOEN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR ^= GMAC_DCFGR_TXCOEN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_DCFGR_DDRP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR |= GMAC_DCFGR_DDRP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_DCFGR_DDRP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_DDRP) >> GMAC_DCFGR_DDRP_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_DCFGR_DDRP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp &= ~GMAC_DCFGR_DDRP;
	tmp |= value << GMAC_DCFGR_DDRP_Pos;
	((Gmac *)hw)->GMAC_DCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_DDRP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR &= ~GMAC_DCFGR_DDRP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_DDRP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR ^= GMAC_DCFGR_DDRP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_DCFGR_FBLDO_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR |= GMAC_DCFGR_FBLDO(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_get_DCFGR_FBLDO_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_FBLDO(mask)) >> GMAC_DCFGR_FBLDO_Pos;
	return tmp;
}

static inline void hri_gmac_write_DCFGR_FBLDO_bf(const void *const hw, hri_gmac_dcfgr_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp &= ~GMAC_DCFGR_FBLDO_Msk;
	tmp |= GMAC_DCFGR_FBLDO(data);
	((Gmac *)hw)->GMAC_DCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_FBLDO_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR &= ~GMAC_DCFGR_FBLDO(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_FBLDO_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR ^= GMAC_DCFGR_FBLDO(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_read_DCFGR_FBLDO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_FBLDO_Msk) >> GMAC_DCFGR_FBLDO_Pos;
	return tmp;
}

static inline void hri_gmac_set_DCFGR_RXBMS_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR |= GMAC_DCFGR_RXBMS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_get_DCFGR_RXBMS_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_RXBMS(mask)) >> GMAC_DCFGR_RXBMS_Pos;
	return tmp;
}

static inline void hri_gmac_write_DCFGR_RXBMS_bf(const void *const hw, hri_gmac_dcfgr_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp &= ~GMAC_DCFGR_RXBMS_Msk;
	tmp |= GMAC_DCFGR_RXBMS(data);
	((Gmac *)hw)->GMAC_DCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_RXBMS_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR &= ~GMAC_DCFGR_RXBMS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_RXBMS_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR ^= GMAC_DCFGR_RXBMS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_read_DCFGR_RXBMS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_RXBMS_Msk) >> GMAC_DCFGR_RXBMS_Pos;
	return tmp;
}

static inline void hri_gmac_set_DCFGR_DRBS_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR |= GMAC_DCFGR_DRBS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_get_DCFGR_DRBS_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_DRBS(mask)) >> GMAC_DCFGR_DRBS_Pos;
	return tmp;
}

static inline void hri_gmac_write_DCFGR_DRBS_bf(const void *const hw, hri_gmac_dcfgr_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp &= ~GMAC_DCFGR_DRBS_Msk;
	tmp |= GMAC_DCFGR_DRBS(data);
	((Gmac *)hw)->GMAC_DCFGR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_DRBS_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR &= ~GMAC_DCFGR_DRBS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_DRBS_bf(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR ^= GMAC_DCFGR_DRBS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_read_DCFGR_DRBS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp = (tmp & GMAC_DCFGR_DRBS_Msk) >> GMAC_DCFGR_DRBS_Pos;
	return tmp;
}

static inline void hri_gmac_set_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_get_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_DCFGR;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_DCFGR_reg(const void *const hw, hri_gmac_dcfgr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_DCFGR ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_dcfgr_reg_t hri_gmac_read_DCFGR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_DCFGR;
}

static inline void hri_gmac_set_TSR_UBR_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR |= GMAC_TSR_UBR;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TSR_UBR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp = (tmp & GMAC_TSR_UBR) >> GMAC_TSR_UBR_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TSR_UBR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp &= ~GMAC_TSR_UBR;
	tmp |= value << GMAC_TSR_UBR_Pos;
	((Gmac *)hw)->GMAC_TSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSR_UBR_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR &= ~GMAC_TSR_UBR;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSR_UBR_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR ^= GMAC_TSR_UBR;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TSR_COL_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR |= GMAC_TSR_COL;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TSR_COL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp = (tmp & GMAC_TSR_COL) >> GMAC_TSR_COL_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TSR_COL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp &= ~GMAC_TSR_COL;
	tmp |= value << GMAC_TSR_COL_Pos;
	((Gmac *)hw)->GMAC_TSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSR_COL_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR &= ~GMAC_TSR_COL;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSR_COL_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR ^= GMAC_TSR_COL;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TSR_RLE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR |= GMAC_TSR_RLE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TSR_RLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp = (tmp & GMAC_TSR_RLE) >> GMAC_TSR_RLE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TSR_RLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp &= ~GMAC_TSR_RLE;
	tmp |= value << GMAC_TSR_RLE_Pos;
	((Gmac *)hw)->GMAC_TSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSR_RLE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR &= ~GMAC_TSR_RLE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSR_RLE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR ^= GMAC_TSR_RLE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TSR_TXGO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR |= GMAC_TSR_TXGO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TSR_TXGO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp = (tmp & GMAC_TSR_TXGO) >> GMAC_TSR_TXGO_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TSR_TXGO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp &= ~GMAC_TSR_TXGO;
	tmp |= value << GMAC_TSR_TXGO_Pos;
	((Gmac *)hw)->GMAC_TSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSR_TXGO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR &= ~GMAC_TSR_TXGO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSR_TXGO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR ^= GMAC_TSR_TXGO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TSR_TFC_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR |= GMAC_TSR_TFC;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TSR_TFC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp = (tmp & GMAC_TSR_TFC) >> GMAC_TSR_TFC_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TSR_TFC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp &= ~GMAC_TSR_TFC;
	tmp |= value << GMAC_TSR_TFC_Pos;
	((Gmac *)hw)->GMAC_TSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSR_TFC_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR &= ~GMAC_TSR_TFC;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSR_TFC_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR ^= GMAC_TSR_TFC;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TSR_TXCOMP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR |= GMAC_TSR_TXCOMP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TSR_TXCOMP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp = (tmp & GMAC_TSR_TXCOMP) >> GMAC_TSR_TXCOMP_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TSR_TXCOMP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp &= ~GMAC_TSR_TXCOMP;
	tmp |= value << GMAC_TSR_TXCOMP_Pos;
	((Gmac *)hw)->GMAC_TSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSR_TXCOMP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR &= ~GMAC_TSR_TXCOMP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSR_TXCOMP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR ^= GMAC_TSR_TXCOMP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TSR_HRESP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR |= GMAC_TSR_HRESP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TSR_HRESP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp = (tmp & GMAC_TSR_HRESP) >> GMAC_TSR_HRESP_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TSR_HRESP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp &= ~GMAC_TSR_HRESP;
	tmp |= value << GMAC_TSR_HRESP_Pos;
	((Gmac *)hw)->GMAC_TSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSR_HRESP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR &= ~GMAC_TSR_HRESP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSR_HRESP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR ^= GMAC_TSR_HRESP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsr_reg_t hri_gmac_get_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSR;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSR_reg(const void *const hw, hri_gmac_tsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSR ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsr_reg_t hri_gmac_read_TSR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TSR;
}

static inline void hri_gmac_set_RBQB_ADDR_bf(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQB |= GMAC_RBQB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqb_reg_t hri_gmac_get_RBQB_ADDR_bf(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RBQB;
	tmp = (tmp & GMAC_RBQB_ADDR(mask)) >> GMAC_RBQB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_write_RBQB_ADDR_bf(const void *const hw, hri_gmac_rbqb_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RBQB;
	tmp &= ~GMAC_RBQB_ADDR_Msk;
	tmp |= GMAC_RBQB_ADDR(data);
	((Gmac *)hw)->GMAC_RBQB = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RBQB_ADDR_bf(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQB &= ~GMAC_RBQB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RBQB_ADDR_bf(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQB ^= GMAC_RBQB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqb_reg_t hri_gmac_read_RBQB_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RBQB;
	tmp = (tmp & GMAC_RBQB_ADDR_Msk) >> GMAC_RBQB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_set_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQB |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqb_reg_t hri_gmac_get_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RBQB;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQB = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQB &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RBQB_reg(const void *const hw, hri_gmac_rbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQB ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqb_reg_t hri_gmac_read_RBQB_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_RBQB;
}

static inline void hri_gmac_set_TBQB_ADDR_bf(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQB |= GMAC_TBQB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqb_reg_t hri_gmac_get_TBQB_ADDR_bf(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBQB;
	tmp = (tmp & GMAC_TBQB_ADDR(mask)) >> GMAC_TBQB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_write_TBQB_ADDR_bf(const void *const hw, hri_gmac_tbqb_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TBQB;
	tmp &= ~GMAC_TBQB_ADDR_Msk;
	tmp |= GMAC_TBQB_ADDR(data);
	((Gmac *)hw)->GMAC_TBQB = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TBQB_ADDR_bf(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQB &= ~GMAC_TBQB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TBQB_ADDR_bf(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQB ^= GMAC_TBQB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqb_reg_t hri_gmac_read_TBQB_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBQB;
	tmp = (tmp & GMAC_TBQB_ADDR_Msk) >> GMAC_TBQB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_set_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQB |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqb_reg_t hri_gmac_get_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBQB;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQB = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQB &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TBQB_reg(const void *const hw, hri_gmac_tbqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQB ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqb_reg_t hri_gmac_read_TBQB_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TBQB;
}

static inline void hri_gmac_set_RSR_BNA_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR |= GMAC_RSR_BNA;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_RSR_BNA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RSR;
	tmp = (tmp & GMAC_RSR_BNA) >> GMAC_RSR_BNA_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_RSR_BNA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RSR;
	tmp &= ~GMAC_RSR_BNA;
	tmp |= value << GMAC_RSR_BNA_Pos;
	((Gmac *)hw)->GMAC_RSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RSR_BNA_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR &= ~GMAC_RSR_BNA;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RSR_BNA_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR ^= GMAC_RSR_BNA;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_RSR_REC_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR |= GMAC_RSR_REC;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_RSR_REC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RSR;
	tmp = (tmp & GMAC_RSR_REC) >> GMAC_RSR_REC_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_RSR_REC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RSR;
	tmp &= ~GMAC_RSR_REC;
	tmp |= value << GMAC_RSR_REC_Pos;
	((Gmac *)hw)->GMAC_RSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RSR_REC_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR &= ~GMAC_RSR_REC;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RSR_REC_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR ^= GMAC_RSR_REC;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_RSR_RXOVR_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR |= GMAC_RSR_RXOVR;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_RSR_RXOVR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RSR;
	tmp = (tmp & GMAC_RSR_RXOVR) >> GMAC_RSR_RXOVR_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_RSR_RXOVR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RSR;
	tmp &= ~GMAC_RSR_RXOVR;
	tmp |= value << GMAC_RSR_RXOVR_Pos;
	((Gmac *)hw)->GMAC_RSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RSR_RXOVR_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR &= ~GMAC_RSR_RXOVR;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RSR_RXOVR_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR ^= GMAC_RSR_RXOVR;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_RSR_HNO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR |= GMAC_RSR_HNO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_RSR_HNO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RSR;
	tmp = (tmp & GMAC_RSR_HNO) >> GMAC_RSR_HNO_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_RSR_HNO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RSR;
	tmp &= ~GMAC_RSR_HNO;
	tmp |= value << GMAC_RSR_HNO_Pos;
	((Gmac *)hw)->GMAC_RSR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RSR_HNO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR &= ~GMAC_RSR_HNO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RSR_HNO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR ^= GMAC_RSR_HNO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rsr_reg_t hri_gmac_get_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RSR;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RSR_reg(const void *const hw, hri_gmac_rsr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RSR ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rsr_reg_t hri_gmac_read_RSR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_RSR;
}

static inline void hri_gmac_set_MAN_CLTTO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN |= GMAC_MAN_CLTTO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_MAN_CLTTO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_CLTTO) >> GMAC_MAN_CLTTO_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_MAN_CLTTO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp &= ~GMAC_MAN_CLTTO;
	tmp |= value << GMAC_MAN_CLTTO_Pos;
	((Gmac *)hw)->GMAC_MAN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_MAN_CLTTO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN &= ~GMAC_MAN_CLTTO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_MAN_CLTTO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN ^= GMAC_MAN_CLTTO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_MAN_WZO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN |= GMAC_MAN_WZO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_MAN_WZO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_WZO) >> GMAC_MAN_WZO_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_MAN_WZO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp &= ~GMAC_MAN_WZO;
	tmp |= value << GMAC_MAN_WZO_Pos;
	((Gmac *)hw)->GMAC_MAN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_MAN_WZO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN &= ~GMAC_MAN_WZO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_MAN_WZO_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN ^= GMAC_MAN_WZO;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_MAN_DATA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN |= GMAC_MAN_DATA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_get_MAN_DATA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_DATA(mask)) >> GMAC_MAN_DATA_Pos;
	return tmp;
}

static inline void hri_gmac_write_MAN_DATA_bf(const void *const hw, hri_gmac_man_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp &= ~GMAC_MAN_DATA_Msk;
	tmp |= GMAC_MAN_DATA(data);
	((Gmac *)hw)->GMAC_MAN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_MAN_DATA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN &= ~GMAC_MAN_DATA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_MAN_DATA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN ^= GMAC_MAN_DATA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_read_MAN_DATA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_DATA_Msk) >> GMAC_MAN_DATA_Pos;
	return tmp;
}

static inline void hri_gmac_set_MAN_WTN_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN |= GMAC_MAN_WTN(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_get_MAN_WTN_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_WTN(mask)) >> GMAC_MAN_WTN_Pos;
	return tmp;
}

static inline void hri_gmac_write_MAN_WTN_bf(const void *const hw, hri_gmac_man_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp &= ~GMAC_MAN_WTN_Msk;
	tmp |= GMAC_MAN_WTN(data);
	((Gmac *)hw)->GMAC_MAN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_MAN_WTN_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN &= ~GMAC_MAN_WTN(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_MAN_WTN_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN ^= GMAC_MAN_WTN(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_read_MAN_WTN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_WTN_Msk) >> GMAC_MAN_WTN_Pos;
	return tmp;
}

static inline void hri_gmac_set_MAN_REGA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN |= GMAC_MAN_REGA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_get_MAN_REGA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_REGA(mask)) >> GMAC_MAN_REGA_Pos;
	return tmp;
}

static inline void hri_gmac_write_MAN_REGA_bf(const void *const hw, hri_gmac_man_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp &= ~GMAC_MAN_REGA_Msk;
	tmp |= GMAC_MAN_REGA(data);
	((Gmac *)hw)->GMAC_MAN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_MAN_REGA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN &= ~GMAC_MAN_REGA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_MAN_REGA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN ^= GMAC_MAN_REGA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_read_MAN_REGA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_REGA_Msk) >> GMAC_MAN_REGA_Pos;
	return tmp;
}

static inline void hri_gmac_set_MAN_PHYA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN |= GMAC_MAN_PHYA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_get_MAN_PHYA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_PHYA(mask)) >> GMAC_MAN_PHYA_Pos;
	return tmp;
}

static inline void hri_gmac_write_MAN_PHYA_bf(const void *const hw, hri_gmac_man_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp &= ~GMAC_MAN_PHYA_Msk;
	tmp |= GMAC_MAN_PHYA(data);
	((Gmac *)hw)->GMAC_MAN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_MAN_PHYA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN &= ~GMAC_MAN_PHYA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_MAN_PHYA_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN ^= GMAC_MAN_PHYA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_read_MAN_PHYA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_PHYA_Msk) >> GMAC_MAN_PHYA_Pos;
	return tmp;
}

static inline void hri_gmac_set_MAN_OP_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN |= GMAC_MAN_OP(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_get_MAN_OP_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_OP(mask)) >> GMAC_MAN_OP_Pos;
	return tmp;
}

static inline void hri_gmac_write_MAN_OP_bf(const void *const hw, hri_gmac_man_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp &= ~GMAC_MAN_OP_Msk;
	tmp |= GMAC_MAN_OP(data);
	((Gmac *)hw)->GMAC_MAN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_MAN_OP_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN &= ~GMAC_MAN_OP(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_MAN_OP_bf(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN ^= GMAC_MAN_OP(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_read_MAN_OP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp = (tmp & GMAC_MAN_OP_Msk) >> GMAC_MAN_OP_Pos;
	return tmp;
}

static inline void hri_gmac_set_MAN_reg(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_get_MAN_reg(const void *const hw, hri_gmac_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_MAN;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_MAN_reg(const void *const hw, hri_gmac_man_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_MAN_reg(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_MAN_reg(const void *const hw, hri_gmac_man_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_MAN ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_man_reg_t hri_gmac_read_MAN_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_MAN;
}

static inline void hri_gmac_set_TPQ_TPQ_bf(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPQ |= GMAC_TPQ_TPQ(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpq_reg_t hri_gmac_get_TPQ_TPQ_bf(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPQ;
	tmp = (tmp & GMAC_TPQ_TPQ(mask)) >> GMAC_TPQ_TPQ_Pos;
	return tmp;
}

static inline void hri_gmac_write_TPQ_TPQ_bf(const void *const hw, hri_gmac_tpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TPQ;
	tmp &= ~GMAC_TPQ_TPQ_Msk;
	tmp |= GMAC_TPQ_TPQ(data);
	((Gmac *)hw)->GMAC_TPQ = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPQ_TPQ_bf(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPQ &= ~GMAC_TPQ_TPQ(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPQ_TPQ_bf(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPQ ^= GMAC_TPQ_TPQ(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpq_reg_t hri_gmac_read_TPQ_TPQ_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPQ;
	tmp = (tmp & GMAC_TPQ_TPQ_Msk) >> GMAC_TPQ_TPQ_Pos;
	return tmp;
}

static inline void hri_gmac_set_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPQ |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpq_reg_t hri_gmac_get_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPQ;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPQ = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPQ &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPQ_reg(const void *const hw, hri_gmac_tpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPQ ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpq_reg_t hri_gmac_read_TPQ_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TPQ;
}

static inline void hri_gmac_set_TPSF_ENTXP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF |= GMAC_TPSF_ENTXP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TPSF_ENTXP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPSF;
	tmp = (tmp & GMAC_TPSF_ENTXP) >> GMAC_TPSF_ENTXP_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TPSF_ENTXP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TPSF;
	tmp &= ~GMAC_TPSF_ENTXP;
	tmp |= value << GMAC_TPSF_ENTXP_Pos;
	((Gmac *)hw)->GMAC_TPSF = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPSF_ENTXP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF &= ~GMAC_TPSF_ENTXP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPSF_ENTXP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF ^= GMAC_TPSF_ENTXP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TPSF_TPB1ADR_bf(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF |= GMAC_TPSF_TPB1ADR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpsf_reg_t hri_gmac_get_TPSF_TPB1ADR_bf(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPSF;
	tmp = (tmp & GMAC_TPSF_TPB1ADR(mask)) >> GMAC_TPSF_TPB1ADR_Pos;
	return tmp;
}

static inline void hri_gmac_write_TPSF_TPB1ADR_bf(const void *const hw, hri_gmac_tpsf_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TPSF;
	tmp &= ~GMAC_TPSF_TPB1ADR_Msk;
	tmp |= GMAC_TPSF_TPB1ADR(data);
	((Gmac *)hw)->GMAC_TPSF = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPSF_TPB1ADR_bf(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF &= ~GMAC_TPSF_TPB1ADR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPSF_TPB1ADR_bf(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF ^= GMAC_TPSF_TPB1ADR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpsf_reg_t hri_gmac_read_TPSF_TPB1ADR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPSF;
	tmp = (tmp & GMAC_TPSF_TPB1ADR_Msk) >> GMAC_TPSF_TPB1ADR_Pos;
	return tmp;
}

static inline void hri_gmac_set_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpsf_reg_t hri_gmac_get_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPSF;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPSF_reg(const void *const hw, hri_gmac_tpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPSF ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpsf_reg_t hri_gmac_read_TPSF_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TPSF;
}

static inline void hri_gmac_set_RPSF_ENRXP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF |= GMAC_RPSF_ENRXP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_RPSF_ENRXP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RPSF;
	tmp = (tmp & GMAC_RPSF_ENRXP) >> GMAC_RPSF_ENRXP_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_RPSF_ENRXP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RPSF;
	tmp &= ~GMAC_RPSF_ENRXP;
	tmp |= value << GMAC_RPSF_ENRXP_Pos;
	((Gmac *)hw)->GMAC_RPSF = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RPSF_ENRXP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF &= ~GMAC_RPSF_ENRXP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RPSF_ENRXP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF ^= GMAC_RPSF_ENRXP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_RPSF_RPB1ADR_bf(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF |= GMAC_RPSF_RPB1ADR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rpsf_reg_t hri_gmac_get_RPSF_RPB1ADR_bf(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RPSF;
	tmp = (tmp & GMAC_RPSF_RPB1ADR(mask)) >> GMAC_RPSF_RPB1ADR_Pos;
	return tmp;
}

static inline void hri_gmac_write_RPSF_RPB1ADR_bf(const void *const hw, hri_gmac_rpsf_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RPSF;
	tmp &= ~GMAC_RPSF_RPB1ADR_Msk;
	tmp |= GMAC_RPSF_RPB1ADR(data);
	((Gmac *)hw)->GMAC_RPSF = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RPSF_RPB1ADR_bf(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF &= ~GMAC_RPSF_RPB1ADR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RPSF_RPB1ADR_bf(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF ^= GMAC_RPSF_RPB1ADR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rpsf_reg_t hri_gmac_read_RPSF_RPB1ADR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RPSF;
	tmp = (tmp & GMAC_RPSF_RPB1ADR_Msk) >> GMAC_RPSF_RPB1ADR_Pos;
	return tmp;
}

static inline void hri_gmac_set_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rpsf_reg_t hri_gmac_get_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RPSF;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RPSF_reg(const void *const hw, hri_gmac_rpsf_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RPSF ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rpsf_reg_t hri_gmac_read_RPSF_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_RPSF;
}

static inline void hri_gmac_set_RJFML_FML_bf(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RJFML |= GMAC_RJFML_FML(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rjfml_reg_t hri_gmac_get_RJFML_FML_bf(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RJFML;
	tmp = (tmp & GMAC_RJFML_FML(mask)) >> GMAC_RJFML_FML_Pos;
	return tmp;
}

static inline void hri_gmac_write_RJFML_FML_bf(const void *const hw, hri_gmac_rjfml_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RJFML;
	tmp &= ~GMAC_RJFML_FML_Msk;
	tmp |= GMAC_RJFML_FML(data);
	((Gmac *)hw)->GMAC_RJFML = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RJFML_FML_bf(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RJFML &= ~GMAC_RJFML_FML(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RJFML_FML_bf(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RJFML ^= GMAC_RJFML_FML(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rjfml_reg_t hri_gmac_read_RJFML_FML_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RJFML;
	tmp = (tmp & GMAC_RJFML_FML_Msk) >> GMAC_RJFML_FML_Pos;
	return tmp;
}

static inline void hri_gmac_set_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RJFML |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rjfml_reg_t hri_gmac_get_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RJFML;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RJFML = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RJFML &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RJFML_reg(const void *const hw, hri_gmac_rjfml_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RJFML ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rjfml_reg_t hri_gmac_read_RJFML_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_RJFML;
}

static inline void hri_gmac_set_HRB_ADDR_bf(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRB |= GMAC_HRB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrb_reg_t hri_gmac_get_HRB_ADDR_bf(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_HRB;
	tmp = (tmp & GMAC_HRB_ADDR(mask)) >> GMAC_HRB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_write_HRB_ADDR_bf(const void *const hw, hri_gmac_hrb_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_HRB;
	tmp &= ~GMAC_HRB_ADDR_Msk;
	tmp |= GMAC_HRB_ADDR(data);
	((Gmac *)hw)->GMAC_HRB = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_HRB_ADDR_bf(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRB &= ~GMAC_HRB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_HRB_ADDR_bf(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRB ^= GMAC_HRB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrb_reg_t hri_gmac_read_HRB_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_HRB;
	tmp = (tmp & GMAC_HRB_ADDR_Msk) >> GMAC_HRB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_set_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRB |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrb_reg_t hri_gmac_get_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_HRB;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRB = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRB &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_HRB_reg(const void *const hw, hri_gmac_hrb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRB ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrb_reg_t hri_gmac_read_HRB_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_HRB;
}

static inline void hri_gmac_set_HRT_ADDR_bf(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRT |= GMAC_HRT_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrt_reg_t hri_gmac_get_HRT_ADDR_bf(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_HRT;
	tmp = (tmp & GMAC_HRT_ADDR(mask)) >> GMAC_HRT_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_write_HRT_ADDR_bf(const void *const hw, hri_gmac_hrt_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_HRT;
	tmp &= ~GMAC_HRT_ADDR_Msk;
	tmp |= GMAC_HRT_ADDR(data);
	((Gmac *)hw)->GMAC_HRT = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_HRT_ADDR_bf(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRT &= ~GMAC_HRT_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_HRT_ADDR_bf(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRT ^= GMAC_HRT_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrt_reg_t hri_gmac_read_HRT_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_HRT;
	tmp = (tmp & GMAC_HRT_ADDR_Msk) >> GMAC_HRT_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_set_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRT |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrt_reg_t hri_gmac_get_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_HRT;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRT = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRT &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_HRT_reg(const void *const hw, hri_gmac_hrt_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_HRT ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_hrt_reg_t hri_gmac_read_HRT_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_HRT;
}

static inline void hri_gmac_set_TIDM1_ENID1_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 |= GMAC_TIDM1_ENID1;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TIDM1_ENID1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM1;
	tmp = (tmp & GMAC_TIDM1_ENID1) >> GMAC_TIDM1_ENID1_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TIDM1_ENID1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TIDM1;
	tmp &= ~GMAC_TIDM1_ENID1;
	tmp |= value << GMAC_TIDM1_ENID1_Pos;
	((Gmac *)hw)->GMAC_TIDM1 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM1_ENID1_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 &= ~GMAC_TIDM1_ENID1;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM1_ENID1_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 ^= GMAC_TIDM1_ENID1;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TIDM1_TID_bf(const void *const hw, hri_gmac_tidm1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 |= GMAC_TIDM1_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm1_reg_t hri_gmac_get_TIDM1_TID_bf(const void *const hw, hri_gmac_tidm1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM1;
	tmp = (tmp & GMAC_TIDM1_TID(mask)) >> GMAC_TIDM1_TID_Pos;
	return tmp;
}

static inline void hri_gmac_write_TIDM1_TID_bf(const void *const hw, hri_gmac_tidm1_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TIDM1;
	tmp &= ~GMAC_TIDM1_TID_Msk;
	tmp |= GMAC_TIDM1_TID(data);
	((Gmac *)hw)->GMAC_TIDM1 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM1_TID_bf(const void *const hw, hri_gmac_tidm1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 &= ~GMAC_TIDM1_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM1_TID_bf(const void *const hw, hri_gmac_tidm1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 ^= GMAC_TIDM1_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm1_reg_t hri_gmac_read_TIDM1_TID_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM1;
	tmp = (tmp & GMAC_TIDM1_TID_Msk) >> GMAC_TIDM1_TID_Pos;
	return tmp;
}

static inline void hri_gmac_set_TIDM1_reg(const void *const hw, hri_gmac_tidm1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm1_reg_t hri_gmac_get_TIDM1_reg(const void *const hw, hri_gmac_tidm1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM1;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TIDM1_reg(const void *const hw, hri_gmac_tidm1_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM1_reg(const void *const hw, hri_gmac_tidm1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM1_reg(const void *const hw, hri_gmac_tidm1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM1 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm1_reg_t hri_gmac_read_TIDM1_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TIDM1;
}

static inline void hri_gmac_set_TIDM2_ENID2_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 |= GMAC_TIDM2_ENID2;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TIDM2_ENID2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM2;
	tmp = (tmp & GMAC_TIDM2_ENID2) >> GMAC_TIDM2_ENID2_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TIDM2_ENID2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TIDM2;
	tmp &= ~GMAC_TIDM2_ENID2;
	tmp |= value << GMAC_TIDM2_ENID2_Pos;
	((Gmac *)hw)->GMAC_TIDM2 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM2_ENID2_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 &= ~GMAC_TIDM2_ENID2;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM2_ENID2_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 ^= GMAC_TIDM2_ENID2;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TIDM2_TID_bf(const void *const hw, hri_gmac_tidm2_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 |= GMAC_TIDM2_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm2_reg_t hri_gmac_get_TIDM2_TID_bf(const void *const hw, hri_gmac_tidm2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM2;
	tmp = (tmp & GMAC_TIDM2_TID(mask)) >> GMAC_TIDM2_TID_Pos;
	return tmp;
}

static inline void hri_gmac_write_TIDM2_TID_bf(const void *const hw, hri_gmac_tidm2_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TIDM2;
	tmp &= ~GMAC_TIDM2_TID_Msk;
	tmp |= GMAC_TIDM2_TID(data);
	((Gmac *)hw)->GMAC_TIDM2 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM2_TID_bf(const void *const hw, hri_gmac_tidm2_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 &= ~GMAC_TIDM2_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM2_TID_bf(const void *const hw, hri_gmac_tidm2_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 ^= GMAC_TIDM2_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm2_reg_t hri_gmac_read_TIDM2_TID_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM2;
	tmp = (tmp & GMAC_TIDM2_TID_Msk) >> GMAC_TIDM2_TID_Pos;
	return tmp;
}

static inline void hri_gmac_set_TIDM2_reg(const void *const hw, hri_gmac_tidm2_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm2_reg_t hri_gmac_get_TIDM2_reg(const void *const hw, hri_gmac_tidm2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM2;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TIDM2_reg(const void *const hw, hri_gmac_tidm2_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM2_reg(const void *const hw, hri_gmac_tidm2_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM2_reg(const void *const hw, hri_gmac_tidm2_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM2 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm2_reg_t hri_gmac_read_TIDM2_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TIDM2;
}

static inline void hri_gmac_set_TIDM3_ENID3_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 |= GMAC_TIDM3_ENID3;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TIDM3_ENID3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM3;
	tmp = (tmp & GMAC_TIDM3_ENID3) >> GMAC_TIDM3_ENID3_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TIDM3_ENID3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TIDM3;
	tmp &= ~GMAC_TIDM3_ENID3;
	tmp |= value << GMAC_TIDM3_ENID3_Pos;
	((Gmac *)hw)->GMAC_TIDM3 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM3_ENID3_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 &= ~GMAC_TIDM3_ENID3;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM3_ENID3_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 ^= GMAC_TIDM3_ENID3;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TIDM3_TID_bf(const void *const hw, hri_gmac_tidm3_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 |= GMAC_TIDM3_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm3_reg_t hri_gmac_get_TIDM3_TID_bf(const void *const hw, hri_gmac_tidm3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM3;
	tmp = (tmp & GMAC_TIDM3_TID(mask)) >> GMAC_TIDM3_TID_Pos;
	return tmp;
}

static inline void hri_gmac_write_TIDM3_TID_bf(const void *const hw, hri_gmac_tidm3_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TIDM3;
	tmp &= ~GMAC_TIDM3_TID_Msk;
	tmp |= GMAC_TIDM3_TID(data);
	((Gmac *)hw)->GMAC_TIDM3 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM3_TID_bf(const void *const hw, hri_gmac_tidm3_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 &= ~GMAC_TIDM3_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM3_TID_bf(const void *const hw, hri_gmac_tidm3_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 ^= GMAC_TIDM3_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm3_reg_t hri_gmac_read_TIDM3_TID_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM3;
	tmp = (tmp & GMAC_TIDM3_TID_Msk) >> GMAC_TIDM3_TID_Pos;
	return tmp;
}

static inline void hri_gmac_set_TIDM3_reg(const void *const hw, hri_gmac_tidm3_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm3_reg_t hri_gmac_get_TIDM3_reg(const void *const hw, hri_gmac_tidm3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM3;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TIDM3_reg(const void *const hw, hri_gmac_tidm3_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM3_reg(const void *const hw, hri_gmac_tidm3_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM3_reg(const void *const hw, hri_gmac_tidm3_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM3 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm3_reg_t hri_gmac_read_TIDM3_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TIDM3;
}

static inline void hri_gmac_set_TIDM4_ENID4_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 |= GMAC_TIDM4_ENID4;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_TIDM4_ENID4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM4;
	tmp = (tmp & GMAC_TIDM4_ENID4) >> GMAC_TIDM4_ENID4_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_TIDM4_ENID4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TIDM4;
	tmp &= ~GMAC_TIDM4_ENID4;
	tmp |= value << GMAC_TIDM4_ENID4_Pos;
	((Gmac *)hw)->GMAC_TIDM4 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM4_ENID4_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 &= ~GMAC_TIDM4_ENID4;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM4_ENID4_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 ^= GMAC_TIDM4_ENID4;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_TIDM4_TID_bf(const void *const hw, hri_gmac_tidm4_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 |= GMAC_TIDM4_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm4_reg_t hri_gmac_get_TIDM4_TID_bf(const void *const hw, hri_gmac_tidm4_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM4;
	tmp = (tmp & GMAC_TIDM4_TID(mask)) >> GMAC_TIDM4_TID_Pos;
	return tmp;
}

static inline void hri_gmac_write_TIDM4_TID_bf(const void *const hw, hri_gmac_tidm4_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TIDM4;
	tmp &= ~GMAC_TIDM4_TID_Msk;
	tmp |= GMAC_TIDM4_TID(data);
	((Gmac *)hw)->GMAC_TIDM4 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM4_TID_bf(const void *const hw, hri_gmac_tidm4_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 &= ~GMAC_TIDM4_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM4_TID_bf(const void *const hw, hri_gmac_tidm4_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 ^= GMAC_TIDM4_TID(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm4_reg_t hri_gmac_read_TIDM4_TID_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM4;
	tmp = (tmp & GMAC_TIDM4_TID_Msk) >> GMAC_TIDM4_TID_Pos;
	return tmp;
}

static inline void hri_gmac_set_TIDM4_reg(const void *const hw, hri_gmac_tidm4_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm4_reg_t hri_gmac_get_TIDM4_reg(const void *const hw, hri_gmac_tidm4_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TIDM4;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TIDM4_reg(const void *const hw, hri_gmac_tidm4_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TIDM4_reg(const void *const hw, hri_gmac_tidm4_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TIDM4_reg(const void *const hw, hri_gmac_tidm4_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TIDM4 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tidm4_reg_t hri_gmac_read_TIDM4_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TIDM4;
}

static inline void hri_gmac_set_WOL_MAG_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL |= GMAC_WOL_MAG;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_WOL_MAG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp = (tmp & GMAC_WOL_MAG) >> GMAC_WOL_MAG_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_WOL_MAG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp &= ~GMAC_WOL_MAG;
	tmp |= value << GMAC_WOL_MAG_Pos;
	((Gmac *)hw)->GMAC_WOL = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_WOL_MAG_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL &= ~GMAC_WOL_MAG;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_WOL_MAG_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL ^= GMAC_WOL_MAG;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_WOL_ARP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL |= GMAC_WOL_ARP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_WOL_ARP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp = (tmp & GMAC_WOL_ARP) >> GMAC_WOL_ARP_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_WOL_ARP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp &= ~GMAC_WOL_ARP;
	tmp |= value << GMAC_WOL_ARP_Pos;
	((Gmac *)hw)->GMAC_WOL = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_WOL_ARP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL &= ~GMAC_WOL_ARP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_WOL_ARP_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL ^= GMAC_WOL_ARP;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_WOL_SA1_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL |= GMAC_WOL_SA1;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_WOL_SA1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp = (tmp & GMAC_WOL_SA1) >> GMAC_WOL_SA1_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_WOL_SA1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp &= ~GMAC_WOL_SA1;
	tmp |= value << GMAC_WOL_SA1_Pos;
	((Gmac *)hw)->GMAC_WOL = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_WOL_SA1_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL &= ~GMAC_WOL_SA1;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_WOL_SA1_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL ^= GMAC_WOL_SA1;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_WOL_MTI_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL |= GMAC_WOL_MTI;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_WOL_MTI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp = (tmp & GMAC_WOL_MTI) >> GMAC_WOL_MTI_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_WOL_MTI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp &= ~GMAC_WOL_MTI;
	tmp |= value << GMAC_WOL_MTI_Pos;
	((Gmac *)hw)->GMAC_WOL = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_WOL_MTI_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL &= ~GMAC_WOL_MTI;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_WOL_MTI_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL ^= GMAC_WOL_MTI;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_WOL_IP_bf(const void *const hw, hri_gmac_wol_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL |= GMAC_WOL_IP(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_wol_reg_t hri_gmac_get_WOL_IP_bf(const void *const hw, hri_gmac_wol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp = (tmp & GMAC_WOL_IP(mask)) >> GMAC_WOL_IP_Pos;
	return tmp;
}

static inline void hri_gmac_write_WOL_IP_bf(const void *const hw, hri_gmac_wol_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp &= ~GMAC_WOL_IP_Msk;
	tmp |= GMAC_WOL_IP(data);
	((Gmac *)hw)->GMAC_WOL = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_WOL_IP_bf(const void *const hw, hri_gmac_wol_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL &= ~GMAC_WOL_IP(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_WOL_IP_bf(const void *const hw, hri_gmac_wol_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL ^= GMAC_WOL_IP(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_wol_reg_t hri_gmac_read_WOL_IP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp = (tmp & GMAC_WOL_IP_Msk) >> GMAC_WOL_IP_Pos;
	return tmp;
}

static inline void hri_gmac_set_WOL_reg(const void *const hw, hri_gmac_wol_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_wol_reg_t hri_gmac_get_WOL_reg(const void *const hw, hri_gmac_wol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_WOL;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_WOL_reg(const void *const hw, hri_gmac_wol_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_WOL_reg(const void *const hw, hri_gmac_wol_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_WOL_reg(const void *const hw, hri_gmac_wol_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_WOL ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_wol_reg_t hri_gmac_read_WOL_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_WOL;
}

static inline void hri_gmac_set_IPGS_FL_bf(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_IPGS |= GMAC_IPGS_FL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ipgs_reg_t hri_gmac_get_IPGS_FL_bf(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_IPGS;
	tmp = (tmp & GMAC_IPGS_FL(mask)) >> GMAC_IPGS_FL_Pos;
	return tmp;
}

static inline void hri_gmac_write_IPGS_FL_bf(const void *const hw, hri_gmac_ipgs_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_IPGS;
	tmp &= ~GMAC_IPGS_FL_Msk;
	tmp |= GMAC_IPGS_FL(data);
	((Gmac *)hw)->GMAC_IPGS = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_IPGS_FL_bf(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_IPGS &= ~GMAC_IPGS_FL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_IPGS_FL_bf(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_IPGS ^= GMAC_IPGS_FL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ipgs_reg_t hri_gmac_read_IPGS_FL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_IPGS;
	tmp = (tmp & GMAC_IPGS_FL_Msk) >> GMAC_IPGS_FL_Pos;
	return tmp;
}

static inline void hri_gmac_set_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_IPGS |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ipgs_reg_t hri_gmac_get_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_IPGS;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_IPGS = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_IPGS &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_IPGS_reg(const void *const hw, hri_gmac_ipgs_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_IPGS ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ipgs_reg_t hri_gmac_read_IPGS_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_IPGS;
}

static inline void hri_gmac_set_SVLAN_ESVLAN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN |= GMAC_SVLAN_ESVLAN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_SVLAN_ESVLAN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SVLAN;
	tmp = (tmp & GMAC_SVLAN_ESVLAN) >> GMAC_SVLAN_ESVLAN_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_SVLAN_ESVLAN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_SVLAN;
	tmp &= ~GMAC_SVLAN_ESVLAN;
	tmp |= value << GMAC_SVLAN_ESVLAN_Pos;
	((Gmac *)hw)->GMAC_SVLAN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SVLAN_ESVLAN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN &= ~GMAC_SVLAN_ESVLAN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SVLAN_ESVLAN_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN ^= GMAC_SVLAN_ESVLAN;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_SVLAN_VLAN_TYPE_bf(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN |= GMAC_SVLAN_VLAN_TYPE(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_svlan_reg_t hri_gmac_get_SVLAN_VLAN_TYPE_bf(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SVLAN;
	tmp = (tmp & GMAC_SVLAN_VLAN_TYPE(mask)) >> GMAC_SVLAN_VLAN_TYPE_Pos;
	return tmp;
}

static inline void hri_gmac_write_SVLAN_VLAN_TYPE_bf(const void *const hw, hri_gmac_svlan_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_SVLAN;
	tmp &= ~GMAC_SVLAN_VLAN_TYPE_Msk;
	tmp |= GMAC_SVLAN_VLAN_TYPE(data);
	((Gmac *)hw)->GMAC_SVLAN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SVLAN_VLAN_TYPE_bf(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN &= ~GMAC_SVLAN_VLAN_TYPE(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SVLAN_VLAN_TYPE_bf(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN ^= GMAC_SVLAN_VLAN_TYPE(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_svlan_reg_t hri_gmac_read_SVLAN_VLAN_TYPE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SVLAN;
	tmp = (tmp & GMAC_SVLAN_VLAN_TYPE_Msk) >> GMAC_SVLAN_VLAN_TYPE_Pos;
	return tmp;
}

static inline void hri_gmac_set_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_svlan_reg_t hri_gmac_get_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SVLAN;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SVLAN_reg(const void *const hw, hri_gmac_svlan_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SVLAN ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_svlan_reg_t hri_gmac_read_SVLAN_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_SVLAN;
}

static inline void hri_gmac_set_TPFCP_PEV_bf(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP |= GMAC_TPFCP_PEV(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpfcp_reg_t hri_gmac_get_TPFCP_PEV_bf(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPFCP;
	tmp = (tmp & GMAC_TPFCP_PEV(mask)) >> GMAC_TPFCP_PEV_Pos;
	return tmp;
}

static inline void hri_gmac_write_TPFCP_PEV_bf(const void *const hw, hri_gmac_tpfcp_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TPFCP;
	tmp &= ~GMAC_TPFCP_PEV_Msk;
	tmp |= GMAC_TPFCP_PEV(data);
	((Gmac *)hw)->GMAC_TPFCP = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPFCP_PEV_bf(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP &= ~GMAC_TPFCP_PEV(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPFCP_PEV_bf(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP ^= GMAC_TPFCP_PEV(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpfcp_reg_t hri_gmac_read_TPFCP_PEV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPFCP;
	tmp = (tmp & GMAC_TPFCP_PEV_Msk) >> GMAC_TPFCP_PEV_Pos;
	return tmp;
}

static inline void hri_gmac_set_TPFCP_PQ_bf(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP |= GMAC_TPFCP_PQ(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpfcp_reg_t hri_gmac_get_TPFCP_PQ_bf(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPFCP;
	tmp = (tmp & GMAC_TPFCP_PQ(mask)) >> GMAC_TPFCP_PQ_Pos;
	return tmp;
}

static inline void hri_gmac_write_TPFCP_PQ_bf(const void *const hw, hri_gmac_tpfcp_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TPFCP;
	tmp &= ~GMAC_TPFCP_PQ_Msk;
	tmp |= GMAC_TPFCP_PQ(data);
	((Gmac *)hw)->GMAC_TPFCP = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPFCP_PQ_bf(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP &= ~GMAC_TPFCP_PQ(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPFCP_PQ_bf(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP ^= GMAC_TPFCP_PQ(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpfcp_reg_t hri_gmac_read_TPFCP_PQ_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPFCP;
	tmp = (tmp & GMAC_TPFCP_PQ_Msk) >> GMAC_TPFCP_PQ_Pos;
	return tmp;
}

static inline void hri_gmac_set_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpfcp_reg_t hri_gmac_get_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TPFCP;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TPFCP_reg(const void *const hw, hri_gmac_tpfcp_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TPFCP ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tpfcp_reg_t hri_gmac_read_TPFCP_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TPFCP;
}

static inline void hri_gmac_set_SAMB1_ADDR_bf(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMB1 |= GMAC_SAMB1_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samb1_reg_t hri_gmac_get_SAMB1_ADDR_bf(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SAMB1;
	tmp = (tmp & GMAC_SAMB1_ADDR(mask)) >> GMAC_SAMB1_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_write_SAMB1_ADDR_bf(const void *const hw, hri_gmac_samb1_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_SAMB1;
	tmp &= ~GMAC_SAMB1_ADDR_Msk;
	tmp |= GMAC_SAMB1_ADDR(data);
	((Gmac *)hw)->GMAC_SAMB1 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAMB1_ADDR_bf(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMB1 &= ~GMAC_SAMB1_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAMB1_ADDR_bf(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMB1 ^= GMAC_SAMB1_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samb1_reg_t hri_gmac_read_SAMB1_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SAMB1;
	tmp = (tmp & GMAC_SAMB1_ADDR_Msk) >> GMAC_SAMB1_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_set_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMB1 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samb1_reg_t hri_gmac_get_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SAMB1;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMB1 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMB1 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAMB1_reg(const void *const hw, hri_gmac_samb1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMB1 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samb1_reg_t hri_gmac_read_SAMB1_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_SAMB1;
}

static inline void hri_gmac_set_SAMT1_ADDR_bf(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMT1 |= GMAC_SAMT1_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samt1_reg_t hri_gmac_get_SAMT1_ADDR_bf(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SAMT1;
	tmp = (tmp & GMAC_SAMT1_ADDR(mask)) >> GMAC_SAMT1_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_write_SAMT1_ADDR_bf(const void *const hw, hri_gmac_samt1_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_SAMT1;
	tmp &= ~GMAC_SAMT1_ADDR_Msk;
	tmp |= GMAC_SAMT1_ADDR(data);
	((Gmac *)hw)->GMAC_SAMT1 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAMT1_ADDR_bf(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMT1 &= ~GMAC_SAMT1_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAMT1_ADDR_bf(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMT1 ^= GMAC_SAMT1_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samt1_reg_t hri_gmac_read_SAMT1_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SAMT1;
	tmp = (tmp & GMAC_SAMT1_ADDR_Msk) >> GMAC_SAMT1_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_set_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMT1 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samt1_reg_t hri_gmac_get_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SAMT1;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMT1 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMT1 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAMT1_reg(const void *const hw, hri_gmac_samt1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SAMT1 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_samt1_reg_t hri_gmac_read_SAMT1_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_SAMT1;
}

static inline void hri_gmac_set_NSC_NANOSEC_bf(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NSC |= GMAC_NSC_NANOSEC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_nsc_reg_t hri_gmac_get_NSC_NANOSEC_bf(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NSC;
	tmp = (tmp & GMAC_NSC_NANOSEC(mask)) >> GMAC_NSC_NANOSEC_Pos;
	return tmp;
}

static inline void hri_gmac_write_NSC_NANOSEC_bf(const void *const hw, hri_gmac_nsc_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_NSC;
	tmp &= ~GMAC_NSC_NANOSEC_Msk;
	tmp |= GMAC_NSC_NANOSEC(data);
	((Gmac *)hw)->GMAC_NSC = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NSC_NANOSEC_bf(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NSC &= ~GMAC_NSC_NANOSEC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NSC_NANOSEC_bf(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NSC ^= GMAC_NSC_NANOSEC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_nsc_reg_t hri_gmac_read_NSC_NANOSEC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NSC;
	tmp = (tmp & GMAC_NSC_NANOSEC_Msk) >> GMAC_NSC_NANOSEC_Pos;
	return tmp;
}

static inline void hri_gmac_set_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NSC |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_nsc_reg_t hri_gmac_get_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_NSC;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NSC = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NSC &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_NSC_reg(const void *const hw, hri_gmac_nsc_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_NSC ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_nsc_reg_t hri_gmac_read_NSC_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_NSC;
}

static inline void hri_gmac_set_SCL_SEC_bf(const void *const hw, hri_gmac_scl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCL |= GMAC_SCL_SEC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_scl_reg_t hri_gmac_get_SCL_SEC_bf(const void *const hw, hri_gmac_scl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SCL;
	tmp = (tmp & GMAC_SCL_SEC(mask)) >> GMAC_SCL_SEC_Pos;
	return tmp;
}

static inline void hri_gmac_write_SCL_SEC_bf(const void *const hw, hri_gmac_scl_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_SCL;
	tmp &= ~GMAC_SCL_SEC_Msk;
	tmp |= GMAC_SCL_SEC(data);
	((Gmac *)hw)->GMAC_SCL = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SCL_SEC_bf(const void *const hw, hri_gmac_scl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCL &= ~GMAC_SCL_SEC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SCL_SEC_bf(const void *const hw, hri_gmac_scl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCL ^= GMAC_SCL_SEC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_scl_reg_t hri_gmac_read_SCL_SEC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SCL;
	tmp = (tmp & GMAC_SCL_SEC_Msk) >> GMAC_SCL_SEC_Pos;
	return tmp;
}

static inline void hri_gmac_set_SCL_reg(const void *const hw, hri_gmac_scl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCL |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_scl_reg_t hri_gmac_get_SCL_reg(const void *const hw, hri_gmac_scl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SCL;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SCL_reg(const void *const hw, hri_gmac_scl_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCL = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SCL_reg(const void *const hw, hri_gmac_scl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCL &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SCL_reg(const void *const hw, hri_gmac_scl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCL ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_scl_reg_t hri_gmac_read_SCL_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_SCL;
}

static inline void hri_gmac_set_SCH_SEC_bf(const void *const hw, hri_gmac_sch_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCH |= GMAC_SCH_SEC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sch_reg_t hri_gmac_get_SCH_SEC_bf(const void *const hw, hri_gmac_sch_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SCH;
	tmp = (tmp & GMAC_SCH_SEC(mask)) >> GMAC_SCH_SEC_Pos;
	return tmp;
}

static inline void hri_gmac_write_SCH_SEC_bf(const void *const hw, hri_gmac_sch_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_SCH;
	tmp &= ~GMAC_SCH_SEC_Msk;
	tmp |= GMAC_SCH_SEC(data);
	((Gmac *)hw)->GMAC_SCH = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SCH_SEC_bf(const void *const hw, hri_gmac_sch_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCH &= ~GMAC_SCH_SEC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SCH_SEC_bf(const void *const hw, hri_gmac_sch_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCH ^= GMAC_SCH_SEC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sch_reg_t hri_gmac_read_SCH_SEC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SCH;
	tmp = (tmp & GMAC_SCH_SEC_Msk) >> GMAC_SCH_SEC_Pos;
	return tmp;
}

static inline void hri_gmac_set_SCH_reg(const void *const hw, hri_gmac_sch_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCH |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sch_reg_t hri_gmac_get_SCH_reg(const void *const hw, hri_gmac_sch_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_SCH;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SCH_reg(const void *const hw, hri_gmac_sch_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCH = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SCH_reg(const void *const hw, hri_gmac_sch_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCH &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SCH_reg(const void *const hw, hri_gmac_sch_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_SCH ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sch_reg_t hri_gmac_read_SCH_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_SCH;
}

static inline void hri_gmac_set_TISUBN_LSBTIR_bf(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TISUBN |= GMAC_TISUBN_LSBTIR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tisubn_reg_t hri_gmac_get_TISUBN_LSBTIR_bf(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TISUBN;
	tmp = (tmp & GMAC_TISUBN_LSBTIR(mask)) >> GMAC_TISUBN_LSBTIR_Pos;
	return tmp;
}

static inline void hri_gmac_write_TISUBN_LSBTIR_bf(const void *const hw, hri_gmac_tisubn_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TISUBN;
	tmp &= ~GMAC_TISUBN_LSBTIR_Msk;
	tmp |= GMAC_TISUBN_LSBTIR(data);
	((Gmac *)hw)->GMAC_TISUBN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TISUBN_LSBTIR_bf(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TISUBN &= ~GMAC_TISUBN_LSBTIR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TISUBN_LSBTIR_bf(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TISUBN ^= GMAC_TISUBN_LSBTIR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tisubn_reg_t hri_gmac_read_TISUBN_LSBTIR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TISUBN;
	tmp = (tmp & GMAC_TISUBN_LSBTIR_Msk) >> GMAC_TISUBN_LSBTIR_Pos;
	return tmp;
}

static inline void hri_gmac_set_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TISUBN |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tisubn_reg_t hri_gmac_get_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TISUBN;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TISUBN = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TISUBN &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TISUBN_reg(const void *const hw, hri_gmac_tisubn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TISUBN ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tisubn_reg_t hri_gmac_read_TISUBN_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TISUBN;
}

static inline void hri_gmac_set_TSH_TCS_bf(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSH |= GMAC_TSH_TCS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsh_reg_t hri_gmac_get_TSH_TCS_bf(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSH;
	tmp = (tmp & GMAC_TSH_TCS(mask)) >> GMAC_TSH_TCS_Pos;
	return tmp;
}

static inline void hri_gmac_write_TSH_TCS_bf(const void *const hw, hri_gmac_tsh_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TSH;
	tmp &= ~GMAC_TSH_TCS_Msk;
	tmp |= GMAC_TSH_TCS(data);
	((Gmac *)hw)->GMAC_TSH = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSH_TCS_bf(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSH &= ~GMAC_TSH_TCS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSH_TCS_bf(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSH ^= GMAC_TSH_TCS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsh_reg_t hri_gmac_read_TSH_TCS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSH;
	tmp = (tmp & GMAC_TSH_TCS_Msk) >> GMAC_TSH_TCS_Pos;
	return tmp;
}

static inline void hri_gmac_set_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSH |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsh_reg_t hri_gmac_get_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSH;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSH = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSH &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSH_reg(const void *const hw, hri_gmac_tsh_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSH ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsh_reg_t hri_gmac_read_TSH_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TSH;
}

static inline void hri_gmac_set_TSL_TCS_bf(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSL |= GMAC_TSL_TCS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsl_reg_t hri_gmac_get_TSL_TCS_bf(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSL;
	tmp = (tmp & GMAC_TSL_TCS(mask)) >> GMAC_TSL_TCS_Pos;
	return tmp;
}

static inline void hri_gmac_write_TSL_TCS_bf(const void *const hw, hri_gmac_tsl_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TSL;
	tmp &= ~GMAC_TSL_TCS_Msk;
	tmp |= GMAC_TSL_TCS(data);
	((Gmac *)hw)->GMAC_TSL = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSL_TCS_bf(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSL &= ~GMAC_TSL_TCS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSL_TCS_bf(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSL ^= GMAC_TSL_TCS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsl_reg_t hri_gmac_read_TSL_TCS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSL;
	tmp = (tmp & GMAC_TSL_TCS_Msk) >> GMAC_TSL_TCS_Pos;
	return tmp;
}

static inline void hri_gmac_set_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSL |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsl_reg_t hri_gmac_get_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TSL;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSL = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSL &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TSL_reg(const void *const hw, hri_gmac_tsl_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TSL ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tsl_reg_t hri_gmac_read_TSL_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TSL;
}

static inline void hri_gmac_set_TN_TNS_bf(const void *const hw, hri_gmac_tn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TN |= GMAC_TN_TNS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tn_reg_t hri_gmac_get_TN_TNS_bf(const void *const hw, hri_gmac_tn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TN;
	tmp = (tmp & GMAC_TN_TNS(mask)) >> GMAC_TN_TNS_Pos;
	return tmp;
}

static inline void hri_gmac_write_TN_TNS_bf(const void *const hw, hri_gmac_tn_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TN;
	tmp &= ~GMAC_TN_TNS_Msk;
	tmp |= GMAC_TN_TNS(data);
	((Gmac *)hw)->GMAC_TN = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TN_TNS_bf(const void *const hw, hri_gmac_tn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TN &= ~GMAC_TN_TNS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TN_TNS_bf(const void *const hw, hri_gmac_tn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TN ^= GMAC_TN_TNS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tn_reg_t hri_gmac_read_TN_TNS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TN;
	tmp = (tmp & GMAC_TN_TNS_Msk) >> GMAC_TN_TNS_Pos;
	return tmp;
}

static inline void hri_gmac_set_TN_reg(const void *const hw, hri_gmac_tn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TN |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tn_reg_t hri_gmac_get_TN_reg(const void *const hw, hri_gmac_tn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TN;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TN_reg(const void *const hw, hri_gmac_tn_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TN = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TN_reg(const void *const hw, hri_gmac_tn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TN &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TN_reg(const void *const hw, hri_gmac_tn_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TN ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tn_reg_t hri_gmac_read_TN_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TN;
}

static inline void hri_gmac_set_TI_CNS_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI |= GMAC_TI_CNS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_get_TI_CNS_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp = (tmp & GMAC_TI_CNS(mask)) >> GMAC_TI_CNS_Pos;
	return tmp;
}

static inline void hri_gmac_write_TI_CNS_bf(const void *const hw, hri_gmac_ti_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp &= ~GMAC_TI_CNS_Msk;
	tmp |= GMAC_TI_CNS(data);
	((Gmac *)hw)->GMAC_TI = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TI_CNS_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI &= ~GMAC_TI_CNS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TI_CNS_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI ^= GMAC_TI_CNS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_read_TI_CNS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp = (tmp & GMAC_TI_CNS_Msk) >> GMAC_TI_CNS_Pos;
	return tmp;
}

static inline void hri_gmac_set_TI_ACNS_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI |= GMAC_TI_ACNS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_get_TI_ACNS_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp = (tmp & GMAC_TI_ACNS(mask)) >> GMAC_TI_ACNS_Pos;
	return tmp;
}

static inline void hri_gmac_write_TI_ACNS_bf(const void *const hw, hri_gmac_ti_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp &= ~GMAC_TI_ACNS_Msk;
	tmp |= GMAC_TI_ACNS(data);
	((Gmac *)hw)->GMAC_TI = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TI_ACNS_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI &= ~GMAC_TI_ACNS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TI_ACNS_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI ^= GMAC_TI_ACNS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_read_TI_ACNS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp = (tmp & GMAC_TI_ACNS_Msk) >> GMAC_TI_ACNS_Pos;
	return tmp;
}

static inline void hri_gmac_set_TI_NIT_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI |= GMAC_TI_NIT(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_get_TI_NIT_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp = (tmp & GMAC_TI_NIT(mask)) >> GMAC_TI_NIT_Pos;
	return tmp;
}

static inline void hri_gmac_write_TI_NIT_bf(const void *const hw, hri_gmac_ti_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp &= ~GMAC_TI_NIT_Msk;
	tmp |= GMAC_TI_NIT(data);
	((Gmac *)hw)->GMAC_TI = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TI_NIT_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI &= ~GMAC_TI_NIT(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TI_NIT_bf(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI ^= GMAC_TI_NIT(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_read_TI_NIT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp = (tmp & GMAC_TI_NIT_Msk) >> GMAC_TI_NIT_Pos;
	return tmp;
}

static inline void hri_gmac_set_TI_reg(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_get_TI_reg(const void *const hw, hri_gmac_ti_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TI;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TI_reg(const void *const hw, hri_gmac_ti_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TI_reg(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TI_reg(const void *const hw, hri_gmac_ti_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TI ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_ti_reg_t hri_gmac_read_TI_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_TI;
}

static inline void hri_gmac_set_TBQBAPQ_TXBQBA_bf(const void *const hw, uint8_t index, hri_gmac_tbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQBAPQ[index] |= GMAC_TBQBAPQ_TXBQBA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqbapq_reg_t hri_gmac_get_TBQBAPQ_TXBQBA_bf(const void *const hw, uint8_t index,
                                                                    hri_gmac_tbqbapq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBQBAPQ[index];
	tmp = (tmp & GMAC_TBQBAPQ_TXBQBA(mask)) >> GMAC_TBQBAPQ_TXBQBA_Pos;
	return tmp;
}

static inline void hri_gmac_write_TBQBAPQ_TXBQBA_bf(const void *const hw, uint8_t index, hri_gmac_tbqbapq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_TBQBAPQ[index];
	tmp &= ~GMAC_TBQBAPQ_TXBQBA_Msk;
	tmp |= GMAC_TBQBAPQ_TXBQBA(data);
	((Gmac *)hw)->GMAC_TBQBAPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TBQBAPQ_TXBQBA_bf(const void *const hw, uint8_t index, hri_gmac_tbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQBAPQ[index] &= ~GMAC_TBQBAPQ_TXBQBA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TBQBAPQ_TXBQBA_bf(const void *const hw, uint8_t index, hri_gmac_tbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQBAPQ[index] ^= GMAC_TBQBAPQ_TXBQBA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqbapq_reg_t hri_gmac_read_TBQBAPQ_TXBQBA_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBQBAPQ[index];
	tmp = (tmp & GMAC_TBQBAPQ_TXBQBA_Msk) >> GMAC_TBQBAPQ_TXBQBA_Pos;
	return tmp;
}

static inline void hri_gmac_set_TBQBAPQ_reg(const void *const hw, uint8_t index, hri_gmac_tbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQBAPQ[index] |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqbapq_reg_t hri_gmac_get_TBQBAPQ_reg(const void *const hw, uint8_t index,
                                                              hri_gmac_tbqbapq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_TBQBAPQ[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_TBQBAPQ_reg(const void *const hw, uint8_t index, hri_gmac_tbqbapq_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQBAPQ[index] = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_TBQBAPQ_reg(const void *const hw, uint8_t index, hri_gmac_tbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQBAPQ[index] &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_TBQBAPQ_reg(const void *const hw, uint8_t index, hri_gmac_tbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TBQBAPQ[index] ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_tbqbapq_reg_t hri_gmac_read_TBQBAPQ_reg(const void *const hw, uint8_t index)
{
	return ((Gmac *)hw)->GMAC_TBQBAPQ[index];
}

static inline void hri_gmac_set_RBQBAPQ_RXBQBA_bf(const void *const hw, uint8_t index, hri_gmac_rbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQBAPQ[index] |= GMAC_RBQBAPQ_RXBQBA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqbapq_reg_t hri_gmac_get_RBQBAPQ_RXBQBA_bf(const void *const hw, uint8_t index,
                                                                    hri_gmac_rbqbapq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RBQBAPQ[index];
	tmp = (tmp & GMAC_RBQBAPQ_RXBQBA(mask)) >> GMAC_RBQBAPQ_RXBQBA_Pos;
	return tmp;
}

static inline void hri_gmac_write_RBQBAPQ_RXBQBA_bf(const void *const hw, uint8_t index, hri_gmac_rbqbapq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RBQBAPQ[index];
	tmp &= ~GMAC_RBQBAPQ_RXBQBA_Msk;
	tmp |= GMAC_RBQBAPQ_RXBQBA(data);
	((Gmac *)hw)->GMAC_RBQBAPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RBQBAPQ_RXBQBA_bf(const void *const hw, uint8_t index, hri_gmac_rbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQBAPQ[index] &= ~GMAC_RBQBAPQ_RXBQBA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RBQBAPQ_RXBQBA_bf(const void *const hw, uint8_t index, hri_gmac_rbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQBAPQ[index] ^= GMAC_RBQBAPQ_RXBQBA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqbapq_reg_t hri_gmac_read_RBQBAPQ_RXBQBA_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RBQBAPQ[index];
	tmp = (tmp & GMAC_RBQBAPQ_RXBQBA_Msk) >> GMAC_RBQBAPQ_RXBQBA_Pos;
	return tmp;
}

static inline void hri_gmac_set_RBQBAPQ_reg(const void *const hw, uint8_t index, hri_gmac_rbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQBAPQ[index] |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqbapq_reg_t hri_gmac_get_RBQBAPQ_reg(const void *const hw, uint8_t index,
                                                              hri_gmac_rbqbapq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RBQBAPQ[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RBQBAPQ_reg(const void *const hw, uint8_t index, hri_gmac_rbqbapq_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQBAPQ[index] = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RBQBAPQ_reg(const void *const hw, uint8_t index, hri_gmac_rbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQBAPQ[index] &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RBQBAPQ_reg(const void *const hw, uint8_t index, hri_gmac_rbqbapq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBQBAPQ[index] ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbqbapq_reg_t hri_gmac_read_RBQBAPQ_reg(const void *const hw, uint8_t index)
{
	return ((Gmac *)hw)->GMAC_RBQBAPQ[index];
}

static inline void hri_gmac_set_RBSRPQ_RBS_bf(const void *const hw, uint8_t index, hri_gmac_rbsrpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBSRPQ[index] |= GMAC_RBSRPQ_RBS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbsrpq_reg_t hri_gmac_get_RBSRPQ_RBS_bf(const void *const hw, uint8_t index,
                                                               hri_gmac_rbsrpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RBSRPQ[index];
	tmp = (tmp & GMAC_RBSRPQ_RBS(mask)) >> GMAC_RBSRPQ_RBS_Pos;
	return tmp;
}

static inline void hri_gmac_write_RBSRPQ_RBS_bf(const void *const hw, uint8_t index, hri_gmac_rbsrpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_RBSRPQ[index];
	tmp &= ~GMAC_RBSRPQ_RBS_Msk;
	tmp |= GMAC_RBSRPQ_RBS(data);
	((Gmac *)hw)->GMAC_RBSRPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RBSRPQ_RBS_bf(const void *const hw, uint8_t index, hri_gmac_rbsrpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBSRPQ[index] &= ~GMAC_RBSRPQ_RBS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RBSRPQ_RBS_bf(const void *const hw, uint8_t index, hri_gmac_rbsrpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBSRPQ[index] ^= GMAC_RBSRPQ_RBS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbsrpq_reg_t hri_gmac_read_RBSRPQ_RBS_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RBSRPQ[index];
	tmp = (tmp & GMAC_RBSRPQ_RBS_Msk) >> GMAC_RBSRPQ_RBS_Pos;
	return tmp;
}

static inline void hri_gmac_set_RBSRPQ_reg(const void *const hw, uint8_t index, hri_gmac_rbsrpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBSRPQ[index] |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbsrpq_reg_t hri_gmac_get_RBSRPQ_reg(const void *const hw, uint8_t index,
                                                            hri_gmac_rbsrpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_RBSRPQ[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_RBSRPQ_reg(const void *const hw, uint8_t index, hri_gmac_rbsrpq_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBSRPQ[index] = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_RBSRPQ_reg(const void *const hw, uint8_t index, hri_gmac_rbsrpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBSRPQ[index] &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_RBSRPQ_reg(const void *const hw, uint8_t index, hri_gmac_rbsrpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_RBSRPQ[index] ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_rbsrpq_reg_t hri_gmac_read_RBSRPQ_reg(const void *const hw, uint8_t index)
{
	return ((Gmac *)hw)->GMAC_RBSRPQ[index];
}

static inline void hri_gmac_set_CBSCR_QBE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR |= GMAC_CBSCR_QBE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_CBSCR_QBE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CBSCR;
	tmp = (tmp & GMAC_CBSCR_QBE) >> GMAC_CBSCR_QBE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_CBSCR_QBE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_CBSCR;
	tmp &= ~GMAC_CBSCR_QBE;
	tmp |= value << GMAC_CBSCR_QBE_Pos;
	((Gmac *)hw)->GMAC_CBSCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_CBSCR_QBE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR &= ~GMAC_CBSCR_QBE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_CBSCR_QBE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR ^= GMAC_CBSCR_QBE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_CBSCR_QAE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR |= GMAC_CBSCR_QAE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_CBSCR_QAE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CBSCR;
	tmp = (tmp & GMAC_CBSCR_QAE) >> GMAC_CBSCR_QAE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_CBSCR_QAE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_CBSCR;
	tmp &= ~GMAC_CBSCR_QAE;
	tmp |= value << GMAC_CBSCR_QAE_Pos;
	((Gmac *)hw)->GMAC_CBSCR = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_CBSCR_QAE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR &= ~GMAC_CBSCR_QAE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_CBSCR_QAE_bit(const void *const hw)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR ^= GMAC_CBSCR_QAE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_CBSCR_reg(const void *const hw, hri_gmac_cbscr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbscr_reg_t hri_gmac_get_CBSCR_reg(const void *const hw, hri_gmac_cbscr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CBSCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_CBSCR_reg(const void *const hw, hri_gmac_cbscr_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_CBSCR_reg(const void *const hw, hri_gmac_cbscr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_CBSCR_reg(const void *const hw, hri_gmac_cbscr_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSCR ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbscr_reg_t hri_gmac_read_CBSCR_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_CBSCR;
}

static inline void hri_gmac_set_CBSISQA_IS_bf(const void *const hw, hri_gmac_cbsisqa_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQA |= GMAC_CBSISQA_IS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbsisqa_reg_t hri_gmac_get_CBSISQA_IS_bf(const void *const hw, hri_gmac_cbsisqa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CBSISQA;
	tmp = (tmp & GMAC_CBSISQA_IS(mask)) >> GMAC_CBSISQA_IS_Pos;
	return tmp;
}

static inline void hri_gmac_write_CBSISQA_IS_bf(const void *const hw, hri_gmac_cbsisqa_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_CBSISQA;
	tmp &= ~GMAC_CBSISQA_IS_Msk;
	tmp |= GMAC_CBSISQA_IS(data);
	((Gmac *)hw)->GMAC_CBSISQA = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_CBSISQA_IS_bf(const void *const hw, hri_gmac_cbsisqa_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQA &= ~GMAC_CBSISQA_IS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_CBSISQA_IS_bf(const void *const hw, hri_gmac_cbsisqa_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQA ^= GMAC_CBSISQA_IS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbsisqa_reg_t hri_gmac_read_CBSISQA_IS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CBSISQA;
	tmp = (tmp & GMAC_CBSISQA_IS_Msk) >> GMAC_CBSISQA_IS_Pos;
	return tmp;
}

static inline void hri_gmac_set_CBSISQA_reg(const void *const hw, hri_gmac_cbsisqa_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQA |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbsisqa_reg_t hri_gmac_get_CBSISQA_reg(const void *const hw, hri_gmac_cbsisqa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CBSISQA;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_CBSISQA_reg(const void *const hw, hri_gmac_cbsisqa_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQA = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_CBSISQA_reg(const void *const hw, hri_gmac_cbsisqa_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQA &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_CBSISQA_reg(const void *const hw, hri_gmac_cbsisqa_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQA ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbsisqa_reg_t hri_gmac_read_CBSISQA_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_CBSISQA;
}

static inline void hri_gmac_set_CBSISQB_IS_bf(const void *const hw, hri_gmac_cbsisqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQB |= GMAC_CBSISQB_IS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbsisqb_reg_t hri_gmac_get_CBSISQB_IS_bf(const void *const hw, hri_gmac_cbsisqb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CBSISQB;
	tmp = (tmp & GMAC_CBSISQB_IS(mask)) >> GMAC_CBSISQB_IS_Pos;
	return tmp;
}

static inline void hri_gmac_write_CBSISQB_IS_bf(const void *const hw, hri_gmac_cbsisqb_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_CBSISQB;
	tmp &= ~GMAC_CBSISQB_IS_Msk;
	tmp |= GMAC_CBSISQB_IS(data);
	((Gmac *)hw)->GMAC_CBSISQB = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_CBSISQB_IS_bf(const void *const hw, hri_gmac_cbsisqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQB &= ~GMAC_CBSISQB_IS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_CBSISQB_IS_bf(const void *const hw, hri_gmac_cbsisqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQB ^= GMAC_CBSISQB_IS(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbsisqb_reg_t hri_gmac_read_CBSISQB_IS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CBSISQB;
	tmp = (tmp & GMAC_CBSISQB_IS_Msk) >> GMAC_CBSISQB_IS_Pos;
	return tmp;
}

static inline void hri_gmac_set_CBSISQB_reg(const void *const hw, hri_gmac_cbsisqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQB |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbsisqb_reg_t hri_gmac_get_CBSISQB_reg(const void *const hw, hri_gmac_cbsisqb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_CBSISQB;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_CBSISQB_reg(const void *const hw, hri_gmac_cbsisqb_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQB = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_CBSISQB_reg(const void *const hw, hri_gmac_cbsisqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQB &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_CBSISQB_reg(const void *const hw, hri_gmac_cbsisqb_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_CBSISQB ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_cbsisqb_reg_t hri_gmac_read_CBSISQB_reg(const void *const hw)
{
	return ((Gmac *)hw)->GMAC_CBSISQB;
}

static inline void hri_gmac_set_ST1RPQ_DSTCE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] |= GMAC_ST1RPQ_DSTCE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_ST1RPQ_DSTCE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp = (tmp & GMAC_ST1RPQ_DSTCE) >> GMAC_ST1RPQ_DSTCE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_ST1RPQ_DSTCE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp &= ~GMAC_ST1RPQ_DSTCE;
	tmp |= value << GMAC_ST1RPQ_DSTCE_Pos;
	((Gmac *)hw)->GMAC_ST1RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST1RPQ_DSTCE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] &= ~GMAC_ST1RPQ_DSTCE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST1RPQ_DSTCE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] ^= GMAC_ST1RPQ_DSTCE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_ST1RPQ_UDPE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] |= GMAC_ST1RPQ_UDPE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_ST1RPQ_UDPE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp = (tmp & GMAC_ST1RPQ_UDPE) >> GMAC_ST1RPQ_UDPE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_ST1RPQ_UDPE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp &= ~GMAC_ST1RPQ_UDPE;
	tmp |= value << GMAC_ST1RPQ_UDPE_Pos;
	((Gmac *)hw)->GMAC_ST1RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST1RPQ_UDPE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] &= ~GMAC_ST1RPQ_UDPE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST1RPQ_UDPE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] ^= GMAC_ST1RPQ_UDPE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_ST1RPQ_QNB_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] |= GMAC_ST1RPQ_QNB(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st1rpq_reg_t hri_gmac_get_ST1RPQ_QNB_bf(const void *const hw, uint8_t index,
                                                               hri_gmac_st1rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp = (tmp & GMAC_ST1RPQ_QNB(mask)) >> GMAC_ST1RPQ_QNB_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST1RPQ_QNB_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp &= ~GMAC_ST1RPQ_QNB_Msk;
	tmp |= GMAC_ST1RPQ_QNB(data);
	((Gmac *)hw)->GMAC_ST1RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST1RPQ_QNB_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] &= ~GMAC_ST1RPQ_QNB(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST1RPQ_QNB_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] ^= GMAC_ST1RPQ_QNB(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st1rpq_reg_t hri_gmac_read_ST1RPQ_QNB_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp = (tmp & GMAC_ST1RPQ_QNB_Msk) >> GMAC_ST1RPQ_QNB_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST1RPQ_DSTCM_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] |= GMAC_ST1RPQ_DSTCM(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st1rpq_reg_t hri_gmac_get_ST1RPQ_DSTCM_bf(const void *const hw, uint8_t index,
                                                                 hri_gmac_st1rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp = (tmp & GMAC_ST1RPQ_DSTCM(mask)) >> GMAC_ST1RPQ_DSTCM_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST1RPQ_DSTCM_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp &= ~GMAC_ST1RPQ_DSTCM_Msk;
	tmp |= GMAC_ST1RPQ_DSTCM(data);
	((Gmac *)hw)->GMAC_ST1RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST1RPQ_DSTCM_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] &= ~GMAC_ST1RPQ_DSTCM(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST1RPQ_DSTCM_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] ^= GMAC_ST1RPQ_DSTCM(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st1rpq_reg_t hri_gmac_read_ST1RPQ_DSTCM_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp = (tmp & GMAC_ST1RPQ_DSTCM_Msk) >> GMAC_ST1RPQ_DSTCM_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST1RPQ_UDPM_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] |= GMAC_ST1RPQ_UDPM(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st1rpq_reg_t hri_gmac_get_ST1RPQ_UDPM_bf(const void *const hw, uint8_t index,
                                                                hri_gmac_st1rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp = (tmp & GMAC_ST1RPQ_UDPM(mask)) >> GMAC_ST1RPQ_UDPM_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST1RPQ_UDPM_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp &= ~GMAC_ST1RPQ_UDPM_Msk;
	tmp |= GMAC_ST1RPQ_UDPM(data);
	((Gmac *)hw)->GMAC_ST1RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST1RPQ_UDPM_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] &= ~GMAC_ST1RPQ_UDPM(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST1RPQ_UDPM_bf(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] ^= GMAC_ST1RPQ_UDPM(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st1rpq_reg_t hri_gmac_read_ST1RPQ_UDPM_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp = (tmp & GMAC_ST1RPQ_UDPM_Msk) >> GMAC_ST1RPQ_UDPM_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST1RPQ_reg(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st1rpq_reg_t hri_gmac_get_ST1RPQ_reg(const void *const hw, uint8_t index,
                                                            hri_gmac_st1rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST1RPQ[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_ST1RPQ_reg(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST1RPQ_reg(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST1RPQ_reg(const void *const hw, uint8_t index, hri_gmac_st1rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST1RPQ[index] ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st1rpq_reg_t hri_gmac_read_ST1RPQ_reg(const void *const hw, uint8_t index)
{
	return ((Gmac *)hw)->GMAC_ST1RPQ[index];
}

static inline void hri_gmac_set_ST2RPQ_VLANE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_VLANE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_ST2RPQ_VLANE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_VLANE) >> GMAC_ST2RPQ_VLANE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_ST2RPQ_VLANE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_VLANE;
	tmp |= value << GMAC_ST2RPQ_VLANE_Pos;
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_VLANE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_VLANE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_VLANE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_VLANE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_ST2RPQ_ETHE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_ETHE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_ST2RPQ_ETHE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_ETHE) >> GMAC_ST2RPQ_ETHE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_ST2RPQ_ETHE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_ETHE;
	tmp |= value << GMAC_ST2RPQ_ETHE_Pos;
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_ETHE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_ETHE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_ETHE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_ETHE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_ST2RPQ_COMPAE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_COMPAE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_ST2RPQ_COMPAE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_COMPAE) >> GMAC_ST2RPQ_COMPAE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_ST2RPQ_COMPAE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_COMPAE;
	tmp |= value << GMAC_ST2RPQ_COMPAE_Pos;
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_COMPAE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_COMPAE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_COMPAE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_COMPAE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_ST2RPQ_COMPBE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_COMPBE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_ST2RPQ_COMPBE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_COMPBE) >> GMAC_ST2RPQ_COMPBE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_ST2RPQ_COMPBE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_COMPBE;
	tmp |= value << GMAC_ST2RPQ_COMPBE_Pos;
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_COMPBE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_COMPBE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_COMPBE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_COMPBE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_ST2RPQ_COMPCE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_COMPCE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gmac_get_ST2RPQ_COMPCE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_COMPCE) >> GMAC_ST2RPQ_COMPCE_Pos;
	return (bool)tmp;
}

static inline void hri_gmac_write_ST2RPQ_COMPCE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_COMPCE;
	tmp |= value << GMAC_ST2RPQ_COMPCE_Pos;
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_COMPCE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_COMPCE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_COMPCE_bit(const void *const hw, uint8_t index)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_COMPCE;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_set_ST2RPQ_QNB_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_QNB(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_get_ST2RPQ_QNB_bf(const void *const hw, uint8_t index,
                                                               hri_gmac_st2rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_QNB(mask)) >> GMAC_ST2RPQ_QNB_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2RPQ_QNB_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_QNB_Msk;
	tmp |= GMAC_ST2RPQ_QNB(data);
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_QNB_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_QNB(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_QNB_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_QNB(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_read_ST2RPQ_QNB_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_QNB_Msk) >> GMAC_ST2RPQ_QNB_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2RPQ_VLANP_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_VLANP(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_get_ST2RPQ_VLANP_bf(const void *const hw, uint8_t index,
                                                                 hri_gmac_st2rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_VLANP(mask)) >> GMAC_ST2RPQ_VLANP_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2RPQ_VLANP_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_VLANP_Msk;
	tmp |= GMAC_ST2RPQ_VLANP(data);
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_VLANP_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_VLANP(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_VLANP_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_VLANP(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_read_ST2RPQ_VLANP_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_VLANP_Msk) >> GMAC_ST2RPQ_VLANP_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2RPQ_I2ETH_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_I2ETH(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_get_ST2RPQ_I2ETH_bf(const void *const hw, uint8_t index,
                                                                 hri_gmac_st2rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_I2ETH(mask)) >> GMAC_ST2RPQ_I2ETH_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2RPQ_I2ETH_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_I2ETH_Msk;
	tmp |= GMAC_ST2RPQ_I2ETH(data);
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_I2ETH_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_I2ETH(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_I2ETH_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_I2ETH(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_read_ST2RPQ_I2ETH_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_I2ETH_Msk) >> GMAC_ST2RPQ_I2ETH_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2RPQ_COMPA_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_COMPA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_get_ST2RPQ_COMPA_bf(const void *const hw, uint8_t index,
                                                                 hri_gmac_st2rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_COMPA(mask)) >> GMAC_ST2RPQ_COMPA_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2RPQ_COMPA_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_COMPA_Msk;
	tmp |= GMAC_ST2RPQ_COMPA(data);
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_COMPA_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_COMPA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_COMPA_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_COMPA(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_read_ST2RPQ_COMPA_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_COMPA_Msk) >> GMAC_ST2RPQ_COMPA_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2RPQ_COMPB_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_COMPB(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_get_ST2RPQ_COMPB_bf(const void *const hw, uint8_t index,
                                                                 hri_gmac_st2rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_COMPB(mask)) >> GMAC_ST2RPQ_COMPB_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2RPQ_COMPB_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_COMPB_Msk;
	tmp |= GMAC_ST2RPQ_COMPB(data);
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_COMPB_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_COMPB(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_COMPB_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_COMPB(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_read_ST2RPQ_COMPB_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_COMPB_Msk) >> GMAC_ST2RPQ_COMPB_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2RPQ_COMPC_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= GMAC_ST2RPQ_COMPC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_get_ST2RPQ_COMPC_bf(const void *const hw, uint8_t index,
                                                                 hri_gmac_st2rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_COMPC(mask)) >> GMAC_ST2RPQ_COMPC_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2RPQ_COMPC_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= ~GMAC_ST2RPQ_COMPC_Msk;
	tmp |= GMAC_ST2RPQ_COMPC(data);
	((Gmac *)hw)->GMAC_ST2RPQ[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_COMPC_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~GMAC_ST2RPQ_COMPC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_COMPC_bf(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= GMAC_ST2RPQ_COMPC(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_read_ST2RPQ_COMPC_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp = (tmp & GMAC_ST2RPQ_COMPC_Msk) >> GMAC_ST2RPQ_COMPC_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2RPQ_reg(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_get_ST2RPQ_reg(const void *const hw, uint8_t index,
                                                            hri_gmac_st2rpq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2RPQ[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_ST2RPQ_reg(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2RPQ_reg(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2RPQ_reg(const void *const hw, uint8_t index, hri_gmac_st2rpq_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2RPQ[index] ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2rpq_reg_t hri_gmac_read_ST2RPQ_reg(const void *const hw, uint8_t index)
{
	return ((Gmac *)hw)->GMAC_ST2RPQ[index];
}

static inline void hri_gmac_set_ST2ER_COMPVAL_bf(const void *const hw, uint8_t index, hri_gmac_st2er_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2ER[index] |= GMAC_ST2ER_COMPVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2er_reg_t hri_gmac_get_ST2ER_COMPVAL_bf(const void *const hw, uint8_t index,
                                                                 hri_gmac_st2er_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2ER[index];
	tmp = (tmp & GMAC_ST2ER_COMPVAL(mask)) >> GMAC_ST2ER_COMPVAL_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2ER_COMPVAL_bf(const void *const hw, uint8_t index, hri_gmac_st2er_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GMAC_ST2ER[index];
	tmp &= ~GMAC_ST2ER_COMPVAL_Msk;
	tmp |= GMAC_ST2ER_COMPVAL(data);
	((Gmac *)hw)->GMAC_ST2ER[index] = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2ER_COMPVAL_bf(const void *const hw, uint8_t index, hri_gmac_st2er_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2ER[index] &= ~GMAC_ST2ER_COMPVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2ER_COMPVAL_bf(const void *const hw, uint8_t index, hri_gmac_st2er_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2ER[index] ^= GMAC_ST2ER_COMPVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2er_reg_t hri_gmac_read_ST2ER_COMPVAL_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2ER[index];
	tmp = (tmp & GMAC_ST2ER_COMPVAL_Msk) >> GMAC_ST2ER_COMPVAL_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2ER_reg(const void *const hw, uint8_t index, hri_gmac_st2er_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2ER[index] |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2er_reg_t hri_gmac_get_ST2ER_reg(const void *const hw, uint8_t index,
                                                          hri_gmac_st2er_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GMAC_ST2ER[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_ST2ER_reg(const void *const hw, uint8_t index, hri_gmac_st2er_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2ER[index] = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2ER_reg(const void *const hw, uint8_t index, hri_gmac_st2er_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2ER[index] &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2ER_reg(const void *const hw, uint8_t index, hri_gmac_st2er_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_ST2ER[index] ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2er_reg_t hri_gmac_read_ST2ER_reg(const void *const hw, uint8_t index)
{
	return ((Gmac *)hw)->GMAC_ST2ER[index];
}

static inline void hri_gmac_write_TA_reg(const void *const hw, hri_gmac_ta_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GMAC_TA = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_set_ST2CW0_MASKVAL_bf(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 |= GMAC_ST2CW0_MASKVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmacst2cw_get_ST2CW0_MASKVAL_bf(const void *const     hw,
                                                                        hri_gmac_st2cw0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW0;
	tmp = (tmp & GMAC_ST2CW0_MASKVAL(mask)) >> GMAC_ST2CW0_MASKVAL_Pos;
	return tmp;
}

static inline void hri_gmacst2cw_write_ST2CW0_MASKVAL_bf(const void *const hw, hri_gmac_st2cw0_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW0;
	tmp &= ~GMAC_ST2CW0_MASKVAL_Msk;
	tmp |= GMAC_ST2CW0_MASKVAL(data);
	((GmacSt2cw *)hw)->GMAC_ST2CW0 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_clear_ST2CW0_MASKVAL_bf(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 &= ~GMAC_ST2CW0_MASKVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_toggle_ST2CW0_MASKVAL_bf(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 ^= GMAC_ST2CW0_MASKVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmacst2cw_read_ST2CW0_MASKVAL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW0;
	tmp = (tmp & GMAC_ST2CW0_MASKVAL_Msk) >> GMAC_ST2CW0_MASKVAL_Pos;
	return tmp;
}

static inline void hri_gmacst2cw_set_ST2CW0_COMPVAL_bf(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 |= GMAC_ST2CW0_COMPVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmacst2cw_get_ST2CW0_COMPVAL_bf(const void *const     hw,
                                                                        hri_gmac_st2cw0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW0;
	tmp = (tmp & GMAC_ST2CW0_COMPVAL(mask)) >> GMAC_ST2CW0_COMPVAL_Pos;
	return tmp;
}

static inline void hri_gmacst2cw_write_ST2CW0_COMPVAL_bf(const void *const hw, hri_gmac_st2cw0_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW0;
	tmp &= ~GMAC_ST2CW0_COMPVAL_Msk;
	tmp |= GMAC_ST2CW0_COMPVAL(data);
	((GmacSt2cw *)hw)->GMAC_ST2CW0 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_clear_ST2CW0_COMPVAL_bf(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 &= ~GMAC_ST2CW0_COMPVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_toggle_ST2CW0_COMPVAL_bf(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 ^= GMAC_ST2CW0_COMPVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmacst2cw_read_ST2CW0_COMPVAL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW0;
	tmp = (tmp & GMAC_ST2CW0_COMPVAL_Msk) >> GMAC_ST2CW0_COMPVAL_Pos;
	return tmp;
}

static inline void hri_gmacst2cw_set_ST2CW0_reg(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmacst2cw_get_ST2CW0_reg(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW0;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmacst2cw_write_ST2CW0_reg(const void *const hw, hri_gmac_st2cw0_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_clear_ST2CW0_reg(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_toggle_ST2CW0_reg(const void *const hw, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW0 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmacst2cw_read_ST2CW0_reg(const void *const hw)
{
	return ((GmacSt2cw *)hw)->GMAC_ST2CW0;
}

static inline void hri_gmacst2cw_set_ST2CW1_OFFSVAL_bf(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 |= GMAC_ST2CW1_OFFSVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmacst2cw_get_ST2CW1_OFFSVAL_bf(const void *const     hw,
                                                                        hri_gmac_st2cw1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW1;
	tmp = (tmp & GMAC_ST2CW1_OFFSVAL(mask)) >> GMAC_ST2CW1_OFFSVAL_Pos;
	return tmp;
}

static inline void hri_gmacst2cw_write_ST2CW1_OFFSVAL_bf(const void *const hw, hri_gmac_st2cw1_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW1;
	tmp &= ~GMAC_ST2CW1_OFFSVAL_Msk;
	tmp |= GMAC_ST2CW1_OFFSVAL(data);
	((GmacSt2cw *)hw)->GMAC_ST2CW1 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_clear_ST2CW1_OFFSVAL_bf(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 &= ~GMAC_ST2CW1_OFFSVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_toggle_ST2CW1_OFFSVAL_bf(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 ^= GMAC_ST2CW1_OFFSVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmacst2cw_read_ST2CW1_OFFSVAL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW1;
	tmp = (tmp & GMAC_ST2CW1_OFFSVAL_Msk) >> GMAC_ST2CW1_OFFSVAL_Pos;
	return tmp;
}

static inline void hri_gmacst2cw_set_ST2CW1_OFFSSTRT_bf(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 |= GMAC_ST2CW1_OFFSSTRT(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmacst2cw_get_ST2CW1_OFFSSTRT_bf(const void *const     hw,
                                                                         hri_gmac_st2cw1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW1;
	tmp = (tmp & GMAC_ST2CW1_OFFSSTRT(mask)) >> GMAC_ST2CW1_OFFSSTRT_Pos;
	return tmp;
}

static inline void hri_gmacst2cw_write_ST2CW1_OFFSSTRT_bf(const void *const hw, hri_gmac_st2cw1_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW1;
	tmp &= ~GMAC_ST2CW1_OFFSSTRT_Msk;
	tmp |= GMAC_ST2CW1_OFFSSTRT(data);
	((GmacSt2cw *)hw)->GMAC_ST2CW1 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_clear_ST2CW1_OFFSSTRT_bf(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 &= ~GMAC_ST2CW1_OFFSSTRT(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_toggle_ST2CW1_OFFSSTRT_bf(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 ^= GMAC_ST2CW1_OFFSSTRT(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmacst2cw_read_ST2CW1_OFFSSTRT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW1;
	tmp = (tmp & GMAC_ST2CW1_OFFSSTRT_Msk) >> GMAC_ST2CW1_OFFSSTRT_Pos;
	return tmp;
}

static inline void hri_gmacst2cw_set_ST2CW1_reg(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmacst2cw_get_ST2CW1_reg(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSt2cw *)hw)->GMAC_ST2CW1;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmacst2cw_write_ST2CW1_reg(const void *const hw, hri_gmac_st2cw1_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_clear_ST2CW1_reg(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacst2cw_toggle_ST2CW1_reg(const void *const hw, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSt2cw *)hw)->GMAC_ST2CW1 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmacst2cw_read_ST2CW1_reg(const void *const hw)
{
	return ((GmacSt2cw *)hw)->GMAC_ST2CW1;
}

static inline void hri_gmac_set_ST2CW0_MASKVAL_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 |= GMAC_ST2CW0_MASKVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmac_get_ST2CW0_MASKVAL_bf(const void *const hw, uint8_t submodule_index,
                                                                   hri_gmac_st2cw0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0;
	tmp = (tmp & GMAC_ST2CW0_MASKVAL(mask)) >> GMAC_ST2CW0_MASKVAL_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2CW0_MASKVAL_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_gmac_st2cw0_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0;
	tmp &= ~GMAC_ST2CW0_MASKVAL_Msk;
	tmp |= GMAC_ST2CW0_MASKVAL(data);
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2CW0_MASKVAL_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 &= ~GMAC_ST2CW0_MASKVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2CW0_MASKVAL_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 ^= GMAC_ST2CW0_MASKVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmac_read_ST2CW0_MASKVAL_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0;
	tmp = (tmp & GMAC_ST2CW0_MASKVAL_Msk) >> GMAC_ST2CW0_MASKVAL_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2CW0_COMPVAL_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 |= GMAC_ST2CW0_COMPVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmac_get_ST2CW0_COMPVAL_bf(const void *const hw, uint8_t submodule_index,
                                                                   hri_gmac_st2cw0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0;
	tmp = (tmp & GMAC_ST2CW0_COMPVAL(mask)) >> GMAC_ST2CW0_COMPVAL_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2CW0_COMPVAL_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_gmac_st2cw0_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0;
	tmp &= ~GMAC_ST2CW0_COMPVAL_Msk;
	tmp |= GMAC_ST2CW0_COMPVAL(data);
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2CW0_COMPVAL_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 &= ~GMAC_ST2CW0_COMPVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2CW0_COMPVAL_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 ^= GMAC_ST2CW0_COMPVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmac_read_ST2CW0_COMPVAL_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0;
	tmp = (tmp & GMAC_ST2CW0_COMPVAL_Msk) >> GMAC_ST2CW0_COMPVAL_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2CW0_reg(const void *const hw, uint8_t submodule_index, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmac_get_ST2CW0_reg(const void *const hw, uint8_t submodule_index,
                                                            hri_gmac_st2cw0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_ST2CW0_reg(const void *const hw, uint8_t submodule_index, hri_gmac_st2cw0_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2CW0_reg(const void *const hw, uint8_t submodule_index, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2CW0_reg(const void *const hw, uint8_t submodule_index, hri_gmac_st2cw0_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw0_reg_t hri_gmac_read_ST2CW0_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW0;
}

static inline void hri_gmac_set_ST2CW1_OFFSVAL_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 |= GMAC_ST2CW1_OFFSVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmac_get_ST2CW1_OFFSVAL_bf(const void *const hw, uint8_t submodule_index,
                                                                   hri_gmac_st2cw1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1;
	tmp = (tmp & GMAC_ST2CW1_OFFSVAL(mask)) >> GMAC_ST2CW1_OFFSVAL_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2CW1_OFFSVAL_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_gmac_st2cw1_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1;
	tmp &= ~GMAC_ST2CW1_OFFSVAL_Msk;
	tmp |= GMAC_ST2CW1_OFFSVAL(data);
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2CW1_OFFSVAL_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 &= ~GMAC_ST2CW1_OFFSVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2CW1_OFFSVAL_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 ^= GMAC_ST2CW1_OFFSVAL(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmac_read_ST2CW1_OFFSVAL_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1;
	tmp = (tmp & GMAC_ST2CW1_OFFSVAL_Msk) >> GMAC_ST2CW1_OFFSVAL_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2CW1_OFFSSTRT_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 |= GMAC_ST2CW1_OFFSSTRT(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmac_get_ST2CW1_OFFSSTRT_bf(const void *const hw, uint8_t submodule_index,
                                                                    hri_gmac_st2cw1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1;
	tmp = (tmp & GMAC_ST2CW1_OFFSSTRT(mask)) >> GMAC_ST2CW1_OFFSSTRT_Pos;
	return tmp;
}

static inline void hri_gmac_write_ST2CW1_OFFSSTRT_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_gmac_st2cw1_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1;
	tmp &= ~GMAC_ST2CW1_OFFSSTRT_Msk;
	tmp |= GMAC_ST2CW1_OFFSSTRT(data);
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2CW1_OFFSSTRT_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 &= ~GMAC_ST2CW1_OFFSSTRT(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2CW1_OFFSSTRT_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 ^= GMAC_ST2CW1_OFFSSTRT(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmac_read_ST2CW1_OFFSSTRT_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1;
	tmp = (tmp & GMAC_ST2CW1_OFFSSTRT_Msk) >> GMAC_ST2CW1_OFFSSTRT_Pos;
	return tmp;
}

static inline void hri_gmac_set_ST2CW1_reg(const void *const hw, uint8_t submodule_index, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmac_get_ST2CW1_reg(const void *const hw, uint8_t submodule_index,
                                                            hri_gmac_st2cw1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_ST2CW1_reg(const void *const hw, uint8_t submodule_index, hri_gmac_st2cw1_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_ST2CW1_reg(const void *const hw, uint8_t submodule_index, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_ST2CW1_reg(const void *const hw, uint8_t submodule_index, hri_gmac_st2cw1_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1 ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_st2cw1_reg_t hri_gmac_read_ST2CW1_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Gmac *)hw)->GmacSt2cw[submodule_index].GMAC_ST2CW1;
}

static inline void hri_gmacsa_set_SAB_ADDR_bf(const void *const hw, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAB |= GMAC_SAB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmacsa_get_SAB_ADDR_bf(const void *const hw, hri_gmac_sab_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSa *)hw)->GMAC_SAB;
	tmp = (tmp & GMAC_SAB_ADDR(mask)) >> GMAC_SAB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmacsa_write_SAB_ADDR_bf(const void *const hw, hri_gmac_sab_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((GmacSa *)hw)->GMAC_SAB;
	tmp &= ~GMAC_SAB_ADDR_Msk;
	tmp |= GMAC_SAB_ADDR(data);
	((GmacSa *)hw)->GMAC_SAB = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_clear_SAB_ADDR_bf(const void *const hw, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAB &= ~GMAC_SAB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_toggle_SAB_ADDR_bf(const void *const hw, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAB ^= GMAC_SAB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmacsa_read_SAB_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((GmacSa *)hw)->GMAC_SAB;
	tmp = (tmp & GMAC_SAB_ADDR_Msk) >> GMAC_SAB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmacsa_set_SAB_reg(const void *const hw, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAB |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmacsa_get_SAB_reg(const void *const hw, hri_gmac_sab_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSa *)hw)->GMAC_SAB;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmacsa_write_SAB_reg(const void *const hw, hri_gmac_sab_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAB = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_clear_SAB_reg(const void *const hw, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAB &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_toggle_SAB_reg(const void *const hw, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAB ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmacsa_read_SAB_reg(const void *const hw)
{
	return ((GmacSa *)hw)->GMAC_SAB;
}

static inline void hri_gmacsa_set_SAT_ADDR_bf(const void *const hw, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAT |= GMAC_SAT_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmacsa_get_SAT_ADDR_bf(const void *const hw, hri_gmac_sat_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSa *)hw)->GMAC_SAT;
	tmp = (tmp & GMAC_SAT_ADDR(mask)) >> GMAC_SAT_ADDR_Pos;
	return tmp;
}

static inline void hri_gmacsa_write_SAT_ADDR_bf(const void *const hw, hri_gmac_sat_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((GmacSa *)hw)->GMAC_SAT;
	tmp &= ~GMAC_SAT_ADDR_Msk;
	tmp |= GMAC_SAT_ADDR(data);
	((GmacSa *)hw)->GMAC_SAT = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_clear_SAT_ADDR_bf(const void *const hw, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAT &= ~GMAC_SAT_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_toggle_SAT_ADDR_bf(const void *const hw, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAT ^= GMAC_SAT_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmacsa_read_SAT_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((GmacSa *)hw)->GMAC_SAT;
	tmp = (tmp & GMAC_SAT_ADDR_Msk) >> GMAC_SAT_ADDR_Pos;
	return tmp;
}

static inline void hri_gmacsa_set_SAT_reg(const void *const hw, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAT |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmacsa_get_SAT_reg(const void *const hw, hri_gmac_sat_reg_t mask)
{
	uint32_t tmp;
	tmp = ((GmacSa *)hw)->GMAC_SAT;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmacsa_write_SAT_reg(const void *const hw, hri_gmac_sat_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAT = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_clear_SAT_reg(const void *const hw, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAT &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmacsa_toggle_SAT_reg(const void *const hw, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((GmacSa *)hw)->GMAC_SAT ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmacsa_read_SAT_reg(const void *const hw)
{
	return ((GmacSa *)hw)->GMAC_SAT;
}

static inline void hri_gmac_set_SAB_ADDR_bf(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB |= GMAC_SAB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmac_get_SAB_ADDR_bf(const void *const hw, uint8_t submodule_index,
                                                          hri_gmac_sab_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB;
	tmp = (tmp & GMAC_SAB_ADDR(mask)) >> GMAC_SAB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_write_SAB_ADDR_bf(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB;
	tmp &= ~GMAC_SAB_ADDR_Msk;
	tmp |= GMAC_SAB_ADDR(data);
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAB_ADDR_bf(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB &= ~GMAC_SAB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAB_ADDR_bf(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB ^= GMAC_SAB_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmac_read_SAB_ADDR_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB;
	tmp = (tmp & GMAC_SAB_ADDR_Msk) >> GMAC_SAB_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_set_SAB_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmac_get_SAB_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_gmac_sab_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SAB_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAB_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAB_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sab_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sab_reg_t hri_gmac_read_SAB_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAB;
}

static inline void hri_gmac_set_SAT_ADDR_bf(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT |= GMAC_SAT_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmac_get_SAT_ADDR_bf(const void *const hw, uint8_t submodule_index,
                                                          hri_gmac_sat_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT;
	tmp = (tmp & GMAC_SAT_ADDR(mask)) >> GMAC_SAT_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_write_SAT_ADDR_bf(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t data)
{
	uint32_t tmp;
	GMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT;
	tmp &= ~GMAC_SAT_ADDR_Msk;
	tmp |= GMAC_SAT_ADDR(data);
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT = tmp;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAT_ADDR_bf(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT &= ~GMAC_SAT_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAT_ADDR_bf(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT ^= GMAC_SAT_ADDR(mask);
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmac_read_SAT_ADDR_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT;
	tmp = (tmp & GMAC_SAT_ADDR_Msk) >> GMAC_SAT_ADDR_Pos;
	return tmp;
}

static inline void hri_gmac_set_SAT_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT |= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmac_get_SAT_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_gmac_sat_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT;
	tmp &= mask;
	return tmp;
}

static inline void hri_gmac_write_SAT_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t data)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT = data;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_clear_SAT_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT &= ~mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gmac_toggle_SAT_reg(const void *const hw, uint8_t submodule_index, hri_gmac_sat_reg_t mask)
{
	GMAC_CRITICAL_SECTION_ENTER();
	((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT ^= mask;
	GMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_gmac_sat_reg_t hri_gmac_read_SAT_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Gmac *)hw)->GmacSa[submodule_index].GMAC_SAT;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_GMAC_E70B_H_INCLUDED */
#endif /* _SAME70_GMAC_COMPONENT_ */
