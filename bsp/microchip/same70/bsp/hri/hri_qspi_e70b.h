/**
 * \file
 *
 * \brief SAM QSPI
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
 */

#ifdef _SAME70_QSPI_COMPONENT_
#ifndef _HRI_QSPI_E70B_H_INCLUDED_
#define _HRI_QSPI_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_QSPI_CRITICAL_SECTIONS)
#define QSPI_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define QSPI_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define QSPI_CRITICAL_SECTION_ENTER()
#define QSPI_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_qspi_cr_reg_t;
typedef uint32_t hri_qspi_iar_reg_t;
typedef uint32_t hri_qspi_icr_reg_t;
typedef uint32_t hri_qspi_ifr_reg_t;
typedef uint32_t hri_qspi_imr_reg_t;
typedef uint32_t hri_qspi_mr_reg_t;
typedef uint32_t hri_qspi_rdr_reg_t;
typedef uint32_t hri_qspi_scr_reg_t;
typedef uint32_t hri_qspi_skr_reg_t;
typedef uint32_t hri_qspi_smr_reg_t;
typedef uint32_t hri_qspi_sr_reg_t;
typedef uint32_t hri_qspi_tdr_reg_t;
typedef uint32_t hri_qspi_wpmr_reg_t;
typedef uint32_t hri_qspi_wpsr_reg_t;

static inline void hri_qspi_set_IMR_RDRF_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IER = QSPI_IMR_RDRF;
}

static inline bool hri_qspi_get_IMR_RDRF_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_IMR & QSPI_IMR_RDRF) >> QSPI_IMR_RDRF_Pos;
}

static inline void hri_qspi_write_IMR_RDRF_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Qspi *)hw)->QSPI_IDR = QSPI_IMR_RDRF;
	} else {
		((Qspi *)hw)->QSPI_IER = QSPI_IMR_RDRF;
	}
}

static inline void hri_qspi_clear_IMR_RDRF_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IDR = QSPI_IMR_RDRF;
}

static inline void hri_qspi_set_IMR_TDRE_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IER = QSPI_IMR_TDRE;
}

static inline bool hri_qspi_get_IMR_TDRE_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_IMR & QSPI_IMR_TDRE) >> QSPI_IMR_TDRE_Pos;
}

static inline void hri_qspi_write_IMR_TDRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Qspi *)hw)->QSPI_IDR = QSPI_IMR_TDRE;
	} else {
		((Qspi *)hw)->QSPI_IER = QSPI_IMR_TDRE;
	}
}

static inline void hri_qspi_clear_IMR_TDRE_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IDR = QSPI_IMR_TDRE;
}

static inline void hri_qspi_set_IMR_TXEMPTY_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IER = QSPI_IMR_TXEMPTY;
}

static inline bool hri_qspi_get_IMR_TXEMPTY_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_IMR & QSPI_IMR_TXEMPTY) >> QSPI_IMR_TXEMPTY_Pos;
}

static inline void hri_qspi_write_IMR_TXEMPTY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Qspi *)hw)->QSPI_IDR = QSPI_IMR_TXEMPTY;
	} else {
		((Qspi *)hw)->QSPI_IER = QSPI_IMR_TXEMPTY;
	}
}

static inline void hri_qspi_clear_IMR_TXEMPTY_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IDR = QSPI_IMR_TXEMPTY;
}

static inline void hri_qspi_set_IMR_OVRES_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IER = QSPI_IMR_OVRES;
}

static inline bool hri_qspi_get_IMR_OVRES_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_IMR & QSPI_IMR_OVRES) >> QSPI_IMR_OVRES_Pos;
}

static inline void hri_qspi_write_IMR_OVRES_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Qspi *)hw)->QSPI_IDR = QSPI_IMR_OVRES;
	} else {
		((Qspi *)hw)->QSPI_IER = QSPI_IMR_OVRES;
	}
}

static inline void hri_qspi_clear_IMR_OVRES_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IDR = QSPI_IMR_OVRES;
}

static inline void hri_qspi_set_IMR_CSR_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IER = QSPI_IMR_CSR;
}

static inline bool hri_qspi_get_IMR_CSR_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_IMR & QSPI_IMR_CSR) >> QSPI_IMR_CSR_Pos;
}

