/**
 * \file
 *
 * \brief SAM AFEC
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

#ifdef _SAME70_AFEC_COMPONENT_
#ifndef _HRI_AFEC_E70B_H_INCLUDED_
#define _HRI_AFEC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_AFEC_CRITICAL_SECTIONS)
#define AFEC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define AFEC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define AFEC_CRITICAL_SECTION_ENTER()
#define AFEC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_afec_acr_reg_t;
typedef uint32_t hri_afec_cdr_reg_t;
typedef uint32_t hri_afec_cecr_reg_t;
typedef uint32_t hri_afec_cgr_reg_t;
typedef uint32_t hri_afec_chsr_reg_t;
typedef uint32_t hri_afec_cocr_reg_t;
typedef uint32_t hri_afec_cosr_reg_t;
typedef uint32_t hri_afec_cr_reg_t;
typedef uint32_t hri_afec_cselr_reg_t;
typedef uint32_t hri_afec_cvr_reg_t;
typedef uint32_t hri_afec_cwr_reg_t;
typedef uint32_t hri_afec_diffr_reg_t;
typedef uint32_t hri_afec_emr_reg_t;
typedef uint32_t hri_afec_imr_reg_t;
typedef uint32_t hri_afec_isr_reg_t;
typedef uint32_t hri_afec_lcdr_reg_t;
typedef uint32_t hri_afec_mr_reg_t;
typedef uint32_t hri_afec_over_reg_t;
typedef uint32_t hri_afec_seq1r_reg_t;
typedef uint32_t hri_afec_seq2r_reg_t;
typedef uint32_t hri_afec_shmr_reg_t;
typedef uint32_t hri_afec_tempcwr_reg_t;
typedef uint32_t hri_afec_tempmr_reg_t;
typedef uint32_t hri_afec_wpmr_reg_t;
typedef uint32_t hri_afec_wpsr_reg_t;

static inline bool hri_afec_get_ISR_EOC0_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC0) >> AFEC_ISR_EOC0_Pos;
}

static inline bool hri_afec_get_ISR_EOC1_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC1) >> AFEC_ISR_EOC1_Pos;
}

static inline bool hri_afec_get_ISR_EOC2_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC2) >> AFEC_ISR_EOC2_Pos;
}

static inline bool hri_afec_get_ISR_EOC3_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC3) >> AFEC_ISR_EOC3_Pos;
}

static inline bool hri_afec_get_ISR_EOC4_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC4) >> AFEC_ISR_EOC4_Pos;
}

static inline bool hri_afec_get_ISR_EOC5_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC5) >> AFEC_ISR_EOC5_Pos;
}

static inline bool hri_afec_get_ISR_EOC6_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC6) >> AFEC_ISR_EOC6_Pos;
}

static inline bool hri_afec_get_ISR_EOC7_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC7) >> AFEC_ISR_EOC7_Pos;
}

static inline bool hri_afec_get_ISR_EOC8_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC8) >> AFEC_ISR_EOC8_Pos;
}

static inline bool hri_afec_get_ISR_EOC9_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC9) >> AFEC_ISR_EOC9_Pos;
}

static inline bool hri_afec_get_ISR_EOC10_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC10) >> AFEC_ISR_EOC10_Pos;
}

static inline bool hri_afec_get_ISR_EOC11_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_EOC11) >> AFEC_ISR_EOC11_Pos;
}

static inline bool hri_afec_get_ISR_DRDY_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_DRDY) >> AFEC_ISR_DRDY_Pos;
}

static inline bool hri_afec_get_ISR_GOVRE_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_GOVRE) >> AFEC_ISR_GOVRE_Pos;
}

static inline bool hri_afec_get_ISR_COMPE_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_COMPE) >> AFEC_ISR_COMPE_Pos;
}

static inline bool hri_afec_get_ISR_TEMPCHG_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_ISR & AFEC_ISR_TEMPCHG) >> AFEC_ISR_TEMPCHG_Pos;
}

static inline hri_afec_isr_reg_t hri_afec_get_ISR_reg(const void *const hw, hri_afec_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_afec_isr_reg_t hri_afec_read_ISR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_ISR;
}

static inline void hri_afec_set_CHSR_CH0_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH0;
}

static inline bool hri_afec_get_CHSR_CH0_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH0) >> AFEC_CHSR_CH0_Pos;
}

static inline void hri_afec_write_CHSR_CH0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH0;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH0;
	}
}

static inline void hri_afec_clear_CHSR_CH0_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH0;
}

static inline void hri_afec_set_CHSR_CH1_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH1;
}

static inline bool hri_afec_get_CHSR_CH1_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH1) >> AFEC_CHSR_CH1_Pos;
}

static inline void hri_afec_write_CHSR_CH1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH1;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH1;
	}
}

static inline void hri_afec_clear_CHSR_CH1_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH1;
}

static inline void hri_afec_set_CHSR_CH2_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH2;
}

static inline bool hri_afec_get_CHSR_CH2_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH2) >> AFEC_CHSR_CH2_Pos;
}

static inline void hri_afec_write_CHSR_CH2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH2;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH2;
	}
}

static inline void hri_afec_clear_CHSR_CH2_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH2;
}

static inline void hri_afec_set_CHSR_CH3_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH3;
}

static inline bool hri_afec_get_CHSR_CH3_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH3) >> AFEC_CHSR_CH3_Pos;
}

static inline void hri_afec_write_CHSR_CH3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH3;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH3;
	}
}

static inline void hri_afec_clear_CHSR_CH3_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH3;
}

static inline void hri_afec_set_CHSR_CH4_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH4;
}

static inline bool hri_afec_get_CHSR_CH4_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH4) >> AFEC_CHSR_CH4_Pos;
}

static inline void hri_afec_write_CHSR_CH4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH4;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH4;
	}
}

static inline void hri_afec_clear_CHSR_CH4_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH4;
}

static inline void hri_afec_set_CHSR_CH5_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH5;
}

static inline bool hri_afec_get_CHSR_CH5_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH5) >> AFEC_CHSR_CH5_Pos;
}

static inline void hri_afec_write_CHSR_CH5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH5;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH5;
	}
}

static inline void hri_afec_clear_CHSR_CH5_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH5;
}

static inline void hri_afec_set_CHSR_CH6_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH6;
}

static inline bool hri_afec_get_CHSR_CH6_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH6) >> AFEC_CHSR_CH6_Pos;
}

static inline void hri_afec_write_CHSR_CH6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH6;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH6;
	}
}

static inline void hri_afec_clear_CHSR_CH6_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH6;
}

static inline void hri_afec_set_CHSR_CH7_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH7;
}

static inline bool hri_afec_get_CHSR_CH7_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH7) >> AFEC_CHSR_CH7_Pos;
}

static inline void hri_afec_write_CHSR_CH7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH7;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH7;
	}
}

static inline void hri_afec_clear_CHSR_CH7_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH7;
}

static inline void hri_afec_set_CHSR_CH8_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH8;
}

static inline bool hri_afec_get_CHSR_CH8_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH8) >> AFEC_CHSR_CH8_Pos;
}

static inline void hri_afec_write_CHSR_CH8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH8;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH8;
	}
}

static inline void hri_afec_clear_CHSR_CH8_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH8;
}

static inline void hri_afec_set_CHSR_CH9_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH9;
}

static inline bool hri_afec_get_CHSR_CH9_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH9) >> AFEC_CHSR_CH9_Pos;
}

static inline void hri_afec_write_CHSR_CH9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH9;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH9;
	}
}

static inline void hri_afec_clear_CHSR_CH9_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH9;
}

static inline void hri_afec_set_CHSR_CH10_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH10;
}

static inline bool hri_afec_get_CHSR_CH10_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH10) >> AFEC_CHSR_CH10_Pos;
}

static inline void hri_afec_write_CHSR_CH10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH10;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH10;
	}
}

static inline void hri_afec_clear_CHSR_CH10_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH10;
}

static inline void hri_afec_set_CHSR_CH11_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH11;
}

static inline bool hri_afec_get_CHSR_CH11_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CHSR & AFEC_CHSR_CH11) >> AFEC_CHSR_CH11_Pos;
}

static inline void hri_afec_write_CHSR_CH11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH11;
	} else {
		((Afec *)hw)->AFEC_CHER = AFEC_CHSR_CH11;
	}
}

static inline void hri_afec_clear_CHSR_CH11_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_CHDR = AFEC_CHSR_CH11;
}

static inline void hri_afec_set_CHSR_reg(const void *const hw, hri_afec_chsr_reg_t mask)
{
	((Afec *)hw)->AFEC_CHER = mask;
}

static inline hri_afec_chsr_reg_t hri_afec_get_CHSR_reg(const void *const hw, hri_afec_chsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CHSR;
	tmp &= mask;
	return tmp;
}

static inline hri_afec_chsr_reg_t hri_afec_read_CHSR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_CHSR;
}

static inline void hri_afec_write_CHSR_reg(const void *const hw, hri_afec_chsr_reg_t data)
{
	((Afec *)hw)->AFEC_CHER = data;
	((Afec *)hw)->AFEC_CHDR = ~data;
}

static inline void hri_afec_clear_CHSR_reg(const void *const hw, hri_afec_chsr_reg_t mask)
{
	((Afec *)hw)->AFEC_CHDR = mask;
}

static inline void hri_afec_set_IMR_EOC0_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC0;
}

static inline bool hri_afec_get_IMR_EOC0_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC0) >> AFEC_IMR_EOC0_Pos;
}

static inline void hri_afec_write_IMR_EOC0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC0;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC0;
	}
}

static inline void hri_afec_clear_IMR_EOC0_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC0;
}

static inline void hri_afec_set_IMR_EOC1_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC1;
}

static inline bool hri_afec_get_IMR_EOC1_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC1) >> AFEC_IMR_EOC1_Pos;
}

static inline void hri_afec_write_IMR_EOC1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC1;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC1;
	}
}

static inline void hri_afec_clear_IMR_EOC1_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC1;
}

static inline void hri_afec_set_IMR_EOC2_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC2;
}

static inline bool hri_afec_get_IMR_EOC2_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC2) >> AFEC_IMR_EOC2_Pos;
}

static inline void hri_afec_write_IMR_EOC2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC2;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC2;
	}
}

static inline void hri_afec_clear_IMR_EOC2_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC2;
}

static inline void hri_afec_set_IMR_EOC3_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC3;
}

static inline bool hri_afec_get_IMR_EOC3_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC3) >> AFEC_IMR_EOC3_Pos;
}

static inline void hri_afec_write_IMR_EOC3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC3;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC3;
	}
}

static inline void hri_afec_clear_IMR_EOC3_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC3;
}

static inline void hri_afec_set_IMR_EOC4_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC4;
}

static inline bool hri_afec_get_IMR_EOC4_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC4) >> AFEC_IMR_EOC4_Pos;
}

static inline void hri_afec_write_IMR_EOC4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC4;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC4;
	}
}

static inline void hri_afec_clear_IMR_EOC4_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC4;
}

static inline void hri_afec_set_IMR_EOC5_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC5;
}

static inline bool hri_afec_get_IMR_EOC5_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC5) >> AFEC_IMR_EOC5_Pos;
}

static inline void hri_afec_write_IMR_EOC5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC5;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC5;
	}
}

static inline void hri_afec_clear_IMR_EOC5_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC5;
}

static inline void hri_afec_set_IMR_EOC6_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC6;
}

static inline bool hri_afec_get_IMR_EOC6_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC6) >> AFEC_IMR_EOC6_Pos;
}

static inline void hri_afec_write_IMR_EOC6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC6;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC6;
	}
}

static inline void hri_afec_clear_IMR_EOC6_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC6;
}

static inline void hri_afec_set_IMR_EOC7_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC7;
}

static inline bool hri_afec_get_IMR_EOC7_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC7) >> AFEC_IMR_EOC7_Pos;
}

static inline void hri_afec_write_IMR_EOC7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC7;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC7;
	}
}

static inline void hri_afec_clear_IMR_EOC7_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC7;
}

static inline void hri_afec_set_IMR_EOC8_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC8;
}

static inline bool hri_afec_get_IMR_EOC8_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC8) >> AFEC_IMR_EOC8_Pos;
}

static inline void hri_afec_write_IMR_EOC8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC8;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC8;
	}
}

static inline void hri_afec_clear_IMR_EOC8_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC8;
}

static inline void hri_afec_set_IMR_EOC9_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC9;
}

static inline bool hri_afec_get_IMR_EOC9_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC9) >> AFEC_IMR_EOC9_Pos;
}

static inline void hri_afec_write_IMR_EOC9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC9;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC9;
	}
}

static inline void hri_afec_clear_IMR_EOC9_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC9;
}

static inline void hri_afec_set_IMR_EOC10_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC10;
}

static inline bool hri_afec_get_IMR_EOC10_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC10) >> AFEC_IMR_EOC10_Pos;
}

static inline void hri_afec_write_IMR_EOC10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC10;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC10;
	}
}

static inline void hri_afec_clear_IMR_EOC10_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC10;
}

static inline void hri_afec_set_IMR_EOC11_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC11;
}

static inline bool hri_afec_get_IMR_EOC11_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_EOC11) >> AFEC_IMR_EOC11_Pos;
}

static inline void hri_afec_write_IMR_EOC11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC11;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_EOC11;
	}
}

static inline void hri_afec_clear_IMR_EOC11_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_EOC11;
}

static inline void hri_afec_set_IMR_DRDY_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_DRDY;
}

static inline bool hri_afec_get_IMR_DRDY_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_DRDY) >> AFEC_IMR_DRDY_Pos;
}

static inline void hri_afec_write_IMR_DRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_DRDY;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_DRDY;
	}
}

static inline void hri_afec_clear_IMR_DRDY_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_DRDY;
}

static inline void hri_afec_set_IMR_GOVRE_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_GOVRE;
}

static inline bool hri_afec_get_IMR_GOVRE_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_GOVRE) >> AFEC_IMR_GOVRE_Pos;
}

static inline void hri_afec_write_IMR_GOVRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_GOVRE;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_GOVRE;
	}
}

static inline void hri_afec_clear_IMR_GOVRE_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_GOVRE;
}

static inline void hri_afec_set_IMR_COMPE_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_COMPE;
}

static inline bool hri_afec_get_IMR_COMPE_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_COMPE) >> AFEC_IMR_COMPE_Pos;
}

static inline void hri_afec_write_IMR_COMPE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_COMPE;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_COMPE;
	}
}

static inline void hri_afec_clear_IMR_COMPE_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_COMPE;
}

static inline void hri_afec_set_IMR_TEMPCHG_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IER = AFEC_IMR_TEMPCHG;
}

static inline bool hri_afec_get_IMR_TEMPCHG_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_IMR & AFEC_IMR_TEMPCHG) >> AFEC_IMR_TEMPCHG_Pos;
}

static inline void hri_afec_write_IMR_TEMPCHG_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Afec *)hw)->AFEC_IDR = AFEC_IMR_TEMPCHG;
	} else {
		((Afec *)hw)->AFEC_IER = AFEC_IMR_TEMPCHG;
	}
}

static inline void hri_afec_clear_IMR_TEMPCHG_bit(const void *const hw)
{
	((Afec *)hw)->AFEC_IDR = AFEC_IMR_TEMPCHG;
}

static inline void hri_afec_set_IMR_reg(const void *const hw, hri_afec_imr_reg_t mask)
{
	((Afec *)hw)->AFEC_IER = mask;
}

static inline hri_afec_imr_reg_t hri_afec_get_IMR_reg(const void *const hw, hri_afec_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_afec_imr_reg_t hri_afec_read_IMR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_IMR;
}

static inline void hri_afec_write_IMR_reg(const void *const hw, hri_afec_imr_reg_t data)
{
	((Afec *)hw)->AFEC_IER = data;
	((Afec *)hw)->AFEC_IDR = ~data;
}

static inline void hri_afec_clear_IMR_reg(const void *const hw, hri_afec_imr_reg_t mask)
{
	((Afec *)hw)->AFEC_IDR = mask;
}

static inline hri_afec_lcdr_reg_t hri_afec_get_LCDR_LDATA_bf(const void *const hw, hri_afec_lcdr_reg_t mask)
{
	return (((Afec *)hw)->AFEC_LCDR & AFEC_LCDR_LDATA(mask)) >> AFEC_LCDR_LDATA_Pos;
}

static inline hri_afec_lcdr_reg_t hri_afec_read_LCDR_LDATA_bf(const void *const hw)
{
	return (((Afec *)hw)->AFEC_LCDR & AFEC_LCDR_LDATA_Msk) >> AFEC_LCDR_LDATA_Pos;
}

static inline hri_afec_lcdr_reg_t hri_afec_get_LCDR_CHNB_bf(const void *const hw, hri_afec_lcdr_reg_t mask)
{
	return (((Afec *)hw)->AFEC_LCDR & AFEC_LCDR_CHNB(mask)) >> AFEC_LCDR_CHNB_Pos;
}

static inline hri_afec_lcdr_reg_t hri_afec_read_LCDR_CHNB_bf(const void *const hw)
{
	return (((Afec *)hw)->AFEC_LCDR & AFEC_LCDR_CHNB_Msk) >> AFEC_LCDR_CHNB_Pos;
}

static inline hri_afec_lcdr_reg_t hri_afec_get_LCDR_reg(const void *const hw, hri_afec_lcdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_LCDR;
	tmp &= mask;
	return tmp;
}

static inline hri_afec_lcdr_reg_t hri_afec_read_LCDR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_LCDR;
}

static inline bool hri_afec_get_OVER_OVRE0_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE0) > 0;
}

static inline bool hri_afec_get_OVER_OVRE1_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE1) > 0;
}

static inline bool hri_afec_get_OVER_OVRE2_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE2) > 0;
}

static inline bool hri_afec_get_OVER_OVRE3_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE3) > 0;
}

static inline bool hri_afec_get_OVER_OVRE4_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE4) > 0;
}

static inline bool hri_afec_get_OVER_OVRE5_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE5) > 0;
}

static inline bool hri_afec_get_OVER_OVRE6_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE6) > 0;
}

static inline bool hri_afec_get_OVER_OVRE7_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE7) > 0;
}

static inline bool hri_afec_get_OVER_OVRE8_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE8) > 0;
}

static inline bool hri_afec_get_OVER_OVRE9_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE9) > 0;
}

static inline bool hri_afec_get_OVER_OVRE10_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE10) > 0;
}

static inline bool hri_afec_get_OVER_OVRE11_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_OVER & AFEC_OVER_OVRE11) > 0;
}

static inline hri_afec_over_reg_t hri_afec_get_OVER_reg(const void *const hw, hri_afec_over_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_OVER;
	tmp &= mask;
	return tmp;
}

static inline hri_afec_over_reg_t hri_afec_read_OVER_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_OVER;
}

static inline hri_afec_cdr_reg_t hri_afec_get_CDR_DATA_bf(const void *const hw, hri_afec_cdr_reg_t mask)
{
	return (((Afec *)hw)->AFEC_CDR & AFEC_CDR_DATA(mask)) >> AFEC_CDR_DATA_Pos;
}

static inline hri_afec_cdr_reg_t hri_afec_read_CDR_DATA_bf(const void *const hw)
{
	return (((Afec *)hw)->AFEC_CDR & AFEC_CDR_DATA_Msk) >> AFEC_CDR_DATA_Pos;
}

static inline hri_afec_cdr_reg_t hri_afec_get_CDR_reg(const void *const hw, hri_afec_cdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CDR;
	tmp &= mask;
	return tmp;
}

static inline hri_afec_cdr_reg_t hri_afec_read_CDR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_CDR;
}

static inline bool hri_afec_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Afec *)hw)->AFEC_WPSR & AFEC_WPSR_WPVS) > 0;
}

static inline hri_afec_wpsr_reg_t hri_afec_get_WPSR_WPVSRC_bf(const void *const hw, hri_afec_wpsr_reg_t mask)
{
	return (((Afec *)hw)->AFEC_WPSR & AFEC_WPSR_WPVSRC(mask)) >> AFEC_WPSR_WPVSRC_Pos;
}

static inline hri_afec_wpsr_reg_t hri_afec_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Afec *)hw)->AFEC_WPSR & AFEC_WPSR_WPVSRC_Msk) >> AFEC_WPSR_WPVSRC_Pos;
}

static inline hri_afec_wpsr_reg_t hri_afec_get_WPSR_reg(const void *const hw, hri_afec_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_afec_wpsr_reg_t hri_afec_read_WPSR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_WPSR;
}

static inline void hri_afec_set_MR_TRGEN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_TRGEN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_MR_TRGEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_TRGEN) >> AFEC_MR_TRGEN_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_MR_TRGEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_TRGEN;
	tmp |= value << AFEC_MR_TRGEN_Pos;
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_TRGEN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_TRGEN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_TRGEN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_TRGEN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_MR_SLEEP_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_SLEEP;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_MR_SLEEP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_SLEEP) >> AFEC_MR_SLEEP_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_MR_SLEEP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_SLEEP;
	tmp |= value << AFEC_MR_SLEEP_Pos;
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_SLEEP_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_SLEEP;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_SLEEP_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_SLEEP;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_MR_FWUP_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_FWUP;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_MR_FWUP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_FWUP) >> AFEC_MR_FWUP_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_MR_FWUP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_FWUP;
	tmp |= value << AFEC_MR_FWUP_Pos;
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_FWUP_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_FWUP;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_FWUP_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_FWUP;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_MR_FREERUN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_FREERUN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_MR_FREERUN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_FREERUN) >> AFEC_MR_FREERUN_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_MR_FREERUN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_FREERUN;
	tmp |= value << AFEC_MR_FREERUN_Pos;
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_FREERUN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_FREERUN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_FREERUN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_FREERUN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_MR_ONE_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_ONE;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_MR_ONE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_ONE) >> AFEC_MR_ONE_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_MR_ONE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_ONE;
	tmp |= value << AFEC_MR_ONE_Pos;
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_ONE_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_ONE;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_ONE_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_ONE;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_MR_USEQ_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_USEQ;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_MR_USEQ_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_USEQ) >> AFEC_MR_USEQ_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_MR_USEQ_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_USEQ;
	tmp |= value << AFEC_MR_USEQ_Pos;
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_USEQ_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_USEQ;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_USEQ_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_USEQ;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_MR_TRGSEL_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_TRGSEL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_get_MR_TRGSEL_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_TRGSEL(mask)) >> AFEC_MR_TRGSEL_Pos;
	return tmp;
}

static inline void hri_afec_write_MR_TRGSEL_bf(const void *const hw, hri_afec_mr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_TRGSEL_Msk;
	tmp |= AFEC_MR_TRGSEL(data);
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_TRGSEL_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_TRGSEL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_TRGSEL_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_TRGSEL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_read_MR_TRGSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_TRGSEL_Msk) >> AFEC_MR_TRGSEL_Pos;
	return tmp;
}

static inline void hri_afec_set_MR_PRESCAL_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_PRESCAL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_get_MR_PRESCAL_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_PRESCAL(mask)) >> AFEC_MR_PRESCAL_Pos;
	return tmp;
}

static inline void hri_afec_write_MR_PRESCAL_bf(const void *const hw, hri_afec_mr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_PRESCAL_Msk;
	tmp |= AFEC_MR_PRESCAL(data);
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_PRESCAL_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_PRESCAL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_PRESCAL_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_PRESCAL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_read_MR_PRESCAL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_PRESCAL_Msk) >> AFEC_MR_PRESCAL_Pos;
	return tmp;
}

static inline void hri_afec_set_MR_STARTUP_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_STARTUP(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_get_MR_STARTUP_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_STARTUP(mask)) >> AFEC_MR_STARTUP_Pos;
	return tmp;
}

static inline void hri_afec_write_MR_STARTUP_bf(const void *const hw, hri_afec_mr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_STARTUP_Msk;
	tmp |= AFEC_MR_STARTUP(data);
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_STARTUP_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_STARTUP(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_STARTUP_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_STARTUP(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_read_MR_STARTUP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_STARTUP_Msk) >> AFEC_MR_STARTUP_Pos;
	return tmp;
}

static inline void hri_afec_set_MR_TRACKTIM_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_TRACKTIM(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_get_MR_TRACKTIM_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_TRACKTIM(mask)) >> AFEC_MR_TRACKTIM_Pos;
	return tmp;
}

static inline void hri_afec_write_MR_TRACKTIM_bf(const void *const hw, hri_afec_mr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_TRACKTIM_Msk;
	tmp |= AFEC_MR_TRACKTIM(data);
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_TRACKTIM_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_TRACKTIM(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_TRACKTIM_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_TRACKTIM(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_read_MR_TRACKTIM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_TRACKTIM_Msk) >> AFEC_MR_TRACKTIM_Pos;
	return tmp;
}

static inline void hri_afec_set_MR_TRANSFER_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= AFEC_MR_TRANSFER(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_get_MR_TRANSFER_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_TRANSFER(mask)) >> AFEC_MR_TRANSFER_Pos;
	return tmp;
}

static inline void hri_afec_write_MR_TRANSFER_bf(const void *const hw, hri_afec_mr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= ~AFEC_MR_TRANSFER_Msk;
	tmp |= AFEC_MR_TRANSFER(data);
	((Afec *)hw)->AFEC_MR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_TRANSFER_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~AFEC_MR_TRANSFER(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_TRANSFER_bf(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= AFEC_MR_TRANSFER(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_read_MR_TRANSFER_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp = (tmp & AFEC_MR_TRANSFER_Msk) >> AFEC_MR_TRANSFER_Pos;
	return tmp;
}

static inline void hri_afec_set_MR_reg(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_get_MR_reg(const void *const hw, hri_afec_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_MR_reg(const void *const hw, hri_afec_mr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_MR_reg(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_MR_reg(const void *const hw, hri_afec_mr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_MR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_mr_reg_t hri_afec_read_MR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_MR;
}

static inline void hri_afec_set_EMR_CMPALL_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR |= AFEC_EMR_CMPALL;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_EMR_CMPALL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_CMPALL) >> AFEC_EMR_CMPALL_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_EMR_CMPALL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp &= ~AFEC_EMR_CMPALL;
	tmp |= value << AFEC_EMR_CMPALL_Pos;
	((Afec *)hw)->AFEC_EMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_EMR_CMPALL_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR &= ~AFEC_EMR_CMPALL;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_EMR_CMPALL_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR ^= AFEC_EMR_CMPALL;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_EMR_TAG_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR |= AFEC_EMR_TAG;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_EMR_TAG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_TAG) >> AFEC_EMR_TAG_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_EMR_TAG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp &= ~AFEC_EMR_TAG;
	tmp |= value << AFEC_EMR_TAG_Pos;
	((Afec *)hw)->AFEC_EMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_EMR_TAG_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR &= ~AFEC_EMR_TAG;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_EMR_TAG_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR ^= AFEC_EMR_TAG;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_EMR_STM_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR |= AFEC_EMR_STM;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_EMR_STM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_STM) >> AFEC_EMR_STM_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_EMR_STM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp &= ~AFEC_EMR_STM;
	tmp |= value << AFEC_EMR_STM_Pos;
	((Afec *)hw)->AFEC_EMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_EMR_STM_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR &= ~AFEC_EMR_STM;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_EMR_STM_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR ^= AFEC_EMR_STM;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_EMR_CMPMODE_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR |= AFEC_EMR_CMPMODE(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_get_EMR_CMPMODE_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_CMPMODE(mask)) >> AFEC_EMR_CMPMODE_Pos;
	return tmp;
}

static inline void hri_afec_write_EMR_CMPMODE_bf(const void *const hw, hri_afec_emr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp &= ~AFEC_EMR_CMPMODE_Msk;
	tmp |= AFEC_EMR_CMPMODE(data);
	((Afec *)hw)->AFEC_EMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_EMR_CMPMODE_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR &= ~AFEC_EMR_CMPMODE(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_EMR_CMPMODE_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR ^= AFEC_EMR_CMPMODE(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_read_EMR_CMPMODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_CMPMODE_Msk) >> AFEC_EMR_CMPMODE_Pos;
	return tmp;
}

static inline void hri_afec_set_EMR_CMPSEL_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR |= AFEC_EMR_CMPSEL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_get_EMR_CMPSEL_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_CMPSEL(mask)) >> AFEC_EMR_CMPSEL_Pos;
	return tmp;
}

static inline void hri_afec_write_EMR_CMPSEL_bf(const void *const hw, hri_afec_emr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp &= ~AFEC_EMR_CMPSEL_Msk;
	tmp |= AFEC_EMR_CMPSEL(data);
	((Afec *)hw)->AFEC_EMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_EMR_CMPSEL_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR &= ~AFEC_EMR_CMPSEL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_EMR_CMPSEL_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR ^= AFEC_EMR_CMPSEL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_read_EMR_CMPSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_CMPSEL_Msk) >> AFEC_EMR_CMPSEL_Pos;
	return tmp;
}

static inline void hri_afec_set_EMR_CMPFILTER_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR |= AFEC_EMR_CMPFILTER(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_get_EMR_CMPFILTER_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_CMPFILTER(mask)) >> AFEC_EMR_CMPFILTER_Pos;
	return tmp;
}

static inline void hri_afec_write_EMR_CMPFILTER_bf(const void *const hw, hri_afec_emr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp &= ~AFEC_EMR_CMPFILTER_Msk;
	tmp |= AFEC_EMR_CMPFILTER(data);
	((Afec *)hw)->AFEC_EMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_EMR_CMPFILTER_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR &= ~AFEC_EMR_CMPFILTER(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_EMR_CMPFILTER_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR ^= AFEC_EMR_CMPFILTER(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_read_EMR_CMPFILTER_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_CMPFILTER_Msk) >> AFEC_EMR_CMPFILTER_Pos;
	return tmp;
}

static inline void hri_afec_set_EMR_RES_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR |= AFEC_EMR_RES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_get_EMR_RES_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_RES(mask)) >> AFEC_EMR_RES_Pos;
	return tmp;
}

static inline void hri_afec_write_EMR_RES_bf(const void *const hw, hri_afec_emr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp &= ~AFEC_EMR_RES_Msk;
	tmp |= AFEC_EMR_RES(data);
	((Afec *)hw)->AFEC_EMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_EMR_RES_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR &= ~AFEC_EMR_RES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_EMR_RES_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR ^= AFEC_EMR_RES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_read_EMR_RES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_RES_Msk) >> AFEC_EMR_RES_Pos;
	return tmp;
}

static inline void hri_afec_set_EMR_SIGNMODE_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR |= AFEC_EMR_SIGNMODE(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_get_EMR_SIGNMODE_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_SIGNMODE(mask)) >> AFEC_EMR_SIGNMODE_Pos;
	return tmp;
}

static inline void hri_afec_write_EMR_SIGNMODE_bf(const void *const hw, hri_afec_emr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp &= ~AFEC_EMR_SIGNMODE_Msk;
	tmp |= AFEC_EMR_SIGNMODE(data);
	((Afec *)hw)->AFEC_EMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_EMR_SIGNMODE_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR &= ~AFEC_EMR_SIGNMODE(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_EMR_SIGNMODE_bf(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR ^= AFEC_EMR_SIGNMODE(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_read_EMR_SIGNMODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp = (tmp & AFEC_EMR_SIGNMODE_Msk) >> AFEC_EMR_SIGNMODE_Pos;
	return tmp;
}

static inline void hri_afec_set_EMR_reg(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_get_EMR_reg(const void *const hw, hri_afec_emr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_EMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_EMR_reg(const void *const hw, hri_afec_emr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_EMR_reg(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_EMR_reg(const void *const hw, hri_afec_emr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_EMR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_emr_reg_t hri_afec_read_EMR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_EMR;
}

static inline void hri_afec_set_SEQ1R_USCH0_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R |= AFEC_SEQ1R_USCH0(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_get_SEQ1R_USCH0_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH0(mask)) >> AFEC_SEQ1R_USCH0_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ1R_USCH0_bf(const void *const hw, hri_afec_seq1r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp &= ~AFEC_SEQ1R_USCH0_Msk;
	tmp |= AFEC_SEQ1R_USCH0(data);
	((Afec *)hw)->AFEC_SEQ1R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ1R_USCH0_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R &= ~AFEC_SEQ1R_USCH0(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ1R_USCH0_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R ^= AFEC_SEQ1R_USCH0(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_read_SEQ1R_USCH0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH0_Msk) >> AFEC_SEQ1R_USCH0_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ1R_USCH1_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R |= AFEC_SEQ1R_USCH1(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_get_SEQ1R_USCH1_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH1(mask)) >> AFEC_SEQ1R_USCH1_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ1R_USCH1_bf(const void *const hw, hri_afec_seq1r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp &= ~AFEC_SEQ1R_USCH1_Msk;
	tmp |= AFEC_SEQ1R_USCH1(data);
	((Afec *)hw)->AFEC_SEQ1R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ1R_USCH1_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R &= ~AFEC_SEQ1R_USCH1(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ1R_USCH1_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R ^= AFEC_SEQ1R_USCH1(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_read_SEQ1R_USCH1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH1_Msk) >> AFEC_SEQ1R_USCH1_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ1R_USCH2_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R |= AFEC_SEQ1R_USCH2(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_get_SEQ1R_USCH2_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH2(mask)) >> AFEC_SEQ1R_USCH2_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ1R_USCH2_bf(const void *const hw, hri_afec_seq1r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp &= ~AFEC_SEQ1R_USCH2_Msk;
	tmp |= AFEC_SEQ1R_USCH2(data);
	((Afec *)hw)->AFEC_SEQ1R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ1R_USCH2_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R &= ~AFEC_SEQ1R_USCH2(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ1R_USCH2_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R ^= AFEC_SEQ1R_USCH2(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_read_SEQ1R_USCH2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH2_Msk) >> AFEC_SEQ1R_USCH2_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ1R_USCH3_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R |= AFEC_SEQ1R_USCH3(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_get_SEQ1R_USCH3_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH3(mask)) >> AFEC_SEQ1R_USCH3_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ1R_USCH3_bf(const void *const hw, hri_afec_seq1r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp &= ~AFEC_SEQ1R_USCH3_Msk;
	tmp |= AFEC_SEQ1R_USCH3(data);
	((Afec *)hw)->AFEC_SEQ1R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ1R_USCH3_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R &= ~AFEC_SEQ1R_USCH3(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ1R_USCH3_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R ^= AFEC_SEQ1R_USCH3(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_read_SEQ1R_USCH3_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH3_Msk) >> AFEC_SEQ1R_USCH3_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ1R_USCH4_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R |= AFEC_SEQ1R_USCH4(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_get_SEQ1R_USCH4_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH4(mask)) >> AFEC_SEQ1R_USCH4_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ1R_USCH4_bf(const void *const hw, hri_afec_seq1r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp &= ~AFEC_SEQ1R_USCH4_Msk;
	tmp |= AFEC_SEQ1R_USCH4(data);
	((Afec *)hw)->AFEC_SEQ1R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ1R_USCH4_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R &= ~AFEC_SEQ1R_USCH4(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ1R_USCH4_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R ^= AFEC_SEQ1R_USCH4(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_read_SEQ1R_USCH4_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH4_Msk) >> AFEC_SEQ1R_USCH4_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ1R_USCH5_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R |= AFEC_SEQ1R_USCH5(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_get_SEQ1R_USCH5_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH5(mask)) >> AFEC_SEQ1R_USCH5_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ1R_USCH5_bf(const void *const hw, hri_afec_seq1r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp &= ~AFEC_SEQ1R_USCH5_Msk;
	tmp |= AFEC_SEQ1R_USCH5(data);
	((Afec *)hw)->AFEC_SEQ1R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ1R_USCH5_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R &= ~AFEC_SEQ1R_USCH5(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ1R_USCH5_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R ^= AFEC_SEQ1R_USCH5(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_read_SEQ1R_USCH5_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH5_Msk) >> AFEC_SEQ1R_USCH5_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ1R_USCH6_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R |= AFEC_SEQ1R_USCH6(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_get_SEQ1R_USCH6_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH6(mask)) >> AFEC_SEQ1R_USCH6_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ1R_USCH6_bf(const void *const hw, hri_afec_seq1r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp &= ~AFEC_SEQ1R_USCH6_Msk;
	tmp |= AFEC_SEQ1R_USCH6(data);
	((Afec *)hw)->AFEC_SEQ1R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ1R_USCH6_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R &= ~AFEC_SEQ1R_USCH6(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ1R_USCH6_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R ^= AFEC_SEQ1R_USCH6(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_read_SEQ1R_USCH6_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH6_Msk) >> AFEC_SEQ1R_USCH6_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ1R_USCH7_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R |= AFEC_SEQ1R_USCH7(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_get_SEQ1R_USCH7_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH7(mask)) >> AFEC_SEQ1R_USCH7_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ1R_USCH7_bf(const void *const hw, hri_afec_seq1r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp &= ~AFEC_SEQ1R_USCH7_Msk;
	tmp |= AFEC_SEQ1R_USCH7(data);
	((Afec *)hw)->AFEC_SEQ1R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ1R_USCH7_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R &= ~AFEC_SEQ1R_USCH7(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ1R_USCH7_bf(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R ^= AFEC_SEQ1R_USCH7(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_read_SEQ1R_USCH7_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp = (tmp & AFEC_SEQ1R_USCH7_Msk) >> AFEC_SEQ1R_USCH7_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ1R_reg(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_get_SEQ1R_reg(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ1R;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_SEQ1R_reg(const void *const hw, hri_afec_seq1r_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ1R_reg(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ1R_reg(const void *const hw, hri_afec_seq1r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ1R ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq1r_reg_t hri_afec_read_SEQ1R_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_SEQ1R;
}

static inline void hri_afec_set_SEQ2R_USCH8_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R |= AFEC_SEQ2R_USCH8(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_get_SEQ2R_USCH8_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp = (tmp & AFEC_SEQ2R_USCH8(mask)) >> AFEC_SEQ2R_USCH8_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ2R_USCH8_bf(const void *const hw, hri_afec_seq2r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp &= ~AFEC_SEQ2R_USCH8_Msk;
	tmp |= AFEC_SEQ2R_USCH8(data);
	((Afec *)hw)->AFEC_SEQ2R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ2R_USCH8_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R &= ~AFEC_SEQ2R_USCH8(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ2R_USCH8_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R ^= AFEC_SEQ2R_USCH8(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_read_SEQ2R_USCH8_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp = (tmp & AFEC_SEQ2R_USCH8_Msk) >> AFEC_SEQ2R_USCH8_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ2R_USCH9_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R |= AFEC_SEQ2R_USCH9(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_get_SEQ2R_USCH9_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp = (tmp & AFEC_SEQ2R_USCH9(mask)) >> AFEC_SEQ2R_USCH9_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ2R_USCH9_bf(const void *const hw, hri_afec_seq2r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp &= ~AFEC_SEQ2R_USCH9_Msk;
	tmp |= AFEC_SEQ2R_USCH9(data);
	((Afec *)hw)->AFEC_SEQ2R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ2R_USCH9_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R &= ~AFEC_SEQ2R_USCH9(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ2R_USCH9_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R ^= AFEC_SEQ2R_USCH9(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_read_SEQ2R_USCH9_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp = (tmp & AFEC_SEQ2R_USCH9_Msk) >> AFEC_SEQ2R_USCH9_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ2R_USCH10_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R |= AFEC_SEQ2R_USCH10(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_get_SEQ2R_USCH10_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp = (tmp & AFEC_SEQ2R_USCH10(mask)) >> AFEC_SEQ2R_USCH10_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ2R_USCH10_bf(const void *const hw, hri_afec_seq2r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp &= ~AFEC_SEQ2R_USCH10_Msk;
	tmp |= AFEC_SEQ2R_USCH10(data);
	((Afec *)hw)->AFEC_SEQ2R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ2R_USCH10_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R &= ~AFEC_SEQ2R_USCH10(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ2R_USCH10_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R ^= AFEC_SEQ2R_USCH10(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_read_SEQ2R_USCH10_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp = (tmp & AFEC_SEQ2R_USCH10_Msk) >> AFEC_SEQ2R_USCH10_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ2R_USCH11_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R |= AFEC_SEQ2R_USCH11(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_get_SEQ2R_USCH11_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp = (tmp & AFEC_SEQ2R_USCH11(mask)) >> AFEC_SEQ2R_USCH11_Pos;
	return tmp;
}

static inline void hri_afec_write_SEQ2R_USCH11_bf(const void *const hw, hri_afec_seq2r_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp &= ~AFEC_SEQ2R_USCH11_Msk;
	tmp |= AFEC_SEQ2R_USCH11(data);
	((Afec *)hw)->AFEC_SEQ2R = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ2R_USCH11_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R &= ~AFEC_SEQ2R_USCH11(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ2R_USCH11_bf(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R ^= AFEC_SEQ2R_USCH11(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_read_SEQ2R_USCH11_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp = (tmp & AFEC_SEQ2R_USCH11_Msk) >> AFEC_SEQ2R_USCH11_Pos;
	return tmp;
}

static inline void hri_afec_set_SEQ2R_reg(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_get_SEQ2R_reg(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SEQ2R;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_SEQ2R_reg(const void *const hw, hri_afec_seq2r_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SEQ2R_reg(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SEQ2R_reg(const void *const hw, hri_afec_seq2r_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SEQ2R ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_seq2r_reg_t hri_afec_read_SEQ2R_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_SEQ2R;
}

static inline void hri_afec_set_CWR_LOWTHRES_bf(const void *const hw, hri_afec_cwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR |= AFEC_CWR_LOWTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cwr_reg_t hri_afec_get_CWR_LOWTHRES_bf(const void *const hw, hri_afec_cwr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CWR;
	tmp = (tmp & AFEC_CWR_LOWTHRES(mask)) >> AFEC_CWR_LOWTHRES_Pos;
	return tmp;
}

static inline void hri_afec_write_CWR_LOWTHRES_bf(const void *const hw, hri_afec_cwr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CWR;
	tmp &= ~AFEC_CWR_LOWTHRES_Msk;
	tmp |= AFEC_CWR_LOWTHRES(data);
	((Afec *)hw)->AFEC_CWR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CWR_LOWTHRES_bf(const void *const hw, hri_afec_cwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR &= ~AFEC_CWR_LOWTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CWR_LOWTHRES_bf(const void *const hw, hri_afec_cwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR ^= AFEC_CWR_LOWTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cwr_reg_t hri_afec_read_CWR_LOWTHRES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CWR;
	tmp = (tmp & AFEC_CWR_LOWTHRES_Msk) >> AFEC_CWR_LOWTHRES_Pos;
	return tmp;
}

static inline void hri_afec_set_CWR_HIGHTHRES_bf(const void *const hw, hri_afec_cwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR |= AFEC_CWR_HIGHTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cwr_reg_t hri_afec_get_CWR_HIGHTHRES_bf(const void *const hw, hri_afec_cwr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CWR;
	tmp = (tmp & AFEC_CWR_HIGHTHRES(mask)) >> AFEC_CWR_HIGHTHRES_Pos;
	return tmp;
}

static inline void hri_afec_write_CWR_HIGHTHRES_bf(const void *const hw, hri_afec_cwr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CWR;
	tmp &= ~AFEC_CWR_HIGHTHRES_Msk;
	tmp |= AFEC_CWR_HIGHTHRES(data);
	((Afec *)hw)->AFEC_CWR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CWR_HIGHTHRES_bf(const void *const hw, hri_afec_cwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR &= ~AFEC_CWR_HIGHTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CWR_HIGHTHRES_bf(const void *const hw, hri_afec_cwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR ^= AFEC_CWR_HIGHTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cwr_reg_t hri_afec_read_CWR_HIGHTHRES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CWR;
	tmp = (tmp & AFEC_CWR_HIGHTHRES_Msk) >> AFEC_CWR_HIGHTHRES_Pos;
	return tmp;
}

static inline void hri_afec_set_CWR_reg(const void *const hw, hri_afec_cwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cwr_reg_t hri_afec_get_CWR_reg(const void *const hw, hri_afec_cwr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CWR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_CWR_reg(const void *const hw, hri_afec_cwr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CWR_reg(const void *const hw, hri_afec_cwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CWR_reg(const void *const hw, hri_afec_cwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CWR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cwr_reg_t hri_afec_read_CWR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_CWR;
}

static inline void hri_afec_set_CGR_GAIN0_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN0(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN0_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN0(mask)) >> AFEC_CGR_GAIN0_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN0_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN0_Msk;
	tmp |= AFEC_CGR_GAIN0(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN0_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN0(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN0_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN0(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN0_Msk) >> AFEC_CGR_GAIN0_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN1_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN1(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN1_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN1(mask)) >> AFEC_CGR_GAIN1_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN1_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN1_Msk;
	tmp |= AFEC_CGR_GAIN1(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN1_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN1(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN1_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN1(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN1_Msk) >> AFEC_CGR_GAIN1_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN2_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN2(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN2_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN2(mask)) >> AFEC_CGR_GAIN2_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN2_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN2_Msk;
	tmp |= AFEC_CGR_GAIN2(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN2_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN2(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN2_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN2(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN2_Msk) >> AFEC_CGR_GAIN2_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN3_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN3(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN3_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN3(mask)) >> AFEC_CGR_GAIN3_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN3_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN3_Msk;
	tmp |= AFEC_CGR_GAIN3(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN3_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN3(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN3_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN3(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN3_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN3_Msk) >> AFEC_CGR_GAIN3_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN4_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN4(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN4_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN4(mask)) >> AFEC_CGR_GAIN4_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN4_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN4_Msk;
	tmp |= AFEC_CGR_GAIN4(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN4_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN4(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN4_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN4(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN4_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN4_Msk) >> AFEC_CGR_GAIN4_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN5_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN5(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN5_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN5(mask)) >> AFEC_CGR_GAIN5_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN5_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN5_Msk;
	tmp |= AFEC_CGR_GAIN5(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN5_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN5(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN5_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN5(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN5_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN5_Msk) >> AFEC_CGR_GAIN5_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN6_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN6(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN6_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN6(mask)) >> AFEC_CGR_GAIN6_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN6_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN6_Msk;
	tmp |= AFEC_CGR_GAIN6(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN6_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN6(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN6_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN6(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN6_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN6_Msk) >> AFEC_CGR_GAIN6_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN7_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN7(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN7_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN7(mask)) >> AFEC_CGR_GAIN7_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN7_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN7_Msk;
	tmp |= AFEC_CGR_GAIN7(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN7_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN7(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN7_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN7(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN7_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN7_Msk) >> AFEC_CGR_GAIN7_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN8_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN8(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN8_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN8(mask)) >> AFEC_CGR_GAIN8_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN8_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN8_Msk;
	tmp |= AFEC_CGR_GAIN8(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN8_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN8(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN8_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN8(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN8_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN8_Msk) >> AFEC_CGR_GAIN8_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN9_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN9(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN9_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN9(mask)) >> AFEC_CGR_GAIN9_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN9_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN9_Msk;
	tmp |= AFEC_CGR_GAIN9(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN9_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN9(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN9_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN9(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN9_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN9_Msk) >> AFEC_CGR_GAIN9_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN10_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN10(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN10_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN10(mask)) >> AFEC_CGR_GAIN10_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN10_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN10_Msk;
	tmp |= AFEC_CGR_GAIN10(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN10_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN10(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN10_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN10(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN10_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN10_Msk) >> AFEC_CGR_GAIN10_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_GAIN11_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= AFEC_CGR_GAIN11(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_GAIN11_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN11(mask)) >> AFEC_CGR_GAIN11_Pos;
	return tmp;
}

static inline void hri_afec_write_CGR_GAIN11_bf(const void *const hw, hri_afec_cgr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= ~AFEC_CGR_GAIN11_Msk;
	tmp |= AFEC_CGR_GAIN11(data);
	((Afec *)hw)->AFEC_CGR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_GAIN11_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~AFEC_CGR_GAIN11(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_GAIN11_bf(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= AFEC_CGR_GAIN11(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_GAIN11_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp = (tmp & AFEC_CGR_GAIN11_Msk) >> AFEC_CGR_GAIN11_Pos;
	return tmp;
}

static inline void hri_afec_set_CGR_reg(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_get_CGR_reg(const void *const hw, hri_afec_cgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CGR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_CGR_reg(const void *const hw, hri_afec_cgr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CGR_reg(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CGR_reg(const void *const hw, hri_afec_cgr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CGR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cgr_reg_t hri_afec_read_CGR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_CGR;
}

static inline void hri_afec_set_DIFFR_DIFF0_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF0;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF0) >> AFEC_DIFFR_DIFF0_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF0;
	tmp |= value << AFEC_DIFFR_DIFF0_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF0_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF0;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF0_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF0;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF1_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF1;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF1) >> AFEC_DIFFR_DIFF1_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF1;
	tmp |= value << AFEC_DIFFR_DIFF1_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF1_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF1;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF1_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF1;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF2_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF2;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF2) >> AFEC_DIFFR_DIFF2_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF2;
	tmp |= value << AFEC_DIFFR_DIFF2_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF2_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF2;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF2_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF2;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF3_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF3;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF3) >> AFEC_DIFFR_DIFF3_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF3;
	tmp |= value << AFEC_DIFFR_DIFF3_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF3_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF3;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF3_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF3;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF4_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF4;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF4) >> AFEC_DIFFR_DIFF4_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF4;
	tmp |= value << AFEC_DIFFR_DIFF4_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF4_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF4;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF4_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF4;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF5_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF5;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF5) >> AFEC_DIFFR_DIFF5_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF5;
	tmp |= value << AFEC_DIFFR_DIFF5_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF5_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF5;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF5_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF5;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF6_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF6;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF6) >> AFEC_DIFFR_DIFF6_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF6;
	tmp |= value << AFEC_DIFFR_DIFF6_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF6_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF6;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF6_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF6;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF7_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF7;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF7) >> AFEC_DIFFR_DIFF7_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF7;
	tmp |= value << AFEC_DIFFR_DIFF7_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF7_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF7;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF7_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF7;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF8_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF8;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF8) >> AFEC_DIFFR_DIFF8_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF8;
	tmp |= value << AFEC_DIFFR_DIFF8_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF8_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF8;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF8_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF8;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF9_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF9;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF9) >> AFEC_DIFFR_DIFF9_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF9;
	tmp |= value << AFEC_DIFFR_DIFF9_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF9_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF9;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF9_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF9;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF10_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF10;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF10) >> AFEC_DIFFR_DIFF10_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF10;
	tmp |= value << AFEC_DIFFR_DIFF10_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF10_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF10;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF10_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF10;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_DIFF11_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= AFEC_DIFFR_DIFF11;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_DIFFR_DIFF11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp = (tmp & AFEC_DIFFR_DIFF11) >> AFEC_DIFFR_DIFF11_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_DIFFR_DIFF11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= ~AFEC_DIFFR_DIFF11;
	tmp |= value << AFEC_DIFFR_DIFF11_Pos;
	((Afec *)hw)->AFEC_DIFFR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_DIFF11_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~AFEC_DIFFR_DIFF11;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_DIFF11_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= AFEC_DIFFR_DIFF11;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_DIFFR_reg(const void *const hw, hri_afec_diffr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_diffr_reg_t hri_afec_get_DIFFR_reg(const void *const hw, hri_afec_diffr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_DIFFR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_DIFFR_reg(const void *const hw, hri_afec_diffr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_DIFFR_reg(const void *const hw, hri_afec_diffr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_DIFFR_reg(const void *const hw, hri_afec_diffr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_DIFFR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_diffr_reg_t hri_afec_read_DIFFR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_DIFFR;
}

static inline void hri_afec_set_CSELR_CSEL_bf(const void *const hw, hri_afec_cselr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CSELR |= AFEC_CSELR_CSEL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cselr_reg_t hri_afec_get_CSELR_CSEL_bf(const void *const hw, hri_afec_cselr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CSELR;
	tmp = (tmp & AFEC_CSELR_CSEL(mask)) >> AFEC_CSELR_CSEL_Pos;
	return tmp;
}

static inline void hri_afec_write_CSELR_CSEL_bf(const void *const hw, hri_afec_cselr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CSELR;
	tmp &= ~AFEC_CSELR_CSEL_Msk;
	tmp |= AFEC_CSELR_CSEL(data);
	((Afec *)hw)->AFEC_CSELR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CSELR_CSEL_bf(const void *const hw, hri_afec_cselr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CSELR &= ~AFEC_CSELR_CSEL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CSELR_CSEL_bf(const void *const hw, hri_afec_cselr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CSELR ^= AFEC_CSELR_CSEL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cselr_reg_t hri_afec_read_CSELR_CSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CSELR;
	tmp = (tmp & AFEC_CSELR_CSEL_Msk) >> AFEC_CSELR_CSEL_Pos;
	return tmp;
}

static inline void hri_afec_set_CSELR_reg(const void *const hw, hri_afec_cselr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CSELR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cselr_reg_t hri_afec_get_CSELR_reg(const void *const hw, hri_afec_cselr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CSELR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_CSELR_reg(const void *const hw, hri_afec_cselr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CSELR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CSELR_reg(const void *const hw, hri_afec_cselr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CSELR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CSELR_reg(const void *const hw, hri_afec_cselr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CSELR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cselr_reg_t hri_afec_read_CSELR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_CSELR;
}

static inline void hri_afec_set_COCR_AOFF_bf(const void *const hw, hri_afec_cocr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COCR |= AFEC_COCR_AOFF(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cocr_reg_t hri_afec_get_COCR_AOFF_bf(const void *const hw, hri_afec_cocr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_COCR;
	tmp = (tmp & AFEC_COCR_AOFF(mask)) >> AFEC_COCR_AOFF_Pos;
	return tmp;
}

static inline void hri_afec_write_COCR_AOFF_bf(const void *const hw, hri_afec_cocr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_COCR;
	tmp &= ~AFEC_COCR_AOFF_Msk;
	tmp |= AFEC_COCR_AOFF(data);
	((Afec *)hw)->AFEC_COCR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_COCR_AOFF_bf(const void *const hw, hri_afec_cocr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COCR &= ~AFEC_COCR_AOFF(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_COCR_AOFF_bf(const void *const hw, hri_afec_cocr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COCR ^= AFEC_COCR_AOFF(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cocr_reg_t hri_afec_read_COCR_AOFF_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_COCR;
	tmp = (tmp & AFEC_COCR_AOFF_Msk) >> AFEC_COCR_AOFF_Pos;
	return tmp;
}

static inline void hri_afec_set_COCR_reg(const void *const hw, hri_afec_cocr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COCR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cocr_reg_t hri_afec_get_COCR_reg(const void *const hw, hri_afec_cocr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_COCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_COCR_reg(const void *const hw, hri_afec_cocr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COCR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_COCR_reg(const void *const hw, hri_afec_cocr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COCR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_COCR_reg(const void *const hw, hri_afec_cocr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COCR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cocr_reg_t hri_afec_read_COCR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_COCR;
}

static inline void hri_afec_set_TEMPMR_RTCT_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR |= AFEC_TEMPMR_RTCT;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_TEMPMR_RTCT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_TEMPMR;
	tmp = (tmp & AFEC_TEMPMR_RTCT) >> AFEC_TEMPMR_RTCT_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_TEMPMR_RTCT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_TEMPMR;
	tmp &= ~AFEC_TEMPMR_RTCT;
	tmp |= value << AFEC_TEMPMR_RTCT_Pos;
	((Afec *)hw)->AFEC_TEMPMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_TEMPMR_RTCT_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR &= ~AFEC_TEMPMR_RTCT;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_TEMPMR_RTCT_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR ^= AFEC_TEMPMR_RTCT;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_TEMPMR_TEMPCMPMOD_bf(const void *const hw, hri_afec_tempmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR |= AFEC_TEMPMR_TEMPCMPMOD(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempmr_reg_t hri_afec_get_TEMPMR_TEMPCMPMOD_bf(const void *const hw, hri_afec_tempmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_TEMPMR;
	tmp = (tmp & AFEC_TEMPMR_TEMPCMPMOD(mask)) >> AFEC_TEMPMR_TEMPCMPMOD_Pos;
	return tmp;
}

static inline void hri_afec_write_TEMPMR_TEMPCMPMOD_bf(const void *const hw, hri_afec_tempmr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_TEMPMR;
	tmp &= ~AFEC_TEMPMR_TEMPCMPMOD_Msk;
	tmp |= AFEC_TEMPMR_TEMPCMPMOD(data);
	((Afec *)hw)->AFEC_TEMPMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_TEMPMR_TEMPCMPMOD_bf(const void *const hw, hri_afec_tempmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR &= ~AFEC_TEMPMR_TEMPCMPMOD(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_TEMPMR_TEMPCMPMOD_bf(const void *const hw, hri_afec_tempmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR ^= AFEC_TEMPMR_TEMPCMPMOD(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempmr_reg_t hri_afec_read_TEMPMR_TEMPCMPMOD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_TEMPMR;
	tmp = (tmp & AFEC_TEMPMR_TEMPCMPMOD_Msk) >> AFEC_TEMPMR_TEMPCMPMOD_Pos;
	return tmp;
}

static inline void hri_afec_set_TEMPMR_reg(const void *const hw, hri_afec_tempmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempmr_reg_t hri_afec_get_TEMPMR_reg(const void *const hw, hri_afec_tempmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_TEMPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_TEMPMR_reg(const void *const hw, hri_afec_tempmr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_TEMPMR_reg(const void *const hw, hri_afec_tempmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_TEMPMR_reg(const void *const hw, hri_afec_tempmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPMR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempmr_reg_t hri_afec_read_TEMPMR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_TEMPMR;
}

static inline void hri_afec_set_TEMPCWR_TLOWTHRES_bf(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR |= AFEC_TEMPCWR_TLOWTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempcwr_reg_t hri_afec_get_TEMPCWR_TLOWTHRES_bf(const void *const      hw,
                                                                       hri_afec_tempcwr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_TEMPCWR;
	tmp = (tmp & AFEC_TEMPCWR_TLOWTHRES(mask)) >> AFEC_TEMPCWR_TLOWTHRES_Pos;
	return tmp;
}

static inline void hri_afec_write_TEMPCWR_TLOWTHRES_bf(const void *const hw, hri_afec_tempcwr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_TEMPCWR;
	tmp &= ~AFEC_TEMPCWR_TLOWTHRES_Msk;
	tmp |= AFEC_TEMPCWR_TLOWTHRES(data);
	((Afec *)hw)->AFEC_TEMPCWR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_TEMPCWR_TLOWTHRES_bf(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR &= ~AFEC_TEMPCWR_TLOWTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_TEMPCWR_TLOWTHRES_bf(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR ^= AFEC_TEMPCWR_TLOWTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempcwr_reg_t hri_afec_read_TEMPCWR_TLOWTHRES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_TEMPCWR;
	tmp = (tmp & AFEC_TEMPCWR_TLOWTHRES_Msk) >> AFEC_TEMPCWR_TLOWTHRES_Pos;
	return tmp;
}

static inline void hri_afec_set_TEMPCWR_THIGHTHRES_bf(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR |= AFEC_TEMPCWR_THIGHTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempcwr_reg_t hri_afec_get_TEMPCWR_THIGHTHRES_bf(const void *const      hw,
                                                                        hri_afec_tempcwr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_TEMPCWR;
	tmp = (tmp & AFEC_TEMPCWR_THIGHTHRES(mask)) >> AFEC_TEMPCWR_THIGHTHRES_Pos;
	return tmp;
}

static inline void hri_afec_write_TEMPCWR_THIGHTHRES_bf(const void *const hw, hri_afec_tempcwr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_TEMPCWR;
	tmp &= ~AFEC_TEMPCWR_THIGHTHRES_Msk;
	tmp |= AFEC_TEMPCWR_THIGHTHRES(data);
	((Afec *)hw)->AFEC_TEMPCWR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_TEMPCWR_THIGHTHRES_bf(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR &= ~AFEC_TEMPCWR_THIGHTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_TEMPCWR_THIGHTHRES_bf(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR ^= AFEC_TEMPCWR_THIGHTHRES(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempcwr_reg_t hri_afec_read_TEMPCWR_THIGHTHRES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_TEMPCWR;
	tmp = (tmp & AFEC_TEMPCWR_THIGHTHRES_Msk) >> AFEC_TEMPCWR_THIGHTHRES_Pos;
	return tmp;
}

static inline void hri_afec_set_TEMPCWR_reg(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempcwr_reg_t hri_afec_get_TEMPCWR_reg(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_TEMPCWR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_TEMPCWR_reg(const void *const hw, hri_afec_tempcwr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_TEMPCWR_reg(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_TEMPCWR_reg(const void *const hw, hri_afec_tempcwr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_TEMPCWR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_tempcwr_reg_t hri_afec_read_TEMPCWR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_TEMPCWR;
}

static inline void hri_afec_set_ACR_PGA0EN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR |= AFEC_ACR_PGA0EN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_ACR_PGA0EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_ACR;
	tmp = (tmp & AFEC_ACR_PGA0EN) >> AFEC_ACR_PGA0EN_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_ACR_PGA0EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_ACR;
	tmp &= ~AFEC_ACR_PGA0EN;
	tmp |= value << AFEC_ACR_PGA0EN_Pos;
	((Afec *)hw)->AFEC_ACR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_ACR_PGA0EN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR &= ~AFEC_ACR_PGA0EN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_ACR_PGA0EN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR ^= AFEC_ACR_PGA0EN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_ACR_PGA1EN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR |= AFEC_ACR_PGA1EN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_ACR_PGA1EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_ACR;
	tmp = (tmp & AFEC_ACR_PGA1EN) >> AFEC_ACR_PGA1EN_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_ACR_PGA1EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_ACR;
	tmp &= ~AFEC_ACR_PGA1EN;
	tmp |= value << AFEC_ACR_PGA1EN_Pos;
	((Afec *)hw)->AFEC_ACR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_ACR_PGA1EN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR &= ~AFEC_ACR_PGA1EN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_ACR_PGA1EN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR ^= AFEC_ACR_PGA1EN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_ACR_IBCTL_bf(const void *const hw, hri_afec_acr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR |= AFEC_ACR_IBCTL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_acr_reg_t hri_afec_get_ACR_IBCTL_bf(const void *const hw, hri_afec_acr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_ACR;
	tmp = (tmp & AFEC_ACR_IBCTL(mask)) >> AFEC_ACR_IBCTL_Pos;
	return tmp;
}

static inline void hri_afec_write_ACR_IBCTL_bf(const void *const hw, hri_afec_acr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_ACR;
	tmp &= ~AFEC_ACR_IBCTL_Msk;
	tmp |= AFEC_ACR_IBCTL(data);
	((Afec *)hw)->AFEC_ACR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_ACR_IBCTL_bf(const void *const hw, hri_afec_acr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR &= ~AFEC_ACR_IBCTL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_ACR_IBCTL_bf(const void *const hw, hri_afec_acr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR ^= AFEC_ACR_IBCTL(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_acr_reg_t hri_afec_read_ACR_IBCTL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_ACR;
	tmp = (tmp & AFEC_ACR_IBCTL_Msk) >> AFEC_ACR_IBCTL_Pos;
	return tmp;
}

static inline void hri_afec_set_ACR_reg(const void *const hw, hri_afec_acr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_acr_reg_t hri_afec_get_ACR_reg(const void *const hw, hri_afec_acr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_ACR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_ACR_reg(const void *const hw, hri_afec_acr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_ACR_reg(const void *const hw, hri_afec_acr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_ACR_reg(const void *const hw, hri_afec_acr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_ACR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_acr_reg_t hri_afec_read_ACR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_ACR;
}

static inline void hri_afec_set_SHMR_DUAL0_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL0;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL0) >> AFEC_SHMR_DUAL0_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL0;
	tmp |= value << AFEC_SHMR_DUAL0_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL0_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL0;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL0_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL0;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL1_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL1;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL1) >> AFEC_SHMR_DUAL1_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL1;
	tmp |= value << AFEC_SHMR_DUAL1_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL1_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL1;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL1_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL1;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL2_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL2;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL2) >> AFEC_SHMR_DUAL2_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL2;
	tmp |= value << AFEC_SHMR_DUAL2_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL2_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL2;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL2_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL2;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL3_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL3;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL3) >> AFEC_SHMR_DUAL3_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL3;
	tmp |= value << AFEC_SHMR_DUAL3_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL3_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL3;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL3_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL3;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL4_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL4;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL4) >> AFEC_SHMR_DUAL4_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL4;
	tmp |= value << AFEC_SHMR_DUAL4_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL4_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL4;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL4_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL4;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL5_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL5;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL5) >> AFEC_SHMR_DUAL5_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL5;
	tmp |= value << AFEC_SHMR_DUAL5_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL5_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL5;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL5_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL5;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL6_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL6;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL6) >> AFEC_SHMR_DUAL6_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL6;
	tmp |= value << AFEC_SHMR_DUAL6_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL6_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL6;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL6_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL6;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL7_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL7;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL7) >> AFEC_SHMR_DUAL7_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL7;
	tmp |= value << AFEC_SHMR_DUAL7_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL7_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL7;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL7_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL7;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL8_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL8;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL8) >> AFEC_SHMR_DUAL8_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL8;
	tmp |= value << AFEC_SHMR_DUAL8_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL8_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL8;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL8_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL8;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL9_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL9;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL9) >> AFEC_SHMR_DUAL9_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL9;
	tmp |= value << AFEC_SHMR_DUAL9_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL9_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL9;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL9_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL9;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL10_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL10;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL10) >> AFEC_SHMR_DUAL10_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL10;
	tmp |= value << AFEC_SHMR_DUAL10_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL10_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL10;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL10_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL10;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_DUAL11_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= AFEC_SHMR_DUAL11;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_SHMR_DUAL11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp = (tmp & AFEC_SHMR_DUAL11) >> AFEC_SHMR_DUAL11_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_SHMR_DUAL11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= ~AFEC_SHMR_DUAL11;
	tmp |= value << AFEC_SHMR_DUAL11_Pos;
	((Afec *)hw)->AFEC_SHMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_DUAL11_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~AFEC_SHMR_DUAL11;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_DUAL11_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= AFEC_SHMR_DUAL11;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_SHMR_reg(const void *const hw, hri_afec_shmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_shmr_reg_t hri_afec_get_SHMR_reg(const void *const hw, hri_afec_shmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_SHMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_SHMR_reg(const void *const hw, hri_afec_shmr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_SHMR_reg(const void *const hw, hri_afec_shmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_SHMR_reg(const void *const hw, hri_afec_shmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_SHMR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_shmr_reg_t hri_afec_read_SHMR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_SHMR;
}

static inline void hri_afec_set_COSR_CSEL_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COSR |= AFEC_COSR_CSEL;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_COSR_CSEL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_COSR;
	tmp = (tmp & AFEC_COSR_CSEL) >> AFEC_COSR_CSEL_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_COSR_CSEL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_COSR;
	tmp &= ~AFEC_COSR_CSEL;
	tmp |= value << AFEC_COSR_CSEL_Pos;
	((Afec *)hw)->AFEC_COSR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_COSR_CSEL_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COSR &= ~AFEC_COSR_CSEL;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_COSR_CSEL_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COSR ^= AFEC_COSR_CSEL;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_COSR_reg(const void *const hw, hri_afec_cosr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COSR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cosr_reg_t hri_afec_get_COSR_reg(const void *const hw, hri_afec_cosr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_COSR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_COSR_reg(const void *const hw, hri_afec_cosr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COSR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_COSR_reg(const void *const hw, hri_afec_cosr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COSR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_COSR_reg(const void *const hw, hri_afec_cosr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_COSR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cosr_reg_t hri_afec_read_COSR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_COSR;
}

static inline void hri_afec_set_CVR_OFFSETCORR_bf(const void *const hw, hri_afec_cvr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR |= AFEC_CVR_OFFSETCORR(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cvr_reg_t hri_afec_get_CVR_OFFSETCORR_bf(const void *const hw, hri_afec_cvr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CVR;
	tmp = (tmp & AFEC_CVR_OFFSETCORR(mask)) >> AFEC_CVR_OFFSETCORR_Pos;
	return tmp;
}

static inline void hri_afec_write_CVR_OFFSETCORR_bf(const void *const hw, hri_afec_cvr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CVR;
	tmp &= ~AFEC_CVR_OFFSETCORR_Msk;
	tmp |= AFEC_CVR_OFFSETCORR(data);
	((Afec *)hw)->AFEC_CVR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CVR_OFFSETCORR_bf(const void *const hw, hri_afec_cvr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR &= ~AFEC_CVR_OFFSETCORR(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CVR_OFFSETCORR_bf(const void *const hw, hri_afec_cvr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR ^= AFEC_CVR_OFFSETCORR(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cvr_reg_t hri_afec_read_CVR_OFFSETCORR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CVR;
	tmp = (tmp & AFEC_CVR_OFFSETCORR_Msk) >> AFEC_CVR_OFFSETCORR_Pos;
	return tmp;
}

static inline void hri_afec_set_CVR_GAINCORR_bf(const void *const hw, hri_afec_cvr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR |= AFEC_CVR_GAINCORR(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cvr_reg_t hri_afec_get_CVR_GAINCORR_bf(const void *const hw, hri_afec_cvr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CVR;
	tmp = (tmp & AFEC_CVR_GAINCORR(mask)) >> AFEC_CVR_GAINCORR_Pos;
	return tmp;
}

static inline void hri_afec_write_CVR_GAINCORR_bf(const void *const hw, hri_afec_cvr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CVR;
	tmp &= ~AFEC_CVR_GAINCORR_Msk;
	tmp |= AFEC_CVR_GAINCORR(data);
	((Afec *)hw)->AFEC_CVR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CVR_GAINCORR_bf(const void *const hw, hri_afec_cvr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR &= ~AFEC_CVR_GAINCORR(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CVR_GAINCORR_bf(const void *const hw, hri_afec_cvr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR ^= AFEC_CVR_GAINCORR(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cvr_reg_t hri_afec_read_CVR_GAINCORR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CVR;
	tmp = (tmp & AFEC_CVR_GAINCORR_Msk) >> AFEC_CVR_GAINCORR_Pos;
	return tmp;
}

static inline void hri_afec_set_CVR_reg(const void *const hw, hri_afec_cvr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cvr_reg_t hri_afec_get_CVR_reg(const void *const hw, hri_afec_cvr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CVR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_CVR_reg(const void *const hw, hri_afec_cvr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CVR_reg(const void *const hw, hri_afec_cvr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CVR_reg(const void *const hw, hri_afec_cvr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CVR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cvr_reg_t hri_afec_read_CVR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_CVR;
}

static inline void hri_afec_set_CECR_ECORR0_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR0;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR0) >> AFEC_CECR_ECORR0_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR0;
	tmp |= value << AFEC_CECR_ECORR0_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR0_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR0;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR0_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR0;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR1_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR1;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR1) >> AFEC_CECR_ECORR1_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR1;
	tmp |= value << AFEC_CECR_ECORR1_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR1_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR1;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR1_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR1;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR2_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR2;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR2) >> AFEC_CECR_ECORR2_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR2;
	tmp |= value << AFEC_CECR_ECORR2_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR2_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR2;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR2_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR2;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR3_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR3;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR3) >> AFEC_CECR_ECORR3_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR3;
	tmp |= value << AFEC_CECR_ECORR3_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR3_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR3;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR3_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR3;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR4_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR4;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR4) >> AFEC_CECR_ECORR4_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR4;
	tmp |= value << AFEC_CECR_ECORR4_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR4_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR4;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR4_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR4;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR5_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR5;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR5) >> AFEC_CECR_ECORR5_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR5;
	tmp |= value << AFEC_CECR_ECORR5_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR5_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR5;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR5_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR5;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR6_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR6;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR6) >> AFEC_CECR_ECORR6_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR6;
	tmp |= value << AFEC_CECR_ECORR6_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR6_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR6;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR6_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR6;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR7_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR7;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR7) >> AFEC_CECR_ECORR7_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR7;
	tmp |= value << AFEC_CECR_ECORR7_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR7_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR7;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR7_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR7;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR8_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR8;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR8) >> AFEC_CECR_ECORR8_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR8;
	tmp |= value << AFEC_CECR_ECORR8_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR8_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR8;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR8_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR8;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR9_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR9;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR9) >> AFEC_CECR_ECORR9_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR9;
	tmp |= value << AFEC_CECR_ECORR9_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR9_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR9;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR9_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR9;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR10_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR10;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR10) >> AFEC_CECR_ECORR10_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR10;
	tmp |= value << AFEC_CECR_ECORR10_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR10_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR10;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR10_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR10;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_ECORR11_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= AFEC_CECR_ECORR11;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_CECR_ECORR11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp = (tmp & AFEC_CECR_ECORR11) >> AFEC_CECR_ECORR11_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_CECR_ECORR11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= ~AFEC_CECR_ECORR11;
	tmp |= value << AFEC_CECR_ECORR11_Pos;
	((Afec *)hw)->AFEC_CECR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_ECORR11_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~AFEC_CECR_ECORR11;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_ECORR11_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= AFEC_CECR_ECORR11;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_CECR_reg(const void *const hw, hri_afec_cecr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cecr_reg_t hri_afec_get_CECR_reg(const void *const hw, hri_afec_cecr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_CECR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_CECR_reg(const void *const hw, hri_afec_cecr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_CECR_reg(const void *const hw, hri_afec_cecr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_CECR_reg(const void *const hw, hri_afec_cecr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CECR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_cecr_reg_t hri_afec_read_CECR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_CECR;
}

static inline void hri_afec_set_WPMR_WPEN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR |= AFEC_WPMR_WPEN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_afec_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_WPMR;
	tmp = (tmp & AFEC_WPMR_WPEN) >> AFEC_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_afec_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_WPMR;
	tmp &= ~AFEC_WPMR_WPEN;
	tmp |= value << AFEC_WPMR_WPEN_Pos;
	((Afec *)hw)->AFEC_WPMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_WPMR_WPEN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR &= ~AFEC_WPMR_WPEN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_WPMR_WPEN_bit(const void *const hw)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR ^= AFEC_WPMR_WPEN;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_set_WPMR_WPKEY_bf(const void *const hw, hri_afec_wpmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR |= AFEC_WPMR_WPKEY(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_wpmr_reg_t hri_afec_get_WPMR_WPKEY_bf(const void *const hw, hri_afec_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_WPMR;
	tmp = (tmp & AFEC_WPMR_WPKEY(mask)) >> AFEC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_afec_write_WPMR_WPKEY_bf(const void *const hw, hri_afec_wpmr_reg_t data)
{
	uint32_t tmp;
	AFEC_CRITICAL_SECTION_ENTER();
	tmp = ((Afec *)hw)->AFEC_WPMR;
	tmp &= ~AFEC_WPMR_WPKEY_Msk;
	tmp |= AFEC_WPMR_WPKEY(data);
	((Afec *)hw)->AFEC_WPMR = tmp;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_WPMR_WPKEY_bf(const void *const hw, hri_afec_wpmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR &= ~AFEC_WPMR_WPKEY(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_WPMR_WPKEY_bf(const void *const hw, hri_afec_wpmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR ^= AFEC_WPMR_WPKEY(mask);
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_wpmr_reg_t hri_afec_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_WPMR;
	tmp = (tmp & AFEC_WPMR_WPKEY_Msk) >> AFEC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_afec_set_WPMR_reg(const void *const hw, hri_afec_wpmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR |= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_wpmr_reg_t hri_afec_get_WPMR_reg(const void *const hw, hri_afec_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Afec *)hw)->AFEC_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_afec_write_WPMR_reg(const void *const hw, hri_afec_wpmr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_clear_WPMR_reg(const void *const hw, hri_afec_wpmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR &= ~mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_afec_toggle_WPMR_reg(const void *const hw, hri_afec_wpmr_reg_t mask)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_WPMR ^= mask;
	AFEC_CRITICAL_SECTION_LEAVE();
}

static inline hri_afec_wpmr_reg_t hri_afec_read_WPMR_reg(const void *const hw)
{
	return ((Afec *)hw)->AFEC_WPMR;
}

static inline void hri_afec_write_CR_reg(const void *const hw, hri_afec_cr_reg_t data)
{
	AFEC_CRITICAL_SECTION_ENTER();
	((Afec *)hw)->AFEC_CR = data;
	AFEC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_AFEC_E70B_H_INCLUDED */
#endif /* _SAME70_AFEC_COMPONENT_ */
