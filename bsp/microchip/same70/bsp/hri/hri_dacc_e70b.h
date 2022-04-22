/**
 * \file
 *
 * \brief SAM DACC
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

#ifdef _SAME70_DACC_COMPONENT_
#ifndef _HRI_DACC_E70B_H_INCLUDED_
#define _HRI_DACC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_DACC_CRITICAL_SECTIONS)
#define DACC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define DACC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define DACC_CRITICAL_SECTION_ENTER()
#define DACC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_dacc_acr_reg_t;
typedef uint32_t hri_dacc_cdr_reg_t;
typedef uint32_t hri_dacc_chsr_reg_t;
typedef uint32_t hri_dacc_cr_reg_t;
typedef uint32_t hri_dacc_imr_reg_t;
typedef uint32_t hri_dacc_isr_reg_t;
typedef uint32_t hri_dacc_mr_reg_t;
typedef uint32_t hri_dacc_trigr_reg_t;
typedef uint32_t hri_dacc_wpmr_reg_t;
typedef uint32_t hri_dacc_wpsr_reg_t;

static inline bool hri_dacc_get_ISR_TXRDY0_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_ISR & DACC_ISR_TXRDY0) >> DACC_ISR_TXRDY0_Pos;
}

static inline bool hri_dacc_get_ISR_TXRDY1_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_ISR & DACC_ISR_TXRDY1) >> DACC_ISR_TXRDY1_Pos;
}

static inline bool hri_dacc_get_ISR_EOC0_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_ISR & DACC_ISR_EOC0) >> DACC_ISR_EOC0_Pos;
}

static inline bool hri_dacc_get_ISR_EOC1_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_ISR & DACC_ISR_EOC1) >> DACC_ISR_EOC1_Pos;
}

static inline hri_dacc_isr_reg_t hri_dacc_get_ISR_reg(const void *const hw, hri_dacc_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_dacc_isr_reg_t hri_dacc_read_ISR_reg(const void *const hw)
{
	return ((Dacc *)hw)->DACC_ISR;
}

static inline void hri_dacc_set_CHSR_CH0_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_CHER = DACC_CHSR_CH0;
}

static inline bool hri_dacc_get_CHSR_CH0_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_CHSR & DACC_CHSR_CH0) >> DACC_CHSR_CH0_Pos;
}

static inline void hri_dacc_write_CHSR_CH0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Dacc *)hw)->DACC_CHDR = DACC_CHSR_CH0;
	} else {
		((Dacc *)hw)->DACC_CHER = DACC_CHSR_CH0;
	}
}

static inline void hri_dacc_clear_CHSR_CH0_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_CHDR = DACC_CHSR_CH0;
}

static inline void hri_dacc_set_CHSR_CH1_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_CHER = DACC_CHSR_CH1;
}

static inline bool hri_dacc_get_CHSR_CH1_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_CHSR & DACC_CHSR_CH1) >> DACC_CHSR_CH1_Pos;
}

static inline void hri_dacc_write_CHSR_CH1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Dacc *)hw)->DACC_CHDR = DACC_CHSR_CH1;
	} else {
		((Dacc *)hw)->DACC_CHER = DACC_CHSR_CH1;
	}
}

static inline void hri_dacc_clear_CHSR_CH1_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_CHDR = DACC_CHSR_CH1;
}

static inline bool hri_dacc_get_CHSR_DACRDY0_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_CHSR & DACC_CHSR_DACRDY0) >> DACC_CHSR_DACRDY0_Pos;
}

static inline bool hri_dacc_get_CHSR_DACRDY1_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_CHSR & DACC_CHSR_DACRDY1) >> DACC_CHSR_DACRDY1_Pos;
}

static inline void hri_dacc_set_CHSR_reg(const void *const hw, hri_dacc_chsr_reg_t mask)
{
	((Dacc *)hw)->DACC_CHER = mask;
}

static inline hri_dacc_chsr_reg_t hri_dacc_get_CHSR_reg(const void *const hw, hri_dacc_chsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_CHSR;
	tmp &= mask;
	return tmp;
}

static inline hri_dacc_chsr_reg_t hri_dacc_read_CHSR_reg(const void *const hw)
{
	return ((Dacc *)hw)->DACC_CHSR;
}

static inline void hri_dacc_write_CHSR_reg(const void *const hw, hri_dacc_chsr_reg_t data)
{
	((Dacc *)hw)->DACC_CHER = data;
	((Dacc *)hw)->DACC_CHDR = ~data;
}

static inline void hri_dacc_clear_CHSR_reg(const void *const hw, hri_dacc_chsr_reg_t mask)
{
	((Dacc *)hw)->DACC_CHDR = mask;
}

static inline void hri_dacc_write_CHDR_reg(const void *const hw, hri_dacc_chsr_reg_t data)
{
	((Dacc *)hw)->DACC_CHDR = data;
}

static inline void hri_dacc_write_CHER_reg(const void *const hw, hri_dacc_chsr_reg_t data)
{
	((Dacc *)hw)->DACC_CHER = data;
}

static inline void hri_dacc_set_IMR_TXRDY0_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_IER = DACC_IMR_TXRDY0;
}

static inline bool hri_dacc_get_IMR_TXRDY0_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_IMR & DACC_IMR_TXRDY0) >> DACC_IMR_TXRDY0_Pos;
}

static inline void hri_dacc_write_IMR_TXRDY0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Dacc *)hw)->DACC_IDR = DACC_IMR_TXRDY0;
	} else {
		((Dacc *)hw)->DACC_IER = DACC_IMR_TXRDY0;
	}
}

static inline void hri_dacc_clear_IMR_TXRDY0_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_IDR = DACC_IMR_TXRDY0;
}

static inline void hri_dacc_set_IMR_TXRDY1_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_IER = DACC_IMR_TXRDY1;
}

static inline bool hri_dacc_get_IMR_TXRDY1_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_IMR & DACC_IMR_TXRDY1) >> DACC_IMR_TXRDY1_Pos;
}

static inline void hri_dacc_write_IMR_TXRDY1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Dacc *)hw)->DACC_IDR = DACC_IMR_TXRDY1;
	} else {
		((Dacc *)hw)->DACC_IER = DACC_IMR_TXRDY1;
	}
}

static inline void hri_dacc_clear_IMR_TXRDY1_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_IDR = DACC_IMR_TXRDY1;
}

static inline void hri_dacc_set_IMR_EOC0_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_IER = DACC_IMR_EOC0;
}

static inline bool hri_dacc_get_IMR_EOC0_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_IMR & DACC_IMR_EOC0) >> DACC_IMR_EOC0_Pos;
}

static inline void hri_dacc_write_IMR_EOC0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Dacc *)hw)->DACC_IDR = DACC_IMR_EOC0;
	} else {
		((Dacc *)hw)->DACC_IER = DACC_IMR_EOC0;
	}
}

static inline void hri_dacc_clear_IMR_EOC0_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_IDR = DACC_IMR_EOC0;
}

static inline void hri_dacc_set_IMR_EOC1_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_IER = DACC_IMR_EOC1;
}

static inline bool hri_dacc_get_IMR_EOC1_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_IMR & DACC_IMR_EOC1) >> DACC_IMR_EOC1_Pos;
}

static inline void hri_dacc_write_IMR_EOC1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Dacc *)hw)->DACC_IDR = DACC_IMR_EOC1;
	} else {
		((Dacc *)hw)->DACC_IER = DACC_IMR_EOC1;
	}
}

static inline void hri_dacc_clear_IMR_EOC1_bit(const void *const hw)
{
	((Dacc *)hw)->DACC_IDR = DACC_IMR_EOC1;
}

static inline void hri_dacc_set_IMR_reg(const void *const hw, hri_dacc_imr_reg_t mask)
{
	((Dacc *)hw)->DACC_IER = mask;
}

static inline hri_dacc_imr_reg_t hri_dacc_get_IMR_reg(const void *const hw, hri_dacc_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_dacc_imr_reg_t hri_dacc_read_IMR_reg(const void *const hw)
{
	return ((Dacc *)hw)->DACC_IMR;
}

static inline void hri_dacc_write_IMR_reg(const void *const hw, hri_dacc_imr_reg_t data)
{
	((Dacc *)hw)->DACC_IER = data;
	((Dacc *)hw)->DACC_IDR = ~data;
}

static inline void hri_dacc_clear_IMR_reg(const void *const hw, hri_dacc_imr_reg_t mask)
{
	((Dacc *)hw)->DACC_IDR = mask;
}

static inline bool hri_dacc_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Dacc *)hw)->DACC_WPSR & DACC_WPSR_WPVS) > 0;
}

static inline hri_dacc_wpsr_reg_t hri_dacc_get_WPSR_WPVSRC_bf(const void *const hw, hri_dacc_wpsr_reg_t mask)
{
	return (((Dacc *)hw)->DACC_WPSR & DACC_WPSR_WPVSRC(mask)) >> DACC_WPSR_WPVSRC_Pos;
}

static inline hri_dacc_wpsr_reg_t hri_dacc_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Dacc *)hw)->DACC_WPSR & DACC_WPSR_WPVSRC_Msk) >> DACC_WPSR_WPVSRC_Pos;
}

static inline hri_dacc_wpsr_reg_t hri_dacc_get_WPSR_reg(const void *const hw, hri_dacc_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_dacc_wpsr_reg_t hri_dacc_read_WPSR_reg(const void *const hw)
{
	return ((Dacc *)hw)->DACC_WPSR;
}

static inline void hri_dacc_set_MR_MAXS0_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR |= DACC_MR_MAXS0;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dacc_get_MR_MAXS0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp = (tmp & DACC_MR_MAXS0) >> DACC_MR_MAXS0_Pos;
	return (bool)tmp;
}

static inline void hri_dacc_write_MR_MAXS0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp &= ~DACC_MR_MAXS0;
	tmp |= value << DACC_MR_MAXS0_Pos;
	((Dacc *)hw)->DACC_MR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_MR_MAXS0_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR &= ~DACC_MR_MAXS0;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_MR_MAXS0_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR ^= DACC_MR_MAXS0;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_set_MR_MAXS1_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR |= DACC_MR_MAXS1;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dacc_get_MR_MAXS1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp = (tmp & DACC_MR_MAXS1) >> DACC_MR_MAXS1_Pos;
	return (bool)tmp;
}

static inline void hri_dacc_write_MR_MAXS1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp &= ~DACC_MR_MAXS1;
	tmp |= value << DACC_MR_MAXS1_Pos;
	((Dacc *)hw)->DACC_MR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_MR_MAXS1_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR &= ~DACC_MR_MAXS1;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_MR_MAXS1_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR ^= DACC_MR_MAXS1;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_set_MR_WORD_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR |= DACC_MR_WORD;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dacc_get_MR_WORD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp = (tmp & DACC_MR_WORD) >> DACC_MR_WORD_Pos;
	return (bool)tmp;
}

static inline void hri_dacc_write_MR_WORD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp &= ~DACC_MR_WORD;
	tmp |= value << DACC_MR_WORD_Pos;
	((Dacc *)hw)->DACC_MR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_MR_WORD_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR &= ~DACC_MR_WORD;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_MR_WORD_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR ^= DACC_MR_WORD;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_set_MR_ZERO_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR |= DACC_MR_ZERO;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dacc_get_MR_ZERO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp = (tmp & DACC_MR_ZERO) >> DACC_MR_ZERO_Pos;
	return (bool)tmp;
}

static inline void hri_dacc_write_MR_ZERO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp &= ~DACC_MR_ZERO;
	tmp |= value << DACC_MR_ZERO_Pos;
	((Dacc *)hw)->DACC_MR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_MR_ZERO_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR &= ~DACC_MR_ZERO;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_MR_ZERO_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR ^= DACC_MR_ZERO;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_set_MR_DIFF_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR |= DACC_MR_DIFF;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dacc_get_MR_DIFF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp = (tmp & DACC_MR_DIFF) >> DACC_MR_DIFF_Pos;
	return (bool)tmp;
}

static inline void hri_dacc_write_MR_DIFF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp &= ~DACC_MR_DIFF;
	tmp |= value << DACC_MR_DIFF_Pos;
	((Dacc *)hw)->DACC_MR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_MR_DIFF_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR &= ~DACC_MR_DIFF;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_MR_DIFF_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR ^= DACC_MR_DIFF;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_set_MR_PRESCALER_bf(const void *const hw, hri_dacc_mr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR |= DACC_MR_PRESCALER(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_mr_reg_t hri_dacc_get_MR_PRESCALER_bf(const void *const hw, hri_dacc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp = (tmp & DACC_MR_PRESCALER(mask)) >> DACC_MR_PRESCALER_Pos;
	return tmp;
}

static inline void hri_dacc_write_MR_PRESCALER_bf(const void *const hw, hri_dacc_mr_reg_t data)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp &= ~DACC_MR_PRESCALER_Msk;
	tmp |= DACC_MR_PRESCALER(data);
	((Dacc *)hw)->DACC_MR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_MR_PRESCALER_bf(const void *const hw, hri_dacc_mr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR &= ~DACC_MR_PRESCALER(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_MR_PRESCALER_bf(const void *const hw, hri_dacc_mr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR ^= DACC_MR_PRESCALER(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_mr_reg_t hri_dacc_read_MR_PRESCALER_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp = (tmp & DACC_MR_PRESCALER_Msk) >> DACC_MR_PRESCALER_Pos;
	return tmp;
}

static inline void hri_dacc_set_MR_reg(const void *const hw, hri_dacc_mr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR |= mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_mr_reg_t hri_dacc_get_MR_reg(const void *const hw, hri_dacc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_dacc_write_MR_reg(const void *const hw, hri_dacc_mr_reg_t data)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR = data;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_MR_reg(const void *const hw, hri_dacc_mr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR &= ~mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_MR_reg(const void *const hw, hri_dacc_mr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_MR ^= mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_mr_reg_t hri_dacc_read_MR_reg(const void *const hw)
{
	return ((Dacc *)hw)->DACC_MR;
}

static inline void hri_dacc_set_TRIGR_TRGEN0_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR |= DACC_TRIGR_TRGEN0;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dacc_get_TRIGR_TRGEN0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_TRGEN0) >> DACC_TRIGR_TRGEN0_Pos;
	return (bool)tmp;
}

static inline void hri_dacc_write_TRIGR_TRGEN0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp &= ~DACC_TRIGR_TRGEN0;
	tmp |= value << DACC_TRIGR_TRGEN0_Pos;
	((Dacc *)hw)->DACC_TRIGR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_TRIGR_TRGEN0_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR &= ~DACC_TRIGR_TRGEN0;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_TRIGR_TRGEN0_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR ^= DACC_TRIGR_TRGEN0;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_set_TRIGR_TRGEN1_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR |= DACC_TRIGR_TRGEN1;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dacc_get_TRIGR_TRGEN1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_TRGEN1) >> DACC_TRIGR_TRGEN1_Pos;
	return (bool)tmp;
}

static inline void hri_dacc_write_TRIGR_TRGEN1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp &= ~DACC_TRIGR_TRGEN1;
	tmp |= value << DACC_TRIGR_TRGEN1_Pos;
	((Dacc *)hw)->DACC_TRIGR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_TRIGR_TRGEN1_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR &= ~DACC_TRIGR_TRGEN1;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_TRIGR_TRGEN1_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR ^= DACC_TRIGR_TRGEN1;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_set_TRIGR_TRGSEL0_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR |= DACC_TRIGR_TRGSEL0(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_get_TRIGR_TRGSEL0_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_TRGSEL0(mask)) >> DACC_TRIGR_TRGSEL0_Pos;
	return tmp;
}

static inline void hri_dacc_write_TRIGR_TRGSEL0_bf(const void *const hw, hri_dacc_trigr_reg_t data)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp &= ~DACC_TRIGR_TRGSEL0_Msk;
	tmp |= DACC_TRIGR_TRGSEL0(data);
	((Dacc *)hw)->DACC_TRIGR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_TRIGR_TRGSEL0_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR &= ~DACC_TRIGR_TRGSEL0(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_TRIGR_TRGSEL0_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR ^= DACC_TRIGR_TRGSEL0(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_read_TRIGR_TRGSEL0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_TRGSEL0_Msk) >> DACC_TRIGR_TRGSEL0_Pos;
	return tmp;
}

static inline void hri_dacc_set_TRIGR_TRGSEL1_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR |= DACC_TRIGR_TRGSEL1(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_get_TRIGR_TRGSEL1_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_TRGSEL1(mask)) >> DACC_TRIGR_TRGSEL1_Pos;
	return tmp;
}

static inline void hri_dacc_write_TRIGR_TRGSEL1_bf(const void *const hw, hri_dacc_trigr_reg_t data)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp &= ~DACC_TRIGR_TRGSEL1_Msk;
	tmp |= DACC_TRIGR_TRGSEL1(data);
	((Dacc *)hw)->DACC_TRIGR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_TRIGR_TRGSEL1_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR &= ~DACC_TRIGR_TRGSEL1(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_TRIGR_TRGSEL1_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR ^= DACC_TRIGR_TRGSEL1(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_read_TRIGR_TRGSEL1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_TRGSEL1_Msk) >> DACC_TRIGR_TRGSEL1_Pos;
	return tmp;
}

static inline void hri_dacc_set_TRIGR_OSR0_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR |= DACC_TRIGR_OSR0(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_get_TRIGR_OSR0_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_OSR0(mask)) >> DACC_TRIGR_OSR0_Pos;
	return tmp;
}

static inline void hri_dacc_write_TRIGR_OSR0_bf(const void *const hw, hri_dacc_trigr_reg_t data)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp &= ~DACC_TRIGR_OSR0_Msk;
	tmp |= DACC_TRIGR_OSR0(data);
	((Dacc *)hw)->DACC_TRIGR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_TRIGR_OSR0_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR &= ~DACC_TRIGR_OSR0(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_TRIGR_OSR0_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR ^= DACC_TRIGR_OSR0(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_read_TRIGR_OSR0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_OSR0_Msk) >> DACC_TRIGR_OSR0_Pos;
	return tmp;
}

static inline void hri_dacc_set_TRIGR_OSR1_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR |= DACC_TRIGR_OSR1(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_get_TRIGR_OSR1_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_OSR1(mask)) >> DACC_TRIGR_OSR1_Pos;
	return tmp;
}

static inline void hri_dacc_write_TRIGR_OSR1_bf(const void *const hw, hri_dacc_trigr_reg_t data)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp &= ~DACC_TRIGR_OSR1_Msk;
	tmp |= DACC_TRIGR_OSR1(data);
	((Dacc *)hw)->DACC_TRIGR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_TRIGR_OSR1_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR &= ~DACC_TRIGR_OSR1(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_TRIGR_OSR1_bf(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR ^= DACC_TRIGR_OSR1(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_read_TRIGR_OSR1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp = (tmp & DACC_TRIGR_OSR1_Msk) >> DACC_TRIGR_OSR1_Pos;
	return tmp;
}

static inline void hri_dacc_set_TRIGR_reg(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR |= mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_get_TRIGR_reg(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_TRIGR;
	tmp &= mask;
	return tmp;
}

static inline void hri_dacc_write_TRIGR_reg(const void *const hw, hri_dacc_trigr_reg_t data)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR = data;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_TRIGR_reg(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR &= ~mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_TRIGR_reg(const void *const hw, hri_dacc_trigr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_TRIGR ^= mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_trigr_reg_t hri_dacc_read_TRIGR_reg(const void *const hw)
{
	return ((Dacc *)hw)->DACC_TRIGR;
}

static inline void hri_dacc_set_ACR_IBCTLCH0_bf(const void *const hw, hri_dacc_acr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR |= DACC_ACR_IBCTLCH0(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_acr_reg_t hri_dacc_get_ACR_IBCTLCH0_bf(const void *const hw, hri_dacc_acr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_ACR;
	tmp = (tmp & DACC_ACR_IBCTLCH0(mask)) >> DACC_ACR_IBCTLCH0_Pos;
	return tmp;
}

static inline void hri_dacc_write_ACR_IBCTLCH0_bf(const void *const hw, hri_dacc_acr_reg_t data)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_ACR;
	tmp &= ~DACC_ACR_IBCTLCH0_Msk;
	tmp |= DACC_ACR_IBCTLCH0(data);
	((Dacc *)hw)->DACC_ACR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_ACR_IBCTLCH0_bf(const void *const hw, hri_dacc_acr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR &= ~DACC_ACR_IBCTLCH0(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_ACR_IBCTLCH0_bf(const void *const hw, hri_dacc_acr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR ^= DACC_ACR_IBCTLCH0(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_acr_reg_t hri_dacc_read_ACR_IBCTLCH0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_ACR;
	tmp = (tmp & DACC_ACR_IBCTLCH0_Msk) >> DACC_ACR_IBCTLCH0_Pos;
	return tmp;
}

static inline void hri_dacc_set_ACR_IBCTLCH1_bf(const void *const hw, hri_dacc_acr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR |= DACC_ACR_IBCTLCH1(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_acr_reg_t hri_dacc_get_ACR_IBCTLCH1_bf(const void *const hw, hri_dacc_acr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_ACR;
	tmp = (tmp & DACC_ACR_IBCTLCH1(mask)) >> DACC_ACR_IBCTLCH1_Pos;
	return tmp;
}

static inline void hri_dacc_write_ACR_IBCTLCH1_bf(const void *const hw, hri_dacc_acr_reg_t data)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_ACR;
	tmp &= ~DACC_ACR_IBCTLCH1_Msk;
	tmp |= DACC_ACR_IBCTLCH1(data);
	((Dacc *)hw)->DACC_ACR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_ACR_IBCTLCH1_bf(const void *const hw, hri_dacc_acr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR &= ~DACC_ACR_IBCTLCH1(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_ACR_IBCTLCH1_bf(const void *const hw, hri_dacc_acr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR ^= DACC_ACR_IBCTLCH1(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_acr_reg_t hri_dacc_read_ACR_IBCTLCH1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_ACR;
	tmp = (tmp & DACC_ACR_IBCTLCH1_Msk) >> DACC_ACR_IBCTLCH1_Pos;
	return tmp;
}

static inline void hri_dacc_set_ACR_reg(const void *const hw, hri_dacc_acr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR |= mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_acr_reg_t hri_dacc_get_ACR_reg(const void *const hw, hri_dacc_acr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_ACR;
	tmp &= mask;
	return tmp;
}

static inline void hri_dacc_write_ACR_reg(const void *const hw, hri_dacc_acr_reg_t data)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR = data;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_ACR_reg(const void *const hw, hri_dacc_acr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR &= ~mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_ACR_reg(const void *const hw, hri_dacc_acr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_ACR ^= mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_acr_reg_t hri_dacc_read_ACR_reg(const void *const hw)
{
	return ((Dacc *)hw)->DACC_ACR;
}

static inline void hri_dacc_set_WPMR_WPEN_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR |= DACC_WPMR_WPEN;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dacc_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_WPMR;
	tmp = (tmp & DACC_WPMR_WPEN) >> DACC_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_dacc_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_WPMR;
	tmp &= ~DACC_WPMR_WPEN;
	tmp |= value << DACC_WPMR_WPEN_Pos;
	((Dacc *)hw)->DACC_WPMR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_WPMR_WPEN_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR &= ~DACC_WPMR_WPEN;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_WPMR_WPEN_bit(const void *const hw)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR ^= DACC_WPMR_WPEN;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_set_WPMR_WPKEY_bf(const void *const hw, hri_dacc_wpmr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR |= DACC_WPMR_WPKEY(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_wpmr_reg_t hri_dacc_get_WPMR_WPKEY_bf(const void *const hw, hri_dacc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_WPMR;
	tmp = (tmp & DACC_WPMR_WPKEY(mask)) >> DACC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_dacc_write_WPMR_WPKEY_bf(const void *const hw, hri_dacc_wpmr_reg_t data)
{
	uint32_t tmp;
	DACC_CRITICAL_SECTION_ENTER();
	tmp = ((Dacc *)hw)->DACC_WPMR;
	tmp &= ~DACC_WPMR_WPKEY_Msk;
	tmp |= DACC_WPMR_WPKEY(data);
	((Dacc *)hw)->DACC_WPMR = tmp;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_WPMR_WPKEY_bf(const void *const hw, hri_dacc_wpmr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR &= ~DACC_WPMR_WPKEY(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_WPMR_WPKEY_bf(const void *const hw, hri_dacc_wpmr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR ^= DACC_WPMR_WPKEY(mask);
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_wpmr_reg_t hri_dacc_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_WPMR;
	tmp = (tmp & DACC_WPMR_WPKEY_Msk) >> DACC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_dacc_set_WPMR_reg(const void *const hw, hri_dacc_wpmr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR |= mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_wpmr_reg_t hri_dacc_get_WPMR_reg(const void *const hw, hri_dacc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dacc *)hw)->DACC_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_dacc_write_WPMR_reg(const void *const hw, hri_dacc_wpmr_reg_t data)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR = data;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_clear_WPMR_reg(const void *const hw, hri_dacc_wpmr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR &= ~mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_toggle_WPMR_reg(const void *const hw, hri_dacc_wpmr_reg_t mask)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_WPMR ^= mask;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline hri_dacc_wpmr_reg_t hri_dacc_read_WPMR_reg(const void *const hw)
{
	return ((Dacc *)hw)->DACC_WPMR;
}

static inline void hri_dacc_write_CR_reg(const void *const hw, hri_dacc_cr_reg_t data)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_CR = data;
	DACC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dacc_write_CDR_reg(const void *const hw, uint8_t index, hri_dacc_cdr_reg_t data)
{
	DACC_CRITICAL_SECTION_ENTER();
	((Dacc *)hw)->DACC_CDR[index] = data;
	DACC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_DACC_E70B_H_INCLUDED */
#endif /* _SAME70_DACC_COMPONENT_ */
