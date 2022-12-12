/**
 * \file
 *
 * \brief SAM LOCKBIT
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

#ifdef _SAME70_LOCKBIT_COMPONENT_
#ifndef _HRI_LOCKBIT_E70B_H_INCLUDED_
#define _HRI_LOCKBIT_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_LOCKBIT_CRITICAL_SECTIONS)
#define LOCKBIT_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define LOCKBIT_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define LOCKBIT_CRITICAL_SECTION_ENTER()
#define LOCKBIT_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_lockbit_word0_reg_t;
typedef uint32_t hri_lockbit_word1_reg_t;
typedef uint32_t hri_lockbit_word2_reg_t;
typedef uint32_t hri_lockbit_word3_reg_t;

static inline void hri_lockbit_set_WORD0_LOCK_REGION_0_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_0;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_0) >> 0;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_0;
	tmp |= value << 0;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_0_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_0;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_0_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_0;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_1_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_1;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_1) >> 1;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_1;
	tmp |= value << 1;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_1_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_1;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_1_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_1;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_2_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_2;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_2) >> 2;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_2;
	tmp |= value << 2;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_2_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_2;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_2_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_2;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_3_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_3;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_3) >> 3;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_3;
	tmp |= value << 3;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_3_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_3;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_3_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_3;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_4_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_4;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_4) >> 4;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_4;
	tmp |= value << 4;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_4_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_4;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_4_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_4;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_5_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_5;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_5) >> 5;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_5;
	tmp |= value << 5;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_5_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_5;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_5_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_5;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_6_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_6;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_6) >> 6;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_6;
	tmp |= value << 6;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_6_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_6;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_6_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_6;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_7_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_7;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_7) >> 7;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_7;
	tmp |= value << 7;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_7_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_7;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_7_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_7;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_8_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_8;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_8) >> 8;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_8;
	tmp |= value << 8;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_8_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_8;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_8_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_8;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_9_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_9;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_9) >> 9;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_9;
	tmp |= value << 9;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_9_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_9;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_9_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_9;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_10_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_10;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_10) >> 10;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_10;
	tmp |= value << 10;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_10_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_10;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_10_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_10;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_11_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_11;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_11) >> 11;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_11;
	tmp |= value << 11;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_11_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_11;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_11_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_11;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_12_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_12;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_12) >> 12;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_12;
	tmp |= value << 12;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_12_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_12;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_12_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_12;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_13_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_13;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_13) >> 13;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_13;
	tmp |= value << 13;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_13_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_13;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_13_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_13;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_14_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_14;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_14) >> 14;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_14;
	tmp |= value << 14;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_14_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_14;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_14_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_14;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_15_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_15;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_15) >> 15;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_15;
	tmp |= value << 15;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_15_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_15;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_15_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_15;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_16_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_16;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_16) >> 16;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_16;
	tmp |= value << 16;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_16_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_16;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_16_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_16;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_17_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_17;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_17) >> 17;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_17;
	tmp |= value << 17;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_17_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_17;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_17_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_17;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_18_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_18;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_18) >> 18;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_18;
	tmp |= value << 18;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_18_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_18;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_18_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_18;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_19_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_19;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_19) >> 19;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_19;
	tmp |= value << 19;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_19_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_19;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_19_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_19;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_20_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_20;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_20) >> 20;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_20;
	tmp |= value << 20;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_20_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_20;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_20_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_20;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_21_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_21;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_21) >> 21;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_21;
	tmp |= value << 21;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_21_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_21;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_21_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_21;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_22_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_22;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_22) >> 22;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_22;
	tmp |= value << 22;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_22_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_22;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_22_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_22;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_23_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_23;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_23) >> 23;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_23;
	tmp |= value << 23;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_23_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_23;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_23_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_23;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_24_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_24;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_24) >> 24;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_24;
	tmp |= value << 24;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_24_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_24;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_24_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_24;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_25_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_25;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_25) >> 25;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_25;
	tmp |= value << 25;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_25_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_25;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_25_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_25;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_26_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_26;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_26) >> 26;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_26;
	tmp |= value << 26;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_26_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_26;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_26_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_26;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_27_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_27;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_27) >> 27;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_27;
	tmp |= value << 27;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_27_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_27;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_27_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_27;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_28_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_28;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_28) >> 28;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_28;
	tmp |= value << 28;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_28_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_28;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_28_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_28;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_29_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_29;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_29) >> 29;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_29;
	tmp |= value << 29;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_29_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_29;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_29_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_29;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_30_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_30;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_30) >> 30;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_30;
	tmp |= value << 30;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_30_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_30;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_30_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_30;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_LOCK_REGION_31_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= LOCKBIT_WORD0_LOCK_REGION_31;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD0_LOCK_REGION_31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp = (tmp & LOCKBIT_WORD0_LOCK_REGION_31) >> 31;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD0_LOCK_REGION_31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= ~LOCKBIT_WORD0_LOCK_REGION_31;
	tmp |= value << 31;
	((Lockbit *)hw)->WORD0 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_LOCK_REGION_31_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~LOCKBIT_WORD0_LOCK_REGION_31;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_LOCK_REGION_31_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= LOCKBIT_WORD0_LOCK_REGION_31;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD0_reg(const void *const hw, hri_lockbit_word0_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 |= mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline hri_lockbit_word0_reg_t hri_lockbit_get_WORD0_reg(const void *const hw, hri_lockbit_word0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD0;
	tmp &= mask;
	return tmp;
}

static inline void hri_lockbit_write_WORD0_reg(const void *const hw, hri_lockbit_word0_reg_t data)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 = data;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD0_reg(const void *const hw, hri_lockbit_word0_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 &= ~mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD0_reg(const void *const hw, hri_lockbit_word0_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD0 ^= mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline hri_lockbit_word0_reg_t hri_lockbit_read_WORD0_reg(const void *const hw)
{
	return ((Lockbit *)hw)->WORD0;
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_32_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_32;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_32_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_32) >> 0;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_32_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_32;
	tmp |= value << 0;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_32_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_32;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_32_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_32;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_33_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_33;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_33_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_33) >> 1;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_33_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_33;
	tmp |= value << 1;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_33_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_33;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_33_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_33;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_34_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_34;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_34_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_34) >> 2;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_34_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_34;
	tmp |= value << 2;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_34_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_34;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_34_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_34;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_35_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_35;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_35_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_35) >> 3;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_35_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_35;
	tmp |= value << 3;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_35_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_35;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_35_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_35;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_36_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_36;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_36_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_36) >> 4;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_36_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_36;
	tmp |= value << 4;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_36_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_36;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_36_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_36;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_37_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_37;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_37_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_37) >> 5;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_37_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_37;
	tmp |= value << 5;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_37_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_37;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_37_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_37;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_38_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_38;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_38_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_38) >> 6;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_38_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_38;
	tmp |= value << 6;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_38_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_38;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_38_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_38;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_39_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_39;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_39_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_39) >> 7;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_39_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_39;
	tmp |= value << 7;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_39_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_39;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_39_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_39;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_40_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_40;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_40_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_40) >> 8;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_40_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_40;
	tmp |= value << 8;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_40_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_40;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_40_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_40;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_41_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_41;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_41_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_41) >> 9;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_41_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_41;
	tmp |= value << 9;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_41_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_41;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_41_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_41;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_42_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_42;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_42_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_42) >> 10;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_42_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_42;
	tmp |= value << 10;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_42_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_42;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_42_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_42;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_43_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_43;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_43_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_43) >> 11;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_43_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_43;
	tmp |= value << 11;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_43_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_43;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_43_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_43;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_44_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_44;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_44_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_44) >> 12;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_44_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_44;
	tmp |= value << 12;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_44_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_44;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_44_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_44;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_45_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_45;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_45_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_45) >> 13;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_45_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_45;
	tmp |= value << 13;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_45_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_45;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_45_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_45;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_46_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_46;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_46_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_46) >> 14;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_46_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_46;
	tmp |= value << 14;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_46_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_46;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_46_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_46;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_47_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_47;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_47_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_47) >> 15;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_47_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_47;
	tmp |= value << 15;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_47_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_47;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_47_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_47;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_48_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_48;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_48_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_48) >> 16;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_48_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_48;
	tmp |= value << 16;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_48_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_48;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_48_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_48;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_49_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_49;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_49_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_49) >> 17;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_49_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_49;
	tmp |= value << 17;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_49_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_49;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_49_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_49;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_50_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_50;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_50_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_50) >> 18;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_50_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_50;
	tmp |= value << 18;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_50_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_50;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_50_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_50;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_51_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_51;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_51_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_51) >> 19;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_51_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_51;
	tmp |= value << 19;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_51_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_51;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_51_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_51;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_52_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_52;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_52_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_52) >> 20;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_52_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_52;
	tmp |= value << 20;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_52_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_52;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_52_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_52;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_53_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_53;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_53_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_53) >> 21;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_53_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_53;
	tmp |= value << 21;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_53_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_53;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_53_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_53;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_54_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_54;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_54_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_54) >> 22;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_54_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_54;
	tmp |= value << 22;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_54_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_54;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_54_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_54;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_55_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_55;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_55_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_55) >> 23;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_55_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_55;
	tmp |= value << 23;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_55_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_55;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_55_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_55;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_56_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_56;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_56_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_56) >> 24;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_56_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_56;
	tmp |= value << 24;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_56_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_56;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_56_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_56;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_57_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_57;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_57_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_57) >> 25;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_57_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_57;
	tmp |= value << 25;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_57_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_57;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_57_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_57;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_58_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_58;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_58_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_58) >> 26;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_58_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_58;
	tmp |= value << 26;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_58_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_58;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_58_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_58;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_59_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_59;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_59_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_59) >> 27;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_59_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_59;
	tmp |= value << 27;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_59_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_59;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_59_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_59;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_60_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_60;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_60_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_60) >> 28;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_60_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_60;
	tmp |= value << 28;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_60_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_60;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_60_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_60;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_61_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_61;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_61_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_61) >> 29;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_61_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_61;
	tmp |= value << 29;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_61_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_61;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_61_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_61;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_62_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_62;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_62_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_62) >> 30;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_62_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_62;
	tmp |= value << 30;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_62_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_62;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_62_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_62;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_LOCK_REGION_63_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= LOCKBIT_WORD1_LOCK_REGION_63;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD1_LOCK_REGION_63_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp = (tmp & LOCKBIT_WORD1_LOCK_REGION_63) >> 31;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD1_LOCK_REGION_63_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= ~LOCKBIT_WORD1_LOCK_REGION_63;
	tmp |= value << 31;
	((Lockbit *)hw)->WORD1 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_LOCK_REGION_63_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~LOCKBIT_WORD1_LOCK_REGION_63;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_LOCK_REGION_63_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= LOCKBIT_WORD1_LOCK_REGION_63;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD1_reg(const void *const hw, hri_lockbit_word1_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 |= mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline hri_lockbit_word1_reg_t hri_lockbit_get_WORD1_reg(const void *const hw, hri_lockbit_word1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD1;
	tmp &= mask;
	return tmp;
}

static inline void hri_lockbit_write_WORD1_reg(const void *const hw, hri_lockbit_word1_reg_t data)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 = data;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD1_reg(const void *const hw, hri_lockbit_word1_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 &= ~mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD1_reg(const void *const hw, hri_lockbit_word1_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD1 ^= mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline hri_lockbit_word1_reg_t hri_lockbit_read_WORD1_reg(const void *const hw)
{
	return ((Lockbit *)hw)->WORD1;
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_64_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_64;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_64_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_64) >> 0;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_64_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_64;
	tmp |= value << 0;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_64_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_64;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_64_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_64;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_65_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_65;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_65_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_65) >> 1;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_65_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_65;
	tmp |= value << 1;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_65_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_65;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_65_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_65;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_66_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_66;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_66_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_66) >> 2;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_66_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_66;
	tmp |= value << 2;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_66_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_66;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_66_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_66;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_67_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_67;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_67_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_67) >> 3;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_67_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_67;
	tmp |= value << 3;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_67_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_67;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_67_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_67;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_68_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_68;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_68_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_68) >> 4;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_68_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_68;
	tmp |= value << 4;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_68_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_68;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_68_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_68;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_69_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_69;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_69_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_69) >> 5;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_69_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_69;
	tmp |= value << 5;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_69_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_69;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_69_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_69;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_70_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_70;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_70_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_70) >> 6;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_70_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_70;
	tmp |= value << 6;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_70_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_70;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_70_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_70;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_71_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_71;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_71_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_71) >> 7;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_71_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_71;
	tmp |= value << 7;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_71_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_71;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_71_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_71;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_72_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_72;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_72_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_72) >> 8;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_72_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_72;
	tmp |= value << 8;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_72_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_72;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_72_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_72;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_73_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_73;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_73_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_73) >> 9;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_73_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_73;
	tmp |= value << 9;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_73_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_73;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_73_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_73;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_74_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_74;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_74_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_74) >> 10;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_74_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_74;
	tmp |= value << 10;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_74_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_74;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_74_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_74;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_75_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_75;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_75_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_75) >> 11;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_75_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_75;
	tmp |= value << 11;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_75_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_75;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_75_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_75;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_76_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_76;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_76_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_76) >> 12;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_76_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_76;
	tmp |= value << 12;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_76_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_76;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_76_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_76;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_77_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_77;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_77_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_77) >> 13;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_77_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_77;
	tmp |= value << 13;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_77_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_77;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_77_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_77;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_78_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_78;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_78_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_78) >> 14;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_78_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_78;
	tmp |= value << 14;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_78_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_78;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_78_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_78;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_79_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_79;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_79_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_79) >> 15;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_79_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_79;
	tmp |= value << 15;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_79_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_79;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_79_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_79;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_80_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_80;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_80_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_80) >> 16;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_80_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_80;
	tmp |= value << 16;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_80_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_80;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_80_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_80;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_81_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_81;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_81_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_81) >> 17;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_81_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_81;
	tmp |= value << 17;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_81_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_81;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_81_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_81;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_82_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_82;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_82_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_82) >> 18;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_82_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_82;
	tmp |= value << 18;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_82_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_82;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_82_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_82;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_83_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_83;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_83_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_83) >> 19;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_83_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_83;
	tmp |= value << 19;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_83_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_83;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_83_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_83;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_84_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_84;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_84_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_84) >> 20;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_84_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_84;
	tmp |= value << 20;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_84_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_84;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_84_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_84;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_85_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_85;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_85_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_85) >> 21;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_85_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_85;
	tmp |= value << 21;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_85_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_85;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_85_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_85;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_86_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_86;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_86_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_86) >> 22;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_86_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_86;
	tmp |= value << 22;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_86_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_86;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_86_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_86;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_87_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_87;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_87_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_87) >> 23;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_87_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_87;
	tmp |= value << 23;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_87_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_87;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_87_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_87;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_88_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_88;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_88_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_88) >> 24;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_88_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_88;
	tmp |= value << 24;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_88_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_88;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_88_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_88;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_89_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_89;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_89_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_89) >> 25;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_89_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_89;
	tmp |= value << 25;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_89_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_89;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_89_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_89;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_90_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_90;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_90_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_90) >> 26;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_90_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_90;
	tmp |= value << 26;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_90_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_90;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_90_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_90;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_91_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_91;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_91_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_91) >> 27;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_91_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_91;
	tmp |= value << 27;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_91_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_91;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_91_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_91;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_92_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_92;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_92_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_92) >> 28;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_92_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_92;
	tmp |= value << 28;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_92_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_92;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_92_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_92;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_93_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_93;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_93_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_93) >> 29;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_93_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_93;
	tmp |= value << 29;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_93_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_93;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_93_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_93;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_94_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_94;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_94_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_94) >> 30;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_94_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_94;
	tmp |= value << 30;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_94_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_94;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_94_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_94;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_LOCK_REGION_95_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= LOCKBIT_WORD2_LOCK_REGION_95;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD2_LOCK_REGION_95_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp = (tmp & LOCKBIT_WORD2_LOCK_REGION_95) >> 31;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD2_LOCK_REGION_95_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= ~LOCKBIT_WORD2_LOCK_REGION_95;
	tmp |= value << 31;
	((Lockbit *)hw)->WORD2 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_LOCK_REGION_95_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~LOCKBIT_WORD2_LOCK_REGION_95;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_LOCK_REGION_95_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= LOCKBIT_WORD2_LOCK_REGION_95;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD2_reg(const void *const hw, hri_lockbit_word2_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 |= mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline hri_lockbit_word2_reg_t hri_lockbit_get_WORD2_reg(const void *const hw, hri_lockbit_word2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD2;
	tmp &= mask;
	return tmp;
}

static inline void hri_lockbit_write_WORD2_reg(const void *const hw, hri_lockbit_word2_reg_t data)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 = data;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD2_reg(const void *const hw, hri_lockbit_word2_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 &= ~mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD2_reg(const void *const hw, hri_lockbit_word2_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD2 ^= mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline hri_lockbit_word2_reg_t hri_lockbit_read_WORD2_reg(const void *const hw)
{
	return ((Lockbit *)hw)->WORD2;
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_96_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_96;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_96_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_96) >> 0;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_96_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_96;
	tmp |= value << 0;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_96_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_96;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_96_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_96;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_97_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_97;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_97_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_97) >> 1;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_97_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_97;
	tmp |= value << 1;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_97_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_97;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_97_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_97;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_98_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_98;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_98_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_98) >> 2;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_98_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_98;
	tmp |= value << 2;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_98_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_98;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_98_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_98;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_99_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_99;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_99_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_99) >> 3;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_99_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_99;
	tmp |= value << 3;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_99_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_99;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_99_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_99;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_100_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_100;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_100_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_100) >> 4;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_100_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_100;
	tmp |= value << 4;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_100_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_100;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_100_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_100;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_101_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_101;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_101_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_101) >> 5;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_101_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_101;
	tmp |= value << 5;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_101_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_101;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_101_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_101;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_102_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_102;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_102_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_102) >> 6;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_102_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_102;
	tmp |= value << 6;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_102_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_102;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_102_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_102;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_103_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_103;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_103_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_103) >> 7;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_103_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_103;
	tmp |= value << 7;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_103_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_103;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_103_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_103;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_104_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_104;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_104_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_104) >> 8;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_104_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_104;
	tmp |= value << 8;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_104_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_104;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_104_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_104;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_105_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_105;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_105_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_105) >> 9;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_105_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_105;
	tmp |= value << 9;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_105_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_105;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_105_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_105;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_106_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_106;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_106_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_106) >> 10;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_106_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_106;
	tmp |= value << 10;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_106_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_106;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_106_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_106;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_107_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_107;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_107_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_107) >> 11;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_107_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_107;
	tmp |= value << 11;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_107_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_107;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_107_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_107;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_108_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_108;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_108_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_108) >> 12;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_108_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_108;
	tmp |= value << 12;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_108_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_108;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_108_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_108;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_109_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_109;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_109_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_109) >> 13;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_109_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_109;
	tmp |= value << 13;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_109_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_109;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_109_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_109;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_110_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_110;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_110_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_110) >> 14;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_110_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_110;
	tmp |= value << 14;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_110_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_110;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_110_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_110;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_111_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_111;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_111_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_111) >> 15;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_111_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_111;
	tmp |= value << 15;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_111_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_111;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_111_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_111;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_112_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_112;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_112_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_112) >> 16;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_112_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_112;
	tmp |= value << 16;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_112_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_112;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_112_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_112;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_113_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_113;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_113_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_113) >> 17;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_113_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_113;
	tmp |= value << 17;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_113_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_113;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_113_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_113;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_114_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_114;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_114_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_114) >> 18;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_114_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_114;
	tmp |= value << 18;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_114_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_114;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_114_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_114;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_115_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_115;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_115_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_115) >> 19;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_115_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_115;
	tmp |= value << 19;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_115_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_115;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_115_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_115;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_116_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_116;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_116_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_116) >> 20;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_116_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_116;
	tmp |= value << 20;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_116_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_116;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_116_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_116;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_117_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_117;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_117_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_117) >> 21;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_117_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_117;
	tmp |= value << 21;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_117_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_117;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_117_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_117;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_118_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_118;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_118_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_118) >> 22;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_118_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_118;
	tmp |= value << 22;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_118_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_118;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_118_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_118;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_119_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_119;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_119_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_119) >> 23;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_119_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_119;
	tmp |= value << 23;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_119_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_119;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_119_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_119;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_120_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_120;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_120_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_120) >> 24;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_120_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_120;
	tmp |= value << 24;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_120_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_120;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_120_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_120;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_121_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_121;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_121_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_121) >> 25;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_121_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_121;
	tmp |= value << 25;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_121_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_121;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_121_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_121;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_122_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_122;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_122_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_122) >> 26;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_122_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_122;
	tmp |= value << 26;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_122_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_122;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_122_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_122;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_123_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_123;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_123_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_123) >> 27;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_123_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_123;
	tmp |= value << 27;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_123_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_123;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_123_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_123;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_124_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_124;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_124_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_124) >> 28;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_124_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_124;
	tmp |= value << 28;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_124_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_124;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_124_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_124;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_125_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_125;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_125_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_125) >> 29;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_125_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_125;
	tmp |= value << 29;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_125_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_125;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_125_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_125;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_126_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_126;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_126_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_126) >> 30;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_126_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_126;
	tmp |= value << 30;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_126_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_126;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_126_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_126;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_LOCK_REGION_127_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= LOCKBIT_WORD3_LOCK_REGION_127;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_lockbit_get_WORD3_LOCK_REGION_127_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp = (tmp & LOCKBIT_WORD3_LOCK_REGION_127) >> 31;
	return (bool)tmp;
}

static inline void hri_lockbit_write_WORD3_LOCK_REGION_127_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	LOCKBIT_CRITICAL_SECTION_ENTER();
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= ~LOCKBIT_WORD3_LOCK_REGION_127;
	tmp |= value << 31;
	((Lockbit *)hw)->WORD3 = tmp;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_LOCK_REGION_127_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~LOCKBIT_WORD3_LOCK_REGION_127;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_LOCK_REGION_127_bit(const void *const hw)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= LOCKBIT_WORD3_LOCK_REGION_127;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_set_WORD3_reg(const void *const hw, hri_lockbit_word3_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 |= mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline hri_lockbit_word3_reg_t hri_lockbit_get_WORD3_reg(const void *const hw, hri_lockbit_word3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Lockbit *)hw)->WORD3;
	tmp &= mask;
	return tmp;
}

static inline void hri_lockbit_write_WORD3_reg(const void *const hw, hri_lockbit_word3_reg_t data)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 = data;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_clear_WORD3_reg(const void *const hw, hri_lockbit_word3_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 &= ~mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline void hri_lockbit_toggle_WORD3_reg(const void *const hw, hri_lockbit_word3_reg_t mask)
{
	LOCKBIT_CRITICAL_SECTION_ENTER();
	((Lockbit *)hw)->WORD3 ^= mask;
	LOCKBIT_CRITICAL_SECTION_LEAVE();
}

static inline hri_lockbit_word3_reg_t hri_lockbit_read_WORD3_reg(const void *const hw)
{
	return ((Lockbit *)hw)->WORD3;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_LOCKBIT_E70B_H_INCLUDED */
#endif /* _SAME70_LOCKBIT_COMPONENT_ */
