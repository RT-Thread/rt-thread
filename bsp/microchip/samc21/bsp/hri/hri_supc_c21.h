/**
 * \file
 *
 * \brief SAM SUPC
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
 *
 */

#ifdef _SAMC21_SUPC_COMPONENT_
#ifndef _HRI_SUPC_C21_H_INCLUDED_
#define _HRI_SUPC_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_SUPC_CRITICAL_SECTIONS)
#define SUPC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define SUPC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define SUPC_CRITICAL_SECTION_ENTER()
#define SUPC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_supc_bodcore_reg_t;
typedef uint32_t hri_supc_bodvdd_reg_t;
typedef uint32_t hri_supc_intenset_reg_t;
typedef uint32_t hri_supc_intflag_reg_t;
typedef uint32_t hri_supc_status_reg_t;
typedef uint32_t hri_supc_vref_reg_t;
typedef uint32_t hri_supc_vreg_reg_t;

static inline bool hri_supc_get_INTFLAG_BODVDDRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BODVDDRDY) >> SUPC_INTFLAG_BODVDDRDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_BODVDDRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BODVDDRDY;
}

static inline bool hri_supc_get_INTFLAG_BODVDDDET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BODVDDDET) >> SUPC_INTFLAG_BODVDDDET_Pos;
}

static inline void hri_supc_clear_INTFLAG_BODVDDDET_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BODVDDDET;
}

static inline bool hri_supc_get_INTFLAG_BVDDSRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BVDDSRDY) >> SUPC_INTFLAG_BVDDSRDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_BVDDSRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BVDDSRDY;
}

static inline bool hri_supc_get_INTFLAG_BODCORERDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BODCORERDY) >> SUPC_INTFLAG_BODCORERDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_BODCORERDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BODCORERDY;
}

static inline bool hri_supc_get_INTFLAG_BODCOREDET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BODCOREDET) >> SUPC_INTFLAG_BODCOREDET_Pos;
}

static inline void hri_supc_clear_INTFLAG_BODCOREDET_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BODCOREDET;
}

static inline bool hri_supc_get_INTFLAG_BCORESRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BCORESRDY) >> SUPC_INTFLAG_BCORESRDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_BCORESRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BCORESRDY;
}

static inline bool hri_supc_get_interrupt_BODVDDRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BODVDDRDY) >> SUPC_INTFLAG_BODVDDRDY_Pos;
}

static inline void hri_supc_clear_interrupt_BODVDDRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BODVDDRDY;
}

static inline bool hri_supc_get_interrupt_BODVDDDET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BODVDDDET) >> SUPC_INTFLAG_BODVDDDET_Pos;
}

static inline void hri_supc_clear_interrupt_BODVDDDET_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BODVDDDET;
}

static inline bool hri_supc_get_interrupt_BVDDSRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BVDDSRDY) >> SUPC_INTFLAG_BVDDSRDY_Pos;
}

static inline void hri_supc_clear_interrupt_BVDDSRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BVDDSRDY;
}

static inline bool hri_supc_get_interrupt_BODCORERDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BODCORERDY) >> SUPC_INTFLAG_BODCORERDY_Pos;
}

static inline void hri_supc_clear_interrupt_BODCORERDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BODCORERDY;
}

static inline bool hri_supc_get_interrupt_BODCOREDET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BODCOREDET) >> SUPC_INTFLAG_BODCOREDET_Pos;
}

static inline void hri_supc_clear_interrupt_BODCOREDET_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BODCOREDET;
}

static inline bool hri_supc_get_interrupt_BCORESRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BCORESRDY) >> SUPC_INTFLAG_BCORESRDY_Pos;
}

static inline void hri_supc_clear_interrupt_BCORESRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BCORESRDY;
}

