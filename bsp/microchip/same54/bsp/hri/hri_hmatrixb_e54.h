/**
 * \file
 *
 * \brief SAM HMATRIXB
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

#ifdef _SAME54_HMATRIXB_COMPONENT_
#ifndef _HRI_HMATRIXB_E54_H_INCLUDED_
#define _HRI_HMATRIXB_E54_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_HMATRIXB_CRITICAL_SECTIONS)
#define HMATRIXB_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define HMATRIXB_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define HMATRIXB_CRITICAL_SECTION_ENTER()
#define HMATRIXB_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_hmatrixb_pras_reg_t;
typedef uint32_t hri_hmatrixb_prbs_reg_t;
typedef uint32_t hri_hmatrixbprs_pras_reg_t;
typedef uint32_t hri_hmatrixbprs_prbs_reg_t;

static inline void hri_hmatrixbprs_set_PRAS_reg(const void *const hw, hri_hmatrixb_pras_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((HmatrixbPrs *)hw)->PRAS.reg |= mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline hri_hmatrixb_pras_reg_t hri_hmatrixbprs_get_PRAS_reg(const void *const hw, hri_hmatrixb_pras_reg_t mask)
{
	uint32_t tmp;
	tmp = ((HmatrixbPrs *)hw)->PRAS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_hmatrixbprs_write_PRAS_reg(const void *const hw, hri_hmatrixb_pras_reg_t data)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((HmatrixbPrs *)hw)->PRAS.reg = data;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hmatrixbprs_clear_PRAS_reg(const void *const hw, hri_hmatrixb_pras_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((HmatrixbPrs *)hw)->PRAS.reg &= ~mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hmatrixbprs_toggle_PRAS_reg(const void *const hw, hri_hmatrixb_pras_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((HmatrixbPrs *)hw)->PRAS.reg ^= mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline hri_hmatrixb_pras_reg_t hri_hmatrixbprs_read_PRAS_reg(const void *const hw)
{
	return ((HmatrixbPrs *)hw)->PRAS.reg;
}

static inline void hri_hmatrixbprs_set_PRBS_reg(const void *const hw, hri_hmatrixb_prbs_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((HmatrixbPrs *)hw)->PRBS.reg |= mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline hri_hmatrixb_prbs_reg_t hri_hmatrixbprs_get_PRBS_reg(const void *const hw, hri_hmatrixb_prbs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((HmatrixbPrs *)hw)->PRBS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_hmatrixbprs_write_PRBS_reg(const void *const hw, hri_hmatrixb_prbs_reg_t data)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((HmatrixbPrs *)hw)->PRBS.reg = data;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hmatrixbprs_clear_PRBS_reg(const void *const hw, hri_hmatrixb_prbs_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((HmatrixbPrs *)hw)->PRBS.reg &= ~mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hmatrixbprs_toggle_PRBS_reg(const void *const hw, hri_hmatrixb_prbs_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((HmatrixbPrs *)hw)->PRBS.reg ^= mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline hri_hmatrixb_prbs_reg_t hri_hmatrixbprs_read_PRBS_reg(const void *const hw)
{
	return ((HmatrixbPrs *)hw)->PRBS.reg;
}

static inline void hri_hmatrixb_set_PRAS_reg(const void *const hw, uint8_t submodule_index,
                                             hri_hmatrixb_pras_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((Hmatrixb *)hw)->Prs[submodule_index].PRAS.reg |= mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline hri_hmatrixb_pras_reg_t hri_hmatrixb_get_PRAS_reg(const void *const hw, uint8_t submodule_index,
                                                                hri_hmatrixb_pras_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hmatrixb *)hw)->Prs[submodule_index].PRAS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_hmatrixb_write_PRAS_reg(const void *const hw, uint8_t submodule_index,
                                               hri_hmatrixb_pras_reg_t data)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((Hmatrixb *)hw)->Prs[submodule_index].PRAS.reg = data;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hmatrixb_clear_PRAS_reg(const void *const hw, uint8_t submodule_index,
                                               hri_hmatrixb_pras_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((Hmatrixb *)hw)->Prs[submodule_index].PRAS.reg &= ~mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hmatrixb_toggle_PRAS_reg(const void *const hw, uint8_t submodule_index,
                                                hri_hmatrixb_pras_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((Hmatrixb *)hw)->Prs[submodule_index].PRAS.reg ^= mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline hri_hmatrixb_pras_reg_t hri_hmatrixb_read_PRAS_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Hmatrixb *)hw)->Prs[submodule_index].PRAS.reg;
}

static inline void hri_hmatrixb_set_PRBS_reg(const void *const hw, uint8_t submodule_index,
                                             hri_hmatrixb_prbs_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((Hmatrixb *)hw)->Prs[submodule_index].PRBS.reg |= mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline hri_hmatrixb_prbs_reg_t hri_hmatrixb_get_PRBS_reg(const void *const hw, uint8_t submodule_index,
                                                                hri_hmatrixb_prbs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hmatrixb *)hw)->Prs[submodule_index].PRBS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_hmatrixb_write_PRBS_reg(const void *const hw, uint8_t submodule_index,
                                               hri_hmatrixb_prbs_reg_t data)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((Hmatrixb *)hw)->Prs[submodule_index].PRBS.reg = data;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hmatrixb_clear_PRBS_reg(const void *const hw, uint8_t submodule_index,
                                               hri_hmatrixb_prbs_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((Hmatrixb *)hw)->Prs[submodule_index].PRBS.reg &= ~mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hmatrixb_toggle_PRBS_reg(const void *const hw, uint8_t submodule_index,
                                                hri_hmatrixb_prbs_reg_t mask)
{
	HMATRIXB_CRITICAL_SECTION_ENTER();
	((Hmatrixb *)hw)->Prs[submodule_index].PRBS.reg ^= mask;
	HMATRIXB_CRITICAL_SECTION_LEAVE();
}

static inline hri_hmatrixb_prbs_reg_t hri_hmatrixb_read_PRBS_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Hmatrixb *)hw)->Prs[submodule_index].PRBS.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_HMATRIXB_E54_H_INCLUDED */
#endif /* _SAME54_HMATRIXB_COMPONENT_ */
