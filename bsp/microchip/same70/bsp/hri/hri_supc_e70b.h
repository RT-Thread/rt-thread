/**
 * \file
 *
 * \brief SAM SUPC
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

#ifdef _SAME70_SUPC_COMPONENT_
#ifndef _HRI_SUPC_E70B_H_INCLUDED_
#define _HRI_SUPC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_SUPC_CRITICAL_SECTIONS)
#define SUPC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define SUPC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define SUPC_CRITICAL_SECTION_ENTER()
#define SUPC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_supc_cr_reg_t;
typedef uint32_t hri_supc_mr_reg_t;
typedef uint32_t hri_supc_smmr_reg_t;
typedef uint32_t hri_supc_sr_reg_t;
typedef uint32_t hri_supc_wuir_reg_t;
typedef uint32_t hri_supc_wumr_reg_t;

static inline bool hri_supc_get_SR_WKUPS_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPS) > 0;
}

static inline bool hri_supc_get_SR_SMWS_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_SMWS) > 0;
}

static inline bool hri_supc_get_SR_BODRSTS_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_BODRSTS) > 0;
}

static inline bool hri_supc_get_SR_SMRSTS_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_SMRSTS) > 0;
}

static inline bool hri_supc_get_SR_SMS_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_SMS) > 0;
}

static inline bool hri_supc_get_SR_SMOS_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_SMOS) > 0;
}

static inline bool hri_supc_get_SR_OSCSEL_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_OSCSEL) > 0;
}

static inline bool hri_supc_get_SR_LPDBCS0_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_LPDBCS0) > 0;
}

static inline bool hri_supc_get_SR_LPDBCS1_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_LPDBCS1) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS0_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS0) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS1_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS1) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS2_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS2) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS3_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS3) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS4_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS4) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS5_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS5) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS6_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS6) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS7_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS7) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS8_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS8) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS9_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS9) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS10_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS10) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS11_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS11) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS12_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS12) > 0;
}

static inline bool hri_supc_get_SR_WKUPIS13_bit(const void *const hw)
{
	return (((Supc *)hw)->SUPC_SR & SUPC_SR_WKUPIS13) > 0;
}

static inline hri_supc_sr_reg_t hri_supc_get_SR_reg(const void *const hw, hri_supc_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_supc_sr_reg_t hri_supc_read_SR_reg(const void *const hw)
{
	return ((Supc *)hw)->SUPC_SR;
}

static inline void hri_supc_set_SMMR_SMRSTEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR |= SUPC_SMMR_SMRSTEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_SMMR_SMRSTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp = (tmp & SUPC_SMMR_SMRSTEN) >> SUPC_SMMR_SMRSTEN_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_SMMR_SMRSTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp &= ~SUPC_SMMR_SMRSTEN;
	tmp |= value << SUPC_SMMR_SMRSTEN_Pos;
	((Supc *)hw)->SUPC_SMMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_SMMR_SMRSTEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR &= ~SUPC_SMMR_SMRSTEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_SMMR_SMRSTEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR ^= SUPC_SMMR_SMRSTEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_SMMR_SMIEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR |= SUPC_SMMR_SMIEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_SMMR_SMIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp = (tmp & SUPC_SMMR_SMIEN) >> SUPC_SMMR_SMIEN_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_SMMR_SMIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp &= ~SUPC_SMMR_SMIEN;
	tmp |= value << SUPC_SMMR_SMIEN_Pos;
	((Supc *)hw)->SUPC_SMMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_SMMR_SMIEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR &= ~SUPC_SMMR_SMIEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_SMMR_SMIEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR ^= SUPC_SMMR_SMIEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_SMMR_SMTH_bf(const void *const hw, hri_supc_smmr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR |= SUPC_SMMR_SMTH(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_smmr_reg_t hri_supc_get_SMMR_SMTH_bf(const void *const hw, hri_supc_smmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp = (tmp & SUPC_SMMR_SMTH(mask)) >> SUPC_SMMR_SMTH_Pos;
	return tmp;
}

static inline void hri_supc_write_SMMR_SMTH_bf(const void *const hw, hri_supc_smmr_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp &= ~SUPC_SMMR_SMTH_Msk;
	tmp |= SUPC_SMMR_SMTH(data);
	((Supc *)hw)->SUPC_SMMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_SMMR_SMTH_bf(const void *const hw, hri_supc_smmr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR &= ~SUPC_SMMR_SMTH(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_SMMR_SMTH_bf(const void *const hw, hri_supc_smmr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR ^= SUPC_SMMR_SMTH(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_smmr_reg_t hri_supc_read_SMMR_SMTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp = (tmp & SUPC_SMMR_SMTH_Msk) >> SUPC_SMMR_SMTH_Pos;
	return tmp;
}

static inline void hri_supc_set_SMMR_SMSMPL_bf(const void *const hw, hri_supc_smmr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR |= SUPC_SMMR_SMSMPL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_smmr_reg_t hri_supc_get_SMMR_SMSMPL_bf(const void *const hw, hri_supc_smmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp = (tmp & SUPC_SMMR_SMSMPL(mask)) >> SUPC_SMMR_SMSMPL_Pos;
	return tmp;
}

static inline void hri_supc_write_SMMR_SMSMPL_bf(const void *const hw, hri_supc_smmr_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp &= ~SUPC_SMMR_SMSMPL_Msk;
	tmp |= SUPC_SMMR_SMSMPL(data);
	((Supc *)hw)->SUPC_SMMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_SMMR_SMSMPL_bf(const void *const hw, hri_supc_smmr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR &= ~SUPC_SMMR_SMSMPL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_SMMR_SMSMPL_bf(const void *const hw, hri_supc_smmr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR ^= SUPC_SMMR_SMSMPL(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_smmr_reg_t hri_supc_read_SMMR_SMSMPL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp = (tmp & SUPC_SMMR_SMSMPL_Msk) >> SUPC_SMMR_SMSMPL_Pos;
	return tmp;
}

static inline void hri_supc_set_SMMR_reg(const void *const hw, hri_supc_smmr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_smmr_reg_t hri_supc_get_SMMR_reg(const void *const hw, hri_supc_smmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_SMMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_SMMR_reg(const void *const hw, hri_supc_smmr_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_SMMR_reg(const void *const hw, hri_supc_smmr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_SMMR_reg(const void *const hw, hri_supc_smmr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_SMMR ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_smmr_reg_t hri_supc_read_SMMR_reg(const void *const hw)
{
	return ((Supc *)hw)->SUPC_SMMR;
}

static inline void hri_supc_set_MR_BODRSTEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR |= SUPC_MR_BODRSTEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_MR_BODRSTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp = (tmp & SUPC_MR_BODRSTEN) >> SUPC_MR_BODRSTEN_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_MR_BODRSTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp &= ~SUPC_MR_BODRSTEN;
	tmp |= value << SUPC_MR_BODRSTEN_Pos;
	((Supc *)hw)->SUPC_MR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_MR_BODRSTEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR &= ~SUPC_MR_BODRSTEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_MR_BODRSTEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR ^= SUPC_MR_BODRSTEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_MR_BODDIS_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR |= SUPC_MR_BODDIS;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_MR_BODDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp = (tmp & SUPC_MR_BODDIS) >> SUPC_MR_BODDIS_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_MR_BODDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp &= ~SUPC_MR_BODDIS;
	tmp |= value << SUPC_MR_BODDIS_Pos;
	((Supc *)hw)->SUPC_MR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_MR_BODDIS_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR &= ~SUPC_MR_BODDIS;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_MR_BODDIS_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR ^= SUPC_MR_BODDIS;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_MR_ONREG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR |= SUPC_MR_ONREG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_MR_ONREG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp = (tmp & SUPC_MR_ONREG) >> SUPC_MR_ONREG_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_MR_ONREG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp &= ~SUPC_MR_ONREG;
	tmp |= value << SUPC_MR_ONREG_Pos;
	((Supc *)hw)->SUPC_MR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_MR_ONREG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR &= ~SUPC_MR_ONREG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_MR_ONREG_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR ^= SUPC_MR_ONREG;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_MR_BKUPRETON_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR |= SUPC_MR_BKUPRETON;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_MR_BKUPRETON_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp = (tmp & SUPC_MR_BKUPRETON) >> SUPC_MR_BKUPRETON_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_MR_BKUPRETON_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp &= ~SUPC_MR_BKUPRETON;
	tmp |= value << SUPC_MR_BKUPRETON_Pos;
	((Supc *)hw)->SUPC_MR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_MR_BKUPRETON_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR &= ~SUPC_MR_BKUPRETON;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_MR_BKUPRETON_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR ^= SUPC_MR_BKUPRETON;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_MR_OSCBYPASS_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR |= SUPC_MR_OSCBYPASS;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_MR_OSCBYPASS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp = (tmp & SUPC_MR_OSCBYPASS) >> SUPC_MR_OSCBYPASS_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_MR_OSCBYPASS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp &= ~SUPC_MR_OSCBYPASS;
	tmp |= value << SUPC_MR_OSCBYPASS_Pos;
	((Supc *)hw)->SUPC_MR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_MR_OSCBYPASS_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR &= ~SUPC_MR_OSCBYPASS;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_MR_OSCBYPASS_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR ^= SUPC_MR_OSCBYPASS;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_MR_KEY_bf(const void *const hw, hri_supc_mr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR |= SUPC_MR_KEY(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_mr_reg_t hri_supc_get_MR_KEY_bf(const void *const hw, hri_supc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp = (tmp & SUPC_MR_KEY(mask)) >> SUPC_MR_KEY_Pos;
	return tmp;
}

static inline void hri_supc_write_MR_KEY_bf(const void *const hw, hri_supc_mr_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp &= ~SUPC_MR_KEY_Msk;
	tmp |= SUPC_MR_KEY(data);
	((Supc *)hw)->SUPC_MR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_MR_KEY_bf(const void *const hw, hri_supc_mr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR &= ~SUPC_MR_KEY(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_MR_KEY_bf(const void *const hw, hri_supc_mr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR ^= SUPC_MR_KEY(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_mr_reg_t hri_supc_read_MR_KEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp = (tmp & SUPC_MR_KEY_Msk) >> SUPC_MR_KEY_Pos;
	return tmp;
}

static inline void hri_supc_set_MR_reg(const void *const hw, hri_supc_mr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_mr_reg_t hri_supc_get_MR_reg(const void *const hw, hri_supc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_MR_reg(const void *const hw, hri_supc_mr_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_MR_reg(const void *const hw, hri_supc_mr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_MR_reg(const void *const hw, hri_supc_mr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_MR ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_mr_reg_t hri_supc_read_MR_reg(const void *const hw)
{
	return ((Supc *)hw)->SUPC_MR;
}

static inline void hri_supc_set_WUMR_SMEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR |= SUPC_WUMR_SMEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUMR_SMEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_SMEN) >> SUPC_WUMR_SMEN_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUMR_SMEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp &= ~SUPC_WUMR_SMEN;
	tmp |= value << SUPC_WUMR_SMEN_Pos;
	((Supc *)hw)->SUPC_WUMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUMR_SMEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR &= ~SUPC_WUMR_SMEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUMR_SMEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR ^= SUPC_WUMR_SMEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUMR_RTTEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR |= SUPC_WUMR_RTTEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUMR_RTTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_RTTEN) >> SUPC_WUMR_RTTEN_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUMR_RTTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp &= ~SUPC_WUMR_RTTEN;
	tmp |= value << SUPC_WUMR_RTTEN_Pos;
	((Supc *)hw)->SUPC_WUMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUMR_RTTEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR &= ~SUPC_WUMR_RTTEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUMR_RTTEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR ^= SUPC_WUMR_RTTEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUMR_RTCEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR |= SUPC_WUMR_RTCEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUMR_RTCEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_RTCEN) >> SUPC_WUMR_RTCEN_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUMR_RTCEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp &= ~SUPC_WUMR_RTCEN;
	tmp |= value << SUPC_WUMR_RTCEN_Pos;
	((Supc *)hw)->SUPC_WUMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUMR_RTCEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR &= ~SUPC_WUMR_RTCEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUMR_RTCEN_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR ^= SUPC_WUMR_RTCEN;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUMR_LPDBCEN0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR |= SUPC_WUMR_LPDBCEN0;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUMR_LPDBCEN0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_LPDBCEN0) >> SUPC_WUMR_LPDBCEN0_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUMR_LPDBCEN0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp &= ~SUPC_WUMR_LPDBCEN0;
	tmp |= value << SUPC_WUMR_LPDBCEN0_Pos;
	((Supc *)hw)->SUPC_WUMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUMR_LPDBCEN0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR &= ~SUPC_WUMR_LPDBCEN0;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUMR_LPDBCEN0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR ^= SUPC_WUMR_LPDBCEN0;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUMR_LPDBCEN1_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR |= SUPC_WUMR_LPDBCEN1;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUMR_LPDBCEN1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_LPDBCEN1) >> SUPC_WUMR_LPDBCEN1_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUMR_LPDBCEN1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp &= ~SUPC_WUMR_LPDBCEN1;
	tmp |= value << SUPC_WUMR_LPDBCEN1_Pos;
	((Supc *)hw)->SUPC_WUMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUMR_LPDBCEN1_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR &= ~SUPC_WUMR_LPDBCEN1;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUMR_LPDBCEN1_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR ^= SUPC_WUMR_LPDBCEN1;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUMR_LPDBCCLR_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR |= SUPC_WUMR_LPDBCCLR;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUMR_LPDBCCLR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_LPDBCCLR) >> SUPC_WUMR_LPDBCCLR_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUMR_LPDBCCLR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp &= ~SUPC_WUMR_LPDBCCLR;
	tmp |= value << SUPC_WUMR_LPDBCCLR_Pos;
	((Supc *)hw)->SUPC_WUMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUMR_LPDBCCLR_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR &= ~SUPC_WUMR_LPDBCCLR;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUMR_LPDBCCLR_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR ^= SUPC_WUMR_LPDBCCLR;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUMR_WKUPDBC_bf(const void *const hw, hri_supc_wumr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR |= SUPC_WUMR_WKUPDBC(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_wumr_reg_t hri_supc_get_WUMR_WKUPDBC_bf(const void *const hw, hri_supc_wumr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_WKUPDBC(mask)) >> SUPC_WUMR_WKUPDBC_Pos;
	return tmp;
}

static inline void hri_supc_write_WUMR_WKUPDBC_bf(const void *const hw, hri_supc_wumr_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp &= ~SUPC_WUMR_WKUPDBC_Msk;
	tmp |= SUPC_WUMR_WKUPDBC(data);
	((Supc *)hw)->SUPC_WUMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUMR_WKUPDBC_bf(const void *const hw, hri_supc_wumr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR &= ~SUPC_WUMR_WKUPDBC(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUMR_WKUPDBC_bf(const void *const hw, hri_supc_wumr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR ^= SUPC_WUMR_WKUPDBC(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_wumr_reg_t hri_supc_read_WUMR_WKUPDBC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_WKUPDBC_Msk) >> SUPC_WUMR_WKUPDBC_Pos;
	return tmp;
}

static inline void hri_supc_set_WUMR_LPDBC_bf(const void *const hw, hri_supc_wumr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR |= SUPC_WUMR_LPDBC(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_wumr_reg_t hri_supc_get_WUMR_LPDBC_bf(const void *const hw, hri_supc_wumr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_LPDBC(mask)) >> SUPC_WUMR_LPDBC_Pos;
	return tmp;
}

static inline void hri_supc_write_WUMR_LPDBC_bf(const void *const hw, hri_supc_wumr_reg_t data)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp &= ~SUPC_WUMR_LPDBC_Msk;
	tmp |= SUPC_WUMR_LPDBC(data);
	((Supc *)hw)->SUPC_WUMR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUMR_LPDBC_bf(const void *const hw, hri_supc_wumr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR &= ~SUPC_WUMR_LPDBC(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUMR_LPDBC_bf(const void *const hw, hri_supc_wumr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR ^= SUPC_WUMR_LPDBC(mask);
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_wumr_reg_t hri_supc_read_WUMR_LPDBC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp = (tmp & SUPC_WUMR_LPDBC_Msk) >> SUPC_WUMR_LPDBC_Pos;
	return tmp;
}

static inline void hri_supc_set_WUMR_reg(const void *const hw, hri_supc_wumr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_wumr_reg_t hri_supc_get_WUMR_reg(const void *const hw, hri_supc_wumr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_WUMR_reg(const void *const hw, hri_supc_wumr_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUMR_reg(const void *const hw, hri_supc_wumr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUMR_reg(const void *const hw, hri_supc_wumr_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUMR ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_wumr_reg_t hri_supc_read_WUMR_reg(const void *const hw)
{
	return ((Supc *)hw)->SUPC_WUMR;
}

static inline void hri_supc_set_WUIR_WKUPEN0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN0;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN0) >> SUPC_WUIR_WKUPEN0_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN0;
	tmp |= value << SUPC_WUIR_WKUPEN0_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN0;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN0;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN1_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN1;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN1) >> SUPC_WUIR_WKUPEN1_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN1;
	tmp |= value << SUPC_WUIR_WKUPEN1_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN1_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN1;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN1_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN1;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN2_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN2;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN2) >> SUPC_WUIR_WKUPEN2_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN2;
	tmp |= value << SUPC_WUIR_WKUPEN2_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN2_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN2;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN2_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN2;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN3_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN3;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN3) >> SUPC_WUIR_WKUPEN3_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN3;
	tmp |= value << SUPC_WUIR_WKUPEN3_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN3_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN3;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN3_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN3;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN4_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN4;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN4) >> SUPC_WUIR_WKUPEN4_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN4;
	tmp |= value << SUPC_WUIR_WKUPEN4_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN4_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN4;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN4_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN4;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN5_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN5;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN5) >> SUPC_WUIR_WKUPEN5_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN5;
	tmp |= value << SUPC_WUIR_WKUPEN5_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN5_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN5;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN5_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN5;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN6_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN6;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN6) >> SUPC_WUIR_WKUPEN6_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN6;
	tmp |= value << SUPC_WUIR_WKUPEN6_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN6_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN6;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN6_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN6;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN7_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN7;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN7) >> SUPC_WUIR_WKUPEN7_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN7;
	tmp |= value << SUPC_WUIR_WKUPEN7_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN7_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN7;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN7_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN7;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN8_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN8;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN8) >> SUPC_WUIR_WKUPEN8_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN8;
	tmp |= value << SUPC_WUIR_WKUPEN8_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN8_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN8;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN8_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN8;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN9_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN9;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN9) >> SUPC_WUIR_WKUPEN9_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN9;
	tmp |= value << SUPC_WUIR_WKUPEN9_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN9_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN9;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN9_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN9;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN10_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN10;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN10) >> SUPC_WUIR_WKUPEN10_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN10;
	tmp |= value << SUPC_WUIR_WKUPEN10_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN10_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN10;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN10_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN10;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN11_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN11;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN11) >> SUPC_WUIR_WKUPEN11_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN11;
	tmp |= value << SUPC_WUIR_WKUPEN11_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN11_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN11;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN11_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN11;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN12_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN12;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN12) >> SUPC_WUIR_WKUPEN12_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN12;
	tmp |= value << SUPC_WUIR_WKUPEN12_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN12_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN12;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN12_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN12;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPEN13_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPEN13;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPEN13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPEN13) >> SUPC_WUIR_WKUPEN13_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPEN13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPEN13;
	tmp |= value << SUPC_WUIR_WKUPEN13_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPEN13_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPEN13;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPEN13_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPEN13;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT0;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT0) >> SUPC_WUIR_WKUPT0_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT0;
	tmp |= value << SUPC_WUIR_WKUPT0_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT0;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT0_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT0;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT1_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT1;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT1) >> SUPC_WUIR_WKUPT1_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT1;
	tmp |= value << SUPC_WUIR_WKUPT1_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT1_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT1;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT1_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT1;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT2_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT2;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT2) >> SUPC_WUIR_WKUPT2_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT2;
	tmp |= value << SUPC_WUIR_WKUPT2_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT2_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT2;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT2_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT2;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT3_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT3;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT3) >> SUPC_WUIR_WKUPT3_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT3;
	tmp |= value << SUPC_WUIR_WKUPT3_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT3_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT3;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT3_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT3;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT4_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT4;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT4) >> SUPC_WUIR_WKUPT4_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT4;
	tmp |= value << SUPC_WUIR_WKUPT4_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT4_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT4;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT4_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT4;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT5_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT5;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT5) >> SUPC_WUIR_WKUPT5_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT5;
	tmp |= value << SUPC_WUIR_WKUPT5_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT5_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT5;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT5_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT5;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT6_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT6;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT6) >> SUPC_WUIR_WKUPT6_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT6;
	tmp |= value << SUPC_WUIR_WKUPT6_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT6_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT6;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT6_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT6;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT7_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT7;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT7) >> SUPC_WUIR_WKUPT7_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT7;
	tmp |= value << SUPC_WUIR_WKUPT7_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT7_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT7;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT7_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT7;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT8_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT8;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT8) >> SUPC_WUIR_WKUPT8_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT8;
	tmp |= value << SUPC_WUIR_WKUPT8_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT8_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT8;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT8_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT8;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT9_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT9;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT9) >> SUPC_WUIR_WKUPT9_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT9;
	tmp |= value << SUPC_WUIR_WKUPT9_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT9_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT9;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT9_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT9;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT10_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT10;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT10) >> SUPC_WUIR_WKUPT10_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT10;
	tmp |= value << SUPC_WUIR_WKUPT10_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT10_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT10;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT10_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT10;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT11_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT11;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT11) >> SUPC_WUIR_WKUPT11_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT11;
	tmp |= value << SUPC_WUIR_WKUPT11_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT11_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT11;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT11_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT11;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT12_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT12;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT12) >> SUPC_WUIR_WKUPT12_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT12;
	tmp |= value << SUPC_WUIR_WKUPT12_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT12_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT12;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT12_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT12;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_WKUPT13_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= SUPC_WUIR_WKUPT13;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_supc_get_WUIR_WKUPT13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp = (tmp & SUPC_WUIR_WKUPT13) >> SUPC_WUIR_WKUPT13_Pos;
	return (bool)tmp;
}

static inline void hri_supc_write_WUIR_WKUPT13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SUPC_CRITICAL_SECTION_ENTER();
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= ~SUPC_WUIR_WKUPT13;
	tmp |= value << SUPC_WUIR_WKUPT13_Pos;
	((Supc *)hw)->SUPC_WUIR = tmp;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_WKUPT13_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~SUPC_WUIR_WKUPT13;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_WKUPT13_bit(const void *const hw)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= SUPC_WUIR_WKUPT13;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_set_WUIR_reg(const void *const hw, hri_supc_wuir_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR |= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_wuir_reg_t hri_supc_get_WUIR_reg(const void *const hw, hri_supc_wuir_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Supc *)hw)->SUPC_WUIR;
	tmp &= mask;
	return tmp;
}

static inline void hri_supc_write_WUIR_reg(const void *const hw, hri_supc_wuir_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_clear_WUIR_reg(const void *const hw, hri_supc_wuir_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR &= ~mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_supc_toggle_WUIR_reg(const void *const hw, hri_supc_wuir_reg_t mask)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_WUIR ^= mask;
	SUPC_CRITICAL_SECTION_LEAVE();
}

static inline hri_supc_wuir_reg_t hri_supc_read_WUIR_reg(const void *const hw)
{
	return ((Supc *)hw)->SUPC_WUIR;
}

static inline void hri_supc_write_CR_reg(const void *const hw, hri_supc_cr_reg_t data)
{
	SUPC_CRITICAL_SECTION_ENTER();
	((Supc *)hw)->SUPC_CR = data;
	SUPC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SUPC_E70B_H_INCLUDED */
#endif /* _SAME70_SUPC_COMPONENT_ */