static inline hri_supc_intflag_reg_t hri_supc_get_INTFLAG_reg(const void *const hw, hri_supc_intflag_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_supc_intflag_reg_t hri_supc_read_INTFLAG_reg(const void *const hw)
{
	return ((Supc *)hw)->INTFLAG.reg;
}

static inline void hri_supc_clear_INTFLAG_reg(const void *const hw, hri_supc_intflag_reg_t mask)
{
	((Supc *)hw)->INTFLAG.reg = mask;
}

static inline void hri_supc_set_INTEN_BODVDDRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BODVDDRDY;
}

static inline bool hri_supc_get_INTEN_BODVDDRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BODVDDRDY) >> SUPC_INTENSET_BODVDDRDY_Pos;
}

static inline void hri_supc_write_INTEN_BODVDDRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BODVDDRDY;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BODVDDRDY;
	}
}

static inline void hri_supc_clear_INTEN_BODVDDRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BODVDDRDY;
}

static inline void hri_supc_set_INTEN_BODVDDDET_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BODVDDDET;
}

static inline bool hri_supc_get_INTEN_BODVDDDET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BODVDDDET) >> SUPC_INTENSET_BODVDDDET_Pos;
}

static inline void hri_supc_write_INTEN_BODVDDDET_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BODVDDDET;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BODVDDDET;
	}
}

static inline void hri_supc_clear_INTEN_BODVDDDET_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BODVDDDET;
}

static inline void hri_supc_set_INTEN_BVDDSRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BVDDSRDY;
}

static inline bool hri_supc_get_INTEN_BVDDSRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BVDDSRDY) >> SUPC_INTENSET_BVDDSRDY_Pos;
}

static inline void hri_supc_write_INTEN_BVDDSRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BVDDSRDY;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BVDDSRDY;
	}
}

static inline void hri_supc_clear_INTEN_BVDDSRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BVDDSRDY;
}

static inline void hri_supc_set_INTEN_BODCORERDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BODCORERDY;
}

static inline bool hri_supc_get_INTEN_BODCORERDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BODCORERDY) >> SUPC_INTENSET_BODCORERDY_Pos;
}

static inline void hri_supc_write_INTEN_BODCORERDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BODCORERDY;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BODCORERDY;
	}
}

static inline void hri_supc_clear_INTEN_BODCORERDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BODCORERDY;
}

static inline void hri_supc_set_INTEN_BODCOREDET_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BODCOREDET;
}

static inline bool hri_supc_get_INTEN_BODCOREDET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BODCOREDET) >> SUPC_INTENSET_BODCOREDET_Pos;
}

static inline void hri_supc_write_INTEN_BODCOREDET_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BODCOREDET;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BODCOREDET;
	}
}

static inline void hri_supc_clear_INTEN_BODCOREDET_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BODCOREDET;
}

static inline void hri_supc_set_INTEN_BCORESRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BCORESRDY;
}

static inline bool hri_supc_get_INTEN_BCORESRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BCORESRDY) >> SUPC_INTENSET_BCORESRDY_Pos;
}

static inline void hri_supc_write_INTEN_BCORESRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BCORESRDY;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BCORESRDY;
	}
}

static inline void hri_supc_clear_INTEN_BCORESRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BCORESRDY;
}

static inline void hri_supc_set_INTEN_reg(const void *const hw, hri_supc_intenset_reg_t mask)
{
	((Supc *)hw)->INTENSET.reg = mask;
}

static inline hri_supc_intenset_reg_t hri_supc_get_INTEN_reg(const void *const hw, hri_supc_intenset_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_supc_intenset_reg_t hri_supc_read_INTEN_reg(const void *const hw)
{
	return ((Supc *)hw)->INTENSET.reg;
}

static inline void hri_supc_write_INTEN_reg(const void *const hw, hri_supc_intenset_reg_t data)
{
	((Supc *)hw)->INTENSET.reg = data;
	((Supc *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_supc_clear_INTEN_reg(const void *const hw, hri_supc_intenset_reg_t mask)
{
	((Supc *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_supc_get_STATUS_BODVDDRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BODVDDRDY) >> SUPC_STATUS_BODVDDRDY_Pos;
}

static inline bool hri_supc_get_STATUS_BODVDDDET_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BODVDDDET) >> SUPC_STATUS_BODVDDDET_Pos;
}

static inline bool hri_supc_get_STATUS_BVDDSRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BVDDSRDY) >> SUPC_STATUS_BVDDSRDY_Pos;
}

static inline bool hri_supc_get_STATUS_BODCORERDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BODCORERDY) >> SUPC_STATUS_BODCORERDY_Pos;
}

