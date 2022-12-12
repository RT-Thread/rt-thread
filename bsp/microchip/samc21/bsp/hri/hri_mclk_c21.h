/**
 * \file
 *
 * \brief SAM MCLK
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

#ifdef _SAMC21_MCLK_COMPONENT_
#ifndef _HRI_MCLK_C21_H_INCLUDED_
#define _HRI_MCLK_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_MCLK_CRITICAL_SECTIONS)
#define MCLK_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define MCLK_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define MCLK_CRITICAL_SECTION_ENTER()
#define MCLK_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_mclk_ahbmask_reg_t;
typedef uint32_t hri_mclk_apbamask_reg_t;
typedef uint32_t hri_mclk_apbbmask_reg_t;
typedef uint32_t hri_mclk_apbcmask_reg_t;
typedef uint8_t  hri_mclk_cpudiv_reg_t;
typedef uint8_t  hri_mclk_intenset_reg_t;
typedef uint8_t  hri_mclk_intflag_reg_t;

static inline bool hri_mclk_get_INTFLAG_CKRDY_bit(const void *const hw)
{
	return (((Mclk *)hw)->INTFLAG.reg & MCLK_INTFLAG_CKRDY) >> MCLK_INTFLAG_CKRDY_Pos;
}

static inline void hri_mclk_clear_INTFLAG_CKRDY_bit(const void *const hw)
{
	((Mclk *)hw)->INTFLAG.reg = MCLK_INTFLAG_CKRDY;
}

static inline bool hri_mclk_get_interrupt_CKRDY_bit(const void *const hw)
{
	return (((Mclk *)hw)->INTFLAG.reg & MCLK_INTFLAG_CKRDY) >> MCLK_INTFLAG_CKRDY_Pos;
}

static inline void hri_mclk_clear_interrupt_CKRDY_bit(const void *const hw)
{
	((Mclk *)hw)->INTFLAG.reg = MCLK_INTFLAG_CKRDY;
}

static inline hri_mclk_intflag_reg_t hri_mclk_get_INTFLAG_reg(const void *const hw, hri_mclk_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Mclk *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mclk_intflag_reg_t hri_mclk_read_INTFLAG_reg(const void *const hw)
{
	return ((Mclk *)hw)->INTFLAG.reg;
}

static inline void hri_mclk_clear_INTFLAG_reg(const void *const hw, hri_mclk_intflag_reg_t mask)
{
	((Mclk *)hw)->INTFLAG.reg = mask;
}

static inline void hri_mclk_set_INTEN_CKRDY_bit(const void *const hw)
{
	((Mclk *)hw)->INTENSET.reg = MCLK_INTENSET_CKRDY;
}

static inline bool hri_mclk_get_INTEN_CKRDY_bit(const void *const hw)
{
	return (((Mclk *)hw)->INTENSET.reg & MCLK_INTENSET_CKRDY) >> MCLK_INTENSET_CKRDY_Pos;
}

static inline void hri_mclk_write_INTEN_CKRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Mclk *)hw)->INTENCLR.reg = MCLK_INTENSET_CKRDY;
	} else {
		((Mclk *)hw)->INTENSET.reg = MCLK_INTENSET_CKRDY;
	}
}

static inline void hri_mclk_clear_INTEN_CKRDY_bit(const void *const hw)
{
	((Mclk *)hw)->INTENCLR.reg = MCLK_INTENSET_CKRDY;
}

static inline void hri_mclk_set_INTEN_reg(const void *const hw, hri_mclk_intenset_reg_t mask)
{
	((Mclk *)hw)->INTENSET.reg = mask;
}

static inline hri_mclk_intenset_reg_t hri_mclk_get_INTEN_reg(const void *const hw, hri_mclk_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Mclk *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mclk_intenset_reg_t hri_mclk_read_INTEN_reg(const void *const hw)
{
	return ((Mclk *)hw)->INTENSET.reg;
}

static inline void hri_mclk_write_INTEN_reg(const void *const hw, hri_mclk_intenset_reg_t data)
{
	((Mclk *)hw)->INTENSET.reg = data;
	((Mclk *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_mclk_clear_INTEN_reg(const void *const hw, hri_mclk_intenset_reg_t mask)
{
	((Mclk *)hw)->INTENCLR.reg = mask;
}

static inline void hri_mclk_set_CPUDIV_CPUDIV_bf(const void *const hw, hri_mclk_cpudiv_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->CPUDIV.reg |= MCLK_CPUDIV_CPUDIV(mask);
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_cpudiv_reg_t hri_mclk_get_CPUDIV_CPUDIV_bf(const void *const hw, hri_mclk_cpudiv_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Mclk *)hw)->CPUDIV.reg;
	tmp = (tmp & MCLK_CPUDIV_CPUDIV(mask)) >> MCLK_CPUDIV_CPUDIV_Pos;
	return tmp;
}

static inline void hri_mclk_write_CPUDIV_CPUDIV_bf(const void *const hw, hri_mclk_cpudiv_reg_t data)
{
	uint8_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->CPUDIV.reg;
	tmp &= ~MCLK_CPUDIV_CPUDIV_Msk;
	tmp |= MCLK_CPUDIV_CPUDIV(data);
	((Mclk *)hw)->CPUDIV.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_CPUDIV_CPUDIV_bf(const void *const hw, hri_mclk_cpudiv_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->CPUDIV.reg &= ~MCLK_CPUDIV_CPUDIV(mask);
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_CPUDIV_CPUDIV_bf(const void *const hw, hri_mclk_cpudiv_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->CPUDIV.reg ^= MCLK_CPUDIV_CPUDIV(mask);
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_cpudiv_reg_t hri_mclk_read_CPUDIV_CPUDIV_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Mclk *)hw)->CPUDIV.reg;
	tmp = (tmp & MCLK_CPUDIV_CPUDIV_Msk) >> MCLK_CPUDIV_CPUDIV_Pos;
	return tmp;
}

static inline void hri_mclk_set_CPUDIV_reg(const void *const hw, hri_mclk_cpudiv_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->CPUDIV.reg |= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_cpudiv_reg_t hri_mclk_get_CPUDIV_reg(const void *const hw, hri_mclk_cpudiv_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Mclk *)hw)->CPUDIV.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mclk_write_CPUDIV_reg(const void *const hw, hri_mclk_cpudiv_reg_t data)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->CPUDIV.reg = data;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_CPUDIV_reg(const void *const hw, hri_mclk_cpudiv_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->CPUDIV.reg &= ~mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_CPUDIV_reg(const void *const hw, hri_mclk_cpudiv_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->CPUDIV.reg ^= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_cpudiv_reg_t hri_mclk_read_CPUDIV_reg(const void *const hw)
{
	return ((Mclk *)hw)->CPUDIV.reg;
}

static inline void hri_mclk_set_AHBMASK_HPB0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_HPB0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_HPB0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_HPB0) >> MCLK_AHBMASK_HPB0_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_HPB0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_HPB0;
	tmp |= value << MCLK_AHBMASK_HPB0_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_HPB0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_HPB0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_HPB0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_HPB0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_HPB1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_HPB1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_HPB1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_HPB1) >> MCLK_AHBMASK_HPB1_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_HPB1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_HPB1;
	tmp |= value << MCLK_AHBMASK_HPB1_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_HPB1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_HPB1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_HPB1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_HPB1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_HPB2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_HPB2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_HPB2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_HPB2) >> MCLK_AHBMASK_HPB2_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_HPB2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_HPB2;
	tmp |= value << MCLK_AHBMASK_HPB2_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_HPB2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_HPB2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_HPB2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_HPB2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_DSU_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_DSU;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_DSU_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_DSU) >> MCLK_AHBMASK_DSU_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_DSU_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_DSU;
	tmp |= value << MCLK_AHBMASK_DSU_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_DSU_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_DSU;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_DSU_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_DSU;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_HMATRIXHS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_HMATRIXHS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_HMATRIXHS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_HMATRIXHS) >> MCLK_AHBMASK_HMATRIXHS_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_HMATRIXHS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_HMATRIXHS;
	tmp |= value << MCLK_AHBMASK_HMATRIXHS_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_HMATRIXHS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_HMATRIXHS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_HMATRIXHS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_HMATRIXHS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_NVMCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_NVMCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_NVMCTRL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_NVMCTRL) >> MCLK_AHBMASK_NVMCTRL_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_NVMCTRL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_NVMCTRL;
	tmp |= value << MCLK_AHBMASK_NVMCTRL_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_NVMCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_NVMCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_NVMCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_NVMCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_HSRAM_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_HSRAM;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_HSRAM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_HSRAM) >> MCLK_AHBMASK_HSRAM_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_HSRAM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_HSRAM;
	tmp |= value << MCLK_AHBMASK_HSRAM_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_HSRAM_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_HSRAM;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_HSRAM_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_HSRAM;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_DMAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_DMAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_DMAC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_DMAC) >> MCLK_AHBMASK_DMAC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_DMAC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_DMAC;
	tmp |= value << MCLK_AHBMASK_DMAC_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_DMAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_DMAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_DMAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_DMAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_CAN0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_CAN0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_CAN0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_CAN0) >> MCLK_AHBMASK_CAN0_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_CAN0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_CAN0;
	tmp |= value << MCLK_AHBMASK_CAN0_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_CAN0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_CAN0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_CAN0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_CAN0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_CAN1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_CAN1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_CAN1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_CAN1) >> MCLK_AHBMASK_CAN1_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_CAN1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_CAN1;
	tmp |= value << MCLK_AHBMASK_CAN1_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_CAN1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_CAN1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_CAN1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_CAN1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_PAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_PAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_PAC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_PAC) >> MCLK_AHBMASK_PAC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_PAC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_PAC;
	tmp |= value << MCLK_AHBMASK_PAC_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_PAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_PAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_PAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_PAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_NVMCTRL_PICACHU_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_NVMCTRL_PICACHU;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_NVMCTRL_PICACHU_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_NVMCTRL_PICACHU) >> MCLK_AHBMASK_NVMCTRL_PICACHU_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_NVMCTRL_PICACHU_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_NVMCTRL_PICACHU;
	tmp |= value << MCLK_AHBMASK_NVMCTRL_PICACHU_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_NVMCTRL_PICACHU_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_NVMCTRL_PICACHU;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_NVMCTRL_PICACHU_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_NVMCTRL_PICACHU;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_DIVAS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= MCLK_AHBMASK_DIVAS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_AHBMASK_DIVAS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp = (tmp & MCLK_AHBMASK_DIVAS) >> MCLK_AHBMASK_DIVAS_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_AHBMASK_DIVAS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= ~MCLK_AHBMASK_DIVAS;
	tmp |= value << MCLK_AHBMASK_DIVAS_Pos;
	((Mclk *)hw)->AHBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_DIVAS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~MCLK_AHBMASK_DIVAS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_DIVAS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= MCLK_AHBMASK_DIVAS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_AHBMASK_reg(const void *const hw, hri_mclk_ahbmask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg |= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_ahbmask_reg_t hri_mclk_get_AHBMASK_reg(const void *const hw, hri_mclk_ahbmask_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->AHBMASK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mclk_write_AHBMASK_reg(const void *const hw, hri_mclk_ahbmask_reg_t data)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg = data;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_AHBMASK_reg(const void *const hw, hri_mclk_ahbmask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg &= ~mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_AHBMASK_reg(const void *const hw, hri_mclk_ahbmask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->AHBMASK.reg ^= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_ahbmask_reg_t hri_mclk_read_AHBMASK_reg(const void *const hw)
{
	return ((Mclk *)hw)->AHBMASK.reg;
}

static inline void hri_mclk_set_APBAMASK_PAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_PAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_PAC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_PAC) >> MCLK_APBAMASK_PAC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_PAC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_PAC;
	tmp |= value << MCLK_APBAMASK_PAC_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_PAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_PAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_PAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_PAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_PM_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_PM;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_PM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_PM) >> MCLK_APBAMASK_PM_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_PM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_PM;
	tmp |= value << MCLK_APBAMASK_PM_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_PM_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_PM;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_PM_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_PM;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_MCLK_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_MCLK;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_MCLK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_MCLK) >> MCLK_APBAMASK_MCLK_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_MCLK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_MCLK;
	tmp |= value << MCLK_APBAMASK_MCLK_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_MCLK_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_MCLK;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_MCLK_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_MCLK;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_RSTC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_RSTC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_RSTC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_RSTC) >> MCLK_APBAMASK_RSTC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_RSTC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_RSTC;
	tmp |= value << MCLK_APBAMASK_RSTC_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_RSTC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_RSTC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_RSTC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_RSTC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_OSCCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_OSCCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_OSCCTRL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_OSCCTRL) >> MCLK_APBAMASK_OSCCTRL_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_OSCCTRL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_OSCCTRL;
	tmp |= value << MCLK_APBAMASK_OSCCTRL_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_OSCCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_OSCCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_OSCCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_OSCCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_OSC32KCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_OSC32KCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_OSC32KCTRL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_OSC32KCTRL) >> MCLK_APBAMASK_OSC32KCTRL_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_OSC32KCTRL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_OSC32KCTRL;
	tmp |= value << MCLK_APBAMASK_OSC32KCTRL_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_OSC32KCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_OSC32KCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_OSC32KCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_OSC32KCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_SUPC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_SUPC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_SUPC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_SUPC) >> MCLK_APBAMASK_SUPC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_SUPC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_SUPC;
	tmp |= value << MCLK_APBAMASK_SUPC_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_SUPC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_SUPC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_SUPC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_SUPC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_GCLK_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_GCLK;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_GCLK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_GCLK) >> MCLK_APBAMASK_GCLK_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_GCLK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_GCLK;
	tmp |= value << MCLK_APBAMASK_GCLK_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_GCLK_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_GCLK;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_GCLK_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_GCLK;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_WDT_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_WDT;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_WDT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_WDT) >> MCLK_APBAMASK_WDT_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_WDT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_WDT;
	tmp |= value << MCLK_APBAMASK_WDT_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_WDT_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_WDT;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_WDT_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_WDT;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_RTC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_RTC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_RTC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_RTC) >> MCLK_APBAMASK_RTC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_RTC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_RTC;
	tmp |= value << MCLK_APBAMASK_RTC_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_RTC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_RTC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_RTC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_RTC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_EIC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_EIC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_EIC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_EIC) >> MCLK_APBAMASK_EIC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_EIC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_EIC;
	tmp |= value << MCLK_APBAMASK_EIC_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_EIC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_EIC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_EIC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_EIC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_FREQM_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_FREQM;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_FREQM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_FREQM) >> MCLK_APBAMASK_FREQM_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_FREQM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_FREQM;
	tmp |= value << MCLK_APBAMASK_FREQM_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_FREQM_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_FREQM;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_FREQM_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_FREQM;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_TSENS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= MCLK_APBAMASK_TSENS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBAMASK_TSENS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp = (tmp & MCLK_APBAMASK_TSENS) >> MCLK_APBAMASK_TSENS_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBAMASK_TSENS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= ~MCLK_APBAMASK_TSENS;
	tmp |= value << MCLK_APBAMASK_TSENS_Pos;
	((Mclk *)hw)->APBAMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_TSENS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~MCLK_APBAMASK_TSENS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_TSENS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= MCLK_APBAMASK_TSENS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBAMASK_reg(const void *const hw, hri_mclk_apbamask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg |= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_apbamask_reg_t hri_mclk_get_APBAMASK_reg(const void *const hw, hri_mclk_apbamask_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBAMASK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mclk_write_APBAMASK_reg(const void *const hw, hri_mclk_apbamask_reg_t data)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg = data;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBAMASK_reg(const void *const hw, hri_mclk_apbamask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg &= ~mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBAMASK_reg(const void *const hw, hri_mclk_apbamask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBAMASK.reg ^= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_apbamask_reg_t hri_mclk_read_APBAMASK_reg(const void *const hw)
{
	return ((Mclk *)hw)->APBAMASK.reg;
}

static inline void hri_mclk_set_APBBMASK_PORT_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg |= MCLK_APBBMASK_PORT;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBBMASK_PORT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBBMASK.reg;
	tmp = (tmp & MCLK_APBBMASK_PORT) >> MCLK_APBBMASK_PORT_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBBMASK_PORT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBBMASK.reg;
	tmp &= ~MCLK_APBBMASK_PORT;
	tmp |= value << MCLK_APBBMASK_PORT_Pos;
	((Mclk *)hw)->APBBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBBMASK_PORT_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg &= ~MCLK_APBBMASK_PORT;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBBMASK_PORT_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg ^= MCLK_APBBMASK_PORT;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBBMASK_DSU_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg |= MCLK_APBBMASK_DSU;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBBMASK_DSU_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBBMASK.reg;
	tmp = (tmp & MCLK_APBBMASK_DSU) >> MCLK_APBBMASK_DSU_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBBMASK_DSU_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBBMASK.reg;
	tmp &= ~MCLK_APBBMASK_DSU;
	tmp |= value << MCLK_APBBMASK_DSU_Pos;
	((Mclk *)hw)->APBBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBBMASK_DSU_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg &= ~MCLK_APBBMASK_DSU;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBBMASK_DSU_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg ^= MCLK_APBBMASK_DSU;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBBMASK_NVMCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg |= MCLK_APBBMASK_NVMCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBBMASK_NVMCTRL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBBMASK.reg;
	tmp = (tmp & MCLK_APBBMASK_NVMCTRL) >> MCLK_APBBMASK_NVMCTRL_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBBMASK_NVMCTRL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBBMASK.reg;
	tmp &= ~MCLK_APBBMASK_NVMCTRL;
	tmp |= value << MCLK_APBBMASK_NVMCTRL_Pos;
	((Mclk *)hw)->APBBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBBMASK_NVMCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg &= ~MCLK_APBBMASK_NVMCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBBMASK_NVMCTRL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg ^= MCLK_APBBMASK_NVMCTRL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBBMASK_HMATRIXHS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg |= MCLK_APBBMASK_HMATRIXHS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBBMASK_HMATRIXHS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBBMASK.reg;
	tmp = (tmp & MCLK_APBBMASK_HMATRIXHS) >> MCLK_APBBMASK_HMATRIXHS_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBBMASK_HMATRIXHS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBBMASK.reg;
	tmp &= ~MCLK_APBBMASK_HMATRIXHS;
	tmp |= value << MCLK_APBBMASK_HMATRIXHS_Pos;
	((Mclk *)hw)->APBBMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBBMASK_HMATRIXHS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg &= ~MCLK_APBBMASK_HMATRIXHS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBBMASK_HMATRIXHS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg ^= MCLK_APBBMASK_HMATRIXHS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBBMASK_reg(const void *const hw, hri_mclk_apbbmask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg |= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_apbbmask_reg_t hri_mclk_get_APBBMASK_reg(const void *const hw, hri_mclk_apbbmask_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBBMASK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mclk_write_APBBMASK_reg(const void *const hw, hri_mclk_apbbmask_reg_t data)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg = data;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBBMASK_reg(const void *const hw, hri_mclk_apbbmask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg &= ~mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBBMASK_reg(const void *const hw, hri_mclk_apbbmask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBBMASK.reg ^= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_apbbmask_reg_t hri_mclk_read_APBBMASK_reg(const void *const hw)
{
	return ((Mclk *)hw)->APBBMASK.reg;
}

static inline void hri_mclk_set_APBCMASK_EVSYS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_EVSYS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_EVSYS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_EVSYS) >> MCLK_APBCMASK_EVSYS_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_EVSYS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_EVSYS;
	tmp |= value << MCLK_APBCMASK_EVSYS_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_EVSYS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_EVSYS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_EVSYS_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_EVSYS;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_SERCOM0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_SERCOM0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_SERCOM0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_SERCOM0) >> MCLK_APBCMASK_SERCOM0_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_SERCOM0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_SERCOM0;
	tmp |= value << MCLK_APBCMASK_SERCOM0_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_SERCOM0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_SERCOM0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_SERCOM0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_SERCOM0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_SERCOM1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_SERCOM1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_SERCOM1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_SERCOM1) >> MCLK_APBCMASK_SERCOM1_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_SERCOM1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_SERCOM1;
	tmp |= value << MCLK_APBCMASK_SERCOM1_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_SERCOM1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_SERCOM1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_SERCOM1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_SERCOM1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_SERCOM2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_SERCOM2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_SERCOM2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_SERCOM2) >> MCLK_APBCMASK_SERCOM2_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_SERCOM2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_SERCOM2;
	tmp |= value << MCLK_APBCMASK_SERCOM2_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_SERCOM2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_SERCOM2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_SERCOM2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_SERCOM2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_SERCOM3_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_SERCOM3;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_SERCOM3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_SERCOM3) >> MCLK_APBCMASK_SERCOM3_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_SERCOM3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_SERCOM3;
	tmp |= value << MCLK_APBCMASK_SERCOM3_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_SERCOM3_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_SERCOM3;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_SERCOM3_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_SERCOM3;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_SERCOM4_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_SERCOM4;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_SERCOM4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_SERCOM4) >> MCLK_APBCMASK_SERCOM4_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_SERCOM4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_SERCOM4;
	tmp |= value << MCLK_APBCMASK_SERCOM4_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_SERCOM4_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_SERCOM4;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_SERCOM4_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_SERCOM4;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_SERCOM5_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_SERCOM5;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_SERCOM5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_SERCOM5) >> MCLK_APBCMASK_SERCOM5_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_SERCOM5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_SERCOM5;
	tmp |= value << MCLK_APBCMASK_SERCOM5_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_SERCOM5_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_SERCOM5;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_SERCOM5_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_SERCOM5;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_TCC0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_TCC0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_TCC0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_TCC0) >> MCLK_APBCMASK_TCC0_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_TCC0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_TCC0;
	tmp |= value << MCLK_APBCMASK_TCC0_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_TCC0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_TCC0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_TCC0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_TCC0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_TCC1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_TCC1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_TCC1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_TCC1) >> MCLK_APBCMASK_TCC1_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_TCC1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_TCC1;
	tmp |= value << MCLK_APBCMASK_TCC1_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_TCC1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_TCC1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_TCC1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_TCC1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_TCC2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_TCC2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_TCC2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_TCC2) >> MCLK_APBCMASK_TCC2_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_TCC2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_TCC2;
	tmp |= value << MCLK_APBCMASK_TCC2_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_TCC2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_TCC2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_TCC2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_TCC2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_TC0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_TC0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_TC0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_TC0) >> MCLK_APBCMASK_TC0_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_TC0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_TC0;
	tmp |= value << MCLK_APBCMASK_TC0_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_TC0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_TC0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_TC0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_TC0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_TC1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_TC1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_TC1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_TC1) >> MCLK_APBCMASK_TC1_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_TC1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_TC1;
	tmp |= value << MCLK_APBCMASK_TC1_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_TC1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_TC1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_TC1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_TC1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_TC2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_TC2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_TC2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_TC2) >> MCLK_APBCMASK_TC2_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_TC2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_TC2;
	tmp |= value << MCLK_APBCMASK_TC2_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_TC2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_TC2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_TC2_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_TC2;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_TC3_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_TC3;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_TC3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_TC3) >> MCLK_APBCMASK_TC3_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_TC3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_TC3;
	tmp |= value << MCLK_APBCMASK_TC3_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_TC3_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_TC3;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_TC3_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_TC3;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_TC4_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_TC4;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_TC4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_TC4) >> MCLK_APBCMASK_TC4_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_TC4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_TC4;
	tmp |= value << MCLK_APBCMASK_TC4_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_TC4_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_TC4;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_TC4_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_TC4;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_ADC0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_ADC0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_ADC0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_ADC0) >> MCLK_APBCMASK_ADC0_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_ADC0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_ADC0;
	tmp |= value << MCLK_APBCMASK_ADC0_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_ADC0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_ADC0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_ADC0_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_ADC0;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_ADC1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_ADC1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_ADC1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_ADC1) >> MCLK_APBCMASK_ADC1_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_ADC1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_ADC1;
	tmp |= value << MCLK_APBCMASK_ADC1_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_ADC1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_ADC1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_ADC1_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_ADC1;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_SDADC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_SDADC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_SDADC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_SDADC) >> MCLK_APBCMASK_SDADC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_SDADC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_SDADC;
	tmp |= value << MCLK_APBCMASK_SDADC_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_SDADC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_SDADC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_SDADC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_SDADC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_AC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_AC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_AC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_AC) >> MCLK_APBCMASK_AC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_AC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_AC;
	tmp |= value << MCLK_APBCMASK_AC_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_AC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_AC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_AC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_AC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_DAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_DAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_DAC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_DAC) >> MCLK_APBCMASK_DAC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_DAC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_DAC;
	tmp |= value << MCLK_APBCMASK_DAC_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_DAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_DAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_DAC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_DAC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_PTC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_PTC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_PTC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_PTC) >> MCLK_APBCMASK_PTC_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_PTC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_PTC;
	tmp |= value << MCLK_APBCMASK_PTC_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_PTC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_PTC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_PTC_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_PTC;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_CCL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= MCLK_APBCMASK_CCL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mclk_get_APBCMASK_CCL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp = (tmp & MCLK_APBCMASK_CCL) >> MCLK_APBCMASK_CCL_Pos;
	return (bool)tmp;
}

static inline void hri_mclk_write_APBCMASK_CCL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCLK_CRITICAL_SECTION_ENTER();
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= ~MCLK_APBCMASK_CCL;
	tmp |= value << MCLK_APBCMASK_CCL_Pos;
	((Mclk *)hw)->APBCMASK.reg = tmp;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_CCL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~MCLK_APBCMASK_CCL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_CCL_bit(const void *const hw)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= MCLK_APBCMASK_CCL;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_set_APBCMASK_reg(const void *const hw, hri_mclk_apbcmask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg |= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_apbcmask_reg_t hri_mclk_get_APBCMASK_reg(const void *const hw, hri_mclk_apbcmask_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mclk *)hw)->APBCMASK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mclk_write_APBCMASK_reg(const void *const hw, hri_mclk_apbcmask_reg_t data)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg = data;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_clear_APBCMASK_reg(const void *const hw, hri_mclk_apbcmask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg &= ~mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mclk_toggle_APBCMASK_reg(const void *const hw, hri_mclk_apbcmask_reg_t mask)
{
	MCLK_CRITICAL_SECTION_ENTER();
	((Mclk *)hw)->APBCMASK.reg ^= mask;
	MCLK_CRITICAL_SECTION_LEAVE();
}

static inline hri_mclk_apbcmask_reg_t hri_mclk_read_APBCMASK_reg(const void *const hw)
{
	return ((Mclk *)hw)->APBCMASK.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_MCLK_C21_H_INCLUDED */
#endif /* _SAMC21_MCLK_COMPONENT_ */
