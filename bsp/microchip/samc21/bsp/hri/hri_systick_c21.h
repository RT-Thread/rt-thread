/**
 * \file
 *
 * \brief SAM SysTick
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
 *
 */

#ifdef _SAMC21_SysTick_COMPONENT_
#ifndef _HRI_SysTick_C21_H_INCLUDED_
#define _HRI_SysTick_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_SysTick_CRITICAL_SECTIONS)
#define SysTick_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define SysTick_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define SysTick_CRITICAL_SECTION_ENTER()
#define SysTick_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_systick_calib_reg_t;
typedef uint32_t hri_systick_csr_reg_t;
typedef uint32_t hri_systick_cvr_reg_t;
typedef uint32_t hri_systick_rvr_reg_t;

static inline bool hri_systick_get_CALIB_SKEW_bit(const void *const hw)
{
	return (((Systick *)hw)->CALIB.reg & SysTick_CALIB_SKEW) >> 30;
}

static inline bool hri_systick_get_CALIB_NOREF_bit(const void *const hw)
{
	return (((Systick *)hw)->CALIB.reg & SysTick_CALIB_NOREF) >> 31;
}

static inline hri_systick_calib_reg_t hri_systick_get_CALIB_TENMS_bf(const void *const hw, hri_systick_calib_reg_t mask)
{
	return (((Systick *)hw)->CALIB.reg & SysTick_CALIB_TENMS(mask)) >> 0;
}

static inline hri_systick_calib_reg_t hri_systick_read_CALIB_TENMS_bf(const void *const hw)
{
	return (((Systick *)hw)->CALIB.reg & SysTick_CALIB_TENMS_Msk) >> 0;
}

static inline hri_systick_calib_reg_t hri_systick_get_CALIB_reg(const void *const hw, hri_systick_calib_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CALIB.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_systick_calib_reg_t hri_systick_read_CALIB_reg(const void *const hw)
{
	return ((Systick *)hw)->CALIB.reg;
}

static inline void hri_systick_set_CSR_reg(const void *const hw, hri_systick_csr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR.reg |= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_csr_reg_t hri_systick_get_CSR_reg(const void *const hw, hri_systick_csr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CSR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_systick_write_CSR_reg(const void *const hw, hri_systick_csr_reg_t data)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR.reg = data;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CSR_reg(const void *const hw, hri_systick_csr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR.reg &= ~mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CSR_reg(const void *const hw, hri_systick_csr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CSR.reg ^= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_csr_reg_t hri_systick_read_CSR_reg(const void *const hw)
{
	return ((Systick *)hw)->CSR.reg;
}

static inline void hri_systick_set_RVR_reg(const void *const hw, hri_systick_rvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR.reg |= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_rvr_reg_t hri_systick_get_RVR_reg(const void *const hw, hri_systick_rvr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->RVR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_systick_write_RVR_reg(const void *const hw, hri_systick_rvr_reg_t data)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR.reg = data;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_RVR_reg(const void *const hw, hri_systick_rvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR.reg &= ~mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_RVR_reg(const void *const hw, hri_systick_rvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->RVR.reg ^= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_rvr_reg_t hri_systick_read_RVR_reg(const void *const hw)
{
	return ((Systick *)hw)->RVR.reg;
}

static inline void hri_systick_set_CVR_reg(const void *const hw, hri_systick_cvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR.reg |= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_cvr_reg_t hri_systick_get_CVR_reg(const void *const hw, hri_systick_cvr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Systick *)hw)->CVR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_systick_write_CVR_reg(const void *const hw, hri_systick_cvr_reg_t data)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR.reg = data;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_clear_CVR_reg(const void *const hw, hri_systick_cvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR.reg &= ~mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline void hri_systick_toggle_CVR_reg(const void *const hw, hri_systick_cvr_reg_t mask)
{
	SysTick_CRITICAL_SECTION_ENTER();
	((Systick *)hw)->CVR.reg ^= mask;
	SysTick_CRITICAL_SECTION_LEAVE();
}

static inline hri_systick_cvr_reg_t hri_systick_read_CVR_reg(const void *const hw)
{
	return ((Systick *)hw)->CVR.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SysTick_C21_H_INCLUDED */
#endif /* _SAMC21_SysTick_COMPONENT_ */