static inline bool hri_supc_get_STATUS_BODCOREDET_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BODCOREDET) >> SUPC_STATUS_BODCOREDET_Pos;
}

static inline bool hri_supc_get_STATUS_BCORESRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BCORESRDY) >> SUPC_STATUS_BCORESRDY_Pos;
}

static inline hri_supc_status_reg_t hri_supc_get_STATUS_reg(const void *const hw, hri_supc_status_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_supc_status_reg_t hri_supc_read_STATUS_reg(const void *const hw)
{
	return ((Supc *)hw)->STATUS.reg;
}

static inline void hri_supc_set_BODVDD_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg |= SUPC_BODVDD_ENABLE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODVDD_ENABLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_ENABLE) >> SUPC_BODVDD_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODVDD_ENABLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp &= ~SUPC_BODVDD_ENABLE;
	tmp |= value << SUPC_BODVDD_ENABLE_Pos;
	((Supc *)hw)->BODVDD.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODVDD_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg &= ~SUPC_BODVDD_ENABLE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODVDD_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg ^= SUPC_BODVDD_ENABLE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODVDD_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg |= SUPC_BODVDD_HYST;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODVDD_HYST_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_HYST) >> SUPC_BODVDD_HYST_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODVDD_HYST_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp &= ~SUPC_BODVDD_HYST;
	tmp |= value << SUPC_BODVDD_HYST_Pos;
	((Supc *)hw)->BODVDD.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODVDD_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg &= ~SUPC_BODVDD_HYST;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODVDD_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg ^= SUPC_BODVDD_HYST;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODVDD_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg |= SUPC_BODVDD_STDBYCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODVDD_STDBYCFG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_STDBYCFG) >> SUPC_BODVDD_STDBYCFG_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODVDD_STDBYCFG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp &= ~SUPC_BODVDD_STDBYCFG;
	tmp |= value << SUPC_BODVDD_STDBYCFG_Pos;
	((Supc *)hw)->BODVDD.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODVDD_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg &= ~SUPC_BODVDD_STDBYCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODVDD_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg ^= SUPC_BODVDD_STDBYCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODVDD_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg |= SUPC_BODVDD_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODVDD_RUNSTDBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_RUNSTDBY) >> SUPC_BODVDD_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODVDD_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp &= ~SUPC_BODVDD_RUNSTDBY;
	tmp |= value << SUPC_BODVDD_RUNSTDBY_Pos;
	((Supc *)hw)->BODVDD.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODVDD_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg &= ~SUPC_BODVDD_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODVDD_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg ^= SUPC_BODVDD_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODVDD_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg |= SUPC_BODVDD_ACTCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODVDD_ACTCFG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_ACTCFG) >> SUPC_BODVDD_ACTCFG_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODVDD_ACTCFG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp &= ~SUPC_BODVDD_ACTCFG;
	tmp |= value << SUPC_BODVDD_ACTCFG_Pos;
	((Supc *)hw)->BODVDD.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODVDD_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg &= ~SUPC_BODVDD_ACTCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODVDD_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg ^= SUPC_BODVDD_ACTCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODVDD_ACTION_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg |= SUPC_BODVDD_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodvdd_reg_t hri_supc_get_BODVDD_ACTION_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_ACTION(mask)) >> SUPC_BODVDD_ACTION_Pos;
	return tmp;
}

