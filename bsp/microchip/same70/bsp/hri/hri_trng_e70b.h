/**
 * \file
 *
 * \brief SAM TRNG
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

#ifdef _SAME70_TRNG_COMPONENT_
#ifndef _HRI_TRNG_E70B_H_INCLUDED_
#define _HRI_TRNG_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_TRNG_CRITICAL_SECTIONS)
#define TRNG_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define TRNG_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define TRNG_CRITICAL_SECTION_ENTER()
#define TRNG_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_trng_cr_reg_t;
typedef uint32_t hri_trng_imr_reg_t;
typedef uint32_t hri_trng_isr_reg_t;
typedef uint32_t hri_trng_odata_reg_t;

static inline bool hri_trng_get_ISR_DATRDY_bit(const void *const hw)
{
	return (((Trng *)hw)->TRNG_ISR & TRNG_ISR_DATRDY) >> TRNG_ISR_DATRDY_Pos;
}

static inline hri_trng_isr_reg_t hri_trng_get_ISR_reg(const void *const hw, hri_trng_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Trng *)hw)->TRNG_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_trng_isr_reg_t hri_trng_read_ISR_reg(const void *const hw)
{
	return ((Trng *)hw)->TRNG_ISR;
}

static inline void hri_trng_set_IMR_DATRDY_bit(const void *const hw)
{
	((Trng *)hw)->TRNG_IER = TRNG_IMR_DATRDY;
}

static inline bool hri_trng_get_IMR_DATRDY_bit(const void *const hw)
{
	return (((Trng *)hw)->TRNG_IMR & TRNG_IMR_DATRDY) >> TRNG_IMR_DATRDY_Pos;
}

static inline void hri_trng_write_IMR_DATRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Trng *)hw)->TRNG_IDR = TRNG_IMR_DATRDY;
	} else {
		((Trng *)hw)->TRNG_IER = TRNG_IMR_DATRDY;
	}
}

static inline void hri_trng_clear_IMR_DATRDY_bit(const void *const hw)
{
	((Trng *)hw)->TRNG_IDR = TRNG_IMR_DATRDY;
}

static inline void hri_trng_set_IMR_reg(const void *const hw, hri_trng_imr_reg_t mask)
{
	((Trng *)hw)->TRNG_IER = mask;
}

static inline hri_trng_imr_reg_t hri_trng_get_IMR_reg(const void *const hw, hri_trng_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Trng *)hw)->TRNG_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_trng_imr_reg_t hri_trng_read_IMR_reg(const void *const hw)
{
	return ((Trng *)hw)->TRNG_IMR;
}

static inline void hri_trng_write_IMR_reg(const void *const hw, hri_trng_imr_reg_t data)
{
	((Trng *)hw)->TRNG_IER = data;
	((Trng *)hw)->TRNG_IDR = ~data;
}

static inline void hri_trng_clear_IMR_reg(const void *const hw, hri_trng_imr_reg_t mask)
{
	((Trng *)hw)->TRNG_IDR = mask;
}

static inline hri_trng_odata_reg_t hri_trng_get_ODATA_ODATA_bf(const void *const hw, hri_trng_odata_reg_t mask)
{
	return (((Trng *)hw)->TRNG_ODATA & TRNG_ODATA_ODATA(mask)) >> TRNG_ODATA_ODATA_Pos;
}

static inline hri_trng_odata_reg_t hri_trng_read_ODATA_ODATA_bf(const void *const hw)
{
	return (((Trng *)hw)->TRNG_ODATA & TRNG_ODATA_ODATA_Msk) >> TRNG_ODATA_ODATA_Pos;
}

static inline hri_trng_odata_reg_t hri_trng_get_ODATA_reg(const void *const hw, hri_trng_odata_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Trng *)hw)->TRNG_ODATA;
	tmp &= mask;
	return tmp;
}

static inline hri_trng_odata_reg_t hri_trng_read_ODATA_reg(const void *const hw)
{
	return ((Trng *)hw)->TRNG_ODATA;
}

static inline void hri_trng_write_CR_reg(const void *const hw, hri_trng_cr_reg_t data)
{
	TRNG_CRITICAL_SECTION_ENTER();
	((Trng *)hw)->TRNG_CR = data;
	TRNG_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_TRNG_E70B_H_INCLUDED */
#endif /* _SAME70_TRNG_COMPONENT_ */
