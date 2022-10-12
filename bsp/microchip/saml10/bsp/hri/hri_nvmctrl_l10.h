/**
 * \file
 *
 * \brief SAM NVMCTRL
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

#ifdef _SAML10_NVMCTRL_COMPONENT_
#ifndef _HRI_NVMCTRL_L10_H_INCLUDED_
#define _HRI_NVMCTRL_L10_H_INCLUDED_

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
typedef uint16_t hri_nvmctrl_nsulck_reg_t;
typedef uint16_t hri_nvmctrl_status_reg_t;
typedef uint16_t hri_nvmctrl_sulck_reg_t;
typedef uint32_t hri_nvmctrl_addr_reg_t;
typedef uint32_t hri_nvmctrl_ctrlb_reg_t;
typedef uint32_t hri_nvmctrl_dscc_reg_t;
typedef uint32_t hri_nvmctrl_nonsec_reg_t;
typedef uint32_t hri_nvmctrl_nschk_reg_t;
typedef uint32_t hri_nvmctrl_param_reg_t;
typedef uint32_t hri_nvmctrl_scfgad_reg_t;
typedef uint32_t hri_nvmctrl_scfgb_reg_t;
typedef uint32_t hri_nvmctrl_secctrl_reg_t;
typedef uint8_t  hri_nvmctrl_ctrlc_reg_t;
typedef uint8_t  hri_nvmctrl_evctrl_reg_t;
typedef uint8_t  hri_nvmctrl_intenset_reg_t;
typedef uint8_t  hri_nvmctrl_intflag_reg_t;

static inline bool hri_nvmctrl_get_INTFLAG_DONE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_DONE_Msk) >> NVMCTRL_INTFLAG_DONE_Pos;
}

static inline void hri_nvmctrl_clear_INTFLAG_DONE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_DONE_Msk;
}

static inline bool hri_nvmctrl_get_INTFLAG_PROGE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_PROGE_Msk) >> NVMCTRL_INTFLAG_PROGE_Pos;
}

static inline void hri_nvmctrl_clear_INTFLAG_PROGE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_PROGE_Msk;
}

static inline bool hri_nvmctrl_get_INTFLAG_LOCKE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_LOCKE_Msk) >> NVMCTRL_INTFLAG_LOCKE_Pos;
}

static inline void hri_nvmctrl_clear_INTFLAG_LOCKE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_LOCKE_Msk;
}

static inline bool hri_nvmctrl_get_INTFLAG_NVME_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_NVME_Msk) >> NVMCTRL_INTFLAG_NVME_Pos;
}

static inline void hri_nvmctrl_clear_INTFLAG_NVME_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_NVME_Msk;
}

static inline bool hri_nvmctrl_get_INTFLAG_KEYE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_KEYE_Msk) >> NVMCTRL_INTFLAG_KEYE_Pos;
}

static inline void hri_nvmctrl_clear_INTFLAG_KEYE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_KEYE_Msk;
}

static inline bool hri_nvmctrl_get_INTFLAG_NSCHK_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_NSCHK_Msk) >> NVMCTRL_INTFLAG_NSCHK_Pos;
}

static inline void hri_nvmctrl_clear_INTFLAG_NSCHK_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_NSCHK_Msk;
}

static inline bool hri_nvmctrl_get_interrupt_DONE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_DONE_Msk) >> NVMCTRL_INTFLAG_DONE_Pos;
}

static inline void hri_nvmctrl_clear_interrupt_DONE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_DONE_Msk;
}

static inline bool hri_nvmctrl_get_interrupt_PROGE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_PROGE_Msk) >> NVMCTRL_INTFLAG_PROGE_Pos;
}

static inline void hri_nvmctrl_clear_interrupt_PROGE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_PROGE_Msk;
}

static inline bool hri_nvmctrl_get_interrupt_LOCKE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_LOCKE_Msk) >> NVMCTRL_INTFLAG_LOCKE_Pos;
}

static inline void hri_nvmctrl_clear_interrupt_LOCKE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_LOCKE_Msk;
}

static inline bool hri_nvmctrl_get_interrupt_NVME_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_NVME_Msk) >> NVMCTRL_INTFLAG_NVME_Pos;
}

static inline void hri_nvmctrl_clear_interrupt_NVME_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_NVME_Msk;
}

static inline bool hri_nvmctrl_get_interrupt_KEYE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_KEYE_Msk) >> NVMCTRL_INTFLAG_KEYE_Pos;
}

static inline void hri_nvmctrl_clear_interrupt_KEYE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_KEYE_Msk;
}

static inline bool hri_nvmctrl_get_interrupt_NSCHK_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTFLAG.reg & NVMCTRL_INTFLAG_NSCHK_Msk) >> NVMCTRL_INTFLAG_NSCHK_Pos;
}

static inline void hri_nvmctrl_clear_interrupt_NSCHK_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTFLAG.reg = NVMCTRL_INTFLAG_NSCHK_Msk;
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

static inline void hri_nvmctrl_set_INTEN_DONE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_DONE_Msk;
}

static inline bool hri_nvmctrl_get_INTEN_DONE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTENSET.reg & NVMCTRL_INTENSET_DONE_Msk) >> NVMCTRL_INTENSET_DONE_Pos;
}

static inline void hri_nvmctrl_write_INTEN_DONE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_DONE_Msk;
	} else {
		((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_DONE_Msk;
	}
}

static inline void hri_nvmctrl_clear_INTEN_DONE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_DONE_Msk;
}

static inline void hri_nvmctrl_set_INTEN_PROGE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_PROGE_Msk;
}

static inline bool hri_nvmctrl_get_INTEN_PROGE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTENSET.reg & NVMCTRL_INTENSET_PROGE_Msk) >> NVMCTRL_INTENSET_PROGE_Pos;
}

static inline void hri_nvmctrl_write_INTEN_PROGE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_PROGE_Msk;
	} else {
		((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_PROGE_Msk;
	}
}

static inline void hri_nvmctrl_clear_INTEN_PROGE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_PROGE_Msk;
}

static inline void hri_nvmctrl_set_INTEN_LOCKE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_LOCKE_Msk;
}

static inline bool hri_nvmctrl_get_INTEN_LOCKE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTENSET.reg & NVMCTRL_INTENSET_LOCKE_Msk) >> NVMCTRL_INTENSET_LOCKE_Pos;
}

static inline void hri_nvmctrl_write_INTEN_LOCKE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_LOCKE_Msk;
	} else {
		((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_LOCKE_Msk;
	}
}

static inline void hri_nvmctrl_clear_INTEN_LOCKE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_LOCKE_Msk;
}

static inline void hri_nvmctrl_set_INTEN_NVME_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_NVME_Msk;
}

static inline bool hri_nvmctrl_get_INTEN_NVME_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTENSET.reg & NVMCTRL_INTENSET_NVME_Msk) >> NVMCTRL_INTENSET_NVME_Pos;
}

static inline void hri_nvmctrl_write_INTEN_NVME_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_NVME_Msk;
	} else {
		((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_NVME_Msk;
	}
}

static inline void hri_nvmctrl_clear_INTEN_NVME_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_NVME_Msk;
}

static inline void hri_nvmctrl_set_INTEN_KEYE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_KEYE_Msk;
}

static inline bool hri_nvmctrl_get_INTEN_KEYE_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTENSET.reg & NVMCTRL_INTENSET_KEYE_Msk) >> NVMCTRL_INTENSET_KEYE_Pos;
}

static inline void hri_nvmctrl_write_INTEN_KEYE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_KEYE_Msk;
	} else {
		((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_KEYE_Msk;
	}
}

static inline void hri_nvmctrl_clear_INTEN_KEYE_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_KEYE_Msk;
}

static inline void hri_nvmctrl_set_INTEN_NSCHK_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_NSCHK_Msk;
}

static inline bool hri_nvmctrl_get_INTEN_NSCHK_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->INTENSET.reg & NVMCTRL_INTENSET_NSCHK_Msk) >> NVMCTRL_INTENSET_NSCHK_Pos;
}

static inline void hri_nvmctrl_write_INTEN_NSCHK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_NSCHK_Msk;
	} else {
		((Nvmctrl *)hw)->INTENSET.reg = NVMCTRL_INTENSET_NSCHK_Msk;
	}
}

static inline void hri_nvmctrl_clear_INTEN_NSCHK_bit(const void *const hw)
{
	((Nvmctrl *)hw)->INTENCLR.reg = NVMCTRL_INTENSET_NSCHK_Msk;
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

static inline bool hri_nvmctrl_get_STATUS_PRM_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_PRM_Msk) >> NVMCTRL_STATUS_PRM_Pos;
}

static inline bool hri_nvmctrl_get_STATUS_LOAD_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_LOAD_Msk) >> NVMCTRL_STATUS_LOAD_Pos;
}

static inline bool hri_nvmctrl_get_STATUS_READY_bit(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_READY_Msk) >> NVMCTRL_STATUS_READY_Pos;
}

static inline hri_nvmctrl_status_reg_t hri_nvmctrl_get_STATUS_DALFUSE_bf(const void *const        hw,
                                                                         hri_nvmctrl_status_reg_t mask)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_DALFUSE(mask)) >> NVMCTRL_STATUS_DALFUSE_Pos;
}

static inline hri_nvmctrl_status_reg_t hri_nvmctrl_read_STATUS_DALFUSE_bf(const void *const hw)
{
	return (((Nvmctrl *)hw)->STATUS.reg & NVMCTRL_STATUS_DALFUSE_Msk) >> NVMCTRL_STATUS_DALFUSE_Pos;
}

static inline hri_nvmctrl_status_reg_t hri_nvmctrl_get_STATUS_reg(const void *const hw, hri_nvmctrl_status_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_nvmctrl_status_reg_t hri_nvmctrl_read_STATUS_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->STATUS.reg;
}

static inline void hri_nvmctrl_set_CTRLB_FWUP_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg |= NVMCTRL_CTRLB_FWUP_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_CTRLB_FWUP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_FWUP_Msk) >> NVMCTRL_CTRLB_FWUP_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_CTRLB_FWUP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp &= ~NVMCTRL_CTRLB_FWUP_Msk;
	tmp |= value << NVMCTRL_CTRLB_FWUP_Pos;
	((Nvmctrl *)hw)->CTRLB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLB_FWUP_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg &= ~NVMCTRL_CTRLB_FWUP_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLB_FWUP_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg ^= NVMCTRL_CTRLB_FWUP_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_CTRLB_CACHEDIS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg |= NVMCTRL_CTRLB_CACHEDIS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_CTRLB_CACHEDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_CACHEDIS_Msk) >> NVMCTRL_CTRLB_CACHEDIS_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_CTRLB_CACHEDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp &= ~NVMCTRL_CTRLB_CACHEDIS_Msk;
	tmp |= value << NVMCTRL_CTRLB_CACHEDIS_Pos;
	((Nvmctrl *)hw)->CTRLB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLB_CACHEDIS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg &= ~NVMCTRL_CTRLB_CACHEDIS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLB_CACHEDIS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg ^= NVMCTRL_CTRLB_CACHEDIS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_CTRLB_QWEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg |= NVMCTRL_CTRLB_QWEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_CTRLB_QWEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp = (tmp & NVMCTRL_CTRLB_QWEN_Msk) >> NVMCTRL_CTRLB_QWEN_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_CTRLB_QWEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLB.reg;
	tmp &= ~NVMCTRL_CTRLB_QWEN_Msk;
	tmp |= value << NVMCTRL_CTRLB_QWEN_Pos;
	((Nvmctrl *)hw)->CTRLB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLB_QWEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg &= ~NVMCTRL_CTRLB_QWEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLB_QWEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLB.reg ^= NVMCTRL_CTRLB_QWEN_Msk;
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

static inline void hri_nvmctrl_set_CTRLC_MANW_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLC.reg |= NVMCTRL_CTRLC_MANW_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_CTRLC_MANW_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLC.reg;
	tmp = (tmp & NVMCTRL_CTRLC_MANW_Msk) >> NVMCTRL_CTRLC_MANW_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_CTRLC_MANW_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->CTRLC.reg;
	tmp &= ~NVMCTRL_CTRLC_MANW_Msk;
	tmp |= value << NVMCTRL_CTRLC_MANW_Pos;
	((Nvmctrl *)hw)->CTRLC.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLC_MANW_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLC.reg &= ~NVMCTRL_CTRLC_MANW_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLC_MANW_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLC.reg ^= NVMCTRL_CTRLC_MANW_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_CTRLC_reg(const void *const hw, hri_nvmctrl_ctrlc_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLC.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlc_reg_t hri_nvmctrl_get_CTRLC_reg(const void *const hw, hri_nvmctrl_ctrlc_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Nvmctrl *)hw)->CTRLC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_CTRLC_reg(const void *const hw, hri_nvmctrl_ctrlc_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLC.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_CTRLC_reg(const void *const hw, hri_nvmctrl_ctrlc_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLC.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_CTRLC_reg(const void *const hw, hri_nvmctrl_ctrlc_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLC.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_ctrlc_reg_t hri_nvmctrl_read_CTRLC_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->CTRLC.reg;
}

static inline void hri_nvmctrl_set_EVCTRL_AUTOWEI_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg |= NVMCTRL_EVCTRL_AUTOWEI_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_EVCTRL_AUTOWEI_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Nvmctrl *)hw)->EVCTRL.reg;
	tmp = (tmp & NVMCTRL_EVCTRL_AUTOWEI_Msk) >> NVMCTRL_EVCTRL_AUTOWEI_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_EVCTRL_AUTOWEI_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->EVCTRL.reg;
	tmp &= ~NVMCTRL_EVCTRL_AUTOWEI_Msk;
	tmp |= value << NVMCTRL_EVCTRL_AUTOWEI_Pos;
	((Nvmctrl *)hw)->EVCTRL.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_EVCTRL_AUTOWEI_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg &= ~NVMCTRL_EVCTRL_AUTOWEI_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_EVCTRL_AUTOWEI_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg ^= NVMCTRL_EVCTRL_AUTOWEI_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_EVCTRL_AUTOWINV_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg |= NVMCTRL_EVCTRL_AUTOWINV_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_EVCTRL_AUTOWINV_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Nvmctrl *)hw)->EVCTRL.reg;
	tmp = (tmp & NVMCTRL_EVCTRL_AUTOWINV_Msk) >> NVMCTRL_EVCTRL_AUTOWINV_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_EVCTRL_AUTOWINV_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->EVCTRL.reg;
	tmp &= ~NVMCTRL_EVCTRL_AUTOWINV_Msk;
	tmp |= value << NVMCTRL_EVCTRL_AUTOWINV_Pos;
	((Nvmctrl *)hw)->EVCTRL.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_EVCTRL_AUTOWINV_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg &= ~NVMCTRL_EVCTRL_AUTOWINV_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_EVCTRL_AUTOWINV_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg ^= NVMCTRL_EVCTRL_AUTOWINV_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_EVCTRL_reg(const void *const hw, hri_nvmctrl_evctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_evctrl_reg_t hri_nvmctrl_get_EVCTRL_reg(const void *const hw, hri_nvmctrl_evctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Nvmctrl *)hw)->EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_EVCTRL_reg(const void *const hw, hri_nvmctrl_evctrl_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_EVCTRL_reg(const void *const hw, hri_nvmctrl_evctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_EVCTRL_reg(const void *const hw, hri_nvmctrl_evctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->EVCTRL.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_evctrl_reg_t hri_nvmctrl_read_EVCTRL_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->EVCTRL.reg;
}

static inline void hri_nvmctrl_set_ADDR_AOFFSET_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg |= NVMCTRL_ADDR_AOFFSET(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_addr_reg_t hri_nvmctrl_get_ADDR_AOFFSET_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp = (tmp & NVMCTRL_ADDR_AOFFSET(mask)) >> NVMCTRL_ADDR_AOFFSET_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_ADDR_AOFFSET_bf(const void *const hw, hri_nvmctrl_addr_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp &= ~NVMCTRL_ADDR_AOFFSET_Msk;
	tmp |= NVMCTRL_ADDR_AOFFSET(data);
	((Nvmctrl *)hw)->ADDR.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_ADDR_AOFFSET_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg &= ~NVMCTRL_ADDR_AOFFSET(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_ADDR_AOFFSET_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg ^= NVMCTRL_ADDR_AOFFSET(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_addr_reg_t hri_nvmctrl_read_ADDR_AOFFSET_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp = (tmp & NVMCTRL_ADDR_AOFFSET_Msk) >> NVMCTRL_ADDR_AOFFSET_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_ADDR_ARRAY_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg |= NVMCTRL_ADDR_ARRAY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_addr_reg_t hri_nvmctrl_get_ADDR_ARRAY_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp = (tmp & NVMCTRL_ADDR_ARRAY(mask)) >> NVMCTRL_ADDR_ARRAY_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_ADDR_ARRAY_bf(const void *const hw, hri_nvmctrl_addr_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp &= ~NVMCTRL_ADDR_ARRAY_Msk;
	tmp |= NVMCTRL_ADDR_ARRAY(data);
	((Nvmctrl *)hw)->ADDR.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_ADDR_ARRAY_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg &= ~NVMCTRL_ADDR_ARRAY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_ADDR_ARRAY_bf(const void *const hw, hri_nvmctrl_addr_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->ADDR.reg ^= NVMCTRL_ADDR_ARRAY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_addr_reg_t hri_nvmctrl_read_ADDR_ARRAY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->ADDR.reg;
	tmp = (tmp & NVMCTRL_ADDR_ARRAY_Msk) >> NVMCTRL_ADDR_ARRAY_Pos;
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

static inline void hri_nvmctrl_set_SULCK_BS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg |= NVMCTRL_SULCK_BS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SULCK_BS_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp = (tmp & NVMCTRL_SULCK_BS_Msk) >> NVMCTRL_SULCK_BS_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SULCK_BS_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp &= ~NVMCTRL_SULCK_BS_Msk;
	tmp |= value << NVMCTRL_SULCK_BS_Pos;
	((Nvmctrl *)hw)->SULCK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SULCK_BS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg &= ~NVMCTRL_SULCK_BS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SULCK_BS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg ^= NVMCTRL_SULCK_BS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SULCK_AS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg |= NVMCTRL_SULCK_AS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SULCK_AS_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp = (tmp & NVMCTRL_SULCK_AS_Msk) >> NVMCTRL_SULCK_AS_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SULCK_AS_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp &= ~NVMCTRL_SULCK_AS_Msk;
	tmp |= value << NVMCTRL_SULCK_AS_Pos;
	((Nvmctrl *)hw)->SULCK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SULCK_AS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg &= ~NVMCTRL_SULCK_AS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SULCK_AS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg ^= NVMCTRL_SULCK_AS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SULCK_DS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg |= NVMCTRL_SULCK_DS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SULCK_DS_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp = (tmp & NVMCTRL_SULCK_DS_Msk) >> NVMCTRL_SULCK_DS_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SULCK_DS_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp &= ~NVMCTRL_SULCK_DS_Msk;
	tmp |= value << NVMCTRL_SULCK_DS_Pos;
	((Nvmctrl *)hw)->SULCK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SULCK_DS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg &= ~NVMCTRL_SULCK_DS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SULCK_DS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg ^= NVMCTRL_SULCK_DS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SULCK_SLKEY_bf(const void *const hw, hri_nvmctrl_sulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg |= NVMCTRL_SULCK_SLKEY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_sulck_reg_t hri_nvmctrl_get_SULCK_SLKEY_bf(const void *const hw, hri_nvmctrl_sulck_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp = (tmp & NVMCTRL_SULCK_SLKEY(mask)) >> NVMCTRL_SULCK_SLKEY_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_SULCK_SLKEY_bf(const void *const hw, hri_nvmctrl_sulck_reg_t data)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp &= ~NVMCTRL_SULCK_SLKEY_Msk;
	tmp |= NVMCTRL_SULCK_SLKEY(data);
	((Nvmctrl *)hw)->SULCK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SULCK_SLKEY_bf(const void *const hw, hri_nvmctrl_sulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg &= ~NVMCTRL_SULCK_SLKEY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SULCK_SLKEY_bf(const void *const hw, hri_nvmctrl_sulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg ^= NVMCTRL_SULCK_SLKEY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_sulck_reg_t hri_nvmctrl_read_SULCK_SLKEY_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp = (tmp & NVMCTRL_SULCK_SLKEY_Msk) >> NVMCTRL_SULCK_SLKEY_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_SULCK_reg(const void *const hw, hri_nvmctrl_sulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_sulck_reg_t hri_nvmctrl_get_SULCK_reg(const void *const hw, hri_nvmctrl_sulck_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->SULCK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_SULCK_reg(const void *const hw, hri_nvmctrl_sulck_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SULCK_reg(const void *const hw, hri_nvmctrl_sulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SULCK_reg(const void *const hw, hri_nvmctrl_sulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SULCK.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_sulck_reg_t hri_nvmctrl_read_SULCK_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->SULCK.reg;
}

static inline void hri_nvmctrl_set_NSULCK_BNS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg |= NVMCTRL_NSULCK_BNS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_NSULCK_BNS_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp = (tmp & NVMCTRL_NSULCK_BNS_Msk) >> NVMCTRL_NSULCK_BNS_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_NSULCK_BNS_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp &= ~NVMCTRL_NSULCK_BNS_Msk;
	tmp |= value << NVMCTRL_NSULCK_BNS_Pos;
	((Nvmctrl *)hw)->NSULCK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_NSULCK_BNS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg &= ~NVMCTRL_NSULCK_BNS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_NSULCK_BNS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg ^= NVMCTRL_NSULCK_BNS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_NSULCK_ANS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg |= NVMCTRL_NSULCK_ANS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_NSULCK_ANS_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp = (tmp & NVMCTRL_NSULCK_ANS_Msk) >> NVMCTRL_NSULCK_ANS_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_NSULCK_ANS_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp &= ~NVMCTRL_NSULCK_ANS_Msk;
	tmp |= value << NVMCTRL_NSULCK_ANS_Pos;
	((Nvmctrl *)hw)->NSULCK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_NSULCK_ANS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg &= ~NVMCTRL_NSULCK_ANS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_NSULCK_ANS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg ^= NVMCTRL_NSULCK_ANS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_NSULCK_DNS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg |= NVMCTRL_NSULCK_DNS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_NSULCK_DNS_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp = (tmp & NVMCTRL_NSULCK_DNS_Msk) >> NVMCTRL_NSULCK_DNS_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_NSULCK_DNS_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp &= ~NVMCTRL_NSULCK_DNS_Msk;
	tmp |= value << NVMCTRL_NSULCK_DNS_Pos;
	((Nvmctrl *)hw)->NSULCK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_NSULCK_DNS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg &= ~NVMCTRL_NSULCK_DNS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_NSULCK_DNS_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg ^= NVMCTRL_NSULCK_DNS_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_NSULCK_NSLKEY_bf(const void *const hw, hri_nvmctrl_nsulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg |= NVMCTRL_NSULCK_NSLKEY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_nsulck_reg_t hri_nvmctrl_get_NSULCK_NSLKEY_bf(const void *const        hw,
                                                                        hri_nvmctrl_nsulck_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp = (tmp & NVMCTRL_NSULCK_NSLKEY(mask)) >> NVMCTRL_NSULCK_NSLKEY_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_NSULCK_NSLKEY_bf(const void *const hw, hri_nvmctrl_nsulck_reg_t data)
{
	uint16_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp &= ~NVMCTRL_NSULCK_NSLKEY_Msk;
	tmp |= NVMCTRL_NSULCK_NSLKEY(data);
	((Nvmctrl *)hw)->NSULCK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_NSULCK_NSLKEY_bf(const void *const hw, hri_nvmctrl_nsulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg &= ~NVMCTRL_NSULCK_NSLKEY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_NSULCK_NSLKEY_bf(const void *const hw, hri_nvmctrl_nsulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg ^= NVMCTRL_NSULCK_NSLKEY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_nsulck_reg_t hri_nvmctrl_read_NSULCK_NSLKEY_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp = (tmp & NVMCTRL_NSULCK_NSLKEY_Msk) >> NVMCTRL_NSULCK_NSLKEY_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_NSULCK_reg(const void *const hw, hri_nvmctrl_nsulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_nsulck_reg_t hri_nvmctrl_get_NSULCK_reg(const void *const hw, hri_nvmctrl_nsulck_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Nvmctrl *)hw)->NSULCK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_NSULCK_reg(const void *const hw, hri_nvmctrl_nsulck_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_NSULCK_reg(const void *const hw, hri_nvmctrl_nsulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_NSULCK_reg(const void *const hw, hri_nvmctrl_nsulck_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSULCK.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_nsulck_reg_t hri_nvmctrl_read_NSULCK_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->NSULCK.reg;
}

static inline void hri_nvmctrl_set_PARAM_FLASHP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg |= NVMCTRL_PARAM_FLASHP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_get_PARAM_FLASHP_bf(const void *const       hw,
                                                                      hri_nvmctrl_param_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_FLASHP(mask)) >> NVMCTRL_PARAM_FLASHP_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_PARAM_FLASHP_bf(const void *const hw, hri_nvmctrl_param_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp &= ~NVMCTRL_PARAM_FLASHP_Msk;
	tmp |= NVMCTRL_PARAM_FLASHP(data);
	((Nvmctrl *)hw)->PARAM.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_PARAM_FLASHP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg &= ~NVMCTRL_PARAM_FLASHP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_PARAM_FLASHP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg ^= NVMCTRL_PARAM_FLASHP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_read_PARAM_FLASHP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_FLASHP_Msk) >> NVMCTRL_PARAM_FLASHP_Pos;
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

static inline void hri_nvmctrl_set_PARAM_DFLASHP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg |= NVMCTRL_PARAM_DFLASHP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_get_PARAM_DFLASHP_bf(const void *const       hw,
                                                                       hri_nvmctrl_param_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_DFLASHP(mask)) >> NVMCTRL_PARAM_DFLASHP_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_PARAM_DFLASHP_bf(const void *const hw, hri_nvmctrl_param_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp &= ~NVMCTRL_PARAM_DFLASHP_Msk;
	tmp |= NVMCTRL_PARAM_DFLASHP(data);
	((Nvmctrl *)hw)->PARAM.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_PARAM_DFLASHP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg &= ~NVMCTRL_PARAM_DFLASHP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_PARAM_DFLASHP_bf(const void *const hw, hri_nvmctrl_param_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->PARAM.reg ^= NVMCTRL_PARAM_DFLASHP(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_param_reg_t hri_nvmctrl_read_PARAM_DFLASHP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->PARAM.reg;
	tmp = (tmp & NVMCTRL_PARAM_DFLASHP_Msk) >> NVMCTRL_PARAM_DFLASHP_Pos;
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

static inline void hri_nvmctrl_set_SECCTRL_TAMPEEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg |= NVMCTRL_SECCTRL_TAMPEEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SECCTRL_TAMPEEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp = (tmp & NVMCTRL_SECCTRL_TAMPEEN_Msk) >> NVMCTRL_SECCTRL_TAMPEEN_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SECCTRL_TAMPEEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp &= ~NVMCTRL_SECCTRL_TAMPEEN_Msk;
	tmp |= value << NVMCTRL_SECCTRL_TAMPEEN_Pos;
	((Nvmctrl *)hw)->SECCTRL.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SECCTRL_TAMPEEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg &= ~NVMCTRL_SECCTRL_TAMPEEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SECCTRL_TAMPEEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg ^= NVMCTRL_SECCTRL_TAMPEEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SECCTRL_SILACC_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg |= NVMCTRL_SECCTRL_SILACC_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SECCTRL_SILACC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp = (tmp & NVMCTRL_SECCTRL_SILACC_Msk) >> NVMCTRL_SECCTRL_SILACC_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SECCTRL_SILACC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp &= ~NVMCTRL_SECCTRL_SILACC_Msk;
	tmp |= value << NVMCTRL_SECCTRL_SILACC_Pos;
	((Nvmctrl *)hw)->SECCTRL.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SECCTRL_SILACC_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg &= ~NVMCTRL_SECCTRL_SILACC_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SECCTRL_SILACC_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg ^= NVMCTRL_SECCTRL_SILACC_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SECCTRL_DSCEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg |= NVMCTRL_SECCTRL_DSCEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SECCTRL_DSCEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp = (tmp & NVMCTRL_SECCTRL_DSCEN_Msk) >> NVMCTRL_SECCTRL_DSCEN_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SECCTRL_DSCEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp &= ~NVMCTRL_SECCTRL_DSCEN_Msk;
	tmp |= value << NVMCTRL_SECCTRL_DSCEN_Pos;
	((Nvmctrl *)hw)->SECCTRL.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SECCTRL_DSCEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg &= ~NVMCTRL_SECCTRL_DSCEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SECCTRL_DSCEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg ^= NVMCTRL_SECCTRL_DSCEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SECCTRL_DXN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg |= NVMCTRL_SECCTRL_DXN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SECCTRL_DXN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp = (tmp & NVMCTRL_SECCTRL_DXN_Msk) >> NVMCTRL_SECCTRL_DXN_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SECCTRL_DXN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp &= ~NVMCTRL_SECCTRL_DXN_Msk;
	tmp |= value << NVMCTRL_SECCTRL_DXN_Pos;
	((Nvmctrl *)hw)->SECCTRL.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SECCTRL_DXN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg &= ~NVMCTRL_SECCTRL_DXN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SECCTRL_DXN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg ^= NVMCTRL_SECCTRL_DXN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SECCTRL_TEROW_bf(const void *const hw, hri_nvmctrl_secctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg |= NVMCTRL_SECCTRL_TEROW(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_secctrl_reg_t hri_nvmctrl_get_SECCTRL_TEROW_bf(const void *const         hw,
                                                                         hri_nvmctrl_secctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp = (tmp & NVMCTRL_SECCTRL_TEROW(mask)) >> NVMCTRL_SECCTRL_TEROW_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_SECCTRL_TEROW_bf(const void *const hw, hri_nvmctrl_secctrl_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp &= ~NVMCTRL_SECCTRL_TEROW_Msk;
	tmp |= NVMCTRL_SECCTRL_TEROW(data);
	((Nvmctrl *)hw)->SECCTRL.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SECCTRL_TEROW_bf(const void *const hw, hri_nvmctrl_secctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg &= ~NVMCTRL_SECCTRL_TEROW(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SECCTRL_TEROW_bf(const void *const hw, hri_nvmctrl_secctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg ^= NVMCTRL_SECCTRL_TEROW(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_secctrl_reg_t hri_nvmctrl_read_SECCTRL_TEROW_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp = (tmp & NVMCTRL_SECCTRL_TEROW_Msk) >> NVMCTRL_SECCTRL_TEROW_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_SECCTRL_KEY_bf(const void *const hw, hri_nvmctrl_secctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg |= NVMCTRL_SECCTRL_KEY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_secctrl_reg_t hri_nvmctrl_get_SECCTRL_KEY_bf(const void *const         hw,
                                                                       hri_nvmctrl_secctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp = (tmp & NVMCTRL_SECCTRL_KEY(mask)) >> NVMCTRL_SECCTRL_KEY_Pos;
	return tmp;
}

static inline void hri_nvmctrl_write_SECCTRL_KEY_bf(const void *const hw, hri_nvmctrl_secctrl_reg_t data)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp &= ~NVMCTRL_SECCTRL_KEY_Msk;
	tmp |= NVMCTRL_SECCTRL_KEY(data);
	((Nvmctrl *)hw)->SECCTRL.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SECCTRL_KEY_bf(const void *const hw, hri_nvmctrl_secctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg &= ~NVMCTRL_SECCTRL_KEY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SECCTRL_KEY_bf(const void *const hw, hri_nvmctrl_secctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg ^= NVMCTRL_SECCTRL_KEY(mask);
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_secctrl_reg_t hri_nvmctrl_read_SECCTRL_KEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp = (tmp & NVMCTRL_SECCTRL_KEY_Msk) >> NVMCTRL_SECCTRL_KEY_Pos;
	return tmp;
}

static inline void hri_nvmctrl_set_SECCTRL_reg(const void *const hw, hri_nvmctrl_secctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_secctrl_reg_t hri_nvmctrl_get_SECCTRL_reg(const void *const         hw,
                                                                    hri_nvmctrl_secctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SECCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_SECCTRL_reg(const void *const hw, hri_nvmctrl_secctrl_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SECCTRL_reg(const void *const hw, hri_nvmctrl_secctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SECCTRL_reg(const void *const hw, hri_nvmctrl_secctrl_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SECCTRL.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_secctrl_reg_t hri_nvmctrl_read_SECCTRL_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->SECCTRL.reg;
}

static inline void hri_nvmctrl_set_SCFGB_BCREN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg |= NVMCTRL_SCFGB_BCREN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SCFGB_BCREN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SCFGB.reg;
	tmp = (tmp & NVMCTRL_SCFGB_BCREN_Msk) >> NVMCTRL_SCFGB_BCREN_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SCFGB_BCREN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SCFGB.reg;
	tmp &= ~NVMCTRL_SCFGB_BCREN_Msk;
	tmp |= value << NVMCTRL_SCFGB_BCREN_Pos;
	((Nvmctrl *)hw)->SCFGB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SCFGB_BCREN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg &= ~NVMCTRL_SCFGB_BCREN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SCFGB_BCREN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg ^= NVMCTRL_SCFGB_BCREN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SCFGB_BCWEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg |= NVMCTRL_SCFGB_BCWEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SCFGB_BCWEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SCFGB.reg;
	tmp = (tmp & NVMCTRL_SCFGB_BCWEN_Msk) >> NVMCTRL_SCFGB_BCWEN_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SCFGB_BCWEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SCFGB.reg;
	tmp &= ~NVMCTRL_SCFGB_BCWEN_Msk;
	tmp |= value << NVMCTRL_SCFGB_BCWEN_Pos;
	((Nvmctrl *)hw)->SCFGB.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SCFGB_BCWEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg &= ~NVMCTRL_SCFGB_BCWEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SCFGB_BCWEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg ^= NVMCTRL_SCFGB_BCWEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SCFGB_reg(const void *const hw, hri_nvmctrl_scfgb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_scfgb_reg_t hri_nvmctrl_get_SCFGB_reg(const void *const hw, hri_nvmctrl_scfgb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SCFGB.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_SCFGB_reg(const void *const hw, hri_nvmctrl_scfgb_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SCFGB_reg(const void *const hw, hri_nvmctrl_scfgb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SCFGB_reg(const void *const hw, hri_nvmctrl_scfgb_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGB.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_scfgb_reg_t hri_nvmctrl_read_SCFGB_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->SCFGB.reg;
}

static inline void hri_nvmctrl_set_SCFGAD_URWEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGAD.reg |= NVMCTRL_SCFGAD_URWEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_SCFGAD_URWEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SCFGAD.reg;
	tmp = (tmp & NVMCTRL_SCFGAD_URWEN_Msk) >> NVMCTRL_SCFGAD_URWEN_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_SCFGAD_URWEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->SCFGAD.reg;
	tmp &= ~NVMCTRL_SCFGAD_URWEN_Msk;
	tmp |= value << NVMCTRL_SCFGAD_URWEN_Pos;
	((Nvmctrl *)hw)->SCFGAD.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SCFGAD_URWEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGAD.reg &= ~NVMCTRL_SCFGAD_URWEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SCFGAD_URWEN_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGAD.reg ^= NVMCTRL_SCFGAD_URWEN_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_SCFGAD_reg(const void *const hw, hri_nvmctrl_scfgad_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGAD.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_scfgad_reg_t hri_nvmctrl_get_SCFGAD_reg(const void *const hw, hri_nvmctrl_scfgad_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->SCFGAD.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_SCFGAD_reg(const void *const hw, hri_nvmctrl_scfgad_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGAD.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_SCFGAD_reg(const void *const hw, hri_nvmctrl_scfgad_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGAD.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_SCFGAD_reg(const void *const hw, hri_nvmctrl_scfgad_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->SCFGAD.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_scfgad_reg_t hri_nvmctrl_read_SCFGAD_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->SCFGAD.reg;
}

static inline void hri_nvmctrl_set_NONSEC_WRITE_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NONSEC.reg |= NVMCTRL_NONSEC_WRITE_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_NONSEC_WRITE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->NONSEC.reg;
	tmp = (tmp & NVMCTRL_NONSEC_WRITE_Msk) >> NVMCTRL_NONSEC_WRITE_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_NONSEC_WRITE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->NONSEC.reg;
	tmp &= ~NVMCTRL_NONSEC_WRITE_Msk;
	tmp |= value << NVMCTRL_NONSEC_WRITE_Pos;
	((Nvmctrl *)hw)->NONSEC.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_NONSEC_WRITE_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NONSEC.reg &= ~NVMCTRL_NONSEC_WRITE_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_NONSEC_WRITE_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NONSEC.reg ^= NVMCTRL_NONSEC_WRITE_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_NONSEC_reg(const void *const hw, hri_nvmctrl_nonsec_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NONSEC.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_nonsec_reg_t hri_nvmctrl_get_NONSEC_reg(const void *const hw, hri_nvmctrl_nonsec_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->NONSEC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_NONSEC_reg(const void *const hw, hri_nvmctrl_nonsec_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NONSEC.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_NONSEC_reg(const void *const hw, hri_nvmctrl_nonsec_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NONSEC.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_NONSEC_reg(const void *const hw, hri_nvmctrl_nonsec_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NONSEC.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_nonsec_reg_t hri_nvmctrl_read_NONSEC_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->NONSEC.reg;
}

static inline void hri_nvmctrl_set_NSCHK_WRITE_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSCHK.reg |= NVMCTRL_NSCHK_WRITE_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_nvmctrl_get_NSCHK_WRITE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->NSCHK.reg;
	tmp = (tmp & NVMCTRL_NSCHK_WRITE_Msk) >> NVMCTRL_NSCHK_WRITE_Pos;
	return (bool)tmp;
}

static inline void hri_nvmctrl_write_NSCHK_WRITE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	NVMCTRL_CRITICAL_SECTION_ENTER();
	tmp = ((Nvmctrl *)hw)->NSCHK.reg;
	tmp &= ~NVMCTRL_NSCHK_WRITE_Msk;
	tmp |= value << NVMCTRL_NSCHK_WRITE_Pos;
	((Nvmctrl *)hw)->NSCHK.reg = tmp;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_NSCHK_WRITE_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSCHK.reg &= ~NVMCTRL_NSCHK_WRITE_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_NSCHK_WRITE_bit(const void *const hw)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSCHK.reg ^= NVMCTRL_NSCHK_WRITE_Msk;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_set_NSCHK_reg(const void *const hw, hri_nvmctrl_nschk_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSCHK.reg |= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_nschk_reg_t hri_nvmctrl_get_NSCHK_reg(const void *const hw, hri_nvmctrl_nschk_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Nvmctrl *)hw)->NSCHK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_nvmctrl_write_NSCHK_reg(const void *const hw, hri_nvmctrl_nschk_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSCHK.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_clear_NSCHK_reg(const void *const hw, hri_nvmctrl_nschk_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSCHK.reg &= ~mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_toggle_NSCHK_reg(const void *const hw, hri_nvmctrl_nschk_reg_t mask)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->NSCHK.reg ^= mask;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline hri_nvmctrl_nschk_reg_t hri_nvmctrl_read_NSCHK_reg(const void *const hw)
{
	return ((Nvmctrl *)hw)->NSCHK.reg;
}

static inline void hri_nvmctrl_write_CTRLA_reg(const void *const hw, hri_nvmctrl_ctrla_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->CTRLA.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_nvmctrl_write_DSCC_reg(const void *const hw, hri_nvmctrl_dscc_reg_t data)
{
	NVMCTRL_CRITICAL_SECTION_ENTER();
	((Nvmctrl *)hw)->DSCC.reg = data;
	NVMCTRL_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_NVMCTRL_L10_H_INCLUDED */
#endif /* _SAML10_NVMCTRL_COMPONENT_ */