static inline void hri_supc_write_BODVDD_ACTION_bf(const void *const hw, hri_supc_bodvdd_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp &= ~SUPC_BODVDD_ACTION_Msk;
	tmp |= SUPC_BODVDD_ACTION(data);
	((Supc *)hw)->BODVDD.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODVDD_ACTION_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg &= ~SUPC_BODVDD_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODVDD_ACTION_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg ^= SUPC_BODVDD_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodvdd_reg_t hri_supc_read_BODVDD_ACTION_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_ACTION_Msk) >> SUPC_BODVDD_ACTION_Pos;
	return tmp;
}

static inline void hri_supc_set_BODVDD_PSEL_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg |= SUPC_BODVDD_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodvdd_reg_t hri_supc_get_BODVDD_PSEL_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_PSEL(mask)) >> SUPC_BODVDD_PSEL_Pos;
	return tmp;
}

static inline void hri_supc_write_BODVDD_PSEL_bf(const void *const hw, hri_supc_bodvdd_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp &= ~SUPC_BODVDD_PSEL_Msk;
	tmp |= SUPC_BODVDD_PSEL(data);
	((Supc *)hw)->BODVDD.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODVDD_PSEL_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg &= ~SUPC_BODVDD_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODVDD_PSEL_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg ^= SUPC_BODVDD_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodvdd_reg_t hri_supc_read_BODVDD_PSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_PSEL_Msk) >> SUPC_BODVDD_PSEL_Pos;
	return tmp;
}

static inline void hri_supc_set_BODVDD_LEVEL_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg |= SUPC_BODVDD_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodvdd_reg_t hri_supc_get_BODVDD_LEVEL_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_LEVEL(mask)) >> SUPC_BODVDD_LEVEL_Pos;
	return tmp;
}

static inline void hri_supc_write_BODVDD_LEVEL_bf(const void *const hw, hri_supc_bodvdd_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp &= ~SUPC_BODVDD_LEVEL_Msk;
	tmp |= SUPC_BODVDD_LEVEL(data);
	((Supc *)hw)->BODVDD.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODVDD_LEVEL_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg &= ~SUPC_BODVDD_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODVDD_LEVEL_bf(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg ^= SUPC_BODVDD_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodvdd_reg_t hri_supc_read_BODVDD_LEVEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp = (tmp & SUPC_BODVDD_LEVEL_Msk) >> SUPC_BODVDD_LEVEL_Pos;
	return tmp;
}

static inline void hri_supc_set_BODVDD_reg(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodvdd_reg_t hri_supc_get_BODVDD_reg(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODVDD.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_BODVDD_reg(const void *const hw, hri_supc_bodvdd_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODVDD_reg(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODVDD_reg(const void *const hw, hri_supc_bodvdd_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODVDD.reg ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodvdd_reg_t hri_supc_read_BODVDD_reg(const void *const hw)
{
	return ((Supc *)hw)->BODVDD.reg;
}

static inline void hri_supc_set_BODCORE_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg |= SUPC_BODCORE_ENABLE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODCORE_ENABLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_ENABLE) >> SUPC_BODCORE_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODCORE_ENABLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp &= ~SUPC_BODCORE_ENABLE;
	tmp |= value << SUPC_BODCORE_ENABLE_Pos;
	((Supc *)hw)->BODCORE.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODCORE_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg &= ~SUPC_BODCORE_ENABLE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODCORE_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg ^= SUPC_BODCORE_ENABLE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODCORE_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg |= SUPC_BODCORE_HYST;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODCORE_HYST_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_HYST) >> SUPC_BODCORE_HYST_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODCORE_HYST_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp &= ~SUPC_BODCORE_HYST;
	tmp |= value << SUPC_BODCORE_HYST_Pos;
	((Supc *)hw)->BODCORE.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODCORE_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg &= ~SUPC_BODCORE_HYST;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODCORE_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg ^= SUPC_BODCORE_HYST;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODCORE_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg |= SUPC_BODCORE_STDBYCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODCORE_STDBYCFG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_STDBYCFG) >> SUPC_BODCORE_STDBYCFG_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODCORE_STDBYCFG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp &= ~SUPC_BODCORE_STDBYCFG;
	tmp |= value << SUPC_BODCORE_STDBYCFG_Pos;
	((Supc *)hw)->BODCORE.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODCORE_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg &= ~SUPC_BODCORE_STDBYCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODCORE_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg ^= SUPC_BODCORE_STDBYCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODCORE_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg |= SUPC_BODCORE_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODCORE_RUNSTDBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_RUNSTDBY) >> SUPC_BODCORE_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODCORE_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp &= ~SUPC_BODCORE_RUNSTDBY;
	tmp |= value << SUPC_BODCORE_RUNSTDBY_Pos;
	((Supc *)hw)->BODCORE.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODCORE_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg &= ~SUPC_BODCORE_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODCORE_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg ^= SUPC_BODCORE_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODCORE_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg |= SUPC_BODCORE_ACTCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BODCORE_ACTCFG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_ACTCFG) >> SUPC_BODCORE_ACTCFG_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BODCORE_ACTCFG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp &= ~SUPC_BODCORE_ACTCFG;
	tmp |= value << SUPC_BODCORE_ACTCFG_Pos;
	((Supc *)hw)->BODCORE.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODCORE_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg &= ~SUPC_BODCORE_ACTCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODCORE_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg ^= SUPC_BODCORE_ACTCFG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BODCORE_ACTION_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg |= SUPC_BODCORE_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodcore_reg_t hri_supc_get_BODCORE_ACTION_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_ACTION(mask)) >> SUPC_BODCORE_ACTION_Pos;
	return tmp;
}

