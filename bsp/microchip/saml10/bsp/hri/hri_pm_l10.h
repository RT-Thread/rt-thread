/**
 * \file
 *
 * \brief SAM PM
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

#ifdef _SAML10_PM_COMPONENT_
#ifndef _HRI_PM_L10_H_INCLUDED_
#define _HRI_PM_L10_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_PM_CRITICAL_SECTIONS)
#define PM_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define PM_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define PM_CRITICAL_SECTION_ENTER()
#define PM_CRITICAL_SECTION_LEAVE()
#endif

typedef uint16_t hri_pm_stdbycfg_reg_t;
typedef uint8_t  hri_pm_intenset_reg_t;
typedef uint8_t  hri_pm_intflag_reg_t;
typedef uint8_t  hri_pm_plcfg_reg_t;
typedef uint8_t  hri_pm_pwcfg_reg_t;
typedef uint8_t  hri_pm_sleepcfg_reg_t;

static inline bool hri_pm_get_INTFLAG_PLRDY_bit(const void *const hw)
{
	return (((Pm *)hw)->INTFLAG.reg & PM_INTFLAG_PLRDY_Msk) >> PM_INTFLAG_PLRDY_Pos;
}

static inline void hri_pm_clear_INTFLAG_PLRDY_bit(const void *const hw)
{
	((Pm *)hw)->INTFLAG.reg = PM_INTFLAG_PLRDY_Msk;
}

static inline bool hri_pm_get_interrupt_PLRDY_bit(const void *const hw)
{
	return (((Pm *)hw)->INTFLAG.reg & PM_INTFLAG_PLRDY_Msk) >> PM_INTFLAG_PLRDY_Pos;
}

static inline void hri_pm_clear_interrupt_PLRDY_bit(const void *const hw)
{
	((Pm *)hw)->INTFLAG.reg = PM_INTFLAG_PLRDY_Msk;
}

static inline hri_pm_intflag_reg_t hri_pm_get_INTFLAG_reg(const void *const hw, hri_pm_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pm_intflag_reg_t hri_pm_read_INTFLAG_reg(const void *const hw)
{
	return ((Pm *)hw)->INTFLAG.reg;
}

static inline void hri_pm_clear_INTFLAG_reg(const void *const hw, hri_pm_intflag_reg_t mask)
{
	((Pm *)hw)->INTFLAG.reg = mask;
}

static inline void hri_pm_set_INTEN_PLRDY_bit(const void *const hw)
{
	((Pm *)hw)->INTENSET.reg = PM_INTENSET_PLRDY_Msk;
}

static inline bool hri_pm_get_INTEN_PLRDY_bit(const void *const hw)
{
	return (((Pm *)hw)->INTENSET.reg & PM_INTENSET_PLRDY_Msk) >> PM_INTENSET_PLRDY_Pos;
}

static inline void hri_pm_write_INTEN_PLRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pm *)hw)->INTENCLR.reg = PM_INTENSET_PLRDY_Msk;
	} else {
		((Pm *)hw)->INTENSET.reg = PM_INTENSET_PLRDY_Msk;
	}
}

static inline void hri_pm_clear_INTEN_PLRDY_bit(const void *const hw)
{
	((Pm *)hw)->INTENCLR.reg = PM_INTENSET_PLRDY_Msk;
}

static inline void hri_pm_set_INTEN_reg(const void *const hw, hri_pm_intenset_reg_t mask)
{
	((Pm *)hw)->INTENSET.reg = mask;
}

static inline hri_pm_intenset_reg_t hri_pm_get_INTEN_reg(const void *const hw, hri_pm_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pm_intenset_reg_t hri_pm_read_INTEN_reg(const void *const hw)
{
	return ((Pm *)hw)->INTENSET.reg;
}

static inline void hri_pm_write_INTEN_reg(const void *const hw, hri_pm_intenset_reg_t data)
{
	((Pm *)hw)->INTENSET.reg = data;
	((Pm *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_pm_clear_INTEN_reg(const void *const hw, hri_pm_intenset_reg_t mask)
{
	((Pm *)hw)->INTENCLR.reg = mask;
}

static inline void hri_pm_set_SLEEPCFG_SLEEPMODE_bf(const void *const hw, hri_pm_sleepcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->SLEEPCFG.reg |= PM_SLEEPCFG_SLEEPMODE(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_sleepcfg_reg_t hri_pm_get_SLEEPCFG_SLEEPMODE_bf(const void *const hw, hri_pm_sleepcfg_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->SLEEPCFG.reg;
	tmp = (tmp & PM_SLEEPCFG_SLEEPMODE(mask)) >> PM_SLEEPCFG_SLEEPMODE_Pos;
	return tmp;
}

static inline void hri_pm_write_SLEEPCFG_SLEEPMODE_bf(const void *const hw, hri_pm_sleepcfg_reg_t data)
{
	uint8_t tmp;
	PM_CRITICAL_SECTION_ENTER();
	tmp = ((Pm *)hw)->SLEEPCFG.reg;
	tmp &= ~PM_SLEEPCFG_SLEEPMODE_Msk;
	tmp |= PM_SLEEPCFG_SLEEPMODE(data);
	((Pm *)hw)->SLEEPCFG.reg = tmp;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_SLEEPCFG_SLEEPMODE_bf(const void *const hw, hri_pm_sleepcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->SLEEPCFG.reg &= ~PM_SLEEPCFG_SLEEPMODE(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_SLEEPCFG_SLEEPMODE_bf(const void *const hw, hri_pm_sleepcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->SLEEPCFG.reg ^= PM_SLEEPCFG_SLEEPMODE(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_sleepcfg_reg_t hri_pm_read_SLEEPCFG_SLEEPMODE_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->SLEEPCFG.reg;
	tmp = (tmp & PM_SLEEPCFG_SLEEPMODE_Msk) >> PM_SLEEPCFG_SLEEPMODE_Pos;
	return tmp;
}

static inline void hri_pm_set_SLEEPCFG_reg(const void *const hw, hri_pm_sleepcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->SLEEPCFG.reg |= mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_sleepcfg_reg_t hri_pm_get_SLEEPCFG_reg(const void *const hw, hri_pm_sleepcfg_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->SLEEPCFG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_pm_write_SLEEPCFG_reg(const void *const hw, hri_pm_sleepcfg_reg_t data)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->SLEEPCFG.reg = data;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_SLEEPCFG_reg(const void *const hw, hri_pm_sleepcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->SLEEPCFG.reg &= ~mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_SLEEPCFG_reg(const void *const hw, hri_pm_sleepcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->SLEEPCFG.reg ^= mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_sleepcfg_reg_t hri_pm_read_SLEEPCFG_reg(const void *const hw)
{
	return ((Pm *)hw)->SLEEPCFG.reg;
}

static inline void hri_pm_set_PLCFG_PLDIS_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg |= PM_PLCFG_PLDIS_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pm_get_PLCFG_PLDIS_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->PLCFG.reg;
	tmp = (tmp & PM_PLCFG_PLDIS_Msk) >> PM_PLCFG_PLDIS_Pos;
	return (bool)tmp;
}

static inline void hri_pm_write_PLCFG_PLDIS_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	PM_CRITICAL_SECTION_ENTER();
	tmp = ((Pm *)hw)->PLCFG.reg;
	tmp &= ~PM_PLCFG_PLDIS_Msk;
	tmp |= value << PM_PLCFG_PLDIS_Pos;
	((Pm *)hw)->PLCFG.reg = tmp;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_PLCFG_PLDIS_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg &= ~PM_PLCFG_PLDIS_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_PLCFG_PLDIS_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg ^= PM_PLCFG_PLDIS_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_set_PLCFG_PLSEL_bf(const void *const hw, hri_pm_plcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg |= PM_PLCFG_PLSEL(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_plcfg_reg_t hri_pm_get_PLCFG_PLSEL_bf(const void *const hw, hri_pm_plcfg_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->PLCFG.reg;
	tmp = (tmp & PM_PLCFG_PLSEL(mask)) >> PM_PLCFG_PLSEL_Pos;
	return tmp;
}

static inline void hri_pm_write_PLCFG_PLSEL_bf(const void *const hw, hri_pm_plcfg_reg_t data)
{
	uint8_t tmp;
	PM_CRITICAL_SECTION_ENTER();
	tmp = ((Pm *)hw)->PLCFG.reg;
	tmp &= ~PM_PLCFG_PLSEL_Msk;
	tmp |= PM_PLCFG_PLSEL(data);
	((Pm *)hw)->PLCFG.reg = tmp;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_PLCFG_PLSEL_bf(const void *const hw, hri_pm_plcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg &= ~PM_PLCFG_PLSEL(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_PLCFG_PLSEL_bf(const void *const hw, hri_pm_plcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg ^= PM_PLCFG_PLSEL(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_plcfg_reg_t hri_pm_read_PLCFG_PLSEL_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->PLCFG.reg;
	tmp = (tmp & PM_PLCFG_PLSEL_Msk) >> PM_PLCFG_PLSEL_Pos;
	return tmp;
}

static inline void hri_pm_set_PLCFG_reg(const void *const hw, hri_pm_plcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg |= mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_plcfg_reg_t hri_pm_get_PLCFG_reg(const void *const hw, hri_pm_plcfg_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->PLCFG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_pm_write_PLCFG_reg(const void *const hw, hri_pm_plcfg_reg_t data)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg = data;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_PLCFG_reg(const void *const hw, hri_pm_plcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg &= ~mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_PLCFG_reg(const void *const hw, hri_pm_plcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PLCFG.reg ^= mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_plcfg_reg_t hri_pm_read_PLCFG_reg(const void *const hw)
{
	return ((Pm *)hw)->PLCFG.reg;
}

static inline void hri_pm_set_PWCFG_RAMPSWC_bf(const void *const hw, hri_pm_pwcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PWCFG.reg |= PM_PWCFG_RAMPSWC(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_pwcfg_reg_t hri_pm_get_PWCFG_RAMPSWC_bf(const void *const hw, hri_pm_pwcfg_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->PWCFG.reg;
	tmp = (tmp & PM_PWCFG_RAMPSWC(mask)) >> PM_PWCFG_RAMPSWC_Pos;
	return tmp;
}

static inline void hri_pm_write_PWCFG_RAMPSWC_bf(const void *const hw, hri_pm_pwcfg_reg_t data)
{
	uint8_t tmp;
	PM_CRITICAL_SECTION_ENTER();
	tmp = ((Pm *)hw)->PWCFG.reg;
	tmp &= ~PM_PWCFG_RAMPSWC_Msk;
	tmp |= PM_PWCFG_RAMPSWC(data);
	((Pm *)hw)->PWCFG.reg = tmp;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_PWCFG_RAMPSWC_bf(const void *const hw, hri_pm_pwcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PWCFG.reg &= ~PM_PWCFG_RAMPSWC(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_PWCFG_RAMPSWC_bf(const void *const hw, hri_pm_pwcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PWCFG.reg ^= PM_PWCFG_RAMPSWC(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_pwcfg_reg_t hri_pm_read_PWCFG_RAMPSWC_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->PWCFG.reg;
	tmp = (tmp & PM_PWCFG_RAMPSWC_Msk) >> PM_PWCFG_RAMPSWC_Pos;
	return tmp;
}

static inline void hri_pm_set_PWCFG_reg(const void *const hw, hri_pm_pwcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PWCFG.reg |= mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_pwcfg_reg_t hri_pm_get_PWCFG_reg(const void *const hw, hri_pm_pwcfg_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pm *)hw)->PWCFG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_pm_write_PWCFG_reg(const void *const hw, hri_pm_pwcfg_reg_t data)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PWCFG.reg = data;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_PWCFG_reg(const void *const hw, hri_pm_pwcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PWCFG.reg &= ~mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_PWCFG_reg(const void *const hw, hri_pm_pwcfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->PWCFG.reg ^= mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_pwcfg_reg_t hri_pm_read_PWCFG_reg(const void *const hw)
{
	return ((Pm *)hw)->PWCFG.reg;
}

static inline void hri_pm_set_STDBYCFG_PDCFG_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg |= PM_STDBYCFG_PDCFG_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pm_get_STDBYCFG_PDCFG_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp = (tmp & PM_STDBYCFG_PDCFG_Msk) >> PM_STDBYCFG_PDCFG_Pos;
	return (bool)tmp;
}

static inline void hri_pm_write_STDBYCFG_PDCFG_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	PM_CRITICAL_SECTION_ENTER();
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp &= ~PM_STDBYCFG_PDCFG_Msk;
	tmp |= value << PM_STDBYCFG_PDCFG_Pos;
	((Pm *)hw)->STDBYCFG.reg = tmp;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_STDBYCFG_PDCFG_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg &= ~PM_STDBYCFG_PDCFG_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_STDBYCFG_PDCFG_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg ^= PM_STDBYCFG_PDCFG_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_set_STDBYCFG_DPGPDSW_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg |= PM_STDBYCFG_DPGPDSW_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pm_get_STDBYCFG_DPGPDSW_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp = (tmp & PM_STDBYCFG_DPGPDSW_Msk) >> PM_STDBYCFG_DPGPDSW_Pos;
	return (bool)tmp;
}

static inline void hri_pm_write_STDBYCFG_DPGPDSW_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	PM_CRITICAL_SECTION_ENTER();
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp &= ~PM_STDBYCFG_DPGPDSW_Msk;
	tmp |= value << PM_STDBYCFG_DPGPDSW_Pos;
	((Pm *)hw)->STDBYCFG.reg = tmp;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_STDBYCFG_DPGPDSW_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg &= ~PM_STDBYCFG_DPGPDSW_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_STDBYCFG_DPGPDSW_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg ^= PM_STDBYCFG_DPGPDSW_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_set_STDBYCFG_BBIASHS_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg |= PM_STDBYCFG_BBIASHS_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pm_get_STDBYCFG_BBIASHS_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp = (tmp & PM_STDBYCFG_BBIASHS_Msk) >> PM_STDBYCFG_BBIASHS_Pos;
	return (bool)tmp;
}

static inline void hri_pm_write_STDBYCFG_BBIASHS_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	PM_CRITICAL_SECTION_ENTER();
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp &= ~PM_STDBYCFG_BBIASHS_Msk;
	tmp |= value << PM_STDBYCFG_BBIASHS_Pos;
	((Pm *)hw)->STDBYCFG.reg = tmp;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_STDBYCFG_BBIASHS_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg &= ~PM_STDBYCFG_BBIASHS_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_STDBYCFG_BBIASHS_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg ^= PM_STDBYCFG_BBIASHS_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_set_STDBYCFG_BBIASTR_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg |= PM_STDBYCFG_BBIASTR_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pm_get_STDBYCFG_BBIASTR_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp = (tmp & PM_STDBYCFG_BBIASTR_Msk) >> PM_STDBYCFG_BBIASTR_Pos;
	return (bool)tmp;
}

static inline void hri_pm_write_STDBYCFG_BBIASTR_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	PM_CRITICAL_SECTION_ENTER();
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp &= ~PM_STDBYCFG_BBIASTR_Msk;
	tmp |= value << PM_STDBYCFG_BBIASTR_Pos;
	((Pm *)hw)->STDBYCFG.reg = tmp;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_STDBYCFG_BBIASTR_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg &= ~PM_STDBYCFG_BBIASTR_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_STDBYCFG_BBIASTR_bit(const void *const hw)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg ^= PM_STDBYCFG_BBIASTR_Msk;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_set_STDBYCFG_VREGSMOD_bf(const void *const hw, hri_pm_stdbycfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg |= PM_STDBYCFG_VREGSMOD(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_stdbycfg_reg_t hri_pm_get_STDBYCFG_VREGSMOD_bf(const void *const hw, hri_pm_stdbycfg_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp = (tmp & PM_STDBYCFG_VREGSMOD(mask)) >> PM_STDBYCFG_VREGSMOD_Pos;
	return tmp;
}

static inline void hri_pm_write_STDBYCFG_VREGSMOD_bf(const void *const hw, hri_pm_stdbycfg_reg_t data)
{
	uint16_t tmp;
	PM_CRITICAL_SECTION_ENTER();
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp &= ~PM_STDBYCFG_VREGSMOD_Msk;
	tmp |= PM_STDBYCFG_VREGSMOD(data);
	((Pm *)hw)->STDBYCFG.reg = tmp;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_STDBYCFG_VREGSMOD_bf(const void *const hw, hri_pm_stdbycfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg &= ~PM_STDBYCFG_VREGSMOD(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_STDBYCFG_VREGSMOD_bf(const void *const hw, hri_pm_stdbycfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg ^= PM_STDBYCFG_VREGSMOD(mask);
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_stdbycfg_reg_t hri_pm_read_STDBYCFG_VREGSMOD_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp = (tmp & PM_STDBYCFG_VREGSMOD_Msk) >> PM_STDBYCFG_VREGSMOD_Pos;
	return tmp;
}

static inline void hri_pm_set_STDBYCFG_reg(const void *const hw, hri_pm_stdbycfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg |= mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_stdbycfg_reg_t hri_pm_get_STDBYCFG_reg(const void *const hw, hri_pm_stdbycfg_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Pm *)hw)->STDBYCFG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_pm_write_STDBYCFG_reg(const void *const hw, hri_pm_stdbycfg_reg_t data)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg = data;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_clear_STDBYCFG_reg(const void *const hw, hri_pm_stdbycfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg &= ~mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pm_toggle_STDBYCFG_reg(const void *const hw, hri_pm_stdbycfg_reg_t mask)
{
	PM_CRITICAL_SECTION_ENTER();
	((Pm *)hw)->STDBYCFG.reg ^= mask;
	PM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pm_stdbycfg_reg_t hri_pm_read_STDBYCFG_reg(const void *const hw)
{
	return ((Pm *)hw)->STDBYCFG.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_PM_L10_H_INCLUDED */
#endif /* _SAML10_PM_COMPONENT_ */
