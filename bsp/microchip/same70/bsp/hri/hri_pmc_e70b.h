/**
 * \file
 *
 * \brief SAM PMC
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

#ifdef _SAME70_PMC_COMPONENT_
#ifndef _HRI_PMC_E70B_H_INCLUDED_
#define _HRI_PMC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_PMC_CRITICAL_SECTIONS)
#define PMC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define PMC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define PMC_CRITICAL_SECTION_ENTER()
#define PMC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_pmc_ckgr_mcfr_reg_t;
typedef uint32_t hri_pmc_ckgr_mor_reg_t;
typedef uint32_t hri_pmc_ckgr_pllar_reg_t;
typedef uint32_t hri_pmc_ckgr_uckr_reg_t;
typedef uint32_t hri_pmc_focr_reg_t;
typedef uint32_t hri_pmc_fsmr_reg_t;
typedef uint32_t hri_pmc_fspr_reg_t;
typedef uint32_t hri_pmc_imr_reg_t;
typedef uint32_t hri_pmc_mckr_reg_t;
typedef uint32_t hri_pmc_ocr_reg_t;
typedef uint32_t hri_pmc_pck_reg_t;
typedef uint32_t hri_pmc_pcr_reg_t;
typedef uint32_t hri_pmc_pcsr0_reg_t;
typedef uint32_t hri_pmc_pcsr1_reg_t;
typedef uint32_t hri_pmc_pmmr_reg_t;
typedef uint32_t hri_pmc_scsr_reg_t;
typedef uint32_t hri_pmc_slpwk_aipr_reg_t;
typedef uint32_t hri_pmc_slpwk_asr0_reg_t;
typedef uint32_t hri_pmc_slpwk_asr1_reg_t;
typedef uint32_t hri_pmc_slpwk_sr0_reg_t;
typedef uint32_t hri_pmc_slpwk_sr1_reg_t;
typedef uint32_t hri_pmc_sr_reg_t;
typedef uint32_t hri_pmc_usb_reg_t;
typedef uint32_t hri_pmc_wpmr_reg_t;
typedef uint32_t hri_pmc_wpsr_reg_t;

static inline bool hri_pmc_get_SCSR_HCLKS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_HCLKS) >> PMC_SCSR_HCLKS_Pos;
}

static inline void hri_pmc_set_SCSR_USBCLK_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCER = PMC_SCSR_USBCLK;
}

static inline bool hri_pmc_get_SCSR_USBCLK_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_USBCLK) >> PMC_SCSR_USBCLK_Pos;
}

static inline void hri_pmc_write_SCSR_USBCLK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SCDR = PMC_SCSR_USBCLK;
	} else {
		((Pmc *)hw)->PMC_SCER = PMC_SCSR_USBCLK;
	}
}

static inline void hri_pmc_clear_SCSR_USBCLK_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCDR = PMC_SCSR_USBCLK;
}

static inline void hri_pmc_set_SCSR_PCK0_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK0;
}

static inline bool hri_pmc_get_SCSR_PCK0_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_PCK0) >> PMC_SCSR_PCK0_Pos;
}

static inline void hri_pmc_write_SCSR_PCK0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK0;
	} else {
		((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK0;
	}
}

static inline void hri_pmc_clear_SCSR_PCK0_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK0;
}

static inline void hri_pmc_set_SCSR_PCK1_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK1;
}

static inline bool hri_pmc_get_SCSR_PCK1_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_PCK1) >> PMC_SCSR_PCK1_Pos;
}

static inline void hri_pmc_write_SCSR_PCK1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK1;
	} else {
		((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK1;
	}
}

static inline void hri_pmc_clear_SCSR_PCK1_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK1;
}

static inline void hri_pmc_set_SCSR_PCK2_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK2;
}

static inline bool hri_pmc_get_SCSR_PCK2_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_PCK2) >> PMC_SCSR_PCK2_Pos;
}

static inline void hri_pmc_write_SCSR_PCK2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK2;
	} else {
		((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK2;
	}
}

static inline void hri_pmc_clear_SCSR_PCK2_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK2;
}

static inline void hri_pmc_set_SCSR_PCK3_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK3;
}

static inline bool hri_pmc_get_SCSR_PCK3_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_PCK3) >> PMC_SCSR_PCK3_Pos;
}

static inline void hri_pmc_write_SCSR_PCK3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK3;
	} else {
		((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK3;
	}
}

static inline void hri_pmc_clear_SCSR_PCK3_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK3;
}

static inline void hri_pmc_set_SCSR_PCK4_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK4;
}

static inline bool hri_pmc_get_SCSR_PCK4_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_PCK4) >> PMC_SCSR_PCK4_Pos;
}

static inline void hri_pmc_write_SCSR_PCK4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK4;
	} else {
		((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK4;
	}
}

static inline void hri_pmc_clear_SCSR_PCK4_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK4;
}

static inline void hri_pmc_set_SCSR_PCK5_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK5;
}

static inline bool hri_pmc_get_SCSR_PCK5_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_PCK5) >> PMC_SCSR_PCK5_Pos;
}

static inline void hri_pmc_write_SCSR_PCK5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK5;
	} else {
		((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK5;
	}
}

static inline void hri_pmc_clear_SCSR_PCK5_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK5;
}

static inline void hri_pmc_set_SCSR_PCK6_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK6;
}

static inline bool hri_pmc_get_SCSR_PCK6_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_PCK6) >> PMC_SCSR_PCK6_Pos;
}

static inline void hri_pmc_write_SCSR_PCK6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK6;
	} else {
		((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK6;
	}
}

static inline void hri_pmc_clear_SCSR_PCK6_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK6;
}

static inline void hri_pmc_set_SCSR_PCK7_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK7;
}

static inline bool hri_pmc_get_SCSR_PCK7_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SCSR & PMC_SCSR_PCK7) >> PMC_SCSR_PCK7_Pos;
}

static inline void hri_pmc_write_SCSR_PCK7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK7;
	} else {
		((Pmc *)hw)->PMC_SCER = PMC_SCSR_PCK7;
	}
}

static inline void hri_pmc_clear_SCSR_PCK7_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SCDR = PMC_SCSR_PCK7;
}

static inline void hri_pmc_set_SCSR_reg(const void *const hw, hri_pmc_scsr_reg_t mask)
{
	((Pmc *)hw)->PMC_SCER = mask;
}

static inline hri_pmc_scsr_reg_t hri_pmc_get_SCSR_reg(const void *const hw, hri_pmc_scsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_SCSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_scsr_reg_t hri_pmc_read_SCSR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_SCSR;
}

static inline void hri_pmc_write_SCSR_reg(const void *const hw, hri_pmc_scsr_reg_t data)
{
	((Pmc *)hw)->PMC_SCER = data;
	((Pmc *)hw)->PMC_SCDR = ~data;
}

static inline void hri_pmc_clear_SCSR_reg(const void *const hw, hri_pmc_scsr_reg_t mask)
{
	((Pmc *)hw)->PMC_SCDR = mask;
}

static inline void hri_pmc_write_SCDR_reg(const void *const hw, hri_pmc_scsr_reg_t data)
{
	((Pmc *)hw)->PMC_SCDR = data;
}

static inline void hri_pmc_write_SCER_reg(const void *const hw, hri_pmc_scsr_reg_t data)
{
	((Pmc *)hw)->PMC_SCER = data;
}

static inline void hri_pmc_set_PCSR0_PID7_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID7;
}

static inline bool hri_pmc_get_PCSR0_PID7_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID7) >> PMC_PCSR0_PID7_Pos;
}

static inline void hri_pmc_write_PCSR0_PID7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID7;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID7;
	}
}

static inline void hri_pmc_clear_PCSR0_PID7_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID7;
}

static inline void hri_pmc_set_PCSR0_PID8_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID8;
}

static inline bool hri_pmc_get_PCSR0_PID8_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID8) >> PMC_PCSR0_PID8_Pos;
}

static inline void hri_pmc_write_PCSR0_PID8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID8;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID8;
	}
}

static inline void hri_pmc_clear_PCSR0_PID8_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID8;
}

static inline void hri_pmc_set_PCSR0_PID9_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID9;
}

static inline bool hri_pmc_get_PCSR0_PID9_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID9) >> PMC_PCSR0_PID9_Pos;
}

static inline void hri_pmc_write_PCSR0_PID9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID9;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID9;
	}
}

static inline void hri_pmc_clear_PCSR0_PID9_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID9;
}

static inline void hri_pmc_set_PCSR0_PID10_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID10;
}

static inline bool hri_pmc_get_PCSR0_PID10_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID10) >> PMC_PCSR0_PID10_Pos;
}

static inline void hri_pmc_write_PCSR0_PID10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID10;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID10;
	}
}

static inline void hri_pmc_clear_PCSR0_PID10_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID10;
}

static inline void hri_pmc_set_PCSR0_PID11_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID11;
}

static inline bool hri_pmc_get_PCSR0_PID11_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID11) >> PMC_PCSR0_PID11_Pos;
}

static inline void hri_pmc_write_PCSR0_PID11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID11;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID11;
	}
}

static inline void hri_pmc_clear_PCSR0_PID11_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID11;
}

static inline void hri_pmc_set_PCSR0_PID12_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID12;
}

static inline bool hri_pmc_get_PCSR0_PID12_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID12) >> PMC_PCSR0_PID12_Pos;
}

static inline void hri_pmc_write_PCSR0_PID12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID12;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID12;
	}
}

static inline void hri_pmc_clear_PCSR0_PID12_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID12;
}

static inline void hri_pmc_set_PCSR0_PID13_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID13;
}

static inline bool hri_pmc_get_PCSR0_PID13_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID13) >> PMC_PCSR0_PID13_Pos;
}

static inline void hri_pmc_write_PCSR0_PID13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID13;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID13;
	}
}

static inline void hri_pmc_clear_PCSR0_PID13_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID13;
}

static inline void hri_pmc_set_PCSR0_PID14_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID14;
}

static inline bool hri_pmc_get_PCSR0_PID14_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID14) >> PMC_PCSR0_PID14_Pos;
}

static inline void hri_pmc_write_PCSR0_PID14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID14;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID14;
	}
}

static inline void hri_pmc_clear_PCSR0_PID14_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID14;
}

static inline void hri_pmc_set_PCSR0_PID15_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID15;
}

static inline bool hri_pmc_get_PCSR0_PID15_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID15) >> PMC_PCSR0_PID15_Pos;
}

static inline void hri_pmc_write_PCSR0_PID15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID15;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID15;
	}
}

static inline void hri_pmc_clear_PCSR0_PID15_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID15;
}

static inline void hri_pmc_set_PCSR0_PID16_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID16;
}

static inline bool hri_pmc_get_PCSR0_PID16_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID16) >> PMC_PCSR0_PID16_Pos;
}

static inline void hri_pmc_write_PCSR0_PID16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID16;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID16;
	}
}

static inline void hri_pmc_clear_PCSR0_PID16_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID16;
}

static inline void hri_pmc_set_PCSR0_PID17_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID17;
}

static inline bool hri_pmc_get_PCSR0_PID17_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID17) >> PMC_PCSR0_PID17_Pos;
}

static inline void hri_pmc_write_PCSR0_PID17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID17;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID17;
	}
}

static inline void hri_pmc_clear_PCSR0_PID17_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID17;
}

static inline void hri_pmc_set_PCSR0_PID18_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID18;
}

static inline bool hri_pmc_get_PCSR0_PID18_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID18) >> PMC_PCSR0_PID18_Pos;
}

static inline void hri_pmc_write_PCSR0_PID18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID18;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID18;
	}
}

static inline void hri_pmc_clear_PCSR0_PID18_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID18;
}

static inline void hri_pmc_set_PCSR0_PID19_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID19;
}

static inline bool hri_pmc_get_PCSR0_PID19_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID19) >> PMC_PCSR0_PID19_Pos;
}

static inline void hri_pmc_write_PCSR0_PID19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID19;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID19;
	}
}

static inline void hri_pmc_clear_PCSR0_PID19_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID19;
}

static inline void hri_pmc_set_PCSR0_PID20_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID20;
}

static inline bool hri_pmc_get_PCSR0_PID20_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID20) >> PMC_PCSR0_PID20_Pos;
}

static inline void hri_pmc_write_PCSR0_PID20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID20;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID20;
	}
}

static inline void hri_pmc_clear_PCSR0_PID20_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID20;
}

static inline void hri_pmc_set_PCSR0_PID21_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID21;
}

static inline bool hri_pmc_get_PCSR0_PID21_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID21) >> PMC_PCSR0_PID21_Pos;
}

static inline void hri_pmc_write_PCSR0_PID21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID21;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID21;
	}
}

static inline void hri_pmc_clear_PCSR0_PID21_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID21;
}

static inline void hri_pmc_set_PCSR0_PID22_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID22;
}

static inline bool hri_pmc_get_PCSR0_PID22_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID22) >> PMC_PCSR0_PID22_Pos;
}

static inline void hri_pmc_write_PCSR0_PID22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID22;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID22;
	}
}

static inline void hri_pmc_clear_PCSR0_PID22_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID22;
}

static inline void hri_pmc_set_PCSR0_PID23_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID23;
}

static inline bool hri_pmc_get_PCSR0_PID23_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID23) >> PMC_PCSR0_PID23_Pos;
}

static inline void hri_pmc_write_PCSR0_PID23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID23;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID23;
	}
}

static inline void hri_pmc_clear_PCSR0_PID23_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID23;
}

static inline void hri_pmc_set_PCSR0_PID24_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID24;
}

static inline bool hri_pmc_get_PCSR0_PID24_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID24) >> PMC_PCSR0_PID24_Pos;
}

static inline void hri_pmc_write_PCSR0_PID24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID24;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID24;
	}
}

static inline void hri_pmc_clear_PCSR0_PID24_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID24;
}

static inline void hri_pmc_set_PCSR0_PID25_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID25;
}

static inline bool hri_pmc_get_PCSR0_PID25_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID25) >> PMC_PCSR0_PID25_Pos;
}

static inline void hri_pmc_write_PCSR0_PID25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID25;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID25;
	}
}

static inline void hri_pmc_clear_PCSR0_PID25_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID25;
}

static inline void hri_pmc_set_PCSR0_PID26_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID26;
}

static inline bool hri_pmc_get_PCSR0_PID26_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID26) >> PMC_PCSR0_PID26_Pos;
}

static inline void hri_pmc_write_PCSR0_PID26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID26;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID26;
	}
}

static inline void hri_pmc_clear_PCSR0_PID26_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID26;
}

static inline void hri_pmc_set_PCSR0_PID27_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID27;
}

static inline bool hri_pmc_get_PCSR0_PID27_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID27) >> PMC_PCSR0_PID27_Pos;
}

static inline void hri_pmc_write_PCSR0_PID27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID27;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID27;
	}
}

static inline void hri_pmc_clear_PCSR0_PID27_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID27;
}

static inline void hri_pmc_set_PCSR0_PID28_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID28;
}

static inline bool hri_pmc_get_PCSR0_PID28_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID28) >> PMC_PCSR0_PID28_Pos;
}

static inline void hri_pmc_write_PCSR0_PID28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID28;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID28;
	}
}

static inline void hri_pmc_clear_PCSR0_PID28_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID28;
}

static inline void hri_pmc_set_PCSR0_PID29_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID29;
}

static inline bool hri_pmc_get_PCSR0_PID29_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID29) >> PMC_PCSR0_PID29_Pos;
}

static inline void hri_pmc_write_PCSR0_PID29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID29;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID29;
	}
}

static inline void hri_pmc_clear_PCSR0_PID29_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID29;
}

static inline void hri_pmc_set_PCSR0_PID30_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID30;
}

static inline bool hri_pmc_get_PCSR0_PID30_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID30) >> PMC_PCSR0_PID30_Pos;
}

static inline void hri_pmc_write_PCSR0_PID30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID30;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID30;
	}
}

static inline void hri_pmc_clear_PCSR0_PID30_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID30;
}

static inline void hri_pmc_set_PCSR0_PID31_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID31;
}

static inline bool hri_pmc_get_PCSR0_PID31_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR0 & PMC_PCSR0_PID31) >> PMC_PCSR0_PID31_Pos;
}

static inline void hri_pmc_write_PCSR0_PID31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID31;
	} else {
		((Pmc *)hw)->PMC_PCER0 = PMC_PCSR0_PID31;
	}
}

static inline void hri_pmc_clear_PCSR0_PID31_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR0 = PMC_PCSR0_PID31;
}

static inline void hri_pmc_set_PCSR0_reg(const void *const hw, hri_pmc_pcsr0_reg_t mask)
{
	((Pmc *)hw)->PMC_PCER0 = mask;
}

static inline hri_pmc_pcsr0_reg_t hri_pmc_get_PCSR0_reg(const void *const hw, hri_pmc_pcsr0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCSR0;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_pcsr0_reg_t hri_pmc_read_PCSR0_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_PCSR0;
}

static inline void hri_pmc_write_PCSR0_reg(const void *const hw, hri_pmc_pcsr0_reg_t data)
{
	((Pmc *)hw)->PMC_PCER0 = data;
	((Pmc *)hw)->PMC_PCDR0 = ~data;
}

static inline void hri_pmc_clear_PCSR0_reg(const void *const hw, hri_pmc_pcsr0_reg_t mask)
{
	((Pmc *)hw)->PMC_PCDR0 = mask;
}

static inline void hri_pmc_set_IMR_MOSCXTS_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_MOSCXTS;
}

static inline bool hri_pmc_get_IMR_MOSCXTS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_MOSCXTS) >> PMC_IMR_MOSCXTS_Pos;
}

static inline void hri_pmc_write_IMR_MOSCXTS_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_MOSCXTS;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_MOSCXTS;
	}
}

static inline void hri_pmc_clear_IMR_MOSCXTS_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_MOSCXTS;
}

static inline void hri_pmc_set_IMR_LOCKA_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_LOCKA;
}

static inline bool hri_pmc_get_IMR_LOCKA_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_LOCKA) >> PMC_IMR_LOCKA_Pos;
}

static inline void hri_pmc_write_IMR_LOCKA_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_LOCKA;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_LOCKA;
	}
}

static inline void hri_pmc_clear_IMR_LOCKA_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_LOCKA;
}

static inline void hri_pmc_set_IMR_MCKRDY_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_MCKRDY;
}

static inline bool hri_pmc_get_IMR_MCKRDY_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_MCKRDY) >> PMC_IMR_MCKRDY_Pos;
}

static inline void hri_pmc_write_IMR_MCKRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_MCKRDY;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_MCKRDY;
	}
}

static inline void hri_pmc_clear_IMR_MCKRDY_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_MCKRDY;
}

static inline void hri_pmc_set_IMR_LOCKU_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_LOCKU;
}

static inline bool hri_pmc_get_IMR_LOCKU_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_LOCKU) >> PMC_IMR_LOCKU_Pos;
}

static inline void hri_pmc_write_IMR_LOCKU_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_LOCKU;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_LOCKU;
	}
}

static inline void hri_pmc_clear_IMR_LOCKU_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_LOCKU;
}

static inline void hri_pmc_set_IMR_PCKRDY0_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY0;
}

static inline bool hri_pmc_get_IMR_PCKRDY0_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_PCKRDY0) >> PMC_IMR_PCKRDY0_Pos;
}

static inline void hri_pmc_write_IMR_PCKRDY0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY0;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY0;
	}
}

static inline void hri_pmc_clear_IMR_PCKRDY0_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY0;
}

static inline void hri_pmc_set_IMR_PCKRDY1_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY1;
}

static inline bool hri_pmc_get_IMR_PCKRDY1_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_PCKRDY1) >> PMC_IMR_PCKRDY1_Pos;
}

static inline void hri_pmc_write_IMR_PCKRDY1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY1;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY1;
	}
}

static inline void hri_pmc_clear_IMR_PCKRDY1_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY1;
}

static inline void hri_pmc_set_IMR_PCKRDY2_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY2;
}

static inline bool hri_pmc_get_IMR_PCKRDY2_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_PCKRDY2) >> PMC_IMR_PCKRDY2_Pos;
}

static inline void hri_pmc_write_IMR_PCKRDY2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY2;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY2;
	}
}

static inline void hri_pmc_clear_IMR_PCKRDY2_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY2;
}

static inline void hri_pmc_set_IMR_PCKRDY3_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY3;
}

static inline bool hri_pmc_get_IMR_PCKRDY3_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_PCKRDY3) >> PMC_IMR_PCKRDY3_Pos;
}

static inline void hri_pmc_write_IMR_PCKRDY3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY3;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY3;
	}
}

static inline void hri_pmc_clear_IMR_PCKRDY3_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY3;
}

static inline void hri_pmc_set_IMR_PCKRDY4_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY4;
}

static inline bool hri_pmc_get_IMR_PCKRDY4_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_PCKRDY4) >> PMC_IMR_PCKRDY4_Pos;
}

static inline void hri_pmc_write_IMR_PCKRDY4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY4;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY4;
	}
}

static inline void hri_pmc_clear_IMR_PCKRDY4_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY4;
}

static inline void hri_pmc_set_IMR_PCKRDY5_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY5;
}

static inline bool hri_pmc_get_IMR_PCKRDY5_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_PCKRDY5) >> PMC_IMR_PCKRDY5_Pos;
}

static inline void hri_pmc_write_IMR_PCKRDY5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY5;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY5;
	}
}

static inline void hri_pmc_clear_IMR_PCKRDY5_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY5;
}

static inline void hri_pmc_set_IMR_PCKRDY6_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY6;
}

static inline bool hri_pmc_get_IMR_PCKRDY6_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_PCKRDY6) >> PMC_IMR_PCKRDY6_Pos;
}

static inline void hri_pmc_write_IMR_PCKRDY6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY6;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY6;
	}
}

static inline void hri_pmc_clear_IMR_PCKRDY6_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY6;
}

static inline void hri_pmc_set_IMR_PCKRDY7_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY7;
}

static inline bool hri_pmc_get_IMR_PCKRDY7_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_PCKRDY7) >> PMC_IMR_PCKRDY7_Pos;
}

static inline void hri_pmc_write_IMR_PCKRDY7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY7;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_PCKRDY7;
	}
}

static inline void hri_pmc_clear_IMR_PCKRDY7_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_PCKRDY7;
}

static inline void hri_pmc_set_IMR_MOSCSELS_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_MOSCSELS;
}

static inline bool hri_pmc_get_IMR_MOSCSELS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_MOSCSELS) >> PMC_IMR_MOSCSELS_Pos;
}

static inline void hri_pmc_write_IMR_MOSCSELS_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_MOSCSELS;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_MOSCSELS;
	}
}

static inline void hri_pmc_clear_IMR_MOSCSELS_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_MOSCSELS;
}

static inline void hri_pmc_set_IMR_MOSCRCS_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_MOSCRCS;
}

static inline bool hri_pmc_get_IMR_MOSCRCS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_MOSCRCS) >> PMC_IMR_MOSCRCS_Pos;
}

static inline void hri_pmc_write_IMR_MOSCRCS_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_MOSCRCS;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_MOSCRCS;
	}
}

static inline void hri_pmc_clear_IMR_MOSCRCS_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_MOSCRCS;
}

static inline void hri_pmc_set_IMR_CFDEV_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_CFDEV;
}

static inline bool hri_pmc_get_IMR_CFDEV_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_CFDEV) >> PMC_IMR_CFDEV_Pos;
}

static inline void hri_pmc_write_IMR_CFDEV_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_CFDEV;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_CFDEV;
	}
}

static inline void hri_pmc_clear_IMR_CFDEV_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_CFDEV;
}

static inline void hri_pmc_set_IMR_XT32KERR_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IER = PMC_IMR_XT32KERR;
}

static inline bool hri_pmc_get_IMR_XT32KERR_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_IMR & PMC_IMR_XT32KERR) >> PMC_IMR_XT32KERR_Pos;
}

static inline void hri_pmc_write_IMR_XT32KERR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_IDR = PMC_IMR_XT32KERR;
	} else {
		((Pmc *)hw)->PMC_IER = PMC_IMR_XT32KERR;
	}
}

static inline void hri_pmc_clear_IMR_XT32KERR_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_IDR = PMC_IMR_XT32KERR;
}

static inline void hri_pmc_set_IMR_reg(const void *const hw, hri_pmc_imr_reg_t mask)
{
	((Pmc *)hw)->PMC_IER = mask;
}

static inline hri_pmc_imr_reg_t hri_pmc_get_IMR_reg(const void *const hw, hri_pmc_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_imr_reg_t hri_pmc_read_IMR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_IMR;
}

static inline void hri_pmc_write_IMR_reg(const void *const hw, hri_pmc_imr_reg_t data)
{
	((Pmc *)hw)->PMC_IER = data;
	((Pmc *)hw)->PMC_IDR = ~data;
}

static inline void hri_pmc_clear_IMR_reg(const void *const hw, hri_pmc_imr_reg_t mask)
{
	((Pmc *)hw)->PMC_IDR = mask;
}

static inline void hri_pmc_set_PCSR1_PID32_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID32;
}

static inline bool hri_pmc_get_PCSR1_PID32_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID32) >> PMC_PCSR1_PID32_Pos;
}

static inline void hri_pmc_write_PCSR1_PID32_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID32;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID32;
	}
}

static inline void hri_pmc_clear_PCSR1_PID32_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID32;
}

static inline void hri_pmc_set_PCSR1_PID33_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID33;
}

static inline bool hri_pmc_get_PCSR1_PID33_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID33) >> PMC_PCSR1_PID33_Pos;
}

static inline void hri_pmc_write_PCSR1_PID33_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID33;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID33;
	}
}

static inline void hri_pmc_clear_PCSR1_PID33_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID33;
}

static inline void hri_pmc_set_PCSR1_PID34_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID34;
}

static inline bool hri_pmc_get_PCSR1_PID34_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID34) >> PMC_PCSR1_PID34_Pos;
}

static inline void hri_pmc_write_PCSR1_PID34_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID34;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID34;
	}
}

static inline void hri_pmc_clear_PCSR1_PID34_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID34;
}

static inline void hri_pmc_set_PCSR1_PID35_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID35;
}

static inline bool hri_pmc_get_PCSR1_PID35_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID35) >> PMC_PCSR1_PID35_Pos;
}

static inline void hri_pmc_write_PCSR1_PID35_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID35;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID35;
	}
}

static inline void hri_pmc_clear_PCSR1_PID35_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID35;
}

static inline void hri_pmc_set_PCSR1_PID37_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID37;
}

static inline bool hri_pmc_get_PCSR1_PID37_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID37) >> PMC_PCSR1_PID37_Pos;
}

static inline void hri_pmc_write_PCSR1_PID37_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID37;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID37;
	}
}

static inline void hri_pmc_clear_PCSR1_PID37_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID37;
}

static inline void hri_pmc_set_PCSR1_PID39_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID39;
}

static inline bool hri_pmc_get_PCSR1_PID39_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID39) >> PMC_PCSR1_PID39_Pos;
}

static inline void hri_pmc_write_PCSR1_PID39_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID39;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID39;
	}
}

static inline void hri_pmc_clear_PCSR1_PID39_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID39;
}

static inline void hri_pmc_set_PCSR1_PID40_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID40;
}

static inline bool hri_pmc_get_PCSR1_PID40_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID40) >> PMC_PCSR1_PID40_Pos;
}

static inline void hri_pmc_write_PCSR1_PID40_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID40;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID40;
	}
}

static inline void hri_pmc_clear_PCSR1_PID40_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID40;
}

static inline void hri_pmc_set_PCSR1_PID41_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID41;
}

static inline bool hri_pmc_get_PCSR1_PID41_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID41) >> PMC_PCSR1_PID41_Pos;
}

static inline void hri_pmc_write_PCSR1_PID41_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID41;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID41;
	}
}

static inline void hri_pmc_clear_PCSR1_PID41_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID41;
}

static inline void hri_pmc_set_PCSR1_PID42_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID42;
}

static inline bool hri_pmc_get_PCSR1_PID42_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID42) >> PMC_PCSR1_PID42_Pos;
}

static inline void hri_pmc_write_PCSR1_PID42_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID42;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID42;
	}
}

static inline void hri_pmc_clear_PCSR1_PID42_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID42;
}

static inline void hri_pmc_set_PCSR1_PID43_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID43;
}

static inline bool hri_pmc_get_PCSR1_PID43_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID43) >> PMC_PCSR1_PID43_Pos;
}

static inline void hri_pmc_write_PCSR1_PID43_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID43;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID43;
	}
}

static inline void hri_pmc_clear_PCSR1_PID43_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID43;
}

static inline void hri_pmc_set_PCSR1_PID44_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID44;
}

static inline bool hri_pmc_get_PCSR1_PID44_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID44) >> PMC_PCSR1_PID44_Pos;
}

static inline void hri_pmc_write_PCSR1_PID44_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID44;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID44;
	}
}

static inline void hri_pmc_clear_PCSR1_PID44_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID44;
}

static inline void hri_pmc_set_PCSR1_PID45_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID45;
}

static inline bool hri_pmc_get_PCSR1_PID45_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID45) >> PMC_PCSR1_PID45_Pos;
}

static inline void hri_pmc_write_PCSR1_PID45_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID45;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID45;
	}
}

static inline void hri_pmc_clear_PCSR1_PID45_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID45;
}

static inline void hri_pmc_set_PCSR1_PID46_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID46;
}

static inline bool hri_pmc_get_PCSR1_PID46_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID46) >> PMC_PCSR1_PID46_Pos;
}

static inline void hri_pmc_write_PCSR1_PID46_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID46;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID46;
	}
}

static inline void hri_pmc_clear_PCSR1_PID46_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID46;
}

static inline void hri_pmc_set_PCSR1_PID47_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID47;
}

static inline bool hri_pmc_get_PCSR1_PID47_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID47) >> PMC_PCSR1_PID47_Pos;
}

static inline void hri_pmc_write_PCSR1_PID47_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID47;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID47;
	}
}

static inline void hri_pmc_clear_PCSR1_PID47_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID47;
}

static inline void hri_pmc_set_PCSR1_PID48_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID48;
}

static inline bool hri_pmc_get_PCSR1_PID48_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID48) >> PMC_PCSR1_PID48_Pos;
}

static inline void hri_pmc_write_PCSR1_PID48_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID48;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID48;
	}
}

static inline void hri_pmc_clear_PCSR1_PID48_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID48;
}

static inline void hri_pmc_set_PCSR1_PID49_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID49;
}

static inline bool hri_pmc_get_PCSR1_PID49_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID49) >> PMC_PCSR1_PID49_Pos;
}

static inline void hri_pmc_write_PCSR1_PID49_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID49;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID49;
	}
}

static inline void hri_pmc_clear_PCSR1_PID49_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID49;
}

static inline void hri_pmc_set_PCSR1_PID50_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID50;
}

static inline bool hri_pmc_get_PCSR1_PID50_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID50) >> PMC_PCSR1_PID50_Pos;
}

static inline void hri_pmc_write_PCSR1_PID50_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID50;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID50;
	}
}

static inline void hri_pmc_clear_PCSR1_PID50_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID50;
}

static inline void hri_pmc_set_PCSR1_PID51_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID51;
}

static inline bool hri_pmc_get_PCSR1_PID51_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID51) >> PMC_PCSR1_PID51_Pos;
}

static inline void hri_pmc_write_PCSR1_PID51_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID51;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID51;
	}
}

static inline void hri_pmc_clear_PCSR1_PID51_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID51;
}

static inline void hri_pmc_set_PCSR1_PID52_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID52;
}

static inline bool hri_pmc_get_PCSR1_PID52_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID52) >> PMC_PCSR1_PID52_Pos;
}

static inline void hri_pmc_write_PCSR1_PID52_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID52;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID52;
	}
}

static inline void hri_pmc_clear_PCSR1_PID52_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID52;
}

static inline void hri_pmc_set_PCSR1_PID56_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID56;
}

static inline bool hri_pmc_get_PCSR1_PID56_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID56) >> PMC_PCSR1_PID56_Pos;
}

static inline void hri_pmc_write_PCSR1_PID56_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID56;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID56;
	}
}

static inline void hri_pmc_clear_PCSR1_PID56_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID56;
}

static inline void hri_pmc_set_PCSR1_PID57_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID57;
}

static inline bool hri_pmc_get_PCSR1_PID57_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID57) >> PMC_PCSR1_PID57_Pos;
}

static inline void hri_pmc_write_PCSR1_PID57_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID57;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID57;
	}
}

static inline void hri_pmc_clear_PCSR1_PID57_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID57;
}

static inline void hri_pmc_set_PCSR1_PID58_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID58;
}

static inline bool hri_pmc_get_PCSR1_PID58_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID58) >> PMC_PCSR1_PID58_Pos;
}

static inline void hri_pmc_write_PCSR1_PID58_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID58;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID58;
	}
}

static inline void hri_pmc_clear_PCSR1_PID58_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID58;
}

static inline void hri_pmc_set_PCSR1_PID59_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID59;
}

static inline bool hri_pmc_get_PCSR1_PID59_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID59) >> PMC_PCSR1_PID59_Pos;
}

static inline void hri_pmc_write_PCSR1_PID59_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID59;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID59;
	}
}

static inline void hri_pmc_clear_PCSR1_PID59_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID59;
}

static inline void hri_pmc_set_PCSR1_PID60_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID60;
}

static inline bool hri_pmc_get_PCSR1_PID60_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_PCSR1 & PMC_PCSR1_PID60) >> PMC_PCSR1_PID60_Pos;
}

static inline void hri_pmc_write_PCSR1_PID60_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID60;
	} else {
		((Pmc *)hw)->PMC_PCER1 = PMC_PCSR1_PID60;
	}
}

static inline void hri_pmc_clear_PCSR1_PID60_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_PCDR1 = PMC_PCSR1_PID60;
}

static inline void hri_pmc_set_PCSR1_reg(const void *const hw, hri_pmc_pcsr1_reg_t mask)
{
	((Pmc *)hw)->PMC_PCER1 = mask;
}

static inline hri_pmc_pcsr1_reg_t hri_pmc_get_PCSR1_reg(const void *const hw, hri_pmc_pcsr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCSR1;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_pcsr1_reg_t hri_pmc_read_PCSR1_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_PCSR1;
}

static inline void hri_pmc_write_PCSR1_reg(const void *const hw, hri_pmc_pcsr1_reg_t data)
{
	((Pmc *)hw)->PMC_PCER1 = data;
	((Pmc *)hw)->PMC_PCDR1 = ~data;
}

static inline void hri_pmc_clear_PCSR1_reg(const void *const hw, hri_pmc_pcsr1_reg_t mask)
{
	((Pmc *)hw)->PMC_PCDR1 = mask;
}

static inline void hri_pmc_set_SLPWK_SR0_PID7_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID7;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID7_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID7) >> PMC_SLPWK_SR0_PID7_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID7;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID7;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID7_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID7;
}

static inline void hri_pmc_set_SLPWK_SR0_PID8_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID8;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID8_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID8) >> PMC_SLPWK_SR0_PID8_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID8;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID8;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID8_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID8;
}

static inline void hri_pmc_set_SLPWK_SR0_PID9_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID9;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID9_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID9) >> PMC_SLPWK_SR0_PID9_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID9;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID9;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID9_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID9;
}

static inline void hri_pmc_set_SLPWK_SR0_PID10_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID10;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID10_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID10) >> PMC_SLPWK_SR0_PID10_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID10;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID10;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID10_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID10;
}

static inline void hri_pmc_set_SLPWK_SR0_PID11_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID11;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID11_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID11) >> PMC_SLPWK_SR0_PID11_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID11;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID11;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID11_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID11;
}

static inline void hri_pmc_set_SLPWK_SR0_PID12_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID12;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID12_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID12) >> PMC_SLPWK_SR0_PID12_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID12;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID12;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID12_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID12;
}

static inline void hri_pmc_set_SLPWK_SR0_PID13_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID13;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID13_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID13) >> PMC_SLPWK_SR0_PID13_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID13;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID13;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID13_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID13;
}

static inline void hri_pmc_set_SLPWK_SR0_PID14_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID14;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID14_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID14) >> PMC_SLPWK_SR0_PID14_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID14;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID14;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID14_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID14;
}

static inline void hri_pmc_set_SLPWK_SR0_PID15_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID15;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID15_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID15) >> PMC_SLPWK_SR0_PID15_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID15;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID15;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID15_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID15;
}

static inline void hri_pmc_set_SLPWK_SR0_PID16_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID16;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID16_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID16) >> PMC_SLPWK_SR0_PID16_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID16;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID16;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID16_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID16;
}

static inline void hri_pmc_set_SLPWK_SR0_PID17_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID17;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID17_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID17) >> PMC_SLPWK_SR0_PID17_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID17;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID17;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID17_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID17;
}

static inline void hri_pmc_set_SLPWK_SR0_PID18_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID18;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID18_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID18) >> PMC_SLPWK_SR0_PID18_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID18;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID18;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID18_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID18;
}

static inline void hri_pmc_set_SLPWK_SR0_PID19_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID19;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID19_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID19) >> PMC_SLPWK_SR0_PID19_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID19;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID19;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID19_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID19;
}

static inline void hri_pmc_set_SLPWK_SR0_PID20_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID20;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID20_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID20) >> PMC_SLPWK_SR0_PID20_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID20;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID20;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID20_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID20;
}

static inline void hri_pmc_set_SLPWK_SR0_PID21_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID21;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID21_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID21) >> PMC_SLPWK_SR0_PID21_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID21;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID21;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID21_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID21;
}

static inline void hri_pmc_set_SLPWK_SR0_PID22_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID22;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID22_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID22) >> PMC_SLPWK_SR0_PID22_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID22;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID22;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID22_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID22;
}

static inline void hri_pmc_set_SLPWK_SR0_PID23_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID23;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID23_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID23) >> PMC_SLPWK_SR0_PID23_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID23;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID23;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID23_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID23;
}

static inline void hri_pmc_set_SLPWK_SR0_PID24_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID24;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID24_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID24) >> PMC_SLPWK_SR0_PID24_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID24;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID24;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID24_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID24;
}

static inline void hri_pmc_set_SLPWK_SR0_PID25_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID25;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID25_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID25) >> PMC_SLPWK_SR0_PID25_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID25;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID25;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID25_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID25;
}

static inline void hri_pmc_set_SLPWK_SR0_PID26_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID26;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID26_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID26) >> PMC_SLPWK_SR0_PID26_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID26;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID26;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID26_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID26;
}

static inline void hri_pmc_set_SLPWK_SR0_PID27_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID27;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID27_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID27) >> PMC_SLPWK_SR0_PID27_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID27;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID27;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID27_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID27;
}

static inline void hri_pmc_set_SLPWK_SR0_PID28_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID28;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID28_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID28) >> PMC_SLPWK_SR0_PID28_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID28;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID28;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID28_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID28;
}

static inline void hri_pmc_set_SLPWK_SR0_PID29_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID29;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID29_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID29) >> PMC_SLPWK_SR0_PID29_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID29;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID29;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID29_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID29;
}

static inline void hri_pmc_set_SLPWK_SR0_PID30_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID30;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID30_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID30) >> PMC_SLPWK_SR0_PID30_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID30;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID30;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID30_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID30;
}

static inline void hri_pmc_set_SLPWK_SR0_PID31_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID31;
}

static inline bool hri_pmc_get_SLPWK_SR0_PID31_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR0 & PMC_SLPWK_SR0_PID31) >> PMC_SLPWK_SR0_PID31_Pos;
}

static inline void hri_pmc_write_SLPWK_SR0_PID31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID31;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER0 = PMC_SLPWK_SR0_PID31;
	}
}

static inline void hri_pmc_clear_SLPWK_SR0_PID31_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = PMC_SLPWK_SR0_PID31;
}

static inline void hri_pmc_set_SLPWK_SR0_reg(const void *const hw, hri_pmc_slpwk_sr0_reg_t mask)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = mask;
}

static inline hri_pmc_slpwk_sr0_reg_t hri_pmc_get_SLPWK_SR0_reg(const void *const hw, hri_pmc_slpwk_sr0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_SLPWK_SR0;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_slpwk_sr0_reg_t hri_pmc_read_SLPWK_SR0_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_SLPWK_SR0;
}

static inline void hri_pmc_write_SLPWK_SR0_reg(const void *const hw, hri_pmc_slpwk_sr0_reg_t data)
{
	((Pmc *)hw)->PMC_SLPWK_ER0 = data;
	((Pmc *)hw)->PMC_SLPWK_DR0 = ~data;
}

static inline void hri_pmc_clear_SLPWK_SR0_reg(const void *const hw, hri_pmc_slpwk_sr0_reg_t mask)
{
	((Pmc *)hw)->PMC_SLPWK_DR0 = mask;
}

static inline void hri_pmc_set_SLPWK_SR1_PID32_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID32;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID32_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID32) >> PMC_SLPWK_SR1_PID32_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID32_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID32;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID32;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID32_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID32;
}

static inline void hri_pmc_set_SLPWK_SR1_PID33_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID33;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID33_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID33) >> PMC_SLPWK_SR1_PID33_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID33_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID33;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID33;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID33_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID33;
}

static inline void hri_pmc_set_SLPWK_SR1_PID34_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID34;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID34_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID34) >> PMC_SLPWK_SR1_PID34_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID34_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID34;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID34;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID34_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID34;
}

static inline void hri_pmc_set_SLPWK_SR1_PID35_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID35;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID35_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID35) >> PMC_SLPWK_SR1_PID35_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID35_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID35;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID35;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID35_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID35;
}

static inline void hri_pmc_set_SLPWK_SR1_PID37_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID37;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID37_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID37) >> PMC_SLPWK_SR1_PID37_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID37_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID37;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID37;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID37_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID37;
}

static inline void hri_pmc_set_SLPWK_SR1_PID39_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID39;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID39_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID39) >> PMC_SLPWK_SR1_PID39_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID39_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID39;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID39;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID39_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID39;
}

static inline void hri_pmc_set_SLPWK_SR1_PID40_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID40;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID40_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID40) >> PMC_SLPWK_SR1_PID40_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID40_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID40;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID40;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID40_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID40;
}

static inline void hri_pmc_set_SLPWK_SR1_PID41_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID41;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID41_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID41) >> PMC_SLPWK_SR1_PID41_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID41_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID41;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID41;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID41_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID41;
}

static inline void hri_pmc_set_SLPWK_SR1_PID42_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID42;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID42_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID42) >> PMC_SLPWK_SR1_PID42_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID42_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID42;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID42;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID42_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID42;
}

static inline void hri_pmc_set_SLPWK_SR1_PID43_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID43;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID43_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID43) >> PMC_SLPWK_SR1_PID43_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID43_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID43;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID43;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID43_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID43;
}

static inline void hri_pmc_set_SLPWK_SR1_PID44_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID44;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID44_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID44) >> PMC_SLPWK_SR1_PID44_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID44_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID44;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID44;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID44_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID44;
}

static inline void hri_pmc_set_SLPWK_SR1_PID45_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID45;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID45_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID45) >> PMC_SLPWK_SR1_PID45_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID45_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID45;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID45;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID45_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID45;
}

static inline void hri_pmc_set_SLPWK_SR1_PID46_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID46;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID46_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID46) >> PMC_SLPWK_SR1_PID46_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID46_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID46;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID46;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID46_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID46;
}

static inline void hri_pmc_set_SLPWK_SR1_PID47_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID47;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID47_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID47) >> PMC_SLPWK_SR1_PID47_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID47_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID47;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID47;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID47_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID47;
}

static inline void hri_pmc_set_SLPWK_SR1_PID48_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID48;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID48_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID48) >> PMC_SLPWK_SR1_PID48_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID48_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID48;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID48;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID48_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID48;
}

static inline void hri_pmc_set_SLPWK_SR1_PID49_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID49;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID49_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID49) >> PMC_SLPWK_SR1_PID49_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID49_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID49;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID49;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID49_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID49;
}

static inline void hri_pmc_set_SLPWK_SR1_PID50_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID50;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID50_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID50) >> PMC_SLPWK_SR1_PID50_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID50_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID50;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID50;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID50_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID50;
}

static inline void hri_pmc_set_SLPWK_SR1_PID51_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID51;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID51_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID51) >> PMC_SLPWK_SR1_PID51_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID51_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID51;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID51;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID51_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID51;
}

static inline void hri_pmc_set_SLPWK_SR1_PID52_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID52;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID52_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID52) >> PMC_SLPWK_SR1_PID52_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID52_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID52;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID52;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID52_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID52;
}

static inline void hri_pmc_set_SLPWK_SR1_PID56_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID56;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID56_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID56) >> PMC_SLPWK_SR1_PID56_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID56_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID56;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID56;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID56_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID56;
}

static inline void hri_pmc_set_SLPWK_SR1_PID57_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID57;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID57_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID57) >> PMC_SLPWK_SR1_PID57_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID57_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID57;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID57;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID57_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID57;
}

static inline void hri_pmc_set_SLPWK_SR1_PID58_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID58;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID58_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID58) >> PMC_SLPWK_SR1_PID58_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID58_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID58;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID58;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID58_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID58;
}

static inline void hri_pmc_set_SLPWK_SR1_PID59_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID59;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID59_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID59) >> PMC_SLPWK_SR1_PID59_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID59_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID59;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID59;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID59_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID59;
}

static inline void hri_pmc_set_SLPWK_SR1_PID60_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID60;
}

static inline bool hri_pmc_get_SLPWK_SR1_PID60_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_SR1 & PMC_SLPWK_SR1_PID60) >> PMC_SLPWK_SR1_PID60_Pos;
}

static inline void hri_pmc_write_SLPWK_SR1_PID60_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID60;
	} else {
		((Pmc *)hw)->PMC_SLPWK_ER1 = PMC_SLPWK_SR1_PID60;
	}
}

static inline void hri_pmc_clear_SLPWK_SR1_PID60_bit(const void *const hw)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = PMC_SLPWK_SR1_PID60;
}

static inline void hri_pmc_set_SLPWK_SR1_reg(const void *const hw, hri_pmc_slpwk_sr1_reg_t mask)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = mask;
}

static inline hri_pmc_slpwk_sr1_reg_t hri_pmc_get_SLPWK_SR1_reg(const void *const hw, hri_pmc_slpwk_sr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_SLPWK_SR1;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_slpwk_sr1_reg_t hri_pmc_read_SLPWK_SR1_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_SLPWK_SR1;
}

static inline void hri_pmc_write_SLPWK_SR1_reg(const void *const hw, hri_pmc_slpwk_sr1_reg_t data)
{
	((Pmc *)hw)->PMC_SLPWK_ER1 = data;
	((Pmc *)hw)->PMC_SLPWK_DR1 = ~data;
}

static inline void hri_pmc_clear_SLPWK_SR1_reg(const void *const hw, hri_pmc_slpwk_sr1_reg_t mask)
{
	((Pmc *)hw)->PMC_SLPWK_DR1 = mask;
}

static inline bool hri_pmc_get_SR_MOSCXTS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_MOSCXTS) > 0;
}

static inline bool hri_pmc_get_SR_LOCKA_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_LOCKA) > 0;
}

static inline bool hri_pmc_get_SR_MCKRDY_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_MCKRDY) > 0;
}

static inline bool hri_pmc_get_SR_LOCKU_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_LOCKU) > 0;
}

static inline bool hri_pmc_get_SR_OSCSELS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_OSCSELS) > 0;
}

static inline bool hri_pmc_get_SR_PCKRDY0_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_PCKRDY0) > 0;
}

static inline bool hri_pmc_get_SR_PCKRDY1_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_PCKRDY1) > 0;
}

static inline bool hri_pmc_get_SR_PCKRDY2_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_PCKRDY2) > 0;
}

static inline bool hri_pmc_get_SR_PCKRDY3_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_PCKRDY3) > 0;
}

static inline bool hri_pmc_get_SR_PCKRDY4_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_PCKRDY4) > 0;
}

static inline bool hri_pmc_get_SR_PCKRDY5_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_PCKRDY5) > 0;
}

static inline bool hri_pmc_get_SR_PCKRDY6_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_PCKRDY6) > 0;
}

static inline bool hri_pmc_get_SR_PCKRDY7_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_PCKRDY7) > 0;
}

static inline bool hri_pmc_get_SR_MOSCSELS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_MOSCSELS) > 0;
}

static inline bool hri_pmc_get_SR_MOSCRCS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_MOSCRCS) > 0;
}

static inline bool hri_pmc_get_SR_CFDEV_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_CFDEV) > 0;
}

static inline bool hri_pmc_get_SR_CFDS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_CFDS) > 0;
}

static inline bool hri_pmc_get_SR_FOS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_FOS) > 0;
}

static inline bool hri_pmc_get_SR_XT32KERR_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SR & PMC_SR_XT32KERR) > 0;
}

static inline hri_pmc_sr_reg_t hri_pmc_get_SR_reg(const void *const hw, hri_pmc_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_sr_reg_t hri_pmc_read_SR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_SR;
}

static inline bool hri_pmc_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_WPSR & PMC_WPSR_WPVS) > 0;
}

static inline hri_pmc_wpsr_reg_t hri_pmc_get_WPSR_WPVSRC_bf(const void *const hw, hri_pmc_wpsr_reg_t mask)
{
	return (((Pmc *)hw)->PMC_WPSR & PMC_WPSR_WPVSRC(mask)) >> PMC_WPSR_WPVSRC_Pos;
}

static inline hri_pmc_wpsr_reg_t hri_pmc_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Pmc *)hw)->PMC_WPSR & PMC_WPSR_WPVSRC_Msk) >> PMC_WPSR_WPVSRC_Pos;
}

static inline hri_pmc_wpsr_reg_t hri_pmc_get_WPSR_reg(const void *const hw, hri_pmc_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_wpsr_reg_t hri_pmc_read_WPSR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_WPSR;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID7_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID7) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID8_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID8) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID9_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID9) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID10_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID10) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID11_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID11) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID12_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID12) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID13_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID13) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID14_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID14) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID15_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID15) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID16_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID16) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID17_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID17) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID18_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID18) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID19_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID19) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID20_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID20) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID21_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID21) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID22_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID22) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID23_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID23) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID24_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID24) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID25_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID25) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID26_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID26) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID27_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID27) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID28_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID28) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID29_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID29) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID30_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID30) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR0_PID31_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR0 & PMC_SLPWK_ASR0_PID31) > 0;
}

static inline hri_pmc_slpwk_asr0_reg_t hri_pmc_get_SLPWK_ASR0_reg(const void *const hw, hri_pmc_slpwk_asr0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_SLPWK_ASR0;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_slpwk_asr0_reg_t hri_pmc_read_SLPWK_ASR0_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_SLPWK_ASR0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID32_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID32) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID33_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID33) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID34_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID34) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID35_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID35) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID37_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID37) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID39_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID39) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID40_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID40) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID41_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID41) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID42_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID42) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID43_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID43) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID44_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID44) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID45_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID45) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID46_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID46) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID47_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID47) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID48_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID48) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID49_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID49) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID50_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID50) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID51_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID51) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID52_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID52) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID56_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID56) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID57_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID57) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID58_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID58) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID59_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID59) > 0;
}

static inline bool hri_pmc_get_SLPWK_ASR1_PID60_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_ASR1 & PMC_SLPWK_ASR1_PID60) > 0;
}

static inline hri_pmc_slpwk_asr1_reg_t hri_pmc_get_SLPWK_ASR1_reg(const void *const hw, hri_pmc_slpwk_asr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_SLPWK_ASR1;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_slpwk_asr1_reg_t hri_pmc_read_SLPWK_ASR1_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_SLPWK_ASR1;
}

static inline bool hri_pmc_get_SLPWK_AIPR_AIP_bit(const void *const hw)
{
	return (((Pmc *)hw)->PMC_SLPWK_AIPR & PMC_SLPWK_AIPR_AIP) > 0;
}

static inline hri_pmc_slpwk_aipr_reg_t hri_pmc_get_SLPWK_AIPR_reg(const void *const hw, hri_pmc_slpwk_aipr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_SLPWK_AIPR;
	tmp &= mask;
	return tmp;
}

static inline hri_pmc_slpwk_aipr_reg_t hri_pmc_read_SLPWK_AIPR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_SLPWK_AIPR;
}

static inline void hri_pmc_set_CKGR_UCKR_UPLLEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR |= CKGR_UCKR_UPLLEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_UCKR_UPLLEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_UCKR;
	tmp = (tmp & CKGR_UCKR_UPLLEN) >> CKGR_UCKR_UPLLEN_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_UCKR_UPLLEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_UCKR;
	tmp &= ~CKGR_UCKR_UPLLEN;
	tmp |= value << CKGR_UCKR_UPLLEN_Pos;
	((Pmc *)hw)->CKGR_UCKR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_UCKR_UPLLEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR &= ~CKGR_UCKR_UPLLEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_UCKR_UPLLEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR ^= CKGR_UCKR_UPLLEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_UCKR_UPLLCOUNT_bf(const void *const hw, hri_pmc_ckgr_uckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR |= CKGR_UCKR_UPLLCOUNT(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_uckr_reg_t hri_pmc_get_CKGR_UCKR_UPLLCOUNT_bf(const void *const       hw,
                                                                         hri_pmc_ckgr_uckr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_UCKR;
	tmp = (tmp & CKGR_UCKR_UPLLCOUNT(mask)) >> CKGR_UCKR_UPLLCOUNT_Pos;
	return tmp;
}

static inline void hri_pmc_write_CKGR_UCKR_UPLLCOUNT_bf(const void *const hw, hri_pmc_ckgr_uckr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_UCKR;
	tmp &= ~CKGR_UCKR_UPLLCOUNT_Msk;
	tmp |= CKGR_UCKR_UPLLCOUNT(data);
	((Pmc *)hw)->CKGR_UCKR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_UCKR_UPLLCOUNT_bf(const void *const hw, hri_pmc_ckgr_uckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR &= ~CKGR_UCKR_UPLLCOUNT(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_UCKR_UPLLCOUNT_bf(const void *const hw, hri_pmc_ckgr_uckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR ^= CKGR_UCKR_UPLLCOUNT(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_uckr_reg_t hri_pmc_read_CKGR_UCKR_UPLLCOUNT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_UCKR;
	tmp = (tmp & CKGR_UCKR_UPLLCOUNT_Msk) >> CKGR_UCKR_UPLLCOUNT_Pos;
	return tmp;
}

static inline void hri_pmc_set_CKGR_UCKR_reg(const void *const hw, hri_pmc_ckgr_uckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_uckr_reg_t hri_pmc_get_CKGR_UCKR_reg(const void *const hw, hri_pmc_ckgr_uckr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_UCKR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_CKGR_UCKR_reg(const void *const hw, hri_pmc_ckgr_uckr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_UCKR_reg(const void *const hw, hri_pmc_ckgr_uckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_UCKR_reg(const void *const hw, hri_pmc_ckgr_uckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_UCKR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_uckr_reg_t hri_pmc_read_CKGR_UCKR_reg(const void *const hw)
{
	return ((Pmc *)hw)->CKGR_UCKR;
}

static inline void hri_pmc_set_CKGR_MOR_MOSCXTEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_MOSCXTEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MOR_MOSCXTEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_MOSCXTEN) >> CKGR_MOR_MOSCXTEN_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MOR_MOSCXTEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_MOSCXTEN;
	tmp |= value << CKGR_MOR_MOSCXTEN_Pos;
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_MOSCXTEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_MOSCXTEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_MOSCXTEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_MOSCXTEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MOR_MOSCXTBY_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_MOSCXTBY;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MOR_MOSCXTBY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_MOSCXTBY) >> CKGR_MOR_MOSCXTBY_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MOR_MOSCXTBY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_MOSCXTBY;
	tmp |= value << CKGR_MOR_MOSCXTBY_Pos;
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_MOSCXTBY_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_MOSCXTBY;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_MOSCXTBY_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_MOSCXTBY;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MOR_WAITMODE_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_WAITMODE;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MOR_WAITMODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_WAITMODE) >> CKGR_MOR_WAITMODE_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MOR_WAITMODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_WAITMODE;
	tmp |= value << CKGR_MOR_WAITMODE_Pos;
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_WAITMODE_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_WAITMODE;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_WAITMODE_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_WAITMODE;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MOR_MOSCRCEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_MOSCRCEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MOR_MOSCRCEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_MOSCRCEN) >> CKGR_MOR_MOSCRCEN_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MOR_MOSCRCEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_MOSCRCEN;
	tmp |= value << CKGR_MOR_MOSCRCEN_Pos;
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_MOSCRCEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_MOSCRCEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_MOSCRCEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_MOSCRCEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MOR_MOSCSEL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_MOSCSEL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MOR_MOSCSEL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_MOSCSEL) >> CKGR_MOR_MOSCSEL_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MOR_MOSCSEL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_MOSCSEL;
	tmp |= value << CKGR_MOR_MOSCSEL_Pos;
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_MOSCSEL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_MOSCSEL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_MOSCSEL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_MOSCSEL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MOR_CFDEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_CFDEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MOR_CFDEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_CFDEN) >> CKGR_MOR_CFDEN_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MOR_CFDEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_CFDEN;
	tmp |= value << CKGR_MOR_CFDEN_Pos;
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_CFDEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_CFDEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_CFDEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_CFDEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MOR_XT32KFME_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_XT32KFME;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MOR_XT32KFME_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_XT32KFME) >> CKGR_MOR_XT32KFME_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MOR_XT32KFME_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_XT32KFME;
	tmp |= value << CKGR_MOR_XT32KFME_Pos;
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_XT32KFME_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_XT32KFME;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_XT32KFME_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_XT32KFME;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MOR_MOSCRCF_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_MOSCRCF(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mor_reg_t hri_pmc_get_CKGR_MOR_MOSCRCF_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_MOSCRCF(mask)) >> CKGR_MOR_MOSCRCF_Pos;
	return tmp;
}

static inline void hri_pmc_write_CKGR_MOR_MOSCRCF_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_MOSCRCF_Msk;
	tmp |= CKGR_MOR_MOSCRCF(data);
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_MOSCRCF_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_MOSCRCF(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_MOSCRCF_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_MOSCRCF(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mor_reg_t hri_pmc_read_CKGR_MOR_MOSCRCF_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_MOSCRCF_Msk) >> CKGR_MOR_MOSCRCF_Pos;
	return tmp;
}

static inline void hri_pmc_set_CKGR_MOR_MOSCXTST_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_MOSCXTST(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mor_reg_t hri_pmc_get_CKGR_MOR_MOSCXTST_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_MOSCXTST(mask)) >> CKGR_MOR_MOSCXTST_Pos;
	return tmp;
}

static inline void hri_pmc_write_CKGR_MOR_MOSCXTST_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_MOSCXTST_Msk;
	tmp |= CKGR_MOR_MOSCXTST(data);
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_MOSCXTST_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_MOSCXTST(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_MOSCXTST_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_MOSCXTST(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mor_reg_t hri_pmc_read_CKGR_MOR_MOSCXTST_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_MOSCXTST_Msk) >> CKGR_MOR_MOSCXTST_Pos;
	return tmp;
}

static inline void hri_pmc_set_CKGR_MOR_KEY_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= CKGR_MOR_KEY(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mor_reg_t hri_pmc_get_CKGR_MOR_KEY_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_KEY(mask)) >> CKGR_MOR_KEY_Pos;
	return tmp;
}

static inline void hri_pmc_write_CKGR_MOR_KEY_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= ~CKGR_MOR_KEY_Msk;
	tmp |= CKGR_MOR_KEY(data);
	((Pmc *)hw)->CKGR_MOR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_KEY_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~CKGR_MOR_KEY(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_KEY_bf(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= CKGR_MOR_KEY(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mor_reg_t hri_pmc_read_CKGR_MOR_KEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp = (tmp & CKGR_MOR_KEY_Msk) >> CKGR_MOR_KEY_Pos;
	return tmp;
}

static inline void hri_pmc_set_CKGR_MOR_reg(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mor_reg_t hri_pmc_get_CKGR_MOR_reg(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MOR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_CKGR_MOR_reg(const void *const hw, hri_pmc_ckgr_mor_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MOR_reg(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MOR_reg(const void *const hw, hri_pmc_ckgr_mor_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MOR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mor_reg_t hri_pmc_read_CKGR_MOR_reg(const void *const hw)
{
	return ((Pmc *)hw)->CKGR_MOR;
}

static inline void hri_pmc_set_CKGR_MCFR_MAINFRDY_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR |= CKGR_MCFR_MAINFRDY;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MCFR_MAINFRDY_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp = (tmp & CKGR_MCFR_MAINFRDY) >> CKGR_MCFR_MAINFRDY_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MCFR_MAINFRDY_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp &= ~CKGR_MCFR_MAINFRDY;
	tmp |= value << CKGR_MCFR_MAINFRDY_Pos;
	((Pmc *)hw)->CKGR_MCFR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MCFR_MAINFRDY_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR &= ~CKGR_MCFR_MAINFRDY;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MCFR_MAINFRDY_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR ^= CKGR_MCFR_MAINFRDY;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MCFR_RCMEAS_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR |= CKGR_MCFR_RCMEAS;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MCFR_RCMEAS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp = (tmp & CKGR_MCFR_RCMEAS) >> CKGR_MCFR_RCMEAS_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MCFR_RCMEAS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp &= ~CKGR_MCFR_RCMEAS;
	tmp |= value << CKGR_MCFR_RCMEAS_Pos;
	((Pmc *)hw)->CKGR_MCFR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MCFR_RCMEAS_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR &= ~CKGR_MCFR_RCMEAS;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MCFR_RCMEAS_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR ^= CKGR_MCFR_RCMEAS;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MCFR_CCSS_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR |= CKGR_MCFR_CCSS;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_MCFR_CCSS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp = (tmp & CKGR_MCFR_CCSS) >> CKGR_MCFR_CCSS_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_MCFR_CCSS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp &= ~CKGR_MCFR_CCSS;
	tmp |= value << CKGR_MCFR_CCSS_Pos;
	((Pmc *)hw)->CKGR_MCFR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MCFR_CCSS_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR &= ~CKGR_MCFR_CCSS;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MCFR_CCSS_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR ^= CKGR_MCFR_CCSS;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_MCFR_MAINF_bf(const void *const hw, hri_pmc_ckgr_mcfr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR |= CKGR_MCFR_MAINF(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mcfr_reg_t hri_pmc_get_CKGR_MCFR_MAINF_bf(const void *const hw, hri_pmc_ckgr_mcfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp = (tmp & CKGR_MCFR_MAINF(mask)) >> CKGR_MCFR_MAINF_Pos;
	return tmp;
}

static inline void hri_pmc_write_CKGR_MCFR_MAINF_bf(const void *const hw, hri_pmc_ckgr_mcfr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp &= ~CKGR_MCFR_MAINF_Msk;
	tmp |= CKGR_MCFR_MAINF(data);
	((Pmc *)hw)->CKGR_MCFR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MCFR_MAINF_bf(const void *const hw, hri_pmc_ckgr_mcfr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR &= ~CKGR_MCFR_MAINF(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MCFR_MAINF_bf(const void *const hw, hri_pmc_ckgr_mcfr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR ^= CKGR_MCFR_MAINF(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mcfr_reg_t hri_pmc_read_CKGR_MCFR_MAINF_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp = (tmp & CKGR_MCFR_MAINF_Msk) >> CKGR_MCFR_MAINF_Pos;
	return tmp;
}

static inline void hri_pmc_set_CKGR_MCFR_reg(const void *const hw, hri_pmc_ckgr_mcfr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mcfr_reg_t hri_pmc_get_CKGR_MCFR_reg(const void *const hw, hri_pmc_ckgr_mcfr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_MCFR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_CKGR_MCFR_reg(const void *const hw, hri_pmc_ckgr_mcfr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_MCFR_reg(const void *const hw, hri_pmc_ckgr_mcfr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_MCFR_reg(const void *const hw, hri_pmc_ckgr_mcfr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_MCFR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_mcfr_reg_t hri_pmc_read_CKGR_MCFR_reg(const void *const hw)
{
	return ((Pmc *)hw)->CKGR_MCFR;
}

static inline void hri_pmc_set_CKGR_PLLAR_ONE_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR |= CKGR_PLLAR_ONE;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_CKGR_PLLAR_ONE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp = (tmp & CKGR_PLLAR_ONE) >> CKGR_PLLAR_ONE_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_CKGR_PLLAR_ONE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp &= ~CKGR_PLLAR_ONE;
	tmp |= value << CKGR_PLLAR_ONE_Pos;
	((Pmc *)hw)->CKGR_PLLAR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_PLLAR_ONE_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR &= ~CKGR_PLLAR_ONE;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_PLLAR_ONE_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR ^= CKGR_PLLAR_ONE;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_CKGR_PLLAR_DIVA_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR |= CKGR_PLLAR_DIVA(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_pllar_reg_t hri_pmc_get_CKGR_PLLAR_DIVA_bf(const void *const        hw,
                                                                      hri_pmc_ckgr_pllar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp = (tmp & CKGR_PLLAR_DIVA(mask)) >> CKGR_PLLAR_DIVA_Pos;
	return tmp;
}

static inline void hri_pmc_write_CKGR_PLLAR_DIVA_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp &= ~CKGR_PLLAR_DIVA_Msk;
	tmp |= CKGR_PLLAR_DIVA(data);
	((Pmc *)hw)->CKGR_PLLAR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_PLLAR_DIVA_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR &= ~CKGR_PLLAR_DIVA(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_PLLAR_DIVA_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR ^= CKGR_PLLAR_DIVA(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_pllar_reg_t hri_pmc_read_CKGR_PLLAR_DIVA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp = (tmp & CKGR_PLLAR_DIVA_Msk) >> CKGR_PLLAR_DIVA_Pos;
	return tmp;
}

static inline void hri_pmc_set_CKGR_PLLAR_PLLACOUNT_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR |= CKGR_PLLAR_PLLACOUNT(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_pllar_reg_t hri_pmc_get_CKGR_PLLAR_PLLACOUNT_bf(const void *const        hw,
                                                                           hri_pmc_ckgr_pllar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp = (tmp & CKGR_PLLAR_PLLACOUNT(mask)) >> CKGR_PLLAR_PLLACOUNT_Pos;
	return tmp;
}

static inline void hri_pmc_write_CKGR_PLLAR_PLLACOUNT_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp &= ~CKGR_PLLAR_PLLACOUNT_Msk;
	tmp |= CKGR_PLLAR_PLLACOUNT(data);
	((Pmc *)hw)->CKGR_PLLAR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_PLLAR_PLLACOUNT_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR &= ~CKGR_PLLAR_PLLACOUNT(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_PLLAR_PLLACOUNT_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR ^= CKGR_PLLAR_PLLACOUNT(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_pllar_reg_t hri_pmc_read_CKGR_PLLAR_PLLACOUNT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp = (tmp & CKGR_PLLAR_PLLACOUNT_Msk) >> CKGR_PLLAR_PLLACOUNT_Pos;
	return tmp;
}

static inline void hri_pmc_set_CKGR_PLLAR_MULA_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR |= CKGR_PLLAR_MULA(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_pllar_reg_t hri_pmc_get_CKGR_PLLAR_MULA_bf(const void *const        hw,
                                                                      hri_pmc_ckgr_pllar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp = (tmp & CKGR_PLLAR_MULA(mask)) >> CKGR_PLLAR_MULA_Pos;
	return tmp;
}

static inline void hri_pmc_write_CKGR_PLLAR_MULA_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp &= ~CKGR_PLLAR_MULA_Msk;
	tmp |= CKGR_PLLAR_MULA(data);
	((Pmc *)hw)->CKGR_PLLAR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_PLLAR_MULA_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR &= ~CKGR_PLLAR_MULA(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_PLLAR_MULA_bf(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR ^= CKGR_PLLAR_MULA(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_pllar_reg_t hri_pmc_read_CKGR_PLLAR_MULA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp = (tmp & CKGR_PLLAR_MULA_Msk) >> CKGR_PLLAR_MULA_Pos;
	return tmp;
}

static inline void hri_pmc_set_CKGR_PLLAR_reg(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_pllar_reg_t hri_pmc_get_CKGR_PLLAR_reg(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->CKGR_PLLAR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_CKGR_PLLAR_reg(const void *const hw, hri_pmc_ckgr_pllar_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_CKGR_PLLAR_reg(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_CKGR_PLLAR_reg(const void *const hw, hri_pmc_ckgr_pllar_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->CKGR_PLLAR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ckgr_pllar_reg_t hri_pmc_read_CKGR_PLLAR_reg(const void *const hw)
{
	return ((Pmc *)hw)->CKGR_PLLAR;
}

static inline void hri_pmc_set_MCKR_UPLLDIV2_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR |= PMC_MCKR_UPLLDIV2;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_MCKR_UPLLDIV2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp = (tmp & PMC_MCKR_UPLLDIV2) >> PMC_MCKR_UPLLDIV2_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_MCKR_UPLLDIV2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp &= ~PMC_MCKR_UPLLDIV2;
	tmp |= value << PMC_MCKR_UPLLDIV2_Pos;
	((Pmc *)hw)->PMC_MCKR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_MCKR_UPLLDIV2_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR &= ~PMC_MCKR_UPLLDIV2;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_MCKR_UPLLDIV2_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR ^= PMC_MCKR_UPLLDIV2;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_MCKR_CSS_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR |= PMC_MCKR_CSS(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_mckr_reg_t hri_pmc_get_MCKR_CSS_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp = (tmp & PMC_MCKR_CSS(mask)) >> PMC_MCKR_CSS_Pos;
	return tmp;
}

static inline void hri_pmc_write_MCKR_CSS_bf(const void *const hw, hri_pmc_mckr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp &= ~PMC_MCKR_CSS_Msk;
	tmp |= PMC_MCKR_CSS(data);
	((Pmc *)hw)->PMC_MCKR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_MCKR_CSS_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR &= ~PMC_MCKR_CSS(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_MCKR_CSS_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR ^= PMC_MCKR_CSS(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_mckr_reg_t hri_pmc_read_MCKR_CSS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp = (tmp & PMC_MCKR_CSS_Msk) >> PMC_MCKR_CSS_Pos;
	return tmp;
}

static inline void hri_pmc_set_MCKR_PRES_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR |= PMC_MCKR_PRES(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_mckr_reg_t hri_pmc_get_MCKR_PRES_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp = (tmp & PMC_MCKR_PRES(mask)) >> PMC_MCKR_PRES_Pos;
	return tmp;
}

static inline void hri_pmc_write_MCKR_PRES_bf(const void *const hw, hri_pmc_mckr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp &= ~PMC_MCKR_PRES_Msk;
	tmp |= PMC_MCKR_PRES(data);
	((Pmc *)hw)->PMC_MCKR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_MCKR_PRES_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR &= ~PMC_MCKR_PRES(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_MCKR_PRES_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR ^= PMC_MCKR_PRES(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_mckr_reg_t hri_pmc_read_MCKR_PRES_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp = (tmp & PMC_MCKR_PRES_Msk) >> PMC_MCKR_PRES_Pos;
	return tmp;
}

static inline void hri_pmc_set_MCKR_MDIV_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR |= PMC_MCKR_MDIV(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_mckr_reg_t hri_pmc_get_MCKR_MDIV_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp = (tmp & PMC_MCKR_MDIV(mask)) >> PMC_MCKR_MDIV_Pos;
	return tmp;
}

static inline void hri_pmc_write_MCKR_MDIV_bf(const void *const hw, hri_pmc_mckr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp &= ~PMC_MCKR_MDIV_Msk;
	tmp |= PMC_MCKR_MDIV(data);
	((Pmc *)hw)->PMC_MCKR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_MCKR_MDIV_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR &= ~PMC_MCKR_MDIV(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_MCKR_MDIV_bf(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR ^= PMC_MCKR_MDIV(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_mckr_reg_t hri_pmc_read_MCKR_MDIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp = (tmp & PMC_MCKR_MDIV_Msk) >> PMC_MCKR_MDIV_Pos;
	return tmp;
}

static inline void hri_pmc_set_MCKR_reg(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_mckr_reg_t hri_pmc_get_MCKR_reg(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_MCKR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_MCKR_reg(const void *const hw, hri_pmc_mckr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_MCKR_reg(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_MCKR_reg(const void *const hw, hri_pmc_mckr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_MCKR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_mckr_reg_t hri_pmc_read_MCKR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_MCKR;
}

static inline void hri_pmc_set_USB_USBS_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB |= PMC_USB_USBS;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_USB_USBS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_USB;
	tmp = (tmp & PMC_USB_USBS) >> PMC_USB_USBS_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_USB_USBS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_USB;
	tmp &= ~PMC_USB_USBS;
	tmp |= value << PMC_USB_USBS_Pos;
	((Pmc *)hw)->PMC_USB = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_USB_USBS_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB &= ~PMC_USB_USBS;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_USB_USBS_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB ^= PMC_USB_USBS;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_USB_USBDIV_bf(const void *const hw, hri_pmc_usb_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB |= PMC_USB_USBDIV(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_usb_reg_t hri_pmc_get_USB_USBDIV_bf(const void *const hw, hri_pmc_usb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_USB;
	tmp = (tmp & PMC_USB_USBDIV(mask)) >> PMC_USB_USBDIV_Pos;
	return tmp;
}

static inline void hri_pmc_write_USB_USBDIV_bf(const void *const hw, hri_pmc_usb_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_USB;
	tmp &= ~PMC_USB_USBDIV_Msk;
	tmp |= PMC_USB_USBDIV(data);
	((Pmc *)hw)->PMC_USB = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_USB_USBDIV_bf(const void *const hw, hri_pmc_usb_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB &= ~PMC_USB_USBDIV(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_USB_USBDIV_bf(const void *const hw, hri_pmc_usb_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB ^= PMC_USB_USBDIV(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_usb_reg_t hri_pmc_read_USB_USBDIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_USB;
	tmp = (tmp & PMC_USB_USBDIV_Msk) >> PMC_USB_USBDIV_Pos;
	return tmp;
}

static inline void hri_pmc_set_USB_reg(const void *const hw, hri_pmc_usb_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_usb_reg_t hri_pmc_get_USB_reg(const void *const hw, hri_pmc_usb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_USB;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_USB_reg(const void *const hw, hri_pmc_usb_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_USB_reg(const void *const hw, hri_pmc_usb_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_USB_reg(const void *const hw, hri_pmc_usb_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_USB ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_usb_reg_t hri_pmc_read_USB_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_USB;
}

static inline void hri_pmc_set_PCK_CSS_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] |= PMC_PCK_CSS(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pck_reg_t hri_pmc_get_PCK_CSS_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCK[index];
	tmp = (tmp & PMC_PCK_CSS(mask)) >> PMC_PCK_CSS_Pos;
	return tmp;
}

static inline void hri_pmc_write_PCK_CSS_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_PCK[index];
	tmp &= ~PMC_PCK_CSS_Msk;
	tmp |= PMC_PCK_CSS(data);
	((Pmc *)hw)->PMC_PCK[index] = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCK_CSS_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] &= ~PMC_PCK_CSS(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCK_CSS_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] ^= PMC_PCK_CSS(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pck_reg_t hri_pmc_read_PCK_CSS_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCK[index];
	tmp = (tmp & PMC_PCK_CSS_Msk) >> PMC_PCK_CSS_Pos;
	return tmp;
}

static inline void hri_pmc_set_PCK_PRES_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] |= PMC_PCK_PRES(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pck_reg_t hri_pmc_get_PCK_PRES_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCK[index];
	tmp = (tmp & PMC_PCK_PRES(mask)) >> PMC_PCK_PRES_Pos;
	return tmp;
}

static inline void hri_pmc_write_PCK_PRES_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_PCK[index];
	tmp &= ~PMC_PCK_PRES_Msk;
	tmp |= PMC_PCK_PRES(data);
	((Pmc *)hw)->PMC_PCK[index] = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCK_PRES_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] &= ~PMC_PCK_PRES(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCK_PRES_bf(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] ^= PMC_PCK_PRES(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pck_reg_t hri_pmc_read_PCK_PRES_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCK[index];
	tmp = (tmp & PMC_PCK_PRES_Msk) >> PMC_PCK_PRES_Pos;
	return tmp;
}

static inline void hri_pmc_set_PCK_reg(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pck_reg_t hri_pmc_get_PCK_reg(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCK[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_PCK_reg(const void *const hw, uint8_t index, hri_pmc_pck_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCK_reg(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCK_reg(const void *const hw, uint8_t index, hri_pmc_pck_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCK[index] ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pck_reg_t hri_pmc_read_PCK_reg(const void *const hw, uint8_t index)
{
	return ((Pmc *)hw)->PMC_PCK[index];
}

static inline void hri_pmc_set_FSMR_FSTT0_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT0;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT0) >> PMC_FSMR_FSTT0_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT0;
	tmp |= value << PMC_FSMR_FSTT0_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT0_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT0;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT0_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT0;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT1_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT1;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT1) >> PMC_FSMR_FSTT1_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT1;
	tmp |= value << PMC_FSMR_FSTT1_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT1_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT1;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT1_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT1;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT2_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT2;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT2) >> PMC_FSMR_FSTT2_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT2;
	tmp |= value << PMC_FSMR_FSTT2_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT2_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT2;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT2_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT2;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT3_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT3;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT3) >> PMC_FSMR_FSTT3_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT3;
	tmp |= value << PMC_FSMR_FSTT3_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT3_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT3;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT3_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT3;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT4_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT4;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT4) >> PMC_FSMR_FSTT4_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT4;
	tmp |= value << PMC_FSMR_FSTT4_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT4_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT4;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT4_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT4;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT5_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT5;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT5) >> PMC_FSMR_FSTT5_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT5;
	tmp |= value << PMC_FSMR_FSTT5_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT5_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT5;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT5_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT5;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT6_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT6;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT6) >> PMC_FSMR_FSTT6_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT6;
	tmp |= value << PMC_FSMR_FSTT6_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT6_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT6;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT6_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT6;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT7_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT7;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT7) >> PMC_FSMR_FSTT7_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT7;
	tmp |= value << PMC_FSMR_FSTT7_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT7_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT7;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT7_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT7;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT8_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT8;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT8) >> PMC_FSMR_FSTT8_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT8;
	tmp |= value << PMC_FSMR_FSTT8_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT8_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT8;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT8_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT8;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT9_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT9;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT9) >> PMC_FSMR_FSTT9_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT9;
	tmp |= value << PMC_FSMR_FSTT9_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT9_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT9;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT9_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT9;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT10_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT10;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT10) >> PMC_FSMR_FSTT10_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT10;
	tmp |= value << PMC_FSMR_FSTT10_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT10_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT10;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT10_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT10;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT11_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT11;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT11) >> PMC_FSMR_FSTT11_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT11;
	tmp |= value << PMC_FSMR_FSTT11_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT11_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT11;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT11_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT11;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT12_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT12;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT12) >> PMC_FSMR_FSTT12_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT12;
	tmp |= value << PMC_FSMR_FSTT12_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT12_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT12;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT12_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT12;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT13_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT13;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT13) >> PMC_FSMR_FSTT13_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT13;
	tmp |= value << PMC_FSMR_FSTT13_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT13_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT13;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT13_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT13;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT14_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT14;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT14) >> PMC_FSMR_FSTT14_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT14;
	tmp |= value << PMC_FSMR_FSTT14_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT14_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT14;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT14_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT14;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FSTT15_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FSTT15;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FSTT15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FSTT15) >> PMC_FSMR_FSTT15_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FSTT15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FSTT15;
	tmp |= value << PMC_FSMR_FSTT15_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FSTT15_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FSTT15;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FSTT15_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FSTT15;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_RTTAL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_RTTAL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_RTTAL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_RTTAL) >> PMC_FSMR_RTTAL_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_RTTAL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_RTTAL;
	tmp |= value << PMC_FSMR_RTTAL_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_RTTAL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_RTTAL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_RTTAL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_RTTAL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_RTCAL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_RTCAL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_RTCAL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_RTCAL) >> PMC_FSMR_RTCAL_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_RTCAL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_RTCAL;
	tmp |= value << PMC_FSMR_RTCAL_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_RTCAL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_RTCAL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_RTCAL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_RTCAL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_USBAL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_USBAL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_USBAL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_USBAL) >> PMC_FSMR_USBAL_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_USBAL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_USBAL;
	tmp |= value << PMC_FSMR_USBAL_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_USBAL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_USBAL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_USBAL_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_USBAL;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_LPM_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_LPM;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_LPM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_LPM) >> PMC_FSMR_LPM_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_LPM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_LPM;
	tmp |= value << PMC_FSMR_LPM_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_LPM_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_LPM;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_LPM_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_LPM;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FFLPM_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FFLPM;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSMR_FFLPM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FFLPM) >> PMC_FSMR_FFLPM_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSMR_FFLPM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FFLPM;
	tmp |= value << PMC_FSMR_FFLPM_Pos;
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FFLPM_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FFLPM;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FFLPM_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FFLPM;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSMR_FLPM_bf(const void *const hw, hri_pmc_fsmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= PMC_FSMR_FLPM(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_fsmr_reg_t hri_pmc_get_FSMR_FLPM_bf(const void *const hw, hri_pmc_fsmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FLPM(mask)) >> PMC_FSMR_FLPM_Pos;
	return tmp;
}

static inline void hri_pmc_write_FSMR_FLPM_bf(const void *const hw, hri_pmc_fsmr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= ~PMC_FSMR_FLPM_Msk;
	tmp |= PMC_FSMR_FLPM(data);
	((Pmc *)hw)->PMC_FSMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_FLPM_bf(const void *const hw, hri_pmc_fsmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~PMC_FSMR_FLPM(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_FLPM_bf(const void *const hw, hri_pmc_fsmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= PMC_FSMR_FLPM(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_fsmr_reg_t hri_pmc_read_FSMR_FLPM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp = (tmp & PMC_FSMR_FLPM_Msk) >> PMC_FSMR_FLPM_Pos;
	return tmp;
}

static inline void hri_pmc_set_FSMR_reg(const void *const hw, hri_pmc_fsmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_fsmr_reg_t hri_pmc_get_FSMR_reg(const void *const hw, hri_pmc_fsmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_FSMR_reg(const void *const hw, hri_pmc_fsmr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSMR_reg(const void *const hw, hri_pmc_fsmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSMR_reg(const void *const hw, hri_pmc_fsmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSMR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_fsmr_reg_t hri_pmc_read_FSMR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_FSMR;
}

static inline void hri_pmc_set_FSPR_FSTP0_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP0;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP0) >> PMC_FSPR_FSTP0_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP0;
	tmp |= value << PMC_FSPR_FSTP0_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP0_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP0;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP0_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP0;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP1_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP1;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP1) >> PMC_FSPR_FSTP1_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP1;
	tmp |= value << PMC_FSPR_FSTP1_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP1_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP1;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP1_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP1;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP2_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP2;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP2) >> PMC_FSPR_FSTP2_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP2;
	tmp |= value << PMC_FSPR_FSTP2_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP2_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP2;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP2_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP2;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP3_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP3;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP3) >> PMC_FSPR_FSTP3_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP3;
	tmp |= value << PMC_FSPR_FSTP3_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP3_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP3;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP3_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP3;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP4_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP4;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP4) >> PMC_FSPR_FSTP4_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP4;
	tmp |= value << PMC_FSPR_FSTP4_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP4_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP4;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP4_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP4;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP5_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP5;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP5) >> PMC_FSPR_FSTP5_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP5;
	tmp |= value << PMC_FSPR_FSTP5_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP5_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP5;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP5_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP5;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP6_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP6;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP6) >> PMC_FSPR_FSTP6_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP6;
	tmp |= value << PMC_FSPR_FSTP6_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP6_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP6;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP6_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP6;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP7_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP7;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP7) >> PMC_FSPR_FSTP7_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP7;
	tmp |= value << PMC_FSPR_FSTP7_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP7_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP7;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP7_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP7;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP8_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP8;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP8) >> PMC_FSPR_FSTP8_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP8;
	tmp |= value << PMC_FSPR_FSTP8_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP8_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP8;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP8_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP8;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP9_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP9;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP9) >> PMC_FSPR_FSTP9_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP9;
	tmp |= value << PMC_FSPR_FSTP9_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP9_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP9;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP9_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP9;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP10_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP10;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP10) >> PMC_FSPR_FSTP10_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP10;
	tmp |= value << PMC_FSPR_FSTP10_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP10_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP10;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP10_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP10;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP11_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP11;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP11) >> PMC_FSPR_FSTP11_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP11;
	tmp |= value << PMC_FSPR_FSTP11_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP11_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP11;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP11_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP11;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP12_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP12;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP12) >> PMC_FSPR_FSTP12_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP12;
	tmp |= value << PMC_FSPR_FSTP12_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP12_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP12;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP12_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP12;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP13_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP13;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP13) >> PMC_FSPR_FSTP13_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP13;
	tmp |= value << PMC_FSPR_FSTP13_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP13_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP13;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP13_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP13;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP14_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP14;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP14) >> PMC_FSPR_FSTP14_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP14;
	tmp |= value << PMC_FSPR_FSTP14_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP14_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP14;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP14_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP14;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_FSTP15_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= PMC_FSPR_FSTP15;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_FSPR_FSTP15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp = (tmp & PMC_FSPR_FSTP15) >> PMC_FSPR_FSTP15_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_FSPR_FSTP15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= ~PMC_FSPR_FSTP15;
	tmp |= value << PMC_FSPR_FSTP15_Pos;
	((Pmc *)hw)->PMC_FSPR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_FSTP15_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~PMC_FSPR_FSTP15;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_FSTP15_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= PMC_FSPR_FSTP15;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_FSPR_reg(const void *const hw, hri_pmc_fspr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_fspr_reg_t hri_pmc_get_FSPR_reg(const void *const hw, hri_pmc_fspr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_FSPR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_FSPR_reg(const void *const hw, hri_pmc_fspr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_FSPR_reg(const void *const hw, hri_pmc_fspr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_FSPR_reg(const void *const hw, hri_pmc_fspr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FSPR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_fspr_reg_t hri_pmc_read_FSPR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_FSPR;
}

static inline void hri_pmc_set_WPMR_WPEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR |= PMC_WPMR_WPEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_WPMR;
	tmp = (tmp & PMC_WPMR_WPEN) >> PMC_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_WPMR;
	tmp &= ~PMC_WPMR_WPEN;
	tmp |= value << PMC_WPMR_WPEN_Pos;
	((Pmc *)hw)->PMC_WPMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_WPMR_WPEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR &= ~PMC_WPMR_WPEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_WPMR_WPEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR ^= PMC_WPMR_WPEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_WPMR_WPKEY_bf(const void *const hw, hri_pmc_wpmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR |= PMC_WPMR_WPKEY(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_wpmr_reg_t hri_pmc_get_WPMR_WPKEY_bf(const void *const hw, hri_pmc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_WPMR;
	tmp = (tmp & PMC_WPMR_WPKEY(mask)) >> PMC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_pmc_write_WPMR_WPKEY_bf(const void *const hw, hri_pmc_wpmr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_WPMR;
	tmp &= ~PMC_WPMR_WPKEY_Msk;
	tmp |= PMC_WPMR_WPKEY(data);
	((Pmc *)hw)->PMC_WPMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_WPMR_WPKEY_bf(const void *const hw, hri_pmc_wpmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR &= ~PMC_WPMR_WPKEY(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_WPMR_WPKEY_bf(const void *const hw, hri_pmc_wpmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR ^= PMC_WPMR_WPKEY(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_wpmr_reg_t hri_pmc_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_WPMR;
	tmp = (tmp & PMC_WPMR_WPKEY_Msk) >> PMC_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_pmc_set_WPMR_reg(const void *const hw, hri_pmc_wpmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_wpmr_reg_t hri_pmc_get_WPMR_reg(const void *const hw, hri_pmc_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_WPMR_reg(const void *const hw, hri_pmc_wpmr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_WPMR_reg(const void *const hw, hri_pmc_wpmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_WPMR_reg(const void *const hw, hri_pmc_wpmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_WPMR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_wpmr_reg_t hri_pmc_read_WPMR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_WPMR;
}

static inline void hri_pmc_set_PCR_CMD_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR |= PMC_PCR_CMD;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_PCR_CMD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp = (tmp & PMC_PCR_CMD) >> PMC_PCR_CMD_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_PCR_CMD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp &= ~PMC_PCR_CMD;
	tmp |= value << PMC_PCR_CMD_Pos;
	((Pmc *)hw)->PMC_PCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCR_CMD_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR &= ~PMC_PCR_CMD;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCR_CMD_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR ^= PMC_PCR_CMD;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_PCR_EN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR |= PMC_PCR_EN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_PCR_EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp = (tmp & PMC_PCR_EN) >> PMC_PCR_EN_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_PCR_EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp &= ~PMC_PCR_EN;
	tmp |= value << PMC_PCR_EN_Pos;
	((Pmc *)hw)->PMC_PCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCR_EN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR &= ~PMC_PCR_EN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCR_EN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR ^= PMC_PCR_EN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_PCR_GCLKEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR |= PMC_PCR_GCLKEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_PCR_GCLKEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp = (tmp & PMC_PCR_GCLKEN) >> PMC_PCR_GCLKEN_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_PCR_GCLKEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp &= ~PMC_PCR_GCLKEN;
	tmp |= value << PMC_PCR_GCLKEN_Pos;
	((Pmc *)hw)->PMC_PCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCR_GCLKEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR &= ~PMC_PCR_GCLKEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCR_GCLKEN_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR ^= PMC_PCR_GCLKEN;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_PCR_PID_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR |= PMC_PCR_PID(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pcr_reg_t hri_pmc_get_PCR_PID_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp = (tmp & PMC_PCR_PID(mask)) >> PMC_PCR_PID_Pos;
	return tmp;
}

static inline void hri_pmc_write_PCR_PID_bf(const void *const hw, hri_pmc_pcr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp &= ~PMC_PCR_PID_Msk;
	tmp |= PMC_PCR_PID(data);
	((Pmc *)hw)->PMC_PCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCR_PID_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR &= ~PMC_PCR_PID(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCR_PID_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR ^= PMC_PCR_PID(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pcr_reg_t hri_pmc_read_PCR_PID_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp = (tmp & PMC_PCR_PID_Msk) >> PMC_PCR_PID_Pos;
	return tmp;
}

static inline void hri_pmc_set_PCR_GCLKCSS_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR |= PMC_PCR_GCLKCSS(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pcr_reg_t hri_pmc_get_PCR_GCLKCSS_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp = (tmp & PMC_PCR_GCLKCSS(mask)) >> PMC_PCR_GCLKCSS_Pos;
	return tmp;
}

static inline void hri_pmc_write_PCR_GCLKCSS_bf(const void *const hw, hri_pmc_pcr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp &= ~PMC_PCR_GCLKCSS_Msk;
	tmp |= PMC_PCR_GCLKCSS(data);
	((Pmc *)hw)->PMC_PCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCR_GCLKCSS_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR &= ~PMC_PCR_GCLKCSS(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCR_GCLKCSS_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR ^= PMC_PCR_GCLKCSS(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pcr_reg_t hri_pmc_read_PCR_GCLKCSS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp = (tmp & PMC_PCR_GCLKCSS_Msk) >> PMC_PCR_GCLKCSS_Pos;
	return tmp;
}

static inline void hri_pmc_set_PCR_GCLKDIV_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR |= PMC_PCR_GCLKDIV(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pcr_reg_t hri_pmc_get_PCR_GCLKDIV_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp = (tmp & PMC_PCR_GCLKDIV(mask)) >> PMC_PCR_GCLKDIV_Pos;
	return tmp;
}

static inline void hri_pmc_write_PCR_GCLKDIV_bf(const void *const hw, hri_pmc_pcr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp &= ~PMC_PCR_GCLKDIV_Msk;
	tmp |= PMC_PCR_GCLKDIV(data);
	((Pmc *)hw)->PMC_PCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCR_GCLKDIV_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR &= ~PMC_PCR_GCLKDIV(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCR_GCLKDIV_bf(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR ^= PMC_PCR_GCLKDIV(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pcr_reg_t hri_pmc_read_PCR_GCLKDIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp = (tmp & PMC_PCR_GCLKDIV_Msk) >> PMC_PCR_GCLKDIV_Pos;
	return tmp;
}

static inline void hri_pmc_set_PCR_reg(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pcr_reg_t hri_pmc_get_PCR_reg(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_PCR_reg(const void *const hw, hri_pmc_pcr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PCR_reg(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PCR_reg(const void *const hw, hri_pmc_pcr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PCR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pcr_reg_t hri_pmc_read_PCR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_PCR;
}

static inline void hri_pmc_set_OCR_SEL4_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR |= PMC_OCR_SEL4;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_OCR_SEL4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp = (tmp & PMC_OCR_SEL4) >> PMC_OCR_SEL4_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_OCR_SEL4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp &= ~PMC_OCR_SEL4;
	tmp |= value << PMC_OCR_SEL4_Pos;
	((Pmc *)hw)->PMC_OCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_OCR_SEL4_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR &= ~PMC_OCR_SEL4;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_OCR_SEL4_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR ^= PMC_OCR_SEL4;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_OCR_SEL8_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR |= PMC_OCR_SEL8;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_OCR_SEL8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp = (tmp & PMC_OCR_SEL8) >> PMC_OCR_SEL8_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_OCR_SEL8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp &= ~PMC_OCR_SEL8;
	tmp |= value << PMC_OCR_SEL8_Pos;
	((Pmc *)hw)->PMC_OCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_OCR_SEL8_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR &= ~PMC_OCR_SEL8;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_OCR_SEL8_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR ^= PMC_OCR_SEL8;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_OCR_SEL12_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR |= PMC_OCR_SEL12;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pmc_get_OCR_SEL12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp = (tmp & PMC_OCR_SEL12) >> PMC_OCR_SEL12_Pos;
	return (bool)tmp;
}

static inline void hri_pmc_write_OCR_SEL12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp &= ~PMC_OCR_SEL12;
	tmp |= value << PMC_OCR_SEL12_Pos;
	((Pmc *)hw)->PMC_OCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_OCR_SEL12_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR &= ~PMC_OCR_SEL12;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_OCR_SEL12_bit(const void *const hw)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR ^= PMC_OCR_SEL12;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_set_OCR_CAL4_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR |= PMC_OCR_CAL4(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ocr_reg_t hri_pmc_get_OCR_CAL4_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp = (tmp & PMC_OCR_CAL4(mask)) >> PMC_OCR_CAL4_Pos;
	return tmp;
}

static inline void hri_pmc_write_OCR_CAL4_bf(const void *const hw, hri_pmc_ocr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp &= ~PMC_OCR_CAL4_Msk;
	tmp |= PMC_OCR_CAL4(data);
	((Pmc *)hw)->PMC_OCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_OCR_CAL4_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR &= ~PMC_OCR_CAL4(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_OCR_CAL4_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR ^= PMC_OCR_CAL4(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ocr_reg_t hri_pmc_read_OCR_CAL4_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp = (tmp & PMC_OCR_CAL4_Msk) >> PMC_OCR_CAL4_Pos;
	return tmp;
}

static inline void hri_pmc_set_OCR_CAL8_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR |= PMC_OCR_CAL8(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ocr_reg_t hri_pmc_get_OCR_CAL8_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp = (tmp & PMC_OCR_CAL8(mask)) >> PMC_OCR_CAL8_Pos;
	return tmp;
}

static inline void hri_pmc_write_OCR_CAL8_bf(const void *const hw, hri_pmc_ocr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp &= ~PMC_OCR_CAL8_Msk;
	tmp |= PMC_OCR_CAL8(data);
	((Pmc *)hw)->PMC_OCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_OCR_CAL8_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR &= ~PMC_OCR_CAL8(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_OCR_CAL8_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR ^= PMC_OCR_CAL8(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ocr_reg_t hri_pmc_read_OCR_CAL8_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp = (tmp & PMC_OCR_CAL8_Msk) >> PMC_OCR_CAL8_Pos;
	return tmp;
}

static inline void hri_pmc_set_OCR_CAL12_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR |= PMC_OCR_CAL12(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ocr_reg_t hri_pmc_get_OCR_CAL12_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp = (tmp & PMC_OCR_CAL12(mask)) >> PMC_OCR_CAL12_Pos;
	return tmp;
}

static inline void hri_pmc_write_OCR_CAL12_bf(const void *const hw, hri_pmc_ocr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp &= ~PMC_OCR_CAL12_Msk;
	tmp |= PMC_OCR_CAL12(data);
	((Pmc *)hw)->PMC_OCR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_OCR_CAL12_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR &= ~PMC_OCR_CAL12(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_OCR_CAL12_bf(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR ^= PMC_OCR_CAL12(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ocr_reg_t hri_pmc_read_OCR_CAL12_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp = (tmp & PMC_OCR_CAL12_Msk) >> PMC_OCR_CAL12_Pos;
	return tmp;
}

static inline void hri_pmc_set_OCR_reg(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ocr_reg_t hri_pmc_get_OCR_reg(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_OCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_OCR_reg(const void *const hw, hri_pmc_ocr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_OCR_reg(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_OCR_reg(const void *const hw, hri_pmc_ocr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_OCR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_ocr_reg_t hri_pmc_read_OCR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_OCR;
}

static inline void hri_pmc_set_PMMR_PLLA_MMAX_bf(const void *const hw, hri_pmc_pmmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PMMR |= PMC_PMMR_PLLA_MMAX(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pmmr_reg_t hri_pmc_get_PMMR_PLLA_MMAX_bf(const void *const hw, hri_pmc_pmmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PMMR;
	tmp = (tmp & PMC_PMMR_PLLA_MMAX(mask)) >> PMC_PMMR_PLLA_MMAX_Pos;
	return tmp;
}

static inline void hri_pmc_write_PMMR_PLLA_MMAX_bf(const void *const hw, hri_pmc_pmmr_reg_t data)
{
	uint32_t tmp;
	PMC_CRITICAL_SECTION_ENTER();
	tmp = ((Pmc *)hw)->PMC_PMMR;
	tmp &= ~PMC_PMMR_PLLA_MMAX_Msk;
	tmp |= PMC_PMMR_PLLA_MMAX(data);
	((Pmc *)hw)->PMC_PMMR = tmp;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PMMR_PLLA_MMAX_bf(const void *const hw, hri_pmc_pmmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PMMR &= ~PMC_PMMR_PLLA_MMAX(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PMMR_PLLA_MMAX_bf(const void *const hw, hri_pmc_pmmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PMMR ^= PMC_PMMR_PLLA_MMAX(mask);
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pmmr_reg_t hri_pmc_read_PMMR_PLLA_MMAX_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PMMR;
	tmp = (tmp & PMC_PMMR_PLLA_MMAX_Msk) >> PMC_PMMR_PLLA_MMAX_Pos;
	return tmp;
}

static inline void hri_pmc_set_PMMR_reg(const void *const hw, hri_pmc_pmmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PMMR |= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pmmr_reg_t hri_pmc_get_PMMR_reg(const void *const hw, hri_pmc_pmmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pmc *)hw)->PMC_PMMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pmc_write_PMMR_reg(const void *const hw, hri_pmc_pmmr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PMMR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_clear_PMMR_reg(const void *const hw, hri_pmc_pmmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PMMR &= ~mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pmc_toggle_PMMR_reg(const void *const hw, hri_pmc_pmmr_reg_t mask)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_PMMR ^= mask;
	PMC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pmc_pmmr_reg_t hri_pmc_read_PMMR_reg(const void *const hw)
{
	return ((Pmc *)hw)->PMC_PMMR;
}

static inline void hri_pmc_write_FOCR_reg(const void *const hw, hri_pmc_focr_reg_t data)
{
	PMC_CRITICAL_SECTION_ENTER();
	((Pmc *)hw)->PMC_FOCR = data;
	PMC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_PMC_E70B_H_INCLUDED */
#endif /* _SAME70_PMC_COMPONENT_ */