static inline void hri_supc_write_BODCORE_ACTION_bf(const void *const hw, hri_supc_bodcore_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp &= ~SUPC_BODCORE_ACTION_Msk;
	tmp |= SUPC_BODCORE_ACTION(data);
	((Supc *)hw)->BODCORE.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODCORE_ACTION_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg &= ~SUPC_BODCORE_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODCORE_ACTION_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg ^= SUPC_BODCORE_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodcore_reg_t hri_supc_read_BODCORE_ACTION_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_ACTION_Msk) >> SUPC_BODCORE_ACTION_Pos;
	return tmp;
}

static inline void hri_supc_set_BODCORE_PSEL_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg |= SUPC_BODCORE_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodcore_reg_t hri_supc_get_BODCORE_PSEL_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_PSEL(mask)) >> SUPC_BODCORE_PSEL_Pos;
	return tmp;
}

static inline void hri_supc_write_BODCORE_PSEL_bf(const void *const hw, hri_supc_bodcore_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp &= ~SUPC_BODCORE_PSEL_Msk;
	tmp |= SUPC_BODCORE_PSEL(data);
	((Supc *)hw)->BODCORE.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODCORE_PSEL_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg &= ~SUPC_BODCORE_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODCORE_PSEL_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg ^= SUPC_BODCORE_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodcore_reg_t hri_supc_read_BODCORE_PSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_PSEL_Msk) >> SUPC_BODCORE_PSEL_Pos;
	return tmp;
}

static inline void hri_supc_set_BODCORE_LEVEL_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg |= SUPC_BODCORE_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodcore_reg_t hri_supc_get_BODCORE_LEVEL_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_LEVEL(mask)) >> SUPC_BODCORE_LEVEL_Pos;
	return tmp;
}

