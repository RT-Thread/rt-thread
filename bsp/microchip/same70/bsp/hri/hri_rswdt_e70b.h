/**
 * \file
 *
 * \brief SAM RSWDT
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
 */

#ifdef _SAME70_RSWDT_COMPONENT_
#ifndef _HRI_RSWDT_E70B_H_INCLUDED_
#define _HRI_RSWDT_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_RSWDT_CRITICAL_SECTIONS)
#define RSWDT_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define RSWDT_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define RSWDT_CRITICAL_SECTION_ENTER()
#define RSWDT_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_rswdt_cr_reg_t;
typedef uint32_t hri_rswdt_mr_reg_t;
typedef uint32_t hri_rswdt_sr_reg_t;

static inline bool hri_rswdt_get_SR_WDUNF_bit(const void *const hw)
{
	return (((Rswdt *)hw)->RSWDT_SR & RSWDT_SR_WDUNF) > 0;
}

static inline hri_rswdt_sr_reg_t hri_rswdt_get_SR_reg(const void *const hw, hri_rswdt_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_rswdt_sr_reg_t hri_rswdt_read_SR_reg(const void *const hw)
{
	return ((Rswdt *)hw)->RSWDT_SR;
}

static inline void hri_rswdt_set_MR_WDFIEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDFIEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDFIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDFIEN) >> RSWDT_MR_WDFIEN_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDFIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDFIEN;
	tmp |= value << RSWDT_MR_WDFIEN_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDFIEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDFIEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDFIEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDFIEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDRSTEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDRSTEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDRSTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDRSTEN) >> RSWDT_MR_WDRSTEN_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDRSTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDRSTEN;
	tmp |= value << RSWDT_MR_WDRSTEN_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDRSTEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDRSTEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDRSTEN_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDRSTEN;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDDIS_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDDIS;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDDIS) >> RSWDT_MR_WDDIS_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDDIS;
	tmp |= value << RSWDT_MR_WDDIS_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDDIS_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDDIS;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDDIS_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDDIS;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDDBGHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDDBGHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDDBGHLT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDDBGHLT) >> RSWDT_MR_WDDBGHLT_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDDBGHLT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDDBGHLT;
	tmp |= value << RSWDT_MR_WDDBGHLT_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDDBGHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDDBGHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDDBGHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDDBGHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDIDLEHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDIDLEHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rswdt_get_MR_WDIDLEHLT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDIDLEHLT) >> RSWDT_MR_WDIDLEHLT_Pos;
	return (bool)tmp;
}

static inline void hri_rswdt_write_MR_WDIDLEHLT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDIDLEHLT;
	tmp |= value << RSWDT_MR_WDIDLEHLT_Pos;
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDIDLEHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDIDLEHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDIDLEHLT_bit(const void *const hw)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDIDLEHLT;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_set_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_WDV(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_get_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDV(mask)) >> RSWDT_MR_WDV_Pos;
	return tmp;
}

static inline void hri_rswdt_write_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t data)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_WDV_Msk;
	tmp |= RSWDT_MR_WDV(data);
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_WDV(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_WDV_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_WDV(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_read_MR_WDV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_WDV_Msk) >> RSWDT_MR_WDV_Pos;
	return tmp;
}

static inline void hri_rswdt_set_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= RSWDT_MR_ALLONES(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_get_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_ALLONES(mask)) >> RSWDT_MR_ALLONES_Pos;
	return tmp;
}

static inline void hri_rswdt_write_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t data)
{
	uint32_t tmp;
	RSWDT_CRITICAL_SECTION_ENTER();
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= ~RSWDT_MR_ALLONES_Msk;
	tmp |= RSWDT_MR_ALLONES(data);
	((Rswdt *)hw)->RSWDT_MR = tmp;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~RSWDT_MR_ALLONES(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_ALLONES_bf(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= RSWDT_MR_ALLONES(mask);
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_read_MR_ALLONES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp = (tmp & RSWDT_MR_ALLONES_Msk) >> RSWDT_MR_ALLONES_Pos;
	return tmp;
}

static inline void hri_rswdt_set_MR_reg(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR |= mask;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_get_MR_reg(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rswdt *)hw)->RSWDT_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rswdt_write_MR_reg(const void *const hw, hri_rswdt_mr_reg_t data)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR = data;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_clear_MR_reg(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR &= ~mask;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rswdt_toggle_MR_reg(const void *const hw, hri_rswdt_mr_reg_t mask)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_MR ^= mask;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rswdt_mr_reg_t hri_rswdt_read_MR_reg(const void *const hw)
{
	return ((Rswdt *)hw)->RSWDT_MR;
}

static inline void hri_rswdt_write_CR_reg(const void *const hw, hri_rswdt_cr_reg_t data)
{
	RSWDT_CRITICAL_SECTION_ENTER();
	((Rswdt *)hw)->RSWDT_CR = data;
	RSWDT_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RSWDT_E70B_H_INCLUDED */
#endif /* _SAME70_RSWDT_COMPONENT_ */
