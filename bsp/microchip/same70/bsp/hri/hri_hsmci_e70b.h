/**
 * \file
 *
 * \brief SAM HSMCI
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

#ifdef _SAME70_HSMCI_COMPONENT_
#ifndef _HRI_HSMCI_E70B_H_INCLUDED_
#define _HRI_HSMCI_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_HSMCI_CRITICAL_SECTIONS)
#define HSMCI_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define HSMCI_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define HSMCI_CRITICAL_SECTION_ENTER()
#define HSMCI_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_hsmci_argr_reg_t;
typedef uint32_t hri_hsmci_blkr_reg_t;
typedef uint32_t hri_hsmci_cfg_reg_t;
typedef uint32_t hri_hsmci_cmdr_reg_t;
typedef uint32_t hri_hsmci_cr_reg_t;
typedef uint32_t hri_hsmci_cstor_reg_t;
typedef uint32_t hri_hsmci_dma_reg_t;
typedef uint32_t hri_hsmci_dtor_reg_t;
typedef uint32_t hri_hsmci_fifo_reg_t;
typedef uint32_t hri_hsmci_imr_reg_t;
typedef uint32_t hri_hsmci_mr_reg_t;
typedef uint32_t hri_hsmci_rdr_reg_t;
typedef uint32_t hri_hsmci_rspr_reg_t;
typedef uint32_t hri_hsmci_sdcr_reg_t;
typedef uint32_t hri_hsmci_sr_reg_t;
typedef uint32_t hri_hsmci_tdr_reg_t;
typedef uint32_t hri_hsmci_wpmr_reg_t;
typedef uint32_t hri_hsmci_wpsr_reg_t;

static inline void hri_hsmci_set_IMR_CMDRDY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_CMDRDY;
}

static inline bool hri_hsmci_get_IMR_CMDRDY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_CMDRDY) >> HSMCI_IMR_CMDRDY_Pos;
}

static inline void hri_hsmci_write_IMR_CMDRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_CMDRDY;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_CMDRDY;
	}
}

static inline void hri_hsmci_clear_IMR_CMDRDY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_CMDRDY;
}

static inline void hri_hsmci_set_IMR_RXRDY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RXRDY;
}

static inline bool hri_hsmci_get_IMR_RXRDY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_RXRDY) >> HSMCI_IMR_RXRDY_Pos;
}

static inline void hri_hsmci_write_IMR_RXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RXRDY;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RXRDY;
	}
}

static inline void hri_hsmci_clear_IMR_RXRDY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RXRDY;
}

static inline void hri_hsmci_set_IMR_TXRDY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_TXRDY;
}

static inline bool hri_hsmci_get_IMR_TXRDY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_TXRDY) >> HSMCI_IMR_TXRDY_Pos;
}

static inline void hri_hsmci_write_IMR_TXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_TXRDY;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_TXRDY;
	}
}

static inline void hri_hsmci_clear_IMR_TXRDY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_TXRDY;
}

static inline void hri_hsmci_set_IMR_BLKE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_BLKE;
}

static inline bool hri_hsmci_get_IMR_BLKE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_BLKE) >> HSMCI_IMR_BLKE_Pos;
}

static inline void hri_hsmci_write_IMR_BLKE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_BLKE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_BLKE;
	}
}

static inline void hri_hsmci_clear_IMR_BLKE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_BLKE;
}

static inline void hri_hsmci_set_IMR_DTIP_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_DTIP;
}

static inline bool hri_hsmci_get_IMR_DTIP_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_DTIP) >> HSMCI_IMR_DTIP_Pos;
}

static inline void hri_hsmci_write_IMR_DTIP_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_DTIP;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_DTIP;
	}
}

static inline void hri_hsmci_clear_IMR_DTIP_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_DTIP;
}

static inline void hri_hsmci_set_IMR_NOTBUSY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_NOTBUSY;
}

static inline bool hri_hsmci_get_IMR_NOTBUSY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_NOTBUSY) >> HSMCI_IMR_NOTBUSY_Pos;
}

static inline void hri_hsmci_write_IMR_NOTBUSY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_NOTBUSY;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_NOTBUSY;
	}
}

static inline void hri_hsmci_clear_IMR_NOTBUSY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_NOTBUSY;
}

static inline void hri_hsmci_set_IMR_SDIOIRQA_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_SDIOIRQA;
}

static inline bool hri_hsmci_get_IMR_SDIOIRQA_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_SDIOIRQA) >> HSMCI_IMR_SDIOIRQA_Pos;
}

static inline void hri_hsmci_write_IMR_SDIOIRQA_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_SDIOIRQA;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_SDIOIRQA;
	}
}

static inline void hri_hsmci_clear_IMR_SDIOIRQA_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_SDIOIRQA;
}

static inline void hri_hsmci_set_IMR_SDIOWAIT_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_SDIOWAIT;
}

static inline bool hri_hsmci_get_IMR_SDIOWAIT_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_SDIOWAIT) >> HSMCI_IMR_SDIOWAIT_Pos;
}

static inline void hri_hsmci_write_IMR_SDIOWAIT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_SDIOWAIT;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_SDIOWAIT;
	}
}

static inline void hri_hsmci_clear_IMR_SDIOWAIT_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_SDIOWAIT;
}

static inline void hri_hsmci_set_IMR_CSRCV_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_CSRCV;
}

static inline bool hri_hsmci_get_IMR_CSRCV_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_CSRCV) >> HSMCI_IMR_CSRCV_Pos;
}

static inline void hri_hsmci_write_IMR_CSRCV_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_CSRCV;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_CSRCV;
	}
}

static inline void hri_hsmci_clear_IMR_CSRCV_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_CSRCV;
}

static inline void hri_hsmci_set_IMR_RINDE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RINDE;
}

static inline bool hri_hsmci_get_IMR_RINDE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_RINDE) >> HSMCI_IMR_RINDE_Pos;
}

static inline void hri_hsmci_write_IMR_RINDE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RINDE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RINDE;
	}
}

static inline void hri_hsmci_clear_IMR_RINDE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RINDE;
}

static inline void hri_hsmci_set_IMR_RDIRE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RDIRE;
}

static inline bool hri_hsmci_get_IMR_RDIRE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_RDIRE) >> HSMCI_IMR_RDIRE_Pos;
}

static inline void hri_hsmci_write_IMR_RDIRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RDIRE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RDIRE;
	}
}

static inline void hri_hsmci_clear_IMR_RDIRE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RDIRE;
}

static inline void hri_hsmci_set_IMR_RCRCE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RCRCE;
}

static inline bool hri_hsmci_get_IMR_RCRCE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_RCRCE) >> HSMCI_IMR_RCRCE_Pos;
}

static inline void hri_hsmci_write_IMR_RCRCE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RCRCE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RCRCE;
	}
}

static inline void hri_hsmci_clear_IMR_RCRCE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RCRCE;
}

static inline void hri_hsmci_set_IMR_RENDE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RENDE;
}

static inline bool hri_hsmci_get_IMR_RENDE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_RENDE) >> HSMCI_IMR_RENDE_Pos;
}

static inline void hri_hsmci_write_IMR_RENDE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RENDE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RENDE;
	}
}

static inline void hri_hsmci_clear_IMR_RENDE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RENDE;
}

static inline void hri_hsmci_set_IMR_RTOE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RTOE;
}

static inline bool hri_hsmci_get_IMR_RTOE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_RTOE) >> HSMCI_IMR_RTOE_Pos;
}

static inline void hri_hsmci_write_IMR_RTOE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RTOE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_RTOE;
	}
}

static inline void hri_hsmci_clear_IMR_RTOE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_RTOE;
}

static inline void hri_hsmci_set_IMR_DCRCE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_DCRCE;
}

static inline bool hri_hsmci_get_IMR_DCRCE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_DCRCE) >> HSMCI_IMR_DCRCE_Pos;
}

static inline void hri_hsmci_write_IMR_DCRCE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_DCRCE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_DCRCE;
	}
}

static inline void hri_hsmci_clear_IMR_DCRCE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_DCRCE;
}

static inline void hri_hsmci_set_IMR_DTOE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_DTOE;
}

static inline bool hri_hsmci_get_IMR_DTOE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_DTOE) >> HSMCI_IMR_DTOE_Pos;
}

static inline void hri_hsmci_write_IMR_DTOE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_DTOE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_DTOE;
	}
}

static inline void hri_hsmci_clear_IMR_DTOE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_DTOE;
}

static inline void hri_hsmci_set_IMR_CSTOE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_CSTOE;
}

static inline bool hri_hsmci_get_IMR_CSTOE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_CSTOE) >> HSMCI_IMR_CSTOE_Pos;
}

static inline void hri_hsmci_write_IMR_CSTOE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_CSTOE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_CSTOE;
	}
}

static inline void hri_hsmci_clear_IMR_CSTOE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_CSTOE;
}

static inline void hri_hsmci_set_IMR_BLKOVRE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_BLKOVRE;
}

static inline bool hri_hsmci_get_IMR_BLKOVRE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_BLKOVRE) >> HSMCI_IMR_BLKOVRE_Pos;
}

static inline void hri_hsmci_write_IMR_BLKOVRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_BLKOVRE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_BLKOVRE;
	}
}

static inline void hri_hsmci_clear_IMR_BLKOVRE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_BLKOVRE;
}

static inline void hri_hsmci_set_IMR_FIFOEMPTY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_FIFOEMPTY;
}

static inline bool hri_hsmci_get_IMR_FIFOEMPTY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_FIFOEMPTY) >> HSMCI_IMR_FIFOEMPTY_Pos;
}

static inline void hri_hsmci_write_IMR_FIFOEMPTY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_FIFOEMPTY;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_FIFOEMPTY;
	}
}

static inline void hri_hsmci_clear_IMR_FIFOEMPTY_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_FIFOEMPTY;
}

static inline void hri_hsmci_set_IMR_XFRDONE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_XFRDONE;
}

static inline bool hri_hsmci_get_IMR_XFRDONE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_XFRDONE) >> HSMCI_IMR_XFRDONE_Pos;
}

static inline void hri_hsmci_write_IMR_XFRDONE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_XFRDONE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_XFRDONE;
	}
}

static inline void hri_hsmci_clear_IMR_XFRDONE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_XFRDONE;
}

static inline void hri_hsmci_set_IMR_ACKRCV_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_ACKRCV;
}

static inline bool hri_hsmci_get_IMR_ACKRCV_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_ACKRCV) >> HSMCI_IMR_ACKRCV_Pos;
}

static inline void hri_hsmci_write_IMR_ACKRCV_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_ACKRCV;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_ACKRCV;
	}
}

static inline void hri_hsmci_clear_IMR_ACKRCV_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_ACKRCV;
}

static inline void hri_hsmci_set_IMR_ACKRCVE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_ACKRCVE;
}

static inline bool hri_hsmci_get_IMR_ACKRCVE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_ACKRCVE) >> HSMCI_IMR_ACKRCVE_Pos;
}

static inline void hri_hsmci_write_IMR_ACKRCVE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_ACKRCVE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_ACKRCVE;
	}
}

static inline void hri_hsmci_clear_IMR_ACKRCVE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_ACKRCVE;
}

static inline void hri_hsmci_set_IMR_OVRE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_OVRE;
}

static inline bool hri_hsmci_get_IMR_OVRE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_OVRE) >> HSMCI_IMR_OVRE_Pos;
}

static inline void hri_hsmci_write_IMR_OVRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_OVRE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_OVRE;
	}
}

static inline void hri_hsmci_clear_IMR_OVRE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_OVRE;
}

static inline void hri_hsmci_set_IMR_UNRE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_UNRE;
}

static inline bool hri_hsmci_get_IMR_UNRE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_IMR & HSMCI_IMR_UNRE) >> HSMCI_IMR_UNRE_Pos;
}

static inline void hri_hsmci_write_IMR_UNRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_UNRE;
	} else {
		((Hsmci *)hw)->HSMCI_IER = HSMCI_IMR_UNRE;
	}
}

static inline void hri_hsmci_clear_IMR_UNRE_bit(const void *const hw)
{
	((Hsmci *)hw)->HSMCI_IDR = HSMCI_IMR_UNRE;
}

static inline void hri_hsmci_set_IMR_reg(const void *const hw, hri_hsmci_imr_reg_t mask)
{
	((Hsmci *)hw)->HSMCI_IER = mask;
}

static inline hri_hsmci_imr_reg_t hri_hsmci_get_IMR_reg(const void *const hw, hri_hsmci_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_hsmci_imr_reg_t hri_hsmci_read_IMR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_IMR;
}

static inline void hri_hsmci_write_IMR_reg(const void *const hw, hri_hsmci_imr_reg_t data)
{
	((Hsmci *)hw)->HSMCI_IER = data;
	((Hsmci *)hw)->HSMCI_IDR = ~data;
}

static inline void hri_hsmci_clear_IMR_reg(const void *const hw, hri_hsmci_imr_reg_t mask)
{
	((Hsmci *)hw)->HSMCI_IDR = mask;
}

static inline hri_hsmci_rspr_reg_t hri_hsmci_get_RSPR_RSP_bf(const void *const hw, uint8_t index,
                                                             hri_hsmci_rspr_reg_t mask)
{
	return (((Hsmci *)hw)->HSMCI_RSPR[index] & HSMCI_RSPR_RSP(mask)) >> HSMCI_RSPR_RSP_Pos;
}

static inline hri_hsmci_rspr_reg_t hri_hsmci_read_RSPR_RSP_bf(const void *const hw, uint8_t index)
{
	return (((Hsmci *)hw)->HSMCI_RSPR[index] & HSMCI_RSPR_RSP_Msk) >> HSMCI_RSPR_RSP_Pos;
}

static inline hri_hsmci_rspr_reg_t hri_hsmci_get_RSPR_reg(const void *const hw, uint8_t index,
                                                          hri_hsmci_rspr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_RSPR[index];
	tmp &= mask;
	return tmp;
}

static inline hri_hsmci_rspr_reg_t hri_hsmci_read_RSPR_reg(const void *const hw, uint8_t index)
{
	return ((Hsmci *)hw)->HSMCI_RSPR[index];
}

static inline hri_hsmci_rdr_reg_t hri_hsmci_get_RDR_DATA_bf(const void *const hw, hri_hsmci_rdr_reg_t mask)
{
	return (((Hsmci *)hw)->HSMCI_RDR & HSMCI_RDR_DATA(mask)) >> HSMCI_RDR_DATA_Pos;
}

static inline hri_hsmci_rdr_reg_t hri_hsmci_read_RDR_DATA_bf(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_RDR & HSMCI_RDR_DATA_Msk) >> HSMCI_RDR_DATA_Pos;
}

static inline hri_hsmci_rdr_reg_t hri_hsmci_get_RDR_reg(const void *const hw, hri_hsmci_rdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_RDR;
	tmp &= mask;
	return tmp;
}

static inline hri_hsmci_rdr_reg_t hri_hsmci_read_RDR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_RDR;
}

static inline bool hri_hsmci_get_SR_CMDRDY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_CMDRDY) > 0;
}

static inline bool hri_hsmci_get_SR_RXRDY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_RXRDY) > 0;
}

static inline bool hri_hsmci_get_SR_TXRDY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_TXRDY) > 0;
}

static inline bool hri_hsmci_get_SR_BLKE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_BLKE) > 0;
}

static inline bool hri_hsmci_get_SR_DTIP_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_DTIP) > 0;
}

static inline bool hri_hsmci_get_SR_NOTBUSY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_NOTBUSY) > 0;
}

static inline bool hri_hsmci_get_SR_SDIOIRQA_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_SDIOIRQA) > 0;
}

static inline bool hri_hsmci_get_SR_SDIOWAIT_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_SDIOWAIT) > 0;
}

static inline bool hri_hsmci_get_SR_CSRCV_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_CSRCV) > 0;
}

static inline bool hri_hsmci_get_SR_RINDE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_RINDE) > 0;
}

static inline bool hri_hsmci_get_SR_RDIRE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_RDIRE) > 0;
}

static inline bool hri_hsmci_get_SR_RCRCE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_RCRCE) > 0;
}

static inline bool hri_hsmci_get_SR_RENDE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_RENDE) > 0;
}

static inline bool hri_hsmci_get_SR_RTOE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_RTOE) > 0;
}

static inline bool hri_hsmci_get_SR_DCRCE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_DCRCE) > 0;
}

static inline bool hri_hsmci_get_SR_DTOE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_DTOE) > 0;
}

static inline bool hri_hsmci_get_SR_CSTOE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_CSTOE) > 0;
}

static inline bool hri_hsmci_get_SR_BLKOVRE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_BLKOVRE) > 0;
}

static inline bool hri_hsmci_get_SR_FIFOEMPTY_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_FIFOEMPTY) > 0;
}

static inline bool hri_hsmci_get_SR_XFRDONE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_XFRDONE) > 0;
}

static inline bool hri_hsmci_get_SR_ACKRCV_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_ACKRCV) > 0;
}

static inline bool hri_hsmci_get_SR_ACKRCVE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_ACKRCVE) > 0;
}

static inline bool hri_hsmci_get_SR_OVRE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_OVRE) > 0;
}

static inline bool hri_hsmci_get_SR_UNRE_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_SR & HSMCI_SR_UNRE) > 0;
}

static inline hri_hsmci_sr_reg_t hri_hsmci_get_SR_reg(const void *const hw, hri_hsmci_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_hsmci_sr_reg_t hri_hsmci_read_SR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_SR;
}

static inline bool hri_hsmci_get_WPSR_WPVS_bit(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_WPSR & HSMCI_WPSR_WPVS) > 0;
}

static inline hri_hsmci_wpsr_reg_t hri_hsmci_get_WPSR_WPVSRC_bf(const void *const hw, hri_hsmci_wpsr_reg_t mask)
{
	return (((Hsmci *)hw)->HSMCI_WPSR & HSMCI_WPSR_WPVSRC(mask)) >> HSMCI_WPSR_WPVSRC_Pos;
}

static inline hri_hsmci_wpsr_reg_t hri_hsmci_read_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Hsmci *)hw)->HSMCI_WPSR & HSMCI_WPSR_WPVSRC_Msk) >> HSMCI_WPSR_WPVSRC_Pos;
}

static inline hri_hsmci_wpsr_reg_t hri_hsmci_get_WPSR_reg(const void *const hw, hri_hsmci_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_hsmci_wpsr_reg_t hri_hsmci_read_WPSR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_WPSR;
}

static inline void hri_hsmci_set_MR_RDPROOF_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR |= HSMCI_MR_RDPROOF;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_MR_RDPROOF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp = (tmp & HSMCI_MR_RDPROOF) >> HSMCI_MR_RDPROOF_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_MR_RDPROOF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp &= ~HSMCI_MR_RDPROOF;
	tmp |= value << HSMCI_MR_RDPROOF_Pos;
	((Hsmci *)hw)->HSMCI_MR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_MR_RDPROOF_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR &= ~HSMCI_MR_RDPROOF;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_MR_RDPROOF_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR ^= HSMCI_MR_RDPROOF;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_MR_WRPROOF_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR |= HSMCI_MR_WRPROOF;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_MR_WRPROOF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp = (tmp & HSMCI_MR_WRPROOF) >> HSMCI_MR_WRPROOF_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_MR_WRPROOF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp &= ~HSMCI_MR_WRPROOF;
	tmp |= value << HSMCI_MR_WRPROOF_Pos;
	((Hsmci *)hw)->HSMCI_MR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_MR_WRPROOF_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR &= ~HSMCI_MR_WRPROOF;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_MR_WRPROOF_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR ^= HSMCI_MR_WRPROOF;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_MR_FBYTE_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR |= HSMCI_MR_FBYTE;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_MR_FBYTE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp = (tmp & HSMCI_MR_FBYTE) >> HSMCI_MR_FBYTE_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_MR_FBYTE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp &= ~HSMCI_MR_FBYTE;
	tmp |= value << HSMCI_MR_FBYTE_Pos;
	((Hsmci *)hw)->HSMCI_MR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_MR_FBYTE_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR &= ~HSMCI_MR_FBYTE;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_MR_FBYTE_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR ^= HSMCI_MR_FBYTE;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_MR_PADV_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR |= HSMCI_MR_PADV;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_MR_PADV_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp = (tmp & HSMCI_MR_PADV) >> HSMCI_MR_PADV_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_MR_PADV_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp &= ~HSMCI_MR_PADV;
	tmp |= value << HSMCI_MR_PADV_Pos;
	((Hsmci *)hw)->HSMCI_MR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_MR_PADV_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR &= ~HSMCI_MR_PADV;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_MR_PADV_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR ^= HSMCI_MR_PADV;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_MR_CLKODD_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR |= HSMCI_MR_CLKODD;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_MR_CLKODD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp = (tmp & HSMCI_MR_CLKODD) >> HSMCI_MR_CLKODD_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_MR_CLKODD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp &= ~HSMCI_MR_CLKODD;
	tmp |= value << HSMCI_MR_CLKODD_Pos;
	((Hsmci *)hw)->HSMCI_MR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_MR_CLKODD_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR &= ~HSMCI_MR_CLKODD;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_MR_CLKODD_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR ^= HSMCI_MR_CLKODD;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_MR_CLKDIV_bf(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR |= HSMCI_MR_CLKDIV(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_mr_reg_t hri_hsmci_get_MR_CLKDIV_bf(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp = (tmp & HSMCI_MR_CLKDIV(mask)) >> HSMCI_MR_CLKDIV_Pos;
	return tmp;
}

static inline void hri_hsmci_write_MR_CLKDIV_bf(const void *const hw, hri_hsmci_mr_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp &= ~HSMCI_MR_CLKDIV_Msk;
	tmp |= HSMCI_MR_CLKDIV(data);
	((Hsmci *)hw)->HSMCI_MR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_MR_CLKDIV_bf(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR &= ~HSMCI_MR_CLKDIV(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_MR_CLKDIV_bf(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR ^= HSMCI_MR_CLKDIV(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_mr_reg_t hri_hsmci_read_MR_CLKDIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp = (tmp & HSMCI_MR_CLKDIV_Msk) >> HSMCI_MR_CLKDIV_Pos;
	return tmp;
}

static inline void hri_hsmci_set_MR_PWSDIV_bf(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR |= HSMCI_MR_PWSDIV(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_mr_reg_t hri_hsmci_get_MR_PWSDIV_bf(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp = (tmp & HSMCI_MR_PWSDIV(mask)) >> HSMCI_MR_PWSDIV_Pos;
	return tmp;
}

static inline void hri_hsmci_write_MR_PWSDIV_bf(const void *const hw, hri_hsmci_mr_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp &= ~HSMCI_MR_PWSDIV_Msk;
	tmp |= HSMCI_MR_PWSDIV(data);
	((Hsmci *)hw)->HSMCI_MR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_MR_PWSDIV_bf(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR &= ~HSMCI_MR_PWSDIV(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_MR_PWSDIV_bf(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR ^= HSMCI_MR_PWSDIV(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_mr_reg_t hri_hsmci_read_MR_PWSDIV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp = (tmp & HSMCI_MR_PWSDIV_Msk) >> HSMCI_MR_PWSDIV_Pos;
	return tmp;
}

static inline void hri_hsmci_set_MR_reg(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_mr_reg_t hri_hsmci_get_MR_reg(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_MR_reg(const void *const hw, hri_hsmci_mr_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_MR_reg(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_MR_reg(const void *const hw, hri_hsmci_mr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_MR ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_mr_reg_t hri_hsmci_read_MR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_MR;
}

static inline void hri_hsmci_set_DTOR_DTOCYC_bf(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR |= HSMCI_DTOR_DTOCYC(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dtor_reg_t hri_hsmci_get_DTOR_DTOCYC_bf(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_DTOR;
	tmp = (tmp & HSMCI_DTOR_DTOCYC(mask)) >> HSMCI_DTOR_DTOCYC_Pos;
	return tmp;
}

static inline void hri_hsmci_write_DTOR_DTOCYC_bf(const void *const hw, hri_hsmci_dtor_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_DTOR;
	tmp &= ~HSMCI_DTOR_DTOCYC_Msk;
	tmp |= HSMCI_DTOR_DTOCYC(data);
	((Hsmci *)hw)->HSMCI_DTOR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_DTOR_DTOCYC_bf(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR &= ~HSMCI_DTOR_DTOCYC(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_DTOR_DTOCYC_bf(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR ^= HSMCI_DTOR_DTOCYC(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dtor_reg_t hri_hsmci_read_DTOR_DTOCYC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_DTOR;
	tmp = (tmp & HSMCI_DTOR_DTOCYC_Msk) >> HSMCI_DTOR_DTOCYC_Pos;
	return tmp;
}

static inline void hri_hsmci_set_DTOR_DTOMUL_bf(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR |= HSMCI_DTOR_DTOMUL(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dtor_reg_t hri_hsmci_get_DTOR_DTOMUL_bf(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_DTOR;
	tmp = (tmp & HSMCI_DTOR_DTOMUL(mask)) >> HSMCI_DTOR_DTOMUL_Pos;
	return tmp;
}

static inline void hri_hsmci_write_DTOR_DTOMUL_bf(const void *const hw, hri_hsmci_dtor_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_DTOR;
	tmp &= ~HSMCI_DTOR_DTOMUL_Msk;
	tmp |= HSMCI_DTOR_DTOMUL(data);
	((Hsmci *)hw)->HSMCI_DTOR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_DTOR_DTOMUL_bf(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR &= ~HSMCI_DTOR_DTOMUL(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_DTOR_DTOMUL_bf(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR ^= HSMCI_DTOR_DTOMUL(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dtor_reg_t hri_hsmci_read_DTOR_DTOMUL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_DTOR;
	tmp = (tmp & HSMCI_DTOR_DTOMUL_Msk) >> HSMCI_DTOR_DTOMUL_Pos;
	return tmp;
}

static inline void hri_hsmci_set_DTOR_reg(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dtor_reg_t hri_hsmci_get_DTOR_reg(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_DTOR;
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_DTOR_reg(const void *const hw, hri_hsmci_dtor_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_DTOR_reg(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_DTOR_reg(const void *const hw, hri_hsmci_dtor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DTOR ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dtor_reg_t hri_hsmci_read_DTOR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_DTOR;
}

static inline void hri_hsmci_set_SDCR_SDCSEL_bf(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR |= HSMCI_SDCR_SDCSEL(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_sdcr_reg_t hri_hsmci_get_SDCR_SDCSEL_bf(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_SDCR;
	tmp = (tmp & HSMCI_SDCR_SDCSEL(mask)) >> HSMCI_SDCR_SDCSEL_Pos;
	return tmp;
}

static inline void hri_hsmci_write_SDCR_SDCSEL_bf(const void *const hw, hri_hsmci_sdcr_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_SDCR;
	tmp &= ~HSMCI_SDCR_SDCSEL_Msk;
	tmp |= HSMCI_SDCR_SDCSEL(data);
	((Hsmci *)hw)->HSMCI_SDCR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_SDCR_SDCSEL_bf(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR &= ~HSMCI_SDCR_SDCSEL(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_SDCR_SDCSEL_bf(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR ^= HSMCI_SDCR_SDCSEL(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_sdcr_reg_t hri_hsmci_read_SDCR_SDCSEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_SDCR;
	tmp = (tmp & HSMCI_SDCR_SDCSEL_Msk) >> HSMCI_SDCR_SDCSEL_Pos;
	return tmp;
}

static inline void hri_hsmci_set_SDCR_SDCBUS_bf(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR |= HSMCI_SDCR_SDCBUS(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_sdcr_reg_t hri_hsmci_get_SDCR_SDCBUS_bf(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_SDCR;
	tmp = (tmp & HSMCI_SDCR_SDCBUS(mask)) >> HSMCI_SDCR_SDCBUS_Pos;
	return tmp;
}

static inline void hri_hsmci_write_SDCR_SDCBUS_bf(const void *const hw, hri_hsmci_sdcr_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_SDCR;
	tmp &= ~HSMCI_SDCR_SDCBUS_Msk;
	tmp |= HSMCI_SDCR_SDCBUS(data);
	((Hsmci *)hw)->HSMCI_SDCR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_SDCR_SDCBUS_bf(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR &= ~HSMCI_SDCR_SDCBUS(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_SDCR_SDCBUS_bf(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR ^= HSMCI_SDCR_SDCBUS(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_sdcr_reg_t hri_hsmci_read_SDCR_SDCBUS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_SDCR;
	tmp = (tmp & HSMCI_SDCR_SDCBUS_Msk) >> HSMCI_SDCR_SDCBUS_Pos;
	return tmp;
}

static inline void hri_hsmci_set_SDCR_reg(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_sdcr_reg_t hri_hsmci_get_SDCR_reg(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_SDCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_SDCR_reg(const void *const hw, hri_hsmci_sdcr_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_SDCR_reg(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_SDCR_reg(const void *const hw, hri_hsmci_sdcr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_SDCR ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_sdcr_reg_t hri_hsmci_read_SDCR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_SDCR;
}

static inline void hri_hsmci_set_ARGR_ARG_bf(const void *const hw, hri_hsmci_argr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_ARGR |= HSMCI_ARGR_ARG(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_argr_reg_t hri_hsmci_get_ARGR_ARG_bf(const void *const hw, hri_hsmci_argr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_ARGR;
	tmp = (tmp & HSMCI_ARGR_ARG(mask)) >> HSMCI_ARGR_ARG_Pos;
	return tmp;
}

static inline void hri_hsmci_write_ARGR_ARG_bf(const void *const hw, hri_hsmci_argr_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_ARGR;
	tmp &= ~HSMCI_ARGR_ARG_Msk;
	tmp |= HSMCI_ARGR_ARG(data);
	((Hsmci *)hw)->HSMCI_ARGR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_ARGR_ARG_bf(const void *const hw, hri_hsmci_argr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_ARGR &= ~HSMCI_ARGR_ARG(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_ARGR_ARG_bf(const void *const hw, hri_hsmci_argr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_ARGR ^= HSMCI_ARGR_ARG(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_argr_reg_t hri_hsmci_read_ARGR_ARG_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_ARGR;
	tmp = (tmp & HSMCI_ARGR_ARG_Msk) >> HSMCI_ARGR_ARG_Pos;
	return tmp;
}

static inline void hri_hsmci_set_ARGR_reg(const void *const hw, hri_hsmci_argr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_ARGR |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_argr_reg_t hri_hsmci_get_ARGR_reg(const void *const hw, hri_hsmci_argr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_ARGR;
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_ARGR_reg(const void *const hw, hri_hsmci_argr_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_ARGR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_ARGR_reg(const void *const hw, hri_hsmci_argr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_ARGR &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_ARGR_reg(const void *const hw, hri_hsmci_argr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_ARGR ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_argr_reg_t hri_hsmci_read_ARGR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_ARGR;
}

static inline void hri_hsmci_set_BLKR_BCNT_bf(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR |= HSMCI_BLKR_BCNT(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_blkr_reg_t hri_hsmci_get_BLKR_BCNT_bf(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_BLKR;
	tmp = (tmp & HSMCI_BLKR_BCNT(mask)) >> HSMCI_BLKR_BCNT_Pos;
	return tmp;
}

static inline void hri_hsmci_write_BLKR_BCNT_bf(const void *const hw, hri_hsmci_blkr_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_BLKR;
	tmp &= ~HSMCI_BLKR_BCNT_Msk;
	tmp |= HSMCI_BLKR_BCNT(data);
	((Hsmci *)hw)->HSMCI_BLKR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_BLKR_BCNT_bf(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR &= ~HSMCI_BLKR_BCNT(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_BLKR_BCNT_bf(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR ^= HSMCI_BLKR_BCNT(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_blkr_reg_t hri_hsmci_read_BLKR_BCNT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_BLKR;
	tmp = (tmp & HSMCI_BLKR_BCNT_Msk) >> HSMCI_BLKR_BCNT_Pos;
	return tmp;
}

static inline void hri_hsmci_set_BLKR_BLKLEN_bf(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR |= HSMCI_BLKR_BLKLEN(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_blkr_reg_t hri_hsmci_get_BLKR_BLKLEN_bf(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_BLKR;
	tmp = (tmp & HSMCI_BLKR_BLKLEN(mask)) >> HSMCI_BLKR_BLKLEN_Pos;
	return tmp;
}

static inline void hri_hsmci_write_BLKR_BLKLEN_bf(const void *const hw, hri_hsmci_blkr_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_BLKR;
	tmp &= ~HSMCI_BLKR_BLKLEN_Msk;
	tmp |= HSMCI_BLKR_BLKLEN(data);
	((Hsmci *)hw)->HSMCI_BLKR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_BLKR_BLKLEN_bf(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR &= ~HSMCI_BLKR_BLKLEN(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_BLKR_BLKLEN_bf(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR ^= HSMCI_BLKR_BLKLEN(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_blkr_reg_t hri_hsmci_read_BLKR_BLKLEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_BLKR;
	tmp = (tmp & HSMCI_BLKR_BLKLEN_Msk) >> HSMCI_BLKR_BLKLEN_Pos;
	return tmp;
}

static inline void hri_hsmci_set_BLKR_reg(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_blkr_reg_t hri_hsmci_get_BLKR_reg(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_BLKR;
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_BLKR_reg(const void *const hw, hri_hsmci_blkr_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_BLKR_reg(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_BLKR_reg(const void *const hw, hri_hsmci_blkr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_BLKR ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_blkr_reg_t hri_hsmci_read_BLKR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_BLKR;
}

static inline void hri_hsmci_set_CSTOR_CSTOCYC_bf(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR |= HSMCI_CSTOR_CSTOCYC(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_cstor_reg_t hri_hsmci_get_CSTOR_CSTOCYC_bf(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CSTOR;
	tmp = (tmp & HSMCI_CSTOR_CSTOCYC(mask)) >> HSMCI_CSTOR_CSTOCYC_Pos;
	return tmp;
}

static inline void hri_hsmci_write_CSTOR_CSTOCYC_bf(const void *const hw, hri_hsmci_cstor_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_CSTOR;
	tmp &= ~HSMCI_CSTOR_CSTOCYC_Msk;
	tmp |= HSMCI_CSTOR_CSTOCYC(data);
	((Hsmci *)hw)->HSMCI_CSTOR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_CSTOR_CSTOCYC_bf(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR &= ~HSMCI_CSTOR_CSTOCYC(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_CSTOR_CSTOCYC_bf(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR ^= HSMCI_CSTOR_CSTOCYC(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_cstor_reg_t hri_hsmci_read_CSTOR_CSTOCYC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CSTOR;
	tmp = (tmp & HSMCI_CSTOR_CSTOCYC_Msk) >> HSMCI_CSTOR_CSTOCYC_Pos;
	return tmp;
}

static inline void hri_hsmci_set_CSTOR_CSTOMUL_bf(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR |= HSMCI_CSTOR_CSTOMUL(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_cstor_reg_t hri_hsmci_get_CSTOR_CSTOMUL_bf(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CSTOR;
	tmp = (tmp & HSMCI_CSTOR_CSTOMUL(mask)) >> HSMCI_CSTOR_CSTOMUL_Pos;
	return tmp;
}

static inline void hri_hsmci_write_CSTOR_CSTOMUL_bf(const void *const hw, hri_hsmci_cstor_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_CSTOR;
	tmp &= ~HSMCI_CSTOR_CSTOMUL_Msk;
	tmp |= HSMCI_CSTOR_CSTOMUL(data);
	((Hsmci *)hw)->HSMCI_CSTOR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_CSTOR_CSTOMUL_bf(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR &= ~HSMCI_CSTOR_CSTOMUL(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_CSTOR_CSTOMUL_bf(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR ^= HSMCI_CSTOR_CSTOMUL(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_cstor_reg_t hri_hsmci_read_CSTOR_CSTOMUL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CSTOR;
	tmp = (tmp & HSMCI_CSTOR_CSTOMUL_Msk) >> HSMCI_CSTOR_CSTOMUL_Pos;
	return tmp;
}

static inline void hri_hsmci_set_CSTOR_reg(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_cstor_reg_t hri_hsmci_get_CSTOR_reg(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CSTOR;
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_CSTOR_reg(const void *const hw, hri_hsmci_cstor_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_CSTOR_reg(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_CSTOR_reg(const void *const hw, hri_hsmci_cstor_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CSTOR ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_cstor_reg_t hri_hsmci_read_CSTOR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_CSTOR;
}

static inline void hri_hsmci_set_DMA_DMAEN_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA |= HSMCI_DMA_DMAEN;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_DMA_DMAEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_DMA;
	tmp = (tmp & HSMCI_DMA_DMAEN) >> HSMCI_DMA_DMAEN_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_DMA_DMAEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_DMA;
	tmp &= ~HSMCI_DMA_DMAEN;
	tmp |= value << HSMCI_DMA_DMAEN_Pos;
	((Hsmci *)hw)->HSMCI_DMA = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_DMA_DMAEN_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA &= ~HSMCI_DMA_DMAEN;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_DMA_DMAEN_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA ^= HSMCI_DMA_DMAEN;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_DMA_CHKSIZE_bf(const void *const hw, hri_hsmci_dma_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA |= HSMCI_DMA_CHKSIZE(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dma_reg_t hri_hsmci_get_DMA_CHKSIZE_bf(const void *const hw, hri_hsmci_dma_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_DMA;
	tmp = (tmp & HSMCI_DMA_CHKSIZE(mask)) >> HSMCI_DMA_CHKSIZE_Pos;
	return tmp;
}

static inline void hri_hsmci_write_DMA_CHKSIZE_bf(const void *const hw, hri_hsmci_dma_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_DMA;
	tmp &= ~HSMCI_DMA_CHKSIZE_Msk;
	tmp |= HSMCI_DMA_CHKSIZE(data);
	((Hsmci *)hw)->HSMCI_DMA = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_DMA_CHKSIZE_bf(const void *const hw, hri_hsmci_dma_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA &= ~HSMCI_DMA_CHKSIZE(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_DMA_CHKSIZE_bf(const void *const hw, hri_hsmci_dma_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA ^= HSMCI_DMA_CHKSIZE(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dma_reg_t hri_hsmci_read_DMA_CHKSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_DMA;
	tmp = (tmp & HSMCI_DMA_CHKSIZE_Msk) >> HSMCI_DMA_CHKSIZE_Pos;
	return tmp;
}

static inline void hri_hsmci_set_DMA_reg(const void *const hw, hri_hsmci_dma_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dma_reg_t hri_hsmci_get_DMA_reg(const void *const hw, hri_hsmci_dma_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_DMA;
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_DMA_reg(const void *const hw, hri_hsmci_dma_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_DMA_reg(const void *const hw, hri_hsmci_dma_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_DMA_reg(const void *const hw, hri_hsmci_dma_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_DMA ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_dma_reg_t hri_hsmci_read_DMA_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_DMA;
}

static inline void hri_hsmci_set_CFG_FIFOMODE_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG |= HSMCI_CFG_FIFOMODE;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_CFG_FIFOMODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CFG;
	tmp = (tmp & HSMCI_CFG_FIFOMODE) >> HSMCI_CFG_FIFOMODE_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_CFG_FIFOMODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_CFG;
	tmp &= ~HSMCI_CFG_FIFOMODE;
	tmp |= value << HSMCI_CFG_FIFOMODE_Pos;
	((Hsmci *)hw)->HSMCI_CFG = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_CFG_FIFOMODE_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG &= ~HSMCI_CFG_FIFOMODE;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_CFG_FIFOMODE_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG ^= HSMCI_CFG_FIFOMODE;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_CFG_FERRCTRL_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG |= HSMCI_CFG_FERRCTRL;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_CFG_FERRCTRL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CFG;
	tmp = (tmp & HSMCI_CFG_FERRCTRL) >> HSMCI_CFG_FERRCTRL_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_CFG_FERRCTRL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_CFG;
	tmp &= ~HSMCI_CFG_FERRCTRL;
	tmp |= value << HSMCI_CFG_FERRCTRL_Pos;
	((Hsmci *)hw)->HSMCI_CFG = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_CFG_FERRCTRL_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG &= ~HSMCI_CFG_FERRCTRL;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_CFG_FERRCTRL_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG ^= HSMCI_CFG_FERRCTRL;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_CFG_HSMODE_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG |= HSMCI_CFG_HSMODE;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_CFG_HSMODE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CFG;
	tmp = (tmp & HSMCI_CFG_HSMODE) >> HSMCI_CFG_HSMODE_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_CFG_HSMODE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_CFG;
	tmp &= ~HSMCI_CFG_HSMODE;
	tmp |= value << HSMCI_CFG_HSMODE_Pos;
	((Hsmci *)hw)->HSMCI_CFG = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_CFG_HSMODE_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG &= ~HSMCI_CFG_HSMODE;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_CFG_HSMODE_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG ^= HSMCI_CFG_HSMODE;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_CFG_LSYNC_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG |= HSMCI_CFG_LSYNC;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_CFG_LSYNC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CFG;
	tmp = (tmp & HSMCI_CFG_LSYNC) >> HSMCI_CFG_LSYNC_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_CFG_LSYNC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_CFG;
	tmp &= ~HSMCI_CFG_LSYNC;
	tmp |= value << HSMCI_CFG_LSYNC_Pos;
	((Hsmci *)hw)->HSMCI_CFG = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_CFG_LSYNC_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG &= ~HSMCI_CFG_LSYNC;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_CFG_LSYNC_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG ^= HSMCI_CFG_LSYNC;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_CFG_reg(const void *const hw, hri_hsmci_cfg_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_cfg_reg_t hri_hsmci_get_CFG_reg(const void *const hw, hri_hsmci_cfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_CFG;
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_CFG_reg(const void *const hw, hri_hsmci_cfg_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_CFG_reg(const void *const hw, hri_hsmci_cfg_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_CFG_reg(const void *const hw, hri_hsmci_cfg_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CFG ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_cfg_reg_t hri_hsmci_read_CFG_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_CFG;
}

static inline void hri_hsmci_set_WPMR_WPEN_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR |= HSMCI_WPMR_WPEN;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_hsmci_get_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_WPMR;
	tmp = (tmp & HSMCI_WPMR_WPEN) >> HSMCI_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_hsmci_write_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_WPMR;
	tmp &= ~HSMCI_WPMR_WPEN;
	tmp |= value << HSMCI_WPMR_WPEN_Pos;
	((Hsmci *)hw)->HSMCI_WPMR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_WPMR_WPEN_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR &= ~HSMCI_WPMR_WPEN;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_WPMR_WPEN_bit(const void *const hw)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR ^= HSMCI_WPMR_WPEN;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_set_WPMR_WPKEY_bf(const void *const hw, hri_hsmci_wpmr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR |= HSMCI_WPMR_WPKEY(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_wpmr_reg_t hri_hsmci_get_WPMR_WPKEY_bf(const void *const hw, hri_hsmci_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_WPMR;
	tmp = (tmp & HSMCI_WPMR_WPKEY(mask)) >> HSMCI_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_hsmci_write_WPMR_WPKEY_bf(const void *const hw, hri_hsmci_wpmr_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_WPMR;
	tmp &= ~HSMCI_WPMR_WPKEY_Msk;
	tmp |= HSMCI_WPMR_WPKEY(data);
	((Hsmci *)hw)->HSMCI_WPMR = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_WPMR_WPKEY_bf(const void *const hw, hri_hsmci_wpmr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR &= ~HSMCI_WPMR_WPKEY(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_WPMR_WPKEY_bf(const void *const hw, hri_hsmci_wpmr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR ^= HSMCI_WPMR_WPKEY(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_wpmr_reg_t hri_hsmci_read_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_WPMR;
	tmp = (tmp & HSMCI_WPMR_WPKEY_Msk) >> HSMCI_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_hsmci_set_WPMR_reg(const void *const hw, hri_hsmci_wpmr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_wpmr_reg_t hri_hsmci_get_WPMR_reg(const void *const hw, hri_hsmci_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_WPMR_reg(const void *const hw, hri_hsmci_wpmr_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_WPMR_reg(const void *const hw, hri_hsmci_wpmr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_WPMR_reg(const void *const hw, hri_hsmci_wpmr_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_WPMR ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_wpmr_reg_t hri_hsmci_read_WPMR_reg(const void *const hw)
{
	return ((Hsmci *)hw)->HSMCI_WPMR;
}

static inline void hri_hsmci_set_FIFO_DATA_bf(const void *const hw, uint8_t index, hri_hsmci_fifo_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_FIFO[index] |= HSMCI_FIFO_DATA(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_fifo_reg_t hri_hsmci_get_FIFO_DATA_bf(const void *const hw, uint8_t index,
                                                              hri_hsmci_fifo_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_FIFO[index];
	tmp = (tmp & HSMCI_FIFO_DATA(mask)) >> HSMCI_FIFO_DATA_Pos;
	return tmp;
}

static inline void hri_hsmci_write_FIFO_DATA_bf(const void *const hw, uint8_t index, hri_hsmci_fifo_reg_t data)
{
	uint32_t tmp;
	HSMCI_CRITICAL_SECTION_ENTER();
	tmp = ((Hsmci *)hw)->HSMCI_FIFO[index];
	tmp &= ~HSMCI_FIFO_DATA_Msk;
	tmp |= HSMCI_FIFO_DATA(data);
	((Hsmci *)hw)->HSMCI_FIFO[index] = tmp;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_FIFO_DATA_bf(const void *const hw, uint8_t index, hri_hsmci_fifo_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_FIFO[index] &= ~HSMCI_FIFO_DATA(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_FIFO_DATA_bf(const void *const hw, uint8_t index, hri_hsmci_fifo_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_FIFO[index] ^= HSMCI_FIFO_DATA(mask);
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_fifo_reg_t hri_hsmci_read_FIFO_DATA_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_FIFO[index];
	tmp = (tmp & HSMCI_FIFO_DATA_Msk) >> HSMCI_FIFO_DATA_Pos;
	return tmp;
}

static inline void hri_hsmci_set_FIFO_reg(const void *const hw, uint8_t index, hri_hsmci_fifo_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_FIFO[index] |= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_fifo_reg_t hri_hsmci_get_FIFO_reg(const void *const hw, uint8_t index,
                                                          hri_hsmci_fifo_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Hsmci *)hw)->HSMCI_FIFO[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_hsmci_write_FIFO_reg(const void *const hw, uint8_t index, hri_hsmci_fifo_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_FIFO[index] = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_clear_FIFO_reg(const void *const hw, uint8_t index, hri_hsmci_fifo_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_FIFO[index] &= ~mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_toggle_FIFO_reg(const void *const hw, uint8_t index, hri_hsmci_fifo_reg_t mask)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_FIFO[index] ^= mask;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline hri_hsmci_fifo_reg_t hri_hsmci_read_FIFO_reg(const void *const hw, uint8_t index)
{
	return ((Hsmci *)hw)->HSMCI_FIFO[index];
}

static inline void hri_hsmci_write_CR_reg(const void *const hw, hri_hsmci_cr_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_write_CMDR_reg(const void *const hw, hri_hsmci_cmdr_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_CMDR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

static inline void hri_hsmci_write_TDR_reg(const void *const hw, hri_hsmci_tdr_reg_t data)
{
	HSMCI_CRITICAL_SECTION_ENTER();
	((Hsmci *)hw)->HSMCI_TDR = data;
	HSMCI_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_HSMCI_E70B_H_INCLUDED */
#endif /* _SAME70_HSMCI_COMPONENT_ */
