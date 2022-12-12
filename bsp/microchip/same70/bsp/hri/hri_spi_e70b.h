/**
 * \file
 *
 * \brief SAM SPI
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

#ifdef _SAME70_SPI_COMPONENT_
#ifndef _HRI_SPI_E70B_H_INCLUDED_
#define _HRI_SPI_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_SPI_CRITICAL_SECTIONS)
#define SPI_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define SPI_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define SPI_CRITICAL_SECTION_ENTER()
#define SPI_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_spi_cr_reg_t;
typedef uint32_t hri_spi_csr_reg_t;
typedef uint32_t hri_spi_imr_reg_t;
typedef uint32_t hri_spi_mr_reg_t;
typedef uint32_t hri_spi_rdr_reg_t;
typedef uint32_t hri_spi_sr_reg_t;
typedef uint32_t hri_spi_tdr_reg_t;
typedef uint32_t hri_spi_wpmr_reg_t;
typedef uint32_t hri_spi_wpsr_reg_t;

static inline void hri_spi_set_IMR_RDRF_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IER = SPI_IMR_RDRF;
}

static inline bool hri_spi_get_IMR_RDRF_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_IMR & SPI_IMR_RDRF) >> SPI_IMR_RDRF_Pos;
}

static inline void hri_spi_write_IMR_RDRF_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Spi *)hw)->SPI_IDR = SPI_IMR_RDRF;
	} else {
		((Spi *)hw)->SPI_IER = SPI_IMR_RDRF;
	}
}

static inline void hri_spi_clear_IMR_RDRF_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IDR = SPI_IMR_RDRF;
}

static inline void hri_spi_set_IMR_TDRE_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IER = SPI_IMR_TDRE;
}

static inline bool hri_spi_get_IMR_TDRE_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_IMR & SPI_IMR_TDRE) >> SPI_IMR_TDRE_Pos;
}

static inline void hri_spi_write_IMR_TDRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Spi *)hw)->SPI_IDR = SPI_IMR_TDRE;
	} else {
		((Spi *)hw)->SPI_IER = SPI_IMR_TDRE;
	}
}

static inline void hri_spi_clear_IMR_TDRE_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IDR = SPI_IMR_TDRE;
}

static inline void hri_spi_set_IMR_MODF_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IER = SPI_IMR_MODF;
}

static inline bool hri_spi_get_IMR_MODF_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_IMR & SPI_IMR_MODF) >> SPI_IMR_MODF_Pos;
}

static inline void hri_spi_write_IMR_MODF_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Spi *)hw)->SPI_IDR = SPI_IMR_MODF;
	} else {
		((Spi *)hw)->SPI_IER = SPI_IMR_MODF;
	}
}

static inline void hri_spi_clear_IMR_MODF_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IDR = SPI_IMR_MODF;
}

static inline void hri_spi_set_IMR_OVRES_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IER = SPI_IMR_OVRES;
}

static inline bool hri_spi_get_IMR_OVRES_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_IMR & SPI_IMR_OVRES) >> SPI_IMR_OVRES_Pos;
}

static inline void hri_spi_write_IMR_OVRES_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Spi *)hw)->SPI_IDR = SPI_IMR_OVRES;
	} else {
		((Spi *)hw)->SPI_IER = SPI_IMR_OVRES;
	}
}

static inline void hri_spi_clear_IMR_OVRES_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IDR = SPI_IMR_OVRES;
}

static inline void hri_spi_set_IMR_NSSR_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IER = SPI_IMR_NSSR;
}

static inline bool hri_spi_get_IMR_NSSR_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_IMR & SPI_IMR_NSSR) >> SPI_IMR_NSSR_Pos;
}

static inline void hri_spi_write_IMR_NSSR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Spi *)hw)->SPI_IDR = SPI_IMR_NSSR;
	} else {
		((Spi *)hw)->SPI_IER = SPI_IMR_NSSR;
	}
}

static inline void hri_spi_clear_IMR_NSSR_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IDR = SPI_IMR_NSSR;
}

static inline void hri_spi_set_IMR_TXEMPTY_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IER = SPI_IMR_TXEMPTY;
}

static inline bool hri_spi_get_IMR_TXEMPTY_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_IMR & SPI_IMR_TXEMPTY) >> SPI_IMR_TXEMPTY_Pos;
}

static inline void hri_spi_write_IMR_TXEMPTY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Spi *)hw)->SPI_IDR = SPI_IMR_TXEMPTY;
	} else {
		((Spi *)hw)->SPI_IER = SPI_IMR_TXEMPTY;
	}
}

static inline void hri_spi_clear_IMR_TXEMPTY_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IDR = SPI_IMR_TXEMPTY;
}

static inline void hri_spi_set_IMR_UNDES_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IER = SPI_IMR_UNDES;
}

static inline bool hri_spi_get_IMR_UNDES_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_IMR & SPI_IMR_UNDES) >> SPI_IMR_UNDES_Pos;
}

static inline void hri_spi_write_IMR_UNDES_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Spi *)hw)->SPI_IDR = SPI_IMR_UNDES;
	} else {
		((Spi *)hw)->SPI_IER = SPI_IMR_UNDES;
	}
}

static inline void hri_spi_clear_IMR_UNDES_bit(const void *const hw)
{
	((Spi *)hw)->SPI_IDR = SPI_IMR_UNDES;
}

static inline void hri_spi_set_IMR_reg(const void *const hw, hri_spi_imr_reg_t mask)
{
	((Spi *)hw)->SPI_IER = mask;
}

static inline hri_spi_imr_reg_t hri_spi_get_IMR_reg(const void *const hw, hri_spi_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_spi_imr_reg_t hri_spi_read_IMR_reg(const void *const hw)
{
	return ((Spi *)hw)->SPI_IMR;
}

static inline void hri_spi_write_IMR_reg(const void *const hw, hri_spi_imr_reg_t data)
{
	((Spi *)hw)->SPI_IER = data;
	((Spi *)hw)->SPI_IDR = ~data;
}

static inline void hri_spi_clear_IMR_reg(const void *const hw, hri_spi_imr_reg_t mask)
{
	((Spi *)hw)->SPI_IDR = mask;
}

static inline hri_spi_rdr_reg_t hri_spi_get_RDR_RD_bf(const void *const hw, hri_spi_rdr_reg_t mask)
{
	return (((Spi *)hw)->SPI_RDR & SPI_RDR_RD(mask)) >> SPI_RDR_RD_Pos;
}

static inline hri_spi_rdr_reg_t hri_spi_read_RDR_RD_bf(const void *const hw)
{
	return (((Spi *)hw)->SPI_RDR & SPI_RDR_RD_Msk) >> SPI_RDR_RD_Pos;
}

static inline hri_spi_rdr_reg_t hri_spi_get_RDR_PCS_bf(const void *const hw, hri_spi_rdr_reg_t mask)
{
	return (((Spi *)hw)->SPI_RDR & SPI_RDR_PCS(mask)) >> SPI_RDR_PCS_Pos;
}

static inline hri_spi_rdr_reg_t hri_spi_read_RDR_PCS_bf(const void *const hw)
{
	return (((Spi *)hw)->SPI_RDR & SPI_RDR_PCS_Msk) >> SPI_RDR_PCS_Pos;
}

static inline hri_spi_rdr_reg_t hri_spi_get_RDR_reg(const void *const hw, hri_spi_rdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_RDR;
	tmp &= mask;
	return tmp;
}

static inline hri_spi_rdr_reg_t hri_spi_read_RDR_reg(const void *const hw)
{
	return ((Spi *)hw)->SPI_RDR;
}

static inline bool hri_spi_get_SR_RDRF_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_SR & SPI_SR_RDRF) > 0;
}

static inline bool hri_spi_get_SR_TDRE_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_SR & SPI_SR_TDRE) > 0;
}

static inline bool hri_spi_get_SR_MODF_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_SR & SPI_SR_MODF) > 0;
}

static inline bool hri_spi_get_SR_OVRES_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_SR & SPI_SR_OVRES) > 0;
}

static inline bool hri_spi_get_SR_NSSR_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_SR & SPI_SR_NSSR) > 0;
}

static inline bool hri_spi_get_SR_TXEMPTY_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_SR & SPI_SR_TXEMPTY) > 0;
}

static inline bool hri_spi_get_SR_UNDES_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_SR & SPI_SR_UNDES) > 0;
}

static inline bool hri_spi_get_SR_SPIENS_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_SR & SPI_SR_SPIENS) > 0;
}

static inline hri_spi_sr_reg_t hri_spi_get_SR_reg(const void *const hw, hri_spi_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_spi_sr_reg_t hri_spi_read_SR_reg(const void *const hw)
{
	return ((Spi *)hw)->SPI_SR;
}

static inline bool hri_spi_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Spi *)hw)->SPI_WPSR & SPI_WPSR_WPVS) > 0;
}

static inline hri_spi_wpsr_reg_t hri_spi_get_WPSR_WPVSRC_bf(const void *const hw, hri_spi_wpsr_reg_t mask)
{
	return (((Spi *)hw)->SPI_WPSR & SPI_WPSR_WPVSRC(mask)) >> SPI_WPSR_WPVSRC_Pos;
}

static inline hri_spi_wpsr_reg_t hri_spi_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Spi *)hw)->SPI_WPSR & SPI_WPSR_WPVSRC_Msk) >> SPI_WPSR_WPVSRC_Pos;
}

static inline hri_spi_wpsr_reg_t hri_spi_get_WPSR_reg(const void *const hw, hri_spi_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_spi_wpsr_reg_t hri_spi_read_WPSR_reg(const void *const hw)
{
	return ((Spi *)hw)->SPI_WPSR;
}

static inline void hri_spi_set_MR_MSTR_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR |= SPI_MR_MSTR;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_MR_MSTR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_MSTR) >> SPI_MR_MSTR_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_MR_MSTR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_MR;
	tmp &= ~SPI_MR_MSTR;
	tmp |= value << SPI_MR_MSTR_Pos;
	((Spi *)hw)->SPI_MR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_MR_MSTR_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR &= ~SPI_MR_MSTR;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_MR_MSTR_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR ^= SPI_MR_MSTR;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_MR_PS_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR |= SPI_MR_PS;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_MR_PS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_PS) >> SPI_MR_PS_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_MR_PS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_MR;
	tmp &= ~SPI_MR_PS;
	tmp |= value << SPI_MR_PS_Pos;
	((Spi *)hw)->SPI_MR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_MR_PS_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR &= ~SPI_MR_PS;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_MR_PS_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR ^= SPI_MR_PS;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_MR_PCSDEC_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR |= SPI_MR_PCSDEC;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_MR_PCSDEC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_PCSDEC) >> SPI_MR_PCSDEC_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_MR_PCSDEC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_MR;
	tmp &= ~SPI_MR_PCSDEC;
	tmp |= value << SPI_MR_PCSDEC_Pos;
	((Spi *)hw)->SPI_MR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_MR_PCSDEC_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR &= ~SPI_MR_PCSDEC;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_MR_PCSDEC_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR ^= SPI_MR_PCSDEC;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_MR_MODFDIS_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR |= SPI_MR_MODFDIS;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_MR_MODFDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_MODFDIS) >> SPI_MR_MODFDIS_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_MR_MODFDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_MR;
	tmp &= ~SPI_MR_MODFDIS;
	tmp |= value << SPI_MR_MODFDIS_Pos;
	((Spi *)hw)->SPI_MR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_MR_MODFDIS_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR &= ~SPI_MR_MODFDIS;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_MR_MODFDIS_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR ^= SPI_MR_MODFDIS;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_MR_WDRBT_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR |= SPI_MR_WDRBT;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_MR_WDRBT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_WDRBT) >> SPI_MR_WDRBT_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_MR_WDRBT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_MR;
	tmp &= ~SPI_MR_WDRBT;
	tmp |= value << SPI_MR_WDRBT_Pos;
	((Spi *)hw)->SPI_MR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_MR_WDRBT_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR &= ~SPI_MR_WDRBT;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_MR_WDRBT_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR ^= SPI_MR_WDRBT;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_MR_LLB_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR |= SPI_MR_LLB;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_MR_LLB_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_LLB) >> SPI_MR_LLB_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_MR_LLB_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_MR;
	tmp &= ~SPI_MR_LLB;
	tmp |= value << SPI_MR_LLB_Pos;
	((Spi *)hw)->SPI_MR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_MR_LLB_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR &= ~SPI_MR_LLB;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_MR_LLB_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR ^= SPI_MR_LLB;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_MR_PCS_bf(const void *const hw, hri_spi_mr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR |= SPI_MR_PCS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_mr_reg_t hri_spi_get_MR_PCS_bf(const void *const hw, hri_spi_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_PCS(mask)) >> SPI_MR_PCS_Pos;
	return tmp;
}

static inline void hri_spi_write_MR_PCS_bf(const void *const hw, hri_spi_mr_reg_t data)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_MR;
	tmp &= ~SPI_MR_PCS_Msk;
	tmp |= SPI_MR_PCS(data);
	((Spi *)hw)->SPI_MR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_MR_PCS_bf(const void *const hw, hri_spi_mr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR &= ~SPI_MR_PCS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_MR_PCS_bf(const void *const hw, hri_spi_mr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR ^= SPI_MR_PCS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_mr_reg_t hri_spi_read_MR_PCS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_PCS_Msk) >> SPI_MR_PCS_Pos;
	return tmp;
}

static inline void hri_spi_set_MR_DLYBCS_bf(const void *const hw, hri_spi_mr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR |= SPI_MR_DLYBCS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_mr_reg_t hri_spi_get_MR_DLYBCS_bf(const void *const hw, hri_spi_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_DLYBCS(mask)) >> SPI_MR_DLYBCS_Pos;
	return tmp;
}

static inline void hri_spi_write_MR_DLYBCS_bf(const void *const hw, hri_spi_mr_reg_t data)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_MR;
	tmp &= ~SPI_MR_DLYBCS_Msk;
	tmp |= SPI_MR_DLYBCS(data);
	((Spi *)hw)->SPI_MR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_MR_DLYBCS_bf(const void *const hw, hri_spi_mr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR &= ~SPI_MR_DLYBCS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_MR_DLYBCS_bf(const void *const hw, hri_spi_mr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR ^= SPI_MR_DLYBCS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_mr_reg_t hri_spi_read_MR_DLYBCS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp = (tmp & SPI_MR_DLYBCS_Msk) >> SPI_MR_DLYBCS_Pos;
	return tmp;
}

static inline void hri_spi_set_MR_reg(const void *const hw, hri_spi_mr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR |= mask;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_mr_reg_t hri_spi_get_MR_reg(const void *const hw, hri_spi_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_spi_write_MR_reg(const void *const hw, hri_spi_mr_reg_t data)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR = data;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_MR_reg(const void *const hw, hri_spi_mr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR &= ~mask;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_MR_reg(const void *const hw, hri_spi_mr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_MR ^= mask;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_mr_reg_t hri_spi_read_MR_reg(const void *const hw)
{
	return ((Spi *)hw)->SPI_MR;
}

static inline void hri_spi_set_CSR_CPOL_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] |= SPI_CSR_CPOL;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_CSR_CPOL_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_CPOL) >> SPI_CSR_CPOL_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_CSR_CPOL_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp &= ~SPI_CSR_CPOL;
	tmp |= value << SPI_CSR_CPOL_Pos;
	((Spi *)hw)->SPI_CSR[index] = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_CSR_CPOL_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] &= ~SPI_CSR_CPOL;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_CSR_CPOL_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] ^= SPI_CSR_CPOL;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_CSR_NCPHA_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] |= SPI_CSR_NCPHA;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_CSR_NCPHA_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_NCPHA) >> SPI_CSR_NCPHA_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_CSR_NCPHA_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp &= ~SPI_CSR_NCPHA;
	tmp |= value << SPI_CSR_NCPHA_Pos;
	((Spi *)hw)->SPI_CSR[index] = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_CSR_NCPHA_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] &= ~SPI_CSR_NCPHA;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_CSR_NCPHA_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] ^= SPI_CSR_NCPHA;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_CSR_CSNAAT_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] |= SPI_CSR_CSNAAT;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_CSR_CSNAAT_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_CSNAAT) >> SPI_CSR_CSNAAT_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_CSR_CSNAAT_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp &= ~SPI_CSR_CSNAAT;
	tmp |= value << SPI_CSR_CSNAAT_Pos;
	((Spi *)hw)->SPI_CSR[index] = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_CSR_CSNAAT_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] &= ~SPI_CSR_CSNAAT;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_CSR_CSNAAT_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] ^= SPI_CSR_CSNAAT;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_CSR_CSAAT_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] |= SPI_CSR_CSAAT;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_CSR_CSAAT_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_CSAAT) >> SPI_CSR_CSAAT_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_CSR_CSAAT_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp &= ~SPI_CSR_CSAAT;
	tmp |= value << SPI_CSR_CSAAT_Pos;
	((Spi *)hw)->SPI_CSR[index] = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_CSR_CSAAT_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] &= ~SPI_CSR_CSAAT;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_CSR_CSAAT_bit(const void *const hw, uint8_t index)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] ^= SPI_CSR_CSAAT;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_CSR_BITS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] |= SPI_CSR_BITS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_get_CSR_BITS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_BITS(mask)) >> SPI_CSR_BITS_Pos;
	return tmp;
}

static inline void hri_spi_write_CSR_BITS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t data)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp &= ~SPI_CSR_BITS_Msk;
	tmp |= SPI_CSR_BITS(data);
	((Spi *)hw)->SPI_CSR[index] = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_CSR_BITS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] &= ~SPI_CSR_BITS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_CSR_BITS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] ^= SPI_CSR_BITS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_read_CSR_BITS_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_BITS_Msk) >> SPI_CSR_BITS_Pos;
	return tmp;
}

static inline void hri_spi_set_CSR_SCBR_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] |= SPI_CSR_SCBR(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_get_CSR_SCBR_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_SCBR(mask)) >> SPI_CSR_SCBR_Pos;
	return tmp;
}

static inline void hri_spi_write_CSR_SCBR_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t data)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp &= ~SPI_CSR_SCBR_Msk;
	tmp |= SPI_CSR_SCBR(data);
	((Spi *)hw)->SPI_CSR[index] = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_CSR_SCBR_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] &= ~SPI_CSR_SCBR(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_CSR_SCBR_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] ^= SPI_CSR_SCBR(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_read_CSR_SCBR_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_SCBR_Msk) >> SPI_CSR_SCBR_Pos;
	return tmp;
}

static inline void hri_spi_set_CSR_DLYBS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] |= SPI_CSR_DLYBS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_get_CSR_DLYBS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_DLYBS(mask)) >> SPI_CSR_DLYBS_Pos;
	return tmp;
}

static inline void hri_spi_write_CSR_DLYBS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t data)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp &= ~SPI_CSR_DLYBS_Msk;
	tmp |= SPI_CSR_DLYBS(data);
	((Spi *)hw)->SPI_CSR[index] = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_CSR_DLYBS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] &= ~SPI_CSR_DLYBS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_CSR_DLYBS_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] ^= SPI_CSR_DLYBS(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_read_CSR_DLYBS_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_DLYBS_Msk) >> SPI_CSR_DLYBS_Pos;
	return tmp;
}

static inline void hri_spi_set_CSR_DLYBCT_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] |= SPI_CSR_DLYBCT(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_get_CSR_DLYBCT_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_DLYBCT(mask)) >> SPI_CSR_DLYBCT_Pos;
	return tmp;
}

static inline void hri_spi_write_CSR_DLYBCT_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t data)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp &= ~SPI_CSR_DLYBCT_Msk;
	tmp |= SPI_CSR_DLYBCT(data);
	((Spi *)hw)->SPI_CSR[index] = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_CSR_DLYBCT_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] &= ~SPI_CSR_DLYBCT(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_CSR_DLYBCT_bf(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] ^= SPI_CSR_DLYBCT(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_read_CSR_DLYBCT_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp = (tmp & SPI_CSR_DLYBCT_Msk) >> SPI_CSR_DLYBCT_Pos;
	return tmp;
}

static inline void hri_spi_set_CSR_reg(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] |= mask;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_get_CSR_reg(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_CSR[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_spi_write_CSR_reg(const void *const hw, uint8_t index, hri_spi_csr_reg_t data)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] = data;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_CSR_reg(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] &= ~mask;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_CSR_reg(const void *const hw, uint8_t index, hri_spi_csr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CSR[index] ^= mask;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_csr_reg_t hri_spi_read_CSR_reg(const void *const hw, uint8_t index)
{
	return ((Spi *)hw)->SPI_CSR[index];
}

static inline void hri_spi_set_WPMR_WPEN_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR |= SPI_WPMR_WPEN;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_spi_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_WPMR;
	tmp = (tmp & SPI_WPMR_WPEN) >> SPI_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_spi_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_WPMR;
	tmp &= ~SPI_WPMR_WPEN;
	tmp |= value << SPI_WPMR_WPEN_Pos;
	((Spi *)hw)->SPI_WPMR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_WPMR_WPEN_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR &= ~SPI_WPMR_WPEN;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_WPMR_WPEN_bit(const void *const hw)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR ^= SPI_WPMR_WPEN;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_set_WPMR_WPKEY_bf(const void *const hw, hri_spi_wpmr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR |= SPI_WPMR_WPKEY(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_wpmr_reg_t hri_spi_get_WPMR_WPKEY_bf(const void *const hw, hri_spi_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_WPMR;
	tmp = (tmp & SPI_WPMR_WPKEY(mask)) >> SPI_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_spi_write_WPMR_WPKEY_bf(const void *const hw, hri_spi_wpmr_reg_t data)
{
	uint32_t tmp;
	SPI_CRITICAL_SECTION_ENTER();
	tmp = ((Spi *)hw)->SPI_WPMR;
	tmp &= ~SPI_WPMR_WPKEY_Msk;
	tmp |= SPI_WPMR_WPKEY(data);
	((Spi *)hw)->SPI_WPMR = tmp;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_WPMR_WPKEY_bf(const void *const hw, hri_spi_wpmr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR &= ~SPI_WPMR_WPKEY(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_WPMR_WPKEY_bf(const void *const hw, hri_spi_wpmr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR ^= SPI_WPMR_WPKEY(mask);
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_wpmr_reg_t hri_spi_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_WPMR;
	tmp = (tmp & SPI_WPMR_WPKEY_Msk) >> SPI_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_spi_set_WPMR_reg(const void *const hw, hri_spi_wpmr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR |= mask;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_wpmr_reg_t hri_spi_get_WPMR_reg(const void *const hw, hri_spi_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Spi *)hw)->SPI_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_spi_write_WPMR_reg(const void *const hw, hri_spi_wpmr_reg_t data)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR = data;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_clear_WPMR_reg(const void *const hw, hri_spi_wpmr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR &= ~mask;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_toggle_WPMR_reg(const void *const hw, hri_spi_wpmr_reg_t mask)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_WPMR ^= mask;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline hri_spi_wpmr_reg_t hri_spi_read_WPMR_reg(const void *const hw)
{
	return ((Spi *)hw)->SPI_WPMR;
}

static inline void hri_spi_write_CR_reg(const void *const hw, hri_spi_cr_reg_t data)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_CR = data;
	SPI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_spi_write_TDR_reg(const void *const hw, hri_spi_tdr_reg_t data)
{
	SPI_CRITICAL_SECTION_ENTER();
	((Spi *)hw)->SPI_TDR = data;
	SPI_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SPI_E70B_H_INCLUDED */
#endif /* _SAME70_SPI_COMPONENT_ */
