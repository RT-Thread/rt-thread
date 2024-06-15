/**
 * \file
 *
 * \brief SAM RAMECC
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAMD51_RAMECC_COMPONENT_
#ifndef _HRI_RAMECC_D51_H_INCLUDED_
#define _HRI_RAMECC_D51_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_RAMECC_CRITICAL_SECTIONS)
#define RAMECC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define RAMECC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define RAMECC_CRITICAL_SECTION_ENTER()
#define RAMECC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_ramecc_erraddr_reg_t;
typedef uint8_t  hri_ramecc_dbgctrl_reg_t;
typedef uint8_t  hri_ramecc_intenset_reg_t;
typedef uint8_t  hri_ramecc_intflag_reg_t;
typedef uint8_t  hri_ramecc_status_reg_t;

static inline bool hri_ramecc_get_INTFLAG_SINGLEE_bit(const void *const hw)
{
	return (((Ramecc *)hw)->INTFLAG.reg & RAMECC_INTFLAG_SINGLEE) >> RAMECC_INTFLAG_SINGLEE_Pos;
}

static inline void hri_ramecc_clear_INTFLAG_SINGLEE_bit(const void *const hw)
{
	((Ramecc *)hw)->INTFLAG.reg = RAMECC_INTFLAG_SINGLEE;
}

static inline bool hri_ramecc_get_INTFLAG_DUALE_bit(const void *const hw)
{
	return (((Ramecc *)hw)->INTFLAG.reg & RAMECC_INTFLAG_DUALE) >> RAMECC_INTFLAG_DUALE_Pos;
}

static inline void hri_ramecc_clear_INTFLAG_DUALE_bit(const void *const hw)
{
	((Ramecc *)hw)->INTFLAG.reg = RAMECC_INTFLAG_DUALE;
}

static inline bool hri_ramecc_get_interrupt_SINGLEE_bit(const void *const hw)
{
	return (((Ramecc *)hw)->INTFLAG.reg & RAMECC_INTFLAG_SINGLEE) >> RAMECC_INTFLAG_SINGLEE_Pos;
}

static inline void hri_ramecc_clear_interrupt_SINGLEE_bit(const void *const hw)
{
	((Ramecc *)hw)->INTFLAG.reg = RAMECC_INTFLAG_SINGLEE;
}

static inline bool hri_ramecc_get_interrupt_DUALE_bit(const void *const hw)
{
	return (((Ramecc *)hw)->INTFLAG.reg & RAMECC_INTFLAG_DUALE) >> RAMECC_INTFLAG_DUALE_Pos;
}

static inline void hri_ramecc_clear_interrupt_DUALE_bit(const void *const hw)
{
	((Ramecc *)hw)->INTFLAG.reg = RAMECC_INTFLAG_DUALE;
}

static inline hri_ramecc_intflag_reg_t hri_ramecc_get_INTFLAG_reg(const void *const hw, hri_ramecc_intflag_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Ramecc *)hw)->INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_ramecc_intflag_reg_t hri_ramecc_read_INTFLAG_reg(const void *const hw)
{
	return ((Ramecc *)hw)->INTFLAG.reg;
}

static inline void hri_ramecc_clear_INTFLAG_reg(const void *const hw, hri_ramecc_intflag_reg_t mask)
{
	((Ramecc *)hw)->INTFLAG.reg = mask;
}

static inline void hri_ramecc_set_INTEN_SINGLEE_bit(const void *const hw)
{
	((Ramecc *)hw)->INTENSET.reg = RAMECC_INTENSET_SINGLEE;
}

static inline bool hri_ramecc_get_INTEN_SINGLEE_bit(const void *const hw)
{
	return (((Ramecc *)hw)->INTENSET.reg & RAMECC_INTENSET_SINGLEE) >> RAMECC_INTENSET_SINGLEE_Pos;
}

static inline void hri_ramecc_write_INTEN_SINGLEE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ramecc *)hw)->INTENCLR.reg = RAMECC_INTENSET_SINGLEE;
	} else {
		((Ramecc *)hw)->INTENSET.reg = RAMECC_INTENSET_SINGLEE;
	}
}

static inline void hri_ramecc_clear_INTEN_SINGLEE_bit(const void *const hw)
{
	((Ramecc *)hw)->INTENCLR.reg = RAMECC_INTENSET_SINGLEE;
}

static inline void hri_ramecc_set_INTEN_DUALE_bit(const void *const hw)
{
	((Ramecc *)hw)->INTENSET.reg = RAMECC_INTENSET_DUALE;
}

static inline bool hri_ramecc_get_INTEN_DUALE_bit(const void *const hw)
{
	return (((Ramecc *)hw)->INTENSET.reg & RAMECC_INTENSET_DUALE) >> RAMECC_INTENSET_DUALE_Pos;
}

static inline void hri_ramecc_write_INTEN_DUALE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Ramecc *)hw)->INTENCLR.reg = RAMECC_INTENSET_DUALE;
	} else {
		((Ramecc *)hw)->INTENSET.reg = RAMECC_INTENSET_DUALE;
	}
}

static inline void hri_ramecc_clear_INTEN_DUALE_bit(const void *const hw)
{
	((Ramecc *)hw)->INTENCLR.reg = RAMECC_INTENSET_DUALE;
}

static inline void hri_ramecc_set_INTEN_reg(const void *const hw, hri_ramecc_intenset_reg_t mask)
{
	((Ramecc *)hw)->INTENSET.reg = mask;
}

static inline hri_ramecc_intenset_reg_t hri_ramecc_get_INTEN_reg(const void *const hw, hri_ramecc_intenset_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Ramecc *)hw)->INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_ramecc_intenset_reg_t hri_ramecc_read_INTEN_reg(const void *const hw)
{
	return ((Ramecc *)hw)->INTENSET.reg;
}

static inline void hri_ramecc_write_INTEN_reg(const void *const hw, hri_ramecc_intenset_reg_t data)
{
	((Ramecc *)hw)->INTENSET.reg = data;
	((Ramecc *)hw)->INTENCLR.reg = ~data;
}

static inline void hri_ramecc_clear_INTEN_reg(const void *const hw, hri_ramecc_intenset_reg_t mask)
{
	((Ramecc *)hw)->INTENCLR.reg = mask;
}

static inline bool hri_ramecc_get_STATUS_ECCDIS_bit(const void *const hw)
{
	return (((Ramecc *)hw)->STATUS.reg & RAMECC_STATUS_ECCDIS) >> RAMECC_STATUS_ECCDIS_Pos;
}

static inline hri_ramecc_status_reg_t hri_ramecc_get_STATUS_reg(const void *const hw, hri_ramecc_status_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Ramecc *)hw)->STATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_ramecc_status_reg_t hri_ramecc_read_STATUS_reg(const void *const hw)
{
	return ((Ramecc *)hw)->STATUS.reg;
}

static inline hri_ramecc_erraddr_reg_t hri_ramecc_get_ERRADDR_ERRADDR_bf(const void *const        hw,
                                                                         hri_ramecc_erraddr_reg_t mask)
{
	return (((Ramecc *)hw)->ERRADDR.reg & RAMECC_ERRADDR_ERRADDR(mask)) >> RAMECC_ERRADDR_ERRADDR_Pos;
}

static inline hri_ramecc_erraddr_reg_t hri_ramecc_read_ERRADDR_ERRADDR_bf(const void *const hw)
{
	return (((Ramecc *)hw)->ERRADDR.reg & RAMECC_ERRADDR_ERRADDR_Msk) >> RAMECC_ERRADDR_ERRADDR_Pos;
}

static inline hri_ramecc_erraddr_reg_t hri_ramecc_get_ERRADDR_reg(const void *const hw, hri_ramecc_erraddr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Ramecc *)hw)->ERRADDR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_ramecc_erraddr_reg_t hri_ramecc_read_ERRADDR_reg(const void *const hw)
{
	return ((Ramecc *)hw)->ERRADDR.reg;
}

static inline void hri_ramecc_set_DBGCTRL_ECCDIS_bit(const void *const hw)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg |= RAMECC_DBGCTRL_ECCDIS;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ramecc_get_DBGCTRL_ECCDIS_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Ramecc *)hw)->DBGCTRL.reg;
	tmp = (tmp & RAMECC_DBGCTRL_ECCDIS) >> RAMECC_DBGCTRL_ECCDIS_Pos;
	return (bool)tmp;
}

static inline void hri_ramecc_write_DBGCTRL_ECCDIS_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	RAMECC_CRITICAL_SECTION_ENTER();
	tmp = ((Ramecc *)hw)->DBGCTRL.reg;
	tmp &= ~RAMECC_DBGCTRL_ECCDIS;
	tmp |= value << RAMECC_DBGCTRL_ECCDIS_Pos;
	((Ramecc *)hw)->DBGCTRL.reg = tmp;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ramecc_clear_DBGCTRL_ECCDIS_bit(const void *const hw)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg &= ~RAMECC_DBGCTRL_ECCDIS;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ramecc_toggle_DBGCTRL_ECCDIS_bit(const void *const hw)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg ^= RAMECC_DBGCTRL_ECCDIS;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ramecc_set_DBGCTRL_ECCELOG_bit(const void *const hw)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg |= RAMECC_DBGCTRL_ECCELOG;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_ramecc_get_DBGCTRL_ECCELOG_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Ramecc *)hw)->DBGCTRL.reg;
	tmp = (tmp & RAMECC_DBGCTRL_ECCELOG) >> RAMECC_DBGCTRL_ECCELOG_Pos;
	return (bool)tmp;
}

static inline void hri_ramecc_write_DBGCTRL_ECCELOG_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	RAMECC_CRITICAL_SECTION_ENTER();
	tmp = ((Ramecc *)hw)->DBGCTRL.reg;
	tmp &= ~RAMECC_DBGCTRL_ECCELOG;
	tmp |= value << RAMECC_DBGCTRL_ECCELOG_Pos;
	((Ramecc *)hw)->DBGCTRL.reg = tmp;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ramecc_clear_DBGCTRL_ECCELOG_bit(const void *const hw)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg &= ~RAMECC_DBGCTRL_ECCELOG;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ramecc_toggle_DBGCTRL_ECCELOG_bit(const void *const hw)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg ^= RAMECC_DBGCTRL_ECCELOG;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ramecc_set_DBGCTRL_reg(const void *const hw, hri_ramecc_dbgctrl_reg_t mask)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg |= mask;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ramecc_dbgctrl_reg_t hri_ramecc_get_DBGCTRL_reg(const void *const hw, hri_ramecc_dbgctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Ramecc *)hw)->DBGCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_ramecc_write_DBGCTRL_reg(const void *const hw, hri_ramecc_dbgctrl_reg_t data)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg = data;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ramecc_clear_DBGCTRL_reg(const void *const hw, hri_ramecc_dbgctrl_reg_t mask)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg &= ~mask;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_ramecc_toggle_DBGCTRL_reg(const void *const hw, hri_ramecc_dbgctrl_reg_t mask)
{
	RAMECC_CRITICAL_SECTION_ENTER();
	((Ramecc *)hw)->DBGCTRL.reg ^= mask;
	RAMECC_CRITICAL_SECTION_LEAVE();
}

static inline hri_ramecc_dbgctrl_reg_t hri_ramecc_read_DBGCTRL_reg(const void *const hw)
{
	return ((Ramecc *)hw)->DBGCTRL.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RAMECC_D51_H_INCLUDED */
#endif /* _SAMD51_RAMECC_COMPONENT_ */
