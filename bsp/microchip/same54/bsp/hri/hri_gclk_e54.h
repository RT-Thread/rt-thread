/**
 * \file
 *
 * \brief SAM GCLK
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAME54_GCLK_COMPONENT_
#ifndef _HRI_GCLK_E54_H_INCLUDED_
#define _HRI_GCLK_E54_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_GCLK_CRITICAL_SECTIONS)
#define GCLK_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define GCLK_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define GCLK_CRITICAL_SECTION_ENTER()
#define GCLK_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_gclk_genctrl_reg_t;
typedef uint32_t hri_gclk_pchctrl_reg_t;
typedef uint32_t hri_gclk_syncbusy_reg_t;
typedef uint8_t  hri_gclk_ctrla_reg_t;

static inline void hri_gclk_wait_for_sync(const void *const hw, hri_gclk_syncbusy_reg_t reg)
{
	while (((Gclk *)hw)->SYNCBUSY.reg & reg) {
	};
}

static inline bool hri_gclk_is_syncing(const void *const hw, hri_gclk_syncbusy_reg_t reg)
{
	return ((Gclk *)hw)->SYNCBUSY.reg & reg;
}

static inline bool hri_gclk_get_SYNCBUSY_SWRST_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_SWRST) >> GCLK_SYNCBUSY_SWRST_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL0_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL0) >> GCLK_SYNCBUSY_GENCTRL0_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL1_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL1) >> GCLK_SYNCBUSY_GENCTRL1_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL2_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL2) >> GCLK_SYNCBUSY_GENCTRL2_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL3_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL3) >> GCLK_SYNCBUSY_GENCTRL3_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL4_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL4) >> GCLK_SYNCBUSY_GENCTRL4_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL5_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL5) >> GCLK_SYNCBUSY_GENCTRL5_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL6_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL6) >> GCLK_SYNCBUSY_GENCTRL6_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL7_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL7) >> GCLK_SYNCBUSY_GENCTRL7_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL8_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL8) >> GCLK_SYNCBUSY_GENCTRL8_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL9_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL9) >> GCLK_SYNCBUSY_GENCTRL9_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL10_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL10) >> GCLK_SYNCBUSY_GENCTRL10_Pos;
}

static inline bool hri_gclk_get_SYNCBUSY_GENCTRL11_bit(const void *const hw)
{
	return (((Gclk *)hw)->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL11) >> GCLK_SYNCBUSY_GENCTRL11_Pos;
}

static inline hri_gclk_syncbusy_reg_t hri_gclk_get_SYNCBUSY_reg(const void *const hw, hri_gclk_syncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->SYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_gclk_syncbusy_reg_t hri_gclk_read_SYNCBUSY_reg(const void *const hw)
{
	return ((Gclk *)hw)->SYNCBUSY.reg;
}

static inline void hri_gclk_set_CTRLA_SWRST_bit(const void *const hw)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->CTRLA.reg |= GCLK_CTRLA_SWRST;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_SWRST);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gclk_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint8_t tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_SWRST);
	tmp = ((Gclk *)hw)->CTRLA.reg;
	tmp = (tmp & GCLK_CTRLA_SWRST) >> GCLK_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_gclk_set_CTRLA_reg(const void *const hw, hri_gclk_ctrla_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->CTRLA.reg |= mask;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_SWRST);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_ctrla_reg_t hri_gclk_get_CTRLA_reg(const void *const hw, hri_gclk_ctrla_reg_t mask)
{
	uint8_t tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_SWRST);
	tmp = ((Gclk *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gclk_write_CTRLA_reg(const void *const hw, hri_gclk_ctrla_reg_t data)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->CTRLA.reg = data;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_SWRST);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_CTRLA_reg(const void *const hw, hri_gclk_ctrla_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->CTRLA.reg &= ~mask;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_SWRST);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_CTRLA_reg(const void *const hw, hri_gclk_ctrla_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->CTRLA.reg ^= mask;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_SWRST);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_ctrla_reg_t hri_gclk_read_CTRLA_reg(const void *const hw)
{
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_SWRST);
	return ((Gclk *)hw)->CTRLA.reg;
}

static inline void hri_gclk_set_GENCTRL_GENEN_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg |= GCLK_GENCTRL_GENEN;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gclk_get_GENCTRL_GENEN_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_GENEN) >> GCLK_GENCTRL_GENEN_Pos;
	return (bool)tmp;
}

static inline void hri_gclk_write_GENCTRL_GENEN_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp &= ~GCLK_GENCTRL_GENEN;
	tmp |= value << GCLK_GENCTRL_GENEN_Pos;
	((Gclk *)hw)->GENCTRL[index].reg = tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_GENCTRL_GENEN_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg &= ~GCLK_GENCTRL_GENEN;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_GENCTRL_GENEN_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg ^= GCLK_GENCTRL_GENEN;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_set_GENCTRL_IDC_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg |= GCLK_GENCTRL_IDC;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gclk_get_GENCTRL_IDC_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_IDC) >> GCLK_GENCTRL_IDC_Pos;
	return (bool)tmp;
}

static inline void hri_gclk_write_GENCTRL_IDC_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp &= ~GCLK_GENCTRL_IDC;
	tmp |= value << GCLK_GENCTRL_IDC_Pos;
	((Gclk *)hw)->GENCTRL[index].reg = tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_GENCTRL_IDC_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg &= ~GCLK_GENCTRL_IDC;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_GENCTRL_IDC_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg ^= GCLK_GENCTRL_IDC;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_set_GENCTRL_OOV_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg |= GCLK_GENCTRL_OOV;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gclk_get_GENCTRL_OOV_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_OOV) >> GCLK_GENCTRL_OOV_Pos;
	return (bool)tmp;
}

static inline void hri_gclk_write_GENCTRL_OOV_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp &= ~GCLK_GENCTRL_OOV;
	tmp |= value << GCLK_GENCTRL_OOV_Pos;
	((Gclk *)hw)->GENCTRL[index].reg = tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_GENCTRL_OOV_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg &= ~GCLK_GENCTRL_OOV;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_GENCTRL_OOV_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg ^= GCLK_GENCTRL_OOV;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_set_GENCTRL_OE_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg |= GCLK_GENCTRL_OE;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gclk_get_GENCTRL_OE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_OE) >> GCLK_GENCTRL_OE_Pos;
	return (bool)tmp;
}

static inline void hri_gclk_write_GENCTRL_OE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp &= ~GCLK_GENCTRL_OE;
	tmp |= value << GCLK_GENCTRL_OE_Pos;
	((Gclk *)hw)->GENCTRL[index].reg = tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_GENCTRL_OE_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg &= ~GCLK_GENCTRL_OE;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_GENCTRL_OE_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg ^= GCLK_GENCTRL_OE;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_set_GENCTRL_DIVSEL_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg |= GCLK_GENCTRL_DIVSEL;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gclk_get_GENCTRL_DIVSEL_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_DIVSEL) >> GCLK_GENCTRL_DIVSEL_Pos;
	return (bool)tmp;
}

static inline void hri_gclk_write_GENCTRL_DIVSEL_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp &= ~GCLK_GENCTRL_DIVSEL;
	tmp |= value << GCLK_GENCTRL_DIVSEL_Pos;
	((Gclk *)hw)->GENCTRL[index].reg = tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_GENCTRL_DIVSEL_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg &= ~GCLK_GENCTRL_DIVSEL;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_GENCTRL_DIVSEL_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg ^= GCLK_GENCTRL_DIVSEL;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_set_GENCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg |= GCLK_GENCTRL_RUNSTDBY;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gclk_get_GENCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_RUNSTDBY) >> GCLK_GENCTRL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_gclk_write_GENCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp &= ~GCLK_GENCTRL_RUNSTDBY;
	tmp |= value << GCLK_GENCTRL_RUNSTDBY_Pos;
	((Gclk *)hw)->GENCTRL[index].reg = tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_GENCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg &= ~GCLK_GENCTRL_RUNSTDBY;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_GENCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg ^= GCLK_GENCTRL_RUNSTDBY;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_set_GENCTRL_SRC_bf(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg |= GCLK_GENCTRL_SRC(mask);
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_genctrl_reg_t hri_gclk_get_GENCTRL_SRC_bf(const void *const hw, uint8_t index,
                                                                 hri_gclk_genctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_SRC(mask)) >> GCLK_GENCTRL_SRC_Pos;
	return tmp;
}

static inline void hri_gclk_write_GENCTRL_SRC_bf(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t data)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp &= ~GCLK_GENCTRL_SRC_Msk;
	tmp |= GCLK_GENCTRL_SRC(data);
	((Gclk *)hw)->GENCTRL[index].reg = tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_GENCTRL_SRC_bf(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg &= ~GCLK_GENCTRL_SRC(mask);
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_GENCTRL_SRC_bf(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg ^= GCLK_GENCTRL_SRC(mask);
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_genctrl_reg_t hri_gclk_read_GENCTRL_SRC_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_SRC_Msk) >> GCLK_GENCTRL_SRC_Pos;
	return tmp;
}

static inline void hri_gclk_set_GENCTRL_DIV_bf(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg |= GCLK_GENCTRL_DIV(mask);
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_genctrl_reg_t hri_gclk_get_GENCTRL_DIV_bf(const void *const hw, uint8_t index,
                                                                 hri_gclk_genctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_DIV(mask)) >> GCLK_GENCTRL_DIV_Pos;
	return tmp;
}

static inline void hri_gclk_write_GENCTRL_DIV_bf(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t data)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp &= ~GCLK_GENCTRL_DIV_Msk;
	tmp |= GCLK_GENCTRL_DIV(data);
	((Gclk *)hw)->GENCTRL[index].reg = tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_GENCTRL_DIV_bf(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg &= ~GCLK_GENCTRL_DIV(mask);
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_GENCTRL_DIV_bf(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg ^= GCLK_GENCTRL_DIV(mask);
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_genctrl_reg_t hri_gclk_read_GENCTRL_DIV_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp = (tmp & GCLK_GENCTRL_DIV_Msk) >> GCLK_GENCTRL_DIV_Pos;
	return tmp;
}

static inline void hri_gclk_set_GENCTRL_reg(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg |= mask;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_genctrl_reg_t hri_gclk_get_GENCTRL_reg(const void *const hw, uint8_t index,
                                                              hri_gclk_genctrl_reg_t mask)
{
	uint32_t tmp;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	tmp = ((Gclk *)hw)->GENCTRL[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gclk_write_GENCTRL_reg(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t data)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg = data;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_GENCTRL_reg(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg &= ~mask;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_GENCTRL_reg(const void *const hw, uint8_t index, hri_gclk_genctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->GENCTRL[index].reg ^= mask;
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_genctrl_reg_t hri_gclk_read_GENCTRL_reg(const void *const hw, uint8_t index)
{
	hri_gclk_wait_for_sync(hw, GCLK_SYNCBUSY_MASK);
	return ((Gclk *)hw)->GENCTRL[index].reg;
}

static inline void hri_gclk_set_PCHCTRL_CHEN_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg |= GCLK_PCHCTRL_CHEN;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gclk_get_PCHCTRL_CHEN_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->PCHCTRL[index].reg;
	tmp = (tmp & GCLK_PCHCTRL_CHEN) >> GCLK_PCHCTRL_CHEN_Pos;
	return (bool)tmp;
}

static inline void hri_gclk_write_PCHCTRL_CHEN_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->PCHCTRL[index].reg;
	tmp &= ~GCLK_PCHCTRL_CHEN;
	tmp |= value << GCLK_PCHCTRL_CHEN_Pos;
	((Gclk *)hw)->PCHCTRL[index].reg = tmp;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_PCHCTRL_CHEN_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg &= ~GCLK_PCHCTRL_CHEN;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_PCHCTRL_CHEN_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg ^= GCLK_PCHCTRL_CHEN;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_set_PCHCTRL_WRTLOCK_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg |= GCLK_PCHCTRL_WRTLOCK;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_gclk_get_PCHCTRL_WRTLOCK_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->PCHCTRL[index].reg;
	tmp = (tmp & GCLK_PCHCTRL_WRTLOCK) >> GCLK_PCHCTRL_WRTLOCK_Pos;
	return (bool)tmp;
}

static inline void hri_gclk_write_PCHCTRL_WRTLOCK_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->PCHCTRL[index].reg;
	tmp &= ~GCLK_PCHCTRL_WRTLOCK;
	tmp |= value << GCLK_PCHCTRL_WRTLOCK_Pos;
	((Gclk *)hw)->PCHCTRL[index].reg = tmp;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_PCHCTRL_WRTLOCK_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg &= ~GCLK_PCHCTRL_WRTLOCK;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_PCHCTRL_WRTLOCK_bit(const void *const hw, uint8_t index)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg ^= GCLK_PCHCTRL_WRTLOCK;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_set_PCHCTRL_GEN_bf(const void *const hw, uint8_t index, hri_gclk_pchctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg |= GCLK_PCHCTRL_GEN(mask);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_pchctrl_reg_t hri_gclk_get_PCHCTRL_GEN_bf(const void *const hw, uint8_t index,
                                                                 hri_gclk_pchctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->PCHCTRL[index].reg;
	tmp = (tmp & GCLK_PCHCTRL_GEN(mask)) >> GCLK_PCHCTRL_GEN_Pos;
	return tmp;
}

static inline void hri_gclk_write_PCHCTRL_GEN_bf(const void *const hw, uint8_t index, hri_gclk_pchctrl_reg_t data)
{
	uint32_t tmp;
	GCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Gclk *)hw)->PCHCTRL[index].reg;
	tmp &= ~GCLK_PCHCTRL_GEN_Msk;
	tmp |= GCLK_PCHCTRL_GEN(data);
	((Gclk *)hw)->PCHCTRL[index].reg = tmp;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_PCHCTRL_GEN_bf(const void *const hw, uint8_t index, hri_gclk_pchctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg &= ~GCLK_PCHCTRL_GEN(mask);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_PCHCTRL_GEN_bf(const void *const hw, uint8_t index, hri_gclk_pchctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg ^= GCLK_PCHCTRL_GEN(mask);
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_pchctrl_reg_t hri_gclk_read_PCHCTRL_GEN_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->PCHCTRL[index].reg;
	tmp = (tmp & GCLK_PCHCTRL_GEN_Msk) >> GCLK_PCHCTRL_GEN_Pos;
	return tmp;
}

static inline void hri_gclk_set_PCHCTRL_reg(const void *const hw, uint8_t index, hri_gclk_pchctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg |= mask;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_pchctrl_reg_t hri_gclk_get_PCHCTRL_reg(const void *const hw, uint8_t index,
                                                              hri_gclk_pchctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gclk *)hw)->PCHCTRL[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_gclk_write_PCHCTRL_reg(const void *const hw, uint8_t index, hri_gclk_pchctrl_reg_t data)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg = data;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_clear_PCHCTRL_reg(const void *const hw, uint8_t index, hri_gclk_pchctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg &= ~mask;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gclk_toggle_PCHCTRL_reg(const void *const hw, uint8_t index, hri_gclk_pchctrl_reg_t mask)
{
	GCLK_CRITICAL_SECTION_ENTER();
	((Gclk *)hw)->PCHCTRL[index].reg ^= mask;
	GCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_gclk_pchctrl_reg_t hri_gclk_read_PCHCTRL_reg(const void *const hw, uint8_t index)
{
	return ((Gclk *)hw)->PCHCTRL[index].reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_GCLK_E54_H_INCLUDED */
#endif /* _SAME54_GCLK_COMPONENT_ */
