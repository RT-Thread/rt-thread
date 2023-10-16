/**
 * \file
 *
 * \brief SAM CCL
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAMD51_CCL_COMPONENT_
#ifndef _HRI_CCL_D51_H_INCLUDED_
#define _HRI_CCL_D51_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_CCL_CRITICAL_SECTIONS)
#define CCL_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define CCL_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define CCL_CRITICAL_SECTION_ENTER()
#define CCL_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_ccl_lutctrl_reg_t;
typedef uint8_t  hri_ccl_ctrl_reg_t;
typedef uint8_t  hri_ccl_seqctrl_reg_t;

static inline void hri_ccl_set_CTRL_SWRST_bit(const void *const hw)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg |= CCL_CTRL_SWRST;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ccl_get_CTRL_SWRST_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Ccl *)hw)->CTRL.reg;
	tmp = (tmp & CCL_CTRL_SWRST) >> CCL_CTRL_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_ccl_set_CTRL_ENABLE_bit(const void *const hw)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg |= CCL_CTRL_ENABLE;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ccl_get_CTRL_ENABLE_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Ccl *)hw)->CTRL.reg;
	tmp = (tmp & CCL_CTRL_ENABLE) >> CCL_CTRL_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_ccl_write_CTRL_ENABLE_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->CTRL.reg;
	tmp &= ~CCL_CTRL_ENABLE;
	tmp |= value << CCL_CTRL_ENABLE_Pos;
	((Ccl *)hw)->CTRL.reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_CTRL_ENABLE_bit(const void *const hw)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg &= ~CCL_CTRL_ENABLE;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_CTRL_ENABLE_bit(const void *const hw)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg ^= CCL_CTRL_ENABLE;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_set_CTRL_RUNSTDBY_bit(const void *const hw)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg |= CCL_CTRL_RUNSTDBY;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ccl_get_CTRL_RUNSTDBY_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Ccl *)hw)->CTRL.reg;
	tmp = (tmp & CCL_CTRL_RUNSTDBY) >> CCL_CTRL_RUNSTDBY_Pos;
	return (bool)tmp;
}

static inline void hri_ccl_write_CTRL_RUNSTDBY_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->CTRL.reg;
	tmp &= ~CCL_CTRL_RUNSTDBY;
	tmp |= value << CCL_CTRL_RUNSTDBY_Pos;
	((Ccl *)hw)->CTRL.reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_CTRL_RUNSTDBY_bit(const void *const hw)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg &= ~CCL_CTRL_RUNSTDBY;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_CTRL_RUNSTDBY_bit(const void *const hw)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg ^= CCL_CTRL_RUNSTDBY;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_set_CTRL_reg(const void *const hw, hri_ccl_ctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg |= mask;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_ctrl_reg_t hri_ccl_get_CTRL_reg(const void *const hw, hri_ccl_ctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Ccl *)hw)->CTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_ccl_write_CTRL_reg(const void *const hw, hri_ccl_ctrl_reg_t data)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg = data;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_CTRL_reg(const void *const hw, hri_ccl_ctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg &= ~mask;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_CTRL_reg(const void *const hw, hri_ccl_ctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->CTRL.reg ^= mask;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_ctrl_reg_t hri_ccl_read_CTRL_reg(const void *const hw)
{
	return ((Ccl *)hw)->CTRL.reg;
}

static inline void hri_ccl_set_SEQCTRL_SEQSEL_bf(const void *const hw, uint8_t index, hri_ccl_seqctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->SEQCTRL[index].reg |= CCL_SEQCTRL_SEQSEL(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_seqctrl_reg_t hri_ccl_get_SEQCTRL_SEQSEL_bf(const void *const hw, uint8_t index,
                                                                  hri_ccl_seqctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Ccl *)hw)->SEQCTRL[index].reg;
	tmp = (tmp & CCL_SEQCTRL_SEQSEL(mask)) >> CCL_SEQCTRL_SEQSEL_Pos;
	return tmp;
}

static inline void hri_ccl_write_SEQCTRL_SEQSEL_bf(const void *const hw, uint8_t index, hri_ccl_seqctrl_reg_t data)
{
	uint8_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->SEQCTRL[index].reg;
	tmp &= ~CCL_SEQCTRL_SEQSEL_Msk;
	tmp |= CCL_SEQCTRL_SEQSEL(data);
	((Ccl *)hw)->SEQCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_SEQCTRL_SEQSEL_bf(const void *const hw, uint8_t index, hri_ccl_seqctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->SEQCTRL[index].reg &= ~CCL_SEQCTRL_SEQSEL(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_SEQCTRL_SEQSEL_bf(const void *const hw, uint8_t index, hri_ccl_seqctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->SEQCTRL[index].reg ^= CCL_SEQCTRL_SEQSEL(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_seqctrl_reg_t hri_ccl_read_SEQCTRL_SEQSEL_bf(const void *const hw, uint8_t index)
{
	uint8_t tmp;
	tmp = ((Ccl *)hw)->SEQCTRL[index].reg;
	tmp = (tmp & CCL_SEQCTRL_SEQSEL_Msk) >> CCL_SEQCTRL_SEQSEL_Pos;
	return tmp;
}

static inline void hri_ccl_set_SEQCTRL_reg(const void *const hw, uint8_t index, hri_ccl_seqctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->SEQCTRL[index].reg |= mask;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_seqctrl_reg_t hri_ccl_get_SEQCTRL_reg(const void *const hw, uint8_t index,
                                                            hri_ccl_seqctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Ccl *)hw)->SEQCTRL[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_ccl_write_SEQCTRL_reg(const void *const hw, uint8_t index, hri_ccl_seqctrl_reg_t data)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->SEQCTRL[index].reg = data;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_SEQCTRL_reg(const void *const hw, uint8_t index, hri_ccl_seqctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->SEQCTRL[index].reg &= ~mask;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_SEQCTRL_reg(const void *const hw, uint8_t index, hri_ccl_seqctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->SEQCTRL[index].reg ^= mask;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_seqctrl_reg_t hri_ccl_read_SEQCTRL_reg(const void *const hw, uint8_t index)
{
	return ((Ccl *)hw)->SEQCTRL[index].reg;
}

static inline void hri_ccl_set_LUTCTRL_ENABLE_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_ENABLE;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ccl_get_LUTCTRL_ENABLE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_ENABLE) >> CCL_LUTCTRL_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_ccl_write_LUTCTRL_ENABLE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_ENABLE;
	tmp |= value << CCL_LUTCTRL_ENABLE_Pos;
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_ENABLE_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_ENABLE;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_ENABLE_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_ENABLE;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_set_LUTCTRL_EDGESEL_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_EDGESEL;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ccl_get_LUTCTRL_EDGESEL_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_EDGESEL) >> CCL_LUTCTRL_EDGESEL_Pos;
	return (bool)tmp;
}

static inline void hri_ccl_write_LUTCTRL_EDGESEL_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_EDGESEL;
	tmp |= value << CCL_LUTCTRL_EDGESEL_Pos;
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_EDGESEL_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_EDGESEL;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_EDGESEL_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_EDGESEL;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_set_LUTCTRL_INVEI_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_INVEI;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ccl_get_LUTCTRL_INVEI_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_INVEI) >> CCL_LUTCTRL_INVEI_Pos;
	return (bool)tmp;
}

static inline void hri_ccl_write_LUTCTRL_INVEI_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_INVEI;
	tmp |= value << CCL_LUTCTRL_INVEI_Pos;
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_INVEI_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_INVEI;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_INVEI_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_INVEI;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_set_LUTCTRL_LUTEI_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_LUTEI;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ccl_get_LUTCTRL_LUTEI_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_LUTEI) >> CCL_LUTCTRL_LUTEI_Pos;
	return (bool)tmp;
}

static inline void hri_ccl_write_LUTCTRL_LUTEI_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_LUTEI;
	tmp |= value << CCL_LUTCTRL_LUTEI_Pos;
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_LUTEI_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_LUTEI;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_LUTEI_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_LUTEI;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_set_LUTCTRL_LUTEO_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_LUTEO;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ccl_get_LUTCTRL_LUTEO_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_LUTEO) >> CCL_LUTCTRL_LUTEO_Pos;
	return (bool)tmp;
}

static inline void hri_ccl_write_LUTCTRL_LUTEO_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_LUTEO;
	tmp |= value << CCL_LUTCTRL_LUTEO_Pos;
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_LUTEO_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_LUTEO;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_LUTEO_bit(const void *const hw, uint8_t index)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_LUTEO;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_set_LUTCTRL_FILTSEL_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_FILTSEL(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_get_LUTCTRL_FILTSEL_bf(const void *const hw, uint8_t index,
                                                                   hri_ccl_lutctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_FILTSEL(mask)) >> CCL_LUTCTRL_FILTSEL_Pos;
	return tmp;
}

static inline void hri_ccl_write_LUTCTRL_FILTSEL_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t data)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_FILTSEL_Msk;
	tmp |= CCL_LUTCTRL_FILTSEL(data);
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_FILTSEL_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_FILTSEL(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_FILTSEL_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_FILTSEL(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_read_LUTCTRL_FILTSEL_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_FILTSEL_Msk) >> CCL_LUTCTRL_FILTSEL_Pos;
	return tmp;
}

static inline void hri_ccl_set_LUTCTRL_INSEL0_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_INSEL0(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_get_LUTCTRL_INSEL0_bf(const void *const hw, uint8_t index,
                                                                  hri_ccl_lutctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_INSEL0(mask)) >> CCL_LUTCTRL_INSEL0_Pos;
	return tmp;
}

static inline void hri_ccl_write_LUTCTRL_INSEL0_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t data)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_INSEL0_Msk;
	tmp |= CCL_LUTCTRL_INSEL0(data);
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_INSEL0_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_INSEL0(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_INSEL0_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_INSEL0(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_read_LUTCTRL_INSEL0_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_INSEL0_Msk) >> CCL_LUTCTRL_INSEL0_Pos;
	return tmp;
}

static inline void hri_ccl_set_LUTCTRL_INSEL1_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_INSEL1(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_get_LUTCTRL_INSEL1_bf(const void *const hw, uint8_t index,
                                                                  hri_ccl_lutctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_INSEL1(mask)) >> CCL_LUTCTRL_INSEL1_Pos;
	return tmp;
}

static inline void hri_ccl_write_LUTCTRL_INSEL1_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t data)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_INSEL1_Msk;
	tmp |= CCL_LUTCTRL_INSEL1(data);
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_INSEL1_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_INSEL1(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_INSEL1_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_INSEL1(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_read_LUTCTRL_INSEL1_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_INSEL1_Msk) >> CCL_LUTCTRL_INSEL1_Pos;
	return tmp;
}

static inline void hri_ccl_set_LUTCTRL_INSEL2_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_INSEL2(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_get_LUTCTRL_INSEL2_bf(const void *const hw, uint8_t index,
                                                                  hri_ccl_lutctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_INSEL2(mask)) >> CCL_LUTCTRL_INSEL2_Pos;
	return tmp;
}

static inline void hri_ccl_write_LUTCTRL_INSEL2_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t data)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_INSEL2_Msk;
	tmp |= CCL_LUTCTRL_INSEL2(data);
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_INSEL2_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_INSEL2(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_INSEL2_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_INSEL2(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_read_LUTCTRL_INSEL2_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_INSEL2_Msk) >> CCL_LUTCTRL_INSEL2_Pos;
	return tmp;
}

static inline void hri_ccl_set_LUTCTRL_TRUTH_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= CCL_LUTCTRL_TRUTH(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_get_LUTCTRL_TRUTH_bf(const void *const hw, uint8_t index,
                                                                 hri_ccl_lutctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_TRUTH(mask)) >> CCL_LUTCTRL_TRUTH_Pos;
	return tmp;
}

static inline void hri_ccl_write_LUTCTRL_TRUTH_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t data)
{
	uint32_t tmp;
	CCL_CRITICAL_SECTION_ENTER();
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= ~CCL_LUTCTRL_TRUTH_Msk;
	tmp |= CCL_LUTCTRL_TRUTH(data);
	((Ccl *)hw)->LUTCTRL[index].reg = tmp;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_TRUTH_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~CCL_LUTCTRL_TRUTH(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_TRUTH_bf(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= CCL_LUTCTRL_TRUTH(mask);
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_read_LUTCTRL_TRUTH_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp = (tmp & CCL_LUTCTRL_TRUTH_Msk) >> CCL_LUTCTRL_TRUTH_Pos;
	return tmp;
}

static inline void hri_ccl_set_LUTCTRL_reg(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg |= mask;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_get_LUTCTRL_reg(const void *const hw, uint8_t index,
                                                            hri_ccl_lutctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ccl *)hw)->LUTCTRL[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_ccl_write_LUTCTRL_reg(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t data)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg = data;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_clear_LUTCTRL_reg(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg &= ~mask;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ccl_toggle_LUTCTRL_reg(const void *const hw, uint8_t index, hri_ccl_lutctrl_reg_t mask)
{
	CCL_CRITICAL_SECTION_ENTER();
	((Ccl *)hw)->LUTCTRL[index].reg ^= mask;
	CCL_CRITICAL_SECTION_LEAVE();
}

static inline hri_ccl_lutctrl_reg_t hri_ccl_read_LUTCTRL_reg(const void *const hw, uint8_t index)
{
	return ((Ccl *)hw)->LUTCTRL[index].reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_CCL_D51_H_INCLUDED */
#endif /* _SAMD51_CCL_COMPONENT_ */
