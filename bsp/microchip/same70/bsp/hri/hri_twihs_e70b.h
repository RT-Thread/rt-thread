/**
 * \file
 *
 * \brief SAM TWIHS
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

#ifdef _SAME70_TWIHS_COMPONENT_
#ifndef _HRI_TWIHS_E70B_H_INCLUDED_
#define _HRI_TWIHS_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_TWIHS_CRITICAL_SECTIONS)
#define TWIHS_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define TWIHS_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define TWIHS_CRITICAL_SECTION_ENTER()
#define TWIHS_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_twihs_cr_reg_t;
typedef uint32_t hri_twihs_cwgr_reg_t;
typedef uint32_t hri_twihs_filtr_reg_t;
typedef uint32_t hri_twihs_iadr_reg_t;
typedef uint32_t hri_twihs_imr_reg_t;
typedef uint32_t hri_twihs_mmr_reg_t;
typedef uint32_t hri_twihs_rhr_reg_t;
typedef uint32_t hri_twihs_smbtr_reg_t;
typedef uint32_t hri_twihs_smr_reg_t;
typedef uint32_t hri_twihs_sr_reg_t;
typedef uint32_t hri_twihs_swmr_reg_t;
typedef uint32_t hri_twihs_thr_reg_t;
typedef uint32_t hri_twihs_wpmr_reg_t;
typedef uint32_t hri_twihs_wpsr_reg_t;

static inline void hri_twihs_set_IMR_TXCOMP_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_TXCOMP;
}

static inline bool hri_twihs_get_IMR_TXCOMP_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_TXCOMP) >> TWIHS_IMR_TXCOMP_Pos;
}

static inline void hri_twihs_write_IMR_TXCOMP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_TXCOMP;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_TXCOMP;
	}
}

static inline void hri_twihs_clear_IMR_TXCOMP_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_TXCOMP;
}

static inline void hri_twihs_set_IMR_RXRDY_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_RXRDY;
}

static inline bool hri_twihs_get_IMR_RXRDY_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_RXRDY) >> TWIHS_IMR_RXRDY_Pos;
}

static inline void hri_twihs_write_IMR_RXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_RXRDY;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_RXRDY;
	}
}

static inline void hri_twihs_clear_IMR_RXRDY_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_RXRDY;
}

static inline void hri_twihs_set_IMR_TXRDY_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_TXRDY;
}

static inline bool hri_twihs_get_IMR_TXRDY_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_TXRDY) >> TWIHS_IMR_TXRDY_Pos;
}

static inline void hri_twihs_write_IMR_TXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_TXRDY;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_TXRDY;
	}
}

static inline void hri_twihs_clear_IMR_TXRDY_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_TXRDY;
}

static inline void hri_twihs_set_IMR_SVACC_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_SVACC;
}

static inline bool hri_twihs_get_IMR_SVACC_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_SVACC) >> TWIHS_IMR_SVACC_Pos;
}

static inline void hri_twihs_write_IMR_SVACC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_SVACC;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_SVACC;
	}
}

static inline void hri_twihs_clear_IMR_SVACC_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_SVACC;
}

static inline void hri_twihs_set_IMR_GACC_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_GACC;
}

static inline bool hri_twihs_get_IMR_GACC_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_GACC) >> TWIHS_IMR_GACC_Pos;
}

static inline void hri_twihs_write_IMR_GACC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_GACC;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_GACC;
	}
}

static inline void hri_twihs_clear_IMR_GACC_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_GACC;
}

static inline void hri_twihs_set_IMR_OVRE_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_OVRE;
}

static inline bool hri_twihs_get_IMR_OVRE_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_OVRE) >> TWIHS_IMR_OVRE_Pos;
}

static inline void hri_twihs_write_IMR_OVRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_OVRE;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_OVRE;
	}
}

static inline void hri_twihs_clear_IMR_OVRE_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_OVRE;
}

static inline void hri_twihs_set_IMR_UNRE_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_UNRE;
}

static inline bool hri_twihs_get_IMR_UNRE_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_UNRE) >> TWIHS_IMR_UNRE_Pos;
}

static inline void hri_twihs_write_IMR_UNRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_UNRE;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_UNRE;
	}
}

static inline void hri_twihs_clear_IMR_UNRE_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_UNRE;
}

static inline void hri_twihs_set_IMR_NACK_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_NACK;
}

static inline bool hri_twihs_get_IMR_NACK_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_NACK) >> TWIHS_IMR_NACK_Pos;
}

static inline void hri_twihs_write_IMR_NACK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_NACK;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_NACK;
	}
}

static inline void hri_twihs_clear_IMR_NACK_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_NACK;
}

static inline void hri_twihs_set_IMR_ARBLST_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_ARBLST;
}

static inline bool hri_twihs_get_IMR_ARBLST_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_ARBLST) >> TWIHS_IMR_ARBLST_Pos;
}

static inline void hri_twihs_write_IMR_ARBLST_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_ARBLST;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_ARBLST;
	}
}

static inline void hri_twihs_clear_IMR_ARBLST_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_ARBLST;
}

static inline void hri_twihs_set_IMR_SCL_WS_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_SCL_WS;
}

static inline bool hri_twihs_get_IMR_SCL_WS_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_SCL_WS) >> TWIHS_IMR_SCL_WS_Pos;
}

static inline void hri_twihs_write_IMR_SCL_WS_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_SCL_WS;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_SCL_WS;
	}
}

static inline void hri_twihs_clear_IMR_SCL_WS_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_SCL_WS;
}

static inline void hri_twihs_set_IMR_EOSACC_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_EOSACC;
}

static inline bool hri_twihs_get_IMR_EOSACC_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_EOSACC) >> TWIHS_IMR_EOSACC_Pos;
}

static inline void hri_twihs_write_IMR_EOSACC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_EOSACC;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_EOSACC;
	}
}

static inline void hri_twihs_clear_IMR_EOSACC_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_EOSACC;
}

static inline void hri_twihs_set_IMR_MCACK_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_MCACK;
}

static inline bool hri_twihs_get_IMR_MCACK_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_MCACK) >> TWIHS_IMR_MCACK_Pos;
}

static inline void hri_twihs_write_IMR_MCACK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_MCACK;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_MCACK;
	}
}

static inline void hri_twihs_clear_IMR_MCACK_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_MCACK;
}

static inline void hri_twihs_set_IMR_TOUT_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_TOUT;
}

static inline bool hri_twihs_get_IMR_TOUT_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_TOUT) >> TWIHS_IMR_TOUT_Pos;
}

static inline void hri_twihs_write_IMR_TOUT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_TOUT;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_TOUT;
	}
}

static inline void hri_twihs_clear_IMR_TOUT_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_TOUT;
}

static inline void hri_twihs_set_IMR_PECERR_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_PECERR;
}

static inline bool hri_twihs_get_IMR_PECERR_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_PECERR) >> TWIHS_IMR_PECERR_Pos;
}

static inline void hri_twihs_write_IMR_PECERR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_PECERR;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_PECERR;
	}
}

static inline void hri_twihs_clear_IMR_PECERR_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_PECERR;
}

static inline void hri_twihs_set_IMR_SMBDAM_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_SMBDAM;
}

static inline bool hri_twihs_get_IMR_SMBDAM_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_SMBDAM) >> TWIHS_IMR_SMBDAM_Pos;
}

static inline void hri_twihs_write_IMR_SMBDAM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_SMBDAM;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_SMBDAM;
	}
}

static inline void hri_twihs_clear_IMR_SMBDAM_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_SMBDAM;
}

static inline void hri_twihs_set_IMR_SMBHHM_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_SMBHHM;
}

static inline bool hri_twihs_get_IMR_SMBHHM_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_IMR & TWIHS_IMR_SMBHHM) >> TWIHS_IMR_SMBHHM_Pos;
}

static inline void hri_twihs_write_IMR_SMBHHM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_SMBHHM;
	} else {
		((Twihs *)hw)->TWIHS_IER = TWIHS_IMR_SMBHHM;
	}
}

static inline void hri_twihs_clear_IMR_SMBHHM_bit(const void *const hw)
{
	((Twihs *)hw)->TWIHS_IDR = TWIHS_IMR_SMBHHM;
}

static inline void hri_twihs_set_IMR_reg(const void *const hw, hri_twihs_imr_reg_t mask)
{
	((Twihs *)hw)->TWIHS_IER = mask;
}

static inline hri_twihs_imr_reg_t hri_twihs_get_IMR_reg(const void *const hw, hri_twihs_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_twihs_imr_reg_t hri_twihs_read_IMR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_IMR;
}

static inline void hri_twihs_write_IMR_reg(const void *const hw, hri_twihs_imr_reg_t data)
{
	((Twihs *)hw)->TWIHS_IER = data;
	((Twihs *)hw)->TWIHS_IDR = ~data;
}

static inline void hri_twihs_clear_IMR_reg(const void *const hw, hri_twihs_imr_reg_t mask)
{
	((Twihs *)hw)->TWIHS_IDR = mask;
}

static inline bool hri_twihs_get_SR_TXCOMP_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_TXCOMP) > 0;
}

static inline bool hri_twihs_get_SR_RXRDY_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_RXRDY) > 0;
}

static inline bool hri_twihs_get_SR_TXRDY_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_TXRDY) > 0;
}

static inline bool hri_twihs_get_SR_SVREAD_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_SVREAD) > 0;
}

static inline bool hri_twihs_get_SR_SVACC_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_SVACC) > 0;
}

static inline bool hri_twihs_get_SR_GACC_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_GACC) > 0;
}

static inline bool hri_twihs_get_SR_OVRE_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_OVRE) > 0;
}

static inline bool hri_twihs_get_SR_UNRE_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_UNRE) > 0;
}

static inline bool hri_twihs_get_SR_NACK_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_NACK) > 0;
}

static inline bool hri_twihs_get_SR_ARBLST_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_ARBLST) > 0;
}

static inline bool hri_twihs_get_SR_SCLWS_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_SCLWS) > 0;
}

static inline bool hri_twihs_get_SR_EOSACC_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_EOSACC) > 0;
}

static inline bool hri_twihs_get_SR_MCACK_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_MCACK) > 0;
}

static inline bool hri_twihs_get_SR_TOUT_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_TOUT) > 0;
}

static inline bool hri_twihs_get_SR_PECERR_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_PECERR) > 0;
}

static inline bool hri_twihs_get_SR_SMBDAM_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_SMBDAM) > 0;
}

static inline bool hri_twihs_get_SR_SMBHHM_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_SMBHHM) > 0;
}

static inline bool hri_twihs_get_SR_SCL_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_SCL) > 0;
}

static inline bool hri_twihs_get_SR_SDA_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_SR & TWIHS_SR_SDA) > 0;
}

static inline hri_twihs_sr_reg_t hri_twihs_get_SR_reg(const void *const hw, hri_twihs_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_twihs_sr_reg_t hri_twihs_read_SR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_SR;
}

static inline hri_twihs_rhr_reg_t hri_twihs_get_RHR_RXDATA_bf(const void *const hw, hri_twihs_rhr_reg_t mask)
{
	return (((Twihs *)hw)->TWIHS_RHR & TWIHS_RHR_RXDATA(mask)) >> TWIHS_RHR_RXDATA_Pos;
}

static inline hri_twihs_rhr_reg_t hri_twihs_read_RHR_RXDATA_bf(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_RHR & TWIHS_RHR_RXDATA_Msk) >> TWIHS_RHR_RXDATA_Pos;
}

static inline hri_twihs_rhr_reg_t hri_twihs_get_RHR_reg(const void *const hw, hri_twihs_rhr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_RHR;
	tmp &= mask;
	return tmp;
}

static inline hri_twihs_rhr_reg_t hri_twihs_read_RHR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_RHR;
}

static inline bool hri_twihs_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_WPSR & TWIHS_WPSR_WPVS) > 0;
}

static inline hri_twihs_wpsr_reg_t hri_twihs_get_WPSR_WPVSRC_bf(const void *const hw, hri_twihs_wpsr_reg_t mask)
{
	return (((Twihs *)hw)->TWIHS_WPSR & TWIHS_WPSR_WPVSRC(mask)) >> TWIHS_WPSR_WPVSRC_Pos;
}

static inline hri_twihs_wpsr_reg_t hri_twihs_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Twihs *)hw)->TWIHS_WPSR & TWIHS_WPSR_WPVSRC_Msk) >> TWIHS_WPSR_WPVSRC_Pos;
}

static inline hri_twihs_wpsr_reg_t hri_twihs_get_WPSR_reg(const void *const hw, hri_twihs_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_twihs_wpsr_reg_t hri_twihs_read_WPSR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_WPSR;
}

static inline void hri_twihs_set_MMR_MREAD_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR |= TWIHS_MMR_MREAD;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_MMR_MREAD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_MMR;
	tmp = (tmp & TWIHS_MMR_MREAD) >> TWIHS_MMR_MREAD_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_MMR_MREAD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_MMR;
	tmp &= ~TWIHS_MMR_MREAD;
	tmp |= value << TWIHS_MMR_MREAD_Pos;
	((Twihs *)hw)->TWIHS_MMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_MMR_MREAD_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR &= ~TWIHS_MMR_MREAD;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_MMR_MREAD_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR ^= TWIHS_MMR_MREAD;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_MMR_IADRSZ_bf(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR |= TWIHS_MMR_IADRSZ(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_mmr_reg_t hri_twihs_get_MMR_IADRSZ_bf(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_MMR;
	tmp = (tmp & TWIHS_MMR_IADRSZ(mask)) >> TWIHS_MMR_IADRSZ_Pos;
	return tmp;
}

static inline void hri_twihs_write_MMR_IADRSZ_bf(const void *const hw, hri_twihs_mmr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_MMR;
	tmp &= ~TWIHS_MMR_IADRSZ_Msk;
	tmp |= TWIHS_MMR_IADRSZ(data);
	((Twihs *)hw)->TWIHS_MMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_MMR_IADRSZ_bf(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR &= ~TWIHS_MMR_IADRSZ(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_MMR_IADRSZ_bf(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR ^= TWIHS_MMR_IADRSZ(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_mmr_reg_t hri_twihs_read_MMR_IADRSZ_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_MMR;
	tmp = (tmp & TWIHS_MMR_IADRSZ_Msk) >> TWIHS_MMR_IADRSZ_Pos;
	return tmp;
}

static inline void hri_twihs_set_MMR_DADR_bf(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR |= TWIHS_MMR_DADR(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_mmr_reg_t hri_twihs_get_MMR_DADR_bf(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_MMR;
	tmp = (tmp & TWIHS_MMR_DADR(mask)) >> TWIHS_MMR_DADR_Pos;
	return tmp;
}

static inline void hri_twihs_write_MMR_DADR_bf(const void *const hw, hri_twihs_mmr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_MMR;
	tmp &= ~TWIHS_MMR_DADR_Msk;
	tmp |= TWIHS_MMR_DADR(data);
	((Twihs *)hw)->TWIHS_MMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_MMR_DADR_bf(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR &= ~TWIHS_MMR_DADR(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_MMR_DADR_bf(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR ^= TWIHS_MMR_DADR(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_mmr_reg_t hri_twihs_read_MMR_DADR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_MMR;
	tmp = (tmp & TWIHS_MMR_DADR_Msk) >> TWIHS_MMR_DADR_Pos;
	return tmp;
}

static inline void hri_twihs_set_MMR_reg(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR |= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_mmr_reg_t hri_twihs_get_MMR_reg(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_MMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_twihs_write_MMR_reg(const void *const hw, hri_twihs_mmr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_MMR_reg(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR &= ~mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_MMR_reg(const void *const hw, hri_twihs_mmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_MMR ^= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_mmr_reg_t hri_twihs_read_MMR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_MMR;
}

static inline void hri_twihs_set_SMR_NACKEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_NACKEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_SMR_NACKEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_NACKEN) >> TWIHS_SMR_NACKEN_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_SMR_NACKEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_NACKEN;
	tmp |= value << TWIHS_SMR_NACKEN_Pos;
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_NACKEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_NACKEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_NACKEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_NACKEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_SMR_SMDA_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_SMDA;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_SMR_SMDA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_SMDA) >> TWIHS_SMR_SMDA_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_SMR_SMDA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_SMDA;
	tmp |= value << TWIHS_SMR_SMDA_Pos;
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_SMDA_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_SMDA;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_SMDA_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_SMDA;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_SMR_SMHH_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_SMHH;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_SMR_SMHH_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_SMHH) >> TWIHS_SMR_SMHH_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_SMR_SMHH_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_SMHH;
	tmp |= value << TWIHS_SMR_SMHH_Pos;
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_SMHH_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_SMHH;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_SMHH_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_SMHH;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_SMR_SCLWSDIS_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_SCLWSDIS;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_SMR_SCLWSDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_SCLWSDIS) >> TWIHS_SMR_SCLWSDIS_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_SMR_SCLWSDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_SCLWSDIS;
	tmp |= value << TWIHS_SMR_SCLWSDIS_Pos;
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_SCLWSDIS_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_SCLWSDIS;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_SCLWSDIS_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_SCLWSDIS;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_SMR_SADR1EN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_SADR1EN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_SMR_SADR1EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_SADR1EN) >> TWIHS_SMR_SADR1EN_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_SMR_SADR1EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_SADR1EN;
	tmp |= value << TWIHS_SMR_SADR1EN_Pos;
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_SADR1EN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_SADR1EN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_SADR1EN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_SADR1EN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_SMR_SADR2EN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_SADR2EN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_SMR_SADR2EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_SADR2EN) >> TWIHS_SMR_SADR2EN_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_SMR_SADR2EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_SADR2EN;
	tmp |= value << TWIHS_SMR_SADR2EN_Pos;
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_SADR2EN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_SADR2EN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_SADR2EN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_SADR2EN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_SMR_SADR3EN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_SADR3EN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_SMR_SADR3EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_SADR3EN) >> TWIHS_SMR_SADR3EN_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_SMR_SADR3EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_SADR3EN;
	tmp |= value << TWIHS_SMR_SADR3EN_Pos;
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_SADR3EN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_SADR3EN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_SADR3EN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_SADR3EN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_SMR_DATAMEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_DATAMEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_SMR_DATAMEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_DATAMEN) >> TWIHS_SMR_DATAMEN_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_SMR_DATAMEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_DATAMEN;
	tmp |= value << TWIHS_SMR_DATAMEN_Pos;
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_DATAMEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_DATAMEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_DATAMEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_DATAMEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_SMR_MASK_bf(const void *const hw, hri_twihs_smr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_MASK(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smr_reg_t hri_twihs_get_SMR_MASK_bf(const void *const hw, hri_twihs_smr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_MASK(mask)) >> TWIHS_SMR_MASK_Pos;
	return tmp;
}

static inline void hri_twihs_write_SMR_MASK_bf(const void *const hw, hri_twihs_smr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_MASK_Msk;
	tmp |= TWIHS_SMR_MASK(data);
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_MASK_bf(const void *const hw, hri_twihs_smr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_MASK(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_MASK_bf(const void *const hw, hri_twihs_smr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_MASK(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smr_reg_t hri_twihs_read_SMR_MASK_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_MASK_Msk) >> TWIHS_SMR_MASK_Pos;
	return tmp;
}

static inline void hri_twihs_set_SMR_SADR_bf(const void *const hw, hri_twihs_smr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= TWIHS_SMR_SADR(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smr_reg_t hri_twihs_get_SMR_SADR_bf(const void *const hw, hri_twihs_smr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_SADR(mask)) >> TWIHS_SMR_SADR_Pos;
	return tmp;
}

static inline void hri_twihs_write_SMR_SADR_bf(const void *const hw, hri_twihs_smr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= ~TWIHS_SMR_SADR_Msk;
	tmp |= TWIHS_SMR_SADR(data);
	((Twihs *)hw)->TWIHS_SMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_SADR_bf(const void *const hw, hri_twihs_smr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~TWIHS_SMR_SADR(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_SADR_bf(const void *const hw, hri_twihs_smr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= TWIHS_SMR_SADR(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smr_reg_t hri_twihs_read_SMR_SADR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp = (tmp & TWIHS_SMR_SADR_Msk) >> TWIHS_SMR_SADR_Pos;
	return tmp;
}

static inline void hri_twihs_set_SMR_reg(const void *const hw, hri_twihs_smr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR |= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smr_reg_t hri_twihs_get_SMR_reg(const void *const hw, hri_twihs_smr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_twihs_write_SMR_reg(const void *const hw, hri_twihs_smr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMR_reg(const void *const hw, hri_twihs_smr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR &= ~mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMR_reg(const void *const hw, hri_twihs_smr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMR ^= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smr_reg_t hri_twihs_read_SMR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_SMR;
}

static inline void hri_twihs_set_IADR_IADR_bf(const void *const hw, hri_twihs_iadr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_IADR |= TWIHS_IADR_IADR(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_iadr_reg_t hri_twihs_get_IADR_IADR_bf(const void *const hw, hri_twihs_iadr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_IADR;
	tmp = (tmp & TWIHS_IADR_IADR(mask)) >> TWIHS_IADR_IADR_Pos;
	return tmp;
}

static inline void hri_twihs_write_IADR_IADR_bf(const void *const hw, hri_twihs_iadr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_IADR;
	tmp &= ~TWIHS_IADR_IADR_Msk;
	tmp |= TWIHS_IADR_IADR(data);
	((Twihs *)hw)->TWIHS_IADR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_IADR_IADR_bf(const void *const hw, hri_twihs_iadr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_IADR &= ~TWIHS_IADR_IADR(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_IADR_IADR_bf(const void *const hw, hri_twihs_iadr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_IADR ^= TWIHS_IADR_IADR(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_iadr_reg_t hri_twihs_read_IADR_IADR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_IADR;
	tmp = (tmp & TWIHS_IADR_IADR_Msk) >> TWIHS_IADR_IADR_Pos;
	return tmp;
}

static inline void hri_twihs_set_IADR_reg(const void *const hw, hri_twihs_iadr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_IADR |= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_iadr_reg_t hri_twihs_get_IADR_reg(const void *const hw, hri_twihs_iadr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_IADR;
	tmp &= mask;
	return tmp;
}

static inline void hri_twihs_write_IADR_reg(const void *const hw, hri_twihs_iadr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_IADR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_IADR_reg(const void *const hw, hri_twihs_iadr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_IADR &= ~mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_IADR_reg(const void *const hw, hri_twihs_iadr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_IADR ^= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_iadr_reg_t hri_twihs_read_IADR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_IADR;
}

static inline void hri_twihs_set_CWGR_CLDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR |= TWIHS_CWGR_CLDIV(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_get_CWGR_CLDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp = (tmp & TWIHS_CWGR_CLDIV(mask)) >> TWIHS_CWGR_CLDIV_Pos;
	return tmp;
}

static inline void hri_twihs_write_CWGR_CLDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp &= ~TWIHS_CWGR_CLDIV_Msk;
	tmp |= TWIHS_CWGR_CLDIV(data);
	((Twihs *)hw)->TWIHS_CWGR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_CWGR_CLDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR &= ~TWIHS_CWGR_CLDIV(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_CWGR_CLDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR ^= TWIHS_CWGR_CLDIV(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_read_CWGR_CLDIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp = (tmp & TWIHS_CWGR_CLDIV_Msk) >> TWIHS_CWGR_CLDIV_Pos;
	return tmp;
}

static inline void hri_twihs_set_CWGR_CHDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR |= TWIHS_CWGR_CHDIV(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_get_CWGR_CHDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp = (tmp & TWIHS_CWGR_CHDIV(mask)) >> TWIHS_CWGR_CHDIV_Pos;
	return tmp;
}

static inline void hri_twihs_write_CWGR_CHDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp &= ~TWIHS_CWGR_CHDIV_Msk;
	tmp |= TWIHS_CWGR_CHDIV(data);
	((Twihs *)hw)->TWIHS_CWGR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_CWGR_CHDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR &= ~TWIHS_CWGR_CHDIV(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_CWGR_CHDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR ^= TWIHS_CWGR_CHDIV(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_read_CWGR_CHDIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp = (tmp & TWIHS_CWGR_CHDIV_Msk) >> TWIHS_CWGR_CHDIV_Pos;
	return tmp;
}

static inline void hri_twihs_set_CWGR_CKDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR |= TWIHS_CWGR_CKDIV(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_get_CWGR_CKDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp = (tmp & TWIHS_CWGR_CKDIV(mask)) >> TWIHS_CWGR_CKDIV_Pos;
	return tmp;
}

static inline void hri_twihs_write_CWGR_CKDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp &= ~TWIHS_CWGR_CKDIV_Msk;
	tmp |= TWIHS_CWGR_CKDIV(data);
	((Twihs *)hw)->TWIHS_CWGR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_CWGR_CKDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR &= ~TWIHS_CWGR_CKDIV(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_CWGR_CKDIV_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR ^= TWIHS_CWGR_CKDIV(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_read_CWGR_CKDIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp = (tmp & TWIHS_CWGR_CKDIV_Msk) >> TWIHS_CWGR_CKDIV_Pos;
	return tmp;
}

static inline void hri_twihs_set_CWGR_HOLD_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR |= TWIHS_CWGR_HOLD(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_get_CWGR_HOLD_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp = (tmp & TWIHS_CWGR_HOLD(mask)) >> TWIHS_CWGR_HOLD_Pos;
	return tmp;
}

static inline void hri_twihs_write_CWGR_HOLD_bf(const void *const hw, hri_twihs_cwgr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp &= ~TWIHS_CWGR_HOLD_Msk;
	tmp |= TWIHS_CWGR_HOLD(data);
	((Twihs *)hw)->TWIHS_CWGR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_CWGR_HOLD_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR &= ~TWIHS_CWGR_HOLD(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_CWGR_HOLD_bf(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR ^= TWIHS_CWGR_HOLD(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_read_CWGR_HOLD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp = (tmp & TWIHS_CWGR_HOLD_Msk) >> TWIHS_CWGR_HOLD_Pos;
	return tmp;
}

static inline void hri_twihs_set_CWGR_reg(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR |= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_get_CWGR_reg(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_CWGR;
	tmp &= mask;
	return tmp;
}

static inline void hri_twihs_write_CWGR_reg(const void *const hw, hri_twihs_cwgr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_CWGR_reg(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR &= ~mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_CWGR_reg(const void *const hw, hri_twihs_cwgr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CWGR ^= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_cwgr_reg_t hri_twihs_read_CWGR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_CWGR;
}

static inline void hri_twihs_set_SMBTR_PRESC_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR |= TWIHS_SMBTR_PRESC(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_get_SMBTR_PRESC_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp = (tmp & TWIHS_SMBTR_PRESC(mask)) >> TWIHS_SMBTR_PRESC_Pos;
	return tmp;
}

static inline void hri_twihs_write_SMBTR_PRESC_bf(const void *const hw, hri_twihs_smbtr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp &= ~TWIHS_SMBTR_PRESC_Msk;
	tmp |= TWIHS_SMBTR_PRESC(data);
	((Twihs *)hw)->TWIHS_SMBTR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMBTR_PRESC_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR &= ~TWIHS_SMBTR_PRESC(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMBTR_PRESC_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR ^= TWIHS_SMBTR_PRESC(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_read_SMBTR_PRESC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp = (tmp & TWIHS_SMBTR_PRESC_Msk) >> TWIHS_SMBTR_PRESC_Pos;
	return tmp;
}

static inline void hri_twihs_set_SMBTR_TLOWS_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR |= TWIHS_SMBTR_TLOWS(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_get_SMBTR_TLOWS_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp = (tmp & TWIHS_SMBTR_TLOWS(mask)) >> TWIHS_SMBTR_TLOWS_Pos;
	return tmp;
}

static inline void hri_twihs_write_SMBTR_TLOWS_bf(const void *const hw, hri_twihs_smbtr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp &= ~TWIHS_SMBTR_TLOWS_Msk;
	tmp |= TWIHS_SMBTR_TLOWS(data);
	((Twihs *)hw)->TWIHS_SMBTR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMBTR_TLOWS_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR &= ~TWIHS_SMBTR_TLOWS(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMBTR_TLOWS_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR ^= TWIHS_SMBTR_TLOWS(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_read_SMBTR_TLOWS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp = (tmp & TWIHS_SMBTR_TLOWS_Msk) >> TWIHS_SMBTR_TLOWS_Pos;
	return tmp;
}

static inline void hri_twihs_set_SMBTR_TLOWM_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR |= TWIHS_SMBTR_TLOWM(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_get_SMBTR_TLOWM_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp = (tmp & TWIHS_SMBTR_TLOWM(mask)) >> TWIHS_SMBTR_TLOWM_Pos;
	return tmp;
}

static inline void hri_twihs_write_SMBTR_TLOWM_bf(const void *const hw, hri_twihs_smbtr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp &= ~TWIHS_SMBTR_TLOWM_Msk;
	tmp |= TWIHS_SMBTR_TLOWM(data);
	((Twihs *)hw)->TWIHS_SMBTR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMBTR_TLOWM_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR &= ~TWIHS_SMBTR_TLOWM(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMBTR_TLOWM_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR ^= TWIHS_SMBTR_TLOWM(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_read_SMBTR_TLOWM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp = (tmp & TWIHS_SMBTR_TLOWM_Msk) >> TWIHS_SMBTR_TLOWM_Pos;
	return tmp;
}

static inline void hri_twihs_set_SMBTR_THMAX_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR |= TWIHS_SMBTR_THMAX(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_get_SMBTR_THMAX_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp = (tmp & TWIHS_SMBTR_THMAX(mask)) >> TWIHS_SMBTR_THMAX_Pos;
	return tmp;
}

static inline void hri_twihs_write_SMBTR_THMAX_bf(const void *const hw, hri_twihs_smbtr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp &= ~TWIHS_SMBTR_THMAX_Msk;
	tmp |= TWIHS_SMBTR_THMAX(data);
	((Twihs *)hw)->TWIHS_SMBTR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMBTR_THMAX_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR &= ~TWIHS_SMBTR_THMAX(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMBTR_THMAX_bf(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR ^= TWIHS_SMBTR_THMAX(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_read_SMBTR_THMAX_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp = (tmp & TWIHS_SMBTR_THMAX_Msk) >> TWIHS_SMBTR_THMAX_Pos;
	return tmp;
}

static inline void hri_twihs_set_SMBTR_reg(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR |= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_get_SMBTR_reg(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SMBTR;
	tmp &= mask;
	return tmp;
}

static inline void hri_twihs_write_SMBTR_reg(const void *const hw, hri_twihs_smbtr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SMBTR_reg(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR &= ~mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SMBTR_reg(const void *const hw, hri_twihs_smbtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SMBTR ^= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_smbtr_reg_t hri_twihs_read_SMBTR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_SMBTR;
}

static inline void hri_twihs_set_FILTR_FILT_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR |= TWIHS_FILTR_FILT;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_FILTR_FILT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp = (tmp & TWIHS_FILTR_FILT) >> TWIHS_FILTR_FILT_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_FILTR_FILT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp &= ~TWIHS_FILTR_FILT;
	tmp |= value << TWIHS_FILTR_FILT_Pos;
	((Twihs *)hw)->TWIHS_FILTR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_FILTR_FILT_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR &= ~TWIHS_FILTR_FILT;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_FILTR_FILT_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR ^= TWIHS_FILTR_FILT;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_FILTR_PADFEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR |= TWIHS_FILTR_PADFEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_FILTR_PADFEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp = (tmp & TWIHS_FILTR_PADFEN) >> TWIHS_FILTR_PADFEN_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_FILTR_PADFEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp &= ~TWIHS_FILTR_PADFEN;
	tmp |= value << TWIHS_FILTR_PADFEN_Pos;
	((Twihs *)hw)->TWIHS_FILTR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_FILTR_PADFEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR &= ~TWIHS_FILTR_PADFEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_FILTR_PADFEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR ^= TWIHS_FILTR_PADFEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_FILTR_PADFCFG_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR |= TWIHS_FILTR_PADFCFG;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_FILTR_PADFCFG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp = (tmp & TWIHS_FILTR_PADFCFG) >> TWIHS_FILTR_PADFCFG_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_FILTR_PADFCFG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp &= ~TWIHS_FILTR_PADFCFG;
	tmp |= value << TWIHS_FILTR_PADFCFG_Pos;
	((Twihs *)hw)->TWIHS_FILTR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_FILTR_PADFCFG_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR &= ~TWIHS_FILTR_PADFCFG;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_FILTR_PADFCFG_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR ^= TWIHS_FILTR_PADFCFG;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_FILTR_THRES_bf(const void *const hw, hri_twihs_filtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR |= TWIHS_FILTR_THRES(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_filtr_reg_t hri_twihs_get_FILTR_THRES_bf(const void *const hw, hri_twihs_filtr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp = (tmp & TWIHS_FILTR_THRES(mask)) >> TWIHS_FILTR_THRES_Pos;
	return tmp;
}

static inline void hri_twihs_write_FILTR_THRES_bf(const void *const hw, hri_twihs_filtr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp &= ~TWIHS_FILTR_THRES_Msk;
	tmp |= TWIHS_FILTR_THRES(data);
	((Twihs *)hw)->TWIHS_FILTR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_FILTR_THRES_bf(const void *const hw, hri_twihs_filtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR &= ~TWIHS_FILTR_THRES(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_FILTR_THRES_bf(const void *const hw, hri_twihs_filtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR ^= TWIHS_FILTR_THRES(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_filtr_reg_t hri_twihs_read_FILTR_THRES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp = (tmp & TWIHS_FILTR_THRES_Msk) >> TWIHS_FILTR_THRES_Pos;
	return tmp;
}

static inline void hri_twihs_set_FILTR_reg(const void *const hw, hri_twihs_filtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR |= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_filtr_reg_t hri_twihs_get_FILTR_reg(const void *const hw, hri_twihs_filtr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_FILTR;
	tmp &= mask;
	return tmp;
}

static inline void hri_twihs_write_FILTR_reg(const void *const hw, hri_twihs_filtr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_FILTR_reg(const void *const hw, hri_twihs_filtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR &= ~mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_FILTR_reg(const void *const hw, hri_twihs_filtr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_FILTR ^= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_filtr_reg_t hri_twihs_read_FILTR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_FILTR;
}

static inline void hri_twihs_set_SWMR_SADR1_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR |= TWIHS_SWMR_SADR1(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_get_SWMR_SADR1_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp = (tmp & TWIHS_SWMR_SADR1(mask)) >> TWIHS_SWMR_SADR1_Pos;
	return tmp;
}

static inline void hri_twihs_write_SWMR_SADR1_bf(const void *const hw, hri_twihs_swmr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp &= ~TWIHS_SWMR_SADR1_Msk;
	tmp |= TWIHS_SWMR_SADR1(data);
	((Twihs *)hw)->TWIHS_SWMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SWMR_SADR1_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR &= ~TWIHS_SWMR_SADR1(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SWMR_SADR1_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR ^= TWIHS_SWMR_SADR1(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_read_SWMR_SADR1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp = (tmp & TWIHS_SWMR_SADR1_Msk) >> TWIHS_SWMR_SADR1_Pos;
	return tmp;
}

static inline void hri_twihs_set_SWMR_SADR2_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR |= TWIHS_SWMR_SADR2(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_get_SWMR_SADR2_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp = (tmp & TWIHS_SWMR_SADR2(mask)) >> TWIHS_SWMR_SADR2_Pos;
	return tmp;
}

static inline void hri_twihs_write_SWMR_SADR2_bf(const void *const hw, hri_twihs_swmr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp &= ~TWIHS_SWMR_SADR2_Msk;
	tmp |= TWIHS_SWMR_SADR2(data);
	((Twihs *)hw)->TWIHS_SWMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SWMR_SADR2_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR &= ~TWIHS_SWMR_SADR2(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SWMR_SADR2_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR ^= TWIHS_SWMR_SADR2(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_read_SWMR_SADR2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp = (tmp & TWIHS_SWMR_SADR2_Msk) >> TWIHS_SWMR_SADR2_Pos;
	return tmp;
}

static inline void hri_twihs_set_SWMR_SADR3_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR |= TWIHS_SWMR_SADR3(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_get_SWMR_SADR3_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp = (tmp & TWIHS_SWMR_SADR3(mask)) >> TWIHS_SWMR_SADR3_Pos;
	return tmp;
}

static inline void hri_twihs_write_SWMR_SADR3_bf(const void *const hw, hri_twihs_swmr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp &= ~TWIHS_SWMR_SADR3_Msk;
	tmp |= TWIHS_SWMR_SADR3(data);
	((Twihs *)hw)->TWIHS_SWMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SWMR_SADR3_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR &= ~TWIHS_SWMR_SADR3(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SWMR_SADR3_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR ^= TWIHS_SWMR_SADR3(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_read_SWMR_SADR3_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp = (tmp & TWIHS_SWMR_SADR3_Msk) >> TWIHS_SWMR_SADR3_Pos;
	return tmp;
}

static inline void hri_twihs_set_SWMR_DATAM_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR |= TWIHS_SWMR_DATAM(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_get_SWMR_DATAM_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp = (tmp & TWIHS_SWMR_DATAM(mask)) >> TWIHS_SWMR_DATAM_Pos;
	return tmp;
}

static inline void hri_twihs_write_SWMR_DATAM_bf(const void *const hw, hri_twihs_swmr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp &= ~TWIHS_SWMR_DATAM_Msk;
	tmp |= TWIHS_SWMR_DATAM(data);
	((Twihs *)hw)->TWIHS_SWMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SWMR_DATAM_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR &= ~TWIHS_SWMR_DATAM(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SWMR_DATAM_bf(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR ^= TWIHS_SWMR_DATAM(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_read_SWMR_DATAM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp = (tmp & TWIHS_SWMR_DATAM_Msk) >> TWIHS_SWMR_DATAM_Pos;
	return tmp;
}

static inline void hri_twihs_set_SWMR_reg(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR |= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_get_SWMR_reg(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_SWMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_twihs_write_SWMR_reg(const void *const hw, hri_twihs_swmr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_SWMR_reg(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR &= ~mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_SWMR_reg(const void *const hw, hri_twihs_swmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_SWMR ^= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_swmr_reg_t hri_twihs_read_SWMR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_SWMR;
}

static inline void hri_twihs_set_WPMR_WPEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR |= TWIHS_WPMR_WPEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_twihs_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_WPMR;
	tmp = (tmp & TWIHS_WPMR_WPEN) >> TWIHS_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_twihs_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_WPMR;
	tmp &= ~TWIHS_WPMR_WPEN;
	tmp |= value << TWIHS_WPMR_WPEN_Pos;
	((Twihs *)hw)->TWIHS_WPMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_WPMR_WPEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR &= ~TWIHS_WPMR_WPEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_WPMR_WPEN_bit(const void *const hw)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR ^= TWIHS_WPMR_WPEN;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_set_WPMR_WPKEY_bf(const void *const hw, hri_twihs_wpmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR |= TWIHS_WPMR_WPKEY(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_wpmr_reg_t hri_twihs_get_WPMR_WPKEY_bf(const void *const hw, hri_twihs_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_WPMR;
	tmp = (tmp & TWIHS_WPMR_WPKEY(mask)) >> TWIHS_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_twihs_write_WPMR_WPKEY_bf(const void *const hw, hri_twihs_wpmr_reg_t data)
{
	uint32_t tmp;
	TWIHS_CRITICAL_SECTION_ENTER();
	tmp = ((Twihs *)hw)->TWIHS_WPMR;
	tmp &= ~TWIHS_WPMR_WPKEY_Msk;
	tmp |= TWIHS_WPMR_WPKEY(data);
	((Twihs *)hw)->TWIHS_WPMR = tmp;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_WPMR_WPKEY_bf(const void *const hw, hri_twihs_wpmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR &= ~TWIHS_WPMR_WPKEY(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_WPMR_WPKEY_bf(const void *const hw, hri_twihs_wpmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR ^= TWIHS_WPMR_WPKEY(mask);
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_wpmr_reg_t hri_twihs_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_WPMR;
	tmp = (tmp & TWIHS_WPMR_WPKEY_Msk) >> TWIHS_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_twihs_set_WPMR_reg(const void *const hw, hri_twihs_wpmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR |= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_wpmr_reg_t hri_twihs_get_WPMR_reg(const void *const hw, hri_twihs_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Twihs *)hw)->TWIHS_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_twihs_write_WPMR_reg(const void *const hw, hri_twihs_wpmr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_clear_WPMR_reg(const void *const hw, hri_twihs_wpmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR &= ~mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_toggle_WPMR_reg(const void *const hw, hri_twihs_wpmr_reg_t mask)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_WPMR ^= mask;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_twihs_wpmr_reg_t hri_twihs_read_WPMR_reg(const void *const hw)
{
	return ((Twihs *)hw)->TWIHS_WPMR;
}

static inline void hri_twihs_write_CR_reg(const void *const hw, hri_twihs_cr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_CR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_twihs_write_THR_reg(const void *const hw, hri_twihs_thr_reg_t data)
{
	TWIHS_CRITICAL_SECTION_ENTER();
	((Twihs *)hw)->TWIHS_THR = data;
	TWIHS_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_TWIHS_E70B_H_INCLUDED */
#endif /* _SAME70_TWIHS_COMPONENT_ */
