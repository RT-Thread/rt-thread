/**
 * \file
 *
 * \brief SAM RTC
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

#ifdef _SAME70_RTC_COMPONENT_
#ifndef _HRI_RTC_E70B_H_INCLUDED_
#define _HRI_RTC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_RTC_CRITICAL_SECTIONS)
#define RTC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define RTC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define RTC_CRITICAL_SECTION_ENTER()
#define RTC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_rtc_calalr_reg_t;
typedef uint32_t hri_rtc_calr_reg_t;
typedef uint32_t hri_rtc_cr_reg_t;
typedef uint32_t hri_rtc_imr_reg_t;
typedef uint32_t hri_rtc_mr_reg_t;
typedef uint32_t hri_rtc_sccr_reg_t;
typedef uint32_t hri_rtc_sr_reg_t;
typedef uint32_t hri_rtc_timalr_reg_t;
typedef uint32_t hri_rtc_timr_reg_t;
typedef uint32_t hri_rtc_ver_reg_t;

static inline void hri_rtc_set_IMR_ACK_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IER = RTC_IMR_ACK;
}

static inline bool hri_rtc_get_IMR_ACK_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_IMR & RTC_IMR_ACK) >> RTC_IMR_ACK_Pos;
}

static inline void hri_rtc_write_IMR_ACK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->RTC_IDR = RTC_IMR_ACK;
	} else {
		((Rtc *)hw)->RTC_IER = RTC_IMR_ACK;
	}
}

static inline void hri_rtc_clear_IMR_ACK_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IDR = RTC_IMR_ACK;
}

static inline void hri_rtc_set_IMR_ALR_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IER = RTC_IMR_ALR;
}

static inline bool hri_rtc_get_IMR_ALR_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_IMR & RTC_IMR_ALR) >> RTC_IMR_ALR_Pos;
}

static inline void hri_rtc_write_IMR_ALR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->RTC_IDR = RTC_IMR_ALR;
	} else {
		((Rtc *)hw)->RTC_IER = RTC_IMR_ALR;
	}
}

static inline void hri_rtc_clear_IMR_ALR_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IDR = RTC_IMR_ALR;
}

static inline void hri_rtc_set_IMR_SEC_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IER = RTC_IMR_SEC;
}

static inline bool hri_rtc_get_IMR_SEC_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_IMR & RTC_IMR_SEC) >> RTC_IMR_SEC_Pos;
}

static inline void hri_rtc_write_IMR_SEC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->RTC_IDR = RTC_IMR_SEC;
	} else {
		((Rtc *)hw)->RTC_IER = RTC_IMR_SEC;
	}
}

static inline void hri_rtc_clear_IMR_SEC_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IDR = RTC_IMR_SEC;
}

static inline void hri_rtc_set_IMR_TIM_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IER = RTC_IMR_TIM;
}

static inline bool hri_rtc_get_IMR_TIM_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_IMR & RTC_IMR_TIM) >> RTC_IMR_TIM_Pos;
}

static inline void hri_rtc_write_IMR_TIM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->RTC_IDR = RTC_IMR_TIM;
	} else {
		((Rtc *)hw)->RTC_IER = RTC_IMR_TIM;
	}
}

static inline void hri_rtc_clear_IMR_TIM_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IDR = RTC_IMR_TIM;
}

static inline void hri_rtc_set_IMR_CAL_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IER = RTC_IMR_CAL;
}

static inline bool hri_rtc_get_IMR_CAL_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_IMR & RTC_IMR_CAL) >> RTC_IMR_CAL_Pos;
}

static inline void hri_rtc_write_IMR_CAL_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->RTC_IDR = RTC_IMR_CAL;
	} else {
		((Rtc *)hw)->RTC_IER = RTC_IMR_CAL;
	}
}

static inline void hri_rtc_clear_IMR_CAL_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IDR = RTC_IMR_CAL;
}

static inline void hri_rtc_set_IMR_TDERR_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IER = RTC_IMR_TDERR;
}

static inline bool hri_rtc_get_IMR_TDERR_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_IMR & RTC_IMR_TDERR) >> RTC_IMR_TDERR_Pos;
}

static inline void hri_rtc_write_IMR_TDERR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->RTC_IDR = RTC_IMR_TDERR;
	} else {
		((Rtc *)hw)->RTC_IER = RTC_IMR_TDERR;
	}
}

static inline void hri_rtc_clear_IMR_TDERR_bit(const void *const hw)
{
	((Rtc *)hw)->RTC_IDR = RTC_IMR_TDERR;
}

static inline void hri_rtc_set_IMR_reg(const void *const hw, hri_rtc_imr_reg_t mask)
{
	((Rtc *)hw)->RTC_IER = mask;
}

static inline hri_rtc_imr_reg_t hri_rtc_get_IMR_reg(const void *const hw, hri_rtc_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_rtc_imr_reg_t hri_rtc_read_IMR_reg(const void *const hw)
{
	return ((Rtc *)hw)->RTC_IMR;
}

static inline void hri_rtc_write_IMR_reg(const void *const hw, hri_rtc_imr_reg_t data)
{
	((Rtc *)hw)->RTC_IER = data;
	((Rtc *)hw)->RTC_IDR = ~data;
}

static inline void hri_rtc_clear_IMR_reg(const void *const hw, hri_rtc_imr_reg_t mask)
{
	((Rtc *)hw)->RTC_IDR = mask;
}

static inline bool hri_rtc_get_SR_ACKUPD_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_SR & RTC_SR_ACKUPD) > 0;
}

static inline bool hri_rtc_get_SR_ALARM_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_SR & RTC_SR_ALARM) > 0;
}

static inline bool hri_rtc_get_SR_SEC_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_SR & RTC_SR_SEC) > 0;
}

static inline bool hri_rtc_get_SR_TIMEV_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_SR & RTC_SR_TIMEV) > 0;
}

static inline bool hri_rtc_get_SR_CALEV_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_SR & RTC_SR_CALEV) > 0;
}

static inline bool hri_rtc_get_SR_TDERR_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_SR & RTC_SR_TDERR) > 0;
}

static inline hri_rtc_sr_reg_t hri_rtc_get_SR_reg(const void *const hw, hri_rtc_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_rtc_sr_reg_t hri_rtc_read_SR_reg(const void *const hw)
{
	return ((Rtc *)hw)->RTC_SR;
}

static inline bool hri_rtc_get_VER_NVTIM_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_VER & RTC_VER_NVTIM) > 0;
}

static inline bool hri_rtc_get_VER_NVCAL_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_VER & RTC_VER_NVCAL) > 0;
}

static inline bool hri_rtc_get_VER_NVTIMALR_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_VER & RTC_VER_NVTIMALR) > 0;
}

static inline bool hri_rtc_get_VER_NVCALALR_bit(const void *const hw)
{
	return (((Rtc *)hw)->RTC_VER & RTC_VER_NVCALALR) > 0;
}

static inline hri_rtc_ver_reg_t hri_rtc_get_VER_reg(const void *const hw, hri_rtc_ver_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_VER;
	tmp &= mask;
	return tmp;
}

static inline hri_rtc_ver_reg_t hri_rtc_read_VER_reg(const void *const hw)
{
	return ((Rtc *)hw)->RTC_VER;
}

static inline void hri_rtc_set_CR_UPDTIM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR |= RTC_CR_UPDTIM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_CR_UPDTIM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp = (tmp & RTC_CR_UPDTIM) >> RTC_CR_UPDTIM_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_CR_UPDTIM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp &= ~RTC_CR_UPDTIM;
	tmp |= value << RTC_CR_UPDTIM_Pos;
	((Rtc *)hw)->RTC_CR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CR_UPDTIM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR &= ~RTC_CR_UPDTIM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CR_UPDTIM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR ^= RTC_CR_UPDTIM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_CR_UPDCAL_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR |= RTC_CR_UPDCAL;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_CR_UPDCAL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp = (tmp & RTC_CR_UPDCAL) >> RTC_CR_UPDCAL_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_CR_UPDCAL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp &= ~RTC_CR_UPDCAL;
	tmp |= value << RTC_CR_UPDCAL_Pos;
	((Rtc *)hw)->RTC_CR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CR_UPDCAL_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR &= ~RTC_CR_UPDCAL;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CR_UPDCAL_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR ^= RTC_CR_UPDCAL;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_CR_TIMEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR |= RTC_CR_TIMEVSEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_cr_reg_t hri_rtc_get_CR_TIMEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp = (tmp & RTC_CR_TIMEVSEL(mask)) >> RTC_CR_TIMEVSEL_Pos;
	return tmp;
}

static inline void hri_rtc_write_CR_TIMEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp &= ~RTC_CR_TIMEVSEL_Msk;
	tmp |= RTC_CR_TIMEVSEL(data);
	((Rtc *)hw)->RTC_CR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CR_TIMEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR &= ~RTC_CR_TIMEVSEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CR_TIMEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR ^= RTC_CR_TIMEVSEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_cr_reg_t hri_rtc_read_CR_TIMEVSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp = (tmp & RTC_CR_TIMEVSEL_Msk) >> RTC_CR_TIMEVSEL_Pos;
	return tmp;
}

static inline void hri_rtc_set_CR_CALEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR |= RTC_CR_CALEVSEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_cr_reg_t hri_rtc_get_CR_CALEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp = (tmp & RTC_CR_CALEVSEL(mask)) >> RTC_CR_CALEVSEL_Pos;
	return tmp;
}

static inline void hri_rtc_write_CR_CALEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp &= ~RTC_CR_CALEVSEL_Msk;
	tmp |= RTC_CR_CALEVSEL(data);
	((Rtc *)hw)->RTC_CR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CR_CALEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR &= ~RTC_CR_CALEVSEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CR_CALEVSEL_bf(const void *const hw, hri_rtc_cr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR ^= RTC_CR_CALEVSEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_cr_reg_t hri_rtc_read_CR_CALEVSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp = (tmp & RTC_CR_CALEVSEL_Msk) >> RTC_CR_CALEVSEL_Pos;
	return tmp;
}

static inline void hri_rtc_set_CR_reg(const void *const hw, hri_rtc_cr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_cr_reg_t hri_rtc_get_CR_reg(const void *const hw, hri_rtc_cr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtc_write_CR_reg(const void *const hw, hri_rtc_cr_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CR_reg(const void *const hw, hri_rtc_cr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CR_reg(const void *const hw, hri_rtc_cr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CR ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_cr_reg_t hri_rtc_read_CR_reg(const void *const hw)
{
	return ((Rtc *)hw)->RTC_CR;
}

static inline void hri_rtc_set_MR_HRMOD_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= RTC_MR_HRMOD;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_MR_HRMOD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_HRMOD) >> RTC_MR_HRMOD_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_MR_HRMOD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= ~RTC_MR_HRMOD;
	tmp |= value << RTC_MR_HRMOD_Pos;
	((Rtc *)hw)->RTC_MR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_HRMOD_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~RTC_MR_HRMOD;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_HRMOD_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= RTC_MR_HRMOD;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_MR_PERSIAN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= RTC_MR_PERSIAN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_MR_PERSIAN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_PERSIAN) >> RTC_MR_PERSIAN_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_MR_PERSIAN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= ~RTC_MR_PERSIAN;
	tmp |= value << RTC_MR_PERSIAN_Pos;
	((Rtc *)hw)->RTC_MR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_PERSIAN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~RTC_MR_PERSIAN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_PERSIAN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= RTC_MR_PERSIAN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_MR_NEGPPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= RTC_MR_NEGPPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_MR_NEGPPM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_NEGPPM) >> RTC_MR_NEGPPM_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_MR_NEGPPM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= ~RTC_MR_NEGPPM;
	tmp |= value << RTC_MR_NEGPPM_Pos;
	((Rtc *)hw)->RTC_MR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_NEGPPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~RTC_MR_NEGPPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_NEGPPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= RTC_MR_NEGPPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_MR_HIGHPPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= RTC_MR_HIGHPPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_MR_HIGHPPM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_HIGHPPM) >> RTC_MR_HIGHPPM_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_MR_HIGHPPM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= ~RTC_MR_HIGHPPM;
	tmp |= value << RTC_MR_HIGHPPM_Pos;
	((Rtc *)hw)->RTC_MR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_HIGHPPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~RTC_MR_HIGHPPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_HIGHPPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= RTC_MR_HIGHPPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_MR_CORRECTION_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= RTC_MR_CORRECTION(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_get_MR_CORRECTION_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_CORRECTION(mask)) >> RTC_MR_CORRECTION_Pos;
	return tmp;
}

static inline void hri_rtc_write_MR_CORRECTION_bf(const void *const hw, hri_rtc_mr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= ~RTC_MR_CORRECTION_Msk;
	tmp |= RTC_MR_CORRECTION(data);
	((Rtc *)hw)->RTC_MR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_CORRECTION_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~RTC_MR_CORRECTION(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_CORRECTION_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= RTC_MR_CORRECTION(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_read_MR_CORRECTION_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_CORRECTION_Msk) >> RTC_MR_CORRECTION_Pos;
	return tmp;
}

static inline void hri_rtc_set_MR_OUT0_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= RTC_MR_OUT0(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_get_MR_OUT0_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_OUT0(mask)) >> RTC_MR_OUT0_Pos;
	return tmp;
}

static inline void hri_rtc_write_MR_OUT0_bf(const void *const hw, hri_rtc_mr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= ~RTC_MR_OUT0_Msk;
	tmp |= RTC_MR_OUT0(data);
	((Rtc *)hw)->RTC_MR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_OUT0_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~RTC_MR_OUT0(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_OUT0_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= RTC_MR_OUT0(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_read_MR_OUT0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_OUT0_Msk) >> RTC_MR_OUT0_Pos;
	return tmp;
}

static inline void hri_rtc_set_MR_OUT1_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= RTC_MR_OUT1(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_get_MR_OUT1_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_OUT1(mask)) >> RTC_MR_OUT1_Pos;
	return tmp;
}

static inline void hri_rtc_write_MR_OUT1_bf(const void *const hw, hri_rtc_mr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= ~RTC_MR_OUT1_Msk;
	tmp |= RTC_MR_OUT1(data);
	((Rtc *)hw)->RTC_MR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_OUT1_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~RTC_MR_OUT1(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_OUT1_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= RTC_MR_OUT1(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_read_MR_OUT1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_OUT1_Msk) >> RTC_MR_OUT1_Pos;
	return tmp;
}

static inline void hri_rtc_set_MR_THIGH_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= RTC_MR_THIGH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_get_MR_THIGH_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_THIGH(mask)) >> RTC_MR_THIGH_Pos;
	return tmp;
}

static inline void hri_rtc_write_MR_THIGH_bf(const void *const hw, hri_rtc_mr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= ~RTC_MR_THIGH_Msk;
	tmp |= RTC_MR_THIGH(data);
	((Rtc *)hw)->RTC_MR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_THIGH_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~RTC_MR_THIGH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_THIGH_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= RTC_MR_THIGH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_read_MR_THIGH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_THIGH_Msk) >> RTC_MR_THIGH_Pos;
	return tmp;
}

static inline void hri_rtc_set_MR_TPERIOD_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= RTC_MR_TPERIOD(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_get_MR_TPERIOD_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_TPERIOD(mask)) >> RTC_MR_TPERIOD_Pos;
	return tmp;
}

static inline void hri_rtc_write_MR_TPERIOD_bf(const void *const hw, hri_rtc_mr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= ~RTC_MR_TPERIOD_Msk;
	tmp |= RTC_MR_TPERIOD(data);
	((Rtc *)hw)->RTC_MR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_TPERIOD_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~RTC_MR_TPERIOD(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_TPERIOD_bf(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= RTC_MR_TPERIOD(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_read_MR_TPERIOD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp = (tmp & RTC_MR_TPERIOD_Msk) >> RTC_MR_TPERIOD_Pos;
	return tmp;
}

static inline void hri_rtc_set_MR_reg(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_get_MR_reg(const void *const hw, hri_rtc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtc_write_MR_reg(const void *const hw, hri_rtc_mr_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_MR_reg(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_MR_reg(const void *const hw, hri_rtc_mr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_MR ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_mr_reg_t hri_rtc_read_MR_reg(const void *const hw)
{
	return ((Rtc *)hw)->RTC_MR;
}

static inline void hri_rtc_set_TIMR_AMPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR |= RTC_TIMR_AMPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_TIMR_AMPM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp = (tmp & RTC_TIMR_AMPM) >> RTC_TIMR_AMPM_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_TIMR_AMPM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp &= ~RTC_TIMR_AMPM;
	tmp |= value << RTC_TIMR_AMPM_Pos;
	((Rtc *)hw)->RTC_TIMR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMR_AMPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR &= ~RTC_TIMR_AMPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMR_AMPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR ^= RTC_TIMR_AMPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_TIMR_SEC_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR |= RTC_TIMR_SEC(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timr_reg_t hri_rtc_get_TIMR_SEC_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp = (tmp & RTC_TIMR_SEC(mask)) >> RTC_TIMR_SEC_Pos;
	return tmp;
}

static inline void hri_rtc_write_TIMR_SEC_bf(const void *const hw, hri_rtc_timr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp &= ~RTC_TIMR_SEC_Msk;
	tmp |= RTC_TIMR_SEC(data);
	((Rtc *)hw)->RTC_TIMR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMR_SEC_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR &= ~RTC_TIMR_SEC(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMR_SEC_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR ^= RTC_TIMR_SEC(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timr_reg_t hri_rtc_read_TIMR_SEC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp = (tmp & RTC_TIMR_SEC_Msk) >> RTC_TIMR_SEC_Pos;
	return tmp;
}

static inline void hri_rtc_set_TIMR_MIN_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR |= RTC_TIMR_MIN(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timr_reg_t hri_rtc_get_TIMR_MIN_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp = (tmp & RTC_TIMR_MIN(mask)) >> RTC_TIMR_MIN_Pos;
	return tmp;
}

static inline void hri_rtc_write_TIMR_MIN_bf(const void *const hw, hri_rtc_timr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp &= ~RTC_TIMR_MIN_Msk;
	tmp |= RTC_TIMR_MIN(data);
	((Rtc *)hw)->RTC_TIMR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMR_MIN_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR &= ~RTC_TIMR_MIN(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMR_MIN_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR ^= RTC_TIMR_MIN(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timr_reg_t hri_rtc_read_TIMR_MIN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp = (tmp & RTC_TIMR_MIN_Msk) >> RTC_TIMR_MIN_Pos;
	return tmp;
}

static inline void hri_rtc_set_TIMR_HOUR_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR |= RTC_TIMR_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timr_reg_t hri_rtc_get_TIMR_HOUR_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp = (tmp & RTC_TIMR_HOUR(mask)) >> RTC_TIMR_HOUR_Pos;
	return tmp;
}

static inline void hri_rtc_write_TIMR_HOUR_bf(const void *const hw, hri_rtc_timr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp &= ~RTC_TIMR_HOUR_Msk;
	tmp |= RTC_TIMR_HOUR(data);
	((Rtc *)hw)->RTC_TIMR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMR_HOUR_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR &= ~RTC_TIMR_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMR_HOUR_bf(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR ^= RTC_TIMR_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timr_reg_t hri_rtc_read_TIMR_HOUR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp = (tmp & RTC_TIMR_HOUR_Msk) >> RTC_TIMR_HOUR_Pos;
	return tmp;
}

static inline void hri_rtc_set_TIMR_reg(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timr_reg_t hri_rtc_get_TIMR_reg(const void *const hw, hri_rtc_timr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtc_write_TIMR_reg(const void *const hw, hri_rtc_timr_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMR_reg(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMR_reg(const void *const hw, hri_rtc_timr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMR ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timr_reg_t hri_rtc_read_TIMR_reg(const void *const hw)
{
	return ((Rtc *)hw)->RTC_TIMR;
}

static inline void hri_rtc_set_CALR_CENT_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR |= RTC_CALR_CENT(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_get_CALR_CENT_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_CENT(mask)) >> RTC_CALR_CENT_Pos;
	return tmp;
}

static inline void hri_rtc_write_CALR_CENT_bf(const void *const hw, hri_rtc_calr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp &= ~RTC_CALR_CENT_Msk;
	tmp |= RTC_CALR_CENT(data);
	((Rtc *)hw)->RTC_CALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALR_CENT_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR &= ~RTC_CALR_CENT(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALR_CENT_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR ^= RTC_CALR_CENT(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_read_CALR_CENT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_CENT_Msk) >> RTC_CALR_CENT_Pos;
	return tmp;
}

static inline void hri_rtc_set_CALR_YEAR_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR |= RTC_CALR_YEAR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_get_CALR_YEAR_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_YEAR(mask)) >> RTC_CALR_YEAR_Pos;
	return tmp;
}

static inline void hri_rtc_write_CALR_YEAR_bf(const void *const hw, hri_rtc_calr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp &= ~RTC_CALR_YEAR_Msk;
	tmp |= RTC_CALR_YEAR(data);
	((Rtc *)hw)->RTC_CALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALR_YEAR_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR &= ~RTC_CALR_YEAR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALR_YEAR_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR ^= RTC_CALR_YEAR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_read_CALR_YEAR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_YEAR_Msk) >> RTC_CALR_YEAR_Pos;
	return tmp;
}

static inline void hri_rtc_set_CALR_MONTH_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR |= RTC_CALR_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_get_CALR_MONTH_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_MONTH(mask)) >> RTC_CALR_MONTH_Pos;
	return tmp;
}

static inline void hri_rtc_write_CALR_MONTH_bf(const void *const hw, hri_rtc_calr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp &= ~RTC_CALR_MONTH_Msk;
	tmp |= RTC_CALR_MONTH(data);
	((Rtc *)hw)->RTC_CALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALR_MONTH_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR &= ~RTC_CALR_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALR_MONTH_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR ^= RTC_CALR_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_read_CALR_MONTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_MONTH_Msk) >> RTC_CALR_MONTH_Pos;
	return tmp;
}

static inline void hri_rtc_set_CALR_DAY_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR |= RTC_CALR_DAY(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_get_CALR_DAY_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_DAY(mask)) >> RTC_CALR_DAY_Pos;
	return tmp;
}

static inline void hri_rtc_write_CALR_DAY_bf(const void *const hw, hri_rtc_calr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp &= ~RTC_CALR_DAY_Msk;
	tmp |= RTC_CALR_DAY(data);
	((Rtc *)hw)->RTC_CALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALR_DAY_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR &= ~RTC_CALR_DAY(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALR_DAY_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR ^= RTC_CALR_DAY(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_read_CALR_DAY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_DAY_Msk) >> RTC_CALR_DAY_Pos;
	return tmp;
}

static inline void hri_rtc_set_CALR_DATE_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR |= RTC_CALR_DATE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_get_CALR_DATE_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_DATE(mask)) >> RTC_CALR_DATE_Pos;
	return tmp;
}

static inline void hri_rtc_write_CALR_DATE_bf(const void *const hw, hri_rtc_calr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp &= ~RTC_CALR_DATE_Msk;
	tmp |= RTC_CALR_DATE(data);
	((Rtc *)hw)->RTC_CALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALR_DATE_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR &= ~RTC_CALR_DATE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALR_DATE_bf(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR ^= RTC_CALR_DATE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_read_CALR_DATE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp = (tmp & RTC_CALR_DATE_Msk) >> RTC_CALR_DATE_Pos;
	return tmp;
}

static inline void hri_rtc_set_CALR_reg(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_get_CALR_reg(const void *const hw, hri_rtc_calr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtc_write_CALR_reg(const void *const hw, hri_rtc_calr_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALR_reg(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALR_reg(const void *const hw, hri_rtc_calr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALR ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calr_reg_t hri_rtc_read_CALR_reg(const void *const hw)
{
	return ((Rtc *)hw)->RTC_CALR;
}

static inline void hri_rtc_set_TIMALR_SECEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR |= RTC_TIMALR_SECEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_TIMALR_SECEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_SECEN) >> RTC_TIMALR_SECEN_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_TIMALR_SECEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp &= ~RTC_TIMALR_SECEN;
	tmp |= value << RTC_TIMALR_SECEN_Pos;
	((Rtc *)hw)->RTC_TIMALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMALR_SECEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR &= ~RTC_TIMALR_SECEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMALR_SECEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR ^= RTC_TIMALR_SECEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_TIMALR_MINEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR |= RTC_TIMALR_MINEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_TIMALR_MINEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_MINEN) >> RTC_TIMALR_MINEN_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_TIMALR_MINEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp &= ~RTC_TIMALR_MINEN;
	tmp |= value << RTC_TIMALR_MINEN_Pos;
	((Rtc *)hw)->RTC_TIMALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMALR_MINEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR &= ~RTC_TIMALR_MINEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMALR_MINEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR ^= RTC_TIMALR_MINEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_TIMALR_AMPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR |= RTC_TIMALR_AMPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_TIMALR_AMPM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_AMPM) >> RTC_TIMALR_AMPM_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_TIMALR_AMPM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp &= ~RTC_TIMALR_AMPM;
	tmp |= value << RTC_TIMALR_AMPM_Pos;
	((Rtc *)hw)->RTC_TIMALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMALR_AMPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR &= ~RTC_TIMALR_AMPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMALR_AMPM_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR ^= RTC_TIMALR_AMPM;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_TIMALR_HOUREN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR |= RTC_TIMALR_HOUREN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_TIMALR_HOUREN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_HOUREN) >> RTC_TIMALR_HOUREN_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_TIMALR_HOUREN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp &= ~RTC_TIMALR_HOUREN;
	tmp |= value << RTC_TIMALR_HOUREN_Pos;
	((Rtc *)hw)->RTC_TIMALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMALR_HOUREN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR &= ~RTC_TIMALR_HOUREN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMALR_HOUREN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR ^= RTC_TIMALR_HOUREN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_TIMALR_SEC_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR |= RTC_TIMALR_SEC(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timalr_reg_t hri_rtc_get_TIMALR_SEC_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_SEC(mask)) >> RTC_TIMALR_SEC_Pos;
	return tmp;
}

static inline void hri_rtc_write_TIMALR_SEC_bf(const void *const hw, hri_rtc_timalr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp &= ~RTC_TIMALR_SEC_Msk;
	tmp |= RTC_TIMALR_SEC(data);
	((Rtc *)hw)->RTC_TIMALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMALR_SEC_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR &= ~RTC_TIMALR_SEC(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMALR_SEC_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR ^= RTC_TIMALR_SEC(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timalr_reg_t hri_rtc_read_TIMALR_SEC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_SEC_Msk) >> RTC_TIMALR_SEC_Pos;
	return tmp;
}

static inline void hri_rtc_set_TIMALR_MIN_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR |= RTC_TIMALR_MIN(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timalr_reg_t hri_rtc_get_TIMALR_MIN_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_MIN(mask)) >> RTC_TIMALR_MIN_Pos;
	return tmp;
}

static inline void hri_rtc_write_TIMALR_MIN_bf(const void *const hw, hri_rtc_timalr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp &= ~RTC_TIMALR_MIN_Msk;
	tmp |= RTC_TIMALR_MIN(data);
	((Rtc *)hw)->RTC_TIMALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMALR_MIN_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR &= ~RTC_TIMALR_MIN(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMALR_MIN_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR ^= RTC_TIMALR_MIN(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timalr_reg_t hri_rtc_read_TIMALR_MIN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_MIN_Msk) >> RTC_TIMALR_MIN_Pos;
	return tmp;
}

static inline void hri_rtc_set_TIMALR_HOUR_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR |= RTC_TIMALR_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timalr_reg_t hri_rtc_get_TIMALR_HOUR_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_HOUR(mask)) >> RTC_TIMALR_HOUR_Pos;
	return tmp;
}

static inline void hri_rtc_write_TIMALR_HOUR_bf(const void *const hw, hri_rtc_timalr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp &= ~RTC_TIMALR_HOUR_Msk;
	tmp |= RTC_TIMALR_HOUR(data);
	((Rtc *)hw)->RTC_TIMALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMALR_HOUR_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR &= ~RTC_TIMALR_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMALR_HOUR_bf(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR ^= RTC_TIMALR_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timalr_reg_t hri_rtc_read_TIMALR_HOUR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp = (tmp & RTC_TIMALR_HOUR_Msk) >> RTC_TIMALR_HOUR_Pos;
	return tmp;
}

static inline void hri_rtc_set_TIMALR_reg(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timalr_reg_t hri_rtc_get_TIMALR_reg(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_TIMALR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtc_write_TIMALR_reg(const void *const hw, hri_rtc_timalr_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_TIMALR_reg(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_TIMALR_reg(const void *const hw, hri_rtc_timalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_TIMALR ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_timalr_reg_t hri_rtc_read_TIMALR_reg(const void *const hw)
{
	return ((Rtc *)hw)->RTC_TIMALR;
}

static inline void hri_rtc_set_CALALR_MTHEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR |= RTC_CALALR_MTHEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_CALALR_MTHEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp = (tmp & RTC_CALALR_MTHEN) >> RTC_CALALR_MTHEN_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_CALALR_MTHEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp &= ~RTC_CALALR_MTHEN;
	tmp |= value << RTC_CALALR_MTHEN_Pos;
	((Rtc *)hw)->RTC_CALALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALALR_MTHEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR &= ~RTC_CALALR_MTHEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALALR_MTHEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR ^= RTC_CALALR_MTHEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_CALALR_DATEEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR |= RTC_CALALR_DATEEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_CALALR_DATEEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp = (tmp & RTC_CALALR_DATEEN) >> RTC_CALALR_DATEEN_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_CALALR_DATEEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp &= ~RTC_CALALR_DATEEN;
	tmp |= value << RTC_CALALR_DATEEN_Pos;
	((Rtc *)hw)->RTC_CALALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALALR_DATEEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR &= ~RTC_CALALR_DATEEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALALR_DATEEN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR ^= RTC_CALALR_DATEEN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_CALALR_MONTH_bf(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR |= RTC_CALALR_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calalr_reg_t hri_rtc_get_CALALR_MONTH_bf(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp = (tmp & RTC_CALALR_MONTH(mask)) >> RTC_CALALR_MONTH_Pos;
	return tmp;
}

static inline void hri_rtc_write_CALALR_MONTH_bf(const void *const hw, hri_rtc_calalr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp &= ~RTC_CALALR_MONTH_Msk;
	tmp |= RTC_CALALR_MONTH(data);
	((Rtc *)hw)->RTC_CALALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALALR_MONTH_bf(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR &= ~RTC_CALALR_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALALR_MONTH_bf(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR ^= RTC_CALALR_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calalr_reg_t hri_rtc_read_CALALR_MONTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp = (tmp & RTC_CALALR_MONTH_Msk) >> RTC_CALALR_MONTH_Pos;
	return tmp;
}

static inline void hri_rtc_set_CALALR_DATE_bf(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR |= RTC_CALALR_DATE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calalr_reg_t hri_rtc_get_CALALR_DATE_bf(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp = (tmp & RTC_CALALR_DATE(mask)) >> RTC_CALALR_DATE_Pos;
	return tmp;
}

static inline void hri_rtc_write_CALALR_DATE_bf(const void *const hw, hri_rtc_calalr_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp &= ~RTC_CALALR_DATE_Msk;
	tmp |= RTC_CALALR_DATE(data);
	((Rtc *)hw)->RTC_CALALR = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALALR_DATE_bf(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR &= ~RTC_CALALR_DATE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALALR_DATE_bf(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR ^= RTC_CALALR_DATE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calalr_reg_t hri_rtc_read_CALALR_DATE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp = (tmp & RTC_CALALR_DATE_Msk) >> RTC_CALALR_DATE_Pos;
	return tmp;
}

static inline void hri_rtc_set_CALALR_reg(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calalr_reg_t hri_rtc_get_CALALR_reg(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->RTC_CALALR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtc_write_CALALR_reg(const void *const hw, hri_rtc_calalr_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_CALALR_reg(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_CALALR_reg(const void *const hw, hri_rtc_calalr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_CALALR ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_calalr_reg_t hri_rtc_read_CALALR_reg(const void *const hw)
{
	return ((Rtc *)hw)->RTC_CALALR;
}

static inline void hri_rtc_write_SCCR_reg(const void *const hw, hri_rtc_sccr_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->RTC_SCCR = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RTC_E70B_H_INCLUDED */
#endif /* _SAME70_RTC_COMPONENT_ */
