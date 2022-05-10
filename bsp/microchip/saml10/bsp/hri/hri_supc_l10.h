/**
 * \file
 *
 * \brief SAM SUPC
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

#ifdef _SAML10_SUPC_COMPONENT_
#ifndef _HRI_SUPC_L10_H_INCLUDED_
#define _HRI_SUPC_L10_H_INCLUDED_

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

typedef uint32_t hri_supc_bod12_reg_t;
typedef uint32_t hri_supc_bod33_reg_t;
typedef uint32_t hri_supc_evctrl_reg_t;
typedef uint32_t hri_supc_intenset_reg_t;
typedef uint32_t hri_supc_intflag_reg_t;
typedef uint32_t hri_supc_status_reg_t;
typedef uint32_t hri_supc_vref_reg_t;
typedef uint32_t hri_supc_vreg_reg_t;
typedef uint32_t hri_supc_vregsusp_reg_t;

static inline bool hri_supc_get_INTFLAG_BOD33RDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BOD33RDY_Msk) >> SUPC_INTFLAG_BOD33RDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_BOD33RDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BOD33RDY_Msk;
}

static inline bool hri_supc_get_INTFLAG_BOD33DET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BOD33DET_Msk) >> SUPC_INTFLAG_BOD33DET_Pos;
}

static inline void hri_supc_clear_INTFLAG_BOD33DET_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BOD33DET_Msk;
}

static inline bool hri_supc_get_INTFLAG_B33SRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_B33SRDY_Msk) >> SUPC_INTFLAG_B33SRDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_B33SRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_B33SRDY_Msk;
}

static inline bool hri_supc_get_INTFLAG_BOD12RDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BOD12RDY_Msk) >> SUPC_INTFLAG_BOD12RDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_BOD12RDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BOD12RDY_Msk;
}

static inline bool hri_supc_get_INTFLAG_BOD12DET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BOD12DET_Msk) >> SUPC_INTFLAG_BOD12DET_Pos;
}

static inline void hri_supc_clear_INTFLAG_BOD12DET_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BOD12DET_Msk;
}

static inline bool hri_supc_get_INTFLAG_B12SRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_B12SRDY_Msk) >> SUPC_INTFLAG_B12SRDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_B12SRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_B12SRDY_Msk;
}

static inline bool hri_supc_get_INTFLAG_VREGRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_VREGRDY_Msk) >> SUPC_INTFLAG_VREGRDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_VREGRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_VREGRDY_Msk;
}

static inline bool hri_supc_get_INTFLAG_VCORERDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_VCORERDY_Msk) >> SUPC_INTFLAG_VCORERDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_VCORERDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_VCORERDY_Msk;
}

static inline bool hri_supc_get_INTFLAG_ULPVREFRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_ULPVREFRDY_Msk) >> SUPC_INTFLAG_ULPVREFRDY_Pos;
}

static inline void hri_supc_clear_INTFLAG_ULPVREFRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_ULPVREFRDY_Msk;
}

static inline bool hri_supc_get_interrupt_BOD33RDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BOD33RDY_Msk) >> SUPC_INTFLAG_BOD33RDY_Pos;
}

static inline void hri_supc_clear_interrupt_BOD33RDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BOD33RDY_Msk;
}

static inline bool hri_supc_get_interrupt_BOD33DET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BOD33DET_Msk) >> SUPC_INTFLAG_BOD33DET_Pos;
}

static inline void hri_supc_clear_interrupt_BOD33DET_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BOD33DET_Msk;
}

static inline bool hri_supc_get_interrupt_B33SRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_B33SRDY_Msk) >> SUPC_INTFLAG_B33SRDY_Pos;
}

static inline void hri_supc_clear_interrupt_B33SRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_B33SRDY_Msk;
}

static inline bool hri_supc_get_interrupt_BOD12RDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BOD12RDY_Msk) >> SUPC_INTFLAG_BOD12RDY_Pos;
}

static inline void hri_supc_clear_interrupt_BOD12RDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BOD12RDY_Msk;
}

static inline bool hri_supc_get_interrupt_BOD12DET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_BOD12DET_Msk) >> SUPC_INTFLAG_BOD12DET_Pos;
}

static inline void hri_supc_clear_interrupt_BOD12DET_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_BOD12DET_Msk;
}

static inline bool hri_supc_get_interrupt_B12SRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_B12SRDY_Msk) >> SUPC_INTFLAG_B12SRDY_Pos;
}

static inline void hri_supc_clear_interrupt_B12SRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_B12SRDY_Msk;
}

static inline bool hri_supc_get_interrupt_VREGRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_VREGRDY_Msk) >> SUPC_INTFLAG_VREGRDY_Pos;
}

static inline void hri_supc_clear_interrupt_VREGRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_VREGRDY_Msk;
}

static inline bool hri_supc_get_interrupt_VCORERDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_VCORERDY_Msk) >> SUPC_INTFLAG_VCORERDY_Pos;
}

static inline void hri_supc_clear_interrupt_VCORERDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_VCORERDY_Msk;
}

static inline bool hri_supc_get_interrupt_ULPVREFRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTFLAG.reg & SUPC_INTFLAG_ULPVREFRDY_Msk) >> SUPC_INTFLAG_ULPVREFRDY_Pos;
}

static inline void hri_supc_clear_interrupt_ULPVREFRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTFLAG.reg = SUPC_INTFLAG_ULPVREFRDY_Msk;
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

static inline void hri_supc_set_INTEN_BOD33RDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BOD33RDY_Msk;
}

static inline bool hri_supc_get_INTEN_BOD33RDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BOD33RDY_Msk) >> SUPC_INTENSET_BOD33RDY_Pos;
}

static inline void hri_supc_write_INTEN_BOD33RDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BOD33RDY_Msk;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BOD33RDY_Msk;
	}
}

static inline void hri_supc_clear_INTEN_BOD33RDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BOD33RDY_Msk;
}

static inline void hri_supc_set_INTEN_BOD33DET_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BOD33DET_Msk;
}

static inline bool hri_supc_get_INTEN_BOD33DET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BOD33DET_Msk) >> SUPC_INTENSET_BOD33DET_Pos;
}

static inline void hri_supc_write_INTEN_BOD33DET_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BOD33DET_Msk;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BOD33DET_Msk;
	}
}

static inline void hri_supc_clear_INTEN_BOD33DET_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BOD33DET_Msk;
}

static inline void hri_supc_set_INTEN_B33SRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_B33SRDY_Msk;
}

static inline bool hri_supc_get_INTEN_B33SRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_B33SRDY_Msk) >> SUPC_INTENSET_B33SRDY_Pos;
}

static inline void hri_supc_write_INTEN_B33SRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_B33SRDY_Msk;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_B33SRDY_Msk;
	}
}

static inline void hri_supc_clear_INTEN_B33SRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_B33SRDY_Msk;
}

static inline void hri_supc_set_INTEN_BOD12RDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BOD12RDY_Msk;
}

static inline bool hri_supc_get_INTEN_BOD12RDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BOD12RDY_Msk) >> SUPC_INTENSET_BOD12RDY_Pos;
}

static inline void hri_supc_write_INTEN_BOD12RDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BOD12RDY_Msk;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BOD12RDY_Msk;
	}
}

static inline void hri_supc_clear_INTEN_BOD12RDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BOD12RDY_Msk;
}

static inline void hri_supc_set_INTEN_BOD12DET_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BOD12DET_Msk;
}

static inline bool hri_supc_get_INTEN_BOD12DET_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_BOD12DET_Msk) >> SUPC_INTENSET_BOD12DET_Pos;
}

static inline void hri_supc_write_INTEN_BOD12DET_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BOD12DET_Msk;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_BOD12DET_Msk;
	}
}

static inline void hri_supc_clear_INTEN_BOD12DET_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_BOD12DET_Msk;
}

static inline void hri_supc_set_INTEN_B12SRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_B12SRDY_Msk;
}

static inline bool hri_supc_get_INTEN_B12SRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_B12SRDY_Msk) >> SUPC_INTENSET_B12SRDY_Pos;
}

static inline void hri_supc_write_INTEN_B12SRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_B12SRDY_Msk;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_B12SRDY_Msk;
	}
}

static inline void hri_supc_clear_INTEN_B12SRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_B12SRDY_Msk;
}

static inline void hri_supc_set_INTEN_VREGRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_VREGRDY_Msk;
}

static inline bool hri_supc_get_INTEN_VREGRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_VREGRDY_Msk) >> SUPC_INTENSET_VREGRDY_Pos;
}

static inline void hri_supc_write_INTEN_VREGRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_VREGRDY_Msk;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_VREGRDY_Msk;
	}
}

static inline void hri_supc_clear_INTEN_VREGRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_VREGRDY_Msk;
}

static inline void hri_supc_set_INTEN_VCORERDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_VCORERDY_Msk;
}

static inline bool hri_supc_get_INTEN_VCORERDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_VCORERDY_Msk) >> SUPC_INTENSET_VCORERDY_Pos;
}

static inline void hri_supc_write_INTEN_VCORERDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_VCORERDY_Msk;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_VCORERDY_Msk;
	}
}

static inline void hri_supc_clear_INTEN_VCORERDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_VCORERDY_Msk;
}

static inline void hri_supc_set_INTEN_ULPVREFRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_ULPVREFRDY_Msk;
}

static inline bool hri_supc_get_INTEN_ULPVREFRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->INTENSET.reg & SUPC_INTENSET_ULPVREFRDY_Msk) >> SUPC_INTENSET_ULPVREFRDY_Pos;
}

static inline void hri_supc_write_INTEN_ULPVREFRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_ULPVREFRDY_Msk;
	} else {
		((Supc *)hw)->INTENSET.reg = SUPC_INTENSET_ULPVREFRDY_Msk;
	}
}

static inline void hri_supc_clear_INTEN_ULPVREFRDY_bit(const void *const hw)
{
	((Supc *)hw)->INTENCLR.reg = SUPC_INTENSET_ULPVREFRDY_Msk;
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

static inline bool hri_supc_get_STATUS_BOD33RDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BOD33RDY_Msk) >> SUPC_STATUS_BOD33RDY_Pos;
}

static inline bool hri_supc_get_STATUS_BOD33DET_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BOD33DET_Msk) >> SUPC_STATUS_BOD33DET_Pos;
}

static inline bool hri_supc_get_STATUS_B33SRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_B33SRDY_Msk) >> SUPC_STATUS_B33SRDY_Pos;
}

static inline bool hri_supc_get_STATUS_BOD12RDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BOD12RDY_Msk) >> SUPC_STATUS_BOD12RDY_Pos;
}

static inline bool hri_supc_get_STATUS_BOD12DET_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_BOD12DET_Msk) >> SUPC_STATUS_BOD12DET_Pos;
}

static inline bool hri_supc_get_STATUS_B12SRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_B12SRDY_Msk) >> SUPC_STATUS_B12SRDY_Pos;
}

static inline bool hri_supc_get_STATUS_VREGRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_VREGRDY_Msk) >> SUPC_STATUS_VREGRDY_Pos;
}

static inline bool hri_supc_get_STATUS_VCORERDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_VCORERDY_Msk) >> SUPC_STATUS_VCORERDY_Pos;
}

static inline bool hri_supc_get_STATUS_ULPVREFRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_ULPVREFRDY_Msk) >> SUPC_STATUS_ULPVREFRDY_Pos;
}

static inline bool hri_supc_get_STATUS_ULPBIASRDY_bit(const void *const hw)
{
	return (((Supc *)hw)->STATUS.reg & SUPC_STATUS_ULPBIASRDY_Msk) >> SUPC_STATUS_ULPBIASRDY_Pos;
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

static inline void hri_supc_set_BOD33_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= SUPC_BOD33_ENABLE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD33_ENABLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_ENABLE_Msk) >> SUPC_BOD33_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD33_ENABLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= ~SUPC_BOD33_ENABLE_Msk;
	tmp |= value << SUPC_BOD33_ENABLE_Pos;
	((Supc *)hw)->BOD33.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~SUPC_BOD33_ENABLE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= SUPC_BOD33_ENABLE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD33_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= SUPC_BOD33_HYST_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD33_HYST_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_HYST_Msk) >> SUPC_BOD33_HYST_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD33_HYST_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= ~SUPC_BOD33_HYST_Msk;
	tmp |= value << SUPC_BOD33_HYST_Pos;
	((Supc *)hw)->BOD33.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~SUPC_BOD33_HYST_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= SUPC_BOD33_HYST_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD33_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= SUPC_BOD33_STDBYCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD33_STDBYCFG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_STDBYCFG_Msk) >> SUPC_BOD33_STDBYCFG_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD33_STDBYCFG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= ~SUPC_BOD33_STDBYCFG_Msk;
	tmp |= value << SUPC_BOD33_STDBYCFG_Pos;
	((Supc *)hw)->BOD33.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~SUPC_BOD33_STDBYCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= SUPC_BOD33_STDBYCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD33_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= SUPC_BOD33_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD33_RUNSTDBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_RUNSTDBY_Msk) >> SUPC_BOD33_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD33_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= ~SUPC_BOD33_RUNSTDBY_Msk;
	tmp |= value << SUPC_BOD33_RUNSTDBY_Pos;
	((Supc *)hw)->BOD33.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~SUPC_BOD33_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= SUPC_BOD33_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD33_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= SUPC_BOD33_ACTCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD33_ACTCFG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_ACTCFG_Msk) >> SUPC_BOD33_ACTCFG_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD33_ACTCFG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= ~SUPC_BOD33_ACTCFG_Msk;
	tmp |= value << SUPC_BOD33_ACTCFG_Pos;
	((Supc *)hw)->BOD33.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~SUPC_BOD33_ACTCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= SUPC_BOD33_ACTCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD33_REFSEL_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= SUPC_BOD33_REFSEL_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD33_REFSEL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_REFSEL_Msk) >> SUPC_BOD33_REFSEL_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD33_REFSEL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= ~SUPC_BOD33_REFSEL_Msk;
	tmp |= value << SUPC_BOD33_REFSEL_Pos;
	((Supc *)hw)->BOD33.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_REFSEL_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~SUPC_BOD33_REFSEL_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_REFSEL_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= SUPC_BOD33_REFSEL_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD33_ACTION_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= SUPC_BOD33_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod33_reg_t hri_supc_get_BOD33_ACTION_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_ACTION(mask)) >> SUPC_BOD33_ACTION_Pos;
	return tmp;
}

static inline void hri_supc_write_BOD33_ACTION_bf(const void *const hw, hri_supc_bod33_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= ~SUPC_BOD33_ACTION_Msk;
	tmp |= SUPC_BOD33_ACTION(data);
	((Supc *)hw)->BOD33.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_ACTION_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~SUPC_BOD33_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_ACTION_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= SUPC_BOD33_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod33_reg_t hri_supc_read_BOD33_ACTION_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_ACTION_Msk) >> SUPC_BOD33_ACTION_Pos;
	return tmp;
}

static inline void hri_supc_set_BOD33_PSEL_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= SUPC_BOD33_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod33_reg_t hri_supc_get_BOD33_PSEL_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_PSEL(mask)) >> SUPC_BOD33_PSEL_Pos;
	return tmp;
}

static inline void hri_supc_write_BOD33_PSEL_bf(const void *const hw, hri_supc_bod33_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= ~SUPC_BOD33_PSEL_Msk;
	tmp |= SUPC_BOD33_PSEL(data);
	((Supc *)hw)->BOD33.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_PSEL_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~SUPC_BOD33_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_PSEL_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= SUPC_BOD33_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod33_reg_t hri_supc_read_BOD33_PSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_PSEL_Msk) >> SUPC_BOD33_PSEL_Pos;
	return tmp;
}

static inline void hri_supc_set_BOD33_LEVEL_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= SUPC_BOD33_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod33_reg_t hri_supc_get_BOD33_LEVEL_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_LEVEL(mask)) >> SUPC_BOD33_LEVEL_Pos;
	return tmp;
}

static inline void hri_supc_write_BOD33_LEVEL_bf(const void *const hw, hri_supc_bod33_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= ~SUPC_BOD33_LEVEL_Msk;
	tmp |= SUPC_BOD33_LEVEL(data);
	((Supc *)hw)->BOD33.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_LEVEL_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~SUPC_BOD33_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_LEVEL_bf(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= SUPC_BOD33_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod33_reg_t hri_supc_read_BOD33_LEVEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp = (tmp & SUPC_BOD33_LEVEL_Msk) >> SUPC_BOD33_LEVEL_Pos;
	return tmp;
}

static inline void hri_supc_set_BOD33_reg(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod33_reg_t hri_supc_get_BOD33_reg(const void *const hw, hri_supc_bod33_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD33.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_BOD33_reg(const void *const hw, hri_supc_bod33_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD33_reg(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD33_reg(const void *const hw, hri_supc_bod33_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD33.reg ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod33_reg_t hri_supc_read_BOD33_reg(const void *const hw)
{
	return ((Supc *)hw)->BOD33.reg;
}

static inline void hri_supc_set_BOD12_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg |= SUPC_BOD12_ENABLE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD12_ENABLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_ENABLE_Msk) >> SUPC_BOD12_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD12_ENABLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp &= ~SUPC_BOD12_ENABLE_Msk;
	tmp |= value << SUPC_BOD12_ENABLE_Pos;
	((Supc *)hw)->BOD12.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD12_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg &= ~SUPC_BOD12_ENABLE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD12_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg ^= SUPC_BOD12_ENABLE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD12_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg |= SUPC_BOD12_HYST_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD12_HYST_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_HYST_Msk) >> SUPC_BOD12_HYST_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD12_HYST_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp &= ~SUPC_BOD12_HYST_Msk;
	tmp |= value << SUPC_BOD12_HYST_Pos;
	((Supc *)hw)->BOD12.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD12_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg &= ~SUPC_BOD12_HYST_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD12_HYST_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg ^= SUPC_BOD12_HYST_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD12_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg |= SUPC_BOD12_STDBYCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD12_STDBYCFG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_STDBYCFG_Msk) >> SUPC_BOD12_STDBYCFG_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD12_STDBYCFG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp &= ~SUPC_BOD12_STDBYCFG_Msk;
	tmp |= value << SUPC_BOD12_STDBYCFG_Pos;
	((Supc *)hw)->BOD12.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD12_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg &= ~SUPC_BOD12_STDBYCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD12_STDBYCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg ^= SUPC_BOD12_STDBYCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD12_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg |= SUPC_BOD12_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD12_RUNSTDBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_RUNSTDBY_Msk) >> SUPC_BOD12_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD12_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp &= ~SUPC_BOD12_RUNSTDBY_Msk;
	tmp |= value << SUPC_BOD12_RUNSTDBY_Pos;
	((Supc *)hw)->BOD12.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD12_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg &= ~SUPC_BOD12_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD12_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg ^= SUPC_BOD12_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD12_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg |= SUPC_BOD12_ACTCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_BOD12_ACTCFG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_ACTCFG_Msk) >> SUPC_BOD12_ACTCFG_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_BOD12_ACTCFG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp &= ~SUPC_BOD12_ACTCFG_Msk;
	tmp |= value << SUPC_BOD12_ACTCFG_Pos;
	((Supc *)hw)->BOD12.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD12_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg &= ~SUPC_BOD12_ACTCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD12_ACTCFG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg ^= SUPC_BOD12_ACTCFG_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_BOD12_ACTION_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg |= SUPC_BOD12_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod12_reg_t hri_supc_get_BOD12_ACTION_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_ACTION(mask)) >> SUPC_BOD12_ACTION_Pos;
	return tmp;
}

static inline void hri_supc_write_BOD12_ACTION_bf(const void *const hw, hri_supc_bod12_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp &= ~SUPC_BOD12_ACTION_Msk;
	tmp |= SUPC_BOD12_ACTION(data);
	((Supc *)hw)->BOD12.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD12_ACTION_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg &= ~SUPC_BOD12_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD12_ACTION_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg ^= SUPC_BOD12_ACTION(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod12_reg_t hri_supc_read_BOD12_ACTION_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_ACTION_Msk) >> SUPC_BOD12_ACTION_Pos;
	return tmp;
}

static inline void hri_supc_set_BOD12_PSEL_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg |= SUPC_BOD12_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod12_reg_t hri_supc_get_BOD12_PSEL_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_PSEL(mask)) >> SUPC_BOD12_PSEL_Pos;
	return tmp;
}

static inline void hri_supc_write_BOD12_PSEL_bf(const void *const hw, hri_supc_bod12_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp &= ~SUPC_BOD12_PSEL_Msk;
	tmp |= SUPC_BOD12_PSEL(data);
	((Supc *)hw)->BOD12.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD12_PSEL_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg &= ~SUPC_BOD12_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD12_PSEL_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg ^= SUPC_BOD12_PSEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod12_reg_t hri_supc_read_BOD12_PSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_PSEL_Msk) >> SUPC_BOD12_PSEL_Pos;
	return tmp;
}

static inline void hri_supc_set_BOD12_LEVEL_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg |= SUPC_BOD12_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod12_reg_t hri_supc_get_BOD12_LEVEL_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_LEVEL(mask)) >> SUPC_BOD12_LEVEL_Pos;
	return tmp;
}

static inline void hri_supc_write_BOD12_LEVEL_bf(const void *const hw, hri_supc_bod12_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp &= ~SUPC_BOD12_LEVEL_Msk;
	tmp |= SUPC_BOD12_LEVEL(data);
	((Supc *)hw)->BOD12.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD12_LEVEL_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg &= ~SUPC_BOD12_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD12_LEVEL_bf(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg ^= SUPC_BOD12_LEVEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod12_reg_t hri_supc_read_BOD12_LEVEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp = (tmp & SUPC_BOD12_LEVEL_Msk) >> SUPC_BOD12_LEVEL_Pos;
	return tmp;
}

static inline void hri_supc_set_BOD12_reg(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod12_reg_t hri_supc_get_BOD12_reg(const void *const hw, hri_supc_bod12_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->BOD12.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_BOD12_reg(const void *const hw, hri_supc_bod12_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_BOD12_reg(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_BOD12_reg(const void *const hw, hri_supc_bod12_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->BOD12.reg ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_bod12_reg_t hri_supc_read_BOD12_reg(const void *const hw)
{
	return ((Supc *)hw)->BOD12.reg;
}

static inline void hri_supc_set_VREG_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_ENABLE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREG_ENABLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_ENABLE_Msk) >> SUPC_VREG_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREG_ENABLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_ENABLE_Msk;
	tmp |= value << SUPC_VREG_ENABLE_Pos;
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_ENABLE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_ENABLE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_ENABLE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREG_STDBYPL0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_STDBYPL0_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREG_STDBYPL0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_STDBYPL0_Msk) >> SUPC_VREG_STDBYPL0_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREG_STDBYPL0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_STDBYPL0_Msk;
	tmp |= value << SUPC_VREG_STDBYPL0_Pos;
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_STDBYPL0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_STDBYPL0_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_STDBYPL0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_STDBYPL0_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREG_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREG_RUNSTDBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_RUNSTDBY_Msk) >> SUPC_VREG_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREG_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_RUNSTDBY_Msk;
	tmp |= value << SUPC_VREG_RUNSTDBY_Pos;
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREG_LPEFF_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_LPEFF_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREG_LPEFF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_LPEFF_Msk) >> SUPC_VREG_LPEFF_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREG_LPEFF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_LPEFF_Msk;
	tmp |= value << SUPC_VREG_LPEFF_Pos;
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_LPEFF_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_LPEFF_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_LPEFF_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_LPEFF_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREG_VREFSEL_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_VREFSEL_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREG_VREFSEL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_VREFSEL_Msk) >> SUPC_VREG_VREFSEL_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREG_VREFSEL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_VREFSEL_Msk;
	tmp |= value << SUPC_VREG_VREFSEL_Pos;
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_VREFSEL_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_VREFSEL_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_VREFSEL_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_VREFSEL_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREG_SEL_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_SEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vreg_reg_t hri_supc_get_VREG_SEL_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_SEL(mask)) >> SUPC_VREG_SEL_Pos;
	return tmp;
}

static inline void hri_supc_write_VREG_SEL_bf(const void *const hw, hri_supc_vreg_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_SEL_Msk;
	tmp |= SUPC_VREG_SEL(data);
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_SEL_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_SEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_SEL_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_SEL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vreg_reg_t hri_supc_read_VREG_SEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_SEL_Msk) >> SUPC_VREG_SEL_Pos;
	return tmp;
}

static inline void hri_supc_set_VREG_VSVSTEP_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_VSVSTEP(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vreg_reg_t hri_supc_get_VREG_VSVSTEP_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_VSVSTEP(mask)) >> SUPC_VREG_VSVSTEP_Pos;
	return tmp;
}

static inline void hri_supc_write_VREG_VSVSTEP_bf(const void *const hw, hri_supc_vreg_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_VSVSTEP_Msk;
	tmp |= SUPC_VREG_VSVSTEP(data);
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_VSVSTEP_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_VSVSTEP(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_VSVSTEP_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_VSVSTEP(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vreg_reg_t hri_supc_read_VREG_VSVSTEP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_VSVSTEP_Msk) >> SUPC_VREG_VSVSTEP_Pos;
	return tmp;
}

static inline void hri_supc_set_VREG_VSPER_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg |= SUPC_VREG_VSPER(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vreg_reg_t hri_supc_get_VREG_VSPER_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_VSPER(mask)) >> SUPC_VREG_VSPER_Pos;
	return tmp;
}

static inline void hri_supc_write_VREG_VSPER_bf(const void *const hw, hri_supc_vreg_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREG.reg;
	tmp &= ~SUPC_VREG_VSPER_Msk;
	tmp |= SUPC_VREG_VSPER(data);
	((Supc *)hw)->VREG.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREG_VSPER_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg &= ~SUPC_VREG_VSPER(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREG_VSPER_bf(const void *const hw, hri_supc_vreg_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREG.reg ^= SUPC_VREG_VSPER(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vreg_reg_t hri_supc_read_VREG_VSPER_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREG.reg;
	tmp = (tmp & SUPC_VREG_VSPER_Msk) >> SUPC_VREG_VSPER_Pos;
	return tmp;
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
	((Supc *)hw)->VREF.reg |= SUPC_VREF_TSEN_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREF_TSEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_TSEN_Msk) >> SUPC_VREF_TSEN_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREF_TSEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_TSEN_Msk;
	tmp |= value << SUPC_VREF_TSEN_Pos;
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_TSEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_TSEN_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_TSEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_TSEN_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREF_VREFOE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= SUPC_VREF_VREFOE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREF_VREFOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_VREFOE_Msk) >> SUPC_VREF_VREFOE_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREF_VREFOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_VREFOE_Msk;
	tmp |= value << SUPC_VREF_VREFOE_Pos;
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_VREFOE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_VREFOE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_VREFOE_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_VREFOE_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREF_TSSEL_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= SUPC_VREF_TSSEL_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREF_TSSEL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_TSSEL_Msk) >> SUPC_VREF_TSSEL_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREF_TSSEL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_TSSEL_Msk;
	tmp |= value << SUPC_VREF_TSSEL_Pos;
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_TSSEL_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_TSSEL_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_TSSEL_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_TSSEL_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREF_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= SUPC_VREF_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREF_RUNSTDBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_RUNSTDBY_Msk) >> SUPC_VREF_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREF_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_RUNSTDBY_Msk;
	tmp |= value << SUPC_VREF_RUNSTDBY_Pos;
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_RUNSTDBY_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_RUNSTDBY_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREF_ONDEMAND_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg |= SUPC_VREF_ONDEMAND_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREF_ONDEMAND_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREF.reg;
	tmp = (tmp & SUPC_VREF_ONDEMAND_Msk) >> SUPC_VREF_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREF_ONDEMAND_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREF.reg;
	tmp &= ~SUPC_VREF_ONDEMAND_Msk;
	tmp |= value << SUPC_VREF_ONDEMAND_Pos;
	((Supc *)hw)->VREF.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREF_ONDEMAND_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg &= ~SUPC_VREF_ONDEMAND_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREF_ONDEMAND_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREF.reg ^= SUPC_VREF_ONDEMAND_Msk;
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

static inline void hri_supc_set_EVCTRL_BOD33DETEO_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg |= SUPC_EVCTRL_BOD33DETEO_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_EVCTRL_BOD33DETEO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->EVCTRL.reg;
	tmp = (tmp & SUPC_EVCTRL_BOD33DETEO_Msk) >> SUPC_EVCTRL_BOD33DETEO_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_EVCTRL_BOD33DETEO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->EVCTRL.reg;
	tmp &= ~SUPC_EVCTRL_BOD33DETEO_Msk;
	tmp |= value << SUPC_EVCTRL_BOD33DETEO_Pos;
	((Supc *)hw)->EVCTRL.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_EVCTRL_BOD33DETEO_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg &= ~SUPC_EVCTRL_BOD33DETEO_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_EVCTRL_BOD33DETEO_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg ^= SUPC_EVCTRL_BOD33DETEO_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_EVCTRL_BOD12DETEO_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg |= SUPC_EVCTRL_BOD12DETEO_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_EVCTRL_BOD12DETEO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->EVCTRL.reg;
	tmp = (tmp & SUPC_EVCTRL_BOD12DETEO_Msk) >> SUPC_EVCTRL_BOD12DETEO_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_EVCTRL_BOD12DETEO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->EVCTRL.reg;
	tmp &= ~SUPC_EVCTRL_BOD12DETEO_Msk;
	tmp |= value << SUPC_EVCTRL_BOD12DETEO_Pos;
	((Supc *)hw)->EVCTRL.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_EVCTRL_BOD12DETEO_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg &= ~SUPC_EVCTRL_BOD12DETEO_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_EVCTRL_BOD12DETEO_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg ^= SUPC_EVCTRL_BOD12DETEO_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_EVCTRL_reg(const void *const hw, hri_supc_evctrl_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_evctrl_reg_t hri_supc_get_EVCTRL_reg(const void *const hw, hri_supc_evctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_EVCTRL_reg(const void *const hw, hri_supc_evctrl_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_EVCTRL_reg(const void *const hw, hri_supc_evctrl_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_EVCTRL_reg(const void *const hw, hri_supc_evctrl_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->EVCTRL.reg ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_evctrl_reg_t hri_supc_read_EVCTRL_reg(const void *const hw)
{
	return ((Supc *)hw)->EVCTRL.reg;
}

static inline void hri_supc_set_VREGSUSP_VREGSEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREGSUSP.reg |= SUPC_VREGSUSP_VREGSEN_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_VREGSUSP_VREGSEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREGSUSP.reg;
	tmp = (tmp & SUPC_VREGSUSP_VREGSEN_Msk) >> SUPC_VREGSUSP_VREGSEN_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_VREGSUSP_VREGSEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->VREGSUSP.reg;
	tmp &= ~SUPC_VREGSUSP_VREGSEN_Msk;
	tmp |= value << SUPC_VREGSUSP_VREGSEN_Pos;
	((Supc *)hw)->VREGSUSP.reg = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREGSUSP_VREGSEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREGSUSP.reg &= ~SUPC_VREGSUSP_VREGSEN_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREGSUSP_VREGSEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREGSUSP.reg ^= SUPC_VREGSUSP_VREGSEN_Msk;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_VREGSUSP_reg(const void *const hw, hri_supc_vregsusp_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREGSUSP.reg |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vregsusp_reg_t hri_supc_get_VREGSUSP_reg(const void *const hw, hri_supc_vregsusp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->VREGSUSP.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_VREGSUSP_reg(const void *const hw, hri_supc_vregsusp_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREGSUSP.reg = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_VREGSUSP_reg(const void *const hw, hri_supc_vregsusp_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREGSUSP.reg &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_VREGSUSP_reg(const void *const hw, hri_supc_vregsusp_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->VREGSUSP.reg ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_vregsusp_reg_t hri_supc_read_VREGSUSP_reg(const void *const hw)
{
	return ((Supc *)hw)->VREGSUSP.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SUPC_L10_H_INCLUDED */
#endif /* _SAML10_SUPC_COMPONENT_ */
