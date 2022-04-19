/**
 * \file
 *
 * \brief SAM CHIPID
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

#ifdef _SAME70_CHIPID_COMPONENT_
#ifndef _HRI_CHIPID_E70B_H_INCLUDED_
#define _HRI_CHIPID_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_CHIPID_CRITICAL_SECTIONS)
#define CHIPID_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define CHIPID_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define CHIPID_CRITICAL_SECTION_ENTER()
#define CHIPID_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_chipid_cidr_reg_t;
typedef uint32_t hri_chipid_exid_reg_t;

static inline bool hri_chipid_get_CIDR_EXT_bit(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_EXT) > 0;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_VERSION_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_VERSION(mask)) >> CHIPID_CIDR_VERSION_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_VERSION_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_VERSION_Msk) >> CHIPID_CIDR_VERSION_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_EPROC_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_EPROC(mask)) >> CHIPID_CIDR_EPROC_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_EPROC_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_EPROC_Msk) >> CHIPID_CIDR_EPROC_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_NVPSIZ_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPSIZ(mask)) >> CHIPID_CIDR_NVPSIZ_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_NVPSIZ_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPSIZ_Msk) >> CHIPID_CIDR_NVPSIZ_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_NVPSIZ2_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPSIZ2(mask)) >> CHIPID_CIDR_NVPSIZ2_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_NVPSIZ2_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPSIZ2_Msk) >> CHIPID_CIDR_NVPSIZ2_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_SRAMSIZ_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_SRAMSIZ(mask)) >> CHIPID_CIDR_SRAMSIZ_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_SRAMSIZ_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_SRAMSIZ_Msk) >> CHIPID_CIDR_SRAMSIZ_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_ARCH_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_ARCH(mask)) >> CHIPID_CIDR_ARCH_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_ARCH_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_ARCH_Msk) >> CHIPID_CIDR_ARCH_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_NVPTYP_bf(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPTYP(mask)) >> CHIPID_CIDR_NVPTYP_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_NVPTYP_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_CIDR & CHIPID_CIDR_NVPTYP_Msk) >> CHIPID_CIDR_NVPTYP_Pos;
}

static inline hri_chipid_cidr_reg_t hri_chipid_get_CIDR_reg(const void *const hw, hri_chipid_cidr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Chipid *)hw)->CHIPID_CIDR;
	tmp &= mask;
	return tmp;
}

static inline hri_chipid_cidr_reg_t hri_chipid_read_CIDR_reg(const void *const hw)
{
	return ((Chipid *)hw)->CHIPID_CIDR;
}

static inline hri_chipid_exid_reg_t hri_chipid_get_EXID_EXID_bf(const void *const hw, hri_chipid_exid_reg_t mask)
{
	return (((Chipid *)hw)->CHIPID_EXID & CHIPID_EXID_EXID(mask)) >> CHIPID_EXID_EXID_Pos;
}

static inline hri_chipid_exid_reg_t hri_chipid_read_EXID_EXID_bf(const void *const hw)
{
	return (((Chipid *)hw)->CHIPID_EXID & CHIPID_EXID_EXID_Msk) >> CHIPID_EXID_EXID_Pos;
}

static inline hri_chipid_exid_reg_t hri_chipid_get_EXID_reg(const void *const hw, hri_chipid_exid_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Chipid *)hw)->CHIPID_EXID;
	tmp &= mask;
	return tmp;
}

static inline hri_chipid_exid_reg_t hri_chipid_read_EXID_reg(const void *const hw)
{
	return ((Chipid *)hw)->CHIPID_EXID;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_CHIPID_E70B_H_INCLUDED */
#endif /* _SAME70_CHIPID_COMPONENT_ */
