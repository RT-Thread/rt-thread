/**
 * \file
 *
 * \brief SAM RSTC
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

#ifdef _SAME70_RSTC_COMPONENT_
#ifndef _HRI_RSTC_E70B_H_INCLUDED_
#define _HRI_RSTC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_RSTC_CRITICAL_SECTIONS)
#define RSTC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define RSTC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define RSTC_CRITICAL_SECTION_ENTER()
#define RSTC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_rstc_cr_reg_t;
typedef uint32_t hri_rstc_mr_reg_t;
typedef uint32_t hri_rstc_sr_reg_t;

static inline bool hri_rstc_get_SR_URSTS_bit(const void *const hw)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_URSTS) > 0;
}

static inline bool hri_rstc_get_SR_NRSTL_bit(const void *const hw)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_NRSTL) > 0;
}

static inline bool hri_rstc_get_SR_SRCMP_bit(const void *const hw)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_SRCMP) > 0;
}

static inline hri_rstc_sr_reg_t hri_rstc_get_SR_RSTTYP_bf(const void *const hw, hri_rstc_sr_reg_t mask)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_RSTTYP(mask)) >> RSTC_SR_RSTTYP_Pos;
}

static inline hri_rstc_sr_reg_t hri_rstc_read_SR_RSTTYP_bf(const void *const hw)
{
	return (((Rstc *)hw)->RSTC_SR & RSTC_SR_RSTTYP_Msk) >> RSTC_SR_RSTTYP_Pos;
}

static inline hri_rstc_sr_reg_t hri_rstc_get_SR_reg(const void *const hw, hri_rstc_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_rstc_sr_reg_t hri_rstc_read_SR_reg(const void *const hw)
{
	return ((Rstc *)hw)->RSTC_SR;
}

static inline void hri_rstc_set_MR_URSTEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= RSTC_MR_URSTEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rstc_get_MR_URSTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_URSTEN) >> RSTC_MR_URSTEN_Pos;
	return (bool)tmp;
}

static inline void hri_rstc_write_MR_URSTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= ~RSTC_MR_URSTEN;
	tmp |= value << RSTC_MR_URSTEN_Pos;
	((Rstc *)hw)->RSTC_MR = tmp;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_URSTEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~RSTC_MR_URSTEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_URSTEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= RSTC_MR_URSTEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_set_MR_URSTIEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= RSTC_MR_URSTIEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rstc_get_MR_URSTIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_URSTIEN) >> RSTC_MR_URSTIEN_Pos;
	return (bool)tmp;
}

static inline void hri_rstc_write_MR_URSTIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RSTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= ~RSTC_MR_URSTIEN;
	tmp |= value << RSTC_MR_URSTIEN_Pos;
	((Rstc *)hw)->RSTC_MR = tmp;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_URSTIEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~RSTC_MR_URSTIEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_URSTIEN_bit(const void *const hw)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= RSTC_MR_URSTIEN;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_set_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= RSTC_MR_ERSTL(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_get_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_ERSTL(mask)) >> RSTC_MR_ERSTL_Pos;
	return tmp;
}

static inline void hri_rstc_write_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t data)
{
	uint32_t tmp;
	RSTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= ~RSTC_MR_ERSTL_Msk;
	tmp |= RSTC_MR_ERSTL(data);
	((Rstc *)hw)->RSTC_MR = tmp;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~RSTC_MR_ERSTL(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_ERSTL_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= RSTC_MR_ERSTL(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_read_MR_ERSTL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_ERSTL_Msk) >> RSTC_MR_ERSTL_Pos;
	return tmp;
}

static inline void hri_rstc_set_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= RSTC_MR_KEY(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_get_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_KEY(mask)) >> RSTC_MR_KEY_Pos;
	return tmp;
}

static inline void hri_rstc_write_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t data)
{
	uint32_t tmp;
	RSTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= ~RSTC_MR_KEY_Msk;
	tmp |= RSTC_MR_KEY(data);
	((Rstc *)hw)->RSTC_MR = tmp;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~RSTC_MR_KEY(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_KEY_bf(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= RSTC_MR_KEY(mask);
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_read_MR_KEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp = (tmp & RSTC_MR_KEY_Msk) >> RSTC_MR_KEY_Pos;
	return tmp;
}

static inline void hri_rstc_set_MR_reg(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR |= mask;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_get_MR_reg(const void *const hw, hri_rstc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rstc *)hw)->RSTC_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rstc_write_MR_reg(const void *const hw, hri_rstc_mr_reg_t data)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR = data;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_clear_MR_reg(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR &= ~mask;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rstc_toggle_MR_reg(const void *const hw, hri_rstc_mr_reg_t mask)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_MR ^= mask;
	RSTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rstc_mr_reg_t hri_rstc_read_MR_reg(const void *const hw)
{
	return ((Rstc *)hw)->RSTC_MR;
}

static inline void hri_rstc_write_CR_reg(const void *const hw, hri_rstc_cr_reg_t data)
{
	RSTC_CRITICAL_SECTION_ENTER();
	((Rstc *)hw)->RSTC_CR = data;
	RSTC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RSTC_E70B_H_INCLUDED */
#endif /* _SAME70_RSTC_COMPONENT_ */