static inline void hri_qspi_write_IMR_CSR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Qspi *)hw)->QSPI_IDR = QSPI_IMR_CSR;
	} else {
		((Qspi *)hw)->QSPI_IER = QSPI_IMR_CSR;
	}
}

static inline void hri_qspi_clear_IMR_CSR_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IDR = QSPI_IMR_CSR;
}

static inline void hri_qspi_set_IMR_CSS_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IER = QSPI_IMR_CSS;
}

static inline bool hri_qspi_get_IMR_CSS_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_IMR & QSPI_IMR_CSS) >> QSPI_IMR_CSS_Pos;
}

static inline void hri_qspi_write_IMR_CSS_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Qspi *)hw)->QSPI_IDR = QSPI_IMR_CSS;
	} else {
		((Qspi *)hw)->QSPI_IER = QSPI_IMR_CSS;
	}
}

static inline void hri_qspi_clear_IMR_CSS_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IDR = QSPI_IMR_CSS;
}

static inline void hri_qspi_set_IMR_INSTRE_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IER = QSPI_IMR_INSTRE;
}

static inline bool hri_qspi_get_IMR_INSTRE_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_IMR & QSPI_IMR_INSTRE) >> QSPI_IMR_INSTRE_Pos;
}

static inline void hri_qspi_write_IMR_INSTRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Qspi *)hw)->QSPI_IDR = QSPI_IMR_INSTRE;
	} else {
		((Qspi *)hw)->QSPI_IER = QSPI_IMR_INSTRE;
	}
}

static inline void hri_qspi_clear_IMR_INSTRE_bit(const void *const hw)
{
	((Qspi *)hw)->QSPI_IDR = QSPI_IMR_INSTRE;
}

static inline void hri_qspi_set_IMR_reg(const void *const hw, hri_qspi_imr_reg_t mask)
{
	((Qspi *)hw)->QSPI_IER = mask;
}

static inline hri_qspi_imr_reg_t hri_qspi_get_IMR_reg(const void *const hw, hri_qspi_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_qspi_imr_reg_t hri_qspi_read_IMR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_IMR;
}

static inline void hri_qspi_write_IMR_reg(const void *const hw, hri_qspi_imr_reg_t data)
{
	((Qspi *)hw)->QSPI_IER = data;
	((Qspi *)hw)->QSPI_IDR = ~data;
}

static inline void hri_qspi_clear_IMR_reg(const void *const hw, hri_qspi_imr_reg_t mask)
{
	((Qspi *)hw)->QSPI_IDR = mask;
}

static inline hri_qspi_rdr_reg_t hri_qspi_get_RDR_RD_bf(const void *const hw, hri_qspi_rdr_reg_t mask)
{
	return (((Qspi *)hw)->QSPI_RDR & QSPI_RDR_RD(mask)) >> QSPI_RDR_RD_Pos;
}

static inline hri_qspi_rdr_reg_t hri_qspi_read_RDR_RD_bf(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_RDR & QSPI_RDR_RD_Msk) >> QSPI_RDR_RD_Pos;
}

static inline hri_qspi_rdr_reg_t hri_qspi_get_RDR_reg(const void *const hw, hri_qspi_rdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_RDR;
	tmp &= mask;
	return tmp;
}

static inline hri_qspi_rdr_reg_t hri_qspi_read_RDR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_RDR;
}

static inline bool hri_qspi_get_SR_RDRF_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_SR & QSPI_SR_RDRF) > 0;
}

static inline bool hri_qspi_get_SR_TDRE_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_SR & QSPI_SR_TDRE) > 0;
}

static inline bool hri_qspi_get_SR_TXEMPTY_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_SR & QSPI_SR_TXEMPTY) > 0;
}

static inline bool hri_qspi_get_SR_OVRES_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_SR & QSPI_SR_OVRES) > 0;
}

static inline bool hri_qspi_get_SR_CSR_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_SR & QSPI_SR_CSR) > 0;
}

static inline bool hri_qspi_get_SR_CSS_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_SR & QSPI_SR_CSS) > 0;
}

