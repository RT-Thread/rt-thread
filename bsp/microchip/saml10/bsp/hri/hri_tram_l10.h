/**
 * \file
 *
 * \brief SAM TRAM
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

#ifdef _SAML10_TRAM_COMPONENT_
#ifndef _HRI_TRAM_L10_H_INCLUDED_
#define _HRI_TRAM_L10_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_TRAM_CRITICAL_SECTIONS)
#define TRAM_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define TRAM_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define TRAM_CRITICAL_SECTION_ENTER()
#define TRAM_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_tram_dscc_reg_t;
typedef uint32_t hri_tram_ram_reg_t;
typedef uint32_t hri_tram_syncbusy_reg_t;
typedef uint8_t  hri_tram_ctrla_reg_t;
typedef uint8_t  hri_tram_intenset_reg_t;
typedef uint8_t  hri_tram_intflag_reg_t;
typedef uint8_t  hri_tram_permr_reg_t;
typedef uint8_t  hri_tram_permw_reg_t;
typedef uint8_t  hri_tram_status_reg_t;

static inline void hri_tram_wait_for_sync(const void *const hw, hri_tram_syncbusy_reg_t reg)
{
	while (((Tram *)hw)->SYNCBUSY.reg & reg) {
	};
}

static inline bool hri_tram_is_syncing(const void *const hw, hri_tram_syncbusy_reg_t reg)
{
	return ((Tram *)hw)->SYNCBUSY.reg & reg;
}

static inline bool hri_tram_get_INTFLAG_ERR_bit(const void *const hw)
{
	return (((Tram *)hw)->INTFLAG.reg & TRAM_INTFLAG_ERR_Msk) >> TRAM_INTFLAG_ERR_Pos;
}

static inline void hri_tram_clear_INTFLAG_ERR_bit(const void *const hw)
{
	((Tram *)hw)->INTFLAG.reg = TRAM_INTFLAG_ERR_Msk;
}

static inline bool hri_tram_get_INTFLAG_DRP_bit(const void *const hw)
{
	return (((Tram *)hw)->INTFLAG.reg & TRAM_INTFLAG_DRP_Msk) >> TRAM_INTFLAG_DRP_Pos;
}

static inline void hri_tram_clear_INTFLAG_DRP_bit(const void *const hw)
{
	((Tram *)hw)->INTFLAG.reg = TRAM_INTFLAG_DRP_Msk;
}

static inline bool hri_tram_get_interrupt_ERR_bit(const void *const hw)
{
	return (((Tram *)hw)->INTFLAG.reg & TRAM_INTFLAG_ERR_Msk) >> TRAM_INTFLAG_ERR_Pos;
}

static inline void hri_tram_clear_interrupt_ERR_bit(const void *const hw)
{
	((Tram *)hw)->INTFLAG.reg = TRAM_INTFLAG_ERR_Msk;
}

static inline bool hri_tram_get_interrupt_DRP_bit(const void *const hw)
{
	return (((Tram *)hw)->INTFLAG.reg & TRAM_INTFLAG_DRP_Msk) >> TRAM_INTFLAG_DRP_Pos;
}

static inline void hri_tram_clear_interrupt_DRP_bit(const void *const hw)
{
	((Tram *)hw)->INTFLAG.reg = TRAM_INTFLAG_DRP_Msk;
}

static inline hri_tram_intflag_reg_t hri_tram_get_INTFLAG_reg(const void *const hw, hri_tram_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tram *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tram_intflag_reg_t hri_tram_read_INTFLAG_reg(const void *const hw)
{
	return ((Tram *)hw)->INTFLAG.reg;
}

static inline void hri_tram_clear_INTFLAG_reg(const void *const hw, hri_tram_intflag_reg_t mask)
{
	((Tram *)hw)->INTFLAG.reg = mask;
}

static inline void hri_tram_set_INTEN_ERR_bit(const void *const hw)
{
	((Tram *)hw)->INTENSET.reg = TRAM_INTENSET_ERR_Msk;
}

static inline bool hri_tram_get_INTEN_ERR_bit(const void *const hw)
{
	return (((Tram *)hw)->INTENSET.reg & TRAM_INTENSET_ERR_Msk) >> TRAM_INTENSET_ERR_Pos;
}

static inline void hri_tram_write_INTEN_ERR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Tram *)hw)->INTENCLR.reg = TRAM_INTENSET_ERR_Msk;
	} else {
		((Tram *)hw)->INTENSET.reg = TRAM_INTENSET_ERR_Msk;
	}
}

static inline void hri_tram_clear_INTEN_ERR_bit(const void *const hw)
{
	((Tram *)hw)->INTENCLR.reg = TRAM_INTENSET_ERR_Msk;
}

static inline void hri_tram_set_INTEN_DRP_bit(const void *const hw)
{
	((Tram *)hw)->INTENSET.reg = TRAM_INTENSET_DRP_Msk;
}

static inline bool hri_tram_get_INTEN_DRP_bit(const void *const hw)
{
	return (((Tram *)hw)->INTENSET.reg & TRAM_INTENSET_DRP_Msk) >> TRAM_INTENSET_DRP_Pos;
}

static inline void hri_tram_write_INTEN_DRP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Tram *)hw)->INTENCLR.reg = TRAM_INTENSET_DRP_Msk;
	} else {
		((Tram *)hw)->INTENSET.reg = TRAM_INTENSET_DRP_Msk;
	}
}

static inline void hri_tram_clear_INTEN_DRP_bit(const void *const hw)
{
	((Tram *)hw)->INTENCLR.reg = TRAM_INTENSET_DRP_Msk;
}

static inline void hri_tram_set_INTEN_reg(const void *const hw, hri_tram_intenset_reg_t mask)
{
	((Tram *)hw)->INTENSET.reg = mask;
}

static inline hri_tram_intenset_reg_t hri_tram_get_INTEN_reg(const void *const hw, hri_tram_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tram *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tram_intenset_reg_t hri_tram_read_INTEN_reg(const void *const hw)
{
	return ((Tram *)hw)->INTENSET.reg;
}

static inline void hri_tram_write_INTEN_reg(const void *const hw, hri_tram_intenset_reg_t data)
{
	((Tram *)hw)->INTENSET.reg = data;
	((Tram *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_tram_clear_INTEN_reg(const void *const hw, hri_tram_intenset_reg_t mask)
{
	((Tram *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_tram_get_STATUS_RAMINV_bit(const void *const hw)
{
	return (((Tram *)hw)->STATUS.reg & TRAM_STATUS_RAMINV_Msk) >> TRAM_STATUS_RAMINV_Pos;
}

static inline bool hri_tram_get_STATUS_DRP_bit(const void *const hw)
{
	return (((Tram *)hw)->STATUS.reg & TRAM_STATUS_DRP_Msk) >> TRAM_STATUS_DRP_Pos;
}

static inline hri_tram_status_reg_t hri_tram_get_STATUS_reg(const void *const hw, hri_tram_status_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tram *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tram_status_reg_t hri_tram_read_STATUS_reg(const void *const hw)
{
	return ((Tram *)hw)->STATUS.reg;
}

static inline bool hri_tram_get_SYNCBUSY_SWRST_bit(const void *const hw)
{
	return (((Tram *)hw)->SYNCBUSY.reg & TRAM_SYNCBUSY_SWRST_Msk) >> TRAM_SYNCBUSY_SWRST_Pos;
}

static inline bool hri_tram_get_SYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Tram *)hw)->SYNCBUSY.reg & TRAM_SYNCBUSY_ENABLE_Msk) >> TRAM_SYNCBUSY_ENABLE_Pos;
}

static inline hri_tram_syncbusy_reg_t hri_tram_get_SYNCBUSY_reg(const void *const hw, hri_tram_syncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tram *)hw)->SYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tram_syncbusy_reg_t hri_tram_read_SYNCBUSY_reg(const void *const hw)
{
	return ((Tram *)hw)->SYNCBUSY.reg;
}

static inline hri_tram_permr_reg_t hri_tram_get_PERMR_DATA_bf(const void *const hw, hri_tram_permr_reg_t mask)
{
	return (((Tram *)hw)->PERMR.reg & TRAM_PERMR_DATA(mask)) >> TRAM_PERMR_DATA_Pos;
}

static inline hri_tram_permr_reg_t hri_tram_read_PERMR_DATA_bf(const void *const hw)
{
	return (((Tram *)hw)->PERMR.reg & TRAM_PERMR_DATA_Msk) >> TRAM_PERMR_DATA_Pos;
}

static inline hri_tram_permr_reg_t hri_tram_get_PERMR_reg(const void *const hw, hri_tram_permr_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Tram *)hw)->PERMR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_tram_permr_reg_t hri_tram_read_PERMR_reg(const void *const hw)
{
	return ((Tram *)hw)->PERMR.reg;
}

static inline void hri_tram_set_CTRLA_SWRST_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg |= TRAM_CTRLA_SWRST_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_SWRST);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tram_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint8_t tmp;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_SWRST);
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp = (tmp & TRAM_CTRLA_SWRST_Msk) >> TRAM_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_tram_set_CTRLA_ENABLE_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg |= TRAM_CTRLA_ENABLE_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_SWRST | TRAM_SYNCBUSY_ENABLE);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tram_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_SWRST | TRAM_SYNCBUSY_ENABLE);
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp = (tmp & TRAM_CTRLA_ENABLE_Msk) >> TRAM_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_tram_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TRAM_CRITICAL_SECTION_ENTER();
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp &= ~TRAM_CTRLA_ENABLE_Msk;
	tmp |= value << TRAM_CTRLA_ENABLE_Pos;
	((Tram *)hw)->CTRLA.reg = tmp;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_SWRST | TRAM_SYNCBUSY_ENABLE);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg &= ~TRAM_CTRLA_ENABLE_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_SWRST | TRAM_SYNCBUSY_ENABLE);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg ^= TRAM_CTRLA_ENABLE_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_SWRST | TRAM_SYNCBUSY_ENABLE);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_set_CTRLA_TAMPERS_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg |= TRAM_CTRLA_TAMPERS_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tram_get_CTRLA_TAMPERS_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp = (tmp & TRAM_CTRLA_TAMPERS_Msk) >> TRAM_CTRLA_TAMPERS_Pos;
	return (bool)tmp;
}

static inline void hri_tram_write_CTRLA_TAMPERS_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TRAM_CRITICAL_SECTION_ENTER();
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp &= ~TRAM_CTRLA_TAMPERS_Msk;
	tmp |= value << TRAM_CTRLA_TAMPERS_Pos;
	((Tram *)hw)->CTRLA.reg = tmp;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_clear_CTRLA_TAMPERS_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg &= ~TRAM_CTRLA_TAMPERS_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_toggle_CTRLA_TAMPERS_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg ^= TRAM_CTRLA_TAMPERS_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_set_CTRLA_DRP_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg |= TRAM_CTRLA_DRP_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tram_get_CTRLA_DRP_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp = (tmp & TRAM_CTRLA_DRP_Msk) >> TRAM_CTRLA_DRP_Pos;
	return (bool)tmp;
}

static inline void hri_tram_write_CTRLA_DRP_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TRAM_CRITICAL_SECTION_ENTER();
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp &= ~TRAM_CTRLA_DRP_Msk;
	tmp |= value << TRAM_CTRLA_DRP_Pos;
	((Tram *)hw)->CTRLA.reg = tmp;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_clear_CTRLA_DRP_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg &= ~TRAM_CTRLA_DRP_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_toggle_CTRLA_DRP_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg ^= TRAM_CTRLA_DRP_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_set_CTRLA_SILACC_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg |= TRAM_CTRLA_SILACC_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_tram_get_CTRLA_SILACC_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp = (tmp & TRAM_CTRLA_SILACC_Msk) >> TRAM_CTRLA_SILACC_Pos;
	return (bool)tmp;
}

static inline void hri_tram_write_CTRLA_SILACC_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	TRAM_CRITICAL_SECTION_ENTER();
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp &= ~TRAM_CTRLA_SILACC_Msk;
	tmp |= value << TRAM_CTRLA_SILACC_Pos;
	((Tram *)hw)->CTRLA.reg = tmp;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_clear_CTRLA_SILACC_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg &= ~TRAM_CTRLA_SILACC_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_toggle_CTRLA_SILACC_bit(const void *const hw)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg ^= TRAM_CTRLA_SILACC_Msk;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_set_CTRLA_reg(const void *const hw, hri_tram_ctrla_reg_t mask)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg |= mask;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline hri_tram_ctrla_reg_t hri_tram_get_CTRLA_reg(const void *const hw, hri_tram_ctrla_reg_t mask)
{
	uint8_t tmp;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	tmp = ((Tram *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tram_write_CTRLA_reg(const void *const hw, hri_tram_ctrla_reg_t data)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg = data;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_clear_CTRLA_reg(const void *const hw, hri_tram_ctrla_reg_t mask)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg &= ~mask;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_toggle_CTRLA_reg(const void *const hw, hri_tram_ctrla_reg_t mask)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->CTRLA.reg ^= mask;
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline hri_tram_ctrla_reg_t hri_tram_read_CTRLA_reg(const void *const hw)
{
	hri_tram_wait_for_sync(hw, TRAM_SYNCBUSY_MASK);
	return ((Tram *)hw)->CTRLA.reg;
}

static inline void hri_tram_set_RAM_DATA_bf(const void *const hw, uint8_t index, hri_tram_ram_reg_t mask)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->RAM[index].reg |= TRAM_RAM_DATA(mask);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline hri_tram_ram_reg_t hri_tram_get_RAM_DATA_bf(const void *const hw, uint8_t index, hri_tram_ram_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tram *)hw)->RAM[index].reg;
	tmp = (tmp & TRAM_RAM_DATA(mask)) >> TRAM_RAM_DATA_Pos;
	return tmp;
}

static inline void hri_tram_write_RAM_DATA_bf(const void *const hw, uint8_t index, hri_tram_ram_reg_t data)
{
	uint32_t tmp;
	TRAM_CRITICAL_SECTION_ENTER();
	tmp = ((Tram *)hw)->RAM[index].reg;
	tmp &= ~TRAM_RAM_DATA_Msk;
	tmp |= TRAM_RAM_DATA(data);
	((Tram *)hw)->RAM[index].reg = tmp;
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_clear_RAM_DATA_bf(const void *const hw, uint8_t index, hri_tram_ram_reg_t mask)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->RAM[index].reg &= ~TRAM_RAM_DATA(mask);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_toggle_RAM_DATA_bf(const void *const hw, uint8_t index, hri_tram_ram_reg_t mask)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->RAM[index].reg ^= TRAM_RAM_DATA(mask);
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline hri_tram_ram_reg_t hri_tram_read_RAM_DATA_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Tram *)hw)->RAM[index].reg;
	tmp = (tmp & TRAM_RAM_DATA_Msk) >> TRAM_RAM_DATA_Pos;
	return tmp;
}

static inline void hri_tram_set_RAM_reg(const void *const hw, uint8_t index, hri_tram_ram_reg_t mask)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->RAM[index].reg |= mask;
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline hri_tram_ram_reg_t hri_tram_get_RAM_reg(const void *const hw, uint8_t index, hri_tram_ram_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Tram *)hw)->RAM[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_tram_write_RAM_reg(const void *const hw, uint8_t index, hri_tram_ram_reg_t data)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->RAM[index].reg = data;
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_clear_RAM_reg(const void *const hw, uint8_t index, hri_tram_ram_reg_t mask)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->RAM[index].reg &= ~mask;
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_toggle_RAM_reg(const void *const hw, uint8_t index, hri_tram_ram_reg_t mask)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->RAM[index].reg ^= mask;
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline hri_tram_ram_reg_t hri_tram_read_RAM_reg(const void *const hw, uint8_t index)
{
	return ((Tram *)hw)->RAM[index].reg;
}

static inline void hri_tram_write_DSCC_reg(const void *const hw, hri_tram_dscc_reg_t data)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->DSCC.reg = data;
	TRAM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_tram_write_PERMW_reg(const void *const hw, hri_tram_permw_reg_t data)
{
	TRAM_CRITICAL_SECTION_ENTER();
	((Tram *)hw)->PERMW.reg = data;
	TRAM_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_TRAM_L10_H_INCLUDED */
#endif /* _SAML10_TRAM_COMPONENT_ */
