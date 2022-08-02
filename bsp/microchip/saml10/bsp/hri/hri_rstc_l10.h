/**
 * \file
 *
 * \brief SAM RSTC
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAML10_RSTC_COMPONENT_
#ifndef _HRI_RSTC_L10_H_INCLUDED_
#define _HRI_RSTC_L10_H_INCLUDED_

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

typedef uint8_t hri_rstc_rcause_reg_t;

static inline bool hri_rstc_get_RCAUSE_POR_bit(const void *const hw)
{
	return (((Rstc *)hw)->RCAUSE.reg & RSTC_RCAUSE_POR_Msk) >> RSTC_RCAUSE_POR_Pos;
}

static inline bool hri_rstc_get_RCAUSE_BODCORE_bit(const void *const hw)
{
	return (((Rstc *)hw)->RCAUSE.reg & RSTC_RCAUSE_BODCORE_Msk) >> RSTC_RCAUSE_BODCORE_Pos;
}

static inline bool hri_rstc_get_RCAUSE_BODVDD_bit(const void *const hw)
{
	return (((Rstc *)hw)->RCAUSE.reg & RSTC_RCAUSE_BODVDD_Msk) >> RSTC_RCAUSE_BODVDD_Pos;
}

static inline bool hri_rstc_get_RCAUSE_EXT_bit(const void *const hw)
{
	return (((Rstc *)hw)->RCAUSE.reg & RSTC_RCAUSE_EXT_Msk) >> RSTC_RCAUSE_EXT_Pos;
}

static inline bool hri_rstc_get_RCAUSE_WDT_bit(const void *const hw)
{
	return (((Rstc *)hw)->RCAUSE.reg & RSTC_RCAUSE_WDT_Msk) >> RSTC_RCAUSE_WDT_Pos;
}

static inline bool hri_rstc_get_RCAUSE_SYST_bit(const void *const hw)
{
	return (((Rstc *)hw)->RCAUSE.reg & RSTC_RCAUSE_SYST_Msk) >> RSTC_RCAUSE_SYST_Pos;
}

static inline hri_rstc_rcause_reg_t hri_rstc_get_RCAUSE_reg(const void *const hw, hri_rstc_rcause_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Rstc *)hw)->RCAUSE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rstc_rcause_reg_t hri_rstc_read_RCAUSE_reg(const void *const hw)
{
	return ((Rstc *)hw)->RCAUSE.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RSTC_L10_H_INCLUDED */
#endif /* _SAML10_RSTC_COMPONENT_ */
