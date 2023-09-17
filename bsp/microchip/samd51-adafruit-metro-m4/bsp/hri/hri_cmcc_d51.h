/**
 * \file
 *
 * \brief SAM CMCC
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

#ifdef _SAMD51_CMCC_COMPONENT_
#ifndef _HRI_CMCC_D51_H_INCLUDED_
#define _HRI_CMCC_D51_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_CMCC_CRITICAL_SECTIONS)
#define CMCC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define CMCC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define CMCC_CRITICAL_SECTION_ENTER()
#define CMCC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_cmcc_cfg_reg_t;
typedef uint32_t hri_cmcc_ctrl_reg_t;
typedef uint32_t hri_cmcc_lckway_reg_t;
typedef uint32_t hri_cmcc_maint0_reg_t;
typedef uint32_t hri_cmcc_maint1_reg_t;
typedef uint32_t hri_cmcc_mcfg_reg_t;
typedef uint32_t hri_cmcc_mctrl_reg_t;
typedef uint32_t hri_cmcc_men_reg_t;
typedef uint32_t hri_cmcc_msr_reg_t;
typedef uint32_t hri_cmcc_sr_reg_t;
typedef uint32_t hri_cmcc_type_reg_t;

static inline bool hri_cmcc_get_TYPE_GCLK_bit(const void *const hw)
{
	return (((Cmcc *)hw)->TYPE.reg & CMCC_TYPE_GCLK) >> CMCC_TYPE_GCLK_Pos;
}

static inline bool hri_cmcc_get_TYPE_RRP_bit(const void *const hw)
{
	return (((Cmcc *)hw)->TYPE.reg & CMCC_TYPE_RRP) >> CMCC_TYPE_RRP_Pos;
}

static inline bool hri_cmcc_get_TYPE_LCKDOWN_bit(const void *const hw)
{
	return (((Cmcc *)hw)->TYPE.reg & CMCC_TYPE_LCKDOWN) >> CMCC_TYPE_LCKDOWN_Pos;
}

static inline hri_cmcc_type_reg_t hri_cmcc_get_TYPE_WAYNUM_bf(const void *const hw, hri_cmcc_type_reg_t mask)
{
	return (((Cmcc *)hw)->TYPE.reg & CMCC_TYPE_WAYNUM(mask)) >> CMCC_TYPE_WAYNUM_Pos;
}

static inline hri_cmcc_type_reg_t hri_cmcc_read_TYPE_WAYNUM_bf(const void *const hw)
{
	return (((Cmcc *)hw)->TYPE.reg & CMCC_TYPE_WAYNUM_Msk) >> CMCC_TYPE_WAYNUM_Pos;
}

static inline hri_cmcc_type_reg_t hri_cmcc_get_TYPE_CSIZE_bf(const void *const hw, hri_cmcc_type_reg_t mask)
{
	return (((Cmcc *)hw)->TYPE.reg & CMCC_TYPE_CSIZE(mask)) >> CMCC_TYPE_CSIZE_Pos;
}

static inline hri_cmcc_type_reg_t hri_cmcc_read_TYPE_CSIZE_bf(const void *const hw)
{
	return (((Cmcc *)hw)->TYPE.reg & CMCC_TYPE_CSIZE_Msk) >> CMCC_TYPE_CSIZE_Pos;
}

static inline hri_cmcc_type_reg_t hri_cmcc_get_TYPE_CLSIZE_bf(const void *const hw, hri_cmcc_type_reg_t mask)
{
	return (((Cmcc *)hw)->TYPE.reg & CMCC_TYPE_CLSIZE(mask)) >> CMCC_TYPE_CLSIZE_Pos;
}

static inline hri_cmcc_type_reg_t hri_cmcc_read_TYPE_CLSIZE_bf(const void *const hw)
{
	return (((Cmcc *)hw)->TYPE.reg & CMCC_TYPE_CLSIZE_Msk) >> CMCC_TYPE_CLSIZE_Pos;
}

static inline hri_cmcc_type_reg_t hri_cmcc_get_TYPE_reg(const void *const hw, hri_cmcc_type_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Cmcc *)hw)->TYPE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_cmcc_type_reg_t hri_cmcc_read_TYPE_reg(const void *const hw)
{
	return ((Cmcc *)hw)->TYPE.reg;
}

static inline bool hri_cmcc_get_SR_CSTS_bit(const void *const hw)
{
	return (((Cmcc *)hw)->SR.reg & CMCC_SR_CSTS) >> CMCC_SR_CSTS_Pos;
}

static inline hri_cmcc_sr_reg_t hri_cmcc_get_SR_reg(const void *const hw, hri_cmcc_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Cmcc *)hw)->SR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_cmcc_sr_reg_t hri_cmcc_read_SR_reg(const void *const hw)
{
	return ((Cmcc *)hw)->SR.reg;
}

static inline hri_cmcc_msr_reg_t hri_cmcc_get_MSR_EVENT_CNT_bf(const void *const hw, hri_cmcc_msr_reg_t mask)
{
	return (((Cmcc *)hw)->MSR.reg & CMCC_MSR_EVENT_CNT(mask)) >> CMCC_MSR_EVENT_CNT_Pos;
}

static inline hri_cmcc_msr_reg_t hri_cmcc_read_MSR_EVENT_CNT_bf(const void *const hw)
{
	return (((Cmcc *)hw)->MSR.reg & CMCC_MSR_EVENT_CNT_Msk) >> CMCC_MSR_EVENT_CNT_Pos;
}

static inline hri_cmcc_msr_reg_t hri_cmcc_get_MSR_reg(const void *const hw, hri_cmcc_msr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Cmcc *)hw)->MSR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_cmcc_msr_reg_t hri_cmcc_read_MSR_reg(const void *const hw)
{
	return ((Cmcc *)hw)->MSR.reg;
}

static inline void hri_cmcc_set_CFG_reg(const void *const hw, hri_cmcc_cfg_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->CFG.reg |= mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_cmcc_cfg_reg_t hri_cmcc_get_CFG_reg(const void *const hw, hri_cmcc_cfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Cmcc *)hw)->CFG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_cmcc_write_CFG_reg(const void *const hw, hri_cmcc_cfg_reg_t data)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->CFG.reg = data;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_clear_CFG_reg(const void *const hw, hri_cmcc_cfg_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->CFG.reg &= ~mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_toggle_CFG_reg(const void *const hw, hri_cmcc_cfg_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->CFG.reg ^= mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_cmcc_cfg_reg_t hri_cmcc_read_CFG_reg(const void *const hw)
{
	return ((Cmcc *)hw)->CFG.reg;
}

static inline void hri_cmcc_set_LCKWAY_reg(const void *const hw, hri_cmcc_lckway_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->LCKWAY.reg |= mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_cmcc_lckway_reg_t hri_cmcc_get_LCKWAY_reg(const void *const hw, hri_cmcc_lckway_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Cmcc *)hw)->LCKWAY.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_cmcc_write_LCKWAY_reg(const void *const hw, hri_cmcc_lckway_reg_t data)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->LCKWAY.reg = data;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_clear_LCKWAY_reg(const void *const hw, hri_cmcc_lckway_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->LCKWAY.reg &= ~mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_toggle_LCKWAY_reg(const void *const hw, hri_cmcc_lckway_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->LCKWAY.reg ^= mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_cmcc_lckway_reg_t hri_cmcc_read_LCKWAY_reg(const void *const hw)
{
	return ((Cmcc *)hw)->LCKWAY.reg;
}

static inline void hri_cmcc_set_MCFG_reg(const void *const hw, hri_cmcc_mcfg_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MCFG.reg |= mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_cmcc_mcfg_reg_t hri_cmcc_get_MCFG_reg(const void *const hw, hri_cmcc_mcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Cmcc *)hw)->MCFG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_cmcc_write_MCFG_reg(const void *const hw, hri_cmcc_mcfg_reg_t data)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MCFG.reg = data;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_clear_MCFG_reg(const void *const hw, hri_cmcc_mcfg_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MCFG.reg &= ~mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_toggle_MCFG_reg(const void *const hw, hri_cmcc_mcfg_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MCFG.reg ^= mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_cmcc_mcfg_reg_t hri_cmcc_read_MCFG_reg(const void *const hw)
{
	return ((Cmcc *)hw)->MCFG.reg;
}

static inline void hri_cmcc_set_MEN_reg(const void *const hw, hri_cmcc_men_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MEN.reg |= mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_cmcc_men_reg_t hri_cmcc_get_MEN_reg(const void *const hw, hri_cmcc_men_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Cmcc *)hw)->MEN.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_cmcc_write_MEN_reg(const void *const hw, hri_cmcc_men_reg_t data)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MEN.reg = data;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_clear_MEN_reg(const void *const hw, hri_cmcc_men_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MEN.reg &= ~mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_toggle_MEN_reg(const void *const hw, hri_cmcc_men_reg_t mask)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MEN.reg ^= mask;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_cmcc_men_reg_t hri_cmcc_read_MEN_reg(const void *const hw)
{
	return ((Cmcc *)hw)->MEN.reg;
}

static inline void hri_cmcc_write_CTRL_reg(const void *const hw, hri_cmcc_ctrl_reg_t data)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->CTRL.reg = data;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_write_MAINT0_reg(const void *const hw, hri_cmcc_maint0_reg_t data)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MAINT0.reg = data;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_write_MAINT1_reg(const void *const hw, hri_cmcc_maint1_reg_t data)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MAINT1.reg = data;
	CMCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_cmcc_write_MCTRL_reg(const void *const hw, hri_cmcc_mctrl_reg_t data)
{
	CMCC_CRITICAL_SECTION_ENTER();
	((Cmcc *)hw)->MCTRL.reg = data;
	CMCC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_CMCC_D51_H_INCLUDED */
#endif /* _SAMD51_CMCC_COMPONENT_ */
