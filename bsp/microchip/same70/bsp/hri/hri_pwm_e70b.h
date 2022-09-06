/**
 * \file
 *
 * \brief SAM PWM
 *
 * Copyright (c) 2017-2019 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAME70_PWM_COMPONENT_
#ifndef _HRI_PWM_E70B_H_INCLUDED_
#define _HRI_PWM_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_PWM_CRITICAL_SECTIONS)
#define PWM_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define PWM_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define PWM_CRITICAL_SECTION_ENTER()
#define PWM_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_pwm_ccnt_reg_t;
typedef uint32_t hri_pwm_cdty_reg_t;
typedef uint32_t hri_pwm_cdtyupd_reg_t;
typedef uint32_t hri_pwm_clk_reg_t;
typedef uint32_t hri_pwm_cmpm_reg_t;
typedef uint32_t hri_pwm_cmpmupd_reg_t;
typedef uint32_t hri_pwm_cmpv_reg_t;
typedef uint32_t hri_pwm_cmpvupd_reg_t;
typedef uint32_t hri_pwm_cmr_reg_t;
typedef uint32_t hri_pwm_cmupd0_reg_t;
typedef uint32_t hri_pwm_cmupd1_reg_t;
typedef uint32_t hri_pwm_cmupd2_reg_t;
typedef uint32_t hri_pwm_cmupd3_reg_t;
typedef uint32_t hri_pwm_cprd_reg_t;
typedef uint32_t hri_pwm_cprdupd_reg_t;
typedef uint32_t hri_pwm_dis_reg_t;
typedef uint32_t hri_pwm_dmar_reg_t;
typedef uint32_t hri_pwm_dt_reg_t;
typedef uint32_t hri_pwm_dtupd_reg_t;
typedef uint32_t hri_pwm_elmr_reg_t;
typedef uint32_t hri_pwm_ena_reg_t;
typedef uint32_t hri_pwm_etrg1_reg_t;
typedef uint32_t hri_pwm_etrg2_reg_t;
typedef uint32_t hri_pwm_fcr_reg_t;
typedef uint32_t hri_pwm_fmr_reg_t;
typedef uint32_t hri_pwm_fpe_reg_t;
typedef uint32_t hri_pwm_fpv1_reg_t;
typedef uint32_t hri_pwm_fpv2_reg_t;
typedef uint32_t hri_pwm_fsr_reg_t;
typedef uint32_t hri_pwm_imr1_reg_t;
typedef uint32_t hri_pwm_imr2_reg_t;
typedef uint32_t hri_pwm_isr1_reg_t;
typedef uint32_t hri_pwm_isr2_reg_t;
typedef uint32_t hri_pwm_lebr1_reg_t;
typedef uint32_t hri_pwm_lebr2_reg_t;
typedef uint32_t hri_pwm_oov_reg_t;
typedef uint32_t hri_pwm_os_reg_t;
typedef uint32_t hri_pwm_osc_reg_t;
typedef uint32_t hri_pwm_oscupd_reg_t;
typedef uint32_t hri_pwm_oss_reg_t;
typedef uint32_t hri_pwm_ossupd_reg_t;
typedef uint32_t hri_pwm_scm_reg_t;
typedef uint32_t hri_pwm_scuc_reg_t;
typedef uint32_t hri_pwm_scup_reg_t;
typedef uint32_t hri_pwm_scupupd_reg_t;
typedef uint32_t hri_pwm_smmr_reg_t;
typedef uint32_t hri_pwm_sr_reg_t;
typedef uint32_t hri_pwm_sspr_reg_t;
typedef uint32_t hri_pwm_sspup_reg_t;
typedef uint32_t hri_pwm_wpcr_reg_t;
typedef uint32_t hri_pwm_wpsr_reg_t;
typedef uint32_t hri_pwmch_num_ccnt_reg_t;
typedef uint32_t hri_pwmch_num_cdty_reg_t;
typedef uint32_t hri_pwmch_num_cdtyupd_reg_t;
typedef uint32_t hri_pwmch_num_cmr_reg_t;
typedef uint32_t hri_pwmch_num_cprd_reg_t;
typedef uint32_t hri_pwmch_num_cprdupd_reg_t;
typedef uint32_t hri_pwmch_num_dt_reg_t;
typedef uint32_t hri_pwmch_num_dtupd_reg_t;
typedef uint32_t hri_pwmcmp_cmpm_reg_t;
typedef uint32_t hri_pwmcmp_cmpmupd_reg_t;
typedef uint32_t hri_pwmcmp_cmpv_reg_t;
typedef uint32_t hri_pwmcmp_cmpvupd_reg_t;

static inline hri_pwm_ccnt_reg_t hri_pwmchnum_get_CCNT_CNT_bf(const void *const hw, hri_pwm_ccnt_reg_t mask)
{
	return (((PwmChNum *)hw)->PWM_CCNT & PWM_CCNT_CNT(mask)) >> PWM_CCNT_CNT_Pos;
}

static inline hri_pwm_ccnt_reg_t hri_pwmchnum_read_CCNT_CNT_bf(const void *const hw)
{
	return (((PwmChNum *)hw)->PWM_CCNT & PWM_CCNT_CNT_Msk) >> PWM_CCNT_CNT_Pos;
}

static inline hri_pwm_ccnt_reg_t hri_pwmchnum_get_CCNT_reg(const void *const hw, hri_pwm_ccnt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CCNT;
	tmp &= mask;
	return tmp;
}

static inline hri_pwm_ccnt_reg_t hri_pwmchnum_read_CCNT_reg(const void *const hw)
{
	return ((PwmChNum *)hw)->PWM_CCNT;
}

static inline void hri_pwmchnum_set_CMR_CALG_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_CALG;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_CALG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_CALG) >> PWM_CMR_CALG_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_CALG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_CALG;
	tmp |= value << PWM_CMR_CALG_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_CALG_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_CALG;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_CALG_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_CALG;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_CPOL_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_CPOL;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_CPOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_CPOL) >> PWM_CMR_CPOL_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_CPOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_CPOL;
	tmp |= value << PWM_CMR_CPOL_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_CPOL_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_CPOL;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_CPOL_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_CPOL;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_CES_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_CES;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_CES_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_CES) >> PWM_CMR_CES_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_CES_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_CES;
	tmp |= value << PWM_CMR_CES_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_CES_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_CES;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_CES_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_CES;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_UPDS_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_UPDS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_UPDS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_UPDS) >> PWM_CMR_UPDS_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_UPDS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_UPDS;
	tmp |= value << PWM_CMR_UPDS_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_UPDS_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_UPDS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_UPDS_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_UPDS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_DPOLI_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_DPOLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_DPOLI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_DPOLI) >> PWM_CMR_DPOLI_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_DPOLI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_DPOLI;
	tmp |= value << PWM_CMR_DPOLI_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_DPOLI_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_DPOLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_DPOLI_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_DPOLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_TCTS_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_TCTS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_TCTS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_TCTS) >> PWM_CMR_TCTS_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_TCTS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_TCTS;
	tmp |= value << PWM_CMR_TCTS_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_TCTS_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_TCTS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_TCTS_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_TCTS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_DTE_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_DTE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_DTE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_DTE) >> PWM_CMR_DTE_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_DTE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_DTE;
	tmp |= value << PWM_CMR_DTE_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_DTE_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_DTE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_DTE_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_DTE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_DTHI_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_DTHI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_DTHI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_DTHI) >> PWM_CMR_DTHI_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_DTHI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_DTHI;
	tmp |= value << PWM_CMR_DTHI_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_DTHI_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_DTHI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_DTHI_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_DTHI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_DTLI_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_DTLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_DTLI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_DTLI) >> PWM_CMR_DTLI_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_DTLI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_DTLI;
	tmp |= value << PWM_CMR_DTLI_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_DTLI_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_DTLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_DTLI_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_DTLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_PPM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_PPM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmchnum_get_CMR_PPM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_PPM) >> PWM_CMR_PPM_Pos;
	return (bool)tmp;
}

static inline void hri_pwmchnum_write_CMR_PPM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_PPM;
	tmp |= value << PWM_CMR_PPM_Pos;
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_PPM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_PPM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_PPM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_PPM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_set_CMR_CPRE_bf(const void *const hw, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= PWM_CMR_CPRE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmr_reg_t hri_pwmchnum_get_CMR_CPRE_bf(const void *const hw, hri_pwm_cmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_CPRE(mask)) >> PWM_CMR_CPRE_Pos;
	return tmp;
}

static inline void hri_pwmchnum_write_CMR_CPRE_bf(const void *const hw, hri_pwm_cmr_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= ~PWM_CMR_CPRE_Msk;
	tmp |= PWM_CMR_CPRE(data);
	((PwmChNum *)hw)->PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_CPRE_bf(const void *const hw, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~PWM_CMR_CPRE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_CPRE_bf(const void *const hw, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= PWM_CMR_CPRE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmr_reg_t hri_pwmchnum_read_CMR_CPRE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp = (tmp & PWM_CMR_CPRE_Msk) >> PWM_CMR_CPRE_Pos;
	return tmp;
}

static inline void hri_pwmchnum_set_CMR_reg(const void *const hw, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmr_reg_t hri_pwmchnum_get_CMR_reg(const void *const hw, hri_pwm_cmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwmchnum_write_CMR_reg(const void *const hw, hri_pwm_cmr_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CMR_reg(const void *const hw, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CMR_reg(const void *const hw, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CMR ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmr_reg_t hri_pwmchnum_read_CMR_reg(const void *const hw)
{
	return ((PwmChNum *)hw)->PWM_CMR;
}

static inline void hri_pwmchnum_set_CDTY_CDTY_bf(const void *const hw, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CDTY |= PWM_CDTY_CDTY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cdty_reg_t hri_pwmchnum_get_CDTY_CDTY_bf(const void *const hw, hri_pwm_cdty_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CDTY;
	tmp = (tmp & PWM_CDTY_CDTY(mask)) >> PWM_CDTY_CDTY_Pos;
	return tmp;
}

static inline void hri_pwmchnum_write_CDTY_CDTY_bf(const void *const hw, hri_pwm_cdty_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CDTY;
	tmp &= ~PWM_CDTY_CDTY_Msk;
	tmp |= PWM_CDTY_CDTY(data);
	((PwmChNum *)hw)->PWM_CDTY = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CDTY_CDTY_bf(const void *const hw, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CDTY &= ~PWM_CDTY_CDTY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CDTY_CDTY_bf(const void *const hw, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CDTY ^= PWM_CDTY_CDTY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cdty_reg_t hri_pwmchnum_read_CDTY_CDTY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CDTY;
	tmp = (tmp & PWM_CDTY_CDTY_Msk) >> PWM_CDTY_CDTY_Pos;
	return tmp;
}

static inline void hri_pwmchnum_set_CDTY_reg(const void *const hw, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CDTY |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cdty_reg_t hri_pwmchnum_get_CDTY_reg(const void *const hw, hri_pwm_cdty_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CDTY;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwmchnum_write_CDTY_reg(const void *const hw, hri_pwm_cdty_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CDTY = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CDTY_reg(const void *const hw, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CDTY &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CDTY_reg(const void *const hw, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CDTY ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cdty_reg_t hri_pwmchnum_read_CDTY_reg(const void *const hw)
{
	return ((PwmChNum *)hw)->PWM_CDTY;
}

static inline void hri_pwmchnum_set_CPRD_CPRD_bf(const void *const hw, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CPRD |= PWM_CPRD_CPRD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cprd_reg_t hri_pwmchnum_get_CPRD_CPRD_bf(const void *const hw, hri_pwm_cprd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CPRD;
	tmp = (tmp & PWM_CPRD_CPRD(mask)) >> PWM_CPRD_CPRD_Pos;
	return tmp;
}

static inline void hri_pwmchnum_write_CPRD_CPRD_bf(const void *const hw, hri_pwm_cprd_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_CPRD;
	tmp &= ~PWM_CPRD_CPRD_Msk;
	tmp |= PWM_CPRD_CPRD(data);
	((PwmChNum *)hw)->PWM_CPRD = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CPRD_CPRD_bf(const void *const hw, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CPRD &= ~PWM_CPRD_CPRD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CPRD_CPRD_bf(const void *const hw, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CPRD ^= PWM_CPRD_CPRD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cprd_reg_t hri_pwmchnum_read_CPRD_CPRD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CPRD;
	tmp = (tmp & PWM_CPRD_CPRD_Msk) >> PWM_CPRD_CPRD_Pos;
	return tmp;
}

static inline void hri_pwmchnum_set_CPRD_reg(const void *const hw, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CPRD |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cprd_reg_t hri_pwmchnum_get_CPRD_reg(const void *const hw, hri_pwm_cprd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_CPRD;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwmchnum_write_CPRD_reg(const void *const hw, hri_pwm_cprd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CPRD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_CPRD_reg(const void *const hw, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CPRD &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_CPRD_reg(const void *const hw, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CPRD ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cprd_reg_t hri_pwmchnum_read_CPRD_reg(const void *const hw)
{
	return ((PwmChNum *)hw)->PWM_CPRD;
}

static inline void hri_pwmchnum_set_DT_DTH_bf(const void *const hw, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT |= PWM_DT_DTH(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwmchnum_get_DT_DTH_bf(const void *const hw, hri_pwm_dt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_DT;
	tmp = (tmp & PWM_DT_DTH(mask)) >> PWM_DT_DTH_Pos;
	return tmp;
}

static inline void hri_pwmchnum_write_DT_DTH_bf(const void *const hw, hri_pwm_dt_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_DT;
	tmp &= ~PWM_DT_DTH_Msk;
	tmp |= PWM_DT_DTH(data);
	((PwmChNum *)hw)->PWM_DT = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_DT_DTH_bf(const void *const hw, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT &= ~PWM_DT_DTH(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_DT_DTH_bf(const void *const hw, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT ^= PWM_DT_DTH(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwmchnum_read_DT_DTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_DT;
	tmp = (tmp & PWM_DT_DTH_Msk) >> PWM_DT_DTH_Pos;
	return tmp;
}

static inline void hri_pwmchnum_set_DT_DTL_bf(const void *const hw, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT |= PWM_DT_DTL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwmchnum_get_DT_DTL_bf(const void *const hw, hri_pwm_dt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_DT;
	tmp = (tmp & PWM_DT_DTL(mask)) >> PWM_DT_DTL_Pos;
	return tmp;
}

static inline void hri_pwmchnum_write_DT_DTL_bf(const void *const hw, hri_pwm_dt_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmChNum *)hw)->PWM_DT;
	tmp &= ~PWM_DT_DTL_Msk;
	tmp |= PWM_DT_DTL(data);
	((PwmChNum *)hw)->PWM_DT = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_DT_DTL_bf(const void *const hw, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT &= ~PWM_DT_DTL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_DT_DTL_bf(const void *const hw, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT ^= PWM_DT_DTL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwmchnum_read_DT_DTL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_DT;
	tmp = (tmp & PWM_DT_DTL_Msk) >> PWM_DT_DTL_Pos;
	return tmp;
}

static inline void hri_pwmchnum_set_DT_reg(const void *const hw, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwmchnum_get_DT_reg(const void *const hw, hri_pwm_dt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmChNum *)hw)->PWM_DT;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwmchnum_write_DT_reg(const void *const hw, hri_pwm_dt_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_clear_DT_reg(const void *const hw, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_toggle_DT_reg(const void *const hw, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DT ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwmchnum_read_DT_reg(const void *const hw)
{
	return ((PwmChNum *)hw)->PWM_DT;
}

static inline void hri_pwmchnum_write_CDTYUPD_reg(const void *const hw, hri_pwm_cdtyupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CDTYUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_write_CPRDUPD_reg(const void *const hw, hri_pwm_cprdupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_CPRDUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmchnum_write_DTUPD_reg(const void *const hw, hri_pwm_dtupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmChNum *)hw)->PWM_DTUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_ccnt_reg_t hri_pwm_get_CCNT_CNT_bf(const void *const hw, uint8_t submodule_index,
                                                         hri_pwm_ccnt_reg_t mask)
{
	return (((Pwm *)hw)->PwmChNum[submodule_index].PWM_CCNT & PWM_CCNT_CNT(mask)) >> PWM_CCNT_CNT_Pos;
}

static inline hri_pwm_ccnt_reg_t hri_pwm_read_CCNT_CNT_bf(const void *const hw, uint8_t submodule_index)
{
	return (((Pwm *)hw)->PwmChNum[submodule_index].PWM_CCNT & PWM_CCNT_CNT_Msk) >> PWM_CCNT_CNT_Pos;
}

static inline hri_pwm_ccnt_reg_t hri_pwm_get_CCNT_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_pwm_ccnt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CCNT;
	tmp &= mask;
	return tmp;
}

static inline hri_pwm_ccnt_reg_t hri_pwm_read_CCNT_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CCNT;
}

static inline void hri_pwm_set_CMR_CALG_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_CALG;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_CALG_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_CALG) >> PWM_CMR_CALG_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_CALG_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_CALG;
	tmp |= value << PWM_CMR_CALG_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_CALG_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_CALG;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_CALG_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_CALG;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_CPOL_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_CPOL;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_CPOL_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_CPOL) >> PWM_CMR_CPOL_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_CPOL_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_CPOL;
	tmp |= value << PWM_CMR_CPOL_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_CPOL_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_CPOL;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_CPOL_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_CPOL;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_CES_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_CES;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_CES_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_CES) >> PWM_CMR_CES_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_CES_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_CES;
	tmp |= value << PWM_CMR_CES_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_CES_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_CES;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_CES_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_CES;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_UPDS_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_UPDS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_UPDS_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_UPDS) >> PWM_CMR_UPDS_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_UPDS_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_UPDS;
	tmp |= value << PWM_CMR_UPDS_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_UPDS_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_UPDS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_UPDS_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_UPDS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_DPOLI_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_DPOLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_DPOLI_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_DPOLI) >> PWM_CMR_DPOLI_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_DPOLI_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_DPOLI;
	tmp |= value << PWM_CMR_DPOLI_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_DPOLI_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_DPOLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_DPOLI_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_DPOLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_TCTS_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_TCTS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_TCTS_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_TCTS) >> PWM_CMR_TCTS_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_TCTS_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_TCTS;
	tmp |= value << PWM_CMR_TCTS_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_TCTS_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_TCTS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_TCTS_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_TCTS;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_DTE_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_DTE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_DTE_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_DTE) >> PWM_CMR_DTE_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_DTE_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_DTE;
	tmp |= value << PWM_CMR_DTE_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_DTE_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_DTE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_DTE_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_DTE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_DTHI_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_DTHI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_DTHI_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_DTHI) >> PWM_CMR_DTHI_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_DTHI_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_DTHI;
	tmp |= value << PWM_CMR_DTHI_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_DTHI_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_DTHI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_DTHI_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_DTHI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_DTLI_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_DTLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_DTLI_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_DTLI) >> PWM_CMR_DTLI_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_DTLI_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_DTLI;
	tmp |= value << PWM_CMR_DTLI_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_DTLI_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_DTLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_DTLI_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_DTLI;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_PPM_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_PPM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMR_PPM_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_PPM) >> PWM_CMR_PPM_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMR_PPM_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_PPM;
	tmp |= value << PWM_CMR_PPM_Pos;
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_PPM_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_PPM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_PPM_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_PPM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMR_CPRE_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= PWM_CMR_CPRE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmr_reg_t hri_pwm_get_CMR_CPRE_bf(const void *const hw, uint8_t submodule_index,
                                                        hri_pwm_cmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_CPRE(mask)) >> PWM_CMR_CPRE_Pos;
	return tmp;
}

static inline void hri_pwm_write_CMR_CPRE_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmr_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= ~PWM_CMR_CPRE_Msk;
	tmp |= PWM_CMR_CPRE(data);
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_CPRE_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~PWM_CMR_CPRE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_CPRE_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= PWM_CMR_CPRE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmr_reg_t hri_pwm_read_CMR_CPRE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp = (tmp & PWM_CMR_CPRE_Msk) >> PWM_CMR_CPRE_Pos;
	return tmp;
}

static inline void hri_pwm_set_CMR_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmr_reg_t hri_pwm_get_CMR_reg(const void *const hw, uint8_t submodule_index,
                                                    hri_pwm_cmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_CMR_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmr_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMR_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMR_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmr_reg_t hri_pwm_read_CMR_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CMR;
}

static inline void hri_pwm_set_CDTY_CDTY_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY |= PWM_CDTY_CDTY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cdty_reg_t hri_pwm_get_CDTY_CDTY_bf(const void *const hw, uint8_t submodule_index,
                                                          hri_pwm_cdty_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY;
	tmp = (tmp & PWM_CDTY_CDTY(mask)) >> PWM_CDTY_CDTY_Pos;
	return tmp;
}

static inline void hri_pwm_write_CDTY_CDTY_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cdty_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY;
	tmp &= ~PWM_CDTY_CDTY_Msk;
	tmp |= PWM_CDTY_CDTY(data);
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CDTY_CDTY_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY &= ~PWM_CDTY_CDTY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CDTY_CDTY_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY ^= PWM_CDTY_CDTY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cdty_reg_t hri_pwm_read_CDTY_CDTY_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY;
	tmp = (tmp & PWM_CDTY_CDTY_Msk) >> PWM_CDTY_CDTY_Pos;
	return tmp;
}

static inline void hri_pwm_set_CDTY_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cdty_reg_t hri_pwm_get_CDTY_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_pwm_cdty_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_CDTY_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cdty_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CDTY_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CDTY_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cdty_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cdty_reg_t hri_pwm_read_CDTY_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTY;
}

static inline void hri_pwm_set_CPRD_CPRD_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD |= PWM_CPRD_CPRD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cprd_reg_t hri_pwm_get_CPRD_CPRD_bf(const void *const hw, uint8_t submodule_index,
                                                          hri_pwm_cprd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD;
	tmp = (tmp & PWM_CPRD_CPRD(mask)) >> PWM_CPRD_CPRD_Pos;
	return tmp;
}

static inline void hri_pwm_write_CPRD_CPRD_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cprd_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD;
	tmp &= ~PWM_CPRD_CPRD_Msk;
	tmp |= PWM_CPRD_CPRD(data);
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CPRD_CPRD_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD &= ~PWM_CPRD_CPRD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CPRD_CPRD_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD ^= PWM_CPRD_CPRD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cprd_reg_t hri_pwm_read_CPRD_CPRD_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD;
	tmp = (tmp & PWM_CPRD_CPRD_Msk) >> PWM_CPRD_CPRD_Pos;
	return tmp;
}

static inline void hri_pwm_set_CPRD_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cprd_reg_t hri_pwm_get_CPRD_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_pwm_cprd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_CPRD_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cprd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CPRD_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CPRD_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cprd_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cprd_reg_t hri_pwm_read_CPRD_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRD;
}

static inline void hri_pwm_set_DT_DTH_bf(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT |= PWM_DT_DTH(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwm_get_DT_DTH_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_pwm_dt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT;
	tmp = (tmp & PWM_DT_DTH(mask)) >> PWM_DT_DTH_Pos;
	return tmp;
}

static inline void hri_pwm_write_DT_DTH_bf(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT;
	tmp &= ~PWM_DT_DTH_Msk;
	tmp |= PWM_DT_DTH(data);
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_DT_DTH_bf(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT &= ~PWM_DT_DTH(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_DT_DTH_bf(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT ^= PWM_DT_DTH(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwm_read_DT_DTH_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT;
	tmp = (tmp & PWM_DT_DTH_Msk) >> PWM_DT_DTH_Pos;
	return tmp;
}

static inline void hri_pwm_set_DT_DTL_bf(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT |= PWM_DT_DTL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwm_get_DT_DTL_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_pwm_dt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT;
	tmp = (tmp & PWM_DT_DTL(mask)) >> PWM_DT_DTL_Pos;
	return tmp;
}

static inline void hri_pwm_write_DT_DTL_bf(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT;
	tmp &= ~PWM_DT_DTL_Msk;
	tmp |= PWM_DT_DTL(data);
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_DT_DTL_bf(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT &= ~PWM_DT_DTL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_DT_DTL_bf(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT ^= PWM_DT_DTL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwm_read_DT_DTL_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT;
	tmp = (tmp & PWM_DT_DTL_Msk) >> PWM_DT_DTL_Pos;
	return tmp;
}

static inline void hri_pwm_set_DT_reg(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwm_get_DT_reg(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_DT_reg(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_DT_reg(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_DT_reg(const void *const hw, uint8_t submodule_index, hri_pwm_dt_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_dt_reg_t hri_pwm_read_DT_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Pwm *)hw)->PwmChNum[submodule_index].PWM_DT;
}

static inline void hri_pwm_write_CDTYUPD_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cdtyupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CDTYUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_CPRDUPD_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cprdupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_CPRDUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_DTUPD_reg(const void *const hw, uint8_t submodule_index, hri_pwm_dtupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmChNum[submodule_index].PWM_DTUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_set_CMPV_CVM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV |= PWM_CMPV_CVM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmcmp_get_CMPV_CVM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPV;
	tmp = (tmp & PWM_CMPV_CVM) >> PWM_CMPV_CVM_Pos;
	return (bool)tmp;
}

static inline void hri_pwmcmp_write_CMPV_CVM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmCmp *)hw)->PWM_CMPV;
	tmp &= ~PWM_CMPV_CVM;
	tmp |= value << PWM_CMPV_CVM_Pos;
	((PwmCmp *)hw)->PWM_CMPV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPV_CVM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV &= ~PWM_CMPV_CVM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPV_CVM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV ^= PWM_CMPV_CVM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_set_CMPV_CV_bf(const void *const hw, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV |= PWM_CMPV_CV(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpv_reg_t hri_pwmcmp_get_CMPV_CV_bf(const void *const hw, hri_pwm_cmpv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPV;
	tmp = (tmp & PWM_CMPV_CV(mask)) >> PWM_CMPV_CV_Pos;
	return tmp;
}

static inline void hri_pwmcmp_write_CMPV_CV_bf(const void *const hw, hri_pwm_cmpv_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmCmp *)hw)->PWM_CMPV;
	tmp &= ~PWM_CMPV_CV_Msk;
	tmp |= PWM_CMPV_CV(data);
	((PwmCmp *)hw)->PWM_CMPV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPV_CV_bf(const void *const hw, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV &= ~PWM_CMPV_CV(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPV_CV_bf(const void *const hw, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV ^= PWM_CMPV_CV(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpv_reg_t hri_pwmcmp_read_CMPV_CV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPV;
	tmp = (tmp & PWM_CMPV_CV_Msk) >> PWM_CMPV_CV_Pos;
	return tmp;
}

static inline void hri_pwmcmp_set_CMPV_reg(const void *const hw, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpv_reg_t hri_pwmcmp_get_CMPV_reg(const void *const hw, hri_pwm_cmpv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPV;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwmcmp_write_CMPV_reg(const void *const hw, hri_pwm_cmpv_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPV_reg(const void *const hw, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPV_reg(const void *const hw, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPV ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpv_reg_t hri_pwmcmp_read_CMPV_reg(const void *const hw)
{
	return ((PwmCmp *)hw)->PWM_CMPV;
}

static inline void hri_pwmcmp_set_CMPM_CEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM |= PWM_CMPM_CEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwmcmp_get_CMPM_CEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CEN) >> PWM_CMPM_CEN_Pos;
	return (bool)tmp;
}

static inline void hri_pwmcmp_write_CMPM_CEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp &= ~PWM_CMPM_CEN;
	tmp |= value << PWM_CMPM_CEN_Pos;
	((PwmCmp *)hw)->PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPM_CEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM &= ~PWM_CMPM_CEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPM_CEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM ^= PWM_CMPM_CEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_set_CMPM_CTR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM |= PWM_CMPM_CTR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_get_CMPM_CTR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CTR(mask)) >> PWM_CMPM_CTR_Pos;
	return tmp;
}

static inline void hri_pwmcmp_write_CMPM_CTR_bf(const void *const hw, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp &= ~PWM_CMPM_CTR_Msk;
	tmp |= PWM_CMPM_CTR(data);
	((PwmCmp *)hw)->PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPM_CTR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM &= ~PWM_CMPM_CTR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPM_CTR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM ^= PWM_CMPM_CTR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_read_CMPM_CTR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CTR_Msk) >> PWM_CMPM_CTR_Pos;
	return tmp;
}

static inline void hri_pwmcmp_set_CMPM_CPR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM |= PWM_CMPM_CPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_get_CMPM_CPR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CPR(mask)) >> PWM_CMPM_CPR_Pos;
	return tmp;
}

static inline void hri_pwmcmp_write_CMPM_CPR_bf(const void *const hw, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp &= ~PWM_CMPM_CPR_Msk;
	tmp |= PWM_CMPM_CPR(data);
	((PwmCmp *)hw)->PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPM_CPR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM &= ~PWM_CMPM_CPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPM_CPR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM ^= PWM_CMPM_CPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_read_CMPM_CPR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CPR_Msk) >> PWM_CMPM_CPR_Pos;
	return tmp;
}

static inline void hri_pwmcmp_set_CMPM_CPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM |= PWM_CMPM_CPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_get_CMPM_CPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CPRCNT(mask)) >> PWM_CMPM_CPRCNT_Pos;
	return tmp;
}

static inline void hri_pwmcmp_write_CMPM_CPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp &= ~PWM_CMPM_CPRCNT_Msk;
	tmp |= PWM_CMPM_CPRCNT(data);
	((PwmCmp *)hw)->PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPM_CPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM &= ~PWM_CMPM_CPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPM_CPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM ^= PWM_CMPM_CPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_read_CMPM_CPRCNT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CPRCNT_Msk) >> PWM_CMPM_CPRCNT_Pos;
	return tmp;
}

static inline void hri_pwmcmp_set_CMPM_CUPR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM |= PWM_CMPM_CUPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_get_CMPM_CUPR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CUPR(mask)) >> PWM_CMPM_CUPR_Pos;
	return tmp;
}

static inline void hri_pwmcmp_write_CMPM_CUPR_bf(const void *const hw, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp &= ~PWM_CMPM_CUPR_Msk;
	tmp |= PWM_CMPM_CUPR(data);
	((PwmCmp *)hw)->PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPM_CUPR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM &= ~PWM_CMPM_CUPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPM_CUPR_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM ^= PWM_CMPM_CUPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_read_CMPM_CUPR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CUPR_Msk) >> PWM_CMPM_CUPR_Pos;
	return tmp;
}

static inline void hri_pwmcmp_set_CMPM_CUPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM |= PWM_CMPM_CUPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_get_CMPM_CUPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CUPRCNT(mask)) >> PWM_CMPM_CUPRCNT_Pos;
	return tmp;
}

static inline void hri_pwmcmp_write_CMPM_CUPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp &= ~PWM_CMPM_CUPRCNT_Msk;
	tmp |= PWM_CMPM_CUPRCNT(data);
	((PwmCmp *)hw)->PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPM_CUPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM &= ~PWM_CMPM_CUPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPM_CUPRCNT_bf(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM ^= PWM_CMPM_CUPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_read_CMPM_CUPRCNT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CUPRCNT_Msk) >> PWM_CMPM_CUPRCNT_Pos;
	return tmp;
}

static inline void hri_pwmcmp_set_CMPM_reg(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_get_CMPM_reg(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((PwmCmp *)hw)->PWM_CMPM;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwmcmp_write_CMPM_reg(const void *const hw, hri_pwm_cmpm_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_clear_CMPM_reg(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_toggle_CMPM_reg(const void *const hw, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPM ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwmcmp_read_CMPM_reg(const void *const hw)
{
	return ((PwmCmp *)hw)->PWM_CMPM;
}

static inline void hri_pwmcmp_write_CMPVUPD_reg(const void *const hw, hri_pwm_cmpvupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPVUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwmcmp_write_CMPMUPD_reg(const void *const hw, hri_pwm_cmpmupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((PwmCmp *)hw)->PWM_CMPMUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMPV_CVM_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV |= PWM_CMPV_CVM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMPV_CVM_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV;
	tmp = (tmp & PWM_CMPV_CVM) >> PWM_CMPV_CVM_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMPV_CVM_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV;
	tmp &= ~PWM_CMPV_CVM;
	tmp |= value << PWM_CMPV_CVM_Pos;
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPV_CVM_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV &= ~PWM_CMPV_CVM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPV_CVM_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV ^= PWM_CMPV_CVM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMPV_CV_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV |= PWM_CMPV_CV(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpv_reg_t hri_pwm_get_CMPV_CV_bf(const void *const hw, uint8_t submodule_index,
                                                        hri_pwm_cmpv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV;
	tmp = (tmp & PWM_CMPV_CV(mask)) >> PWM_CMPV_CV_Pos;
	return tmp;
}

static inline void hri_pwm_write_CMPV_CV_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpv_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV;
	tmp &= ~PWM_CMPV_CV_Msk;
	tmp |= PWM_CMPV_CV(data);
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPV_CV_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV &= ~PWM_CMPV_CV(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPV_CV_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV ^= PWM_CMPV_CV(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpv_reg_t hri_pwm_read_CMPV_CV_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV;
	tmp = (tmp & PWM_CMPV_CV_Msk) >> PWM_CMPV_CV_Pos;
	return tmp;
}

static inline void hri_pwm_set_CMPV_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpv_reg_t hri_pwm_get_CMPV_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_pwm_cmpv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_CMPV_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpv_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPV_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPV_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpv_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpv_reg_t hri_pwm_read_CMPV_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPV;
}

static inline void hri_pwm_set_CMPM_CEN_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM |= PWM_CMPM_CEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_CMPM_CEN_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CEN) >> PWM_CMPM_CEN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_CMPM_CEN_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp &= ~PWM_CMPM_CEN;
	tmp |= value << PWM_CMPM_CEN_Pos;
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPM_CEN_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM &= ~PWM_CMPM_CEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPM_CEN_bit(const void *const hw, uint8_t submodule_index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM ^= PWM_CMPM_CEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_CMPM_CTR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM |= PWM_CMPM_CTR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_get_CMPM_CTR_bf(const void *const hw, uint8_t submodule_index,
                                                         hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CTR(mask)) >> PWM_CMPM_CTR_Pos;
	return tmp;
}

static inline void hri_pwm_write_CMPM_CTR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp &= ~PWM_CMPM_CTR_Msk;
	tmp |= PWM_CMPM_CTR(data);
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPM_CTR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM &= ~PWM_CMPM_CTR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPM_CTR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM ^= PWM_CMPM_CTR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_read_CMPM_CTR_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CTR_Msk) >> PWM_CMPM_CTR_Pos;
	return tmp;
}

static inline void hri_pwm_set_CMPM_CPR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM |= PWM_CMPM_CPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_get_CMPM_CPR_bf(const void *const hw, uint8_t submodule_index,
                                                         hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CPR(mask)) >> PWM_CMPM_CPR_Pos;
	return tmp;
}

static inline void hri_pwm_write_CMPM_CPR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp &= ~PWM_CMPM_CPR_Msk;
	tmp |= PWM_CMPM_CPR(data);
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPM_CPR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM &= ~PWM_CMPM_CPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPM_CPR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM ^= PWM_CMPM_CPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_read_CMPM_CPR_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CPR_Msk) >> PWM_CMPM_CPR_Pos;
	return tmp;
}

static inline void hri_pwm_set_CMPM_CPRCNT_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM |= PWM_CMPM_CPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_get_CMPM_CPRCNT_bf(const void *const hw, uint8_t submodule_index,
                                                            hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CPRCNT(mask)) >> PWM_CMPM_CPRCNT_Pos;
	return tmp;
}

static inline void hri_pwm_write_CMPM_CPRCNT_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp &= ~PWM_CMPM_CPRCNT_Msk;
	tmp |= PWM_CMPM_CPRCNT(data);
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPM_CPRCNT_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM &= ~PWM_CMPM_CPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPM_CPRCNT_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM ^= PWM_CMPM_CPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_read_CMPM_CPRCNT_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CPRCNT_Msk) >> PWM_CMPM_CPRCNT_Pos;
	return tmp;
}

static inline void hri_pwm_set_CMPM_CUPR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM |= PWM_CMPM_CUPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_get_CMPM_CUPR_bf(const void *const hw, uint8_t submodule_index,
                                                          hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CUPR(mask)) >> PWM_CMPM_CUPR_Pos;
	return tmp;
}

static inline void hri_pwm_write_CMPM_CUPR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp &= ~PWM_CMPM_CUPR_Msk;
	tmp |= PWM_CMPM_CUPR(data);
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPM_CUPR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM &= ~PWM_CMPM_CUPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPM_CUPR_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM ^= PWM_CMPM_CUPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_read_CMPM_CUPR_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CUPR_Msk) >> PWM_CMPM_CUPR_Pos;
	return tmp;
}

static inline void hri_pwm_set_CMPM_CUPRCNT_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM |= PWM_CMPM_CUPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_get_CMPM_CUPRCNT_bf(const void *const hw, uint8_t submodule_index,
                                                             hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CUPRCNT(mask)) >> PWM_CMPM_CUPRCNT_Pos;
	return tmp;
}

static inline void hri_pwm_write_CMPM_CUPRCNT_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp &= ~PWM_CMPM_CUPRCNT_Msk;
	tmp |= PWM_CMPM_CUPRCNT(data);
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPM_CUPRCNT_bf(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM &= ~PWM_CMPM_CUPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPM_CUPRCNT_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM ^= PWM_CMPM_CUPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_read_CMPM_CUPRCNT_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp = (tmp & PWM_CMPM_CUPRCNT_Msk) >> PWM_CMPM_CUPRCNT_Pos;
	return tmp;
}

static inline void hri_pwm_set_CMPM_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_get_CMPM_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_pwm_cmpm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_CMPM_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CMPM_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CMPM_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_cmpm_reg_t hri_pwm_read_CMPM_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPM;
}

static inline void hri_pwm_write_CMPVUPD_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpvupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPVUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_CMPMUPD_reg(const void *const hw, uint8_t submodule_index, hri_pwm_cmpmupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PwmCmp[submodule_index].PWM_CMPMUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ISR1_CHID0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR1 & PWM_ISR1_CHID0) >> PWM_ISR1_CHID0_Pos;
}

static inline bool hri_pwm_get_ISR1_CHID1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR1 & PWM_ISR1_CHID1) >> PWM_ISR1_CHID1_Pos;
}

static inline bool hri_pwm_get_ISR1_CHID2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR1 & PWM_ISR1_CHID2) >> PWM_ISR1_CHID2_Pos;
}

static inline bool hri_pwm_get_ISR1_CHID3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR1 & PWM_ISR1_CHID3) >> PWM_ISR1_CHID3_Pos;
}

static inline bool hri_pwm_get_ISR1_FCHID0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR1 & PWM_ISR1_FCHID0) >> PWM_ISR1_FCHID0_Pos;
}

static inline bool hri_pwm_get_ISR1_FCHID1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR1 & PWM_ISR1_FCHID1) >> PWM_ISR1_FCHID1_Pos;
}

static inline bool hri_pwm_get_ISR1_FCHID2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR1 & PWM_ISR1_FCHID2) >> PWM_ISR1_FCHID2_Pos;
}

static inline bool hri_pwm_get_ISR1_FCHID3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR1 & PWM_ISR1_FCHID3) >> PWM_ISR1_FCHID3_Pos;
}

static inline hri_pwm_isr1_reg_t hri_pwm_get_ISR1_reg(const void *const hw, hri_pwm_isr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ISR1;
	tmp &= mask;
	return tmp;
}

static inline hri_pwm_isr1_reg_t hri_pwm_read_ISR1_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_ISR1;
}

static inline bool hri_pwm_get_ISR2_WRDY_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_WRDY) >> PWM_ISR2_WRDY_Pos;
}

static inline bool hri_pwm_get_ISR2_UNRE_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_UNRE) >> PWM_ISR2_UNRE_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPM0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPM0) >> PWM_ISR2_CMPM0_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPM1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPM1) >> PWM_ISR2_CMPM1_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPM2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPM2) >> PWM_ISR2_CMPM2_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPM3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPM3) >> PWM_ISR2_CMPM3_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPM4_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPM4) >> PWM_ISR2_CMPM4_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPM5_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPM5) >> PWM_ISR2_CMPM5_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPM6_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPM6) >> PWM_ISR2_CMPM6_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPM7_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPM7) >> PWM_ISR2_CMPM7_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPU0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPU0) >> PWM_ISR2_CMPU0_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPU1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPU1) >> PWM_ISR2_CMPU1_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPU2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPU2) >> PWM_ISR2_CMPU2_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPU3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPU3) >> PWM_ISR2_CMPU3_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPU4_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPU4) >> PWM_ISR2_CMPU4_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPU5_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPU5) >> PWM_ISR2_CMPU5_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPU6_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPU6) >> PWM_ISR2_CMPU6_Pos;
}

static inline bool hri_pwm_get_ISR2_CMPU7_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_ISR2 & PWM_ISR2_CMPU7) >> PWM_ISR2_CMPU7_Pos;
}

static inline hri_pwm_isr2_reg_t hri_pwm_get_ISR2_reg(const void *const hw, hri_pwm_isr2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ISR2;
	tmp &= mask;
	return tmp;
}

static inline hri_pwm_isr2_reg_t hri_pwm_read_ISR2_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_ISR2;
}

static inline void hri_pwm_set_IMR1_CHID0_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER1 = PWM_IMR1_CHID0;
}

static inline bool hri_pwm_get_IMR1_CHID0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR1 & PWM_IMR1_CHID0) >> PWM_IMR1_CHID0_Pos;
}

static inline void hri_pwm_write_IMR1_CHID0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_CHID0;
	} else {
		((Pwm *)hw)->PWM_IER1 = PWM_IMR1_CHID0;
	}
}

static inline void hri_pwm_clear_IMR1_CHID0_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_CHID0;
}

static inline void hri_pwm_set_IMR1_CHID1_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER1 = PWM_IMR1_CHID1;
}

static inline bool hri_pwm_get_IMR1_CHID1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR1 & PWM_IMR1_CHID1) >> PWM_IMR1_CHID1_Pos;
}

static inline void hri_pwm_write_IMR1_CHID1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_CHID1;
	} else {
		((Pwm *)hw)->PWM_IER1 = PWM_IMR1_CHID1;
	}
}

static inline void hri_pwm_clear_IMR1_CHID1_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_CHID1;
}

static inline void hri_pwm_set_IMR1_CHID2_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER1 = PWM_IMR1_CHID2;
}

static inline bool hri_pwm_get_IMR1_CHID2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR1 & PWM_IMR1_CHID2) >> PWM_IMR1_CHID2_Pos;
}

static inline void hri_pwm_write_IMR1_CHID2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_CHID2;
	} else {
		((Pwm *)hw)->PWM_IER1 = PWM_IMR1_CHID2;
	}
}

static inline void hri_pwm_clear_IMR1_CHID2_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_CHID2;
}

static inline void hri_pwm_set_IMR1_CHID3_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER1 = PWM_IMR1_CHID3;
}

static inline bool hri_pwm_get_IMR1_CHID3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR1 & PWM_IMR1_CHID3) >> PWM_IMR1_CHID3_Pos;
}

static inline void hri_pwm_write_IMR1_CHID3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_CHID3;
	} else {
		((Pwm *)hw)->PWM_IER1 = PWM_IMR1_CHID3;
	}
}

static inline void hri_pwm_clear_IMR1_CHID3_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_CHID3;
}

static inline void hri_pwm_set_IMR1_FCHID0_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER1 = PWM_IMR1_FCHID0;
}

static inline bool hri_pwm_get_IMR1_FCHID0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR1 & PWM_IMR1_FCHID0) >> PWM_IMR1_FCHID0_Pos;
}

static inline void hri_pwm_write_IMR1_FCHID0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_FCHID0;
	} else {
		((Pwm *)hw)->PWM_IER1 = PWM_IMR1_FCHID0;
	}
}

static inline void hri_pwm_clear_IMR1_FCHID0_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_FCHID0;
}

static inline void hri_pwm_set_IMR1_FCHID1_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER1 = PWM_IMR1_FCHID1;
}

static inline bool hri_pwm_get_IMR1_FCHID1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR1 & PWM_IMR1_FCHID1) >> PWM_IMR1_FCHID1_Pos;
}

static inline void hri_pwm_write_IMR1_FCHID1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_FCHID1;
	} else {
		((Pwm *)hw)->PWM_IER1 = PWM_IMR1_FCHID1;
	}
}

static inline void hri_pwm_clear_IMR1_FCHID1_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_FCHID1;
}

static inline void hri_pwm_set_IMR1_FCHID2_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER1 = PWM_IMR1_FCHID2;
}

static inline bool hri_pwm_get_IMR1_FCHID2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR1 & PWM_IMR1_FCHID2) >> PWM_IMR1_FCHID2_Pos;
}

static inline void hri_pwm_write_IMR1_FCHID2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_FCHID2;
	} else {
		((Pwm *)hw)->PWM_IER1 = PWM_IMR1_FCHID2;
	}
}

static inline void hri_pwm_clear_IMR1_FCHID2_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_FCHID2;
}

static inline void hri_pwm_set_IMR1_FCHID3_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER1 = PWM_IMR1_FCHID3;
}

static inline bool hri_pwm_get_IMR1_FCHID3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR1 & PWM_IMR1_FCHID3) >> PWM_IMR1_FCHID3_Pos;
}

static inline void hri_pwm_write_IMR1_FCHID3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_FCHID3;
	} else {
		((Pwm *)hw)->PWM_IER1 = PWM_IMR1_FCHID3;
	}
}

static inline void hri_pwm_clear_IMR1_FCHID3_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR1 = PWM_IMR1_FCHID3;
}

static inline void hri_pwm_set_IMR1_reg(const void *const hw, hri_pwm_imr1_reg_t mask)
{
	((Pwm *)hw)->PWM_IER1 = mask;
}

static inline hri_pwm_imr1_reg_t hri_pwm_get_IMR1_reg(const void *const hw, hri_pwm_imr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_IMR1;
	tmp &= mask;
	return tmp;
}

static inline hri_pwm_imr1_reg_t hri_pwm_read_IMR1_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_IMR1;
}

static inline void hri_pwm_write_IMR1_reg(const void *const hw, hri_pwm_imr1_reg_t data)
{
	((Pwm *)hw)->PWM_IER1 = data;
	((Pwm *)hw)->PWM_IDR1 = ~data;
}

static inline void hri_pwm_clear_IMR1_reg(const void *const hw, hri_pwm_imr1_reg_t mask)
{
	((Pwm *)hw)->PWM_IDR1 = mask;
}

static inline void hri_pwm_set_IMR2_WRDY_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_WRDY;
}

static inline bool hri_pwm_get_IMR2_WRDY_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_WRDY) >> PWM_IMR2_WRDY_Pos;
}

static inline void hri_pwm_write_IMR2_WRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_WRDY;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_WRDY;
	}
}

static inline void hri_pwm_clear_IMR2_WRDY_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_WRDY;
}

static inline void hri_pwm_set_IMR2_UNRE_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_UNRE;
}

static inline bool hri_pwm_get_IMR2_UNRE_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_UNRE) >> PWM_IMR2_UNRE_Pos;
}

static inline void hri_pwm_write_IMR2_UNRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_UNRE;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_UNRE;
	}
}

static inline void hri_pwm_clear_IMR2_UNRE_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_UNRE;
}

static inline void hri_pwm_set_IMR2_CMPM0_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM0;
}

static inline bool hri_pwm_get_IMR2_CMPM0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPM0) >> PWM_IMR2_CMPM0_Pos;
}

static inline void hri_pwm_write_IMR2_CMPM0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM0;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM0;
	}
}

static inline void hri_pwm_clear_IMR2_CMPM0_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM0;
}

static inline void hri_pwm_set_IMR2_CMPM1_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM1;
}

static inline bool hri_pwm_get_IMR2_CMPM1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPM1) >> PWM_IMR2_CMPM1_Pos;
}

static inline void hri_pwm_write_IMR2_CMPM1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM1;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM1;
	}
}

static inline void hri_pwm_clear_IMR2_CMPM1_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM1;
}

static inline void hri_pwm_set_IMR2_CMPM2_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM2;
}

static inline bool hri_pwm_get_IMR2_CMPM2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPM2) >> PWM_IMR2_CMPM2_Pos;
}

static inline void hri_pwm_write_IMR2_CMPM2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM2;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM2;
	}
}

static inline void hri_pwm_clear_IMR2_CMPM2_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM2;
}

static inline void hri_pwm_set_IMR2_CMPM3_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM3;
}

static inline bool hri_pwm_get_IMR2_CMPM3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPM3) >> PWM_IMR2_CMPM3_Pos;
}

static inline void hri_pwm_write_IMR2_CMPM3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM3;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM3;
	}
}

static inline void hri_pwm_clear_IMR2_CMPM3_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM3;
}

static inline void hri_pwm_set_IMR2_CMPM4_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM4;
}

static inline bool hri_pwm_get_IMR2_CMPM4_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPM4) >> PWM_IMR2_CMPM4_Pos;
}

static inline void hri_pwm_write_IMR2_CMPM4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM4;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM4;
	}
}

static inline void hri_pwm_clear_IMR2_CMPM4_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM4;
}

static inline void hri_pwm_set_IMR2_CMPM5_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM5;
}

static inline bool hri_pwm_get_IMR2_CMPM5_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPM5) >> PWM_IMR2_CMPM5_Pos;
}

static inline void hri_pwm_write_IMR2_CMPM5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM5;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM5;
	}
}

static inline void hri_pwm_clear_IMR2_CMPM5_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM5;
}

static inline void hri_pwm_set_IMR2_CMPM6_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM6;
}

static inline bool hri_pwm_get_IMR2_CMPM6_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPM6) >> PWM_IMR2_CMPM6_Pos;
}

static inline void hri_pwm_write_IMR2_CMPM6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM6;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM6;
	}
}

static inline void hri_pwm_clear_IMR2_CMPM6_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM6;
}

static inline void hri_pwm_set_IMR2_CMPM7_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM7;
}

static inline bool hri_pwm_get_IMR2_CMPM7_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPM7) >> PWM_IMR2_CMPM7_Pos;
}

static inline void hri_pwm_write_IMR2_CMPM7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM7;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPM7;
	}
}

static inline void hri_pwm_clear_IMR2_CMPM7_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPM7;
}

static inline void hri_pwm_set_IMR2_CMPU0_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU0;
}

static inline bool hri_pwm_get_IMR2_CMPU0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPU0) >> PWM_IMR2_CMPU0_Pos;
}

static inline void hri_pwm_write_IMR2_CMPU0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU0;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU0;
	}
}

static inline void hri_pwm_clear_IMR2_CMPU0_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU0;
}

static inline void hri_pwm_set_IMR2_CMPU1_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU1;
}

static inline bool hri_pwm_get_IMR2_CMPU1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPU1) >> PWM_IMR2_CMPU1_Pos;
}

static inline void hri_pwm_write_IMR2_CMPU1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU1;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU1;
	}
}

static inline void hri_pwm_clear_IMR2_CMPU1_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU1;
}

static inline void hri_pwm_set_IMR2_CMPU2_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU2;
}

static inline bool hri_pwm_get_IMR2_CMPU2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPU2) >> PWM_IMR2_CMPU2_Pos;
}

static inline void hri_pwm_write_IMR2_CMPU2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU2;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU2;
	}
}

static inline void hri_pwm_clear_IMR2_CMPU2_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU2;
}

static inline void hri_pwm_set_IMR2_CMPU3_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU3;
}

static inline bool hri_pwm_get_IMR2_CMPU3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPU3) >> PWM_IMR2_CMPU3_Pos;
}

static inline void hri_pwm_write_IMR2_CMPU3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU3;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU3;
	}
}

static inline void hri_pwm_clear_IMR2_CMPU3_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU3;
}

static inline void hri_pwm_set_IMR2_CMPU4_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU4;
}

static inline bool hri_pwm_get_IMR2_CMPU4_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPU4) >> PWM_IMR2_CMPU4_Pos;
}

static inline void hri_pwm_write_IMR2_CMPU4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU4;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU4;
	}
}

static inline void hri_pwm_clear_IMR2_CMPU4_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU4;
}

static inline void hri_pwm_set_IMR2_CMPU5_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU5;
}

static inline bool hri_pwm_get_IMR2_CMPU5_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPU5) >> PWM_IMR2_CMPU5_Pos;
}

static inline void hri_pwm_write_IMR2_CMPU5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU5;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU5;
	}
}

static inline void hri_pwm_clear_IMR2_CMPU5_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU5;
}

static inline void hri_pwm_set_IMR2_CMPU6_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU6;
}

static inline bool hri_pwm_get_IMR2_CMPU6_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPU6) >> PWM_IMR2_CMPU6_Pos;
}

static inline void hri_pwm_write_IMR2_CMPU6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU6;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU6;
	}
}

static inline void hri_pwm_clear_IMR2_CMPU6_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU6;
}

static inline void hri_pwm_set_IMR2_CMPU7_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU7;
}

static inline bool hri_pwm_get_IMR2_CMPU7_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_IMR2 & PWM_IMR2_CMPU7) >> PWM_IMR2_CMPU7_Pos;
}

static inline void hri_pwm_write_IMR2_CMPU7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU7;
	} else {
		((Pwm *)hw)->PWM_IER2 = PWM_IMR2_CMPU7;
	}
}

static inline void hri_pwm_clear_IMR2_CMPU7_bit(const void *const hw)
{
	((Pwm *)hw)->PWM_IDR2 = PWM_IMR2_CMPU7;
}

static inline void hri_pwm_set_IMR2_reg(const void *const hw, hri_pwm_imr2_reg_t mask)
{
	((Pwm *)hw)->PWM_IER2 = mask;
}

static inline hri_pwm_imr2_reg_t hri_pwm_get_IMR2_reg(const void *const hw, hri_pwm_imr2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_IMR2;
	tmp &= mask;
	return tmp;
}

static inline hri_pwm_imr2_reg_t hri_pwm_read_IMR2_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_IMR2;
}

static inline void hri_pwm_write_IMR2_reg(const void *const hw, hri_pwm_imr2_reg_t data)
{
	((Pwm *)hw)->PWM_IER2 = data;
	((Pwm *)hw)->PWM_IDR2 = ~data;
}

static inline void hri_pwm_clear_IMR2_reg(const void *const hw, hri_pwm_imr2_reg_t mask)
{
	((Pwm *)hw)->PWM_IDR2 = mask;
}

static inline bool hri_pwm_get_SR_CHID0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_SR & PWM_SR_CHID0) > 0;
}

static inline bool hri_pwm_get_SR_CHID1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_SR & PWM_SR_CHID1) > 0;
}

static inline bool hri_pwm_get_SR_CHID2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_SR & PWM_SR_CHID2) > 0;
}

static inline bool hri_pwm_get_SR_CHID3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_SR & PWM_SR_CHID3) > 0;
}

static inline hri_pwm_sr_reg_t hri_pwm_get_SR_reg(const void *const hw, hri_pwm_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_pwm_sr_reg_t hri_pwm_read_SR_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_SR;
}

static inline hri_pwm_fsr_reg_t hri_pwm_get_FSR_FIV_bf(const void *const hw, hri_pwm_fsr_reg_t mask)
{
	return (((Pwm *)hw)->PWM_FSR & PWM_FSR_FIV(mask)) >> PWM_FSR_FIV_Pos;
}

static inline hri_pwm_fsr_reg_t hri_pwm_read_FSR_FIV_bf(const void *const hw)
{
	return (((Pwm *)hw)->PWM_FSR & PWM_FSR_FIV_Msk) >> PWM_FSR_FIV_Pos;
}

static inline hri_pwm_fsr_reg_t hri_pwm_get_FSR_FS_bf(const void *const hw, hri_pwm_fsr_reg_t mask)
{
	return (((Pwm *)hw)->PWM_FSR & PWM_FSR_FS(mask)) >> PWM_FSR_FS_Pos;
}

static inline hri_pwm_fsr_reg_t hri_pwm_read_FSR_FS_bf(const void *const hw)
{
	return (((Pwm *)hw)->PWM_FSR & PWM_FSR_FS_Msk) >> PWM_FSR_FS_Pos;
}

static inline hri_pwm_fsr_reg_t hri_pwm_get_FSR_reg(const void *const hw, hri_pwm_fsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pwm_fsr_reg_t hri_pwm_read_FSR_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_FSR;
}

static inline bool hri_pwm_get_WPSR_WPSWS0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPSWS0) > 0;
}

static inline bool hri_pwm_get_WPSR_WPSWS1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPSWS1) > 0;
}

static inline bool hri_pwm_get_WPSR_WPSWS2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPSWS2) > 0;
}

static inline bool hri_pwm_get_WPSR_WPSWS3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPSWS3) > 0;
}

static inline bool hri_pwm_get_WPSR_WPSWS4_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPSWS4) > 0;
}

static inline bool hri_pwm_get_WPSR_WPSWS5_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPSWS5) > 0;
}

static inline bool hri_pwm_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPVS) > 0;
}

static inline bool hri_pwm_get_WPSR_WPHWS0_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPHWS0) > 0;
}

static inline bool hri_pwm_get_WPSR_WPHWS1_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPHWS1) > 0;
}

static inline bool hri_pwm_get_WPSR_WPHWS2_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPHWS2) > 0;
}

static inline bool hri_pwm_get_WPSR_WPHWS3_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPHWS3) > 0;
}

static inline bool hri_pwm_get_WPSR_WPHWS4_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPHWS4) > 0;
}

static inline bool hri_pwm_get_WPSR_WPHWS5_bit(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPHWS5) > 0;
}

static inline hri_pwm_wpsr_reg_t hri_pwm_get_WPSR_WPVSRC_bf(const void *const hw, hri_pwm_wpsr_reg_t mask)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPVSRC(mask)) >> PWM_WPSR_WPVSRC_Pos;
}

static inline hri_pwm_wpsr_reg_t hri_pwm_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Pwm *)hw)->PWM_WPSR & PWM_WPSR_WPVSRC_Msk) >> PWM_WPSR_WPVSRC_Pos;
}

static inline hri_pwm_wpsr_reg_t hri_pwm_get_WPSR_reg(const void *const hw, hri_pwm_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pwm_wpsr_reg_t hri_pwm_read_WPSR_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_WPSR;
}

static inline void hri_pwm_set_CLK_DIVA_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK |= PWM_CLK_DIVA(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_get_CLK_DIVA_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp = (tmp & PWM_CLK_DIVA(mask)) >> PWM_CLK_DIVA_Pos;
	return tmp;
}

static inline void hri_pwm_write_CLK_DIVA_bf(const void *const hw, hri_pwm_clk_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp &= ~PWM_CLK_DIVA_Msk;
	tmp |= PWM_CLK_DIVA(data);
	((Pwm *)hw)->PWM_CLK = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CLK_DIVA_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK &= ~PWM_CLK_DIVA(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CLK_DIVA_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK ^= PWM_CLK_DIVA(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_read_CLK_DIVA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp = (tmp & PWM_CLK_DIVA_Msk) >> PWM_CLK_DIVA_Pos;
	return tmp;
}

static inline void hri_pwm_set_CLK_PREA_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK |= PWM_CLK_PREA(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_get_CLK_PREA_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp = (tmp & PWM_CLK_PREA(mask)) >> PWM_CLK_PREA_Pos;
	return tmp;
}

static inline void hri_pwm_write_CLK_PREA_bf(const void *const hw, hri_pwm_clk_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp &= ~PWM_CLK_PREA_Msk;
	tmp |= PWM_CLK_PREA(data);
	((Pwm *)hw)->PWM_CLK = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CLK_PREA_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK &= ~PWM_CLK_PREA(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CLK_PREA_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK ^= PWM_CLK_PREA(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_read_CLK_PREA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp = (tmp & PWM_CLK_PREA_Msk) >> PWM_CLK_PREA_Pos;
	return tmp;
}

static inline void hri_pwm_set_CLK_DIVB_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK |= PWM_CLK_DIVB(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_get_CLK_DIVB_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp = (tmp & PWM_CLK_DIVB(mask)) >> PWM_CLK_DIVB_Pos;
	return tmp;
}

static inline void hri_pwm_write_CLK_DIVB_bf(const void *const hw, hri_pwm_clk_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp &= ~PWM_CLK_DIVB_Msk;
	tmp |= PWM_CLK_DIVB(data);
	((Pwm *)hw)->PWM_CLK = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CLK_DIVB_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK &= ~PWM_CLK_DIVB(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CLK_DIVB_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK ^= PWM_CLK_DIVB(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_read_CLK_DIVB_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp = (tmp & PWM_CLK_DIVB_Msk) >> PWM_CLK_DIVB_Pos;
	return tmp;
}

static inline void hri_pwm_set_CLK_PREB_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK |= PWM_CLK_PREB(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_get_CLK_PREB_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp = (tmp & PWM_CLK_PREB(mask)) >> PWM_CLK_PREB_Pos;
	return tmp;
}

static inline void hri_pwm_write_CLK_PREB_bf(const void *const hw, hri_pwm_clk_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp &= ~PWM_CLK_PREB_Msk;
	tmp |= PWM_CLK_PREB(data);
	((Pwm *)hw)->PWM_CLK = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CLK_PREB_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK &= ~PWM_CLK_PREB(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CLK_PREB_bf(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK ^= PWM_CLK_PREB(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_read_CLK_PREB_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp = (tmp & PWM_CLK_PREB_Msk) >> PWM_CLK_PREB_Pos;
	return tmp;
}

static inline void hri_pwm_set_CLK_reg(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_get_CLK_reg(const void *const hw, hri_pwm_clk_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_CLK;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_CLK_reg(const void *const hw, hri_pwm_clk_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_CLK_reg(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_CLK_reg(const void *const hw, hri_pwm_clk_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CLK ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_clk_reg_t hri_pwm_read_CLK_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_CLK;
}

static inline void hri_pwm_set_SCM_SYNC0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM |= PWM_SCM_SYNC0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SCM_SYNC0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp = (tmp & PWM_SCM_SYNC0) >> PWM_SCM_SYNC0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SCM_SYNC0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp &= ~PWM_SCM_SYNC0;
	tmp |= value << PWM_SCM_SYNC0_Pos;
	((Pwm *)hw)->PWM_SCM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCM_SYNC0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM &= ~PWM_SCM_SYNC0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCM_SYNC0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM ^= PWM_SCM_SYNC0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SCM_SYNC1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM |= PWM_SCM_SYNC1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SCM_SYNC1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp = (tmp & PWM_SCM_SYNC1) >> PWM_SCM_SYNC1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SCM_SYNC1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp &= ~PWM_SCM_SYNC1;
	tmp |= value << PWM_SCM_SYNC1_Pos;
	((Pwm *)hw)->PWM_SCM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCM_SYNC1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM &= ~PWM_SCM_SYNC1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCM_SYNC1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM ^= PWM_SCM_SYNC1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SCM_SYNC2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM |= PWM_SCM_SYNC2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SCM_SYNC2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp = (tmp & PWM_SCM_SYNC2) >> PWM_SCM_SYNC2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SCM_SYNC2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp &= ~PWM_SCM_SYNC2;
	tmp |= value << PWM_SCM_SYNC2_Pos;
	((Pwm *)hw)->PWM_SCM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCM_SYNC2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM &= ~PWM_SCM_SYNC2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCM_SYNC2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM ^= PWM_SCM_SYNC2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SCM_SYNC3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM |= PWM_SCM_SYNC3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SCM_SYNC3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp = (tmp & PWM_SCM_SYNC3) >> PWM_SCM_SYNC3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SCM_SYNC3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp &= ~PWM_SCM_SYNC3;
	tmp |= value << PWM_SCM_SYNC3_Pos;
	((Pwm *)hw)->PWM_SCM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCM_SYNC3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM &= ~PWM_SCM_SYNC3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCM_SYNC3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM ^= PWM_SCM_SYNC3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SCM_PTRM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM |= PWM_SCM_PTRM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SCM_PTRM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp = (tmp & PWM_SCM_PTRM) >> PWM_SCM_PTRM_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SCM_PTRM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp &= ~PWM_SCM_PTRM;
	tmp |= value << PWM_SCM_PTRM_Pos;
	((Pwm *)hw)->PWM_SCM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCM_PTRM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM &= ~PWM_SCM_PTRM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCM_PTRM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM ^= PWM_SCM_PTRM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SCM_UPDM_bf(const void *const hw, hri_pwm_scm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM |= PWM_SCM_UPDM(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scm_reg_t hri_pwm_get_SCM_UPDM_bf(const void *const hw, hri_pwm_scm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp = (tmp & PWM_SCM_UPDM(mask)) >> PWM_SCM_UPDM_Pos;
	return tmp;
}

static inline void hri_pwm_write_SCM_UPDM_bf(const void *const hw, hri_pwm_scm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp &= ~PWM_SCM_UPDM_Msk;
	tmp |= PWM_SCM_UPDM(data);
	((Pwm *)hw)->PWM_SCM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCM_UPDM_bf(const void *const hw, hri_pwm_scm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM &= ~PWM_SCM_UPDM(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCM_UPDM_bf(const void *const hw, hri_pwm_scm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM ^= PWM_SCM_UPDM(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scm_reg_t hri_pwm_read_SCM_UPDM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp = (tmp & PWM_SCM_UPDM_Msk) >> PWM_SCM_UPDM_Pos;
	return tmp;
}

static inline void hri_pwm_set_SCM_PTRCS_bf(const void *const hw, hri_pwm_scm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM |= PWM_SCM_PTRCS(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scm_reg_t hri_pwm_get_SCM_PTRCS_bf(const void *const hw, hri_pwm_scm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp = (tmp & PWM_SCM_PTRCS(mask)) >> PWM_SCM_PTRCS_Pos;
	return tmp;
}

static inline void hri_pwm_write_SCM_PTRCS_bf(const void *const hw, hri_pwm_scm_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp &= ~PWM_SCM_PTRCS_Msk;
	tmp |= PWM_SCM_PTRCS(data);
	((Pwm *)hw)->PWM_SCM = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCM_PTRCS_bf(const void *const hw, hri_pwm_scm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM &= ~PWM_SCM_PTRCS(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCM_PTRCS_bf(const void *const hw, hri_pwm_scm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM ^= PWM_SCM_PTRCS(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scm_reg_t hri_pwm_read_SCM_PTRCS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp = (tmp & PWM_SCM_PTRCS_Msk) >> PWM_SCM_PTRCS_Pos;
	return tmp;
}

static inline void hri_pwm_set_SCM_reg(const void *const hw, hri_pwm_scm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scm_reg_t hri_pwm_get_SCM_reg(const void *const hw, hri_pwm_scm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCM;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_SCM_reg(const void *const hw, hri_pwm_scm_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCM_reg(const void *const hw, hri_pwm_scm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCM_reg(const void *const hw, hri_pwm_scm_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCM ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scm_reg_t hri_pwm_read_SCM_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_SCM;
}

static inline void hri_pwm_set_SCUC_UPDULOCK_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUC |= PWM_SCUC_UPDULOCK;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SCUC_UPDULOCK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCUC;
	tmp = (tmp & PWM_SCUC_UPDULOCK) >> PWM_SCUC_UPDULOCK_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SCUC_UPDULOCK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCUC;
	tmp &= ~PWM_SCUC_UPDULOCK;
	tmp |= value << PWM_SCUC_UPDULOCK_Pos;
	((Pwm *)hw)->PWM_SCUC = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCUC_UPDULOCK_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUC &= ~PWM_SCUC_UPDULOCK;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCUC_UPDULOCK_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUC ^= PWM_SCUC_UPDULOCK;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SCUC_reg(const void *const hw, hri_pwm_scuc_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUC |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scuc_reg_t hri_pwm_get_SCUC_reg(const void *const hw, hri_pwm_scuc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCUC;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_SCUC_reg(const void *const hw, hri_pwm_scuc_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUC = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCUC_reg(const void *const hw, hri_pwm_scuc_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUC &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCUC_reg(const void *const hw, hri_pwm_scuc_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUC ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scuc_reg_t hri_pwm_read_SCUC_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_SCUC;
}

static inline void hri_pwm_set_SCUP_UPR_bf(const void *const hw, hri_pwm_scup_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP |= PWM_SCUP_UPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scup_reg_t hri_pwm_get_SCUP_UPR_bf(const void *const hw, hri_pwm_scup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCUP;
	tmp = (tmp & PWM_SCUP_UPR(mask)) >> PWM_SCUP_UPR_Pos;
	return tmp;
}

static inline void hri_pwm_write_SCUP_UPR_bf(const void *const hw, hri_pwm_scup_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCUP;
	tmp &= ~PWM_SCUP_UPR_Msk;
	tmp |= PWM_SCUP_UPR(data);
	((Pwm *)hw)->PWM_SCUP = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCUP_UPR_bf(const void *const hw, hri_pwm_scup_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP &= ~PWM_SCUP_UPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCUP_UPR_bf(const void *const hw, hri_pwm_scup_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP ^= PWM_SCUP_UPR(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scup_reg_t hri_pwm_read_SCUP_UPR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCUP;
	tmp = (tmp & PWM_SCUP_UPR_Msk) >> PWM_SCUP_UPR_Pos;
	return tmp;
}

static inline void hri_pwm_set_SCUP_UPRCNT_bf(const void *const hw, hri_pwm_scup_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP |= PWM_SCUP_UPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scup_reg_t hri_pwm_get_SCUP_UPRCNT_bf(const void *const hw, hri_pwm_scup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCUP;
	tmp = (tmp & PWM_SCUP_UPRCNT(mask)) >> PWM_SCUP_UPRCNT_Pos;
	return tmp;
}

static inline void hri_pwm_write_SCUP_UPRCNT_bf(const void *const hw, hri_pwm_scup_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SCUP;
	tmp &= ~PWM_SCUP_UPRCNT_Msk;
	tmp |= PWM_SCUP_UPRCNT(data);
	((Pwm *)hw)->PWM_SCUP = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCUP_UPRCNT_bf(const void *const hw, hri_pwm_scup_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP &= ~PWM_SCUP_UPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCUP_UPRCNT_bf(const void *const hw, hri_pwm_scup_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP ^= PWM_SCUP_UPRCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scup_reg_t hri_pwm_read_SCUP_UPRCNT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCUP;
	tmp = (tmp & PWM_SCUP_UPRCNT_Msk) >> PWM_SCUP_UPRCNT_Pos;
	return tmp;
}

static inline void hri_pwm_set_SCUP_reg(const void *const hw, hri_pwm_scup_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scup_reg_t hri_pwm_get_SCUP_reg(const void *const hw, hri_pwm_scup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SCUP;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_SCUP_reg(const void *const hw, hri_pwm_scup_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SCUP_reg(const void *const hw, hri_pwm_scup_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SCUP_reg(const void *const hw, hri_pwm_scup_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUP ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_scup_reg_t hri_pwm_read_SCUP_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_SCUP;
}

static inline void hri_pwm_set_OOV_OOVH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV |= PWM_OOV_OOVH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OOV_OOVH0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp = (tmp & PWM_OOV_OOVH0) >> PWM_OOV_OOVH0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OOV_OOVH0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp &= ~PWM_OOV_OOVH0;
	tmp |= value << PWM_OOV_OOVH0_Pos;
	((Pwm *)hw)->PWM_OOV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OOV_OOVH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV &= ~PWM_OOV_OOVH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OOV_OOVH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV ^= PWM_OOV_OOVH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OOV_OOVH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV |= PWM_OOV_OOVH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OOV_OOVH1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp = (tmp & PWM_OOV_OOVH1) >> PWM_OOV_OOVH1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OOV_OOVH1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp &= ~PWM_OOV_OOVH1;
	tmp |= value << PWM_OOV_OOVH1_Pos;
	((Pwm *)hw)->PWM_OOV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OOV_OOVH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV &= ~PWM_OOV_OOVH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OOV_OOVH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV ^= PWM_OOV_OOVH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OOV_OOVH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV |= PWM_OOV_OOVH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OOV_OOVH2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp = (tmp & PWM_OOV_OOVH2) >> PWM_OOV_OOVH2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OOV_OOVH2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp &= ~PWM_OOV_OOVH2;
	tmp |= value << PWM_OOV_OOVH2_Pos;
	((Pwm *)hw)->PWM_OOV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OOV_OOVH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV &= ~PWM_OOV_OOVH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OOV_OOVH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV ^= PWM_OOV_OOVH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OOV_OOVH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV |= PWM_OOV_OOVH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OOV_OOVH3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp = (tmp & PWM_OOV_OOVH3) >> PWM_OOV_OOVH3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OOV_OOVH3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp &= ~PWM_OOV_OOVH3;
	tmp |= value << PWM_OOV_OOVH3_Pos;
	((Pwm *)hw)->PWM_OOV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OOV_OOVH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV &= ~PWM_OOV_OOVH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OOV_OOVH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV ^= PWM_OOV_OOVH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OOV_OOVL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV |= PWM_OOV_OOVL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OOV_OOVL0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp = (tmp & PWM_OOV_OOVL0) >> PWM_OOV_OOVL0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OOV_OOVL0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp &= ~PWM_OOV_OOVL0;
	tmp |= value << PWM_OOV_OOVL0_Pos;
	((Pwm *)hw)->PWM_OOV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OOV_OOVL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV &= ~PWM_OOV_OOVL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OOV_OOVL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV ^= PWM_OOV_OOVL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OOV_OOVL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV |= PWM_OOV_OOVL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OOV_OOVL1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp = (tmp & PWM_OOV_OOVL1) >> PWM_OOV_OOVL1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OOV_OOVL1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp &= ~PWM_OOV_OOVL1;
	tmp |= value << PWM_OOV_OOVL1_Pos;
	((Pwm *)hw)->PWM_OOV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OOV_OOVL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV &= ~PWM_OOV_OOVL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OOV_OOVL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV ^= PWM_OOV_OOVL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OOV_OOVL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV |= PWM_OOV_OOVL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OOV_OOVL2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp = (tmp & PWM_OOV_OOVL2) >> PWM_OOV_OOVL2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OOV_OOVL2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp &= ~PWM_OOV_OOVL2;
	tmp |= value << PWM_OOV_OOVL2_Pos;
	((Pwm *)hw)->PWM_OOV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OOV_OOVL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV &= ~PWM_OOV_OOVL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OOV_OOVL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV ^= PWM_OOV_OOVL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OOV_OOVL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV |= PWM_OOV_OOVL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OOV_OOVL3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp = (tmp & PWM_OOV_OOVL3) >> PWM_OOV_OOVL3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OOV_OOVL3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp &= ~PWM_OOV_OOVL3;
	tmp |= value << PWM_OOV_OOVL3_Pos;
	((Pwm *)hw)->PWM_OOV = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OOV_OOVL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV &= ~PWM_OOV_OOVL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OOV_OOVL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV ^= PWM_OOV_OOVL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OOV_reg(const void *const hw, hri_pwm_oov_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_oov_reg_t hri_pwm_get_OOV_reg(const void *const hw, hri_pwm_oov_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OOV;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_OOV_reg(const void *const hw, hri_pwm_oov_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OOV_reg(const void *const hw, hri_pwm_oov_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OOV_reg(const void *const hw, hri_pwm_oov_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OOV ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_oov_reg_t hri_pwm_read_OOV_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_OOV;
}

static inline void hri_pwm_set_OS_OSH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS |= PWM_OS_OSH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OS_OSH0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp = (tmp & PWM_OS_OSH0) >> PWM_OS_OSH0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OS_OSH0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp &= ~PWM_OS_OSH0;
	tmp |= value << PWM_OS_OSH0_Pos;
	((Pwm *)hw)->PWM_OS = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OS_OSH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS &= ~PWM_OS_OSH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OS_OSH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS ^= PWM_OS_OSH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OS_OSH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS |= PWM_OS_OSH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OS_OSH1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp = (tmp & PWM_OS_OSH1) >> PWM_OS_OSH1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OS_OSH1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp &= ~PWM_OS_OSH1;
	tmp |= value << PWM_OS_OSH1_Pos;
	((Pwm *)hw)->PWM_OS = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OS_OSH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS &= ~PWM_OS_OSH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OS_OSH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS ^= PWM_OS_OSH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OS_OSH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS |= PWM_OS_OSH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OS_OSH2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp = (tmp & PWM_OS_OSH2) >> PWM_OS_OSH2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OS_OSH2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp &= ~PWM_OS_OSH2;
	tmp |= value << PWM_OS_OSH2_Pos;
	((Pwm *)hw)->PWM_OS = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OS_OSH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS &= ~PWM_OS_OSH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OS_OSH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS ^= PWM_OS_OSH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OS_OSH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS |= PWM_OS_OSH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OS_OSH3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp = (tmp & PWM_OS_OSH3) >> PWM_OS_OSH3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OS_OSH3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp &= ~PWM_OS_OSH3;
	tmp |= value << PWM_OS_OSH3_Pos;
	((Pwm *)hw)->PWM_OS = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OS_OSH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS &= ~PWM_OS_OSH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OS_OSH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS ^= PWM_OS_OSH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OS_OSL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS |= PWM_OS_OSL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OS_OSL0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp = (tmp & PWM_OS_OSL0) >> PWM_OS_OSL0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OS_OSL0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp &= ~PWM_OS_OSL0;
	tmp |= value << PWM_OS_OSL0_Pos;
	((Pwm *)hw)->PWM_OS = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OS_OSL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS &= ~PWM_OS_OSL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OS_OSL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS ^= PWM_OS_OSL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OS_OSL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS |= PWM_OS_OSL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OS_OSL1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp = (tmp & PWM_OS_OSL1) >> PWM_OS_OSL1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OS_OSL1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp &= ~PWM_OS_OSL1;
	tmp |= value << PWM_OS_OSL1_Pos;
	((Pwm *)hw)->PWM_OS = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OS_OSL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS &= ~PWM_OS_OSL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OS_OSL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS ^= PWM_OS_OSL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OS_OSL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS |= PWM_OS_OSL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OS_OSL2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp = (tmp & PWM_OS_OSL2) >> PWM_OS_OSL2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OS_OSL2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp &= ~PWM_OS_OSL2;
	tmp |= value << PWM_OS_OSL2_Pos;
	((Pwm *)hw)->PWM_OS = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OS_OSL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS &= ~PWM_OS_OSL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OS_OSL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS ^= PWM_OS_OSL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OS_OSL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS |= PWM_OS_OSL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_OS_OSL3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp = (tmp & PWM_OS_OSL3) >> PWM_OS_OSL3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_OS_OSL3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp &= ~PWM_OS_OSL3;
	tmp |= value << PWM_OS_OSL3_Pos;
	((Pwm *)hw)->PWM_OS = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OS_OSL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS &= ~PWM_OS_OSL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OS_OSL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS ^= PWM_OS_OSL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_OS_reg(const void *const hw, hri_pwm_os_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_os_reg_t hri_pwm_get_OS_reg(const void *const hw, hri_pwm_os_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_OS;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_OS_reg(const void *const hw, hri_pwm_os_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_OS_reg(const void *const hw, hri_pwm_os_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_OS_reg(const void *const hw, hri_pwm_os_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OS ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_os_reg_t hri_pwm_read_OS_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_OS;
}

static inline void hri_pwm_set_FMR_FPOL_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR |= PWM_FMR_FPOL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fmr_reg_t hri_pwm_get_FMR_FPOL_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp = (tmp & PWM_FMR_FPOL(mask)) >> PWM_FMR_FPOL_Pos;
	return tmp;
}

static inline void hri_pwm_write_FMR_FPOL_bf(const void *const hw, hri_pwm_fmr_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp &= ~PWM_FMR_FPOL_Msk;
	tmp |= PWM_FMR_FPOL(data);
	((Pwm *)hw)->PWM_FMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FMR_FPOL_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR &= ~PWM_FMR_FPOL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FMR_FPOL_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR ^= PWM_FMR_FPOL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fmr_reg_t hri_pwm_read_FMR_FPOL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp = (tmp & PWM_FMR_FPOL_Msk) >> PWM_FMR_FPOL_Pos;
	return tmp;
}

static inline void hri_pwm_set_FMR_FMOD_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR |= PWM_FMR_FMOD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fmr_reg_t hri_pwm_get_FMR_FMOD_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp = (tmp & PWM_FMR_FMOD(mask)) >> PWM_FMR_FMOD_Pos;
	return tmp;
}

static inline void hri_pwm_write_FMR_FMOD_bf(const void *const hw, hri_pwm_fmr_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp &= ~PWM_FMR_FMOD_Msk;
	tmp |= PWM_FMR_FMOD(data);
	((Pwm *)hw)->PWM_FMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FMR_FMOD_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR &= ~PWM_FMR_FMOD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FMR_FMOD_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR ^= PWM_FMR_FMOD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fmr_reg_t hri_pwm_read_FMR_FMOD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp = (tmp & PWM_FMR_FMOD_Msk) >> PWM_FMR_FMOD_Pos;
	return tmp;
}

static inline void hri_pwm_set_FMR_FFIL_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR |= PWM_FMR_FFIL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fmr_reg_t hri_pwm_get_FMR_FFIL_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp = (tmp & PWM_FMR_FFIL(mask)) >> PWM_FMR_FFIL_Pos;
	return tmp;
}

static inline void hri_pwm_write_FMR_FFIL_bf(const void *const hw, hri_pwm_fmr_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp &= ~PWM_FMR_FFIL_Msk;
	tmp |= PWM_FMR_FFIL(data);
	((Pwm *)hw)->PWM_FMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FMR_FFIL_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR &= ~PWM_FMR_FFIL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FMR_FFIL_bf(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR ^= PWM_FMR_FFIL(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fmr_reg_t hri_pwm_read_FMR_FFIL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp = (tmp & PWM_FMR_FFIL_Msk) >> PWM_FMR_FFIL_Pos;
	return tmp;
}

static inline void hri_pwm_set_FMR_reg(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fmr_reg_t hri_pwm_get_FMR_reg(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_FMR_reg(const void *const hw, hri_pwm_fmr_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FMR_reg(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FMR_reg(const void *const hw, hri_pwm_fmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FMR ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fmr_reg_t hri_pwm_read_FMR_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_FMR;
}

static inline void hri_pwm_set_FPV1_FPVH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 |= PWM_FPV1_FPVH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV1_FPVH0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp = (tmp & PWM_FPV1_FPVH0) >> PWM_FPV1_FPVH0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV1_FPVH0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp &= ~PWM_FPV1_FPVH0;
	tmp |= value << PWM_FPV1_FPVH0_Pos;
	((Pwm *)hw)->PWM_FPV1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV1_FPVH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 &= ~PWM_FPV1_FPVH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV1_FPVH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 ^= PWM_FPV1_FPVH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV1_FPVH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 |= PWM_FPV1_FPVH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV1_FPVH1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp = (tmp & PWM_FPV1_FPVH1) >> PWM_FPV1_FPVH1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV1_FPVH1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp &= ~PWM_FPV1_FPVH1;
	tmp |= value << PWM_FPV1_FPVH1_Pos;
	((Pwm *)hw)->PWM_FPV1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV1_FPVH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 &= ~PWM_FPV1_FPVH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV1_FPVH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 ^= PWM_FPV1_FPVH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV1_FPVH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 |= PWM_FPV1_FPVH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV1_FPVH2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp = (tmp & PWM_FPV1_FPVH2) >> PWM_FPV1_FPVH2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV1_FPVH2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp &= ~PWM_FPV1_FPVH2;
	tmp |= value << PWM_FPV1_FPVH2_Pos;
	((Pwm *)hw)->PWM_FPV1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV1_FPVH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 &= ~PWM_FPV1_FPVH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV1_FPVH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 ^= PWM_FPV1_FPVH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV1_FPVH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 |= PWM_FPV1_FPVH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV1_FPVH3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp = (tmp & PWM_FPV1_FPVH3) >> PWM_FPV1_FPVH3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV1_FPVH3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp &= ~PWM_FPV1_FPVH3;
	tmp |= value << PWM_FPV1_FPVH3_Pos;
	((Pwm *)hw)->PWM_FPV1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV1_FPVH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 &= ~PWM_FPV1_FPVH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV1_FPVH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 ^= PWM_FPV1_FPVH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV1_FPVL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 |= PWM_FPV1_FPVL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV1_FPVL0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp = (tmp & PWM_FPV1_FPVL0) >> PWM_FPV1_FPVL0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV1_FPVL0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp &= ~PWM_FPV1_FPVL0;
	tmp |= value << PWM_FPV1_FPVL0_Pos;
	((Pwm *)hw)->PWM_FPV1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV1_FPVL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 &= ~PWM_FPV1_FPVL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV1_FPVL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 ^= PWM_FPV1_FPVL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV1_FPVL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 |= PWM_FPV1_FPVL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV1_FPVL1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp = (tmp & PWM_FPV1_FPVL1) >> PWM_FPV1_FPVL1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV1_FPVL1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp &= ~PWM_FPV1_FPVL1;
	tmp |= value << PWM_FPV1_FPVL1_Pos;
	((Pwm *)hw)->PWM_FPV1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV1_FPVL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 &= ~PWM_FPV1_FPVL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV1_FPVL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 ^= PWM_FPV1_FPVL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV1_FPVL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 |= PWM_FPV1_FPVL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV1_FPVL2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp = (tmp & PWM_FPV1_FPVL2) >> PWM_FPV1_FPVL2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV1_FPVL2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp &= ~PWM_FPV1_FPVL2;
	tmp |= value << PWM_FPV1_FPVL2_Pos;
	((Pwm *)hw)->PWM_FPV1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV1_FPVL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 &= ~PWM_FPV1_FPVL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV1_FPVL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 ^= PWM_FPV1_FPVL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV1_FPVL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 |= PWM_FPV1_FPVL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV1_FPVL3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp = (tmp & PWM_FPV1_FPVL3) >> PWM_FPV1_FPVL3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV1_FPVL3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp &= ~PWM_FPV1_FPVL3;
	tmp |= value << PWM_FPV1_FPVL3_Pos;
	((Pwm *)hw)->PWM_FPV1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV1_FPVL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 &= ~PWM_FPV1_FPVL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV1_FPVL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 ^= PWM_FPV1_FPVL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV1_reg(const void *const hw, hri_pwm_fpv1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpv1_reg_t hri_pwm_get_FPV1_reg(const void *const hw, hri_pwm_fpv1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV1;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_FPV1_reg(const void *const hw, hri_pwm_fpv1_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV1_reg(const void *const hw, hri_pwm_fpv1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV1_reg(const void *const hw, hri_pwm_fpv1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV1 ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpv1_reg_t hri_pwm_read_FPV1_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_FPV1;
}

static inline void hri_pwm_set_FPE_FPE0_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE |= PWM_FPE_FPE0(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_get_FPE_FPE0_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp = (tmp & PWM_FPE_FPE0(mask)) >> PWM_FPE_FPE0_Pos;
	return tmp;
}

static inline void hri_pwm_write_FPE_FPE0_bf(const void *const hw, hri_pwm_fpe_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp &= ~PWM_FPE_FPE0_Msk;
	tmp |= PWM_FPE_FPE0(data);
	((Pwm *)hw)->PWM_FPE = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPE_FPE0_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE &= ~PWM_FPE_FPE0(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPE_FPE0_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE ^= PWM_FPE_FPE0(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_read_FPE_FPE0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp = (tmp & PWM_FPE_FPE0_Msk) >> PWM_FPE_FPE0_Pos;
	return tmp;
}

static inline void hri_pwm_set_FPE_FPE1_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE |= PWM_FPE_FPE1(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_get_FPE_FPE1_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp = (tmp & PWM_FPE_FPE1(mask)) >> PWM_FPE_FPE1_Pos;
	return tmp;
}

static inline void hri_pwm_write_FPE_FPE1_bf(const void *const hw, hri_pwm_fpe_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp &= ~PWM_FPE_FPE1_Msk;
	tmp |= PWM_FPE_FPE1(data);
	((Pwm *)hw)->PWM_FPE = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPE_FPE1_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE &= ~PWM_FPE_FPE1(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPE_FPE1_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE ^= PWM_FPE_FPE1(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_read_FPE_FPE1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp = (tmp & PWM_FPE_FPE1_Msk) >> PWM_FPE_FPE1_Pos;
	return tmp;
}

static inline void hri_pwm_set_FPE_FPE2_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE |= PWM_FPE_FPE2(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_get_FPE_FPE2_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp = (tmp & PWM_FPE_FPE2(mask)) >> PWM_FPE_FPE2_Pos;
	return tmp;
}

static inline void hri_pwm_write_FPE_FPE2_bf(const void *const hw, hri_pwm_fpe_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp &= ~PWM_FPE_FPE2_Msk;
	tmp |= PWM_FPE_FPE2(data);
	((Pwm *)hw)->PWM_FPE = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPE_FPE2_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE &= ~PWM_FPE_FPE2(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPE_FPE2_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE ^= PWM_FPE_FPE2(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_read_FPE_FPE2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp = (tmp & PWM_FPE_FPE2_Msk) >> PWM_FPE_FPE2_Pos;
	return tmp;
}

static inline void hri_pwm_set_FPE_FPE3_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE |= PWM_FPE_FPE3(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_get_FPE_FPE3_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp = (tmp & PWM_FPE_FPE3(mask)) >> PWM_FPE_FPE3_Pos;
	return tmp;
}

static inline void hri_pwm_write_FPE_FPE3_bf(const void *const hw, hri_pwm_fpe_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp &= ~PWM_FPE_FPE3_Msk;
	tmp |= PWM_FPE_FPE3(data);
	((Pwm *)hw)->PWM_FPE = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPE_FPE3_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE &= ~PWM_FPE_FPE3(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPE_FPE3_bf(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE ^= PWM_FPE_FPE3(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_read_FPE_FPE3_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp = (tmp & PWM_FPE_FPE3_Msk) >> PWM_FPE_FPE3_Pos;
	return tmp;
}

static inline void hri_pwm_set_FPE_reg(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_get_FPE_reg(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPE;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_FPE_reg(const void *const hw, hri_pwm_fpe_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPE_reg(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPE_reg(const void *const hw, hri_pwm_fpe_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPE ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpe_reg_t hri_pwm_read_FPE_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_FPE;
}

static inline void hri_pwm_set_ELMR_CSEL0_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] |= PWM_ELMR_CSEL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ELMR_CSEL0_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp = (tmp & PWM_ELMR_CSEL0) >> PWM_ELMR_CSEL0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ELMR_CSEL0_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp &= ~PWM_ELMR_CSEL0;
	tmp |= value << PWM_ELMR_CSEL0_Pos;
	((Pwm *)hw)->PWM_ELMR[index] = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ELMR_CSEL0_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] &= ~PWM_ELMR_CSEL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ELMR_CSEL0_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] ^= PWM_ELMR_CSEL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ELMR_CSEL1_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] |= PWM_ELMR_CSEL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ELMR_CSEL1_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp = (tmp & PWM_ELMR_CSEL1) >> PWM_ELMR_CSEL1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ELMR_CSEL1_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp &= ~PWM_ELMR_CSEL1;
	tmp |= value << PWM_ELMR_CSEL1_Pos;
	((Pwm *)hw)->PWM_ELMR[index] = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ELMR_CSEL1_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] &= ~PWM_ELMR_CSEL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ELMR_CSEL1_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] ^= PWM_ELMR_CSEL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ELMR_CSEL2_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] |= PWM_ELMR_CSEL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ELMR_CSEL2_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp = (tmp & PWM_ELMR_CSEL2) >> PWM_ELMR_CSEL2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ELMR_CSEL2_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp &= ~PWM_ELMR_CSEL2;
	tmp |= value << PWM_ELMR_CSEL2_Pos;
	((Pwm *)hw)->PWM_ELMR[index] = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ELMR_CSEL2_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] &= ~PWM_ELMR_CSEL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ELMR_CSEL2_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] ^= PWM_ELMR_CSEL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ELMR_CSEL3_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] |= PWM_ELMR_CSEL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ELMR_CSEL3_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp = (tmp & PWM_ELMR_CSEL3) >> PWM_ELMR_CSEL3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ELMR_CSEL3_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp &= ~PWM_ELMR_CSEL3;
	tmp |= value << PWM_ELMR_CSEL3_Pos;
	((Pwm *)hw)->PWM_ELMR[index] = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ELMR_CSEL3_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] &= ~PWM_ELMR_CSEL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ELMR_CSEL3_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] ^= PWM_ELMR_CSEL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ELMR_CSEL4_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] |= PWM_ELMR_CSEL4;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ELMR_CSEL4_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp = (tmp & PWM_ELMR_CSEL4) >> PWM_ELMR_CSEL4_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ELMR_CSEL4_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp &= ~PWM_ELMR_CSEL4;
	tmp |= value << PWM_ELMR_CSEL4_Pos;
	((Pwm *)hw)->PWM_ELMR[index] = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ELMR_CSEL4_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] &= ~PWM_ELMR_CSEL4;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ELMR_CSEL4_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] ^= PWM_ELMR_CSEL4;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ELMR_CSEL5_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] |= PWM_ELMR_CSEL5;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ELMR_CSEL5_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp = (tmp & PWM_ELMR_CSEL5) >> PWM_ELMR_CSEL5_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ELMR_CSEL5_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp &= ~PWM_ELMR_CSEL5;
	tmp |= value << PWM_ELMR_CSEL5_Pos;
	((Pwm *)hw)->PWM_ELMR[index] = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ELMR_CSEL5_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] &= ~PWM_ELMR_CSEL5;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ELMR_CSEL5_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] ^= PWM_ELMR_CSEL5;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ELMR_CSEL6_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] |= PWM_ELMR_CSEL6;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ELMR_CSEL6_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp = (tmp & PWM_ELMR_CSEL6) >> PWM_ELMR_CSEL6_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ELMR_CSEL6_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp &= ~PWM_ELMR_CSEL6;
	tmp |= value << PWM_ELMR_CSEL6_Pos;
	((Pwm *)hw)->PWM_ELMR[index] = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ELMR_CSEL6_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] &= ~PWM_ELMR_CSEL6;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ELMR_CSEL6_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] ^= PWM_ELMR_CSEL6;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ELMR_CSEL7_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] |= PWM_ELMR_CSEL7;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ELMR_CSEL7_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp = (tmp & PWM_ELMR_CSEL7) >> PWM_ELMR_CSEL7_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ELMR_CSEL7_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp &= ~PWM_ELMR_CSEL7;
	tmp |= value << PWM_ELMR_CSEL7_Pos;
	((Pwm *)hw)->PWM_ELMR[index] = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ELMR_CSEL7_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] &= ~PWM_ELMR_CSEL7;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ELMR_CSEL7_bit(const void *const hw, uint8_t index)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] ^= PWM_ELMR_CSEL7;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ELMR_reg(const void *const hw, uint8_t index, hri_pwm_elmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_elmr_reg_t hri_pwm_get_ELMR_reg(const void *const hw, uint8_t index, hri_pwm_elmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ELMR[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_ELMR_reg(const void *const hw, uint8_t index, hri_pwm_elmr_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ELMR_reg(const void *const hw, uint8_t index, hri_pwm_elmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ELMR_reg(const void *const hw, uint8_t index, hri_pwm_elmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ELMR[index] ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_elmr_reg_t hri_pwm_read_ELMR_reg(const void *const hw, uint8_t index)
{
	return ((Pwm *)hw)->PWM_ELMR[index];
}

static inline void hri_pwm_set_SSPR_SPRDM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR |= PWM_SSPR_SPRDM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SSPR_SPRDM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SSPR;
	tmp = (tmp & PWM_SSPR_SPRDM) >> PWM_SSPR_SPRDM_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SSPR_SPRDM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SSPR;
	tmp &= ~PWM_SSPR_SPRDM;
	tmp |= value << PWM_SSPR_SPRDM_Pos;
	((Pwm *)hw)->PWM_SSPR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SSPR_SPRDM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR &= ~PWM_SSPR_SPRDM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SSPR_SPRDM_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR ^= PWM_SSPR_SPRDM;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SSPR_SPRD_bf(const void *const hw, hri_pwm_sspr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR |= PWM_SSPR_SPRD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_sspr_reg_t hri_pwm_get_SSPR_SPRD_bf(const void *const hw, hri_pwm_sspr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SSPR;
	tmp = (tmp & PWM_SSPR_SPRD(mask)) >> PWM_SSPR_SPRD_Pos;
	return tmp;
}

static inline void hri_pwm_write_SSPR_SPRD_bf(const void *const hw, hri_pwm_sspr_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SSPR;
	tmp &= ~PWM_SSPR_SPRD_Msk;
	tmp |= PWM_SSPR_SPRD(data);
	((Pwm *)hw)->PWM_SSPR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SSPR_SPRD_bf(const void *const hw, hri_pwm_sspr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR &= ~PWM_SSPR_SPRD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SSPR_SPRD_bf(const void *const hw, hri_pwm_sspr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR ^= PWM_SSPR_SPRD(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_sspr_reg_t hri_pwm_read_SSPR_SPRD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SSPR;
	tmp = (tmp & PWM_SSPR_SPRD_Msk) >> PWM_SSPR_SPRD_Pos;
	return tmp;
}

static inline void hri_pwm_set_SSPR_reg(const void *const hw, hri_pwm_sspr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_sspr_reg_t hri_pwm_get_SSPR_reg(const void *const hw, hri_pwm_sspr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SSPR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_SSPR_reg(const void *const hw, hri_pwm_sspr_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SSPR_reg(const void *const hw, hri_pwm_sspr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SSPR_reg(const void *const hw, hri_pwm_sspr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPR ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_sspr_reg_t hri_pwm_read_SSPR_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_SSPR;
}

static inline void hri_pwm_set_SMMR_GCEN0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR |= PWM_SMMR_GCEN0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SMMR_GCEN0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SMMR;
	tmp = (tmp & PWM_SMMR_GCEN0) >> PWM_SMMR_GCEN0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SMMR_GCEN0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SMMR;
	tmp &= ~PWM_SMMR_GCEN0;
	tmp |= value << PWM_SMMR_GCEN0_Pos;
	((Pwm *)hw)->PWM_SMMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SMMR_GCEN0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR &= ~PWM_SMMR_GCEN0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SMMR_GCEN0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR ^= PWM_SMMR_GCEN0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SMMR_GCEN1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR |= PWM_SMMR_GCEN1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SMMR_GCEN1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SMMR;
	tmp = (tmp & PWM_SMMR_GCEN1) >> PWM_SMMR_GCEN1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SMMR_GCEN1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SMMR;
	tmp &= ~PWM_SMMR_GCEN1;
	tmp |= value << PWM_SMMR_GCEN1_Pos;
	((Pwm *)hw)->PWM_SMMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SMMR_GCEN1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR &= ~PWM_SMMR_GCEN1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SMMR_GCEN1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR ^= PWM_SMMR_GCEN1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SMMR_DOWN0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR |= PWM_SMMR_DOWN0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SMMR_DOWN0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SMMR;
	tmp = (tmp & PWM_SMMR_DOWN0) >> PWM_SMMR_DOWN0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SMMR_DOWN0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SMMR;
	tmp &= ~PWM_SMMR_DOWN0;
	tmp |= value << PWM_SMMR_DOWN0_Pos;
	((Pwm *)hw)->PWM_SMMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SMMR_DOWN0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR &= ~PWM_SMMR_DOWN0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SMMR_DOWN0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR ^= PWM_SMMR_DOWN0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SMMR_DOWN1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR |= PWM_SMMR_DOWN1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_SMMR_DOWN1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SMMR;
	tmp = (tmp & PWM_SMMR_DOWN1) >> PWM_SMMR_DOWN1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_SMMR_DOWN1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_SMMR;
	tmp &= ~PWM_SMMR_DOWN1;
	tmp |= value << PWM_SMMR_DOWN1_Pos;
	((Pwm *)hw)->PWM_SMMR = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SMMR_DOWN1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR &= ~PWM_SMMR_DOWN1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SMMR_DOWN1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR ^= PWM_SMMR_DOWN1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_SMMR_reg(const void *const hw, hri_pwm_smmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_smmr_reg_t hri_pwm_get_SMMR_reg(const void *const hw, hri_pwm_smmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_SMMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_SMMR_reg(const void *const hw, hri_pwm_smmr_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_SMMR_reg(const void *const hw, hri_pwm_smmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_SMMR_reg(const void *const hw, hri_pwm_smmr_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SMMR ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_smmr_reg_t hri_pwm_read_SMMR_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_SMMR;
}

static inline void hri_pwm_set_FPV2_FPZH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 |= PWM_FPV2_FPZH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV2_FPZH0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp = (tmp & PWM_FPV2_FPZH0) >> PWM_FPV2_FPZH0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV2_FPZH0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp &= ~PWM_FPV2_FPZH0;
	tmp |= value << PWM_FPV2_FPZH0_Pos;
	((Pwm *)hw)->PWM_FPV2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV2_FPZH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 &= ~PWM_FPV2_FPZH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV2_FPZH0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 ^= PWM_FPV2_FPZH0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV2_FPZH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 |= PWM_FPV2_FPZH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV2_FPZH1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp = (tmp & PWM_FPV2_FPZH1) >> PWM_FPV2_FPZH1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV2_FPZH1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp &= ~PWM_FPV2_FPZH1;
	tmp |= value << PWM_FPV2_FPZH1_Pos;
	((Pwm *)hw)->PWM_FPV2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV2_FPZH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 &= ~PWM_FPV2_FPZH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV2_FPZH1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 ^= PWM_FPV2_FPZH1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV2_FPZH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 |= PWM_FPV2_FPZH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV2_FPZH2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp = (tmp & PWM_FPV2_FPZH2) >> PWM_FPV2_FPZH2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV2_FPZH2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp &= ~PWM_FPV2_FPZH2;
	tmp |= value << PWM_FPV2_FPZH2_Pos;
	((Pwm *)hw)->PWM_FPV2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV2_FPZH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 &= ~PWM_FPV2_FPZH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV2_FPZH2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 ^= PWM_FPV2_FPZH2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV2_FPZH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 |= PWM_FPV2_FPZH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV2_FPZH3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp = (tmp & PWM_FPV2_FPZH3) >> PWM_FPV2_FPZH3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV2_FPZH3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp &= ~PWM_FPV2_FPZH3;
	tmp |= value << PWM_FPV2_FPZH3_Pos;
	((Pwm *)hw)->PWM_FPV2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV2_FPZH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 &= ~PWM_FPV2_FPZH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV2_FPZH3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 ^= PWM_FPV2_FPZH3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV2_FPZL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 |= PWM_FPV2_FPZL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV2_FPZL0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp = (tmp & PWM_FPV2_FPZL0) >> PWM_FPV2_FPZL0_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV2_FPZL0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp &= ~PWM_FPV2_FPZL0;
	tmp |= value << PWM_FPV2_FPZL0_Pos;
	((Pwm *)hw)->PWM_FPV2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV2_FPZL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 &= ~PWM_FPV2_FPZL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV2_FPZL0_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 ^= PWM_FPV2_FPZL0;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV2_FPZL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 |= PWM_FPV2_FPZL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV2_FPZL1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp = (tmp & PWM_FPV2_FPZL1) >> PWM_FPV2_FPZL1_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV2_FPZL1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp &= ~PWM_FPV2_FPZL1;
	tmp |= value << PWM_FPV2_FPZL1_Pos;
	((Pwm *)hw)->PWM_FPV2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV2_FPZL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 &= ~PWM_FPV2_FPZL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV2_FPZL1_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 ^= PWM_FPV2_FPZL1;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV2_FPZL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 |= PWM_FPV2_FPZL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV2_FPZL2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp = (tmp & PWM_FPV2_FPZL2) >> PWM_FPV2_FPZL2_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV2_FPZL2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp &= ~PWM_FPV2_FPZL2;
	tmp |= value << PWM_FPV2_FPZL2_Pos;
	((Pwm *)hw)->PWM_FPV2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV2_FPZL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 &= ~PWM_FPV2_FPZL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV2_FPZL2_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 ^= PWM_FPV2_FPZL2;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV2_FPZL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 |= PWM_FPV2_FPZL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_FPV2_FPZL3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp = (tmp & PWM_FPV2_FPZL3) >> PWM_FPV2_FPZL3_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_FPV2_FPZL3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp &= ~PWM_FPV2_FPZL3;
	tmp |= value << PWM_FPV2_FPZL3_Pos;
	((Pwm *)hw)->PWM_FPV2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV2_FPZL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 &= ~PWM_FPV2_FPZL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV2_FPZL3_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 ^= PWM_FPV2_FPZL3;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_FPV2_reg(const void *const hw, hri_pwm_fpv2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpv2_reg_t hri_pwm_get_FPV2_reg(const void *const hw, hri_pwm_fpv2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_FPV2;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_FPV2_reg(const void *const hw, hri_pwm_fpv2_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_FPV2_reg(const void *const hw, hri_pwm_fpv2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_FPV2_reg(const void *const hw, hri_pwm_fpv2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FPV2 ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_fpv2_reg_t hri_pwm_read_FPV2_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_FPV2;
}

static inline void hri_pwm_set_ETRG1_TRGEDGE_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 |= PWM_ETRG1_TRGEDGE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ETRG1_TRGEDGE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp = (tmp & PWM_ETRG1_TRGEDGE) >> PWM_ETRG1_TRGEDGE_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ETRG1_TRGEDGE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp &= ~PWM_ETRG1_TRGEDGE;
	tmp |= value << PWM_ETRG1_TRGEDGE_Pos;
	((Pwm *)hw)->PWM_ETRG1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG1_TRGEDGE_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 &= ~PWM_ETRG1_TRGEDGE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG1_TRGEDGE_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 ^= PWM_ETRG1_TRGEDGE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ETRG1_TRGFILT_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 |= PWM_ETRG1_TRGFILT;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ETRG1_TRGFILT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp = (tmp & PWM_ETRG1_TRGFILT) >> PWM_ETRG1_TRGFILT_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ETRG1_TRGFILT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp &= ~PWM_ETRG1_TRGFILT;
	tmp |= value << PWM_ETRG1_TRGFILT_Pos;
	((Pwm *)hw)->PWM_ETRG1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG1_TRGFILT_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 &= ~PWM_ETRG1_TRGFILT;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG1_TRGFILT_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 ^= PWM_ETRG1_TRGFILT;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ETRG1_TRGSRC_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 |= PWM_ETRG1_TRGSRC;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ETRG1_TRGSRC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp = (tmp & PWM_ETRG1_TRGSRC) >> PWM_ETRG1_TRGSRC_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ETRG1_TRGSRC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp &= ~PWM_ETRG1_TRGSRC;
	tmp |= value << PWM_ETRG1_TRGSRC_Pos;
	((Pwm *)hw)->PWM_ETRG1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG1_TRGSRC_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 &= ~PWM_ETRG1_TRGSRC;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG1_TRGSRC_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 ^= PWM_ETRG1_TRGSRC;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ETRG1_RFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 |= PWM_ETRG1_RFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ETRG1_RFEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp = (tmp & PWM_ETRG1_RFEN) >> PWM_ETRG1_RFEN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ETRG1_RFEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp &= ~PWM_ETRG1_RFEN;
	tmp |= value << PWM_ETRG1_RFEN_Pos;
	((Pwm *)hw)->PWM_ETRG1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG1_RFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 &= ~PWM_ETRG1_RFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG1_RFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 ^= PWM_ETRG1_RFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ETRG1_MAXCNT_bf(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 |= PWM_ETRG1_MAXCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg1_reg_t hri_pwm_get_ETRG1_MAXCNT_bf(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp = (tmp & PWM_ETRG1_MAXCNT(mask)) >> PWM_ETRG1_MAXCNT_Pos;
	return tmp;
}

static inline void hri_pwm_write_ETRG1_MAXCNT_bf(const void *const hw, hri_pwm_etrg1_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp &= ~PWM_ETRG1_MAXCNT_Msk;
	tmp |= PWM_ETRG1_MAXCNT(data);
	((Pwm *)hw)->PWM_ETRG1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG1_MAXCNT_bf(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 &= ~PWM_ETRG1_MAXCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG1_MAXCNT_bf(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 ^= PWM_ETRG1_MAXCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg1_reg_t hri_pwm_read_ETRG1_MAXCNT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp = (tmp & PWM_ETRG1_MAXCNT_Msk) >> PWM_ETRG1_MAXCNT_Pos;
	return tmp;
}

static inline void hri_pwm_set_ETRG1_TRGMODE_bf(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 |= PWM_ETRG1_TRGMODE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg1_reg_t hri_pwm_get_ETRG1_TRGMODE_bf(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp = (tmp & PWM_ETRG1_TRGMODE(mask)) >> PWM_ETRG1_TRGMODE_Pos;
	return tmp;
}

static inline void hri_pwm_write_ETRG1_TRGMODE_bf(const void *const hw, hri_pwm_etrg1_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp &= ~PWM_ETRG1_TRGMODE_Msk;
	tmp |= PWM_ETRG1_TRGMODE(data);
	((Pwm *)hw)->PWM_ETRG1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG1_TRGMODE_bf(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 &= ~PWM_ETRG1_TRGMODE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG1_TRGMODE_bf(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 ^= PWM_ETRG1_TRGMODE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg1_reg_t hri_pwm_read_ETRG1_TRGMODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp = (tmp & PWM_ETRG1_TRGMODE_Msk) >> PWM_ETRG1_TRGMODE_Pos;
	return tmp;
}

static inline void hri_pwm_set_ETRG1_reg(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg1_reg_t hri_pwm_get_ETRG1_reg(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG1;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_ETRG1_reg(const void *const hw, hri_pwm_etrg1_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG1_reg(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG1_reg(const void *const hw, hri_pwm_etrg1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG1 ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg1_reg_t hri_pwm_read_ETRG1_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_ETRG1;
}

static inline void hri_pwm_set_LEBR1_PWMLFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 |= PWM_LEBR1_PWMLFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_LEBR1_PWMLFEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp = (tmp & PWM_LEBR1_PWMLFEN) >> PWM_LEBR1_PWMLFEN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_LEBR1_PWMLFEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp &= ~PWM_LEBR1_PWMLFEN;
	tmp |= value << PWM_LEBR1_PWMLFEN_Pos;
	((Pwm *)hw)->PWM_LEBR1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR1_PWMLFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 &= ~PWM_LEBR1_PWMLFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR1_PWMLFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 ^= PWM_LEBR1_PWMLFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_LEBR1_PWMLREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 |= PWM_LEBR1_PWMLREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_LEBR1_PWMLREN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp = (tmp & PWM_LEBR1_PWMLREN) >> PWM_LEBR1_PWMLREN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_LEBR1_PWMLREN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp &= ~PWM_LEBR1_PWMLREN;
	tmp |= value << PWM_LEBR1_PWMLREN_Pos;
	((Pwm *)hw)->PWM_LEBR1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR1_PWMLREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 &= ~PWM_LEBR1_PWMLREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR1_PWMLREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 ^= PWM_LEBR1_PWMLREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_LEBR1_PWMHFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 |= PWM_LEBR1_PWMHFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_LEBR1_PWMHFEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp = (tmp & PWM_LEBR1_PWMHFEN) >> PWM_LEBR1_PWMHFEN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_LEBR1_PWMHFEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp &= ~PWM_LEBR1_PWMHFEN;
	tmp |= value << PWM_LEBR1_PWMHFEN_Pos;
	((Pwm *)hw)->PWM_LEBR1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR1_PWMHFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 &= ~PWM_LEBR1_PWMHFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR1_PWMHFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 ^= PWM_LEBR1_PWMHFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_LEBR1_PWMHREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 |= PWM_LEBR1_PWMHREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_LEBR1_PWMHREN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp = (tmp & PWM_LEBR1_PWMHREN) >> PWM_LEBR1_PWMHREN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_LEBR1_PWMHREN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp &= ~PWM_LEBR1_PWMHREN;
	tmp |= value << PWM_LEBR1_PWMHREN_Pos;
	((Pwm *)hw)->PWM_LEBR1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR1_PWMHREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 &= ~PWM_LEBR1_PWMHREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR1_PWMHREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 ^= PWM_LEBR1_PWMHREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_LEBR1_LEBDELAY_bf(const void *const hw, hri_pwm_lebr1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 |= PWM_LEBR1_LEBDELAY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_lebr1_reg_t hri_pwm_get_LEBR1_LEBDELAY_bf(const void *const hw, hri_pwm_lebr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp = (tmp & PWM_LEBR1_LEBDELAY(mask)) >> PWM_LEBR1_LEBDELAY_Pos;
	return tmp;
}

static inline void hri_pwm_write_LEBR1_LEBDELAY_bf(const void *const hw, hri_pwm_lebr1_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp &= ~PWM_LEBR1_LEBDELAY_Msk;
	tmp |= PWM_LEBR1_LEBDELAY(data);
	((Pwm *)hw)->PWM_LEBR1 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR1_LEBDELAY_bf(const void *const hw, hri_pwm_lebr1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 &= ~PWM_LEBR1_LEBDELAY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR1_LEBDELAY_bf(const void *const hw, hri_pwm_lebr1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 ^= PWM_LEBR1_LEBDELAY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_lebr1_reg_t hri_pwm_read_LEBR1_LEBDELAY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp = (tmp & PWM_LEBR1_LEBDELAY_Msk) >> PWM_LEBR1_LEBDELAY_Pos;
	return tmp;
}

static inline void hri_pwm_set_LEBR1_reg(const void *const hw, hri_pwm_lebr1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_lebr1_reg_t hri_pwm_get_LEBR1_reg(const void *const hw, hri_pwm_lebr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR1;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_LEBR1_reg(const void *const hw, hri_pwm_lebr1_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR1_reg(const void *const hw, hri_pwm_lebr1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR1_reg(const void *const hw, hri_pwm_lebr1_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR1 ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_lebr1_reg_t hri_pwm_read_LEBR1_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_LEBR1;
}

static inline void hri_pwm_set_ETRG2_TRGEDGE_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 |= PWM_ETRG2_TRGEDGE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ETRG2_TRGEDGE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp = (tmp & PWM_ETRG2_TRGEDGE) >> PWM_ETRG2_TRGEDGE_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ETRG2_TRGEDGE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp &= ~PWM_ETRG2_TRGEDGE;
	tmp |= value << PWM_ETRG2_TRGEDGE_Pos;
	((Pwm *)hw)->PWM_ETRG2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG2_TRGEDGE_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 &= ~PWM_ETRG2_TRGEDGE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG2_TRGEDGE_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 ^= PWM_ETRG2_TRGEDGE;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ETRG2_TRGFILT_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 |= PWM_ETRG2_TRGFILT;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ETRG2_TRGFILT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp = (tmp & PWM_ETRG2_TRGFILT) >> PWM_ETRG2_TRGFILT_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ETRG2_TRGFILT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp &= ~PWM_ETRG2_TRGFILT;
	tmp |= value << PWM_ETRG2_TRGFILT_Pos;
	((Pwm *)hw)->PWM_ETRG2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG2_TRGFILT_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 &= ~PWM_ETRG2_TRGFILT;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG2_TRGFILT_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 ^= PWM_ETRG2_TRGFILT;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ETRG2_TRGSRC_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 |= PWM_ETRG2_TRGSRC;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ETRG2_TRGSRC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp = (tmp & PWM_ETRG2_TRGSRC) >> PWM_ETRG2_TRGSRC_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ETRG2_TRGSRC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp &= ~PWM_ETRG2_TRGSRC;
	tmp |= value << PWM_ETRG2_TRGSRC_Pos;
	((Pwm *)hw)->PWM_ETRG2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG2_TRGSRC_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 &= ~PWM_ETRG2_TRGSRC;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG2_TRGSRC_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 ^= PWM_ETRG2_TRGSRC;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ETRG2_RFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 |= PWM_ETRG2_RFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_ETRG2_RFEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp = (tmp & PWM_ETRG2_RFEN) >> PWM_ETRG2_RFEN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_ETRG2_RFEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp &= ~PWM_ETRG2_RFEN;
	tmp |= value << PWM_ETRG2_RFEN_Pos;
	((Pwm *)hw)->PWM_ETRG2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG2_RFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 &= ~PWM_ETRG2_RFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG2_RFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 ^= PWM_ETRG2_RFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_ETRG2_MAXCNT_bf(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 |= PWM_ETRG2_MAXCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg2_reg_t hri_pwm_get_ETRG2_MAXCNT_bf(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp = (tmp & PWM_ETRG2_MAXCNT(mask)) >> PWM_ETRG2_MAXCNT_Pos;
	return tmp;
}

static inline void hri_pwm_write_ETRG2_MAXCNT_bf(const void *const hw, hri_pwm_etrg2_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp &= ~PWM_ETRG2_MAXCNT_Msk;
	tmp |= PWM_ETRG2_MAXCNT(data);
	((Pwm *)hw)->PWM_ETRG2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG2_MAXCNT_bf(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 &= ~PWM_ETRG2_MAXCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG2_MAXCNT_bf(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 ^= PWM_ETRG2_MAXCNT(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg2_reg_t hri_pwm_read_ETRG2_MAXCNT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp = (tmp & PWM_ETRG2_MAXCNT_Msk) >> PWM_ETRG2_MAXCNT_Pos;
	return tmp;
}

static inline void hri_pwm_set_ETRG2_TRGMODE_bf(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 |= PWM_ETRG2_TRGMODE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg2_reg_t hri_pwm_get_ETRG2_TRGMODE_bf(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp = (tmp & PWM_ETRG2_TRGMODE(mask)) >> PWM_ETRG2_TRGMODE_Pos;
	return tmp;
}

static inline void hri_pwm_write_ETRG2_TRGMODE_bf(const void *const hw, hri_pwm_etrg2_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp &= ~PWM_ETRG2_TRGMODE_Msk;
	tmp |= PWM_ETRG2_TRGMODE(data);
	((Pwm *)hw)->PWM_ETRG2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG2_TRGMODE_bf(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 &= ~PWM_ETRG2_TRGMODE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG2_TRGMODE_bf(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 ^= PWM_ETRG2_TRGMODE(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg2_reg_t hri_pwm_read_ETRG2_TRGMODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp = (tmp & PWM_ETRG2_TRGMODE_Msk) >> PWM_ETRG2_TRGMODE_Pos;
	return tmp;
}

static inline void hri_pwm_set_ETRG2_reg(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg2_reg_t hri_pwm_get_ETRG2_reg(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_ETRG2;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_ETRG2_reg(const void *const hw, hri_pwm_etrg2_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_ETRG2_reg(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_ETRG2_reg(const void *const hw, hri_pwm_etrg2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ETRG2 ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_etrg2_reg_t hri_pwm_read_ETRG2_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_ETRG2;
}

static inline void hri_pwm_set_LEBR2_PWMLFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 |= PWM_LEBR2_PWMLFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_LEBR2_PWMLFEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp = (tmp & PWM_LEBR2_PWMLFEN) >> PWM_LEBR2_PWMLFEN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_LEBR2_PWMLFEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp &= ~PWM_LEBR2_PWMLFEN;
	tmp |= value << PWM_LEBR2_PWMLFEN_Pos;
	((Pwm *)hw)->PWM_LEBR2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR2_PWMLFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 &= ~PWM_LEBR2_PWMLFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR2_PWMLFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 ^= PWM_LEBR2_PWMLFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_LEBR2_PWMLREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 |= PWM_LEBR2_PWMLREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_LEBR2_PWMLREN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp = (tmp & PWM_LEBR2_PWMLREN) >> PWM_LEBR2_PWMLREN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_LEBR2_PWMLREN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp &= ~PWM_LEBR2_PWMLREN;
	tmp |= value << PWM_LEBR2_PWMLREN_Pos;
	((Pwm *)hw)->PWM_LEBR2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR2_PWMLREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 &= ~PWM_LEBR2_PWMLREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR2_PWMLREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 ^= PWM_LEBR2_PWMLREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_LEBR2_PWMHFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 |= PWM_LEBR2_PWMHFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_LEBR2_PWMHFEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp = (tmp & PWM_LEBR2_PWMHFEN) >> PWM_LEBR2_PWMHFEN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_LEBR2_PWMHFEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp &= ~PWM_LEBR2_PWMHFEN;
	tmp |= value << PWM_LEBR2_PWMHFEN_Pos;
	((Pwm *)hw)->PWM_LEBR2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR2_PWMHFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 &= ~PWM_LEBR2_PWMHFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR2_PWMHFEN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 ^= PWM_LEBR2_PWMHFEN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_LEBR2_PWMHREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 |= PWM_LEBR2_PWMHREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pwm_get_LEBR2_PWMHREN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp = (tmp & PWM_LEBR2_PWMHREN) >> PWM_LEBR2_PWMHREN_Pos;
	return (bool)tmp;
}

static inline void hri_pwm_write_LEBR2_PWMHREN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp &= ~PWM_LEBR2_PWMHREN;
	tmp |= value << PWM_LEBR2_PWMHREN_Pos;
	((Pwm *)hw)->PWM_LEBR2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR2_PWMHREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 &= ~PWM_LEBR2_PWMHREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR2_PWMHREN_bit(const void *const hw)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 ^= PWM_LEBR2_PWMHREN;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_set_LEBR2_LEBDELAY_bf(const void *const hw, hri_pwm_lebr2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 |= PWM_LEBR2_LEBDELAY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_lebr2_reg_t hri_pwm_get_LEBR2_LEBDELAY_bf(const void *const hw, hri_pwm_lebr2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp = (tmp & PWM_LEBR2_LEBDELAY(mask)) >> PWM_LEBR2_LEBDELAY_Pos;
	return tmp;
}

static inline void hri_pwm_write_LEBR2_LEBDELAY_bf(const void *const hw, hri_pwm_lebr2_reg_t data)
{
	uint32_t tmp;
	PWM_CRITICAL_SECTION_ENTER();
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp &= ~PWM_LEBR2_LEBDELAY_Msk;
	tmp |= PWM_LEBR2_LEBDELAY(data);
	((Pwm *)hw)->PWM_LEBR2 = tmp;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR2_LEBDELAY_bf(const void *const hw, hri_pwm_lebr2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 &= ~PWM_LEBR2_LEBDELAY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR2_LEBDELAY_bf(const void *const hw, hri_pwm_lebr2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 ^= PWM_LEBR2_LEBDELAY(mask);
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_lebr2_reg_t hri_pwm_read_LEBR2_LEBDELAY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp = (tmp & PWM_LEBR2_LEBDELAY_Msk) >> PWM_LEBR2_LEBDELAY_Pos;
	return tmp;
}

static inline void hri_pwm_set_LEBR2_reg(const void *const hw, hri_pwm_lebr2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 |= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_lebr2_reg_t hri_pwm_get_LEBR2_reg(const void *const hw, hri_pwm_lebr2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pwm *)hw)->PWM_LEBR2;
	tmp &= mask;
	return tmp;
}

static inline void hri_pwm_write_LEBR2_reg(const void *const hw, hri_pwm_lebr2_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_clear_LEBR2_reg(const void *const hw, hri_pwm_lebr2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 &= ~mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_toggle_LEBR2_reg(const void *const hw, hri_pwm_lebr2_reg_t mask)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_LEBR2 ^= mask;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline hri_pwm_lebr2_reg_t hri_pwm_read_LEBR2_reg(const void *const hw)
{
	return ((Pwm *)hw)->PWM_LEBR2;
}

static inline void hri_pwm_write_ENA_reg(const void *const hw, hri_pwm_ena_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_ENA = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_DIS_reg(const void *const hw, hri_pwm_dis_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_DIS = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_DMAR_reg(const void *const hw, hri_pwm_dmar_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_DMAR = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_SCUPUPD_reg(const void *const hw, hri_pwm_scupupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SCUPUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_OSS_reg(const void *const hw, hri_pwm_oss_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OSS = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_OSC_reg(const void *const hw, hri_pwm_osc_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OSC = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_OSSUPD_reg(const void *const hw, hri_pwm_ossupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OSSUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_OSCUPD_reg(const void *const hw, hri_pwm_oscupd_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_OSCUPD = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_FCR_reg(const void *const hw, hri_pwm_fcr_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_FCR = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_SSPUP_reg(const void *const hw, hri_pwm_sspup_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_SSPUP = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_WPCR_reg(const void *const hw, hri_pwm_wpcr_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_WPCR = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_CMUPD0_reg(const void *const hw, hri_pwm_cmupd0_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CMUPD0 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_CMUPD1_reg(const void *const hw, hri_pwm_cmupd1_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CMUPD1 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_CMUPD2_reg(const void *const hw, hri_pwm_cmupd2_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CMUPD2 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pwm_write_CMUPD3_reg(const void *const hw, hri_pwm_cmupd3_reg_t data)
{
	PWM_CRITICAL_SECTION_ENTER();
	((Pwm *)hw)->PWM_CMUPD3 = data;
	PWM_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_PWM_E70B_H_INCLUDED */
#endif /* _SAME70_PWM_COMPONENT_ */
