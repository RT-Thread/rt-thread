/**
 * \file
 *
 * \brief SAM UTMI
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

#ifdef _SAME70_UTMI_COMPONENT_
#ifndef _HRI_UTMI_E70B_H_INCLUDED_
#define _HRI_UTMI_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_UTMI_CRITICAL_SECTIONS)
#define UTMI_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define UTMI_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define UTMI_CRITICAL_SECTION_ENTER()
#define UTMI_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_utmi_cktrim_reg_t;
typedef uint32_t hri_utmi_ohciicr_reg_t;

static inline void hri_utmi_set_OHCIICR_RES0_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= UTMI_OHCIICR_RES0;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_utmi_get_OHCIICR_RES0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp = (tmp & UTMI_OHCIICR_RES0) >> UTMI_OHCIICR_RES0_Pos;
	return (bool)tmp;
}

static inline void hri_utmi_write_OHCIICR_RES0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= ~UTMI_OHCIICR_RES0;
	tmp |= value << UTMI_OHCIICR_RES0_Pos;
	((Utmi *)hw)->UTMI_OHCIICR = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_RES0_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~UTMI_OHCIICR_RES0;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_RES0_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= UTMI_OHCIICR_RES0;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_set_OHCIICR_ARIE_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= UTMI_OHCIICR_ARIE;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_utmi_get_OHCIICR_ARIE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp = (tmp & UTMI_OHCIICR_ARIE) >> UTMI_OHCIICR_ARIE_Pos;
	return (bool)tmp;
}

static inline void hri_utmi_write_OHCIICR_ARIE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= ~UTMI_OHCIICR_ARIE;
	tmp |= value << UTMI_OHCIICR_ARIE_Pos;
	((Utmi *)hw)->UTMI_OHCIICR = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_ARIE_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~UTMI_OHCIICR_ARIE;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_ARIE_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= UTMI_OHCIICR_ARIE;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_set_OHCIICR_APPSTART_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= UTMI_OHCIICR_APPSTART;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_utmi_get_OHCIICR_APPSTART_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp = (tmp & UTMI_OHCIICR_APPSTART) >> UTMI_OHCIICR_APPSTART_Pos;
	return (bool)tmp;
}

static inline void hri_utmi_write_OHCIICR_APPSTART_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= ~UTMI_OHCIICR_APPSTART;
	tmp |= value << UTMI_OHCIICR_APPSTART_Pos;
	((Utmi *)hw)->UTMI_OHCIICR = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_APPSTART_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~UTMI_OHCIICR_APPSTART;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_APPSTART_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= UTMI_OHCIICR_APPSTART;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_set_OHCIICR_UDPPUDIS_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= UTMI_OHCIICR_UDPPUDIS;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_utmi_get_OHCIICR_UDPPUDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp = (tmp & UTMI_OHCIICR_UDPPUDIS) >> UTMI_OHCIICR_UDPPUDIS_Pos;
	return (bool)tmp;
}

static inline void hri_utmi_write_OHCIICR_UDPPUDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= ~UTMI_OHCIICR_UDPPUDIS;
	tmp |= value << UTMI_OHCIICR_UDPPUDIS_Pos;
	((Utmi *)hw)->UTMI_OHCIICR = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_UDPPUDIS_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~UTMI_OHCIICR_UDPPUDIS;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_UDPPUDIS_bit(const void *const hw)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= UTMI_OHCIICR_UDPPUDIS;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_set_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR |= mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_ohciicr_reg_t hri_utmi_get_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_OHCIICR;
	tmp &= mask;
	return tmp;
}

static inline void hri_utmi_write_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t data)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR = data;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR &= ~mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_OHCIICR_reg(const void *const hw, hri_utmi_ohciicr_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_OHCIICR ^= mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_ohciicr_reg_t hri_utmi_read_OHCIICR_reg(const void *const hw)
{
	return ((Utmi *)hw)->UTMI_OHCIICR;
}

static inline void hri_utmi_set_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM |= UTMI_CKTRIM_FREQ(mask);
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_cktrim_reg_t hri_utmi_get_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_CKTRIM;
	tmp = (tmp & UTMI_CKTRIM_FREQ(mask)) >> UTMI_CKTRIM_FREQ_Pos;
	return tmp;
}

static inline void hri_utmi_write_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t data)
{
	uint32_t tmp;
	UTMI_CRITICAL_SECTION_ENTER();
	tmp = ((Utmi *)hw)->UTMI_CKTRIM;
	tmp &= ~UTMI_CKTRIM_FREQ_Msk;
	tmp |= UTMI_CKTRIM_FREQ(data);
	((Utmi *)hw)->UTMI_CKTRIM = tmp;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM &= ~UTMI_CKTRIM_FREQ(mask);
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_CKTRIM_FREQ_bf(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM ^= UTMI_CKTRIM_FREQ(mask);
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_cktrim_reg_t hri_utmi_read_CKTRIM_FREQ_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_CKTRIM;
	tmp = (tmp & UTMI_CKTRIM_FREQ_Msk) >> UTMI_CKTRIM_FREQ_Pos;
	return tmp;
}

static inline void hri_utmi_set_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM |= mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_cktrim_reg_t hri_utmi_get_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Utmi *)hw)->UTMI_CKTRIM;
	tmp &= mask;
	return tmp;
}

static inline void hri_utmi_write_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t data)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM = data;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_clear_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM &= ~mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_utmi_toggle_CKTRIM_reg(const void *const hw, hri_utmi_cktrim_reg_t mask)
{
	UTMI_CRITICAL_SECTION_ENTER();
	((Utmi *)hw)->UTMI_CKTRIM ^= mask;
	UTMI_CRITICAL_SECTION_LEAVE();
}

static inline hri_utmi_cktrim_reg_t hri_utmi_read_CKTRIM_reg(const void *const hw)
{
	return ((Utmi *)hw)->UTMI_CKTRIM;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_UTMI_E70B_H_INCLUDED */
#endif /* _SAME70_UTMI_COMPONENT_ */
