/**
 * \file
 *
 * \brief SAM AES
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

#ifdef _SAME70_AES_COMPONENT_
#ifndef _HRI_AES_E70B_H_INCLUDED_
#define _HRI_AES_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_AES_CRITICAL_SECTIONS)
#define AES_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define AES_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define AES_CRITICAL_SECTION_ENTER()
#define AES_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_aes_aadlenr_reg_t;
typedef uint32_t hri_aes_clenr_reg_t;
typedef uint32_t hri_aes_cr_reg_t;
typedef uint32_t hri_aes_ctrr_reg_t;
typedef uint32_t hri_aes_gcmhr_reg_t;
typedef uint32_t hri_aes_ghashr_reg_t;
typedef uint32_t hri_aes_idatar_reg_t;
typedef uint32_t hri_aes_imr_reg_t;
typedef uint32_t hri_aes_isr_reg_t;
typedef uint32_t hri_aes_ivr_reg_t;
typedef uint32_t hri_aes_keywr_reg_t;
typedef uint32_t hri_aes_mr_reg_t;
typedef uint32_t hri_aes_odatar_reg_t;
typedef uint32_t hri_aes_tagr_reg_t;

static inline bool hri_aes_get_ISR_DATRDY_bit(const void *const hw)
{
	return (((Aes *)hw)->AES_ISR & AES_ISR_DATRDY) >> AES_ISR_DATRDY_Pos;
}

static inline bool hri_aes_get_ISR_URAD_bit(const void *const hw)
{
	return (((Aes *)hw)->AES_ISR & AES_ISR_URAD) >> AES_ISR_URAD_Pos;
}

static inline bool hri_aes_get_ISR_TAGRDY_bit(const void *const hw)
{
	return (((Aes *)hw)->AES_ISR & AES_ISR_TAGRDY) >> AES_ISR_TAGRDY_Pos;
}

static inline hri_aes_isr_reg_t hri_aes_get_ISR_reg(const void *const hw, hri_aes_isr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_ISR;
	tmp &= mask;
	return tmp;
}

static inline hri_aes_isr_reg_t hri_aes_read_ISR_reg(const void *const hw)
{
	return ((Aes *)hw)->AES_ISR;
}

static inline void hri_aes_set_IMR_DATRDY_bit(const void *const hw)
{
	((Aes *)hw)->AES_IER = AES_IMR_DATRDY;
}

static inline bool hri_aes_get_IMR_DATRDY_bit(const void *const hw)
{
	return (((Aes *)hw)->AES_IMR & AES_IMR_DATRDY) >> AES_IMR_DATRDY_Pos;
}

static inline void hri_aes_write_IMR_DATRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Aes *)hw)->AES_IDR = AES_IMR_DATRDY;
	} else {
		((Aes *)hw)->AES_IER = AES_IMR_DATRDY;
	}
}

static inline void hri_aes_clear_IMR_DATRDY_bit(const void *const hw)
{
	((Aes *)hw)->AES_IDR = AES_IMR_DATRDY;
}

static inline void hri_aes_set_IMR_URAD_bit(const void *const hw)
{
	((Aes *)hw)->AES_IER = AES_IMR_URAD;
}

static inline bool hri_aes_get_IMR_URAD_bit(const void *const hw)
{
	return (((Aes *)hw)->AES_IMR & AES_IMR_URAD) >> AES_IMR_URAD_Pos;
}

static inline void hri_aes_write_IMR_URAD_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Aes *)hw)->AES_IDR = AES_IMR_URAD;
	} else {
		((Aes *)hw)->AES_IER = AES_IMR_URAD;
	}
}

static inline void hri_aes_clear_IMR_URAD_bit(const void *const hw)
{
	((Aes *)hw)->AES_IDR = AES_IMR_URAD;
}

static inline void hri_aes_set_IMR_TAGRDY_bit(const void *const hw)
{
	((Aes *)hw)->AES_IER = AES_IMR_TAGRDY;
}

static inline bool hri_aes_get_IMR_TAGRDY_bit(const void *const hw)
{
	return (((Aes *)hw)->AES_IMR & AES_IMR_TAGRDY) >> AES_IMR_TAGRDY_Pos;
}

static inline void hri_aes_write_IMR_TAGRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Aes *)hw)->AES_IDR = AES_IMR_TAGRDY;
	} else {
		((Aes *)hw)->AES_IER = AES_IMR_TAGRDY;
	}
}

static inline void hri_aes_clear_IMR_TAGRDY_bit(const void *const hw)
{
	((Aes *)hw)->AES_IDR = AES_IMR_TAGRDY;
}

static inline void hri_aes_set_IMR_reg(const void *const hw, hri_aes_imr_reg_t mask)
{
	((Aes *)hw)->AES_IER = mask;
}

static inline hri_aes_imr_reg_t hri_aes_get_IMR_reg(const void *const hw, hri_aes_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_aes_imr_reg_t hri_aes_read_IMR_reg(const void *const hw)
{
	return ((Aes *)hw)->AES_IMR;
}

static inline void hri_aes_write_IMR_reg(const void *const hw, hri_aes_imr_reg_t data)
{
	((Aes *)hw)->AES_IER = data;
	((Aes *)hw)->AES_IDR = ~data;
}

static inline void hri_aes_clear_IMR_reg(const void *const hw, hri_aes_imr_reg_t mask)
{
	((Aes *)hw)->AES_IDR = mask;
}

static inline hri_aes_odatar_reg_t hri_aes_get_ODATAR_ODATA_bf(const void *const hw, uint8_t index,
                                                               hri_aes_odatar_reg_t mask)
{
	return (((Aes *)hw)->AES_ODATAR[index] & AES_ODATAR_ODATA(mask)) >> AES_ODATAR_ODATA_Pos;
}

static inline hri_aes_odatar_reg_t hri_aes_read_ODATAR_ODATA_bf(const void *const hw, uint8_t index)
{
	return (((Aes *)hw)->AES_ODATAR[index] & AES_ODATAR_ODATA_Msk) >> AES_ODATAR_ODATA_Pos;
}

static inline hri_aes_odatar_reg_t hri_aes_get_ODATAR_reg(const void *const hw, uint8_t index,
                                                          hri_aes_odatar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_ODATAR[index];
	tmp &= mask;
	return tmp;
}

static inline hri_aes_odatar_reg_t hri_aes_read_ODATAR_reg(const void *const hw, uint8_t index)
{
	return ((Aes *)hw)->AES_ODATAR[index];
}

static inline hri_aes_tagr_reg_t hri_aes_get_TAGR_TAG_bf(const void *const hw, uint8_t index, hri_aes_tagr_reg_t mask)
{
	return (((Aes *)hw)->AES_TAGR[index] & AES_TAGR_TAG(mask)) >> AES_TAGR_TAG_Pos;
}

static inline hri_aes_tagr_reg_t hri_aes_read_TAGR_TAG_bf(const void *const hw, uint8_t index)
{
	return (((Aes *)hw)->AES_TAGR[index] & AES_TAGR_TAG_Msk) >> AES_TAGR_TAG_Pos;
}

static inline hri_aes_tagr_reg_t hri_aes_get_TAGR_reg(const void *const hw, uint8_t index, hri_aes_tagr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_TAGR[index];
	tmp &= mask;
	return tmp;
}

static inline hri_aes_tagr_reg_t hri_aes_read_TAGR_reg(const void *const hw, uint8_t index)
{
	return ((Aes *)hw)->AES_TAGR[index];
}

static inline hri_aes_ctrr_reg_t hri_aes_get_CTRR_CTR_bf(const void *const hw, hri_aes_ctrr_reg_t mask)
{
	return (((Aes *)hw)->AES_CTRR & AES_CTRR_CTR(mask)) >> AES_CTRR_CTR_Pos;
}

static inline hri_aes_ctrr_reg_t hri_aes_read_CTRR_CTR_bf(const void *const hw)
{
	return (((Aes *)hw)->AES_CTRR & AES_CTRR_CTR_Msk) >> AES_CTRR_CTR_Pos;
}

static inline hri_aes_ctrr_reg_t hri_aes_get_CTRR_reg(const void *const hw, hri_aes_ctrr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_CTRR;
	tmp &= mask;
	return tmp;
}

static inline hri_aes_ctrr_reg_t hri_aes_read_CTRR_reg(const void *const hw)
{
	return ((Aes *)hw)->AES_CTRR;
}

static inline void hri_aes_set_MR_CIPHER_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_CIPHER;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_MR_CIPHER_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_CIPHER) >> AES_MR_CIPHER_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_MR_CIPHER_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_CIPHER;
	tmp |= value << AES_MR_CIPHER_Pos;
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_CIPHER_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_CIPHER;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_CIPHER_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_CIPHER;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_MR_GTAGEN_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_GTAGEN;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_MR_GTAGEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_GTAGEN) >> AES_MR_GTAGEN_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_MR_GTAGEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_GTAGEN;
	tmp |= value << AES_MR_GTAGEN_Pos;
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_GTAGEN_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_GTAGEN;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_GTAGEN_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_GTAGEN;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_MR_DUALBUFF_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_DUALBUFF;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_MR_DUALBUFF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_DUALBUFF) >> AES_MR_DUALBUFF_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_MR_DUALBUFF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_DUALBUFF;
	tmp |= value << AES_MR_DUALBUFF_Pos;
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_DUALBUFF_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_DUALBUFF;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_DUALBUFF_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_DUALBUFF;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_MR_LOD_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_LOD;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_aes_get_MR_LOD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_LOD) >> AES_MR_LOD_Pos;
	return (bool)tmp;
}

static inline void hri_aes_write_MR_LOD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_LOD;
	tmp |= value << AES_MR_LOD_Pos;
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_LOD_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_LOD;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_LOD_bit(const void *const hw)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_LOD;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_set_MR_PROCDLY_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_PROCDLY(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_get_MR_PROCDLY_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_PROCDLY(mask)) >> AES_MR_PROCDLY_Pos;
	return tmp;
}

static inline void hri_aes_write_MR_PROCDLY_bf(const void *const hw, hri_aes_mr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_PROCDLY_Msk;
	tmp |= AES_MR_PROCDLY(data);
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_PROCDLY_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_PROCDLY(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_PROCDLY_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_PROCDLY(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_read_MR_PROCDLY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_PROCDLY_Msk) >> AES_MR_PROCDLY_Pos;
	return tmp;
}

static inline void hri_aes_set_MR_SMOD_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_SMOD(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_get_MR_SMOD_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_SMOD(mask)) >> AES_MR_SMOD_Pos;
	return tmp;
}

static inline void hri_aes_write_MR_SMOD_bf(const void *const hw, hri_aes_mr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_SMOD_Msk;
	tmp |= AES_MR_SMOD(data);
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_SMOD_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_SMOD(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_SMOD_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_SMOD(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_read_MR_SMOD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_SMOD_Msk) >> AES_MR_SMOD_Pos;
	return tmp;
}

static inline void hri_aes_set_MR_KEYSIZE_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_KEYSIZE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_get_MR_KEYSIZE_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_KEYSIZE(mask)) >> AES_MR_KEYSIZE_Pos;
	return tmp;
}

static inline void hri_aes_write_MR_KEYSIZE_bf(const void *const hw, hri_aes_mr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_KEYSIZE_Msk;
	tmp |= AES_MR_KEYSIZE(data);
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_KEYSIZE_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_KEYSIZE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_KEYSIZE_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_KEYSIZE(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_read_MR_KEYSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_KEYSIZE_Msk) >> AES_MR_KEYSIZE_Pos;
	return tmp;
}

static inline void hri_aes_set_MR_OPMOD_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_OPMOD(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_get_MR_OPMOD_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_OPMOD(mask)) >> AES_MR_OPMOD_Pos;
	return tmp;
}

static inline void hri_aes_write_MR_OPMOD_bf(const void *const hw, hri_aes_mr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_OPMOD_Msk;
	tmp |= AES_MR_OPMOD(data);
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_OPMOD_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_OPMOD(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_OPMOD_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_OPMOD(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_read_MR_OPMOD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_OPMOD_Msk) >> AES_MR_OPMOD_Pos;
	return tmp;
}

static inline void hri_aes_set_MR_CFBS_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_CFBS(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_get_MR_CFBS_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_CFBS(mask)) >> AES_MR_CFBS_Pos;
	return tmp;
}

static inline void hri_aes_write_MR_CFBS_bf(const void *const hw, hri_aes_mr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_CFBS_Msk;
	tmp |= AES_MR_CFBS(data);
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_CFBS_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_CFBS(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_CFBS_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_CFBS(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_read_MR_CFBS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_CFBS_Msk) >> AES_MR_CFBS_Pos;
	return tmp;
}

static inline void hri_aes_set_MR_CKEY_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= AES_MR_CKEY(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_get_MR_CKEY_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_CKEY(mask)) >> AES_MR_CKEY_Pos;
	return tmp;
}

static inline void hri_aes_write_MR_CKEY_bf(const void *const hw, hri_aes_mr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= ~AES_MR_CKEY_Msk;
	tmp |= AES_MR_CKEY(data);
	((Aes *)hw)->AES_MR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_CKEY_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~AES_MR_CKEY(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_CKEY_bf(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= AES_MR_CKEY(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_read_MR_CKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp = (tmp & AES_MR_CKEY_Msk) >> AES_MR_CKEY_Pos;
	return tmp;
}

static inline void hri_aes_set_MR_reg(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_get_MR_reg(const void *const hw, hri_aes_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_MR_reg(const void *const hw, hri_aes_mr_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_MR_reg(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_MR_reg(const void *const hw, hri_aes_mr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_MR ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_mr_reg_t hri_aes_read_MR_reg(const void *const hw)
{
	return ((Aes *)hw)->AES_MR;
}

static inline void hri_aes_set_AADLENR_AADLEN_bf(const void *const hw, hri_aes_aadlenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_AADLENR |= AES_AADLENR_AADLEN(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_aadlenr_reg_t hri_aes_get_AADLENR_AADLEN_bf(const void *const hw, hri_aes_aadlenr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_AADLENR;
	tmp = (tmp & AES_AADLENR_AADLEN(mask)) >> AES_AADLENR_AADLEN_Pos;
	return tmp;
}

static inline void hri_aes_write_AADLENR_AADLEN_bf(const void *const hw, hri_aes_aadlenr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_AADLENR;
	tmp &= ~AES_AADLENR_AADLEN_Msk;
	tmp |= AES_AADLENR_AADLEN(data);
	((Aes *)hw)->AES_AADLENR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_AADLENR_AADLEN_bf(const void *const hw, hri_aes_aadlenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_AADLENR &= ~AES_AADLENR_AADLEN(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_AADLENR_AADLEN_bf(const void *const hw, hri_aes_aadlenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_AADLENR ^= AES_AADLENR_AADLEN(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_aadlenr_reg_t hri_aes_read_AADLENR_AADLEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_AADLENR;
	tmp = (tmp & AES_AADLENR_AADLEN_Msk) >> AES_AADLENR_AADLEN_Pos;
	return tmp;
}

static inline void hri_aes_set_AADLENR_reg(const void *const hw, hri_aes_aadlenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_AADLENR |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_aadlenr_reg_t hri_aes_get_AADLENR_reg(const void *const hw, hri_aes_aadlenr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_AADLENR;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_AADLENR_reg(const void *const hw, hri_aes_aadlenr_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_AADLENR = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_AADLENR_reg(const void *const hw, hri_aes_aadlenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_AADLENR &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_AADLENR_reg(const void *const hw, hri_aes_aadlenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_AADLENR ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_aadlenr_reg_t hri_aes_read_AADLENR_reg(const void *const hw)
{
	return ((Aes *)hw)->AES_AADLENR;
}

static inline void hri_aes_set_CLENR_CLEN_bf(const void *const hw, hri_aes_clenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_CLENR |= AES_CLENR_CLEN(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_clenr_reg_t hri_aes_get_CLENR_CLEN_bf(const void *const hw, hri_aes_clenr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_CLENR;
	tmp = (tmp & AES_CLENR_CLEN(mask)) >> AES_CLENR_CLEN_Pos;
	return tmp;
}

static inline void hri_aes_write_CLENR_CLEN_bf(const void *const hw, hri_aes_clenr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_CLENR;
	tmp &= ~AES_CLENR_CLEN_Msk;
	tmp |= AES_CLENR_CLEN(data);
	((Aes *)hw)->AES_CLENR = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CLENR_CLEN_bf(const void *const hw, hri_aes_clenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_CLENR &= ~AES_CLENR_CLEN(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CLENR_CLEN_bf(const void *const hw, hri_aes_clenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_CLENR ^= AES_CLENR_CLEN(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_clenr_reg_t hri_aes_read_CLENR_CLEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_CLENR;
	tmp = (tmp & AES_CLENR_CLEN_Msk) >> AES_CLENR_CLEN_Pos;
	return tmp;
}

static inline void hri_aes_set_CLENR_reg(const void *const hw, hri_aes_clenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_CLENR |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_clenr_reg_t hri_aes_get_CLENR_reg(const void *const hw, hri_aes_clenr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_CLENR;
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_CLENR_reg(const void *const hw, hri_aes_clenr_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_CLENR = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_CLENR_reg(const void *const hw, hri_aes_clenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_CLENR &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_CLENR_reg(const void *const hw, hri_aes_clenr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_CLENR ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_clenr_reg_t hri_aes_read_CLENR_reg(const void *const hw)
{
	return ((Aes *)hw)->AES_CLENR;
}

static inline void hri_aes_set_GHASHR_GHASH_bf(const void *const hw, uint8_t index, hri_aes_ghashr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GHASHR[index] |= AES_GHASHR_GHASH(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ghashr_reg_t hri_aes_get_GHASHR_GHASH_bf(const void *const hw, uint8_t index,
                                                               hri_aes_ghashr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_GHASHR[index];
	tmp = (tmp & AES_GHASHR_GHASH(mask)) >> AES_GHASHR_GHASH_Pos;
	return tmp;
}

static inline void hri_aes_write_GHASHR_GHASH_bf(const void *const hw, uint8_t index, hri_aes_ghashr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_GHASHR[index];
	tmp &= ~AES_GHASHR_GHASH_Msk;
	tmp |= AES_GHASHR_GHASH(data);
	((Aes *)hw)->AES_GHASHR[index] = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_GHASHR_GHASH_bf(const void *const hw, uint8_t index, hri_aes_ghashr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GHASHR[index] &= ~AES_GHASHR_GHASH(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_GHASHR_GHASH_bf(const void *const hw, uint8_t index, hri_aes_ghashr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GHASHR[index] ^= AES_GHASHR_GHASH(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ghashr_reg_t hri_aes_read_GHASHR_GHASH_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_GHASHR[index];
	tmp = (tmp & AES_GHASHR_GHASH_Msk) >> AES_GHASHR_GHASH_Pos;
	return tmp;
}

static inline void hri_aes_set_GHASHR_reg(const void *const hw, uint8_t index, hri_aes_ghashr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GHASHR[index] |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ghashr_reg_t hri_aes_get_GHASHR_reg(const void *const hw, uint8_t index,
                                                          hri_aes_ghashr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_GHASHR[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_GHASHR_reg(const void *const hw, uint8_t index, hri_aes_ghashr_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GHASHR[index] = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_GHASHR_reg(const void *const hw, uint8_t index, hri_aes_ghashr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GHASHR[index] &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_GHASHR_reg(const void *const hw, uint8_t index, hri_aes_ghashr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GHASHR[index] ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_ghashr_reg_t hri_aes_read_GHASHR_reg(const void *const hw, uint8_t index)
{
	return ((Aes *)hw)->AES_GHASHR[index];
}

static inline void hri_aes_set_GCMHR_H_bf(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GCMHR[index] |= AES_GCMHR_H(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_gcmhr_reg_t hri_aes_get_GCMHR_H_bf(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_GCMHR[index];
	tmp = (tmp & AES_GCMHR_H(mask)) >> AES_GCMHR_H_Pos;
	return tmp;
}

static inline void hri_aes_write_GCMHR_H_bf(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t data)
{
	uint32_t tmp;
	AES_CRITICAL_SECTION_ENTER();
	tmp = ((Aes *)hw)->AES_GCMHR[index];
	tmp &= ~AES_GCMHR_H_Msk;
	tmp |= AES_GCMHR_H(data);
	((Aes *)hw)->AES_GCMHR[index] = tmp;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_GCMHR_H_bf(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GCMHR[index] &= ~AES_GCMHR_H(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_GCMHR_H_bf(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GCMHR[index] ^= AES_GCMHR_H(mask);
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_gcmhr_reg_t hri_aes_read_GCMHR_H_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_GCMHR[index];
	tmp = (tmp & AES_GCMHR_H_Msk) >> AES_GCMHR_H_Pos;
	return tmp;
}

static inline void hri_aes_set_GCMHR_reg(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GCMHR[index] |= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_gcmhr_reg_t hri_aes_get_GCMHR_reg(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Aes *)hw)->AES_GCMHR[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_aes_write_GCMHR_reg(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GCMHR[index] = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_clear_GCMHR_reg(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GCMHR[index] &= ~mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_toggle_GCMHR_reg(const void *const hw, uint8_t index, hri_aes_gcmhr_reg_t mask)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_GCMHR[index] ^= mask;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline hri_aes_gcmhr_reg_t hri_aes_read_GCMHR_reg(const void *const hw, uint8_t index)
{
	return ((Aes *)hw)->AES_GCMHR[index];
}

static inline void hri_aes_write_CR_reg(const void *const hw, hri_aes_cr_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_CR = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_write_KEYWR_reg(const void *const hw, uint8_t index, hri_aes_keywr_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_KEYWR[index] = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_write_IDATAR_reg(const void *const hw, uint8_t index, hri_aes_idatar_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_IDATAR[index] = data;
	AES_CRITICAL_SECTION_LEAVE();
}

static inline void hri_aes_write_IVR_reg(const void *const hw, uint8_t index, hri_aes_ivr_reg_t data)
{
	AES_CRITICAL_SECTION_ENTER();
	((Aes *)hw)->AES_IVR[index] = data;
	AES_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_AES_E70B_H_INCLUDED */
#endif /* _SAME70_AES_COMPONENT_ */
