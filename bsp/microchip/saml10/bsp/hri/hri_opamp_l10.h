/**
 * \file
 *
 * \brief SAM OPAMP
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

#ifdef _SAML10_OPAMP_COMPONENT_
#ifndef _HRI_OPAMP_L10_H_INCLUDED_
#define _HRI_OPAMP_L10_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_OPAMP_CRITICAL_SECTIONS)
#define OPAMP_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define OPAMP_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define OPAMP_CRITICAL_SECTION_ENTER()
#define OPAMP_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_opamp_opampctrl_reg_t;
typedef uint8_t  hri_opamp_ctrla_reg_t;
typedef uint8_t  hri_opamp_resctrl_reg_t;
typedef uint8_t  hri_opamp_status_reg_t;

static inline bool hri_opamp_get_STATUS_READY0_bit(const void *const hw)
{
	return (((Opamp *)hw)->STATUS.reg & OPAMP_STATUS_READY0_Msk) >> OPAMP_STATUS_READY0_Pos;
}

static inline bool hri_opamp_get_STATUS_READY1_bit(const void *const hw)
{
	return (((Opamp *)hw)->STATUS.reg & OPAMP_STATUS_READY1_Msk) >> OPAMP_STATUS_READY1_Pos;
}

static inline bool hri_opamp_get_STATUS_READY2_bit(const void *const hw)
{
	return (((Opamp *)hw)->STATUS.reg & OPAMP_STATUS_READY2_Msk) >> OPAMP_STATUS_READY2_Pos;
}

static inline hri_opamp_status_reg_t hri_opamp_get_STATUS_reg(const void *const hw, hri_opamp_status_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_opamp_status_reg_t hri_opamp_read_STATUS_reg(const void *const hw)
{
	return ((Opamp *)hw)->STATUS.reg;
}

static inline void hri_opamp_set_CTRLA_SWRST_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg |= OPAMP_CTRLA_SWRST_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->CTRLA.reg;
	tmp = (tmp & OPAMP_CTRLA_SWRST_Msk) >> OPAMP_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_set_CTRLA_ENABLE_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg |= OPAMP_CTRLA_ENABLE_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->CTRLA.reg;
	tmp = (tmp & OPAMP_CTRLA_ENABLE_Msk) >> OPAMP_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->CTRLA.reg;
	tmp &= ~OPAMP_CTRLA_ENABLE_Msk;
	tmp |= value << OPAMP_CTRLA_ENABLE_Pos;
	((Opamp *)hw)->CTRLA.reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg &= ~OPAMP_CTRLA_ENABLE_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg ^= OPAMP_CTRLA_ENABLE_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_CTRLA_LPMUX_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg |= OPAMP_CTRLA_LPMUX_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_CTRLA_LPMUX_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->CTRLA.reg;
	tmp = (tmp & OPAMP_CTRLA_LPMUX_Msk) >> OPAMP_CTRLA_LPMUX_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_CTRLA_LPMUX_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->CTRLA.reg;
	tmp &= ~OPAMP_CTRLA_LPMUX_Msk;
	tmp |= value << OPAMP_CTRLA_LPMUX_Pos;
	((Opamp *)hw)->CTRLA.reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_CTRLA_LPMUX_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg &= ~OPAMP_CTRLA_LPMUX_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_CTRLA_LPMUX_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg ^= OPAMP_CTRLA_LPMUX_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_CTRLA_reg(const void *const hw, hri_opamp_ctrla_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg |= mask;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_ctrla_reg_t hri_opamp_get_CTRLA_reg(const void *const hw, hri_opamp_ctrla_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_opamp_write_CTRLA_reg(const void *const hw, hri_opamp_ctrla_reg_t data)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg = data;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_CTRLA_reg(const void *const hw, hri_opamp_ctrla_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg &= ~mask;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_CTRLA_reg(const void *const hw, hri_opamp_ctrla_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->CTRLA.reg ^= mask;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_ctrla_reg_t hri_opamp_read_CTRLA_reg(const void *const hw)
{
	return ((Opamp *)hw)->CTRLA.reg;
}

static inline void hri_opamp_set_OPAMPCTRL_ENABLE_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_ENABLE_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_OPAMPCTRL_ENABLE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_ENABLE_Msk) >> OPAMP_OPAMPCTRL_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_ENABLE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_ENABLE_Msk;
	tmp |= value << OPAMP_OPAMPCTRL_ENABLE_Pos;
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_ENABLE_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_ENABLE_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_ENABLE_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_ENABLE_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_OPAMPCTRL_ANAOUT_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_ANAOUT_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_OPAMPCTRL_ANAOUT_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_ANAOUT_Msk) >> OPAMP_OPAMPCTRL_ANAOUT_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_ANAOUT_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_ANAOUT_Msk;
	tmp |= value << OPAMP_OPAMPCTRL_ANAOUT_Pos;
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_ANAOUT_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_ANAOUT_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_ANAOUT_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_ANAOUT_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_OPAMPCTRL_RES2VCC_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_RES2VCC_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_OPAMPCTRL_RES2VCC_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_RES2VCC_Msk) >> OPAMP_OPAMPCTRL_RES2VCC_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_RES2VCC_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_RES2VCC_Msk;
	tmp |= value << OPAMP_OPAMPCTRL_RES2VCC_Pos;
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_RES2VCC_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_RES2VCC_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_RES2VCC_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_RES2VCC_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_OPAMPCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_RUNSTDBY_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_OPAMPCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_RUNSTDBY_Msk) >> OPAMP_OPAMPCTRL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_RUNSTDBY_Msk;
	tmp |= value << OPAMP_OPAMPCTRL_RUNSTDBY_Pos;
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_RUNSTDBY_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_RUNSTDBY_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_RUNSTDBY_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_OPAMPCTRL_ONDEMAND_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_ONDEMAND_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_OPAMPCTRL_ONDEMAND_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_ONDEMAND_Msk) >> OPAMP_OPAMPCTRL_ONDEMAND_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_ONDEMAND_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_ONDEMAND_Msk;
	tmp |= value << OPAMP_OPAMPCTRL_ONDEMAND_Pos;
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_ONDEMAND_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_ONDEMAND_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_ONDEMAND_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_ONDEMAND_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_OPAMPCTRL_RES2OUT_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_RES2OUT_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_OPAMPCTRL_RES2OUT_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_RES2OUT_Msk) >> OPAMP_OPAMPCTRL_RES2OUT_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_RES2OUT_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_RES2OUT_Msk;
	tmp |= value << OPAMP_OPAMPCTRL_RES2OUT_Pos;
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_RES2OUT_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_RES2OUT_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_RES2OUT_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_RES2OUT_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_OPAMPCTRL_RES1EN_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_RES1EN_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_OPAMPCTRL_RES1EN_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_RES1EN_Msk) >> OPAMP_OPAMPCTRL_RES1EN_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_RES1EN_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_RES1EN_Msk;
	tmp |= value << OPAMP_OPAMPCTRL_RES1EN_Pos;
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_RES1EN_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_RES1EN_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_RES1EN_bit(const void *const hw, uint8_t index)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_RES1EN_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_OPAMPCTRL_BIAS_bf(const void *const hw, uint8_t index, hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_BIAS(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_get_OPAMPCTRL_BIAS_bf(const void *const hw, uint8_t index,
                                                                        hri_opamp_opampctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_BIAS(mask)) >> OPAMP_OPAMPCTRL_BIAS_Pos;
	return tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_BIAS_bf(const void *const hw, uint8_t index,
                                                     hri_opamp_opampctrl_reg_t data)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_BIAS_Msk;
	tmp |= OPAMP_OPAMPCTRL_BIAS(data);
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_BIAS_bf(const void *const hw, uint8_t index,
                                                     hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_BIAS(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_BIAS_bf(const void *const hw, uint8_t index,
                                                      hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_BIAS(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_read_OPAMPCTRL_BIAS_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_BIAS_Msk) >> OPAMP_OPAMPCTRL_BIAS_Pos;
	return tmp;
}

static inline void hri_opamp_set_OPAMPCTRL_RES1MUX_bf(const void *const hw, uint8_t index,
                                                      hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_RES1MUX(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_get_OPAMPCTRL_RES1MUX_bf(const void *const hw, uint8_t index,
                                                                           hri_opamp_opampctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_RES1MUX(mask)) >> OPAMP_OPAMPCTRL_RES1MUX_Pos;
	return tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_RES1MUX_bf(const void *const hw, uint8_t index,
                                                        hri_opamp_opampctrl_reg_t data)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_RES1MUX_Msk;
	tmp |= OPAMP_OPAMPCTRL_RES1MUX(data);
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_RES1MUX_bf(const void *const hw, uint8_t index,
                                                        hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_RES1MUX(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_RES1MUX_bf(const void *const hw, uint8_t index,
                                                         hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_RES1MUX(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_read_OPAMPCTRL_RES1MUX_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_RES1MUX_Msk) >> OPAMP_OPAMPCTRL_RES1MUX_Pos;
	return tmp;
}

static inline void hri_opamp_set_OPAMPCTRL_POTMUX_bf(const void *const hw, uint8_t index,
                                                     hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_POTMUX(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_get_OPAMPCTRL_POTMUX_bf(const void *const hw, uint8_t index,
                                                                          hri_opamp_opampctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_POTMUX(mask)) >> OPAMP_OPAMPCTRL_POTMUX_Pos;
	return tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_POTMUX_bf(const void *const hw, uint8_t index,
                                                       hri_opamp_opampctrl_reg_t data)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_POTMUX_Msk;
	tmp |= OPAMP_OPAMPCTRL_POTMUX(data);
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_POTMUX_bf(const void *const hw, uint8_t index,
                                                       hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_POTMUX(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_POTMUX_bf(const void *const hw, uint8_t index,
                                                        hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_POTMUX(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_read_OPAMPCTRL_POTMUX_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_POTMUX_Msk) >> OPAMP_OPAMPCTRL_POTMUX_Pos;
	return tmp;
}

static inline void hri_opamp_set_OPAMPCTRL_MUXPOS_bf(const void *const hw, uint8_t index,
                                                     hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_MUXPOS(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_get_OPAMPCTRL_MUXPOS_bf(const void *const hw, uint8_t index,
                                                                          hri_opamp_opampctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_MUXPOS(mask)) >> OPAMP_OPAMPCTRL_MUXPOS_Pos;
	return tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_MUXPOS_bf(const void *const hw, uint8_t index,
                                                       hri_opamp_opampctrl_reg_t data)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_MUXPOS_Msk;
	tmp |= OPAMP_OPAMPCTRL_MUXPOS(data);
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_MUXPOS_bf(const void *const hw, uint8_t index,
                                                       hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_MUXPOS(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_MUXPOS_bf(const void *const hw, uint8_t index,
                                                        hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_MUXPOS(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_read_OPAMPCTRL_MUXPOS_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_MUXPOS_Msk) >> OPAMP_OPAMPCTRL_MUXPOS_Pos;
	return tmp;
}

static inline void hri_opamp_set_OPAMPCTRL_MUXNEG_bf(const void *const hw, uint8_t index,
                                                     hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= OPAMP_OPAMPCTRL_MUXNEG(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_get_OPAMPCTRL_MUXNEG_bf(const void *const hw, uint8_t index,
                                                                          hri_opamp_opampctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_MUXNEG(mask)) >> OPAMP_OPAMPCTRL_MUXNEG_Pos;
	return tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_MUXNEG_bf(const void *const hw, uint8_t index,
                                                       hri_opamp_opampctrl_reg_t data)
{
	uint32_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= ~OPAMP_OPAMPCTRL_MUXNEG_Msk;
	tmp |= OPAMP_OPAMPCTRL_MUXNEG(data);
	((Opamp *)hw)->OPAMPCTRL[index].reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_MUXNEG_bf(const void *const hw, uint8_t index,
                                                       hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~OPAMP_OPAMPCTRL_MUXNEG(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_MUXNEG_bf(const void *const hw, uint8_t index,
                                                        hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= OPAMP_OPAMPCTRL_MUXNEG(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_read_OPAMPCTRL_MUXNEG_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp = (tmp & OPAMP_OPAMPCTRL_MUXNEG_Msk) >> OPAMP_OPAMPCTRL_MUXNEG_Pos;
	return tmp;
}

static inline void hri_opamp_set_OPAMPCTRL_reg(const void *const hw, uint8_t index, hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg |= mask;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_get_OPAMPCTRL_reg(const void *const hw, uint8_t index,
                                                                    hri_opamp_opampctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Opamp *)hw)->OPAMPCTRL[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_opamp_write_OPAMPCTRL_reg(const void *const hw, uint8_t index, hri_opamp_opampctrl_reg_t data)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg = data;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_OPAMPCTRL_reg(const void *const hw, uint8_t index, hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg &= ~mask;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_OPAMPCTRL_reg(const void *const hw, uint8_t index, hri_opamp_opampctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->OPAMPCTRL[index].reg ^= mask;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_opampctrl_reg_t hri_opamp_read_OPAMPCTRL_reg(const void *const hw, uint8_t index)
{
	return ((Opamp *)hw)->OPAMPCTRL[index].reg;
}

static inline void hri_opamp_set_RESCTRL_RES2OUT_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg |= OPAMP_RESCTRL_RES2OUT_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_RESCTRL_RES2OUT_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp = (tmp & OPAMP_RESCTRL_RES2OUT_Msk) >> OPAMP_RESCTRL_RES2OUT_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_RESCTRL_RES2OUT_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp &= ~OPAMP_RESCTRL_RES2OUT_Msk;
	tmp |= value << OPAMP_RESCTRL_RES2OUT_Pos;
	((Opamp *)hw)->RESCTRL.reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_RESCTRL_RES2OUT_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg &= ~OPAMP_RESCTRL_RES2OUT_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_RESCTRL_RES2OUT_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg ^= OPAMP_RESCTRL_RES2OUT_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_RESCTRL_RES1EN_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg |= OPAMP_RESCTRL_RES1EN_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_RESCTRL_RES1EN_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp = (tmp & OPAMP_RESCTRL_RES1EN_Msk) >> OPAMP_RESCTRL_RES1EN_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_RESCTRL_RES1EN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp &= ~OPAMP_RESCTRL_RES1EN_Msk;
	tmp |= value << OPAMP_RESCTRL_RES1EN_Pos;
	((Opamp *)hw)->RESCTRL.reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_RESCTRL_RES1EN_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg &= ~OPAMP_RESCTRL_RES1EN_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_RESCTRL_RES1EN_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg ^= OPAMP_RESCTRL_RES1EN_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_RESCTRL_RES1MUX_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg |= OPAMP_RESCTRL_RES1MUX_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_opamp_get_RESCTRL_RES1MUX_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp = (tmp & OPAMP_RESCTRL_RES1MUX_Msk) >> OPAMP_RESCTRL_RES1MUX_Pos;
	return (bool)tmp;
}

static inline void hri_opamp_write_RESCTRL_RES1MUX_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp &= ~OPAMP_RESCTRL_RES1MUX_Msk;
	tmp |= value << OPAMP_RESCTRL_RES1MUX_Pos;
	((Opamp *)hw)->RESCTRL.reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_RESCTRL_RES1MUX_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg &= ~OPAMP_RESCTRL_RES1MUX_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_RESCTRL_RES1MUX_bit(const void *const hw)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg ^= OPAMP_RESCTRL_RES1MUX_Msk;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_set_RESCTRL_POTMUX_bf(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg |= OPAMP_RESCTRL_POTMUX(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_resctrl_reg_t hri_opamp_get_RESCTRL_POTMUX_bf(const void *const       hw,
                                                                      hri_opamp_resctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp = (tmp & OPAMP_RESCTRL_POTMUX(mask)) >> OPAMP_RESCTRL_POTMUX_Pos;
	return tmp;
}

static inline void hri_opamp_write_RESCTRL_POTMUX_bf(const void *const hw, hri_opamp_resctrl_reg_t data)
{
	uint8_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp &= ~OPAMP_RESCTRL_POTMUX_Msk;
	tmp |= OPAMP_RESCTRL_POTMUX(data);
	((Opamp *)hw)->RESCTRL.reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_RESCTRL_POTMUX_bf(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg &= ~OPAMP_RESCTRL_POTMUX(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_RESCTRL_POTMUX_bf(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg ^= OPAMP_RESCTRL_POTMUX(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_resctrl_reg_t hri_opamp_read_RESCTRL_POTMUX_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp = (tmp & OPAMP_RESCTRL_POTMUX_Msk) >> OPAMP_RESCTRL_POTMUX_Pos;
	return tmp;
}

static inline void hri_opamp_set_RESCTRL_REFBUFLEVEL_bf(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg |= OPAMP_RESCTRL_REFBUFLEVEL(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_resctrl_reg_t hri_opamp_get_RESCTRL_REFBUFLEVEL_bf(const void *const       hw,
                                                                           hri_opamp_resctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp = (tmp & OPAMP_RESCTRL_REFBUFLEVEL(mask)) >> OPAMP_RESCTRL_REFBUFLEVEL_Pos;
	return tmp;
}

static inline void hri_opamp_write_RESCTRL_REFBUFLEVEL_bf(const void *const hw, hri_opamp_resctrl_reg_t data)
{
	uint8_t tmp;
	OPAMP_CRITICAL_SECTION_ENTER();
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp &= ~OPAMP_RESCTRL_REFBUFLEVEL_Msk;
	tmp |= OPAMP_RESCTRL_REFBUFLEVEL(data);
	((Opamp *)hw)->RESCTRL.reg = tmp;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_RESCTRL_REFBUFLEVEL_bf(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg &= ~OPAMP_RESCTRL_REFBUFLEVEL(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_RESCTRL_REFBUFLEVEL_bf(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg ^= OPAMP_RESCTRL_REFBUFLEVEL(mask);
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_resctrl_reg_t hri_opamp_read_RESCTRL_REFBUFLEVEL_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp = (tmp & OPAMP_RESCTRL_REFBUFLEVEL_Msk) >> OPAMP_RESCTRL_REFBUFLEVEL_Pos;
	return tmp;
}

static inline void hri_opamp_set_RESCTRL_reg(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg |= mask;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_resctrl_reg_t hri_opamp_get_RESCTRL_reg(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Opamp *)hw)->RESCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_opamp_write_RESCTRL_reg(const void *const hw, hri_opamp_resctrl_reg_t data)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg = data;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_clear_RESCTRL_reg(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg &= ~mask;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline void hri_opamp_toggle_RESCTRL_reg(const void *const hw, hri_opamp_resctrl_reg_t mask)
{
	OPAMP_CRITICAL_SECTION_ENTER();
	((Opamp *)hw)->RESCTRL.reg ^= mask;
	OPAMP_CRITICAL_SECTION_LEAVE();
}

static inline hri_opamp_resctrl_reg_t hri_opamp_read_RESCTRL_reg(const void *const hw)
{
	return ((Opamp *)hw)->RESCTRL.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_OPAMP_L10_H_INCLUDED */
#endif /* _SAML10_OPAMP_COMPONENT_ */
