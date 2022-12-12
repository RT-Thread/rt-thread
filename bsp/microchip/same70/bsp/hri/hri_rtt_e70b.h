/**
 * \file
 *
 * \brief SAM RTT
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

#ifdef _SAME70_RTT_COMPONENT_
#ifndef _HRI_RTT_E70B_H_INCLUDED_
#define _HRI_RTT_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_RTT_CRITICAL_SECTIONS)
#define RTT_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define RTT_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define RTT_CRITICAL_SECTION_ENTER()
#define RTT_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_rtt_ar_reg_t;
typedef uint32_t hri_rtt_mr_reg_t;
typedef uint32_t hri_rtt_sr_reg_t;
typedef uint32_t hri_rtt_vr_reg_t;

static inline hri_rtt_vr_reg_t hri_rtt_get_VR_CRTV_bf(const void *const hw, hri_rtt_vr_reg_t mask)
{
	return (((Rtt *)hw)->RTT_VR & RTT_VR_CRTV(mask)) >> RTT_VR_CRTV_Pos;
}

static inline hri_rtt_vr_reg_t hri_rtt_read_VR_CRTV_bf(const void *const hw)
{
	return (((Rtt *)hw)->RTT_VR & RTT_VR_CRTV_Msk) >> RTT_VR_CRTV_Pos;
}

static inline hri_rtt_vr_reg_t hri_rtt_get_VR_reg(const void *const hw, hri_rtt_vr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_VR;
	tmp &= mask;
	return tmp;
}

static inline hri_rtt_vr_reg_t hri_rtt_read_VR_reg(const void *const hw)
{
	return ((Rtt *)hw)->RTT_VR;
}

static inline bool hri_rtt_get_SR_ALMS_bit(const void *const hw)
{
	return (((Rtt *)hw)->RTT_SR & RTT_SR_ALMS) > 0;
}

static inline bool hri_rtt_get_SR_RTTINC_bit(const void *const hw)
{
	return (((Rtt *)hw)->RTT_SR & RTT_SR_RTTINC) > 0;
}

static inline hri_rtt_sr_reg_t hri_rtt_get_SR_reg(const void *const hw, hri_rtt_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_rtt_sr_reg_t hri_rtt_read_SR_reg(const void *const hw)
{
	return ((Rtt *)hw)->RTT_SR;
}

static inline void hri_rtt_set_MR_ALMIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_ALMIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_ALMIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_ALMIEN) >> RTT_MR_ALMIEN_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_ALMIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_ALMIEN;
	tmp |= value << RTT_MR_ALMIEN_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_ALMIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_ALMIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_ALMIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_ALMIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTTINCIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTTINCIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_RTTINCIEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTTINCIEN) >> RTT_MR_RTTINCIEN_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_RTTINCIEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTTINCIEN;
	tmp |= value << RTT_MR_RTTINCIEN_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTTINCIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTTINCIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTTINCIEN_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTTINCIEN;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTTRST_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTTRST;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_RTTRST_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTTRST) >> RTT_MR_RTTRST_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_RTTRST_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTTRST;
	tmp |= value << RTT_MR_RTTRST_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTTRST_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTTRST;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTTRST_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTTRST;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTTDIS_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTTDIS;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_RTTDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTTDIS) >> RTT_MR_RTTDIS_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_RTTDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTTDIS;
	tmp |= value << RTT_MR_RTTDIS_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTTDIS_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTTDIS;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTTDIS_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTTDIS;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTC1HZ_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTC1HZ;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtt_get_MR_RTC1HZ_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTC1HZ) >> RTT_MR_RTC1HZ_Pos;
	return (bool)tmp;
}

static inline void hri_rtt_write_MR_RTC1HZ_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTC1HZ;
	tmp |= value << RTT_MR_RTC1HZ_Pos;
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTC1HZ_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTC1HZ;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTC1HZ_bit(const void *const hw)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTC1HZ;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_set_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= RTT_MR_RTPRES(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_mr_reg_t hri_rtt_get_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTPRES(mask)) >> RTT_MR_RTPRES_Pos;
	return tmp;
}

static inline void hri_rtt_write_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t data)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= ~RTT_MR_RTPRES_Msk;
	tmp |= RTT_MR_RTPRES(data);
	((Rtt *)hw)->RTT_MR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~RTT_MR_RTPRES(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_RTPRES_bf(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= RTT_MR_RTPRES(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_mr_reg_t hri_rtt_read_MR_RTPRES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp = (tmp & RTT_MR_RTPRES_Msk) >> RTT_MR_RTPRES_Pos;
	return tmp;
}

static inline void hri_rtt_set_MR_reg(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR |= mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_mr_reg_t hri_rtt_get_MR_reg(const void *const hw, hri_rtt_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtt_write_MR_reg(const void *const hw, hri_rtt_mr_reg_t data)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR = data;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_MR_reg(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR &= ~mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_MR_reg(const void *const hw, hri_rtt_mr_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_MR ^= mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_mr_reg_t hri_rtt_read_MR_reg(const void *const hw)
{
	return ((Rtt *)hw)->RTT_MR;
}

static inline void hri_rtt_set_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR |= RTT_AR_ALMV(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_ar_reg_t hri_rtt_get_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_AR;
	tmp = (tmp & RTT_AR_ALMV(mask)) >> RTT_AR_ALMV_Pos;
	return tmp;
}

static inline void hri_rtt_write_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t data)
{
	uint32_t tmp;
	RTT_CRITICAL_SECTION_ENTER();
	tmp = ((Rtt *)hw)->RTT_AR;
	tmp &= ~RTT_AR_ALMV_Msk;
	tmp |= RTT_AR_ALMV(data);
	((Rtt *)hw)->RTT_AR = tmp;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR &= ~RTT_AR_ALMV(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_AR_ALMV_bf(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR ^= RTT_AR_ALMV(mask);
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_ar_reg_t hri_rtt_read_AR_ALMV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_AR;
	tmp = (tmp & RTT_AR_ALMV_Msk) >> RTT_AR_ALMV_Pos;
	return tmp;
}

static inline void hri_rtt_set_AR_reg(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR |= mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_ar_reg_t hri_rtt_get_AR_reg(const void *const hw, hri_rtt_ar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtt *)hw)->RTT_AR;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtt_write_AR_reg(const void *const hw, hri_rtt_ar_reg_t data)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR = data;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_clear_AR_reg(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR &= ~mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtt_toggle_AR_reg(const void *const hw, hri_rtt_ar_reg_t mask)
{
	RTT_CRITICAL_SECTION_ENTER();
	((Rtt *)hw)->RTT_AR ^= mask;
	RTT_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtt_ar_reg_t hri_rtt_read_AR_reg(const void *const hw)
{
	return ((Rtt *)hw)->RTT_AR;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RTT_E70B_H_INCLUDED */
#endif /* _SAME70_RTT_COMPONENT_ */
