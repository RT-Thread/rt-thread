/**
 * \file
 *
 * \brief SAM TSENS
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

#ifdef _SAMC21_TSENS_COMPONENT_
#ifndef _HRI_TSENS_C21_H_INCLUDED_
#define _HRI_TSENS_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_TSENS_CRITICAL_SECTIONS)
#define TSENS_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define TSENS_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define TSENS_CRITICAL_SECTION_ENTER()
#define TSENS_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_tsens_cal_reg_t;
typedef uint32_t hri_tsens_gain_reg_t;
typedef uint32_t hri_tsens_offset_reg_t;
typedef uint32_t hri_tsens_syncbusy_reg_t;
typedef uint32_t hri_tsens_value_reg_t;
typedef uint32_t hri_tsens_winlt_reg_t;
typedef uint32_t hri_tsens_winut_reg_t;
typedef uint8_t  hri_tsens_ctrla_reg_t;
typedef uint8_t  hri_tsens_ctrlb_reg_t;
typedef uint8_t  hri_tsens_ctrlc_reg_t;
typedef uint8_t  hri_tsens_dbgctrl_reg_t;
typedef uint8_t  hri_tsens_evctrl_reg_t;
typedef uint8_t  hri_tsens_intenset_reg_t;
typedef uint8_t  hri_tsens_intflag_reg_t;
typedef uint8_t  hri_tsens_status_reg_t;

static inline void hri_tsens_wait_for_sync(const void *const hw, hri_tsens_syncbusy_reg_t reg)
{
	while (((Tsens *)hw)->SYNCBUSY.reg & reg) {
	};
}

static inline bool hri_tsens_is_syncing(const void *const hw, hri_tsens_syncbusy_reg_t reg)
{
	return ((Tsens *)hw)->SYNCBUSY.reg & reg;
}

static inline bool hri_tsens_get_INTFLAG_RESRDY_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTFLAG.reg & TSENS_INTFLAG_RESRDY) >> TSENS_INTFLAG_RESRDY_Pos;
}

static inline void hri_tsens_clear_INTFLAG_RESRDY_bit(const void *const hw)
{
	((Tsens *)hw)->INTFLAG.reg = TSENS_INTFLAG_RESRDY;
}

static inline bool hri_tsens_get_INTFLAG_OVERRUN_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTFLAG.reg & TSENS_INTFLAG_OVERRUN) >> TSENS_INTFLAG_OVERRUN_Pos;
}

static inline void hri_tsens_clear_INTFLAG_OVERRUN_bit(const void *const hw)
{
	((Tsens *)hw)->INTFLAG.reg = TSENS_INTFLAG_OVERRUN;
}

static inline bool hri_tsens_get_INTFLAG_WINMON_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTFLAG.reg & TSENS_INTFLAG_WINMON) >> TSENS_INTFLAG_WINMON_Pos;
}

static inline void hri_tsens_clear_INTFLAG_WINMON_bit(const void *const hw)
{
	((Tsens *)hw)->INTFLAG.reg = TSENS_INTFLAG_WINMON;
}

static inline bool hri_tsens_get_INTFLAG_OVF_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTFLAG.reg & TSENS_INTFLAG_OVF) >> TSENS_INTFLAG_OVF_Pos;
}

static inline void hri_tsens_clear_INTFLAG_OVF_bit(const void *const hw)
{
	((Tsens *)hw)->INTFLAG.reg = TSENS_INTFLAG_OVF;
}

static inline bool hri_tsens_get_interrupt_RESRDY_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTFLAG.reg & TSENS_INTFLAG_RESRDY) >> TSENS_INTFLAG_RESRDY_Pos;
}

static inline void hri_tsens_clear_interrupt_RESRDY_bit(const void *const hw)
{
	((Tsens *)hw)->INTFLAG.reg = TSENS_INTFLAG_RESRDY;
}

static inline bool hri_tsens_get_interrupt_OVERRUN_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTFLAG.reg & TSENS_INTFLAG_OVERRUN) >> TSENS_INTFLAG_OVERRUN_Pos;
}

static inline void hri_tsens_clear_interrupt_OVERRUN_bit(const void *const hw)
{
	((Tsens *)hw)->INTFLAG.reg = TSENS_INTFLAG_OVERRUN;
}

static inline bool hri_tsens_get_interrupt_WINMON_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTFLAG.reg & TSENS_INTFLAG_WINMON) >> TSENS_INTFLAG_WINMON_Pos;
}

static inline void hri_tsens_clear_interrupt_WINMON_bit(const void *const hw)
{
	((Tsens *)hw)->INTFLAG.reg = TSENS_INTFLAG_WINMON;
}

static inline bool hri_tsens_get_interrupt_OVF_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTFLAG.reg & TSENS_INTFLAG_OVF) >> TSENS_INTFLAG_OVF_Pos;
}

static inline void hri_tsens_clear_interrupt_OVF_bit(const void *const hw)
{
	((Tsens *)hw)->INTFLAG.reg = TSENS_INTFLAG_OVF;
}

static inline hri_tsens_intflag_reg_t hri_tsens_get_INTFLAG_reg(const void *const hw, hri_tsens_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tsens_intflag_reg_t hri_tsens_read_INTFLAG_reg(const void *const hw)
{
	return ((Tsens *)hw)->INTFLAG.reg;
}

static inline void hri_tsens_clear_INTFLAG_reg(const void *const hw, hri_tsens_intflag_reg_t mask)
{
	((Tsens *)hw)->INTFLAG.reg = mask;
}

static inline void hri_tsens_set_INTEN_RESRDY_bit(const void *const hw)
{
	((Tsens *)hw)->INTENSET.reg = TSENS_INTENSET_RESRDY;
}

static inline bool hri_tsens_get_INTEN_RESRDY_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTENSET.reg & TSENS_INTENSET_RESRDY) >> TSENS_INTENSET_RESRDY_Pos;
}

static inline void hri_tsens_write_INTEN_RESRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Tsens *)hw)->INTENCLR.reg = TSENS_INTENSET_RESRDY;
	} else {
		((Tsens *)hw)->INTENSET.reg = TSENS_INTENSET_RESRDY;
	}
}

static inline void hri_tsens_clear_INTEN_RESRDY_bit(const void *const hw)
{
	((Tsens *)hw)->INTENCLR.reg = TSENS_INTENSET_RESRDY;
}

static inline void hri_tsens_set_INTEN_OVERRUN_bit(const void *const hw)
{
	((Tsens *)hw)->INTENSET.reg = TSENS_INTENSET_OVERRUN;
}

static inline bool hri_tsens_get_INTEN_OVERRUN_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTENSET.reg & TSENS_INTENSET_OVERRUN) >> TSENS_INTENSET_OVERRUN_Pos;
}

static inline void hri_tsens_write_INTEN_OVERRUN_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Tsens *)hw)->INTENCLR.reg = TSENS_INTENSET_OVERRUN;
	} else {
		((Tsens *)hw)->INTENSET.reg = TSENS_INTENSET_OVERRUN;
	}
}

static inline void hri_tsens_clear_INTEN_OVERRUN_bit(const void *const hw)
{
	((Tsens *)hw)->INTENCLR.reg = TSENS_INTENSET_OVERRUN;
}

static inline void hri_tsens_set_INTEN_WINMON_bit(const void *const hw)
{
	((Tsens *)hw)->INTENSET.reg = TSENS_INTENSET_WINMON;
}

static inline bool hri_tsens_get_INTEN_WINMON_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTENSET.reg & TSENS_INTENSET_WINMON) >> TSENS_INTENSET_WINMON_Pos;
}

static inline void hri_tsens_write_INTEN_WINMON_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Tsens *)hw)->INTENCLR.reg = TSENS_INTENSET_WINMON;
	} else {
		((Tsens *)hw)->INTENSET.reg = TSENS_INTENSET_WINMON;
	}
}

static inline void hri_tsens_clear_INTEN_WINMON_bit(const void *const hw)
{
	((Tsens *)hw)->INTENCLR.reg = TSENS_INTENSET_WINMON;
}

static inline void hri_tsens_set_INTEN_OVF_bit(const void *const hw)
{
	((Tsens *)hw)->INTENSET.reg = TSENS_INTENSET_OVF;
}

static inline bool hri_tsens_get_INTEN_OVF_bit(const void *const hw)
{
	return (((Tsens *)hw)->INTENSET.reg & TSENS_INTENSET_OVF) >> TSENS_INTENSET_OVF_Pos;
}

static inline void hri_tsens_write_INTEN_OVF_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Tsens *)hw)->INTENCLR.reg = TSENS_INTENSET_OVF;
	} else {
		((Tsens *)hw)->INTENSET.reg = TSENS_INTENSET_OVF;
	}
}

static inline void hri_tsens_clear_INTEN_OVF_bit(const void *const hw)
{
	((Tsens *)hw)->INTENCLR.reg = TSENS_INTENSET_OVF;
}

static inline void hri_tsens_set_INTEN_reg(const void *const hw, hri_tsens_intenset_reg_t mask)
{
	((Tsens *)hw)->INTENSET.reg = mask;
}

static inline hri_tsens_intenset_reg_t hri_tsens_get_INTEN_reg(const void *const hw, hri_tsens_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tsens_intenset_reg_t hri_tsens_read_INTEN_reg(const void *const hw)
{
	return ((Tsens *)hw)->INTENSET.reg;
}

static inline void hri_tsens_write_INTEN_reg(const void *const hw, hri_tsens_intenset_reg_t data)
{
	((Tsens *)hw)->INTENSET.reg = data;
	((Tsens *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_tsens_clear_INTEN_reg(const void *const hw, hri_tsens_intenset_reg_t mask)
{
	((Tsens *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_tsens_get_STATUS_OVF_bit(const void *const hw)
{
	return (((Tsens *)hw)->STATUS.reg & TSENS_STATUS_OVF) >> TSENS_STATUS_OVF_Pos;
}

static inline hri_tsens_status_reg_t hri_tsens_get_STATUS_reg(const void *const hw, hri_tsens_status_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tsens_status_reg_t hri_tsens_read_STATUS_reg(const void *const hw)
{
	return ((Tsens *)hw)->STATUS.reg;
}

static inline bool hri_tsens_get_SYNCBUSY_SWRST_bit(const void *const hw)
{
	return (((Tsens *)hw)->SYNCBUSY.reg & TSENS_SYNCBUSY_SWRST) >> TSENS_SYNCBUSY_SWRST_Pos;
}

static inline bool hri_tsens_get_SYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Tsens *)hw)->SYNCBUSY.reg & TSENS_SYNCBUSY_ENABLE) >> TSENS_SYNCBUSY_ENABLE_Pos;
}

static inline hri_tsens_syncbusy_reg_t hri_tsens_get_SYNCBUSY_reg(const void *const hw, hri_tsens_syncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->SYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tsens_syncbusy_reg_t hri_tsens_read_SYNCBUSY_reg(const void *const hw)
{
	return ((Tsens *)hw)->SYNCBUSY.reg;
}

static inline hri_tsens_value_reg_t hri_tsens_get_VALUE_VALUE_bf(const void *const hw, hri_tsens_value_reg_t mask)
{
	return (((Tsens *)hw)->VALUE.reg & TSENS_VALUE_VALUE(mask)) >> TSENS_VALUE_VALUE_Pos;
}

static inline hri_tsens_value_reg_t hri_tsens_read_VALUE_VALUE_bf(const void *const hw)
{
	return (((Tsens *)hw)->VALUE.reg & TSENS_VALUE_VALUE_Msk) >> TSENS_VALUE_VALUE_Pos;
}

static inline hri_tsens_value_reg_t hri_tsens_get_VALUE_reg(const void *const hw, hri_tsens_value_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->VALUE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tsens_value_reg_t hri_tsens_read_VALUE_reg(const void *const hw)
{
	return ((Tsens *)hw)->VALUE.reg;
}

static inline void hri_tsens_set_CTRLA_SWRST_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg |= TSENS_CTRLA_SWRST;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_SWRST);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tsens_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint8_t tmp;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_SWRST);
	tmp = ((Tsens *)hw)->CTRLA.reg;
	tmp = (tmp & TSENS_CTRLA_SWRST) >> TSENS_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_tsens_set_CTRLA_ENABLE_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg |= TSENS_CTRLA_ENABLE;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_SWRST | TSENS_SYNCBUSY_ENABLE);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tsens_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_SWRST | TSENS_SYNCBUSY_ENABLE);
	tmp = ((Tsens *)hw)->CTRLA.reg;
	tmp = (tmp & TSENS_CTRLA_ENABLE) >> TSENS_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_tsens_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->CTRLA.reg;
	tmp &= ~TSENS_CTRLA_ENABLE;
	tmp |= value << TSENS_CTRLA_ENABLE_Pos;
	((Tsens *)hw)->CTRLA.reg = tmp;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_SWRST | TSENS_SYNCBUSY_ENABLE);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg &= ~TSENS_CTRLA_ENABLE;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_SWRST | TSENS_SYNCBUSY_ENABLE);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg ^= TSENS_CTRLA_ENABLE;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_SWRST | TSENS_SYNCBUSY_ENABLE);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_set_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg |= TSENS_CTRLA_RUNSTDBY;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tsens_get_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->CTRLA.reg;
	tmp = (tmp & TSENS_CTRLA_RUNSTDBY) >> TSENS_CTRLA_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_tsens_write_CTRLA_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->CTRLA.reg;
	tmp &= ~TSENS_CTRLA_RUNSTDBY;
	tmp |= value << TSENS_CTRLA_RUNSTDBY_Pos;
	((Tsens *)hw)->CTRLA.reg = tmp;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg &= ~TSENS_CTRLA_RUNSTDBY;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg ^= TSENS_CTRLA_RUNSTDBY;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_set_CTRLA_reg(const void *const hw, hri_tsens_ctrla_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg |= mask;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_ctrla_reg_t hri_tsens_get_CTRLA_reg(const void *const hw, hri_tsens_ctrla_reg_t mask)
{
	uint8_t tmp;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	tmp = ((Tsens *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tsens_write_CTRLA_reg(const void *const hw, hri_tsens_ctrla_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg = data;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_CTRLA_reg(const void *const hw, hri_tsens_ctrla_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg &= ~mask;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_CTRLA_reg(const void *const hw, hri_tsens_ctrla_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLA.reg ^= mask;
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_ctrla_reg_t hri_tsens_read_CTRLA_reg(const void *const hw)
{
	hri_tsens_wait_for_sync(hw, TSENS_SYNCBUSY_MASK);
	return ((Tsens *)hw)->CTRLA.reg;
}

static inline void hri_tsens_set_CTRLC_FREERUN_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg |= TSENS_CTRLC_FREERUN;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tsens_get_CTRLC_FREERUN_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->CTRLC.reg;
	tmp = (tmp & TSENS_CTRLC_FREERUN) >> TSENS_CTRLC_FREERUN_Pos;
	return (bool)tmp;
}

static inline void hri_tsens_write_CTRLC_FREERUN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->CTRLC.reg;
	tmp &= ~TSENS_CTRLC_FREERUN;
	tmp |= value << TSENS_CTRLC_FREERUN_Pos;
	((Tsens *)hw)->CTRLC.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_CTRLC_FREERUN_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg &= ~TSENS_CTRLC_FREERUN;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_CTRLC_FREERUN_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg ^= TSENS_CTRLC_FREERUN;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_set_CTRLC_WINMODE_bf(const void *const hw, hri_tsens_ctrlc_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg |= TSENS_CTRLC_WINMODE(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_ctrlc_reg_t hri_tsens_get_CTRLC_WINMODE_bf(const void *const hw, hri_tsens_ctrlc_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->CTRLC.reg;
	tmp = (tmp & TSENS_CTRLC_WINMODE(mask)) >> TSENS_CTRLC_WINMODE_Pos;
	return tmp;
}

static inline void hri_tsens_write_CTRLC_WINMODE_bf(const void *const hw, hri_tsens_ctrlc_reg_t data)
{
	uint8_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->CTRLC.reg;
	tmp &= ~TSENS_CTRLC_WINMODE_Msk;
	tmp |= TSENS_CTRLC_WINMODE(data);
	((Tsens *)hw)->CTRLC.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_CTRLC_WINMODE_bf(const void *const hw, hri_tsens_ctrlc_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg &= ~TSENS_CTRLC_WINMODE(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_CTRLC_WINMODE_bf(const void *const hw, hri_tsens_ctrlc_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg ^= TSENS_CTRLC_WINMODE(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_ctrlc_reg_t hri_tsens_read_CTRLC_WINMODE_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->CTRLC.reg;
	tmp = (tmp & TSENS_CTRLC_WINMODE_Msk) >> TSENS_CTRLC_WINMODE_Pos;
	return tmp;
}

static inline void hri_tsens_set_CTRLC_reg(const void *const hw, hri_tsens_ctrlc_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg |= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_ctrlc_reg_t hri_tsens_get_CTRLC_reg(const void *const hw, hri_tsens_ctrlc_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->CTRLC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tsens_write_CTRLC_reg(const void *const hw, hri_tsens_ctrlc_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg = data;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_CTRLC_reg(const void *const hw, hri_tsens_ctrlc_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg &= ~mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_CTRLC_reg(const void *const hw, hri_tsens_ctrlc_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLC.reg ^= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_ctrlc_reg_t hri_tsens_read_CTRLC_reg(const void *const hw)
{
	return ((Tsens *)hw)->CTRLC.reg;
}

static inline void hri_tsens_set_EVCTRL_STARTEI_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg |= TSENS_EVCTRL_STARTEI;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tsens_get_EVCTRL_STARTEI_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->EVCTRL.reg;
	tmp = (tmp & TSENS_EVCTRL_STARTEI) >> TSENS_EVCTRL_STARTEI_Pos;
	return (bool)tmp;
}

static inline void hri_tsens_write_EVCTRL_STARTEI_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->EVCTRL.reg;
	tmp &= ~TSENS_EVCTRL_STARTEI;
	tmp |= value << TSENS_EVCTRL_STARTEI_Pos;
	((Tsens *)hw)->EVCTRL.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_EVCTRL_STARTEI_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg &= ~TSENS_EVCTRL_STARTEI;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_EVCTRL_STARTEI_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg ^= TSENS_EVCTRL_STARTEI;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_set_EVCTRL_STARTINV_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg |= TSENS_EVCTRL_STARTINV;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tsens_get_EVCTRL_STARTINV_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->EVCTRL.reg;
	tmp = (tmp & TSENS_EVCTRL_STARTINV) >> TSENS_EVCTRL_STARTINV_Pos;
	return (bool)tmp;
}

static inline void hri_tsens_write_EVCTRL_STARTINV_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->EVCTRL.reg;
	tmp &= ~TSENS_EVCTRL_STARTINV;
	tmp |= value << TSENS_EVCTRL_STARTINV_Pos;
	((Tsens *)hw)->EVCTRL.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_EVCTRL_STARTINV_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg &= ~TSENS_EVCTRL_STARTINV;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_EVCTRL_STARTINV_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg ^= TSENS_EVCTRL_STARTINV;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_set_EVCTRL_WINEO_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg |= TSENS_EVCTRL_WINEO;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tsens_get_EVCTRL_WINEO_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->EVCTRL.reg;
	tmp = (tmp & TSENS_EVCTRL_WINEO) >> TSENS_EVCTRL_WINEO_Pos;
	return (bool)tmp;
}

static inline void hri_tsens_write_EVCTRL_WINEO_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->EVCTRL.reg;
	tmp &= ~TSENS_EVCTRL_WINEO;
	tmp |= value << TSENS_EVCTRL_WINEO_Pos;
	((Tsens *)hw)->EVCTRL.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_EVCTRL_WINEO_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg &= ~TSENS_EVCTRL_WINEO;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_EVCTRL_WINEO_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg ^= TSENS_EVCTRL_WINEO;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_set_EVCTRL_reg(const void *const hw, hri_tsens_evctrl_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg |= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_evctrl_reg_t hri_tsens_get_EVCTRL_reg(const void *const hw, hri_tsens_evctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tsens_write_EVCTRL_reg(const void *const hw, hri_tsens_evctrl_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg = data;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_EVCTRL_reg(const void *const hw, hri_tsens_evctrl_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg &= ~mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_EVCTRL_reg(const void *const hw, hri_tsens_evctrl_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->EVCTRL.reg ^= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_evctrl_reg_t hri_tsens_read_EVCTRL_reg(const void *const hw)
{
	return ((Tsens *)hw)->EVCTRL.reg;
}

static inline void hri_tsens_set_WINLT_WINLT_bf(const void *const hw, hri_tsens_winlt_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINLT.reg |= TSENS_WINLT_WINLT(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_winlt_reg_t hri_tsens_get_WINLT_WINLT_bf(const void *const hw, hri_tsens_winlt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->WINLT.reg;
	tmp = (tmp & TSENS_WINLT_WINLT(mask)) >> TSENS_WINLT_WINLT_Pos;
	return tmp;
}

static inline void hri_tsens_write_WINLT_WINLT_bf(const void *const hw, hri_tsens_winlt_reg_t data)
{
	uint32_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->WINLT.reg;
	tmp &= ~TSENS_WINLT_WINLT_Msk;
	tmp |= TSENS_WINLT_WINLT(data);
	((Tsens *)hw)->WINLT.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_WINLT_WINLT_bf(const void *const hw, hri_tsens_winlt_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINLT.reg &= ~TSENS_WINLT_WINLT(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_WINLT_WINLT_bf(const void *const hw, hri_tsens_winlt_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINLT.reg ^= TSENS_WINLT_WINLT(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_winlt_reg_t hri_tsens_read_WINLT_WINLT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->WINLT.reg;
	tmp = (tmp & TSENS_WINLT_WINLT_Msk) >> TSENS_WINLT_WINLT_Pos;
	return tmp;
}

static inline void hri_tsens_set_WINLT_reg(const void *const hw, hri_tsens_winlt_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINLT.reg |= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_winlt_reg_t hri_tsens_get_WINLT_reg(const void *const hw, hri_tsens_winlt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->WINLT.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tsens_write_WINLT_reg(const void *const hw, hri_tsens_winlt_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINLT.reg = data;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_WINLT_reg(const void *const hw, hri_tsens_winlt_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINLT.reg &= ~mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_WINLT_reg(const void *const hw, hri_tsens_winlt_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINLT.reg ^= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_winlt_reg_t hri_tsens_read_WINLT_reg(const void *const hw)
{
	return ((Tsens *)hw)->WINLT.reg;
}

static inline void hri_tsens_set_WINUT_WINUT_bf(const void *const hw, hri_tsens_winut_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINUT.reg |= TSENS_WINUT_WINUT(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_winut_reg_t hri_tsens_get_WINUT_WINUT_bf(const void *const hw, hri_tsens_winut_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->WINUT.reg;
	tmp = (tmp & TSENS_WINUT_WINUT(mask)) >> TSENS_WINUT_WINUT_Pos;
	return tmp;
}

static inline void hri_tsens_write_WINUT_WINUT_bf(const void *const hw, hri_tsens_winut_reg_t data)
{
	uint32_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->WINUT.reg;
	tmp &= ~TSENS_WINUT_WINUT_Msk;
	tmp |= TSENS_WINUT_WINUT(data);
	((Tsens *)hw)->WINUT.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_WINUT_WINUT_bf(const void *const hw, hri_tsens_winut_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINUT.reg &= ~TSENS_WINUT_WINUT(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_WINUT_WINUT_bf(const void *const hw, hri_tsens_winut_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINUT.reg ^= TSENS_WINUT_WINUT(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_winut_reg_t hri_tsens_read_WINUT_WINUT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->WINUT.reg;
	tmp = (tmp & TSENS_WINUT_WINUT_Msk) >> TSENS_WINUT_WINUT_Pos;
	return tmp;
}

static inline void hri_tsens_set_WINUT_reg(const void *const hw, hri_tsens_winut_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINUT.reg |= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_winut_reg_t hri_tsens_get_WINUT_reg(const void *const hw, hri_tsens_winut_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->WINUT.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tsens_write_WINUT_reg(const void *const hw, hri_tsens_winut_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINUT.reg = data;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_WINUT_reg(const void *const hw, hri_tsens_winut_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINUT.reg &= ~mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_WINUT_reg(const void *const hw, hri_tsens_winut_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->WINUT.reg ^= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_winut_reg_t hri_tsens_read_WINUT_reg(const void *const hw)
{
	return ((Tsens *)hw)->WINUT.reg;
}

static inline void hri_tsens_set_GAIN_GAIN_bf(const void *const hw, hri_tsens_gain_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->GAIN.reg |= TSENS_GAIN_GAIN(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_gain_reg_t hri_tsens_get_GAIN_GAIN_bf(const void *const hw, hri_tsens_gain_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->GAIN.reg;
	tmp = (tmp & TSENS_GAIN_GAIN(mask)) >> TSENS_GAIN_GAIN_Pos;
	return tmp;
}

static inline void hri_tsens_write_GAIN_GAIN_bf(const void *const hw, hri_tsens_gain_reg_t data)
{
	uint32_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->GAIN.reg;
	tmp &= ~TSENS_GAIN_GAIN_Msk;
	tmp |= TSENS_GAIN_GAIN(data);
	((Tsens *)hw)->GAIN.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_GAIN_GAIN_bf(const void *const hw, hri_tsens_gain_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->GAIN.reg &= ~TSENS_GAIN_GAIN(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_GAIN_GAIN_bf(const void *const hw, hri_tsens_gain_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->GAIN.reg ^= TSENS_GAIN_GAIN(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_gain_reg_t hri_tsens_read_GAIN_GAIN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->GAIN.reg;
	tmp = (tmp & TSENS_GAIN_GAIN_Msk) >> TSENS_GAIN_GAIN_Pos;
	return tmp;
}

static inline void hri_tsens_set_GAIN_reg(const void *const hw, hri_tsens_gain_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->GAIN.reg |= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_gain_reg_t hri_tsens_get_GAIN_reg(const void *const hw, hri_tsens_gain_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->GAIN.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tsens_write_GAIN_reg(const void *const hw, hri_tsens_gain_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->GAIN.reg = data;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_GAIN_reg(const void *const hw, hri_tsens_gain_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->GAIN.reg &= ~mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_GAIN_reg(const void *const hw, hri_tsens_gain_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->GAIN.reg ^= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_gain_reg_t hri_tsens_read_GAIN_reg(const void *const hw)
{
	return ((Tsens *)hw)->GAIN.reg;
}

static inline void hri_tsens_set_OFFSET_OFFSETC_bf(const void *const hw, hri_tsens_offset_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->OFFSET.reg |= TSENS_OFFSET_OFFSETC(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_offset_reg_t hri_tsens_get_OFFSET_OFFSETC_bf(const void *const hw, hri_tsens_offset_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->OFFSET.reg;
	tmp = (tmp & TSENS_OFFSET_OFFSETC(mask)) >> TSENS_OFFSET_OFFSETC_Pos;
	return tmp;
}

static inline void hri_tsens_write_OFFSET_OFFSETC_bf(const void *const hw, hri_tsens_offset_reg_t data)
{
	uint32_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->OFFSET.reg;
	tmp &= ~TSENS_OFFSET_OFFSETC_Msk;
	tmp |= TSENS_OFFSET_OFFSETC(data);
	((Tsens *)hw)->OFFSET.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_OFFSET_OFFSETC_bf(const void *const hw, hri_tsens_offset_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->OFFSET.reg &= ~TSENS_OFFSET_OFFSETC(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_OFFSET_OFFSETC_bf(const void *const hw, hri_tsens_offset_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->OFFSET.reg ^= TSENS_OFFSET_OFFSETC(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_offset_reg_t hri_tsens_read_OFFSET_OFFSETC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->OFFSET.reg;
	tmp = (tmp & TSENS_OFFSET_OFFSETC_Msk) >> TSENS_OFFSET_OFFSETC_Pos;
	return tmp;
}

static inline void hri_tsens_set_OFFSET_reg(const void *const hw, hri_tsens_offset_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->OFFSET.reg |= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_offset_reg_t hri_tsens_get_OFFSET_reg(const void *const hw, hri_tsens_offset_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->OFFSET.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tsens_write_OFFSET_reg(const void *const hw, hri_tsens_offset_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->OFFSET.reg = data;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_OFFSET_reg(const void *const hw, hri_tsens_offset_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->OFFSET.reg &= ~mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_OFFSET_reg(const void *const hw, hri_tsens_offset_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->OFFSET.reg ^= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_offset_reg_t hri_tsens_read_OFFSET_reg(const void *const hw)
{
	return ((Tsens *)hw)->OFFSET.reg;
}

static inline void hri_tsens_set_CAL_FCAL_bf(const void *const hw, hri_tsens_cal_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg |= TSENS_CAL_FCAL(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_cal_reg_t hri_tsens_get_CAL_FCAL_bf(const void *const hw, hri_tsens_cal_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->CAL.reg;
	tmp = (tmp & TSENS_CAL_FCAL(mask)) >> TSENS_CAL_FCAL_Pos;
	return tmp;
}

static inline void hri_tsens_write_CAL_FCAL_bf(const void *const hw, hri_tsens_cal_reg_t data)
{
	uint32_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->CAL.reg;
	tmp &= ~TSENS_CAL_FCAL_Msk;
	tmp |= TSENS_CAL_FCAL(data);
	((Tsens *)hw)->CAL.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_CAL_FCAL_bf(const void *const hw, hri_tsens_cal_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg &= ~TSENS_CAL_FCAL(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_CAL_FCAL_bf(const void *const hw, hri_tsens_cal_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg ^= TSENS_CAL_FCAL(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_cal_reg_t hri_tsens_read_CAL_FCAL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->CAL.reg;
	tmp = (tmp & TSENS_CAL_FCAL_Msk) >> TSENS_CAL_FCAL_Pos;
	return tmp;
}

static inline void hri_tsens_set_CAL_TCAL_bf(const void *const hw, hri_tsens_cal_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg |= TSENS_CAL_TCAL(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_cal_reg_t hri_tsens_get_CAL_TCAL_bf(const void *const hw, hri_tsens_cal_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->CAL.reg;
	tmp = (tmp & TSENS_CAL_TCAL(mask)) >> TSENS_CAL_TCAL_Pos;
	return tmp;
}

static inline void hri_tsens_write_CAL_TCAL_bf(const void *const hw, hri_tsens_cal_reg_t data)
{
	uint32_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->CAL.reg;
	tmp &= ~TSENS_CAL_TCAL_Msk;
	tmp |= TSENS_CAL_TCAL(data);
	((Tsens *)hw)->CAL.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_CAL_TCAL_bf(const void *const hw, hri_tsens_cal_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg &= ~TSENS_CAL_TCAL(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_CAL_TCAL_bf(const void *const hw, hri_tsens_cal_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg ^= TSENS_CAL_TCAL(mask);
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_cal_reg_t hri_tsens_read_CAL_TCAL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->CAL.reg;
	tmp = (tmp & TSENS_CAL_TCAL_Msk) >> TSENS_CAL_TCAL_Pos;
	return tmp;
}

static inline void hri_tsens_set_CAL_reg(const void *const hw, hri_tsens_cal_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg |= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_cal_reg_t hri_tsens_get_CAL_reg(const void *const hw, hri_tsens_cal_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tsens *)hw)->CAL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tsens_write_CAL_reg(const void *const hw, hri_tsens_cal_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg = data;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_CAL_reg(const void *const hw, hri_tsens_cal_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg &= ~mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_CAL_reg(const void *const hw, hri_tsens_cal_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CAL.reg ^= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_cal_reg_t hri_tsens_read_CAL_reg(const void *const hw)
{
	return ((Tsens *)hw)->CAL.reg;
}

static inline void hri_tsens_set_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->DBGCTRL.reg |= TSENS_DBGCTRL_DBGRUN;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tsens_get_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->DBGCTRL.reg;
	tmp = (tmp & TSENS_DBGCTRL_DBGRUN) >> TSENS_DBGCTRL_DBGRUN_Pos;
	return (bool)tmp;
}

static inline void hri_tsens_write_DBGCTRL_DBGRUN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TSENS_CRITICAL_SECTION_ENTER();
	tmp = ((Tsens *)hw)->DBGCTRL.reg;
	tmp &= ~TSENS_DBGCTRL_DBGRUN;
	tmp |= value << TSENS_DBGCTRL_DBGRUN_Pos;
	((Tsens *)hw)->DBGCTRL.reg = tmp;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->DBGCTRL.reg &= ~TSENS_DBGCTRL_DBGRUN;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->DBGCTRL.reg ^= TSENS_DBGCTRL_DBGRUN;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_set_DBGCTRL_reg(const void *const hw, hri_tsens_dbgctrl_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->DBGCTRL.reg |= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_dbgctrl_reg_t hri_tsens_get_DBGCTRL_reg(const void *const hw, hri_tsens_dbgctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tsens *)hw)->DBGCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tsens_write_DBGCTRL_reg(const void *const hw, hri_tsens_dbgctrl_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->DBGCTRL.reg = data;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_clear_DBGCTRL_reg(const void *const hw, hri_tsens_dbgctrl_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->DBGCTRL.reg &= ~mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tsens_toggle_DBGCTRL_reg(const void *const hw, hri_tsens_dbgctrl_reg_t mask)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->DBGCTRL.reg ^= mask;
	TSENS_CRITICAL_SECTION_LEAVE();
}

static inline hri_tsens_dbgctrl_reg_t hri_tsens_read_DBGCTRL_reg(const void *const hw)
{
	return ((Tsens *)hw)->DBGCTRL.reg;
}

static inline void hri_tsens_write_CTRLB_reg(const void *const hw, hri_tsens_ctrlb_reg_t data)
{
	TSENS_CRITICAL_SECTION_ENTER();
	((Tsens *)hw)->CTRLB.reg = data;
	TSENS_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_TSENS_C21_H_INCLUDED */
#endif /* _SAMC21_TSENS_COMPONENT_ */
