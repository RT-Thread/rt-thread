/**
 * \file
 *
 * \brief SAM I2SC
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

#ifdef _SAME70_I2SC_COMPONENT_
#ifndef _HRI_I2SC_E70B_H_INCLUDED_
#define _HRI_I2SC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_I2SC_CRITICAL_SECTIONS)
#define I2SC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define I2SC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define I2SC_CRITICAL_SECTION_ENTER()
#define I2SC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_i2sc_cr_reg_t;
typedef uint32_t hri_i2sc_imr_reg_t;
typedef uint32_t hri_i2sc_mr_reg_t;
typedef uint32_t hri_i2sc_rhr_reg_t;
typedef uint32_t hri_i2sc_scr_reg_t;
typedef uint32_t hri_i2sc_sr_reg_t;
typedef uint32_t hri_i2sc_ssr_reg_t;
typedef uint32_t hri_i2sc_thr_reg_t;

static inline void hri_i2sc_set_IMR_RXRDY_bit(const void *const hw)
{
	((I2sc *)hw)->I2SC_IER = I2SC_IMR_RXRDY;
}

static inline bool hri_i2sc_get_IMR_RXRDY_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_IMR & I2SC_IMR_RXRDY) >> I2SC_IMR_RXRDY_Pos;
}

static inline void hri_i2sc_write_IMR_RXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((I2sc *)hw)->I2SC_IDR = I2SC_IMR_RXRDY;
	} else {
		((I2sc *)hw)->I2SC_IER = I2SC_IMR_RXRDY;
	}
}

static inline void hri_i2sc_clear_IMR_RXRDY_bit(const void *const hw)
{
	((I2sc *)hw)->I2SC_IDR = I2SC_IMR_RXRDY;
}

static inline void hri_i2sc_set_IMR_RXOR_bit(const void *const hw)
{
	((I2sc *)hw)->I2SC_IER = I2SC_IMR_RXOR;
}

static inline bool hri_i2sc_get_IMR_RXOR_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_IMR & I2SC_IMR_RXOR) >> I2SC_IMR_RXOR_Pos;
}

static inline void hri_i2sc_write_IMR_RXOR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((I2sc *)hw)->I2SC_IDR = I2SC_IMR_RXOR;
	} else {
		((I2sc *)hw)->I2SC_IER = I2SC_IMR_RXOR;
	}
}

static inline void hri_i2sc_clear_IMR_RXOR_bit(const void *const hw)
{
	((I2sc *)hw)->I2SC_IDR = I2SC_IMR_RXOR;
}

static inline void hri_i2sc_set_IMR_TXRDY_bit(const void *const hw)
{
	((I2sc *)hw)->I2SC_IER = I2SC_IMR_TXRDY;
}

static inline bool hri_i2sc_get_IMR_TXRDY_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_IMR & I2SC_IMR_TXRDY) >> I2SC_IMR_TXRDY_Pos;
}

static inline void hri_i2sc_write_IMR_TXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((I2sc *)hw)->I2SC_IDR = I2SC_IMR_TXRDY;
	} else {
		((I2sc *)hw)->I2SC_IER = I2SC_IMR_TXRDY;
	}
}

static inline void hri_i2sc_clear_IMR_TXRDY_bit(const void *const hw)
{
	((I2sc *)hw)->I2SC_IDR = I2SC_IMR_TXRDY;
}

static inline void hri_i2sc_set_IMR_TXUR_bit(const void *const hw)
{
	((I2sc *)hw)->I2SC_IER = I2SC_IMR_TXUR;
}

static inline bool hri_i2sc_get_IMR_TXUR_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_IMR & I2SC_IMR_TXUR) >> I2SC_IMR_TXUR_Pos;
}

static inline void hri_i2sc_write_IMR_TXUR_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((I2sc *)hw)->I2SC_IDR = I2SC_IMR_TXUR;
	} else {
		((I2sc *)hw)->I2SC_IER = I2SC_IMR_TXUR;
	}
}

static inline void hri_i2sc_clear_IMR_TXUR_bit(const void *const hw)
{
	((I2sc *)hw)->I2SC_IDR = I2SC_IMR_TXUR;
}

static inline void hri_i2sc_set_IMR_reg(const void *const hw, hri_i2sc_imr_reg_t mask)
{
	((I2sc *)hw)->I2SC_IER = mask;
}

static inline hri_i2sc_imr_reg_t hri_i2sc_get_IMR_reg(const void *const hw, hri_i2sc_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_i2sc_imr_reg_t hri_i2sc_read_IMR_reg(const void *const hw)
{
	return ((I2sc *)hw)->I2SC_IMR;
}

static inline void hri_i2sc_write_IMR_reg(const void *const hw, hri_i2sc_imr_reg_t data)
{
	((I2sc *)hw)->I2SC_IER = data;
	((I2sc *)hw)->I2SC_IDR = ~data;
}

static inline void hri_i2sc_clear_IMR_reg(const void *const hw, hri_i2sc_imr_reg_t mask)
{
	((I2sc *)hw)->I2SC_IDR = mask;
}

static inline bool hri_i2sc_get_SR_RXEN_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_RXEN) > 0;
}

static inline bool hri_i2sc_get_SR_RXRDY_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_RXRDY) > 0;
}

static inline bool hri_i2sc_get_SR_RXOR_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_RXOR) > 0;
}

static inline bool hri_i2sc_get_SR_TXEN_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_TXEN) > 0;
}

static inline bool hri_i2sc_get_SR_TXRDY_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_TXRDY) > 0;
}

static inline bool hri_i2sc_get_SR_TXUR_bit(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_TXUR) > 0;
}

static inline hri_i2sc_sr_reg_t hri_i2sc_get_SR_RXORCH_bf(const void *const hw, hri_i2sc_sr_reg_t mask)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_RXORCH(mask)) >> I2SC_SR_RXORCH_Pos;
}

static inline hri_i2sc_sr_reg_t hri_i2sc_read_SR_RXORCH_bf(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_RXORCH_Msk) >> I2SC_SR_RXORCH_Pos;
}

static inline hri_i2sc_sr_reg_t hri_i2sc_get_SR_TXURCH_bf(const void *const hw, hri_i2sc_sr_reg_t mask)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_TXURCH(mask)) >> I2SC_SR_TXURCH_Pos;
}

static inline hri_i2sc_sr_reg_t hri_i2sc_read_SR_TXURCH_bf(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_SR & I2SC_SR_TXURCH_Msk) >> I2SC_SR_TXURCH_Pos;
}

static inline hri_i2sc_sr_reg_t hri_i2sc_get_SR_reg(const void *const hw, hri_i2sc_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_i2sc_sr_reg_t hri_i2sc_read_SR_reg(const void *const hw)
{
	return ((I2sc *)hw)->I2SC_SR;
}

static inline hri_i2sc_rhr_reg_t hri_i2sc_get_RHR_RHR_bf(const void *const hw, hri_i2sc_rhr_reg_t mask)
{
	return (((I2sc *)hw)->I2SC_RHR & I2SC_RHR_RHR(mask)) >> I2SC_RHR_RHR_Pos;
}

static inline hri_i2sc_rhr_reg_t hri_i2sc_read_RHR_RHR_bf(const void *const hw)
{
	return (((I2sc *)hw)->I2SC_RHR & I2SC_RHR_RHR_Msk) >> I2SC_RHR_RHR_Pos;
}

static inline hri_i2sc_rhr_reg_t hri_i2sc_get_RHR_reg(const void *const hw, hri_i2sc_rhr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_RHR;
	tmp &= mask;
	return tmp;
}

static inline hri_i2sc_rhr_reg_t hri_i2sc_read_RHR_reg(const void *const hw)
{
	return ((I2sc *)hw)->I2SC_RHR;
}

static inline void hri_i2sc_set_MR_MODE_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_MODE;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_i2sc_get_MR_MODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_MODE) >> I2SC_MR_MODE_Pos;
	return (bool)tmp;
}

static inline void hri_i2sc_write_MR_MODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_MODE;
	tmp |= value << I2SC_MR_MODE_Pos;
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_MODE_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_MODE;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_MODE_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_MODE;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_set_MR_RXMONO_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_RXMONO;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_i2sc_get_MR_RXMONO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_RXMONO) >> I2SC_MR_RXMONO_Pos;
	return (bool)tmp;
}

static inline void hri_i2sc_write_MR_RXMONO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_RXMONO;
	tmp |= value << I2SC_MR_RXMONO_Pos;
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_RXMONO_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_RXMONO;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_RXMONO_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_RXMONO;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_set_MR_RXDMA_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_RXDMA;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_i2sc_get_MR_RXDMA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_RXDMA) >> I2SC_MR_RXDMA_Pos;
	return (bool)tmp;
}

static inline void hri_i2sc_write_MR_RXDMA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_RXDMA;
	tmp |= value << I2SC_MR_RXDMA_Pos;
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_RXDMA_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_RXDMA;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_RXDMA_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_RXDMA;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_set_MR_RXLOOP_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_RXLOOP;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_i2sc_get_MR_RXLOOP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_RXLOOP) >> I2SC_MR_RXLOOP_Pos;
	return (bool)tmp;
}

static inline void hri_i2sc_write_MR_RXLOOP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_RXLOOP;
	tmp |= value << I2SC_MR_RXLOOP_Pos;
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_RXLOOP_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_RXLOOP;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_RXLOOP_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_RXLOOP;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_set_MR_TXMONO_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_TXMONO;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_i2sc_get_MR_TXMONO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_TXMONO) >> I2SC_MR_TXMONO_Pos;
	return (bool)tmp;
}

static inline void hri_i2sc_write_MR_TXMONO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_TXMONO;
	tmp |= value << I2SC_MR_TXMONO_Pos;
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_TXMONO_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_TXMONO;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_TXMONO_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_TXMONO;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_set_MR_TXDMA_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_TXDMA;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_i2sc_get_MR_TXDMA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_TXDMA) >> I2SC_MR_TXDMA_Pos;
	return (bool)tmp;
}

static inline void hri_i2sc_write_MR_TXDMA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_TXDMA;
	tmp |= value << I2SC_MR_TXDMA_Pos;
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_TXDMA_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_TXDMA;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_TXDMA_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_TXDMA;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_set_MR_TXSAME_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_TXSAME;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_i2sc_get_MR_TXSAME_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_TXSAME) >> I2SC_MR_TXSAME_Pos;
	return (bool)tmp;
}

static inline void hri_i2sc_write_MR_TXSAME_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_TXSAME;
	tmp |= value << I2SC_MR_TXSAME_Pos;
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_TXSAME_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_TXSAME;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_TXSAME_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_TXSAME;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_set_MR_IMCKMODE_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_IMCKMODE;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_i2sc_get_MR_IMCKMODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_IMCKMODE) >> I2SC_MR_IMCKMODE_Pos;
	return (bool)tmp;
}

static inline void hri_i2sc_write_MR_IMCKMODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_IMCKMODE;
	tmp |= value << I2SC_MR_IMCKMODE_Pos;
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_IMCKMODE_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_IMCKMODE;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_IMCKMODE_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_IMCKMODE;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_set_MR_IWS_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_IWS;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_i2sc_get_MR_IWS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_IWS) >> I2SC_MR_IWS_Pos;
	return (bool)tmp;
}

static inline void hri_i2sc_write_MR_IWS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_IWS;
	tmp |= value << I2SC_MR_IWS_Pos;
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_IWS_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_IWS;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_IWS_bit(const void *const hw)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_IWS;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_set_MR_DATALENGTH_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_DATALENGTH(mask);
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline hri_i2sc_mr_reg_t hri_i2sc_get_MR_DATALENGTH_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_DATALENGTH(mask)) >> I2SC_MR_DATALENGTH_Pos;
	return tmp;
}

static inline void hri_i2sc_write_MR_DATALENGTH_bf(const void *const hw, hri_i2sc_mr_reg_t data)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_DATALENGTH_Msk;
	tmp |= I2SC_MR_DATALENGTH(data);
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_DATALENGTH_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_DATALENGTH(mask);
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_DATALENGTH_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_DATALENGTH(mask);
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline hri_i2sc_mr_reg_t hri_i2sc_read_MR_DATALENGTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_DATALENGTH_Msk) >> I2SC_MR_DATALENGTH_Pos;
	return tmp;
}

static inline void hri_i2sc_set_MR_IMCKDIV_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_IMCKDIV(mask);
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline hri_i2sc_mr_reg_t hri_i2sc_get_MR_IMCKDIV_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_IMCKDIV(mask)) >> I2SC_MR_IMCKDIV_Pos;
	return tmp;
}

static inline void hri_i2sc_write_MR_IMCKDIV_bf(const void *const hw, hri_i2sc_mr_reg_t data)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_IMCKDIV_Msk;
	tmp |= I2SC_MR_IMCKDIV(data);
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_IMCKDIV_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_IMCKDIV(mask);
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_IMCKDIV_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_IMCKDIV(mask);
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline hri_i2sc_mr_reg_t hri_i2sc_read_MR_IMCKDIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_IMCKDIV_Msk) >> I2SC_MR_IMCKDIV_Pos;
	return tmp;
}

static inline void hri_i2sc_set_MR_IMCKFS_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= I2SC_MR_IMCKFS(mask);
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline hri_i2sc_mr_reg_t hri_i2sc_get_MR_IMCKFS_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_IMCKFS(mask)) >> I2SC_MR_IMCKFS_Pos;
	return tmp;
}

static inline void hri_i2sc_write_MR_IMCKFS_bf(const void *const hw, hri_i2sc_mr_reg_t data)
{
	uint32_t tmp;
	I2SC_CRITICAL_SECTION_ENTER();
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= ~I2SC_MR_IMCKFS_Msk;
	tmp |= I2SC_MR_IMCKFS(data);
	((I2sc *)hw)->I2SC_MR = tmp;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_IMCKFS_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~I2SC_MR_IMCKFS(mask);
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_IMCKFS_bf(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= I2SC_MR_IMCKFS(mask);
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline hri_i2sc_mr_reg_t hri_i2sc_read_MR_IMCKFS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp = (tmp & I2SC_MR_IMCKFS_Msk) >> I2SC_MR_IMCKFS_Pos;
	return tmp;
}

static inline void hri_i2sc_set_MR_reg(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR |= mask;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline hri_i2sc_mr_reg_t hri_i2sc_get_MR_reg(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((I2sc *)hw)->I2SC_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_i2sc_write_MR_reg(const void *const hw, hri_i2sc_mr_reg_t data)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR = data;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_clear_MR_reg(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR &= ~mask;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_toggle_MR_reg(const void *const hw, hri_i2sc_mr_reg_t mask)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_MR ^= mask;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline hri_i2sc_mr_reg_t hri_i2sc_read_MR_reg(const void *const hw)
{
	return ((I2sc *)hw)->I2SC_MR;
}

static inline void hri_i2sc_write_CR_reg(const void *const hw, hri_i2sc_cr_reg_t data)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_CR = data;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_write_SCR_reg(const void *const hw, hri_i2sc_scr_reg_t data)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_SCR = data;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_write_SSR_reg(const void *const hw, hri_i2sc_ssr_reg_t data)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_SSR = data;
	I2SC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_i2sc_write_THR_reg(const void *const hw, hri_i2sc_thr_reg_t data)
{
	I2SC_CRITICAL_SECTION_ENTER();
	((I2sc *)hw)->I2SC_THR = data;
	I2SC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_I2SC_E70B_H_INCLUDED */
#endif /* _SAME70_I2SC_COMPONENT_ */