static inline bool hri_qspi_get_SR_INSTRE_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_SR & QSPI_SR_INSTRE) > 0;
}

static inline bool hri_qspi_get_SR_QSPIENS_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_SR & QSPI_SR_QSPIENS) > 0;
}

static inline hri_qspi_sr_reg_t hri_qspi_get_SR_reg(const void *const hw, hri_qspi_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_qspi_sr_reg_t hri_qspi_read_SR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_SR;
}

static inline bool hri_qspi_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_WPSR & QSPI_WPSR_WPVS) > 0;
}

static inline hri_qspi_wpsr_reg_t hri_qspi_get_WPSR_WPVSRC_bf(const void *const hw, hri_qspi_wpsr_reg_t mask)
{
	return (((Qspi *)hw)->QSPI_WPSR & QSPI_WPSR_WPVSRC(mask)) >> QSPI_WPSR_WPVSRC_Pos;
}

static inline hri_qspi_wpsr_reg_t hri_qspi_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Qspi *)hw)->QSPI_WPSR & QSPI_WPSR_WPVSRC_Msk) >> QSPI_WPSR_WPVSRC_Pos;
}

static inline hri_qspi_wpsr_reg_t hri_qspi_get_WPSR_reg(const void *const hw, hri_qspi_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_qspi_wpsr_reg_t hri_qspi_read_WPSR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_WPSR;
}

static inline void hri_qspi_set_MR_SMM_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR |= QSPI_MR_SMM;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_MR_SMM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_SMM) >> QSPI_MR_SMM_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_MR_SMM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp &= ~QSPI_MR_SMM;
	tmp |= value << QSPI_MR_SMM_Pos;
	((Qspi *)hw)->QSPI_MR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_MR_SMM_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR &= ~QSPI_MR_SMM;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_MR_SMM_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR ^= QSPI_MR_SMM;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_MR_LLB_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR |= QSPI_MR_LLB;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_MR_LLB_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_LLB) >> QSPI_MR_LLB_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_MR_LLB_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp &= ~QSPI_MR_LLB;
	tmp |= value << QSPI_MR_LLB_Pos;
	((Qspi *)hw)->QSPI_MR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_MR_LLB_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR &= ~QSPI_MR_LLB;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_MR_LLB_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR ^= QSPI_MR_LLB;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_MR_WDRBT_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR |= QSPI_MR_WDRBT;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_MR_WDRBT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_WDRBT) >> QSPI_MR_WDRBT_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_MR_WDRBT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp &= ~QSPI_MR_WDRBT;
	tmp |= value << QSPI_MR_WDRBT_Pos;
	((Qspi *)hw)->QSPI_MR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_MR_WDRBT_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR &= ~QSPI_MR_WDRBT;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_MR_WDRBT_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR ^= QSPI_MR_WDRBT;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_MR_CSMODE_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR |= QSPI_MR_CSMODE(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_get_MR_CSMODE_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_CSMODE(mask)) >> QSPI_MR_CSMODE_Pos;
	return tmp;
}

static inline void hri_qspi_write_MR_CSMODE_bf(const void *const hw, hri_qspi_mr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp &= ~QSPI_MR_CSMODE_Msk;
	tmp |= QSPI_MR_CSMODE(data);
	((Qspi *)hw)->QSPI_MR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_MR_CSMODE_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR &= ~QSPI_MR_CSMODE(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_MR_CSMODE_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR ^= QSPI_MR_CSMODE(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_read_MR_CSMODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_CSMODE_Msk) >> QSPI_MR_CSMODE_Pos;
	return tmp;
}

static inline void hri_qspi_set_MR_NBBITS_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR |= QSPI_MR_NBBITS(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_get_MR_NBBITS_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_NBBITS(mask)) >> QSPI_MR_NBBITS_Pos;
	return tmp;
}

