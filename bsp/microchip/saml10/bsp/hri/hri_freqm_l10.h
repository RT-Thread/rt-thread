/**
 * \file
 *
 * \brief SAM FREQM
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAML10_FREQM_COMPONENT_
#ifndef _HRI_FREQM_L10_H_INCLUDED_
#define _HRI_FREQM_L10_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_FREQM_CRITICAL_SECTIONS)
#define FREQM_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define FREQM_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define FREQM_CRITICAL_SECTION_ENTER()
#define FREQM_CRITICAL_SECTION_LEAVE()
#endif

typedef uint16_t hri_freqm_cfga_reg_t;
typedef uint32_t hri_freqm_syncbusy_reg_t;
typedef uint32_t hri_freqm_value_reg_t;
typedef uint8_t  hri_freqm_ctrla_reg_t;
typedef uint8_t  hri_freqm_ctrlb_reg_t;
typedef uint8_t  hri_freqm_intenset_reg_t;
typedef uint8_t  hri_freqm_intflag_reg_t;
typedef uint8_t  hri_freqm_status_reg_t;

static inline void hri_freqm_wait_for_sync(const void *const hw, hri_freqm_syncbusy_reg_t reg)
{
	while (((Freqm *)hw)->SYNCBUSY.reg & reg) {
	};
}

static inline bool hri_freqm_is_syncing(const void *const hw, hri_freqm_syncbusy_reg_t reg)
{
	return ((Freqm *)hw)->SYNCBUSY.reg & reg;
}

static inline bool hri_freqm_get_INTFLAG_DONE_bit(const void *const hw)
{
	return (((Freqm *)hw)->INTFLAG.reg & FREQM_INTFLAG_DONE_Msk) >> FREQM_INTFLAG_DONE_Pos;
}

static inline void hri_freqm_clear_INTFLAG_DONE_bit(const void *const hw)
{
	((Freqm *)hw)->INTFLAG.reg = FREQM_INTFLAG_DONE_Msk;
}

static inline bool hri_freqm_get_interrupt_DONE_bit(const void *const hw)
{
	return (((Freqm *)hw)->INTFLAG.reg & FREQM_INTFLAG_DONE_Msk) >> FREQM_INTFLAG_DONE_Pos;
}

static inline void hri_freqm_clear_interrupt_DONE_bit(const void *const hw)
{
	((Freqm *)hw)->INTFLAG.reg = FREQM_INTFLAG_DONE_Msk;
}

static inline hri_freqm_intflag_reg_t hri_freqm_get_INTFLAG_reg(const void *const hw, hri_freqm_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Freqm *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_freqm_intflag_reg_t hri_freqm_read_INTFLAG_reg(const void *const hw)
{
	return ((Freqm *)hw)->INTFLAG.reg;
}

static inline void hri_freqm_clear_INTFLAG_reg(const void *const hw, hri_freqm_intflag_reg_t mask)
{
	((Freqm *)hw)->INTFLAG.reg = mask;
}

static inline void hri_freqm_set_INTEN_DONE_bit(const void *const hw)
{
	((Freqm *)hw)->INTENSET.reg = FREQM_INTENSET_DONE_Msk;
}

static inline bool hri_freqm_get_INTEN_DONE_bit(const void *const hw)
{
	return (((Freqm *)hw)->INTENSET.reg & FREQM_INTENSET_DONE_Msk) >> FREQM_INTENSET_DONE_Pos;
}

static inline void hri_freqm_write_INTEN_DONE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Freqm *)hw)->INTENCLR.reg = FREQM_INTENSET_DONE_Msk;
	} else {
		((Freqm *)hw)->INTENSET.reg = FREQM_INTENSET_DONE_Msk;
	}
}

static inline void hri_freqm_clear_INTEN_DONE_bit(const void *const hw)
{
	((Freqm *)hw)->INTENCLR.reg = FREQM_INTENSET_DONE_Msk;
}

static inline void hri_freqm_set_INTEN_reg(const void *const hw, hri_freqm_intenset_reg_t mask)
{
	((Freqm *)hw)->INTENSET.reg = mask;
}

static inline hri_freqm_intenset_reg_t hri_freqm_get_INTEN_reg(const void *const hw, hri_freqm_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Freqm *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_freqm_intenset_reg_t hri_freqm_read_INTEN_reg(const void *const hw)
{
	return ((Freqm *)hw)->INTENSET.reg;
}

static inline void hri_freqm_write_INTEN_reg(const void *const hw, hri_freqm_intenset_reg_t data)
{
	((Freqm *)hw)->INTENSET.reg = data;
	((Freqm *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_freqm_clear_INTEN_reg(const void *const hw, hri_freqm_intenset_reg_t mask)
{
	((Freqm *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_freqm_get_SYNCBUSY_SWRST_bit(const void *const hw)
{
	return (((Freqm *)hw)->SYNCBUSY.reg & FREQM_SYNCBUSY_SWRST_Msk) >> FREQM_SYNCBUSY_SWRST_Pos;
}

static inline bool hri_freqm_get_SYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Freqm *)hw)->SYNCBUSY.reg & FREQM_SYNCBUSY_ENABLE_Msk) >> FREQM_SYNCBUSY_ENABLE_Pos;
}

static inline hri_freqm_syncbusy_reg_t hri_freqm_get_SYNCBUSY_reg(const void *const hw, hri_freqm_syncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Freqm *)hw)->SYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_freqm_syncbusy_reg_t hri_freqm_read_SYNCBUSY_reg(const void *const hw)
{
	return ((Freqm *)hw)->SYNCBUSY.reg;
}

static inline hri_freqm_value_reg_t hri_freqm_get_VALUE_VALUE_bf(const void *const hw, hri_freqm_value_reg_t mask)
{
	return (((Freqm *)hw)->VALUE.reg & FREQM_VALUE_VALUE(mask)) >> FREQM_VALUE_VALUE_Pos;
}

static inline hri_freqm_value_reg_t hri_freqm_read_VALUE_VALUE_bf(const void *const hw)
{
	return (((Freqm *)hw)->VALUE.reg & FREQM_VALUE_VALUE_Msk) >> FREQM_VALUE_VALUE_Pos;
}

static inline hri_freqm_value_reg_t hri_freqm_get_VALUE_reg(const void *const hw, hri_freqm_value_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Freqm *)hw)->VALUE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_freqm_value_reg_t hri_freqm_read_VALUE_reg(const void *const hw)
{
	return ((Freqm *)hw)->VALUE.reg;
}

static inline void hri_freqm_set_CTRLA_SWRST_bit(const void *const hw)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CTRLA.reg |= FREQM_CTRLA_SWRST_Msk;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_SWRST);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_freqm_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint8_t tmp;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_SWRST);
	tmp = ((Freqm *)hw)->CTRLA.reg;
	tmp = (tmp & FREQM_CTRLA_SWRST_Msk) >> FREQM_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_freqm_set_CTRLA_ENABLE_bit(const void *const hw)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CTRLA.reg |= FREQM_CTRLA_ENABLE_Msk;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_SWRST | FREQM_SYNCBUSY_ENABLE);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_freqm_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_SWRST | FREQM_SYNCBUSY_ENABLE);
	tmp = ((Freqm *)hw)->CTRLA.reg;
	tmp = (tmp & FREQM_CTRLA_ENABLE_Msk) >> FREQM_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_freqm_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	FREQM_CRITICAL_SECTION_ENTER();
	tmp = ((Freqm *)hw)->CTRLA.reg;
	tmp &= ~FREQM_CTRLA_ENABLE_Msk;
	tmp |= value << FREQM_CTRLA_ENABLE_Pos;
	((Freqm *)hw)->CTRLA.reg = tmp;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_SWRST | FREQM_SYNCBUSY_ENABLE);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CTRLA.reg &= ~FREQM_CTRLA_ENABLE_Msk;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_SWRST | FREQM_SYNCBUSY_ENABLE);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CTRLA.reg ^= FREQM_CTRLA_ENABLE_Msk;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_SWRST | FREQM_SYNCBUSY_ENABLE);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_set_CTRLA_reg(const void *const hw, hri_freqm_ctrla_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CTRLA.reg |= mask;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_MASK);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline hri_freqm_ctrla_reg_t hri_freqm_get_CTRLA_reg(const void *const hw, hri_freqm_ctrla_reg_t mask)
{
	uint8_t tmp;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_MASK);
	tmp = ((Freqm *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_freqm_write_CTRLA_reg(const void *const hw, hri_freqm_ctrla_reg_t data)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CTRLA.reg = data;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_MASK);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_clear_CTRLA_reg(const void *const hw, hri_freqm_ctrla_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CTRLA.reg &= ~mask;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_MASK);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_toggle_CTRLA_reg(const void *const hw, hri_freqm_ctrla_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CTRLA.reg ^= mask;
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_MASK);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline hri_freqm_ctrla_reg_t hri_freqm_read_CTRLA_reg(const void *const hw)
{
	hri_freqm_wait_for_sync(hw, FREQM_SYNCBUSY_MASK);
	return ((Freqm *)hw)->CTRLA.reg;
}

static inline void hri_freqm_set_CFGA_DIVREF_bit(const void *const hw)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg |= FREQM_CFGA_DIVREF_Msk;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_freqm_get_CFGA_DIVREF_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Freqm *)hw)->CFGA.reg;
	tmp = (tmp & FREQM_CFGA_DIVREF_Msk) >> FREQM_CFGA_DIVREF_Pos;
	return (bool)tmp;
}

static inline void hri_freqm_write_CFGA_DIVREF_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	FREQM_CRITICAL_SECTION_ENTER();
	tmp = ((Freqm *)hw)->CFGA.reg;
	tmp &= ~FREQM_CFGA_DIVREF_Msk;
	tmp |= value << FREQM_CFGA_DIVREF_Pos;
	((Freqm *)hw)->CFGA.reg = tmp;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_clear_CFGA_DIVREF_bit(const void *const hw)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg &= ~FREQM_CFGA_DIVREF_Msk;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_toggle_CFGA_DIVREF_bit(const void *const hw)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg ^= FREQM_CFGA_DIVREF_Msk;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_set_CFGA_REFNUM_bf(const void *const hw, hri_freqm_cfga_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg |= FREQM_CFGA_REFNUM(mask);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline hri_freqm_cfga_reg_t hri_freqm_get_CFGA_REFNUM_bf(const void *const hw, hri_freqm_cfga_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Freqm *)hw)->CFGA.reg;
	tmp = (tmp & FREQM_CFGA_REFNUM(mask)) >> FREQM_CFGA_REFNUM_Pos;
	return tmp;
}

static inline void hri_freqm_write_CFGA_REFNUM_bf(const void *const hw, hri_freqm_cfga_reg_t data)
{
	uint16_t tmp;
	FREQM_CRITICAL_SECTION_ENTER();
	tmp = ((Freqm *)hw)->CFGA.reg;
	tmp &= ~FREQM_CFGA_REFNUM_Msk;
	tmp |= FREQM_CFGA_REFNUM(data);
	((Freqm *)hw)->CFGA.reg = tmp;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_clear_CFGA_REFNUM_bf(const void *const hw, hri_freqm_cfga_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg &= ~FREQM_CFGA_REFNUM(mask);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_toggle_CFGA_REFNUM_bf(const void *const hw, hri_freqm_cfga_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg ^= FREQM_CFGA_REFNUM(mask);
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline hri_freqm_cfga_reg_t hri_freqm_read_CFGA_REFNUM_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Freqm *)hw)->CFGA.reg;
	tmp = (tmp & FREQM_CFGA_REFNUM_Msk) >> FREQM_CFGA_REFNUM_Pos;
	return tmp;
}

static inline void hri_freqm_set_CFGA_reg(const void *const hw, hri_freqm_cfga_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg |= mask;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline hri_freqm_cfga_reg_t hri_freqm_get_CFGA_reg(const void *const hw, hri_freqm_cfga_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Freqm *)hw)->CFGA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_freqm_write_CFGA_reg(const void *const hw, hri_freqm_cfga_reg_t data)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg = data;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_clear_CFGA_reg(const void *const hw, hri_freqm_cfga_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg &= ~mask;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_freqm_toggle_CFGA_reg(const void *const hw, hri_freqm_cfga_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CFGA.reg ^= mask;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline hri_freqm_cfga_reg_t hri_freqm_read_CFGA_reg(const void *const hw)
{
	return ((Freqm *)hw)->CFGA.reg;
}

static inline bool hri_freqm_get_STATUS_BUSY_bit(const void *const hw)
{
	return (((Freqm *)hw)->STATUS.reg & FREQM_STATUS_BUSY_Msk) >> FREQM_STATUS_BUSY_Pos;
}

static inline void hri_freqm_clear_STATUS_BUSY_bit(const void *const hw)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->STATUS.reg = FREQM_STATUS_BUSY_Msk;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_freqm_get_STATUS_OVF_bit(const void *const hw)
{
	return (((Freqm *)hw)->STATUS.reg & FREQM_STATUS_OVF_Msk) >> FREQM_STATUS_OVF_Pos;
}

static inline void hri_freqm_clear_STATUS_OVF_bit(const void *const hw)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->STATUS.reg = FREQM_STATUS_OVF_Msk;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline hri_freqm_status_reg_t hri_freqm_get_STATUS_reg(const void *const hw, hri_freqm_status_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Freqm *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_freqm_clear_STATUS_reg(const void *const hw, hri_freqm_status_reg_t mask)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->STATUS.reg = mask;
	FREQM_CRITICAL_SECTION_LEAVE();
}

static inline hri_freqm_status_reg_t hri_freqm_read_STATUS_reg(const void *const hw)
{
	return ((Freqm *)hw)->STATUS.reg;
}

static inline void hri_freqm_write_CTRLB_reg(const void *const hw, hri_freqm_ctrlb_reg_t data)
{
	FREQM_CRITICAL_SECTION_ENTER();
	((Freqm *)hw)->CTRLB.reg = data;
	FREQM_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_FREQM_L10_H_INCLUDED */
#endif /* _SAML10_FREQM_COMPONENT_ */
