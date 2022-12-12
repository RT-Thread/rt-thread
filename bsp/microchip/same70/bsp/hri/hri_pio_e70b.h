/**
 * \file
 *
 * \brief SAM PIO
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

#ifdef _SAME70_PIO_COMPONENT_
#ifndef _HRI_PIO_E70B_H_INCLUDED_
#define _HRI_PIO_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_PIO_CRITICAL_SECTIONS)
#define PIO_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define PIO_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define PIO_CRITICAL_SECTION_ENTER()
#define PIO_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_pio_abcdsr_reg_t;
typedef uint32_t hri_pio_aimmr_reg_t;
typedef uint32_t hri_pio_driver_reg_t;
typedef uint32_t hri_pio_elsr_reg_t;
typedef uint32_t hri_pio_frlhsr_reg_t;
typedef uint32_t hri_pio_ifscsr_reg_t;
typedef uint32_t hri_pio_ifsr_reg_t;
typedef uint32_t hri_pio_imr_reg_t;
typedef uint32_t hri_pio_isr_reg_t;
typedef uint32_t hri_pio_locksr_reg_t;
typedef uint32_t hri_pio_mdsr_reg_t;
typedef uint32_t hri_pio_odsr_reg_t;
typedef uint32_t hri_pio_osr_reg_t;
typedef uint32_t hri_pio_owsr_reg_t;
typedef uint32_t hri_pio_pcidr_reg_t;
typedef uint32_t hri_pio_pcier_reg_t;
typedef uint32_t hri_pio_pcimr_reg_t;
typedef uint32_t hri_pio_pcisr_reg_t;
typedef uint32_t hri_pio_pcmr_reg_t;
typedef uint32_t hri_pio_pcrhr_reg_t;
typedef uint32_t hri_pio_pdsr_reg_t;
typedef uint32_t hri_pio_ppdsr_reg_t;
typedef uint32_t hri_pio_psr_reg_t;
typedef uint32_t hri_pio_pusr_reg_t;
typedef uint32_t hri_pio_scdr_reg_t;
typedef uint32_t hri_pio_schmitt_reg_t;
typedef uint32_t hri_pio_wpmr_reg_t;
typedef uint32_t hri_pio_wpsr_reg_t;

static inline bool hri_pio_get_ISR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P0) >> PIO_ISR_P0_Pos;
}

static inline bool hri_pio_get_ISR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P1) >> PIO_ISR_P1_Pos;
}

static inline bool hri_pio_get_ISR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P2) >> PIO_ISR_P2_Pos;
}

static inline bool hri_pio_get_ISR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P3) >> PIO_ISR_P3_Pos;
}

static inline bool hri_pio_get_ISR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P4) >> PIO_ISR_P4_Pos;
}

static inline bool hri_pio_get_ISR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P5) >> PIO_ISR_P5_Pos;
}

static inline bool hri_pio_get_ISR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P6) >> PIO_ISR_P6_Pos;
}

static inline bool hri_pio_get_ISR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P7) >> PIO_ISR_P7_Pos;
}

static inline bool hri_pio_get_ISR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P8) >> PIO_ISR_P8_Pos;
}

static inline bool hri_pio_get_ISR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P9) >> PIO_ISR_P9_Pos;
}

static inline bool hri_pio_get_ISR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P10) >> PIO_ISR_P10_Pos;
}

static inline bool hri_pio_get_ISR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P11) >> PIO_ISR_P11_Pos;
}

static inline bool hri_pio_get_ISR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P12) >> PIO_ISR_P12_Pos;
}

static inline bool hri_pio_get_ISR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P13) >> PIO_ISR_P13_Pos;
}

static inline bool hri_pio_get_ISR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P14) >> PIO_ISR_P14_Pos;
}

static inline bool hri_pio_get_ISR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P15) >> PIO_ISR_P15_Pos;
}

static inline bool hri_pio_get_ISR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P16) >> PIO_ISR_P16_Pos;
}

static inline bool hri_pio_get_ISR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P17) >> PIO_ISR_P17_Pos;
}

static inline bool hri_pio_get_ISR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P18) >> PIO_ISR_P18_Pos;
}

static inline bool hri_pio_get_ISR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P19) >> PIO_ISR_P19_Pos;
}

static inline bool hri_pio_get_ISR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P20) >> PIO_ISR_P20_Pos;
}

static inline bool hri_pio_get_ISR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P21) >> PIO_ISR_P21_Pos;
}

static inline bool hri_pio_get_ISR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P22) >> PIO_ISR_P22_Pos;
}

static inline bool hri_pio_get_ISR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P23) >> PIO_ISR_P23_Pos;
}

static inline bool hri_pio_get_ISR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P24) >> PIO_ISR_P24_Pos;
}

static inline bool hri_pio_get_ISR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P25) >> PIO_ISR_P25_Pos;
}

static inline bool hri_pio_get_ISR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P26) >> PIO_ISR_P26_Pos;
}

static inline bool hri_pio_get_ISR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P27) >> PIO_ISR_P27_Pos;
}

static inline bool hri_pio_get_ISR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P28) >> PIO_ISR_P28_Pos;
}

static inline bool hri_pio_get_ISR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P29) >> PIO_ISR_P29_Pos;
}

static inline bool hri_pio_get_ISR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P30) >> PIO_ISR_P30_Pos;
}

static inline bool hri_pio_get_ISR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ISR & PIO_ISR_P31) >> PIO_ISR_P31_Pos;
}

static inline hri_pio_isr_reg_t hri_pio_get_ISR_reg(const void *const hw, hri_pio_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_isr_reg_t hri_pio_read_ISR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_ISR;
}

static inline void hri_pio_set_PSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P0;
}

static inline bool hri_pio_get_PSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P0) >> PIO_PSR_P0_Pos;
}

static inline void hri_pio_write_PSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P0;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P0;
	}
}

static inline void hri_pio_clear_PSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P0;
}

static inline void hri_pio_set_PSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P1;
}

static inline bool hri_pio_get_PSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P1) >> PIO_PSR_P1_Pos;
}

static inline void hri_pio_write_PSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P1;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P1;
	}
}

static inline void hri_pio_clear_PSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P1;
}

static inline void hri_pio_set_PSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P2;
}

static inline bool hri_pio_get_PSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P2) >> PIO_PSR_P2_Pos;
}

static inline void hri_pio_write_PSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P2;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P2;
	}
}

static inline void hri_pio_clear_PSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P2;
}

static inline void hri_pio_set_PSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P3;
}

static inline bool hri_pio_get_PSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P3) >> PIO_PSR_P3_Pos;
}

static inline void hri_pio_write_PSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P3;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P3;
	}
}

static inline void hri_pio_clear_PSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P3;
}

static inline void hri_pio_set_PSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P4;
}

static inline bool hri_pio_get_PSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P4) >> PIO_PSR_P4_Pos;
}

static inline void hri_pio_write_PSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P4;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P4;
	}
}

static inline void hri_pio_clear_PSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P4;
}

static inline void hri_pio_set_PSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P5;
}

static inline bool hri_pio_get_PSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P5) >> PIO_PSR_P5_Pos;
}

static inline void hri_pio_write_PSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P5;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P5;
	}
}

static inline void hri_pio_clear_PSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P5;
}

static inline void hri_pio_set_PSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P6;
}

static inline bool hri_pio_get_PSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P6) >> PIO_PSR_P6_Pos;
}

static inline void hri_pio_write_PSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P6;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P6;
	}
}

static inline void hri_pio_clear_PSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P6;
}

static inline void hri_pio_set_PSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P7;
}

static inline bool hri_pio_get_PSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P7) >> PIO_PSR_P7_Pos;
}

static inline void hri_pio_write_PSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P7;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P7;
	}
}

static inline void hri_pio_clear_PSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P7;
}

static inline void hri_pio_set_PSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P8;
}

static inline bool hri_pio_get_PSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P8) >> PIO_PSR_P8_Pos;
}

static inline void hri_pio_write_PSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P8;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P8;
	}
}

static inline void hri_pio_clear_PSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P8;
}

static inline void hri_pio_set_PSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P9;
}

static inline bool hri_pio_get_PSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P9) >> PIO_PSR_P9_Pos;
}

static inline void hri_pio_write_PSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P9;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P9;
	}
}

static inline void hri_pio_clear_PSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P9;
}

static inline void hri_pio_set_PSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P10;
}

static inline bool hri_pio_get_PSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P10) >> PIO_PSR_P10_Pos;
}

static inline void hri_pio_write_PSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P10;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P10;
	}
}

static inline void hri_pio_clear_PSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P10;
}

static inline void hri_pio_set_PSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P11;
}

static inline bool hri_pio_get_PSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P11) >> PIO_PSR_P11_Pos;
}

static inline void hri_pio_write_PSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P11;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P11;
	}
}

static inline void hri_pio_clear_PSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P11;
}

static inline void hri_pio_set_PSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P12;
}

static inline bool hri_pio_get_PSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P12) >> PIO_PSR_P12_Pos;
}

static inline void hri_pio_write_PSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P12;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P12;
	}
}

static inline void hri_pio_clear_PSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P12;
}

static inline void hri_pio_set_PSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P13;
}

static inline bool hri_pio_get_PSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P13) >> PIO_PSR_P13_Pos;
}

static inline void hri_pio_write_PSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P13;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P13;
	}
}

static inline void hri_pio_clear_PSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P13;
}

static inline void hri_pio_set_PSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P14;
}

static inline bool hri_pio_get_PSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P14) >> PIO_PSR_P14_Pos;
}

static inline void hri_pio_write_PSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P14;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P14;
	}
}

static inline void hri_pio_clear_PSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P14;
}

static inline void hri_pio_set_PSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P15;
}

static inline bool hri_pio_get_PSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P15) >> PIO_PSR_P15_Pos;
}

static inline void hri_pio_write_PSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P15;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P15;
	}
}

static inline void hri_pio_clear_PSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P15;
}

static inline void hri_pio_set_PSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P16;
}

static inline bool hri_pio_get_PSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P16) >> PIO_PSR_P16_Pos;
}

static inline void hri_pio_write_PSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P16;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P16;
	}
}

static inline void hri_pio_clear_PSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P16;
}

static inline void hri_pio_set_PSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P17;
}

static inline bool hri_pio_get_PSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P17) >> PIO_PSR_P17_Pos;
}

static inline void hri_pio_write_PSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P17;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P17;
	}
}

static inline void hri_pio_clear_PSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P17;
}

static inline void hri_pio_set_PSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P18;
}

static inline bool hri_pio_get_PSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P18) >> PIO_PSR_P18_Pos;
}

static inline void hri_pio_write_PSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P18;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P18;
	}
}

static inline void hri_pio_clear_PSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P18;
}

static inline void hri_pio_set_PSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P19;
}

static inline bool hri_pio_get_PSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P19) >> PIO_PSR_P19_Pos;
}

static inline void hri_pio_write_PSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P19;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P19;
	}
}

static inline void hri_pio_clear_PSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P19;
}

static inline void hri_pio_set_PSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P20;
}

static inline bool hri_pio_get_PSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P20) >> PIO_PSR_P20_Pos;
}

static inline void hri_pio_write_PSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P20;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P20;
	}
}

static inline void hri_pio_clear_PSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P20;
}

static inline void hri_pio_set_PSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P21;
}

static inline bool hri_pio_get_PSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P21) >> PIO_PSR_P21_Pos;
}

static inline void hri_pio_write_PSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P21;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P21;
	}
}

static inline void hri_pio_clear_PSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P21;
}

static inline void hri_pio_set_PSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P22;
}

static inline bool hri_pio_get_PSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P22) >> PIO_PSR_P22_Pos;
}

static inline void hri_pio_write_PSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P22;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P22;
	}
}

static inline void hri_pio_clear_PSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P22;
}

static inline void hri_pio_set_PSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P23;
}

static inline bool hri_pio_get_PSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P23) >> PIO_PSR_P23_Pos;
}

static inline void hri_pio_write_PSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P23;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P23;
	}
}

static inline void hri_pio_clear_PSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P23;
}

static inline void hri_pio_set_PSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P24;
}

static inline bool hri_pio_get_PSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P24) >> PIO_PSR_P24_Pos;
}

static inline void hri_pio_write_PSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P24;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P24;
	}
}

static inline void hri_pio_clear_PSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P24;
}

static inline void hri_pio_set_PSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P25;
}

static inline bool hri_pio_get_PSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P25) >> PIO_PSR_P25_Pos;
}

static inline void hri_pio_write_PSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P25;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P25;
	}
}

static inline void hri_pio_clear_PSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P25;
}

static inline void hri_pio_set_PSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P26;
}

static inline bool hri_pio_get_PSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P26) >> PIO_PSR_P26_Pos;
}

static inline void hri_pio_write_PSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P26;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P26;
	}
}

static inline void hri_pio_clear_PSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P26;
}

static inline void hri_pio_set_PSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P27;
}

static inline bool hri_pio_get_PSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P27) >> PIO_PSR_P27_Pos;
}

static inline void hri_pio_write_PSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P27;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P27;
	}
}

static inline void hri_pio_clear_PSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P27;
}

static inline void hri_pio_set_PSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P28;
}

static inline bool hri_pio_get_PSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P28) >> PIO_PSR_P28_Pos;
}

static inline void hri_pio_write_PSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P28;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P28;
	}
}

static inline void hri_pio_clear_PSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P28;
}

static inline void hri_pio_set_PSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P29;
}

static inline bool hri_pio_get_PSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P29) >> PIO_PSR_P29_Pos;
}

static inline void hri_pio_write_PSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P29;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P29;
	}
}

static inline void hri_pio_clear_PSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P29;
}

static inline void hri_pio_set_PSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P30;
}

static inline bool hri_pio_get_PSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P30) >> PIO_PSR_P30_Pos;
}

static inline void hri_pio_write_PSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P30;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P30;
	}
}

static inline void hri_pio_clear_PSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P30;
}

static inline void hri_pio_set_PSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PER = PIO_PSR_P31;
}

static inline bool hri_pio_get_PSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PSR & PIO_PSR_P31) >> PIO_PSR_P31_Pos;
}

static inline void hri_pio_write_PSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PDR = PIO_PSR_P31;
	} else {
		((Pio *)hw)->PIO_PER = PIO_PSR_P31;
	}
}

static inline void hri_pio_clear_PSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PDR = PIO_PSR_P31;
}

static inline void hri_pio_set_PSR_reg(const void *const hw, hri_pio_psr_reg_t mask)
{
	((Pio *)hw)->PIO_PER = mask;
}

static inline hri_pio_psr_reg_t hri_pio_get_PSR_reg(const void *const hw, hri_pio_psr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_psr_reg_t hri_pio_read_PSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_PSR;
}

static inline void hri_pio_write_PSR_reg(const void *const hw, hri_pio_psr_reg_t data)
{
	((Pio *)hw)->PIO_PER = data;
	((Pio *)hw)->PIO_PDR = ~data;
}

static inline void hri_pio_clear_PSR_reg(const void *const hw, hri_pio_psr_reg_t mask)
{
	((Pio *)hw)->PIO_PDR = mask;
}

static inline void hri_pio_set_OSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P0;
}

static inline bool hri_pio_get_OSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P0) >> PIO_OSR_P0_Pos;
}

static inline void hri_pio_write_OSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P0;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P0;
	}
}

static inline void hri_pio_clear_OSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P0;
}

static inline void hri_pio_set_OSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P1;
}

static inline bool hri_pio_get_OSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P1) >> PIO_OSR_P1_Pos;
}

static inline void hri_pio_write_OSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P1;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P1;
	}
}

static inline void hri_pio_clear_OSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P1;
}

static inline void hri_pio_set_OSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P2;
}

static inline bool hri_pio_get_OSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P2) >> PIO_OSR_P2_Pos;
}

static inline void hri_pio_write_OSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P2;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P2;
	}
}

static inline void hri_pio_clear_OSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P2;
}

static inline void hri_pio_set_OSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P3;
}

static inline bool hri_pio_get_OSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P3) >> PIO_OSR_P3_Pos;
}

static inline void hri_pio_write_OSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P3;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P3;
	}
}

static inline void hri_pio_clear_OSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P3;
}

static inline void hri_pio_set_OSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P4;
}

static inline bool hri_pio_get_OSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P4) >> PIO_OSR_P4_Pos;
}

static inline void hri_pio_write_OSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P4;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P4;
	}
}

static inline void hri_pio_clear_OSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P4;
}

static inline void hri_pio_set_OSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P5;
}

static inline bool hri_pio_get_OSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P5) >> PIO_OSR_P5_Pos;
}

static inline void hri_pio_write_OSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P5;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P5;
	}
}

static inline void hri_pio_clear_OSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P5;
}

static inline void hri_pio_set_OSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P6;
}

static inline bool hri_pio_get_OSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P6) >> PIO_OSR_P6_Pos;
}

static inline void hri_pio_write_OSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P6;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P6;
	}
}

static inline void hri_pio_clear_OSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P6;
}

static inline void hri_pio_set_OSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P7;
}

static inline bool hri_pio_get_OSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P7) >> PIO_OSR_P7_Pos;
}

static inline void hri_pio_write_OSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P7;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P7;
	}
}

static inline void hri_pio_clear_OSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P7;
}

static inline void hri_pio_set_OSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P8;
}

static inline bool hri_pio_get_OSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P8) >> PIO_OSR_P8_Pos;
}

static inline void hri_pio_write_OSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P8;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P8;
	}
}

static inline void hri_pio_clear_OSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P8;
}

static inline void hri_pio_set_OSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P9;
}

static inline bool hri_pio_get_OSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P9) >> PIO_OSR_P9_Pos;
}

static inline void hri_pio_write_OSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P9;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P9;
	}
}

static inline void hri_pio_clear_OSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P9;
}

static inline void hri_pio_set_OSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P10;
}

static inline bool hri_pio_get_OSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P10) >> PIO_OSR_P10_Pos;
}

static inline void hri_pio_write_OSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P10;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P10;
	}
}

static inline void hri_pio_clear_OSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P10;
}

static inline void hri_pio_set_OSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P11;
}

static inline bool hri_pio_get_OSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P11) >> PIO_OSR_P11_Pos;
}

static inline void hri_pio_write_OSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P11;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P11;
	}
}

static inline void hri_pio_clear_OSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P11;
}

static inline void hri_pio_set_OSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P12;
}

static inline bool hri_pio_get_OSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P12) >> PIO_OSR_P12_Pos;
}

static inline void hri_pio_write_OSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P12;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P12;
	}
}

static inline void hri_pio_clear_OSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P12;
}

static inline void hri_pio_set_OSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P13;
}

static inline bool hri_pio_get_OSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P13) >> PIO_OSR_P13_Pos;
}

static inline void hri_pio_write_OSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P13;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P13;
	}
}

static inline void hri_pio_clear_OSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P13;
}

static inline void hri_pio_set_OSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P14;
}

static inline bool hri_pio_get_OSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P14) >> PIO_OSR_P14_Pos;
}

static inline void hri_pio_write_OSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P14;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P14;
	}
}

static inline void hri_pio_clear_OSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P14;
}

static inline void hri_pio_set_OSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P15;
}

static inline bool hri_pio_get_OSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P15) >> PIO_OSR_P15_Pos;
}

static inline void hri_pio_write_OSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P15;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P15;
	}
}

static inline void hri_pio_clear_OSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P15;
}

static inline void hri_pio_set_OSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P16;
}

static inline bool hri_pio_get_OSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P16) >> PIO_OSR_P16_Pos;
}

static inline void hri_pio_write_OSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P16;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P16;
	}
}

static inline void hri_pio_clear_OSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P16;
}

static inline void hri_pio_set_OSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P17;
}

static inline bool hri_pio_get_OSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P17) >> PIO_OSR_P17_Pos;
}

static inline void hri_pio_write_OSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P17;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P17;
	}
}

static inline void hri_pio_clear_OSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P17;
}

static inline void hri_pio_set_OSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P18;
}

static inline bool hri_pio_get_OSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P18) >> PIO_OSR_P18_Pos;
}

static inline void hri_pio_write_OSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P18;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P18;
	}
}

static inline void hri_pio_clear_OSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P18;
}

static inline void hri_pio_set_OSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P19;
}

static inline bool hri_pio_get_OSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P19) >> PIO_OSR_P19_Pos;
}

static inline void hri_pio_write_OSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P19;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P19;
	}
}

static inline void hri_pio_clear_OSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P19;
}

static inline void hri_pio_set_OSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P20;
}

static inline bool hri_pio_get_OSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P20) >> PIO_OSR_P20_Pos;
}

static inline void hri_pio_write_OSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P20;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P20;
	}
}

static inline void hri_pio_clear_OSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P20;
}

static inline void hri_pio_set_OSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P21;
}

static inline bool hri_pio_get_OSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P21) >> PIO_OSR_P21_Pos;
}

static inline void hri_pio_write_OSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P21;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P21;
	}
}

static inline void hri_pio_clear_OSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P21;
}

static inline void hri_pio_set_OSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P22;
}

static inline bool hri_pio_get_OSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P22) >> PIO_OSR_P22_Pos;
}

static inline void hri_pio_write_OSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P22;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P22;
	}
}

static inline void hri_pio_clear_OSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P22;
}

static inline void hri_pio_set_OSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P23;
}

static inline bool hri_pio_get_OSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P23) >> PIO_OSR_P23_Pos;
}

static inline void hri_pio_write_OSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P23;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P23;
	}
}

static inline void hri_pio_clear_OSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P23;
}

static inline void hri_pio_set_OSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P24;
}

static inline bool hri_pio_get_OSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P24) >> PIO_OSR_P24_Pos;
}

static inline void hri_pio_write_OSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P24;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P24;
	}
}

static inline void hri_pio_clear_OSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P24;
}

static inline void hri_pio_set_OSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P25;
}

static inline bool hri_pio_get_OSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P25) >> PIO_OSR_P25_Pos;
}

static inline void hri_pio_write_OSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P25;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P25;
	}
}

static inline void hri_pio_clear_OSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P25;
}

static inline void hri_pio_set_OSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P26;
}

static inline bool hri_pio_get_OSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P26) >> PIO_OSR_P26_Pos;
}

static inline void hri_pio_write_OSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P26;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P26;
	}
}

static inline void hri_pio_clear_OSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P26;
}

static inline void hri_pio_set_OSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P27;
}

static inline bool hri_pio_get_OSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P27) >> PIO_OSR_P27_Pos;
}

static inline void hri_pio_write_OSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P27;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P27;
	}
}

static inline void hri_pio_clear_OSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P27;
}

static inline void hri_pio_set_OSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P28;
}

static inline bool hri_pio_get_OSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P28) >> PIO_OSR_P28_Pos;
}

static inline void hri_pio_write_OSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P28;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P28;
	}
}

static inline void hri_pio_clear_OSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P28;
}

static inline void hri_pio_set_OSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P29;
}

static inline bool hri_pio_get_OSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P29) >> PIO_OSR_P29_Pos;
}

static inline void hri_pio_write_OSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P29;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P29;
	}
}

static inline void hri_pio_clear_OSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P29;
}

static inline void hri_pio_set_OSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P30;
}

static inline bool hri_pio_get_OSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P30) >> PIO_OSR_P30_Pos;
}

static inline void hri_pio_write_OSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P30;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P30;
	}
}

static inline void hri_pio_clear_OSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P30;
}

static inline void hri_pio_set_OSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OER = PIO_OSR_P31;
}

static inline bool hri_pio_get_OSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OSR & PIO_OSR_P31) >> PIO_OSR_P31_Pos;
}

static inline void hri_pio_write_OSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ODR = PIO_OSR_P31;
	} else {
		((Pio *)hw)->PIO_OER = PIO_OSR_P31;
	}
}

static inline void hri_pio_clear_OSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ODR = PIO_OSR_P31;
}

static inline void hri_pio_set_OSR_reg(const void *const hw, hri_pio_osr_reg_t mask)
{
	((Pio *)hw)->PIO_OER = mask;
}

static inline hri_pio_osr_reg_t hri_pio_get_OSR_reg(const void *const hw, hri_pio_osr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_OSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_osr_reg_t hri_pio_read_OSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_OSR;
}

static inline void hri_pio_write_OSR_reg(const void *const hw, hri_pio_osr_reg_t data)
{
	((Pio *)hw)->PIO_OER = data;
	((Pio *)hw)->PIO_ODR = ~data;
}

static inline void hri_pio_clear_OSR_reg(const void *const hw, hri_pio_osr_reg_t mask)
{
	((Pio *)hw)->PIO_ODR = mask;
}

static inline void hri_pio_set_IFSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P0;
}

static inline bool hri_pio_get_IFSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P0) >> PIO_IFSR_P0_Pos;
}

static inline void hri_pio_write_IFSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P0;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P0;
	}
}

static inline void hri_pio_clear_IFSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P0;
}

static inline void hri_pio_set_IFSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P1;
}

static inline bool hri_pio_get_IFSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P1) >> PIO_IFSR_P1_Pos;
}

static inline void hri_pio_write_IFSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P1;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P1;
	}
}

static inline void hri_pio_clear_IFSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P1;
}

static inline void hri_pio_set_IFSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P2;
}

static inline bool hri_pio_get_IFSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P2) >> PIO_IFSR_P2_Pos;
}

static inline void hri_pio_write_IFSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P2;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P2;
	}
}

static inline void hri_pio_clear_IFSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P2;
}

static inline void hri_pio_set_IFSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P3;
}

static inline bool hri_pio_get_IFSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P3) >> PIO_IFSR_P3_Pos;
}

static inline void hri_pio_write_IFSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P3;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P3;
	}
}

static inline void hri_pio_clear_IFSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P3;
}

static inline void hri_pio_set_IFSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P4;
}

static inline bool hri_pio_get_IFSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P4) >> PIO_IFSR_P4_Pos;
}

static inline void hri_pio_write_IFSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P4;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P4;
	}
}

static inline void hri_pio_clear_IFSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P4;
}

static inline void hri_pio_set_IFSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P5;
}

static inline bool hri_pio_get_IFSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P5) >> PIO_IFSR_P5_Pos;
}

static inline void hri_pio_write_IFSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P5;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P5;
	}
}

static inline void hri_pio_clear_IFSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P5;
}

static inline void hri_pio_set_IFSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P6;
}

static inline bool hri_pio_get_IFSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P6) >> PIO_IFSR_P6_Pos;
}

static inline void hri_pio_write_IFSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P6;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P6;
	}
}

static inline void hri_pio_clear_IFSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P6;
}

static inline void hri_pio_set_IFSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P7;
}

static inline bool hri_pio_get_IFSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P7) >> PIO_IFSR_P7_Pos;
}

static inline void hri_pio_write_IFSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P7;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P7;
	}
}

static inline void hri_pio_clear_IFSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P7;
}

static inline void hri_pio_set_IFSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P8;
}

static inline bool hri_pio_get_IFSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P8) >> PIO_IFSR_P8_Pos;
}

static inline void hri_pio_write_IFSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P8;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P8;
	}
}

static inline void hri_pio_clear_IFSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P8;
}

static inline void hri_pio_set_IFSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P9;
}

static inline bool hri_pio_get_IFSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P9) >> PIO_IFSR_P9_Pos;
}

static inline void hri_pio_write_IFSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P9;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P9;
	}
}

static inline void hri_pio_clear_IFSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P9;
}

static inline void hri_pio_set_IFSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P10;
}

static inline bool hri_pio_get_IFSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P10) >> PIO_IFSR_P10_Pos;
}

static inline void hri_pio_write_IFSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P10;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P10;
	}
}

static inline void hri_pio_clear_IFSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P10;
}

static inline void hri_pio_set_IFSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P11;
}

static inline bool hri_pio_get_IFSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P11) >> PIO_IFSR_P11_Pos;
}

static inline void hri_pio_write_IFSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P11;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P11;
	}
}

static inline void hri_pio_clear_IFSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P11;
}

static inline void hri_pio_set_IFSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P12;
}

static inline bool hri_pio_get_IFSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P12) >> PIO_IFSR_P12_Pos;
}

static inline void hri_pio_write_IFSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P12;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P12;
	}
}

static inline void hri_pio_clear_IFSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P12;
}

static inline void hri_pio_set_IFSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P13;
}

static inline bool hri_pio_get_IFSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P13) >> PIO_IFSR_P13_Pos;
}

static inline void hri_pio_write_IFSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P13;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P13;
	}
}

static inline void hri_pio_clear_IFSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P13;
}

static inline void hri_pio_set_IFSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P14;
}

static inline bool hri_pio_get_IFSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P14) >> PIO_IFSR_P14_Pos;
}

static inline void hri_pio_write_IFSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P14;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P14;
	}
}

static inline void hri_pio_clear_IFSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P14;
}

static inline void hri_pio_set_IFSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P15;
}

static inline bool hri_pio_get_IFSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P15) >> PIO_IFSR_P15_Pos;
}

static inline void hri_pio_write_IFSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P15;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P15;
	}
}

static inline void hri_pio_clear_IFSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P15;
}

static inline void hri_pio_set_IFSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P16;
}

static inline bool hri_pio_get_IFSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P16) >> PIO_IFSR_P16_Pos;
}

static inline void hri_pio_write_IFSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P16;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P16;
	}
}

static inline void hri_pio_clear_IFSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P16;
}

static inline void hri_pio_set_IFSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P17;
}

static inline bool hri_pio_get_IFSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P17) >> PIO_IFSR_P17_Pos;
}

static inline void hri_pio_write_IFSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P17;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P17;
	}
}

static inline void hri_pio_clear_IFSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P17;
}

static inline void hri_pio_set_IFSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P18;
}

static inline bool hri_pio_get_IFSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P18) >> PIO_IFSR_P18_Pos;
}

static inline void hri_pio_write_IFSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P18;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P18;
	}
}

static inline void hri_pio_clear_IFSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P18;
}

static inline void hri_pio_set_IFSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P19;
}

static inline bool hri_pio_get_IFSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P19) >> PIO_IFSR_P19_Pos;
}

static inline void hri_pio_write_IFSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P19;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P19;
	}
}

static inline void hri_pio_clear_IFSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P19;
}

static inline void hri_pio_set_IFSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P20;
}

static inline bool hri_pio_get_IFSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P20) >> PIO_IFSR_P20_Pos;
}

static inline void hri_pio_write_IFSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P20;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P20;
	}
}

static inline void hri_pio_clear_IFSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P20;
}

static inline void hri_pio_set_IFSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P21;
}

static inline bool hri_pio_get_IFSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P21) >> PIO_IFSR_P21_Pos;
}

static inline void hri_pio_write_IFSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P21;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P21;
	}
}

static inline void hri_pio_clear_IFSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P21;
}

static inline void hri_pio_set_IFSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P22;
}

static inline bool hri_pio_get_IFSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P22) >> PIO_IFSR_P22_Pos;
}

static inline void hri_pio_write_IFSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P22;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P22;
	}
}

static inline void hri_pio_clear_IFSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P22;
}

static inline void hri_pio_set_IFSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P23;
}

static inline bool hri_pio_get_IFSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P23) >> PIO_IFSR_P23_Pos;
}

static inline void hri_pio_write_IFSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P23;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P23;
	}
}

static inline void hri_pio_clear_IFSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P23;
}

static inline void hri_pio_set_IFSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P24;
}

static inline bool hri_pio_get_IFSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P24) >> PIO_IFSR_P24_Pos;
}

static inline void hri_pio_write_IFSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P24;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P24;
	}
}

static inline void hri_pio_clear_IFSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P24;
}

static inline void hri_pio_set_IFSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P25;
}

static inline bool hri_pio_get_IFSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P25) >> PIO_IFSR_P25_Pos;
}

static inline void hri_pio_write_IFSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P25;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P25;
	}
}

static inline void hri_pio_clear_IFSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P25;
}

static inline void hri_pio_set_IFSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P26;
}

static inline bool hri_pio_get_IFSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P26) >> PIO_IFSR_P26_Pos;
}

static inline void hri_pio_write_IFSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P26;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P26;
	}
}

static inline void hri_pio_clear_IFSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P26;
}

static inline void hri_pio_set_IFSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P27;
}

static inline bool hri_pio_get_IFSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P27) >> PIO_IFSR_P27_Pos;
}

static inline void hri_pio_write_IFSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P27;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P27;
	}
}

static inline void hri_pio_clear_IFSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P27;
}

static inline void hri_pio_set_IFSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P28;
}

static inline bool hri_pio_get_IFSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P28) >> PIO_IFSR_P28_Pos;
}

static inline void hri_pio_write_IFSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P28;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P28;
	}
}

static inline void hri_pio_clear_IFSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P28;
}

static inline void hri_pio_set_IFSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P29;
}

static inline bool hri_pio_get_IFSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P29) >> PIO_IFSR_P29_Pos;
}

static inline void hri_pio_write_IFSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P29;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P29;
	}
}

static inline void hri_pio_clear_IFSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P29;
}

static inline void hri_pio_set_IFSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P30;
}

static inline bool hri_pio_get_IFSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P30) >> PIO_IFSR_P30_Pos;
}

static inline void hri_pio_write_IFSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P30;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P30;
	}
}

static inline void hri_pio_clear_IFSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P30;
}

static inline void hri_pio_set_IFSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFER = PIO_IFSR_P31;
}

static inline bool hri_pio_get_IFSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSR & PIO_IFSR_P31) >> PIO_IFSR_P31_Pos;
}

static inline void hri_pio_write_IFSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFDR = PIO_IFSR_P31;
	} else {
		((Pio *)hw)->PIO_IFER = PIO_IFSR_P31;
	}
}

static inline void hri_pio_clear_IFSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFDR = PIO_IFSR_P31;
}

static inline void hri_pio_set_IFSR_reg(const void *const hw, hri_pio_ifsr_reg_t mask)
{
	((Pio *)hw)->PIO_IFER = mask;
}

static inline hri_pio_ifsr_reg_t hri_pio_get_IFSR_reg(const void *const hw, hri_pio_ifsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_IFSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_ifsr_reg_t hri_pio_read_IFSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_IFSR;
}

static inline void hri_pio_write_IFSR_reg(const void *const hw, hri_pio_ifsr_reg_t data)
{
	((Pio *)hw)->PIO_IFER = data;
	((Pio *)hw)->PIO_IFDR = ~data;
}

static inline void hri_pio_clear_IFSR_reg(const void *const hw, hri_pio_ifsr_reg_t mask)
{
	((Pio *)hw)->PIO_IFDR = mask;
}

static inline void hri_pio_set_ODSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P0;
}

static inline bool hri_pio_get_ODSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P0) >> PIO_ODSR_P0_Pos;
}

static inline void hri_pio_write_ODSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P0;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P0;
	}
}

static inline void hri_pio_clear_ODSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P0;
}

static inline void hri_pio_set_ODSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P1;
}

static inline bool hri_pio_get_ODSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P1) >> PIO_ODSR_P1_Pos;
}

static inline void hri_pio_write_ODSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P1;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P1;
	}
}

static inline void hri_pio_clear_ODSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P1;
}

static inline void hri_pio_set_ODSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P2;
}

static inline bool hri_pio_get_ODSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P2) >> PIO_ODSR_P2_Pos;
}

static inline void hri_pio_write_ODSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P2;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P2;
	}
}

static inline void hri_pio_clear_ODSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P2;
}

static inline void hri_pio_set_ODSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P3;
}

static inline bool hri_pio_get_ODSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P3) >> PIO_ODSR_P3_Pos;
}

static inline void hri_pio_write_ODSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P3;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P3;
	}
}

static inline void hri_pio_clear_ODSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P3;
}

static inline void hri_pio_set_ODSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P4;
}

static inline bool hri_pio_get_ODSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P4) >> PIO_ODSR_P4_Pos;
}

static inline void hri_pio_write_ODSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P4;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P4;
	}
}

static inline void hri_pio_clear_ODSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P4;
}

static inline void hri_pio_set_ODSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P5;
}

static inline bool hri_pio_get_ODSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P5) >> PIO_ODSR_P5_Pos;
}

static inline void hri_pio_write_ODSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P5;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P5;
	}
}

static inline void hri_pio_clear_ODSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P5;
}

static inline void hri_pio_set_ODSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P6;
}

static inline bool hri_pio_get_ODSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P6) >> PIO_ODSR_P6_Pos;
}

static inline void hri_pio_write_ODSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P6;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P6;
	}
}

static inline void hri_pio_clear_ODSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P6;
}

static inline void hri_pio_set_ODSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P7;
}

static inline bool hri_pio_get_ODSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P7) >> PIO_ODSR_P7_Pos;
}

static inline void hri_pio_write_ODSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P7;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P7;
	}
}

static inline void hri_pio_clear_ODSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P7;
}

static inline void hri_pio_set_ODSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P8;
}

static inline bool hri_pio_get_ODSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P8) >> PIO_ODSR_P8_Pos;
}

static inline void hri_pio_write_ODSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P8;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P8;
	}
}

static inline void hri_pio_clear_ODSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P8;
}

static inline void hri_pio_set_ODSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P9;
}

static inline bool hri_pio_get_ODSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P9) >> PIO_ODSR_P9_Pos;
}

static inline void hri_pio_write_ODSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P9;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P9;
	}
}

static inline void hri_pio_clear_ODSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P9;
}

static inline void hri_pio_set_ODSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P10;
}

static inline bool hri_pio_get_ODSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P10) >> PIO_ODSR_P10_Pos;
}

static inline void hri_pio_write_ODSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P10;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P10;
	}
}

static inline void hri_pio_clear_ODSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P10;
}

static inline void hri_pio_set_ODSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P11;
}

static inline bool hri_pio_get_ODSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P11) >> PIO_ODSR_P11_Pos;
}

static inline void hri_pio_write_ODSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P11;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P11;
	}
}

static inline void hri_pio_clear_ODSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P11;
}

static inline void hri_pio_set_ODSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P12;
}

static inline bool hri_pio_get_ODSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P12) >> PIO_ODSR_P12_Pos;
}

static inline void hri_pio_write_ODSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P12;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P12;
	}
}

static inline void hri_pio_clear_ODSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P12;
}

static inline void hri_pio_set_ODSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P13;
}

static inline bool hri_pio_get_ODSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P13) >> PIO_ODSR_P13_Pos;
}

static inline void hri_pio_write_ODSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P13;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P13;
	}
}

static inline void hri_pio_clear_ODSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P13;
}

static inline void hri_pio_set_ODSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P14;
}

static inline bool hri_pio_get_ODSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P14) >> PIO_ODSR_P14_Pos;
}

static inline void hri_pio_write_ODSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P14;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P14;
	}
}

static inline void hri_pio_clear_ODSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P14;
}

static inline void hri_pio_set_ODSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P15;
}

static inline bool hri_pio_get_ODSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P15) >> PIO_ODSR_P15_Pos;
}

static inline void hri_pio_write_ODSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P15;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P15;
	}
}

static inline void hri_pio_clear_ODSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P15;
}

static inline void hri_pio_set_ODSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P16;
}

static inline bool hri_pio_get_ODSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P16) >> PIO_ODSR_P16_Pos;
}

static inline void hri_pio_write_ODSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P16;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P16;
	}
}

static inline void hri_pio_clear_ODSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P16;
}

static inline void hri_pio_set_ODSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P17;
}

static inline bool hri_pio_get_ODSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P17) >> PIO_ODSR_P17_Pos;
}

static inline void hri_pio_write_ODSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P17;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P17;
	}
}

static inline void hri_pio_clear_ODSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P17;
}

static inline void hri_pio_set_ODSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P18;
}

static inline bool hri_pio_get_ODSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P18) >> PIO_ODSR_P18_Pos;
}

static inline void hri_pio_write_ODSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P18;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P18;
	}
}

static inline void hri_pio_clear_ODSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P18;
}

static inline void hri_pio_set_ODSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P19;
}

static inline bool hri_pio_get_ODSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P19) >> PIO_ODSR_P19_Pos;
}

static inline void hri_pio_write_ODSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P19;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P19;
	}
}

static inline void hri_pio_clear_ODSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P19;
}

static inline void hri_pio_set_ODSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P20;
}

static inline bool hri_pio_get_ODSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P20) >> PIO_ODSR_P20_Pos;
}

static inline void hri_pio_write_ODSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P20;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P20;
	}
}

static inline void hri_pio_clear_ODSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P20;
}

static inline void hri_pio_set_ODSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P21;
}

static inline bool hri_pio_get_ODSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P21) >> PIO_ODSR_P21_Pos;
}

static inline void hri_pio_write_ODSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P21;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P21;
	}
}

static inline void hri_pio_clear_ODSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P21;
}

static inline void hri_pio_set_ODSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P22;
}

static inline bool hri_pio_get_ODSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P22) >> PIO_ODSR_P22_Pos;
}

static inline void hri_pio_write_ODSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P22;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P22;
	}
}

static inline void hri_pio_clear_ODSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P22;
}

static inline void hri_pio_set_ODSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P23;
}

static inline bool hri_pio_get_ODSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P23) >> PIO_ODSR_P23_Pos;
}

static inline void hri_pio_write_ODSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P23;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P23;
	}
}

static inline void hri_pio_clear_ODSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P23;
}

static inline void hri_pio_set_ODSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P24;
}

static inline bool hri_pio_get_ODSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P24) >> PIO_ODSR_P24_Pos;
}

static inline void hri_pio_write_ODSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P24;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P24;
	}
}

static inline void hri_pio_clear_ODSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P24;
}

static inline void hri_pio_set_ODSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P25;
}

static inline bool hri_pio_get_ODSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P25) >> PIO_ODSR_P25_Pos;
}

static inline void hri_pio_write_ODSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P25;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P25;
	}
}

static inline void hri_pio_clear_ODSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P25;
}

static inline void hri_pio_set_ODSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P26;
}

static inline bool hri_pio_get_ODSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P26) >> PIO_ODSR_P26_Pos;
}

static inline void hri_pio_write_ODSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P26;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P26;
	}
}

static inline void hri_pio_clear_ODSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P26;
}

static inline void hri_pio_set_ODSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P27;
}

static inline bool hri_pio_get_ODSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P27) >> PIO_ODSR_P27_Pos;
}

static inline void hri_pio_write_ODSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P27;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P27;
	}
}

static inline void hri_pio_clear_ODSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P27;
}

static inline void hri_pio_set_ODSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P28;
}

static inline bool hri_pio_get_ODSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P28) >> PIO_ODSR_P28_Pos;
}

static inline void hri_pio_write_ODSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P28;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P28;
	}
}

static inline void hri_pio_clear_ODSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P28;
}

static inline void hri_pio_set_ODSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P29;
}

static inline bool hri_pio_get_ODSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P29) >> PIO_ODSR_P29_Pos;
}

static inline void hri_pio_write_ODSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P29;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P29;
	}
}

static inline void hri_pio_clear_ODSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P29;
}

static inline void hri_pio_set_ODSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P30;
}

static inline bool hri_pio_get_ODSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P30) >> PIO_ODSR_P30_Pos;
}

static inline void hri_pio_write_ODSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P30;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P30;
	}
}

static inline void hri_pio_clear_ODSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P30;
}

static inline void hri_pio_set_ODSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_SODR = PIO_ODSR_P31;
}

static inline bool hri_pio_get_ODSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ODSR & PIO_ODSR_P31) >> PIO_ODSR_P31_Pos;
}

static inline void hri_pio_write_ODSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_CODR = PIO_ODSR_P31;
	} else {
		((Pio *)hw)->PIO_SODR = PIO_ODSR_P31;
	}
}

static inline void hri_pio_clear_ODSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_CODR = PIO_ODSR_P31;
}

static inline void hri_pio_set_ODSR_reg(const void *const hw, hri_pio_odsr_reg_t mask)
{
	((Pio *)hw)->PIO_SODR = mask;
}

static inline hri_pio_odsr_reg_t hri_pio_get_ODSR_reg(const void *const hw, hri_pio_odsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ODSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_odsr_reg_t hri_pio_read_ODSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_ODSR;
}

static inline void hri_pio_write_ODSR_reg(const void *const hw, hri_pio_odsr_reg_t data)
{
	((Pio *)hw)->PIO_SODR = data;
	((Pio *)hw)->PIO_CODR = ~data;
}

static inline void hri_pio_clear_ODSR_reg(const void *const hw, hri_pio_odsr_reg_t mask)
{
	((Pio *)hw)->PIO_CODR = mask;
}

static inline void hri_pio_set_IMR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P0;
}

static inline bool hri_pio_get_IMR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P0) >> PIO_IMR_P0_Pos;
}

static inline void hri_pio_write_IMR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P0;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P0;
	}
}

static inline void hri_pio_clear_IMR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P0;
}

static inline void hri_pio_set_IMR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P1;
}

static inline bool hri_pio_get_IMR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P1) >> PIO_IMR_P1_Pos;
}

static inline void hri_pio_write_IMR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P1;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P1;
	}
}

static inline void hri_pio_clear_IMR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P1;
}

static inline void hri_pio_set_IMR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P2;
}

static inline bool hri_pio_get_IMR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P2) >> PIO_IMR_P2_Pos;
}

static inline void hri_pio_write_IMR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P2;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P2;
	}
}

static inline void hri_pio_clear_IMR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P2;
}

static inline void hri_pio_set_IMR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P3;
}

static inline bool hri_pio_get_IMR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P3) >> PIO_IMR_P3_Pos;
}

static inline void hri_pio_write_IMR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P3;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P3;
	}
}

static inline void hri_pio_clear_IMR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P3;
}

static inline void hri_pio_set_IMR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P4;
}

static inline bool hri_pio_get_IMR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P4) >> PIO_IMR_P4_Pos;
}

static inline void hri_pio_write_IMR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P4;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P4;
	}
}

static inline void hri_pio_clear_IMR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P4;
}

static inline void hri_pio_set_IMR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P5;
}

static inline bool hri_pio_get_IMR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P5) >> PIO_IMR_P5_Pos;
}

static inline void hri_pio_write_IMR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P5;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P5;
	}
}

static inline void hri_pio_clear_IMR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P5;
}

static inline void hri_pio_set_IMR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P6;
}

static inline bool hri_pio_get_IMR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P6) >> PIO_IMR_P6_Pos;
}

static inline void hri_pio_write_IMR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P6;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P6;
	}
}

static inline void hri_pio_clear_IMR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P6;
}

static inline void hri_pio_set_IMR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P7;
}

static inline bool hri_pio_get_IMR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P7) >> PIO_IMR_P7_Pos;
}

static inline void hri_pio_write_IMR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P7;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P7;
	}
}

static inline void hri_pio_clear_IMR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P7;
}

static inline void hri_pio_set_IMR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P8;
}

static inline bool hri_pio_get_IMR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P8) >> PIO_IMR_P8_Pos;
}

static inline void hri_pio_write_IMR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P8;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P8;
	}
}

static inline void hri_pio_clear_IMR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P8;
}

static inline void hri_pio_set_IMR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P9;
}

static inline bool hri_pio_get_IMR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P9) >> PIO_IMR_P9_Pos;
}

static inline void hri_pio_write_IMR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P9;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P9;
	}
}

static inline void hri_pio_clear_IMR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P9;
}

static inline void hri_pio_set_IMR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P10;
}

static inline bool hri_pio_get_IMR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P10) >> PIO_IMR_P10_Pos;
}

static inline void hri_pio_write_IMR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P10;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P10;
	}
}

static inline void hri_pio_clear_IMR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P10;
}

static inline void hri_pio_set_IMR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P11;
}

static inline bool hri_pio_get_IMR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P11) >> PIO_IMR_P11_Pos;
}

static inline void hri_pio_write_IMR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P11;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P11;
	}
}

static inline void hri_pio_clear_IMR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P11;
}

static inline void hri_pio_set_IMR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P12;
}

static inline bool hri_pio_get_IMR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P12) >> PIO_IMR_P12_Pos;
}

static inline void hri_pio_write_IMR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P12;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P12;
	}
}

static inline void hri_pio_clear_IMR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P12;
}

static inline void hri_pio_set_IMR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P13;
}

static inline bool hri_pio_get_IMR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P13) >> PIO_IMR_P13_Pos;
}

static inline void hri_pio_write_IMR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P13;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P13;
	}
}

static inline void hri_pio_clear_IMR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P13;
}

static inline void hri_pio_set_IMR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P14;
}

static inline bool hri_pio_get_IMR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P14) >> PIO_IMR_P14_Pos;
}

static inline void hri_pio_write_IMR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P14;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P14;
	}
}

static inline void hri_pio_clear_IMR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P14;
}

static inline void hri_pio_set_IMR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P15;
}

static inline bool hri_pio_get_IMR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P15) >> PIO_IMR_P15_Pos;
}

static inline void hri_pio_write_IMR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P15;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P15;
	}
}

static inline void hri_pio_clear_IMR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P15;
}

static inline void hri_pio_set_IMR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P16;
}

static inline bool hri_pio_get_IMR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P16) >> PIO_IMR_P16_Pos;
}

static inline void hri_pio_write_IMR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P16;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P16;
	}
}

static inline void hri_pio_clear_IMR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P16;
}

static inline void hri_pio_set_IMR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P17;
}

static inline bool hri_pio_get_IMR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P17) >> PIO_IMR_P17_Pos;
}

static inline void hri_pio_write_IMR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P17;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P17;
	}
}

static inline void hri_pio_clear_IMR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P17;
}

static inline void hri_pio_set_IMR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P18;
}

static inline bool hri_pio_get_IMR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P18) >> PIO_IMR_P18_Pos;
}

static inline void hri_pio_write_IMR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P18;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P18;
	}
}

static inline void hri_pio_clear_IMR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P18;
}

static inline void hri_pio_set_IMR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P19;
}

static inline bool hri_pio_get_IMR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P19) >> PIO_IMR_P19_Pos;
}

static inline void hri_pio_write_IMR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P19;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P19;
	}
}

static inline void hri_pio_clear_IMR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P19;
}

static inline void hri_pio_set_IMR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P20;
}

static inline bool hri_pio_get_IMR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P20) >> PIO_IMR_P20_Pos;
}

static inline void hri_pio_write_IMR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P20;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P20;
	}
}

static inline void hri_pio_clear_IMR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P20;
}

static inline void hri_pio_set_IMR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P21;
}

static inline bool hri_pio_get_IMR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P21) >> PIO_IMR_P21_Pos;
}

static inline void hri_pio_write_IMR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P21;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P21;
	}
}

static inline void hri_pio_clear_IMR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P21;
}

static inline void hri_pio_set_IMR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P22;
}

static inline bool hri_pio_get_IMR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P22) >> PIO_IMR_P22_Pos;
}

static inline void hri_pio_write_IMR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P22;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P22;
	}
}

static inline void hri_pio_clear_IMR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P22;
}

static inline void hri_pio_set_IMR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P23;
}

static inline bool hri_pio_get_IMR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P23) >> PIO_IMR_P23_Pos;
}

static inline void hri_pio_write_IMR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P23;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P23;
	}
}

static inline void hri_pio_clear_IMR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P23;
}

static inline void hri_pio_set_IMR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P24;
}

static inline bool hri_pio_get_IMR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P24) >> PIO_IMR_P24_Pos;
}

static inline void hri_pio_write_IMR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P24;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P24;
	}
}

static inline void hri_pio_clear_IMR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P24;
}

static inline void hri_pio_set_IMR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P25;
}

static inline bool hri_pio_get_IMR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P25) >> PIO_IMR_P25_Pos;
}

static inline void hri_pio_write_IMR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P25;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P25;
	}
}

static inline void hri_pio_clear_IMR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P25;
}

static inline void hri_pio_set_IMR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P26;
}

static inline bool hri_pio_get_IMR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P26) >> PIO_IMR_P26_Pos;
}

static inline void hri_pio_write_IMR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P26;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P26;
	}
}

static inline void hri_pio_clear_IMR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P26;
}

static inline void hri_pio_set_IMR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P27;
}

static inline bool hri_pio_get_IMR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P27) >> PIO_IMR_P27_Pos;
}

static inline void hri_pio_write_IMR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P27;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P27;
	}
}

static inline void hri_pio_clear_IMR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P27;
}

static inline void hri_pio_set_IMR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P28;
}

static inline bool hri_pio_get_IMR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P28) >> PIO_IMR_P28_Pos;
}

static inline void hri_pio_write_IMR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P28;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P28;
	}
}

static inline void hri_pio_clear_IMR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P28;
}

static inline void hri_pio_set_IMR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P29;
}

static inline bool hri_pio_get_IMR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P29) >> PIO_IMR_P29_Pos;
}

static inline void hri_pio_write_IMR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P29;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P29;
	}
}

static inline void hri_pio_clear_IMR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P29;
}

static inline void hri_pio_set_IMR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P30;
}

static inline bool hri_pio_get_IMR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P30) >> PIO_IMR_P30_Pos;
}

static inline void hri_pio_write_IMR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P30;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P30;
	}
}

static inline void hri_pio_clear_IMR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P30;
}

static inline void hri_pio_set_IMR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IER = PIO_IMR_P31;
}

static inline bool hri_pio_get_IMR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IMR & PIO_IMR_P31) >> PIO_IMR_P31_Pos;
}

static inline void hri_pio_write_IMR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IDR = PIO_IMR_P31;
	} else {
		((Pio *)hw)->PIO_IER = PIO_IMR_P31;
	}
}

static inline void hri_pio_clear_IMR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IDR = PIO_IMR_P31;
}

static inline void hri_pio_set_IMR_reg(const void *const hw, hri_pio_imr_reg_t mask)
{
	((Pio *)hw)->PIO_IER = mask;
}

static inline hri_pio_imr_reg_t hri_pio_get_IMR_reg(const void *const hw, hri_pio_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_imr_reg_t hri_pio_read_IMR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_IMR;
}

static inline void hri_pio_write_IMR_reg(const void *const hw, hri_pio_imr_reg_t data)
{
	((Pio *)hw)->PIO_IER = data;
	((Pio *)hw)->PIO_IDR = ~data;
}

static inline void hri_pio_clear_IMR_reg(const void *const hw, hri_pio_imr_reg_t mask)
{
	((Pio *)hw)->PIO_IDR = mask;
}

static inline void hri_pio_set_MDSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P0;
}

static inline bool hri_pio_get_MDSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P0) >> PIO_MDSR_P0_Pos;
}

static inline void hri_pio_write_MDSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P0;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P0;
	}
}

static inline void hri_pio_clear_MDSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P0;
}

static inline void hri_pio_set_MDSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P1;
}

static inline bool hri_pio_get_MDSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P1) >> PIO_MDSR_P1_Pos;
}

static inline void hri_pio_write_MDSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P1;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P1;
	}
}

static inline void hri_pio_clear_MDSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P1;
}

static inline void hri_pio_set_MDSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P2;
}

static inline bool hri_pio_get_MDSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P2) >> PIO_MDSR_P2_Pos;
}

static inline void hri_pio_write_MDSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P2;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P2;
	}
}

static inline void hri_pio_clear_MDSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P2;
}

static inline void hri_pio_set_MDSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P3;
}

static inline bool hri_pio_get_MDSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P3) >> PIO_MDSR_P3_Pos;
}

static inline void hri_pio_write_MDSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P3;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P3;
	}
}

static inline void hri_pio_clear_MDSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P3;
}

static inline void hri_pio_set_MDSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P4;
}

static inline bool hri_pio_get_MDSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P4) >> PIO_MDSR_P4_Pos;
}

static inline void hri_pio_write_MDSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P4;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P4;
	}
}

static inline void hri_pio_clear_MDSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P4;
}

static inline void hri_pio_set_MDSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P5;
}

static inline bool hri_pio_get_MDSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P5) >> PIO_MDSR_P5_Pos;
}

static inline void hri_pio_write_MDSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P5;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P5;
	}
}

static inline void hri_pio_clear_MDSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P5;
}

static inline void hri_pio_set_MDSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P6;
}

static inline bool hri_pio_get_MDSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P6) >> PIO_MDSR_P6_Pos;
}

static inline void hri_pio_write_MDSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P6;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P6;
	}
}

static inline void hri_pio_clear_MDSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P6;
}

static inline void hri_pio_set_MDSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P7;
}

static inline bool hri_pio_get_MDSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P7) >> PIO_MDSR_P7_Pos;
}

static inline void hri_pio_write_MDSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P7;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P7;
	}
}

static inline void hri_pio_clear_MDSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P7;
}

static inline void hri_pio_set_MDSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P8;
}

static inline bool hri_pio_get_MDSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P8) >> PIO_MDSR_P8_Pos;
}

static inline void hri_pio_write_MDSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P8;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P8;
	}
}

static inline void hri_pio_clear_MDSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P8;
}

static inline void hri_pio_set_MDSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P9;
}

static inline bool hri_pio_get_MDSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P9) >> PIO_MDSR_P9_Pos;
}

static inline void hri_pio_write_MDSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P9;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P9;
	}
}

static inline void hri_pio_clear_MDSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P9;
}

static inline void hri_pio_set_MDSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P10;
}

static inline bool hri_pio_get_MDSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P10) >> PIO_MDSR_P10_Pos;
}

static inline void hri_pio_write_MDSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P10;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P10;
	}
}

static inline void hri_pio_clear_MDSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P10;
}

static inline void hri_pio_set_MDSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P11;
}

static inline bool hri_pio_get_MDSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P11) >> PIO_MDSR_P11_Pos;
}

static inline void hri_pio_write_MDSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P11;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P11;
	}
}

static inline void hri_pio_clear_MDSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P11;
}

static inline void hri_pio_set_MDSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P12;
}

static inline bool hri_pio_get_MDSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P12) >> PIO_MDSR_P12_Pos;
}

static inline void hri_pio_write_MDSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P12;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P12;
	}
}

static inline void hri_pio_clear_MDSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P12;
}

static inline void hri_pio_set_MDSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P13;
}

static inline bool hri_pio_get_MDSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P13) >> PIO_MDSR_P13_Pos;
}

static inline void hri_pio_write_MDSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P13;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P13;
	}
}

static inline void hri_pio_clear_MDSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P13;
}

static inline void hri_pio_set_MDSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P14;
}

static inline bool hri_pio_get_MDSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P14) >> PIO_MDSR_P14_Pos;
}

static inline void hri_pio_write_MDSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P14;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P14;
	}
}

static inline void hri_pio_clear_MDSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P14;
}

static inline void hri_pio_set_MDSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P15;
}

static inline bool hri_pio_get_MDSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P15) >> PIO_MDSR_P15_Pos;
}

static inline void hri_pio_write_MDSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P15;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P15;
	}
}

static inline void hri_pio_clear_MDSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P15;
}

static inline void hri_pio_set_MDSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P16;
}

static inline bool hri_pio_get_MDSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P16) >> PIO_MDSR_P16_Pos;
}

static inline void hri_pio_write_MDSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P16;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P16;
	}
}

static inline void hri_pio_clear_MDSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P16;
}

static inline void hri_pio_set_MDSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P17;
}

static inline bool hri_pio_get_MDSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P17) >> PIO_MDSR_P17_Pos;
}

static inline void hri_pio_write_MDSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P17;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P17;
	}
}

static inline void hri_pio_clear_MDSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P17;
}

static inline void hri_pio_set_MDSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P18;
}

static inline bool hri_pio_get_MDSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P18) >> PIO_MDSR_P18_Pos;
}

static inline void hri_pio_write_MDSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P18;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P18;
	}
}

static inline void hri_pio_clear_MDSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P18;
}

static inline void hri_pio_set_MDSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P19;
}

static inline bool hri_pio_get_MDSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P19) >> PIO_MDSR_P19_Pos;
}

static inline void hri_pio_write_MDSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P19;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P19;
	}
}

static inline void hri_pio_clear_MDSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P19;
}

static inline void hri_pio_set_MDSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P20;
}

static inline bool hri_pio_get_MDSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P20) >> PIO_MDSR_P20_Pos;
}

static inline void hri_pio_write_MDSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P20;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P20;
	}
}

static inline void hri_pio_clear_MDSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P20;
}

static inline void hri_pio_set_MDSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P21;
}

static inline bool hri_pio_get_MDSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P21) >> PIO_MDSR_P21_Pos;
}

static inline void hri_pio_write_MDSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P21;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P21;
	}
}

static inline void hri_pio_clear_MDSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P21;
}

static inline void hri_pio_set_MDSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P22;
}

static inline bool hri_pio_get_MDSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P22) >> PIO_MDSR_P22_Pos;
}

static inline void hri_pio_write_MDSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P22;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P22;
	}
}

static inline void hri_pio_clear_MDSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P22;
}

static inline void hri_pio_set_MDSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P23;
}

static inline bool hri_pio_get_MDSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P23) >> PIO_MDSR_P23_Pos;
}

static inline void hri_pio_write_MDSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P23;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P23;
	}
}

static inline void hri_pio_clear_MDSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P23;
}

static inline void hri_pio_set_MDSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P24;
}

static inline bool hri_pio_get_MDSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P24) >> PIO_MDSR_P24_Pos;
}

static inline void hri_pio_write_MDSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P24;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P24;
	}
}

static inline void hri_pio_clear_MDSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P24;
}

static inline void hri_pio_set_MDSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P25;
}

static inline bool hri_pio_get_MDSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P25) >> PIO_MDSR_P25_Pos;
}

static inline void hri_pio_write_MDSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P25;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P25;
	}
}

static inline void hri_pio_clear_MDSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P25;
}

static inline void hri_pio_set_MDSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P26;
}

static inline bool hri_pio_get_MDSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P26) >> PIO_MDSR_P26_Pos;
}

static inline void hri_pio_write_MDSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P26;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P26;
	}
}

static inline void hri_pio_clear_MDSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P26;
}

static inline void hri_pio_set_MDSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P27;
}

static inline bool hri_pio_get_MDSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P27) >> PIO_MDSR_P27_Pos;
}

static inline void hri_pio_write_MDSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P27;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P27;
	}
}

static inline void hri_pio_clear_MDSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P27;
}

static inline void hri_pio_set_MDSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P28;
}

static inline bool hri_pio_get_MDSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P28) >> PIO_MDSR_P28_Pos;
}

static inline void hri_pio_write_MDSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P28;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P28;
	}
}

static inline void hri_pio_clear_MDSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P28;
}

static inline void hri_pio_set_MDSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P29;
}

static inline bool hri_pio_get_MDSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P29) >> PIO_MDSR_P29_Pos;
}

static inline void hri_pio_write_MDSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P29;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P29;
	}
}

static inline void hri_pio_clear_MDSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P29;
}

static inline void hri_pio_set_MDSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P30;
}

static inline bool hri_pio_get_MDSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P30) >> PIO_MDSR_P30_Pos;
}

static inline void hri_pio_write_MDSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P30;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P30;
	}
}

static inline void hri_pio_clear_MDSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P30;
}

static inline void hri_pio_set_MDSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDER = PIO_MDSR_P31;
}

static inline bool hri_pio_get_MDSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_MDSR & PIO_MDSR_P31) >> PIO_MDSR_P31_Pos;
}

static inline void hri_pio_write_MDSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_MDDR = PIO_MDSR_P31;
	} else {
		((Pio *)hw)->PIO_MDER = PIO_MDSR_P31;
	}
}

static inline void hri_pio_clear_MDSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_MDDR = PIO_MDSR_P31;
}

static inline void hri_pio_set_MDSR_reg(const void *const hw, hri_pio_mdsr_reg_t mask)
{
	((Pio *)hw)->PIO_MDER = mask;
}

static inline hri_pio_mdsr_reg_t hri_pio_get_MDSR_reg(const void *const hw, hri_pio_mdsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_MDSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_mdsr_reg_t hri_pio_read_MDSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_MDSR;
}

static inline void hri_pio_write_MDSR_reg(const void *const hw, hri_pio_mdsr_reg_t data)
{
	((Pio *)hw)->PIO_MDER = data;
	((Pio *)hw)->PIO_MDDR = ~data;
}

static inline void hri_pio_clear_MDSR_reg(const void *const hw, hri_pio_mdsr_reg_t mask)
{
	((Pio *)hw)->PIO_MDDR = mask;
}

static inline void hri_pio_set_PUSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P0;
}

static inline bool hri_pio_get_PUSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P0) >> PIO_PUSR_P0_Pos;
}

static inline void hri_pio_write_PUSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P0;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P0;
	}
}

static inline void hri_pio_clear_PUSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P0;
}

static inline void hri_pio_set_PUSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P1;
}

static inline bool hri_pio_get_PUSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P1) >> PIO_PUSR_P1_Pos;
}

static inline void hri_pio_write_PUSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P1;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P1;
	}
}

static inline void hri_pio_clear_PUSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P1;
}

static inline void hri_pio_set_PUSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P2;
}

static inline bool hri_pio_get_PUSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P2) >> PIO_PUSR_P2_Pos;
}

static inline void hri_pio_write_PUSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P2;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P2;
	}
}

static inline void hri_pio_clear_PUSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P2;
}

static inline void hri_pio_set_PUSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P3;
}

static inline bool hri_pio_get_PUSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P3) >> PIO_PUSR_P3_Pos;
}

static inline void hri_pio_write_PUSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P3;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P3;
	}
}

static inline void hri_pio_clear_PUSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P3;
}

static inline void hri_pio_set_PUSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P4;
}

static inline bool hri_pio_get_PUSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P4) >> PIO_PUSR_P4_Pos;
}

static inline void hri_pio_write_PUSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P4;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P4;
	}
}

static inline void hri_pio_clear_PUSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P4;
}

static inline void hri_pio_set_PUSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P5;
}

static inline bool hri_pio_get_PUSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P5) >> PIO_PUSR_P5_Pos;
}

static inline void hri_pio_write_PUSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P5;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P5;
	}
}

static inline void hri_pio_clear_PUSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P5;
}

static inline void hri_pio_set_PUSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P6;
}

static inline bool hri_pio_get_PUSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P6) >> PIO_PUSR_P6_Pos;
}

static inline void hri_pio_write_PUSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P6;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P6;
	}
}

static inline void hri_pio_clear_PUSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P6;
}

static inline void hri_pio_set_PUSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P7;
}

static inline bool hri_pio_get_PUSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P7) >> PIO_PUSR_P7_Pos;
}

static inline void hri_pio_write_PUSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P7;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P7;
	}
}

static inline void hri_pio_clear_PUSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P7;
}

static inline void hri_pio_set_PUSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P8;
}

static inline bool hri_pio_get_PUSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P8) >> PIO_PUSR_P8_Pos;
}

static inline void hri_pio_write_PUSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P8;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P8;
	}
}

static inline void hri_pio_clear_PUSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P8;
}

static inline void hri_pio_set_PUSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P9;
}

static inline bool hri_pio_get_PUSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P9) >> PIO_PUSR_P9_Pos;
}

static inline void hri_pio_write_PUSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P9;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P9;
	}
}

static inline void hri_pio_clear_PUSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P9;
}

static inline void hri_pio_set_PUSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P10;
}

static inline bool hri_pio_get_PUSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P10) >> PIO_PUSR_P10_Pos;
}

static inline void hri_pio_write_PUSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P10;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P10;
	}
}

static inline void hri_pio_clear_PUSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P10;
}

static inline void hri_pio_set_PUSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P11;
}

static inline bool hri_pio_get_PUSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P11) >> PIO_PUSR_P11_Pos;
}

static inline void hri_pio_write_PUSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P11;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P11;
	}
}

static inline void hri_pio_clear_PUSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P11;
}

static inline void hri_pio_set_PUSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P12;
}

static inline bool hri_pio_get_PUSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P12) >> PIO_PUSR_P12_Pos;
}

static inline void hri_pio_write_PUSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P12;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P12;
	}
}

static inline void hri_pio_clear_PUSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P12;
}

static inline void hri_pio_set_PUSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P13;
}

static inline bool hri_pio_get_PUSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P13) >> PIO_PUSR_P13_Pos;
}

static inline void hri_pio_write_PUSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P13;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P13;
	}
}

static inline void hri_pio_clear_PUSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P13;
}

static inline void hri_pio_set_PUSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P14;
}

static inline bool hri_pio_get_PUSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P14) >> PIO_PUSR_P14_Pos;
}

static inline void hri_pio_write_PUSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P14;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P14;
	}
}

static inline void hri_pio_clear_PUSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P14;
}

static inline void hri_pio_set_PUSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P15;
}

static inline bool hri_pio_get_PUSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P15) >> PIO_PUSR_P15_Pos;
}

static inline void hri_pio_write_PUSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P15;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P15;
	}
}

static inline void hri_pio_clear_PUSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P15;
}

static inline void hri_pio_set_PUSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P16;
}

static inline bool hri_pio_get_PUSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P16) >> PIO_PUSR_P16_Pos;
}

static inline void hri_pio_write_PUSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P16;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P16;
	}
}

static inline void hri_pio_clear_PUSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P16;
}

static inline void hri_pio_set_PUSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P17;
}

static inline bool hri_pio_get_PUSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P17) >> PIO_PUSR_P17_Pos;
}

static inline void hri_pio_write_PUSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P17;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P17;
	}
}

static inline void hri_pio_clear_PUSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P17;
}

static inline void hri_pio_set_PUSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P18;
}

static inline bool hri_pio_get_PUSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P18) >> PIO_PUSR_P18_Pos;
}

static inline void hri_pio_write_PUSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P18;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P18;
	}
}

static inline void hri_pio_clear_PUSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P18;
}

static inline void hri_pio_set_PUSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P19;
}

static inline bool hri_pio_get_PUSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P19) >> PIO_PUSR_P19_Pos;
}

static inline void hri_pio_write_PUSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P19;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P19;
	}
}

static inline void hri_pio_clear_PUSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P19;
}

static inline void hri_pio_set_PUSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P20;
}

static inline bool hri_pio_get_PUSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P20) >> PIO_PUSR_P20_Pos;
}

static inline void hri_pio_write_PUSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P20;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P20;
	}
}

static inline void hri_pio_clear_PUSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P20;
}

static inline void hri_pio_set_PUSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P21;
}

static inline bool hri_pio_get_PUSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P21) >> PIO_PUSR_P21_Pos;
}

static inline void hri_pio_write_PUSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P21;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P21;
	}
}

static inline void hri_pio_clear_PUSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P21;
}

static inline void hri_pio_set_PUSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P22;
}

static inline bool hri_pio_get_PUSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P22) >> PIO_PUSR_P22_Pos;
}

static inline void hri_pio_write_PUSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P22;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P22;
	}
}

static inline void hri_pio_clear_PUSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P22;
}

static inline void hri_pio_set_PUSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P23;
}

static inline bool hri_pio_get_PUSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P23) >> PIO_PUSR_P23_Pos;
}

static inline void hri_pio_write_PUSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P23;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P23;
	}
}

static inline void hri_pio_clear_PUSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P23;
}

static inline void hri_pio_set_PUSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P24;
}

static inline bool hri_pio_get_PUSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P24) >> PIO_PUSR_P24_Pos;
}

static inline void hri_pio_write_PUSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P24;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P24;
	}
}

static inline void hri_pio_clear_PUSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P24;
}

static inline void hri_pio_set_PUSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P25;
}

static inline bool hri_pio_get_PUSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P25) >> PIO_PUSR_P25_Pos;
}

static inline void hri_pio_write_PUSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P25;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P25;
	}
}

static inline void hri_pio_clear_PUSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P25;
}

static inline void hri_pio_set_PUSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P26;
}

static inline bool hri_pio_get_PUSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P26) >> PIO_PUSR_P26_Pos;
}

static inline void hri_pio_write_PUSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P26;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P26;
	}
}

static inline void hri_pio_clear_PUSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P26;
}

static inline void hri_pio_set_PUSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P27;
}

static inline bool hri_pio_get_PUSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P27) >> PIO_PUSR_P27_Pos;
}

static inline void hri_pio_write_PUSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P27;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P27;
	}
}

static inline void hri_pio_clear_PUSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P27;
}

static inline void hri_pio_set_PUSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P28;
}

static inline bool hri_pio_get_PUSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P28) >> PIO_PUSR_P28_Pos;
}

static inline void hri_pio_write_PUSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P28;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P28;
	}
}

static inline void hri_pio_clear_PUSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P28;
}

static inline void hri_pio_set_PUSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P29;
}

static inline bool hri_pio_get_PUSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P29) >> PIO_PUSR_P29_Pos;
}

static inline void hri_pio_write_PUSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P29;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P29;
	}
}

static inline void hri_pio_clear_PUSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P29;
}

static inline void hri_pio_set_PUSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P30;
}

static inline bool hri_pio_get_PUSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P30) >> PIO_PUSR_P30_Pos;
}

static inline void hri_pio_write_PUSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P30;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P30;
	}
}

static inline void hri_pio_clear_PUSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P30;
}

static inline void hri_pio_set_PUSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUER = PIO_PUSR_P31;
}

static inline bool hri_pio_get_PUSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PUSR & PIO_PUSR_P31) >> PIO_PUSR_P31_Pos;
}

static inline void hri_pio_write_PUSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PUDR = PIO_PUSR_P31;
	} else {
		((Pio *)hw)->PIO_PUER = PIO_PUSR_P31;
	}
}

static inline void hri_pio_clear_PUSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PUDR = PIO_PUSR_P31;
}

static inline void hri_pio_set_PUSR_reg(const void *const hw, hri_pio_pusr_reg_t mask)
{
	((Pio *)hw)->PIO_PUER = mask;
}

static inline hri_pio_pusr_reg_t hri_pio_get_PUSR_reg(const void *const hw, hri_pio_pusr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PUSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_pusr_reg_t hri_pio_read_PUSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_PUSR;
}

static inline void hri_pio_write_PUSR_reg(const void *const hw, hri_pio_pusr_reg_t data)
{
	((Pio *)hw)->PIO_PUER = data;
	((Pio *)hw)->PIO_PUDR = ~data;
}

static inline void hri_pio_clear_PUSR_reg(const void *const hw, hri_pio_pusr_reg_t mask)
{
	((Pio *)hw)->PIO_PUDR = mask;
}

static inline void hri_pio_set_IFSCSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P0;
}

static inline bool hri_pio_get_IFSCSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P0) >> PIO_IFSCSR_P0_Pos;
}

static inline void hri_pio_write_IFSCSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P0;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P0;
	}
}

static inline void hri_pio_clear_IFSCSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P0;
}

static inline void hri_pio_set_IFSCSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P1;
}

static inline bool hri_pio_get_IFSCSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P1) >> PIO_IFSCSR_P1_Pos;
}

static inline void hri_pio_write_IFSCSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P1;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P1;
	}
}

static inline void hri_pio_clear_IFSCSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P1;
}

static inline void hri_pio_set_IFSCSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P2;
}

static inline bool hri_pio_get_IFSCSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P2) >> PIO_IFSCSR_P2_Pos;
}

static inline void hri_pio_write_IFSCSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P2;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P2;
	}
}

static inline void hri_pio_clear_IFSCSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P2;
}

static inline void hri_pio_set_IFSCSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P3;
}

static inline bool hri_pio_get_IFSCSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P3) >> PIO_IFSCSR_P3_Pos;
}

static inline void hri_pio_write_IFSCSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P3;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P3;
	}
}

static inline void hri_pio_clear_IFSCSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P3;
}

static inline void hri_pio_set_IFSCSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P4;
}

static inline bool hri_pio_get_IFSCSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P4) >> PIO_IFSCSR_P4_Pos;
}

static inline void hri_pio_write_IFSCSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P4;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P4;
	}
}

static inline void hri_pio_clear_IFSCSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P4;
}

static inline void hri_pio_set_IFSCSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P5;
}

static inline bool hri_pio_get_IFSCSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P5) >> PIO_IFSCSR_P5_Pos;
}

static inline void hri_pio_write_IFSCSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P5;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P5;
	}
}

static inline void hri_pio_clear_IFSCSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P5;
}

static inline void hri_pio_set_IFSCSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P6;
}

static inline bool hri_pio_get_IFSCSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P6) >> PIO_IFSCSR_P6_Pos;
}

static inline void hri_pio_write_IFSCSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P6;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P6;
	}
}

static inline void hri_pio_clear_IFSCSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P6;
}

static inline void hri_pio_set_IFSCSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P7;
}

static inline bool hri_pio_get_IFSCSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P7) >> PIO_IFSCSR_P7_Pos;
}

static inline void hri_pio_write_IFSCSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P7;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P7;
	}
}

static inline void hri_pio_clear_IFSCSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P7;
}

static inline void hri_pio_set_IFSCSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P8;
}

static inline bool hri_pio_get_IFSCSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P8) >> PIO_IFSCSR_P8_Pos;
}

static inline void hri_pio_write_IFSCSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P8;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P8;
	}
}

static inline void hri_pio_clear_IFSCSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P8;
}

static inline void hri_pio_set_IFSCSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P9;
}

static inline bool hri_pio_get_IFSCSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P9) >> PIO_IFSCSR_P9_Pos;
}

static inline void hri_pio_write_IFSCSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P9;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P9;
	}
}

static inline void hri_pio_clear_IFSCSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P9;
}

static inline void hri_pio_set_IFSCSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P10;
}

static inline bool hri_pio_get_IFSCSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P10) >> PIO_IFSCSR_P10_Pos;
}

static inline void hri_pio_write_IFSCSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P10;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P10;
	}
}

static inline void hri_pio_clear_IFSCSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P10;
}

static inline void hri_pio_set_IFSCSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P11;
}

static inline bool hri_pio_get_IFSCSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P11) >> PIO_IFSCSR_P11_Pos;
}

static inline void hri_pio_write_IFSCSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P11;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P11;
	}
}

static inline void hri_pio_clear_IFSCSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P11;
}

static inline void hri_pio_set_IFSCSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P12;
}

static inline bool hri_pio_get_IFSCSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P12) >> PIO_IFSCSR_P12_Pos;
}

static inline void hri_pio_write_IFSCSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P12;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P12;
	}
}

static inline void hri_pio_clear_IFSCSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P12;
}

static inline void hri_pio_set_IFSCSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P13;
}

static inline bool hri_pio_get_IFSCSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P13) >> PIO_IFSCSR_P13_Pos;
}

static inline void hri_pio_write_IFSCSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P13;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P13;
	}
}

static inline void hri_pio_clear_IFSCSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P13;
}

static inline void hri_pio_set_IFSCSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P14;
}

static inline bool hri_pio_get_IFSCSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P14) >> PIO_IFSCSR_P14_Pos;
}

static inline void hri_pio_write_IFSCSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P14;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P14;
	}
}

static inline void hri_pio_clear_IFSCSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P14;
}

static inline void hri_pio_set_IFSCSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P15;
}

static inline bool hri_pio_get_IFSCSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P15) >> PIO_IFSCSR_P15_Pos;
}

static inline void hri_pio_write_IFSCSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P15;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P15;
	}
}

static inline void hri_pio_clear_IFSCSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P15;
}

static inline void hri_pio_set_IFSCSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P16;
}

static inline bool hri_pio_get_IFSCSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P16) >> PIO_IFSCSR_P16_Pos;
}

static inline void hri_pio_write_IFSCSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P16;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P16;
	}
}

static inline void hri_pio_clear_IFSCSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P16;
}

static inline void hri_pio_set_IFSCSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P17;
}

static inline bool hri_pio_get_IFSCSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P17) >> PIO_IFSCSR_P17_Pos;
}

static inline void hri_pio_write_IFSCSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P17;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P17;
	}
}

static inline void hri_pio_clear_IFSCSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P17;
}

static inline void hri_pio_set_IFSCSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P18;
}

static inline bool hri_pio_get_IFSCSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P18) >> PIO_IFSCSR_P18_Pos;
}

static inline void hri_pio_write_IFSCSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P18;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P18;
	}
}

static inline void hri_pio_clear_IFSCSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P18;
}

static inline void hri_pio_set_IFSCSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P19;
}

static inline bool hri_pio_get_IFSCSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P19) >> PIO_IFSCSR_P19_Pos;
}

static inline void hri_pio_write_IFSCSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P19;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P19;
	}
}

static inline void hri_pio_clear_IFSCSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P19;
}

static inline void hri_pio_set_IFSCSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P20;
}

static inline bool hri_pio_get_IFSCSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P20) >> PIO_IFSCSR_P20_Pos;
}

static inline void hri_pio_write_IFSCSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P20;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P20;
	}
}

static inline void hri_pio_clear_IFSCSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P20;
}

static inline void hri_pio_set_IFSCSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P21;
}

static inline bool hri_pio_get_IFSCSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P21) >> PIO_IFSCSR_P21_Pos;
}

static inline void hri_pio_write_IFSCSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P21;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P21;
	}
}

static inline void hri_pio_clear_IFSCSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P21;
}

static inline void hri_pio_set_IFSCSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P22;
}

static inline bool hri_pio_get_IFSCSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P22) >> PIO_IFSCSR_P22_Pos;
}

static inline void hri_pio_write_IFSCSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P22;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P22;
	}
}

static inline void hri_pio_clear_IFSCSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P22;
}

static inline void hri_pio_set_IFSCSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P23;
}

static inline bool hri_pio_get_IFSCSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P23) >> PIO_IFSCSR_P23_Pos;
}

static inline void hri_pio_write_IFSCSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P23;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P23;
	}
}

static inline void hri_pio_clear_IFSCSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P23;
}

static inline void hri_pio_set_IFSCSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P24;
}

static inline bool hri_pio_get_IFSCSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P24) >> PIO_IFSCSR_P24_Pos;
}

static inline void hri_pio_write_IFSCSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P24;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P24;
	}
}

static inline void hri_pio_clear_IFSCSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P24;
}

static inline void hri_pio_set_IFSCSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P25;
}

static inline bool hri_pio_get_IFSCSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P25) >> PIO_IFSCSR_P25_Pos;
}

static inline void hri_pio_write_IFSCSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P25;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P25;
	}
}

static inline void hri_pio_clear_IFSCSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P25;
}

static inline void hri_pio_set_IFSCSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P26;
}

static inline bool hri_pio_get_IFSCSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P26) >> PIO_IFSCSR_P26_Pos;
}

static inline void hri_pio_write_IFSCSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P26;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P26;
	}
}

static inline void hri_pio_clear_IFSCSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P26;
}

static inline void hri_pio_set_IFSCSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P27;
}

static inline bool hri_pio_get_IFSCSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P27) >> PIO_IFSCSR_P27_Pos;
}

static inline void hri_pio_write_IFSCSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P27;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P27;
	}
}

static inline void hri_pio_clear_IFSCSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P27;
}

static inline void hri_pio_set_IFSCSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P28;
}

static inline bool hri_pio_get_IFSCSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P28) >> PIO_IFSCSR_P28_Pos;
}

static inline void hri_pio_write_IFSCSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P28;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P28;
	}
}

static inline void hri_pio_clear_IFSCSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P28;
}

static inline void hri_pio_set_IFSCSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P29;
}

static inline bool hri_pio_get_IFSCSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P29) >> PIO_IFSCSR_P29_Pos;
}

static inline void hri_pio_write_IFSCSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P29;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P29;
	}
}

static inline void hri_pio_clear_IFSCSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P29;
}

static inline void hri_pio_set_IFSCSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P30;
}

static inline bool hri_pio_get_IFSCSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P30) >> PIO_IFSCSR_P30_Pos;
}

static inline void hri_pio_write_IFSCSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P30;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P30;
	}
}

static inline void hri_pio_clear_IFSCSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P30;
}

static inline void hri_pio_set_IFSCSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P31;
}

static inline bool hri_pio_get_IFSCSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_IFSCSR & PIO_IFSCSR_P31) >> PIO_IFSCSR_P31_Pos;
}

static inline void hri_pio_write_IFSCSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P31;
	} else {
		((Pio *)hw)->PIO_IFSCER = PIO_IFSCSR_P31;
	}
}

static inline void hri_pio_clear_IFSCSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_IFSCDR = PIO_IFSCSR_P31;
}

static inline void hri_pio_set_IFSCSR_reg(const void *const hw, hri_pio_ifscsr_reg_t mask)
{
	((Pio *)hw)->PIO_IFSCER = mask;
}

static inline hri_pio_ifscsr_reg_t hri_pio_get_IFSCSR_reg(const void *const hw, hri_pio_ifscsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_IFSCSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_ifscsr_reg_t hri_pio_read_IFSCSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_IFSCSR;
}

static inline void hri_pio_write_IFSCSR_reg(const void *const hw, hri_pio_ifscsr_reg_t data)
{
	((Pio *)hw)->PIO_IFSCER = data;
	((Pio *)hw)->PIO_IFSCDR = ~data;
}

static inline void hri_pio_clear_IFSCSR_reg(const void *const hw, hri_pio_ifscsr_reg_t mask)
{
	((Pio *)hw)->PIO_IFSCDR = mask;
}

static inline void hri_pio_set_PPDSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P0;
}

static inline bool hri_pio_get_PPDSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P0) >> PIO_PPDSR_P0_Pos;
}

static inline void hri_pio_write_PPDSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P0;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P0;
	}
}

static inline void hri_pio_clear_PPDSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P0;
}

static inline void hri_pio_set_PPDSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P1;
}

static inline bool hri_pio_get_PPDSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P1) >> PIO_PPDSR_P1_Pos;
}

static inline void hri_pio_write_PPDSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P1;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P1;
	}
}

static inline void hri_pio_clear_PPDSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P1;
}

static inline void hri_pio_set_PPDSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P2;
}

static inline bool hri_pio_get_PPDSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P2) >> PIO_PPDSR_P2_Pos;
}

static inline void hri_pio_write_PPDSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P2;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P2;
	}
}

static inline void hri_pio_clear_PPDSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P2;
}

static inline void hri_pio_set_PPDSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P3;
}

static inline bool hri_pio_get_PPDSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P3) >> PIO_PPDSR_P3_Pos;
}

static inline void hri_pio_write_PPDSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P3;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P3;
	}
}

static inline void hri_pio_clear_PPDSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P3;
}

static inline void hri_pio_set_PPDSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P4;
}

static inline bool hri_pio_get_PPDSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P4) >> PIO_PPDSR_P4_Pos;
}

static inline void hri_pio_write_PPDSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P4;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P4;
	}
}

static inline void hri_pio_clear_PPDSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P4;
}

static inline void hri_pio_set_PPDSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P5;
}

static inline bool hri_pio_get_PPDSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P5) >> PIO_PPDSR_P5_Pos;
}

static inline void hri_pio_write_PPDSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P5;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P5;
	}
}

static inline void hri_pio_clear_PPDSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P5;
}

static inline void hri_pio_set_PPDSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P6;
}

static inline bool hri_pio_get_PPDSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P6) >> PIO_PPDSR_P6_Pos;
}

static inline void hri_pio_write_PPDSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P6;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P6;
	}
}

static inline void hri_pio_clear_PPDSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P6;
}

static inline void hri_pio_set_PPDSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P7;
}

static inline bool hri_pio_get_PPDSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P7) >> PIO_PPDSR_P7_Pos;
}

static inline void hri_pio_write_PPDSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P7;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P7;
	}
}

static inline void hri_pio_clear_PPDSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P7;
}

static inline void hri_pio_set_PPDSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P8;
}

static inline bool hri_pio_get_PPDSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P8) >> PIO_PPDSR_P8_Pos;
}

static inline void hri_pio_write_PPDSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P8;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P8;
	}
}

static inline void hri_pio_clear_PPDSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P8;
}

static inline void hri_pio_set_PPDSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P9;
}

static inline bool hri_pio_get_PPDSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P9) >> PIO_PPDSR_P9_Pos;
}

static inline void hri_pio_write_PPDSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P9;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P9;
	}
}

static inline void hri_pio_clear_PPDSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P9;
}

static inline void hri_pio_set_PPDSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P10;
}

static inline bool hri_pio_get_PPDSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P10) >> PIO_PPDSR_P10_Pos;
}

static inline void hri_pio_write_PPDSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P10;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P10;
	}
}

static inline void hri_pio_clear_PPDSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P10;
}

static inline void hri_pio_set_PPDSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P11;
}

static inline bool hri_pio_get_PPDSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P11) >> PIO_PPDSR_P11_Pos;
}

static inline void hri_pio_write_PPDSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P11;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P11;
	}
}

static inline void hri_pio_clear_PPDSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P11;
}

static inline void hri_pio_set_PPDSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P12;
}

static inline bool hri_pio_get_PPDSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P12) >> PIO_PPDSR_P12_Pos;
}

static inline void hri_pio_write_PPDSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P12;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P12;
	}
}

static inline void hri_pio_clear_PPDSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P12;
}

static inline void hri_pio_set_PPDSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P13;
}

static inline bool hri_pio_get_PPDSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P13) >> PIO_PPDSR_P13_Pos;
}

static inline void hri_pio_write_PPDSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P13;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P13;
	}
}

static inline void hri_pio_clear_PPDSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P13;
}

static inline void hri_pio_set_PPDSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P14;
}

static inline bool hri_pio_get_PPDSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P14) >> PIO_PPDSR_P14_Pos;
}

static inline void hri_pio_write_PPDSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P14;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P14;
	}
}

static inline void hri_pio_clear_PPDSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P14;
}

static inline void hri_pio_set_PPDSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P15;
}

static inline bool hri_pio_get_PPDSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P15) >> PIO_PPDSR_P15_Pos;
}

static inline void hri_pio_write_PPDSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P15;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P15;
	}
}

static inline void hri_pio_clear_PPDSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P15;
}

static inline void hri_pio_set_PPDSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P16;
}

static inline bool hri_pio_get_PPDSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P16) >> PIO_PPDSR_P16_Pos;
}

static inline void hri_pio_write_PPDSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P16;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P16;
	}
}

static inline void hri_pio_clear_PPDSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P16;
}

static inline void hri_pio_set_PPDSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P17;
}

static inline bool hri_pio_get_PPDSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P17) >> PIO_PPDSR_P17_Pos;
}

static inline void hri_pio_write_PPDSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P17;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P17;
	}
}

static inline void hri_pio_clear_PPDSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P17;
}

static inline void hri_pio_set_PPDSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P18;
}

static inline bool hri_pio_get_PPDSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P18) >> PIO_PPDSR_P18_Pos;
}

static inline void hri_pio_write_PPDSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P18;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P18;
	}
}

static inline void hri_pio_clear_PPDSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P18;
}

static inline void hri_pio_set_PPDSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P19;
}

static inline bool hri_pio_get_PPDSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P19) >> PIO_PPDSR_P19_Pos;
}

static inline void hri_pio_write_PPDSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P19;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P19;
	}
}

static inline void hri_pio_clear_PPDSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P19;
}

static inline void hri_pio_set_PPDSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P20;
}

static inline bool hri_pio_get_PPDSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P20) >> PIO_PPDSR_P20_Pos;
}

static inline void hri_pio_write_PPDSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P20;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P20;
	}
}

static inline void hri_pio_clear_PPDSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P20;
}

static inline void hri_pio_set_PPDSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P21;
}

static inline bool hri_pio_get_PPDSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P21) >> PIO_PPDSR_P21_Pos;
}

static inline void hri_pio_write_PPDSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P21;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P21;
	}
}

static inline void hri_pio_clear_PPDSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P21;
}

static inline void hri_pio_set_PPDSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P22;
}

static inline bool hri_pio_get_PPDSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P22) >> PIO_PPDSR_P22_Pos;
}

static inline void hri_pio_write_PPDSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P22;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P22;
	}
}

static inline void hri_pio_clear_PPDSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P22;
}

static inline void hri_pio_set_PPDSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P23;
}

static inline bool hri_pio_get_PPDSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P23) >> PIO_PPDSR_P23_Pos;
}

static inline void hri_pio_write_PPDSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P23;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P23;
	}
}

static inline void hri_pio_clear_PPDSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P23;
}

static inline void hri_pio_set_PPDSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P24;
}

static inline bool hri_pio_get_PPDSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P24) >> PIO_PPDSR_P24_Pos;
}

static inline void hri_pio_write_PPDSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P24;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P24;
	}
}

static inline void hri_pio_clear_PPDSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P24;
}

static inline void hri_pio_set_PPDSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P25;
}

static inline bool hri_pio_get_PPDSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P25) >> PIO_PPDSR_P25_Pos;
}

static inline void hri_pio_write_PPDSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P25;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P25;
	}
}

static inline void hri_pio_clear_PPDSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P25;
}

static inline void hri_pio_set_PPDSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P26;
}

static inline bool hri_pio_get_PPDSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P26) >> PIO_PPDSR_P26_Pos;
}

static inline void hri_pio_write_PPDSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P26;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P26;
	}
}

static inline void hri_pio_clear_PPDSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P26;
}

static inline void hri_pio_set_PPDSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P27;
}

static inline bool hri_pio_get_PPDSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P27) >> PIO_PPDSR_P27_Pos;
}

static inline void hri_pio_write_PPDSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P27;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P27;
	}
}

static inline void hri_pio_clear_PPDSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P27;
}

static inline void hri_pio_set_PPDSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P28;
}

static inline bool hri_pio_get_PPDSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P28) >> PIO_PPDSR_P28_Pos;
}

static inline void hri_pio_write_PPDSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P28;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P28;
	}
}

static inline void hri_pio_clear_PPDSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P28;
}

static inline void hri_pio_set_PPDSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P29;
}

static inline bool hri_pio_get_PPDSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P29) >> PIO_PPDSR_P29_Pos;
}

static inline void hri_pio_write_PPDSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P29;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P29;
	}
}

static inline void hri_pio_clear_PPDSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P29;
}

static inline void hri_pio_set_PPDSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P30;
}

static inline bool hri_pio_get_PPDSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P30) >> PIO_PPDSR_P30_Pos;
}

static inline void hri_pio_write_PPDSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P30;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P30;
	}
}

static inline void hri_pio_clear_PPDSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P30;
}

static inline void hri_pio_set_PPDSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P31;
}

static inline bool hri_pio_get_PPDSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PPDSR & PIO_PPDSR_P31) >> PIO_PPDSR_P31_Pos;
}

static inline void hri_pio_write_PPDSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P31;
	} else {
		((Pio *)hw)->PIO_PPDER = PIO_PPDSR_P31;
	}
}

static inline void hri_pio_clear_PPDSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_PPDDR = PIO_PPDSR_P31;
}

static inline void hri_pio_set_PPDSR_reg(const void *const hw, hri_pio_ppdsr_reg_t mask)
{
	((Pio *)hw)->PIO_PPDER = mask;
}

static inline hri_pio_ppdsr_reg_t hri_pio_get_PPDSR_reg(const void *const hw, hri_pio_ppdsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PPDSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_ppdsr_reg_t hri_pio_read_PPDSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_PPDSR;
}

static inline void hri_pio_write_PPDSR_reg(const void *const hw, hri_pio_ppdsr_reg_t data)
{
	((Pio *)hw)->PIO_PPDER = data;
	((Pio *)hw)->PIO_PPDDR = ~data;
}

static inline void hri_pio_clear_PPDSR_reg(const void *const hw, hri_pio_ppdsr_reg_t mask)
{
	((Pio *)hw)->PIO_PPDDR = mask;
}

static inline void hri_pio_set_OWSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P0;
}

static inline bool hri_pio_get_OWSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P0) >> PIO_OWSR_P0_Pos;
}

static inline void hri_pio_write_OWSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P0;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P0;
	}
}

static inline void hri_pio_clear_OWSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P0;
}

static inline void hri_pio_set_OWSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P1;
}

static inline bool hri_pio_get_OWSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P1) >> PIO_OWSR_P1_Pos;
}

static inline void hri_pio_write_OWSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P1;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P1;
	}
}

static inline void hri_pio_clear_OWSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P1;
}

static inline void hri_pio_set_OWSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P2;
}

static inline bool hri_pio_get_OWSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P2) >> PIO_OWSR_P2_Pos;
}

static inline void hri_pio_write_OWSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P2;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P2;
	}
}

static inline void hri_pio_clear_OWSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P2;
}

static inline void hri_pio_set_OWSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P3;
}

static inline bool hri_pio_get_OWSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P3) >> PIO_OWSR_P3_Pos;
}

static inline void hri_pio_write_OWSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P3;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P3;
	}
}

static inline void hri_pio_clear_OWSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P3;
}

static inline void hri_pio_set_OWSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P4;
}

static inline bool hri_pio_get_OWSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P4) >> PIO_OWSR_P4_Pos;
}

static inline void hri_pio_write_OWSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P4;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P4;
	}
}

static inline void hri_pio_clear_OWSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P4;
}

static inline void hri_pio_set_OWSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P5;
}

static inline bool hri_pio_get_OWSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P5) >> PIO_OWSR_P5_Pos;
}

static inline void hri_pio_write_OWSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P5;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P5;
	}
}

static inline void hri_pio_clear_OWSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P5;
}

static inline void hri_pio_set_OWSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P6;
}

static inline bool hri_pio_get_OWSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P6) >> PIO_OWSR_P6_Pos;
}

static inline void hri_pio_write_OWSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P6;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P6;
	}
}

static inline void hri_pio_clear_OWSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P6;
}

static inline void hri_pio_set_OWSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P7;
}

static inline bool hri_pio_get_OWSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P7) >> PIO_OWSR_P7_Pos;
}

static inline void hri_pio_write_OWSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P7;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P7;
	}
}

static inline void hri_pio_clear_OWSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P7;
}

static inline void hri_pio_set_OWSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P8;
}

static inline bool hri_pio_get_OWSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P8) >> PIO_OWSR_P8_Pos;
}

static inline void hri_pio_write_OWSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P8;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P8;
	}
}

static inline void hri_pio_clear_OWSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P8;
}

static inline void hri_pio_set_OWSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P9;
}

static inline bool hri_pio_get_OWSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P9) >> PIO_OWSR_P9_Pos;
}

static inline void hri_pio_write_OWSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P9;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P9;
	}
}

static inline void hri_pio_clear_OWSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P9;
}

static inline void hri_pio_set_OWSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P10;
}

static inline bool hri_pio_get_OWSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P10) >> PIO_OWSR_P10_Pos;
}

static inline void hri_pio_write_OWSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P10;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P10;
	}
}

static inline void hri_pio_clear_OWSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P10;
}

static inline void hri_pio_set_OWSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P11;
}

static inline bool hri_pio_get_OWSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P11) >> PIO_OWSR_P11_Pos;
}

static inline void hri_pio_write_OWSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P11;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P11;
	}
}

static inline void hri_pio_clear_OWSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P11;
}

static inline void hri_pio_set_OWSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P12;
}

static inline bool hri_pio_get_OWSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P12) >> PIO_OWSR_P12_Pos;
}

static inline void hri_pio_write_OWSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P12;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P12;
	}
}

static inline void hri_pio_clear_OWSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P12;
}

static inline void hri_pio_set_OWSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P13;
}

static inline bool hri_pio_get_OWSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P13) >> PIO_OWSR_P13_Pos;
}

static inline void hri_pio_write_OWSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P13;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P13;
	}
}

static inline void hri_pio_clear_OWSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P13;
}

static inline void hri_pio_set_OWSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P14;
}

static inline bool hri_pio_get_OWSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P14) >> PIO_OWSR_P14_Pos;
}

static inline void hri_pio_write_OWSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P14;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P14;
	}
}

static inline void hri_pio_clear_OWSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P14;
}

static inline void hri_pio_set_OWSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P15;
}

static inline bool hri_pio_get_OWSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P15) >> PIO_OWSR_P15_Pos;
}

static inline void hri_pio_write_OWSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P15;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P15;
	}
}

static inline void hri_pio_clear_OWSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P15;
}

static inline void hri_pio_set_OWSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P16;
}

static inline bool hri_pio_get_OWSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P16) >> PIO_OWSR_P16_Pos;
}

static inline void hri_pio_write_OWSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P16;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P16;
	}
}

static inline void hri_pio_clear_OWSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P16;
}

static inline void hri_pio_set_OWSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P17;
}

static inline bool hri_pio_get_OWSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P17) >> PIO_OWSR_P17_Pos;
}

static inline void hri_pio_write_OWSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P17;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P17;
	}
}

static inline void hri_pio_clear_OWSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P17;
}

static inline void hri_pio_set_OWSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P18;
}

static inline bool hri_pio_get_OWSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P18) >> PIO_OWSR_P18_Pos;
}

static inline void hri_pio_write_OWSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P18;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P18;
	}
}

static inline void hri_pio_clear_OWSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P18;
}

static inline void hri_pio_set_OWSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P19;
}

static inline bool hri_pio_get_OWSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P19) >> PIO_OWSR_P19_Pos;
}

static inline void hri_pio_write_OWSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P19;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P19;
	}
}

static inline void hri_pio_clear_OWSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P19;
}

static inline void hri_pio_set_OWSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P20;
}

static inline bool hri_pio_get_OWSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P20) >> PIO_OWSR_P20_Pos;
}

static inline void hri_pio_write_OWSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P20;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P20;
	}
}

static inline void hri_pio_clear_OWSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P20;
}

static inline void hri_pio_set_OWSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P21;
}

static inline bool hri_pio_get_OWSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P21) >> PIO_OWSR_P21_Pos;
}

static inline void hri_pio_write_OWSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P21;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P21;
	}
}

static inline void hri_pio_clear_OWSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P21;
}

static inline void hri_pio_set_OWSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P22;
}

static inline bool hri_pio_get_OWSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P22) >> PIO_OWSR_P22_Pos;
}

static inline void hri_pio_write_OWSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P22;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P22;
	}
}

static inline void hri_pio_clear_OWSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P22;
}

static inline void hri_pio_set_OWSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P23;
}

static inline bool hri_pio_get_OWSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P23) >> PIO_OWSR_P23_Pos;
}

static inline void hri_pio_write_OWSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P23;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P23;
	}
}

static inline void hri_pio_clear_OWSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P23;
}

static inline void hri_pio_set_OWSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P24;
}

static inline bool hri_pio_get_OWSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P24) >> PIO_OWSR_P24_Pos;
}

static inline void hri_pio_write_OWSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P24;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P24;
	}
}

static inline void hri_pio_clear_OWSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P24;
}

static inline void hri_pio_set_OWSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P25;
}

static inline bool hri_pio_get_OWSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P25) >> PIO_OWSR_P25_Pos;
}

static inline void hri_pio_write_OWSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P25;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P25;
	}
}

static inline void hri_pio_clear_OWSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P25;
}

static inline void hri_pio_set_OWSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P26;
}

static inline bool hri_pio_get_OWSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P26) >> PIO_OWSR_P26_Pos;
}

static inline void hri_pio_write_OWSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P26;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P26;
	}
}

static inline void hri_pio_clear_OWSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P26;
}

static inline void hri_pio_set_OWSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P27;
}

static inline bool hri_pio_get_OWSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P27) >> PIO_OWSR_P27_Pos;
}

static inline void hri_pio_write_OWSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P27;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P27;
	}
}

static inline void hri_pio_clear_OWSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P27;
}

static inline void hri_pio_set_OWSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P28;
}

static inline bool hri_pio_get_OWSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P28) >> PIO_OWSR_P28_Pos;
}

static inline void hri_pio_write_OWSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P28;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P28;
	}
}

static inline void hri_pio_clear_OWSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P28;
}

static inline void hri_pio_set_OWSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P29;
}

static inline bool hri_pio_get_OWSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P29) >> PIO_OWSR_P29_Pos;
}

static inline void hri_pio_write_OWSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P29;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P29;
	}
}

static inline void hri_pio_clear_OWSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P29;
}

static inline void hri_pio_set_OWSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P30;
}

static inline bool hri_pio_get_OWSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P30) >> PIO_OWSR_P30_Pos;
}

static inline void hri_pio_write_OWSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P30;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P30;
	}
}

static inline void hri_pio_clear_OWSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P30;
}

static inline void hri_pio_set_OWSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWER = PIO_OWSR_P31;
}

static inline bool hri_pio_get_OWSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_OWSR & PIO_OWSR_P31) >> PIO_OWSR_P31_Pos;
}

static inline void hri_pio_write_OWSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_OWDR = PIO_OWSR_P31;
	} else {
		((Pio *)hw)->PIO_OWER = PIO_OWSR_P31;
	}
}

static inline void hri_pio_clear_OWSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_OWDR = PIO_OWSR_P31;
}

static inline void hri_pio_set_OWSR_reg(const void *const hw, hri_pio_owsr_reg_t mask)
{
	((Pio *)hw)->PIO_OWER = mask;
}

static inline hri_pio_owsr_reg_t hri_pio_get_OWSR_reg(const void *const hw, hri_pio_owsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_OWSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_owsr_reg_t hri_pio_read_OWSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_OWSR;
}

static inline void hri_pio_write_OWSR_reg(const void *const hw, hri_pio_owsr_reg_t data)
{
	((Pio *)hw)->PIO_OWER = data;
	((Pio *)hw)->PIO_OWDR = ~data;
}

static inline void hri_pio_clear_OWSR_reg(const void *const hw, hri_pio_owsr_reg_t mask)
{
	((Pio *)hw)->PIO_OWDR = mask;
}

static inline void hri_pio_set_AIMMR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P0;
}

static inline bool hri_pio_get_AIMMR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P0) >> PIO_AIMMR_P0_Pos;
}

static inline void hri_pio_write_AIMMR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P0;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P0;
	}
}

static inline void hri_pio_clear_AIMMR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P0;
}

static inline void hri_pio_set_AIMMR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P1;
}

static inline bool hri_pio_get_AIMMR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P1) >> PIO_AIMMR_P1_Pos;
}

static inline void hri_pio_write_AIMMR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P1;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P1;
	}
}

static inline void hri_pio_clear_AIMMR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P1;
}

static inline void hri_pio_set_AIMMR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P2;
}

static inline bool hri_pio_get_AIMMR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P2) >> PIO_AIMMR_P2_Pos;
}

static inline void hri_pio_write_AIMMR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P2;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P2;
	}
}

static inline void hri_pio_clear_AIMMR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P2;
}

static inline void hri_pio_set_AIMMR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P3;
}

static inline bool hri_pio_get_AIMMR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P3) >> PIO_AIMMR_P3_Pos;
}

static inline void hri_pio_write_AIMMR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P3;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P3;
	}
}

static inline void hri_pio_clear_AIMMR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P3;
}

static inline void hri_pio_set_AIMMR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P4;
}

static inline bool hri_pio_get_AIMMR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P4) >> PIO_AIMMR_P4_Pos;
}

static inline void hri_pio_write_AIMMR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P4;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P4;
	}
}

static inline void hri_pio_clear_AIMMR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P4;
}

static inline void hri_pio_set_AIMMR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P5;
}

static inline bool hri_pio_get_AIMMR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P5) >> PIO_AIMMR_P5_Pos;
}

static inline void hri_pio_write_AIMMR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P5;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P5;
	}
}

static inline void hri_pio_clear_AIMMR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P5;
}

static inline void hri_pio_set_AIMMR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P6;
}

static inline bool hri_pio_get_AIMMR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P6) >> PIO_AIMMR_P6_Pos;
}

static inline void hri_pio_write_AIMMR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P6;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P6;
	}
}

static inline void hri_pio_clear_AIMMR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P6;
}

static inline void hri_pio_set_AIMMR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P7;
}

static inline bool hri_pio_get_AIMMR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P7) >> PIO_AIMMR_P7_Pos;
}

static inline void hri_pio_write_AIMMR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P7;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P7;
	}
}

static inline void hri_pio_clear_AIMMR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P7;
}

static inline void hri_pio_set_AIMMR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P8;
}

static inline bool hri_pio_get_AIMMR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P8) >> PIO_AIMMR_P8_Pos;
}

static inline void hri_pio_write_AIMMR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P8;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P8;
	}
}

static inline void hri_pio_clear_AIMMR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P8;
}

static inline void hri_pio_set_AIMMR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P9;
}

static inline bool hri_pio_get_AIMMR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P9) >> PIO_AIMMR_P9_Pos;
}

static inline void hri_pio_write_AIMMR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P9;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P9;
	}
}

static inline void hri_pio_clear_AIMMR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P9;
}

static inline void hri_pio_set_AIMMR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P10;
}

static inline bool hri_pio_get_AIMMR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P10) >> PIO_AIMMR_P10_Pos;
}

static inline void hri_pio_write_AIMMR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P10;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P10;
	}
}

static inline void hri_pio_clear_AIMMR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P10;
}

static inline void hri_pio_set_AIMMR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P11;
}

static inline bool hri_pio_get_AIMMR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P11) >> PIO_AIMMR_P11_Pos;
}

static inline void hri_pio_write_AIMMR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P11;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P11;
	}
}

static inline void hri_pio_clear_AIMMR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P11;
}

static inline void hri_pio_set_AIMMR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P12;
}

static inline bool hri_pio_get_AIMMR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P12) >> PIO_AIMMR_P12_Pos;
}

static inline void hri_pio_write_AIMMR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P12;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P12;
	}
}

static inline void hri_pio_clear_AIMMR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P12;
}

static inline void hri_pio_set_AIMMR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P13;
}

static inline bool hri_pio_get_AIMMR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P13) >> PIO_AIMMR_P13_Pos;
}

static inline void hri_pio_write_AIMMR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P13;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P13;
	}
}

static inline void hri_pio_clear_AIMMR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P13;
}

static inline void hri_pio_set_AIMMR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P14;
}

static inline bool hri_pio_get_AIMMR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P14) >> PIO_AIMMR_P14_Pos;
}

static inline void hri_pio_write_AIMMR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P14;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P14;
	}
}

static inline void hri_pio_clear_AIMMR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P14;
}

static inline void hri_pio_set_AIMMR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P15;
}

static inline bool hri_pio_get_AIMMR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P15) >> PIO_AIMMR_P15_Pos;
}

static inline void hri_pio_write_AIMMR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P15;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P15;
	}
}

static inline void hri_pio_clear_AIMMR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P15;
}

static inline void hri_pio_set_AIMMR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P16;
}

static inline bool hri_pio_get_AIMMR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P16) >> PIO_AIMMR_P16_Pos;
}

static inline void hri_pio_write_AIMMR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P16;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P16;
	}
}

static inline void hri_pio_clear_AIMMR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P16;
}

static inline void hri_pio_set_AIMMR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P17;
}

static inline bool hri_pio_get_AIMMR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P17) >> PIO_AIMMR_P17_Pos;
}

static inline void hri_pio_write_AIMMR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P17;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P17;
	}
}

static inline void hri_pio_clear_AIMMR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P17;
}

static inline void hri_pio_set_AIMMR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P18;
}

static inline bool hri_pio_get_AIMMR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P18) >> PIO_AIMMR_P18_Pos;
}

static inline void hri_pio_write_AIMMR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P18;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P18;
	}
}

static inline void hri_pio_clear_AIMMR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P18;
}

static inline void hri_pio_set_AIMMR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P19;
}

static inline bool hri_pio_get_AIMMR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P19) >> PIO_AIMMR_P19_Pos;
}

static inline void hri_pio_write_AIMMR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P19;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P19;
	}
}

static inline void hri_pio_clear_AIMMR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P19;
}

static inline void hri_pio_set_AIMMR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P20;
}

static inline bool hri_pio_get_AIMMR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P20) >> PIO_AIMMR_P20_Pos;
}

static inline void hri_pio_write_AIMMR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P20;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P20;
	}
}

static inline void hri_pio_clear_AIMMR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P20;
}

static inline void hri_pio_set_AIMMR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P21;
}

static inline bool hri_pio_get_AIMMR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P21) >> PIO_AIMMR_P21_Pos;
}

static inline void hri_pio_write_AIMMR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P21;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P21;
	}
}

static inline void hri_pio_clear_AIMMR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P21;
}

static inline void hri_pio_set_AIMMR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P22;
}

static inline bool hri_pio_get_AIMMR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P22) >> PIO_AIMMR_P22_Pos;
}

static inline void hri_pio_write_AIMMR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P22;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P22;
	}
}

static inline void hri_pio_clear_AIMMR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P22;
}

static inline void hri_pio_set_AIMMR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P23;
}

static inline bool hri_pio_get_AIMMR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P23) >> PIO_AIMMR_P23_Pos;
}

static inline void hri_pio_write_AIMMR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P23;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P23;
	}
}

static inline void hri_pio_clear_AIMMR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P23;
}

static inline void hri_pio_set_AIMMR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P24;
}

static inline bool hri_pio_get_AIMMR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P24) >> PIO_AIMMR_P24_Pos;
}

static inline void hri_pio_write_AIMMR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P24;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P24;
	}
}

static inline void hri_pio_clear_AIMMR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P24;
}

static inline void hri_pio_set_AIMMR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P25;
}

static inline bool hri_pio_get_AIMMR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P25) >> PIO_AIMMR_P25_Pos;
}

static inline void hri_pio_write_AIMMR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P25;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P25;
	}
}

static inline void hri_pio_clear_AIMMR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P25;
}

static inline void hri_pio_set_AIMMR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P26;
}

static inline bool hri_pio_get_AIMMR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P26) >> PIO_AIMMR_P26_Pos;
}

static inline void hri_pio_write_AIMMR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P26;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P26;
	}
}

static inline void hri_pio_clear_AIMMR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P26;
}

static inline void hri_pio_set_AIMMR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P27;
}

static inline bool hri_pio_get_AIMMR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P27) >> PIO_AIMMR_P27_Pos;
}

static inline void hri_pio_write_AIMMR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P27;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P27;
	}
}

static inline void hri_pio_clear_AIMMR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P27;
}

static inline void hri_pio_set_AIMMR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P28;
}

static inline bool hri_pio_get_AIMMR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P28) >> PIO_AIMMR_P28_Pos;
}

static inline void hri_pio_write_AIMMR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P28;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P28;
	}
}

static inline void hri_pio_clear_AIMMR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P28;
}

static inline void hri_pio_set_AIMMR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P29;
}

static inline bool hri_pio_get_AIMMR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P29) >> PIO_AIMMR_P29_Pos;
}

static inline void hri_pio_write_AIMMR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P29;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P29;
	}
}

static inline void hri_pio_clear_AIMMR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P29;
}

static inline void hri_pio_set_AIMMR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P30;
}

static inline bool hri_pio_get_AIMMR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P30) >> PIO_AIMMR_P30_Pos;
}

static inline void hri_pio_write_AIMMR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P30;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P30;
	}
}

static inline void hri_pio_clear_AIMMR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P30;
}

static inline void hri_pio_set_AIMMR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P31;
}

static inline bool hri_pio_get_AIMMR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_AIMMR & PIO_AIMMR_P31) >> PIO_AIMMR_P31_Pos;
}

static inline void hri_pio_write_AIMMR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P31;
	} else {
		((Pio *)hw)->PIO_AIMER = PIO_AIMMR_P31;
	}
}

static inline void hri_pio_clear_AIMMR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_AIMDR = PIO_AIMMR_P31;
}

static inline void hri_pio_set_AIMMR_reg(const void *const hw, hri_pio_aimmr_reg_t mask)
{
	((Pio *)hw)->PIO_AIMER = mask;
}

static inline hri_pio_aimmr_reg_t hri_pio_get_AIMMR_reg(const void *const hw, hri_pio_aimmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_AIMMR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_aimmr_reg_t hri_pio_read_AIMMR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_AIMMR;
}

static inline void hri_pio_write_AIMMR_reg(const void *const hw, hri_pio_aimmr_reg_t data)
{
	((Pio *)hw)->PIO_AIMER = data;
	((Pio *)hw)->PIO_AIMDR = ~data;
}

static inline void hri_pio_clear_AIMMR_reg(const void *const hw, hri_pio_aimmr_reg_t mask)
{
	((Pio *)hw)->PIO_AIMDR = mask;
}

static inline void hri_pio_set_ELSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P0;
}

static inline bool hri_pio_get_ELSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P0) >> PIO_ELSR_P0_Pos;
}

static inline void hri_pio_write_ELSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P0;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P0;
	}
}

static inline void hri_pio_clear_ELSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P0;
}

static inline void hri_pio_set_ELSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P1;
}

static inline bool hri_pio_get_ELSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P1) >> PIO_ELSR_P1_Pos;
}

static inline void hri_pio_write_ELSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P1;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P1;
	}
}

static inline void hri_pio_clear_ELSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P1;
}

static inline void hri_pio_set_ELSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P2;
}

static inline bool hri_pio_get_ELSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P2) >> PIO_ELSR_P2_Pos;
}

static inline void hri_pio_write_ELSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P2;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P2;
	}
}

static inline void hri_pio_clear_ELSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P2;
}

static inline void hri_pio_set_ELSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P3;
}

static inline bool hri_pio_get_ELSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P3) >> PIO_ELSR_P3_Pos;
}

static inline void hri_pio_write_ELSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P3;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P3;
	}
}

static inline void hri_pio_clear_ELSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P3;
}

static inline void hri_pio_set_ELSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P4;
}

static inline bool hri_pio_get_ELSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P4) >> PIO_ELSR_P4_Pos;
}

static inline void hri_pio_write_ELSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P4;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P4;
	}
}

static inline void hri_pio_clear_ELSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P4;
}

static inline void hri_pio_set_ELSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P5;
}

static inline bool hri_pio_get_ELSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P5) >> PIO_ELSR_P5_Pos;
}

static inline void hri_pio_write_ELSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P5;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P5;
	}
}

static inline void hri_pio_clear_ELSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P5;
}

static inline void hri_pio_set_ELSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P6;
}

static inline bool hri_pio_get_ELSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P6) >> PIO_ELSR_P6_Pos;
}

static inline void hri_pio_write_ELSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P6;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P6;
	}
}

static inline void hri_pio_clear_ELSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P6;
}

static inline void hri_pio_set_ELSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P7;
}

static inline bool hri_pio_get_ELSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P7) >> PIO_ELSR_P7_Pos;
}

static inline void hri_pio_write_ELSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P7;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P7;
	}
}

static inline void hri_pio_clear_ELSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P7;
}

static inline void hri_pio_set_ELSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P8;
}

static inline bool hri_pio_get_ELSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P8) >> PIO_ELSR_P8_Pos;
}

static inline void hri_pio_write_ELSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P8;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P8;
	}
}

static inline void hri_pio_clear_ELSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P8;
}

static inline void hri_pio_set_ELSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P9;
}

static inline bool hri_pio_get_ELSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P9) >> PIO_ELSR_P9_Pos;
}

static inline void hri_pio_write_ELSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P9;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P9;
	}
}

static inline void hri_pio_clear_ELSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P9;
}

static inline void hri_pio_set_ELSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P10;
}

static inline bool hri_pio_get_ELSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P10) >> PIO_ELSR_P10_Pos;
}

static inline void hri_pio_write_ELSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P10;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P10;
	}
}

static inline void hri_pio_clear_ELSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P10;
}

static inline void hri_pio_set_ELSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P11;
}

static inline bool hri_pio_get_ELSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P11) >> PIO_ELSR_P11_Pos;
}

static inline void hri_pio_write_ELSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P11;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P11;
	}
}

static inline void hri_pio_clear_ELSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P11;
}

static inline void hri_pio_set_ELSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P12;
}

static inline bool hri_pio_get_ELSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P12) >> PIO_ELSR_P12_Pos;
}

static inline void hri_pio_write_ELSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P12;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P12;
	}
}

static inline void hri_pio_clear_ELSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P12;
}

static inline void hri_pio_set_ELSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P13;
}

static inline bool hri_pio_get_ELSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P13) >> PIO_ELSR_P13_Pos;
}

static inline void hri_pio_write_ELSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P13;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P13;
	}
}

static inline void hri_pio_clear_ELSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P13;
}

static inline void hri_pio_set_ELSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P14;
}

static inline bool hri_pio_get_ELSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P14) >> PIO_ELSR_P14_Pos;
}

static inline void hri_pio_write_ELSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P14;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P14;
	}
}

static inline void hri_pio_clear_ELSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P14;
}

static inline void hri_pio_set_ELSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P15;
}

static inline bool hri_pio_get_ELSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P15) >> PIO_ELSR_P15_Pos;
}

static inline void hri_pio_write_ELSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P15;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P15;
	}
}

static inline void hri_pio_clear_ELSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P15;
}

static inline void hri_pio_set_ELSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P16;
}

static inline bool hri_pio_get_ELSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P16) >> PIO_ELSR_P16_Pos;
}

static inline void hri_pio_write_ELSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P16;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P16;
	}
}

static inline void hri_pio_clear_ELSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P16;
}

static inline void hri_pio_set_ELSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P17;
}

static inline bool hri_pio_get_ELSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P17) >> PIO_ELSR_P17_Pos;
}

static inline void hri_pio_write_ELSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P17;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P17;
	}
}

static inline void hri_pio_clear_ELSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P17;
}

static inline void hri_pio_set_ELSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P18;
}

static inline bool hri_pio_get_ELSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P18) >> PIO_ELSR_P18_Pos;
}

static inline void hri_pio_write_ELSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P18;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P18;
	}
}

static inline void hri_pio_clear_ELSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P18;
}

static inline void hri_pio_set_ELSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P19;
}

static inline bool hri_pio_get_ELSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P19) >> PIO_ELSR_P19_Pos;
}

static inline void hri_pio_write_ELSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P19;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P19;
	}
}

static inline void hri_pio_clear_ELSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P19;
}

static inline void hri_pio_set_ELSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P20;
}

static inline bool hri_pio_get_ELSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P20) >> PIO_ELSR_P20_Pos;
}

static inline void hri_pio_write_ELSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P20;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P20;
	}
}

static inline void hri_pio_clear_ELSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P20;
}

static inline void hri_pio_set_ELSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P21;
}

static inline bool hri_pio_get_ELSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P21) >> PIO_ELSR_P21_Pos;
}

static inline void hri_pio_write_ELSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P21;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P21;
	}
}

static inline void hri_pio_clear_ELSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P21;
}

static inline void hri_pio_set_ELSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P22;
}

static inline bool hri_pio_get_ELSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P22) >> PIO_ELSR_P22_Pos;
}

static inline void hri_pio_write_ELSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P22;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P22;
	}
}

static inline void hri_pio_clear_ELSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P22;
}

static inline void hri_pio_set_ELSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P23;
}

static inline bool hri_pio_get_ELSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P23) >> PIO_ELSR_P23_Pos;
}

static inline void hri_pio_write_ELSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P23;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P23;
	}
}

static inline void hri_pio_clear_ELSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P23;
}

static inline void hri_pio_set_ELSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P24;
}

static inline bool hri_pio_get_ELSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P24) >> PIO_ELSR_P24_Pos;
}

static inline void hri_pio_write_ELSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P24;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P24;
	}
}

static inline void hri_pio_clear_ELSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P24;
}

static inline void hri_pio_set_ELSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P25;
}

static inline bool hri_pio_get_ELSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P25) >> PIO_ELSR_P25_Pos;
}

static inline void hri_pio_write_ELSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P25;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P25;
	}
}

static inline void hri_pio_clear_ELSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P25;
}

static inline void hri_pio_set_ELSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P26;
}

static inline bool hri_pio_get_ELSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P26) >> PIO_ELSR_P26_Pos;
}

static inline void hri_pio_write_ELSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P26;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P26;
	}
}

static inline void hri_pio_clear_ELSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P26;
}

static inline void hri_pio_set_ELSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P27;
}

static inline bool hri_pio_get_ELSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P27) >> PIO_ELSR_P27_Pos;
}

static inline void hri_pio_write_ELSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P27;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P27;
	}
}

static inline void hri_pio_clear_ELSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P27;
}

static inline void hri_pio_set_ELSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P28;
}

static inline bool hri_pio_get_ELSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P28) >> PIO_ELSR_P28_Pos;
}

static inline void hri_pio_write_ELSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P28;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P28;
	}
}

static inline void hri_pio_clear_ELSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P28;
}

static inline void hri_pio_set_ELSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P29;
}

static inline bool hri_pio_get_ELSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P29) >> PIO_ELSR_P29_Pos;
}

static inline void hri_pio_write_ELSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P29;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P29;
	}
}

static inline void hri_pio_clear_ELSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P29;
}

static inline void hri_pio_set_ELSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P30;
}

static inline bool hri_pio_get_ELSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P30) >> PIO_ELSR_P30_Pos;
}

static inline void hri_pio_write_ELSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P30;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P30;
	}
}

static inline void hri_pio_clear_ELSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P30;
}

static inline void hri_pio_set_ELSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_LSR = PIO_ELSR_P31;
}

static inline bool hri_pio_get_ELSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_ELSR & PIO_ELSR_P31) >> PIO_ELSR_P31_Pos;
}

static inline void hri_pio_write_ELSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_ESR = PIO_ELSR_P31;
	} else {
		((Pio *)hw)->PIO_LSR = PIO_ELSR_P31;
	}
}

static inline void hri_pio_clear_ELSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_ESR = PIO_ELSR_P31;
}

static inline void hri_pio_set_ELSR_reg(const void *const hw, hri_pio_elsr_reg_t mask)
{
	((Pio *)hw)->PIO_LSR = mask;
}

static inline hri_pio_elsr_reg_t hri_pio_get_ELSR_reg(const void *const hw, hri_pio_elsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ELSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_elsr_reg_t hri_pio_read_ELSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_ELSR;
}

static inline void hri_pio_write_ELSR_reg(const void *const hw, hri_pio_elsr_reg_t data)
{
	((Pio *)hw)->PIO_LSR = data;
	((Pio *)hw)->PIO_ESR = ~data;
}

static inline void hri_pio_clear_ELSR_reg(const void *const hw, hri_pio_elsr_reg_t mask)
{
	((Pio *)hw)->PIO_ESR = mask;
}

static inline void hri_pio_set_FRLHSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P0;
}

static inline bool hri_pio_get_FRLHSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P0) >> PIO_FRLHSR_P0_Pos;
}

static inline void hri_pio_write_FRLHSR_P0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P0;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P0;
	}
}

static inline void hri_pio_clear_FRLHSR_P0_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P0;
}

static inline void hri_pio_set_FRLHSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P1;
}

static inline bool hri_pio_get_FRLHSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P1) >> PIO_FRLHSR_P1_Pos;
}

static inline void hri_pio_write_FRLHSR_P1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P1;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P1;
	}
}

static inline void hri_pio_clear_FRLHSR_P1_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P1;
}

static inline void hri_pio_set_FRLHSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P2;
}

static inline bool hri_pio_get_FRLHSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P2) >> PIO_FRLHSR_P2_Pos;
}

static inline void hri_pio_write_FRLHSR_P2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P2;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P2;
	}
}

static inline void hri_pio_clear_FRLHSR_P2_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P2;
}

static inline void hri_pio_set_FRLHSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P3;
}

static inline bool hri_pio_get_FRLHSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P3) >> PIO_FRLHSR_P3_Pos;
}

static inline void hri_pio_write_FRLHSR_P3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P3;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P3;
	}
}

static inline void hri_pio_clear_FRLHSR_P3_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P3;
}

static inline void hri_pio_set_FRLHSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P4;
}

static inline bool hri_pio_get_FRLHSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P4) >> PIO_FRLHSR_P4_Pos;
}

static inline void hri_pio_write_FRLHSR_P4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P4;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P4;
	}
}

static inline void hri_pio_clear_FRLHSR_P4_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P4;
}

static inline void hri_pio_set_FRLHSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P5;
}

static inline bool hri_pio_get_FRLHSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P5) >> PIO_FRLHSR_P5_Pos;
}

static inline void hri_pio_write_FRLHSR_P5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P5;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P5;
	}
}

static inline void hri_pio_clear_FRLHSR_P5_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P5;
}

static inline void hri_pio_set_FRLHSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P6;
}

static inline bool hri_pio_get_FRLHSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P6) >> PIO_FRLHSR_P6_Pos;
}

static inline void hri_pio_write_FRLHSR_P6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P6;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P6;
	}
}

static inline void hri_pio_clear_FRLHSR_P6_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P6;
}

static inline void hri_pio_set_FRLHSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P7;
}

static inline bool hri_pio_get_FRLHSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P7) >> PIO_FRLHSR_P7_Pos;
}

static inline void hri_pio_write_FRLHSR_P7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P7;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P7;
	}
}

static inline void hri_pio_clear_FRLHSR_P7_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P7;
}

static inline void hri_pio_set_FRLHSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P8;
}

static inline bool hri_pio_get_FRLHSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P8) >> PIO_FRLHSR_P8_Pos;
}

static inline void hri_pio_write_FRLHSR_P8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P8;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P8;
	}
}

static inline void hri_pio_clear_FRLHSR_P8_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P8;
}

static inline void hri_pio_set_FRLHSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P9;
}

static inline bool hri_pio_get_FRLHSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P9) >> PIO_FRLHSR_P9_Pos;
}

static inline void hri_pio_write_FRLHSR_P9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P9;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P9;
	}
}

static inline void hri_pio_clear_FRLHSR_P9_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P9;
}

static inline void hri_pio_set_FRLHSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P10;
}

static inline bool hri_pio_get_FRLHSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P10) >> PIO_FRLHSR_P10_Pos;
}

static inline void hri_pio_write_FRLHSR_P10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P10;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P10;
	}
}

static inline void hri_pio_clear_FRLHSR_P10_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P10;
}

static inline void hri_pio_set_FRLHSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P11;
}

static inline bool hri_pio_get_FRLHSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P11) >> PIO_FRLHSR_P11_Pos;
}

static inline void hri_pio_write_FRLHSR_P11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P11;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P11;
	}
}

static inline void hri_pio_clear_FRLHSR_P11_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P11;
}

static inline void hri_pio_set_FRLHSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P12;
}

static inline bool hri_pio_get_FRLHSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P12) >> PIO_FRLHSR_P12_Pos;
}

static inline void hri_pio_write_FRLHSR_P12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P12;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P12;
	}
}

static inline void hri_pio_clear_FRLHSR_P12_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P12;
}

static inline void hri_pio_set_FRLHSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P13;
}

static inline bool hri_pio_get_FRLHSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P13) >> PIO_FRLHSR_P13_Pos;
}

static inline void hri_pio_write_FRLHSR_P13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P13;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P13;
	}
}

static inline void hri_pio_clear_FRLHSR_P13_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P13;
}

static inline void hri_pio_set_FRLHSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P14;
}

static inline bool hri_pio_get_FRLHSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P14) >> PIO_FRLHSR_P14_Pos;
}

static inline void hri_pio_write_FRLHSR_P14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P14;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P14;
	}
}

static inline void hri_pio_clear_FRLHSR_P14_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P14;
}

static inline void hri_pio_set_FRLHSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P15;
}

static inline bool hri_pio_get_FRLHSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P15) >> PIO_FRLHSR_P15_Pos;
}

static inline void hri_pio_write_FRLHSR_P15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P15;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P15;
	}
}

static inline void hri_pio_clear_FRLHSR_P15_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P15;
}

static inline void hri_pio_set_FRLHSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P16;
}

static inline bool hri_pio_get_FRLHSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P16) >> PIO_FRLHSR_P16_Pos;
}

static inline void hri_pio_write_FRLHSR_P16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P16;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P16;
	}
}

static inline void hri_pio_clear_FRLHSR_P16_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P16;
}

static inline void hri_pio_set_FRLHSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P17;
}

static inline bool hri_pio_get_FRLHSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P17) >> PIO_FRLHSR_P17_Pos;
}

static inline void hri_pio_write_FRLHSR_P17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P17;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P17;
	}
}

static inline void hri_pio_clear_FRLHSR_P17_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P17;
}

static inline void hri_pio_set_FRLHSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P18;
}

static inline bool hri_pio_get_FRLHSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P18) >> PIO_FRLHSR_P18_Pos;
}

static inline void hri_pio_write_FRLHSR_P18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P18;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P18;
	}
}

static inline void hri_pio_clear_FRLHSR_P18_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P18;
}

static inline void hri_pio_set_FRLHSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P19;
}

static inline bool hri_pio_get_FRLHSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P19) >> PIO_FRLHSR_P19_Pos;
}

static inline void hri_pio_write_FRLHSR_P19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P19;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P19;
	}
}

static inline void hri_pio_clear_FRLHSR_P19_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P19;
}

static inline void hri_pio_set_FRLHSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P20;
}

static inline bool hri_pio_get_FRLHSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P20) >> PIO_FRLHSR_P20_Pos;
}

static inline void hri_pio_write_FRLHSR_P20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P20;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P20;
	}
}

static inline void hri_pio_clear_FRLHSR_P20_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P20;
}

static inline void hri_pio_set_FRLHSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P21;
}

static inline bool hri_pio_get_FRLHSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P21) >> PIO_FRLHSR_P21_Pos;
}

static inline void hri_pio_write_FRLHSR_P21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P21;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P21;
	}
}

static inline void hri_pio_clear_FRLHSR_P21_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P21;
}

static inline void hri_pio_set_FRLHSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P22;
}

static inline bool hri_pio_get_FRLHSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P22) >> PIO_FRLHSR_P22_Pos;
}

static inline void hri_pio_write_FRLHSR_P22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P22;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P22;
	}
}

static inline void hri_pio_clear_FRLHSR_P22_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P22;
}

static inline void hri_pio_set_FRLHSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P23;
}

static inline bool hri_pio_get_FRLHSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P23) >> PIO_FRLHSR_P23_Pos;
}

static inline void hri_pio_write_FRLHSR_P23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P23;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P23;
	}
}

static inline void hri_pio_clear_FRLHSR_P23_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P23;
}

static inline void hri_pio_set_FRLHSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P24;
}

static inline bool hri_pio_get_FRLHSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P24) >> PIO_FRLHSR_P24_Pos;
}

static inline void hri_pio_write_FRLHSR_P24_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P24;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P24;
	}
}

static inline void hri_pio_clear_FRLHSR_P24_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P24;
}

static inline void hri_pio_set_FRLHSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P25;
}

static inline bool hri_pio_get_FRLHSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P25) >> PIO_FRLHSR_P25_Pos;
}

static inline void hri_pio_write_FRLHSR_P25_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P25;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P25;
	}
}

static inline void hri_pio_clear_FRLHSR_P25_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P25;
}

static inline void hri_pio_set_FRLHSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P26;
}

static inline bool hri_pio_get_FRLHSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P26) >> PIO_FRLHSR_P26_Pos;
}

static inline void hri_pio_write_FRLHSR_P26_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P26;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P26;
	}
}

static inline void hri_pio_clear_FRLHSR_P26_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P26;
}

static inline void hri_pio_set_FRLHSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P27;
}

static inline bool hri_pio_get_FRLHSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P27) >> PIO_FRLHSR_P27_Pos;
}

static inline void hri_pio_write_FRLHSR_P27_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P27;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P27;
	}
}

static inline void hri_pio_clear_FRLHSR_P27_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P27;
}

static inline void hri_pio_set_FRLHSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P28;
}

static inline bool hri_pio_get_FRLHSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P28) >> PIO_FRLHSR_P28_Pos;
}

static inline void hri_pio_write_FRLHSR_P28_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P28;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P28;
	}
}

static inline void hri_pio_clear_FRLHSR_P28_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P28;
}

static inline void hri_pio_set_FRLHSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P29;
}

static inline bool hri_pio_get_FRLHSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P29) >> PIO_FRLHSR_P29_Pos;
}

static inline void hri_pio_write_FRLHSR_P29_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P29;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P29;
	}
}

static inline void hri_pio_clear_FRLHSR_P29_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P29;
}

static inline void hri_pio_set_FRLHSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P30;
}

static inline bool hri_pio_get_FRLHSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P30) >> PIO_FRLHSR_P30_Pos;
}

static inline void hri_pio_write_FRLHSR_P30_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P30;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P30;
	}
}

static inline void hri_pio_clear_FRLHSR_P30_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P30;
}

static inline void hri_pio_set_FRLHSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P31;
}

static inline bool hri_pio_get_FRLHSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_FRLHSR & PIO_FRLHSR_P31) >> PIO_FRLHSR_P31_Pos;
}

static inline void hri_pio_write_FRLHSR_P31_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P31;
	} else {
		((Pio *)hw)->PIO_REHLSR = PIO_FRLHSR_P31;
	}
}

static inline void hri_pio_clear_FRLHSR_P31_bit(const void *const hw)
{
	((Pio *)hw)->PIO_FELLSR = PIO_FRLHSR_P31;
}

static inline void hri_pio_set_FRLHSR_reg(const void *const hw, hri_pio_frlhsr_reg_t mask)
{
	((Pio *)hw)->PIO_REHLSR = mask;
}

static inline hri_pio_frlhsr_reg_t hri_pio_get_FRLHSR_reg(const void *const hw, hri_pio_frlhsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_FRLHSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_frlhsr_reg_t hri_pio_read_FRLHSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_FRLHSR;
}

static inline void hri_pio_write_FRLHSR_reg(const void *const hw, hri_pio_frlhsr_reg_t data)
{
	((Pio *)hw)->PIO_REHLSR = data;
	((Pio *)hw)->PIO_FELLSR = ~data;
}

static inline void hri_pio_clear_FRLHSR_reg(const void *const hw, hri_pio_frlhsr_reg_t mask)
{
	((Pio *)hw)->PIO_FELLSR = mask;
}

static inline bool hri_pio_get_PDSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P0) > 0;
}

static inline bool hri_pio_get_PDSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P1) > 0;
}

static inline bool hri_pio_get_PDSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P2) > 0;
}

static inline bool hri_pio_get_PDSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P3) > 0;
}

static inline bool hri_pio_get_PDSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P4) > 0;
}

static inline bool hri_pio_get_PDSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P5) > 0;
}

static inline bool hri_pio_get_PDSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P6) > 0;
}

static inline bool hri_pio_get_PDSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P7) > 0;
}

static inline bool hri_pio_get_PDSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P8) > 0;
}

static inline bool hri_pio_get_PDSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P9) > 0;
}

static inline bool hri_pio_get_PDSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P10) > 0;
}

static inline bool hri_pio_get_PDSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P11) > 0;
}

static inline bool hri_pio_get_PDSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P12) > 0;
}

static inline bool hri_pio_get_PDSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P13) > 0;
}

static inline bool hri_pio_get_PDSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P14) > 0;
}

static inline bool hri_pio_get_PDSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P15) > 0;
}

static inline bool hri_pio_get_PDSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P16) > 0;
}

static inline bool hri_pio_get_PDSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P17) > 0;
}

static inline bool hri_pio_get_PDSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P18) > 0;
}

static inline bool hri_pio_get_PDSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P19) > 0;
}

static inline bool hri_pio_get_PDSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P20) > 0;
}

static inline bool hri_pio_get_PDSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P21) > 0;
}

static inline bool hri_pio_get_PDSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P22) > 0;
}

static inline bool hri_pio_get_PDSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P23) > 0;
}

static inline bool hri_pio_get_PDSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P24) > 0;
}

static inline bool hri_pio_get_PDSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P25) > 0;
}

static inline bool hri_pio_get_PDSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P26) > 0;
}

static inline bool hri_pio_get_PDSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P27) > 0;
}

static inline bool hri_pio_get_PDSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P28) > 0;
}

static inline bool hri_pio_get_PDSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P29) > 0;
}

static inline bool hri_pio_get_PDSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P30) > 0;
}

static inline bool hri_pio_get_PDSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PDSR & PIO_PDSR_P31) > 0;
}

static inline hri_pio_pdsr_reg_t hri_pio_get_PDSR_reg(const void *const hw, hri_pio_pdsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PDSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_pdsr_reg_t hri_pio_read_PDSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_PDSR;
}

static inline bool hri_pio_get_LOCKSR_P0_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P0) > 0;
}

static inline bool hri_pio_get_LOCKSR_P1_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P1) > 0;
}

static inline bool hri_pio_get_LOCKSR_P2_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P2) > 0;
}

static inline bool hri_pio_get_LOCKSR_P3_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P3) > 0;
}

static inline bool hri_pio_get_LOCKSR_P4_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P4) > 0;
}

static inline bool hri_pio_get_LOCKSR_P5_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P5) > 0;
}

static inline bool hri_pio_get_LOCKSR_P6_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P6) > 0;
}

static inline bool hri_pio_get_LOCKSR_P7_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P7) > 0;
}

static inline bool hri_pio_get_LOCKSR_P8_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P8) > 0;
}

static inline bool hri_pio_get_LOCKSR_P9_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P9) > 0;
}

static inline bool hri_pio_get_LOCKSR_P10_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P10) > 0;
}

static inline bool hri_pio_get_LOCKSR_P11_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P11) > 0;
}

static inline bool hri_pio_get_LOCKSR_P12_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P12) > 0;
}

static inline bool hri_pio_get_LOCKSR_P13_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P13) > 0;
}

static inline bool hri_pio_get_LOCKSR_P14_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P14) > 0;
}

static inline bool hri_pio_get_LOCKSR_P15_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P15) > 0;
}

static inline bool hri_pio_get_LOCKSR_P16_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P16) > 0;
}

static inline bool hri_pio_get_LOCKSR_P17_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P17) > 0;
}

static inline bool hri_pio_get_LOCKSR_P18_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P18) > 0;
}

static inline bool hri_pio_get_LOCKSR_P19_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P19) > 0;
}

static inline bool hri_pio_get_LOCKSR_P20_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P20) > 0;
}

static inline bool hri_pio_get_LOCKSR_P21_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P21) > 0;
}

static inline bool hri_pio_get_LOCKSR_P22_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P22) > 0;
}

static inline bool hri_pio_get_LOCKSR_P23_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P23) > 0;
}

static inline bool hri_pio_get_LOCKSR_P24_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P24) > 0;
}

static inline bool hri_pio_get_LOCKSR_P25_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P25) > 0;
}

static inline bool hri_pio_get_LOCKSR_P26_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P26) > 0;
}

static inline bool hri_pio_get_LOCKSR_P27_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P27) > 0;
}

static inline bool hri_pio_get_LOCKSR_P28_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P28) > 0;
}

static inline bool hri_pio_get_LOCKSR_P29_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P29) > 0;
}

static inline bool hri_pio_get_LOCKSR_P30_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P30) > 0;
}

static inline bool hri_pio_get_LOCKSR_P31_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_LOCKSR & PIO_LOCKSR_P31) > 0;
}

static inline hri_pio_locksr_reg_t hri_pio_get_LOCKSR_reg(const void *const hw, hri_pio_locksr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_LOCKSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_locksr_reg_t hri_pio_read_LOCKSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_LOCKSR;
}

static inline bool hri_pio_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_WPSR & PIO_WPSR_WPVS) > 0;
}

static inline hri_pio_wpsr_reg_t hri_pio_get_WPSR_WPVSRC_bf(const void *const hw, hri_pio_wpsr_reg_t mask)
{
	return (((Pio *)hw)->PIO_WPSR & PIO_WPSR_WPVSRC(mask)) >> PIO_WPSR_WPVSRC_Pos;
}

static inline hri_pio_wpsr_reg_t hri_pio_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Pio *)hw)->PIO_WPSR & PIO_WPSR_WPVSRC_Msk) >> PIO_WPSR_WPVSRC_Pos;
}

static inline hri_pio_wpsr_reg_t hri_pio_get_WPSR_reg(const void *const hw, hri_pio_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_wpsr_reg_t hri_pio_read_WPSR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_WPSR;
}

static inline bool hri_pio_get_PCIMR_DRDY_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PCIMR & PIO_PCIMR_DRDY) > 0;
}

static inline bool hri_pio_get_PCIMR_OVRE_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PCIMR & PIO_PCIMR_OVRE) > 0;
}

static inline bool hri_pio_get_PCIMR_ENDRX_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PCIMR & PIO_PCIMR_ENDRX) > 0;
}

static inline bool hri_pio_get_PCIMR_RXBUFF_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PCIMR & PIO_PCIMR_RXBUFF) > 0;
}

static inline hri_pio_pcimr_reg_t hri_pio_get_PCIMR_reg(const void *const hw, hri_pio_pcimr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCIMR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_pcimr_reg_t hri_pio_read_PCIMR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_PCIMR;
}

static inline bool hri_pio_get_PCISR_DRDY_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PCISR & PIO_PCISR_DRDY) > 0;
}

static inline bool hri_pio_get_PCISR_OVRE_bit(const void *const hw)
{
	return (((Pio *)hw)->PIO_PCISR & PIO_PCISR_OVRE) > 0;
}

static inline hri_pio_pcisr_reg_t hri_pio_get_PCISR_reg(const void *const hw, hri_pio_pcisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCISR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_pcisr_reg_t hri_pio_read_PCISR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_PCISR;
}

static inline hri_pio_pcrhr_reg_t hri_pio_get_PCRHR_RDATA_bf(const void *const hw, hri_pio_pcrhr_reg_t mask)
{
	return (((Pio *)hw)->PIO_PCRHR & PIO_PCRHR_RDATA(mask)) >> PIO_PCRHR_RDATA_Pos;
}

static inline hri_pio_pcrhr_reg_t hri_pio_read_PCRHR_RDATA_bf(const void *const hw)
{
	return (((Pio *)hw)->PIO_PCRHR & PIO_PCRHR_RDATA_Msk) >> PIO_PCRHR_RDATA_Pos;
}

static inline hri_pio_pcrhr_reg_t hri_pio_get_PCRHR_reg(const void *const hw, hri_pio_pcrhr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCRHR;
	tmp &= mask;
	return tmp;
}

static inline hri_pio_pcrhr_reg_t hri_pio_read_PCRHR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_PCRHR;
}

static inline void hri_pio_set_ABCDSR_P0_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P0;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P0_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P0) >> PIO_ABCDSR_P0_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P0_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P0;
	tmp |= value << PIO_ABCDSR_P0_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P0_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P0;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P0_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P0;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P1_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P1;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P1_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P1) >> PIO_ABCDSR_P1_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P1_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P1;
	tmp |= value << PIO_ABCDSR_P1_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P1_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P1;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P1_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P1;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P2_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P2;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P2_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P2) >> PIO_ABCDSR_P2_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P2_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P2;
	tmp |= value << PIO_ABCDSR_P2_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P2_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P2;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P2_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P2;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P3_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P3;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P3_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P3) >> PIO_ABCDSR_P3_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P3_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P3;
	tmp |= value << PIO_ABCDSR_P3_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P3_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P3;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P3_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P3;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P4_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P4;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P4_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P4) >> PIO_ABCDSR_P4_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P4_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P4;
	tmp |= value << PIO_ABCDSR_P4_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P4_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P4;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P4_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P4;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P5_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P5;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P5_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P5) >> PIO_ABCDSR_P5_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P5_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P5;
	tmp |= value << PIO_ABCDSR_P5_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P5_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P5;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P5_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P5;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P6_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P6;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P6_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P6) >> PIO_ABCDSR_P6_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P6_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P6;
	tmp |= value << PIO_ABCDSR_P6_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P6_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P6;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P6_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P6;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P7_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P7;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P7_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P7) >> PIO_ABCDSR_P7_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P7_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P7;
	tmp |= value << PIO_ABCDSR_P7_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P7_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P7;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P7_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P7;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P8_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P8;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P8_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P8) >> PIO_ABCDSR_P8_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P8_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P8;
	tmp |= value << PIO_ABCDSR_P8_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P8_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P8;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P8_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P8;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P9_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P9;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P9_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P9) >> PIO_ABCDSR_P9_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P9_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P9;
	tmp |= value << PIO_ABCDSR_P9_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P9_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P9;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P9_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P9;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P10_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P10;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P10_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P10) >> PIO_ABCDSR_P10_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P10_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P10;
	tmp |= value << PIO_ABCDSR_P10_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P10_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P10;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P10_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P10;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P11_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P11;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P11_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P11) >> PIO_ABCDSR_P11_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P11_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P11;
	tmp |= value << PIO_ABCDSR_P11_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P11_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P11;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P11_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P11;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P12_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P12;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P12_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P12) >> PIO_ABCDSR_P12_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P12_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P12;
	tmp |= value << PIO_ABCDSR_P12_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P12_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P12;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P12_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P12;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P13_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P13;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P13_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P13) >> PIO_ABCDSR_P13_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P13_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P13;
	tmp |= value << PIO_ABCDSR_P13_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P13_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P13;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P13_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P13;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P14_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P14;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P14_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P14) >> PIO_ABCDSR_P14_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P14_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P14;
	tmp |= value << PIO_ABCDSR_P14_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P14_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P14;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P14_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P14;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P15_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P15;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P15_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P15) >> PIO_ABCDSR_P15_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P15_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P15;
	tmp |= value << PIO_ABCDSR_P15_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P15_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P15;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P15_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P15;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P16_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P16;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P16_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P16) >> PIO_ABCDSR_P16_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P16_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P16;
	tmp |= value << PIO_ABCDSR_P16_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P16_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P16;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P16_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P16;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P17_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P17;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P17_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P17) >> PIO_ABCDSR_P17_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P17_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P17;
	tmp |= value << PIO_ABCDSR_P17_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P17_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P17;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P17_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P17;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P18_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P18;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P18_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P18) >> PIO_ABCDSR_P18_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P18_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P18;
	tmp |= value << PIO_ABCDSR_P18_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P18_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P18;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P18_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P18;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P19_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P19;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P19_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P19) >> PIO_ABCDSR_P19_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P19_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P19;
	tmp |= value << PIO_ABCDSR_P19_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P19_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P19;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P19_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P19;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P20_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P20;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P20_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P20) >> PIO_ABCDSR_P20_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P20_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P20;
	tmp |= value << PIO_ABCDSR_P20_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P20_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P20;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P20_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P20;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P21_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P21;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P21_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P21) >> PIO_ABCDSR_P21_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P21_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P21;
	tmp |= value << PIO_ABCDSR_P21_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P21_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P21;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P21_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P21;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P22_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P22;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P22_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P22) >> PIO_ABCDSR_P22_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P22_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P22;
	tmp |= value << PIO_ABCDSR_P22_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P22_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P22;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P22_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P22;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P23_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P23;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P23_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P23) >> PIO_ABCDSR_P23_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P23_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P23;
	tmp |= value << PIO_ABCDSR_P23_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P23_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P23;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P23_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P23;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P24_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P24;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P24_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P24) >> PIO_ABCDSR_P24_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P24_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P24;
	tmp |= value << PIO_ABCDSR_P24_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P24_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P24;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P24_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P24;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P25_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P25;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P25_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P25) >> PIO_ABCDSR_P25_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P25_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P25;
	tmp |= value << PIO_ABCDSR_P25_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P25_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P25;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P25_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P25;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P26_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P26;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P26_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P26) >> PIO_ABCDSR_P26_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P26_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P26;
	tmp |= value << PIO_ABCDSR_P26_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P26_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P26;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P26_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P26;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P27_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P27;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P27_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P27) >> PIO_ABCDSR_P27_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P27_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P27;
	tmp |= value << PIO_ABCDSR_P27_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P27_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P27;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P27_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P27;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P28_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P28;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P28_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P28) >> PIO_ABCDSR_P28_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P28_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P28;
	tmp |= value << PIO_ABCDSR_P28_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P28_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P28;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P28_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P28;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P29_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P29;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P29_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P29) >> PIO_ABCDSR_P29_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P29_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P29;
	tmp |= value << PIO_ABCDSR_P29_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P29_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P29;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P29_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P29;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P30_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P30;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P30_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P30) >> PIO_ABCDSR_P30_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P30_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P30;
	tmp |= value << PIO_ABCDSR_P30_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P30_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P30;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P30_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P30;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_P31_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= PIO_ABCDSR_P31;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_ABCDSR_P31_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp = (tmp & PIO_ABCDSR_P31) >> PIO_ABCDSR_P31_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_ABCDSR_P31_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= ~PIO_ABCDSR_P31;
	tmp |= value << PIO_ABCDSR_P31_Pos;
	((Pio *)hw)->PIO_ABCDSR[index] = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_P31_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~PIO_ABCDSR_P31;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_P31_bit(const void *const hw, uint8_t index)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= PIO_ABCDSR_P31;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_ABCDSR_reg(const void *const hw, uint8_t index, hri_pio_abcdsr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] |= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_abcdsr_reg_t hri_pio_get_ABCDSR_reg(const void *const hw, uint8_t index,
                                                          hri_pio_abcdsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_ABCDSR[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_pio_write_ABCDSR_reg(const void *const hw, uint8_t index, hri_pio_abcdsr_reg_t data)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] = data;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_ABCDSR_reg(const void *const hw, uint8_t index, hri_pio_abcdsr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] &= ~mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_ABCDSR_reg(const void *const hw, uint8_t index, hri_pio_abcdsr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_ABCDSR[index] ^= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_abcdsr_reg_t hri_pio_read_ABCDSR_reg(const void *const hw, uint8_t index)
{
	return ((Pio *)hw)->PIO_ABCDSR[index];
}

static inline void hri_pio_set_SCDR_DIV_bf(const void *const hw, hri_pio_scdr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCDR |= PIO_SCDR_DIV(mask);
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_scdr_reg_t hri_pio_get_SCDR_DIV_bf(const void *const hw, hri_pio_scdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCDR;
	tmp = (tmp & PIO_SCDR_DIV(mask)) >> PIO_SCDR_DIV_Pos;
	return tmp;
}

static inline void hri_pio_write_SCDR_DIV_bf(const void *const hw, hri_pio_scdr_reg_t data)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCDR;
	tmp &= ~PIO_SCDR_DIV_Msk;
	tmp |= PIO_SCDR_DIV(data);
	((Pio *)hw)->PIO_SCDR = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCDR_DIV_bf(const void *const hw, hri_pio_scdr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCDR &= ~PIO_SCDR_DIV(mask);
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCDR_DIV_bf(const void *const hw, hri_pio_scdr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCDR ^= PIO_SCDR_DIV(mask);
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_scdr_reg_t hri_pio_read_SCDR_DIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCDR;
	tmp = (tmp & PIO_SCDR_DIV_Msk) >> PIO_SCDR_DIV_Pos;
	return tmp;
}

static inline void hri_pio_set_SCDR_reg(const void *const hw, hri_pio_scdr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCDR |= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_scdr_reg_t hri_pio_get_SCDR_reg(const void *const hw, hri_pio_scdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCDR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pio_write_SCDR_reg(const void *const hw, hri_pio_scdr_reg_t data)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCDR = data;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCDR_reg(const void *const hw, hri_pio_scdr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCDR &= ~mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCDR_reg(const void *const hw, hri_pio_scdr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCDR ^= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_scdr_reg_t hri_pio_read_SCDR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_SCDR;
}

static inline void hri_pio_set_WPMR_WPEN_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR |= PIO_WPMR_WPEN;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_WPMR;
	tmp = (tmp & PIO_WPMR_WPEN) >> PIO_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_WPMR;
	tmp &= ~PIO_WPMR_WPEN;
	tmp |= value << PIO_WPMR_WPEN_Pos;
	((Pio *)hw)->PIO_WPMR = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_WPMR_WPEN_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR &= ~PIO_WPMR_WPEN;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_WPMR_WPEN_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR ^= PIO_WPMR_WPEN;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_WPMR_WPKEY_bf(const void *const hw, hri_pio_wpmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR |= PIO_WPMR_WPKEY(mask);
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_wpmr_reg_t hri_pio_get_WPMR_WPKEY_bf(const void *const hw, hri_pio_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_WPMR;
	tmp = (tmp & PIO_WPMR_WPKEY(mask)) >> PIO_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_pio_write_WPMR_WPKEY_bf(const void *const hw, hri_pio_wpmr_reg_t data)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_WPMR;
	tmp &= ~PIO_WPMR_WPKEY_Msk;
	tmp |= PIO_WPMR_WPKEY(data);
	((Pio *)hw)->PIO_WPMR = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_WPMR_WPKEY_bf(const void *const hw, hri_pio_wpmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR &= ~PIO_WPMR_WPKEY(mask);
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_WPMR_WPKEY_bf(const void *const hw, hri_pio_wpmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR ^= PIO_WPMR_WPKEY(mask);
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_wpmr_reg_t hri_pio_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_WPMR;
	tmp = (tmp & PIO_WPMR_WPKEY_Msk) >> PIO_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_pio_set_WPMR_reg(const void *const hw, hri_pio_wpmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR |= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_wpmr_reg_t hri_pio_get_WPMR_reg(const void *const hw, hri_pio_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pio_write_WPMR_reg(const void *const hw, hri_pio_wpmr_reg_t data)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR = data;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_WPMR_reg(const void *const hw, hri_pio_wpmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR &= ~mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_WPMR_reg(const void *const hw, hri_pio_wpmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_WPMR ^= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_wpmr_reg_t hri_pio_read_WPMR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_WPMR;
}

static inline void hri_pio_set_SCHMITT_SCHMITT0_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT0;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT0) >> PIO_SCHMITT_SCHMITT0_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT0;
	tmp |= value << PIO_SCHMITT_SCHMITT0_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT0_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT0;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT0_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT0;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT1_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT1;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT1) >> PIO_SCHMITT_SCHMITT1_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT1;
	tmp |= value << PIO_SCHMITT_SCHMITT1_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT1_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT1;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT1_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT1;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT2_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT2;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT2) >> PIO_SCHMITT_SCHMITT2_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT2;
	tmp |= value << PIO_SCHMITT_SCHMITT2_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT2_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT2;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT2_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT2;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT3_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT3;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT3) >> PIO_SCHMITT_SCHMITT3_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT3;
	tmp |= value << PIO_SCHMITT_SCHMITT3_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT3_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT3;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT3_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT3;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT4_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT4;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT4) >> PIO_SCHMITT_SCHMITT4_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT4;
	tmp |= value << PIO_SCHMITT_SCHMITT4_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT4_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT4;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT4_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT4;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT5_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT5;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT5) >> PIO_SCHMITT_SCHMITT5_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT5;
	tmp |= value << PIO_SCHMITT_SCHMITT5_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT5_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT5;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT5_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT5;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT6_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT6;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT6) >> PIO_SCHMITT_SCHMITT6_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT6;
	tmp |= value << PIO_SCHMITT_SCHMITT6_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT6_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT6;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT6_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT6;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT7_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT7;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT7) >> PIO_SCHMITT_SCHMITT7_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT7;
	tmp |= value << PIO_SCHMITT_SCHMITT7_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT7_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT7;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT7_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT7;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT8_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT8;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT8) >> PIO_SCHMITT_SCHMITT8_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT8;
	tmp |= value << PIO_SCHMITT_SCHMITT8_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT8_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT8;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT8_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT8;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT9_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT9;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT9) >> PIO_SCHMITT_SCHMITT9_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT9;
	tmp |= value << PIO_SCHMITT_SCHMITT9_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT9_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT9;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT9_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT9;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT10_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT10;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT10) >> PIO_SCHMITT_SCHMITT10_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT10;
	tmp |= value << PIO_SCHMITT_SCHMITT10_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT10_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT10;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT10_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT10;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT11_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT11;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT11) >> PIO_SCHMITT_SCHMITT11_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT11;
	tmp |= value << PIO_SCHMITT_SCHMITT11_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT11_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT11;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT11_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT11;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT12_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT12;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT12) >> PIO_SCHMITT_SCHMITT12_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT12;
	tmp |= value << PIO_SCHMITT_SCHMITT12_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT12_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT12;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT12_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT12;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT13_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT13;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT13) >> PIO_SCHMITT_SCHMITT13_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT13;
	tmp |= value << PIO_SCHMITT_SCHMITT13_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT13_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT13;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT13_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT13;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT14_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT14;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT14) >> PIO_SCHMITT_SCHMITT14_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT14;
	tmp |= value << PIO_SCHMITT_SCHMITT14_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT14_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT14;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT14_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT14;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT15_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT15;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT15) >> PIO_SCHMITT_SCHMITT15_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT15;
	tmp |= value << PIO_SCHMITT_SCHMITT15_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT15_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT15;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT15_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT15;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT16_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT16;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT16) >> PIO_SCHMITT_SCHMITT16_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT16;
	tmp |= value << PIO_SCHMITT_SCHMITT16_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT16_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT16;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT16_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT16;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT17_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT17;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT17) >> PIO_SCHMITT_SCHMITT17_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT17;
	tmp |= value << PIO_SCHMITT_SCHMITT17_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT17_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT17;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT17_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT17;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT18_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT18;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT18) >> PIO_SCHMITT_SCHMITT18_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT18;
	tmp |= value << PIO_SCHMITT_SCHMITT18_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT18_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT18;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT18_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT18;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT19_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT19;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT19) >> PIO_SCHMITT_SCHMITT19_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT19;
	tmp |= value << PIO_SCHMITT_SCHMITT19_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT19_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT19;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT19_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT19;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT20_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT20;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT20) >> PIO_SCHMITT_SCHMITT20_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT20;
	tmp |= value << PIO_SCHMITT_SCHMITT20_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT20_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT20;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT20_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT20;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT21_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT21;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT21) >> PIO_SCHMITT_SCHMITT21_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT21;
	tmp |= value << PIO_SCHMITT_SCHMITT21_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT21_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT21;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT21_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT21;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT22_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT22;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT22) >> PIO_SCHMITT_SCHMITT22_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT22;
	tmp |= value << PIO_SCHMITT_SCHMITT22_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT22_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT22;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT22_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT22;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT23_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT23;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT23) >> PIO_SCHMITT_SCHMITT23_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT23;
	tmp |= value << PIO_SCHMITT_SCHMITT23_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT23_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT23;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT23_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT23;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT24_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT24;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT24) >> PIO_SCHMITT_SCHMITT24_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT24;
	tmp |= value << PIO_SCHMITT_SCHMITT24_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT24_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT24;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT24_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT24;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT25_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT25;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT25) >> PIO_SCHMITT_SCHMITT25_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT25;
	tmp |= value << PIO_SCHMITT_SCHMITT25_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT25_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT25;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT25_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT25;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT26_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT26;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT26) >> PIO_SCHMITT_SCHMITT26_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT26;
	tmp |= value << PIO_SCHMITT_SCHMITT26_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT26_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT26;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT26_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT26;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT27_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT27;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT27) >> PIO_SCHMITT_SCHMITT27_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT27;
	tmp |= value << PIO_SCHMITT_SCHMITT27_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT27_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT27;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT27_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT27;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT28_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT28;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT28) >> PIO_SCHMITT_SCHMITT28_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT28;
	tmp |= value << PIO_SCHMITT_SCHMITT28_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT28_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT28;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT28_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT28;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT29_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT29;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT29) >> PIO_SCHMITT_SCHMITT29_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT29;
	tmp |= value << PIO_SCHMITT_SCHMITT29_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT29_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT29;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT29_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT29;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT30_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT30;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT30) >> PIO_SCHMITT_SCHMITT30_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT30;
	tmp |= value << PIO_SCHMITT_SCHMITT30_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT30_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT30;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT30_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT30;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_SCHMITT31_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= PIO_SCHMITT_SCHMITT31;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_SCHMITT_SCHMITT31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp = (tmp & PIO_SCHMITT_SCHMITT31) >> PIO_SCHMITT_SCHMITT31_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_SCHMITT_SCHMITT31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= ~PIO_SCHMITT_SCHMITT31;
	tmp |= value << PIO_SCHMITT_SCHMITT31_Pos;
	((Pio *)hw)->PIO_SCHMITT = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_SCHMITT31_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~PIO_SCHMITT_SCHMITT31;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_SCHMITT31_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= PIO_SCHMITT_SCHMITT31;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_SCHMITT_reg(const void *const hw, hri_pio_schmitt_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT |= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_schmitt_reg_t hri_pio_get_SCHMITT_reg(const void *const hw, hri_pio_schmitt_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_SCHMITT;
	tmp &= mask;
	return tmp;
}

static inline void hri_pio_write_SCHMITT_reg(const void *const hw, hri_pio_schmitt_reg_t data)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT = data;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_SCHMITT_reg(const void *const hw, hri_pio_schmitt_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT &= ~mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_SCHMITT_reg(const void *const hw, hri_pio_schmitt_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_SCHMITT ^= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_schmitt_reg_t hri_pio_read_SCHMITT_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_SCHMITT;
}

static inline void hri_pio_set_DRIVER_LINE0_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE0;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE0) >> PIO_DRIVER_LINE0_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE0;
	tmp |= value << PIO_DRIVER_LINE0_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE0_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE0;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE0_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE0;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE1_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE1;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE1) >> PIO_DRIVER_LINE1_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE1;
	tmp |= value << PIO_DRIVER_LINE1_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE1_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE1;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE1_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE1;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE2_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE2;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE2) >> PIO_DRIVER_LINE2_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE2;
	tmp |= value << PIO_DRIVER_LINE2_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE2_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE2;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE2_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE2;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE3_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE3;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE3) >> PIO_DRIVER_LINE3_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE3;
	tmp |= value << PIO_DRIVER_LINE3_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE3_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE3;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE3_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE3;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE4_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE4;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE4) >> PIO_DRIVER_LINE4_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE4;
	tmp |= value << PIO_DRIVER_LINE4_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE4_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE4;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE4_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE4;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE5_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE5;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE5) >> PIO_DRIVER_LINE5_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE5;
	tmp |= value << PIO_DRIVER_LINE5_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE5_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE5;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE5_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE5;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE6_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE6;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE6) >> PIO_DRIVER_LINE6_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE6;
	tmp |= value << PIO_DRIVER_LINE6_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE6_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE6;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE6_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE6;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE7_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE7;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE7) >> PIO_DRIVER_LINE7_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE7;
	tmp |= value << PIO_DRIVER_LINE7_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE7_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE7;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE7_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE7;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE8_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE8;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE8) >> PIO_DRIVER_LINE8_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE8;
	tmp |= value << PIO_DRIVER_LINE8_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE8_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE8;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE8_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE8;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE9_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE9;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE9) >> PIO_DRIVER_LINE9_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE9;
	tmp |= value << PIO_DRIVER_LINE9_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE9_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE9;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE9_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE9;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE10_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE10;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE10) >> PIO_DRIVER_LINE10_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE10;
	tmp |= value << PIO_DRIVER_LINE10_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE10_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE10;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE10_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE10;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE11_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE11;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE11) >> PIO_DRIVER_LINE11_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE11;
	tmp |= value << PIO_DRIVER_LINE11_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE11_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE11;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE11_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE11;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE12_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE12;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE12) >> PIO_DRIVER_LINE12_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE12;
	tmp |= value << PIO_DRIVER_LINE12_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE12_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE12;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE12_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE12;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE13_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE13;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE13) >> PIO_DRIVER_LINE13_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE13;
	tmp |= value << PIO_DRIVER_LINE13_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE13_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE13;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE13_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE13;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE14_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE14;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE14) >> PIO_DRIVER_LINE14_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE14;
	tmp |= value << PIO_DRIVER_LINE14_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE14_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE14;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE14_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE14;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE15_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE15;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE15) >> PIO_DRIVER_LINE15_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE15;
	tmp |= value << PIO_DRIVER_LINE15_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE15_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE15;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE15_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE15;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE16_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE16;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE16) >> PIO_DRIVER_LINE16_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE16;
	tmp |= value << PIO_DRIVER_LINE16_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE16_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE16;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE16_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE16;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE17_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE17;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE17) >> PIO_DRIVER_LINE17_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE17;
	tmp |= value << PIO_DRIVER_LINE17_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE17_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE17;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE17_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE17;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE18_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE18;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE18) >> PIO_DRIVER_LINE18_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE18;
	tmp |= value << PIO_DRIVER_LINE18_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE18_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE18;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE18_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE18;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE19_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE19;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE19) >> PIO_DRIVER_LINE19_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE19;
	tmp |= value << PIO_DRIVER_LINE19_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE19_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE19;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE19_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE19;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE20_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE20;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE20) >> PIO_DRIVER_LINE20_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE20;
	tmp |= value << PIO_DRIVER_LINE20_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE20_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE20;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE20_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE20;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE21_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE21;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE21) >> PIO_DRIVER_LINE21_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE21;
	tmp |= value << PIO_DRIVER_LINE21_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE21_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE21;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE21_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE21;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE22_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE22;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE22) >> PIO_DRIVER_LINE22_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE22;
	tmp |= value << PIO_DRIVER_LINE22_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE22_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE22;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE22_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE22;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE23_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE23;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE23) >> PIO_DRIVER_LINE23_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE23;
	tmp |= value << PIO_DRIVER_LINE23_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE23_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE23;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE23_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE23;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE24_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE24;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE24) >> PIO_DRIVER_LINE24_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE24;
	tmp |= value << PIO_DRIVER_LINE24_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE24_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE24;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE24_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE24;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE25_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE25;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE25) >> PIO_DRIVER_LINE25_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE25;
	tmp |= value << PIO_DRIVER_LINE25_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE25_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE25;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE25_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE25;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE26_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE26;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE26) >> PIO_DRIVER_LINE26_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE26;
	tmp |= value << PIO_DRIVER_LINE26_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE26_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE26;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE26_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE26;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE27_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE27;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE27) >> PIO_DRIVER_LINE27_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE27;
	tmp |= value << PIO_DRIVER_LINE27_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE27_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE27;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE27_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE27;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE28_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE28;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE28) >> PIO_DRIVER_LINE28_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE28;
	tmp |= value << PIO_DRIVER_LINE28_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE28_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE28;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE28_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE28;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE29_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE29;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE29) >> PIO_DRIVER_LINE29_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE29;
	tmp |= value << PIO_DRIVER_LINE29_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE29_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE29;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE29_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE29;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE30_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE30;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE30) >> PIO_DRIVER_LINE30_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE30;
	tmp |= value << PIO_DRIVER_LINE30_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE30_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE30;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE30_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE30;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_LINE31_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= PIO_DRIVER_LINE31;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_DRIVER_LINE31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp = (tmp & PIO_DRIVER_LINE31) >> PIO_DRIVER_LINE31_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_DRIVER_LINE31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= ~PIO_DRIVER_LINE31;
	tmp |= value << PIO_DRIVER_LINE31_Pos;
	((Pio *)hw)->PIO_DRIVER = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_LINE31_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~PIO_DRIVER_LINE31;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_LINE31_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= PIO_DRIVER_LINE31;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_DRIVER_reg(const void *const hw, hri_pio_driver_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER |= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_driver_reg_t hri_pio_get_DRIVER_reg(const void *const hw, hri_pio_driver_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_DRIVER;
	tmp &= mask;
	return tmp;
}

static inline void hri_pio_write_DRIVER_reg(const void *const hw, hri_pio_driver_reg_t data)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER = data;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_DRIVER_reg(const void *const hw, hri_pio_driver_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER &= ~mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_DRIVER_reg(const void *const hw, hri_pio_driver_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_DRIVER ^= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_driver_reg_t hri_pio_read_DRIVER_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_DRIVER;
}

static inline void hri_pio_set_PCMR_PCEN_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR |= PIO_PCMR_PCEN;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_PCMR_PCEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp = (tmp & PIO_PCMR_PCEN) >> PIO_PCMR_PCEN_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_PCMR_PCEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp &= ~PIO_PCMR_PCEN;
	tmp |= value << PIO_PCMR_PCEN_Pos;
	((Pio *)hw)->PIO_PCMR = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_PCMR_PCEN_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR &= ~PIO_PCMR_PCEN;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_PCMR_PCEN_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR ^= PIO_PCMR_PCEN;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_PCMR_ALWYS_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR |= PIO_PCMR_ALWYS;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_PCMR_ALWYS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp = (tmp & PIO_PCMR_ALWYS) >> PIO_PCMR_ALWYS_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_PCMR_ALWYS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp &= ~PIO_PCMR_ALWYS;
	tmp |= value << PIO_PCMR_ALWYS_Pos;
	((Pio *)hw)->PIO_PCMR = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_PCMR_ALWYS_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR &= ~PIO_PCMR_ALWYS;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_PCMR_ALWYS_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR ^= PIO_PCMR_ALWYS;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_PCMR_HALFS_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR |= PIO_PCMR_HALFS;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_PCMR_HALFS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp = (tmp & PIO_PCMR_HALFS) >> PIO_PCMR_HALFS_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_PCMR_HALFS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp &= ~PIO_PCMR_HALFS;
	tmp |= value << PIO_PCMR_HALFS_Pos;
	((Pio *)hw)->PIO_PCMR = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_PCMR_HALFS_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR &= ~PIO_PCMR_HALFS;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_PCMR_HALFS_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR ^= PIO_PCMR_HALFS;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_PCMR_FRSTS_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR |= PIO_PCMR_FRSTS;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pio_get_PCMR_FRSTS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp = (tmp & PIO_PCMR_FRSTS) >> PIO_PCMR_FRSTS_Pos;
	return (bool)tmp;
}

static inline void hri_pio_write_PCMR_FRSTS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp &= ~PIO_PCMR_FRSTS;
	tmp |= value << PIO_PCMR_FRSTS_Pos;
	((Pio *)hw)->PIO_PCMR = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_PCMR_FRSTS_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR &= ~PIO_PCMR_FRSTS;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_PCMR_FRSTS_bit(const void *const hw)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR ^= PIO_PCMR_FRSTS;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_set_PCMR_DSIZE_bf(const void *const hw, hri_pio_pcmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR |= PIO_PCMR_DSIZE(mask);
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_pcmr_reg_t hri_pio_get_PCMR_DSIZE_bf(const void *const hw, hri_pio_pcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp = (tmp & PIO_PCMR_DSIZE(mask)) >> PIO_PCMR_DSIZE_Pos;
	return tmp;
}

static inline void hri_pio_write_PCMR_DSIZE_bf(const void *const hw, hri_pio_pcmr_reg_t data)
{
	uint32_t tmp;
	PIO_CRITICAL_SECTION_ENTER();
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp &= ~PIO_PCMR_DSIZE_Msk;
	tmp |= PIO_PCMR_DSIZE(data);
	((Pio *)hw)->PIO_PCMR = tmp;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_PCMR_DSIZE_bf(const void *const hw, hri_pio_pcmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR &= ~PIO_PCMR_DSIZE(mask);
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_PCMR_DSIZE_bf(const void *const hw, hri_pio_pcmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR ^= PIO_PCMR_DSIZE(mask);
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_pcmr_reg_t hri_pio_read_PCMR_DSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp = (tmp & PIO_PCMR_DSIZE_Msk) >> PIO_PCMR_DSIZE_Pos;
	return tmp;
}

static inline void hri_pio_set_PCMR_reg(const void *const hw, hri_pio_pcmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR |= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_pcmr_reg_t hri_pio_get_PCMR_reg(const void *const hw, hri_pio_pcmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pio *)hw)->PIO_PCMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_pio_write_PCMR_reg(const void *const hw, hri_pio_pcmr_reg_t data)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR = data;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_clear_PCMR_reg(const void *const hw, hri_pio_pcmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR &= ~mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_toggle_PCMR_reg(const void *const hw, hri_pio_pcmr_reg_t mask)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCMR ^= mask;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline hri_pio_pcmr_reg_t hri_pio_read_PCMR_reg(const void *const hw)
{
	return ((Pio *)hw)->PIO_PCMR;
}

static inline void hri_pio_write_PCIER_reg(const void *const hw, hri_pio_pcier_reg_t data)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCIER = data;
	PIO_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pio_write_PCIDR_reg(const void *const hw, hri_pio_pcidr_reg_t data)
{
	PIO_CRITICAL_SECTION_ENTER();
	((Pio *)hw)->PIO_PCIDR = data;
	PIO_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_PIO_E70B_H_INCLUDED */
#endif /* _SAME70_PIO_COMPONENT_ */
