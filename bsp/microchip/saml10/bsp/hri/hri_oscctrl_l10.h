/**
 * \file
 *
 * \brief SAM OSCCTRL
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

#ifdef _SAML10_OSCCTRL_COMPONENT_
#ifndef _HRI_OSCCTRL_L10_H_INCLUDED_
#define _HRI_OSCCTRL_L10_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_OSCCTRL_CRITICAL_SECTIONS)
#define OSCCTRL_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define OSCCTRL_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define OSCCTRL_CRITICAL_SECTION_ENTER()
#define OSCCTRL_CRITICAL_SECTION_LEAVE()
#endif

typedef uint16_t hri_oscctrl_dfllulpctrl_reg_t;
typedef uint16_t hri_oscctrl_xoscctrl_reg_t;
typedef uint32_t hri_oscctrl_dfllulpdly_reg_t;
typedef uint32_t hri_oscctrl_dfllulpratio_reg_t;
typedef uint32_t hri_oscctrl_dfllulpsyncbusy_reg_t;
typedef uint32_t hri_oscctrl_dpllctrlb_reg_t;
typedef uint32_t hri_oscctrl_dpllratio_reg_t;
typedef uint32_t hri_oscctrl_intenset_reg_t;
typedef uint32_t hri_oscctrl_intflag_reg_t;
typedef uint32_t hri_oscctrl_status_reg_t;
typedef uint8_t  hri_oscctrl_cfdpresc_reg_t;
typedef uint8_t  hri_oscctrl_dfllulpdither_reg_t;
typedef uint8_t  hri_oscctrl_dfllulprreq_reg_t;
typedef uint8_t  hri_oscctrl_dpllctrla_reg_t;
typedef uint8_t  hri_oscctrl_dpllpresc_reg_t;
typedef uint8_t  hri_oscctrl_dpllstatus_reg_t;
typedef uint8_t  hri_oscctrl_dpllsyncbusy_reg_t;
typedef uint8_t  hri_oscctrl_evctrl_reg_t;
typedef uint8_t  hri_oscctrl_osc16mctrl_reg_t;

static inline void hri_oscctrl_dfllulpsyncbusy_wait_for_sync(const void *const                 hw,
                                                             hri_oscctrl_dfllulpsyncbusy_reg_t reg)
{
	while (((Oscctrl *)hw)->DFLLULPSYNCBUSY.reg & reg) {
	};
}

static inline bool hri_oscctrl_dfllulpsyncbusy_is_syncing(const void *const hw, hri_oscctrl_dfllulpsyncbusy_reg_t reg)
{
	return ((Oscctrl *)hw)->DFLLULPSYNCBUSY.reg & reg;
}

static inline void hri_oscctrl_dpllsyncbusy_wait_for_sync(const void *const hw, hri_oscctrl_dpllsyncbusy_reg_t reg)
{
	while (((Oscctrl *)hw)->DPLLSYNCBUSY.reg & reg) {
	};
}

static inline bool hri_oscctrl_dpllsyncbusy_is_syncing(const void *const hw, hri_oscctrl_dpllsyncbusy_reg_t reg)
{
	return ((Oscctrl *)hw)->DPLLSYNCBUSY.reg & reg;
}

static inline bool hri_oscctrl_get_INTFLAG_XOSCRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_XOSCRDY_Msk) >> OSCCTRL_INTFLAG_XOSCRDY_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_XOSCRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_XOSCRDY_Msk;
}

static inline bool hri_oscctrl_get_INTFLAG_XOSCFAIL_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_XOSCFAIL_Msk) >> OSCCTRL_INTFLAG_XOSCFAIL_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_XOSCFAIL_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_XOSCFAIL_Msk;
}

static inline bool hri_oscctrl_get_INTFLAG_OSC16MRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_OSC16MRDY_Msk) >> OSCCTRL_INTFLAG_OSC16MRDY_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_OSC16MRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_OSC16MRDY_Msk;
}

static inline bool hri_oscctrl_get_INTFLAG_DFLLULPRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DFLLULPRDY_Msk) >> OSCCTRL_INTFLAG_DFLLULPRDY_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DFLLULPRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DFLLULPRDY_Msk;
}

static inline bool hri_oscctrl_get_INTFLAG_DFLLULPLOCK_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DFLLULPLOCK_Msk) >> OSCCTRL_INTFLAG_DFLLULPLOCK_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DFLLULPLOCK_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DFLLULPLOCK_Msk;
}

static inline bool hri_oscctrl_get_INTFLAG_DFLLULPNOLOCK_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DFLLULPNOLOCK_Msk) >> OSCCTRL_INTFLAG_DFLLULPNOLOCK_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DFLLULPNOLOCK_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DFLLULPNOLOCK_Msk;
}

static inline bool hri_oscctrl_get_INTFLAG_DPLLLCKR_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLCKR_Msk) >> OSCCTRL_INTFLAG_DPLLLCKR_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DPLLLCKR_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLCKR_Msk;
}

static inline bool hri_oscctrl_get_INTFLAG_DPLLLCKF_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLCKF_Msk) >> OSCCTRL_INTFLAG_DPLLLCKF_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DPLLLCKF_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLCKF_Msk;
}

static inline bool hri_oscctrl_get_INTFLAG_DPLLLTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLTO_Msk) >> OSCCTRL_INTFLAG_DPLLLTO_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DPLLLTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLTO_Msk;
}

static inline bool hri_oscctrl_get_INTFLAG_DPLLLDRTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLDRTO_Msk) >> OSCCTRL_INTFLAG_DPLLLDRTO_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DPLLLDRTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLDRTO_Msk;
}

static inline bool hri_oscctrl_get_interrupt_XOSCRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_XOSCRDY_Msk) >> OSCCTRL_INTFLAG_XOSCRDY_Pos;
}

static inline void hri_oscctrl_clear_interrupt_XOSCRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_XOSCRDY_Msk;
}

static inline bool hri_oscctrl_get_interrupt_XOSCFAIL_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_XOSCFAIL_Msk) >> OSCCTRL_INTFLAG_XOSCFAIL_Pos;
}

static inline void hri_oscctrl_clear_interrupt_XOSCFAIL_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_XOSCFAIL_Msk;
}

static inline bool hri_oscctrl_get_interrupt_OSC16MRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_OSC16MRDY_Msk) >> OSCCTRL_INTFLAG_OSC16MRDY_Pos;
}

static inline void hri_oscctrl_clear_interrupt_OSC16MRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_OSC16MRDY_Msk;
}

static inline bool hri_oscctrl_get_interrupt_DFLLULPRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DFLLULPRDY_Msk) >> OSCCTRL_INTFLAG_DFLLULPRDY_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DFLLULPRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DFLLULPRDY_Msk;
}

static inline bool hri_oscctrl_get_interrupt_DFLLULPLOCK_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DFLLULPLOCK_Msk) >> OSCCTRL_INTFLAG_DFLLULPLOCK_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DFLLULPLOCK_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DFLLULPLOCK_Msk;
}

static inline bool hri_oscctrl_get_interrupt_DFLLULPNOLOCK_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DFLLULPNOLOCK_Msk) >> OSCCTRL_INTFLAG_DFLLULPNOLOCK_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DFLLULPNOLOCK_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DFLLULPNOLOCK_Msk;
}

static inline bool hri_oscctrl_get_interrupt_DPLLLCKR_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLCKR_Msk) >> OSCCTRL_INTFLAG_DPLLLCKR_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DPLLLCKR_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLCKR_Msk;
}

static inline bool hri_oscctrl_get_interrupt_DPLLLCKF_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLCKF_Msk) >> OSCCTRL_INTFLAG_DPLLLCKF_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DPLLLCKF_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLCKF_Msk;
}

static inline bool hri_oscctrl_get_interrupt_DPLLLTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLTO_Msk) >> OSCCTRL_INTFLAG_DPLLLTO_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DPLLLTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLTO_Msk;
}

static inline bool hri_oscctrl_get_interrupt_DPLLLDRTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLDRTO_Msk) >> OSCCTRL_INTFLAG_DPLLLDRTO_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DPLLLDRTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLDRTO_Msk;
}

static inline hri_oscctrl_intflag_reg_t hri_oscctrl_get_INTFLAG_reg(const void *const         hw,
                                                                    hri_oscctrl_intflag_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_oscctrl_intflag_reg_t hri_oscctrl_read_INTFLAG_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->INTFLAG.reg;
}

static inline void hri_oscctrl_clear_INTFLAG_reg(const void *const hw, hri_oscctrl_intflag_reg_t mask)
{
	((Oscctrl *)hw)->INTFLAG.reg = mask;
}

static inline void hri_oscctrl_set_INTEN_XOSCRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_XOSCRDY_Msk;
}

static inline bool hri_oscctrl_get_INTEN_XOSCRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_XOSCRDY_Msk) >> OSCCTRL_INTENSET_XOSCRDY_Pos;
}

static inline void hri_oscctrl_write_INTEN_XOSCRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_XOSCRDY_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_XOSCRDY_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_XOSCRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_XOSCRDY_Msk;
}

static inline void hri_oscctrl_set_INTEN_XOSCFAIL_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_XOSCFAIL_Msk;
}

static inline bool hri_oscctrl_get_INTEN_XOSCFAIL_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_XOSCFAIL_Msk) >> OSCCTRL_INTENSET_XOSCFAIL_Pos;
}

static inline void hri_oscctrl_write_INTEN_XOSCFAIL_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_XOSCFAIL_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_XOSCFAIL_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_XOSCFAIL_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_XOSCFAIL_Msk;
}

static inline void hri_oscctrl_set_INTEN_OSC16MRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_OSC16MRDY_Msk;
}

static inline bool hri_oscctrl_get_INTEN_OSC16MRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_OSC16MRDY_Msk) >> OSCCTRL_INTENSET_OSC16MRDY_Pos;
}

static inline void hri_oscctrl_write_INTEN_OSC16MRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_OSC16MRDY_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_OSC16MRDY_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_OSC16MRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_OSC16MRDY_Msk;
}

static inline void hri_oscctrl_set_INTEN_DFLLULPRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DFLLULPRDY_Msk;
}

static inline bool hri_oscctrl_get_INTEN_DFLLULPRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DFLLULPRDY_Msk) >> OSCCTRL_INTENSET_DFLLULPRDY_Pos;
}

static inline void hri_oscctrl_write_INTEN_DFLLULPRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DFLLULPRDY_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DFLLULPRDY_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_DFLLULPRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DFLLULPRDY_Msk;
}

static inline void hri_oscctrl_set_INTEN_DFLLULPLOCK_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DFLLULPLOCK_Msk;
}

static inline bool hri_oscctrl_get_INTEN_DFLLULPLOCK_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DFLLULPLOCK_Msk) >> OSCCTRL_INTENSET_DFLLULPLOCK_Pos;
}

static inline void hri_oscctrl_write_INTEN_DFLLULPLOCK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DFLLULPLOCK_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DFLLULPLOCK_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_DFLLULPLOCK_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DFLLULPLOCK_Msk;
}

static inline void hri_oscctrl_set_INTEN_DFLLULPNOLOCK_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DFLLULPNOLOCK_Msk;
}

static inline bool hri_oscctrl_get_INTEN_DFLLULPNOLOCK_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DFLLULPNOLOCK_Msk) >> OSCCTRL_INTENSET_DFLLULPNOLOCK_Pos;
}

static inline void hri_oscctrl_write_INTEN_DFLLULPNOLOCK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DFLLULPNOLOCK_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DFLLULPNOLOCK_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_DFLLULPNOLOCK_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DFLLULPNOLOCK_Msk;
}

static inline void hri_oscctrl_set_INTEN_DPLLLCKR_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLCKR_Msk;
}

static inline bool hri_oscctrl_get_INTEN_DPLLLCKR_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DPLLLCKR_Msk) >> OSCCTRL_INTENSET_DPLLLCKR_Pos;
}

static inline void hri_oscctrl_write_INTEN_DPLLLCKR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLCKR_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLCKR_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_DPLLLCKR_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLCKR_Msk;
}

static inline void hri_oscctrl_set_INTEN_DPLLLCKF_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLCKF_Msk;
}

static inline bool hri_oscctrl_get_INTEN_DPLLLCKF_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DPLLLCKF_Msk) >> OSCCTRL_INTENSET_DPLLLCKF_Pos;
}

static inline void hri_oscctrl_write_INTEN_DPLLLCKF_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLCKF_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLCKF_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_DPLLLCKF_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLCKF_Msk;
}

static inline void hri_oscctrl_set_INTEN_DPLLLTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLTO_Msk;
}

static inline bool hri_oscctrl_get_INTEN_DPLLLTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DPLLLTO_Msk) >> OSCCTRL_INTENSET_DPLLLTO_Pos;
}

static inline void hri_oscctrl_write_INTEN_DPLLLTO_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLTO_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLTO_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_DPLLLTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLTO_Msk;
}

static inline void hri_oscctrl_set_INTEN_DPLLLDRTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLDRTO_Msk;
}

static inline bool hri_oscctrl_get_INTEN_DPLLLDRTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DPLLLDRTO_Msk) >> OSCCTRL_INTENSET_DPLLLDRTO_Pos;
}

static inline void hri_oscctrl_write_INTEN_DPLLLDRTO_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLDRTO_Msk;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLDRTO_Msk;
	}
}

static inline void hri_oscctrl_clear_INTEN_DPLLLDRTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLDRTO_Msk;
}

static inline void hri_oscctrl_set_INTEN_reg(const void *const hw, hri_oscctrl_intenset_reg_t mask)
{
	((Oscctrl *)hw)->INTENSET.reg = mask;
}

static inline hri_oscctrl_intenset_reg_t hri_oscctrl_get_INTEN_reg(const void *const          hw,
                                                                   hri_oscctrl_intenset_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_oscctrl_intenset_reg_t hri_oscctrl_read_INTEN_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->INTENSET.reg;
}

static inline void hri_oscctrl_write_INTEN_reg(const void *const hw, hri_oscctrl_intenset_reg_t data)
{
	((Oscctrl *)hw)->INTENSET.reg = data;
	((Oscctrl *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_oscctrl_clear_INTEN_reg(const void *const hw, hri_oscctrl_intenset_reg_t mask)
{
	((Oscctrl *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_oscctrl_get_STATUS_XOSCRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_XOSCRDY_Msk) >> OSCCTRL_STATUS_XOSCRDY_Pos;
}

static inline bool hri_oscctrl_get_STATUS_XOSCFAIL_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_XOSCFAIL_Msk) >> OSCCTRL_STATUS_XOSCFAIL_Pos;
}

static inline bool hri_oscctrl_get_STATUS_XOSCCKSW_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_XOSCCKSW_Msk) >> OSCCTRL_STATUS_XOSCCKSW_Pos;
}

static inline bool hri_oscctrl_get_STATUS_OSC16MRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_OSC16MRDY_Msk) >> OSCCTRL_STATUS_OSC16MRDY_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DFLLULPRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DFLLULPRDY_Msk) >> OSCCTRL_STATUS_DFLLULPRDY_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DFLLULPLOCK_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DFLLULPLOCK_Msk) >> OSCCTRL_STATUS_DFLLULPLOCK_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DFLLULPNOLOCK_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DFLLULPNOLOCK_Msk) >> OSCCTRL_STATUS_DFLLULPNOLOCK_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DPLLLCKR_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DPLLLCKR_Msk) >> OSCCTRL_STATUS_DPLLLCKR_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DPLLLCKF_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DPLLLCKF_Msk) >> OSCCTRL_STATUS_DPLLLCKF_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DPLLTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DPLLTO_Msk) >> OSCCTRL_STATUS_DPLLTO_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DPLLLDRTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DPLLLDRTO_Msk) >> OSCCTRL_STATUS_DPLLLDRTO_Pos;
}

static inline hri_oscctrl_status_reg_t hri_oscctrl_get_STATUS_reg(const void *const hw, hri_oscctrl_status_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_oscctrl_status_reg_t hri_oscctrl_read_STATUS_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->STATUS.reg;
}

static inline bool hri_oscctrl_get_DFLLULPSYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DFLLULPSYNCBUSY.reg & OSCCTRL_DFLLULPSYNCBUSY_ENABLE_Msk)
	       >> OSCCTRL_DFLLULPSYNCBUSY_ENABLE_Pos;
}

static inline bool hri_oscctrl_get_DFLLULPSYNCBUSY_TUNE_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DFLLULPSYNCBUSY.reg & OSCCTRL_DFLLULPSYNCBUSY_TUNE_Msk)
	       >> OSCCTRL_DFLLULPSYNCBUSY_TUNE_Pos;
}

static inline bool hri_oscctrl_get_DFLLULPSYNCBUSY_DELAY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DFLLULPSYNCBUSY.reg & OSCCTRL_DFLLULPSYNCBUSY_DELAY_Msk)
	       >> OSCCTRL_DFLLULPSYNCBUSY_DELAY_Pos;
}

static inline hri_oscctrl_dfllulpsyncbusy_reg_t
hri_oscctrl_get_DFLLULPSYNCBUSY_reg(const void *const hw, hri_oscctrl_dfllulpsyncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPSYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_oscctrl_dfllulpsyncbusy_reg_t hri_oscctrl_read_DFLLULPSYNCBUSY_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->DFLLULPSYNCBUSY.reg;
}

static inline bool hri_oscctrl_get_DPLLSYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DPLLSYNCBUSY.reg & OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk) >> OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos;
}

static inline bool hri_oscctrl_get_DPLLSYNCBUSY_DPLLRATIO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DPLLSYNCBUSY.reg & OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk)
	       >> OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos;
}

static inline bool hri_oscctrl_get_DPLLSYNCBUSY_DPLLPRESC_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DPLLSYNCBUSY.reg & OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Msk)
	       >> OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos;
}

static inline hri_oscctrl_dpllsyncbusy_reg_t hri_oscctrl_get_DPLLSYNCBUSY_reg(const void *const              hw,
                                                                              hri_oscctrl_dpllsyncbusy_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLSYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_oscctrl_dpllsyncbusy_reg_t hri_oscctrl_read_DPLLSYNCBUSY_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->DPLLSYNCBUSY.reg;
}

static inline bool hri_oscctrl_get_DPLLSTATUS_LOCK_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DPLLSTATUS.reg & OSCCTRL_DPLLSTATUS_LOCK_Msk) >> OSCCTRL_DPLLSTATUS_LOCK_Pos;
}

static inline bool hri_oscctrl_get_DPLLSTATUS_CLKRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DPLLSTATUS.reg & OSCCTRL_DPLLSTATUS_CLKRDY_Msk) >> OSCCTRL_DPLLSTATUS_CLKRDY_Pos;
}

static inline hri_oscctrl_dpllstatus_reg_t hri_oscctrl_get_DPLLSTATUS_reg(const void *const            hw,
                                                                          hri_oscctrl_dpllstatus_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLSTATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_oscctrl_dpllstatus_reg_t hri_oscctrl_read_DPLLSTATUS_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->DPLLSTATUS.reg;
}

static inline void hri_oscctrl_set_EVCTRL_CFDEO_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg |= OSCCTRL_EVCTRL_CFDEO_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_EVCTRL_CFDEO_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->EVCTRL.reg;
	tmp = (tmp & OSCCTRL_EVCTRL_CFDEO_Msk) >> OSCCTRL_EVCTRL_CFDEO_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_EVCTRL_CFDEO_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->EVCTRL.reg;
	tmp &= ~OSCCTRL_EVCTRL_CFDEO_Msk;
	tmp |= value << OSCCTRL_EVCTRL_CFDEO_Pos;
	((Oscctrl *)hw)->EVCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_EVCTRL_CFDEO_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg &= ~OSCCTRL_EVCTRL_CFDEO_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_EVCTRL_CFDEO_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg ^= OSCCTRL_EVCTRL_CFDEO_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_EVCTRL_TUNEEI_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg |= OSCCTRL_EVCTRL_TUNEEI_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_EVCTRL_TUNEEI_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->EVCTRL.reg;
	tmp = (tmp & OSCCTRL_EVCTRL_TUNEEI_Msk) >> OSCCTRL_EVCTRL_TUNEEI_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_EVCTRL_TUNEEI_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->EVCTRL.reg;
	tmp &= ~OSCCTRL_EVCTRL_TUNEEI_Msk;
	tmp |= value << OSCCTRL_EVCTRL_TUNEEI_Pos;
	((Oscctrl *)hw)->EVCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_EVCTRL_TUNEEI_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg &= ~OSCCTRL_EVCTRL_TUNEEI_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_EVCTRL_TUNEEI_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg ^= OSCCTRL_EVCTRL_TUNEEI_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_EVCTRL_TUNEINV_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg |= OSCCTRL_EVCTRL_TUNEINV_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_EVCTRL_TUNEINV_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->EVCTRL.reg;
	tmp = (tmp & OSCCTRL_EVCTRL_TUNEINV_Msk) >> OSCCTRL_EVCTRL_TUNEINV_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_EVCTRL_TUNEINV_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->EVCTRL.reg;
	tmp &= ~OSCCTRL_EVCTRL_TUNEINV_Msk;
	tmp |= value << OSCCTRL_EVCTRL_TUNEINV_Pos;
	((Oscctrl *)hw)->EVCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_EVCTRL_TUNEINV_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg &= ~OSCCTRL_EVCTRL_TUNEINV_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_EVCTRL_TUNEINV_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg ^= OSCCTRL_EVCTRL_TUNEINV_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_EVCTRL_reg(const void *const hw, hri_oscctrl_evctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_evctrl_reg_t hri_oscctrl_get_EVCTRL_reg(const void *const hw, hri_oscctrl_evctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_EVCTRL_reg(const void *const hw, hri_oscctrl_evctrl_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_EVCTRL_reg(const void *const hw, hri_oscctrl_evctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_EVCTRL_reg(const void *const hw, hri_oscctrl_evctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_evctrl_reg_t hri_oscctrl_read_EVCTRL_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->EVCTRL.reg;
}

static inline void hri_oscctrl_set_XOSCCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_ENABLE_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_ENABLE_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_ENABLE_Msk) >> OSCCTRL_XOSCCTRL_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_ENABLE_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_ENABLE_Msk;
	tmp |= value << OSCCTRL_XOSCCTRL_ENABLE_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_ENABLE_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_ENABLE_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_XTALEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_XTALEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_XTALEN_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_XTALEN_Msk) >> OSCCTRL_XOSCCTRL_XTALEN_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_XTALEN_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_XTALEN_Msk;
	tmp |= value << OSCCTRL_XOSCCTRL_XTALEN_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_XTALEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_XTALEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_XTALEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_XTALEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_CFDEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_CFDEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_CFDEN_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_CFDEN_Msk) >> OSCCTRL_XOSCCTRL_CFDEN_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_CFDEN_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_CFDEN_Msk;
	tmp |= value << OSCCTRL_XOSCCTRL_CFDEN_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_CFDEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_CFDEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_CFDEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_CFDEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_SWBEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_SWBEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_SWBEN_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_SWBEN_Msk) >> OSCCTRL_XOSCCTRL_SWBEN_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_SWBEN_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_SWBEN_Msk;
	tmp |= value << OSCCTRL_XOSCCTRL_SWBEN_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_SWBEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_SWBEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_SWBEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_SWBEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_RUNSTDBY_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_RUNSTDBY_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_RUNSTDBY_Msk) >> OSCCTRL_XOSCCTRL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_RUNSTDBY_Msk;
	tmp |= value << OSCCTRL_XOSCCTRL_RUNSTDBY_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_RUNSTDBY_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_RUNSTDBY_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_ONDEMAND_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_ONDEMAND_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_ONDEMAND_Msk) >> OSCCTRL_XOSCCTRL_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_ONDEMAND_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_ONDEMAND_Msk;
	tmp |= value << OSCCTRL_XOSCCTRL_ONDEMAND_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_ONDEMAND_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_ONDEMAND_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_AMPGC_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_AMPGC_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_AMPGC_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_AMPGC_Msk) >> OSCCTRL_XOSCCTRL_AMPGC_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_AMPGC_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_AMPGC_Msk;
	tmp |= value << OSCCTRL_XOSCCTRL_AMPGC_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_AMPGC_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_AMPGC_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_AMPGC_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_AMPGC_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_GAIN_bf(const void *const hw, hri_oscctrl_xoscctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_GAIN(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_xoscctrl_reg_t hri_oscctrl_get_XOSCCTRL_GAIN_bf(const void *const          hw,
                                                                          hri_oscctrl_xoscctrl_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_GAIN(mask)) >> OSCCTRL_XOSCCTRL_GAIN_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_GAIN_bf(const void *const hw, hri_oscctrl_xoscctrl_reg_t data)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_GAIN_Msk;
	tmp |= OSCCTRL_XOSCCTRL_GAIN(data);
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_GAIN_bf(const void *const hw, hri_oscctrl_xoscctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_GAIN(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_GAIN_bf(const void *const hw, hri_oscctrl_xoscctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_GAIN(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_xoscctrl_reg_t hri_oscctrl_read_XOSCCTRL_GAIN_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_GAIN_Msk) >> OSCCTRL_XOSCCTRL_GAIN_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_XOSCCTRL_STARTUP_bf(const void *const hw, hri_oscctrl_xoscctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_STARTUP(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_xoscctrl_reg_t hri_oscctrl_get_XOSCCTRL_STARTUP_bf(const void *const          hw,
                                                                             hri_oscctrl_xoscctrl_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_STARTUP(mask)) >> OSCCTRL_XOSCCTRL_STARTUP_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_STARTUP_bf(const void *const hw, hri_oscctrl_xoscctrl_reg_t data)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_STARTUP_Msk;
	tmp |= OSCCTRL_XOSCCTRL_STARTUP(data);
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_STARTUP_bf(const void *const hw, hri_oscctrl_xoscctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_STARTUP(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_STARTUP_bf(const void *const hw, hri_oscctrl_xoscctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_STARTUP(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_xoscctrl_reg_t hri_oscctrl_read_XOSCCTRL_STARTUP_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_STARTUP_Msk) >> OSCCTRL_XOSCCTRL_STARTUP_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_XOSCCTRL_reg(const void *const hw, hri_oscctrl_xoscctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_xoscctrl_reg_t hri_oscctrl_get_XOSCCTRL_reg(const void *const          hw,
                                                                      hri_oscctrl_xoscctrl_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_reg(const void *const hw, hri_oscctrl_xoscctrl_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_reg(const void *const hw, hri_oscctrl_xoscctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_reg(const void *const hw, hri_oscctrl_xoscctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_xoscctrl_reg_t hri_oscctrl_read_XOSCCTRL_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->XOSCCTRL.reg;
}

static inline void hri_oscctrl_set_CFDPRESC_CFDPRESC_bf(const void *const hw, hri_oscctrl_cfdpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CFDPRESC.reg |= OSCCTRL_CFDPRESC_CFDPRESC(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cfdpresc_reg_t hri_oscctrl_get_CFDPRESC_CFDPRESC_bf(const void *const          hw,
                                                                              hri_oscctrl_cfdpresc_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->CFDPRESC.reg;
	tmp = (tmp & OSCCTRL_CFDPRESC_CFDPRESC(mask)) >> OSCCTRL_CFDPRESC_CFDPRESC_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_CFDPRESC_CFDPRESC_bf(const void *const hw, hri_oscctrl_cfdpresc_reg_t data)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->CFDPRESC.reg;
	tmp &= ~OSCCTRL_CFDPRESC_CFDPRESC_Msk;
	tmp |= OSCCTRL_CFDPRESC_CFDPRESC(data);
	((Oscctrl *)hw)->CFDPRESC.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_CFDPRESC_CFDPRESC_bf(const void *const hw, hri_oscctrl_cfdpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CFDPRESC.reg &= ~OSCCTRL_CFDPRESC_CFDPRESC(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_CFDPRESC_CFDPRESC_bf(const void *const hw, hri_oscctrl_cfdpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CFDPRESC.reg ^= OSCCTRL_CFDPRESC_CFDPRESC(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cfdpresc_reg_t hri_oscctrl_read_CFDPRESC_CFDPRESC_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->CFDPRESC.reg;
	tmp = (tmp & OSCCTRL_CFDPRESC_CFDPRESC_Msk) >> OSCCTRL_CFDPRESC_CFDPRESC_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_CFDPRESC_reg(const void *const hw, hri_oscctrl_cfdpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CFDPRESC.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cfdpresc_reg_t hri_oscctrl_get_CFDPRESC_reg(const void *const          hw,
                                                                      hri_oscctrl_cfdpresc_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->CFDPRESC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_CFDPRESC_reg(const void *const hw, hri_oscctrl_cfdpresc_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CFDPRESC.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_CFDPRESC_reg(const void *const hw, hri_oscctrl_cfdpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CFDPRESC.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_CFDPRESC_reg(const void *const hw, hri_oscctrl_cfdpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CFDPRESC.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cfdpresc_reg_t hri_oscctrl_read_CFDPRESC_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->CFDPRESC.reg;
}

static inline void hri_oscctrl_set_OSC16MCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg |= OSCCTRL_OSC16MCTRL_ENABLE_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_OSC16MCTRL_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp = (tmp & OSCCTRL_OSC16MCTRL_ENABLE_Msk) >> OSCCTRL_OSC16MCTRL_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_OSC16MCTRL_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp &= ~OSCCTRL_OSC16MCTRL_ENABLE_Msk;
	tmp |= value << OSCCTRL_OSC16MCTRL_ENABLE_Pos;
	((Oscctrl *)hw)->OSC16MCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC16MCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg &= ~OSCCTRL_OSC16MCTRL_ENABLE_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC16MCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg ^= OSCCTRL_OSC16MCTRL_ENABLE_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_OSC16MCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg |= OSCCTRL_OSC16MCTRL_RUNSTDBY_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_OSC16MCTRL_RUNSTDBY_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp = (tmp & OSCCTRL_OSC16MCTRL_RUNSTDBY_Msk) >> OSCCTRL_OSC16MCTRL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_OSC16MCTRL_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp &= ~OSCCTRL_OSC16MCTRL_RUNSTDBY_Msk;
	tmp |= value << OSCCTRL_OSC16MCTRL_RUNSTDBY_Pos;
	((Oscctrl *)hw)->OSC16MCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC16MCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg &= ~OSCCTRL_OSC16MCTRL_RUNSTDBY_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC16MCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg ^= OSCCTRL_OSC16MCTRL_RUNSTDBY_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_OSC16MCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg |= OSCCTRL_OSC16MCTRL_ONDEMAND_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_OSC16MCTRL_ONDEMAND_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp = (tmp & OSCCTRL_OSC16MCTRL_ONDEMAND_Msk) >> OSCCTRL_OSC16MCTRL_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_OSC16MCTRL_ONDEMAND_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp &= ~OSCCTRL_OSC16MCTRL_ONDEMAND_Msk;
	tmp |= value << OSCCTRL_OSC16MCTRL_ONDEMAND_Pos;
	((Oscctrl *)hw)->OSC16MCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC16MCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg &= ~OSCCTRL_OSC16MCTRL_ONDEMAND_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC16MCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg ^= OSCCTRL_OSC16MCTRL_ONDEMAND_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_OSC16MCTRL_FSEL_bf(const void *const hw, hri_oscctrl_osc16mctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg |= OSCCTRL_OSC16MCTRL_FSEL(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc16mctrl_reg_t hri_oscctrl_get_OSC16MCTRL_FSEL_bf(const void *const            hw,
                                                                              hri_oscctrl_osc16mctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp = (tmp & OSCCTRL_OSC16MCTRL_FSEL(mask)) >> OSCCTRL_OSC16MCTRL_FSEL_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_OSC16MCTRL_FSEL_bf(const void *const hw, hri_oscctrl_osc16mctrl_reg_t data)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp &= ~OSCCTRL_OSC16MCTRL_FSEL_Msk;
	tmp |= OSCCTRL_OSC16MCTRL_FSEL(data);
	((Oscctrl *)hw)->OSC16MCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC16MCTRL_FSEL_bf(const void *const hw, hri_oscctrl_osc16mctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg &= ~OSCCTRL_OSC16MCTRL_FSEL(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC16MCTRL_FSEL_bf(const void *const hw, hri_oscctrl_osc16mctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg ^= OSCCTRL_OSC16MCTRL_FSEL(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc16mctrl_reg_t hri_oscctrl_read_OSC16MCTRL_FSEL_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp = (tmp & OSCCTRL_OSC16MCTRL_FSEL_Msk) >> OSCCTRL_OSC16MCTRL_FSEL_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_OSC16MCTRL_reg(const void *const hw, hri_oscctrl_osc16mctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc16mctrl_reg_t hri_oscctrl_get_OSC16MCTRL_reg(const void *const            hw,
                                                                          hri_oscctrl_osc16mctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC16MCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_OSC16MCTRL_reg(const void *const hw, hri_oscctrl_osc16mctrl_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC16MCTRL_reg(const void *const hw, hri_oscctrl_osc16mctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC16MCTRL_reg(const void *const hw, hri_oscctrl_osc16mctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC16MCTRL.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc16mctrl_reg_t hri_oscctrl_read_OSC16MCTRL_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->OSC16MCTRL.reg;
}

static inline void hri_oscctrl_set_DFLLULPCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg |= OSCCTRL_DFLLULPCTRL_ENABLE_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DFLLULPCTRL_ENABLE_bit(const void *const hw)
{
	uint16_t tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp = (tmp & OSCCTRL_DFLLULPCTRL_ENABLE_Msk) >> OSCCTRL_DFLLULPCTRL_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DFLLULPCTRL_ENABLE_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp &= ~OSCCTRL_DFLLULPCTRL_ENABLE_Msk;
	tmp |= value << OSCCTRL_DFLLULPCTRL_ENABLE_Pos;
	((Oscctrl *)hw)->DFLLULPCTRL.reg = tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg &= ~OSCCTRL_DFLLULPCTRL_ENABLE_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg ^= OSCCTRL_DFLLULPCTRL_ENABLE_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DFLLULPCTRL_BINSE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg |= OSCCTRL_DFLLULPCTRL_BINSE_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DFLLULPCTRL_BINSE_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp = (tmp & OSCCTRL_DFLLULPCTRL_BINSE_Msk) >> OSCCTRL_DFLLULPCTRL_BINSE_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DFLLULPCTRL_BINSE_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp &= ~OSCCTRL_DFLLULPCTRL_BINSE_Msk;
	tmp |= value << OSCCTRL_DFLLULPCTRL_BINSE_Pos;
	((Oscctrl *)hw)->DFLLULPCTRL.reg = tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPCTRL_BINSE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg &= ~OSCCTRL_DFLLULPCTRL_BINSE_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPCTRL_BINSE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg ^= OSCCTRL_DFLLULPCTRL_BINSE_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DFLLULPCTRL_SAFE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg |= OSCCTRL_DFLLULPCTRL_SAFE_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DFLLULPCTRL_SAFE_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp = (tmp & OSCCTRL_DFLLULPCTRL_SAFE_Msk) >> OSCCTRL_DFLLULPCTRL_SAFE_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DFLLULPCTRL_SAFE_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp &= ~OSCCTRL_DFLLULPCTRL_SAFE_Msk;
	tmp |= value << OSCCTRL_DFLLULPCTRL_SAFE_Pos;
	((Oscctrl *)hw)->DFLLULPCTRL.reg = tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPCTRL_SAFE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg &= ~OSCCTRL_DFLLULPCTRL_SAFE_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPCTRL_SAFE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg ^= OSCCTRL_DFLLULPCTRL_SAFE_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DFLLULPCTRL_DITHER_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg |= OSCCTRL_DFLLULPCTRL_DITHER_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DFLLULPCTRL_DITHER_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp = (tmp & OSCCTRL_DFLLULPCTRL_DITHER_Msk) >> OSCCTRL_DFLLULPCTRL_DITHER_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DFLLULPCTRL_DITHER_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp &= ~OSCCTRL_DFLLULPCTRL_DITHER_Msk;
	tmp |= value << OSCCTRL_DFLLULPCTRL_DITHER_Pos;
	((Oscctrl *)hw)->DFLLULPCTRL.reg = tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPCTRL_DITHER_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg &= ~OSCCTRL_DFLLULPCTRL_DITHER_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPCTRL_DITHER_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg ^= OSCCTRL_DFLLULPCTRL_DITHER_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DFLLULPCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg |= OSCCTRL_DFLLULPCTRL_RUNSTDBY_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DFLLULPCTRL_RUNSTDBY_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp = (tmp & OSCCTRL_DFLLULPCTRL_RUNSTDBY_Msk) >> OSCCTRL_DFLLULPCTRL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DFLLULPCTRL_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp &= ~OSCCTRL_DFLLULPCTRL_RUNSTDBY_Msk;
	tmp |= value << OSCCTRL_DFLLULPCTRL_RUNSTDBY_Pos;
	((Oscctrl *)hw)->DFLLULPCTRL.reg = tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg &= ~OSCCTRL_DFLLULPCTRL_RUNSTDBY_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg ^= OSCCTRL_DFLLULPCTRL_RUNSTDBY_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DFLLULPCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg |= OSCCTRL_DFLLULPCTRL_ONDEMAND_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DFLLULPCTRL_ONDEMAND_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp = (tmp & OSCCTRL_DFLLULPCTRL_ONDEMAND_Msk) >> OSCCTRL_DFLLULPCTRL_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DFLLULPCTRL_ONDEMAND_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp &= ~OSCCTRL_DFLLULPCTRL_ONDEMAND_Msk;
	tmp |= value << OSCCTRL_DFLLULPCTRL_ONDEMAND_Pos;
	((Oscctrl *)hw)->DFLLULPCTRL.reg = tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg &= ~OSCCTRL_DFLLULPCTRL_ONDEMAND_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg ^= OSCCTRL_DFLLULPCTRL_ONDEMAND_Msk;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DFLLULPCTRL_DIV_bf(const void *const hw, hri_oscctrl_dfllulpctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg |= OSCCTRL_DFLLULPCTRL_DIV(mask);
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpctrl_reg_t hri_oscctrl_get_DFLLULPCTRL_DIV_bf(const void *const             hw,
                                                                               hri_oscctrl_dfllulpctrl_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp = (tmp & OSCCTRL_DFLLULPCTRL_DIV(mask)) >> OSCCTRL_DFLLULPCTRL_DIV_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPCTRL_DIV_bf(const void *const hw, hri_oscctrl_dfllulpctrl_reg_t data)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp &= ~OSCCTRL_DFLLULPCTRL_DIV_Msk;
	tmp |= OSCCTRL_DFLLULPCTRL_DIV(data);
	((Oscctrl *)hw)->DFLLULPCTRL.reg = tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPCTRL_DIV_bf(const void *const hw, hri_oscctrl_dfllulpctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg &= ~OSCCTRL_DFLLULPCTRL_DIV(mask);
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPCTRL_DIV_bf(const void *const hw, hri_oscctrl_dfllulpctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg ^= OSCCTRL_DFLLULPCTRL_DIV(mask);
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpctrl_reg_t hri_oscctrl_read_DFLLULPCTRL_DIV_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp = (tmp & OSCCTRL_DFLLULPCTRL_DIV_Msk) >> OSCCTRL_DFLLULPCTRL_DIV_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DFLLULPCTRL_reg(const void *const hw, hri_oscctrl_dfllulpctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg |= mask;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpctrl_reg_t hri_oscctrl_get_DFLLULPCTRL_reg(const void *const             hw,
                                                                            hri_oscctrl_dfllulpctrl_reg_t mask)
{
	uint16_t tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	tmp = ((Oscctrl *)hw)->DFLLULPCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPCTRL_reg(const void *const hw, hri_oscctrl_dfllulpctrl_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg = data;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPCTRL_reg(const void *const hw, hri_oscctrl_dfllulpctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg &= ~mask;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPCTRL_reg(const void *const hw, hri_oscctrl_dfllulpctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPCTRL.reg ^= mask;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpctrl_reg_t hri_oscctrl_read_DFLLULPCTRL_reg(const void *const hw)
{
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_ENABLE);
	return ((Oscctrl *)hw)->DFLLULPCTRL.reg;
}

static inline void hri_oscctrl_set_DFLLULPDITHER_STEP_bf(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg |= OSCCTRL_DFLLULPDITHER_STEP(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdither_reg_t
hri_oscctrl_get_DFLLULPDITHER_STEP_bf(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPDITHER.reg;
	tmp = (tmp & OSCCTRL_DFLLULPDITHER_STEP(mask)) >> OSCCTRL_DFLLULPDITHER_STEP_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPDITHER_STEP_bf(const void *const hw, hri_oscctrl_dfllulpdither_reg_t data)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPDITHER.reg;
	tmp &= ~OSCCTRL_DFLLULPDITHER_STEP_Msk;
	tmp |= OSCCTRL_DFLLULPDITHER_STEP(data);
	((Oscctrl *)hw)->DFLLULPDITHER.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPDITHER_STEP_bf(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg &= ~OSCCTRL_DFLLULPDITHER_STEP(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPDITHER_STEP_bf(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg ^= OSCCTRL_DFLLULPDITHER_STEP(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdither_reg_t hri_oscctrl_read_DFLLULPDITHER_STEP_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPDITHER.reg;
	tmp = (tmp & OSCCTRL_DFLLULPDITHER_STEP_Msk) >> OSCCTRL_DFLLULPDITHER_STEP_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DFLLULPDITHER_PER_bf(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg |= OSCCTRL_DFLLULPDITHER_PER(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdither_reg_t hri_oscctrl_get_DFLLULPDITHER_PER_bf(const void *const               hw,
                                                                                   hri_oscctrl_dfllulpdither_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPDITHER.reg;
	tmp = (tmp & OSCCTRL_DFLLULPDITHER_PER(mask)) >> OSCCTRL_DFLLULPDITHER_PER_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPDITHER_PER_bf(const void *const hw, hri_oscctrl_dfllulpdither_reg_t data)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPDITHER.reg;
	tmp &= ~OSCCTRL_DFLLULPDITHER_PER_Msk;
	tmp |= OSCCTRL_DFLLULPDITHER_PER(data);
	((Oscctrl *)hw)->DFLLULPDITHER.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPDITHER_PER_bf(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg &= ~OSCCTRL_DFLLULPDITHER_PER(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPDITHER_PER_bf(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg ^= OSCCTRL_DFLLULPDITHER_PER(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdither_reg_t hri_oscctrl_read_DFLLULPDITHER_PER_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPDITHER.reg;
	tmp = (tmp & OSCCTRL_DFLLULPDITHER_PER_Msk) >> OSCCTRL_DFLLULPDITHER_PER_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DFLLULPDITHER_reg(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdither_reg_t hri_oscctrl_get_DFLLULPDITHER_reg(const void *const               hw,
                                                                                hri_oscctrl_dfllulpdither_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPDITHER.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPDITHER_reg(const void *const hw, hri_oscctrl_dfllulpdither_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPDITHER_reg(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPDITHER_reg(const void *const hw, hri_oscctrl_dfllulpdither_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDITHER.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdither_reg_t hri_oscctrl_read_DFLLULPDITHER_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->DFLLULPDITHER.reg;
}

static inline void hri_oscctrl_set_DFLLULPRREQ_RREQ_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRREQ.reg |= OSCCTRL_DFLLULPRREQ_RREQ_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DFLLULPRREQ_RREQ_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPRREQ.reg;
	tmp = (tmp & OSCCTRL_DFLLULPRREQ_RREQ_Msk) >> OSCCTRL_DFLLULPRREQ_RREQ_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DFLLULPRREQ_RREQ_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPRREQ.reg;
	tmp &= ~OSCCTRL_DFLLULPRREQ_RREQ_Msk;
	tmp |= value << OSCCTRL_DFLLULPRREQ_RREQ_Pos;
	((Oscctrl *)hw)->DFLLULPRREQ.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPRREQ_RREQ_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRREQ.reg &= ~OSCCTRL_DFLLULPRREQ_RREQ_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPRREQ_RREQ_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRREQ.reg ^= OSCCTRL_DFLLULPRREQ_RREQ_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DFLLULPRREQ_reg(const void *const hw, hri_oscctrl_dfllulprreq_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRREQ.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulprreq_reg_t hri_oscctrl_get_DFLLULPRREQ_reg(const void *const             hw,
                                                                            hri_oscctrl_dfllulprreq_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPRREQ.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPRREQ_reg(const void *const hw, hri_oscctrl_dfllulprreq_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRREQ.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPRREQ_reg(const void *const hw, hri_oscctrl_dfllulprreq_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRREQ.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPRREQ_reg(const void *const hw, hri_oscctrl_dfllulprreq_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRREQ.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulprreq_reg_t hri_oscctrl_read_DFLLULPRREQ_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->DFLLULPRREQ.reg;
}

static inline void hri_oscctrl_set_DFLLULPDLY_DELAY_bf(const void *const hw, hri_oscctrl_dfllulpdly_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDLY.reg |= OSCCTRL_DFLLULPDLY_DELAY(mask);
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdly_reg_t hri_oscctrl_get_DFLLULPDLY_DELAY_bf(const void *const            hw,
                                                                               hri_oscctrl_dfllulpdly_reg_t mask)
{
	uint32_t tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	tmp = ((Oscctrl *)hw)->DFLLULPDLY.reg;
	tmp = (tmp & OSCCTRL_DFLLULPDLY_DELAY(mask)) >> OSCCTRL_DFLLULPDLY_DELAY_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPDLY_DELAY_bf(const void *const hw, hri_oscctrl_dfllulpdly_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPDLY.reg;
	tmp &= ~OSCCTRL_DFLLULPDLY_DELAY_Msk;
	tmp |= OSCCTRL_DFLLULPDLY_DELAY(data);
	((Oscctrl *)hw)->DFLLULPDLY.reg = tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPDLY_DELAY_bf(const void *const hw, hri_oscctrl_dfllulpdly_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDLY.reg &= ~OSCCTRL_DFLLULPDLY_DELAY(mask);
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPDLY_DELAY_bf(const void *const hw, hri_oscctrl_dfllulpdly_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDLY.reg ^= OSCCTRL_DFLLULPDLY_DELAY(mask);
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdly_reg_t hri_oscctrl_read_DFLLULPDLY_DELAY_bf(const void *const hw)
{
	uint32_t tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	tmp = ((Oscctrl *)hw)->DFLLULPDLY.reg;
	tmp = (tmp & OSCCTRL_DFLLULPDLY_DELAY_Msk) >> OSCCTRL_DFLLULPDLY_DELAY_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DFLLULPDLY_reg(const void *const hw, hri_oscctrl_dfllulpdly_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDLY.reg |= mask;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdly_reg_t hri_oscctrl_get_DFLLULPDLY_reg(const void *const            hw,
                                                                          hri_oscctrl_dfllulpdly_reg_t mask)
{
	uint32_t tmp;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	tmp = ((Oscctrl *)hw)->DFLLULPDLY.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPDLY_reg(const void *const hw, hri_oscctrl_dfllulpdly_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDLY.reg = data;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPDLY_reg(const void *const hw, hri_oscctrl_dfllulpdly_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDLY.reg &= ~mask;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPDLY_reg(const void *const hw, hri_oscctrl_dfllulpdly_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPDLY.reg ^= mask;
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpdly_reg_t hri_oscctrl_read_DFLLULPDLY_reg(const void *const hw)
{
	hri_oscctrl_dfllulpsyncbusy_wait_for_sync(hw, OSCCTRL_DFLLULPSYNCBUSY_DELAY);
	return ((Oscctrl *)hw)->DFLLULPDLY.reg;
}

static inline void hri_oscctrl_set_DFLLULPRATIO_RATIO_bf(const void *const hw, hri_oscctrl_dfllulpratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRATIO.reg |= OSCCTRL_DFLLULPRATIO_RATIO(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpratio_reg_t hri_oscctrl_get_DFLLULPRATIO_RATIO_bf(const void *const              hw,
                                                                                   hri_oscctrl_dfllulpratio_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPRATIO.reg;
	tmp = (tmp & OSCCTRL_DFLLULPRATIO_RATIO(mask)) >> OSCCTRL_DFLLULPRATIO_RATIO_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPRATIO_RATIO_bf(const void *const hw, hri_oscctrl_dfllulpratio_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DFLLULPRATIO.reg;
	tmp &= ~OSCCTRL_DFLLULPRATIO_RATIO_Msk;
	tmp |= OSCCTRL_DFLLULPRATIO_RATIO(data);
	((Oscctrl *)hw)->DFLLULPRATIO.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPRATIO_RATIO_bf(const void *const hw, hri_oscctrl_dfllulpratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRATIO.reg &= ~OSCCTRL_DFLLULPRATIO_RATIO(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPRATIO_RATIO_bf(const void *const hw, hri_oscctrl_dfllulpratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRATIO.reg ^= OSCCTRL_DFLLULPRATIO_RATIO(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpratio_reg_t hri_oscctrl_read_DFLLULPRATIO_RATIO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPRATIO.reg;
	tmp = (tmp & OSCCTRL_DFLLULPRATIO_RATIO_Msk) >> OSCCTRL_DFLLULPRATIO_RATIO_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DFLLULPRATIO_reg(const void *const hw, hri_oscctrl_dfllulpratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRATIO.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpratio_reg_t hri_oscctrl_get_DFLLULPRATIO_reg(const void *const              hw,
                                                                              hri_oscctrl_dfllulpratio_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DFLLULPRATIO.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_DFLLULPRATIO_reg(const void *const hw, hri_oscctrl_dfllulpratio_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRATIO.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DFLLULPRATIO_reg(const void *const hw, hri_oscctrl_dfllulpratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRATIO.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DFLLULPRATIO_reg(const void *const hw, hri_oscctrl_dfllulpratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DFLLULPRATIO.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dfllulpratio_reg_t hri_oscctrl_read_DFLLULPRATIO_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->DFLLULPRATIO.reg;
}

static inline void hri_oscctrl_set_DPLLCTRLA_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg |= OSCCTRL_DPLLCTRLA_ENABLE_Msk;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLA_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLA_ENABLE_Msk) >> OSCCTRL_DPLLCTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp &= ~OSCCTRL_DPLLCTRLA_ENABLE_Msk;
	tmp |= value << OSCCTRL_DPLLCTRLA_ENABLE_Pos;
	((Oscctrl *)hw)->DPLLCTRLA.reg = tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLA_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg &= ~OSCCTRL_DPLLCTRLA_ENABLE_Msk;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLA_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg ^= OSCCTRL_DPLLCTRLA_ENABLE_Msk;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLA_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg |= OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLA_RUNSTDBY_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk) >> OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLA_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp &= ~OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk;
	tmp |= value << OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos;
	((Oscctrl *)hw)->DPLLCTRLA.reg = tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLA_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg &= ~OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLA_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg ^= OSCCTRL_DPLLCTRLA_RUNSTDBY_Msk;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLA_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg |= OSCCTRL_DPLLCTRLA_ONDEMAND_Msk;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLA_ONDEMAND_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLA_ONDEMAND_Msk) >> OSCCTRL_DPLLCTRLA_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLA_ONDEMAND_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp &= ~OSCCTRL_DPLLCTRLA_ONDEMAND_Msk;
	tmp |= value << OSCCTRL_DPLLCTRLA_ONDEMAND_Pos;
	((Oscctrl *)hw)->DPLLCTRLA.reg = tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLA_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg &= ~OSCCTRL_DPLLCTRLA_ONDEMAND_Msk;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLA_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg ^= OSCCTRL_DPLLCTRLA_ONDEMAND_Msk;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLA_reg(const void *const hw, hri_oscctrl_dpllctrla_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg |= mask;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrla_reg_t hri_oscctrl_get_DPLLCTRLA_reg(const void *const           hw,
                                                                        hri_oscctrl_dpllctrla_reg_t mask)
{
	uint8_t tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLA_reg(const void *const hw, hri_oscctrl_dpllctrla_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg = data;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLA_reg(const void *const hw, hri_oscctrl_dpllctrla_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg &= ~mask;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLA_reg(const void *const hw, hri_oscctrl_dpllctrla_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg ^= mask;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrla_reg_t hri_oscctrl_read_DPLLCTRLA_reg(const void *const hw)
{
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	return ((Oscctrl *)hw)->DPLLCTRLA.reg;
}

static inline void hri_oscctrl_set_DPLLRATIO_LDR_bf(const void *const hw, hri_oscctrl_dpllratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg |= OSCCTRL_DPLLRATIO_LDR(mask);
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllratio_reg_t hri_oscctrl_get_DPLLRATIO_LDR_bf(const void *const           hw,
                                                                           hri_oscctrl_dpllratio_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLRATIO.reg;
	tmp = (tmp & OSCCTRL_DPLLRATIO_LDR(mask)) >> OSCCTRL_DPLLRATIO_LDR_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLRATIO_LDR_bf(const void *const hw, hri_oscctrl_dpllratio_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLRATIO.reg;
	tmp &= ~OSCCTRL_DPLLRATIO_LDR_Msk;
	tmp |= OSCCTRL_DPLLRATIO_LDR(data);
	((Oscctrl *)hw)->DPLLRATIO.reg = tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLRATIO_LDR_bf(const void *const hw, hri_oscctrl_dpllratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg &= ~OSCCTRL_DPLLRATIO_LDR(mask);
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLRATIO_LDR_bf(const void *const hw, hri_oscctrl_dpllratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg ^= OSCCTRL_DPLLRATIO_LDR(mask);
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllratio_reg_t hri_oscctrl_read_DPLLRATIO_LDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLRATIO.reg;
	tmp = (tmp & OSCCTRL_DPLLRATIO_LDR_Msk) >> OSCCTRL_DPLLRATIO_LDR_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DPLLRATIO_LDRFRAC_bf(const void *const hw, hri_oscctrl_dpllratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg |= OSCCTRL_DPLLRATIO_LDRFRAC(mask);
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllratio_reg_t hri_oscctrl_get_DPLLRATIO_LDRFRAC_bf(const void *const           hw,
                                                                               hri_oscctrl_dpllratio_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLRATIO.reg;
	tmp = (tmp & OSCCTRL_DPLLRATIO_LDRFRAC(mask)) >> OSCCTRL_DPLLRATIO_LDRFRAC_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLRATIO_LDRFRAC_bf(const void *const hw, hri_oscctrl_dpllratio_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLRATIO.reg;
	tmp &= ~OSCCTRL_DPLLRATIO_LDRFRAC_Msk;
	tmp |= OSCCTRL_DPLLRATIO_LDRFRAC(data);
	((Oscctrl *)hw)->DPLLRATIO.reg = tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLRATIO_LDRFRAC_bf(const void *const hw, hri_oscctrl_dpllratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg &= ~OSCCTRL_DPLLRATIO_LDRFRAC(mask);
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLRATIO_LDRFRAC_bf(const void *const hw, hri_oscctrl_dpllratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg ^= OSCCTRL_DPLLRATIO_LDRFRAC(mask);
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllratio_reg_t hri_oscctrl_read_DPLLRATIO_LDRFRAC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLRATIO.reg;
	tmp = (tmp & OSCCTRL_DPLLRATIO_LDRFRAC_Msk) >> OSCCTRL_DPLLRATIO_LDRFRAC_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DPLLRATIO_reg(const void *const hw, hri_oscctrl_dpllratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg |= mask;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllratio_reg_t hri_oscctrl_get_DPLLRATIO_reg(const void *const           hw,
                                                                        hri_oscctrl_dpllratio_reg_t mask)
{
	uint32_t tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	tmp = ((Oscctrl *)hw)->DPLLRATIO.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLRATIO_reg(const void *const hw, hri_oscctrl_dpllratio_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg = data;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLRATIO_reg(const void *const hw, hri_oscctrl_dpllratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg &= ~mask;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLRATIO_reg(const void *const hw, hri_oscctrl_dpllratio_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLRATIO.reg ^= mask;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllratio_reg_t hri_oscctrl_read_DPLLRATIO_reg(const void *const hw)
{
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	return ((Oscctrl *)hw)->DPLLRATIO.reg;
}

static inline void hri_oscctrl_set_DPLLCTRLB_LPEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_LPEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLB_LPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_LPEN_Msk) >> OSCCTRL_DPLLCTRLB_LPEN_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_LPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_LPEN_Msk;
	tmp |= value << OSCCTRL_DPLLCTRLB_LPEN_Pos;
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_LPEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_LPEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_LPEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_LPEN_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLB_WUF_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_WUF_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLB_WUF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_WUF_Msk) >> OSCCTRL_DPLLCTRLB_WUF_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_WUF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_WUF_Msk;
	tmp |= value << OSCCTRL_DPLLCTRLB_WUF_Pos;
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_WUF_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_WUF_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_WUF_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_WUF_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLB_LBYPASS_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_LBYPASS_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLB_LBYPASS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_LBYPASS_Msk) >> OSCCTRL_DPLLCTRLB_LBYPASS_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_LBYPASS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_LBYPASS_Msk;
	tmp |= value << OSCCTRL_DPLLCTRLB_LBYPASS_Pos;
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_LBYPASS_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_LBYPASS_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_LBYPASS_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_LBYPASS_Msk;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLB_FILTER_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_FILTER(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_get_DPLLCTRLB_FILTER_bf(const void *const           hw,
                                                                              hri_oscctrl_dpllctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_FILTER(mask)) >> OSCCTRL_DPLLCTRLB_FILTER_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_FILTER_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_FILTER_Msk;
	tmp |= OSCCTRL_DPLLCTRLB_FILTER(data);
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_FILTER_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_FILTER(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_FILTER_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_FILTER(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_read_DPLLCTRLB_FILTER_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_FILTER_Msk) >> OSCCTRL_DPLLCTRLB_FILTER_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DPLLCTRLB_REFCLK_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_REFCLK(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_get_DPLLCTRLB_REFCLK_bf(const void *const           hw,
                                                                              hri_oscctrl_dpllctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_REFCLK(mask)) >> OSCCTRL_DPLLCTRLB_REFCLK_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_REFCLK_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_REFCLK_Msk;
	tmp |= OSCCTRL_DPLLCTRLB_REFCLK(data);
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_REFCLK_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_REFCLK(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_REFCLK_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_REFCLK(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_read_DPLLCTRLB_REFCLK_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_REFCLK_Msk) >> OSCCTRL_DPLLCTRLB_REFCLK_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DPLLCTRLB_LTIME_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_LTIME(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_get_DPLLCTRLB_LTIME_bf(const void *const           hw,
                                                                             hri_oscctrl_dpllctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_LTIME(mask)) >> OSCCTRL_DPLLCTRLB_LTIME_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_LTIME_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_LTIME_Msk;
	tmp |= OSCCTRL_DPLLCTRLB_LTIME(data);
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_LTIME_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_LTIME(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_LTIME_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_LTIME(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_read_DPLLCTRLB_LTIME_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_LTIME_Msk) >> OSCCTRL_DPLLCTRLB_LTIME_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DPLLCTRLB_DIV_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_DIV(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_get_DPLLCTRLB_DIV_bf(const void *const           hw,
                                                                           hri_oscctrl_dpllctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_DIV(mask)) >> OSCCTRL_DPLLCTRLB_DIV_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_DIV_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_DIV_Msk;
	tmp |= OSCCTRL_DPLLCTRLB_DIV(data);
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_DIV_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_DIV(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_DIV_bf(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_DIV(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_read_DPLLCTRLB_DIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_DIV_Msk) >> OSCCTRL_DPLLCTRLB_DIV_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DPLLCTRLB_reg(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_get_DPLLCTRLB_reg(const void *const           hw,
                                                                        hri_oscctrl_dpllctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_reg(const void *const hw, hri_oscctrl_dpllctrlb_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_reg(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_reg(const void *const hw, hri_oscctrl_dpllctrlb_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllctrlb_reg_t hri_oscctrl_read_DPLLCTRLB_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->DPLLCTRLB.reg;
}

static inline void hri_oscctrl_set_DPLLPRESC_PRESC_bf(const void *const hw, hri_oscctrl_dpllpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLPRESC.reg |= OSCCTRL_DPLLPRESC_PRESC(mask);
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllpresc_reg_t hri_oscctrl_get_DPLLPRESC_PRESC_bf(const void *const           hw,
                                                                             hri_oscctrl_dpllpresc_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLPRESC.reg;
	tmp = (tmp & OSCCTRL_DPLLPRESC_PRESC(mask)) >> OSCCTRL_DPLLPRESC_PRESC_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLPRESC_PRESC_bf(const void *const hw, hri_oscctrl_dpllpresc_reg_t data)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLPRESC.reg;
	tmp &= ~OSCCTRL_DPLLPRESC_PRESC_Msk;
	tmp |= OSCCTRL_DPLLPRESC_PRESC(data);
	((Oscctrl *)hw)->DPLLPRESC.reg = tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLPRESC_PRESC_bf(const void *const hw, hri_oscctrl_dpllpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLPRESC.reg &= ~OSCCTRL_DPLLPRESC_PRESC(mask);
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLPRESC_PRESC_bf(const void *const hw, hri_oscctrl_dpllpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLPRESC.reg ^= OSCCTRL_DPLLPRESC_PRESC(mask);
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllpresc_reg_t hri_oscctrl_read_DPLLPRESC_PRESC_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLPRESC.reg;
	tmp = (tmp & OSCCTRL_DPLLPRESC_PRESC_Msk) >> OSCCTRL_DPLLPRESC_PRESC_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_DPLLPRESC_reg(const void *const hw, hri_oscctrl_dpllpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLPRESC.reg |= mask;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllpresc_reg_t hri_oscctrl_get_DPLLPRESC_reg(const void *const           hw,
                                                                        hri_oscctrl_dpllpresc_reg_t mask)
{
	uint8_t tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	tmp = ((Oscctrl *)hw)->DPLLPRESC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_DPLLPRESC_reg(const void *const hw, hri_oscctrl_dpllpresc_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLPRESC.reg = data;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLPRESC_reg(const void *const hw, hri_oscctrl_dpllpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLPRESC.reg &= ~mask;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLPRESC_reg(const void *const hw, hri_oscctrl_dpllpresc_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLPRESC.reg ^= mask;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_dpllpresc_reg_t hri_oscctrl_read_DPLLPRESC_reg(const void *const hw)
{
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	return ((Oscctrl *)hw)->DPLLPRESC.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_OSCCTRL_L10_H_INCLUDED */
#endif /* _SAML10_OSCCTRL_COMPONENT_ */
