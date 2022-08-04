/**
 * \file
 *
 * \brief SAM PCC
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

#ifdef _SAME54_PCC_COMPONENT_
#ifndef _HRI_PCC_E54_H_INCLUDED_
#define _HRI_PCC_E54_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_PCC_CRITICAL_SECTIONS)
#define PCC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define PCC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define PCC_CRITICAL_SECTION_ENTER()
#define PCC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_pcc_imr_reg_t;
typedef uint32_t hri_pcc_isr_reg_t;
typedef uint32_t hri_pcc_mr_reg_t;
typedef uint32_t hri_pcc_rhr_reg_t;
typedef uint32_t hri_pcc_wpmr_reg_t;
typedef uint32_t hri_pcc_wpsr_reg_t;

static inline void hri_pcc_set_IMR_DRDY_bit(const void *const hw)
{
	((Pcc *)hw)->IER.reg = PCC_IMR_DRDY;
}

static inline bool hri_pcc_get_IMR_DRDY_bit(const void *const hw)
{
	return (((Pcc *)hw)->IMR.reg & PCC_IMR_DRDY) >> PCC_IMR_DRDY_Pos;
}

static inline void hri_pcc_write_IMR_DRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pcc *)hw)->IDR.reg = PCC_IMR_DRDY;
	} else {
		((Pcc *)hw)->IER.reg = PCC_IMR_DRDY;
	}
}

static inline void hri_pcc_clear_IMR_DRDY_bit(const void *const hw)
{
	((Pcc *)hw)->IDR.reg = PCC_IMR_DRDY;
}

static inline void hri_pcc_set_IMR_OVRE_bit(const void *const hw)
{
	((Pcc *)hw)->IER.reg = PCC_IMR_OVRE;
}

static inline bool hri_pcc_get_IMR_OVRE_bit(const void *const hw)
{
	return (((Pcc *)hw)->IMR.reg & PCC_IMR_OVRE) >> PCC_IMR_OVRE_Pos;
}

static inline void hri_pcc_write_IMR_OVRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pcc *)hw)->IDR.reg = PCC_IMR_OVRE;
	} else {
		((Pcc *)hw)->IER.reg = PCC_IMR_OVRE;
	}
}

static inline void hri_pcc_clear_IMR_OVRE_bit(const void *const hw)
{
	((Pcc *)hw)->IDR.reg = PCC_IMR_OVRE;
}

static inline void hri_pcc_set_IMR_reg(const void *const hw, hri_pcc_imr_reg_t mask)
{
	((Pcc *)hw)->IER.reg = mask;
}

static inline hri_pcc_imr_reg_t hri_pcc_get_IMR_reg(const void *const hw, hri_pcc_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pcc *)hw)->IMR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pcc_imr_reg_t hri_pcc_read_IMR_reg(const void *const hw)
{
	return ((Pcc *)hw)->IMR.reg;
}

static inline void hri_pcc_write_IMR_reg(const void *const hw, hri_pcc_imr_reg_t data)
{
	((Pcc *)hw)->IER.reg = data;
	((Pcc *)hw)->IDR.reg = ~data;
}

static inline void hri_pcc_clear_IMR_reg(const void *const hw, hri_pcc_imr_reg_t mask)
{
	((Pcc *)hw)->IDR.reg = mask;
}

static inline bool hri_pcc_get_ISR_DRDY_bit(const void *const hw)
{
	return (((Pcc *)hw)->ISR.reg & PCC_ISR_DRDY) >> PCC_ISR_DRDY_Pos;
}

static inline bool hri_pcc_get_ISR_OVRE_bit(const void *const hw)
{
	return (((Pcc *)hw)->ISR.reg & PCC_ISR_OVRE) >> PCC_ISR_OVRE_Pos;
}

static inline hri_pcc_isr_reg_t hri_pcc_get_ISR_reg(const void *const hw, hri_pcc_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pcc *)hw)->ISR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pcc_isr_reg_t hri_pcc_read_ISR_reg(const void *const hw)
{
	return ((Pcc *)hw)->ISR.reg;
}

static inline hri_pcc_rhr_reg_t hri_pcc_get_RHR_RDATA_bf(const void *const hw, hri_pcc_rhr_reg_t mask)
{
	return (((Pcc *)hw)->RHR.reg & PCC_RHR_RDATA(mask)) >> PCC_RHR_RDATA_Pos;
}

static inline hri_pcc_rhr_reg_t hri_pcc_read_RHR_RDATA_bf(const void *const hw)
{
	return (((Pcc *)hw)->RHR.reg & PCC_RHR_RDATA_Msk) >> PCC_RHR_RDATA_Pos;
}

static inline hri_pcc_rhr_reg_t hri_pcc_get_RHR_reg(const void *const hw, hri_pcc_rhr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pcc *)hw)->RHR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pcc_rhr_reg_t hri_pcc_read_RHR_reg(const void *const hw)
{
	return ((Pcc *)hw)->RHR.reg;
}

static inline bool hri_pcc_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Pcc *)hw)->WPSR.reg & PCC_WPSR_WPVS) >> PCC_WPSR_WPVS_Pos;
}

static inline hri_pcc_wpsr_reg_t hri_pcc_get_WPSR_WPVSRC_bf(const void *const hw, hri_pcc_wpsr_reg_t mask)
{
	return (((Pcc *)hw)->WPSR.reg & PCC_WPSR_WPVSRC(mask)) >> PCC_WPSR_WPVSRC_Pos;
}

static inline hri_pcc_wpsr_reg_t hri_pcc_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Pcc *)hw)->WPSR.reg & PCC_WPSR_WPVSRC_Msk) >> PCC_WPSR_WPVSRC_Pos;
}

static inline hri_pcc_wpsr_reg_t hri_pcc_get_WPSR_reg(const void *const hw, hri_pcc_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pcc *)hw)->WPSR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pcc_wpsr_reg_t hri_pcc_read_WPSR_reg(const void *const hw)
{
	return ((Pcc *)hw)->WPSR.reg;
}

static inline void hri_pcc_set_MR_reg(const void *const hw, hri_pcc_mr_reg_t mask)
{
	PCC_CRITICAL_SECTION_ENTER();
	((Pcc *)hw)->MR.reg |= mask;
	PCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pcc_mr_reg_t hri_pcc_get_MR_reg(const void *const hw, hri_pcc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pcc *)hw)->MR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_pcc_write_MR_reg(const void *const hw, hri_pcc_mr_reg_t data)
{
	PCC_CRITICAL_SECTION_ENTER();
	((Pcc *)hw)->MR.reg = data;
	PCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pcc_clear_MR_reg(const void *const hw, hri_pcc_mr_reg_t mask)
{
	PCC_CRITICAL_SECTION_ENTER();
	((Pcc *)hw)->MR.reg &= ~mask;
	PCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pcc_toggle_MR_reg(const void *const hw, hri_pcc_mr_reg_t mask)
{
	PCC_CRITICAL_SECTION_ENTER();
	((Pcc *)hw)->MR.reg ^= mask;
	PCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pcc_mr_reg_t hri_pcc_read_MR_reg(const void *const hw)
{
	return ((Pcc *)hw)->MR.reg;
}

static inline void hri_pcc_set_WPMR_reg(const void *const hw, hri_pcc_wpmr_reg_t mask)
{
	PCC_CRITICAL_SECTION_ENTER();
	((Pcc *)hw)->WPMR.reg |= mask;
	PCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pcc_wpmr_reg_t hri_pcc_get_WPMR_reg(const void *const hw, hri_pcc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pcc *)hw)->WPMR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_pcc_write_WPMR_reg(const void *const hw, hri_pcc_wpmr_reg_t data)
{
	PCC_CRITICAL_SECTION_ENTER();
	((Pcc *)hw)->WPMR.reg = data;
	PCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pcc_clear_WPMR_reg(const void *const hw, hri_pcc_wpmr_reg_t mask)
{
	PCC_CRITICAL_SECTION_ENTER();
	((Pcc *)hw)->WPMR.reg &= ~mask;
	PCC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pcc_toggle_WPMR_reg(const void *const hw, hri_pcc_wpmr_reg_t mask)
{
	PCC_CRITICAL_SECTION_ENTER();
	((Pcc *)hw)->WPMR.reg ^= mask;
	PCC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pcc_wpmr_reg_t hri_pcc_read_WPMR_reg(const void *const hw)
{
	return ((Pcc *)hw)->WPMR.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_PCC_E54_H_INCLUDED */
#endif /* _SAME54_PCC_COMPONENT_ */