static inline void hri_qspi_write_MR_NBBITS_bf(const void *const hw, hri_qspi_mr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp &= ~QSPI_MR_NBBITS_Msk;
	tmp |= QSPI_MR_NBBITS(data);
	((Qspi *)hw)->QSPI_MR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_MR_NBBITS_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR &= ~QSPI_MR_NBBITS(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_MR_NBBITS_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR ^= QSPI_MR_NBBITS(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_read_MR_NBBITS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_NBBITS_Msk) >> QSPI_MR_NBBITS_Pos;
	return tmp;
}

static inline void hri_qspi_set_MR_DLYBCT_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR |= QSPI_MR_DLYBCT(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_get_MR_DLYBCT_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_DLYBCT(mask)) >> QSPI_MR_DLYBCT_Pos;
	return tmp;
}

static inline void hri_qspi_write_MR_DLYBCT_bf(const void *const hw, hri_qspi_mr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp &= ~QSPI_MR_DLYBCT_Msk;
	tmp |= QSPI_MR_DLYBCT(data);
	((Qspi *)hw)->QSPI_MR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_MR_DLYBCT_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR &= ~QSPI_MR_DLYBCT(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_MR_DLYBCT_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR ^= QSPI_MR_DLYBCT(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_read_MR_DLYBCT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_DLYBCT_Msk) >> QSPI_MR_DLYBCT_Pos;
	return tmp;
}

static inline void hri_qspi_set_MR_DLYCS_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR |= QSPI_MR_DLYCS(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_get_MR_DLYCS_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_DLYCS(mask)) >> QSPI_MR_DLYCS_Pos;
	return tmp;
}

