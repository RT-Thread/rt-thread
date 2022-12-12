/**
 * \file
 *
 * \brief SAM TRNG
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

#ifdef _SAML10_TRNG_COMPONENT_
#ifndef _HRI_TRNG_L10_H_INCLUDED_
#define _HRI_TRNG_L10_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_TRNG_CRITICAL_SECTIONS)
#define TRNG_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define TRNG_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define TRNG_CRITICAL_SECTION_ENTER()
#define TRNG_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_trng_data_reg_t;
typedef uint8_t  hri_trng_ctrla_reg_t;
typedef uint8_t  hri_trng_evctrl_reg_t;
typedef uint8_t  hri_trng_intenset_reg_t;
typedef uint8_t  hri_trng_intflag_reg_t;

static inline bool hri_trng_get_INTFLAG_DATARDY_bit(const void *const hw)
{
	return (((Trng *)hw)->INTFLAG.reg & TRNG_INTFLAG_DATARDY_Msk) >> TRNG_INTFLAG_DATARDY_Pos;
}

static inline void hri_trng_clear_INTFLAG_DATARDY_bit(const void *const hw)
{
	((Trng *)hw)->INTFLAG.reg = TRNG_INTFLAG_DATARDY_Msk;
}

static inline bool hri_trng_get_interrupt_DATARDY_bit(const void *const hw)
{
	return (((Trng *)hw)->INTFLAG.reg & TRNG_INTFLAG_DATARDY_Msk) >> TRNG_INTFLAG_DATARDY_Pos;
}

static inline void hri_trng_clear_interrupt_DATARDY_bit(const void *const hw)
{
	((Trng *)hw)->INTFLAG.reg = TRNG_INTFLAG_DATARDY_Msk;
}

static inline hri_trng_intflag_reg_t hri_trng_get_INTFLAG_reg(const void *const hw, hri_trng_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Trng *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_trng_intflag_reg_t hri_trng_read_INTFLAG_reg(const void *const hw)
{
	return ((Trng *)hw)->INTFLAG.reg;
}

static inline void hri_trng_clear_INTFLAG_reg(const void *const hw, hri_trng_intflag_reg_t mask)
{
	((Trng *)hw)->INTFLAG.reg = mask;
}

static inline void hri_trng_set_INTEN_DATARDY_bit(const void *const hw)
{
	((Trng *)hw)->INTENSET.reg = TRNG_INTENSET_DATARDY_Msk;
}

static inline bool hri_trng_get_INTEN_DATARDY_bit(const void *const hw)
{
	return (((Trng *)hw)->INTENSET.reg & TRNG_INTENSET_DATARDY_Msk) >> TRNG_INTENSET_DATARDY_Pos;
}

static inline void hri_trng_write_INTEN_DATARDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Trng *)hw)->INTENCLR.reg = TRNG_INTENSET_DATARDY_Msk;
	} else {
		((Trng *)hw)->INTENSET.reg = TRNG_INTENSET_DATARDY_Msk;
	}
}

static inline void hri_trng_clear_INTEN_DATARDY_bit(const void *const hw)
{
	((Trng *)hw)->INTENCLR.reg = TRNG_INTENSET_DATARDY_Msk;
}

static inline void hri_trng_set_INTEN_reg(const void *const hw, hri_trng_intenset_reg_t mask)
{
	((Trng *)hw)->INTENSET.reg = mask;
}

static inline hri_trng_intenset_reg_t hri_trng_get_INTEN_reg(const void *const hw, hri_trng_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Trng *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_trng_intenset_reg_t hri_trng_read_INTEN_reg(const void *const hw)
{
	return ((Trng *)hw)->INTENSET.reg;
}

static inline void hri_trng_write_INTEN_reg(const void *const hw, hri_trng_intenset_reg_t data)
{
	((Trng *)hw)->INTENSET.reg = data;
	((Trng *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_trng_clear_INTEN_reg(const void *const hw, hri_trng_intenset_reg_t mask)
{
	((Trng *)hw)->INTENCLR.reg = mask;
}

static inline hri_trng_data_reg_t hri_trng_get_DATA_DATA_bf(const void *const hw, hri_trng_data_reg_t mask)
{
	return (((Trng *)hw)->DATA.reg & TRNG_DATA_DATA(mask)) >> TRNG_DATA_DATA_Pos;
}

static inline hri_trng_data_reg_t hri_trng_read_DATA_DATA_bf(const void *const hw)
{
	return (((Trng *)hw)->DATA.reg & TRNG_DATA_DATA_Msk) >> TRNG_DATA_DATA_Pos;
}

static inline hri_trng_data_reg_t hri_trng_get_DATA_reg(const void *const hw, hri_trng_data_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Trng *)hw)->DATA.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_trng_data_reg_t hri_trng_read_DATA_reg(const void *const hw)
{
	return ((Trng *)hw)->DATA.reg;
}

static inline void hri_trng_set_CTRLA_ENABLE_bit(const void *const hw)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg |= TRNG_CTRLA_ENABLE_Msk;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_trng_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Trng *)hw)->CTRLA.reg;
	tmp = (tmp & TRNG_CTRLA_ENABLE_Msk) >> TRNG_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_trng_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TRNG_CRITICAL_SECTION_ENTER();
	tmp = ((Trng *)hw)->CTRLA.reg;
	tmp &= ~TRNG_CTRLA_ENABLE_Msk;
	tmp |= value << TRNG_CTRLA_ENABLE_Pos;
	((Trng *)hw)->CTRLA.reg = tmp;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg &= ~TRNG_CTRLA_ENABLE_Msk;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg ^= TRNG_CTRLA_ENABLE_Msk;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_set_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg |= TRNG_CTRLA_RUNSTDBY_Msk;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_trng_get_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Trng *)hw)->CTRLA.reg;
	tmp = (tmp & TRNG_CTRLA_RUNSTDBY_Msk) >> TRNG_CTRLA_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_trng_write_CTRLA_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TRNG_CRITICAL_SECTION_ENTER();
	tmp = ((Trng *)hw)->CTRLA.reg;
	tmp &= ~TRNG_CTRLA_RUNSTDBY_Msk;
	tmp |= value << TRNG_CTRLA_RUNSTDBY_Pos;
	((Trng *)hw)->CTRLA.reg = tmp;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_clear_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg &= ~TRNG_CTRLA_RUNSTDBY_Msk;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_toggle_CTRLA_RUNSTDBY_bit(const void *const hw)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg ^= TRNG_CTRLA_RUNSTDBY_Msk;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_set_CTRLA_reg(const void *const hw, hri_trng_ctrla_reg_t mask)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg |= mask;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline hri_trng_ctrla_reg_t hri_trng_get_CTRLA_reg(const void *const hw, hri_trng_ctrla_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Trng *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_trng_write_CTRLA_reg(const void *const hw, hri_trng_ctrla_reg_t data)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg = data;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_clear_CTRLA_reg(const void *const hw, hri_trng_ctrla_reg_t mask)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg &= ~mask;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_toggle_CTRLA_reg(const void *const hw, hri_trng_ctrla_reg_t mask)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->CTRLA.reg ^= mask;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline hri_trng_ctrla_reg_t hri_trng_read_CTRLA_reg(const void *const hw)
{
	return ((Trng *)hw)->CTRLA.reg;
}

static inline void hri_trng_set_EVCTRL_DATARDYEO_bit(const void *const hw)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->EVCTRL.reg |= TRNG_EVCTRL_DATARDYEO_Msk;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_trng_get_EVCTRL_DATARDYEO_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Trng *)hw)->EVCTRL.reg;
	tmp = (tmp & TRNG_EVCTRL_DATARDYEO_Msk) >> TRNG_EVCTRL_DATARDYEO_Pos;
	return (bool)tmp;
}

static inline void hri_trng_write_EVCTRL_DATARDYEO_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TRNG_CRITICAL_SECTION_ENTER();
	tmp = ((Trng *)hw)->EVCTRL.reg;
	tmp &= ~TRNG_EVCTRL_DATARDYEO_Msk;
	tmp |= value << TRNG_EVCTRL_DATARDYEO_Pos;
	((Trng *)hw)->EVCTRL.reg = tmp;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_clear_EVCTRL_DATARDYEO_bit(const void *const hw)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->EVCTRL.reg &= ~TRNG_EVCTRL_DATARDYEO_Msk;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_toggle_EVCTRL_DATARDYEO_bit(const void *const hw)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->EVCTRL.reg ^= TRNG_EVCTRL_DATARDYEO_Msk;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_set_EVCTRL_reg(const void *const hw, hri_trng_evctrl_reg_t mask)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->EVCTRL.reg |= mask;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline hri_trng_evctrl_reg_t hri_trng_get_EVCTRL_reg(const void *const hw, hri_trng_evctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Trng *)hw)->EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_trng_write_EVCTRL_reg(const void *const hw, hri_trng_evctrl_reg_t data)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->EVCTRL.reg = data;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_clear_EVCTRL_reg(const void *const hw, hri_trng_evctrl_reg_t mask)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->EVCTRL.reg &= ~mask;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline void hri_trng_toggle_EVCTRL_reg(const void *const hw, hri_trng_evctrl_reg_t mask)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->EVCTRL.reg ^= mask;
	TRNG_CRITICAL_SECTION_LEAVE();
}

static inline hri_trng_evctrl_reg_t hri_trng_read_EVCTRL_reg(const void *const hw)
{
	return ((Trng *)hw)->EVCTRL.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_TRNG_L10_H_INCLUDED */
#endif /* _SAML10_TRNG_COMPONENT_ */
