/**
 * \file
 *
 * \brief SAM EVSYS
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

#ifdef _SAML10_EVSYS_COMPONENT_
#ifndef _HRI_EVSYS_L10_H_INCLUDED_
#define _HRI_EVSYS_L10_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_EVSYS_CRITICAL_SECTIONS)
#define EVSYS_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define EVSYS_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define EVSYS_CRITICAL_SECTION_ENTER()
#define EVSYS_CRITICAL_SECTION_LEAVE()
#endif

typedef uint16_t hri_evsys_intpend_reg_t;
typedef uint32_t hri_evsys_busych_reg_t;
typedef uint32_t hri_evsys_channel_reg_t;
typedef uint32_t hri_evsys_intstatus_reg_t;
typedef uint32_t hri_evsys_nonsecchan_reg_t;
typedef uint32_t hri_evsys_nonsecuser_reg_t;
typedef uint32_t hri_evsys_nschkchan_reg_t;
typedef uint32_t hri_evsys_nschkuser_reg_t;
typedef uint32_t hri_evsys_readyusr_reg_t;
typedef uint32_t hri_evsys_swevt_reg_t;
typedef uint32_t hri_evsyschannel_channel_reg_t;
typedef uint8_t  hri_evsys_chintenset_reg_t;
typedef uint8_t  hri_evsys_chintflag_reg_t;
typedef uint8_t  hri_evsys_chstatus_reg_t;
typedef uint8_t  hri_evsys_ctrla_reg_t;
typedef uint8_t  hri_evsys_intenset_reg_t;
typedef uint8_t  hri_evsys_intflag_reg_t;
typedef uint8_t  hri_evsys_prictrl_reg_t;
typedef uint8_t  hri_evsys_user_reg_t;
typedef uint8_t  hri_evsyschannel_chintenset_reg_t;
typedef uint8_t  hri_evsyschannel_chintflag_reg_t;
typedef uint8_t  hri_evsyschannel_chstatus_reg_t;

static inline bool hri_evsys_get_INTFLAG_NSCHK_bit(const void *const hw)
{
	return (((Evsys *)hw)->INTFLAG.reg & EVSYS_INTFLAG_NSCHK_Msk) >> EVSYS_INTFLAG_NSCHK_Pos;
}

static inline void hri_evsys_clear_INTFLAG_NSCHK_bit(const void *const hw)
{
	((Evsys *)hw)->INTFLAG.reg = EVSYS_INTFLAG_NSCHK_Msk;
}

static inline bool hri_evsys_get_interrupt_NSCHK_bit(const void *const hw)
{
	return (((Evsys *)hw)->INTFLAG.reg & EVSYS_INTFLAG_NSCHK_Msk) >> EVSYS_INTFLAG_NSCHK_Pos;
}

static inline void hri_evsys_clear_interrupt_NSCHK_bit(const void *const hw)
{
	((Evsys *)hw)->INTFLAG.reg = EVSYS_INTFLAG_NSCHK_Msk;
}

static inline hri_evsys_intflag_reg_t hri_evsys_get_INTFLAG_reg(const void *const hw, hri_evsys_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_intflag_reg_t hri_evsys_read_INTFLAG_reg(const void *const hw)
{
	return ((Evsys *)hw)->INTFLAG.reg;
}

static inline void hri_evsys_clear_INTFLAG_reg(const void *const hw, hri_evsys_intflag_reg_t mask)
{
	((Evsys *)hw)->INTFLAG.reg = mask;
}

static inline void hri_evsys_set_INTEN_NSCHK_bit(const void *const hw)
{
	((Evsys *)hw)->INTENSET.reg = EVSYS_INTENSET_NSCHK_Msk;
}

static inline bool hri_evsys_get_INTEN_NSCHK_bit(const void *const hw)
{
	return (((Evsys *)hw)->INTENSET.reg & EVSYS_INTENSET_NSCHK_Msk) >> EVSYS_INTENSET_NSCHK_Pos;
}

static inline void hri_evsys_write_INTEN_NSCHK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Evsys *)hw)->INTENCLR.reg = EVSYS_INTENSET_NSCHK_Msk;
	} else {
		((Evsys *)hw)->INTENSET.reg = EVSYS_INTENSET_NSCHK_Msk;
	}
}

static inline void hri_evsys_clear_INTEN_NSCHK_bit(const void *const hw)
{
	((Evsys *)hw)->INTENCLR.reg = EVSYS_INTENSET_NSCHK_Msk;
}

static inline void hri_evsys_set_INTEN_reg(const void *const hw, hri_evsys_intenset_reg_t mask)
{
	((Evsys *)hw)->INTENSET.reg = mask;
}

static inline hri_evsys_intenset_reg_t hri_evsys_get_INTEN_reg(const void *const hw, hri_evsys_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_intenset_reg_t hri_evsys_read_INTEN_reg(const void *const hw)
{
	return ((Evsys *)hw)->INTENSET.reg;
}

static inline void hri_evsys_write_INTEN_reg(const void *const hw, hri_evsys_intenset_reg_t data)
{
	((Evsys *)hw)->INTENSET.reg = data;
	((Evsys *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_evsys_clear_INTEN_reg(const void *const hw, hri_evsys_intenset_reg_t mask)
{
	((Evsys *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_evsys_get_INTSTATUS_CHINT0_bit(const void *const hw)
{
	return (((Evsys *)hw)->INTSTATUS.reg & EVSYS_INTSTATUS_CHINT0_Msk) >> EVSYS_INTSTATUS_CHINT0_Pos;
}

static inline bool hri_evsys_get_INTSTATUS_CHINT1_bit(const void *const hw)
{
	return (((Evsys *)hw)->INTSTATUS.reg & EVSYS_INTSTATUS_CHINT1_Msk) >> EVSYS_INTSTATUS_CHINT1_Pos;
}

static inline bool hri_evsys_get_INTSTATUS_CHINT2_bit(const void *const hw)
{
	return (((Evsys *)hw)->INTSTATUS.reg & EVSYS_INTSTATUS_CHINT2_Msk) >> EVSYS_INTSTATUS_CHINT2_Pos;
}

static inline bool hri_evsys_get_INTSTATUS_CHINT3_bit(const void *const hw)
{
	return (((Evsys *)hw)->INTSTATUS.reg & EVSYS_INTSTATUS_CHINT3_Msk) >> EVSYS_INTSTATUS_CHINT3_Pos;
}

static inline hri_evsys_intstatus_reg_t hri_evsys_get_INTSTATUS_reg(const void *const         hw,
                                                                    hri_evsys_intstatus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->INTSTATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_intstatus_reg_t hri_evsys_read_INTSTATUS_reg(const void *const hw)
{
	return ((Evsys *)hw)->INTSTATUS.reg;
}

static inline bool hri_evsys_get_BUSYCH_BUSYCH0_bit(const void *const hw)
{
	return (((Evsys *)hw)->BUSYCH.reg & EVSYS_BUSYCH_BUSYCH0_Msk) >> EVSYS_BUSYCH_BUSYCH0_Pos;
}

static inline bool hri_evsys_get_BUSYCH_BUSYCH1_bit(const void *const hw)
{
	return (((Evsys *)hw)->BUSYCH.reg & EVSYS_BUSYCH_BUSYCH1_Msk) >> EVSYS_BUSYCH_BUSYCH1_Pos;
}

static inline bool hri_evsys_get_BUSYCH_BUSYCH2_bit(const void *const hw)
{
	return (((Evsys *)hw)->BUSYCH.reg & EVSYS_BUSYCH_BUSYCH2_Msk) >> EVSYS_BUSYCH_BUSYCH2_Pos;
}

static inline bool hri_evsys_get_BUSYCH_BUSYCH3_bit(const void *const hw)
{
	return (((Evsys *)hw)->BUSYCH.reg & EVSYS_BUSYCH_BUSYCH3_Msk) >> EVSYS_BUSYCH_BUSYCH3_Pos;
}

static inline hri_evsys_busych_reg_t hri_evsys_get_BUSYCH_reg(const void *const hw, hri_evsys_busych_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->BUSYCH.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_busych_reg_t hri_evsys_read_BUSYCH_reg(const void *const hw)
{
	return ((Evsys *)hw)->BUSYCH.reg;
}

static inline bool hri_evsys_get_READYUSR_READYUSR0_bit(const void *const hw)
{
	return (((Evsys *)hw)->READYUSR.reg & EVSYS_READYUSR_READYUSR0_Msk) >> EVSYS_READYUSR_READYUSR0_Pos;
}

static inline bool hri_evsys_get_READYUSR_READYUSR1_bit(const void *const hw)
{
	return (((Evsys *)hw)->READYUSR.reg & EVSYS_READYUSR_READYUSR1_Msk) >> EVSYS_READYUSR_READYUSR1_Pos;
}

static inline bool hri_evsys_get_READYUSR_READYUSR2_bit(const void *const hw)
{
	return (((Evsys *)hw)->READYUSR.reg & EVSYS_READYUSR_READYUSR2_Msk) >> EVSYS_READYUSR_READYUSR2_Pos;
}

static inline bool hri_evsys_get_READYUSR_READYUSR3_bit(const void *const hw)
{
	return (((Evsys *)hw)->READYUSR.reg & EVSYS_READYUSR_READYUSR3_Msk) >> EVSYS_READYUSR_READYUSR3_Pos;
}

static inline hri_evsys_readyusr_reg_t hri_evsys_get_READYUSR_reg(const void *const hw, hri_evsys_readyusr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->READYUSR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_readyusr_reg_t hri_evsys_read_READYUSR_reg(const void *const hw)
{
	return ((Evsys *)hw)->READYUSR.reg;
}

static inline void hri_evsys_set_PRICTRL_RREN_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg |= EVSYS_PRICTRL_RREN_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_PRICTRL_RREN_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->PRICTRL.reg;
	tmp = (tmp & EVSYS_PRICTRL_RREN_Msk) >> EVSYS_PRICTRL_RREN_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_PRICTRL_RREN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->PRICTRL.reg;
	tmp &= ~EVSYS_PRICTRL_RREN_Msk;
	tmp |= value << EVSYS_PRICTRL_RREN_Pos;
	((Evsys *)hw)->PRICTRL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_PRICTRL_RREN_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg &= ~EVSYS_PRICTRL_RREN_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_PRICTRL_RREN_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg ^= EVSYS_PRICTRL_RREN_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_PRICTRL_PRI_bf(const void *const hw, hri_evsys_prictrl_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg |= EVSYS_PRICTRL_PRI(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_prictrl_reg_t hri_evsys_get_PRICTRL_PRI_bf(const void *const hw, hri_evsys_prictrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->PRICTRL.reg;
	tmp = (tmp & EVSYS_PRICTRL_PRI(mask)) >> EVSYS_PRICTRL_PRI_Pos;
	return tmp;
}

static inline void hri_evsys_write_PRICTRL_PRI_bf(const void *const hw, hri_evsys_prictrl_reg_t data)
{
	uint8_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->PRICTRL.reg;
	tmp &= ~EVSYS_PRICTRL_PRI_Msk;
	tmp |= EVSYS_PRICTRL_PRI(data);
	((Evsys *)hw)->PRICTRL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_PRICTRL_PRI_bf(const void *const hw, hri_evsys_prictrl_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg &= ~EVSYS_PRICTRL_PRI(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_PRICTRL_PRI_bf(const void *const hw, hri_evsys_prictrl_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg ^= EVSYS_PRICTRL_PRI(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_prictrl_reg_t hri_evsys_read_PRICTRL_PRI_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->PRICTRL.reg;
	tmp = (tmp & EVSYS_PRICTRL_PRI_Msk) >> EVSYS_PRICTRL_PRI_Pos;
	return tmp;
}

static inline void hri_evsys_set_PRICTRL_reg(const void *const hw, hri_evsys_prictrl_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg |= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_prictrl_reg_t hri_evsys_get_PRICTRL_reg(const void *const hw, hri_evsys_prictrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->PRICTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_evsys_write_PRICTRL_reg(const void *const hw, hri_evsys_prictrl_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_PRICTRL_reg(const void *const hw, hri_evsys_prictrl_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg &= ~mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_PRICTRL_reg(const void *const hw, hri_evsys_prictrl_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->PRICTRL.reg ^= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_prictrl_reg_t hri_evsys_read_PRICTRL_reg(const void *const hw)
{
	return ((Evsys *)hw)->PRICTRL.reg;
}

static inline void hri_evsys_set_INTPEND_OVR_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg |= EVSYS_INTPEND_OVR_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_INTPEND_OVR_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp = (tmp & EVSYS_INTPEND_OVR_Msk) >> EVSYS_INTPEND_OVR_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_INTPEND_OVR_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp &= ~EVSYS_INTPEND_OVR_Msk;
	tmp |= value << EVSYS_INTPEND_OVR_Pos;
	((Evsys *)hw)->INTPEND.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_INTPEND_OVR_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg &= ~EVSYS_INTPEND_OVR_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_INTPEND_OVR_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg ^= EVSYS_INTPEND_OVR_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_INTPEND_EVD_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg |= EVSYS_INTPEND_EVD_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_INTPEND_EVD_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp = (tmp & EVSYS_INTPEND_EVD_Msk) >> EVSYS_INTPEND_EVD_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_INTPEND_EVD_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp &= ~EVSYS_INTPEND_EVD_Msk;
	tmp |= value << EVSYS_INTPEND_EVD_Pos;
	((Evsys *)hw)->INTPEND.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_INTPEND_EVD_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg &= ~EVSYS_INTPEND_EVD_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_INTPEND_EVD_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg ^= EVSYS_INTPEND_EVD_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_INTPEND_READY_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg |= EVSYS_INTPEND_READY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_INTPEND_READY_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp = (tmp & EVSYS_INTPEND_READY_Msk) >> EVSYS_INTPEND_READY_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_INTPEND_READY_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp &= ~EVSYS_INTPEND_READY_Msk;
	tmp |= value << EVSYS_INTPEND_READY_Pos;
	((Evsys *)hw)->INTPEND.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_INTPEND_READY_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg &= ~EVSYS_INTPEND_READY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_INTPEND_READY_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg ^= EVSYS_INTPEND_READY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_INTPEND_BUSY_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg |= EVSYS_INTPEND_BUSY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_INTPEND_BUSY_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp = (tmp & EVSYS_INTPEND_BUSY_Msk) >> EVSYS_INTPEND_BUSY_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_INTPEND_BUSY_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp &= ~EVSYS_INTPEND_BUSY_Msk;
	tmp |= value << EVSYS_INTPEND_BUSY_Pos;
	((Evsys *)hw)->INTPEND.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_INTPEND_BUSY_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg &= ~EVSYS_INTPEND_BUSY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_INTPEND_BUSY_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg ^= EVSYS_INTPEND_BUSY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_INTPEND_ID_bf(const void *const hw, hri_evsys_intpend_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg |= EVSYS_INTPEND_ID(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_intpend_reg_t hri_evsys_get_INTPEND_ID_bf(const void *const hw, hri_evsys_intpend_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp = (tmp & EVSYS_INTPEND_ID(mask)) >> EVSYS_INTPEND_ID_Pos;
	return tmp;
}

static inline void hri_evsys_write_INTPEND_ID_bf(const void *const hw, hri_evsys_intpend_reg_t data)
{
	uint16_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp &= ~EVSYS_INTPEND_ID_Msk;
	tmp |= EVSYS_INTPEND_ID(data);
	((Evsys *)hw)->INTPEND.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_INTPEND_ID_bf(const void *const hw, hri_evsys_intpend_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg &= ~EVSYS_INTPEND_ID(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_INTPEND_ID_bf(const void *const hw, hri_evsys_intpend_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg ^= EVSYS_INTPEND_ID(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_intpend_reg_t hri_evsys_read_INTPEND_ID_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp = (tmp & EVSYS_INTPEND_ID_Msk) >> EVSYS_INTPEND_ID_Pos;
	return tmp;
}

static inline void hri_evsys_set_INTPEND_reg(const void *const hw, hri_evsys_intpend_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg |= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_intpend_reg_t hri_evsys_get_INTPEND_reg(const void *const hw, hri_evsys_intpend_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Evsys *)hw)->INTPEND.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_evsys_write_INTPEND_reg(const void *const hw, hri_evsys_intpend_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_INTPEND_reg(const void *const hw, hri_evsys_intpend_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg &= ~mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_INTPEND_reg(const void *const hw, hri_evsys_intpend_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->INTPEND.reg ^= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_intpend_reg_t hri_evsys_read_INTPEND_reg(const void *const hw)
{
	return ((Evsys *)hw)->INTPEND.reg;
}

static inline void hri_evsys_set_USER_CHANNEL_bf(const void *const hw, uint8_t index, hri_evsys_user_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->USER[index].reg |= EVSYS_USER_CHANNEL(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_user_reg_t hri_evsys_get_USER_CHANNEL_bf(const void *const hw, uint8_t index,
                                                                 hri_evsys_user_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->USER[index].reg;
	tmp = (tmp & EVSYS_USER_CHANNEL(mask)) >> EVSYS_USER_CHANNEL_Pos;
	return tmp;
}

static inline void hri_evsys_write_USER_CHANNEL_bf(const void *const hw, uint8_t index, hri_evsys_user_reg_t data)
{
	uint8_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->USER[index].reg;
	tmp &= ~EVSYS_USER_CHANNEL_Msk;
	tmp |= EVSYS_USER_CHANNEL(data);
	((Evsys *)hw)->USER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_USER_CHANNEL_bf(const void *const hw, uint8_t index, hri_evsys_user_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->USER[index].reg &= ~EVSYS_USER_CHANNEL(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_USER_CHANNEL_bf(const void *const hw, uint8_t index, hri_evsys_user_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->USER[index].reg ^= EVSYS_USER_CHANNEL(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_user_reg_t hri_evsys_read_USER_CHANNEL_bf(const void *const hw, uint8_t index)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->USER[index].reg;
	tmp = (tmp & EVSYS_USER_CHANNEL_Msk) >> EVSYS_USER_CHANNEL_Pos;
	return tmp;
}

static inline void hri_evsys_set_USER_reg(const void *const hw, uint8_t index, hri_evsys_user_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->USER[index].reg |= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_user_reg_t hri_evsys_get_USER_reg(const void *const hw, uint8_t index,
                                                          hri_evsys_user_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->USER[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_evsys_write_USER_reg(const void *const hw, uint8_t index, hri_evsys_user_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->USER[index].reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_USER_reg(const void *const hw, uint8_t index, hri_evsys_user_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->USER[index].reg &= ~mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_USER_reg(const void *const hw, uint8_t index, hri_evsys_user_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->USER[index].reg ^= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_user_reg_t hri_evsys_read_USER_reg(const void *const hw, uint8_t index)
{
	return ((Evsys *)hw)->USER[index].reg;
}

static inline void hri_evsys_set_NONSECCHAN_CHANNEL0_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg |= EVSYS_NONSECCHAN_CHANNEL0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECCHAN_CHANNEL0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp = (tmp & EVSYS_NONSECCHAN_CHANNEL0_Msk) >> EVSYS_NONSECCHAN_CHANNEL0_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECCHAN_CHANNEL0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp &= ~EVSYS_NONSECCHAN_CHANNEL0_Msk;
	tmp |= value << EVSYS_NONSECCHAN_CHANNEL0_Pos;
	((Evsys *)hw)->NONSECCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECCHAN_CHANNEL0_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg &= ~EVSYS_NONSECCHAN_CHANNEL0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECCHAN_CHANNEL0_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg ^= EVSYS_NONSECCHAN_CHANNEL0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECCHAN_CHANNEL1_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg |= EVSYS_NONSECCHAN_CHANNEL1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECCHAN_CHANNEL1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp = (tmp & EVSYS_NONSECCHAN_CHANNEL1_Msk) >> EVSYS_NONSECCHAN_CHANNEL1_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECCHAN_CHANNEL1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp &= ~EVSYS_NONSECCHAN_CHANNEL1_Msk;
	tmp |= value << EVSYS_NONSECCHAN_CHANNEL1_Pos;
	((Evsys *)hw)->NONSECCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECCHAN_CHANNEL1_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg &= ~EVSYS_NONSECCHAN_CHANNEL1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECCHAN_CHANNEL1_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg ^= EVSYS_NONSECCHAN_CHANNEL1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECCHAN_CHANNEL2_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg |= EVSYS_NONSECCHAN_CHANNEL2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECCHAN_CHANNEL2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp = (tmp & EVSYS_NONSECCHAN_CHANNEL2_Msk) >> EVSYS_NONSECCHAN_CHANNEL2_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECCHAN_CHANNEL2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp &= ~EVSYS_NONSECCHAN_CHANNEL2_Msk;
	tmp |= value << EVSYS_NONSECCHAN_CHANNEL2_Pos;
	((Evsys *)hw)->NONSECCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECCHAN_CHANNEL2_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg &= ~EVSYS_NONSECCHAN_CHANNEL2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECCHAN_CHANNEL2_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg ^= EVSYS_NONSECCHAN_CHANNEL2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECCHAN_CHANNEL3_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg |= EVSYS_NONSECCHAN_CHANNEL3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECCHAN_CHANNEL3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp = (tmp & EVSYS_NONSECCHAN_CHANNEL3_Msk) >> EVSYS_NONSECCHAN_CHANNEL3_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECCHAN_CHANNEL3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp &= ~EVSYS_NONSECCHAN_CHANNEL3_Msk;
	tmp |= value << EVSYS_NONSECCHAN_CHANNEL3_Pos;
	((Evsys *)hw)->NONSECCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECCHAN_CHANNEL3_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg &= ~EVSYS_NONSECCHAN_CHANNEL3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECCHAN_CHANNEL3_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg ^= EVSYS_NONSECCHAN_CHANNEL3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECCHAN_CHANNEL4_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg |= EVSYS_NONSECCHAN_CHANNEL4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECCHAN_CHANNEL4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp = (tmp & EVSYS_NONSECCHAN_CHANNEL4_Msk) >> EVSYS_NONSECCHAN_CHANNEL4_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECCHAN_CHANNEL4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp &= ~EVSYS_NONSECCHAN_CHANNEL4_Msk;
	tmp |= value << EVSYS_NONSECCHAN_CHANNEL4_Pos;
	((Evsys *)hw)->NONSECCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECCHAN_CHANNEL4_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg &= ~EVSYS_NONSECCHAN_CHANNEL4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECCHAN_CHANNEL4_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg ^= EVSYS_NONSECCHAN_CHANNEL4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECCHAN_CHANNEL5_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg |= EVSYS_NONSECCHAN_CHANNEL5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECCHAN_CHANNEL5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp = (tmp & EVSYS_NONSECCHAN_CHANNEL5_Msk) >> EVSYS_NONSECCHAN_CHANNEL5_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECCHAN_CHANNEL5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp &= ~EVSYS_NONSECCHAN_CHANNEL5_Msk;
	tmp |= value << EVSYS_NONSECCHAN_CHANNEL5_Pos;
	((Evsys *)hw)->NONSECCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECCHAN_CHANNEL5_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg &= ~EVSYS_NONSECCHAN_CHANNEL5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECCHAN_CHANNEL5_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg ^= EVSYS_NONSECCHAN_CHANNEL5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECCHAN_CHANNEL6_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg |= EVSYS_NONSECCHAN_CHANNEL6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECCHAN_CHANNEL6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp = (tmp & EVSYS_NONSECCHAN_CHANNEL6_Msk) >> EVSYS_NONSECCHAN_CHANNEL6_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECCHAN_CHANNEL6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp &= ~EVSYS_NONSECCHAN_CHANNEL6_Msk;
	tmp |= value << EVSYS_NONSECCHAN_CHANNEL6_Pos;
	((Evsys *)hw)->NONSECCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECCHAN_CHANNEL6_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg &= ~EVSYS_NONSECCHAN_CHANNEL6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECCHAN_CHANNEL6_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg ^= EVSYS_NONSECCHAN_CHANNEL6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECCHAN_CHANNEL7_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg |= EVSYS_NONSECCHAN_CHANNEL7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECCHAN_CHANNEL7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp = (tmp & EVSYS_NONSECCHAN_CHANNEL7_Msk) >> EVSYS_NONSECCHAN_CHANNEL7_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECCHAN_CHANNEL7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp &= ~EVSYS_NONSECCHAN_CHANNEL7_Msk;
	tmp |= value << EVSYS_NONSECCHAN_CHANNEL7_Pos;
	((Evsys *)hw)->NONSECCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECCHAN_CHANNEL7_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg &= ~EVSYS_NONSECCHAN_CHANNEL7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECCHAN_CHANNEL7_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg ^= EVSYS_NONSECCHAN_CHANNEL7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECCHAN_reg(const void *const hw, hri_evsys_nonsecchan_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg |= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_nonsecchan_reg_t hri_evsys_get_NONSECCHAN_reg(const void *const          hw,
                                                                      hri_evsys_nonsecchan_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECCHAN.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_evsys_write_NONSECCHAN_reg(const void *const hw, hri_evsys_nonsecchan_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECCHAN_reg(const void *const hw, hri_evsys_nonsecchan_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg &= ~mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECCHAN_reg(const void *const hw, hri_evsys_nonsecchan_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECCHAN.reg ^= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_nonsecchan_reg_t hri_evsys_read_NONSECCHAN_reg(const void *const hw)
{
	return ((Evsys *)hw)->NONSECCHAN.reg;
}

static inline void hri_evsys_set_NSCHKCHAN_CHANNEL0_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg |= EVSYS_NSCHKCHAN_CHANNEL0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKCHAN_CHANNEL0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp = (tmp & EVSYS_NSCHKCHAN_CHANNEL0_Msk) >> EVSYS_NSCHKCHAN_CHANNEL0_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKCHAN_CHANNEL0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp &= ~EVSYS_NSCHKCHAN_CHANNEL0_Msk;
	tmp |= value << EVSYS_NSCHKCHAN_CHANNEL0_Pos;
	((Evsys *)hw)->NSCHKCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKCHAN_CHANNEL0_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg &= ~EVSYS_NSCHKCHAN_CHANNEL0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKCHAN_CHANNEL0_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg ^= EVSYS_NSCHKCHAN_CHANNEL0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKCHAN_CHANNEL1_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg |= EVSYS_NSCHKCHAN_CHANNEL1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKCHAN_CHANNEL1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp = (tmp & EVSYS_NSCHKCHAN_CHANNEL1_Msk) >> EVSYS_NSCHKCHAN_CHANNEL1_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKCHAN_CHANNEL1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp &= ~EVSYS_NSCHKCHAN_CHANNEL1_Msk;
	tmp |= value << EVSYS_NSCHKCHAN_CHANNEL1_Pos;
	((Evsys *)hw)->NSCHKCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKCHAN_CHANNEL1_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg &= ~EVSYS_NSCHKCHAN_CHANNEL1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKCHAN_CHANNEL1_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg ^= EVSYS_NSCHKCHAN_CHANNEL1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKCHAN_CHANNEL2_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg |= EVSYS_NSCHKCHAN_CHANNEL2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKCHAN_CHANNEL2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp = (tmp & EVSYS_NSCHKCHAN_CHANNEL2_Msk) >> EVSYS_NSCHKCHAN_CHANNEL2_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKCHAN_CHANNEL2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp &= ~EVSYS_NSCHKCHAN_CHANNEL2_Msk;
	tmp |= value << EVSYS_NSCHKCHAN_CHANNEL2_Pos;
	((Evsys *)hw)->NSCHKCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKCHAN_CHANNEL2_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg &= ~EVSYS_NSCHKCHAN_CHANNEL2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKCHAN_CHANNEL2_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg ^= EVSYS_NSCHKCHAN_CHANNEL2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKCHAN_CHANNEL3_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg |= EVSYS_NSCHKCHAN_CHANNEL3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKCHAN_CHANNEL3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp = (tmp & EVSYS_NSCHKCHAN_CHANNEL3_Msk) >> EVSYS_NSCHKCHAN_CHANNEL3_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKCHAN_CHANNEL3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp &= ~EVSYS_NSCHKCHAN_CHANNEL3_Msk;
	tmp |= value << EVSYS_NSCHKCHAN_CHANNEL3_Pos;
	((Evsys *)hw)->NSCHKCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKCHAN_CHANNEL3_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg &= ~EVSYS_NSCHKCHAN_CHANNEL3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKCHAN_CHANNEL3_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg ^= EVSYS_NSCHKCHAN_CHANNEL3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKCHAN_CHANNEL4_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg |= EVSYS_NSCHKCHAN_CHANNEL4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKCHAN_CHANNEL4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp = (tmp & EVSYS_NSCHKCHAN_CHANNEL4_Msk) >> EVSYS_NSCHKCHAN_CHANNEL4_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKCHAN_CHANNEL4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp &= ~EVSYS_NSCHKCHAN_CHANNEL4_Msk;
	tmp |= value << EVSYS_NSCHKCHAN_CHANNEL4_Pos;
	((Evsys *)hw)->NSCHKCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKCHAN_CHANNEL4_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg &= ~EVSYS_NSCHKCHAN_CHANNEL4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKCHAN_CHANNEL4_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg ^= EVSYS_NSCHKCHAN_CHANNEL4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKCHAN_CHANNEL5_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg |= EVSYS_NSCHKCHAN_CHANNEL5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKCHAN_CHANNEL5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp = (tmp & EVSYS_NSCHKCHAN_CHANNEL5_Msk) >> EVSYS_NSCHKCHAN_CHANNEL5_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKCHAN_CHANNEL5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp &= ~EVSYS_NSCHKCHAN_CHANNEL5_Msk;
	tmp |= value << EVSYS_NSCHKCHAN_CHANNEL5_Pos;
	((Evsys *)hw)->NSCHKCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKCHAN_CHANNEL5_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg &= ~EVSYS_NSCHKCHAN_CHANNEL5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKCHAN_CHANNEL5_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg ^= EVSYS_NSCHKCHAN_CHANNEL5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKCHAN_CHANNEL6_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg |= EVSYS_NSCHKCHAN_CHANNEL6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKCHAN_CHANNEL6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp = (tmp & EVSYS_NSCHKCHAN_CHANNEL6_Msk) >> EVSYS_NSCHKCHAN_CHANNEL6_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKCHAN_CHANNEL6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp &= ~EVSYS_NSCHKCHAN_CHANNEL6_Msk;
	tmp |= value << EVSYS_NSCHKCHAN_CHANNEL6_Pos;
	((Evsys *)hw)->NSCHKCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKCHAN_CHANNEL6_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg &= ~EVSYS_NSCHKCHAN_CHANNEL6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKCHAN_CHANNEL6_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg ^= EVSYS_NSCHKCHAN_CHANNEL6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKCHAN_CHANNEL7_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg |= EVSYS_NSCHKCHAN_CHANNEL7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKCHAN_CHANNEL7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp = (tmp & EVSYS_NSCHKCHAN_CHANNEL7_Msk) >> EVSYS_NSCHKCHAN_CHANNEL7_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKCHAN_CHANNEL7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp &= ~EVSYS_NSCHKCHAN_CHANNEL7_Msk;
	tmp |= value << EVSYS_NSCHKCHAN_CHANNEL7_Pos;
	((Evsys *)hw)->NSCHKCHAN.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKCHAN_CHANNEL7_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg &= ~EVSYS_NSCHKCHAN_CHANNEL7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKCHAN_CHANNEL7_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg ^= EVSYS_NSCHKCHAN_CHANNEL7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKCHAN_reg(const void *const hw, hri_evsys_nschkchan_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg |= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_nschkchan_reg_t hri_evsys_get_NSCHKCHAN_reg(const void *const         hw,
                                                                    hri_evsys_nschkchan_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKCHAN.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_evsys_write_NSCHKCHAN_reg(const void *const hw, hri_evsys_nschkchan_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKCHAN_reg(const void *const hw, hri_evsys_nschkchan_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg &= ~mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKCHAN_reg(const void *const hw, hri_evsys_nschkchan_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKCHAN.reg ^= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_nschkchan_reg_t hri_evsys_read_NSCHKCHAN_reg(const void *const hw)
{
	return ((Evsys *)hw)->NSCHKCHAN.reg;
}

static inline void hri_evsys_set_NONSECUSER_USER0_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER0_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER0_Msk) >> EVSYS_NONSECUSER_USER0_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER0_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER0_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER0_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER0_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER0_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER1_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER1_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER1_Msk) >> EVSYS_NONSECUSER_USER1_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER1_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER1_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER1_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER1_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER1_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER2_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER2_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER2_Msk) >> EVSYS_NONSECUSER_USER2_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER2_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER2_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER2_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER2_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER2_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER3_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER3_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER3_Msk) >> EVSYS_NONSECUSER_USER3_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER3_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER3_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER3_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER3_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER3_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER4_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER4_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER4_Msk) >> EVSYS_NONSECUSER_USER4_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER4_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER4_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER4_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER4_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER4_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER5_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER5_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER5_Msk) >> EVSYS_NONSECUSER_USER5_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER5_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER5_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER5_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER5_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER5_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER6_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER6_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER6_Msk) >> EVSYS_NONSECUSER_USER6_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER6_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER6_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER6_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER6_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER6_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER7_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER7_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER7_Msk) >> EVSYS_NONSECUSER_USER7_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER7_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER7_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER7_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER7_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER7_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER8_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER8_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER8_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER8_Msk) >> EVSYS_NONSECUSER_USER8_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER8_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER8_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER8_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER8_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER8_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER8_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER8_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER9_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER9_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER9_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER9_Msk) >> EVSYS_NONSECUSER_USER9_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER9_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER9_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER9_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER9_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER9_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER9_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER9_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER10_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER10_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER10_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER10_Msk) >> EVSYS_NONSECUSER_USER10_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER10_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER10_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER10_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER10_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER10_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER10_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER10_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER11_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER11_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER11_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER11_Msk) >> EVSYS_NONSECUSER_USER11_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER11_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER11_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER11_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER11_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER11_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER11_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER11_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER12_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER12_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER12_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER12_Msk) >> EVSYS_NONSECUSER_USER12_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER12_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER12_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER12_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER12_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER12_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER12_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER12_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER13_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER13_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER13_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER13_Msk) >> EVSYS_NONSECUSER_USER13_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER13_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER13_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER13_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER13_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER13_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER13_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER13_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER14_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER14_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER14_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER14_Msk) >> EVSYS_NONSECUSER_USER14_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER14_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER14_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER14_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER14_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER14_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER14_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER14_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER15_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER15_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER15_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER15_Msk) >> EVSYS_NONSECUSER_USER15_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER15_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER15_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER15_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER15_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER15_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER15_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER15_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER16_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER16_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER16_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER16_Msk) >> EVSYS_NONSECUSER_USER16_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER16_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER16_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER16_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER16_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER16_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER16_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER16_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER17_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER17_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER17_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER17_Msk) >> EVSYS_NONSECUSER_USER17_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER17_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER17_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER17_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER17_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER17_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER17_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER17_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER18_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER18_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER18_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER18_Msk) >> EVSYS_NONSECUSER_USER18_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER18_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER18_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER18_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER18_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER18_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER18_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER18_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER19_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER19_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER19_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER19_Msk) >> EVSYS_NONSECUSER_USER19_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER19_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER19_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER19_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER19_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER19_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER19_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER19_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER20_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER20_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER20_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER20_Msk) >> EVSYS_NONSECUSER_USER20_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER20_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER20_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER20_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER20_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER20_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER20_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER20_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER21_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER21_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER21_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER21_Msk) >> EVSYS_NONSECUSER_USER21_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER21_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER21_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER21_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER21_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER21_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER21_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER21_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_USER22_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= EVSYS_NONSECUSER_USER22_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NONSECUSER_USER22_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp = (tmp & EVSYS_NONSECUSER_USER22_Msk) >> EVSYS_NONSECUSER_USER22_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NONSECUSER_USER22_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= ~EVSYS_NONSECUSER_USER22_Msk;
	tmp |= value << EVSYS_NONSECUSER_USER22_Pos;
	((Evsys *)hw)->NONSECUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_USER22_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~EVSYS_NONSECUSER_USER22_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_USER22_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= EVSYS_NONSECUSER_USER22_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NONSECUSER_reg(const void *const hw, uint8_t index, hri_evsys_nonsecuser_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg |= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_nonsecuser_reg_t hri_evsys_get_NONSECUSER_reg(const void *const hw, uint8_t index,
                                                                      hri_evsys_nonsecuser_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NONSECUSER[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_evsys_write_NONSECUSER_reg(const void *const hw, uint8_t index, hri_evsys_nonsecuser_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NONSECUSER_reg(const void *const hw, uint8_t index, hri_evsys_nonsecuser_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg &= ~mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NONSECUSER_reg(const void *const hw, uint8_t index, hri_evsys_nonsecuser_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NONSECUSER[index].reg ^= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_nonsecuser_reg_t hri_evsys_read_NONSECUSER_reg(const void *const hw, uint8_t index)
{
	return ((Evsys *)hw)->NONSECUSER[index].reg;
}

static inline void hri_evsys_set_NSCHKUSER_USER0_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER0_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER0_Msk) >> EVSYS_NSCHKUSER_USER0_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER0_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER0_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER0_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER0_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER0_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER0_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER1_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER1_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER1_Msk) >> EVSYS_NSCHKUSER_USER1_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER1_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER1_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER1_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER1_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER1_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER1_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER2_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER2_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER2_Msk) >> EVSYS_NSCHKUSER_USER2_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER2_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER2_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER2_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER2_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER2_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER2_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER3_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER3_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER3_Msk) >> EVSYS_NSCHKUSER_USER3_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER3_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER3_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER3_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER3_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER3_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER3_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER4_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER4_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER4_Msk) >> EVSYS_NSCHKUSER_USER4_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER4_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER4_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER4_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER4_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER4_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER4_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER5_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER5_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER5_Msk) >> EVSYS_NSCHKUSER_USER5_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER5_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER5_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER5_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER5_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER5_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER5_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER6_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER6_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER6_Msk) >> EVSYS_NSCHKUSER_USER6_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER6_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER6_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER6_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER6_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER6_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER6_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER7_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER7_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER7_Msk) >> EVSYS_NSCHKUSER_USER7_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER7_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER7_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER7_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER7_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER7_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER7_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER8_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER8_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER8_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER8_Msk) >> EVSYS_NSCHKUSER_USER8_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER8_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER8_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER8_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER8_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER8_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER8_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER8_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER9_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER9_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER9_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER9_Msk) >> EVSYS_NSCHKUSER_USER9_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER9_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER9_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER9_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER9_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER9_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER9_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER9_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER10_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER10_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER10_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER10_Msk) >> EVSYS_NSCHKUSER_USER10_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER10_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER10_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER10_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER10_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER10_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER10_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER10_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER11_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER11_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER11_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER11_Msk) >> EVSYS_NSCHKUSER_USER11_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER11_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER11_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER11_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER11_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER11_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER11_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER11_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER12_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER12_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER12_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER12_Msk) >> EVSYS_NSCHKUSER_USER12_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER12_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER12_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER12_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER12_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER12_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER12_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER12_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER13_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER13_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER13_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER13_Msk) >> EVSYS_NSCHKUSER_USER13_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER13_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER13_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER13_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER13_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER13_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER13_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER13_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER14_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER14_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER14_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER14_Msk) >> EVSYS_NSCHKUSER_USER14_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER14_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER14_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER14_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER14_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER14_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER14_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER14_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER15_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER15_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER15_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER15_Msk) >> EVSYS_NSCHKUSER_USER15_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER15_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER15_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER15_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER15_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER15_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER15_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER15_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER16_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER16_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER16_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER16_Msk) >> EVSYS_NSCHKUSER_USER16_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER16_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER16_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER16_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER16_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER16_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER16_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER16_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER17_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER17_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER17_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER17_Msk) >> EVSYS_NSCHKUSER_USER17_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER17_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER17_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER17_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER17_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER17_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER17_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER17_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER18_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER18_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER18_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER18_Msk) >> EVSYS_NSCHKUSER_USER18_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER18_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER18_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER18_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER18_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER18_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER18_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER18_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER19_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER19_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER19_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER19_Msk) >> EVSYS_NSCHKUSER_USER19_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER19_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER19_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER19_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER19_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER19_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER19_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER19_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER20_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER20_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER20_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER20_Msk) >> EVSYS_NSCHKUSER_USER20_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER20_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER20_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER20_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER20_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER20_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER20_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER20_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER21_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER21_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER21_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER21_Msk) >> EVSYS_NSCHKUSER_USER21_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER21_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER21_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER21_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER21_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER21_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER21_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER21_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_USER22_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= EVSYS_NSCHKUSER_USER22_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_NSCHKUSER_USER22_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp = (tmp & EVSYS_NSCHKUSER_USER22_Msk) >> EVSYS_NSCHKUSER_USER22_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_NSCHKUSER_USER22_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= ~EVSYS_NSCHKUSER_USER22_Msk;
	tmp |= value << EVSYS_NSCHKUSER_USER22_Pos;
	((Evsys *)hw)->NSCHKUSER[index].reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_USER22_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~EVSYS_NSCHKUSER_USER22_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_USER22_bit(const void *const hw, uint8_t index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= EVSYS_NSCHKUSER_USER22_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_NSCHKUSER_reg(const void *const hw, uint8_t index, hri_evsys_nschkuser_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg |= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_nschkuser_reg_t hri_evsys_get_NSCHKUSER_reg(const void *const hw, uint8_t index,
                                                                    hri_evsys_nschkuser_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->NSCHKUSER[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_evsys_write_NSCHKUSER_reg(const void *const hw, uint8_t index, hri_evsys_nschkuser_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_NSCHKUSER_reg(const void *const hw, uint8_t index, hri_evsys_nschkuser_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg &= ~mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_NSCHKUSER_reg(const void *const hw, uint8_t index, hri_evsys_nschkuser_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->NSCHKUSER[index].reg ^= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_nschkuser_reg_t hri_evsys_read_NSCHKUSER_reg(const void *const hw, uint8_t index)
{
	return ((Evsys *)hw)->NSCHKUSER[index].reg;
}

static inline void hri_evsys_write_CTRLA_reg(const void *const hw, hri_evsys_ctrla_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->CTRLA.reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_write_SWEVT_reg(const void *const hw, hri_evsys_swevt_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->SWEVT.reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsyschannel_get_CHINTFLAG_OVR_bit(const void *const hw)
{
	return (((EvsysChannel *)hw)->CHINTFLAG.reg & EVSYS_CHINTFLAG_OVR_Msk) >> EVSYS_CHINTFLAG_OVR_Pos;
}

static inline void hri_evsyschannel_clear_CHINTFLAG_OVR_bit(const void *const hw)
{
	((EvsysChannel *)hw)->CHINTFLAG.reg = EVSYS_CHINTFLAG_OVR_Msk;
}

static inline bool hri_evsyschannel_get_CHINTFLAG_EVD_bit(const void *const hw)
{
	return (((EvsysChannel *)hw)->CHINTFLAG.reg & EVSYS_CHINTFLAG_EVD_Msk) >> EVSYS_CHINTFLAG_EVD_Pos;
}

static inline void hri_evsyschannel_clear_CHINTFLAG_EVD_bit(const void *const hw)
{
	((EvsysChannel *)hw)->CHINTFLAG.reg = EVSYS_CHINTFLAG_EVD_Msk;
}

static inline bool hri_evsyschannel_get_interrupt_OVR_bit(const void *const hw)
{
	return (((EvsysChannel *)hw)->CHINTFLAG.reg & EVSYS_CHINTFLAG_OVR_Msk) >> EVSYS_CHINTFLAG_OVR_Pos;
}

static inline void hri_evsyschannel_clear_interrupt_OVR_bit(const void *const hw)
{
	((EvsysChannel *)hw)->CHINTFLAG.reg = EVSYS_CHINTFLAG_OVR_Msk;
}

static inline bool hri_evsyschannel_get_interrupt_EVD_bit(const void *const hw)
{
	return (((EvsysChannel *)hw)->CHINTFLAG.reg & EVSYS_CHINTFLAG_EVD_Msk) >> EVSYS_CHINTFLAG_EVD_Pos;
}

static inline void hri_evsyschannel_clear_interrupt_EVD_bit(const void *const hw)
{
	((EvsysChannel *)hw)->CHINTFLAG.reg = EVSYS_CHINTFLAG_EVD_Msk;
}

static inline hri_evsys_chintflag_reg_t hri_evsyschannel_get_CHINTFLAG_reg(const void *const         hw,
                                                                           hri_evsys_chintflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((EvsysChannel *)hw)->CHINTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_chintflag_reg_t hri_evsyschannel_read_CHINTFLAG_reg(const void *const hw)
{
	return ((EvsysChannel *)hw)->CHINTFLAG.reg;
}

static inline void hri_evsyschannel_clear_CHINTFLAG_reg(const void *const hw, hri_evsys_chintflag_reg_t mask)
{
	((EvsysChannel *)hw)->CHINTFLAG.reg = mask;
}

static inline void hri_evsyschannel_set_CHINTEN_OVR_bit(const void *const hw)
{
	((EvsysChannel *)hw)->CHINTENSET.reg = EVSYS_CHINTENSET_OVR_Msk;
}

static inline bool hri_evsyschannel_get_CHINTEN_OVR_bit(const void *const hw)
{
	return (((EvsysChannel *)hw)->CHINTENSET.reg & EVSYS_CHINTENSET_OVR_Msk) >> EVSYS_CHINTENSET_OVR_Pos;
}

static inline void hri_evsyschannel_write_CHINTEN_OVR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((EvsysChannel *)hw)->CHINTENCLR.reg = EVSYS_CHINTENSET_OVR_Msk;
	} else {
		((EvsysChannel *)hw)->CHINTENSET.reg = EVSYS_CHINTENSET_OVR_Msk;
	}
}

static inline void hri_evsyschannel_clear_CHINTEN_OVR_bit(const void *const hw)
{
	((EvsysChannel *)hw)->CHINTENCLR.reg = EVSYS_CHINTENSET_OVR_Msk;
}

static inline void hri_evsyschannel_set_CHINTEN_EVD_bit(const void *const hw)
{
	((EvsysChannel *)hw)->CHINTENSET.reg = EVSYS_CHINTENSET_EVD_Msk;
}

static inline bool hri_evsyschannel_get_CHINTEN_EVD_bit(const void *const hw)
{
	return (((EvsysChannel *)hw)->CHINTENSET.reg & EVSYS_CHINTENSET_EVD_Msk) >> EVSYS_CHINTENSET_EVD_Pos;
}

static inline void hri_evsyschannel_write_CHINTEN_EVD_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((EvsysChannel *)hw)->CHINTENCLR.reg = EVSYS_CHINTENSET_EVD_Msk;
	} else {
		((EvsysChannel *)hw)->CHINTENSET.reg = EVSYS_CHINTENSET_EVD_Msk;
	}
}

static inline void hri_evsyschannel_clear_CHINTEN_EVD_bit(const void *const hw)
{
	((EvsysChannel *)hw)->CHINTENCLR.reg = EVSYS_CHINTENSET_EVD_Msk;
}

static inline void hri_evsyschannel_set_CHINTEN_reg(const void *const hw, hri_evsys_chintenset_reg_t mask)
{
	((EvsysChannel *)hw)->CHINTENSET.reg = mask;
}

static inline hri_evsys_chintenset_reg_t hri_evsyschannel_get_CHINTEN_reg(const void *const          hw,
                                                                          hri_evsys_chintenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((EvsysChannel *)hw)->CHINTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_chintenset_reg_t hri_evsyschannel_read_CHINTEN_reg(const void *const hw)
{
	return ((EvsysChannel *)hw)->CHINTENSET.reg;
}

static inline void hri_evsyschannel_write_CHINTEN_reg(const void *const hw, hri_evsys_chintenset_reg_t data)
{
	((EvsysChannel *)hw)->CHINTENSET.reg = data;
	((EvsysChannel *)hw)->CHINTENCLR.reg = ~data;
}

static inline void hri_evsyschannel_clear_CHINTEN_reg(const void *const hw, hri_evsys_chintenset_reg_t mask)
{
	((EvsysChannel *)hw)->CHINTENCLR.reg = mask;
}

static inline bool hri_evsyschannel_get_CHSTATUS_RDYUSR_bit(const void *const hw)
{
	return (((EvsysChannel *)hw)->CHSTATUS.reg & EVSYS_CHSTATUS_RDYUSR_Msk) >> EVSYS_CHSTATUS_RDYUSR_Pos;
}

static inline bool hri_evsyschannel_get_CHSTATUS_BUSYCH_bit(const void *const hw)
{
	return (((EvsysChannel *)hw)->CHSTATUS.reg & EVSYS_CHSTATUS_BUSYCH_Msk) >> EVSYS_CHSTATUS_BUSYCH_Pos;
}

static inline hri_evsys_chstatus_reg_t hri_evsyschannel_get_CHSTATUS_reg(const void *const        hw,
                                                                         hri_evsys_chstatus_reg_t mask)
{
	uint8_t tmp;
	tmp = ((EvsysChannel *)hw)->CHSTATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_chstatus_reg_t hri_evsyschannel_read_CHSTATUS_reg(const void *const hw)
{
	return ((EvsysChannel *)hw)->CHSTATUS.reg;
}

static inline void hri_evsyschannel_set_CHANNEL_RUNSTDBY_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg |= EVSYS_CHANNEL_RUNSTDBY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsyschannel_get_CHANNEL_RUNSTDBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_RUNSTDBY_Msk) >> EVSYS_CHANNEL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_evsyschannel_write_CHANNEL_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_RUNSTDBY_Msk;
	tmp |= value << EVSYS_CHANNEL_RUNSTDBY_Pos;
	((EvsysChannel *)hw)->CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_clear_CHANNEL_RUNSTDBY_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg &= ~EVSYS_CHANNEL_RUNSTDBY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_toggle_CHANNEL_RUNSTDBY_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg ^= EVSYS_CHANNEL_RUNSTDBY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_set_CHANNEL_ONDEMAND_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg |= EVSYS_CHANNEL_ONDEMAND_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsyschannel_get_CHANNEL_ONDEMAND_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_ONDEMAND_Msk) >> EVSYS_CHANNEL_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_evsyschannel_write_CHANNEL_ONDEMAND_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_ONDEMAND_Msk;
	tmp |= value << EVSYS_CHANNEL_ONDEMAND_Pos;
	((EvsysChannel *)hw)->CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_clear_CHANNEL_ONDEMAND_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg &= ~EVSYS_CHANNEL_ONDEMAND_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_toggle_CHANNEL_ONDEMAND_bit(const void *const hw)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg ^= EVSYS_CHANNEL_ONDEMAND_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_set_CHANNEL_EVGEN_bf(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg |= EVSYS_CHANNEL_EVGEN(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsyschannel_get_CHANNEL_EVGEN_bf(const void *const       hw,
                                                                            hri_evsys_channel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_EVGEN(mask)) >> EVSYS_CHANNEL_EVGEN_Pos;
	return tmp;
}

static inline void hri_evsyschannel_write_CHANNEL_EVGEN_bf(const void *const hw, hri_evsys_channel_reg_t data)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_EVGEN_Msk;
	tmp |= EVSYS_CHANNEL_EVGEN(data);
	((EvsysChannel *)hw)->CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_clear_CHANNEL_EVGEN_bf(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg &= ~EVSYS_CHANNEL_EVGEN(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_toggle_CHANNEL_EVGEN_bf(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg ^= EVSYS_CHANNEL_EVGEN(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsyschannel_read_CHANNEL_EVGEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_EVGEN_Msk) >> EVSYS_CHANNEL_EVGEN_Pos;
	return tmp;
}

static inline void hri_evsyschannel_set_CHANNEL_PATH_bf(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg |= EVSYS_CHANNEL_PATH(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsyschannel_get_CHANNEL_PATH_bf(const void *const       hw,
                                                                           hri_evsys_channel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_PATH(mask)) >> EVSYS_CHANNEL_PATH_Pos;
	return tmp;
}

static inline void hri_evsyschannel_write_CHANNEL_PATH_bf(const void *const hw, hri_evsys_channel_reg_t data)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_PATH_Msk;
	tmp |= EVSYS_CHANNEL_PATH(data);
	((EvsysChannel *)hw)->CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_clear_CHANNEL_PATH_bf(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg &= ~EVSYS_CHANNEL_PATH(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_toggle_CHANNEL_PATH_bf(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg ^= EVSYS_CHANNEL_PATH(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsyschannel_read_CHANNEL_PATH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_PATH_Msk) >> EVSYS_CHANNEL_PATH_Pos;
	return tmp;
}

static inline void hri_evsyschannel_set_CHANNEL_EDGSEL_bf(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg |= EVSYS_CHANNEL_EDGSEL(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsyschannel_get_CHANNEL_EDGSEL_bf(const void *const       hw,
                                                                             hri_evsys_channel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_EDGSEL(mask)) >> EVSYS_CHANNEL_EDGSEL_Pos;
	return tmp;
}

static inline void hri_evsyschannel_write_CHANNEL_EDGSEL_bf(const void *const hw, hri_evsys_channel_reg_t data)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_EDGSEL_Msk;
	tmp |= EVSYS_CHANNEL_EDGSEL(data);
	((EvsysChannel *)hw)->CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_clear_CHANNEL_EDGSEL_bf(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg &= ~EVSYS_CHANNEL_EDGSEL(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_toggle_CHANNEL_EDGSEL_bf(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg ^= EVSYS_CHANNEL_EDGSEL(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsyschannel_read_CHANNEL_EDGSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_EDGSEL_Msk) >> EVSYS_CHANNEL_EDGSEL_Pos;
	return tmp;
}

static inline void hri_evsyschannel_set_CHANNEL_reg(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg |= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsyschannel_get_CHANNEL_reg(const void *const       hw,
                                                                       hri_evsys_channel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((EvsysChannel *)hw)->CHANNEL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_evsyschannel_write_CHANNEL_reg(const void *const hw, hri_evsys_channel_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_clear_CHANNEL_reg(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg &= ~mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsyschannel_toggle_CHANNEL_reg(const void *const hw, hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((EvsysChannel *)hw)->CHANNEL.reg ^= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsyschannel_read_CHANNEL_reg(const void *const hw)
{
	return ((EvsysChannel *)hw)->CHANNEL.reg;
}

static inline bool hri_evsys_get_CHINTFLAG_OVR_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg & EVSYS_CHINTFLAG_OVR_Msk) >> EVSYS_CHINTFLAG_OVR_Pos;
}

static inline void hri_evsys_clear_CHINTFLAG_OVR_bit(const void *const hw, uint8_t submodule_index)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg = EVSYS_CHINTFLAG_OVR_Msk;
}

static inline bool hri_evsys_get_CHINTFLAG_EVD_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg & EVSYS_CHINTFLAG_EVD_Msk) >> EVSYS_CHINTFLAG_EVD_Pos;
}

static inline void hri_evsys_clear_CHINTFLAG_EVD_bit(const void *const hw, uint8_t submodule_index)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg = EVSYS_CHINTFLAG_EVD_Msk;
}

static inline bool hri_evsys_get_interrupt_OVR_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg & EVSYS_CHINTFLAG_OVR_Msk) >> EVSYS_CHINTFLAG_OVR_Pos;
}

static inline void hri_evsys_clear_interrupt_OVR_bit(const void *const hw, uint8_t submodule_index)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg = EVSYS_CHINTFLAG_OVR_Msk;
}

static inline bool hri_evsys_get_interrupt_EVD_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg & EVSYS_CHINTFLAG_EVD_Msk) >> EVSYS_CHINTFLAG_EVD_Pos;
}

static inline void hri_evsys_clear_interrupt_EVD_bit(const void *const hw, uint8_t submodule_index)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg = EVSYS_CHINTFLAG_EVD_Msk;
}

static inline hri_evsys_chintflag_reg_t hri_evsys_get_CHINTFLAG_reg(const void *const hw, uint8_t submodule_index,
                                                                    hri_evsys_chintflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_chintflag_reg_t hri_evsys_read_CHINTFLAG_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg;
}

static inline void hri_evsys_clear_CHINTFLAG_reg(const void *const hw, uint8_t submodule_index,
                                                 hri_evsys_chintflag_reg_t mask)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTFLAG.reg = mask;
}

static inline void hri_evsys_set_CHINTEN_OVR_bit(const void *const hw, uint8_t submodule_index)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg = EVSYS_CHINTENSET_OVR_Msk;
}

static inline bool hri_evsys_get_CHINTEN_OVR_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg & EVSYS_CHINTENSET_OVR_Msk)
	       >> EVSYS_CHINTENSET_OVR_Pos;
}

static inline void hri_evsys_write_CHINTEN_OVR_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	if (value == 0x0) {
		((Evsys *)hw)->Channel[submodule_index].CHINTENCLR.reg = EVSYS_CHINTENSET_OVR_Msk;
	} else {
		((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg = EVSYS_CHINTENSET_OVR_Msk;
	}
}

static inline void hri_evsys_clear_CHINTEN_OVR_bit(const void *const hw, uint8_t submodule_index)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTENCLR.reg = EVSYS_CHINTENSET_OVR_Msk;
}

static inline void hri_evsys_set_CHINTEN_EVD_bit(const void *const hw, uint8_t submodule_index)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg = EVSYS_CHINTENSET_EVD_Msk;
}

static inline bool hri_evsys_get_CHINTEN_EVD_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg & EVSYS_CHINTENSET_EVD_Msk)
	       >> EVSYS_CHINTENSET_EVD_Pos;
}

static inline void hri_evsys_write_CHINTEN_EVD_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	if (value == 0x0) {
		((Evsys *)hw)->Channel[submodule_index].CHINTENCLR.reg = EVSYS_CHINTENSET_EVD_Msk;
	} else {
		((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg = EVSYS_CHINTENSET_EVD_Msk;
	}
}

static inline void hri_evsys_clear_CHINTEN_EVD_bit(const void *const hw, uint8_t submodule_index)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTENCLR.reg = EVSYS_CHINTENSET_EVD_Msk;
}

static inline void hri_evsys_set_CHINTEN_reg(const void *const hw, uint8_t submodule_index,
                                             hri_evsys_chintenset_reg_t mask)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg = mask;
}

static inline hri_evsys_chintenset_reg_t hri_evsys_get_CHINTEN_reg(const void *const hw, uint8_t submodule_index,
                                                                   hri_evsys_chintenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_chintenset_reg_t hri_evsys_read_CHINTEN_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg;
}

static inline void hri_evsys_write_CHINTEN_reg(const void *const hw, uint8_t submodule_index,
                                               hri_evsys_chintenset_reg_t data)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTENSET.reg = data;
	((Evsys *)hw)->Channel[submodule_index].CHINTENCLR.reg = ~data;
}

static inline void hri_evsys_clear_CHINTEN_reg(const void *const hw, uint8_t submodule_index,
                                               hri_evsys_chintenset_reg_t mask)
{
	((Evsys *)hw)->Channel[submodule_index].CHINTENCLR.reg = mask;
}

static inline bool hri_evsys_get_CHSTATUS_RDYUSR_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Evsys *)hw)->Channel[submodule_index].CHSTATUS.reg & EVSYS_CHSTATUS_RDYUSR_Msk)
	       >> EVSYS_CHSTATUS_RDYUSR_Pos;
}

static inline bool hri_evsys_get_CHSTATUS_BUSYCH_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Evsys *)hw)->Channel[submodule_index].CHSTATUS.reg & EVSYS_CHSTATUS_BUSYCH_Msk)
	       >> EVSYS_CHSTATUS_BUSYCH_Pos;
}

static inline hri_evsys_chstatus_reg_t hri_evsys_get_CHSTATUS_reg(const void *const hw, uint8_t submodule_index,
                                                                  hri_evsys_chstatus_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHSTATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_evsys_chstatus_reg_t hri_evsys_read_CHSTATUS_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Evsys *)hw)->Channel[submodule_index].CHSTATUS.reg;
}

static inline void hri_evsys_set_CHANNEL_RUNSTDBY_bit(const void *const hw, uint8_t submodule_index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg |= EVSYS_CHANNEL_RUNSTDBY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_CHANNEL_RUNSTDBY_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_RUNSTDBY_Msk) >> EVSYS_CHANNEL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_CHANNEL_RUNSTDBY_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_RUNSTDBY_Msk;
	tmp |= value << EVSYS_CHANNEL_RUNSTDBY_Pos;
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_CHANNEL_RUNSTDBY_bit(const void *const hw, uint8_t submodule_index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg &= ~EVSYS_CHANNEL_RUNSTDBY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_CHANNEL_RUNSTDBY_bit(const void *const hw, uint8_t submodule_index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg ^= EVSYS_CHANNEL_RUNSTDBY_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_CHANNEL_ONDEMAND_bit(const void *const hw, uint8_t submodule_index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg |= EVSYS_CHANNEL_ONDEMAND_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_evsys_get_CHANNEL_ONDEMAND_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_ONDEMAND_Msk) >> EVSYS_CHANNEL_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_evsys_write_CHANNEL_ONDEMAND_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_ONDEMAND_Msk;
	tmp |= value << EVSYS_CHANNEL_ONDEMAND_Pos;
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_CHANNEL_ONDEMAND_bit(const void *const hw, uint8_t submodule_index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg &= ~EVSYS_CHANNEL_ONDEMAND_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_CHANNEL_ONDEMAND_bit(const void *const hw, uint8_t submodule_index)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg ^= EVSYS_CHANNEL_ONDEMAND_Msk;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_set_CHANNEL_EVGEN_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg |= EVSYS_CHANNEL_EVGEN(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsys_get_CHANNEL_EVGEN_bf(const void *const hw, uint8_t submodule_index,
                                                                     hri_evsys_channel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_EVGEN(mask)) >> EVSYS_CHANNEL_EVGEN_Pos;
	return tmp;
}

static inline void hri_evsys_write_CHANNEL_EVGEN_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_evsys_channel_reg_t data)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_EVGEN_Msk;
	tmp |= EVSYS_CHANNEL_EVGEN(data);
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_CHANNEL_EVGEN_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg &= ~EVSYS_CHANNEL_EVGEN(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_CHANNEL_EVGEN_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg ^= EVSYS_CHANNEL_EVGEN(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsys_read_CHANNEL_EVGEN_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_EVGEN_Msk) >> EVSYS_CHANNEL_EVGEN_Pos;
	return tmp;
}

static inline void hri_evsys_set_CHANNEL_PATH_bf(const void *const hw, uint8_t submodule_index,
                                                 hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg |= EVSYS_CHANNEL_PATH(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsys_get_CHANNEL_PATH_bf(const void *const hw, uint8_t submodule_index,
                                                                    hri_evsys_channel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_PATH(mask)) >> EVSYS_CHANNEL_PATH_Pos;
	return tmp;
}

static inline void hri_evsys_write_CHANNEL_PATH_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_evsys_channel_reg_t data)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_PATH_Msk;
	tmp |= EVSYS_CHANNEL_PATH(data);
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_CHANNEL_PATH_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg &= ~EVSYS_CHANNEL_PATH(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_CHANNEL_PATH_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg ^= EVSYS_CHANNEL_PATH(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsys_read_CHANNEL_PATH_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_PATH_Msk) >> EVSYS_CHANNEL_PATH_Pos;
	return tmp;
}

static inline void hri_evsys_set_CHANNEL_EDGSEL_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg |= EVSYS_CHANNEL_EDGSEL(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsys_get_CHANNEL_EDGSEL_bf(const void *const hw, uint8_t submodule_index,
                                                                      hri_evsys_channel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_EDGSEL(mask)) >> EVSYS_CHANNEL_EDGSEL_Pos;
	return tmp;
}

static inline void hri_evsys_write_CHANNEL_EDGSEL_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_evsys_channel_reg_t data)
{
	uint32_t tmp;
	EVSYS_CRITICAL_SECTION_ENTER();
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp &= ~EVSYS_CHANNEL_EDGSEL_Msk;
	tmp |= EVSYS_CHANNEL_EDGSEL(data);
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg = tmp;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_CHANNEL_EDGSEL_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg &= ~EVSYS_CHANNEL_EDGSEL(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_CHANNEL_EDGSEL_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg ^= EVSYS_CHANNEL_EDGSEL(mask);
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsys_read_CHANNEL_EDGSEL_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp = (tmp & EVSYS_CHANNEL_EDGSEL_Msk) >> EVSYS_CHANNEL_EDGSEL_Pos;
	return tmp;
}

static inline void hri_evsys_set_CHANNEL_reg(const void *const hw, uint8_t submodule_index,
                                             hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg |= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsys_get_CHANNEL_reg(const void *const hw, uint8_t submodule_index,
                                                                hri_evsys_channel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_evsys_write_CHANNEL_reg(const void *const hw, uint8_t submodule_index,
                                               hri_evsys_channel_reg_t data)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg = data;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_clear_CHANNEL_reg(const void *const hw, uint8_t submodule_index,
                                               hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg &= ~mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_evsys_toggle_CHANNEL_reg(const void *const hw, uint8_t submodule_index,
                                                hri_evsys_channel_reg_t mask)
{
	EVSYS_CRITICAL_SECTION_ENTER();
	((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg ^= mask;
	EVSYS_CRITICAL_SECTION_LEAVE();
}

static inline hri_evsys_channel_reg_t hri_evsys_read_CHANNEL_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Evsys *)hw)->Channel[submodule_index].CHANNEL.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_EVSYS_L10_H_INCLUDED */
#endif /* _SAML10_EVSYS_COMPONENT_ */
