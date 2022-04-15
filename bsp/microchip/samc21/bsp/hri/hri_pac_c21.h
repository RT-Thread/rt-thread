/**
 * \file
 *
 * \brief SAM PAC
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

#ifdef _SAMC21_PAC_COMPONENT_
#ifndef _HRI_PAC_C21_H_INCLUDED_
#define _HRI_PAC_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_PAC_CRITICAL_SECTIONS)
#define PAC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define PAC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define PAC_CRITICAL_SECTION_ENTER()
#define PAC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_pac_intflaga_reg_t;
typedef uint32_t hri_pac_intflagahb_reg_t;
typedef uint32_t hri_pac_intflagb_reg_t;
typedef uint32_t hri_pac_intflagc_reg_t;
typedef uint32_t hri_pac_statusa_reg_t;
typedef uint32_t hri_pac_statusb_reg_t;
typedef uint32_t hri_pac_statusc_reg_t;
typedef uint32_t hri_pac_wrctrl_reg_t;
typedef uint8_t  hri_pac_evctrl_reg_t;
typedef uint8_t  hri_pac_intenset_reg_t;

static inline bool hri_pac_get_INTFLAGAHB_FLASH_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGAHB.reg & PAC_INTFLAGAHB_FLASH) >> PAC_INTFLAGAHB_FLASH_Pos;
}

static inline void hri_pac_clear_INTFLAGAHB_FLASH_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGAHB.reg = PAC_INTFLAGAHB_FLASH;
}

static inline bool hri_pac_get_INTFLAGAHB_HSRAMCM0P_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGAHB.reg & PAC_INTFLAGAHB_HSRAMCM0P) >> PAC_INTFLAGAHB_HSRAMCM0P_Pos;
}

static inline void hri_pac_clear_INTFLAGAHB_HSRAMCM0P_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGAHB.reg = PAC_INTFLAGAHB_HSRAMCM0P;
}

static inline bool hri_pac_get_INTFLAGAHB_HSRAMDSU_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGAHB.reg & PAC_INTFLAGAHB_HSRAMDSU) >> PAC_INTFLAGAHB_HSRAMDSU_Pos;
}

static inline void hri_pac_clear_INTFLAGAHB_HSRAMDSU_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGAHB.reg = PAC_INTFLAGAHB_HSRAMDSU;
}

static inline bool hri_pac_get_INTFLAGAHB_HPB1_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGAHB.reg & PAC_INTFLAGAHB_HPB1) >> PAC_INTFLAGAHB_HPB1_Pos;
}

static inline void hri_pac_clear_INTFLAGAHB_HPB1_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGAHB.reg = PAC_INTFLAGAHB_HPB1;
}

static inline bool hri_pac_get_INTFLAGAHB_HPB0_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGAHB.reg & PAC_INTFLAGAHB_HPB0) >> PAC_INTFLAGAHB_HPB0_Pos;
}

static inline void hri_pac_clear_INTFLAGAHB_HPB0_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGAHB.reg = PAC_INTFLAGAHB_HPB0;
}

static inline bool hri_pac_get_INTFLAGAHB_HPB2_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGAHB.reg & PAC_INTFLAGAHB_HPB2) >> PAC_INTFLAGAHB_HPB2_Pos;
}

static inline void hri_pac_clear_INTFLAGAHB_HPB2_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGAHB.reg = PAC_INTFLAGAHB_HPB2;
}

static inline bool hri_pac_get_INTFLAGAHB_LPRAMDMAC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGAHB.reg & PAC_INTFLAGAHB_LPRAMDMAC) >> PAC_INTFLAGAHB_LPRAMDMAC_Pos;
}

static inline void hri_pac_clear_INTFLAGAHB_LPRAMDMAC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGAHB.reg = PAC_INTFLAGAHB_LPRAMDMAC;
}

static inline bool hri_pac_get_INTFLAGAHB_DIVAS_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGAHB.reg & PAC_INTFLAGAHB_DIVAS) >> PAC_INTFLAGAHB_DIVAS_Pos;
}

static inline void hri_pac_clear_INTFLAGAHB_DIVAS_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGAHB.reg = PAC_INTFLAGAHB_DIVAS;
}

static inline hri_pac_intflagahb_reg_t hri_pac_get_INTFLAGAHB_reg(const void *const hw, hri_pac_intflagahb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->INTFLAGAHB.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pac_intflagahb_reg_t hri_pac_read_INTFLAGAHB_reg(const void *const hw)
{
	return ((Pac *)hw)->INTFLAGAHB.reg;
}

static inline void hri_pac_clear_INTFLAGAHB_reg(const void *const hw, hri_pac_intflagahb_reg_t mask)
{
	((Pac *)hw)->INTFLAGAHB.reg = mask;
}

static inline bool hri_pac_get_INTFLAGA_PAC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_PAC) >> PAC_INTFLAGA_PAC_Pos;
}

static inline void hri_pac_clear_INTFLAGA_PAC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_PAC;
}

static inline bool hri_pac_get_INTFLAGA_PM_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_PM) >> PAC_INTFLAGA_PM_Pos;
}

static inline void hri_pac_clear_INTFLAGA_PM_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_PM;
}

static inline bool hri_pac_get_INTFLAGA_MCLK_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_MCLK) >> PAC_INTFLAGA_MCLK_Pos;
}

static inline void hri_pac_clear_INTFLAGA_MCLK_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_MCLK;
}

static inline bool hri_pac_get_INTFLAGA_RSTC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_RSTC) >> PAC_INTFLAGA_RSTC_Pos;
}

static inline void hri_pac_clear_INTFLAGA_RSTC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_RSTC;
}

static inline bool hri_pac_get_INTFLAGA_OSCCTRL_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_OSCCTRL) >> PAC_INTFLAGA_OSCCTRL_Pos;
}

static inline void hri_pac_clear_INTFLAGA_OSCCTRL_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_OSCCTRL;
}

static inline bool hri_pac_get_INTFLAGA_OSC32KCTRL_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_OSC32KCTRL) >> PAC_INTFLAGA_OSC32KCTRL_Pos;
}

static inline void hri_pac_clear_INTFLAGA_OSC32KCTRL_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_OSC32KCTRL;
}

static inline bool hri_pac_get_INTFLAGA_SUPC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_SUPC) >> PAC_INTFLAGA_SUPC_Pos;
}

static inline void hri_pac_clear_INTFLAGA_SUPC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_SUPC;
}

static inline bool hri_pac_get_INTFLAGA_GCLK_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_GCLK) >> PAC_INTFLAGA_GCLK_Pos;
}

static inline void hri_pac_clear_INTFLAGA_GCLK_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_GCLK;
}

static inline bool hri_pac_get_INTFLAGA_WDT_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_WDT) >> PAC_INTFLAGA_WDT_Pos;
}

static inline void hri_pac_clear_INTFLAGA_WDT_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_WDT;
}

static inline bool hri_pac_get_INTFLAGA_RTC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_RTC) >> PAC_INTFLAGA_RTC_Pos;
}

static inline void hri_pac_clear_INTFLAGA_RTC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_RTC;
}

static inline bool hri_pac_get_INTFLAGA_EIC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_EIC) >> PAC_INTFLAGA_EIC_Pos;
}

static inline void hri_pac_clear_INTFLAGA_EIC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_EIC;
}

static inline bool hri_pac_get_INTFLAGA_FREQM_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_FREQM) >> PAC_INTFLAGA_FREQM_Pos;
}

static inline void hri_pac_clear_INTFLAGA_FREQM_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_FREQM;
}

static inline bool hri_pac_get_INTFLAGA_TSENS_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGA.reg & PAC_INTFLAGA_TSENS) >> PAC_INTFLAGA_TSENS_Pos;
}

static inline void hri_pac_clear_INTFLAGA_TSENS_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGA.reg = PAC_INTFLAGA_TSENS;
}

static inline hri_pac_intflaga_reg_t hri_pac_get_INTFLAGA_reg(const void *const hw, hri_pac_intflaga_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->INTFLAGA.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pac_intflaga_reg_t hri_pac_read_INTFLAGA_reg(const void *const hw)
{
	return ((Pac *)hw)->INTFLAGA.reg;
}

static inline void hri_pac_clear_INTFLAGA_reg(const void *const hw, hri_pac_intflaga_reg_t mask)
{
	((Pac *)hw)->INTFLAGA.reg = mask;
}

static inline bool hri_pac_get_INTFLAGB_PORT_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGB.reg & PAC_INTFLAGB_PORT) >> PAC_INTFLAGB_PORT_Pos;
}

static inline void hri_pac_clear_INTFLAGB_PORT_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGB.reg = PAC_INTFLAGB_PORT;
}

static inline bool hri_pac_get_INTFLAGB_DSU_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGB.reg & PAC_INTFLAGB_DSU) >> PAC_INTFLAGB_DSU_Pos;
}

static inline void hri_pac_clear_INTFLAGB_DSU_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGB.reg = PAC_INTFLAGB_DSU;
}

static inline bool hri_pac_get_INTFLAGB_NVMCTRL_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGB.reg & PAC_INTFLAGB_NVMCTRL) >> PAC_INTFLAGB_NVMCTRL_Pos;
}

static inline void hri_pac_clear_INTFLAGB_NVMCTRL_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGB.reg = PAC_INTFLAGB_NVMCTRL;
}

static inline bool hri_pac_get_INTFLAGB_DMAC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGB.reg & PAC_INTFLAGB_DMAC) >> PAC_INTFLAGB_DMAC_Pos;
}

static inline void hri_pac_clear_INTFLAGB_DMAC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGB.reg = PAC_INTFLAGB_DMAC;
}

static inline bool hri_pac_get_INTFLAGB_MTB_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGB.reg & PAC_INTFLAGB_MTB) >> PAC_INTFLAGB_MTB_Pos;
}

static inline void hri_pac_clear_INTFLAGB_MTB_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGB.reg = PAC_INTFLAGB_MTB;
}

static inline bool hri_pac_get_INTFLAGB_HMATRIXHS_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGB.reg & PAC_INTFLAGB_HMATRIXHS) >> PAC_INTFLAGB_HMATRIXHS_Pos;
}

static inline void hri_pac_clear_INTFLAGB_HMATRIXHS_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGB.reg = PAC_INTFLAGB_HMATRIXHS;
}

static inline hri_pac_intflagb_reg_t hri_pac_get_INTFLAGB_reg(const void *const hw, hri_pac_intflagb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->INTFLAGB.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pac_intflagb_reg_t hri_pac_read_INTFLAGB_reg(const void *const hw)
{
	return ((Pac *)hw)->INTFLAGB.reg;
}

static inline void hri_pac_clear_INTFLAGB_reg(const void *const hw, hri_pac_intflagb_reg_t mask)
{
	((Pac *)hw)->INTFLAGB.reg = mask;
}

static inline bool hri_pac_get_INTFLAGC_EVSYS_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_EVSYS) >> PAC_INTFLAGC_EVSYS_Pos;
}

static inline void hri_pac_clear_INTFLAGC_EVSYS_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_EVSYS;
}

static inline bool hri_pac_get_INTFLAGC_SERCOM0_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_SERCOM0) >> PAC_INTFLAGC_SERCOM0_Pos;
}

static inline void hri_pac_clear_INTFLAGC_SERCOM0_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_SERCOM0;
}

static inline bool hri_pac_get_INTFLAGC_SERCOM1_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_SERCOM1) >> PAC_INTFLAGC_SERCOM1_Pos;
}

static inline void hri_pac_clear_INTFLAGC_SERCOM1_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_SERCOM1;
}

static inline bool hri_pac_get_INTFLAGC_SERCOM2_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_SERCOM2) >> PAC_INTFLAGC_SERCOM2_Pos;
}

static inline void hri_pac_clear_INTFLAGC_SERCOM2_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_SERCOM2;
}

static inline bool hri_pac_get_INTFLAGC_SERCOM3_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_SERCOM3) >> PAC_INTFLAGC_SERCOM3_Pos;
}

static inline void hri_pac_clear_INTFLAGC_SERCOM3_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_SERCOM3;
}

static inline bool hri_pac_get_INTFLAGC_SERCOM4_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_SERCOM4) >> PAC_INTFLAGC_SERCOM4_Pos;
}

static inline void hri_pac_clear_INTFLAGC_SERCOM4_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_SERCOM4;
}

static inline bool hri_pac_get_INTFLAGC_SERCOM5_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_SERCOM5) >> PAC_INTFLAGC_SERCOM5_Pos;
}

static inline void hri_pac_clear_INTFLAGC_SERCOM5_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_SERCOM5;
}

static inline bool hri_pac_get_INTFLAGC_CAN0_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_CAN0) >> PAC_INTFLAGC_CAN0_Pos;
}

static inline void hri_pac_clear_INTFLAGC_CAN0_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_CAN0;
}

static inline bool hri_pac_get_INTFLAGC_CAN1_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_CAN1) >> PAC_INTFLAGC_CAN1_Pos;
}

static inline void hri_pac_clear_INTFLAGC_CAN1_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_CAN1;
}

static inline bool hri_pac_get_INTFLAGC_TCC0_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_TCC0) >> PAC_INTFLAGC_TCC0_Pos;
}

static inline void hri_pac_clear_INTFLAGC_TCC0_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_TCC0;
}

static inline bool hri_pac_get_INTFLAGC_TCC1_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_TCC1) >> PAC_INTFLAGC_TCC1_Pos;
}

static inline void hri_pac_clear_INTFLAGC_TCC1_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_TCC1;
}

static inline bool hri_pac_get_INTFLAGC_TCC2_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_TCC2) >> PAC_INTFLAGC_TCC2_Pos;
}

static inline void hri_pac_clear_INTFLAGC_TCC2_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_TCC2;
}

static inline bool hri_pac_get_INTFLAGC_TC0_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_TC0) >> PAC_INTFLAGC_TC0_Pos;
}

static inline void hri_pac_clear_INTFLAGC_TC0_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_TC0;
}

static inline bool hri_pac_get_INTFLAGC_TC1_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_TC1) >> PAC_INTFLAGC_TC1_Pos;
}

static inline void hri_pac_clear_INTFLAGC_TC1_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_TC1;
}

static inline bool hri_pac_get_INTFLAGC_TC2_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_TC2) >> PAC_INTFLAGC_TC2_Pos;
}

static inline void hri_pac_clear_INTFLAGC_TC2_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_TC2;
}

static inline bool hri_pac_get_INTFLAGC_TC3_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_TC3) >> PAC_INTFLAGC_TC3_Pos;
}

static inline void hri_pac_clear_INTFLAGC_TC3_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_TC3;
}

static inline bool hri_pac_get_INTFLAGC_TC4_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_TC4) >> PAC_INTFLAGC_TC4_Pos;
}

static inline void hri_pac_clear_INTFLAGC_TC4_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_TC4;
}

static inline bool hri_pac_get_INTFLAGC_ADC0_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_ADC0) >> PAC_INTFLAGC_ADC0_Pos;
}

static inline void hri_pac_clear_INTFLAGC_ADC0_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_ADC0;
}

static inline bool hri_pac_get_INTFLAGC_ADC1_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_ADC1) >> PAC_INTFLAGC_ADC1_Pos;
}

static inline void hri_pac_clear_INTFLAGC_ADC1_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_ADC1;
}

static inline bool hri_pac_get_INTFLAGC_SDADC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_SDADC) >> PAC_INTFLAGC_SDADC_Pos;
}

static inline void hri_pac_clear_INTFLAGC_SDADC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_SDADC;
}

static inline bool hri_pac_get_INTFLAGC_AC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_AC) >> PAC_INTFLAGC_AC_Pos;
}

static inline void hri_pac_clear_INTFLAGC_AC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_AC;
}

static inline bool hri_pac_get_INTFLAGC_DAC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_DAC) >> PAC_INTFLAGC_DAC_Pos;
}

static inline void hri_pac_clear_INTFLAGC_DAC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_DAC;
}

static inline bool hri_pac_get_INTFLAGC_PTC_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_PTC) >> PAC_INTFLAGC_PTC_Pos;
}

static inline void hri_pac_clear_INTFLAGC_PTC_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_PTC;
}

static inline bool hri_pac_get_INTFLAGC_CCL_bit(const void *const hw)
{
	return (((Pac *)hw)->INTFLAGC.reg & PAC_INTFLAGC_CCL) >> PAC_INTFLAGC_CCL_Pos;
}

static inline void hri_pac_clear_INTFLAGC_CCL_bit(const void *const hw)
{
	((Pac *)hw)->INTFLAGC.reg = PAC_INTFLAGC_CCL;
}

static inline hri_pac_intflagc_reg_t hri_pac_get_INTFLAGC_reg(const void *const hw, hri_pac_intflagc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->INTFLAGC.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pac_intflagc_reg_t hri_pac_read_INTFLAGC_reg(const void *const hw)
{
	return ((Pac *)hw)->INTFLAGC.reg;
}

static inline void hri_pac_clear_INTFLAGC_reg(const void *const hw, hri_pac_intflagc_reg_t mask)
{
	((Pac *)hw)->INTFLAGC.reg = mask;
}

static inline void hri_pac_set_INTEN_ERR_bit(const void *const hw)
{
	((Pac *)hw)->INTENSET.reg = PAC_INTENSET_ERR;
}

static inline bool hri_pac_get_INTEN_ERR_bit(const void *const hw)
{
	return (((Pac *)hw)->INTENSET.reg & PAC_INTENSET_ERR) >> PAC_INTENSET_ERR_Pos;
}

static inline void hri_pac_write_INTEN_ERR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Pac *)hw)->INTENCLR.reg = PAC_INTENSET_ERR;
	} else {
		((Pac *)hw)->INTENSET.reg = PAC_INTENSET_ERR;
	}
}

static inline void hri_pac_clear_INTEN_ERR_bit(const void *const hw)
{
	((Pac *)hw)->INTENCLR.reg = PAC_INTENSET_ERR;
}

static inline void hri_pac_set_INTEN_reg(const void *const hw, hri_pac_intenset_reg_t mask)
{
	((Pac *)hw)->INTENSET.reg = mask;
}

static inline hri_pac_intenset_reg_t hri_pac_get_INTEN_reg(const void *const hw, hri_pac_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pac *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pac_intenset_reg_t hri_pac_read_INTEN_reg(const void *const hw)
{
	return ((Pac *)hw)->INTENSET.reg;
}

static inline void hri_pac_write_INTEN_reg(const void *const hw, hri_pac_intenset_reg_t data)
{
	((Pac *)hw)->INTENSET.reg = data;
	((Pac *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_pac_clear_INTEN_reg(const void *const hw, hri_pac_intenset_reg_t mask)
{
	((Pac *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_pac_get_STATUSA_PAC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_PAC) >> PAC_STATUSA_PAC_Pos;
}

static inline bool hri_pac_get_STATUSA_PM_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_PM) >> PAC_STATUSA_PM_Pos;
}

static inline bool hri_pac_get_STATUSA_MCLK_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_MCLK) >> PAC_STATUSA_MCLK_Pos;
}

static inline bool hri_pac_get_STATUSA_RSTC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_RSTC) >> PAC_STATUSA_RSTC_Pos;
}

static inline bool hri_pac_get_STATUSA_OSCCTRL_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_OSCCTRL) >> PAC_STATUSA_OSCCTRL_Pos;
}

static inline bool hri_pac_get_STATUSA_OSC32KCTRL_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_OSC32KCTRL) >> PAC_STATUSA_OSC32KCTRL_Pos;
}

static inline bool hri_pac_get_STATUSA_SUPC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_SUPC) >> PAC_STATUSA_SUPC_Pos;
}

static inline bool hri_pac_get_STATUSA_GCLK_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_GCLK) >> PAC_STATUSA_GCLK_Pos;
}

static inline bool hri_pac_get_STATUSA_WDT_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_WDT) >> PAC_STATUSA_WDT_Pos;
}

static inline bool hri_pac_get_STATUSA_RTC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_RTC) >> PAC_STATUSA_RTC_Pos;
}

static inline bool hri_pac_get_STATUSA_EIC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_EIC) >> PAC_STATUSA_EIC_Pos;
}

static inline bool hri_pac_get_STATUSA_FREQM_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_FREQM) >> PAC_STATUSA_FREQM_Pos;
}

static inline bool hri_pac_get_STATUSA_TSENS_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSA.reg & PAC_STATUSA_TSENS) >> PAC_STATUSA_TSENS_Pos;
}

static inline hri_pac_statusa_reg_t hri_pac_get_STATUSA_reg(const void *const hw, hri_pac_statusa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->STATUSA.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pac_statusa_reg_t hri_pac_read_STATUSA_reg(const void *const hw)
{
	return ((Pac *)hw)->STATUSA.reg;
}

static inline bool hri_pac_get_STATUSB_PORT_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSB.reg & PAC_STATUSB_PORT) >> PAC_STATUSB_PORT_Pos;
}

static inline bool hri_pac_get_STATUSB_DSU_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSB.reg & PAC_STATUSB_DSU) >> PAC_STATUSB_DSU_Pos;
}

static inline bool hri_pac_get_STATUSB_NVMCTRL_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSB.reg & PAC_STATUSB_NVMCTRL) >> PAC_STATUSB_NVMCTRL_Pos;
}

static inline bool hri_pac_get_STATUSB_DMAC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSB.reg & PAC_STATUSB_DMAC) >> PAC_STATUSB_DMAC_Pos;
}

static inline bool hri_pac_get_STATUSB_MTB_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSB.reg & PAC_STATUSB_MTB) >> PAC_STATUSB_MTB_Pos;
}

static inline bool hri_pac_get_STATUSB_HMATRIXHS_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSB.reg & PAC_STATUSB_HMATRIXHS) >> PAC_STATUSB_HMATRIXHS_Pos;
}

static inline hri_pac_statusb_reg_t hri_pac_get_STATUSB_reg(const void *const hw, hri_pac_statusb_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->STATUSB.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pac_statusb_reg_t hri_pac_read_STATUSB_reg(const void *const hw)
{
	return ((Pac *)hw)->STATUSB.reg;
}

static inline bool hri_pac_get_STATUSC_EVSYS_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_EVSYS) >> PAC_STATUSC_EVSYS_Pos;
}

static inline bool hri_pac_get_STATUSC_SERCOM0_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_SERCOM0) >> PAC_STATUSC_SERCOM0_Pos;
}

static inline bool hri_pac_get_STATUSC_SERCOM1_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_SERCOM1) >> PAC_STATUSC_SERCOM1_Pos;
}

static inline bool hri_pac_get_STATUSC_SERCOM2_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_SERCOM2) >> PAC_STATUSC_SERCOM2_Pos;
}

static inline bool hri_pac_get_STATUSC_SERCOM3_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_SERCOM3) >> PAC_STATUSC_SERCOM3_Pos;
}

static inline bool hri_pac_get_STATUSC_SERCOM4_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_SERCOM4) >> PAC_STATUSC_SERCOM4_Pos;
}

static inline bool hri_pac_get_STATUSC_SERCOM5_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_SERCOM5) >> PAC_STATUSC_SERCOM5_Pos;
}

static inline bool hri_pac_get_STATUSC_CAN0_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_CAN0) >> PAC_STATUSC_CAN0_Pos;
}

static inline bool hri_pac_get_STATUSC_CAN1_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_CAN1) >> PAC_STATUSC_CAN1_Pos;
}

static inline bool hri_pac_get_STATUSC_TCC0_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_TCC0) >> PAC_STATUSC_TCC0_Pos;
}

static inline bool hri_pac_get_STATUSC_TCC1_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_TCC1) >> PAC_STATUSC_TCC1_Pos;
}

static inline bool hri_pac_get_STATUSC_TCC2_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_TCC2) >> PAC_STATUSC_TCC2_Pos;
}

static inline bool hri_pac_get_STATUSC_TC0_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_TC0) >> PAC_STATUSC_TC0_Pos;
}

static inline bool hri_pac_get_STATUSC_TC1_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_TC1) >> PAC_STATUSC_TC1_Pos;
}

static inline bool hri_pac_get_STATUSC_TC2_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_TC2) >> PAC_STATUSC_TC2_Pos;
}

static inline bool hri_pac_get_STATUSC_TC3_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_TC3) >> PAC_STATUSC_TC3_Pos;
}

static inline bool hri_pac_get_STATUSC_TC4_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_TC4) >> PAC_STATUSC_TC4_Pos;
}

static inline bool hri_pac_get_STATUSC_ADC0_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_ADC0) >> PAC_STATUSC_ADC0_Pos;
}

static inline bool hri_pac_get_STATUSC_ADC1_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_ADC1) >> PAC_STATUSC_ADC1_Pos;
}

static inline bool hri_pac_get_STATUSC_SDADC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_SDADC) >> PAC_STATUSC_SDADC_Pos;
}

static inline bool hri_pac_get_STATUSC_AC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_AC) >> PAC_STATUSC_AC_Pos;
}

static inline bool hri_pac_get_STATUSC_DAC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_DAC) >> PAC_STATUSC_DAC_Pos;
}

static inline bool hri_pac_get_STATUSC_PTC_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_PTC) >> PAC_STATUSC_PTC_Pos;
}

static inline bool hri_pac_get_STATUSC_CCL_bit(const void *const hw)
{
	return (((Pac *)hw)->STATUSC.reg & PAC_STATUSC_CCL) >> PAC_STATUSC_CCL_Pos;
}

static inline hri_pac_statusc_reg_t hri_pac_get_STATUSC_reg(const void *const hw, hri_pac_statusc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->STATUSC.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_pac_statusc_reg_t hri_pac_read_STATUSC_reg(const void *const hw)
{
	return ((Pac *)hw)->STATUSC.reg;
}

static inline void hri_pac_set_WRCTRL_PERID_bf(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg |= PAC_WRCTRL_PERID(mask);
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pac_wrctrl_reg_t hri_pac_get_WRCTRL_PERID_bf(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->WRCTRL.reg;
	tmp = (tmp & PAC_WRCTRL_PERID(mask)) >> PAC_WRCTRL_PERID_Pos;
	return tmp;
}

static inline void hri_pac_write_WRCTRL_PERID_bf(const void *const hw, hri_pac_wrctrl_reg_t data)
{
	uint32_t tmp;
	PAC_CRITICAL_SECTION_ENTER();
	tmp = ((Pac *)hw)->WRCTRL.reg;
	tmp &= ~PAC_WRCTRL_PERID_Msk;
	tmp |= PAC_WRCTRL_PERID(data);
	((Pac *)hw)->WRCTRL.reg = tmp;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_clear_WRCTRL_PERID_bf(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg &= ~PAC_WRCTRL_PERID(mask);
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_toggle_WRCTRL_PERID_bf(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg ^= PAC_WRCTRL_PERID(mask);
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pac_wrctrl_reg_t hri_pac_read_WRCTRL_PERID_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->WRCTRL.reg;
	tmp = (tmp & PAC_WRCTRL_PERID_Msk) >> PAC_WRCTRL_PERID_Pos;
	return tmp;
}

static inline void hri_pac_set_WRCTRL_KEY_bf(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg |= PAC_WRCTRL_KEY(mask);
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pac_wrctrl_reg_t hri_pac_get_WRCTRL_KEY_bf(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->WRCTRL.reg;
	tmp = (tmp & PAC_WRCTRL_KEY(mask)) >> PAC_WRCTRL_KEY_Pos;
	return tmp;
}

static inline void hri_pac_write_WRCTRL_KEY_bf(const void *const hw, hri_pac_wrctrl_reg_t data)
{
	uint32_t tmp;
	PAC_CRITICAL_SECTION_ENTER();
	tmp = ((Pac *)hw)->WRCTRL.reg;
	tmp &= ~PAC_WRCTRL_KEY_Msk;
	tmp |= PAC_WRCTRL_KEY(data);
	((Pac *)hw)->WRCTRL.reg = tmp;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_clear_WRCTRL_KEY_bf(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg &= ~PAC_WRCTRL_KEY(mask);
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_toggle_WRCTRL_KEY_bf(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg ^= PAC_WRCTRL_KEY(mask);
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pac_wrctrl_reg_t hri_pac_read_WRCTRL_KEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->WRCTRL.reg;
	tmp = (tmp & PAC_WRCTRL_KEY_Msk) >> PAC_WRCTRL_KEY_Pos;
	return tmp;
}

static inline void hri_pac_set_WRCTRL_reg(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg |= mask;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pac_wrctrl_reg_t hri_pac_get_WRCTRL_reg(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Pac *)hw)->WRCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_pac_write_WRCTRL_reg(const void *const hw, hri_pac_wrctrl_reg_t data)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg = data;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_clear_WRCTRL_reg(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg &= ~mask;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_toggle_WRCTRL_reg(const void *const hw, hri_pac_wrctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->WRCTRL.reg ^= mask;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pac_wrctrl_reg_t hri_pac_read_WRCTRL_reg(const void *const hw)
{
	return ((Pac *)hw)->WRCTRL.reg;
}

static inline void hri_pac_set_EVCTRL_ERREO_bit(const void *const hw)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->EVCTRL.reg |= PAC_EVCTRL_ERREO;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_pac_get_EVCTRL_ERREO_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Pac *)hw)->EVCTRL.reg;
	tmp = (tmp & PAC_EVCTRL_ERREO) >> PAC_EVCTRL_ERREO_Pos;
	return (bool)tmp;
}

static inline void hri_pac_write_EVCTRL_ERREO_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	PAC_CRITICAL_SECTION_ENTER();
	tmp = ((Pac *)hw)->EVCTRL.reg;
	tmp &= ~PAC_EVCTRL_ERREO;
	tmp |= value << PAC_EVCTRL_ERREO_Pos;
	((Pac *)hw)->EVCTRL.reg = tmp;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_clear_EVCTRL_ERREO_bit(const void *const hw)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->EVCTRL.reg &= ~PAC_EVCTRL_ERREO;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_toggle_EVCTRL_ERREO_bit(const void *const hw)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->EVCTRL.reg ^= PAC_EVCTRL_ERREO;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_set_EVCTRL_reg(const void *const hw, hri_pac_evctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->EVCTRL.reg |= mask;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pac_evctrl_reg_t hri_pac_get_EVCTRL_reg(const void *const hw, hri_pac_evctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Pac *)hw)->EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_pac_write_EVCTRL_reg(const void *const hw, hri_pac_evctrl_reg_t data)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->EVCTRL.reg = data;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_clear_EVCTRL_reg(const void *const hw, hri_pac_evctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->EVCTRL.reg &= ~mask;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_pac_toggle_EVCTRL_reg(const void *const hw, hri_pac_evctrl_reg_t mask)
{
	PAC_CRITICAL_SECTION_ENTER();
	((Pac *)hw)->EVCTRL.reg ^= mask;
	PAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_pac_evctrl_reg_t hri_pac_read_EVCTRL_reg(const void *const hw)
{
	return ((Pac *)hw)->EVCTRL.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_PAC_C21_H_INCLUDED */
#endif /* _SAMC21_PAC_COMPONENT_ */
