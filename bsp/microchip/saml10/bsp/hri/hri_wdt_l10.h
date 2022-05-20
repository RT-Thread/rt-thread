/**
 * \file
 *
 * \brief SAM WDT
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

#ifdef _SAML10_WDT_COMPONENT_
#ifndef _HRI_WDT_L10_H_INCLUDED_
#define _HRI_WDT_L10_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_WDT_CRITICAL_SECTIONS)
#define WDT_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define WDT_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define WDT_CRITICAL_SECTION_ENTER()
#define WDT_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_wdt_syncbusy_reg_t;
typedef uint8_t  hri_wdt_clear_reg_t;
typedef uint8_t  hri_wdt_config_reg_t;
typedef uint8_t  hri_wdt_ctrla_reg_t;
typedef uint8_t  hri_wdt_ewctrl_reg_t;
typedef uint8_t  hri_wdt_intenset_reg_t;
typedef uint8_t  hri_wdt_intflag_reg_t;

static inline void hri_wdt_wait_for_sync(const void *const hw, hri_wdt_syncbusy_reg_t reg)
{
	while (((Wdt *)hw)->SYNCBUSY.reg & reg) {
	};
}

static inline bool hri_wdt_is_syncing(const void *const hw, hri_wdt_syncbusy_reg_t reg)
{
	return ((Wdt *)hw)->SYNCBUSY.reg & reg;
}

static inline bool hri_wdt_get_INTFLAG_EW_bit(const void *const hw)
{
	return (((Wdt *)hw)->INTFLAG.reg & WDT_INTFLAG_EW_Msk) >> WDT_INTFLAG_EW_Pos;
}

static inline void hri_wdt_clear_INTFLAG_EW_bit(const void *const hw)
{
	((Wdt *)hw)->INTFLAG.reg = WDT_INTFLAG_EW_Msk;
}

static inline bool hri_wdt_get_interrupt_EW_bit(const void *const hw)
{
	return (((Wdt *)hw)->INTFLAG.reg & WDT_INTFLAG_EW_Msk) >> WDT_INTFLAG_EW_Pos;
}

static inline void hri_wdt_clear_interrupt_EW_bit(const void *const hw)
{
	((Wdt *)hw)->INTFLAG.reg = WDT_INTFLAG_EW_Msk;
}

static inline hri_wdt_intflag_reg_t hri_wdt_get_INTFLAG_reg(const void *const hw, hri_wdt_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_wdt_intflag_reg_t hri_wdt_read_INTFLAG_reg(const void *const hw)
{
	return ((Wdt *)hw)->INTFLAG.reg;
}

static inline void hri_wdt_clear_INTFLAG_reg(const void *const hw, hri_wdt_intflag_reg_t mask)
{
	((Wdt *)hw)->INTFLAG.reg = mask;
}

static inline void hri_wdt_set_INTEN_EW_bit(const void *const hw)
{
	((Wdt *)hw)->INTENSET.reg = WDT_INTENSET_EW_Msk;
}

static inline bool hri_wdt_get_INTEN_EW_bit(const void *const hw)
{
	return (((Wdt *)hw)->INTENSET.reg & WDT_INTENSET_EW_Msk) >> WDT_INTENSET_EW_Pos;
}

static inline void hri_wdt_write_INTEN_EW_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Wdt *)hw)->INTENCLR.reg = WDT_INTENSET_EW_Msk;
	} else {
		((Wdt *)hw)->INTENSET.reg = WDT_INTENSET_EW_Msk;
	}
}

static inline void hri_wdt_clear_INTEN_EW_bit(const void *const hw)
{
	((Wdt *)hw)->INTENCLR.reg = WDT_INTENSET_EW_Msk;
}

static inline void hri_wdt_set_INTEN_reg(const void *const hw, hri_wdt_intenset_reg_t mask)
{
	((Wdt *)hw)->INTENSET.reg = mask;
}

static inline hri_wdt_intenset_reg_t hri_wdt_get_INTEN_reg(const void *const hw, hri_wdt_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_wdt_intenset_reg_t hri_wdt_read_INTEN_reg(const void *const hw)
{
	return ((Wdt *)hw)->INTENSET.reg;
}

static inline void hri_wdt_write_INTEN_reg(const void *const hw, hri_wdt_intenset_reg_t data)
{
	((Wdt *)hw)->INTENSET.reg = data;
	((Wdt *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_wdt_clear_INTEN_reg(const void *const hw, hri_wdt_intenset_reg_t mask)
{
	((Wdt *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_wdt_get_SYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Wdt *)hw)->SYNCBUSY.reg & WDT_SYNCBUSY_ENABLE_Msk) >> WDT_SYNCBUSY_ENABLE_Pos;
}

static inline bool hri_wdt_get_SYNCBUSY_WEN_bit(const void *const hw)
{
	return (((Wdt *)hw)->SYNCBUSY.reg & WDT_SYNCBUSY_WEN_Msk) >> WDT_SYNCBUSY_WEN_Pos;
}

static inline bool hri_wdt_get_SYNCBUSY_RUNSTDBY_bit(const void *const hw)
{
	return (((Wdt *)hw)->SYNCBUSY.reg & WDT_SYNCBUSY_RUNSTDBY_Msk) >> WDT_SYNCBUSY_RUNSTDBY_Pos;
}

static inline bool hri_wdt_get_SYNCBUSY_ALWAYSON_bit(const void *const hw)
{
	return (((Wdt *)hw)->SYNCBUSY.reg & WDT_SYNCBUSY_ALWAYSON_Msk) >> WDT_SYNCBUSY_ALWAYSON_Pos;
}

static inline bool hri_wdt_get_SYNCBUSY_CLEAR_bit(const void *const hw)
{
	return (((Wdt *)hw)->SYNCBUSY.reg & WDT_SYNCBUSY_CLEAR_Msk) >> WDT_SYNCBUSY_CLEAR_Pos;
}

static inline hri_wdt_syncbusy_reg_t hri_wdt_get_SYNCBUSY_reg(const void *const hw, hri_wdt_syncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Wdt *)hw)->SYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_wdt_syncbusy_reg_t hri_wdt_read_SYNCBUSY_reg(const void *const hw)
{
	return ((Wdt *)hw)->SYNCBUSY.reg;
}

static inline void hri_wdt_set_CTRLA_ENABLE_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg |= WDT_CTRLA_ENABLE_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_wdt_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	tmp = ((Wdt *)hw)->CTRLA.reg;
	tmp = (tmp & WDT_CTRLA_ENABLE_Msk) >> WDT_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_wdt_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->CTRLA.reg;
	tmp &= ~WDT_CTRLA_ENABLE_Msk;
	tmp |= value << WDT_CTRLA_ENABLE_Pos;
	((Wdt *)hw)->CTRLA.reg = tmp;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg &= ~WDT_CTRLA_ENABLE_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg ^= WDT_CTRLA_ENABLE_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_CTRLA_WEN_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg |= WDT_CTRLA_WEN_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_wdt_get_CTRLA_WEN_bit(const void *const hw)
{
	uint8_t tmp;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	tmp = ((Wdt *)hw)->CTRLA.reg;
	tmp = (tmp & WDT_CTRLA_WEN_Msk) >> WDT_CTRLA_WEN_Pos;
	return (bool)tmp;
}

static inline void hri_wdt_write_CTRLA_WEN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->CTRLA.reg;
	tmp &= ~WDT_CTRLA_WEN_Msk;
	tmp |= value << WDT_CTRLA_WEN_Pos;
	((Wdt *)hw)->CTRLA.reg = tmp;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_CTRLA_WEN_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg &= ~WDT_CTRLA_WEN_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_CTRLA_WEN_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg ^= WDT_CTRLA_WEN_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg |= WDT_CTRLA_RUNSTDBY_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_wdt_get_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	uint8_t tmp;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	tmp = ((Wdt *)hw)->CTRLA.reg;
	tmp = (tmp & WDT_CTRLA_RUNSTDBY_Msk) >> WDT_CTRLA_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_wdt_write_CTRLA_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->CTRLA.reg;
	tmp &= ~WDT_CTRLA_RUNSTDBY_Msk;
	tmp |= value << WDT_CTRLA_RUNSTDBY_Pos;
	((Wdt *)hw)->CTRLA.reg = tmp;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg &= ~WDT_CTRLA_RUNSTDBY_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg ^= WDT_CTRLA_RUNSTDBY_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_CTRLA_ALWAYSON_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg |= WDT_CTRLA_ALWAYSON_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_wdt_get_CTRLA_ALWAYSON_bit(const void *const hw)
{
	uint8_t tmp;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	tmp = ((Wdt *)hw)->CTRLA.reg;
	tmp = (tmp & WDT_CTRLA_ALWAYSON_Msk) >> WDT_CTRLA_ALWAYSON_Pos;
	return (bool)tmp;
}

static inline void hri_wdt_write_CTRLA_ALWAYSON_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->CTRLA.reg;
	tmp &= ~WDT_CTRLA_ALWAYSON_Msk;
	tmp |= value << WDT_CTRLA_ALWAYSON_Pos;
	((Wdt *)hw)->CTRLA.reg = tmp;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_CTRLA_ALWAYSON_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg &= ~WDT_CTRLA_ALWAYSON_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_CTRLA_ALWAYSON_bit(const void *const hw)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg ^= WDT_CTRLA_ALWAYSON_Msk;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_set_CTRLA_reg(const void *const hw, hri_wdt_ctrla_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg |= mask;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_ctrla_reg_t hri_wdt_get_CTRLA_reg(const void *const hw, hri_wdt_ctrla_reg_t mask)
{
	uint8_t tmp;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	tmp = ((Wdt *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_wdt_write_CTRLA_reg(const void *const hw, hri_wdt_ctrla_reg_t data)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg = data;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_CTRLA_reg(const void *const hw, hri_wdt_ctrla_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg &= ~mask;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_CTRLA_reg(const void *const hw, hri_wdt_ctrla_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CTRLA.reg ^= mask;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_ctrla_reg_t hri_wdt_read_CTRLA_reg(const void *const hw)
{
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_ENABLE | WDT_SYNCBUSY_WEN | WDT_SYNCBUSY_RUNSTDBY | WDT_SYNCBUSY_ALWAYSON);
	return ((Wdt *)hw)->CTRLA.reg;
}

static inline void hri_wdt_set_CONFIG_PER_bf(const void *const hw, hri_wdt_config_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg |= WDT_CONFIG_PER(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_config_reg_t hri_wdt_get_CONFIG_PER_bf(const void *const hw, hri_wdt_config_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->CONFIG.reg;
	tmp = (tmp & WDT_CONFIG_PER(mask)) >> WDT_CONFIG_PER_Pos;
	return tmp;
}

static inline void hri_wdt_write_CONFIG_PER_bf(const void *const hw, hri_wdt_config_reg_t data)
{
	uint8_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->CONFIG.reg;
	tmp &= ~WDT_CONFIG_PER_Msk;
	tmp |= WDT_CONFIG_PER(data);
	((Wdt *)hw)->CONFIG.reg = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_CONFIG_PER_bf(const void *const hw, hri_wdt_config_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg &= ~WDT_CONFIG_PER(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_CONFIG_PER_bf(const void *const hw, hri_wdt_config_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg ^= WDT_CONFIG_PER(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_config_reg_t hri_wdt_read_CONFIG_PER_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->CONFIG.reg;
	tmp = (tmp & WDT_CONFIG_PER_Msk) >> WDT_CONFIG_PER_Pos;
	return tmp;
}

static inline void hri_wdt_set_CONFIG_WINDOW_bf(const void *const hw, hri_wdt_config_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg |= WDT_CONFIG_WINDOW(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_config_reg_t hri_wdt_get_CONFIG_WINDOW_bf(const void *const hw, hri_wdt_config_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->CONFIG.reg;
	tmp = (tmp & WDT_CONFIG_WINDOW(mask)) >> WDT_CONFIG_WINDOW_Pos;
	return tmp;
}

static inline void hri_wdt_write_CONFIG_WINDOW_bf(const void *const hw, hri_wdt_config_reg_t data)
{
	uint8_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->CONFIG.reg;
	tmp &= ~WDT_CONFIG_WINDOW_Msk;
	tmp |= WDT_CONFIG_WINDOW(data);
	((Wdt *)hw)->CONFIG.reg = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_CONFIG_WINDOW_bf(const void *const hw, hri_wdt_config_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg &= ~WDT_CONFIG_WINDOW(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_CONFIG_WINDOW_bf(const void *const hw, hri_wdt_config_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg ^= WDT_CONFIG_WINDOW(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_config_reg_t hri_wdt_read_CONFIG_WINDOW_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->CONFIG.reg;
	tmp = (tmp & WDT_CONFIG_WINDOW_Msk) >> WDT_CONFIG_WINDOW_Pos;
	return tmp;
}

static inline void hri_wdt_set_CONFIG_reg(const void *const hw, hri_wdt_config_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg |= mask;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_config_reg_t hri_wdt_get_CONFIG_reg(const void *const hw, hri_wdt_config_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->CONFIG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_wdt_write_CONFIG_reg(const void *const hw, hri_wdt_config_reg_t data)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg = data;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_CONFIG_reg(const void *const hw, hri_wdt_config_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg &= ~mask;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_CONFIG_reg(const void *const hw, hri_wdt_config_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CONFIG.reg ^= mask;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_config_reg_t hri_wdt_read_CONFIG_reg(const void *const hw)
{
	return ((Wdt *)hw)->CONFIG.reg;
}

static inline void hri_wdt_set_EWCTRL_EWOFFSET_bf(const void *const hw, hri_wdt_ewctrl_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->EWCTRL.reg |= WDT_EWCTRL_EWOFFSET(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_ewctrl_reg_t hri_wdt_get_EWCTRL_EWOFFSET_bf(const void *const hw, hri_wdt_ewctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->EWCTRL.reg;
	tmp = (tmp & WDT_EWCTRL_EWOFFSET(mask)) >> WDT_EWCTRL_EWOFFSET_Pos;
	return tmp;
}

static inline void hri_wdt_write_EWCTRL_EWOFFSET_bf(const void *const hw, hri_wdt_ewctrl_reg_t data)
{
	uint8_t tmp;
	WDT_CRITICAL_SECTION_ENTER();
	tmp = ((Wdt *)hw)->EWCTRL.reg;
	tmp &= ~WDT_EWCTRL_EWOFFSET_Msk;
	tmp |= WDT_EWCTRL_EWOFFSET(data);
	((Wdt *)hw)->EWCTRL.reg = tmp;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_EWCTRL_EWOFFSET_bf(const void *const hw, hri_wdt_ewctrl_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->EWCTRL.reg &= ~WDT_EWCTRL_EWOFFSET(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_EWCTRL_EWOFFSET_bf(const void *const hw, hri_wdt_ewctrl_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->EWCTRL.reg ^= WDT_EWCTRL_EWOFFSET(mask);
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_ewctrl_reg_t hri_wdt_read_EWCTRL_EWOFFSET_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->EWCTRL.reg;
	tmp = (tmp & WDT_EWCTRL_EWOFFSET_Msk) >> WDT_EWCTRL_EWOFFSET_Pos;
	return tmp;
}

static inline void hri_wdt_set_EWCTRL_reg(const void *const hw, hri_wdt_ewctrl_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->EWCTRL.reg |= mask;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_ewctrl_reg_t hri_wdt_get_EWCTRL_reg(const void *const hw, hri_wdt_ewctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Wdt *)hw)->EWCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_wdt_write_EWCTRL_reg(const void *const hw, hri_wdt_ewctrl_reg_t data)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->EWCTRL.reg = data;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_clear_EWCTRL_reg(const void *const hw, hri_wdt_ewctrl_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->EWCTRL.reg &= ~mask;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_wdt_toggle_EWCTRL_reg(const void *const hw, hri_wdt_ewctrl_reg_t mask)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->EWCTRL.reg ^= mask;
	WDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_wdt_ewctrl_reg_t hri_wdt_read_EWCTRL_reg(const void *const hw)
{
	return ((Wdt *)hw)->EWCTRL.reg;
}

static inline void hri_wdt_write_CLEAR_reg(const void *const hw, hri_wdt_clear_reg_t data)
{
	WDT_CRITICAL_SECTION_ENTER();
	((Wdt *)hw)->CLEAR.reg = data;
	hri_wdt_wait_for_sync(hw, WDT_SYNCBUSY_CLEAR);
	WDT_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_WDT_L10_H_INCLUDED */
#endif /* _SAML10_WDT_COMPONENT_ */