static inline void hri_qspi_write_MR_DLYCS_bf(const void *const hw, hri_qspi_mr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp &= ~QSPI_MR_DLYCS_Msk;
	tmp |= QSPI_MR_DLYCS(data);
	((Qspi *)hw)->QSPI_MR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_MR_DLYCS_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR &= ~QSPI_MR_DLYCS(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_MR_DLYCS_bf(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR ^= QSPI_MR_DLYCS(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_read_MR_DLYCS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp = (tmp & QSPI_MR_DLYCS_Msk) >> QSPI_MR_DLYCS_Pos;
	return tmp;
}

static inline void hri_qspi_set_MR_reg(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR |= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_get_MR_reg(const void *const hw, hri_qspi_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_qspi_write_MR_reg(const void *const hw, hri_qspi_mr_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_MR_reg(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR &= ~mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_MR_reg(const void *const hw, hri_qspi_mr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_MR ^= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_mr_reg_t hri_qspi_read_MR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_MR;
}

static inline void hri_qspi_set_SCR_CPOL_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR |= QSPI_SCR_CPOL;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_SCR_CPOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp = (tmp & QSPI_SCR_CPOL) >> QSPI_SCR_CPOL_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_SCR_CPOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp &= ~QSPI_SCR_CPOL;
	tmp |= value << QSPI_SCR_CPOL_Pos;
	((Qspi *)hw)->QSPI_SCR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_SCR_CPOL_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR &= ~QSPI_SCR_CPOL;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_SCR_CPOL_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR ^= QSPI_SCR_CPOL;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_SCR_CPHA_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR |= QSPI_SCR_CPHA;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_SCR_CPHA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp = (tmp & QSPI_SCR_CPHA) >> QSPI_SCR_CPHA_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_SCR_CPHA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp &= ~QSPI_SCR_CPHA;
	tmp |= value << QSPI_SCR_CPHA_Pos;
	((Qspi *)hw)->QSPI_SCR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_SCR_CPHA_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR &= ~QSPI_SCR_CPHA;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_SCR_CPHA_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR ^= QSPI_SCR_CPHA;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_SCR_SCBR_bf(const void *const hw, hri_qspi_scr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR |= QSPI_SCR_SCBR(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_scr_reg_t hri_qspi_get_SCR_SCBR_bf(const void *const hw, hri_qspi_scr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp = (tmp & QSPI_SCR_SCBR(mask)) >> QSPI_SCR_SCBR_Pos;
	return tmp;
}

static inline void hri_qspi_write_SCR_SCBR_bf(const void *const hw, hri_qspi_scr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp &= ~QSPI_SCR_SCBR_Msk;
	tmp |= QSPI_SCR_SCBR(data);
	((Qspi *)hw)->QSPI_SCR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_SCR_SCBR_bf(const void *const hw, hri_qspi_scr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR &= ~QSPI_SCR_SCBR(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_SCR_SCBR_bf(const void *const hw, hri_qspi_scr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR ^= QSPI_SCR_SCBR(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_scr_reg_t hri_qspi_read_SCR_SCBR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp = (tmp & QSPI_SCR_SCBR_Msk) >> QSPI_SCR_SCBR_Pos;
	return tmp;
}

static inline void hri_qspi_set_SCR_DLYBS_bf(const void *const hw, hri_qspi_scr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR |= QSPI_SCR_DLYBS(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_scr_reg_t hri_qspi_get_SCR_DLYBS_bf(const void *const hw, hri_qspi_scr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp = (tmp & QSPI_SCR_DLYBS(mask)) >> QSPI_SCR_DLYBS_Pos;
	return tmp;
}

static inline void hri_qspi_write_SCR_DLYBS_bf(const void *const hw, hri_qspi_scr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp &= ~QSPI_SCR_DLYBS_Msk;
	tmp |= QSPI_SCR_DLYBS(data);
	((Qspi *)hw)->QSPI_SCR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_SCR_DLYBS_bf(const void *const hw, hri_qspi_scr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR &= ~QSPI_SCR_DLYBS(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_SCR_DLYBS_bf(const void *const hw, hri_qspi_scr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR ^= QSPI_SCR_DLYBS(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_scr_reg_t hri_qspi_read_SCR_DLYBS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp = (tmp & QSPI_SCR_DLYBS_Msk) >> QSPI_SCR_DLYBS_Pos;
	return tmp;
}

static inline void hri_qspi_set_SCR_reg(const void *const hw, hri_qspi_scr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR |= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_scr_reg_t hri_qspi_get_SCR_reg(const void *const hw, hri_qspi_scr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_qspi_write_SCR_reg(const void *const hw, hri_qspi_scr_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_SCR_reg(const void *const hw, hri_qspi_scr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR &= ~mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_SCR_reg(const void *const hw, hri_qspi_scr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SCR ^= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_scr_reg_t hri_qspi_read_SCR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_SCR;
}

static inline void hri_qspi_set_IAR_ADDR_bf(const void *const hw, hri_qspi_iar_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IAR |= QSPI_IAR_ADDR(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_iar_reg_t hri_qspi_get_IAR_ADDR_bf(const void *const hw, hri_qspi_iar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IAR;
	tmp = (tmp & QSPI_IAR_ADDR(mask)) >> QSPI_IAR_ADDR_Pos;
	return tmp;
}

static inline void hri_qspi_write_IAR_ADDR_bf(const void *const hw, hri_qspi_iar_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IAR;
	tmp &= ~QSPI_IAR_ADDR_Msk;
	tmp |= QSPI_IAR_ADDR(data);
	((Qspi *)hw)->QSPI_IAR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IAR_ADDR_bf(const void *const hw, hri_qspi_iar_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IAR &= ~QSPI_IAR_ADDR(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IAR_ADDR_bf(const void *const hw, hri_qspi_iar_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IAR ^= QSPI_IAR_ADDR(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_iar_reg_t hri_qspi_read_IAR_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IAR;
	tmp = (tmp & QSPI_IAR_ADDR_Msk) >> QSPI_IAR_ADDR_Pos;
	return tmp;
}

static inline void hri_qspi_set_IAR_reg(const void *const hw, hri_qspi_iar_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IAR |= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_iar_reg_t hri_qspi_get_IAR_reg(const void *const hw, hri_qspi_iar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IAR;
	tmp &= mask;
	return tmp;
}

static inline void hri_qspi_write_IAR_reg(const void *const hw, hri_qspi_iar_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IAR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IAR_reg(const void *const hw, hri_qspi_iar_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IAR &= ~mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IAR_reg(const void *const hw, hri_qspi_iar_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IAR ^= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_iar_reg_t hri_qspi_read_IAR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_IAR;
}

static inline void hri_qspi_set_ICR_INST_bf(const void *const hw, hri_qspi_icr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR |= QSPI_ICR_INST(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_icr_reg_t hri_qspi_get_ICR_INST_bf(const void *const hw, hri_qspi_icr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_ICR;
	tmp = (tmp & QSPI_ICR_INST(mask)) >> QSPI_ICR_INST_Pos;
	return tmp;
}

static inline void hri_qspi_write_ICR_INST_bf(const void *const hw, hri_qspi_icr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_ICR;
	tmp &= ~QSPI_ICR_INST_Msk;
	tmp |= QSPI_ICR_INST(data);
	((Qspi *)hw)->QSPI_ICR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_ICR_INST_bf(const void *const hw, hri_qspi_icr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR &= ~QSPI_ICR_INST(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_ICR_INST_bf(const void *const hw, hri_qspi_icr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR ^= QSPI_ICR_INST(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_icr_reg_t hri_qspi_read_ICR_INST_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_ICR;
	tmp = (tmp & QSPI_ICR_INST_Msk) >> QSPI_ICR_INST_Pos;
	return tmp;
}

static inline void hri_qspi_set_ICR_OPT_bf(const void *const hw, hri_qspi_icr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR |= QSPI_ICR_OPT(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_icr_reg_t hri_qspi_get_ICR_OPT_bf(const void *const hw, hri_qspi_icr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_ICR;
	tmp = (tmp & QSPI_ICR_OPT(mask)) >> QSPI_ICR_OPT_Pos;
	return tmp;
}

static inline void hri_qspi_write_ICR_OPT_bf(const void *const hw, hri_qspi_icr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_ICR;
	tmp &= ~QSPI_ICR_OPT_Msk;
	tmp |= QSPI_ICR_OPT(data);
	((Qspi *)hw)->QSPI_ICR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_ICR_OPT_bf(const void *const hw, hri_qspi_icr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR &= ~QSPI_ICR_OPT(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_ICR_OPT_bf(const void *const hw, hri_qspi_icr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR ^= QSPI_ICR_OPT(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_icr_reg_t hri_qspi_read_ICR_OPT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_ICR;
	tmp = (tmp & QSPI_ICR_OPT_Msk) >> QSPI_ICR_OPT_Pos;
	return tmp;
}

static inline void hri_qspi_set_ICR_reg(const void *const hw, hri_qspi_icr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR |= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_icr_reg_t hri_qspi_get_ICR_reg(const void *const hw, hri_qspi_icr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_ICR;
	tmp &= mask;
	return tmp;
}

static inline void hri_qspi_write_ICR_reg(const void *const hw, hri_qspi_icr_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_ICR_reg(const void *const hw, hri_qspi_icr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR &= ~mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_ICR_reg(const void *const hw, hri_qspi_icr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_ICR ^= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_icr_reg_t hri_qspi_read_ICR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_ICR;
}

static inline void hri_qspi_set_IFR_INSTEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_INSTEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_IFR_INSTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_INSTEN) >> QSPI_IFR_INSTEN_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_IFR_INSTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_INSTEN;
	tmp |= value << QSPI_IFR_INSTEN_Pos;
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_INSTEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_INSTEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_INSTEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_INSTEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_IFR_ADDREN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_ADDREN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_IFR_ADDREN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_ADDREN) >> QSPI_IFR_ADDREN_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_IFR_ADDREN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_ADDREN;
	tmp |= value << QSPI_IFR_ADDREN_Pos;
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_ADDREN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_ADDREN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_ADDREN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_ADDREN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_IFR_OPTEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_OPTEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_IFR_OPTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_OPTEN) >> QSPI_IFR_OPTEN_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_IFR_OPTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_OPTEN;
	tmp |= value << QSPI_IFR_OPTEN_Pos;
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_OPTEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_OPTEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_OPTEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_OPTEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_IFR_DATAEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_DATAEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_IFR_DATAEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_DATAEN) >> QSPI_IFR_DATAEN_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_IFR_DATAEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_DATAEN;
	tmp |= value << QSPI_IFR_DATAEN_Pos;
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_DATAEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_DATAEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_DATAEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_DATAEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_IFR_ADDRL_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_ADDRL;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_IFR_ADDRL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_ADDRL) >> QSPI_IFR_ADDRL_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_IFR_ADDRL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_ADDRL;
	tmp |= value << QSPI_IFR_ADDRL_Pos;
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_ADDRL_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_ADDRL;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_ADDRL_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_ADDRL;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_IFR_CRM_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_CRM;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_IFR_CRM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_CRM) >> QSPI_IFR_CRM_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_IFR_CRM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_CRM;
	tmp |= value << QSPI_IFR_CRM_Pos;
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_CRM_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_CRM;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_CRM_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_CRM;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_IFR_WIDTH_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_WIDTH(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_get_IFR_WIDTH_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_WIDTH(mask)) >> QSPI_IFR_WIDTH_Pos;
	return tmp;
}

static inline void hri_qspi_write_IFR_WIDTH_bf(const void *const hw, hri_qspi_ifr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_WIDTH_Msk;
	tmp |= QSPI_IFR_WIDTH(data);
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_WIDTH_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_WIDTH(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_WIDTH_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_WIDTH(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_read_IFR_WIDTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_WIDTH_Msk) >> QSPI_IFR_WIDTH_Pos;
	return tmp;
}

static inline void hri_qspi_set_IFR_OPTL_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_OPTL(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_get_IFR_OPTL_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_OPTL(mask)) >> QSPI_IFR_OPTL_Pos;
	return tmp;
}

static inline void hri_qspi_write_IFR_OPTL_bf(const void *const hw, hri_qspi_ifr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_OPTL_Msk;
	tmp |= QSPI_IFR_OPTL(data);
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_OPTL_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_OPTL(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_OPTL_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_OPTL(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_read_IFR_OPTL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_OPTL_Msk) >> QSPI_IFR_OPTL_Pos;
	return tmp;
}

static inline void hri_qspi_set_IFR_TFRTYP_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_TFRTYP(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_get_IFR_TFRTYP_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_TFRTYP(mask)) >> QSPI_IFR_TFRTYP_Pos;
	return tmp;
}

static inline void hri_qspi_write_IFR_TFRTYP_bf(const void *const hw, hri_qspi_ifr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_TFRTYP_Msk;
	tmp |= QSPI_IFR_TFRTYP(data);
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_TFRTYP_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_TFRTYP(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_TFRTYP_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_TFRTYP(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_read_IFR_TFRTYP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_TFRTYP_Msk) >> QSPI_IFR_TFRTYP_Pos;
	return tmp;
}

static inline void hri_qspi_set_IFR_NBDUM_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= QSPI_IFR_NBDUM(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_get_IFR_NBDUM_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_NBDUM(mask)) >> QSPI_IFR_NBDUM_Pos;
	return tmp;
}

static inline void hri_qspi_write_IFR_NBDUM_bf(const void *const hw, hri_qspi_ifr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= ~QSPI_IFR_NBDUM_Msk;
	tmp |= QSPI_IFR_NBDUM(data);
	((Qspi *)hw)->QSPI_IFR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_NBDUM_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~QSPI_IFR_NBDUM(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_NBDUM_bf(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= QSPI_IFR_NBDUM(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_read_IFR_NBDUM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp = (tmp & QSPI_IFR_NBDUM_Msk) >> QSPI_IFR_NBDUM_Pos;
	return tmp;
}

static inline void hri_qspi_set_IFR_reg(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR |= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_get_IFR_reg(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_IFR;
	tmp &= mask;
	return tmp;
}

static inline void hri_qspi_write_IFR_reg(const void *const hw, hri_qspi_ifr_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_IFR_reg(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR &= ~mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_IFR_reg(const void *const hw, hri_qspi_ifr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_IFR ^= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_ifr_reg_t hri_qspi_read_IFR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_IFR;
}

static inline void hri_qspi_set_SMR_SCREN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR |= QSPI_SMR_SCREN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_SMR_SCREN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SMR;
	tmp = (tmp & QSPI_SMR_SCREN) >> QSPI_SMR_SCREN_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_SMR_SCREN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_SMR;
	tmp &= ~QSPI_SMR_SCREN;
	tmp |= value << QSPI_SMR_SCREN_Pos;
	((Qspi *)hw)->QSPI_SMR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_SMR_SCREN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR &= ~QSPI_SMR_SCREN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_SMR_SCREN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR ^= QSPI_SMR_SCREN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_SMR_RVDIS_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR |= QSPI_SMR_RVDIS;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_SMR_RVDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SMR;
	tmp = (tmp & QSPI_SMR_RVDIS) >> QSPI_SMR_RVDIS_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_SMR_RVDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_SMR;
	tmp &= ~QSPI_SMR_RVDIS;
	tmp |= value << QSPI_SMR_RVDIS_Pos;
	((Qspi *)hw)->QSPI_SMR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_SMR_RVDIS_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR &= ~QSPI_SMR_RVDIS;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_SMR_RVDIS_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR ^= QSPI_SMR_RVDIS;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_SMR_reg(const void *const hw, hri_qspi_smr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR |= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_smr_reg_t hri_qspi_get_SMR_reg(const void *const hw, hri_qspi_smr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_SMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_qspi_write_SMR_reg(const void *const hw, hri_qspi_smr_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_SMR_reg(const void *const hw, hri_qspi_smr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR &= ~mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_SMR_reg(const void *const hw, hri_qspi_smr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SMR ^= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_smr_reg_t hri_qspi_read_SMR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_SMR;
}

static inline void hri_qspi_set_WPMR_WPEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR |= QSPI_WPMR_WPEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_qspi_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_WPMR;
	tmp = (tmp & QSPI_WPMR_WPEN) >> QSPI_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_qspi_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_WPMR;
	tmp &= ~QSPI_WPMR_WPEN;
	tmp |= value << QSPI_WPMR_WPEN_Pos;
	((Qspi *)hw)->QSPI_WPMR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_WPMR_WPEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR &= ~QSPI_WPMR_WPEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_WPMR_WPEN_bit(const void *const hw)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR ^= QSPI_WPMR_WPEN;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_set_WPMR_WPKEY_bf(const void *const hw, hri_qspi_wpmr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR |= QSPI_WPMR_WPKEY(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_wpmr_reg_t hri_qspi_get_WPMR_WPKEY_bf(const void *const hw, hri_qspi_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_WPMR;
	tmp = (tmp & QSPI_WPMR_WPKEY(mask)) >> QSPI_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_qspi_write_WPMR_WPKEY_bf(const void *const hw, hri_qspi_wpmr_reg_t data)
{
	uint32_t tmp;
	QSPI_CRITICAL_SECTION_ENTER();
	tmp = ((Qspi *)hw)->QSPI_WPMR;
	tmp &= ~QSPI_WPMR_WPKEY_Msk;
	tmp |= QSPI_WPMR_WPKEY(data);
	((Qspi *)hw)->QSPI_WPMR = tmp;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_WPMR_WPKEY_bf(const void *const hw, hri_qspi_wpmr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR &= ~QSPI_WPMR_WPKEY(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_WPMR_WPKEY_bf(const void *const hw, hri_qspi_wpmr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR ^= QSPI_WPMR_WPKEY(mask);
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_wpmr_reg_t hri_qspi_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_WPMR;
	tmp = (tmp & QSPI_WPMR_WPKEY_Msk) >> QSPI_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_qspi_set_WPMR_reg(const void *const hw, hri_qspi_wpmr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR |= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_wpmr_reg_t hri_qspi_get_WPMR_reg(const void *const hw, hri_qspi_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Qspi *)hw)->QSPI_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_qspi_write_WPMR_reg(const void *const hw, hri_qspi_wpmr_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_clear_WPMR_reg(const void *const hw, hri_qspi_wpmr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR &= ~mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_toggle_WPMR_reg(const void *const hw, hri_qspi_wpmr_reg_t mask)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_WPMR ^= mask;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_qspi_wpmr_reg_t hri_qspi_read_WPMR_reg(const void *const hw)
{
	return ((Qspi *)hw)->QSPI_WPMR;
}

static inline void hri_qspi_write_CR_reg(const void *const hw, hri_qspi_cr_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_CR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_write_TDR_reg(const void *const hw, hri_qspi_tdr_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_TDR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_qspi_write_SKR_reg(const void *const hw, hri_qspi_skr_reg_t data)
{
	QSPI_CRITICAL_SECTION_ENTER();
	((Qspi *)hw)->QSPI_SKR = data;
	QSPI_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_QSPI_E70B_H_INCLUDED */
#endif /* _SAME70_QSPI_COMPONENT_ */
