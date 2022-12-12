/**
 * \file
 *
 * \brief SAM SMC
 *
 * Copyright (c) 2017-2019 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAME70_SMC_COMPONENT_
#ifndef _HRI_SMC_E70B_H_INCLUDED_
#define _HRI_SMC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_SMC_CRITICAL_SECTIONS)
#define SMC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define SMC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define SMC_CRITICAL_SECTION_ENTER()
#define SMC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_smc_cycle_reg_t;
typedef uint32_t hri_smc_key1_reg_t;
typedef uint32_t hri_smc_key2_reg_t;
typedef uint32_t hri_smc_mode_reg_t;
typedef uint32_t hri_smc_ocms_reg_t;
typedef uint32_t hri_smc_pulse_reg_t;
typedef uint32_t hri_smc_setup_reg_t;
typedef uint32_t hri_smc_wpmr_reg_t;
typedef uint32_t hri_smc_wpsr_reg_t;
typedef uint32_t hri_smccs_number_cycle_reg_t;
typedef uint32_t hri_smccs_number_mode_reg_t;
typedef uint32_t hri_smccs_number_pulse_reg_t;
typedef uint32_t hri_smccs_number_setup_reg_t;

static inline void hri_smccsnumber_set_SETUP_NWE_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP |= SMC_SETUP_NWE_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_get_SETUP_NWE_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NWE_SETUP(mask)) >> SMC_SETUP_NWE_SETUP_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_SETUP_NWE_SETUP_bf(const void *const hw, hri_smc_setup_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp &= ~SMC_SETUP_NWE_SETUP_Msk;
	tmp |= SMC_SETUP_NWE_SETUP(data);
	((SmcCsNumber *)hw)->SMC_SETUP = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_SETUP_NWE_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP &= ~SMC_SETUP_NWE_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_SETUP_NWE_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP ^= SMC_SETUP_NWE_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_read_SETUP_NWE_SETUP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NWE_SETUP_Msk) >> SMC_SETUP_NWE_SETUP_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_SETUP_NCS_WR_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP |= SMC_SETUP_NCS_WR_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_get_SETUP_NCS_WR_SETUP_bf(const void *const   hw,
                                                                            hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NCS_WR_SETUP(mask)) >> SMC_SETUP_NCS_WR_SETUP_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_SETUP_NCS_WR_SETUP_bf(const void *const hw, hri_smc_setup_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp &= ~SMC_SETUP_NCS_WR_SETUP_Msk;
	tmp |= SMC_SETUP_NCS_WR_SETUP(data);
	((SmcCsNumber *)hw)->SMC_SETUP = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_SETUP_NCS_WR_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP &= ~SMC_SETUP_NCS_WR_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_SETUP_NCS_WR_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP ^= SMC_SETUP_NCS_WR_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_read_SETUP_NCS_WR_SETUP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NCS_WR_SETUP_Msk) >> SMC_SETUP_NCS_WR_SETUP_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_SETUP_NRD_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP |= SMC_SETUP_NRD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_get_SETUP_NRD_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NRD_SETUP(mask)) >> SMC_SETUP_NRD_SETUP_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_SETUP_NRD_SETUP_bf(const void *const hw, hri_smc_setup_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp &= ~SMC_SETUP_NRD_SETUP_Msk;
	tmp |= SMC_SETUP_NRD_SETUP(data);
	((SmcCsNumber *)hw)->SMC_SETUP = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_SETUP_NRD_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP &= ~SMC_SETUP_NRD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_SETUP_NRD_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP ^= SMC_SETUP_NRD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_read_SETUP_NRD_SETUP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NRD_SETUP_Msk) >> SMC_SETUP_NRD_SETUP_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_SETUP_NCS_RD_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP |= SMC_SETUP_NCS_RD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_get_SETUP_NCS_RD_SETUP_bf(const void *const   hw,
                                                                            hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NCS_RD_SETUP(mask)) >> SMC_SETUP_NCS_RD_SETUP_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_SETUP_NCS_RD_SETUP_bf(const void *const hw, hri_smc_setup_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp &= ~SMC_SETUP_NCS_RD_SETUP_Msk;
	tmp |= SMC_SETUP_NCS_RD_SETUP(data);
	((SmcCsNumber *)hw)->SMC_SETUP = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_SETUP_NCS_RD_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP &= ~SMC_SETUP_NCS_RD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_SETUP_NCS_RD_SETUP_bf(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP ^= SMC_SETUP_NCS_RD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_read_SETUP_NCS_RD_SETUP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NCS_RD_SETUP_Msk) >> SMC_SETUP_NCS_RD_SETUP_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_SETUP_reg(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_get_SETUP_reg(const void *const hw, hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_SETUP;
	tmp &= mask;
	return tmp;
}

static inline void hri_smccsnumber_write_SETUP_reg(const void *const hw, hri_smc_setup_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_SETUP_reg(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_SETUP_reg(const void *const hw, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_SETUP ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smccsnumber_read_SETUP_reg(const void *const hw)
{
	return ((SmcCsNumber *)hw)->SMC_SETUP;
}

static inline void hri_smccsnumber_set_PULSE_NWE_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE |= SMC_PULSE_NWE_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_get_PULSE_NWE_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NWE_PULSE(mask)) >> SMC_PULSE_NWE_PULSE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_PULSE_NWE_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp &= ~SMC_PULSE_NWE_PULSE_Msk;
	tmp |= SMC_PULSE_NWE_PULSE(data);
	((SmcCsNumber *)hw)->SMC_PULSE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_PULSE_NWE_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE &= ~SMC_PULSE_NWE_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_PULSE_NWE_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE ^= SMC_PULSE_NWE_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_read_PULSE_NWE_PULSE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NWE_PULSE_Msk) >> SMC_PULSE_NWE_PULSE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_PULSE_NCS_WR_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE |= SMC_PULSE_NCS_WR_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_get_PULSE_NCS_WR_PULSE_bf(const void *const   hw,
                                                                            hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NCS_WR_PULSE(mask)) >> SMC_PULSE_NCS_WR_PULSE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_PULSE_NCS_WR_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp &= ~SMC_PULSE_NCS_WR_PULSE_Msk;
	tmp |= SMC_PULSE_NCS_WR_PULSE(data);
	((SmcCsNumber *)hw)->SMC_PULSE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_PULSE_NCS_WR_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE &= ~SMC_PULSE_NCS_WR_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_PULSE_NCS_WR_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE ^= SMC_PULSE_NCS_WR_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_read_PULSE_NCS_WR_PULSE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NCS_WR_PULSE_Msk) >> SMC_PULSE_NCS_WR_PULSE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_PULSE_NRD_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE |= SMC_PULSE_NRD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_get_PULSE_NRD_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NRD_PULSE(mask)) >> SMC_PULSE_NRD_PULSE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_PULSE_NRD_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp &= ~SMC_PULSE_NRD_PULSE_Msk;
	tmp |= SMC_PULSE_NRD_PULSE(data);
	((SmcCsNumber *)hw)->SMC_PULSE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_PULSE_NRD_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE &= ~SMC_PULSE_NRD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_PULSE_NRD_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE ^= SMC_PULSE_NRD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_read_PULSE_NRD_PULSE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NRD_PULSE_Msk) >> SMC_PULSE_NRD_PULSE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_PULSE_NCS_RD_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE |= SMC_PULSE_NCS_RD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_get_PULSE_NCS_RD_PULSE_bf(const void *const   hw,
                                                                            hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NCS_RD_PULSE(mask)) >> SMC_PULSE_NCS_RD_PULSE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_PULSE_NCS_RD_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp &= ~SMC_PULSE_NCS_RD_PULSE_Msk;
	tmp |= SMC_PULSE_NCS_RD_PULSE(data);
	((SmcCsNumber *)hw)->SMC_PULSE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_PULSE_NCS_RD_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE &= ~SMC_PULSE_NCS_RD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_PULSE_NCS_RD_PULSE_bf(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE ^= SMC_PULSE_NCS_RD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_read_PULSE_NCS_RD_PULSE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NCS_RD_PULSE_Msk) >> SMC_PULSE_NCS_RD_PULSE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_PULSE_reg(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_get_PULSE_reg(const void *const hw, hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_PULSE;
	tmp &= mask;
	return tmp;
}

static inline void hri_smccsnumber_write_PULSE_reg(const void *const hw, hri_smc_pulse_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_PULSE_reg(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_PULSE_reg(const void *const hw, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_PULSE ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smccsnumber_read_PULSE_reg(const void *const hw)
{
	return ((SmcCsNumber *)hw)->SMC_PULSE;
}

static inline void hri_smccsnumber_set_CYCLE_NWE_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE |= SMC_CYCLE_NWE_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smccsnumber_get_CYCLE_NWE_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_CYCLE;
	tmp = (tmp & SMC_CYCLE_NWE_CYCLE(mask)) >> SMC_CYCLE_NWE_CYCLE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_CYCLE_NWE_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_CYCLE;
	tmp &= ~SMC_CYCLE_NWE_CYCLE_Msk;
	tmp |= SMC_CYCLE_NWE_CYCLE(data);
	((SmcCsNumber *)hw)->SMC_CYCLE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_CYCLE_NWE_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE &= ~SMC_CYCLE_NWE_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_CYCLE_NWE_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE ^= SMC_CYCLE_NWE_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smccsnumber_read_CYCLE_NWE_CYCLE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_CYCLE;
	tmp = (tmp & SMC_CYCLE_NWE_CYCLE_Msk) >> SMC_CYCLE_NWE_CYCLE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_CYCLE_NRD_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE |= SMC_CYCLE_NRD_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smccsnumber_get_CYCLE_NRD_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_CYCLE;
	tmp = (tmp & SMC_CYCLE_NRD_CYCLE(mask)) >> SMC_CYCLE_NRD_CYCLE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_CYCLE_NRD_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_CYCLE;
	tmp &= ~SMC_CYCLE_NRD_CYCLE_Msk;
	tmp |= SMC_CYCLE_NRD_CYCLE(data);
	((SmcCsNumber *)hw)->SMC_CYCLE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_CYCLE_NRD_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE &= ~SMC_CYCLE_NRD_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_CYCLE_NRD_CYCLE_bf(const void *const hw, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE ^= SMC_CYCLE_NRD_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smccsnumber_read_CYCLE_NRD_CYCLE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_CYCLE;
	tmp = (tmp & SMC_CYCLE_NRD_CYCLE_Msk) >> SMC_CYCLE_NRD_CYCLE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_CYCLE_reg(const void *const hw, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smccsnumber_get_CYCLE_reg(const void *const hw, hri_smc_cycle_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_CYCLE;
	tmp &= mask;
	return tmp;
}

static inline void hri_smccsnumber_write_CYCLE_reg(const void *const hw, hri_smc_cycle_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_CYCLE_reg(const void *const hw, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_CYCLE_reg(const void *const hw, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_CYCLE ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smccsnumber_read_CYCLE_reg(const void *const hw)
{
	return ((SmcCsNumber *)hw)->SMC_CYCLE;
}

static inline void hri_smccsnumber_set_MODE_READ_MODE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= SMC_MODE_READ_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smccsnumber_get_MODE_READ_MODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_READ_MODE) >> SMC_MODE_READ_MODE_Pos;
	return (bool)tmp;
}

static inline void hri_smccsnumber_write_MODE_READ_MODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= ~SMC_MODE_READ_MODE;
	tmp |= value << SMC_MODE_READ_MODE_Pos;
	((SmcCsNumber *)hw)->SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_READ_MODE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~SMC_MODE_READ_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_READ_MODE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= SMC_MODE_READ_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_set_MODE_WRITE_MODE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= SMC_MODE_WRITE_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smccsnumber_get_MODE_WRITE_MODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_WRITE_MODE) >> SMC_MODE_WRITE_MODE_Pos;
	return (bool)tmp;
}

static inline void hri_smccsnumber_write_MODE_WRITE_MODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= ~SMC_MODE_WRITE_MODE;
	tmp |= value << SMC_MODE_WRITE_MODE_Pos;
	((SmcCsNumber *)hw)->SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_WRITE_MODE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~SMC_MODE_WRITE_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_WRITE_MODE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= SMC_MODE_WRITE_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_set_MODE_BAT_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= SMC_MODE_BAT;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smccsnumber_get_MODE_BAT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_BAT) >> SMC_MODE_BAT_Pos;
	return (bool)tmp;
}

static inline void hri_smccsnumber_write_MODE_BAT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= ~SMC_MODE_BAT;
	tmp |= value << SMC_MODE_BAT_Pos;
	((SmcCsNumber *)hw)->SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_BAT_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~SMC_MODE_BAT;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_BAT_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= SMC_MODE_BAT;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_set_MODE_DBW_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= SMC_MODE_DBW;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smccsnumber_get_MODE_DBW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_DBW) >> SMC_MODE_DBW_Pos;
	return (bool)tmp;
}

static inline void hri_smccsnumber_write_MODE_DBW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= ~SMC_MODE_DBW;
	tmp |= value << SMC_MODE_DBW_Pos;
	((SmcCsNumber *)hw)->SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_DBW_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~SMC_MODE_DBW;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_DBW_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= SMC_MODE_DBW;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_set_MODE_TDF_MODE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= SMC_MODE_TDF_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smccsnumber_get_MODE_TDF_MODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_TDF_MODE) >> SMC_MODE_TDF_MODE_Pos;
	return (bool)tmp;
}

static inline void hri_smccsnumber_write_MODE_TDF_MODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= ~SMC_MODE_TDF_MODE;
	tmp |= value << SMC_MODE_TDF_MODE_Pos;
	((SmcCsNumber *)hw)->SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_TDF_MODE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~SMC_MODE_TDF_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_TDF_MODE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= SMC_MODE_TDF_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_set_MODE_PMEN_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= SMC_MODE_PMEN;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smccsnumber_get_MODE_PMEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_PMEN) >> SMC_MODE_PMEN_Pos;
	return (bool)tmp;
}

static inline void hri_smccsnumber_write_MODE_PMEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= ~SMC_MODE_PMEN;
	tmp |= value << SMC_MODE_PMEN_Pos;
	((SmcCsNumber *)hw)->SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_PMEN_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~SMC_MODE_PMEN;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_PMEN_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= SMC_MODE_PMEN;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_set_MODE_EXNW_MODE_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= SMC_MODE_EXNW_MODE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smccsnumber_get_MODE_EXNW_MODE_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_EXNW_MODE(mask)) >> SMC_MODE_EXNW_MODE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_MODE_EXNW_MODE_bf(const void *const hw, hri_smc_mode_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= ~SMC_MODE_EXNW_MODE_Msk;
	tmp |= SMC_MODE_EXNW_MODE(data);
	((SmcCsNumber *)hw)->SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_EXNW_MODE_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~SMC_MODE_EXNW_MODE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_EXNW_MODE_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= SMC_MODE_EXNW_MODE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smccsnumber_read_MODE_EXNW_MODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_EXNW_MODE_Msk) >> SMC_MODE_EXNW_MODE_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_MODE_TDF_CYCLES_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= SMC_MODE_TDF_CYCLES(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smccsnumber_get_MODE_TDF_CYCLES_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_TDF_CYCLES(mask)) >> SMC_MODE_TDF_CYCLES_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_MODE_TDF_CYCLES_bf(const void *const hw, hri_smc_mode_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= ~SMC_MODE_TDF_CYCLES_Msk;
	tmp |= SMC_MODE_TDF_CYCLES(data);
	((SmcCsNumber *)hw)->SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_TDF_CYCLES_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~SMC_MODE_TDF_CYCLES(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_TDF_CYCLES_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= SMC_MODE_TDF_CYCLES(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smccsnumber_read_MODE_TDF_CYCLES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_TDF_CYCLES_Msk) >> SMC_MODE_TDF_CYCLES_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_MODE_PS_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= SMC_MODE_PS(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smccsnumber_get_MODE_PS_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_PS(mask)) >> SMC_MODE_PS_Pos;
	return tmp;
}

static inline void hri_smccsnumber_write_MODE_PS_bf(const void *const hw, hri_smc_mode_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= ~SMC_MODE_PS_Msk;
	tmp |= SMC_MODE_PS(data);
	((SmcCsNumber *)hw)->SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_PS_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~SMC_MODE_PS(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_PS_bf(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= SMC_MODE_PS(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smccsnumber_read_MODE_PS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp = (tmp & SMC_MODE_PS_Msk) >> SMC_MODE_PS_Pos;
	return tmp;
}

static inline void hri_smccsnumber_set_MODE_reg(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smccsnumber_get_MODE_reg(const void *const hw, hri_smc_mode_reg_t mask)
{
	uint32_t tmp;
	tmp = ((SmcCsNumber *)hw)->SMC_MODE;
	tmp &= mask;
	return tmp;
}

static inline void hri_smccsnumber_write_MODE_reg(const void *const hw, hri_smc_mode_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_clear_MODE_reg(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smccsnumber_toggle_MODE_reg(const void *const hw, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((SmcCsNumber *)hw)->SMC_MODE ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smccsnumber_read_MODE_reg(const void *const hw)
{
	return ((SmcCsNumber *)hw)->SMC_MODE;
}

static inline void hri_smc_set_SETUP_NWE_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP |= SMC_SETUP_NWE_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_get_SETUP_NWE_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                                 hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NWE_SETUP(mask)) >> SMC_SETUP_NWE_SETUP_Pos;
	return tmp;
}

static inline void hri_smc_write_SETUP_NWE_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_setup_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp &= ~SMC_SETUP_NWE_SETUP_Msk;
	tmp |= SMC_SETUP_NWE_SETUP(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_SETUP_NWE_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP &= ~SMC_SETUP_NWE_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_SETUP_NWE_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP ^= SMC_SETUP_NWE_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_read_SETUP_NWE_SETUP_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NWE_SETUP_Msk) >> SMC_SETUP_NWE_SETUP_Pos;
	return tmp;
}

static inline void hri_smc_set_SETUP_NCS_WR_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP |= SMC_SETUP_NCS_WR_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_get_SETUP_NCS_WR_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                                    hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NCS_WR_SETUP(mask)) >> SMC_SETUP_NCS_WR_SETUP_Pos;
	return tmp;
}

static inline void hri_smc_write_SETUP_NCS_WR_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_smc_setup_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp &= ~SMC_SETUP_NCS_WR_SETUP_Msk;
	tmp |= SMC_SETUP_NCS_WR_SETUP(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_SETUP_NCS_WR_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP &= ~SMC_SETUP_NCS_WR_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_SETUP_NCS_WR_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                        hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP ^= SMC_SETUP_NCS_WR_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_read_SETUP_NCS_WR_SETUP_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NCS_WR_SETUP_Msk) >> SMC_SETUP_NCS_WR_SETUP_Pos;
	return tmp;
}

static inline void hri_smc_set_SETUP_NRD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP |= SMC_SETUP_NRD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_get_SETUP_NRD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                                 hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NRD_SETUP(mask)) >> SMC_SETUP_NRD_SETUP_Pos;
	return tmp;
}

static inline void hri_smc_write_SETUP_NRD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_setup_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp &= ~SMC_SETUP_NRD_SETUP_Msk;
	tmp |= SMC_SETUP_NRD_SETUP(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_SETUP_NRD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP &= ~SMC_SETUP_NRD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_SETUP_NRD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP ^= SMC_SETUP_NRD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_read_SETUP_NRD_SETUP_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NRD_SETUP_Msk) >> SMC_SETUP_NRD_SETUP_Pos;
	return tmp;
}

static inline void hri_smc_set_SETUP_NCS_RD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP |= SMC_SETUP_NCS_RD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_get_SETUP_NCS_RD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                                    hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NCS_RD_SETUP(mask)) >> SMC_SETUP_NCS_RD_SETUP_Pos;
	return tmp;
}

static inline void hri_smc_write_SETUP_NCS_RD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_smc_setup_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp &= ~SMC_SETUP_NCS_RD_SETUP_Msk;
	tmp |= SMC_SETUP_NCS_RD_SETUP(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_SETUP_NCS_RD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP &= ~SMC_SETUP_NCS_RD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_SETUP_NCS_RD_SETUP_bf(const void *const hw, uint8_t submodule_index,
                                                        hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP ^= SMC_SETUP_NCS_RD_SETUP(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_read_SETUP_NCS_RD_SETUP_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp = (tmp & SMC_SETUP_NCS_RD_SETUP_Msk) >> SMC_SETUP_NCS_RD_SETUP_Pos;
	return tmp;
}

static inline void hri_smc_set_SETUP_reg(const void *const hw, uint8_t submodule_index, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_get_SETUP_reg(const void *const hw, uint8_t submodule_index,
                                                        hri_smc_setup_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
	tmp &= mask;
	return tmp;
}

static inline void hri_smc_write_SETUP_reg(const void *const hw, uint8_t submodule_index, hri_smc_setup_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_SETUP_reg(const void *const hw, uint8_t submodule_index, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_SETUP_reg(const void *const hw, uint8_t submodule_index, hri_smc_setup_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_setup_reg_t hri_smc_read_SETUP_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_SETUP;
}

static inline void hri_smc_set_PULSE_NWE_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE |= SMC_PULSE_NWE_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_get_PULSE_NWE_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                                 hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NWE_PULSE(mask)) >> SMC_PULSE_NWE_PULSE_Pos;
	return tmp;
}

static inline void hri_smc_write_PULSE_NWE_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_pulse_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp &= ~SMC_PULSE_NWE_PULSE_Msk;
	tmp |= SMC_PULSE_NWE_PULSE(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_PULSE_NWE_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE &= ~SMC_PULSE_NWE_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_PULSE_NWE_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE ^= SMC_PULSE_NWE_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_read_PULSE_NWE_PULSE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NWE_PULSE_Msk) >> SMC_PULSE_NWE_PULSE_Pos;
	return tmp;
}

static inline void hri_smc_set_PULSE_NCS_WR_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE |= SMC_PULSE_NCS_WR_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_get_PULSE_NCS_WR_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                                    hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NCS_WR_PULSE(mask)) >> SMC_PULSE_NCS_WR_PULSE_Pos;
	return tmp;
}

static inline void hri_smc_write_PULSE_NCS_WR_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_smc_pulse_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp &= ~SMC_PULSE_NCS_WR_PULSE_Msk;
	tmp |= SMC_PULSE_NCS_WR_PULSE(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_PULSE_NCS_WR_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE &= ~SMC_PULSE_NCS_WR_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_PULSE_NCS_WR_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                        hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE ^= SMC_PULSE_NCS_WR_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_read_PULSE_NCS_WR_PULSE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NCS_WR_PULSE_Msk) >> SMC_PULSE_NCS_WR_PULSE_Pos;
	return tmp;
}

static inline void hri_smc_set_PULSE_NRD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE |= SMC_PULSE_NRD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_get_PULSE_NRD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                                 hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NRD_PULSE(mask)) >> SMC_PULSE_NRD_PULSE_Pos;
	return tmp;
}

static inline void hri_smc_write_PULSE_NRD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_pulse_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp &= ~SMC_PULSE_NRD_PULSE_Msk;
	tmp |= SMC_PULSE_NRD_PULSE(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_PULSE_NRD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE &= ~SMC_PULSE_NRD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_PULSE_NRD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE ^= SMC_PULSE_NRD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_read_PULSE_NRD_PULSE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NRD_PULSE_Msk) >> SMC_PULSE_NRD_PULSE_Pos;
	return tmp;
}

static inline void hri_smc_set_PULSE_NCS_RD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE |= SMC_PULSE_NCS_RD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_get_PULSE_NCS_RD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                                    hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NCS_RD_PULSE(mask)) >> SMC_PULSE_NCS_RD_PULSE_Pos;
	return tmp;
}

static inline void hri_smc_write_PULSE_NCS_RD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_smc_pulse_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp &= ~SMC_PULSE_NCS_RD_PULSE_Msk;
	tmp |= SMC_PULSE_NCS_RD_PULSE(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_PULSE_NCS_RD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE &= ~SMC_PULSE_NCS_RD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_PULSE_NCS_RD_PULSE_bf(const void *const hw, uint8_t submodule_index,
                                                        hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE ^= SMC_PULSE_NCS_RD_PULSE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_read_PULSE_NCS_RD_PULSE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp = (tmp & SMC_PULSE_NCS_RD_PULSE_Msk) >> SMC_PULSE_NCS_RD_PULSE_Pos;
	return tmp;
}

static inline void hri_smc_set_PULSE_reg(const void *const hw, uint8_t submodule_index, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_get_PULSE_reg(const void *const hw, uint8_t submodule_index,
                                                        hri_smc_pulse_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
	tmp &= mask;
	return tmp;
}

static inline void hri_smc_write_PULSE_reg(const void *const hw, uint8_t submodule_index, hri_smc_pulse_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_PULSE_reg(const void *const hw, uint8_t submodule_index, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_PULSE_reg(const void *const hw, uint8_t submodule_index, hri_smc_pulse_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_pulse_reg_t hri_smc_read_PULSE_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_PULSE;
}

static inline void hri_smc_set_CYCLE_NWE_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE |= SMC_CYCLE_NWE_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smc_get_CYCLE_NWE_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                                 hri_smc_cycle_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE;
	tmp = (tmp & SMC_CYCLE_NWE_CYCLE(mask)) >> SMC_CYCLE_NWE_CYCLE_Pos;
	return tmp;
}

static inline void hri_smc_write_CYCLE_NWE_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_cycle_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE;
	tmp &= ~SMC_CYCLE_NWE_CYCLE_Msk;
	tmp |= SMC_CYCLE_NWE_CYCLE(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_CYCLE_NWE_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE &= ~SMC_CYCLE_NWE_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_CYCLE_NWE_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE ^= SMC_CYCLE_NWE_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smc_read_CYCLE_NWE_CYCLE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE;
	tmp = (tmp & SMC_CYCLE_NWE_CYCLE_Msk) >> SMC_CYCLE_NWE_CYCLE_Pos;
	return tmp;
}

static inline void hri_smc_set_CYCLE_NRD_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE |= SMC_CYCLE_NRD_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smc_get_CYCLE_NRD_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                                 hri_smc_cycle_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE;
	tmp = (tmp & SMC_CYCLE_NRD_CYCLE(mask)) >> SMC_CYCLE_NRD_CYCLE_Pos;
	return tmp;
}

static inline void hri_smc_write_CYCLE_NRD_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_cycle_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE;
	tmp &= ~SMC_CYCLE_NRD_CYCLE_Msk;
	tmp |= SMC_CYCLE_NRD_CYCLE(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_CYCLE_NRD_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE &= ~SMC_CYCLE_NRD_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_CYCLE_NRD_CYCLE_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE ^= SMC_CYCLE_NRD_CYCLE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smc_read_CYCLE_NRD_CYCLE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE;
	tmp = (tmp & SMC_CYCLE_NRD_CYCLE_Msk) >> SMC_CYCLE_NRD_CYCLE_Pos;
	return tmp;
}

static inline void hri_smc_set_CYCLE_reg(const void *const hw, uint8_t submodule_index, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smc_get_CYCLE_reg(const void *const hw, uint8_t submodule_index,
                                                        hri_smc_cycle_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE;
	tmp &= mask;
	return tmp;
}

static inline void hri_smc_write_CYCLE_reg(const void *const hw, uint8_t submodule_index, hri_smc_cycle_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_CYCLE_reg(const void *const hw, uint8_t submodule_index, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_CYCLE_reg(const void *const hw, uint8_t submodule_index, hri_smc_cycle_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_cycle_reg_t hri_smc_read_CYCLE_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_CYCLE;
}

static inline void hri_smc_set_MODE_READ_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= SMC_MODE_READ_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_MODE_READ_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_READ_MODE) >> SMC_MODE_READ_MODE_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_MODE_READ_MODE_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= ~SMC_MODE_READ_MODE;
	tmp |= value << SMC_MODE_READ_MODE_Pos;
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_READ_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~SMC_MODE_READ_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_READ_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= SMC_MODE_READ_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_MODE_WRITE_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= SMC_MODE_WRITE_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_MODE_WRITE_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_WRITE_MODE) >> SMC_MODE_WRITE_MODE_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_MODE_WRITE_MODE_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= ~SMC_MODE_WRITE_MODE;
	tmp |= value << SMC_MODE_WRITE_MODE_Pos;
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_WRITE_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~SMC_MODE_WRITE_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_WRITE_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= SMC_MODE_WRITE_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_MODE_BAT_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= SMC_MODE_BAT;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_MODE_BAT_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_BAT) >> SMC_MODE_BAT_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_MODE_BAT_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= ~SMC_MODE_BAT;
	tmp |= value << SMC_MODE_BAT_Pos;
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_BAT_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~SMC_MODE_BAT;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_BAT_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= SMC_MODE_BAT;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_MODE_DBW_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= SMC_MODE_DBW;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_MODE_DBW_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_DBW) >> SMC_MODE_DBW_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_MODE_DBW_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= ~SMC_MODE_DBW;
	tmp |= value << SMC_MODE_DBW_Pos;
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_DBW_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~SMC_MODE_DBW;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_DBW_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= SMC_MODE_DBW;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_MODE_TDF_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= SMC_MODE_TDF_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_MODE_TDF_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_TDF_MODE) >> SMC_MODE_TDF_MODE_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_MODE_TDF_MODE_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= ~SMC_MODE_TDF_MODE;
	tmp |= value << SMC_MODE_TDF_MODE_Pos;
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_TDF_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~SMC_MODE_TDF_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_TDF_MODE_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= SMC_MODE_TDF_MODE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_MODE_PMEN_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= SMC_MODE_PMEN;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_MODE_PMEN_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_PMEN) >> SMC_MODE_PMEN_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_MODE_PMEN_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= ~SMC_MODE_PMEN;
	tmp |= value << SMC_MODE_PMEN_Pos;
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_PMEN_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~SMC_MODE_PMEN;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_PMEN_bit(const void *const hw, uint8_t submodule_index)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= SMC_MODE_PMEN;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_MODE_EXNW_MODE_bf(const void *const hw, uint8_t submodule_index, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= SMC_MODE_EXNW_MODE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smc_get_MODE_EXNW_MODE_bf(const void *const hw, uint8_t submodule_index,
                                                               hri_smc_mode_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_EXNW_MODE(mask)) >> SMC_MODE_EXNW_MODE_Pos;
	return tmp;
}

static inline void hri_smc_write_MODE_EXNW_MODE_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_smc_mode_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= ~SMC_MODE_EXNW_MODE_Msk;
	tmp |= SMC_MODE_EXNW_MODE(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_EXNW_MODE_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~SMC_MODE_EXNW_MODE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_EXNW_MODE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= SMC_MODE_EXNW_MODE(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smc_read_MODE_EXNW_MODE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_EXNW_MODE_Msk) >> SMC_MODE_EXNW_MODE_Pos;
	return tmp;
}

static inline void hri_smc_set_MODE_TDF_CYCLES_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= SMC_MODE_TDF_CYCLES(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smc_get_MODE_TDF_CYCLES_bf(const void *const hw, uint8_t submodule_index,
                                                                hri_smc_mode_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_TDF_CYCLES(mask)) >> SMC_MODE_TDF_CYCLES_Pos;
	return tmp;
}

static inline void hri_smc_write_MODE_TDF_CYCLES_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_mode_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= ~SMC_MODE_TDF_CYCLES_Msk;
	tmp |= SMC_MODE_TDF_CYCLES(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_TDF_CYCLES_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~SMC_MODE_TDF_CYCLES(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_TDF_CYCLES_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= SMC_MODE_TDF_CYCLES(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smc_read_MODE_TDF_CYCLES_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_TDF_CYCLES_Msk) >> SMC_MODE_TDF_CYCLES_Pos;
	return tmp;
}

static inline void hri_smc_set_MODE_PS_bf(const void *const hw, uint8_t submodule_index, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= SMC_MODE_PS(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smc_get_MODE_PS_bf(const void *const hw, uint8_t submodule_index,
                                                        hri_smc_mode_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_PS(mask)) >> SMC_MODE_PS_Pos;
	return tmp;
}

static inline void hri_smc_write_MODE_PS_bf(const void *const hw, uint8_t submodule_index, hri_smc_mode_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= ~SMC_MODE_PS_Msk;
	tmp |= SMC_MODE_PS(data);
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_PS_bf(const void *const hw, uint8_t submodule_index, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~SMC_MODE_PS(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_PS_bf(const void *const hw, uint8_t submodule_index, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= SMC_MODE_PS(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smc_read_MODE_PS_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp = (tmp & SMC_MODE_PS_Msk) >> SMC_MODE_PS_Pos;
	return tmp;
}

static inline void hri_smc_set_MODE_reg(const void *const hw, uint8_t submodule_index, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smc_get_MODE_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_smc_mode_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
	tmp &= mask;
	return tmp;
}

static inline void hri_smc_write_MODE_reg(const void *const hw, uint8_t submodule_index, hri_smc_mode_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_MODE_reg(const void *const hw, uint8_t submodule_index, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_MODE_reg(const void *const hw, uint8_t submodule_index, hri_smc_mode_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_mode_reg_t hri_smc_read_MODE_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Smc *)hw)->SmcCsNumber[submodule_index].SMC_MODE;
}

static inline bool hri_smc_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Smc *)hw)->SMC_WPSR & SMC_WPSR_WPVS) > 0;
}

static inline hri_smc_wpsr_reg_t hri_smc_get_WPSR_WPVSRC_bf(const void *const hw, hri_smc_wpsr_reg_t mask)
{
	return (((Smc *)hw)->SMC_WPSR & SMC_WPSR_WPVSRC(mask)) >> SMC_WPSR_WPVSRC_Pos;
}

static inline hri_smc_wpsr_reg_t hri_smc_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Smc *)hw)->SMC_WPSR & SMC_WPSR_WPVSRC_Msk) >> SMC_WPSR_WPVSRC_Pos;
}

static inline hri_smc_wpsr_reg_t hri_smc_get_WPSR_reg(const void *const hw, hri_smc_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_smc_wpsr_reg_t hri_smc_read_WPSR_reg(const void *const hw)
{
	return ((Smc *)hw)->SMC_WPSR;
}

static inline void hri_smc_set_OCMS_SMSE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS |= SMC_OCMS_SMSE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_OCMS_SMSE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp = (tmp & SMC_OCMS_SMSE) >> SMC_OCMS_SMSE_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_OCMS_SMSE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp &= ~SMC_OCMS_SMSE;
	tmp |= value << SMC_OCMS_SMSE_Pos;
	((Smc *)hw)->SMC_OCMS = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_OCMS_SMSE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS &= ~SMC_OCMS_SMSE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_OCMS_SMSE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS ^= SMC_OCMS_SMSE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_OCMS_CS0SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS |= SMC_OCMS_CS0SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_OCMS_CS0SE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp = (tmp & SMC_OCMS_CS0SE) >> SMC_OCMS_CS0SE_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_OCMS_CS0SE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp &= ~SMC_OCMS_CS0SE;
	tmp |= value << SMC_OCMS_CS0SE_Pos;
	((Smc *)hw)->SMC_OCMS = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_OCMS_CS0SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS &= ~SMC_OCMS_CS0SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_OCMS_CS0SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS ^= SMC_OCMS_CS0SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_OCMS_CS1SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS |= SMC_OCMS_CS1SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_OCMS_CS1SE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp = (tmp & SMC_OCMS_CS1SE) >> SMC_OCMS_CS1SE_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_OCMS_CS1SE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp &= ~SMC_OCMS_CS1SE;
	tmp |= value << SMC_OCMS_CS1SE_Pos;
	((Smc *)hw)->SMC_OCMS = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_OCMS_CS1SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS &= ~SMC_OCMS_CS1SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_OCMS_CS1SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS ^= SMC_OCMS_CS1SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_OCMS_CS2SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS |= SMC_OCMS_CS2SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_OCMS_CS2SE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp = (tmp & SMC_OCMS_CS2SE) >> SMC_OCMS_CS2SE_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_OCMS_CS2SE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp &= ~SMC_OCMS_CS2SE;
	tmp |= value << SMC_OCMS_CS2SE_Pos;
	((Smc *)hw)->SMC_OCMS = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_OCMS_CS2SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS &= ~SMC_OCMS_CS2SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_OCMS_CS2SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS ^= SMC_OCMS_CS2SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_OCMS_CS3SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS |= SMC_OCMS_CS3SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_OCMS_CS3SE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp = (tmp & SMC_OCMS_CS3SE) >> SMC_OCMS_CS3SE_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_OCMS_CS3SE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp &= ~SMC_OCMS_CS3SE;
	tmp |= value << SMC_OCMS_CS3SE_Pos;
	((Smc *)hw)->SMC_OCMS = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_OCMS_CS3SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS &= ~SMC_OCMS_CS3SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_OCMS_CS3SE_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS ^= SMC_OCMS_CS3SE;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_OCMS_reg(const void *const hw, hri_smc_ocms_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_ocms_reg_t hri_smc_get_OCMS_reg(const void *const hw, hri_smc_ocms_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_OCMS;
	tmp &= mask;
	return tmp;
}

static inline void hri_smc_write_OCMS_reg(const void *const hw, hri_smc_ocms_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_OCMS_reg(const void *const hw, hri_smc_ocms_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_OCMS_reg(const void *const hw, hri_smc_ocms_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_OCMS ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_ocms_reg_t hri_smc_read_OCMS_reg(const void *const hw)
{
	return ((Smc *)hw)->SMC_OCMS;
}

static inline void hri_smc_set_WPMR_WPEN_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR |= SMC_WPMR_WPEN;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_smc_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_WPMR;
	tmp = (tmp & SMC_WPMR_WPEN) >> SMC_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_smc_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SMC_WPMR;
	tmp &= ~SMC_WPMR_WPEN;
	tmp |= value << SMC_WPMR_WPEN_Pos;
	((Smc *)hw)->SMC_WPMR = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_WPMR_WPEN_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR &= ~SMC_WPMR_WPEN;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_WPMR_WPEN_bit(const void *const hw)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR ^= SMC_WPMR_WPEN;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_set_WPMR_WPKEY_bf(const void *const hw, hri_smc_wpmr_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR |= SMC_WPMR_WPKEY(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_wpmr_reg_t hri_smc_get_WPMR_WPKEY_bf(const void *const hw, hri_smc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_WPMR;
	tmp = (tmp & SMC_WPMR_WPKEY(mask)) >> SMC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_smc_write_WPMR_WPKEY_bf(const void *const hw, hri_smc_wpmr_reg_t data)
{
	uint32_t tmp;
	SMC_CRITICAL_SECTION_ENTER();
	tmp = ((Smc *)hw)->SMC_WPMR;
	tmp &= ~SMC_WPMR_WPKEY_Msk;
	tmp |= SMC_WPMR_WPKEY(data);
	((Smc *)hw)->SMC_WPMR = tmp;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_WPMR_WPKEY_bf(const void *const hw, hri_smc_wpmr_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR &= ~SMC_WPMR_WPKEY(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_WPMR_WPKEY_bf(const void *const hw, hri_smc_wpmr_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR ^= SMC_WPMR_WPKEY(mask);
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_wpmr_reg_t hri_smc_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_WPMR;
	tmp = (tmp & SMC_WPMR_WPKEY_Msk) >> SMC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_smc_set_WPMR_reg(const void *const hw, hri_smc_wpmr_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR |= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_wpmr_reg_t hri_smc_get_WPMR_reg(const void *const hw, hri_smc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Smc *)hw)->SMC_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_smc_write_WPMR_reg(const void *const hw, hri_smc_wpmr_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_clear_WPMR_reg(const void *const hw, hri_smc_wpmr_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR &= ~mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_toggle_WPMR_reg(const void *const hw, hri_smc_wpmr_reg_t mask)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_WPMR ^= mask;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_smc_wpmr_reg_t hri_smc_read_WPMR_reg(const void *const hw)
{
	return ((Smc *)hw)->SMC_WPMR;
}

static inline void hri_smc_write_KEY1_reg(const void *const hw, hri_smc_key1_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_KEY1 = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_smc_write_KEY2_reg(const void *const hw, hri_smc_key2_reg_t data)
{
	SMC_CRITICAL_SECTION_ENTER();
	((Smc *)hw)->SMC_KEY2 = data;
	SMC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_SMC_E70B_H_INCLUDED */
#endif /* _SAME70_SMC_COMPONENT_ */
