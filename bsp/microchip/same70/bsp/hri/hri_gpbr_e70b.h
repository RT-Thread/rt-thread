/**
 * \file
 *
 * \brief SAM GPBR
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

#ifdef _SAME70_GPBR_COMPONENT_
#ifndef _HRI_GPBR_E70B_H_INCLUDED_
#define _HRI_GPBR_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_GPBR_CRITICAL_SECTIONS)
#define GPBR_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define GPBR_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define GPBR_CRITICAL_SECTION_ENTER()
#define GPBR_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_gpbr_sys_gpbr_reg_t;

static inline void hri_gpbr_set_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                       hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] |= GPBR_SYS_GPBR_GPBR_VALUE(mask);
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline hri_gpbr_sys_gpbr_reg_t hri_gpbr_get_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                                          hri_gpbr_sys_gpbr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gpbr *)hw)->SYS_GPBR[index];
	tmp = (tmp & GPBR_SYS_GPBR_GPBR_VALUE(mask)) >> GPBR_SYS_GPBR_GPBR_VALUE_Pos;
	return tmp;
}

static inline void hri_gpbr_write_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                         hri_gpbr_sys_gpbr_reg_t data)
{
	uint32_t tmp;
	GPBR_CRITICAL_SECTION_ENTER();
	tmp = ((Gpbr *)hw)->SYS_GPBR[index];
	tmp &= ~GPBR_SYS_GPBR_GPBR_VALUE_Msk;
	tmp |= GPBR_SYS_GPBR_GPBR_VALUE(data);
	((Gpbr *)hw)->SYS_GPBR[index] = tmp;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gpbr_clear_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                         hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] &= ~GPBR_SYS_GPBR_GPBR_VALUE(mask);
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gpbr_toggle_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index,
                                                          hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] ^= GPBR_SYS_GPBR_GPBR_VALUE(mask);
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline hri_gpbr_sys_gpbr_reg_t hri_gpbr_read_SYS_GPBR_GPBR_VALUE_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Gpbr *)hw)->SYS_GPBR[index];
	tmp = (tmp & GPBR_SYS_GPBR_GPBR_VALUE_Msk) >> GPBR_SYS_GPBR_GPBR_VALUE_Pos;
	return tmp;
}

static inline void hri_gpbr_set_SYS_GPBR_reg(const void *const hw, uint8_t index, hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] |= mask;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline hri_gpbr_sys_gpbr_reg_t hri_gpbr_get_SYS_GPBR_reg(const void *const hw, uint8_t index,
                                                                hri_gpbr_sys_gpbr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Gpbr *)hw)->SYS_GPBR[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_gpbr_write_SYS_GPBR_reg(const void *const hw, uint8_t index, hri_gpbr_sys_gpbr_reg_t data)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] = data;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gpbr_clear_SYS_GPBR_reg(const void *const hw, uint8_t index, hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] &= ~mask;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline void hri_gpbr_toggle_SYS_GPBR_reg(const void *const hw, uint8_t index, hri_gpbr_sys_gpbr_reg_t mask)
{
	GPBR_CRITICAL_SECTION_ENTER();
	((Gpbr *)hw)->SYS_GPBR[index] ^= mask;
	GPBR_CRITICAL_SECTION_LEAVE();
}

static inline hri_gpbr_sys_gpbr_reg_t hri_gpbr_read_SYS_GPBR_reg(const void *const hw, uint8_t index)
{
	return ((Gpbr *)hw)->SYS_GPBR[index];
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_GPBR_E70B_H_INCLUDED */
#endif /* _SAME70_GPBR_COMPONENT_ */