static inline void hri_supc_write_BODCORE_LEVEL_bf(const void *const hw, hri_supc_bodcore_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp &= ~SUPC_BODCORE_LEVEL_Msk;
	tmp |= SUPC_BODCORE_LEVEL(data);
	((Supc *)hw)->BODCORE.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODCORE_LEVEL_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg &= ~SUPC_BODCORE_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODCORE_LEVEL_bf(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg ^= SUPC_BODCORE_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodcore_reg_t hri_supc_read_BODCORE_LEVEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp = (tmp & SUPC_BODCORE_LEVEL_Msk) >> SUPC_BODCORE_LEVEL_Pos;
	return tmp;
}

static inline void hri_supc_set_BODCORE_reg(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodcore_reg_t hri_supc_get_BODCORE_reg(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BODCORE.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_BODCORE_reg(const void *const hw, hri_supc_bodcore_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BODCORE_reg(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BODCORE_reg(const void *const hw, hri_supc_bodcore_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BODCORE.reg ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bodcore_reg_t hri_supc_read_BODCORE_reg(const void *const hw)
{
	return ((Supc *)hw)->BODCORE.reg;
}

static inline void hri_supc_set_VREG_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_ENABLE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREG_ENABLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_ENABLE) >> SUPC_VREG_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREG_ENABLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_ENABLE;
	tmp |= value << SUPC_VREG_ENABLE_Pos;
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_ENABLE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_ENABLE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREG_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREG_RUNSTDBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_RUNSTDBY) >> SUPC_VREG_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREG_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_RUNSTDBY;
	tmp |= value << SUPC_VREG_RUNSTDBY_Pos;
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREG_reg(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vreg_reg_t hri_supc_get_VREG_reg(const void *const hw, hri_supc_vreg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_VREG_reg(const void *const hw, hri_supc_vreg_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_reg(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_reg(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vreg_reg_t hri_supc_read_VREG_reg(const void *const hw)
{
	return ((Supc *)hw)->VREG.reg;
}

static inline void hri_supc_set_VREF_TSEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= SUPC_VREF_TSEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREF_TSEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_TSEN) >> SUPC_VREF_TSEN_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREF_TSEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_TSEN;
	tmp |= value << SUPC_VREF_TSEN_Pos;
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_TSEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_TSEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_TSEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_TSEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREF_VREFOE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= SUPC_VREF_VREFOE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREF_VREFOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_VREFOE) >> SUPC_VREF_VREFOE_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREF_VREFOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_VREFOE;
	tmp |= value << SUPC_VREF_VREFOE_Pos;
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_VREFOE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_VREFOE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_VREFOE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_VREFOE;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREF_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= SUPC_VREF_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREF_RUNSTDBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_RUNSTDBY) >> SUPC_VREF_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREF_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_RUNSTDBY;
	tmp |= value << SUPC_VREF_RUNSTDBY_Pos;
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_RUNSTDBY;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREF_ONDEMAND_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= SUPC_VREF_ONDEMAND;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREF_ONDEMAND_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_ONDEMAND) >> SUPC_VREF_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREF_ONDEMAND_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_ONDEMAND;
	tmp |= value << SUPC_VREF_ONDEMAND_Pos;
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_ONDEMAND_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_ONDEMAND;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_ONDEMAND_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_ONDEMAND;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREF_SEL_bf(const void *const hw, hri_supc_vref_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= SUPC_VREF_SEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vref_reg_t hri_supc_get_VREF_SEL_bf(const void *const hw, hri_supc_vref_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_SEL(mask)) >> SUPC_VREF_SEL_Pos;
	return tmp;
}

static inline void hri_supc_write_VREF_SEL_bf(const void *const hw, hri_supc_vref_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_SEL_Msk;
	tmp |= SUPC_VREF_SEL(data);
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_SEL_bf(const void *const hw, hri_supc_vref_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_SEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_SEL_bf(const void *const hw, hri_supc_vref_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_SEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vref_reg_t hri_supc_read_VREF_SEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_SEL_Msk) >> SUPC_VREF_SEL_Pos;
	return tmp;
}

static inline void hri_supc_set_VREF_reg(const void *const hw, hri_supc_vref_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vref_reg_t hri_supc_get_VREF_reg(const void *const hw, hri_supc_vref_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_VREF_reg(const void *const hw, hri_supc_vref_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_reg(const void *const hw, hri_supc_vref_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_reg(const void *const hw, hri_supc_vref_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vref_reg_t hri_supc_read_VREF_reg(const void *const hw)
{
	return ((Supc *)hw)->VREF.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SUPC_C21_H_INCLUDED */
#endif /* _SAMC21_SUPC_COMPONENT_ */
