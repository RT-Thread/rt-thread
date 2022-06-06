/**
 * \file
 *
 * \brief SAM NVMCTRL
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

#ifdef _SAMC21_NVMCTRL_COMPONENT_
#ifndef _HRI_NVMCTRL_C21_H_INCLUDED_
#define _HRI_NVMCTRL_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_NVMCTRL_CRITICAL_SECTIONS)
#define NVMCTRL_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define NVMCTRL_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define NVMCTRL_CRITICAL_SECTION_ENTER()
#define NVMCTRL_CRITICAL_SECTION_LEAVE()
#endif

typedef uint16_t hri_nvmctrl_ctrla_reg_t;
typedef uint16_t hri_nvmctrl_lock_reg_t;
typedef uint16_t hri_nvmctrl_status_reg_t;
typedef uint32_t hri_nvmctrl_addr_reg_t;
typedef uint32_t hri_nvmctrl_ctrlb_reg_t;
typedef uint32_t hri_nvmctrl_param_reg_t;
typedef uint32_t hri_nvmctrl_pbldata0_reg_t;
typedef uint32_t hri_nvmctrl_pbldata1_reg_t;
typedef uint8_t  hri_nvmctrl_intenset_reg_t;
typedef uint8_t  hri_nvmctrl_intflag_reg_t;

static inline bool hri_nvmctrl_get_INTFLAG_READY_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_READY) >> NVMCTRL_INTFLAG_READY_Pos;
}

static inline void hri_nvmctrl_clear_INTFLAG_READY_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_READY;
}

static inline bool hri_nvmctrl_get_INTFLAG_ERROR_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_ERROR) >> NVMCTRL_INTFLAG_ERROR_Pos;
}

static inline void hri_nvmctrl_clear_INTFLAG_ERROR_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_ERROR;
}

static inline bool hri_nvmctrl_get_interrupt_READY_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_READY) >> NVMCTRL_INTFLAG_READY_Pos;
}

static inline void hri_nvmctrl_clear_interrupt_READY_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_READY;
}

static inline bool hri_nvmctrl_get_interrupt_ERROR_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_ERROR) >> NVMCTRL_INTFLAG_ERROR_Pos;
}

static inline void hri_nvmctrl_clear_interrupt_ERROR_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_ERROR;
}

static inline hri_nvmctrl_intflag_reg_t hri_nvmctrl_get_INTFLAG_reg(const void *const         hw,
                                                                    hri_nvmctrl_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Nvmctrl *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_nvmctrl_intflag_reg_t hri_nvmctrl_read_INTFLAG_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->INTFLAG.reg;
}

static inline void hri_nvmctrl_clear_INTFLAG_reg(const void *const hw, hri_nvmctrl_intflag_reg_t mask)
{
	((Nvmctrl *)hw)->INTFLAG.reg = mask;
}

static inline void hri_nvmctrl_set_INTEN_READY_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_READY;
}

static inline bool hri_nvmctrl_get_INTEN_READY_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTENSET.reg & NVMCTRL_INTENSET_READY) >> NVMCTRL_INTENSET_READY_Pos;
}

static inline void hri_nvmctrl_write_INTEN_READY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_READY;
	} else {
		((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_READY;
	}
}

static inline void hri_nvmctrl_clear_INTEN_READY_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_READY;
}

static inline void hri_nvmctrl_set_INTEN_ERROR_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_ERROR;
}

static inline bool hri_nvmctrl_get_INTEN_ERROR_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTENSET.reg & NVMCTRL_INTENSET_ERROR) >> NVMCTRL_INTENSET_ERROR_Pos;
}

static inline void hri_nvmctrl_write_INTEN_ERROR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_ERROR;
	} else {
		((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_ERROR;
	}
}

static inline void hri_nvmctrl_clear_INTEN_ERROR_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_ERROR;
}

static inline void hri_nvmctrl_set_INTEN_reg(const void *const hw, hri_nvmctrl_intenset_reg_t mask)
{
	((Nvmctrl *)hw)->INTENSET.reg = mask;
}

static inline hri_nvmctrl_intenset_reg_t hri_nvmctrl_get_INTEN_reg(const void *const          hw,
                                                                   hri_nvmctrl_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Nvmctrl *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_nvmctrl_intenset_reg_t hri_nvmctrl_read_INTEN_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->INTENSET.reg;
}

static inline void hri_nvmctrl_write_INTEN_reg(const void *const hw, hri_nvmctrl_intenset_reg_t data)
{
	((Nvmctrl *)hw)->INTENSET.reg = data;
	((Nvmctrl *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_nvmctrl_clear_INTEN_reg(const void *const hw, hri_nvmctrl_intenset_reg_t mask)
{
	((Nvmctrl *)hw)->INTENCLR.reg = mask;
}

static inline hri_nvmctrl_pbldata0_reg_t hri_nvmctrl_get_PBLDATA0_reg(const void *const          hw,
                                                                      hri_nvmctrl_pbldata0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PBLDATA0.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_nvmctrl_pbldata0_reg_t hri_nvmctrl_read_PBLDATA0_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->PBLDATA0.reg;
}

static inline hri_nvmctrl_pbldata1_reg_t hri_nvmctrl_get_PBLDATA1_reg(const void *const          hw,
                                                                      hri_nvmctrl_pbldata1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PBLDATA1.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_nvmctrl_pbldata1_reg_t hri_nvmctrl_read_PBLDATA1_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->PBLDATA1.reg;
}

static inline void hri_nvmctrl_set_CTRLA_CMD_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg |= NVMCTRL_CTRLA_CMD(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrla_reg_t hri_nvmctrl_get_CTRLA_CMD_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLA.reg;
	tmp = (tmp & NVMCTRL_CTRLA_CMD(mask)) >> NVMCTRL_CTRLA_CMD_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_CTRLA_CMD_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t data)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLA.reg;
	tmp &= ~NVMCTRL_CTRLA_CMD_Msk;
	tmp |= NVMCTRL_CTRLA_CMD(data);
	((Nvmctrl *)hw)->CTRLA.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLA_CMD_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg &= ~NVMCTRL_CTRLA_CMD(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLA_CMD_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg ^= NVMCTRL_CTRLA_CMD(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrla_reg_t hri_nvmctrl_read_CTRLA_CMD_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLA.reg;
	tmp = (tmp & NVMCTRL_CTRLA_CMD_Msk) >> NVMCTRL_CTRLA_CMD_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_CTRLA_CMDEX_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg |= NVMCTRL_CTRLA_CMDEX(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrla_reg_t hri_nvmctrl_get_CTRLA_CMDEX_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLA.reg;
	tmp = (tmp & NVMCTRL_CTRLA_CMDEX(mask)) >> NVMCTRL_CTRLA_CMDEX_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_CTRLA_CMDEX_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t data)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLA.reg;
	tmp &= ~NVMCTRL_CTRLA_CMDEX_Msk;
	tmp |= NVMCTRL_CTRLA_CMDEX(data);
	((Nvmctrl *)hw)->CTRLA.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLA_CMDEX_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg &= ~NVMCTRL_CTRLA_CMDEX(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLA_CMDEX_bf(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg ^= NVMCTRL_CTRLA_CMDEX(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrla_reg_t hri_nvmctrl_read_CTRLA_CMDEX_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLA.reg;
	tmp = (tmp & NVMCTRL_CTRLA_CMDEX_Msk) >> NVMCTRL_CTRLA_CMDEX_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_CTRLA_reg(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrla_reg_t hri_nvmctrl_get_CTRLA_reg(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_CTRLA_reg(const void *const hw, hri_nvmctrl_ctrla_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLA_reg(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLA_reg(const void *const hw, hri_nvmctrl_ctrla_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrla_reg_t hri_nvmctrl_read_CTRLA_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->CTRLA.reg;
}

static inline void hri_nvmctrl_set_CTRLB_MANW_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg |= NVMCTRL_CTRLB_MANW;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_CTRLB_MANW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_MANW) >> NVMCTRL_CTRLB_MANW_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_CTRLB_MANW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp &= ~NVMCTRL_CTRLB_MANW;
	tmp |= value << NVMCTRL_CTRLB_MANW_Pos;
	((Nvmctrl *)hw)->CTRLB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLB_MANW_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg &= ~NVMCTRL_CTRLB_MANW;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLB_MANW_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg ^= NVMCTRL_CTRLB_MANW;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_CTRLB_RWS_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg |= NVMCTRL_CTRLB_RWS(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_get_CTRLB_RWS_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_RWS(mask)) >> NVMCTRL_CTRLB_RWS_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_CTRLB_RWS_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp &= ~NVMCTRL_CTRLB_RWS_Msk;
	tmp |= NVMCTRL_CTRLB_RWS(data);
	((Nvmctrl *)hw)->CTRLB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLB_RWS_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg &= ~NVMCTRL_CTRLB_RWS(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLB_RWS_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg ^= NVMCTRL_CTRLB_RWS(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_read_CTRLB_RWS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_RWS_Msk) >> NVMCTRL_CTRLB_RWS_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_CTRLB_SLEEPPRM_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg |= NVMCTRL_CTRLB_SLEEPPRM(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_get_CTRLB_SLEEPPRM_bf(const void *const       hw,
                                                                        hri_nvmctrl_ctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_SLEEPPRM(mask)) >> NVMCTRL_CTRLB_SLEEPPRM_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_CTRLB_SLEEPPRM_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp &= ~NVMCTRL_CTRLB_SLEEPPRM_Msk;
	tmp |= NVMCTRL_CTRLB_SLEEPPRM(data);
	((Nvmctrl *)hw)->CTRLB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLB_SLEEPPRM_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg &= ~NVMCTRL_CTRLB_SLEEPPRM(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLB_SLEEPPRM_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg ^= NVMCTRL_CTRLB_SLEEPPRM(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_read_CTRLB_SLEEPPRM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_SLEEPPRM_Msk) >> NVMCTRL_CTRLB_SLEEPPRM_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_CTRLB_READMODE_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg |= NVMCTRL_CTRLB_READMODE(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_get_CTRLB_READMODE_bf(const void *const       hw,
                                                                        hri_nvmctrl_ctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_READMODE(mask)) >> NVMCTRL_CTRLB_READMODE_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_CTRLB_READMODE_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp &= ~NVMCTRL_CTRLB_READMODE_Msk;
	tmp |= NVMCTRL_CTRLB_READMODE(data);
	((Nvmctrl *)hw)->CTRLB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLB_READMODE_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg &= ~NVMCTRL_CTRLB_READMODE(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLB_READMODE_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg ^= NVMCTRL_CTRLB_READMODE(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_read_CTRLB_READMODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_READMODE_Msk) >> NVMCTRL_CTRLB_READMODE_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_CTRLB_CACHEDIS_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg |= NVMCTRL_CTRLB_CACHEDIS(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_get_CTRLB_CACHEDIS_bf(const void *const       hw,
                                                                        hri_nvmctrl_ctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_CACHEDIS(mask)) >> NVMCTRL_CTRLB_CACHEDIS_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_CTRLB_CACHEDIS_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp &= ~NVMCTRL_CTRLB_CACHEDIS_Msk;
	tmp |= NVMCTRL_CTRLB_CACHEDIS(data);
	((Nvmctrl *)hw)->CTRLB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLB_CACHEDIS_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg &= ~NVMCTRL_CTRLB_CACHEDIS(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLB_CACHEDIS_bf(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg ^= NVMCTRL_CTRLB_CACHEDIS(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_read_CTRLB_CACHEDIS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_CACHEDIS_Msk) >> NVMCTRL_CTRLB_CACHEDIS_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_CTRLB_reg(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_get_CTRLB_reg(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_CTRLB_reg(const void *const hw, hri_nvmctrl_ctrlb_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLB_reg(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLB_reg(const void *const hw, hri_nvmctrl_ctrlb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlb_reg_t hri_nvmctrl_read_CTRLB_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->CTRLB.reg;
}

static inline void hri_nvmctrl_set_PARAM_NVMP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg |= NVMCTRL_PARAM_NVMP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_get_PARAM_NVMP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_NVMP(mask)) >> NVMCTRL_PARAM_NVMP_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_PARAM_NVMP_bf(const void *const hw, hri_nvmctrl_param_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp &= ~NVMCTRL_PARAM_NVMP_Msk;
	tmp |= NVMCTRL_PARAM_NVMP(data);
	((Nvmctrl *)hw)->PARAM.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_PARAM_NVMP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg &= ~NVMCTRL_PARAM_NVMP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_PARAM_NVMP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg ^= NVMCTRL_PARAM_NVMP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_read_PARAM_NVMP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_NVMP_Msk) >> NVMCTRL_PARAM_NVMP_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_PARAM_PSZ_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg |= NVMCTRL_PARAM_PSZ(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_get_PARAM_PSZ_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_PSZ(mask)) >> NVMCTRL_PARAM_PSZ_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_PARAM_PSZ_bf(const void *const hw, hri_nvmctrl_param_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp &= ~NVMCTRL_PARAM_PSZ_Msk;
	tmp |= NVMCTRL_PARAM_PSZ(data);
	((Nvmctrl *)hw)->PARAM.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_PARAM_PSZ_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg &= ~NVMCTRL_PARAM_PSZ(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_PARAM_PSZ_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg ^= NVMCTRL_PARAM_PSZ(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_read_PARAM_PSZ_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_PSZ_Msk) >> NVMCTRL_PARAM_PSZ_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_PARAM_RWWEEP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg |= NVMCTRL_PARAM_RWWEEP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_get_PARAM_RWWEEP_bf(const void *const       hw,
                                                                      hri_nvmctrl_param_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_RWWEEP(mask)) >> NVMCTRL_PARAM_RWWEEP_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_PARAM_RWWEEP_bf(const void *const hw, hri_nvmctrl_param_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp &= ~NVMCTRL_PARAM_RWWEEP_Msk;
	tmp |= NVMCTRL_PARAM_RWWEEP(data);
	((Nvmctrl *)hw)->PARAM.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_PARAM_RWWEEP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg &= ~NVMCTRL_PARAM_RWWEEP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_PARAM_RWWEEP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg ^= NVMCTRL_PARAM_RWWEEP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_read_PARAM_RWWEEP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_RWWEEP_Msk) >> NVMCTRL_PARAM_RWWEEP_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_PARAM_reg(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_get_PARAM_reg(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_PARAM_reg(const void *const hw, hri_nvmctrl_param_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_PARAM_reg(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_PARAM_reg(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_read_PARAM_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->PARAM.reg;
}

static inline void hri_nvmctrl_set_ADDR_ADDR_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg |= NVMCTRL_ADDR_ADDR(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_addr_reg_t hri_nvmctrl_get_ADDR_ADDR_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp = (tmp & NVMCTRL_ADDR_ADDR(mask)) >> NVMCTRL_ADDR_ADDR_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_ADDR_ADDR_bf(const void *const hw, hri_nvmctrl_addr_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp &= ~NVMCTRL_ADDR_ADDR_Msk;
	tmp |= NVMCTRL_ADDR_ADDR(data);
	((Nvmctrl *)hw)->ADDR.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_ADDR_ADDR_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg &= ~NVMCTRL_ADDR_ADDR(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_ADDR_ADDR_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg ^= NVMCTRL_ADDR_ADDR(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_addr_reg_t hri_nvmctrl_read_ADDR_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp = (tmp & NVMCTRL_ADDR_ADDR_Msk) >> NVMCTRL_ADDR_ADDR_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_ADDR_reg(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_addr_reg_t hri_nvmctrl_get_ADDR_reg(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_ADDR_reg(const void *const hw, hri_nvmctrl_addr_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_ADDR_reg(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_ADDR_reg(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_addr_reg_t hri_nvmctrl_read_ADDR_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->ADDR.reg;
}

static inline void hri_nvmctrl_set_LOCK_LOCK_bf(const void *const hw, hri_nvmctrl_lock_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->LOCK.reg |= NVMCTRL_LOCK_LOCK(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_lock_reg_t hri_nvmctrl_get_LOCK_LOCK_bf(const void *const hw, hri_nvmctrl_lock_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->LOCK.reg;
	tmp = (tmp & NVMCTRL_LOCK_LOCK(mask)) >> NVMCTRL_LOCK_LOCK_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_LOCK_LOCK_bf(const void *const hw, hri_nvmctrl_lock_reg_t data)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->LOCK.reg;
	tmp &= ~NVMCTRL_LOCK_LOCK_Msk;
	tmp |= NVMCTRL_LOCK_LOCK(data);
	((Nvmctrl *)hw)->LOCK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_LOCK_LOCK_bf(const void *const hw, hri_nvmctrl_lock_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->LOCK.reg &= ~NVMCTRL_LOCK_LOCK(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_LOCK_LOCK_bf(const void *const hw, hri_nvmctrl_lock_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->LOCK.reg ^= NVMCTRL_LOCK_LOCK(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_lock_reg_t hri_nvmctrl_read_LOCK_LOCK_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->LOCK.reg;
	tmp = (tmp & NVMCTRL_LOCK_LOCK_Msk) >> NVMCTRL_LOCK_LOCK_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_LOCK_reg(const void *const hw, hri_nvmctrl_lock_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->LOCK.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_lock_reg_t hri_nvmctrl_get_LOCK_reg(const void *const hw, hri_nvmctrl_lock_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->LOCK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_LOCK_reg(const void *const hw, hri_nvmctrl_lock_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->LOCK.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_LOCK_reg(const void *const hw, hri_nvmctrl_lock_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->LOCK.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_LOCK_reg(const void *const hw, hri_nvmctrl_lock_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->LOCK.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_lock_reg_t hri_nvmctrl_read_LOCK_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->LOCK.reg;
}

static inline bool hri_nvmctrl_get_STATUS_PRM_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_PRM) >> NVMCTRL_STATUS_PRM_Pos;
}

static inline void hri_nvmctrl_clear_STATUS_PRM_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->STATUS.reg = NVMCTRL_STATUS_PRM;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_STATUS_LOAD_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_LOAD) >> NVMCTRL_STATUS_LOAD_Pos;
}

static inline void hri_nvmctrl_clear_STATUS_LOAD_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->STATUS.reg = NVMCTRL_STATUS_LOAD;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_STATUS_PROGE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_PROGE) >> NVMCTRL_STATUS_PROGE_Pos;
}

static inline void hri_nvmctrl_clear_STATUS_PROGE_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->STATUS.reg = NVMCTRL_STATUS_PROGE;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_STATUS_LOCKE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_LOCKE) >> NVMCTRL_STATUS_LOCKE_Pos;
}

static inline void hri_nvmctrl_clear_STATUS_LOCKE_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->STATUS.reg = NVMCTRL_STATUS_LOCKE;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_STATUS_NVME_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_NVME) >> NVMCTRL_STATUS_NVME_Pos;
}

static inline void hri_nvmctrl_clear_STATUS_NVME_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->STATUS.reg = NVMCTRL_STATUS_NVME;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_STATUS_SB_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_SB) >> NVMCTRL_STATUS_SB_Pos;
}

static inline void hri_nvmctrl_clear_STATUS_SB_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->STATUS.reg = NVMCTRL_STATUS_SB;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_status_reg_t hri_nvmctrl_get_STATUS_reg(const void *const hw, hri_nvmctrl_status_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_clear_STATUS_reg(const void *const hw, hri_nvmctrl_status_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->STATUS.reg = mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_status_reg_t hri_nvmctrl_read_STATUS_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->STATUS.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_NVMCTRL_C21_H_INCLUDED */
#endif /* _SAMC21_NVMCTRL_COMPONENT_ */
