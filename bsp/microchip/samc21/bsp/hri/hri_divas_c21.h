/**
 * \file
 *
 * \brief SAM DIVAS
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

#ifdef _SAMC21_DIVAS_COMPONENT_
#ifndef _HRI_DIVAS_C21_H_INCLUDED_
#define _HRI_DIVAS_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_DIVAS_CRITICAL_SECTIONS)
#define DIVAS_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define DIVAS_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define DIVAS_CRITICAL_SECTION_ENTER()
#define DIVAS_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_divas_dividend_reg_t;
typedef uint32_t hri_divas_divisor_reg_t;
typedef uint32_t hri_divas_rem_reg_t;
typedef uint32_t hri_divas_result_reg_t;
typedef uint32_t hri_divas_sqrnum_reg_t;
typedef uint8_t  hri_divas_ctrla_reg_t;
typedef uint8_t  hri_divas_status_reg_t;

static inline hri_divas_result_reg_t hri_divas_get_RESULT_RESULT_bf(const void *const hw, hri_divas_result_reg_t mask)
{
	return (((Divas *)hw)->RESULT.reg & DIVAS_RESULT_RESULT(mask)) >> DIVAS_RESULT_RESULT_Pos;
}

static inline hri_divas_result_reg_t hri_divas_read_RESULT_RESULT_bf(const void *const hw)
{
	return (((Divas *)hw)->RESULT.reg & DIVAS_RESULT_RESULT_Msk) >> DIVAS_RESULT_RESULT_Pos;
}

static inline hri_divas_result_reg_t hri_divas_get_RESULT_reg(const void *const hw, hri_divas_result_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->RESULT.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_divas_result_reg_t hri_divas_read_RESULT_reg(const void *const hw)
{
	return ((Divas *)hw)->RESULT.reg;
}

static inline hri_divas_rem_reg_t hri_divas_get_REM_REM_bf(const void *const hw, hri_divas_rem_reg_t mask)
{
	return (((Divas *)hw)->REM.reg & DIVAS_REM_REM(mask)) >> DIVAS_REM_REM_Pos;
}

static inline hri_divas_rem_reg_t hri_divas_read_REM_REM_bf(const void *const hw)
{
	return (((Divas *)hw)->REM.reg & DIVAS_REM_REM_Msk) >> DIVAS_REM_REM_Pos;
}

static inline hri_divas_rem_reg_t hri_divas_get_REM_reg(const void *const hw, hri_divas_rem_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->REM.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_divas_rem_reg_t hri_divas_read_REM_reg(const void *const hw)
{
	return ((Divas *)hw)->REM.reg;
}

static inline void hri_divas_set_CTRLA_SIGNED_bit(const void *const hw)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg |= DIVAS_CTRLA_SIGNED;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_divas_get_CTRLA_SIGNED_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Divas *)hw)->CTRLA.reg;
	tmp = (tmp & DIVAS_CTRLA_SIGNED) >> DIVAS_CTRLA_SIGNED_Pos;
	return (bool)tmp;
}

static inline void hri_divas_write_CTRLA_SIGNED_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	DIVAS_CRITICAL_SECTION_ENTER();
	tmp = ((Divas *)hw)->CTRLA.reg;
	tmp &= ~DIVAS_CTRLA_SIGNED;
	tmp |= value << DIVAS_CTRLA_SIGNED_Pos;
	((Divas *)hw)->CTRLA.reg = tmp;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_clear_CTRLA_SIGNED_bit(const void *const hw)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg &= ~DIVAS_CTRLA_SIGNED;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_toggle_CTRLA_SIGNED_bit(const void *const hw)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg ^= DIVAS_CTRLA_SIGNED;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_set_CTRLA_DLZ_bit(const void *const hw)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg |= DIVAS_CTRLA_DLZ;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_divas_get_CTRLA_DLZ_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Divas *)hw)->CTRLA.reg;
	tmp = (tmp & DIVAS_CTRLA_DLZ) >> DIVAS_CTRLA_DLZ_Pos;
	return (bool)tmp;
}

static inline void hri_divas_write_CTRLA_DLZ_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	DIVAS_CRITICAL_SECTION_ENTER();
	tmp = ((Divas *)hw)->CTRLA.reg;
	tmp &= ~DIVAS_CTRLA_DLZ;
	tmp |= value << DIVAS_CTRLA_DLZ_Pos;
	((Divas *)hw)->CTRLA.reg = tmp;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_clear_CTRLA_DLZ_bit(const void *const hw)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg &= ~DIVAS_CTRLA_DLZ;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_toggle_CTRLA_DLZ_bit(const void *const hw)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg ^= DIVAS_CTRLA_DLZ;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_set_CTRLA_reg(const void *const hw, hri_divas_ctrla_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg |= mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_ctrla_reg_t hri_divas_get_CTRLA_reg(const void *const hw, hri_divas_ctrla_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Divas *)hw)->CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_divas_write_CTRLA_reg(const void *const hw, hri_divas_ctrla_reg_t data)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg = data;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_clear_CTRLA_reg(const void *const hw, hri_divas_ctrla_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg &= ~mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_toggle_CTRLA_reg(const void *const hw, hri_divas_ctrla_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->CTRLA.reg ^= mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_ctrla_reg_t hri_divas_read_CTRLA_reg(const void *const hw)
{
	return ((Divas *)hw)->CTRLA.reg;
}

static inline void hri_divas_set_DIVIDEND_DIVIDEND_bf(const void *const hw, hri_divas_dividend_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVIDEND.reg |= DIVAS_DIVIDEND_DIVIDEND(mask);
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_dividend_reg_t hri_divas_get_DIVIDEND_DIVIDEND_bf(const void *const        hw,
                                                                          hri_divas_dividend_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->DIVIDEND.reg;
	tmp = (tmp & DIVAS_DIVIDEND_DIVIDEND(mask)) >> DIVAS_DIVIDEND_DIVIDEND_Pos;
	return tmp;
}

static inline void hri_divas_write_DIVIDEND_DIVIDEND_bf(const void *const hw, hri_divas_dividend_reg_t data)
{
	uint32_t tmp;
	DIVAS_CRITICAL_SECTION_ENTER();
	tmp = ((Divas *)hw)->DIVIDEND.reg;
	tmp &= ~DIVAS_DIVIDEND_DIVIDEND_Msk;
	tmp |= DIVAS_DIVIDEND_DIVIDEND(data);
	((Divas *)hw)->DIVIDEND.reg = tmp;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_clear_DIVIDEND_DIVIDEND_bf(const void *const hw, hri_divas_dividend_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVIDEND.reg &= ~DIVAS_DIVIDEND_DIVIDEND(mask);
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_toggle_DIVIDEND_DIVIDEND_bf(const void *const hw, hri_divas_dividend_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVIDEND.reg ^= DIVAS_DIVIDEND_DIVIDEND(mask);
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_dividend_reg_t hri_divas_read_DIVIDEND_DIVIDEND_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->DIVIDEND.reg;
	tmp = (tmp & DIVAS_DIVIDEND_DIVIDEND_Msk) >> DIVAS_DIVIDEND_DIVIDEND_Pos;
	return tmp;
}

static inline void hri_divas_set_DIVIDEND_reg(const void *const hw, hri_divas_dividend_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVIDEND.reg |= mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_dividend_reg_t hri_divas_get_DIVIDEND_reg(const void *const hw, hri_divas_dividend_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->DIVIDEND.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_divas_write_DIVIDEND_reg(const void *const hw, hri_divas_dividend_reg_t data)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVIDEND.reg = data;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_clear_DIVIDEND_reg(const void *const hw, hri_divas_dividend_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVIDEND.reg &= ~mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_toggle_DIVIDEND_reg(const void *const hw, hri_divas_dividend_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVIDEND.reg ^= mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_dividend_reg_t hri_divas_read_DIVIDEND_reg(const void *const hw)
{
	return ((Divas *)hw)->DIVIDEND.reg;
}

static inline void hri_divas_set_DIVISOR_DIVISOR_bf(const void *const hw, hri_divas_divisor_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVISOR.reg |= DIVAS_DIVISOR_DIVISOR(mask);
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_divisor_reg_t hri_divas_get_DIVISOR_DIVISOR_bf(const void *const       hw,
                                                                       hri_divas_divisor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->DIVISOR.reg;
	tmp = (tmp & DIVAS_DIVISOR_DIVISOR(mask)) >> DIVAS_DIVISOR_DIVISOR_Pos;
	return tmp;
}

static inline void hri_divas_write_DIVISOR_DIVISOR_bf(const void *const hw, hri_divas_divisor_reg_t data)
{
	uint32_t tmp;
	DIVAS_CRITICAL_SECTION_ENTER();
	tmp = ((Divas *)hw)->DIVISOR.reg;
	tmp &= ~DIVAS_DIVISOR_DIVISOR_Msk;
	tmp |= DIVAS_DIVISOR_DIVISOR(data);
	((Divas *)hw)->DIVISOR.reg = tmp;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_clear_DIVISOR_DIVISOR_bf(const void *const hw, hri_divas_divisor_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVISOR.reg &= ~DIVAS_DIVISOR_DIVISOR(mask);
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_toggle_DIVISOR_DIVISOR_bf(const void *const hw, hri_divas_divisor_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVISOR.reg ^= DIVAS_DIVISOR_DIVISOR(mask);
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_divisor_reg_t hri_divas_read_DIVISOR_DIVISOR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->DIVISOR.reg;
	tmp = (tmp & DIVAS_DIVISOR_DIVISOR_Msk) >> DIVAS_DIVISOR_DIVISOR_Pos;
	return tmp;
}

static inline void hri_divas_set_DIVISOR_reg(const void *const hw, hri_divas_divisor_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVISOR.reg |= mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_divisor_reg_t hri_divas_get_DIVISOR_reg(const void *const hw, hri_divas_divisor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->DIVISOR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_divas_write_DIVISOR_reg(const void *const hw, hri_divas_divisor_reg_t data)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVISOR.reg = data;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_clear_DIVISOR_reg(const void *const hw, hri_divas_divisor_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVISOR.reg &= ~mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_toggle_DIVISOR_reg(const void *const hw, hri_divas_divisor_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->DIVISOR.reg ^= mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_divisor_reg_t hri_divas_read_DIVISOR_reg(const void *const hw)
{
	return ((Divas *)hw)->DIVISOR.reg;
}

static inline void hri_divas_set_SQRNUM_SQRNUM_bf(const void *const hw, hri_divas_sqrnum_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->SQRNUM.reg |= DIVAS_SQRNUM_SQRNUM(mask);
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_sqrnum_reg_t hri_divas_get_SQRNUM_SQRNUM_bf(const void *const hw, hri_divas_sqrnum_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->SQRNUM.reg;
	tmp = (tmp & DIVAS_SQRNUM_SQRNUM(mask)) >> DIVAS_SQRNUM_SQRNUM_Pos;
	return tmp;
}

static inline void hri_divas_write_SQRNUM_SQRNUM_bf(const void *const hw, hri_divas_sqrnum_reg_t data)
{
	uint32_t tmp;
	DIVAS_CRITICAL_SECTION_ENTER();
	tmp = ((Divas *)hw)->SQRNUM.reg;
	tmp &= ~DIVAS_SQRNUM_SQRNUM_Msk;
	tmp |= DIVAS_SQRNUM_SQRNUM(data);
	((Divas *)hw)->SQRNUM.reg = tmp;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_clear_SQRNUM_SQRNUM_bf(const void *const hw, hri_divas_sqrnum_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->SQRNUM.reg &= ~DIVAS_SQRNUM_SQRNUM(mask);
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_toggle_SQRNUM_SQRNUM_bf(const void *const hw, hri_divas_sqrnum_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->SQRNUM.reg ^= DIVAS_SQRNUM_SQRNUM(mask);
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_sqrnum_reg_t hri_divas_read_SQRNUM_SQRNUM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->SQRNUM.reg;
	tmp = (tmp & DIVAS_SQRNUM_SQRNUM_Msk) >> DIVAS_SQRNUM_SQRNUM_Pos;
	return tmp;
}

static inline void hri_divas_set_SQRNUM_reg(const void *const hw, hri_divas_sqrnum_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->SQRNUM.reg |= mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_sqrnum_reg_t hri_divas_get_SQRNUM_reg(const void *const hw, hri_divas_sqrnum_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Divas *)hw)->SQRNUM.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_divas_write_SQRNUM_reg(const void *const hw, hri_divas_sqrnum_reg_t data)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->SQRNUM.reg = data;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_clear_SQRNUM_reg(const void *const hw, hri_divas_sqrnum_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->SQRNUM.reg &= ~mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_divas_toggle_SQRNUM_reg(const void *const hw, hri_divas_sqrnum_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->SQRNUM.reg ^= mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_sqrnum_reg_t hri_divas_read_SQRNUM_reg(const void *const hw)
{
	return ((Divas *)hw)->SQRNUM.reg;
}

static inline bool hri_divas_get_STATUS_BUSY_bit(const void *const hw)
{
	return (((Divas *)hw)->STATUS.reg & DIVAS_STATUS_BUSY) >> DIVAS_STATUS_BUSY_Pos;
}

static inline void hri_divas_clear_STATUS_BUSY_bit(const void *const hw)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->STATUS.reg = DIVAS_STATUS_BUSY;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_divas_get_STATUS_DBZ_bit(const void *const hw)
{
	return (((Divas *)hw)->STATUS.reg & DIVAS_STATUS_DBZ) >> DIVAS_STATUS_DBZ_Pos;
}

static inline void hri_divas_clear_STATUS_DBZ_bit(const void *const hw)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->STATUS.reg = DIVAS_STATUS_DBZ;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_status_reg_t hri_divas_get_STATUS_reg(const void *const hw, hri_divas_status_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Divas *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_divas_clear_STATUS_reg(const void *const hw, hri_divas_status_reg_t mask)
{
	DIVAS_CRITICAL_SECTION_ENTER();
	((Divas *)hw)->STATUS.reg = mask;
	DIVAS_CRITICAL_SECTION_LEAVE();
}

static inline hri_divas_status_reg_t hri_divas_read_STATUS_reg(const void *const hw)
{
	return ((Divas *)hw)->STATUS.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_DIVAS_C21_H_INCLUDED */
#endif /* _SAMC21_DIVAS_COMPONENT_ */
