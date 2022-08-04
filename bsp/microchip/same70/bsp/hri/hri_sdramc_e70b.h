/**
 * \file
 *
 * \brief SAM SDRAMC
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

#ifdef _SAME70_SDRAMC_COMPONENT_
#ifndef _HRI_SDRAMC_E70B_H_INCLUDED_
#define _HRI_SDRAMC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_SDRAMC_CRITICAL_SECTIONS)
#define SDRAMC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define SDRAMC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define SDRAMC_CRITICAL_SECTION_ENTER()
#define SDRAMC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_sdramc_cfr1_reg_t;
typedef uint32_t hri_sdramc_cr_reg_t;
typedef uint32_t hri_sdramc_imr_reg_t;
typedef uint32_t hri_sdramc_isr_reg_t;
typedef uint32_t hri_sdramc_lpr_reg_t;
typedef uint32_t hri_sdramc_mdr_reg_t;
typedef uint32_t hri_sdramc_mr_reg_t;
typedef uint32_t hri_sdramc_ocms_key1_reg_t;
typedef uint32_t hri_sdramc_ocms_key2_reg_t;
typedef uint32_t hri_sdramc_ocms_reg_t;
typedef uint32_t hri_sdramc_tr_reg_t;

static inline bool hri_sdramc_get_ISR_RES_bit(const void *const hw)
{
	return (((Sdramc *)hw)->SDRAMC_ISR & SDRAMC_ISR_RES) >> SDRAMC_ISR_RES_Pos;
}

static inline hri_sdramc_isr_reg_t hri_sdramc_get_ISR_reg(const void *const hw, hri_sdramc_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_sdramc_isr_reg_t hri_sdramc_read_ISR_reg(const void *const hw)
{
	return ((Sdramc *)hw)->SDRAMC_ISR;
}

static inline void hri_sdramc_set_IMR_RES_bit(const void *const hw)
{
	((Sdramc *)hw)->SDRAMC_IER = SDRAMC_IMR_RES;
}

static inline bool hri_sdramc_get_IMR_RES_bit(const void *const hw)
{
	return (((Sdramc *)hw)->SDRAMC_IMR & SDRAMC_IMR_RES) >> SDRAMC_IMR_RES_Pos;
}

static inline void hri_sdramc_write_IMR_RES_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Sdramc *)hw)->SDRAMC_IDR = SDRAMC_IMR_RES;
	} else {
		((Sdramc *)hw)->SDRAMC_IER = SDRAMC_IMR_RES;
	}
}

static inline void hri_sdramc_clear_IMR_RES_bit(const void *const hw)
{
	((Sdramc *)hw)->SDRAMC_IDR = SDRAMC_IMR_RES;
}

static inline void hri_sdramc_set_IMR_reg(const void *const hw, hri_sdramc_imr_reg_t mask)
{
	((Sdramc *)hw)->SDRAMC_IER = mask;
}

static inline hri_sdramc_imr_reg_t hri_sdramc_get_IMR_reg(const void *const hw, hri_sdramc_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_sdramc_imr_reg_t hri_sdramc_read_IMR_reg(const void *const hw)
{
	return ((Sdramc *)hw)->SDRAMC_IMR;
}

static inline void hri_sdramc_write_IMR_reg(const void *const hw, hri_sdramc_imr_reg_t data)
{
	((Sdramc *)hw)->SDRAMC_IER = data;
	((Sdramc *)hw)->SDRAMC_IDR = ~data;
}

static inline void hri_sdramc_clear_IMR_reg(const void *const hw, hri_sdramc_imr_reg_t mask)
{
	((Sdramc *)hw)->SDRAMC_IDR = mask;
}

static inline void hri_sdramc_set_MR_MODE_bf(const void *const hw, hri_sdramc_mr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MR |= SDRAMC_MR_MODE(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_mr_reg_t hri_sdramc_get_MR_MODE_bf(const void *const hw, hri_sdramc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_MR;
	tmp = (tmp & SDRAMC_MR_MODE(mask)) >> SDRAMC_MR_MODE_Pos;
	return tmp;
}

static inline void hri_sdramc_write_MR_MODE_bf(const void *const hw, hri_sdramc_mr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_MR;
	tmp &= ~SDRAMC_MR_MODE_Msk;
	tmp |= SDRAMC_MR_MODE(data);
	((Sdramc *)hw)->SDRAMC_MR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_MR_MODE_bf(const void *const hw, hri_sdramc_mr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MR &= ~SDRAMC_MR_MODE(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_MR_MODE_bf(const void *const hw, hri_sdramc_mr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MR ^= SDRAMC_MR_MODE(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_mr_reg_t hri_sdramc_read_MR_MODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_MR;
	tmp = (tmp & SDRAMC_MR_MODE_Msk) >> SDRAMC_MR_MODE_Pos;
	return tmp;
}

static inline void hri_sdramc_set_MR_reg(const void *const hw, hri_sdramc_mr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MR |= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_mr_reg_t hri_sdramc_get_MR_reg(const void *const hw, hri_sdramc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdramc_write_MR_reg(const void *const hw, hri_sdramc_mr_reg_t data)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MR = data;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_MR_reg(const void *const hw, hri_sdramc_mr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MR &= ~mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_MR_reg(const void *const hw, hri_sdramc_mr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MR ^= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_mr_reg_t hri_sdramc_read_MR_reg(const void *const hw)
{
	return ((Sdramc *)hw)->SDRAMC_MR;
}

static inline void hri_sdramc_set_TR_COUNT_bf(const void *const hw, hri_sdramc_tr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_TR |= SDRAMC_TR_COUNT(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_tr_reg_t hri_sdramc_get_TR_COUNT_bf(const void *const hw, hri_sdramc_tr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_TR;
	tmp = (tmp & SDRAMC_TR_COUNT(mask)) >> SDRAMC_TR_COUNT_Pos;
	return tmp;
}

static inline void hri_sdramc_write_TR_COUNT_bf(const void *const hw, hri_sdramc_tr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_TR;
	tmp &= ~SDRAMC_TR_COUNT_Msk;
	tmp |= SDRAMC_TR_COUNT(data);
	((Sdramc *)hw)->SDRAMC_TR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_TR_COUNT_bf(const void *const hw, hri_sdramc_tr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_TR &= ~SDRAMC_TR_COUNT(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_TR_COUNT_bf(const void *const hw, hri_sdramc_tr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_TR ^= SDRAMC_TR_COUNT(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_tr_reg_t hri_sdramc_read_TR_COUNT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_TR;
	tmp = (tmp & SDRAMC_TR_COUNT_Msk) >> SDRAMC_TR_COUNT_Pos;
	return tmp;
}

static inline void hri_sdramc_set_TR_reg(const void *const hw, hri_sdramc_tr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_TR |= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_tr_reg_t hri_sdramc_get_TR_reg(const void *const hw, hri_sdramc_tr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_TR;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdramc_write_TR_reg(const void *const hw, hri_sdramc_tr_reg_t data)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_TR = data;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_TR_reg(const void *const hw, hri_sdramc_tr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_TR &= ~mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_TR_reg(const void *const hw, hri_sdramc_tr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_TR ^= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_tr_reg_t hri_sdramc_read_TR_reg(const void *const hw)
{
	return ((Sdramc *)hw)->SDRAMC_TR;
}

static inline void hri_sdramc_set_CR_NB_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_NB;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdramc_get_CR_NB_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_NB) >> SDRAMC_CR_NB_Pos;
	return (bool)tmp;
}

static inline void hri_sdramc_write_CR_NB_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_NB;
	tmp |= value << SDRAMC_CR_NB_Pos;
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_NB_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_NB;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_NB_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_NB;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_set_CR_DBW_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_DBW;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdramc_get_CR_DBW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_DBW) >> SDRAMC_CR_DBW_Pos;
	return (bool)tmp;
}

static inline void hri_sdramc_write_CR_DBW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_DBW;
	tmp |= value << SDRAMC_CR_DBW_Pos;
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_DBW_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_DBW;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_DBW_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_DBW;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_set_CR_NC_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_NC(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_NC_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_NC(mask)) >> SDRAMC_CR_NC_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CR_NC_bf(const void *const hw, hri_sdramc_cr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_NC_Msk;
	tmp |= SDRAMC_CR_NC(data);
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_NC_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_NC(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_NC_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_NC(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_NC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_NC_Msk) >> SDRAMC_CR_NC_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CR_NR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_NR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_NR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_NR(mask)) >> SDRAMC_CR_NR_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CR_NR_bf(const void *const hw, hri_sdramc_cr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_NR_Msk;
	tmp |= SDRAMC_CR_NR(data);
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_NR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_NR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_NR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_NR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_NR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_NR_Msk) >> SDRAMC_CR_NR_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CR_CAS_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_CAS(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_CAS_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_CAS(mask)) >> SDRAMC_CR_CAS_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CR_CAS_bf(const void *const hw, hri_sdramc_cr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_CAS_Msk;
	tmp |= SDRAMC_CR_CAS(data);
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_CAS_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_CAS(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_CAS_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_CAS(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_CAS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_CAS_Msk) >> SDRAMC_CR_CAS_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CR_TWR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_TWR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_TWR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TWR(mask)) >> SDRAMC_CR_TWR_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CR_TWR_bf(const void *const hw, hri_sdramc_cr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_TWR_Msk;
	tmp |= SDRAMC_CR_TWR(data);
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_TWR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_TWR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_TWR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_TWR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_TWR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TWR_Msk) >> SDRAMC_CR_TWR_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CR_TRC_TRFC_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_TRC_TRFC(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_TRC_TRFC_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TRC_TRFC(mask)) >> SDRAMC_CR_TRC_TRFC_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CR_TRC_TRFC_bf(const void *const hw, hri_sdramc_cr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_TRC_TRFC_Msk;
	tmp |= SDRAMC_CR_TRC_TRFC(data);
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_TRC_TRFC_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_TRC_TRFC(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_TRC_TRFC_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_TRC_TRFC(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_TRC_TRFC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TRC_TRFC_Msk) >> SDRAMC_CR_TRC_TRFC_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CR_TRP_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_TRP(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_TRP_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TRP(mask)) >> SDRAMC_CR_TRP_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CR_TRP_bf(const void *const hw, hri_sdramc_cr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_TRP_Msk;
	tmp |= SDRAMC_CR_TRP(data);
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_TRP_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_TRP(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_TRP_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_TRP(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_TRP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TRP_Msk) >> SDRAMC_CR_TRP_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CR_TRCD_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_TRCD(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_TRCD_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TRCD(mask)) >> SDRAMC_CR_TRCD_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CR_TRCD_bf(const void *const hw, hri_sdramc_cr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_TRCD_Msk;
	tmp |= SDRAMC_CR_TRCD(data);
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_TRCD_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_TRCD(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_TRCD_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_TRCD(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_TRCD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TRCD_Msk) >> SDRAMC_CR_TRCD_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CR_TRAS_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_TRAS(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_TRAS_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TRAS(mask)) >> SDRAMC_CR_TRAS_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CR_TRAS_bf(const void *const hw, hri_sdramc_cr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_TRAS_Msk;
	tmp |= SDRAMC_CR_TRAS(data);
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_TRAS_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_TRAS(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_TRAS_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_TRAS(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_TRAS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TRAS_Msk) >> SDRAMC_CR_TRAS_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CR_TXSR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= SDRAMC_CR_TXSR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_TXSR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TXSR(mask)) >> SDRAMC_CR_TXSR_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CR_TXSR_bf(const void *const hw, hri_sdramc_cr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= ~SDRAMC_CR_TXSR_Msk;
	tmp |= SDRAMC_CR_TXSR(data);
	((Sdramc *)hw)->SDRAMC_CR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_TXSR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~SDRAMC_CR_TXSR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_TXSR_bf(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= SDRAMC_CR_TXSR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_TXSR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp = (tmp & SDRAMC_CR_TXSR_Msk) >> SDRAMC_CR_TXSR_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CR_reg(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR |= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_get_CR_reg(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CR;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdramc_write_CR_reg(const void *const hw, hri_sdramc_cr_reg_t data)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR = data;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CR_reg(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR &= ~mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CR_reg(const void *const hw, hri_sdramc_cr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CR ^= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cr_reg_t hri_sdramc_read_CR_reg(const void *const hw)
{
	return ((Sdramc *)hw)->SDRAMC_CR;
}

static inline void hri_sdramc_set_LPR_LPCB_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR |= SDRAMC_LPR_LPCB(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_get_LPR_LPCB_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_LPCB(mask)) >> SDRAMC_LPR_LPCB_Pos;
	return tmp;
}

static inline void hri_sdramc_write_LPR_LPCB_bf(const void *const hw, hri_sdramc_lpr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp &= ~SDRAMC_LPR_LPCB_Msk;
	tmp |= SDRAMC_LPR_LPCB(data);
	((Sdramc *)hw)->SDRAMC_LPR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_LPR_LPCB_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR &= ~SDRAMC_LPR_LPCB(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_LPR_LPCB_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR ^= SDRAMC_LPR_LPCB(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_read_LPR_LPCB_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_LPCB_Msk) >> SDRAMC_LPR_LPCB_Pos;
	return tmp;
}

static inline void hri_sdramc_set_LPR_PASR_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR |= SDRAMC_LPR_PASR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_get_LPR_PASR_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_PASR(mask)) >> SDRAMC_LPR_PASR_Pos;
	return tmp;
}

static inline void hri_sdramc_write_LPR_PASR_bf(const void *const hw, hri_sdramc_lpr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp &= ~SDRAMC_LPR_PASR_Msk;
	tmp |= SDRAMC_LPR_PASR(data);
	((Sdramc *)hw)->SDRAMC_LPR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_LPR_PASR_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR &= ~SDRAMC_LPR_PASR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_LPR_PASR_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR ^= SDRAMC_LPR_PASR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_read_LPR_PASR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_PASR_Msk) >> SDRAMC_LPR_PASR_Pos;
	return tmp;
}

static inline void hri_sdramc_set_LPR_TCSR_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR |= SDRAMC_LPR_TCSR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_get_LPR_TCSR_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_TCSR(mask)) >> SDRAMC_LPR_TCSR_Pos;
	return tmp;
}

static inline void hri_sdramc_write_LPR_TCSR_bf(const void *const hw, hri_sdramc_lpr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp &= ~SDRAMC_LPR_TCSR_Msk;
	tmp |= SDRAMC_LPR_TCSR(data);
	((Sdramc *)hw)->SDRAMC_LPR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_LPR_TCSR_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR &= ~SDRAMC_LPR_TCSR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_LPR_TCSR_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR ^= SDRAMC_LPR_TCSR(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_read_LPR_TCSR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_TCSR_Msk) >> SDRAMC_LPR_TCSR_Pos;
	return tmp;
}

static inline void hri_sdramc_set_LPR_DS_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR |= SDRAMC_LPR_DS(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_get_LPR_DS_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_DS(mask)) >> SDRAMC_LPR_DS_Pos;
	return tmp;
}

static inline void hri_sdramc_write_LPR_DS_bf(const void *const hw, hri_sdramc_lpr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp &= ~SDRAMC_LPR_DS_Msk;
	tmp |= SDRAMC_LPR_DS(data);
	((Sdramc *)hw)->SDRAMC_LPR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_LPR_DS_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR &= ~SDRAMC_LPR_DS(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_LPR_DS_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR ^= SDRAMC_LPR_DS(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_read_LPR_DS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_DS_Msk) >> SDRAMC_LPR_DS_Pos;
	return tmp;
}

static inline void hri_sdramc_set_LPR_TIMEOUT_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR |= SDRAMC_LPR_TIMEOUT(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_get_LPR_TIMEOUT_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_TIMEOUT(mask)) >> SDRAMC_LPR_TIMEOUT_Pos;
	return tmp;
}

static inline void hri_sdramc_write_LPR_TIMEOUT_bf(const void *const hw, hri_sdramc_lpr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp &= ~SDRAMC_LPR_TIMEOUT_Msk;
	tmp |= SDRAMC_LPR_TIMEOUT(data);
	((Sdramc *)hw)->SDRAMC_LPR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_LPR_TIMEOUT_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR &= ~SDRAMC_LPR_TIMEOUT(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_LPR_TIMEOUT_bf(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR ^= SDRAMC_LPR_TIMEOUT(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_read_LPR_TIMEOUT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp = (tmp & SDRAMC_LPR_TIMEOUT_Msk) >> SDRAMC_LPR_TIMEOUT_Pos;
	return tmp;
}

static inline void hri_sdramc_set_LPR_reg(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR |= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_get_LPR_reg(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_LPR;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdramc_write_LPR_reg(const void *const hw, hri_sdramc_lpr_reg_t data)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR = data;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_LPR_reg(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR &= ~mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_LPR_reg(const void *const hw, hri_sdramc_lpr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_LPR ^= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_lpr_reg_t hri_sdramc_read_LPR_reg(const void *const hw)
{
	return ((Sdramc *)hw)->SDRAMC_LPR;
}

static inline void hri_sdramc_set_MDR_MD_bf(const void *const hw, hri_sdramc_mdr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MDR |= SDRAMC_MDR_MD(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_mdr_reg_t hri_sdramc_get_MDR_MD_bf(const void *const hw, hri_sdramc_mdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_MDR;
	tmp = (tmp & SDRAMC_MDR_MD(mask)) >> SDRAMC_MDR_MD_Pos;
	return tmp;
}

static inline void hri_sdramc_write_MDR_MD_bf(const void *const hw, hri_sdramc_mdr_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_MDR;
	tmp &= ~SDRAMC_MDR_MD_Msk;
	tmp |= SDRAMC_MDR_MD(data);
	((Sdramc *)hw)->SDRAMC_MDR = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_MDR_MD_bf(const void *const hw, hri_sdramc_mdr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MDR &= ~SDRAMC_MDR_MD(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_MDR_MD_bf(const void *const hw, hri_sdramc_mdr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MDR ^= SDRAMC_MDR_MD(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_mdr_reg_t hri_sdramc_read_MDR_MD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_MDR;
	tmp = (tmp & SDRAMC_MDR_MD_Msk) >> SDRAMC_MDR_MD_Pos;
	return tmp;
}

static inline void hri_sdramc_set_MDR_reg(const void *const hw, hri_sdramc_mdr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MDR |= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_mdr_reg_t hri_sdramc_get_MDR_reg(const void *const hw, hri_sdramc_mdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_MDR;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdramc_write_MDR_reg(const void *const hw, hri_sdramc_mdr_reg_t data)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MDR = data;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_MDR_reg(const void *const hw, hri_sdramc_mdr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MDR &= ~mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_MDR_reg(const void *const hw, hri_sdramc_mdr_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_MDR ^= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_mdr_reg_t hri_sdramc_read_MDR_reg(const void *const hw)
{
	return ((Sdramc *)hw)->SDRAMC_MDR;
}

static inline void hri_sdramc_set_CFR1_UNAL_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 |= SDRAMC_CFR1_UNAL;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdramc_get_CFR1_UNAL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CFR1;
	tmp = (tmp & SDRAMC_CFR1_UNAL) >> SDRAMC_CFR1_UNAL_Pos;
	return (bool)tmp;
}

static inline void hri_sdramc_write_CFR1_UNAL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CFR1;
	tmp &= ~SDRAMC_CFR1_UNAL;
	tmp |= value << SDRAMC_CFR1_UNAL_Pos;
	((Sdramc *)hw)->SDRAMC_CFR1 = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CFR1_UNAL_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 &= ~SDRAMC_CFR1_UNAL;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CFR1_UNAL_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 ^= SDRAMC_CFR1_UNAL;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_set_CFR1_TMRD_bf(const void *const hw, hri_sdramc_cfr1_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 |= SDRAMC_CFR1_TMRD(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cfr1_reg_t hri_sdramc_get_CFR1_TMRD_bf(const void *const hw, hri_sdramc_cfr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CFR1;
	tmp = (tmp & SDRAMC_CFR1_TMRD(mask)) >> SDRAMC_CFR1_TMRD_Pos;
	return tmp;
}

static inline void hri_sdramc_write_CFR1_TMRD_bf(const void *const hw, hri_sdramc_cfr1_reg_t data)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_CFR1;
	tmp &= ~SDRAMC_CFR1_TMRD_Msk;
	tmp |= SDRAMC_CFR1_TMRD(data);
	((Sdramc *)hw)->SDRAMC_CFR1 = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CFR1_TMRD_bf(const void *const hw, hri_sdramc_cfr1_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 &= ~SDRAMC_CFR1_TMRD(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CFR1_TMRD_bf(const void *const hw, hri_sdramc_cfr1_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 ^= SDRAMC_CFR1_TMRD(mask);
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cfr1_reg_t hri_sdramc_read_CFR1_TMRD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CFR1;
	tmp = (tmp & SDRAMC_CFR1_TMRD_Msk) >> SDRAMC_CFR1_TMRD_Pos;
	return tmp;
}

static inline void hri_sdramc_set_CFR1_reg(const void *const hw, hri_sdramc_cfr1_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 |= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cfr1_reg_t hri_sdramc_get_CFR1_reg(const void *const hw, hri_sdramc_cfr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_CFR1;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdramc_write_CFR1_reg(const void *const hw, hri_sdramc_cfr1_reg_t data)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 = data;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_CFR1_reg(const void *const hw, hri_sdramc_cfr1_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 &= ~mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_CFR1_reg(const void *const hw, hri_sdramc_cfr1_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_CFR1 ^= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_cfr1_reg_t hri_sdramc_read_CFR1_reg(const void *const hw)
{
	return ((Sdramc *)hw)->SDRAMC_CFR1;
}

static inline void hri_sdramc_set_OCMS_SDR_SE_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_OCMS |= SDRAMC_OCMS_SDR_SE;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdramc_get_OCMS_SDR_SE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_OCMS;
	tmp = (tmp & SDRAMC_OCMS_SDR_SE) >> SDRAMC_OCMS_SDR_SE_Pos;
	return (bool)tmp;
}

static inline void hri_sdramc_write_OCMS_SDR_SE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SDRAMC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdramc *)hw)->SDRAMC_OCMS;
	tmp &= ~SDRAMC_OCMS_SDR_SE;
	tmp |= value << SDRAMC_OCMS_SDR_SE_Pos;
	((Sdramc *)hw)->SDRAMC_OCMS = tmp;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_OCMS_SDR_SE_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_OCMS &= ~SDRAMC_OCMS_SDR_SE;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_OCMS_SDR_SE_bit(const void *const hw)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_OCMS ^= SDRAMC_OCMS_SDR_SE;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_set_OCMS_reg(const void *const hw, hri_sdramc_ocms_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_OCMS |= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_ocms_reg_t hri_sdramc_get_OCMS_reg(const void *const hw, hri_sdramc_ocms_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdramc *)hw)->SDRAMC_OCMS;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdramc_write_OCMS_reg(const void *const hw, hri_sdramc_ocms_reg_t data)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_OCMS = data;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_clear_OCMS_reg(const void *const hw, hri_sdramc_ocms_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_OCMS &= ~mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_toggle_OCMS_reg(const void *const hw, hri_sdramc_ocms_reg_t mask)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_OCMS ^= mask;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdramc_ocms_reg_t hri_sdramc_read_OCMS_reg(const void *const hw)
{
	return ((Sdramc *)hw)->SDRAMC_OCMS;
}

static inline void hri_sdramc_write_OCMS_KEY1_reg(const void *const hw, hri_sdramc_ocms_key1_reg_t data)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_OCMS_KEY1 = data;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdramc_write_OCMS_KEY2_reg(const void *const hw, hri_sdramc_ocms_key2_reg_t data)
{
	SDRAMC_CRITICAL_SECTION_ENTER();
	((Sdramc *)hw)->SDRAMC_OCMS_KEY2 = data;
	SDRAMC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SDRAMC_E70B_H_INCLUDED */
#endif /* _SAME70_SDRAMC_COMPONENT_ */
