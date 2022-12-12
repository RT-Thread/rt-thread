/**
 * \file
 *
 * \brief SAM SSC
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

#ifdef _SAME70_SSC_COMPONENT_
#ifndef _HRI_SSC_E70B_H_INCLUDED_
#define _HRI_SSC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_SSC_CRITICAL_SECTIONS)
#define SSC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define SSC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define SSC_CRITICAL_SECTION_ENTER()
#define SSC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_ssc_cmr_reg_t;
typedef uint32_t hri_ssc_cr_reg_t;
typedef uint32_t hri_ssc_imr_reg_t;
typedef uint32_t hri_ssc_rc0r_reg_t;
typedef uint32_t hri_ssc_rc1r_reg_t;
typedef uint32_t hri_ssc_rcmr_reg_t;
typedef uint32_t hri_ssc_rfmr_reg_t;
typedef uint32_t hri_ssc_rhr_reg_t;
typedef uint32_t hri_ssc_rshr_reg_t;
typedef uint32_t hri_ssc_sr_reg_t;
typedef uint32_t hri_ssc_tcmr_reg_t;
typedef uint32_t hri_ssc_tfmr_reg_t;
typedef uint32_t hri_ssc_thr_reg_t;
typedef uint32_t hri_ssc_tshr_reg_t;
typedef uint32_t hri_ssc_wpmr_reg_t;
typedef uint32_t hri_ssc_wpsr_reg_t;

static inline void hri_ssc_set_IMR_TXRDY_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IER = SSC_IMR_TXRDY;
}

static inline bool hri_ssc_get_IMR_TXRDY_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_IMR & SSC_IMR_TXRDY) >> SSC_IMR_TXRDY_Pos;
}

static inline void hri_ssc_write_IMR_TXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ssc *)hw)->SSC_IDR = SSC_IMR_TXRDY;
	} else {
		((Ssc *)hw)->SSC_IER = SSC_IMR_TXRDY;
	}
}

static inline void hri_ssc_clear_IMR_TXRDY_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IDR = SSC_IMR_TXRDY;
}

static inline void hri_ssc_set_IMR_TXEMPTY_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IER = SSC_IMR_TXEMPTY;
}

static inline bool hri_ssc_get_IMR_TXEMPTY_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_IMR & SSC_IMR_TXEMPTY) >> SSC_IMR_TXEMPTY_Pos;
}

static inline void hri_ssc_write_IMR_TXEMPTY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ssc *)hw)->SSC_IDR = SSC_IMR_TXEMPTY;
	} else {
		((Ssc *)hw)->SSC_IER = SSC_IMR_TXEMPTY;
	}
}

static inline void hri_ssc_clear_IMR_TXEMPTY_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IDR = SSC_IMR_TXEMPTY;
}

static inline void hri_ssc_set_IMR_RXRDY_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IER = SSC_IMR_RXRDY;
}

static inline bool hri_ssc_get_IMR_RXRDY_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_IMR & SSC_IMR_RXRDY) >> SSC_IMR_RXRDY_Pos;
}

static inline void hri_ssc_write_IMR_RXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ssc *)hw)->SSC_IDR = SSC_IMR_RXRDY;
	} else {
		((Ssc *)hw)->SSC_IER = SSC_IMR_RXRDY;
	}
}

static inline void hri_ssc_clear_IMR_RXRDY_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IDR = SSC_IMR_RXRDY;
}

static inline void hri_ssc_set_IMR_OVRUN_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IER = SSC_IMR_OVRUN;
}

static inline bool hri_ssc_get_IMR_OVRUN_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_IMR & SSC_IMR_OVRUN) >> SSC_IMR_OVRUN_Pos;
}

static inline void hri_ssc_write_IMR_OVRUN_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ssc *)hw)->SSC_IDR = SSC_IMR_OVRUN;
	} else {
		((Ssc *)hw)->SSC_IER = SSC_IMR_OVRUN;
	}
}

static inline void hri_ssc_clear_IMR_OVRUN_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IDR = SSC_IMR_OVRUN;
}

static inline void hri_ssc_set_IMR_CP0_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IER = SSC_IMR_CP0;
}

static inline bool hri_ssc_get_IMR_CP0_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_IMR & SSC_IMR_CP0) >> SSC_IMR_CP0_Pos;
}

static inline void hri_ssc_write_IMR_CP0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ssc *)hw)->SSC_IDR = SSC_IMR_CP0;
	} else {
		((Ssc *)hw)->SSC_IER = SSC_IMR_CP0;
	}
}

static inline void hri_ssc_clear_IMR_CP0_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IDR = SSC_IMR_CP0;
}

static inline void hri_ssc_set_IMR_CP1_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IER = SSC_IMR_CP1;
}

static inline bool hri_ssc_get_IMR_CP1_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_IMR & SSC_IMR_CP1) >> SSC_IMR_CP1_Pos;
}

static inline void hri_ssc_write_IMR_CP1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ssc *)hw)->SSC_IDR = SSC_IMR_CP1;
	} else {
		((Ssc *)hw)->SSC_IER = SSC_IMR_CP1;
	}
}

static inline void hri_ssc_clear_IMR_CP1_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IDR = SSC_IMR_CP1;
}

static inline void hri_ssc_set_IMR_TXSYN_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IER = SSC_IMR_TXSYN;
}

static inline bool hri_ssc_get_IMR_TXSYN_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_IMR & SSC_IMR_TXSYN) >> SSC_IMR_TXSYN_Pos;
}

static inline void hri_ssc_write_IMR_TXSYN_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ssc *)hw)->SSC_IDR = SSC_IMR_TXSYN;
	} else {
		((Ssc *)hw)->SSC_IER = SSC_IMR_TXSYN;
	}
}

static inline void hri_ssc_clear_IMR_TXSYN_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IDR = SSC_IMR_TXSYN;
}

static inline void hri_ssc_set_IMR_RXSYN_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IER = SSC_IMR_RXSYN;
}

static inline bool hri_ssc_get_IMR_RXSYN_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_IMR & SSC_IMR_RXSYN) >> SSC_IMR_RXSYN_Pos;
}

static inline void hri_ssc_write_IMR_RXSYN_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ssc *)hw)->SSC_IDR = SSC_IMR_RXSYN;
	} else {
		((Ssc *)hw)->SSC_IER = SSC_IMR_RXSYN;
	}
}

static inline void hri_ssc_clear_IMR_RXSYN_bit(const void *const hw)
{
	((Ssc *)hw)->SSC_IDR = SSC_IMR_RXSYN;
}

static inline void hri_ssc_set_IMR_reg(const void *const hw, hri_ssc_imr_reg_t mask)
{
	((Ssc *)hw)->SSC_IER = mask;
}

static inline hri_ssc_imr_reg_t hri_ssc_get_IMR_reg(const void *const hw, hri_ssc_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_ssc_imr_reg_t hri_ssc_read_IMR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_IMR;
}

static inline void hri_ssc_write_IMR_reg(const void *const hw, hri_ssc_imr_reg_t data)
{
	((Ssc *)hw)->SSC_IER = data;
	((Ssc *)hw)->SSC_IDR = ~data;
}

static inline void hri_ssc_clear_IMR_reg(const void *const hw, hri_ssc_imr_reg_t mask)
{
	((Ssc *)hw)->SSC_IDR = mask;
}

static inline hri_ssc_rhr_reg_t hri_ssc_get_RHR_RDAT_bf(const void *const hw, hri_ssc_rhr_reg_t mask)
{
	return (((Ssc *)hw)->SSC_RHR & SSC_RHR_RDAT(mask)) >> SSC_RHR_RDAT_Pos;
}

static inline hri_ssc_rhr_reg_t hri_ssc_read_RHR_RDAT_bf(const void *const hw)
{
	return (((Ssc *)hw)->SSC_RHR & SSC_RHR_RDAT_Msk) >> SSC_RHR_RDAT_Pos;
}

static inline hri_ssc_rhr_reg_t hri_ssc_get_RHR_reg(const void *const hw, hri_ssc_rhr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RHR;
	tmp &= mask;
	return tmp;
}

static inline hri_ssc_rhr_reg_t hri_ssc_read_RHR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_RHR;
}

static inline hri_ssc_rshr_reg_t hri_ssc_get_RSHR_RSDAT_bf(const void *const hw, hri_ssc_rshr_reg_t mask)
{
	return (((Ssc *)hw)->SSC_RSHR & SSC_RSHR_RSDAT(mask)) >> SSC_RSHR_RSDAT_Pos;
}

static inline hri_ssc_rshr_reg_t hri_ssc_read_RSHR_RSDAT_bf(const void *const hw)
{
	return (((Ssc *)hw)->SSC_RSHR & SSC_RSHR_RSDAT_Msk) >> SSC_RSHR_RSDAT_Pos;
}

static inline hri_ssc_rshr_reg_t hri_ssc_get_RSHR_reg(const void *const hw, hri_ssc_rshr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RSHR;
	tmp &= mask;
	return tmp;
}

static inline hri_ssc_rshr_reg_t hri_ssc_read_RSHR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_RSHR;
}

static inline bool hri_ssc_get_SR_TXRDY_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_TXRDY) > 0;
}

static inline bool hri_ssc_get_SR_TXEMPTY_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_TXEMPTY) > 0;
}

static inline bool hri_ssc_get_SR_RXRDY_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_RXRDY) > 0;
}

static inline bool hri_ssc_get_SR_OVRUN_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_OVRUN) > 0;
}

static inline bool hri_ssc_get_SR_CP0_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_CP0) > 0;
}

static inline bool hri_ssc_get_SR_CP1_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_CP1) > 0;
}

static inline bool hri_ssc_get_SR_TXSYN_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_TXSYN) > 0;
}

static inline bool hri_ssc_get_SR_RXSYN_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_RXSYN) > 0;
}

static inline bool hri_ssc_get_SR_TXEN_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_TXEN) > 0;
}

static inline bool hri_ssc_get_SR_RXEN_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_SR & SSC_SR_RXEN) > 0;
}

static inline hri_ssc_sr_reg_t hri_ssc_get_SR_reg(const void *const hw, hri_ssc_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_ssc_sr_reg_t hri_ssc_read_SR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_SR;
}

static inline bool hri_ssc_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Ssc *)hw)->SSC_WPSR & SSC_WPSR_WPVS) > 0;
}

static inline hri_ssc_wpsr_reg_t hri_ssc_get_WPSR_WPVSRC_bf(const void *const hw, hri_ssc_wpsr_reg_t mask)
{
	return (((Ssc *)hw)->SSC_WPSR & SSC_WPSR_WPVSRC(mask)) >> SSC_WPSR_WPVSRC_Pos;
}

static inline hri_ssc_wpsr_reg_t hri_ssc_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Ssc *)hw)->SSC_WPSR & SSC_WPSR_WPVSRC_Msk) >> SSC_WPSR_WPVSRC_Pos;
}

static inline hri_ssc_wpsr_reg_t hri_ssc_get_WPSR_reg(const void *const hw, hri_ssc_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_ssc_wpsr_reg_t hri_ssc_read_WPSR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_WPSR;
}

static inline void hri_ssc_set_CMR_DIV_bf(const void *const hw, hri_ssc_cmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_CMR |= SSC_CMR_DIV(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_cmr_reg_t hri_ssc_get_CMR_DIV_bf(const void *const hw, hri_ssc_cmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_CMR;
	tmp = (tmp & SSC_CMR_DIV(mask)) >> SSC_CMR_DIV_Pos;
	return tmp;
}

static inline void hri_ssc_write_CMR_DIV_bf(const void *const hw, hri_ssc_cmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_CMR;
	tmp &= ~SSC_CMR_DIV_Msk;
	tmp |= SSC_CMR_DIV(data);
	((Ssc *)hw)->SSC_CMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_CMR_DIV_bf(const void *const hw, hri_ssc_cmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_CMR &= ~SSC_CMR_DIV(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_CMR_DIV_bf(const void *const hw, hri_ssc_cmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_CMR ^= SSC_CMR_DIV(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_cmr_reg_t hri_ssc_read_CMR_DIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_CMR;
	tmp = (tmp & SSC_CMR_DIV_Msk) >> SSC_CMR_DIV_Pos;
	return tmp;
}

static inline void hri_ssc_set_CMR_reg(const void *const hw, hri_ssc_cmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_CMR |= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_cmr_reg_t hri_ssc_get_CMR_reg(const void *const hw, hri_ssc_cmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_CMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_ssc_write_CMR_reg(const void *const hw, hri_ssc_cmr_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_CMR = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_CMR_reg(const void *const hw, hri_ssc_cmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_CMR &= ~mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_CMR_reg(const void *const hw, hri_ssc_cmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_CMR ^= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_cmr_reg_t hri_ssc_read_CMR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_CMR;
}

static inline void hri_ssc_set_RCMR_CKI_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR |= SSC_RCMR_CKI;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_RCMR_CKI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_CKI) >> SSC_RCMR_CKI_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_RCMR_CKI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp &= ~SSC_RCMR_CKI;
	tmp |= value << SSC_RCMR_CKI_Pos;
	((Ssc *)hw)->SSC_RCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RCMR_CKI_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR &= ~SSC_RCMR_CKI;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RCMR_CKI_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR ^= SSC_RCMR_CKI;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_RCMR_STOP_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR |= SSC_RCMR_STOP;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_RCMR_STOP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_STOP) >> SSC_RCMR_STOP_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_RCMR_STOP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp &= ~SSC_RCMR_STOP;
	tmp |= value << SSC_RCMR_STOP_Pos;
	((Ssc *)hw)->SSC_RCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RCMR_STOP_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR &= ~SSC_RCMR_STOP;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RCMR_STOP_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR ^= SSC_RCMR_STOP;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_RCMR_CKS_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR |= SSC_RCMR_CKS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_get_RCMR_CKS_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_CKS(mask)) >> SSC_RCMR_CKS_Pos;
	return tmp;
}

static inline void hri_ssc_write_RCMR_CKS_bf(const void *const hw, hri_ssc_rcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp &= ~SSC_RCMR_CKS_Msk;
	tmp |= SSC_RCMR_CKS(data);
	((Ssc *)hw)->SSC_RCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RCMR_CKS_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR &= ~SSC_RCMR_CKS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RCMR_CKS_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR ^= SSC_RCMR_CKS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_read_RCMR_CKS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_CKS_Msk) >> SSC_RCMR_CKS_Pos;
	return tmp;
}

static inline void hri_ssc_set_RCMR_CKO_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR |= SSC_RCMR_CKO(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_get_RCMR_CKO_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_CKO(mask)) >> SSC_RCMR_CKO_Pos;
	return tmp;
}

static inline void hri_ssc_write_RCMR_CKO_bf(const void *const hw, hri_ssc_rcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp &= ~SSC_RCMR_CKO_Msk;
	tmp |= SSC_RCMR_CKO(data);
	((Ssc *)hw)->SSC_RCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RCMR_CKO_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR &= ~SSC_RCMR_CKO(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RCMR_CKO_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR ^= SSC_RCMR_CKO(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_read_RCMR_CKO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_CKO_Msk) >> SSC_RCMR_CKO_Pos;
	return tmp;
}

static inline void hri_ssc_set_RCMR_CKG_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR |= SSC_RCMR_CKG(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_get_RCMR_CKG_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_CKG(mask)) >> SSC_RCMR_CKG_Pos;
	return tmp;
}

static inline void hri_ssc_write_RCMR_CKG_bf(const void *const hw, hri_ssc_rcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp &= ~SSC_RCMR_CKG_Msk;
	tmp |= SSC_RCMR_CKG(data);
	((Ssc *)hw)->SSC_RCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RCMR_CKG_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR &= ~SSC_RCMR_CKG(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RCMR_CKG_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR ^= SSC_RCMR_CKG(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_read_RCMR_CKG_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_CKG_Msk) >> SSC_RCMR_CKG_Pos;
	return tmp;
}

static inline void hri_ssc_set_RCMR_START_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR |= SSC_RCMR_START(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_get_RCMR_START_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_START(mask)) >> SSC_RCMR_START_Pos;
	return tmp;
}

static inline void hri_ssc_write_RCMR_START_bf(const void *const hw, hri_ssc_rcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp &= ~SSC_RCMR_START_Msk;
	tmp |= SSC_RCMR_START(data);
	((Ssc *)hw)->SSC_RCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RCMR_START_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR &= ~SSC_RCMR_START(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RCMR_START_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR ^= SSC_RCMR_START(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_read_RCMR_START_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_START_Msk) >> SSC_RCMR_START_Pos;
	return tmp;
}

static inline void hri_ssc_set_RCMR_STTDLY_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR |= SSC_RCMR_STTDLY(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_get_RCMR_STTDLY_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_STTDLY(mask)) >> SSC_RCMR_STTDLY_Pos;
	return tmp;
}

static inline void hri_ssc_write_RCMR_STTDLY_bf(const void *const hw, hri_ssc_rcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp &= ~SSC_RCMR_STTDLY_Msk;
	tmp |= SSC_RCMR_STTDLY(data);
	((Ssc *)hw)->SSC_RCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RCMR_STTDLY_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR &= ~SSC_RCMR_STTDLY(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RCMR_STTDLY_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR ^= SSC_RCMR_STTDLY(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_read_RCMR_STTDLY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_STTDLY_Msk) >> SSC_RCMR_STTDLY_Pos;
	return tmp;
}

static inline void hri_ssc_set_RCMR_PERIOD_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR |= SSC_RCMR_PERIOD(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_get_RCMR_PERIOD_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_PERIOD(mask)) >> SSC_RCMR_PERIOD_Pos;
	return tmp;
}

static inline void hri_ssc_write_RCMR_PERIOD_bf(const void *const hw, hri_ssc_rcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp &= ~SSC_RCMR_PERIOD_Msk;
	tmp |= SSC_RCMR_PERIOD(data);
	((Ssc *)hw)->SSC_RCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RCMR_PERIOD_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR &= ~SSC_RCMR_PERIOD(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RCMR_PERIOD_bf(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR ^= SSC_RCMR_PERIOD(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_read_RCMR_PERIOD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp = (tmp & SSC_RCMR_PERIOD_Msk) >> SSC_RCMR_PERIOD_Pos;
	return tmp;
}

static inline void hri_ssc_set_RCMR_reg(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR |= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_get_RCMR_reg(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RCMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_ssc_write_RCMR_reg(const void *const hw, hri_ssc_rcmr_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RCMR_reg(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR &= ~mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RCMR_reg(const void *const hw, hri_ssc_rcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RCMR ^= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rcmr_reg_t hri_ssc_read_RCMR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_RCMR;
}

static inline void hri_ssc_set_RFMR_LOOP_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR |= SSC_RFMR_LOOP;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_RFMR_LOOP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_LOOP) >> SSC_RFMR_LOOP_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_RFMR_LOOP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp &= ~SSC_RFMR_LOOP;
	tmp |= value << SSC_RFMR_LOOP_Pos;
	((Ssc *)hw)->SSC_RFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RFMR_LOOP_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR &= ~SSC_RFMR_LOOP;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RFMR_LOOP_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR ^= SSC_RFMR_LOOP;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_RFMR_MSBF_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR |= SSC_RFMR_MSBF;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_RFMR_MSBF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_MSBF) >> SSC_RFMR_MSBF_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_RFMR_MSBF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp &= ~SSC_RFMR_MSBF;
	tmp |= value << SSC_RFMR_MSBF_Pos;
	((Ssc *)hw)->SSC_RFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RFMR_MSBF_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR &= ~SSC_RFMR_MSBF;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RFMR_MSBF_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR ^= SSC_RFMR_MSBF;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_RFMR_FSEDGE_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR |= SSC_RFMR_FSEDGE;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_RFMR_FSEDGE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_FSEDGE) >> SSC_RFMR_FSEDGE_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_RFMR_FSEDGE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp &= ~SSC_RFMR_FSEDGE;
	tmp |= value << SSC_RFMR_FSEDGE_Pos;
	((Ssc *)hw)->SSC_RFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RFMR_FSEDGE_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR &= ~SSC_RFMR_FSEDGE;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RFMR_FSEDGE_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR ^= SSC_RFMR_FSEDGE;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_RFMR_DATLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR |= SSC_RFMR_DATLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_get_RFMR_DATLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_DATLEN(mask)) >> SSC_RFMR_DATLEN_Pos;
	return tmp;
}

static inline void hri_ssc_write_RFMR_DATLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp &= ~SSC_RFMR_DATLEN_Msk;
	tmp |= SSC_RFMR_DATLEN(data);
	((Ssc *)hw)->SSC_RFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RFMR_DATLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR &= ~SSC_RFMR_DATLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RFMR_DATLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR ^= SSC_RFMR_DATLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_read_RFMR_DATLEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_DATLEN_Msk) >> SSC_RFMR_DATLEN_Pos;
	return tmp;
}

static inline void hri_ssc_set_RFMR_DATNB_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR |= SSC_RFMR_DATNB(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_get_RFMR_DATNB_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_DATNB(mask)) >> SSC_RFMR_DATNB_Pos;
	return tmp;
}

static inline void hri_ssc_write_RFMR_DATNB_bf(const void *const hw, hri_ssc_rfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp &= ~SSC_RFMR_DATNB_Msk;
	tmp |= SSC_RFMR_DATNB(data);
	((Ssc *)hw)->SSC_RFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RFMR_DATNB_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR &= ~SSC_RFMR_DATNB(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RFMR_DATNB_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR ^= SSC_RFMR_DATNB(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_read_RFMR_DATNB_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_DATNB_Msk) >> SSC_RFMR_DATNB_Pos;
	return tmp;
}

static inline void hri_ssc_set_RFMR_FSLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR |= SSC_RFMR_FSLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_get_RFMR_FSLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_FSLEN(mask)) >> SSC_RFMR_FSLEN_Pos;
	return tmp;
}

static inline void hri_ssc_write_RFMR_FSLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp &= ~SSC_RFMR_FSLEN_Msk;
	tmp |= SSC_RFMR_FSLEN(data);
	((Ssc *)hw)->SSC_RFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RFMR_FSLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR &= ~SSC_RFMR_FSLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RFMR_FSLEN_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR ^= SSC_RFMR_FSLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_read_RFMR_FSLEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_FSLEN_Msk) >> SSC_RFMR_FSLEN_Pos;
	return tmp;
}

static inline void hri_ssc_set_RFMR_FSOS_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR |= SSC_RFMR_FSOS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_get_RFMR_FSOS_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_FSOS(mask)) >> SSC_RFMR_FSOS_Pos;
	return tmp;
}

static inline void hri_ssc_write_RFMR_FSOS_bf(const void *const hw, hri_ssc_rfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp &= ~SSC_RFMR_FSOS_Msk;
	tmp |= SSC_RFMR_FSOS(data);
	((Ssc *)hw)->SSC_RFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RFMR_FSOS_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR &= ~SSC_RFMR_FSOS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RFMR_FSOS_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR ^= SSC_RFMR_FSOS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_read_RFMR_FSOS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_FSOS_Msk) >> SSC_RFMR_FSOS_Pos;
	return tmp;
}

static inline void hri_ssc_set_RFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR |= SSC_RFMR_FSLEN_EXT(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_get_RFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_FSLEN_EXT(mask)) >> SSC_RFMR_FSLEN_EXT_Pos;
	return tmp;
}

static inline void hri_ssc_write_RFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_rfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp &= ~SSC_RFMR_FSLEN_EXT_Msk;
	tmp |= SSC_RFMR_FSLEN_EXT(data);
	((Ssc *)hw)->SSC_RFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR &= ~SSC_RFMR_FSLEN_EXT(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR ^= SSC_RFMR_FSLEN_EXT(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_read_RFMR_FSLEN_EXT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp = (tmp & SSC_RFMR_FSLEN_EXT_Msk) >> SSC_RFMR_FSLEN_EXT_Pos;
	return tmp;
}

static inline void hri_ssc_set_RFMR_reg(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR |= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_get_RFMR_reg(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RFMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_ssc_write_RFMR_reg(const void *const hw, hri_ssc_rfmr_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RFMR_reg(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR &= ~mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RFMR_reg(const void *const hw, hri_ssc_rfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RFMR ^= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rfmr_reg_t hri_ssc_read_RFMR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_RFMR;
}

static inline void hri_ssc_set_TCMR_CKI_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR |= SSC_TCMR_CKI;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_TCMR_CKI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_CKI) >> SSC_TCMR_CKI_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_TCMR_CKI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp &= ~SSC_TCMR_CKI;
	tmp |= value << SSC_TCMR_CKI_Pos;
	((Ssc *)hw)->SSC_TCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TCMR_CKI_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR &= ~SSC_TCMR_CKI;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TCMR_CKI_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR ^= SSC_TCMR_CKI;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_TCMR_CKS_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR |= SSC_TCMR_CKS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_get_TCMR_CKS_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_CKS(mask)) >> SSC_TCMR_CKS_Pos;
	return tmp;
}

static inline void hri_ssc_write_TCMR_CKS_bf(const void *const hw, hri_ssc_tcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp &= ~SSC_TCMR_CKS_Msk;
	tmp |= SSC_TCMR_CKS(data);
	((Ssc *)hw)->SSC_TCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TCMR_CKS_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR &= ~SSC_TCMR_CKS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TCMR_CKS_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR ^= SSC_TCMR_CKS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_read_TCMR_CKS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_CKS_Msk) >> SSC_TCMR_CKS_Pos;
	return tmp;
}

static inline void hri_ssc_set_TCMR_CKO_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR |= SSC_TCMR_CKO(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_get_TCMR_CKO_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_CKO(mask)) >> SSC_TCMR_CKO_Pos;
	return tmp;
}

static inline void hri_ssc_write_TCMR_CKO_bf(const void *const hw, hri_ssc_tcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp &= ~SSC_TCMR_CKO_Msk;
	tmp |= SSC_TCMR_CKO(data);
	((Ssc *)hw)->SSC_TCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TCMR_CKO_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR &= ~SSC_TCMR_CKO(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TCMR_CKO_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR ^= SSC_TCMR_CKO(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_read_TCMR_CKO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_CKO_Msk) >> SSC_TCMR_CKO_Pos;
	return tmp;
}

static inline void hri_ssc_set_TCMR_CKG_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR |= SSC_TCMR_CKG(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_get_TCMR_CKG_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_CKG(mask)) >> SSC_TCMR_CKG_Pos;
	return tmp;
}

static inline void hri_ssc_write_TCMR_CKG_bf(const void *const hw, hri_ssc_tcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp &= ~SSC_TCMR_CKG_Msk;
	tmp |= SSC_TCMR_CKG(data);
	((Ssc *)hw)->SSC_TCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TCMR_CKG_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR &= ~SSC_TCMR_CKG(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TCMR_CKG_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR ^= SSC_TCMR_CKG(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_read_TCMR_CKG_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_CKG_Msk) >> SSC_TCMR_CKG_Pos;
	return tmp;
}

static inline void hri_ssc_set_TCMR_START_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR |= SSC_TCMR_START(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_get_TCMR_START_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_START(mask)) >> SSC_TCMR_START_Pos;
	return tmp;
}

static inline void hri_ssc_write_TCMR_START_bf(const void *const hw, hri_ssc_tcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp &= ~SSC_TCMR_START_Msk;
	tmp |= SSC_TCMR_START(data);
	((Ssc *)hw)->SSC_TCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TCMR_START_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR &= ~SSC_TCMR_START(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TCMR_START_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR ^= SSC_TCMR_START(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_read_TCMR_START_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_START_Msk) >> SSC_TCMR_START_Pos;
	return tmp;
}

static inline void hri_ssc_set_TCMR_STTDLY_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR |= SSC_TCMR_STTDLY(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_get_TCMR_STTDLY_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_STTDLY(mask)) >> SSC_TCMR_STTDLY_Pos;
	return tmp;
}

static inline void hri_ssc_write_TCMR_STTDLY_bf(const void *const hw, hri_ssc_tcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp &= ~SSC_TCMR_STTDLY_Msk;
	tmp |= SSC_TCMR_STTDLY(data);
	((Ssc *)hw)->SSC_TCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TCMR_STTDLY_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR &= ~SSC_TCMR_STTDLY(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TCMR_STTDLY_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR ^= SSC_TCMR_STTDLY(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_read_TCMR_STTDLY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_STTDLY_Msk) >> SSC_TCMR_STTDLY_Pos;
	return tmp;
}

static inline void hri_ssc_set_TCMR_PERIOD_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR |= SSC_TCMR_PERIOD(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_get_TCMR_PERIOD_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_PERIOD(mask)) >> SSC_TCMR_PERIOD_Pos;
	return tmp;
}

static inline void hri_ssc_write_TCMR_PERIOD_bf(const void *const hw, hri_ssc_tcmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp &= ~SSC_TCMR_PERIOD_Msk;
	tmp |= SSC_TCMR_PERIOD(data);
	((Ssc *)hw)->SSC_TCMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TCMR_PERIOD_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR &= ~SSC_TCMR_PERIOD(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TCMR_PERIOD_bf(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR ^= SSC_TCMR_PERIOD(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_read_TCMR_PERIOD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp = (tmp & SSC_TCMR_PERIOD_Msk) >> SSC_TCMR_PERIOD_Pos;
	return tmp;
}

static inline void hri_ssc_set_TCMR_reg(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR |= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_get_TCMR_reg(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TCMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_ssc_write_TCMR_reg(const void *const hw, hri_ssc_tcmr_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TCMR_reg(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR &= ~mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TCMR_reg(const void *const hw, hri_ssc_tcmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TCMR ^= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tcmr_reg_t hri_ssc_read_TCMR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_TCMR;
}

static inline void hri_ssc_set_TFMR_DATDEF_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= SSC_TFMR_DATDEF;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_TFMR_DATDEF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_DATDEF) >> SSC_TFMR_DATDEF_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_TFMR_DATDEF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= ~SSC_TFMR_DATDEF;
	tmp |= value << SSC_TFMR_DATDEF_Pos;
	((Ssc *)hw)->SSC_TFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_DATDEF_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~SSC_TFMR_DATDEF;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_DATDEF_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= SSC_TFMR_DATDEF;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_TFMR_MSBF_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= SSC_TFMR_MSBF;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_TFMR_MSBF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_MSBF) >> SSC_TFMR_MSBF_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_TFMR_MSBF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= ~SSC_TFMR_MSBF;
	tmp |= value << SSC_TFMR_MSBF_Pos;
	((Ssc *)hw)->SSC_TFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_MSBF_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~SSC_TFMR_MSBF;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_MSBF_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= SSC_TFMR_MSBF;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_TFMR_FSDEN_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= SSC_TFMR_FSDEN;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_TFMR_FSDEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_FSDEN) >> SSC_TFMR_FSDEN_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_TFMR_FSDEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= ~SSC_TFMR_FSDEN;
	tmp |= value << SSC_TFMR_FSDEN_Pos;
	((Ssc *)hw)->SSC_TFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_FSDEN_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~SSC_TFMR_FSDEN;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_FSDEN_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= SSC_TFMR_FSDEN;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_TFMR_FSEDGE_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= SSC_TFMR_FSEDGE;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_TFMR_FSEDGE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_FSEDGE) >> SSC_TFMR_FSEDGE_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_TFMR_FSEDGE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= ~SSC_TFMR_FSEDGE;
	tmp |= value << SSC_TFMR_FSEDGE_Pos;
	((Ssc *)hw)->SSC_TFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_FSEDGE_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~SSC_TFMR_FSEDGE;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_FSEDGE_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= SSC_TFMR_FSEDGE;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_TFMR_DATLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= SSC_TFMR_DATLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_get_TFMR_DATLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_DATLEN(mask)) >> SSC_TFMR_DATLEN_Pos;
	return tmp;
}

static inline void hri_ssc_write_TFMR_DATLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= ~SSC_TFMR_DATLEN_Msk;
	tmp |= SSC_TFMR_DATLEN(data);
	((Ssc *)hw)->SSC_TFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_DATLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~SSC_TFMR_DATLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_DATLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= SSC_TFMR_DATLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_read_TFMR_DATLEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_DATLEN_Msk) >> SSC_TFMR_DATLEN_Pos;
	return tmp;
}

static inline void hri_ssc_set_TFMR_DATNB_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= SSC_TFMR_DATNB(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_get_TFMR_DATNB_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_DATNB(mask)) >> SSC_TFMR_DATNB_Pos;
	return tmp;
}

static inline void hri_ssc_write_TFMR_DATNB_bf(const void *const hw, hri_ssc_tfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= ~SSC_TFMR_DATNB_Msk;
	tmp |= SSC_TFMR_DATNB(data);
	((Ssc *)hw)->SSC_TFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_DATNB_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~SSC_TFMR_DATNB(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_DATNB_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= SSC_TFMR_DATNB(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_read_TFMR_DATNB_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_DATNB_Msk) >> SSC_TFMR_DATNB_Pos;
	return tmp;
}

static inline void hri_ssc_set_TFMR_FSLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= SSC_TFMR_FSLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_get_TFMR_FSLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_FSLEN(mask)) >> SSC_TFMR_FSLEN_Pos;
	return tmp;
}

static inline void hri_ssc_write_TFMR_FSLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= ~SSC_TFMR_FSLEN_Msk;
	tmp |= SSC_TFMR_FSLEN(data);
	((Ssc *)hw)->SSC_TFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_FSLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~SSC_TFMR_FSLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_FSLEN_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= SSC_TFMR_FSLEN(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_read_TFMR_FSLEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_FSLEN_Msk) >> SSC_TFMR_FSLEN_Pos;
	return tmp;
}

static inline void hri_ssc_set_TFMR_FSOS_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= SSC_TFMR_FSOS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_get_TFMR_FSOS_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_FSOS(mask)) >> SSC_TFMR_FSOS_Pos;
	return tmp;
}

static inline void hri_ssc_write_TFMR_FSOS_bf(const void *const hw, hri_ssc_tfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= ~SSC_TFMR_FSOS_Msk;
	tmp |= SSC_TFMR_FSOS(data);
	((Ssc *)hw)->SSC_TFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_FSOS_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~SSC_TFMR_FSOS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_FSOS_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= SSC_TFMR_FSOS(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_read_TFMR_FSOS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_FSOS_Msk) >> SSC_TFMR_FSOS_Pos;
	return tmp;
}

static inline void hri_ssc_set_TFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= SSC_TFMR_FSLEN_EXT(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_get_TFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_FSLEN_EXT(mask)) >> SSC_TFMR_FSLEN_EXT_Pos;
	return tmp;
}

static inline void hri_ssc_write_TFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_tfmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= ~SSC_TFMR_FSLEN_EXT_Msk;
	tmp |= SSC_TFMR_FSLEN_EXT(data);
	((Ssc *)hw)->SSC_TFMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~SSC_TFMR_FSLEN_EXT(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_FSLEN_EXT_bf(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= SSC_TFMR_FSLEN_EXT(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_read_TFMR_FSLEN_EXT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp = (tmp & SSC_TFMR_FSLEN_EXT_Msk) >> SSC_TFMR_FSLEN_EXT_Pos;
	return tmp;
}

static inline void hri_ssc_set_TFMR_reg(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR |= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_get_TFMR_reg(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TFMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_ssc_write_TFMR_reg(const void *const hw, hri_ssc_tfmr_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TFMR_reg(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR &= ~mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TFMR_reg(const void *const hw, hri_ssc_tfmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TFMR ^= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tfmr_reg_t hri_ssc_read_TFMR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_TFMR;
}

static inline void hri_ssc_set_TSHR_TSDAT_bf(const void *const hw, hri_ssc_tshr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TSHR |= SSC_TSHR_TSDAT(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tshr_reg_t hri_ssc_get_TSHR_TSDAT_bf(const void *const hw, hri_ssc_tshr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TSHR;
	tmp = (tmp & SSC_TSHR_TSDAT(mask)) >> SSC_TSHR_TSDAT_Pos;
	return tmp;
}

static inline void hri_ssc_write_TSHR_TSDAT_bf(const void *const hw, hri_ssc_tshr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_TSHR;
	tmp &= ~SSC_TSHR_TSDAT_Msk;
	tmp |= SSC_TSHR_TSDAT(data);
	((Ssc *)hw)->SSC_TSHR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TSHR_TSDAT_bf(const void *const hw, hri_ssc_tshr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TSHR &= ~SSC_TSHR_TSDAT(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TSHR_TSDAT_bf(const void *const hw, hri_ssc_tshr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TSHR ^= SSC_TSHR_TSDAT(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tshr_reg_t hri_ssc_read_TSHR_TSDAT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TSHR;
	tmp = (tmp & SSC_TSHR_TSDAT_Msk) >> SSC_TSHR_TSDAT_Pos;
	return tmp;
}

static inline void hri_ssc_set_TSHR_reg(const void *const hw, hri_ssc_tshr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TSHR |= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tshr_reg_t hri_ssc_get_TSHR_reg(const void *const hw, hri_ssc_tshr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_TSHR;
	tmp &= mask;
	return tmp;
}

static inline void hri_ssc_write_TSHR_reg(const void *const hw, hri_ssc_tshr_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TSHR = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_TSHR_reg(const void *const hw, hri_ssc_tshr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TSHR &= ~mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_TSHR_reg(const void *const hw, hri_ssc_tshr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_TSHR ^= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_tshr_reg_t hri_ssc_read_TSHR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_TSHR;
}

static inline void hri_ssc_set_RC0R_CP0_bf(const void *const hw, hri_ssc_rc0r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC0R |= SSC_RC0R_CP0(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rc0r_reg_t hri_ssc_get_RC0R_CP0_bf(const void *const hw, hri_ssc_rc0r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RC0R;
	tmp = (tmp & SSC_RC0R_CP0(mask)) >> SSC_RC0R_CP0_Pos;
	return tmp;
}

static inline void hri_ssc_write_RC0R_CP0_bf(const void *const hw, hri_ssc_rc0r_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RC0R;
	tmp &= ~SSC_RC0R_CP0_Msk;
	tmp |= SSC_RC0R_CP0(data);
	((Ssc *)hw)->SSC_RC0R = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RC0R_CP0_bf(const void *const hw, hri_ssc_rc0r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC0R &= ~SSC_RC0R_CP0(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RC0R_CP0_bf(const void *const hw, hri_ssc_rc0r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC0R ^= SSC_RC0R_CP0(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rc0r_reg_t hri_ssc_read_RC0R_CP0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RC0R;
	tmp = (tmp & SSC_RC0R_CP0_Msk) >> SSC_RC0R_CP0_Pos;
	return tmp;
}

static inline void hri_ssc_set_RC0R_reg(const void *const hw, hri_ssc_rc0r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC0R |= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rc0r_reg_t hri_ssc_get_RC0R_reg(const void *const hw, hri_ssc_rc0r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RC0R;
	tmp &= mask;
	return tmp;
}

static inline void hri_ssc_write_RC0R_reg(const void *const hw, hri_ssc_rc0r_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC0R = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RC0R_reg(const void *const hw, hri_ssc_rc0r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC0R &= ~mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RC0R_reg(const void *const hw, hri_ssc_rc0r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC0R ^= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rc0r_reg_t hri_ssc_read_RC0R_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_RC0R;
}

static inline void hri_ssc_set_RC1R_CP1_bf(const void *const hw, hri_ssc_rc1r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC1R |= SSC_RC1R_CP1(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rc1r_reg_t hri_ssc_get_RC1R_CP1_bf(const void *const hw, hri_ssc_rc1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RC1R;
	tmp = (tmp & SSC_RC1R_CP1(mask)) >> SSC_RC1R_CP1_Pos;
	return tmp;
}

static inline void hri_ssc_write_RC1R_CP1_bf(const void *const hw, hri_ssc_rc1r_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_RC1R;
	tmp &= ~SSC_RC1R_CP1_Msk;
	tmp |= SSC_RC1R_CP1(data);
	((Ssc *)hw)->SSC_RC1R = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RC1R_CP1_bf(const void *const hw, hri_ssc_rc1r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC1R &= ~SSC_RC1R_CP1(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RC1R_CP1_bf(const void *const hw, hri_ssc_rc1r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC1R ^= SSC_RC1R_CP1(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rc1r_reg_t hri_ssc_read_RC1R_CP1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RC1R;
	tmp = (tmp & SSC_RC1R_CP1_Msk) >> SSC_RC1R_CP1_Pos;
	return tmp;
}

static inline void hri_ssc_set_RC1R_reg(const void *const hw, hri_ssc_rc1r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC1R |= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rc1r_reg_t hri_ssc_get_RC1R_reg(const void *const hw, hri_ssc_rc1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_RC1R;
	tmp &= mask;
	return tmp;
}

static inline void hri_ssc_write_RC1R_reg(const void *const hw, hri_ssc_rc1r_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC1R = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_RC1R_reg(const void *const hw, hri_ssc_rc1r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC1R &= ~mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_RC1R_reg(const void *const hw, hri_ssc_rc1r_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_RC1R ^= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_rc1r_reg_t hri_ssc_read_RC1R_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_RC1R;
}

static inline void hri_ssc_set_WPMR_WPEN_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR |= SSC_WPMR_WPEN;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ssc_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_WPMR;
	tmp = (tmp & SSC_WPMR_WPEN) >> SSC_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_ssc_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_WPMR;
	tmp &= ~SSC_WPMR_WPEN;
	tmp |= value << SSC_WPMR_WPEN_Pos;
	((Ssc *)hw)->SSC_WPMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_WPMR_WPEN_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR &= ~SSC_WPMR_WPEN;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_WPMR_WPEN_bit(const void *const hw)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR ^= SSC_WPMR_WPEN;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_set_WPMR_WPKEY_bf(const void *const hw, hri_ssc_wpmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR |= SSC_WPMR_WPKEY(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_wpmr_reg_t hri_ssc_get_WPMR_WPKEY_bf(const void *const hw, hri_ssc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_WPMR;
	tmp = (tmp & SSC_WPMR_WPKEY(mask)) >> SSC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_ssc_write_WPMR_WPKEY_bf(const void *const hw, hri_ssc_wpmr_reg_t data)
{
	uint32_t tmp;
	SSC_CRITICAL_SECTION_ENTER();
	tmp = ((Ssc *)hw)->SSC_WPMR;
	tmp &= ~SSC_WPMR_WPKEY_Msk;
	tmp |= SSC_WPMR_WPKEY(data);
	((Ssc *)hw)->SSC_WPMR = tmp;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_WPMR_WPKEY_bf(const void *const hw, hri_ssc_wpmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR &= ~SSC_WPMR_WPKEY(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_WPMR_WPKEY_bf(const void *const hw, hri_ssc_wpmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR ^= SSC_WPMR_WPKEY(mask);
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_wpmr_reg_t hri_ssc_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_WPMR;
	tmp = (tmp & SSC_WPMR_WPKEY_Msk) >> SSC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_ssc_set_WPMR_reg(const void *const hw, hri_ssc_wpmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR |= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_wpmr_reg_t hri_ssc_get_WPMR_reg(const void *const hw, hri_ssc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ssc *)hw)->SSC_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_ssc_write_WPMR_reg(const void *const hw, hri_ssc_wpmr_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_clear_WPMR_reg(const void *const hw, hri_ssc_wpmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR &= ~mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_toggle_WPMR_reg(const void *const hw, hri_ssc_wpmr_reg_t mask)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_WPMR ^= mask;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ssc_wpmr_reg_t hri_ssc_read_WPMR_reg(const void *const hw)
{
	return ((Ssc *)hw)->SSC_WPMR;
}

static inline void hri_ssc_write_CR_reg(const void *const hw, hri_ssc_cr_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_CR = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ssc_write_THR_reg(const void *const hw, hri_ssc_thr_reg_t data)
{
	SSC_CRITICAL_SECTION_ENTER();
	((Ssc *)hw)->SSC_THR = data;
	SSC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SSC_E70B_H_INCLUDED */
#endif /* _SAME70_SSC_COMPONENT_ */
