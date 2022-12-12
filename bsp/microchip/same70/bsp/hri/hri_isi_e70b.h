/**
 * \file
 *
 * \brief SAM ISI
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

#ifdef _SAME70_ISI_COMPONENT_
#ifndef _HRI_ISI_E70B_H_INCLUDED_
#define _HRI_ISI_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_ISI_CRITICAL_SECTIONS)
#define ISI_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define ISI_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define ISI_CRITICAL_SECTION_ENTER()
#define ISI_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_isi_cfg1_reg_t;
typedef uint32_t hri_isi_cfg2_reg_t;
typedef uint32_t hri_isi_cr_reg_t;
typedef uint32_t hri_isi_dma_c_addr_reg_t;
typedef uint32_t hri_isi_dma_c_ctrl_reg_t;
typedef uint32_t hri_isi_dma_c_dscr_reg_t;
typedef uint32_t hri_isi_dma_chsr_reg_t;
typedef uint32_t hri_isi_dma_p_addr_reg_t;
typedef uint32_t hri_isi_dma_p_ctrl_reg_t;
typedef uint32_t hri_isi_dma_p_dscr_reg_t;
typedef uint32_t hri_isi_imr_reg_t;
typedef uint32_t hri_isi_pdecf_reg_t;
typedef uint32_t hri_isi_psize_reg_t;
typedef uint32_t hri_isi_r2y_set0_reg_t;
typedef uint32_t hri_isi_r2y_set1_reg_t;
typedef uint32_t hri_isi_r2y_set2_reg_t;
typedef uint32_t hri_isi_sr_reg_t;
typedef uint32_t hri_isi_wpmr_reg_t;
typedef uint32_t hri_isi_wpsr_reg_t;
typedef uint32_t hri_isi_y2r_set0_reg_t;
typedef uint32_t hri_isi_y2r_set1_reg_t;

static inline void hri_isi_set_IMR_DIS_DONE_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IER = ISI_IMR_DIS_DONE;
}

static inline bool hri_isi_get_IMR_DIS_DONE_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_IMR & ISI_IMR_DIS_DONE) >> ISI_IMR_DIS_DONE_Pos;
}

static inline void hri_isi_write_IMR_DIS_DONE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_IDR = ISI_IMR_DIS_DONE;
	} else {
		((Isi *)hw)->ISI_IER = ISI_IMR_DIS_DONE;
	}
}

static inline void hri_isi_clear_IMR_DIS_DONE_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IDR = ISI_IMR_DIS_DONE;
}

static inline void hri_isi_set_IMR_SRST_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IER = ISI_IMR_SRST;
}

static inline bool hri_isi_get_IMR_SRST_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_IMR & ISI_IMR_SRST) >> ISI_IMR_SRST_Pos;
}

static inline void hri_isi_write_IMR_SRST_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_IDR = ISI_IMR_SRST;
	} else {
		((Isi *)hw)->ISI_IER = ISI_IMR_SRST;
	}
}

static inline void hri_isi_clear_IMR_SRST_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IDR = ISI_IMR_SRST;
}

static inline void hri_isi_set_IMR_VSYNC_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IER = ISI_IMR_VSYNC;
}

static inline bool hri_isi_get_IMR_VSYNC_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_IMR & ISI_IMR_VSYNC) >> ISI_IMR_VSYNC_Pos;
}

static inline void hri_isi_write_IMR_VSYNC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_IDR = ISI_IMR_VSYNC;
	} else {
		((Isi *)hw)->ISI_IER = ISI_IMR_VSYNC;
	}
}

static inline void hri_isi_clear_IMR_VSYNC_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IDR = ISI_IMR_VSYNC;
}

static inline void hri_isi_set_IMR_PXFR_DONE_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IER = ISI_IMR_PXFR_DONE;
}

static inline bool hri_isi_get_IMR_PXFR_DONE_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_IMR & ISI_IMR_PXFR_DONE) >> ISI_IMR_PXFR_DONE_Pos;
}

static inline void hri_isi_write_IMR_PXFR_DONE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_IDR = ISI_IMR_PXFR_DONE;
	} else {
		((Isi *)hw)->ISI_IER = ISI_IMR_PXFR_DONE;
	}
}

static inline void hri_isi_clear_IMR_PXFR_DONE_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IDR = ISI_IMR_PXFR_DONE;
}

static inline void hri_isi_set_IMR_CXFR_DONE_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IER = ISI_IMR_CXFR_DONE;
}

static inline bool hri_isi_get_IMR_CXFR_DONE_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_IMR & ISI_IMR_CXFR_DONE) >> ISI_IMR_CXFR_DONE_Pos;
}

static inline void hri_isi_write_IMR_CXFR_DONE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_IDR = ISI_IMR_CXFR_DONE;
	} else {
		((Isi *)hw)->ISI_IER = ISI_IMR_CXFR_DONE;
	}
}

static inline void hri_isi_clear_IMR_CXFR_DONE_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IDR = ISI_IMR_CXFR_DONE;
}

static inline void hri_isi_set_IMR_P_OVR_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IER = ISI_IMR_P_OVR;
}

static inline bool hri_isi_get_IMR_P_OVR_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_IMR & ISI_IMR_P_OVR) >> ISI_IMR_P_OVR_Pos;
}

static inline void hri_isi_write_IMR_P_OVR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_IDR = ISI_IMR_P_OVR;
	} else {
		((Isi *)hw)->ISI_IER = ISI_IMR_P_OVR;
	}
}

static inline void hri_isi_clear_IMR_P_OVR_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IDR = ISI_IMR_P_OVR;
}

static inline void hri_isi_set_IMR_C_OVR_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IER = ISI_IMR_C_OVR;
}

static inline bool hri_isi_get_IMR_C_OVR_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_IMR & ISI_IMR_C_OVR) >> ISI_IMR_C_OVR_Pos;
}

static inline void hri_isi_write_IMR_C_OVR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_IDR = ISI_IMR_C_OVR;
	} else {
		((Isi *)hw)->ISI_IER = ISI_IMR_C_OVR;
	}
}

static inline void hri_isi_clear_IMR_C_OVR_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IDR = ISI_IMR_C_OVR;
}

static inline void hri_isi_set_IMR_CRC_ERR_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IER = ISI_IMR_CRC_ERR;
}

static inline bool hri_isi_get_IMR_CRC_ERR_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_IMR & ISI_IMR_CRC_ERR) >> ISI_IMR_CRC_ERR_Pos;
}

static inline void hri_isi_write_IMR_CRC_ERR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_IDR = ISI_IMR_CRC_ERR;
	} else {
		((Isi *)hw)->ISI_IER = ISI_IMR_CRC_ERR;
	}
}

static inline void hri_isi_clear_IMR_CRC_ERR_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IDR = ISI_IMR_CRC_ERR;
}

static inline void hri_isi_set_IMR_FR_OVR_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IER = ISI_IMR_FR_OVR;
}

static inline bool hri_isi_get_IMR_FR_OVR_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_IMR & ISI_IMR_FR_OVR) >> ISI_IMR_FR_OVR_Pos;
}

static inline void hri_isi_write_IMR_FR_OVR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_IDR = ISI_IMR_FR_OVR;
	} else {
		((Isi *)hw)->ISI_IER = ISI_IMR_FR_OVR;
	}
}

static inline void hri_isi_clear_IMR_FR_OVR_bit(const void *const hw)
{
	((Isi *)hw)->ISI_IDR = ISI_IMR_FR_OVR;
}

static inline void hri_isi_set_IMR_reg(const void *const hw, hri_isi_imr_reg_t mask)
{
	((Isi *)hw)->ISI_IER = mask;
}

static inline hri_isi_imr_reg_t hri_isi_get_IMR_reg(const void *const hw, hri_isi_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_isi_imr_reg_t hri_isi_read_IMR_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_IMR;
}

static inline void hri_isi_write_IMR_reg(const void *const hw, hri_isi_imr_reg_t data)
{
	((Isi *)hw)->ISI_IER = data;
	((Isi *)hw)->ISI_IDR = ~data;
}

static inline void hri_isi_clear_IMR_reg(const void *const hw, hri_isi_imr_reg_t mask)
{
	((Isi *)hw)->ISI_IDR = mask;
}

static inline void hri_isi_set_DMA_CHSR_P_CH_S_bit(const void *const hw)
{
	((Isi *)hw)->ISI_DMA_CHER = ISI_DMA_CHSR_P_CH_S;
}

static inline bool hri_isi_get_DMA_CHSR_P_CH_S_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_DMA_CHSR & ISI_DMA_CHSR_P_CH_S) >> ISI_DMA_CHSR_P_CH_S_Pos;
}

static inline void hri_isi_write_DMA_CHSR_P_CH_S_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_DMA_CHDR = ISI_DMA_CHSR_P_CH_S;
	} else {
		((Isi *)hw)->ISI_DMA_CHER = ISI_DMA_CHSR_P_CH_S;
	}
}

static inline void hri_isi_clear_DMA_CHSR_P_CH_S_bit(const void *const hw)
{
	((Isi *)hw)->ISI_DMA_CHDR = ISI_DMA_CHSR_P_CH_S;
}

static inline void hri_isi_set_DMA_CHSR_C_CH_S_bit(const void *const hw)
{
	((Isi *)hw)->ISI_DMA_CHER = ISI_DMA_CHSR_C_CH_S;
}

static inline bool hri_isi_get_DMA_CHSR_C_CH_S_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_DMA_CHSR & ISI_DMA_CHSR_C_CH_S) >> ISI_DMA_CHSR_C_CH_S_Pos;
}

static inline void hri_isi_write_DMA_CHSR_C_CH_S_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Isi *)hw)->ISI_DMA_CHDR = ISI_DMA_CHSR_C_CH_S;
	} else {
		((Isi *)hw)->ISI_DMA_CHER = ISI_DMA_CHSR_C_CH_S;
	}
}

static inline void hri_isi_clear_DMA_CHSR_C_CH_S_bit(const void *const hw)
{
	((Isi *)hw)->ISI_DMA_CHDR = ISI_DMA_CHSR_C_CH_S;
}

static inline void hri_isi_set_DMA_CHSR_reg(const void *const hw, hri_isi_dma_chsr_reg_t mask)
{
	((Isi *)hw)->ISI_DMA_CHER = mask;
}

static inline hri_isi_dma_chsr_reg_t hri_isi_get_DMA_CHSR_reg(const void *const hw, hri_isi_dma_chsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_CHSR;
	tmp &= mask;
	return tmp;
}

static inline hri_isi_dma_chsr_reg_t hri_isi_read_DMA_CHSR_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_DMA_CHSR;
}

static inline void hri_isi_write_DMA_CHSR_reg(const void *const hw, hri_isi_dma_chsr_reg_t data)
{
	((Isi *)hw)->ISI_DMA_CHER = data;
	((Isi *)hw)->ISI_DMA_CHDR = ~data;
}

static inline void hri_isi_clear_DMA_CHSR_reg(const void *const hw, hri_isi_dma_chsr_reg_t mask)
{
	((Isi *)hw)->ISI_DMA_CHDR = mask;
}

static inline bool hri_isi_get_SR_ENABLE_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_ENABLE) > 0;
}

static inline bool hri_isi_get_SR_DIS_DONE_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_DIS_DONE) > 0;
}

static inline bool hri_isi_get_SR_SRST_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_SRST) > 0;
}

static inline bool hri_isi_get_SR_CDC_PND_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_CDC_PND) > 0;
}

static inline bool hri_isi_get_SR_VSYNC_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_VSYNC) > 0;
}

static inline bool hri_isi_get_SR_PXFR_DONE_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_PXFR_DONE) > 0;
}

static inline bool hri_isi_get_SR_CXFR_DONE_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_CXFR_DONE) > 0;
}

static inline bool hri_isi_get_SR_SIP_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_SIP) > 0;
}

static inline bool hri_isi_get_SR_P_OVR_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_P_OVR) > 0;
}

static inline bool hri_isi_get_SR_C_OVR_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_C_OVR) > 0;
}

static inline bool hri_isi_get_SR_CRC_ERR_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_CRC_ERR) > 0;
}

static inline bool hri_isi_get_SR_FR_OVR_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_SR & ISI_SR_FR_OVR) > 0;
}

static inline hri_isi_sr_reg_t hri_isi_get_SR_reg(const void *const hw, hri_isi_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_isi_sr_reg_t hri_isi_read_SR_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_SR;
}

static inline bool hri_isi_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Isi *)hw)->ISI_WPSR & ISI_WPSR_WPVS) > 0;
}

static inline hri_isi_wpsr_reg_t hri_isi_get_WPSR_WPVSRC_bf(const void *const hw, hri_isi_wpsr_reg_t mask)
{
	return (((Isi *)hw)->ISI_WPSR & ISI_WPSR_WPVSRC(mask)) >> ISI_WPSR_WPVSRC_Pos;
}

static inline hri_isi_wpsr_reg_t hri_isi_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Isi *)hw)->ISI_WPSR & ISI_WPSR_WPVSRC_Msk) >> ISI_WPSR_WPVSRC_Pos;
}

static inline hri_isi_wpsr_reg_t hri_isi_get_WPSR_reg(const void *const hw, hri_isi_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_isi_wpsr_reg_t hri_isi_read_WPSR_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_WPSR;
}

static inline void hri_isi_set_CFG1_HSYNC_POL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_HSYNC_POL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG1_HSYNC_POL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_HSYNC_POL) >> ISI_CFG1_HSYNC_POL_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG1_HSYNC_POL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_HSYNC_POL;
	tmp |= value << ISI_CFG1_HSYNC_POL_Pos;
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_HSYNC_POL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_HSYNC_POL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_HSYNC_POL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_HSYNC_POL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG1_VSYNC_POL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_VSYNC_POL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG1_VSYNC_POL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_VSYNC_POL) >> ISI_CFG1_VSYNC_POL_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG1_VSYNC_POL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_VSYNC_POL;
	tmp |= value << ISI_CFG1_VSYNC_POL_Pos;
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_VSYNC_POL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_VSYNC_POL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_VSYNC_POL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_VSYNC_POL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG1_PIXCLK_POL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_PIXCLK_POL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG1_PIXCLK_POL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_PIXCLK_POL) >> ISI_CFG1_PIXCLK_POL_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG1_PIXCLK_POL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_PIXCLK_POL;
	tmp |= value << ISI_CFG1_PIXCLK_POL_Pos;
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_PIXCLK_POL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_PIXCLK_POL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_PIXCLK_POL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_PIXCLK_POL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG1_GRAYLE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_GRAYLE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG1_GRAYLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_GRAYLE) >> ISI_CFG1_GRAYLE_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG1_GRAYLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_GRAYLE;
	tmp |= value << ISI_CFG1_GRAYLE_Pos;
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_GRAYLE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_GRAYLE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_GRAYLE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_GRAYLE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG1_EMB_SYNC_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_EMB_SYNC;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG1_EMB_SYNC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_EMB_SYNC) >> ISI_CFG1_EMB_SYNC_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG1_EMB_SYNC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_EMB_SYNC;
	tmp |= value << ISI_CFG1_EMB_SYNC_Pos;
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_EMB_SYNC_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_EMB_SYNC;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_EMB_SYNC_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_EMB_SYNC;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG1_CRC_SYNC_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_CRC_SYNC;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG1_CRC_SYNC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_CRC_SYNC) >> ISI_CFG1_CRC_SYNC_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG1_CRC_SYNC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_CRC_SYNC;
	tmp |= value << ISI_CFG1_CRC_SYNC_Pos;
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_CRC_SYNC_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_CRC_SYNC;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_CRC_SYNC_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_CRC_SYNC;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG1_DISCR_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_DISCR;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG1_DISCR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_DISCR) >> ISI_CFG1_DISCR_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG1_DISCR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_DISCR;
	tmp |= value << ISI_CFG1_DISCR_Pos;
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_DISCR_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_DISCR;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_DISCR_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_DISCR;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG1_FULL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_FULL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG1_FULL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_FULL) >> ISI_CFG1_FULL_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG1_FULL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_FULL;
	tmp |= value << ISI_CFG1_FULL_Pos;
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_FULL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_FULL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_FULL_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_FULL;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG1_FRATE_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_FRATE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_get_CFG1_FRATE_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_FRATE(mask)) >> ISI_CFG1_FRATE_Pos;
	return tmp;
}

static inline void hri_isi_write_CFG1_FRATE_bf(const void *const hw, hri_isi_cfg1_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_FRATE_Msk;
	tmp |= ISI_CFG1_FRATE(data);
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_FRATE_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_FRATE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_FRATE_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_FRATE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_read_CFG1_FRATE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_FRATE_Msk) >> ISI_CFG1_FRATE_Pos;
	return tmp;
}

static inline void hri_isi_set_CFG1_THMASK_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_THMASK(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_get_CFG1_THMASK_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_THMASK(mask)) >> ISI_CFG1_THMASK_Pos;
	return tmp;
}

static inline void hri_isi_write_CFG1_THMASK_bf(const void *const hw, hri_isi_cfg1_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_THMASK_Msk;
	tmp |= ISI_CFG1_THMASK(data);
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_THMASK_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_THMASK(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_THMASK_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_THMASK(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_read_CFG1_THMASK_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_THMASK_Msk) >> ISI_CFG1_THMASK_Pos;
	return tmp;
}

static inline void hri_isi_set_CFG1_SLD_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_SLD(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_get_CFG1_SLD_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_SLD(mask)) >> ISI_CFG1_SLD_Pos;
	return tmp;
}

static inline void hri_isi_write_CFG1_SLD_bf(const void *const hw, hri_isi_cfg1_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_SLD_Msk;
	tmp |= ISI_CFG1_SLD(data);
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_SLD_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_SLD(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_SLD_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_SLD(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_read_CFG1_SLD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_SLD_Msk) >> ISI_CFG1_SLD_Pos;
	return tmp;
}

static inline void hri_isi_set_CFG1_SFD_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= ISI_CFG1_SFD(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_get_CFG1_SFD_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_SFD(mask)) >> ISI_CFG1_SFD_Pos;
	return tmp;
}

static inline void hri_isi_write_CFG1_SFD_bf(const void *const hw, hri_isi_cfg1_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= ~ISI_CFG1_SFD_Msk;
	tmp |= ISI_CFG1_SFD(data);
	((Isi *)hw)->ISI_CFG1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_SFD_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~ISI_CFG1_SFD(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_SFD_bf(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= ISI_CFG1_SFD(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_read_CFG1_SFD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp = (tmp & ISI_CFG1_SFD_Msk) >> ISI_CFG1_SFD_Pos;
	return tmp;
}

static inline void hri_isi_set_CFG1_reg(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_get_CFG1_reg(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG1;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_CFG1_reg(const void *const hw, hri_isi_cfg1_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG1_reg(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG1_reg(const void *const hw, hri_isi_cfg1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG1 ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg1_reg_t hri_isi_read_CFG1_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_CFG1;
}

static inline void hri_isi_set_CFG2_GS_MODE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= ISI_CFG2_GS_MODE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG2_GS_MODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_GS_MODE) >> ISI_CFG2_GS_MODE_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG2_GS_MODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= ~ISI_CFG2_GS_MODE;
	tmp |= value << ISI_CFG2_GS_MODE_Pos;
	((Isi *)hw)->ISI_CFG2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_GS_MODE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~ISI_CFG2_GS_MODE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_GS_MODE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= ISI_CFG2_GS_MODE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG2_RGB_MODE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= ISI_CFG2_RGB_MODE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG2_RGB_MODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_RGB_MODE) >> ISI_CFG2_RGB_MODE_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG2_RGB_MODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= ~ISI_CFG2_RGB_MODE;
	tmp |= value << ISI_CFG2_RGB_MODE_Pos;
	((Isi *)hw)->ISI_CFG2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_RGB_MODE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~ISI_CFG2_RGB_MODE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_RGB_MODE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= ISI_CFG2_RGB_MODE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG2_GRAYSCALE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= ISI_CFG2_GRAYSCALE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG2_GRAYSCALE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_GRAYSCALE) >> ISI_CFG2_GRAYSCALE_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG2_GRAYSCALE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= ~ISI_CFG2_GRAYSCALE;
	tmp |= value << ISI_CFG2_GRAYSCALE_Pos;
	((Isi *)hw)->ISI_CFG2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_GRAYSCALE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~ISI_CFG2_GRAYSCALE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_GRAYSCALE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= ISI_CFG2_GRAYSCALE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG2_RGB_SWAP_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= ISI_CFG2_RGB_SWAP;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG2_RGB_SWAP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_RGB_SWAP) >> ISI_CFG2_RGB_SWAP_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG2_RGB_SWAP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= ~ISI_CFG2_RGB_SWAP;
	tmp |= value << ISI_CFG2_RGB_SWAP_Pos;
	((Isi *)hw)->ISI_CFG2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_RGB_SWAP_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~ISI_CFG2_RGB_SWAP;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_RGB_SWAP_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= ISI_CFG2_RGB_SWAP;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG2_COL_SPACE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= ISI_CFG2_COL_SPACE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_CFG2_COL_SPACE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_COL_SPACE) >> ISI_CFG2_COL_SPACE_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_CFG2_COL_SPACE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= ~ISI_CFG2_COL_SPACE;
	tmp |= value << ISI_CFG2_COL_SPACE_Pos;
	((Isi *)hw)->ISI_CFG2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_COL_SPACE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~ISI_CFG2_COL_SPACE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_COL_SPACE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= ISI_CFG2_COL_SPACE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_CFG2_IM_VSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= ISI_CFG2_IM_VSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_get_CFG2_IM_VSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_IM_VSIZE(mask)) >> ISI_CFG2_IM_VSIZE_Pos;
	return tmp;
}

static inline void hri_isi_write_CFG2_IM_VSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= ~ISI_CFG2_IM_VSIZE_Msk;
	tmp |= ISI_CFG2_IM_VSIZE(data);
	((Isi *)hw)->ISI_CFG2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_IM_VSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~ISI_CFG2_IM_VSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_IM_VSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= ISI_CFG2_IM_VSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_read_CFG2_IM_VSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_IM_VSIZE_Msk) >> ISI_CFG2_IM_VSIZE_Pos;
	return tmp;
}

static inline void hri_isi_set_CFG2_IM_HSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= ISI_CFG2_IM_HSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_get_CFG2_IM_HSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_IM_HSIZE(mask)) >> ISI_CFG2_IM_HSIZE_Pos;
	return tmp;
}

static inline void hri_isi_write_CFG2_IM_HSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= ~ISI_CFG2_IM_HSIZE_Msk;
	tmp |= ISI_CFG2_IM_HSIZE(data);
	((Isi *)hw)->ISI_CFG2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_IM_HSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~ISI_CFG2_IM_HSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_IM_HSIZE_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= ISI_CFG2_IM_HSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_read_CFG2_IM_HSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_IM_HSIZE_Msk) >> ISI_CFG2_IM_HSIZE_Pos;
	return tmp;
}

static inline void hri_isi_set_CFG2_YCC_SWAP_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= ISI_CFG2_YCC_SWAP(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_get_CFG2_YCC_SWAP_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_YCC_SWAP(mask)) >> ISI_CFG2_YCC_SWAP_Pos;
	return tmp;
}

static inline void hri_isi_write_CFG2_YCC_SWAP_bf(const void *const hw, hri_isi_cfg2_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= ~ISI_CFG2_YCC_SWAP_Msk;
	tmp |= ISI_CFG2_YCC_SWAP(data);
	((Isi *)hw)->ISI_CFG2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_YCC_SWAP_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~ISI_CFG2_YCC_SWAP(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_YCC_SWAP_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= ISI_CFG2_YCC_SWAP(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_read_CFG2_YCC_SWAP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_YCC_SWAP_Msk) >> ISI_CFG2_YCC_SWAP_Pos;
	return tmp;
}

static inline void hri_isi_set_CFG2_RGB_CFG_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= ISI_CFG2_RGB_CFG(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_get_CFG2_RGB_CFG_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_RGB_CFG(mask)) >> ISI_CFG2_RGB_CFG_Pos;
	return tmp;
}

static inline void hri_isi_write_CFG2_RGB_CFG_bf(const void *const hw, hri_isi_cfg2_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= ~ISI_CFG2_RGB_CFG_Msk;
	tmp |= ISI_CFG2_RGB_CFG(data);
	((Isi *)hw)->ISI_CFG2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_RGB_CFG_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~ISI_CFG2_RGB_CFG(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_RGB_CFG_bf(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= ISI_CFG2_RGB_CFG(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_read_CFG2_RGB_CFG_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp = (tmp & ISI_CFG2_RGB_CFG_Msk) >> ISI_CFG2_RGB_CFG_Pos;
	return tmp;
}

static inline void hri_isi_set_CFG2_reg(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_get_CFG2_reg(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_CFG2;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_CFG2_reg(const void *const hw, hri_isi_cfg2_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_CFG2_reg(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_CFG2_reg(const void *const hw, hri_isi_cfg2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CFG2 ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_cfg2_reg_t hri_isi_read_CFG2_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_CFG2;
}

static inline void hri_isi_set_PSIZE_PREV_VSIZE_bf(const void *const hw, hri_isi_psize_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE |= ISI_PSIZE_PREV_VSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_psize_reg_t hri_isi_get_PSIZE_PREV_VSIZE_bf(const void *const hw, hri_isi_psize_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_PSIZE;
	tmp = (tmp & ISI_PSIZE_PREV_VSIZE(mask)) >> ISI_PSIZE_PREV_VSIZE_Pos;
	return tmp;
}

static inline void hri_isi_write_PSIZE_PREV_VSIZE_bf(const void *const hw, hri_isi_psize_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_PSIZE;
	tmp &= ~ISI_PSIZE_PREV_VSIZE_Msk;
	tmp |= ISI_PSIZE_PREV_VSIZE(data);
	((Isi *)hw)->ISI_PSIZE = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_PSIZE_PREV_VSIZE_bf(const void *const hw, hri_isi_psize_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE &= ~ISI_PSIZE_PREV_VSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_PSIZE_PREV_VSIZE_bf(const void *const hw, hri_isi_psize_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE ^= ISI_PSIZE_PREV_VSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_psize_reg_t hri_isi_read_PSIZE_PREV_VSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_PSIZE;
	tmp = (tmp & ISI_PSIZE_PREV_VSIZE_Msk) >> ISI_PSIZE_PREV_VSIZE_Pos;
	return tmp;
}

static inline void hri_isi_set_PSIZE_PREV_HSIZE_bf(const void *const hw, hri_isi_psize_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE |= ISI_PSIZE_PREV_HSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_psize_reg_t hri_isi_get_PSIZE_PREV_HSIZE_bf(const void *const hw, hri_isi_psize_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_PSIZE;
	tmp = (tmp & ISI_PSIZE_PREV_HSIZE(mask)) >> ISI_PSIZE_PREV_HSIZE_Pos;
	return tmp;
}

static inline void hri_isi_write_PSIZE_PREV_HSIZE_bf(const void *const hw, hri_isi_psize_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_PSIZE;
	tmp &= ~ISI_PSIZE_PREV_HSIZE_Msk;
	tmp |= ISI_PSIZE_PREV_HSIZE(data);
	((Isi *)hw)->ISI_PSIZE = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_PSIZE_PREV_HSIZE_bf(const void *const hw, hri_isi_psize_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE &= ~ISI_PSIZE_PREV_HSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_PSIZE_PREV_HSIZE_bf(const void *const hw, hri_isi_psize_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE ^= ISI_PSIZE_PREV_HSIZE(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_psize_reg_t hri_isi_read_PSIZE_PREV_HSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_PSIZE;
	tmp = (tmp & ISI_PSIZE_PREV_HSIZE_Msk) >> ISI_PSIZE_PREV_HSIZE_Pos;
	return tmp;
}

static inline void hri_isi_set_PSIZE_reg(const void *const hw, hri_isi_psize_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_psize_reg_t hri_isi_get_PSIZE_reg(const void *const hw, hri_isi_psize_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_PSIZE;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_PSIZE_reg(const void *const hw, hri_isi_psize_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_PSIZE_reg(const void *const hw, hri_isi_psize_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_PSIZE_reg(const void *const hw, hri_isi_psize_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PSIZE ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_psize_reg_t hri_isi_read_PSIZE_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_PSIZE;
}

static inline void hri_isi_set_PDECF_DEC_FACTOR_bf(const void *const hw, hri_isi_pdecf_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PDECF |= ISI_PDECF_DEC_FACTOR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_pdecf_reg_t hri_isi_get_PDECF_DEC_FACTOR_bf(const void *const hw, hri_isi_pdecf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_PDECF;
	tmp = (tmp & ISI_PDECF_DEC_FACTOR(mask)) >> ISI_PDECF_DEC_FACTOR_Pos;
	return tmp;
}

static inline void hri_isi_write_PDECF_DEC_FACTOR_bf(const void *const hw, hri_isi_pdecf_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_PDECF;
	tmp &= ~ISI_PDECF_DEC_FACTOR_Msk;
	tmp |= ISI_PDECF_DEC_FACTOR(data);
	((Isi *)hw)->ISI_PDECF = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_PDECF_DEC_FACTOR_bf(const void *const hw, hri_isi_pdecf_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PDECF &= ~ISI_PDECF_DEC_FACTOR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_PDECF_DEC_FACTOR_bf(const void *const hw, hri_isi_pdecf_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PDECF ^= ISI_PDECF_DEC_FACTOR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_pdecf_reg_t hri_isi_read_PDECF_DEC_FACTOR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_PDECF;
	tmp = (tmp & ISI_PDECF_DEC_FACTOR_Msk) >> ISI_PDECF_DEC_FACTOR_Pos;
	return tmp;
}

static inline void hri_isi_set_PDECF_reg(const void *const hw, hri_isi_pdecf_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PDECF |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_pdecf_reg_t hri_isi_get_PDECF_reg(const void *const hw, hri_isi_pdecf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_PDECF;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_PDECF_reg(const void *const hw, hri_isi_pdecf_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PDECF = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_PDECF_reg(const void *const hw, hri_isi_pdecf_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PDECF &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_PDECF_reg(const void *const hw, hri_isi_pdecf_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_PDECF ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_pdecf_reg_t hri_isi_read_PDECF_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_PDECF;
}

static inline void hri_isi_set_Y2R_SET0_C0_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 |= ISI_Y2R_SET0_C0(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_get_Y2R_SET0_C0_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp = (tmp & ISI_Y2R_SET0_C0(mask)) >> ISI_Y2R_SET0_C0_Pos;
	return tmp;
}

static inline void hri_isi_write_Y2R_SET0_C0_bf(const void *const hw, hri_isi_y2r_set0_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp &= ~ISI_Y2R_SET0_C0_Msk;
	tmp |= ISI_Y2R_SET0_C0(data);
	((Isi *)hw)->ISI_Y2R_SET0 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET0_C0_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 &= ~ISI_Y2R_SET0_C0(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET0_C0_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 ^= ISI_Y2R_SET0_C0(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_read_Y2R_SET0_C0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp = (tmp & ISI_Y2R_SET0_C0_Msk) >> ISI_Y2R_SET0_C0_Pos;
	return tmp;
}

static inline void hri_isi_set_Y2R_SET0_C1_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 |= ISI_Y2R_SET0_C1(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_get_Y2R_SET0_C1_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp = (tmp & ISI_Y2R_SET0_C1(mask)) >> ISI_Y2R_SET0_C1_Pos;
	return tmp;
}

static inline void hri_isi_write_Y2R_SET0_C1_bf(const void *const hw, hri_isi_y2r_set0_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp &= ~ISI_Y2R_SET0_C1_Msk;
	tmp |= ISI_Y2R_SET0_C1(data);
	((Isi *)hw)->ISI_Y2R_SET0 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET0_C1_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 &= ~ISI_Y2R_SET0_C1(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET0_C1_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 ^= ISI_Y2R_SET0_C1(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_read_Y2R_SET0_C1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp = (tmp & ISI_Y2R_SET0_C1_Msk) >> ISI_Y2R_SET0_C1_Pos;
	return tmp;
}

static inline void hri_isi_set_Y2R_SET0_C2_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 |= ISI_Y2R_SET0_C2(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_get_Y2R_SET0_C2_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp = (tmp & ISI_Y2R_SET0_C2(mask)) >> ISI_Y2R_SET0_C2_Pos;
	return tmp;
}

static inline void hri_isi_write_Y2R_SET0_C2_bf(const void *const hw, hri_isi_y2r_set0_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp &= ~ISI_Y2R_SET0_C2_Msk;
	tmp |= ISI_Y2R_SET0_C2(data);
	((Isi *)hw)->ISI_Y2R_SET0 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET0_C2_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 &= ~ISI_Y2R_SET0_C2(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET0_C2_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 ^= ISI_Y2R_SET0_C2(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_read_Y2R_SET0_C2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp = (tmp & ISI_Y2R_SET0_C2_Msk) >> ISI_Y2R_SET0_C2_Pos;
	return tmp;
}

static inline void hri_isi_set_Y2R_SET0_C3_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 |= ISI_Y2R_SET0_C3(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_get_Y2R_SET0_C3_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp = (tmp & ISI_Y2R_SET0_C3(mask)) >> ISI_Y2R_SET0_C3_Pos;
	return tmp;
}

static inline void hri_isi_write_Y2R_SET0_C3_bf(const void *const hw, hri_isi_y2r_set0_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp &= ~ISI_Y2R_SET0_C3_Msk;
	tmp |= ISI_Y2R_SET0_C3(data);
	((Isi *)hw)->ISI_Y2R_SET0 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET0_C3_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 &= ~ISI_Y2R_SET0_C3(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET0_C3_bf(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 ^= ISI_Y2R_SET0_C3(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_read_Y2R_SET0_C3_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp = (tmp & ISI_Y2R_SET0_C3_Msk) >> ISI_Y2R_SET0_C3_Pos;
	return tmp;
}

static inline void hri_isi_set_Y2R_SET0_reg(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_get_Y2R_SET0_reg(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET0;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_Y2R_SET0_reg(const void *const hw, hri_isi_y2r_set0_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET0_reg(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET0_reg(const void *const hw, hri_isi_y2r_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET0 ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set0_reg_t hri_isi_read_Y2R_SET0_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_Y2R_SET0;
}

static inline void hri_isi_set_Y2R_SET1_Yoff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 |= ISI_Y2R_SET1_Yoff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_Y2R_SET1_Yoff_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp = (tmp & ISI_Y2R_SET1_Yoff) >> ISI_Y2R_SET1_Yoff_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_Y2R_SET1_Yoff_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp &= ~ISI_Y2R_SET1_Yoff;
	tmp |= value << ISI_Y2R_SET1_Yoff_Pos;
	((Isi *)hw)->ISI_Y2R_SET1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET1_Yoff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 &= ~ISI_Y2R_SET1_Yoff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET1_Yoff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 ^= ISI_Y2R_SET1_Yoff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_Y2R_SET1_Croff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 |= ISI_Y2R_SET1_Croff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_Y2R_SET1_Croff_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp = (tmp & ISI_Y2R_SET1_Croff) >> ISI_Y2R_SET1_Croff_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_Y2R_SET1_Croff_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp &= ~ISI_Y2R_SET1_Croff;
	tmp |= value << ISI_Y2R_SET1_Croff_Pos;
	((Isi *)hw)->ISI_Y2R_SET1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET1_Croff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 &= ~ISI_Y2R_SET1_Croff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET1_Croff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 ^= ISI_Y2R_SET1_Croff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_Y2R_SET1_Cboff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 |= ISI_Y2R_SET1_Cboff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_Y2R_SET1_Cboff_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp = (tmp & ISI_Y2R_SET1_Cboff) >> ISI_Y2R_SET1_Cboff_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_Y2R_SET1_Cboff_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp &= ~ISI_Y2R_SET1_Cboff;
	tmp |= value << ISI_Y2R_SET1_Cboff_Pos;
	((Isi *)hw)->ISI_Y2R_SET1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET1_Cboff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 &= ~ISI_Y2R_SET1_Cboff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET1_Cboff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 ^= ISI_Y2R_SET1_Cboff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_Y2R_SET1_C4_bf(const void *const hw, hri_isi_y2r_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 |= ISI_Y2R_SET1_C4(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set1_reg_t hri_isi_get_Y2R_SET1_C4_bf(const void *const hw, hri_isi_y2r_set1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp = (tmp & ISI_Y2R_SET1_C4(mask)) >> ISI_Y2R_SET1_C4_Pos;
	return tmp;
}

static inline void hri_isi_write_Y2R_SET1_C4_bf(const void *const hw, hri_isi_y2r_set1_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp &= ~ISI_Y2R_SET1_C4_Msk;
	tmp |= ISI_Y2R_SET1_C4(data);
	((Isi *)hw)->ISI_Y2R_SET1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET1_C4_bf(const void *const hw, hri_isi_y2r_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 &= ~ISI_Y2R_SET1_C4(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET1_C4_bf(const void *const hw, hri_isi_y2r_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 ^= ISI_Y2R_SET1_C4(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set1_reg_t hri_isi_read_Y2R_SET1_C4_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp = (tmp & ISI_Y2R_SET1_C4_Msk) >> ISI_Y2R_SET1_C4_Pos;
	return tmp;
}

static inline void hri_isi_set_Y2R_SET1_reg(const void *const hw, hri_isi_y2r_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set1_reg_t hri_isi_get_Y2R_SET1_reg(const void *const hw, hri_isi_y2r_set1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_Y2R_SET1;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_Y2R_SET1_reg(const void *const hw, hri_isi_y2r_set1_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_Y2R_SET1_reg(const void *const hw, hri_isi_y2r_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_Y2R_SET1_reg(const void *const hw, hri_isi_y2r_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_Y2R_SET1 ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_y2r_set1_reg_t hri_isi_read_Y2R_SET1_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_Y2R_SET1;
}

static inline void hri_isi_set_R2Y_SET0_Roff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 |= ISI_R2Y_SET0_Roff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_R2Y_SET0_Roff_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp = (tmp & ISI_R2Y_SET0_Roff) >> ISI_R2Y_SET0_Roff_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_R2Y_SET0_Roff_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp &= ~ISI_R2Y_SET0_Roff;
	tmp |= value << ISI_R2Y_SET0_Roff_Pos;
	((Isi *)hw)->ISI_R2Y_SET0 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET0_Roff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 &= ~ISI_R2Y_SET0_Roff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET0_Roff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 ^= ISI_R2Y_SET0_Roff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_R2Y_SET0_C0_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 |= ISI_R2Y_SET0_C0(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set0_reg_t hri_isi_get_R2Y_SET0_C0_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp = (tmp & ISI_R2Y_SET0_C0(mask)) >> ISI_R2Y_SET0_C0_Pos;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET0_C0_bf(const void *const hw, hri_isi_r2y_set0_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp &= ~ISI_R2Y_SET0_C0_Msk;
	tmp |= ISI_R2Y_SET0_C0(data);
	((Isi *)hw)->ISI_R2Y_SET0 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET0_C0_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 &= ~ISI_R2Y_SET0_C0(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET0_C0_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 ^= ISI_R2Y_SET0_C0(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set0_reg_t hri_isi_read_R2Y_SET0_C0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp = (tmp & ISI_R2Y_SET0_C0_Msk) >> ISI_R2Y_SET0_C0_Pos;
	return tmp;
}

static inline void hri_isi_set_R2Y_SET0_C1_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 |= ISI_R2Y_SET0_C1(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set0_reg_t hri_isi_get_R2Y_SET0_C1_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp = (tmp & ISI_R2Y_SET0_C1(mask)) >> ISI_R2Y_SET0_C1_Pos;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET0_C1_bf(const void *const hw, hri_isi_r2y_set0_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp &= ~ISI_R2Y_SET0_C1_Msk;
	tmp |= ISI_R2Y_SET0_C1(data);
	((Isi *)hw)->ISI_R2Y_SET0 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET0_C1_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 &= ~ISI_R2Y_SET0_C1(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET0_C1_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 ^= ISI_R2Y_SET0_C1(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set0_reg_t hri_isi_read_R2Y_SET0_C1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp = (tmp & ISI_R2Y_SET0_C1_Msk) >> ISI_R2Y_SET0_C1_Pos;
	return tmp;
}

static inline void hri_isi_set_R2Y_SET0_C2_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 |= ISI_R2Y_SET0_C2(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set0_reg_t hri_isi_get_R2Y_SET0_C2_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp = (tmp & ISI_R2Y_SET0_C2(mask)) >> ISI_R2Y_SET0_C2_Pos;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET0_C2_bf(const void *const hw, hri_isi_r2y_set0_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp &= ~ISI_R2Y_SET0_C2_Msk;
	tmp |= ISI_R2Y_SET0_C2(data);
	((Isi *)hw)->ISI_R2Y_SET0 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET0_C2_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 &= ~ISI_R2Y_SET0_C2(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET0_C2_bf(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 ^= ISI_R2Y_SET0_C2(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set0_reg_t hri_isi_read_R2Y_SET0_C2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp = (tmp & ISI_R2Y_SET0_C2_Msk) >> ISI_R2Y_SET0_C2_Pos;
	return tmp;
}

static inline void hri_isi_set_R2Y_SET0_reg(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set0_reg_t hri_isi_get_R2Y_SET0_reg(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET0;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET0_reg(const void *const hw, hri_isi_r2y_set0_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET0_reg(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET0_reg(const void *const hw, hri_isi_r2y_set0_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET0 ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set0_reg_t hri_isi_read_R2Y_SET0_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_R2Y_SET0;
}

static inline void hri_isi_set_R2Y_SET1_Goff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 |= ISI_R2Y_SET1_Goff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_R2Y_SET1_Goff_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp = (tmp & ISI_R2Y_SET1_Goff) >> ISI_R2Y_SET1_Goff_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_R2Y_SET1_Goff_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp &= ~ISI_R2Y_SET1_Goff;
	tmp |= value << ISI_R2Y_SET1_Goff_Pos;
	((Isi *)hw)->ISI_R2Y_SET1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET1_Goff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 &= ~ISI_R2Y_SET1_Goff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET1_Goff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 ^= ISI_R2Y_SET1_Goff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_R2Y_SET1_C3_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 |= ISI_R2Y_SET1_C3(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set1_reg_t hri_isi_get_R2Y_SET1_C3_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp = (tmp & ISI_R2Y_SET1_C3(mask)) >> ISI_R2Y_SET1_C3_Pos;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET1_C3_bf(const void *const hw, hri_isi_r2y_set1_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp &= ~ISI_R2Y_SET1_C3_Msk;
	tmp |= ISI_R2Y_SET1_C3(data);
	((Isi *)hw)->ISI_R2Y_SET1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET1_C3_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 &= ~ISI_R2Y_SET1_C3(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET1_C3_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 ^= ISI_R2Y_SET1_C3(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set1_reg_t hri_isi_read_R2Y_SET1_C3_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp = (tmp & ISI_R2Y_SET1_C3_Msk) >> ISI_R2Y_SET1_C3_Pos;
	return tmp;
}

static inline void hri_isi_set_R2Y_SET1_C4_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 |= ISI_R2Y_SET1_C4(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set1_reg_t hri_isi_get_R2Y_SET1_C4_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp = (tmp & ISI_R2Y_SET1_C4(mask)) >> ISI_R2Y_SET1_C4_Pos;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET1_C4_bf(const void *const hw, hri_isi_r2y_set1_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp &= ~ISI_R2Y_SET1_C4_Msk;
	tmp |= ISI_R2Y_SET1_C4(data);
	((Isi *)hw)->ISI_R2Y_SET1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET1_C4_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 &= ~ISI_R2Y_SET1_C4(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET1_C4_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 ^= ISI_R2Y_SET1_C4(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set1_reg_t hri_isi_read_R2Y_SET1_C4_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp = (tmp & ISI_R2Y_SET1_C4_Msk) >> ISI_R2Y_SET1_C4_Pos;
	return tmp;
}

static inline void hri_isi_set_R2Y_SET1_C5_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 |= ISI_R2Y_SET1_C5(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set1_reg_t hri_isi_get_R2Y_SET1_C5_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp = (tmp & ISI_R2Y_SET1_C5(mask)) >> ISI_R2Y_SET1_C5_Pos;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET1_C5_bf(const void *const hw, hri_isi_r2y_set1_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp &= ~ISI_R2Y_SET1_C5_Msk;
	tmp |= ISI_R2Y_SET1_C5(data);
	((Isi *)hw)->ISI_R2Y_SET1 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET1_C5_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 &= ~ISI_R2Y_SET1_C5(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET1_C5_bf(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 ^= ISI_R2Y_SET1_C5(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set1_reg_t hri_isi_read_R2Y_SET1_C5_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp = (tmp & ISI_R2Y_SET1_C5_Msk) >> ISI_R2Y_SET1_C5_Pos;
	return tmp;
}

static inline void hri_isi_set_R2Y_SET1_reg(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set1_reg_t hri_isi_get_R2Y_SET1_reg(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET1;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET1_reg(const void *const hw, hri_isi_r2y_set1_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET1_reg(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET1_reg(const void *const hw, hri_isi_r2y_set1_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET1 ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set1_reg_t hri_isi_read_R2Y_SET1_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_R2Y_SET1;
}

static inline void hri_isi_set_R2Y_SET2_Boff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 |= ISI_R2Y_SET2_Boff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_R2Y_SET2_Boff_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp = (tmp & ISI_R2Y_SET2_Boff) >> ISI_R2Y_SET2_Boff_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_R2Y_SET2_Boff_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp &= ~ISI_R2Y_SET2_Boff;
	tmp |= value << ISI_R2Y_SET2_Boff_Pos;
	((Isi *)hw)->ISI_R2Y_SET2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET2_Boff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 &= ~ISI_R2Y_SET2_Boff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET2_Boff_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 ^= ISI_R2Y_SET2_Boff;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_R2Y_SET2_C6_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 |= ISI_R2Y_SET2_C6(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set2_reg_t hri_isi_get_R2Y_SET2_C6_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp = (tmp & ISI_R2Y_SET2_C6(mask)) >> ISI_R2Y_SET2_C6_Pos;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET2_C6_bf(const void *const hw, hri_isi_r2y_set2_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp &= ~ISI_R2Y_SET2_C6_Msk;
	tmp |= ISI_R2Y_SET2_C6(data);
	((Isi *)hw)->ISI_R2Y_SET2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET2_C6_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 &= ~ISI_R2Y_SET2_C6(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET2_C6_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 ^= ISI_R2Y_SET2_C6(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set2_reg_t hri_isi_read_R2Y_SET2_C6_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp = (tmp & ISI_R2Y_SET2_C6_Msk) >> ISI_R2Y_SET2_C6_Pos;
	return tmp;
}

static inline void hri_isi_set_R2Y_SET2_C7_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 |= ISI_R2Y_SET2_C7(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set2_reg_t hri_isi_get_R2Y_SET2_C7_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp = (tmp & ISI_R2Y_SET2_C7(mask)) >> ISI_R2Y_SET2_C7_Pos;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET2_C7_bf(const void *const hw, hri_isi_r2y_set2_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp &= ~ISI_R2Y_SET2_C7_Msk;
	tmp |= ISI_R2Y_SET2_C7(data);
	((Isi *)hw)->ISI_R2Y_SET2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET2_C7_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 &= ~ISI_R2Y_SET2_C7(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET2_C7_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 ^= ISI_R2Y_SET2_C7(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set2_reg_t hri_isi_read_R2Y_SET2_C7_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp = (tmp & ISI_R2Y_SET2_C7_Msk) >> ISI_R2Y_SET2_C7_Pos;
	return tmp;
}

static inline void hri_isi_set_R2Y_SET2_C8_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 |= ISI_R2Y_SET2_C8(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set2_reg_t hri_isi_get_R2Y_SET2_C8_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp = (tmp & ISI_R2Y_SET2_C8(mask)) >> ISI_R2Y_SET2_C8_Pos;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET2_C8_bf(const void *const hw, hri_isi_r2y_set2_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp &= ~ISI_R2Y_SET2_C8_Msk;
	tmp |= ISI_R2Y_SET2_C8(data);
	((Isi *)hw)->ISI_R2Y_SET2 = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET2_C8_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 &= ~ISI_R2Y_SET2_C8(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET2_C8_bf(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 ^= ISI_R2Y_SET2_C8(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set2_reg_t hri_isi_read_R2Y_SET2_C8_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp = (tmp & ISI_R2Y_SET2_C8_Msk) >> ISI_R2Y_SET2_C8_Pos;
	return tmp;
}

static inline void hri_isi_set_R2Y_SET2_reg(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set2_reg_t hri_isi_get_R2Y_SET2_reg(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_R2Y_SET2;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_R2Y_SET2_reg(const void *const hw, hri_isi_r2y_set2_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_R2Y_SET2_reg(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_R2Y_SET2_reg(const void *const hw, hri_isi_r2y_set2_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_R2Y_SET2 ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_r2y_set2_reg_t hri_isi_read_R2Y_SET2_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_R2Y_SET2;
}

static inline void hri_isi_set_DMA_P_ADDR_P_ADDR_bf(const void *const hw, hri_isi_dma_p_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_ADDR |= ISI_DMA_P_ADDR_P_ADDR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_addr_reg_t hri_isi_get_DMA_P_ADDR_P_ADDR_bf(const void *const        hw,
                                                                        hri_isi_dma_p_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_ADDR;
	tmp = (tmp & ISI_DMA_P_ADDR_P_ADDR(mask)) >> ISI_DMA_P_ADDR_P_ADDR_Pos;
	return tmp;
}

static inline void hri_isi_write_DMA_P_ADDR_P_ADDR_bf(const void *const hw, hri_isi_dma_p_addr_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_P_ADDR;
	tmp &= ~ISI_DMA_P_ADDR_P_ADDR_Msk;
	tmp |= ISI_DMA_P_ADDR_P_ADDR(data);
	((Isi *)hw)->ISI_DMA_P_ADDR = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_P_ADDR_P_ADDR_bf(const void *const hw, hri_isi_dma_p_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_ADDR &= ~ISI_DMA_P_ADDR_P_ADDR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_P_ADDR_P_ADDR_bf(const void *const hw, hri_isi_dma_p_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_ADDR ^= ISI_DMA_P_ADDR_P_ADDR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_addr_reg_t hri_isi_read_DMA_P_ADDR_P_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_ADDR;
	tmp = (tmp & ISI_DMA_P_ADDR_P_ADDR_Msk) >> ISI_DMA_P_ADDR_P_ADDR_Pos;
	return tmp;
}

static inline void hri_isi_set_DMA_P_ADDR_reg(const void *const hw, hri_isi_dma_p_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_ADDR |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_addr_reg_t hri_isi_get_DMA_P_ADDR_reg(const void *const hw, hri_isi_dma_p_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_ADDR;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_DMA_P_ADDR_reg(const void *const hw, hri_isi_dma_p_addr_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_ADDR = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_P_ADDR_reg(const void *const hw, hri_isi_dma_p_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_ADDR &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_P_ADDR_reg(const void *const hw, hri_isi_dma_p_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_ADDR ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_addr_reg_t hri_isi_read_DMA_P_ADDR_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_DMA_P_ADDR;
}

static inline void hri_isi_set_DMA_P_CTRL_P_FETCH_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL |= ISI_DMA_P_CTRL_P_FETCH;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_DMA_P_CTRL_P_FETCH_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_CTRL;
	tmp = (tmp & ISI_DMA_P_CTRL_P_FETCH) >> ISI_DMA_P_CTRL_P_FETCH_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_DMA_P_CTRL_P_FETCH_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_P_CTRL;
	tmp &= ~ISI_DMA_P_CTRL_P_FETCH;
	tmp |= value << ISI_DMA_P_CTRL_P_FETCH_Pos;
	((Isi *)hw)->ISI_DMA_P_CTRL = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_P_CTRL_P_FETCH_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL &= ~ISI_DMA_P_CTRL_P_FETCH;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_P_CTRL_P_FETCH_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL ^= ISI_DMA_P_CTRL_P_FETCH;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_DMA_P_CTRL_P_WB_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL |= ISI_DMA_P_CTRL_P_WB;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_DMA_P_CTRL_P_WB_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_CTRL;
	tmp = (tmp & ISI_DMA_P_CTRL_P_WB) >> ISI_DMA_P_CTRL_P_WB_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_DMA_P_CTRL_P_WB_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_P_CTRL;
	tmp &= ~ISI_DMA_P_CTRL_P_WB;
	tmp |= value << ISI_DMA_P_CTRL_P_WB_Pos;
	((Isi *)hw)->ISI_DMA_P_CTRL = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_P_CTRL_P_WB_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL &= ~ISI_DMA_P_CTRL_P_WB;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_P_CTRL_P_WB_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL ^= ISI_DMA_P_CTRL_P_WB;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_DMA_P_CTRL_P_IEN_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL |= ISI_DMA_P_CTRL_P_IEN;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_DMA_P_CTRL_P_IEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_CTRL;
	tmp = (tmp & ISI_DMA_P_CTRL_P_IEN) >> ISI_DMA_P_CTRL_P_IEN_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_DMA_P_CTRL_P_IEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_P_CTRL;
	tmp &= ~ISI_DMA_P_CTRL_P_IEN;
	tmp |= value << ISI_DMA_P_CTRL_P_IEN_Pos;
	((Isi *)hw)->ISI_DMA_P_CTRL = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_P_CTRL_P_IEN_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL &= ~ISI_DMA_P_CTRL_P_IEN;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_P_CTRL_P_IEN_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL ^= ISI_DMA_P_CTRL_P_IEN;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_DMA_P_CTRL_P_DONE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL |= ISI_DMA_P_CTRL_P_DONE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_DMA_P_CTRL_P_DONE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_CTRL;
	tmp = (tmp & ISI_DMA_P_CTRL_P_DONE) >> ISI_DMA_P_CTRL_P_DONE_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_DMA_P_CTRL_P_DONE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_P_CTRL;
	tmp &= ~ISI_DMA_P_CTRL_P_DONE;
	tmp |= value << ISI_DMA_P_CTRL_P_DONE_Pos;
	((Isi *)hw)->ISI_DMA_P_CTRL = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_P_CTRL_P_DONE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL &= ~ISI_DMA_P_CTRL_P_DONE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_P_CTRL_P_DONE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL ^= ISI_DMA_P_CTRL_P_DONE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_DMA_P_CTRL_reg(const void *const hw, hri_isi_dma_p_ctrl_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_ctrl_reg_t hri_isi_get_DMA_P_CTRL_reg(const void *const hw, hri_isi_dma_p_ctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_CTRL;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_DMA_P_CTRL_reg(const void *const hw, hri_isi_dma_p_ctrl_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_P_CTRL_reg(const void *const hw, hri_isi_dma_p_ctrl_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_P_CTRL_reg(const void *const hw, hri_isi_dma_p_ctrl_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_CTRL ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_ctrl_reg_t hri_isi_read_DMA_P_CTRL_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_DMA_P_CTRL;
}

static inline void hri_isi_set_DMA_P_DSCR_P_DSCR_bf(const void *const hw, hri_isi_dma_p_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_DSCR |= ISI_DMA_P_DSCR_P_DSCR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_dscr_reg_t hri_isi_get_DMA_P_DSCR_P_DSCR_bf(const void *const        hw,
                                                                        hri_isi_dma_p_dscr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_DSCR;
	tmp = (tmp & ISI_DMA_P_DSCR_P_DSCR(mask)) >> ISI_DMA_P_DSCR_P_DSCR_Pos;
	return tmp;
}

static inline void hri_isi_write_DMA_P_DSCR_P_DSCR_bf(const void *const hw, hri_isi_dma_p_dscr_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_P_DSCR;
	tmp &= ~ISI_DMA_P_DSCR_P_DSCR_Msk;
	tmp |= ISI_DMA_P_DSCR_P_DSCR(data);
	((Isi *)hw)->ISI_DMA_P_DSCR = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_P_DSCR_P_DSCR_bf(const void *const hw, hri_isi_dma_p_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_DSCR &= ~ISI_DMA_P_DSCR_P_DSCR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_P_DSCR_P_DSCR_bf(const void *const hw, hri_isi_dma_p_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_DSCR ^= ISI_DMA_P_DSCR_P_DSCR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_dscr_reg_t hri_isi_read_DMA_P_DSCR_P_DSCR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_DSCR;
	tmp = (tmp & ISI_DMA_P_DSCR_P_DSCR_Msk) >> ISI_DMA_P_DSCR_P_DSCR_Pos;
	return tmp;
}

static inline void hri_isi_set_DMA_P_DSCR_reg(const void *const hw, hri_isi_dma_p_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_DSCR |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_dscr_reg_t hri_isi_get_DMA_P_DSCR_reg(const void *const hw, hri_isi_dma_p_dscr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_P_DSCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_DMA_P_DSCR_reg(const void *const hw, hri_isi_dma_p_dscr_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_DSCR = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_P_DSCR_reg(const void *const hw, hri_isi_dma_p_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_DSCR &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_P_DSCR_reg(const void *const hw, hri_isi_dma_p_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_P_DSCR ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_p_dscr_reg_t hri_isi_read_DMA_P_DSCR_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_DMA_P_DSCR;
}

static inline void hri_isi_set_DMA_C_ADDR_C_ADDR_bf(const void *const hw, hri_isi_dma_c_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_ADDR |= ISI_DMA_C_ADDR_C_ADDR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_addr_reg_t hri_isi_get_DMA_C_ADDR_C_ADDR_bf(const void *const        hw,
                                                                        hri_isi_dma_c_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_ADDR;
	tmp = (tmp & ISI_DMA_C_ADDR_C_ADDR(mask)) >> ISI_DMA_C_ADDR_C_ADDR_Pos;
	return tmp;
}

static inline void hri_isi_write_DMA_C_ADDR_C_ADDR_bf(const void *const hw, hri_isi_dma_c_addr_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_C_ADDR;
	tmp &= ~ISI_DMA_C_ADDR_C_ADDR_Msk;
	tmp |= ISI_DMA_C_ADDR_C_ADDR(data);
	((Isi *)hw)->ISI_DMA_C_ADDR = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_C_ADDR_C_ADDR_bf(const void *const hw, hri_isi_dma_c_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_ADDR &= ~ISI_DMA_C_ADDR_C_ADDR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_C_ADDR_C_ADDR_bf(const void *const hw, hri_isi_dma_c_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_ADDR ^= ISI_DMA_C_ADDR_C_ADDR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_addr_reg_t hri_isi_read_DMA_C_ADDR_C_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_ADDR;
	tmp = (tmp & ISI_DMA_C_ADDR_C_ADDR_Msk) >> ISI_DMA_C_ADDR_C_ADDR_Pos;
	return tmp;
}

static inline void hri_isi_set_DMA_C_ADDR_reg(const void *const hw, hri_isi_dma_c_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_ADDR |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_addr_reg_t hri_isi_get_DMA_C_ADDR_reg(const void *const hw, hri_isi_dma_c_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_ADDR;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_DMA_C_ADDR_reg(const void *const hw, hri_isi_dma_c_addr_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_ADDR = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_C_ADDR_reg(const void *const hw, hri_isi_dma_c_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_ADDR &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_C_ADDR_reg(const void *const hw, hri_isi_dma_c_addr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_ADDR ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_addr_reg_t hri_isi_read_DMA_C_ADDR_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_DMA_C_ADDR;
}

static inline void hri_isi_set_DMA_C_CTRL_C_FETCH_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL |= ISI_DMA_C_CTRL_C_FETCH;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_DMA_C_CTRL_C_FETCH_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_CTRL;
	tmp = (tmp & ISI_DMA_C_CTRL_C_FETCH) >> ISI_DMA_C_CTRL_C_FETCH_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_DMA_C_CTRL_C_FETCH_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_C_CTRL;
	tmp &= ~ISI_DMA_C_CTRL_C_FETCH;
	tmp |= value << ISI_DMA_C_CTRL_C_FETCH_Pos;
	((Isi *)hw)->ISI_DMA_C_CTRL = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_C_CTRL_C_FETCH_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL &= ~ISI_DMA_C_CTRL_C_FETCH;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_C_CTRL_C_FETCH_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL ^= ISI_DMA_C_CTRL_C_FETCH;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_DMA_C_CTRL_C_WB_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL |= ISI_DMA_C_CTRL_C_WB;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_DMA_C_CTRL_C_WB_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_CTRL;
	tmp = (tmp & ISI_DMA_C_CTRL_C_WB) >> ISI_DMA_C_CTRL_C_WB_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_DMA_C_CTRL_C_WB_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_C_CTRL;
	tmp &= ~ISI_DMA_C_CTRL_C_WB;
	tmp |= value << ISI_DMA_C_CTRL_C_WB_Pos;
	((Isi *)hw)->ISI_DMA_C_CTRL = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_C_CTRL_C_WB_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL &= ~ISI_DMA_C_CTRL_C_WB;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_C_CTRL_C_WB_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL ^= ISI_DMA_C_CTRL_C_WB;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_DMA_C_CTRL_C_IEN_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL |= ISI_DMA_C_CTRL_C_IEN;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_DMA_C_CTRL_C_IEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_CTRL;
	tmp = (tmp & ISI_DMA_C_CTRL_C_IEN) >> ISI_DMA_C_CTRL_C_IEN_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_DMA_C_CTRL_C_IEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_C_CTRL;
	tmp &= ~ISI_DMA_C_CTRL_C_IEN;
	tmp |= value << ISI_DMA_C_CTRL_C_IEN_Pos;
	((Isi *)hw)->ISI_DMA_C_CTRL = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_C_CTRL_C_IEN_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL &= ~ISI_DMA_C_CTRL_C_IEN;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_C_CTRL_C_IEN_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL ^= ISI_DMA_C_CTRL_C_IEN;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_DMA_C_CTRL_C_DONE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL |= ISI_DMA_C_CTRL_C_DONE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_DMA_C_CTRL_C_DONE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_CTRL;
	tmp = (tmp & ISI_DMA_C_CTRL_C_DONE) >> ISI_DMA_C_CTRL_C_DONE_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_DMA_C_CTRL_C_DONE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_C_CTRL;
	tmp &= ~ISI_DMA_C_CTRL_C_DONE;
	tmp |= value << ISI_DMA_C_CTRL_C_DONE_Pos;
	((Isi *)hw)->ISI_DMA_C_CTRL = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_C_CTRL_C_DONE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL &= ~ISI_DMA_C_CTRL_C_DONE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_C_CTRL_C_DONE_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL ^= ISI_DMA_C_CTRL_C_DONE;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_DMA_C_CTRL_reg(const void *const hw, hri_isi_dma_c_ctrl_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_ctrl_reg_t hri_isi_get_DMA_C_CTRL_reg(const void *const hw, hri_isi_dma_c_ctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_CTRL;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_DMA_C_CTRL_reg(const void *const hw, hri_isi_dma_c_ctrl_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_C_CTRL_reg(const void *const hw, hri_isi_dma_c_ctrl_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_C_CTRL_reg(const void *const hw, hri_isi_dma_c_ctrl_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_CTRL ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_ctrl_reg_t hri_isi_read_DMA_C_CTRL_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_DMA_C_CTRL;
}

static inline void hri_isi_set_DMA_C_DSCR_C_DSCR_bf(const void *const hw, hri_isi_dma_c_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_DSCR |= ISI_DMA_C_DSCR_C_DSCR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_dscr_reg_t hri_isi_get_DMA_C_DSCR_C_DSCR_bf(const void *const        hw,
                                                                        hri_isi_dma_c_dscr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_DSCR;
	tmp = (tmp & ISI_DMA_C_DSCR_C_DSCR(mask)) >> ISI_DMA_C_DSCR_C_DSCR_Pos;
	return tmp;
}

static inline void hri_isi_write_DMA_C_DSCR_C_DSCR_bf(const void *const hw, hri_isi_dma_c_dscr_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_DMA_C_DSCR;
	tmp &= ~ISI_DMA_C_DSCR_C_DSCR_Msk;
	tmp |= ISI_DMA_C_DSCR_C_DSCR(data);
	((Isi *)hw)->ISI_DMA_C_DSCR = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_C_DSCR_C_DSCR_bf(const void *const hw, hri_isi_dma_c_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_DSCR &= ~ISI_DMA_C_DSCR_C_DSCR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_C_DSCR_C_DSCR_bf(const void *const hw, hri_isi_dma_c_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_DSCR ^= ISI_DMA_C_DSCR_C_DSCR(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_dscr_reg_t hri_isi_read_DMA_C_DSCR_C_DSCR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_DSCR;
	tmp = (tmp & ISI_DMA_C_DSCR_C_DSCR_Msk) >> ISI_DMA_C_DSCR_C_DSCR_Pos;
	return tmp;
}

static inline void hri_isi_set_DMA_C_DSCR_reg(const void *const hw, hri_isi_dma_c_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_DSCR |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_dscr_reg_t hri_isi_get_DMA_C_DSCR_reg(const void *const hw, hri_isi_dma_c_dscr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_DMA_C_DSCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_DMA_C_DSCR_reg(const void *const hw, hri_isi_dma_c_dscr_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_DSCR = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_DMA_C_DSCR_reg(const void *const hw, hri_isi_dma_c_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_DSCR &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_DMA_C_DSCR_reg(const void *const hw, hri_isi_dma_c_dscr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_DMA_C_DSCR ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_dma_c_dscr_reg_t hri_isi_read_DMA_C_DSCR_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_DMA_C_DSCR;
}

static inline void hri_isi_set_WPMR_WPEN_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR |= ISI_WPMR_WPEN;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_isi_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_WPMR;
	tmp = (tmp & ISI_WPMR_WPEN) >> ISI_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_isi_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_WPMR;
	tmp &= ~ISI_WPMR_WPEN;
	tmp |= value << ISI_WPMR_WPEN_Pos;
	((Isi *)hw)->ISI_WPMR = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_WPMR_WPEN_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR &= ~ISI_WPMR_WPEN;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_WPMR_WPEN_bit(const void *const hw)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR ^= ISI_WPMR_WPEN;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_set_WPMR_WPKEY_bf(const void *const hw, hri_isi_wpmr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR |= ISI_WPMR_WPKEY(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_wpmr_reg_t hri_isi_get_WPMR_WPKEY_bf(const void *const hw, hri_isi_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_WPMR;
	tmp = (tmp & ISI_WPMR_WPKEY(mask)) >> ISI_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_isi_write_WPMR_WPKEY_bf(const void *const hw, hri_isi_wpmr_reg_t data)
{
	uint32_t tmp;
	ISI_CRITICAL_SECTION_ENTER();
	tmp = ((Isi *)hw)->ISI_WPMR;
	tmp &= ~ISI_WPMR_WPKEY_Msk;
	tmp |= ISI_WPMR_WPKEY(data);
	((Isi *)hw)->ISI_WPMR = tmp;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_WPMR_WPKEY_bf(const void *const hw, hri_isi_wpmr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR &= ~ISI_WPMR_WPKEY(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_WPMR_WPKEY_bf(const void *const hw, hri_isi_wpmr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR ^= ISI_WPMR_WPKEY(mask);
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_wpmr_reg_t hri_isi_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_WPMR;
	tmp = (tmp & ISI_WPMR_WPKEY_Msk) >> ISI_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_isi_set_WPMR_reg(const void *const hw, hri_isi_wpmr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR |= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_wpmr_reg_t hri_isi_get_WPMR_reg(const void *const hw, hri_isi_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Isi *)hw)->ISI_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_isi_write_WPMR_reg(const void *const hw, hri_isi_wpmr_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_clear_WPMR_reg(const void *const hw, hri_isi_wpmr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR &= ~mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_isi_toggle_WPMR_reg(const void *const hw, hri_isi_wpmr_reg_t mask)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_WPMR ^= mask;
	ISI_CRITICAL_SECTION_LEAVE();
}

static inline hri_isi_wpmr_reg_t hri_isi_read_WPMR_reg(const void *const hw)
{
	return ((Isi *)hw)->ISI_WPMR;
}

static inline void hri_isi_write_CR_reg(const void *const hw, hri_isi_cr_reg_t data)
{
	ISI_CRITICAL_SECTION_ENTER();
	((Isi *)hw)->ISI_CR = data;
	ISI_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_ISI_E70B_H_INCLUDED */
#endif /* _SAME70_ISI_COMPONENT_ */
