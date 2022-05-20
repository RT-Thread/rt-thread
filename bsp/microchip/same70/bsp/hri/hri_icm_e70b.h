/**
 * \file
 *
 * \brief SAM ICM
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

#ifdef _SAME70_ICM_COMPONENT_
#ifndef _HRI_ICM_E70B_H_INCLUDED_
#define _HRI_ICM_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_ICM_CRITICAL_SECTIONS)
#define ICM_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define ICM_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define ICM_CRITICAL_SECTION_ENTER()
#define ICM_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_icm_cfg_reg_t;
typedef uint32_t hri_icm_ctrl_reg_t;
typedef uint32_t hri_icm_dscr_reg_t;
typedef uint32_t hri_icm_hash_reg_t;
typedef uint32_t hri_icm_imr_reg_t;
typedef uint32_t hri_icm_isr_reg_t;
typedef uint32_t hri_icm_sr_reg_t;
typedef uint32_t hri_icm_uasr_reg_t;
typedef uint32_t hri_icm_uihval_reg_t;

static inline bool hri_icm_get_ISR_URAD_bit(const void *const hw)
{
	return (((Icm *)hw)->ICM_ISR & ICM_ISR_URAD) >> ICM_ISR_URAD_Pos;
}

static inline hri_icm_isr_reg_t hri_icm_get_ISR_reg(const void *const hw, hri_icm_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_icm_isr_reg_t hri_icm_read_ISR_reg(const void *const hw)
{
	return ((Icm *)hw)->ICM_ISR;
}

static inline void hri_icm_set_IMR_URAD_bit(const void *const hw)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_URAD;
}

static inline bool hri_icm_get_IMR_URAD_bit(const void *const hw)
{
	return (((Icm *)hw)->ICM_IMR & ICM_IMR_URAD) >> ICM_IMR_URAD_Pos;
}

static inline void hri_icm_write_IMR_URAD_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Icm *)hw)->ICM_IDR = ICM_IMR_URAD;
	} else {
		((Icm *)hw)->ICM_IER = ICM_IMR_URAD;
	}
}

static inline void hri_icm_clear_IMR_URAD_bit(const void *const hw)
{
	((Icm *)hw)->ICM_IDR = ICM_IMR_URAD;
}

static inline void hri_icm_set_IMR_RHC_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RHC(mask);
}

static inline hri_icm_imr_reg_t hri_icm_get_IMR_RHC_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RHC(mask)) >> ICM_IMR_RHC_Pos;
	return tmp;
}

static inline hri_icm_imr_reg_t hri_icm_read_IMR_RHC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RHC_Msk) >> ICM_IMR_RHC_Pos;
	return tmp;
}

static inline void hri_icm_write_IMR_RHC_bf(const void *const hw, hri_icm_imr_reg_t data)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RHC(data);
	((Icm *)hw)->ICM_IDR = ~ICM_IMR_RHC(data);
}

static inline void hri_icm_clear_IMR_RHC_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IDR = ICM_IMR_RHC(mask);
}

static inline void hri_icm_set_IMR_RDM_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RDM(mask);
}

static inline hri_icm_imr_reg_t hri_icm_get_IMR_RDM_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RDM(mask)) >> ICM_IMR_RDM_Pos;
	return tmp;
}

static inline hri_icm_imr_reg_t hri_icm_read_IMR_RDM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RDM_Msk) >> ICM_IMR_RDM_Pos;
	return tmp;
}

static inline void hri_icm_write_IMR_RDM_bf(const void *const hw, hri_icm_imr_reg_t data)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RDM(data);
	((Icm *)hw)->ICM_IDR = ~ICM_IMR_RDM(data);
}

static inline void hri_icm_clear_IMR_RDM_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IDR = ICM_IMR_RDM(mask);
}

static inline void hri_icm_set_IMR_RBE_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RBE(mask);
}

static inline hri_icm_imr_reg_t hri_icm_get_IMR_RBE_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RBE(mask)) >> ICM_IMR_RBE_Pos;
	return tmp;
}

static inline hri_icm_imr_reg_t hri_icm_read_IMR_RBE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RBE_Msk) >> ICM_IMR_RBE_Pos;
	return tmp;
}

static inline void hri_icm_write_IMR_RBE_bf(const void *const hw, hri_icm_imr_reg_t data)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RBE(data);
	((Icm *)hw)->ICM_IDR = ~ICM_IMR_RBE(data);
}

static inline void hri_icm_clear_IMR_RBE_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IDR = ICM_IMR_RBE(mask);
}

static inline void hri_icm_set_IMR_RWC_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RWC(mask);
}

static inline hri_icm_imr_reg_t hri_icm_get_IMR_RWC_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RWC(mask)) >> ICM_IMR_RWC_Pos;
	return tmp;
}

static inline hri_icm_imr_reg_t hri_icm_read_IMR_RWC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RWC_Msk) >> ICM_IMR_RWC_Pos;
	return tmp;
}

static inline void hri_icm_write_IMR_RWC_bf(const void *const hw, hri_icm_imr_reg_t data)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RWC(data);
	((Icm *)hw)->ICM_IDR = ~ICM_IMR_RWC(data);
}

static inline void hri_icm_clear_IMR_RWC_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IDR = ICM_IMR_RWC(mask);
}

static inline void hri_icm_set_IMR_REC_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_REC(mask);
}

static inline hri_icm_imr_reg_t hri_icm_get_IMR_REC_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_REC(mask)) >> ICM_IMR_REC_Pos;
	return tmp;
}

static inline hri_icm_imr_reg_t hri_icm_read_IMR_REC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_REC_Msk) >> ICM_IMR_REC_Pos;
	return tmp;
}

static inline void hri_icm_write_IMR_REC_bf(const void *const hw, hri_icm_imr_reg_t data)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_REC(data);
	((Icm *)hw)->ICM_IDR = ~ICM_IMR_REC(data);
}

static inline void hri_icm_clear_IMR_REC_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IDR = ICM_IMR_REC(mask);
}

static inline void hri_icm_set_IMR_RSU_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RSU(mask);
}

static inline hri_icm_imr_reg_t hri_icm_get_IMR_RSU_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RSU(mask)) >> ICM_IMR_RSU_Pos;
	return tmp;
}

static inline hri_icm_imr_reg_t hri_icm_read_IMR_RSU_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp = (tmp & ICM_IMR_RSU_Msk) >> ICM_IMR_RSU_Pos;
	return tmp;
}

static inline void hri_icm_write_IMR_RSU_bf(const void *const hw, hri_icm_imr_reg_t data)
{
	((Icm *)hw)->ICM_IER = ICM_IMR_RSU(data);
	((Icm *)hw)->ICM_IDR = ~ICM_IMR_RSU(data);
}

static inline void hri_icm_clear_IMR_RSU_bf(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IDR = ICM_IMR_RSU(mask);
}

static inline void hri_icm_set_IMR_reg(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IER = mask;
}

static inline hri_icm_imr_reg_t hri_icm_get_IMR_reg(const void *const hw, hri_icm_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_icm_imr_reg_t hri_icm_read_IMR_reg(const void *const hw)
{
	return ((Icm *)hw)->ICM_IMR;
}

static inline void hri_icm_write_IMR_reg(const void *const hw, hri_icm_imr_reg_t data)
{
	((Icm *)hw)->ICM_IER = data;
	((Icm *)hw)->ICM_IDR = ~data;
}

static inline void hri_icm_clear_IMR_reg(const void *const hw, hri_icm_imr_reg_t mask)
{
	((Icm *)hw)->ICM_IDR = mask;
}

static inline bool hri_icm_get_SR_ENABLE_bit(const void *const hw)
{
	return (((Icm *)hw)->ICM_SR & ICM_SR_ENABLE) > 0;
}

static inline hri_icm_sr_reg_t hri_icm_get_SR_RAWRMDIS_bf(const void *const hw, hri_icm_sr_reg_t mask)
{
	return (((Icm *)hw)->ICM_SR & ICM_SR_RAWRMDIS(mask)) >> ICM_SR_RAWRMDIS_Pos;
}

static inline hri_icm_sr_reg_t hri_icm_read_SR_RAWRMDIS_bf(const void *const hw)
{
	return (((Icm *)hw)->ICM_SR & ICM_SR_RAWRMDIS_Msk) >> ICM_SR_RAWRMDIS_Pos;
}

static inline hri_icm_sr_reg_t hri_icm_get_SR_RMDIS_bf(const void *const hw, hri_icm_sr_reg_t mask)
{
	return (((Icm *)hw)->ICM_SR & ICM_SR_RMDIS(mask)) >> ICM_SR_RMDIS_Pos;
}

static inline hri_icm_sr_reg_t hri_icm_read_SR_RMDIS_bf(const void *const hw)
{
	return (((Icm *)hw)->ICM_SR & ICM_SR_RMDIS_Msk) >> ICM_SR_RMDIS_Pos;
}

static inline hri_icm_sr_reg_t hri_icm_get_SR_reg(const void *const hw, hri_icm_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_icm_sr_reg_t hri_icm_read_SR_reg(const void *const hw)
{
	return ((Icm *)hw)->ICM_SR;
}

static inline hri_icm_uasr_reg_t hri_icm_get_UASR_URAT_bf(const void *const hw, hri_icm_uasr_reg_t mask)
{
	return (((Icm *)hw)->ICM_UASR & ICM_UASR_URAT(mask)) >> ICM_UASR_URAT_Pos;
}

static inline hri_icm_uasr_reg_t hri_icm_read_UASR_URAT_bf(const void *const hw)
{
	return (((Icm *)hw)->ICM_UASR & ICM_UASR_URAT_Msk) >> ICM_UASR_URAT_Pos;
}

static inline hri_icm_uasr_reg_t hri_icm_get_UASR_reg(const void *const hw, hri_icm_uasr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_UASR;
	tmp &= mask;
	return tmp;
}

static inline hri_icm_uasr_reg_t hri_icm_read_UASR_reg(const void *const hw)
{
	return ((Icm *)hw)->ICM_UASR;
}

static inline void hri_icm_set_CFG_WBDIS_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG |= ICM_CFG_WBDIS;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_icm_get_CFG_WBDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_WBDIS) >> ICM_CFG_WBDIS_Pos;
	return (bool)tmp;
}

static inline void hri_icm_write_CFG_WBDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp &= ~ICM_CFG_WBDIS;
	tmp |= value << ICM_CFG_WBDIS_Pos;
	((Icm *)hw)->ICM_CFG = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_CFG_WBDIS_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG &= ~ICM_CFG_WBDIS;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_CFG_WBDIS_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG ^= ICM_CFG_WBDIS;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_set_CFG_EOMDIS_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG |= ICM_CFG_EOMDIS;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_icm_get_CFG_EOMDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_EOMDIS) >> ICM_CFG_EOMDIS_Pos;
	return (bool)tmp;
}

static inline void hri_icm_write_CFG_EOMDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp &= ~ICM_CFG_EOMDIS;
	tmp |= value << ICM_CFG_EOMDIS_Pos;
	((Icm *)hw)->ICM_CFG = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_CFG_EOMDIS_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG &= ~ICM_CFG_EOMDIS;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_CFG_EOMDIS_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG ^= ICM_CFG_EOMDIS;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_set_CFG_SLBDIS_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG |= ICM_CFG_SLBDIS;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_icm_get_CFG_SLBDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_SLBDIS) >> ICM_CFG_SLBDIS_Pos;
	return (bool)tmp;
}

static inline void hri_icm_write_CFG_SLBDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp &= ~ICM_CFG_SLBDIS;
	tmp |= value << ICM_CFG_SLBDIS_Pos;
	((Icm *)hw)->ICM_CFG = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_CFG_SLBDIS_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG &= ~ICM_CFG_SLBDIS;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_CFG_SLBDIS_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG ^= ICM_CFG_SLBDIS;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_set_CFG_ASCD_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG |= ICM_CFG_ASCD;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_icm_get_CFG_ASCD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_ASCD) >> ICM_CFG_ASCD_Pos;
	return (bool)tmp;
}

static inline void hri_icm_write_CFG_ASCD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp &= ~ICM_CFG_ASCD;
	tmp |= value << ICM_CFG_ASCD_Pos;
	((Icm *)hw)->ICM_CFG = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_CFG_ASCD_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG &= ~ICM_CFG_ASCD;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_CFG_ASCD_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG ^= ICM_CFG_ASCD;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_set_CFG_DUALBUFF_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG |= ICM_CFG_DUALBUFF;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_icm_get_CFG_DUALBUFF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_DUALBUFF) >> ICM_CFG_DUALBUFF_Pos;
	return (bool)tmp;
}

static inline void hri_icm_write_CFG_DUALBUFF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp &= ~ICM_CFG_DUALBUFF;
	tmp |= value << ICM_CFG_DUALBUFF_Pos;
	((Icm *)hw)->ICM_CFG = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_CFG_DUALBUFF_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG &= ~ICM_CFG_DUALBUFF;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_CFG_DUALBUFF_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG ^= ICM_CFG_DUALBUFF;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_set_CFG_UIHASH_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG |= ICM_CFG_UIHASH;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_icm_get_CFG_UIHASH_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_UIHASH) >> ICM_CFG_UIHASH_Pos;
	return (bool)tmp;
}

static inline void hri_icm_write_CFG_UIHASH_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp &= ~ICM_CFG_UIHASH;
	tmp |= value << ICM_CFG_UIHASH_Pos;
	((Icm *)hw)->ICM_CFG = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_CFG_UIHASH_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG &= ~ICM_CFG_UIHASH;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_CFG_UIHASH_bit(const void *const hw)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG ^= ICM_CFG_UIHASH;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_set_CFG_BBC_bf(const void *const hw, hri_icm_cfg_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG |= ICM_CFG_BBC(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_cfg_reg_t hri_icm_get_CFG_BBC_bf(const void *const hw, hri_icm_cfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_BBC(mask)) >> ICM_CFG_BBC_Pos;
	return tmp;
}

static inline void hri_icm_write_CFG_BBC_bf(const void *const hw, hri_icm_cfg_reg_t data)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp &= ~ICM_CFG_BBC_Msk;
	tmp |= ICM_CFG_BBC(data);
	((Icm *)hw)->ICM_CFG = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_CFG_BBC_bf(const void *const hw, hri_icm_cfg_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG &= ~ICM_CFG_BBC(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_CFG_BBC_bf(const void *const hw, hri_icm_cfg_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG ^= ICM_CFG_BBC(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_cfg_reg_t hri_icm_read_CFG_BBC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_BBC_Msk) >> ICM_CFG_BBC_Pos;
	return tmp;
}

static inline void hri_icm_set_CFG_UALGO_bf(const void *const hw, hri_icm_cfg_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG |= ICM_CFG_UALGO(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_cfg_reg_t hri_icm_get_CFG_UALGO_bf(const void *const hw, hri_icm_cfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_UALGO(mask)) >> ICM_CFG_UALGO_Pos;
	return tmp;
}

static inline void hri_icm_write_CFG_UALGO_bf(const void *const hw, hri_icm_cfg_reg_t data)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp &= ~ICM_CFG_UALGO_Msk;
	tmp |= ICM_CFG_UALGO(data);
	((Icm *)hw)->ICM_CFG = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_CFG_UALGO_bf(const void *const hw, hri_icm_cfg_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG &= ~ICM_CFG_UALGO(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_CFG_UALGO_bf(const void *const hw, hri_icm_cfg_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG ^= ICM_CFG_UALGO(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_cfg_reg_t hri_icm_read_CFG_UALGO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp = (tmp & ICM_CFG_UALGO_Msk) >> ICM_CFG_UALGO_Pos;
	return tmp;
}

static inline void hri_icm_set_CFG_reg(const void *const hw, hri_icm_cfg_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG |= mask;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_cfg_reg_t hri_icm_get_CFG_reg(const void *const hw, hri_icm_cfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_CFG;
	tmp &= mask;
	return tmp;
}

static inline void hri_icm_write_CFG_reg(const void *const hw, hri_icm_cfg_reg_t data)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG = data;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_CFG_reg(const void *const hw, hri_icm_cfg_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG &= ~mask;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_CFG_reg(const void *const hw, hri_icm_cfg_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CFG ^= mask;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_cfg_reg_t hri_icm_read_CFG_reg(const void *const hw)
{
	return ((Icm *)hw)->ICM_CFG;
}

static inline void hri_icm_set_DSCR_DASA_bf(const void *const hw, hri_icm_dscr_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_DSCR |= ICM_DSCR_DASA(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_dscr_reg_t hri_icm_get_DSCR_DASA_bf(const void *const hw, hri_icm_dscr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_DSCR;
	tmp = (tmp & ICM_DSCR_DASA(mask)) >> ICM_DSCR_DASA_Pos;
	return tmp;
}

static inline void hri_icm_write_DSCR_DASA_bf(const void *const hw, hri_icm_dscr_reg_t data)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_DSCR;
	tmp &= ~ICM_DSCR_DASA_Msk;
	tmp |= ICM_DSCR_DASA(data);
	((Icm *)hw)->ICM_DSCR = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_DSCR_DASA_bf(const void *const hw, hri_icm_dscr_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_DSCR &= ~ICM_DSCR_DASA(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_DSCR_DASA_bf(const void *const hw, hri_icm_dscr_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_DSCR ^= ICM_DSCR_DASA(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_dscr_reg_t hri_icm_read_DSCR_DASA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_DSCR;
	tmp = (tmp & ICM_DSCR_DASA_Msk) >> ICM_DSCR_DASA_Pos;
	return tmp;
}

static inline void hri_icm_set_DSCR_reg(const void *const hw, hri_icm_dscr_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_DSCR |= mask;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_dscr_reg_t hri_icm_get_DSCR_reg(const void *const hw, hri_icm_dscr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_DSCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_icm_write_DSCR_reg(const void *const hw, hri_icm_dscr_reg_t data)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_DSCR = data;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_DSCR_reg(const void *const hw, hri_icm_dscr_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_DSCR &= ~mask;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_DSCR_reg(const void *const hw, hri_icm_dscr_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_DSCR ^= mask;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_dscr_reg_t hri_icm_read_DSCR_reg(const void *const hw)
{
	return ((Icm *)hw)->ICM_DSCR;
}

static inline void hri_icm_set_HASH_HASA_bf(const void *const hw, hri_icm_hash_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_HASH |= ICM_HASH_HASA(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_hash_reg_t hri_icm_get_HASH_HASA_bf(const void *const hw, hri_icm_hash_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_HASH;
	tmp = (tmp & ICM_HASH_HASA(mask)) >> ICM_HASH_HASA_Pos;
	return tmp;
}

static inline void hri_icm_write_HASH_HASA_bf(const void *const hw, hri_icm_hash_reg_t data)
{
	uint32_t tmp;
	ICM_CRITICAL_SECTION_ENTER();
	tmp = ((Icm *)hw)->ICM_HASH;
	tmp &= ~ICM_HASH_HASA_Msk;
	tmp |= ICM_HASH_HASA(data);
	((Icm *)hw)->ICM_HASH = tmp;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_HASH_HASA_bf(const void *const hw, hri_icm_hash_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_HASH &= ~ICM_HASH_HASA(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_HASH_HASA_bf(const void *const hw, hri_icm_hash_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_HASH ^= ICM_HASH_HASA(mask);
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_hash_reg_t hri_icm_read_HASH_HASA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_HASH;
	tmp = (tmp & ICM_HASH_HASA_Msk) >> ICM_HASH_HASA_Pos;
	return tmp;
}

static inline void hri_icm_set_HASH_reg(const void *const hw, hri_icm_hash_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_HASH |= mask;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_hash_reg_t hri_icm_get_HASH_reg(const void *const hw, hri_icm_hash_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Icm *)hw)->ICM_HASH;
	tmp &= mask;
	return tmp;
}

static inline void hri_icm_write_HASH_reg(const void *const hw, hri_icm_hash_reg_t data)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_HASH = data;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_clear_HASH_reg(const void *const hw, hri_icm_hash_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_HASH &= ~mask;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_toggle_HASH_reg(const void *const hw, hri_icm_hash_reg_t mask)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_HASH ^= mask;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline hri_icm_hash_reg_t hri_icm_read_HASH_reg(const void *const hw)
{
	return ((Icm *)hw)->ICM_HASH;
}

static inline void hri_icm_write_CTRL_reg(const void *const hw, hri_icm_ctrl_reg_t data)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_CTRL = data;
	ICM_CRITICAL_SECTION_LEAVE();
}

static inline void hri_icm_write_UIHVAL_reg(const void *const hw, uint8_t index, hri_icm_uihval_reg_t data)
{
	ICM_CRITICAL_SECTION_ENTER();
	((Icm *)hw)->ICM_UIHVAL[index] = data;
	ICM_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_ICM_E70B_H_INCLUDED */
#endif /* _SAME70_ICM_COMPONENT_ */
