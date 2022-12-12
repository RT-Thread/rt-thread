/**
 * \file
 *
 * \brief SAM MPU
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

#ifdef _SAMC21_MPU_COMPONENT_
#ifndef _HRI_MPU_C21_H_INCLUDED_
#define _HRI_MPU_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_MPU_CRITICAL_SECTIONS)
#define MPU_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define MPU_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define MPU_CRITICAL_SECTION_ENTER()
#define MPU_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_mpu_ctrl_reg_t;
typedef uint32_t hri_mpu_rasr_reg_t;
typedef uint32_t hri_mpu_rbar_reg_t;
typedef uint32_t hri_mpu_rnr_reg_t;
typedef uint32_t hri_mpu_type_reg_t;

static inline bool hri_mpu_get_TYPE_SEPARATE_bit(const void *const hw)
{
	return (((Mpu *)hw)->TYPE.reg & MPU_TYPE_SEPARATE) >> 0;
}

static inline hri_mpu_type_reg_t hri_mpu_get_TYPE_DREGION_bf(const void *const hw, hri_mpu_type_reg_t mask)
{
	return (((Mpu *)hw)->TYPE.reg & MPU_TYPE_DREGION(mask)) >> 8;
}

static inline hri_mpu_type_reg_t hri_mpu_read_TYPE_DREGION_bf(const void *const hw)
{
	return (((Mpu *)hw)->TYPE.reg & MPU_TYPE_DREGION_Msk) >> 8;
}

static inline hri_mpu_type_reg_t hri_mpu_get_TYPE_IREGION_bf(const void *const hw, hri_mpu_type_reg_t mask)
{
	return (((Mpu *)hw)->TYPE.reg & MPU_TYPE_IREGION(mask)) >> 16;
}

static inline hri_mpu_type_reg_t hri_mpu_read_TYPE_IREGION_bf(const void *const hw)
{
	return (((Mpu *)hw)->TYPE.reg & MPU_TYPE_IREGION_Msk) >> 16;
}

static inline hri_mpu_type_reg_t hri_mpu_get_TYPE_reg(const void *const hw, hri_mpu_type_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mpu *)hw)->TYPE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mpu_type_reg_t hri_mpu_read_TYPE_reg(const void *const hw)
{
	return ((Mpu *)hw)->TYPE.reg;
}

static inline void hri_mpu_set_CTRL_reg(const void *const hw, hri_mpu_ctrl_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->CTRL.reg |= mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline hri_mpu_ctrl_reg_t hri_mpu_get_CTRL_reg(const void *const hw, hri_mpu_ctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mpu *)hw)->CTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mpu_write_CTRL_reg(const void *const hw, hri_mpu_ctrl_reg_t data)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->CTRL.reg = data;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mpu_clear_CTRL_reg(const void *const hw, hri_mpu_ctrl_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->CTRL.reg &= ~mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mpu_toggle_CTRL_reg(const void *const hw, hri_mpu_ctrl_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->CTRL.reg ^= mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline hri_mpu_ctrl_reg_t hri_mpu_read_CTRL_reg(const void *const hw)
{
	return ((Mpu *)hw)->CTRL.reg;
}

static inline void hri_mpu_set_RNR_reg(const void *const hw, hri_mpu_rnr_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RNR.reg |= mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline hri_mpu_rnr_reg_t hri_mpu_get_RNR_reg(const void *const hw, hri_mpu_rnr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mpu *)hw)->RNR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mpu_write_RNR_reg(const void *const hw, hri_mpu_rnr_reg_t data)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RNR.reg = data;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mpu_clear_RNR_reg(const void *const hw, hri_mpu_rnr_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RNR.reg &= ~mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mpu_toggle_RNR_reg(const void *const hw, hri_mpu_rnr_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RNR.reg ^= mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline hri_mpu_rnr_reg_t hri_mpu_read_RNR_reg(const void *const hw)
{
	return ((Mpu *)hw)->RNR.reg;
}

static inline void hri_mpu_set_RBAR_reg(const void *const hw, hri_mpu_rbar_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RBAR.reg |= mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline hri_mpu_rbar_reg_t hri_mpu_get_RBAR_reg(const void *const hw, hri_mpu_rbar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mpu *)hw)->RBAR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mpu_write_RBAR_reg(const void *const hw, hri_mpu_rbar_reg_t data)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RBAR.reg = data;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mpu_clear_RBAR_reg(const void *const hw, hri_mpu_rbar_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RBAR.reg &= ~mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mpu_toggle_RBAR_reg(const void *const hw, hri_mpu_rbar_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RBAR.reg ^= mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline hri_mpu_rbar_reg_t hri_mpu_read_RBAR_reg(const void *const hw)
{
	return ((Mpu *)hw)->RBAR.reg;
}

static inline void hri_mpu_set_RASR_reg(const void *const hw, hri_mpu_rasr_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RASR.reg |= mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline hri_mpu_rasr_reg_t hri_mpu_get_RASR_reg(const void *const hw, hri_mpu_rasr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mpu *)hw)->RASR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mpu_write_RASR_reg(const void *const hw, hri_mpu_rasr_reg_t data)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RASR.reg = data;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mpu_clear_RASR_reg(const void *const hw, hri_mpu_rasr_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RASR.reg &= ~mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mpu_toggle_RASR_reg(const void *const hw, hri_mpu_rasr_reg_t mask)
{
	MPU_CRITICAL_SECTION_ENTER();
	((Mpu *)hw)->RASR.reg ^= mask;
	MPU_CRITICAL_SECTION_LEAVE();
}

static inline hri_mpu_rasr_reg_t hri_mpu_read_RASR_reg(const void *const hw)
{
	return ((Mpu *)hw)->RASR.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_MPU_C21_H_INCLUDED */
#endif /* _SAMC21_MPU_COMPONENT_ */
