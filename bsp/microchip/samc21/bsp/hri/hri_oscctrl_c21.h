/**
 * \file
 *
 * \brief SAM OSCCTRL
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

#ifdef _SAMC21_OSCCTRL_COMPONENT_
#ifndef _HRI_OSCCTRL_C21_H_INCLUDED_
#define _HRI_OSCCTRL_C21_H_INCLUDED_

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

typedef uint16_t hri_oscctrl_xoscctrl_reg_t;
typedef uint32_t hri_oscctrl_cal48m_reg_t;
typedef uint32_t hri_oscctrl_dpllctrlb_reg_t;
typedef uint32_t hri_oscctrl_dpllratio_reg_t;
typedef uint32_t hri_oscctrl_intenset_reg_t;
typedef uint32_t hri_oscctrl_intflag_reg_t;
typedef uint32_t hri_oscctrl_osc48msyncbusy_reg_t;
typedef uint32_t hri_oscctrl_status_reg_t;
typedef uint8_t  hri_oscctrl_cfdpresc_reg_t;
typedef uint8_t  hri_oscctrl_dpllctrla_reg_t;
typedef uint8_t  hri_oscctrl_dpllpresc_reg_t;
typedef uint8_t  hri_oscctrl_dpllstatus_reg_t;
typedef uint8_t  hri_oscctrl_dpllsyncbusy_reg_t;
typedef uint8_t  hri_oscctrl_evctrl_reg_t;
typedef uint8_t  hri_oscctrl_osc48mctrl_reg_t;
typedef uint8_t  hri_oscctrl_osc48mdiv_reg_t;
typedef uint8_t  hri_oscctrl_osc48mstup_reg_t;

static inline void hri_oscctrl_osc48msyncbusy_wait_for_sync(const void *const hw, hri_oscctrl_osc48msyncbusy_reg_t reg)
{
	while (((Oscctrl *)hw)->OSC48MSYNCBUSY.reg & reg) {
	};
}

static inline bool hri_oscctrl_osc48msyncbusy_is_syncing(const void *const hw, hri_oscctrl_osc48msyncbusy_reg_t reg)
{
	return ((Oscctrl *)hw)->OSC48MSYNCBUSY.reg & reg;
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
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_XOSCRDY) >> OSCCTRL_INTFLAG_XOSCRDY_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_XOSCRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_XOSCRDY;
}

static inline bool hri_oscctrl_get_INTFLAG_XOSCFAIL_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_XOSCFAIL) >> OSCCTRL_INTFLAG_XOSCFAIL_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_XOSCFAIL_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_XOSCFAIL;
}

static inline bool hri_oscctrl_get_INTFLAG_OSC48MRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_OSC48MRDY) >> OSCCTRL_INTFLAG_OSC48MRDY_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_OSC48MRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_OSC48MRDY;
}

static inline bool hri_oscctrl_get_INTFLAG_DPLLLCKR_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLCKR) >> OSCCTRL_INTFLAG_DPLLLCKR_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DPLLLCKR_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLCKR;
}

static inline bool hri_oscctrl_get_INTFLAG_DPLLLCKF_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLCKF) >> OSCCTRL_INTFLAG_DPLLLCKF_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DPLLLCKF_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLCKF;
}

static inline bool hri_oscctrl_get_INTFLAG_DPLLLTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLTO) >> OSCCTRL_INTFLAG_DPLLLTO_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DPLLLTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLTO;
}

static inline bool hri_oscctrl_get_INTFLAG_DPLLLDRTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLDRTO) >> OSCCTRL_INTFLAG_DPLLLDRTO_Pos;
}

static inline void hri_oscctrl_clear_INTFLAG_DPLLLDRTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLDRTO;
}

static inline bool hri_oscctrl_get_interrupt_XOSCRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_XOSCRDY) >> OSCCTRL_INTFLAG_XOSCRDY_Pos;
}

static inline void hri_oscctrl_clear_interrupt_XOSCRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_XOSCRDY;
}

static inline bool hri_oscctrl_get_interrupt_XOSCFAIL_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_XOSCFAIL) >> OSCCTRL_INTFLAG_XOSCFAIL_Pos;
}

static inline void hri_oscctrl_clear_interrupt_XOSCFAIL_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_XOSCFAIL;
}

static inline bool hri_oscctrl_get_interrupt_OSC48MRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_OSC48MRDY) >> OSCCTRL_INTFLAG_OSC48MRDY_Pos;
}

static inline void hri_oscctrl_clear_interrupt_OSC48MRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_OSC48MRDY;
}

static inline bool hri_oscctrl_get_interrupt_DPLLLCKR_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLCKR) >> OSCCTRL_INTFLAG_DPLLLCKR_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DPLLLCKR_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLCKR;
}

static inline bool hri_oscctrl_get_interrupt_DPLLLCKF_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLCKF) >> OSCCTRL_INTFLAG_DPLLLCKF_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DPLLLCKF_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLCKF;
}

static inline bool hri_oscctrl_get_interrupt_DPLLLTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLTO) >> OSCCTRL_INTFLAG_DPLLLTO_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DPLLLTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLTO;
}

static inline bool hri_oscctrl_get_interrupt_DPLLLDRTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTFLAG.reg & OSCCTRL_INTFLAG_DPLLLDRTO) >> OSCCTRL_INTFLAG_DPLLLDRTO_Pos;
}

static inline void hri_oscctrl_clear_interrupt_DPLLLDRTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTFLAG.reg = OSCCTRL_INTFLAG_DPLLLDRTO;
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
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_XOSCRDY;
}

static inline bool hri_oscctrl_get_INTEN_XOSCRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_XOSCRDY) >> OSCCTRL_INTENSET_XOSCRDY_Pos;
}

static inline void hri_oscctrl_write_INTEN_XOSCRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_XOSCRDY;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_XOSCRDY;
	}
}

static inline void hri_oscctrl_clear_INTEN_XOSCRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_XOSCRDY;
}

static inline void hri_oscctrl_set_INTEN_XOSCFAIL_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_XOSCFAIL;
}

static inline bool hri_oscctrl_get_INTEN_XOSCFAIL_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_XOSCFAIL) >> OSCCTRL_INTENSET_XOSCFAIL_Pos;
}

static inline void hri_oscctrl_write_INTEN_XOSCFAIL_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_XOSCFAIL;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_XOSCFAIL;
	}
}

static inline void hri_oscctrl_clear_INTEN_XOSCFAIL_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_XOSCFAIL;
}

static inline void hri_oscctrl_set_INTEN_OSC48MRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_OSC48MRDY;
}

static inline bool hri_oscctrl_get_INTEN_OSC48MRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_OSC48MRDY) >> OSCCTRL_INTENSET_OSC48MRDY_Pos;
}

static inline void hri_oscctrl_write_INTEN_OSC48MRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_OSC48MRDY;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_OSC48MRDY;
	}
}

static inline void hri_oscctrl_clear_INTEN_OSC48MRDY_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_OSC48MRDY;
}

static inline void hri_oscctrl_set_INTEN_DPLLLCKR_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLCKR;
}

static inline bool hri_oscctrl_get_INTEN_DPLLLCKR_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DPLLLCKR) >> OSCCTRL_INTENSET_DPLLLCKR_Pos;
}

static inline void hri_oscctrl_write_INTEN_DPLLLCKR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLCKR;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLCKR;
	}
}

static inline void hri_oscctrl_clear_INTEN_DPLLLCKR_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLCKR;
}

static inline void hri_oscctrl_set_INTEN_DPLLLCKF_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLCKF;
}

static inline bool hri_oscctrl_get_INTEN_DPLLLCKF_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DPLLLCKF) >> OSCCTRL_INTENSET_DPLLLCKF_Pos;
}

static inline void hri_oscctrl_write_INTEN_DPLLLCKF_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLCKF;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLCKF;
	}
}

static inline void hri_oscctrl_clear_INTEN_DPLLLCKF_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLCKF;
}

static inline void hri_oscctrl_set_INTEN_DPLLLTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLTO;
}

static inline bool hri_oscctrl_get_INTEN_DPLLLTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DPLLLTO) >> OSCCTRL_INTENSET_DPLLLTO_Pos;
}

static inline void hri_oscctrl_write_INTEN_DPLLLTO_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLTO;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLTO;
	}
}

static inline void hri_oscctrl_clear_INTEN_DPLLLTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLTO;
}

static inline void hri_oscctrl_set_INTEN_DPLLLDRTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLDRTO;
}

static inline bool hri_oscctrl_get_INTEN_DPLLLDRTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->INTENSET.reg & OSCCTRL_INTENSET_DPLLLDRTO) >> OSCCTRL_INTENSET_DPLLLDRTO_Pos;
}

static inline void hri_oscctrl_write_INTEN_DPLLLDRTO_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLDRTO;
	} else {
		((Oscctrl *)hw)->INTENSET.reg = OSCCTRL_INTENSET_DPLLLDRTO;
	}
}

static inline void hri_oscctrl_clear_INTEN_DPLLLDRTO_bit(const void *const hw)
{
	((Oscctrl *)hw)->INTENCLR.reg = OSCCTRL_INTENSET_DPLLLDRTO;
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
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_XOSCRDY) >> OSCCTRL_STATUS_XOSCRDY_Pos;
}

static inline bool hri_oscctrl_get_STATUS_XOSCFAIL_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_XOSCFAIL) >> OSCCTRL_STATUS_XOSCFAIL_Pos;
}

static inline bool hri_oscctrl_get_STATUS_XOSCCKSW_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_XOSCCKSW) >> OSCCTRL_STATUS_XOSCCKSW_Pos;
}

static inline bool hri_oscctrl_get_STATUS_OSC48MRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_OSC48MRDY) >> OSCCTRL_STATUS_OSC48MRDY_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DPLLLCKR_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DPLLLCKR) >> OSCCTRL_STATUS_DPLLLCKR_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DPLLLCKF_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DPLLLCKF) >> OSCCTRL_STATUS_DPLLLCKF_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DPLLTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DPLLTO) >> OSCCTRL_STATUS_DPLLTO_Pos;
}

static inline bool hri_oscctrl_get_STATUS_DPLLLDRTO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->STATUS.reg & OSCCTRL_STATUS_DPLLLDRTO) >> OSCCTRL_STATUS_DPLLLDRTO_Pos;
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

static inline bool hri_oscctrl_get_OSC48MSYNCBUSY_OSC48MDIV_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->OSC48MSYNCBUSY.reg & OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV)
	       >> OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Pos;
}

static inline hri_oscctrl_osc48msyncbusy_reg_t hri_oscctrl_get_OSC48MSYNCBUSY_reg(const void *const                hw,
                                                                                  hri_oscctrl_osc48msyncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MSYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_oscctrl_osc48msyncbusy_reg_t hri_oscctrl_read_OSC48MSYNCBUSY_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->OSC48MSYNCBUSY.reg;
}

static inline bool hri_oscctrl_get_DPLLSYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DPLLSYNCBUSY.reg & OSCCTRL_DPLLSYNCBUSY_ENABLE) >> OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos;
}

static inline bool hri_oscctrl_get_DPLLSYNCBUSY_DPLLRATIO_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DPLLSYNCBUSY.reg & OSCCTRL_DPLLSYNCBUSY_DPLLRATIO) >> OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos;
}

static inline bool hri_oscctrl_get_DPLLSYNCBUSY_DPLLPRESC_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DPLLSYNCBUSY.reg & OSCCTRL_DPLLSYNCBUSY_DPLLPRESC) >> OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos;
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
	return (((Oscctrl *)hw)->DPLLSTATUS.reg & OSCCTRL_DPLLSTATUS_LOCK) >> OSCCTRL_DPLLSTATUS_LOCK_Pos;
}

static inline bool hri_oscctrl_get_DPLLSTATUS_CLKRDY_bit(const void *const hw)
{
	return (((Oscctrl *)hw)->DPLLSTATUS.reg & OSCCTRL_DPLLSTATUS_CLKRDY) >> OSCCTRL_DPLLSTATUS_CLKRDY_Pos;
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

static inline void hri_oscctrl_set_XOSCCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_ENABLE;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_ENABLE_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_ENABLE) >> OSCCTRL_XOSCCTRL_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_ENABLE_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_ENABLE;
	tmp |= value << OSCCTRL_XOSCCTRL_ENABLE_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_ENABLE;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_ENABLE;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_XTALEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_XTALEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_XTALEN_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_XTALEN) >> OSCCTRL_XOSCCTRL_XTALEN_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_XTALEN_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_XTALEN;
	tmp |= value << OSCCTRL_XOSCCTRL_XTALEN_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_XTALEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_XTALEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_XTALEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_XTALEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_CFDEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_CFDEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_CFDEN_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_CFDEN) >> OSCCTRL_XOSCCTRL_CFDEN_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_CFDEN_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_CFDEN;
	tmp |= value << OSCCTRL_XOSCCTRL_CFDEN_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_CFDEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_CFDEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_CFDEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_CFDEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_SWBEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_SWBEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_SWBEN_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_SWBEN) >> OSCCTRL_XOSCCTRL_SWBEN_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_SWBEN_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_SWBEN;
	tmp |= value << OSCCTRL_XOSCCTRL_SWBEN_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_SWBEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_SWBEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_SWBEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_SWBEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_RUNSTDBY;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_RUNSTDBY_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_RUNSTDBY) >> OSCCTRL_XOSCCTRL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_RUNSTDBY;
	tmp |= value << OSCCTRL_XOSCCTRL_RUNSTDBY_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_RUNSTDBY;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_RUNSTDBY;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_ONDEMAND;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_ONDEMAND_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_ONDEMAND) >> OSCCTRL_XOSCCTRL_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_ONDEMAND_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_ONDEMAND;
	tmp |= value << OSCCTRL_XOSCCTRL_ONDEMAND_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_ONDEMAND;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_ONDEMAND;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_XOSCCTRL_AMPGC_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg |= OSCCTRL_XOSCCTRL_AMPGC;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_XOSCCTRL_AMPGC_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp = (tmp & OSCCTRL_XOSCCTRL_AMPGC) >> OSCCTRL_XOSCCTRL_AMPGC_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_XOSCCTRL_AMPGC_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->XOSCCTRL.reg;
	tmp &= ~OSCCTRL_XOSCCTRL_AMPGC;
	tmp |= value << OSCCTRL_XOSCCTRL_AMPGC_Pos;
	((Oscctrl *)hw)->XOSCCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_XOSCCTRL_AMPGC_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg &= ~OSCCTRL_XOSCCTRL_AMPGC;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_XOSCCTRL_AMPGC_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->XOSCCTRL.reg ^= OSCCTRL_XOSCCTRL_AMPGC;
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

static inline void hri_oscctrl_set_EVCTRL_CFDEO_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg |= OSCCTRL_EVCTRL_CFDEO;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_EVCTRL_CFDEO_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->EVCTRL.reg;
	tmp = (tmp & OSCCTRL_EVCTRL_CFDEO) >> OSCCTRL_EVCTRL_CFDEO_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_EVCTRL_CFDEO_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->EVCTRL.reg;
	tmp &= ~OSCCTRL_EVCTRL_CFDEO;
	tmp |= value << OSCCTRL_EVCTRL_CFDEO_Pos;
	((Oscctrl *)hw)->EVCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_EVCTRL_CFDEO_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg &= ~OSCCTRL_EVCTRL_CFDEO;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_EVCTRL_CFDEO_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->EVCTRL.reg ^= OSCCTRL_EVCTRL_CFDEO;
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

static inline void hri_oscctrl_set_OSC48MCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg |= OSCCTRL_OSC48MCTRL_ENABLE;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_OSC48MCTRL_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MCTRL.reg;
	tmp = (tmp & OSCCTRL_OSC48MCTRL_ENABLE) >> OSCCTRL_OSC48MCTRL_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_OSC48MCTRL_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->OSC48MCTRL.reg;
	tmp &= ~OSCCTRL_OSC48MCTRL_ENABLE;
	tmp |= value << OSCCTRL_OSC48MCTRL_ENABLE_Pos;
	((Oscctrl *)hw)->OSC48MCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC48MCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg &= ~OSCCTRL_OSC48MCTRL_ENABLE;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC48MCTRL_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg ^= OSCCTRL_OSC48MCTRL_ENABLE;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_OSC48MCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg |= OSCCTRL_OSC48MCTRL_RUNSTDBY;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_OSC48MCTRL_RUNSTDBY_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MCTRL.reg;
	tmp = (tmp & OSCCTRL_OSC48MCTRL_RUNSTDBY) >> OSCCTRL_OSC48MCTRL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_OSC48MCTRL_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->OSC48MCTRL.reg;
	tmp &= ~OSCCTRL_OSC48MCTRL_RUNSTDBY;
	tmp |= value << OSCCTRL_OSC48MCTRL_RUNSTDBY_Pos;
	((Oscctrl *)hw)->OSC48MCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC48MCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg &= ~OSCCTRL_OSC48MCTRL_RUNSTDBY;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC48MCTRL_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg ^= OSCCTRL_OSC48MCTRL_RUNSTDBY;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_OSC48MCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg |= OSCCTRL_OSC48MCTRL_ONDEMAND;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_OSC48MCTRL_ONDEMAND_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MCTRL.reg;
	tmp = (tmp & OSCCTRL_OSC48MCTRL_ONDEMAND) >> OSCCTRL_OSC48MCTRL_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_OSC48MCTRL_ONDEMAND_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->OSC48MCTRL.reg;
	tmp &= ~OSCCTRL_OSC48MCTRL_ONDEMAND;
	tmp |= value << OSCCTRL_OSC48MCTRL_ONDEMAND_Pos;
	((Oscctrl *)hw)->OSC48MCTRL.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC48MCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg &= ~OSCCTRL_OSC48MCTRL_ONDEMAND;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC48MCTRL_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg ^= OSCCTRL_OSC48MCTRL_ONDEMAND;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_OSC48MCTRL_reg(const void *const hw, hri_oscctrl_osc48mctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mctrl_reg_t hri_oscctrl_get_OSC48MCTRL_reg(const void *const            hw,
                                                                          hri_oscctrl_osc48mctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_OSC48MCTRL_reg(const void *const hw, hri_oscctrl_osc48mctrl_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC48MCTRL_reg(const void *const hw, hri_oscctrl_osc48mctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC48MCTRL_reg(const void *const hw, hri_oscctrl_osc48mctrl_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MCTRL.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mctrl_reg_t hri_oscctrl_read_OSC48MCTRL_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->OSC48MCTRL.reg;
}

static inline void hri_oscctrl_set_OSC48MDIV_DIV_bf(const void *const hw, hri_oscctrl_osc48mdiv_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MDIV.reg |= OSCCTRL_OSC48MDIV_DIV(mask);
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mdiv_reg_t hri_oscctrl_get_OSC48MDIV_DIV_bf(const void *const           hw,
                                                                           hri_oscctrl_osc48mdiv_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MDIV.reg;
	tmp = (tmp & OSCCTRL_OSC48MDIV_DIV(mask)) >> OSCCTRL_OSC48MDIV_DIV_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_OSC48MDIV_DIV_bf(const void *const hw, hri_oscctrl_osc48mdiv_reg_t data)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->OSC48MDIV.reg;
	tmp &= ~OSCCTRL_OSC48MDIV_DIV_Msk;
	tmp |= OSCCTRL_OSC48MDIV_DIV(data);
	((Oscctrl *)hw)->OSC48MDIV.reg = tmp;
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC48MDIV_DIV_bf(const void *const hw, hri_oscctrl_osc48mdiv_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MDIV.reg &= ~OSCCTRL_OSC48MDIV_DIV(mask);
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC48MDIV_DIV_bf(const void *const hw, hri_oscctrl_osc48mdiv_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MDIV.reg ^= OSCCTRL_OSC48MDIV_DIV(mask);
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mdiv_reg_t hri_oscctrl_read_OSC48MDIV_DIV_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MDIV.reg;
	tmp = (tmp & OSCCTRL_OSC48MDIV_DIV_Msk) >> OSCCTRL_OSC48MDIV_DIV_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_OSC48MDIV_reg(const void *const hw, hri_oscctrl_osc48mdiv_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MDIV.reg |= mask;
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mdiv_reg_t hri_oscctrl_get_OSC48MDIV_reg(const void *const           hw,
                                                                        hri_oscctrl_osc48mdiv_reg_t mask)
{
	uint8_t tmp;
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	tmp = ((Oscctrl *)hw)->OSC48MDIV.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_OSC48MDIV_reg(const void *const hw, hri_oscctrl_osc48mdiv_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MDIV.reg = data;
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC48MDIV_reg(const void *const hw, hri_oscctrl_osc48mdiv_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MDIV.reg &= ~mask;
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC48MDIV_reg(const void *const hw, hri_oscctrl_osc48mdiv_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MDIV.reg ^= mask;
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mdiv_reg_t hri_oscctrl_read_OSC48MDIV_reg(const void *const hw)
{
	hri_oscctrl_osc48msyncbusy_wait_for_sync(hw, OSCCTRL_OSC48MSYNCBUSY_MASK);
	return ((Oscctrl *)hw)->OSC48MDIV.reg;
}

static inline void hri_oscctrl_set_OSC48MSTUP_STARTUP_bf(const void *const hw, hri_oscctrl_osc48mstup_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MSTUP.reg |= OSCCTRL_OSC48MSTUP_STARTUP(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mstup_reg_t hri_oscctrl_get_OSC48MSTUP_STARTUP_bf(const void *const            hw,
                                                                                 hri_oscctrl_osc48mstup_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MSTUP.reg;
	tmp = (tmp & OSCCTRL_OSC48MSTUP_STARTUP(mask)) >> OSCCTRL_OSC48MSTUP_STARTUP_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_OSC48MSTUP_STARTUP_bf(const void *const hw, hri_oscctrl_osc48mstup_reg_t data)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->OSC48MSTUP.reg;
	tmp &= ~OSCCTRL_OSC48MSTUP_STARTUP_Msk;
	tmp |= OSCCTRL_OSC48MSTUP_STARTUP(data);
	((Oscctrl *)hw)->OSC48MSTUP.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC48MSTUP_STARTUP_bf(const void *const hw, hri_oscctrl_osc48mstup_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MSTUP.reg &= ~OSCCTRL_OSC48MSTUP_STARTUP(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC48MSTUP_STARTUP_bf(const void *const hw, hri_oscctrl_osc48mstup_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MSTUP.reg ^= OSCCTRL_OSC48MSTUP_STARTUP(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mstup_reg_t hri_oscctrl_read_OSC48MSTUP_STARTUP_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MSTUP.reg;
	tmp = (tmp & OSCCTRL_OSC48MSTUP_STARTUP_Msk) >> OSCCTRL_OSC48MSTUP_STARTUP_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_OSC48MSTUP_reg(const void *const hw, hri_oscctrl_osc48mstup_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MSTUP.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mstup_reg_t hri_oscctrl_get_OSC48MSTUP_reg(const void *const            hw,
                                                                          hri_oscctrl_osc48mstup_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->OSC48MSTUP.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_OSC48MSTUP_reg(const void *const hw, hri_oscctrl_osc48mstup_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MSTUP.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_OSC48MSTUP_reg(const void *const hw, hri_oscctrl_osc48mstup_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MSTUP.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_OSC48MSTUP_reg(const void *const hw, hri_oscctrl_osc48mstup_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->OSC48MSTUP.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_osc48mstup_reg_t hri_oscctrl_read_OSC48MSTUP_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->OSC48MSTUP.reg;
}

static inline void hri_oscctrl_set_DPLLCTRLA_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg |= OSCCTRL_DPLLCTRLA_ENABLE;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLA_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLA_ENABLE) >> OSCCTRL_DPLLCTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp &= ~OSCCTRL_DPLLCTRLA_ENABLE;
	tmp |= value << OSCCTRL_DPLLCTRLA_ENABLE_Pos;
	((Oscctrl *)hw)->DPLLCTRLA.reg = tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLA_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg &= ~OSCCTRL_DPLLCTRLA_ENABLE;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLA_ENABLE_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg ^= OSCCTRL_DPLLCTRLA_ENABLE;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_ENABLE);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLA_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg |= OSCCTRL_DPLLCTRLA_RUNSTDBY;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLA_RUNSTDBY_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLA_RUNSTDBY) >> OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLA_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp &= ~OSCCTRL_DPLLCTRLA_RUNSTDBY;
	tmp |= value << OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos;
	((Oscctrl *)hw)->DPLLCTRLA.reg = tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLA_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg &= ~OSCCTRL_DPLLCTRLA_RUNSTDBY;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLA_RUNSTDBY_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg ^= OSCCTRL_DPLLCTRLA_RUNSTDBY;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLA_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg |= OSCCTRL_DPLLCTRLA_ONDEMAND;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLA_ONDEMAND_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLA_ONDEMAND) >> OSCCTRL_DPLLCTRLA_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLA_ONDEMAND_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLA.reg;
	tmp &= ~OSCCTRL_DPLLCTRLA_ONDEMAND;
	tmp |= value << OSCCTRL_DPLLCTRLA_ONDEMAND_Pos;
	((Oscctrl *)hw)->DPLLCTRLA.reg = tmp;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLA_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg &= ~OSCCTRL_DPLLCTRLA_ONDEMAND;
	hri_oscctrl_dpllsyncbusy_wait_for_sync(hw, OSCCTRL_DPLLSYNCBUSY_MASK);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLA_ONDEMAND_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLA.reg ^= OSCCTRL_DPLLCTRLA_ONDEMAND;
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
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_LPEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLB_LPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_LPEN) >> OSCCTRL_DPLLCTRLB_LPEN_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_LPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_LPEN;
	tmp |= value << OSCCTRL_DPLLCTRLB_LPEN_Pos;
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_LPEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_LPEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_LPEN_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_LPEN;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLB_WUF_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_WUF;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLB_WUF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_WUF) >> OSCCTRL_DPLLCTRLB_WUF_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_WUF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_WUF;
	tmp |= value << OSCCTRL_DPLLCTRLB_WUF_Pos;
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_WUF_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_WUF;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_WUF_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_WUF;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_set_DPLLCTRLB_LBYPASS_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg |= OSCCTRL_DPLLCTRLB_LBYPASS;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_oscctrl_get_DPLLCTRLB_LBYPASS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp = (tmp & OSCCTRL_DPLLCTRLB_LBYPASS) >> OSCCTRL_DPLLCTRLB_LBYPASS_Pos;
	return (bool)tmp;
}

static inline void hri_oscctrl_write_DPLLCTRLB_LBYPASS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->DPLLCTRLB.reg;
	tmp &= ~OSCCTRL_DPLLCTRLB_LBYPASS;
	tmp |= value << OSCCTRL_DPLLCTRLB_LBYPASS_Pos;
	((Oscctrl *)hw)->DPLLCTRLB.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_DPLLCTRLB_LBYPASS_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg &= ~OSCCTRL_DPLLCTRLB_LBYPASS;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_DPLLCTRLB_LBYPASS_bit(const void *const hw)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->DPLLCTRLB.reg ^= OSCCTRL_DPLLCTRLB_LBYPASS;
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

static inline void hri_oscctrl_set_CAL48M_FCAL_bf(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg |= OSCCTRL_CAL48M_FCAL(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cal48m_reg_t hri_oscctrl_get_CAL48M_FCAL_bf(const void *const        hw,
                                                                      hri_oscctrl_cal48m_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp = (tmp & OSCCTRL_CAL48M_FCAL(mask)) >> OSCCTRL_CAL48M_FCAL_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_CAL48M_FCAL_bf(const void *const hw, hri_oscctrl_cal48m_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp &= ~OSCCTRL_CAL48M_FCAL_Msk;
	tmp |= OSCCTRL_CAL48M_FCAL(data);
	((Oscctrl *)hw)->CAL48M.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_CAL48M_FCAL_bf(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg &= ~OSCCTRL_CAL48M_FCAL(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_CAL48M_FCAL_bf(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg ^= OSCCTRL_CAL48M_FCAL(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cal48m_reg_t hri_oscctrl_read_CAL48M_FCAL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp = (tmp & OSCCTRL_CAL48M_FCAL_Msk) >> OSCCTRL_CAL48M_FCAL_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_CAL48M_FRANGE_bf(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg |= OSCCTRL_CAL48M_FRANGE(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cal48m_reg_t hri_oscctrl_get_CAL48M_FRANGE_bf(const void *const        hw,
                                                                        hri_oscctrl_cal48m_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp = (tmp & OSCCTRL_CAL48M_FRANGE(mask)) >> OSCCTRL_CAL48M_FRANGE_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_CAL48M_FRANGE_bf(const void *const hw, hri_oscctrl_cal48m_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp &= ~OSCCTRL_CAL48M_FRANGE_Msk;
	tmp |= OSCCTRL_CAL48M_FRANGE(data);
	((Oscctrl *)hw)->CAL48M.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_CAL48M_FRANGE_bf(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg &= ~OSCCTRL_CAL48M_FRANGE(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_CAL48M_FRANGE_bf(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg ^= OSCCTRL_CAL48M_FRANGE(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cal48m_reg_t hri_oscctrl_read_CAL48M_FRANGE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp = (tmp & OSCCTRL_CAL48M_FRANGE_Msk) >> OSCCTRL_CAL48M_FRANGE_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_CAL48M_TCAL_bf(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg |= OSCCTRL_CAL48M_TCAL(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cal48m_reg_t hri_oscctrl_get_CAL48M_TCAL_bf(const void *const        hw,
                                                                      hri_oscctrl_cal48m_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp = (tmp & OSCCTRL_CAL48M_TCAL(mask)) >> OSCCTRL_CAL48M_TCAL_Pos;
	return tmp;
}

static inline void hri_oscctrl_write_CAL48M_TCAL_bf(const void *const hw, hri_oscctrl_cal48m_reg_t data)
{
	uint32_t tmp;
	OSCCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp &= ~OSCCTRL_CAL48M_TCAL_Msk;
	tmp |= OSCCTRL_CAL48M_TCAL(data);
	((Oscctrl *)hw)->CAL48M.reg = tmp;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_CAL48M_TCAL_bf(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg &= ~OSCCTRL_CAL48M_TCAL(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_CAL48M_TCAL_bf(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg ^= OSCCTRL_CAL48M_TCAL(mask);
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cal48m_reg_t hri_oscctrl_read_CAL48M_TCAL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp = (tmp & OSCCTRL_CAL48M_TCAL_Msk) >> OSCCTRL_CAL48M_TCAL_Pos;
	return tmp;
}

static inline void hri_oscctrl_set_CAL48M_reg(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg |= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cal48m_reg_t hri_oscctrl_get_CAL48M_reg(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Oscctrl *)hw)->CAL48M.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_oscctrl_write_CAL48M_reg(const void *const hw, hri_oscctrl_cal48m_reg_t data)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg = data;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_clear_CAL48M_reg(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg &= ~mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_oscctrl_toggle_CAL48M_reg(const void *const hw, hri_oscctrl_cal48m_reg_t mask)
{
	OSCCTRL_CRITICAL_SECTION_ENTER();
	((Oscctrl *)hw)->CAL48M.reg ^= mask;
	OSCCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_oscctrl_cal48m_reg_t hri_oscctrl_read_CAL48M_reg(const void *const hw)
{
	return ((Oscctrl *)hw)->CAL48M.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_OSCCTRL_C21_H_INCLUDED */
#endif /* _SAMC21_OSCCTRL_COMPONENT_ */
