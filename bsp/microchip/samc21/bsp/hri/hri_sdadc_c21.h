/**
 * \file
 *
 * \brief SAM SDADC
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

#ifdef _SAMC21_SDADC_COMPONENT_
#ifndef _HRI_SDADC_C21_H_INCLUDED_
#define _HRI_SDADC_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_SDADC_CRITICAL_SECTIONS)
#define SDADC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define SDADC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define SDADC_CRITICAL_SECTION_ENTER()
#define SDADC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint16_t hri_sdadc_ctrlb_reg_t;
typedef uint16_t hri_sdadc_gaincorr_reg_t;
typedef uint32_t hri_sdadc_offsetcorr_reg_t;
typedef uint32_t hri_sdadc_result_reg_t;
typedef uint32_t hri_sdadc_syncbusy_reg_t;
typedef uint32_t hri_sdadc_winlt_reg_t;
typedef uint32_t hri_sdadc_winut_reg_t;
typedef uint8_t  hri_sdadc_anactrl_reg_t;
typedef uint8_t  hri_sdadc_ctrla_reg_t;
typedef uint8_t  hri_sdadc_ctrlc_reg_t;
typedef uint8_t  hri_sdadc_dbgctrl_reg_t;
typedef uint8_t  hri_sdadc_evctrl_reg_t;
typedef uint8_t  hri_sdadc_inputctrl_reg_t;
typedef uint8_t  hri_sdadc_intenset_reg_t;
typedef uint8_t  hri_sdadc_intflag_reg_t;
typedef uint8_t  hri_sdadc_refctrl_reg_t;
typedef uint8_t  hri_sdadc_seqctrl_reg_t;
typedef uint8_t  hri_sdadc_seqstatus_reg_t;
typedef uint8_t  hri_sdadc_shiftcorr_reg_t;
typedef uint8_t  hri_sdadc_swtrig_reg_t;
typedef uint8_t  hri_sdadc_winctrl_reg_t;

static inline void hri_sdadc_wait_for_sync(const void *const hw, hri_sdadc_syncbusy_reg_t reg)
{
	while (((Sdadc *)hw)->SYNCBUSY.reg & reg) {
	};
}

static inline bool hri_sdadc_is_syncing(const void *const hw, hri_sdadc_syncbusy_reg_t reg)
{
	return ((Sdadc *)hw)->SYNCBUSY.reg & reg;
}

static inline bool hri_sdadc_get_INTFLAG_RESRDY_bit(const void *const hw)
{
	return (((Sdadc *)hw)->INTFLAG.reg & SDADC_INTFLAG_RESRDY) >> SDADC_INTFLAG_RESRDY_Pos;
}

static inline void hri_sdadc_clear_INTFLAG_RESRDY_bit(const void *const hw)
{
	((Sdadc *)hw)->INTFLAG.reg = SDADC_INTFLAG_RESRDY;
}

static inline bool hri_sdadc_get_INTFLAG_OVERRUN_bit(const void *const hw)
{
	return (((Sdadc *)hw)->INTFLAG.reg & SDADC_INTFLAG_OVERRUN) >> SDADC_INTFLAG_OVERRUN_Pos;
}

static inline void hri_sdadc_clear_INTFLAG_OVERRUN_bit(const void *const hw)
{
	((Sdadc *)hw)->INTFLAG.reg = SDADC_INTFLAG_OVERRUN;
}

static inline bool hri_sdadc_get_INTFLAG_WINMON_bit(const void *const hw)
{
	return (((Sdadc *)hw)->INTFLAG.reg & SDADC_INTFLAG_WINMON) >> SDADC_INTFLAG_WINMON_Pos;
}

static inline void hri_sdadc_clear_INTFLAG_WINMON_bit(const void *const hw)
{
	((Sdadc *)hw)->INTFLAG.reg = SDADC_INTFLAG_WINMON;
}

static inline bool hri_sdadc_get_interrupt_RESRDY_bit(const void *const hw)
{
	return (((Sdadc *)hw)->INTFLAG.reg & SDADC_INTFLAG_RESRDY) >> SDADC_INTFLAG_RESRDY_Pos;
}

static inline void hri_sdadc_clear_interrupt_RESRDY_bit(const void *const hw)
{
	((Sdadc *)hw)->INTFLAG.reg = SDADC_INTFLAG_RESRDY;
}

static inline bool hri_sdadc_get_interrupt_OVERRUN_bit(const void *const hw)
{
	return (((Sdadc *)hw)->INTFLAG.reg & SDADC_INTFLAG_OVERRUN) >> SDADC_INTFLAG_OVERRUN_Pos;
}

static inline void hri_sdadc_clear_interrupt_OVERRUN_bit(const void *const hw)
{
	((Sdadc *)hw)->INTFLAG.reg = SDADC_INTFLAG_OVERRUN;
}

static inline bool hri_sdadc_get_interrupt_WINMON_bit(const void *const hw)
{
	return (((Sdadc *)hw)->INTFLAG.reg & SDADC_INTFLAG_WINMON) >> SDADC_INTFLAG_WINMON_Pos;
}

static inline void hri_sdadc_clear_interrupt_WINMON_bit(const void *const hw)
{
	((Sdadc *)hw)->INTFLAG.reg = SDADC_INTFLAG_WINMON;
}

static inline hri_sdadc_intflag_reg_t hri_sdadc_get_INTFLAG_reg(const void *const hw, hri_sdadc_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_sdadc_intflag_reg_t hri_sdadc_read_INTFLAG_reg(const void *const hw)
{
	return ((Sdadc *)hw)->INTFLAG.reg;
}

static inline void hri_sdadc_clear_INTFLAG_reg(const void *const hw, hri_sdadc_intflag_reg_t mask)
{
	((Sdadc *)hw)->INTFLAG.reg = mask;
}

static inline void hri_sdadc_set_INTEN_RESRDY_bit(const void *const hw)
{
	((Sdadc *)hw)->INTENSET.reg = SDADC_INTENSET_RESRDY;
}

static inline bool hri_sdadc_get_INTEN_RESRDY_bit(const void *const hw)
{
	return (((Sdadc *)hw)->INTENSET.reg & SDADC_INTENSET_RESRDY) >> SDADC_INTENSET_RESRDY_Pos;
}

static inline void hri_sdadc_write_INTEN_RESRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Sdadc *)hw)->INTENCLR.reg = SDADC_INTENSET_RESRDY;
	} else {
		((Sdadc *)hw)->INTENSET.reg = SDADC_INTENSET_RESRDY;
	}
}

static inline void hri_sdadc_clear_INTEN_RESRDY_bit(const void *const hw)
{
	((Sdadc *)hw)->INTENCLR.reg = SDADC_INTENSET_RESRDY;
}

static inline void hri_sdadc_set_INTEN_OVERRUN_bit(const void *const hw)
{
	((Sdadc *)hw)->INTENSET.reg = SDADC_INTENSET_OVERRUN;
}

static inline bool hri_sdadc_get_INTEN_OVERRUN_bit(const void *const hw)
{
	return (((Sdadc *)hw)->INTENSET.reg & SDADC_INTENSET_OVERRUN) >> SDADC_INTENSET_OVERRUN_Pos;
}

static inline void hri_sdadc_write_INTEN_OVERRUN_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Sdadc *)hw)->INTENCLR.reg = SDADC_INTENSET_OVERRUN;
	} else {
		((Sdadc *)hw)->INTENSET.reg = SDADC_INTENSET_OVERRUN;
	}
}

static inline void hri_sdadc_clear_INTEN_OVERRUN_bit(const void *const hw)
{
	((Sdadc *)hw)->INTENCLR.reg = SDADC_INTENSET_OVERRUN;
}

static inline void hri_sdadc_set_INTEN_WINMON_bit(const void *const hw)
{
	((Sdadc *)hw)->INTENSET.reg = SDADC_INTENSET_WINMON;
}

static inline bool hri_sdadc_get_INTEN_WINMON_bit(const void *const hw)
{
	return (((Sdadc *)hw)->INTENSET.reg & SDADC_INTENSET_WINMON) >> SDADC_INTENSET_WINMON_Pos;
}

static inline void hri_sdadc_write_INTEN_WINMON_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Sdadc *)hw)->INTENCLR.reg = SDADC_INTENSET_WINMON;
	} else {
		((Sdadc *)hw)->INTENSET.reg = SDADC_INTENSET_WINMON;
	}
}

static inline void hri_sdadc_clear_INTEN_WINMON_bit(const void *const hw)
{
	((Sdadc *)hw)->INTENCLR.reg = SDADC_INTENSET_WINMON;
}

static inline void hri_sdadc_set_INTEN_reg(const void *const hw, hri_sdadc_intenset_reg_t mask)
{
	((Sdadc *)hw)->INTENSET.reg = mask;
}

static inline hri_sdadc_intenset_reg_t hri_sdadc_get_INTEN_reg(const void *const hw, hri_sdadc_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_sdadc_intenset_reg_t hri_sdadc_read_INTEN_reg(const void *const hw)
{
	return ((Sdadc *)hw)->INTENSET.reg;
}

static inline void hri_sdadc_write_INTEN_reg(const void *const hw, hri_sdadc_intenset_reg_t data)
{
	((Sdadc *)hw)->INTENSET.reg = data;
	((Sdadc *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_sdadc_clear_INTEN_reg(const void *const hw, hri_sdadc_intenset_reg_t mask)
{
	((Sdadc *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_sdadc_get_SEQSTATUS_SEQBUSY_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SEQSTATUS.reg & SDADC_SEQSTATUS_SEQBUSY) >> SDADC_SEQSTATUS_SEQBUSY_Pos;
}

static inline hri_sdadc_seqstatus_reg_t hri_sdadc_get_SEQSTATUS_SEQSTATE_bf(const void *const         hw,
                                                                            hri_sdadc_seqstatus_reg_t mask)
{
	return (((Sdadc *)hw)->SEQSTATUS.reg & SDADC_SEQSTATUS_SEQSTATE(mask)) >> SDADC_SEQSTATUS_SEQSTATE_Pos;
}

static inline hri_sdadc_seqstatus_reg_t hri_sdadc_read_SEQSTATUS_SEQSTATE_bf(const void *const hw)
{
	return (((Sdadc *)hw)->SEQSTATUS.reg & SDADC_SEQSTATUS_SEQSTATE_Msk) >> SDADC_SEQSTATUS_SEQSTATE_Pos;
}

static inline hri_sdadc_seqstatus_reg_t hri_sdadc_get_SEQSTATUS_reg(const void *const         hw,
                                                                    hri_sdadc_seqstatus_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->SEQSTATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_sdadc_seqstatus_reg_t hri_sdadc_read_SEQSTATUS_reg(const void *const hw)
{
	return ((Sdadc *)hw)->SEQSTATUS.reg;
}

static inline bool hri_sdadc_get_SYNCBUSY_SWRST_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_SWRST) >> SDADC_SYNCBUSY_SWRST_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_ENABLE) >> SDADC_SYNCBUSY_ENABLE_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_CTRLC_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_CTRLC) >> SDADC_SYNCBUSY_CTRLC_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_INPUTCTRL_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_INPUTCTRL) >> SDADC_SYNCBUSY_INPUTCTRL_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_WINCTRL_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_WINCTRL) >> SDADC_SYNCBUSY_WINCTRL_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_WINLT_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_WINLT) >> SDADC_SYNCBUSY_WINLT_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_WINUT_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_WINUT) >> SDADC_SYNCBUSY_WINUT_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_OFFSETCORR_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_OFFSETCORR) >> SDADC_SYNCBUSY_OFFSETCORR_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_GAINCORR_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_GAINCORR) >> SDADC_SYNCBUSY_GAINCORR_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_SHIFTCORR_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_SHIFTCORR) >> SDADC_SYNCBUSY_SHIFTCORR_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_SWTRIG_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_SWTRIG) >> SDADC_SYNCBUSY_SWTRIG_Pos;
}

static inline bool hri_sdadc_get_SYNCBUSY_ANACTRL_bit(const void *const hw)
{
	return (((Sdadc *)hw)->SYNCBUSY.reg & SDADC_SYNCBUSY_ANACTRL) >> SDADC_SYNCBUSY_ANACTRL_Pos;
}

static inline hri_sdadc_syncbusy_reg_t hri_sdadc_get_SYNCBUSY_reg(const void *const hw, hri_sdadc_syncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdadc *)hw)->SYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_sdadc_syncbusy_reg_t hri_sdadc_read_SYNCBUSY_reg(const void *const hw)
{
	return ((Sdadc *)hw)->SYNCBUSY.reg;
}

static inline hri_sdadc_result_reg_t hri_sdadc_get_RESULT_RESULT_bf(const void *const hw, hri_sdadc_result_reg_t mask)
{
	return (((Sdadc *)hw)->RESULT.reg & SDADC_RESULT_RESULT(mask)) >> SDADC_RESULT_RESULT_Pos;
}

static inline hri_sdadc_result_reg_t hri_sdadc_read_RESULT_RESULT_bf(const void *const hw)
{
	return (((Sdadc *)hw)->RESULT.reg & SDADC_RESULT_RESULT_Msk) >> SDADC_RESULT_RESULT_Pos;
}

static inline hri_sdadc_result_reg_t hri_sdadc_get_RESULT_RESERVED_bf(const void *const hw, hri_sdadc_result_reg_t mask)
{
	return (((Sdadc *)hw)->RESULT.reg & SDADC_RESULT_RESERVED(mask)) >> SDADC_RESULT_RESERVED_Pos;
}

static inline hri_sdadc_result_reg_t hri_sdadc_read_RESULT_RESERVED_bf(const void *const hw)
{
	return (((Sdadc *)hw)->RESULT.reg & SDADC_RESULT_RESERVED_Msk) >> SDADC_RESULT_RESERVED_Pos;
}

static inline hri_sdadc_result_reg_t hri_sdadc_get_RESULT_reg(const void *const hw, hri_sdadc_result_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Sdadc *)hw)->RESULT.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_sdadc_result_reg_t hri_sdadc_read_RESULT_reg(const void *const hw)
{
	return ((Sdadc *)hw)->RESULT.reg;
}

static inline void hri_sdadc_set_CTRLA_SWRST_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg |= SDADC_CTRLA_SWRST;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST);
	tmp = ((Sdadc *)hw)->CTRLA.reg;
	tmp = (tmp & SDADC_CTRLA_SWRST) >> SDADC_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_set_CTRLA_ENABLE_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg |= SDADC_CTRLA_ENABLE;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	tmp = ((Sdadc *)hw)->CTRLA.reg;
	tmp = (tmp & SDADC_CTRLA_ENABLE) >> SDADC_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->CTRLA.reg;
	tmp &= ~SDADC_CTRLA_ENABLE;
	tmp |= value << SDADC_CTRLA_ENABLE_Pos;
	((Sdadc *)hw)->CTRLA.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg &= ~SDADC_CTRLA_ENABLE;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg ^= SDADC_CTRLA_ENABLE;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg |= SDADC_CTRLA_RUNSTDBY;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->CTRLA.reg;
	tmp = (tmp & SDADC_CTRLA_RUNSTDBY) >> SDADC_CTRLA_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_CTRLA_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->CTRLA.reg;
	tmp &= ~SDADC_CTRLA_RUNSTDBY;
	tmp |= value << SDADC_CTRLA_RUNSTDBY_Pos;
	((Sdadc *)hw)->CTRLA.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg &= ~SDADC_CTRLA_RUNSTDBY;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg ^= SDADC_CTRLA_RUNSTDBY;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_CTRLA_ONDEMAND_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg |= SDADC_CTRLA_ONDEMAND;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_CTRLA_ONDEMAND_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->CTRLA.reg;
	tmp = (tmp & SDADC_CTRLA_ONDEMAND) >> SDADC_CTRLA_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_CTRLA_ONDEMAND_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->CTRLA.reg;
	tmp &= ~SDADC_CTRLA_ONDEMAND;
	tmp |= value << SDADC_CTRLA_ONDEMAND_Pos;
	((Sdadc *)hw)->CTRLA.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLA_ONDEMAND_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg &= ~SDADC_CTRLA_ONDEMAND;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLA_ONDEMAND_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg ^= SDADC_CTRLA_ONDEMAND;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_CTRLA_reg(const void *const hw, hri_sdadc_ctrla_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrla_reg_t hri_sdadc_get_CTRLA_reg(const void *const hw, hri_sdadc_ctrla_reg_t mask)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	tmp = ((Sdadc *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_CTRLA_reg(const void *const hw, hri_sdadc_ctrla_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLA_reg(const void *const hw, hri_sdadc_ctrla_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLA_reg(const void *const hw, hri_sdadc_ctrla_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLA.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrla_reg_t hri_sdadc_read_CTRLA_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SWRST | SDADC_SYNCBUSY_ENABLE);
	return ((Sdadc *)hw)->CTRLA.reg;
}

static inline void hri_sdadc_set_REFCTRL_ONREFBUF_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg |= SDADC_REFCTRL_ONREFBUF;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_REFCTRL_ONREFBUF_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->REFCTRL.reg;
	tmp = (tmp & SDADC_REFCTRL_ONREFBUF) >> SDADC_REFCTRL_ONREFBUF_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_REFCTRL_ONREFBUF_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->REFCTRL.reg;
	tmp &= ~SDADC_REFCTRL_ONREFBUF;
	tmp |= value << SDADC_REFCTRL_ONREFBUF_Pos;
	((Sdadc *)hw)->REFCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_REFCTRL_ONREFBUF_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg &= ~SDADC_REFCTRL_ONREFBUF;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_REFCTRL_ONREFBUF_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg ^= SDADC_REFCTRL_ONREFBUF;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_REFCTRL_REFSEL_bf(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg |= SDADC_REFCTRL_REFSEL(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_refctrl_reg_t hri_sdadc_get_REFCTRL_REFSEL_bf(const void *const       hw,
                                                                      hri_sdadc_refctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->REFCTRL.reg;
	tmp = (tmp & SDADC_REFCTRL_REFSEL(mask)) >> SDADC_REFCTRL_REFSEL_Pos;
	return tmp;
}

static inline void hri_sdadc_write_REFCTRL_REFSEL_bf(const void *const hw, hri_sdadc_refctrl_reg_t data)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->REFCTRL.reg;
	tmp &= ~SDADC_REFCTRL_REFSEL_Msk;
	tmp |= SDADC_REFCTRL_REFSEL(data);
	((Sdadc *)hw)->REFCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_REFCTRL_REFSEL_bf(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg &= ~SDADC_REFCTRL_REFSEL(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_REFCTRL_REFSEL_bf(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg ^= SDADC_REFCTRL_REFSEL(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_refctrl_reg_t hri_sdadc_read_REFCTRL_REFSEL_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->REFCTRL.reg;
	tmp = (tmp & SDADC_REFCTRL_REFSEL_Msk) >> SDADC_REFCTRL_REFSEL_Pos;
	return tmp;
}

static inline void hri_sdadc_set_REFCTRL_REFRANGE_bf(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg |= SDADC_REFCTRL_REFRANGE(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_refctrl_reg_t hri_sdadc_get_REFCTRL_REFRANGE_bf(const void *const       hw,
                                                                        hri_sdadc_refctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->REFCTRL.reg;
	tmp = (tmp & SDADC_REFCTRL_REFRANGE(mask)) >> SDADC_REFCTRL_REFRANGE_Pos;
	return tmp;
}

static inline void hri_sdadc_write_REFCTRL_REFRANGE_bf(const void *const hw, hri_sdadc_refctrl_reg_t data)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->REFCTRL.reg;
	tmp &= ~SDADC_REFCTRL_REFRANGE_Msk;
	tmp |= SDADC_REFCTRL_REFRANGE(data);
	((Sdadc *)hw)->REFCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_REFCTRL_REFRANGE_bf(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg &= ~SDADC_REFCTRL_REFRANGE(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_REFCTRL_REFRANGE_bf(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg ^= SDADC_REFCTRL_REFRANGE(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_refctrl_reg_t hri_sdadc_read_REFCTRL_REFRANGE_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->REFCTRL.reg;
	tmp = (tmp & SDADC_REFCTRL_REFRANGE_Msk) >> SDADC_REFCTRL_REFRANGE_Pos;
	return tmp;
}

static inline void hri_sdadc_set_REFCTRL_reg(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg |= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_refctrl_reg_t hri_sdadc_get_REFCTRL_reg(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->REFCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_REFCTRL_reg(const void *const hw, hri_sdadc_refctrl_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg = data;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_REFCTRL_reg(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg &= ~mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_REFCTRL_reg(const void *const hw, hri_sdadc_refctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->REFCTRL.reg ^= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_refctrl_reg_t hri_sdadc_read_REFCTRL_reg(const void *const hw)
{
	return ((Sdadc *)hw)->REFCTRL.reg;
}

static inline void hri_sdadc_set_CTRLB_PRESCALER_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg |= SDADC_CTRLB_PRESCALER(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlb_reg_t hri_sdadc_get_CTRLB_PRESCALER_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp = (tmp & SDADC_CTRLB_PRESCALER(mask)) >> SDADC_CTRLB_PRESCALER_Pos;
	return tmp;
}

static inline void hri_sdadc_write_CTRLB_PRESCALER_bf(const void *const hw, hri_sdadc_ctrlb_reg_t data)
{
	uint16_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp &= ~SDADC_CTRLB_PRESCALER_Msk;
	tmp |= SDADC_CTRLB_PRESCALER(data);
	((Sdadc *)hw)->CTRLB.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLB_PRESCALER_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg &= ~SDADC_CTRLB_PRESCALER(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLB_PRESCALER_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg ^= SDADC_CTRLB_PRESCALER(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlb_reg_t hri_sdadc_read_CTRLB_PRESCALER_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp = (tmp & SDADC_CTRLB_PRESCALER_Msk) >> SDADC_CTRLB_PRESCALER_Pos;
	return tmp;
}

static inline void hri_sdadc_set_CTRLB_OSR_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg |= SDADC_CTRLB_OSR(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlb_reg_t hri_sdadc_get_CTRLB_OSR_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp = (tmp & SDADC_CTRLB_OSR(mask)) >> SDADC_CTRLB_OSR_Pos;
	return tmp;
}

static inline void hri_sdadc_write_CTRLB_OSR_bf(const void *const hw, hri_sdadc_ctrlb_reg_t data)
{
	uint16_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp &= ~SDADC_CTRLB_OSR_Msk;
	tmp |= SDADC_CTRLB_OSR(data);
	((Sdadc *)hw)->CTRLB.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLB_OSR_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg &= ~SDADC_CTRLB_OSR(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLB_OSR_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg ^= SDADC_CTRLB_OSR(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlb_reg_t hri_sdadc_read_CTRLB_OSR_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp = (tmp & SDADC_CTRLB_OSR_Msk) >> SDADC_CTRLB_OSR_Pos;
	return tmp;
}

static inline void hri_sdadc_set_CTRLB_SKPCNT_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg |= SDADC_CTRLB_SKPCNT(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlb_reg_t hri_sdadc_get_CTRLB_SKPCNT_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp = (tmp & SDADC_CTRLB_SKPCNT(mask)) >> SDADC_CTRLB_SKPCNT_Pos;
	return tmp;
}

static inline void hri_sdadc_write_CTRLB_SKPCNT_bf(const void *const hw, hri_sdadc_ctrlb_reg_t data)
{
	uint16_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp &= ~SDADC_CTRLB_SKPCNT_Msk;
	tmp |= SDADC_CTRLB_SKPCNT(data);
	((Sdadc *)hw)->CTRLB.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLB_SKPCNT_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg &= ~SDADC_CTRLB_SKPCNT(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLB_SKPCNT_bf(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg ^= SDADC_CTRLB_SKPCNT(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlb_reg_t hri_sdadc_read_CTRLB_SKPCNT_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp = (tmp & SDADC_CTRLB_SKPCNT_Msk) >> SDADC_CTRLB_SKPCNT_Pos;
	return tmp;
}

static inline void hri_sdadc_set_CTRLB_reg(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg |= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlb_reg_t hri_sdadc_get_CTRLB_reg(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Sdadc *)hw)->CTRLB.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_CTRLB_reg(const void *const hw, hri_sdadc_ctrlb_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg = data;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLB_reg(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg &= ~mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLB_reg(const void *const hw, hri_sdadc_ctrlb_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLB.reg ^= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlb_reg_t hri_sdadc_read_CTRLB_reg(const void *const hw)
{
	return ((Sdadc *)hw)->CTRLB.reg;
}

static inline void hri_sdadc_set_EVCTRL_FLUSHEI_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg |= SDADC_EVCTRL_FLUSHEI;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_EVCTRL_FLUSHEI_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp = (tmp & SDADC_EVCTRL_FLUSHEI) >> SDADC_EVCTRL_FLUSHEI_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_EVCTRL_FLUSHEI_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp &= ~SDADC_EVCTRL_FLUSHEI;
	tmp |= value << SDADC_EVCTRL_FLUSHEI_Pos;
	((Sdadc *)hw)->EVCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_EVCTRL_FLUSHEI_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg &= ~SDADC_EVCTRL_FLUSHEI;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_EVCTRL_FLUSHEI_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg ^= SDADC_EVCTRL_FLUSHEI;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_EVCTRL_STARTEI_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg |= SDADC_EVCTRL_STARTEI;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_EVCTRL_STARTEI_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp = (tmp & SDADC_EVCTRL_STARTEI) >> SDADC_EVCTRL_STARTEI_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_EVCTRL_STARTEI_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp &= ~SDADC_EVCTRL_STARTEI;
	tmp |= value << SDADC_EVCTRL_STARTEI_Pos;
	((Sdadc *)hw)->EVCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_EVCTRL_STARTEI_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg &= ~SDADC_EVCTRL_STARTEI;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_EVCTRL_STARTEI_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg ^= SDADC_EVCTRL_STARTEI;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_EVCTRL_FLUSHINV_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg |= SDADC_EVCTRL_FLUSHINV;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_EVCTRL_FLUSHINV_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp = (tmp & SDADC_EVCTRL_FLUSHINV) >> SDADC_EVCTRL_FLUSHINV_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_EVCTRL_FLUSHINV_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp &= ~SDADC_EVCTRL_FLUSHINV;
	tmp |= value << SDADC_EVCTRL_FLUSHINV_Pos;
	((Sdadc *)hw)->EVCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_EVCTRL_FLUSHINV_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg &= ~SDADC_EVCTRL_FLUSHINV;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_EVCTRL_FLUSHINV_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg ^= SDADC_EVCTRL_FLUSHINV;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_EVCTRL_STARTINV_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg |= SDADC_EVCTRL_STARTINV;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_EVCTRL_STARTINV_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp = (tmp & SDADC_EVCTRL_STARTINV) >> SDADC_EVCTRL_STARTINV_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_EVCTRL_STARTINV_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp &= ~SDADC_EVCTRL_STARTINV;
	tmp |= value << SDADC_EVCTRL_STARTINV_Pos;
	((Sdadc *)hw)->EVCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_EVCTRL_STARTINV_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg &= ~SDADC_EVCTRL_STARTINV;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_EVCTRL_STARTINV_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg ^= SDADC_EVCTRL_STARTINV;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_EVCTRL_RESRDYEO_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg |= SDADC_EVCTRL_RESRDYEO;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_EVCTRL_RESRDYEO_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp = (tmp & SDADC_EVCTRL_RESRDYEO) >> SDADC_EVCTRL_RESRDYEO_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_EVCTRL_RESRDYEO_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp &= ~SDADC_EVCTRL_RESRDYEO;
	tmp |= value << SDADC_EVCTRL_RESRDYEO_Pos;
	((Sdadc *)hw)->EVCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_EVCTRL_RESRDYEO_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg &= ~SDADC_EVCTRL_RESRDYEO;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_EVCTRL_RESRDYEO_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg ^= SDADC_EVCTRL_RESRDYEO;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_EVCTRL_WINMONEO_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg |= SDADC_EVCTRL_WINMONEO;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_EVCTRL_WINMONEO_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp = (tmp & SDADC_EVCTRL_WINMONEO) >> SDADC_EVCTRL_WINMONEO_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_EVCTRL_WINMONEO_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp &= ~SDADC_EVCTRL_WINMONEO;
	tmp |= value << SDADC_EVCTRL_WINMONEO_Pos;
	((Sdadc *)hw)->EVCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_EVCTRL_WINMONEO_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg &= ~SDADC_EVCTRL_WINMONEO;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_EVCTRL_WINMONEO_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg ^= SDADC_EVCTRL_WINMONEO;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_EVCTRL_reg(const void *const hw, hri_sdadc_evctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg |= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_evctrl_reg_t hri_sdadc_get_EVCTRL_reg(const void *const hw, hri_sdadc_evctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_EVCTRL_reg(const void *const hw, hri_sdadc_evctrl_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg = data;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_EVCTRL_reg(const void *const hw, hri_sdadc_evctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg &= ~mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_EVCTRL_reg(const void *const hw, hri_sdadc_evctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->EVCTRL.reg ^= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_evctrl_reg_t hri_sdadc_read_EVCTRL_reg(const void *const hw)
{
	return ((Sdadc *)hw)->EVCTRL.reg;
}

static inline void hri_sdadc_set_INPUTCTRL_MUXSEL_bf(const void *const hw, hri_sdadc_inputctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->INPUTCTRL.reg |= SDADC_INPUTCTRL_MUXSEL(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_inputctrl_reg_t hri_sdadc_get_INPUTCTRL_MUXSEL_bf(const void *const         hw,
                                                                          hri_sdadc_inputctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->INPUTCTRL.reg;
	tmp = (tmp & SDADC_INPUTCTRL_MUXSEL(mask)) >> SDADC_INPUTCTRL_MUXSEL_Pos;
	return tmp;
}

static inline void hri_sdadc_write_INPUTCTRL_MUXSEL_bf(const void *const hw, hri_sdadc_inputctrl_reg_t data)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->INPUTCTRL.reg;
	tmp &= ~SDADC_INPUTCTRL_MUXSEL_Msk;
	tmp |= SDADC_INPUTCTRL_MUXSEL(data);
	((Sdadc *)hw)->INPUTCTRL.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_INPUTCTRL_MUXSEL_bf(const void *const hw, hri_sdadc_inputctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->INPUTCTRL.reg &= ~SDADC_INPUTCTRL_MUXSEL(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_INPUTCTRL_MUXSEL_bf(const void *const hw, hri_sdadc_inputctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->INPUTCTRL.reg ^= SDADC_INPUTCTRL_MUXSEL(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_inputctrl_reg_t hri_sdadc_read_INPUTCTRL_MUXSEL_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->INPUTCTRL.reg;
	tmp = (tmp & SDADC_INPUTCTRL_MUXSEL_Msk) >> SDADC_INPUTCTRL_MUXSEL_Pos;
	return tmp;
}

static inline void hri_sdadc_set_INPUTCTRL_reg(const void *const hw, hri_sdadc_inputctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->INPUTCTRL.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_inputctrl_reg_t hri_sdadc_get_INPUTCTRL_reg(const void *const         hw,
                                                                    hri_sdadc_inputctrl_reg_t mask)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	tmp = ((Sdadc *)hw)->INPUTCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_INPUTCTRL_reg(const void *const hw, hri_sdadc_inputctrl_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->INPUTCTRL.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_INPUTCTRL_reg(const void *const hw, hri_sdadc_inputctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->INPUTCTRL.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_INPUTCTRL_reg(const void *const hw, hri_sdadc_inputctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->INPUTCTRL.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_inputctrl_reg_t hri_sdadc_read_INPUTCTRL_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	return ((Sdadc *)hw)->INPUTCTRL.reg;
}

static inline void hri_sdadc_set_CTRLC_FREERUN_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLC.reg |= SDADC_CTRLC_FREERUN;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_CTRLC_FREERUN_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->CTRLC.reg;
	tmp = (tmp & SDADC_CTRLC_FREERUN) >> SDADC_CTRLC_FREERUN_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_CTRLC_FREERUN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->CTRLC.reg;
	tmp &= ~SDADC_CTRLC_FREERUN;
	tmp |= value << SDADC_CTRLC_FREERUN_Pos;
	((Sdadc *)hw)->CTRLC.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLC_FREERUN_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLC.reg &= ~SDADC_CTRLC_FREERUN;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLC_FREERUN_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLC.reg ^= SDADC_CTRLC_FREERUN;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_CTRLC_reg(const void *const hw, hri_sdadc_ctrlc_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLC.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlc_reg_t hri_sdadc_get_CTRLC_reg(const void *const hw, hri_sdadc_ctrlc_reg_t mask)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	tmp = ((Sdadc *)hw)->CTRLC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_CTRLC_reg(const void *const hw, hri_sdadc_ctrlc_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLC.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_CTRLC_reg(const void *const hw, hri_sdadc_ctrlc_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLC.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_CTRLC_reg(const void *const hw, hri_sdadc_ctrlc_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->CTRLC.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_ctrlc_reg_t hri_sdadc_read_CTRLC_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	return ((Sdadc *)hw)->CTRLC.reg;
}

static inline void hri_sdadc_set_WINCTRL_WINMODE_bf(const void *const hw, hri_sdadc_winctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINCTRL.reg |= SDADC_WINCTRL_WINMODE(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winctrl_reg_t hri_sdadc_get_WINCTRL_WINMODE_bf(const void *const       hw,
                                                                       hri_sdadc_winctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->WINCTRL.reg;
	tmp = (tmp & SDADC_WINCTRL_WINMODE(mask)) >> SDADC_WINCTRL_WINMODE_Pos;
	return tmp;
}

static inline void hri_sdadc_write_WINCTRL_WINMODE_bf(const void *const hw, hri_sdadc_winctrl_reg_t data)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->WINCTRL.reg;
	tmp &= ~SDADC_WINCTRL_WINMODE_Msk;
	tmp |= SDADC_WINCTRL_WINMODE(data);
	((Sdadc *)hw)->WINCTRL.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_WINCTRL_WINMODE_bf(const void *const hw, hri_sdadc_winctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINCTRL.reg &= ~SDADC_WINCTRL_WINMODE(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_WINCTRL_WINMODE_bf(const void *const hw, hri_sdadc_winctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINCTRL.reg ^= SDADC_WINCTRL_WINMODE(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winctrl_reg_t hri_sdadc_read_WINCTRL_WINMODE_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->WINCTRL.reg;
	tmp = (tmp & SDADC_WINCTRL_WINMODE_Msk) >> SDADC_WINCTRL_WINMODE_Pos;
	return tmp;
}

static inline void hri_sdadc_set_WINCTRL_reg(const void *const hw, hri_sdadc_winctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINCTRL.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winctrl_reg_t hri_sdadc_get_WINCTRL_reg(const void *const hw, hri_sdadc_winctrl_reg_t mask)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	tmp = ((Sdadc *)hw)->WINCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_WINCTRL_reg(const void *const hw, hri_sdadc_winctrl_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINCTRL.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_WINCTRL_reg(const void *const hw, hri_sdadc_winctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINCTRL.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_WINCTRL_reg(const void *const hw, hri_sdadc_winctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINCTRL.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winctrl_reg_t hri_sdadc_read_WINCTRL_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	return ((Sdadc *)hw)->WINCTRL.reg;
}

static inline void hri_sdadc_set_WINLT_WINLT_bf(const void *const hw, hri_sdadc_winlt_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINLT.reg |= SDADC_WINLT_WINLT(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winlt_reg_t hri_sdadc_get_WINLT_WINLT_bf(const void *const hw, hri_sdadc_winlt_reg_t mask)
{
	uint32_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	tmp = ((Sdadc *)hw)->WINLT.reg;
	tmp = (tmp & SDADC_WINLT_WINLT(mask)) >> SDADC_WINLT_WINLT_Pos;
	return tmp;
}

static inline void hri_sdadc_write_WINLT_WINLT_bf(const void *const hw, hri_sdadc_winlt_reg_t data)
{
	uint32_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->WINLT.reg;
	tmp &= ~SDADC_WINLT_WINLT_Msk;
	tmp |= SDADC_WINLT_WINLT(data);
	((Sdadc *)hw)->WINLT.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_WINLT_WINLT_bf(const void *const hw, hri_sdadc_winlt_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINLT.reg &= ~SDADC_WINLT_WINLT(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_WINLT_WINLT_bf(const void *const hw, hri_sdadc_winlt_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINLT.reg ^= SDADC_WINLT_WINLT(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winlt_reg_t hri_sdadc_read_WINLT_WINLT_bf(const void *const hw)
{
	uint32_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	tmp = ((Sdadc *)hw)->WINLT.reg;
	tmp = (tmp & SDADC_WINLT_WINLT_Msk) >> SDADC_WINLT_WINLT_Pos;
	return tmp;
}

static inline void hri_sdadc_set_WINLT_reg(const void *const hw, hri_sdadc_winlt_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINLT.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winlt_reg_t hri_sdadc_get_WINLT_reg(const void *const hw, hri_sdadc_winlt_reg_t mask)
{
	uint32_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	tmp = ((Sdadc *)hw)->WINLT.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_WINLT_reg(const void *const hw, hri_sdadc_winlt_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINLT.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_WINLT_reg(const void *const hw, hri_sdadc_winlt_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINLT.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_WINLT_reg(const void *const hw, hri_sdadc_winlt_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINLT.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winlt_reg_t hri_sdadc_read_WINLT_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINLT);
	return ((Sdadc *)hw)->WINLT.reg;
}

static inline void hri_sdadc_set_WINUT_WINUT_bf(const void *const hw, hri_sdadc_winut_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINUT.reg |= SDADC_WINUT_WINUT(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winut_reg_t hri_sdadc_get_WINUT_WINUT_bf(const void *const hw, hri_sdadc_winut_reg_t mask)
{
	uint32_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	tmp = ((Sdadc *)hw)->WINUT.reg;
	tmp = (tmp & SDADC_WINUT_WINUT(mask)) >> SDADC_WINUT_WINUT_Pos;
	return tmp;
}

static inline void hri_sdadc_write_WINUT_WINUT_bf(const void *const hw, hri_sdadc_winut_reg_t data)
{
	uint32_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->WINUT.reg;
	tmp &= ~SDADC_WINUT_WINUT_Msk;
	tmp |= SDADC_WINUT_WINUT(data);
	((Sdadc *)hw)->WINUT.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_WINUT_WINUT_bf(const void *const hw, hri_sdadc_winut_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINUT.reg &= ~SDADC_WINUT_WINUT(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_WINUT_WINUT_bf(const void *const hw, hri_sdadc_winut_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINUT.reg ^= SDADC_WINUT_WINUT(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winut_reg_t hri_sdadc_read_WINUT_WINUT_bf(const void *const hw)
{
	uint32_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	tmp = ((Sdadc *)hw)->WINUT.reg;
	tmp = (tmp & SDADC_WINUT_WINUT_Msk) >> SDADC_WINUT_WINUT_Pos;
	return tmp;
}

static inline void hri_sdadc_set_WINUT_reg(const void *const hw, hri_sdadc_winut_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINUT.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winut_reg_t hri_sdadc_get_WINUT_reg(const void *const hw, hri_sdadc_winut_reg_t mask)
{
	uint32_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	tmp = ((Sdadc *)hw)->WINUT.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_WINUT_reg(const void *const hw, hri_sdadc_winut_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINUT.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_WINUT_reg(const void *const hw, hri_sdadc_winut_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINUT.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_WINUT_reg(const void *const hw, hri_sdadc_winut_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->WINUT.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_winut_reg_t hri_sdadc_read_WINUT_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_WINUT);
	return ((Sdadc *)hw)->WINUT.reg;
}

static inline void hri_sdadc_set_OFFSETCORR_OFFSETCORR_bf(const void *const hw, hri_sdadc_offsetcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->OFFSETCORR.reg |= SDADC_OFFSETCORR_OFFSETCORR(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_offsetcorr_reg_t hri_sdadc_get_OFFSETCORR_OFFSETCORR_bf(const void *const          hw,
                                                                                hri_sdadc_offsetcorr_reg_t mask)
{
	uint32_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	tmp = ((Sdadc *)hw)->OFFSETCORR.reg;
	tmp = (tmp & SDADC_OFFSETCORR_OFFSETCORR(mask)) >> SDADC_OFFSETCORR_OFFSETCORR_Pos;
	return tmp;
}

static inline void hri_sdadc_write_OFFSETCORR_OFFSETCORR_bf(const void *const hw, hri_sdadc_offsetcorr_reg_t data)
{
	uint32_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->OFFSETCORR.reg;
	tmp &= ~SDADC_OFFSETCORR_OFFSETCORR_Msk;
	tmp |= SDADC_OFFSETCORR_OFFSETCORR(data);
	((Sdadc *)hw)->OFFSETCORR.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_OFFSETCORR_OFFSETCORR_bf(const void *const hw, hri_sdadc_offsetcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->OFFSETCORR.reg &= ~SDADC_OFFSETCORR_OFFSETCORR(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_OFFSETCORR_OFFSETCORR_bf(const void *const hw, hri_sdadc_offsetcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->OFFSETCORR.reg ^= SDADC_OFFSETCORR_OFFSETCORR(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_offsetcorr_reg_t hri_sdadc_read_OFFSETCORR_OFFSETCORR_bf(const void *const hw)
{
	uint32_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	tmp = ((Sdadc *)hw)->OFFSETCORR.reg;
	tmp = (tmp & SDADC_OFFSETCORR_OFFSETCORR_Msk) >> SDADC_OFFSETCORR_OFFSETCORR_Pos;
	return tmp;
}

static inline void hri_sdadc_set_OFFSETCORR_reg(const void *const hw, hri_sdadc_offsetcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->OFFSETCORR.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_offsetcorr_reg_t hri_sdadc_get_OFFSETCORR_reg(const void *const          hw,
                                                                      hri_sdadc_offsetcorr_reg_t mask)
{
	uint32_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	tmp = ((Sdadc *)hw)->OFFSETCORR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_OFFSETCORR_reg(const void *const hw, hri_sdadc_offsetcorr_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->OFFSETCORR.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_OFFSETCORR_reg(const void *const hw, hri_sdadc_offsetcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->OFFSETCORR.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_OFFSETCORR_reg(const void *const hw, hri_sdadc_offsetcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->OFFSETCORR.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_offsetcorr_reg_t hri_sdadc_read_OFFSETCORR_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_OFFSETCORR);
	return ((Sdadc *)hw)->OFFSETCORR.reg;
}

static inline void hri_sdadc_set_GAINCORR_GAINCORR_bf(const void *const hw, hri_sdadc_gaincorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->GAINCORR.reg |= SDADC_GAINCORR_GAINCORR(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_gaincorr_reg_t hri_sdadc_get_GAINCORR_GAINCORR_bf(const void *const        hw,
                                                                          hri_sdadc_gaincorr_reg_t mask)
{
	uint16_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	tmp = ((Sdadc *)hw)->GAINCORR.reg;
	tmp = (tmp & SDADC_GAINCORR_GAINCORR(mask)) >> SDADC_GAINCORR_GAINCORR_Pos;
	return tmp;
}

static inline void hri_sdadc_write_GAINCORR_GAINCORR_bf(const void *const hw, hri_sdadc_gaincorr_reg_t data)
{
	uint16_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->GAINCORR.reg;
	tmp &= ~SDADC_GAINCORR_GAINCORR_Msk;
	tmp |= SDADC_GAINCORR_GAINCORR(data);
	((Sdadc *)hw)->GAINCORR.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_GAINCORR_GAINCORR_bf(const void *const hw, hri_sdadc_gaincorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->GAINCORR.reg &= ~SDADC_GAINCORR_GAINCORR(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_GAINCORR_GAINCORR_bf(const void *const hw, hri_sdadc_gaincorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->GAINCORR.reg ^= SDADC_GAINCORR_GAINCORR(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_gaincorr_reg_t hri_sdadc_read_GAINCORR_GAINCORR_bf(const void *const hw)
{
	uint16_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	tmp = ((Sdadc *)hw)->GAINCORR.reg;
	tmp = (tmp & SDADC_GAINCORR_GAINCORR_Msk) >> SDADC_GAINCORR_GAINCORR_Pos;
	return tmp;
}

static inline void hri_sdadc_set_GAINCORR_reg(const void *const hw, hri_sdadc_gaincorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->GAINCORR.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_gaincorr_reg_t hri_sdadc_get_GAINCORR_reg(const void *const hw, hri_sdadc_gaincorr_reg_t mask)
{
	uint16_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	tmp = ((Sdadc *)hw)->GAINCORR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_GAINCORR_reg(const void *const hw, hri_sdadc_gaincorr_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->GAINCORR.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_GAINCORR_reg(const void *const hw, hri_sdadc_gaincorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->GAINCORR.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_GAINCORR_reg(const void *const hw, hri_sdadc_gaincorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->GAINCORR.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_gaincorr_reg_t hri_sdadc_read_GAINCORR_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_GAINCORR);
	return ((Sdadc *)hw)->GAINCORR.reg;
}

static inline void hri_sdadc_set_SHIFTCORR_SHIFTCORR_bf(const void *const hw, hri_sdadc_shiftcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SHIFTCORR.reg |= SDADC_SHIFTCORR_SHIFTCORR(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_shiftcorr_reg_t hri_sdadc_get_SHIFTCORR_SHIFTCORR_bf(const void *const         hw,
                                                                             hri_sdadc_shiftcorr_reg_t mask)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	tmp = ((Sdadc *)hw)->SHIFTCORR.reg;
	tmp = (tmp & SDADC_SHIFTCORR_SHIFTCORR(mask)) >> SDADC_SHIFTCORR_SHIFTCORR_Pos;
	return tmp;
}

static inline void hri_sdadc_write_SHIFTCORR_SHIFTCORR_bf(const void *const hw, hri_sdadc_shiftcorr_reg_t data)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->SHIFTCORR.reg;
	tmp &= ~SDADC_SHIFTCORR_SHIFTCORR_Msk;
	tmp |= SDADC_SHIFTCORR_SHIFTCORR(data);
	((Sdadc *)hw)->SHIFTCORR.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_SHIFTCORR_SHIFTCORR_bf(const void *const hw, hri_sdadc_shiftcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SHIFTCORR.reg &= ~SDADC_SHIFTCORR_SHIFTCORR(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_SHIFTCORR_SHIFTCORR_bf(const void *const hw, hri_sdadc_shiftcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SHIFTCORR.reg ^= SDADC_SHIFTCORR_SHIFTCORR(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_shiftcorr_reg_t hri_sdadc_read_SHIFTCORR_SHIFTCORR_bf(const void *const hw)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	tmp = ((Sdadc *)hw)->SHIFTCORR.reg;
	tmp = (tmp & SDADC_SHIFTCORR_SHIFTCORR_Msk) >> SDADC_SHIFTCORR_SHIFTCORR_Pos;
	return tmp;
}

static inline void hri_sdadc_set_SHIFTCORR_reg(const void *const hw, hri_sdadc_shiftcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SHIFTCORR.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_shiftcorr_reg_t hri_sdadc_get_SHIFTCORR_reg(const void *const         hw,
                                                                    hri_sdadc_shiftcorr_reg_t mask)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	tmp = ((Sdadc *)hw)->SHIFTCORR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_SHIFTCORR_reg(const void *const hw, hri_sdadc_shiftcorr_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SHIFTCORR.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_SHIFTCORR_reg(const void *const hw, hri_sdadc_shiftcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SHIFTCORR.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_SHIFTCORR_reg(const void *const hw, hri_sdadc_shiftcorr_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SHIFTCORR.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_shiftcorr_reg_t hri_sdadc_read_SHIFTCORR_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_SHIFTCORR);
	return ((Sdadc *)hw)->SHIFTCORR.reg;
}

static inline void hri_sdadc_set_SWTRIG_FLUSH_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg |= SDADC_SWTRIG_FLUSH;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_SWTRIG_FLUSH_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->SWTRIG.reg;
	tmp = (tmp & SDADC_SWTRIG_FLUSH) >> SDADC_SWTRIG_FLUSH_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_SWTRIG_FLUSH_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->SWTRIG.reg;
	tmp &= ~SDADC_SWTRIG_FLUSH;
	tmp |= value << SDADC_SWTRIG_FLUSH_Pos;
	((Sdadc *)hw)->SWTRIG.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_SWTRIG_FLUSH_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg &= ~SDADC_SWTRIG_FLUSH;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_SWTRIG_FLUSH_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg ^= SDADC_SWTRIG_FLUSH;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_SWTRIG_START_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg |= SDADC_SWTRIG_START;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_SWTRIG_START_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->SWTRIG.reg;
	tmp = (tmp & SDADC_SWTRIG_START) >> SDADC_SWTRIG_START_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_SWTRIG_START_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->SWTRIG.reg;
	tmp &= ~SDADC_SWTRIG_START;
	tmp |= value << SDADC_SWTRIG_START_Pos;
	((Sdadc *)hw)->SWTRIG.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_SWTRIG_START_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg &= ~SDADC_SWTRIG_START;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_SWTRIG_START_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg ^= SDADC_SWTRIG_START;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_SWTRIG_reg(const void *const hw, hri_sdadc_swtrig_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_swtrig_reg_t hri_sdadc_get_SWTRIG_reg(const void *const hw, hri_sdadc_swtrig_reg_t mask)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	tmp = ((Sdadc *)hw)->SWTRIG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_SWTRIG_reg(const void *const hw, hri_sdadc_swtrig_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_SWTRIG_reg(const void *const hw, hri_sdadc_swtrig_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_SWTRIG_reg(const void *const hw, hri_sdadc_swtrig_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SWTRIG.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_swtrig_reg_t hri_sdadc_read_SWTRIG_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	return ((Sdadc *)hw)->SWTRIG.reg;
}

static inline void hri_sdadc_set_SEQCTRL_SEQEN_bf(const void *const hw, hri_sdadc_seqctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SEQCTRL.reg |= SDADC_SEQCTRL_SEQEN(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_seqctrl_reg_t hri_sdadc_get_SEQCTRL_SEQEN_bf(const void *const hw, hri_sdadc_seqctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->SEQCTRL.reg;
	tmp = (tmp & SDADC_SEQCTRL_SEQEN(mask)) >> SDADC_SEQCTRL_SEQEN_Pos;
	return tmp;
}

static inline void hri_sdadc_write_SEQCTRL_SEQEN_bf(const void *const hw, hri_sdadc_seqctrl_reg_t data)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->SEQCTRL.reg;
	tmp &= ~SDADC_SEQCTRL_SEQEN_Msk;
	tmp |= SDADC_SEQCTRL_SEQEN(data);
	((Sdadc *)hw)->SEQCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_SEQCTRL_SEQEN_bf(const void *const hw, hri_sdadc_seqctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SEQCTRL.reg &= ~SDADC_SEQCTRL_SEQEN(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_SEQCTRL_SEQEN_bf(const void *const hw, hri_sdadc_seqctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SEQCTRL.reg ^= SDADC_SEQCTRL_SEQEN(mask);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_seqctrl_reg_t hri_sdadc_read_SEQCTRL_SEQEN_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->SEQCTRL.reg;
	tmp = (tmp & SDADC_SEQCTRL_SEQEN_Msk) >> SDADC_SEQCTRL_SEQEN_Pos;
	return tmp;
}

static inline void hri_sdadc_set_SEQCTRL_reg(const void *const hw, hri_sdadc_seqctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SEQCTRL.reg |= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_seqctrl_reg_t hri_sdadc_get_SEQCTRL_reg(const void *const hw, hri_sdadc_seqctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->SEQCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_SEQCTRL_reg(const void *const hw, hri_sdadc_seqctrl_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SEQCTRL.reg = data;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_SEQCTRL_reg(const void *const hw, hri_sdadc_seqctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SEQCTRL.reg &= ~mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_SEQCTRL_reg(const void *const hw, hri_sdadc_seqctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->SEQCTRL.reg ^= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_seqctrl_reg_t hri_sdadc_read_SEQCTRL_reg(const void *const hw)
{
	return ((Sdadc *)hw)->SEQCTRL.reg;
}

static inline void hri_sdadc_set_ANACTRL_ONCHOP_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg |= SDADC_ANACTRL_ONCHOP;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_ANACTRL_ONCHOP_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->ANACTRL.reg;
	tmp = (tmp & SDADC_ANACTRL_ONCHOP) >> SDADC_ANACTRL_ONCHOP_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_ANACTRL_ONCHOP_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->ANACTRL.reg;
	tmp &= ~SDADC_ANACTRL_ONCHOP;
	tmp |= value << SDADC_ANACTRL_ONCHOP_Pos;
	((Sdadc *)hw)->ANACTRL.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_ANACTRL_ONCHOP_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg &= ~SDADC_ANACTRL_ONCHOP;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_ANACTRL_ONCHOP_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg ^= SDADC_ANACTRL_ONCHOP;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_ANACTRL_BUFTEST_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg |= SDADC_ANACTRL_BUFTEST;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_ANACTRL_BUFTEST_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->ANACTRL.reg;
	tmp = (tmp & SDADC_ANACTRL_BUFTEST) >> SDADC_ANACTRL_BUFTEST_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_ANACTRL_BUFTEST_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->ANACTRL.reg;
	tmp &= ~SDADC_ANACTRL_BUFTEST;
	tmp |= value << SDADC_ANACTRL_BUFTEST_Pos;
	((Sdadc *)hw)->ANACTRL.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_ANACTRL_BUFTEST_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg &= ~SDADC_ANACTRL_BUFTEST;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_ANACTRL_BUFTEST_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg ^= SDADC_ANACTRL_BUFTEST;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_ANACTRL_CTRSDADC_bf(const void *const hw, hri_sdadc_anactrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg |= SDADC_ANACTRL_CTRSDADC(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_anactrl_reg_t hri_sdadc_get_ANACTRL_CTRSDADC_bf(const void *const       hw,
                                                                        hri_sdadc_anactrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->ANACTRL.reg;
	tmp = (tmp & SDADC_ANACTRL_CTRSDADC(mask)) >> SDADC_ANACTRL_CTRSDADC_Pos;
	return tmp;
}

static inline void hri_sdadc_write_ANACTRL_CTRSDADC_bf(const void *const hw, hri_sdadc_anactrl_reg_t data)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->ANACTRL.reg;
	tmp &= ~SDADC_ANACTRL_CTRSDADC_Msk;
	tmp |= SDADC_ANACTRL_CTRSDADC(data);
	((Sdadc *)hw)->ANACTRL.reg = tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_ANACTRL_CTRSDADC_bf(const void *const hw, hri_sdadc_anactrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg &= ~SDADC_ANACTRL_CTRSDADC(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_ANACTRL_CTRSDADC_bf(const void *const hw, hri_sdadc_anactrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg ^= SDADC_ANACTRL_CTRSDADC(mask);
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_anactrl_reg_t hri_sdadc_read_ANACTRL_CTRSDADC_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->ANACTRL.reg;
	tmp = (tmp & SDADC_ANACTRL_CTRSDADC_Msk) >> SDADC_ANACTRL_CTRSDADC_Pos;
	return tmp;
}

static inline void hri_sdadc_set_ANACTRL_reg(const void *const hw, hri_sdadc_anactrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg |= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_anactrl_reg_t hri_sdadc_get_ANACTRL_reg(const void *const hw, hri_sdadc_anactrl_reg_t mask)
{
	uint8_t tmp;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	tmp = ((Sdadc *)hw)->ANACTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_ANACTRL_reg(const void *const hw, hri_sdadc_anactrl_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg = data;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_ANACTRL_reg(const void *const hw, hri_sdadc_anactrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg &= ~mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_ANACTRL_reg(const void *const hw, hri_sdadc_anactrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->ANACTRL.reg ^= mask;
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_anactrl_reg_t hri_sdadc_read_ANACTRL_reg(const void *const hw)
{
	hri_sdadc_wait_for_sync(hw, SDADC_SYNCBUSY_MASK);
	return ((Sdadc *)hw)->ANACTRL.reg;
}

static inline void hri_sdadc_set_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->DBGCTRL.reg |= SDADC_DBGCTRL_DBGRUN;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_sdadc_get_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->DBGCTRL.reg;
	tmp = (tmp & SDADC_DBGCTRL_DBGRUN) >> SDADC_DBGCTRL_DBGRUN_Pos;
	return (bool)tmp;
}

static inline void hri_sdadc_write_DBGCTRL_DBGRUN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	SDADC_CRITICAL_SECTION_ENTER();
	tmp = ((Sdadc *)hw)->DBGCTRL.reg;
	tmp &= ~SDADC_DBGCTRL_DBGRUN;
	tmp |= value << SDADC_DBGCTRL_DBGRUN_Pos;
	((Sdadc *)hw)->DBGCTRL.reg = tmp;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->DBGCTRL.reg &= ~SDADC_DBGCTRL_DBGRUN;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->DBGCTRL.reg ^= SDADC_DBGCTRL_DBGRUN;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_set_DBGCTRL_reg(const void *const hw, hri_sdadc_dbgctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->DBGCTRL.reg |= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_dbgctrl_reg_t hri_sdadc_get_DBGCTRL_reg(const void *const hw, hri_sdadc_dbgctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Sdadc *)hw)->DBGCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_sdadc_write_DBGCTRL_reg(const void *const hw, hri_sdadc_dbgctrl_reg_t data)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->DBGCTRL.reg = data;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_clear_DBGCTRL_reg(const void *const hw, hri_sdadc_dbgctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->DBGCTRL.reg &= ~mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_sdadc_toggle_DBGCTRL_reg(const void *const hw, hri_sdadc_dbgctrl_reg_t mask)
{
	SDADC_CRITICAL_SECTION_ENTER();
	((Sdadc *)hw)->DBGCTRL.reg ^= mask;
	SDADC_CRITICAL_SECTION_LEAVE();
}

static inline hri_sdadc_dbgctrl_reg_t hri_sdadc_read_DBGCTRL_reg(const void *const hw)
{
	return ((Sdadc *)hw)->DBGCTRL.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SDADC_C21_H_INCLUDED */
#endif /* _SAMC21_SDADC_COMPONENT_ */
