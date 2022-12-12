/**
 * \file
 *
 * \brief SAM USART
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

#ifdef _SAME70_USART_COMPONENT_
#ifndef _HRI_USART_E70B_H_INCLUDED_
#define _HRI_USART_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_USART_CRITICAL_SECTIONS)
#define USART_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define USART_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define USART_CRITICAL_SECTION_ENTER()
#define USART_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_usart_us_brgr_reg_t;
typedef uint32_t hri_usart_us_cr_reg_t;
typedef uint32_t hri_usart_us_csr_reg_t;
typedef uint32_t hri_usart_us_fidi_reg_t;
typedef uint32_t hri_usart_us_icdiff_reg_t;
typedef uint32_t hri_usart_us_idtrx_reg_t;
typedef uint32_t hri_usart_us_idttx_reg_t;
typedef uint32_t hri_usart_us_if_reg_t;
typedef uint32_t hri_usart_us_imr_reg_t;
typedef uint32_t hri_usart_us_linbrr_reg_t;
typedef uint32_t hri_usart_us_linir_reg_t;
typedef uint32_t hri_usart_us_linmr_reg_t;
typedef uint32_t hri_usart_us_lonb1rx_reg_t;
typedef uint32_t hri_usart_us_lonb1tx_reg_t;
typedef uint32_t hri_usart_us_lonbl_reg_t;
typedef uint32_t hri_usart_us_londl_reg_t;
typedef uint32_t hri_usart_us_lonl2hdr_reg_t;
typedef uint32_t hri_usart_us_lonmr_reg_t;
typedef uint32_t hri_usart_us_lonpr_reg_t;
typedef uint32_t hri_usart_us_lonprio_reg_t;
typedef uint32_t hri_usart_us_man_reg_t;
typedef uint32_t hri_usart_us_mr_reg_t;
typedef uint32_t hri_usart_us_ner_reg_t;
typedef uint32_t hri_usart_us_rhr_reg_t;
typedef uint32_t hri_usart_us_rtor_reg_t;
typedef uint32_t hri_usart_us_thr_reg_t;
typedef uint32_t hri_usart_us_ttgr_reg_t;
typedef uint32_t hri_usart_us_wpmr_reg_t;
typedef uint32_t hri_usart_us_wpsr_reg_t;

static inline void hri_usart_set_US_IMR_RXRDY_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_RXRDY;
}

static inline bool hri_usart_get_US_IMR_RXRDY_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_RXRDY) >> US_IMR_RXRDY_Pos;
}

static inline void hri_usart_write_US_IMR_RXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_RXRDY;
	} else {
		((Usart *)hw)->US_IER = US_IMR_RXRDY;
	}
}

static inline void hri_usart_clear_US_IMR_RXRDY_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_RXRDY;
}

static inline void hri_usart_set_US_IMR_TXRDY_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_TXRDY;
}

static inline bool hri_usart_get_US_IMR_TXRDY_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_TXRDY) >> US_IMR_TXRDY_Pos;
}

static inline void hri_usart_write_US_IMR_TXRDY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_TXRDY;
	} else {
		((Usart *)hw)->US_IER = US_IMR_TXRDY;
	}
}

static inline void hri_usart_clear_US_IMR_TXRDY_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_TXRDY;
}

static inline void hri_usart_set_US_IMR_USART_RXBRK_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_USART_RXBRK;
}

static inline bool hri_usart_get_US_IMR_USART_RXBRK_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_USART_RXBRK) >> US_IMR_USART_RXBRK_Pos;
}

static inline void hri_usart_write_US_IMR_USART_RXBRK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_USART_RXBRK;
	} else {
		((Usart *)hw)->US_IER = US_IMR_USART_RXBRK;
	}
}

static inline void hri_usart_clear_US_IMR_USART_RXBRK_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_USART_RXBRK;
}

static inline void hri_usart_set_US_IMR_OVRE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_OVRE;
}

static inline bool hri_usart_get_US_IMR_OVRE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_OVRE) >> US_IMR_OVRE_Pos;
}

static inline void hri_usart_write_US_IMR_OVRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_OVRE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_OVRE;
	}
}

static inline void hri_usart_clear_US_IMR_OVRE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_OVRE;
}

static inline void hri_usart_set_US_IMR_USART_LIN_FRAME_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_USART_LIN_FRAME;
}

static inline bool hri_usart_get_US_IMR_USART_LIN_FRAME_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_USART_LIN_FRAME) >> US_IMR_USART_LIN_FRAME_Pos;
}

static inline void hri_usart_write_US_IMR_USART_LIN_FRAME_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_USART_LIN_FRAME;
	} else {
		((Usart *)hw)->US_IER = US_IMR_USART_LIN_FRAME;
	}
}

static inline void hri_usart_clear_US_IMR_USART_LIN_FRAME_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_USART_LIN_FRAME;
}

static inline void hri_usart_set_US_IMR_USART_LIN_PARE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_USART_LIN_PARE;
}

static inline bool hri_usart_get_US_IMR_USART_LIN_PARE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_USART_LIN_PARE) >> US_IMR_USART_LIN_PARE_Pos;
}

static inline void hri_usart_write_US_IMR_USART_LIN_PARE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_USART_LIN_PARE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_USART_LIN_PARE;
	}
}

static inline void hri_usart_clear_US_IMR_USART_LIN_PARE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_USART_LIN_PARE;
}

static inline void hri_usart_set_US_IMR_USART_LIN_TIMEOUT_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_USART_LIN_TIMEOUT;
}

static inline bool hri_usart_get_US_IMR_USART_LIN_TIMEOUT_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_USART_LIN_TIMEOUT) >> US_IMR_USART_LIN_TIMEOUT_Pos;
}

static inline void hri_usart_write_US_IMR_USART_LIN_TIMEOUT_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_USART_LIN_TIMEOUT;
	} else {
		((Usart *)hw)->US_IER = US_IMR_USART_LIN_TIMEOUT;
	}
}

static inline void hri_usart_clear_US_IMR_USART_LIN_TIMEOUT_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_USART_LIN_TIMEOUT;
}

static inline void hri_usart_set_US_IMR_TXEMPTY_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_TXEMPTY;
}

static inline bool hri_usart_get_US_IMR_TXEMPTY_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_TXEMPTY) >> US_IMR_TXEMPTY_Pos;
}

static inline void hri_usart_write_US_IMR_TXEMPTY_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_TXEMPTY;
	} else {
		((Usart *)hw)->US_IER = US_IMR_TXEMPTY;
	}
}

static inline void hri_usart_clear_US_IMR_TXEMPTY_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_TXEMPTY;
}

static inline void hri_usart_set_US_IMR_USART_ITER_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_USART_ITER;
}

static inline bool hri_usart_get_US_IMR_USART_ITER_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_USART_ITER) >> US_IMR_USART_ITER_Pos;
}

static inline void hri_usart_write_US_IMR_USART_ITER_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_USART_ITER;
	} else {
		((Usart *)hw)->US_IER = US_IMR_USART_ITER;
	}
}

static inline void hri_usart_clear_US_IMR_USART_ITER_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_USART_ITER;
}

static inline void hri_usart_set_US_IMR_USART_NACK_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_USART_NACK;
}

static inline bool hri_usart_get_US_IMR_USART_NACK_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_USART_NACK) >> US_IMR_USART_NACK_Pos;
}

static inline void hri_usart_write_US_IMR_USART_NACK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_USART_NACK;
	} else {
		((Usart *)hw)->US_IER = US_IMR_USART_NACK;
	}
}

static inline void hri_usart_clear_US_IMR_USART_NACK_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_USART_NACK;
}

static inline void hri_usart_set_US_IMR_RIIC_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_RIIC;
}

static inline bool hri_usart_get_US_IMR_RIIC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_RIIC) >> US_IMR_RIIC_Pos;
}

static inline void hri_usart_write_US_IMR_RIIC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_RIIC;
	} else {
		((Usart *)hw)->US_IER = US_IMR_RIIC;
	}
}

static inline void hri_usart_clear_US_IMR_RIIC_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_RIIC;
}

static inline void hri_usart_set_US_IMR_DSRIC_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_DSRIC;
}

static inline bool hri_usart_get_US_IMR_DSRIC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_DSRIC) >> US_IMR_DSRIC_Pos;
}

static inline void hri_usart_write_US_IMR_DSRIC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_DSRIC;
	} else {
		((Usart *)hw)->US_IER = US_IMR_DSRIC;
	}
}

static inline void hri_usart_clear_US_IMR_DSRIC_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_DSRIC;
}

static inline void hri_usart_set_US_IMR_DCDIC_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_DCDIC;
}

static inline bool hri_usart_get_US_IMR_DCDIC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_DCDIC) >> US_IMR_DCDIC_Pos;
}

static inline void hri_usart_write_US_IMR_DCDIC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_DCDIC;
	} else {
		((Usart *)hw)->US_IER = US_IMR_DCDIC;
	}
}

static inline void hri_usart_clear_US_IMR_DCDIC_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_DCDIC;
}

static inline void hri_usart_set_US_IMR_USART_CTSIC_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_USART_CTSIC;
}

static inline bool hri_usart_get_US_IMR_USART_CTSIC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_USART_CTSIC) >> US_IMR_USART_CTSIC_Pos;
}

static inline void hri_usart_write_US_IMR_USART_CTSIC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_USART_CTSIC;
	} else {
		((Usart *)hw)->US_IER = US_IMR_USART_CTSIC;
	}
}

static inline void hri_usart_clear_US_IMR_USART_CTSIC_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_USART_CTSIC;
}

static inline void hri_usart_set_US_IMR_USART_MANE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_USART_MANE;
}

static inline bool hri_usart_get_US_IMR_USART_MANE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_USART_MANE) >> US_IMR_USART_MANE_Pos;
}

static inline void hri_usart_write_US_IMR_USART_MANE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_USART_MANE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_USART_MANE;
	}
}

static inline void hri_usart_clear_US_IMR_USART_MANE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_USART_MANE;
}

static inline void hri_usart_set_US_IMR_LON_SPI_UNRE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LON_SPI_UNRE;
}

static inline bool hri_usart_get_US_IMR_LON_SPI_UNRE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LON_SPI_UNRE) >> US_IMR_LON_SPI_UNRE_Pos;
}

static inline void hri_usart_write_US_IMR_LON_SPI_UNRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LON_SPI_UNRE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LON_SPI_UNRE;
	}
}

static inline void hri_usart_clear_US_IMR_LON_SPI_UNRE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LON_SPI_UNRE;
}

static inline void hri_usart_set_US_IMR_SPI_NSSE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_SPI_NSSE;
}

static inline bool hri_usart_get_US_IMR_SPI_NSSE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_SPI_NSSE) >> US_IMR_SPI_NSSE_Pos;
}

static inline void hri_usart_write_US_IMR_SPI_NSSE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_SPI_NSSE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_SPI_NSSE;
	}
}

static inline void hri_usart_clear_US_IMR_SPI_NSSE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_SPI_NSSE;
}

static inline void hri_usart_set_US_IMR_LIN_LINBK_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINBK;
}

static inline bool hri_usart_get_US_IMR_LIN_LINBK_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINBK) >> US_IMR_LIN_LINBK_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINBK_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINBK;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINBK;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINBK_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINBK;
}

static inline void hri_usart_set_US_IMR_LIN_LINID_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINID;
}

static inline bool hri_usart_get_US_IMR_LIN_LINID_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINID) >> US_IMR_LIN_LINID_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINID_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINID;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINID;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINID_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINID;
}

static inline void hri_usart_set_US_IMR_LIN_LINTC_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINTC;
}

static inline bool hri_usart_get_US_IMR_LIN_LINTC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINTC) >> US_IMR_LIN_LINTC_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINTC_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINTC;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINTC;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINTC_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINTC;
}

static inline void hri_usart_set_US_IMR_LIN_LINBE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINBE;
}

static inline bool hri_usart_get_US_IMR_LIN_LINBE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINBE) >> US_IMR_LIN_LINBE_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINBE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINBE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINBE;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINBE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINBE;
}

static inline void hri_usart_set_US_IMR_LIN_LINISFE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINISFE;
}

static inline bool hri_usart_get_US_IMR_LIN_LINISFE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINISFE) >> US_IMR_LIN_LINISFE_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINISFE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINISFE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINISFE;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINISFE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINISFE;
}

static inline void hri_usart_set_US_IMR_LIN_LINIPE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINIPE;
}

static inline bool hri_usart_get_US_IMR_LIN_LINIPE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINIPE) >> US_IMR_LIN_LINIPE_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINIPE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINIPE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINIPE;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINIPE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINIPE;
}

static inline void hri_usart_set_US_IMR_LIN_LINCE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINCE;
}

static inline bool hri_usart_get_US_IMR_LIN_LINCE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINCE) >> US_IMR_LIN_LINCE_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINCE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINCE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINCE;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINCE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINCE;
}

static inline void hri_usart_set_US_IMR_LIN_LINSNRE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINSNRE;
}

static inline bool hri_usart_get_US_IMR_LIN_LINSNRE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINSNRE) >> US_IMR_LIN_LINSNRE_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINSNRE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINSNRE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINSNRE;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINSNRE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINSNRE;
}

static inline void hri_usart_set_US_IMR_LIN_LINSTE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINSTE;
}

static inline bool hri_usart_get_US_IMR_LIN_LINSTE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINSTE) >> US_IMR_LIN_LINSTE_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINSTE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINSTE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINSTE;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINSTE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINSTE;
}

static inline void hri_usart_set_US_IMR_LIN_LINHTE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LIN_LINHTE;
}

static inline bool hri_usart_get_US_IMR_LIN_LINHTE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LIN_LINHTE) >> US_IMR_LIN_LINHTE_Pos;
}

static inline void hri_usart_write_US_IMR_LIN_LINHTE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LIN_LINHTE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LIN_LINHTE;
	}
}

static inline void hri_usart_clear_US_IMR_LIN_LINHTE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LIN_LINHTE;
}

static inline void hri_usart_set_US_IMR_LON_LSFE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LON_LSFE;
}

static inline bool hri_usart_get_US_IMR_LON_LSFE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LON_LSFE) >> US_IMR_LON_LSFE_Pos;
}

static inline void hri_usart_write_US_IMR_LON_LSFE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LON_LSFE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LON_LSFE;
	}
}

static inline void hri_usart_clear_US_IMR_LON_LSFE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LON_LSFE;
}

static inline void hri_usart_set_US_IMR_LON_LCRCE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LON_LCRCE;
}

static inline bool hri_usart_get_US_IMR_LON_LCRCE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LON_LCRCE) >> US_IMR_LON_LCRCE_Pos;
}

static inline void hri_usart_write_US_IMR_LON_LCRCE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LON_LCRCE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LON_LCRCE;
	}
}

static inline void hri_usart_clear_US_IMR_LON_LCRCE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LON_LCRCE;
}

static inline void hri_usart_set_US_IMR_LON_LTXD_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LON_LTXD;
}

static inline bool hri_usart_get_US_IMR_LON_LTXD_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LON_LTXD) >> US_IMR_LON_LTXD_Pos;
}

static inline void hri_usart_write_US_IMR_LON_LTXD_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LON_LTXD;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LON_LTXD;
	}
}

static inline void hri_usart_clear_US_IMR_LON_LTXD_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LON_LTXD;
}

static inline void hri_usart_set_US_IMR_LON_LCOL_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LON_LCOL;
}

static inline bool hri_usart_get_US_IMR_LON_LCOL_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LON_LCOL) >> US_IMR_LON_LCOL_Pos;
}

static inline void hri_usart_write_US_IMR_LON_LCOL_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LON_LCOL;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LON_LCOL;
	}
}

static inline void hri_usart_clear_US_IMR_LON_LCOL_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LON_LCOL;
}

static inline void hri_usart_set_US_IMR_LON_LFET_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LON_LFET;
}

static inline bool hri_usart_get_US_IMR_LON_LFET_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LON_LFET) >> US_IMR_LON_LFET_Pos;
}

static inline void hri_usart_write_US_IMR_LON_LFET_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LON_LFET;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LON_LFET;
	}
}

static inline void hri_usart_clear_US_IMR_LON_LFET_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LON_LFET;
}

static inline void hri_usart_set_US_IMR_LON_LRXD_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LON_LRXD;
}

static inline bool hri_usart_get_US_IMR_LON_LRXD_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LON_LRXD) >> US_IMR_LON_LRXD_Pos;
}

static inline void hri_usart_write_US_IMR_LON_LRXD_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LON_LRXD;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LON_LRXD;
	}
}

static inline void hri_usart_clear_US_IMR_LON_LRXD_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LON_LRXD;
}

static inline void hri_usart_set_US_IMR_LON_LBLOVFE_bit(const void *const hw)
{
	((Usart *)hw)->US_IER = US_IMR_LON_LBLOVFE;
}

static inline bool hri_usart_get_US_IMR_LON_LBLOVFE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_IMR & US_IMR_LON_LBLOVFE) >> US_IMR_LON_LBLOVFE_Pos;
}

static inline void hri_usart_write_US_IMR_LON_LBLOVFE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usart *)hw)->US_IDR = US_IMR_LON_LBLOVFE;
	} else {
		((Usart *)hw)->US_IER = US_IMR_LON_LBLOVFE;
	}
}

static inline void hri_usart_clear_US_IMR_LON_LBLOVFE_bit(const void *const hw)
{
	((Usart *)hw)->US_IDR = US_IMR_LON_LBLOVFE;
}

static inline void hri_usart_set_US_IMR_reg(const void *const hw, hri_usart_us_imr_reg_t mask)
{
	((Usart *)hw)->US_IER = mask;
}

static inline hri_usart_us_imr_reg_t hri_usart_get_US_IMR_reg(const void *const hw, hri_usart_us_imr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IMR;
	tmp &= mask;
	return tmp;
}

static inline hri_usart_us_imr_reg_t hri_usart_read_US_IMR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_IMR;
}

static inline void hri_usart_write_US_IMR_reg(const void *const hw, hri_usart_us_imr_reg_t data)
{
	((Usart *)hw)->US_IER = data;
	((Usart *)hw)->US_IDR = ~data;
}

static inline void hri_usart_clear_US_IMR_reg(const void *const hw, hri_usart_us_imr_reg_t mask)
{
	((Usart *)hw)->US_IDR = mask;
}

static inline bool hri_usart_get_US_CSR_RXRDY_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_RXRDY) > 0;
}

static inline bool hri_usart_get_US_CSR_TXRDY_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_TXRDY) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_RXBRK_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_RXBRK) > 0;
}

static inline bool hri_usart_get_US_CSR_OVRE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_OVRE) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_LIN_FRAME_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_LIN_FRAME) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_LIN_PARE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_LIN_PARE) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_LIN_TIMEOUT_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_LIN_TIMEOUT) > 0;
}

static inline bool hri_usart_get_US_CSR_TXEMPTY_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_TXEMPTY) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_ITER_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_ITER) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_NACK_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_NACK) > 0;
}

static inline bool hri_usart_get_US_CSR_RIIC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_RIIC) > 0;
}

static inline bool hri_usart_get_US_CSR_DSRIC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_DSRIC) > 0;
}

static inline bool hri_usart_get_US_CSR_DCDIC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_DCDIC) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_CTSIC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_CTSIC) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_RI_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_RI) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_DSR_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_DSR) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_DCD_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_DCD) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_CTS_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_CTS) > 0;
}

static inline bool hri_usart_get_US_CSR_USART_MANERR_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_USART_MANERR) > 0;
}

static inline bool hri_usart_get_US_CSR_LON_SPI_UNRE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LON_SPI_UNRE) > 0;
}

static inline bool hri_usart_get_US_CSR_SPI_NSSE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_SPI_NSSE) > 0;
}

static inline bool hri_usart_get_US_CSR_SPI_NSS_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_SPI_NSS) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINBK_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINBK) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINID_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINID) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINTC_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINTC) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINBLS_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINBLS) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINBE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINBE) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINISFE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINISFE) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINIPE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINIPE) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINCE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINCE) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINSNRE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINSNRE) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINSTE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINSTE) > 0;
}

static inline bool hri_usart_get_US_CSR_LIN_LINHTE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LIN_LINHTE) > 0;
}

static inline bool hri_usart_get_US_CSR_LON_LSFE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LON_LSFE) > 0;
}

static inline bool hri_usart_get_US_CSR_LON_LCRCE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LON_LCRCE) > 0;
}

static inline bool hri_usart_get_US_CSR_LON_LTXD_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LON_LTXD) > 0;
}

static inline bool hri_usart_get_US_CSR_LON_LCOL_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LON_LCOL) > 0;
}

static inline bool hri_usart_get_US_CSR_LON_LFET_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LON_LFET) > 0;
}

static inline bool hri_usart_get_US_CSR_LON_LRXD_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LON_LRXD) > 0;
}

static inline bool hri_usart_get_US_CSR_LON_LBLOVFE_bit(const void *const hw)
{
	return (((Usart *)hw)->US_CSR & US_CSR_LON_LBLOVFE) > 0;
}

static inline hri_usart_us_csr_reg_t hri_usart_get_US_CSR_reg(const void *const hw, hri_usart_us_csr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_CSR;
	tmp &= mask;
	return tmp;
}

static inline hri_usart_us_csr_reg_t hri_usart_read_US_CSR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_CSR;
}

static inline bool hri_usart_get_US_RHR_RXSYNH_bit(const void *const hw)
{
	return (((Usart *)hw)->US_RHR & US_RHR_RXSYNH) > 0;
}

static inline hri_usart_us_rhr_reg_t hri_usart_get_US_RHR_RXCHR_bf(const void *const hw, hri_usart_us_rhr_reg_t mask)
{
	return (((Usart *)hw)->US_RHR & US_RHR_RXCHR(mask)) >> US_RHR_RXCHR_Pos;
}

static inline hri_usart_us_rhr_reg_t hri_usart_read_US_RHR_RXCHR_bf(const void *const hw)
{
	return (((Usart *)hw)->US_RHR & US_RHR_RXCHR_Msk) >> US_RHR_RXCHR_Pos;
}

static inline hri_usart_us_rhr_reg_t hri_usart_get_US_RHR_reg(const void *const hw, hri_usart_us_rhr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_RHR;
	tmp &= mask;
	return tmp;
}

static inline hri_usart_us_rhr_reg_t hri_usart_read_US_RHR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_RHR;
}

static inline hri_usart_us_ner_reg_t hri_usart_get_US_NER_NB_ERRORS_bf(const void *const      hw,
                                                                       hri_usart_us_ner_reg_t mask)
{
	return (((Usart *)hw)->US_NER & US_NER_NB_ERRORS(mask)) >> US_NER_NB_ERRORS_Pos;
}

static inline hri_usart_us_ner_reg_t hri_usart_read_US_NER_NB_ERRORS_bf(const void *const hw)
{
	return (((Usart *)hw)->US_NER & US_NER_NB_ERRORS_Msk) >> US_NER_NB_ERRORS_Pos;
}

static inline hri_usart_us_ner_reg_t hri_usart_get_US_NER_reg(const void *const hw, hri_usart_us_ner_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_NER;
	tmp &= mask;
	return tmp;
}

static inline hri_usart_us_ner_reg_t hri_usart_read_US_NER_reg(const void *const hw)
{
	return ((Usart *)hw)->US_NER;
}

static inline hri_usart_us_linbrr_reg_t hri_usart_get_US_LINBRR_LINCD_bf(const void *const         hw,
                                                                         hri_usart_us_linbrr_reg_t mask)
{
	return (((Usart *)hw)->US_LINBRR & US_LINBRR_LINCD(mask)) >> US_LINBRR_LINCD_Pos;
}

static inline hri_usart_us_linbrr_reg_t hri_usart_read_US_LINBRR_LINCD_bf(const void *const hw)
{
	return (((Usart *)hw)->US_LINBRR & US_LINBRR_LINCD_Msk) >> US_LINBRR_LINCD_Pos;
}

static inline hri_usart_us_linbrr_reg_t hri_usart_get_US_LINBRR_LINFP_bf(const void *const         hw,
                                                                         hri_usart_us_linbrr_reg_t mask)
{
	return (((Usart *)hw)->US_LINBRR & US_LINBRR_LINFP(mask)) >> US_LINBRR_LINFP_Pos;
}

static inline hri_usart_us_linbrr_reg_t hri_usart_read_US_LINBRR_LINFP_bf(const void *const hw)
{
	return (((Usart *)hw)->US_LINBRR & US_LINBRR_LINFP_Msk) >> US_LINBRR_LINFP_Pos;
}

static inline hri_usart_us_linbrr_reg_t hri_usart_get_US_LINBRR_reg(const void *const         hw,
                                                                    hri_usart_us_linbrr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINBRR;
	tmp &= mask;
	return tmp;
}

static inline hri_usart_us_linbrr_reg_t hri_usart_read_US_LINBRR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LINBRR;
}

static inline hri_usart_us_lonbl_reg_t hri_usart_get_US_LONBL_LONBL_bf(const void *const        hw,
                                                                       hri_usart_us_lonbl_reg_t mask)
{
	return (((Usart *)hw)->US_LONBL & US_LONBL_LONBL(mask)) >> US_LONBL_LONBL_Pos;
}

static inline hri_usart_us_lonbl_reg_t hri_usart_read_US_LONBL_LONBL_bf(const void *const hw)
{
	return (((Usart *)hw)->US_LONBL & US_LONBL_LONBL_Msk) >> US_LONBL_LONBL_Pos;
}

static inline hri_usart_us_lonbl_reg_t hri_usart_get_US_LONBL_reg(const void *const hw, hri_usart_us_lonbl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONBL;
	tmp &= mask;
	return tmp;
}

static inline hri_usart_us_lonbl_reg_t hri_usart_read_US_LONBL_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LONBL;
}

static inline bool hri_usart_get_US_WPSR_WPVS_bit(const void *const hw)
{
	return (((Usart *)hw)->US_WPSR & US_WPSR_WPVS) > 0;
}

static inline hri_usart_us_wpsr_reg_t hri_usart_get_US_WPSR_WPVSRC_bf(const void *const       hw,
                                                                      hri_usart_us_wpsr_reg_t mask)
{
	return (((Usart *)hw)->US_WPSR & US_WPSR_WPVSRC(mask)) >> US_WPSR_WPVSRC_Pos;
}

static inline hri_usart_us_wpsr_reg_t hri_usart_read_US_WPSR_WPVSRC_bf(const void *const hw)
{
	return (((Usart *)hw)->US_WPSR & US_WPSR_WPVSRC_Msk) >> US_WPSR_WPVSRC_Pos;
}

static inline hri_usart_us_wpsr_reg_t hri_usart_get_US_WPSR_reg(const void *const hw, hri_usart_us_wpsr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_WPSR;
	tmp &= mask;
	return tmp;
}

static inline hri_usart_us_wpsr_reg_t hri_usart_read_US_WPSR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_WPSR;
}

static inline void hri_usart_set_US_MR_USART_SYNC_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_SYNC;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_SYNC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_SYNC) >> US_MR_USART_SYNC_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_SYNC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_SYNC;
	tmp |= value << US_MR_USART_SYNC_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_SYNC_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_SYNC;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_SYNC_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_SYNC;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_MSBF_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_MSBF;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_MSBF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_MSBF) >> US_MR_USART_MSBF_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_MSBF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_MSBF;
	tmp |= value << US_MR_USART_MSBF_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_MSBF_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_MSBF;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_MSBF_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_MSBF;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_MODE9_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_MODE9;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_MODE9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_MODE9) >> US_MR_USART_MODE9_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_MODE9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_MODE9;
	tmp |= value << US_MR_USART_MODE9_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_MODE9_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_MODE9;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_MODE9_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_MODE9;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_CLKO_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_CLKO;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_CLKO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_CLKO) >> US_MR_CLKO_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_CLKO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_CLKO;
	tmp |= value << US_MR_CLKO_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_CLKO_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_CLKO;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_CLKO_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_CLKO;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_OVER_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_OVER;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_OVER_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_OVER) >> US_MR_USART_OVER_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_OVER_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_OVER;
	tmp |= value << US_MR_USART_OVER_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_OVER_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_OVER;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_OVER_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_OVER;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_INACK_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_INACK;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_INACK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_INACK) >> US_MR_USART_INACK_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_INACK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_INACK;
	tmp |= value << US_MR_USART_INACK_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_INACK_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_INACK;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_INACK_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_INACK;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_DSNACK_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_DSNACK;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_DSNACK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_DSNACK) >> US_MR_USART_DSNACK_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_DSNACK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_DSNACK;
	tmp |= value << US_MR_USART_DSNACK_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_DSNACK_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_DSNACK;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_DSNACK_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_DSNACK;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_VAR_SYNC_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_VAR_SYNC;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_VAR_SYNC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_VAR_SYNC) >> US_MR_USART_VAR_SYNC_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_VAR_SYNC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_VAR_SYNC;
	tmp |= value << US_MR_USART_VAR_SYNC_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_VAR_SYNC_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_VAR_SYNC;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_VAR_SYNC_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_VAR_SYNC;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_INVDATA_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_INVDATA;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_INVDATA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_INVDATA) >> US_MR_USART_INVDATA_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_INVDATA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_INVDATA;
	tmp |= value << US_MR_USART_INVDATA_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_INVDATA_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_INVDATA;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_INVDATA_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_INVDATA;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_FILTER_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_FILTER;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_FILTER_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_FILTER) >> US_MR_USART_FILTER_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_FILTER_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_FILTER;
	tmp |= value << US_MR_USART_FILTER_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_FILTER_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_FILTER;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_FILTER_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_FILTER;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_MAN_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_MAN;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_MAN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_MAN) >> US_MR_USART_MAN_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_MAN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_MAN;
	tmp |= value << US_MR_USART_MAN_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_MAN_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_MAN;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_MAN_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_MAN;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_MODSYNC_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_MODSYNC;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_MODSYNC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_MODSYNC) >> US_MR_USART_MODSYNC_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_MODSYNC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_MODSYNC;
	tmp |= value << US_MR_USART_MODSYNC_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_MODSYNC_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_MODSYNC;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_MODSYNC_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_MODSYNC;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_ONEBIT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_ONEBIT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_USART_ONEBIT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_ONEBIT) >> US_MR_USART_ONEBIT_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_USART_ONEBIT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_ONEBIT;
	tmp |= value << US_MR_USART_ONEBIT_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_ONEBIT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_ONEBIT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_ONEBIT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_ONEBIT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_SPI_CPHA_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_SPI_CPHA;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_SPI_CPHA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_SPI_CPHA) >> US_MR_SPI_CPHA_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_SPI_CPHA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_SPI_CPHA;
	tmp |= value << US_MR_SPI_CPHA_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_SPI_CPHA_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_SPI_CPHA;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_SPI_CPHA_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_SPI_CPHA;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_SPI_CPOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_SPI_CPOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_SPI_CPOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_SPI_CPOL) >> US_MR_SPI_CPOL_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_SPI_CPOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_SPI_CPOL;
	tmp |= value << US_MR_SPI_CPOL_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_SPI_CPOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_SPI_CPOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_SPI_CPOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_SPI_CPOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_SPI_WRDBT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_SPI_WRDBT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MR_SPI_WRDBT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_SPI_WRDBT) >> US_MR_SPI_WRDBT_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MR_SPI_WRDBT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_SPI_WRDBT;
	tmp |= value << US_MR_SPI_WRDBT_Pos;
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_SPI_WRDBT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_SPI_WRDBT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_SPI_WRDBT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_SPI_WRDBT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MR_USART_MODE_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_MODE(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_get_US_MR_USART_MODE_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_MODE(mask)) >> US_MR_USART_MODE_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MR_USART_MODE_bf(const void *const hw, hri_usart_us_mr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_MODE_Msk;
	tmp |= US_MR_USART_MODE(data);
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_MODE_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_MODE(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_MODE_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_MODE(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_read_US_MR_USART_MODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_MODE_Msk) >> US_MR_USART_MODE_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MR_USCLKS_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USCLKS(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_get_US_MR_USCLKS_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USCLKS(mask)) >> US_MR_USCLKS_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MR_USCLKS_bf(const void *const hw, hri_usart_us_mr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USCLKS_Msk;
	tmp |= US_MR_USCLKS(data);
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USCLKS_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USCLKS(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USCLKS_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USCLKS(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_read_US_MR_USCLKS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USCLKS_Msk) >> US_MR_USCLKS_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MR_CHRL_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_CHRL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_get_US_MR_CHRL_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_CHRL(mask)) >> US_MR_CHRL_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MR_CHRL_bf(const void *const hw, hri_usart_us_mr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_CHRL_Msk;
	tmp |= US_MR_CHRL(data);
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_CHRL_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_CHRL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_CHRL_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_CHRL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_read_US_MR_CHRL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_CHRL_Msk) >> US_MR_CHRL_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MR_USART_PAR_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_PAR(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_get_US_MR_USART_PAR_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_PAR(mask)) >> US_MR_USART_PAR_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MR_USART_PAR_bf(const void *const hw, hri_usart_us_mr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_PAR_Msk;
	tmp |= US_MR_USART_PAR(data);
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_PAR_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_PAR(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_PAR_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_PAR(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_read_US_MR_USART_PAR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_PAR_Msk) >> US_MR_USART_PAR_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MR_USART_NBSTOP_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_NBSTOP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_get_US_MR_USART_NBSTOP_bf(const void *const     hw,
                                                                        hri_usart_us_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_NBSTOP(mask)) >> US_MR_USART_NBSTOP_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MR_USART_NBSTOP_bf(const void *const hw, hri_usart_us_mr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_NBSTOP_Msk;
	tmp |= US_MR_USART_NBSTOP(data);
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_NBSTOP_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_NBSTOP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_NBSTOP_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_NBSTOP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_read_US_MR_USART_NBSTOP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_NBSTOP_Msk) >> US_MR_USART_NBSTOP_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MR_USART_CHMODE_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_CHMODE(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_get_US_MR_USART_CHMODE_bf(const void *const     hw,
                                                                        hri_usart_us_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_CHMODE(mask)) >> US_MR_USART_CHMODE_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MR_USART_CHMODE_bf(const void *const hw, hri_usart_us_mr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_CHMODE_Msk;
	tmp |= US_MR_USART_CHMODE(data);
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_CHMODE_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_CHMODE(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_CHMODE_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_CHMODE(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_read_US_MR_USART_CHMODE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_CHMODE_Msk) >> US_MR_USART_CHMODE_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MR_USART_MAX_ITERATION_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= US_MR_USART_MAX_ITERATION(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_get_US_MR_USART_MAX_ITERATION_bf(const void *const     hw,
                                                                               hri_usart_us_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_MAX_ITERATION(mask)) >> US_MR_USART_MAX_ITERATION_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MR_USART_MAX_ITERATION_bf(const void *const hw, hri_usart_us_mr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MR;
	tmp &= ~US_MR_USART_MAX_ITERATION_Msk;
	tmp |= US_MR_USART_MAX_ITERATION(data);
	((Usart *)hw)->US_MR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_USART_MAX_ITERATION_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~US_MR_USART_MAX_ITERATION(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_USART_MAX_ITERATION_bf(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= US_MR_USART_MAX_ITERATION(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_read_US_MR_USART_MAX_ITERATION_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp = (tmp & US_MR_USART_MAX_ITERATION_Msk) >> US_MR_USART_MAX_ITERATION_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MR_reg(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_get_US_MR_reg(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_MR_reg(const void *const hw, hri_usart_us_mr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MR_reg(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MR_reg(const void *const hw, hri_usart_us_mr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_mr_reg_t hri_usart_read_US_MR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_MR;
}

static inline void hri_usart_set_US_BRGR_CD_bf(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR |= US_BRGR_CD(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_brgr_reg_t hri_usart_get_US_BRGR_CD_bf(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_BRGR;
	tmp = (tmp & US_BRGR_CD(mask)) >> US_BRGR_CD_Pos;
	return tmp;
}

static inline void hri_usart_write_US_BRGR_CD_bf(const void *const hw, hri_usart_us_brgr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_BRGR;
	tmp &= ~US_BRGR_CD_Msk;
	tmp |= US_BRGR_CD(data);
	((Usart *)hw)->US_BRGR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_BRGR_CD_bf(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR &= ~US_BRGR_CD(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_BRGR_CD_bf(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR ^= US_BRGR_CD(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_brgr_reg_t hri_usart_read_US_BRGR_CD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_BRGR;
	tmp = (tmp & US_BRGR_CD_Msk) >> US_BRGR_CD_Pos;
	return tmp;
}

static inline void hri_usart_set_US_BRGR_FP_bf(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR |= US_BRGR_FP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_brgr_reg_t hri_usart_get_US_BRGR_FP_bf(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_BRGR;
	tmp = (tmp & US_BRGR_FP(mask)) >> US_BRGR_FP_Pos;
	return tmp;
}

static inline void hri_usart_write_US_BRGR_FP_bf(const void *const hw, hri_usart_us_brgr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_BRGR;
	tmp &= ~US_BRGR_FP_Msk;
	tmp |= US_BRGR_FP(data);
	((Usart *)hw)->US_BRGR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_BRGR_FP_bf(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR &= ~US_BRGR_FP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_BRGR_FP_bf(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR ^= US_BRGR_FP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_brgr_reg_t hri_usart_read_US_BRGR_FP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_BRGR;
	tmp = (tmp & US_BRGR_FP_Msk) >> US_BRGR_FP_Pos;
	return tmp;
}

static inline void hri_usart_set_US_BRGR_reg(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_brgr_reg_t hri_usart_get_US_BRGR_reg(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_BRGR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_BRGR_reg(const void *const hw, hri_usart_us_brgr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_BRGR_reg(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_BRGR_reg(const void *const hw, hri_usart_us_brgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_BRGR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_brgr_reg_t hri_usart_read_US_BRGR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_BRGR;
}

static inline void hri_usart_set_US_RTOR_TO_bf(const void *const hw, hri_usart_us_rtor_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_RTOR |= US_RTOR_TO(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_rtor_reg_t hri_usart_get_US_RTOR_TO_bf(const void *const hw, hri_usart_us_rtor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_RTOR;
	tmp = (tmp & US_RTOR_TO(mask)) >> US_RTOR_TO_Pos;
	return tmp;
}

static inline void hri_usart_write_US_RTOR_TO_bf(const void *const hw, hri_usart_us_rtor_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_RTOR;
	tmp &= ~US_RTOR_TO_Msk;
	tmp |= US_RTOR_TO(data);
	((Usart *)hw)->US_RTOR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_RTOR_TO_bf(const void *const hw, hri_usart_us_rtor_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_RTOR &= ~US_RTOR_TO(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_RTOR_TO_bf(const void *const hw, hri_usart_us_rtor_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_RTOR ^= US_RTOR_TO(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_rtor_reg_t hri_usart_read_US_RTOR_TO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_RTOR;
	tmp = (tmp & US_RTOR_TO_Msk) >> US_RTOR_TO_Pos;
	return tmp;
}

static inline void hri_usart_set_US_RTOR_reg(const void *const hw, hri_usart_us_rtor_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_RTOR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_rtor_reg_t hri_usart_get_US_RTOR_reg(const void *const hw, hri_usart_us_rtor_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_RTOR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_RTOR_reg(const void *const hw, hri_usart_us_rtor_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_RTOR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_RTOR_reg(const void *const hw, hri_usart_us_rtor_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_RTOR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_RTOR_reg(const void *const hw, hri_usart_us_rtor_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_RTOR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_rtor_reg_t hri_usart_read_US_RTOR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_RTOR;
}

static inline void hri_usart_set_US_TTGR_USART_TG_bf(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR |= US_TTGR_USART_TG(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_ttgr_reg_t hri_usart_get_US_TTGR_USART_TG_bf(const void *const       hw,
                                                                        hri_usart_us_ttgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_TTGR;
	tmp = (tmp & US_TTGR_USART_TG(mask)) >> US_TTGR_USART_TG_Pos;
	return tmp;
}

static inline void hri_usart_write_US_TTGR_USART_TG_bf(const void *const hw, hri_usart_us_ttgr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_TTGR;
	tmp &= ~US_TTGR_USART_TG_Msk;
	tmp |= US_TTGR_USART_TG(data);
	((Usart *)hw)->US_TTGR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_TTGR_USART_TG_bf(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR &= ~US_TTGR_USART_TG(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_TTGR_USART_TG_bf(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR ^= US_TTGR_USART_TG(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_ttgr_reg_t hri_usart_read_US_TTGR_USART_TG_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_TTGR;
	tmp = (tmp & US_TTGR_USART_TG_Msk) >> US_TTGR_USART_TG_Pos;
	return tmp;
}

static inline void hri_usart_set_US_TTGR_LON_PCYCLE_bf(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR |= US_TTGR_LON_PCYCLE(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_ttgr_reg_t hri_usart_get_US_TTGR_LON_PCYCLE_bf(const void *const       hw,
                                                                          hri_usart_us_ttgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_TTGR;
	tmp = (tmp & US_TTGR_LON_PCYCLE(mask)) >> US_TTGR_LON_PCYCLE_Pos;
	return tmp;
}

static inline void hri_usart_write_US_TTGR_LON_PCYCLE_bf(const void *const hw, hri_usart_us_ttgr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_TTGR;
	tmp &= ~US_TTGR_LON_PCYCLE_Msk;
	tmp |= US_TTGR_LON_PCYCLE(data);
	((Usart *)hw)->US_TTGR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_TTGR_LON_PCYCLE_bf(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR &= ~US_TTGR_LON_PCYCLE(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_TTGR_LON_PCYCLE_bf(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR ^= US_TTGR_LON_PCYCLE(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_ttgr_reg_t hri_usart_read_US_TTGR_LON_PCYCLE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_TTGR;
	tmp = (tmp & US_TTGR_LON_PCYCLE_Msk) >> US_TTGR_LON_PCYCLE_Pos;
	return tmp;
}

static inline void hri_usart_set_US_TTGR_reg(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_ttgr_reg_t hri_usart_get_US_TTGR_reg(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_TTGR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_TTGR_reg(const void *const hw, hri_usart_us_ttgr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_TTGR_reg(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_TTGR_reg(const void *const hw, hri_usart_us_ttgr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_TTGR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_ttgr_reg_t hri_usart_read_US_TTGR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_TTGR;
}

static inline void hri_usart_set_US_FIDI_USART_FI_DI_RATIO_bf(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI |= US_FIDI_USART_FI_DI_RATIO(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_fidi_reg_t hri_usart_get_US_FIDI_USART_FI_DI_RATIO_bf(const void *const       hw,
                                                                                 hri_usart_us_fidi_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_FIDI;
	tmp = (tmp & US_FIDI_USART_FI_DI_RATIO(mask)) >> US_FIDI_USART_FI_DI_RATIO_Pos;
	return tmp;
}

static inline void hri_usart_write_US_FIDI_USART_FI_DI_RATIO_bf(const void *const hw, hri_usart_us_fidi_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_FIDI;
	tmp &= ~US_FIDI_USART_FI_DI_RATIO_Msk;
	tmp |= US_FIDI_USART_FI_DI_RATIO(data);
	((Usart *)hw)->US_FIDI = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_FIDI_USART_FI_DI_RATIO_bf(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI &= ~US_FIDI_USART_FI_DI_RATIO(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_FIDI_USART_FI_DI_RATIO_bf(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI ^= US_FIDI_USART_FI_DI_RATIO(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_fidi_reg_t hri_usart_read_US_FIDI_USART_FI_DI_RATIO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_FIDI;
	tmp = (tmp & US_FIDI_USART_FI_DI_RATIO_Msk) >> US_FIDI_USART_FI_DI_RATIO_Pos;
	return tmp;
}

static inline void hri_usart_set_US_FIDI_LON_BETA2_bf(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI |= US_FIDI_LON_BETA2(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_fidi_reg_t hri_usart_get_US_FIDI_LON_BETA2_bf(const void *const       hw,
                                                                         hri_usart_us_fidi_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_FIDI;
	tmp = (tmp & US_FIDI_LON_BETA2(mask)) >> US_FIDI_LON_BETA2_Pos;
	return tmp;
}

static inline void hri_usart_write_US_FIDI_LON_BETA2_bf(const void *const hw, hri_usart_us_fidi_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_FIDI;
	tmp &= ~US_FIDI_LON_BETA2_Msk;
	tmp |= US_FIDI_LON_BETA2(data);
	((Usart *)hw)->US_FIDI = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_FIDI_LON_BETA2_bf(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI &= ~US_FIDI_LON_BETA2(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_FIDI_LON_BETA2_bf(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI ^= US_FIDI_LON_BETA2(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_fidi_reg_t hri_usart_read_US_FIDI_LON_BETA2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_FIDI;
	tmp = (tmp & US_FIDI_LON_BETA2_Msk) >> US_FIDI_LON_BETA2_Pos;
	return tmp;
}

static inline void hri_usart_set_US_FIDI_reg(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_fidi_reg_t hri_usart_get_US_FIDI_reg(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_FIDI;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_FIDI_reg(const void *const hw, hri_usart_us_fidi_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_FIDI_reg(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_FIDI_reg(const void *const hw, hri_usart_us_fidi_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_FIDI ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_fidi_reg_t hri_usart_read_US_FIDI_reg(const void *const hw)
{
	return ((Usart *)hw)->US_FIDI;
}

static inline void hri_usart_set_US_IF_IRDA_FILTER_bf(const void *const hw, hri_usart_us_if_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IF |= US_IF_IRDA_FILTER(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_if_reg_t hri_usart_get_US_IF_IRDA_FILTER_bf(const void *const hw, hri_usart_us_if_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IF;
	tmp = (tmp & US_IF_IRDA_FILTER(mask)) >> US_IF_IRDA_FILTER_Pos;
	return tmp;
}

static inline void hri_usart_write_US_IF_IRDA_FILTER_bf(const void *const hw, hri_usart_us_if_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_IF;
	tmp &= ~US_IF_IRDA_FILTER_Msk;
	tmp |= US_IF_IRDA_FILTER(data);
	((Usart *)hw)->US_IF = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_IF_IRDA_FILTER_bf(const void *const hw, hri_usart_us_if_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IF &= ~US_IF_IRDA_FILTER(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_IF_IRDA_FILTER_bf(const void *const hw, hri_usart_us_if_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IF ^= US_IF_IRDA_FILTER(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_if_reg_t hri_usart_read_US_IF_IRDA_FILTER_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IF;
	tmp = (tmp & US_IF_IRDA_FILTER_Msk) >> US_IF_IRDA_FILTER_Pos;
	return tmp;
}

static inline void hri_usart_set_US_IF_reg(const void *const hw, hri_usart_us_if_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IF |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_if_reg_t hri_usart_get_US_IF_reg(const void *const hw, hri_usart_us_if_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IF;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_IF_reg(const void *const hw, hri_usart_us_if_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IF = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_IF_reg(const void *const hw, hri_usart_us_if_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IF &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_IF_reg(const void *const hw, hri_usart_us_if_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IF ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_if_reg_t hri_usart_read_US_IF_reg(const void *const hw)
{
	return ((Usart *)hw)->US_IF;
}

static inline void hri_usart_set_US_MAN_TX_MPOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= US_MAN_TX_MPOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MAN_TX_MPOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_TX_MPOL) >> US_MAN_TX_MPOL_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MAN_TX_MPOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= ~US_MAN_TX_MPOL;
	tmp |= value << US_MAN_TX_MPOL_Pos;
	((Usart *)hw)->US_MAN = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_TX_MPOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~US_MAN_TX_MPOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_TX_MPOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= US_MAN_TX_MPOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MAN_RX_MPOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= US_MAN_RX_MPOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MAN_RX_MPOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_RX_MPOL) >> US_MAN_RX_MPOL_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MAN_RX_MPOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= ~US_MAN_RX_MPOL;
	tmp |= value << US_MAN_RX_MPOL_Pos;
	((Usart *)hw)->US_MAN = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_RX_MPOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~US_MAN_RX_MPOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_RX_MPOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= US_MAN_RX_MPOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MAN_ONE_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= US_MAN_ONE;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MAN_ONE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_ONE) >> US_MAN_ONE_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MAN_ONE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= ~US_MAN_ONE;
	tmp |= value << US_MAN_ONE_Pos;
	((Usart *)hw)->US_MAN = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_ONE_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~US_MAN_ONE;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_ONE_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= US_MAN_ONE;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MAN_DRIFT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= US_MAN_DRIFT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MAN_DRIFT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_DRIFT) >> US_MAN_DRIFT_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MAN_DRIFT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= ~US_MAN_DRIFT;
	tmp |= value << US_MAN_DRIFT_Pos;
	((Usart *)hw)->US_MAN = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_DRIFT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~US_MAN_DRIFT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_DRIFT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= US_MAN_DRIFT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MAN_RXIDLEV_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= US_MAN_RXIDLEV;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_MAN_RXIDLEV_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_RXIDLEV) >> US_MAN_RXIDLEV_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_MAN_RXIDLEV_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= ~US_MAN_RXIDLEV;
	tmp |= value << US_MAN_RXIDLEV_Pos;
	((Usart *)hw)->US_MAN = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_RXIDLEV_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~US_MAN_RXIDLEV;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_RXIDLEV_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= US_MAN_RXIDLEV;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_MAN_TX_PL_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= US_MAN_TX_PL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_get_US_MAN_TX_PL_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_TX_PL(mask)) >> US_MAN_TX_PL_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MAN_TX_PL_bf(const void *const hw, hri_usart_us_man_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= ~US_MAN_TX_PL_Msk;
	tmp |= US_MAN_TX_PL(data);
	((Usart *)hw)->US_MAN = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_TX_PL_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~US_MAN_TX_PL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_TX_PL_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= US_MAN_TX_PL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_read_US_MAN_TX_PL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_TX_PL_Msk) >> US_MAN_TX_PL_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MAN_TX_PP_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= US_MAN_TX_PP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_get_US_MAN_TX_PP_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_TX_PP(mask)) >> US_MAN_TX_PP_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MAN_TX_PP_bf(const void *const hw, hri_usart_us_man_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= ~US_MAN_TX_PP_Msk;
	tmp |= US_MAN_TX_PP(data);
	((Usart *)hw)->US_MAN = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_TX_PP_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~US_MAN_TX_PP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_TX_PP_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= US_MAN_TX_PP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_read_US_MAN_TX_PP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_TX_PP_Msk) >> US_MAN_TX_PP_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MAN_RX_PL_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= US_MAN_RX_PL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_get_US_MAN_RX_PL_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_RX_PL(mask)) >> US_MAN_RX_PL_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MAN_RX_PL_bf(const void *const hw, hri_usart_us_man_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= ~US_MAN_RX_PL_Msk;
	tmp |= US_MAN_RX_PL(data);
	((Usart *)hw)->US_MAN = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_RX_PL_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~US_MAN_RX_PL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_RX_PL_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= US_MAN_RX_PL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_read_US_MAN_RX_PL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_RX_PL_Msk) >> US_MAN_RX_PL_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MAN_RX_PP_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= US_MAN_RX_PP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_get_US_MAN_RX_PP_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_RX_PP(mask)) >> US_MAN_RX_PP_Pos;
	return tmp;
}

static inline void hri_usart_write_US_MAN_RX_PP_bf(const void *const hw, hri_usart_us_man_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= ~US_MAN_RX_PP_Msk;
	tmp |= US_MAN_RX_PP(data);
	((Usart *)hw)->US_MAN = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_RX_PP_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~US_MAN_RX_PP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_RX_PP_bf(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= US_MAN_RX_PP(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_read_US_MAN_RX_PP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp = (tmp & US_MAN_RX_PP_Msk) >> US_MAN_RX_PP_Pos;
	return tmp;
}

static inline void hri_usart_set_US_MAN_reg(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_get_US_MAN_reg(const void *const hw, hri_usart_us_man_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_MAN;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_MAN_reg(const void *const hw, hri_usart_us_man_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_MAN_reg(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_MAN_reg(const void *const hw, hri_usart_us_man_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_MAN ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_man_reg_t hri_usart_read_US_MAN_reg(const void *const hw)
{
	return ((Usart *)hw)->US_MAN;
}

static inline void hri_usart_set_US_LINMR_PARDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_PARDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LINMR_PARDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_PARDIS) >> US_LINMR_PARDIS_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LINMR_PARDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_PARDIS;
	tmp |= value << US_LINMR_PARDIS_Pos;
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_PARDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_PARDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_PARDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_PARDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LINMR_CHKDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_CHKDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LINMR_CHKDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_CHKDIS) >> US_LINMR_CHKDIS_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LINMR_CHKDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_CHKDIS;
	tmp |= value << US_LINMR_CHKDIS_Pos;
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_CHKDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_CHKDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_CHKDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_CHKDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LINMR_CHKTYP_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_CHKTYP;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LINMR_CHKTYP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_CHKTYP) >> US_LINMR_CHKTYP_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LINMR_CHKTYP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_CHKTYP;
	tmp |= value << US_LINMR_CHKTYP_Pos;
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_CHKTYP_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_CHKTYP;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_CHKTYP_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_CHKTYP;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LINMR_DLM_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_DLM;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LINMR_DLM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_DLM) >> US_LINMR_DLM_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LINMR_DLM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_DLM;
	tmp |= value << US_LINMR_DLM_Pos;
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_DLM_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_DLM;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_DLM_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_DLM;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LINMR_FSDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_FSDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LINMR_FSDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_FSDIS) >> US_LINMR_FSDIS_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LINMR_FSDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_FSDIS;
	tmp |= value << US_LINMR_FSDIS_Pos;
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_FSDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_FSDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_FSDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_FSDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LINMR_WKUPTYP_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_WKUPTYP;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LINMR_WKUPTYP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_WKUPTYP) >> US_LINMR_WKUPTYP_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LINMR_WKUPTYP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_WKUPTYP;
	tmp |= value << US_LINMR_WKUPTYP_Pos;
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_WKUPTYP_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_WKUPTYP;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_WKUPTYP_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_WKUPTYP;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LINMR_PDCM_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_PDCM;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LINMR_PDCM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_PDCM) >> US_LINMR_PDCM_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LINMR_PDCM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_PDCM;
	tmp |= value << US_LINMR_PDCM_Pos;
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_PDCM_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_PDCM;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_PDCM_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_PDCM;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LINMR_SYNCDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_SYNCDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LINMR_SYNCDIS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_SYNCDIS) >> US_LINMR_SYNCDIS_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LINMR_SYNCDIS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_SYNCDIS;
	tmp |= value << US_LINMR_SYNCDIS_Pos;
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_SYNCDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_SYNCDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_SYNCDIS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_SYNCDIS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LINMR_NACT_bf(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_NACT(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linmr_reg_t hri_usart_get_US_LINMR_NACT_bf(const void *const        hw,
                                                                      hri_usart_us_linmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_NACT(mask)) >> US_LINMR_NACT_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LINMR_NACT_bf(const void *const hw, hri_usart_us_linmr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_NACT_Msk;
	tmp |= US_LINMR_NACT(data);
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_NACT_bf(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_NACT(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_NACT_bf(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_NACT(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linmr_reg_t hri_usart_read_US_LINMR_NACT_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_NACT_Msk) >> US_LINMR_NACT_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LINMR_DLC_bf(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= US_LINMR_DLC(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linmr_reg_t hri_usart_get_US_LINMR_DLC_bf(const void *const        hw,
                                                                     hri_usart_us_linmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_DLC(mask)) >> US_LINMR_DLC_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LINMR_DLC_bf(const void *const hw, hri_usart_us_linmr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= ~US_LINMR_DLC_Msk;
	tmp |= US_LINMR_DLC(data);
	((Usart *)hw)->US_LINMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_DLC_bf(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~US_LINMR_DLC(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_DLC_bf(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= US_LINMR_DLC(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linmr_reg_t hri_usart_read_US_LINMR_DLC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp = (tmp & US_LINMR_DLC_Msk) >> US_LINMR_DLC_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LINMR_reg(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linmr_reg_t hri_usart_get_US_LINMR_reg(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_LINMR_reg(const void *const hw, hri_usart_us_linmr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINMR_reg(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINMR_reg(const void *const hw, hri_usart_us_linmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINMR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linmr_reg_t hri_usart_read_US_LINMR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LINMR;
}

static inline void hri_usart_set_US_LINIR_IDCHR_bf(const void *const hw, hri_usart_us_linir_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINIR |= US_LINIR_IDCHR(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linir_reg_t hri_usart_get_US_LINIR_IDCHR_bf(const void *const        hw,
                                                                       hri_usart_us_linir_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINIR;
	tmp = (tmp & US_LINIR_IDCHR(mask)) >> US_LINIR_IDCHR_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LINIR_IDCHR_bf(const void *const hw, hri_usart_us_linir_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LINIR;
	tmp &= ~US_LINIR_IDCHR_Msk;
	tmp |= US_LINIR_IDCHR(data);
	((Usart *)hw)->US_LINIR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINIR_IDCHR_bf(const void *const hw, hri_usart_us_linir_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINIR &= ~US_LINIR_IDCHR(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINIR_IDCHR_bf(const void *const hw, hri_usart_us_linir_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINIR ^= US_LINIR_IDCHR(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linir_reg_t hri_usart_read_US_LINIR_IDCHR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINIR;
	tmp = (tmp & US_LINIR_IDCHR_Msk) >> US_LINIR_IDCHR_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LINIR_reg(const void *const hw, hri_usart_us_linir_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINIR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linir_reg_t hri_usart_get_US_LINIR_reg(const void *const hw, hri_usart_us_linir_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LINIR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_LINIR_reg(const void *const hw, hri_usart_us_linir_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINIR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LINIR_reg(const void *const hw, hri_usart_us_linir_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINIR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LINIR_reg(const void *const hw, hri_usart_us_linir_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LINIR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_linir_reg_t hri_usart_read_US_LINIR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LINIR;
}

static inline void hri_usart_set_US_LONMR_COMMT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR |= US_LONMR_COMMT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LONMR_COMMT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONMR;
	tmp = (tmp & US_LONMR_COMMT) >> US_LONMR_COMMT_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LONMR_COMMT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONMR;
	tmp &= ~US_LONMR_COMMT;
	tmp |= value << US_LONMR_COMMT_Pos;
	((Usart *)hw)->US_LONMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONMR_COMMT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR &= ~US_LONMR_COMMT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONMR_COMMT_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR ^= US_LONMR_COMMT;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LONMR_COLDET_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR |= US_LONMR_COLDET;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LONMR_COLDET_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONMR;
	tmp = (tmp & US_LONMR_COLDET) >> US_LONMR_COLDET_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LONMR_COLDET_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONMR;
	tmp &= ~US_LONMR_COLDET;
	tmp |= value << US_LONMR_COLDET_Pos;
	((Usart *)hw)->US_LONMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONMR_COLDET_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR &= ~US_LONMR_COLDET;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONMR_COLDET_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR ^= US_LONMR_COLDET;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LONMR_TCOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR |= US_LONMR_TCOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LONMR_TCOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONMR;
	tmp = (tmp & US_LONMR_TCOL) >> US_LONMR_TCOL_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LONMR_TCOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONMR;
	tmp &= ~US_LONMR_TCOL;
	tmp |= value << US_LONMR_TCOL_Pos;
	((Usart *)hw)->US_LONMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONMR_TCOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR &= ~US_LONMR_TCOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONMR_TCOL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR ^= US_LONMR_TCOL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LONMR_CDTAIL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR |= US_LONMR_CDTAIL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LONMR_CDTAIL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONMR;
	tmp = (tmp & US_LONMR_CDTAIL) >> US_LONMR_CDTAIL_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LONMR_CDTAIL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONMR;
	tmp &= ~US_LONMR_CDTAIL;
	tmp |= value << US_LONMR_CDTAIL_Pos;
	((Usart *)hw)->US_LONMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONMR_CDTAIL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR &= ~US_LONMR_CDTAIL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONMR_CDTAIL_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR ^= US_LONMR_CDTAIL;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LONMR_DMAM_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR |= US_LONMR_DMAM;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LONMR_DMAM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONMR;
	tmp = (tmp & US_LONMR_DMAM) >> US_LONMR_DMAM_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LONMR_DMAM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONMR;
	tmp &= ~US_LONMR_DMAM;
	tmp |= value << US_LONMR_DMAM_Pos;
	((Usart *)hw)->US_LONMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONMR_DMAM_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR &= ~US_LONMR_DMAM;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONMR_DMAM_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR ^= US_LONMR_DMAM;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LONMR_LCDS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR |= US_LONMR_LCDS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LONMR_LCDS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONMR;
	tmp = (tmp & US_LONMR_LCDS) >> US_LONMR_LCDS_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LONMR_LCDS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONMR;
	tmp &= ~US_LONMR_LCDS;
	tmp |= value << US_LONMR_LCDS_Pos;
	((Usart *)hw)->US_LONMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONMR_LCDS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR &= ~US_LONMR_LCDS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONMR_LCDS_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR ^= US_LONMR_LCDS;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LONMR_EOFS_bf(const void *const hw, hri_usart_us_lonmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR |= US_LONMR_EOFS(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonmr_reg_t hri_usart_get_US_LONMR_EOFS_bf(const void *const        hw,
                                                                      hri_usart_us_lonmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONMR;
	tmp = (tmp & US_LONMR_EOFS(mask)) >> US_LONMR_EOFS_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LONMR_EOFS_bf(const void *const hw, hri_usart_us_lonmr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONMR;
	tmp &= ~US_LONMR_EOFS_Msk;
	tmp |= US_LONMR_EOFS(data);
	((Usart *)hw)->US_LONMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONMR_EOFS_bf(const void *const hw, hri_usart_us_lonmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR &= ~US_LONMR_EOFS(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONMR_EOFS_bf(const void *const hw, hri_usart_us_lonmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR ^= US_LONMR_EOFS(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonmr_reg_t hri_usart_read_US_LONMR_EOFS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONMR;
	tmp = (tmp & US_LONMR_EOFS_Msk) >> US_LONMR_EOFS_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LONMR_reg(const void *const hw, hri_usart_us_lonmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonmr_reg_t hri_usart_get_US_LONMR_reg(const void *const hw, hri_usart_us_lonmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_LONMR_reg(const void *const hw, hri_usart_us_lonmr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONMR_reg(const void *const hw, hri_usart_us_lonmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONMR_reg(const void *const hw, hri_usart_us_lonmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONMR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonmr_reg_t hri_usart_read_US_LONMR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LONMR;
}

static inline void hri_usart_set_US_LONPR_LONPL_bf(const void *const hw, hri_usart_us_lonpr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPR |= US_LONPR_LONPL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonpr_reg_t hri_usart_get_US_LONPR_LONPL_bf(const void *const        hw,
                                                                       hri_usart_us_lonpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONPR;
	tmp = (tmp & US_LONPR_LONPL(mask)) >> US_LONPR_LONPL_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LONPR_LONPL_bf(const void *const hw, hri_usart_us_lonpr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONPR;
	tmp &= ~US_LONPR_LONPL_Msk;
	tmp |= US_LONPR_LONPL(data);
	((Usart *)hw)->US_LONPR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONPR_LONPL_bf(const void *const hw, hri_usart_us_lonpr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPR &= ~US_LONPR_LONPL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONPR_LONPL_bf(const void *const hw, hri_usart_us_lonpr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPR ^= US_LONPR_LONPL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonpr_reg_t hri_usart_read_US_LONPR_LONPL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONPR;
	tmp = (tmp & US_LONPR_LONPL_Msk) >> US_LONPR_LONPL_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LONPR_reg(const void *const hw, hri_usart_us_lonpr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonpr_reg_t hri_usart_get_US_LONPR_reg(const void *const hw, hri_usart_us_lonpr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONPR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_LONPR_reg(const void *const hw, hri_usart_us_lonpr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONPR_reg(const void *const hw, hri_usart_us_lonpr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONPR_reg(const void *const hw, hri_usart_us_lonpr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonpr_reg_t hri_usart_read_US_LONPR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LONPR;
}

static inline void hri_usart_set_US_LONDL_LONDL_bf(const void *const hw, hri_usart_us_londl_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONDL |= US_LONDL_LONDL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_londl_reg_t hri_usart_get_US_LONDL_LONDL_bf(const void *const        hw,
                                                                       hri_usart_us_londl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONDL;
	tmp = (tmp & US_LONDL_LONDL(mask)) >> US_LONDL_LONDL_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LONDL_LONDL_bf(const void *const hw, hri_usart_us_londl_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONDL;
	tmp &= ~US_LONDL_LONDL_Msk;
	tmp |= US_LONDL_LONDL(data);
	((Usart *)hw)->US_LONDL = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONDL_LONDL_bf(const void *const hw, hri_usart_us_londl_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONDL &= ~US_LONDL_LONDL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONDL_LONDL_bf(const void *const hw, hri_usart_us_londl_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONDL ^= US_LONDL_LONDL(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_londl_reg_t hri_usart_read_US_LONDL_LONDL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONDL;
	tmp = (tmp & US_LONDL_LONDL_Msk) >> US_LONDL_LONDL_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LONDL_reg(const void *const hw, hri_usart_us_londl_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONDL |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_londl_reg_t hri_usart_get_US_LONDL_reg(const void *const hw, hri_usart_us_londl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONDL;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_LONDL_reg(const void *const hw, hri_usart_us_londl_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONDL = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONDL_reg(const void *const hw, hri_usart_us_londl_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONDL &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONDL_reg(const void *const hw, hri_usart_us_londl_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONDL ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_londl_reg_t hri_usart_read_US_LONDL_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LONDL;
}

static inline void hri_usart_set_US_LONL2HDR_ALTP_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR |= US_LONL2HDR_ALTP;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LONL2HDR_ALTP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONL2HDR;
	tmp = (tmp & US_LONL2HDR_ALTP) >> US_LONL2HDR_ALTP_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LONL2HDR_ALTP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONL2HDR;
	tmp &= ~US_LONL2HDR_ALTP;
	tmp |= value << US_LONL2HDR_ALTP_Pos;
	((Usart *)hw)->US_LONL2HDR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONL2HDR_ALTP_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR &= ~US_LONL2HDR_ALTP;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONL2HDR_ALTP_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR ^= US_LONL2HDR_ALTP;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LONL2HDR_PB_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR |= US_LONL2HDR_PB;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_LONL2HDR_PB_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONL2HDR;
	tmp = (tmp & US_LONL2HDR_PB) >> US_LONL2HDR_PB_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_LONL2HDR_PB_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONL2HDR;
	tmp &= ~US_LONL2HDR_PB;
	tmp |= value << US_LONL2HDR_PB_Pos;
	((Usart *)hw)->US_LONL2HDR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONL2HDR_PB_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR &= ~US_LONL2HDR_PB;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONL2HDR_PB_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR ^= US_LONL2HDR_PB;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_LONL2HDR_BLI_bf(const void *const hw, hri_usart_us_lonl2hdr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR |= US_LONL2HDR_BLI(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonl2hdr_reg_t hri_usart_get_US_LONL2HDR_BLI_bf(const void *const           hw,
                                                                           hri_usart_us_lonl2hdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONL2HDR;
	tmp = (tmp & US_LONL2HDR_BLI(mask)) >> US_LONL2HDR_BLI_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LONL2HDR_BLI_bf(const void *const hw, hri_usart_us_lonl2hdr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONL2HDR;
	tmp &= ~US_LONL2HDR_BLI_Msk;
	tmp |= US_LONL2HDR_BLI(data);
	((Usart *)hw)->US_LONL2HDR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONL2HDR_BLI_bf(const void *const hw, hri_usart_us_lonl2hdr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR &= ~US_LONL2HDR_BLI(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONL2HDR_BLI_bf(const void *const hw, hri_usart_us_lonl2hdr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR ^= US_LONL2HDR_BLI(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonl2hdr_reg_t hri_usart_read_US_LONL2HDR_BLI_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONL2HDR;
	tmp = (tmp & US_LONL2HDR_BLI_Msk) >> US_LONL2HDR_BLI_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LONL2HDR_reg(const void *const hw, hri_usart_us_lonl2hdr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonl2hdr_reg_t hri_usart_get_US_LONL2HDR_reg(const void *const           hw,
                                                                        hri_usart_us_lonl2hdr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONL2HDR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_LONL2HDR_reg(const void *const hw, hri_usart_us_lonl2hdr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONL2HDR_reg(const void *const hw, hri_usart_us_lonl2hdr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONL2HDR_reg(const void *const hw, hri_usart_us_lonl2hdr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONL2HDR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonl2hdr_reg_t hri_usart_read_US_LONL2HDR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LONL2HDR;
}

static inline void hri_usart_set_US_LONB1TX_BETA1TX_bf(const void *const hw, hri_usart_us_lonb1tx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1TX |= US_LONB1TX_BETA1TX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonb1tx_reg_t hri_usart_get_US_LONB1TX_BETA1TX_bf(const void *const          hw,
                                                                             hri_usart_us_lonb1tx_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONB1TX;
	tmp = (tmp & US_LONB1TX_BETA1TX(mask)) >> US_LONB1TX_BETA1TX_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LONB1TX_BETA1TX_bf(const void *const hw, hri_usart_us_lonb1tx_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONB1TX;
	tmp &= ~US_LONB1TX_BETA1TX_Msk;
	tmp |= US_LONB1TX_BETA1TX(data);
	((Usart *)hw)->US_LONB1TX = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONB1TX_BETA1TX_bf(const void *const hw, hri_usart_us_lonb1tx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1TX &= ~US_LONB1TX_BETA1TX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONB1TX_BETA1TX_bf(const void *const hw, hri_usart_us_lonb1tx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1TX ^= US_LONB1TX_BETA1TX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonb1tx_reg_t hri_usart_read_US_LONB1TX_BETA1TX_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONB1TX;
	tmp = (tmp & US_LONB1TX_BETA1TX_Msk) >> US_LONB1TX_BETA1TX_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LONB1TX_reg(const void *const hw, hri_usart_us_lonb1tx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1TX |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonb1tx_reg_t hri_usart_get_US_LONB1TX_reg(const void *const          hw,
                                                                      hri_usart_us_lonb1tx_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONB1TX;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_LONB1TX_reg(const void *const hw, hri_usart_us_lonb1tx_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1TX = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONB1TX_reg(const void *const hw, hri_usart_us_lonb1tx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1TX &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONB1TX_reg(const void *const hw, hri_usart_us_lonb1tx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1TX ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonb1tx_reg_t hri_usart_read_US_LONB1TX_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LONB1TX;
}

static inline void hri_usart_set_US_LONB1RX_BETA1RX_bf(const void *const hw, hri_usart_us_lonb1rx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1RX |= US_LONB1RX_BETA1RX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonb1rx_reg_t hri_usart_get_US_LONB1RX_BETA1RX_bf(const void *const          hw,
                                                                             hri_usart_us_lonb1rx_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONB1RX;
	tmp = (tmp & US_LONB1RX_BETA1RX(mask)) >> US_LONB1RX_BETA1RX_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LONB1RX_BETA1RX_bf(const void *const hw, hri_usart_us_lonb1rx_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONB1RX;
	tmp &= ~US_LONB1RX_BETA1RX_Msk;
	tmp |= US_LONB1RX_BETA1RX(data);
	((Usart *)hw)->US_LONB1RX = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONB1RX_BETA1RX_bf(const void *const hw, hri_usart_us_lonb1rx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1RX &= ~US_LONB1RX_BETA1RX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONB1RX_BETA1RX_bf(const void *const hw, hri_usart_us_lonb1rx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1RX ^= US_LONB1RX_BETA1RX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonb1rx_reg_t hri_usart_read_US_LONB1RX_BETA1RX_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONB1RX;
	tmp = (tmp & US_LONB1RX_BETA1RX_Msk) >> US_LONB1RX_BETA1RX_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LONB1RX_reg(const void *const hw, hri_usart_us_lonb1rx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1RX |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonb1rx_reg_t hri_usart_get_US_LONB1RX_reg(const void *const          hw,
                                                                      hri_usart_us_lonb1rx_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONB1RX;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_LONB1RX_reg(const void *const hw, hri_usart_us_lonb1rx_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1RX = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONB1RX_reg(const void *const hw, hri_usart_us_lonb1rx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1RX &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONB1RX_reg(const void *const hw, hri_usart_us_lonb1rx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONB1RX ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonb1rx_reg_t hri_usart_read_US_LONB1RX_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LONB1RX;
}

static inline void hri_usart_set_US_LONPRIO_PSNB_bf(const void *const hw, hri_usart_us_lonprio_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO |= US_LONPRIO_PSNB(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonprio_reg_t hri_usart_get_US_LONPRIO_PSNB_bf(const void *const          hw,
                                                                          hri_usart_us_lonprio_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONPRIO;
	tmp = (tmp & US_LONPRIO_PSNB(mask)) >> US_LONPRIO_PSNB_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LONPRIO_PSNB_bf(const void *const hw, hri_usart_us_lonprio_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONPRIO;
	tmp &= ~US_LONPRIO_PSNB_Msk;
	tmp |= US_LONPRIO_PSNB(data);
	((Usart *)hw)->US_LONPRIO = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONPRIO_PSNB_bf(const void *const hw, hri_usart_us_lonprio_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO &= ~US_LONPRIO_PSNB(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONPRIO_PSNB_bf(const void *const hw, hri_usart_us_lonprio_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO ^= US_LONPRIO_PSNB(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonprio_reg_t hri_usart_read_US_LONPRIO_PSNB_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONPRIO;
	tmp = (tmp & US_LONPRIO_PSNB_Msk) >> US_LONPRIO_PSNB_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LONPRIO_NPS_bf(const void *const hw, hri_usart_us_lonprio_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO |= US_LONPRIO_NPS(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonprio_reg_t hri_usart_get_US_LONPRIO_NPS_bf(const void *const          hw,
                                                                         hri_usart_us_lonprio_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONPRIO;
	tmp = (tmp & US_LONPRIO_NPS(mask)) >> US_LONPRIO_NPS_Pos;
	return tmp;
}

static inline void hri_usart_write_US_LONPRIO_NPS_bf(const void *const hw, hri_usart_us_lonprio_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_LONPRIO;
	tmp &= ~US_LONPRIO_NPS_Msk;
	tmp |= US_LONPRIO_NPS(data);
	((Usart *)hw)->US_LONPRIO = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONPRIO_NPS_bf(const void *const hw, hri_usart_us_lonprio_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO &= ~US_LONPRIO_NPS(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONPRIO_NPS_bf(const void *const hw, hri_usart_us_lonprio_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO ^= US_LONPRIO_NPS(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonprio_reg_t hri_usart_read_US_LONPRIO_NPS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONPRIO;
	tmp = (tmp & US_LONPRIO_NPS_Msk) >> US_LONPRIO_NPS_Pos;
	return tmp;
}

static inline void hri_usart_set_US_LONPRIO_reg(const void *const hw, hri_usart_us_lonprio_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonprio_reg_t hri_usart_get_US_LONPRIO_reg(const void *const          hw,
                                                                      hri_usart_us_lonprio_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_LONPRIO;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_LONPRIO_reg(const void *const hw, hri_usart_us_lonprio_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_LONPRIO_reg(const void *const hw, hri_usart_us_lonprio_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_LONPRIO_reg(const void *const hw, hri_usart_us_lonprio_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_LONPRIO ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_lonprio_reg_t hri_usart_read_US_LONPRIO_reg(const void *const hw)
{
	return ((Usart *)hw)->US_LONPRIO;
}

static inline void hri_usart_set_US_IDTTX_IDTTX_bf(const void *const hw, hri_usart_us_idttx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTTX |= US_IDTTX_IDTTX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_idttx_reg_t hri_usart_get_US_IDTTX_IDTTX_bf(const void *const        hw,
                                                                       hri_usart_us_idttx_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IDTTX;
	tmp = (tmp & US_IDTTX_IDTTX(mask)) >> US_IDTTX_IDTTX_Pos;
	return tmp;
}

static inline void hri_usart_write_US_IDTTX_IDTTX_bf(const void *const hw, hri_usart_us_idttx_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_IDTTX;
	tmp &= ~US_IDTTX_IDTTX_Msk;
	tmp |= US_IDTTX_IDTTX(data);
	((Usart *)hw)->US_IDTTX = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_IDTTX_IDTTX_bf(const void *const hw, hri_usart_us_idttx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTTX &= ~US_IDTTX_IDTTX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_IDTTX_IDTTX_bf(const void *const hw, hri_usart_us_idttx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTTX ^= US_IDTTX_IDTTX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_idttx_reg_t hri_usart_read_US_IDTTX_IDTTX_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IDTTX;
	tmp = (tmp & US_IDTTX_IDTTX_Msk) >> US_IDTTX_IDTTX_Pos;
	return tmp;
}

static inline void hri_usart_set_US_IDTTX_reg(const void *const hw, hri_usart_us_idttx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTTX |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_idttx_reg_t hri_usart_get_US_IDTTX_reg(const void *const hw, hri_usart_us_idttx_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IDTTX;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_IDTTX_reg(const void *const hw, hri_usart_us_idttx_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTTX = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_IDTTX_reg(const void *const hw, hri_usart_us_idttx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTTX &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_IDTTX_reg(const void *const hw, hri_usart_us_idttx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTTX ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_idttx_reg_t hri_usart_read_US_IDTTX_reg(const void *const hw)
{
	return ((Usart *)hw)->US_IDTTX;
}

static inline void hri_usart_set_US_IDTRX_IDTRX_bf(const void *const hw, hri_usart_us_idtrx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTRX |= US_IDTRX_IDTRX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_idtrx_reg_t hri_usart_get_US_IDTRX_IDTRX_bf(const void *const        hw,
                                                                       hri_usart_us_idtrx_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IDTRX;
	tmp = (tmp & US_IDTRX_IDTRX(mask)) >> US_IDTRX_IDTRX_Pos;
	return tmp;
}

static inline void hri_usart_write_US_IDTRX_IDTRX_bf(const void *const hw, hri_usart_us_idtrx_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_IDTRX;
	tmp &= ~US_IDTRX_IDTRX_Msk;
	tmp |= US_IDTRX_IDTRX(data);
	((Usart *)hw)->US_IDTRX = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_IDTRX_IDTRX_bf(const void *const hw, hri_usart_us_idtrx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTRX &= ~US_IDTRX_IDTRX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_IDTRX_IDTRX_bf(const void *const hw, hri_usart_us_idtrx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTRX ^= US_IDTRX_IDTRX(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_idtrx_reg_t hri_usart_read_US_IDTRX_IDTRX_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IDTRX;
	tmp = (tmp & US_IDTRX_IDTRX_Msk) >> US_IDTRX_IDTRX_Pos;
	return tmp;
}

static inline void hri_usart_set_US_IDTRX_reg(const void *const hw, hri_usart_us_idtrx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTRX |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_idtrx_reg_t hri_usart_get_US_IDTRX_reg(const void *const hw, hri_usart_us_idtrx_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_IDTRX;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_IDTRX_reg(const void *const hw, hri_usart_us_idtrx_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTRX = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_IDTRX_reg(const void *const hw, hri_usart_us_idtrx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTRX &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_IDTRX_reg(const void *const hw, hri_usart_us_idtrx_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_IDTRX ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_idtrx_reg_t hri_usart_read_US_IDTRX_reg(const void *const hw)
{
	return ((Usart *)hw)->US_IDTRX;
}

static inline void hri_usart_set_US_ICDIFF_ICDIFF_bf(const void *const hw, hri_usart_us_icdiff_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_ICDIFF |= US_ICDIFF_ICDIFF(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_icdiff_reg_t hri_usart_get_US_ICDIFF_ICDIFF_bf(const void *const         hw,
                                                                          hri_usart_us_icdiff_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_ICDIFF;
	tmp = (tmp & US_ICDIFF_ICDIFF(mask)) >> US_ICDIFF_ICDIFF_Pos;
	return tmp;
}

static inline void hri_usart_write_US_ICDIFF_ICDIFF_bf(const void *const hw, hri_usart_us_icdiff_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_ICDIFF;
	tmp &= ~US_ICDIFF_ICDIFF_Msk;
	tmp |= US_ICDIFF_ICDIFF(data);
	((Usart *)hw)->US_ICDIFF = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_ICDIFF_ICDIFF_bf(const void *const hw, hri_usart_us_icdiff_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_ICDIFF &= ~US_ICDIFF_ICDIFF(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_ICDIFF_ICDIFF_bf(const void *const hw, hri_usart_us_icdiff_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_ICDIFF ^= US_ICDIFF_ICDIFF(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_icdiff_reg_t hri_usart_read_US_ICDIFF_ICDIFF_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_ICDIFF;
	tmp = (tmp & US_ICDIFF_ICDIFF_Msk) >> US_ICDIFF_ICDIFF_Pos;
	return tmp;
}

static inline void hri_usart_set_US_ICDIFF_reg(const void *const hw, hri_usart_us_icdiff_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_ICDIFF |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_icdiff_reg_t hri_usart_get_US_ICDIFF_reg(const void *const         hw,
                                                                    hri_usart_us_icdiff_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_ICDIFF;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_ICDIFF_reg(const void *const hw, hri_usart_us_icdiff_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_ICDIFF = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_ICDIFF_reg(const void *const hw, hri_usart_us_icdiff_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_ICDIFF &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_ICDIFF_reg(const void *const hw, hri_usart_us_icdiff_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_ICDIFF ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_icdiff_reg_t hri_usart_read_US_ICDIFF_reg(const void *const hw)
{
	return ((Usart *)hw)->US_ICDIFF;
}

static inline void hri_usart_set_US_WPMR_WPEN_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR |= US_WPMR_WPEN;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usart_get_US_WPMR_WPEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_WPMR;
	tmp = (tmp & US_WPMR_WPEN) >> US_WPMR_WPEN_Pos;
	return (bool)tmp;
}

static inline void hri_usart_write_US_WPMR_WPEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_WPMR;
	tmp &= ~US_WPMR_WPEN;
	tmp |= value << US_WPMR_WPEN_Pos;
	((Usart *)hw)->US_WPMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_WPMR_WPEN_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR &= ~US_WPMR_WPEN;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_WPMR_WPEN_bit(const void *const hw)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR ^= US_WPMR_WPEN;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_set_US_WPMR_WPKEY_bf(const void *const hw, hri_usart_us_wpmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR |= US_WPMR_WPKEY(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_wpmr_reg_t hri_usart_get_US_WPMR_WPKEY_bf(const void *const hw, hri_usart_us_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_WPMR;
	tmp = (tmp & US_WPMR_WPKEY(mask)) >> US_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_usart_write_US_WPMR_WPKEY_bf(const void *const hw, hri_usart_us_wpmr_reg_t data)
{
	uint32_t tmp;
	USART_CRITICAL_SECTION_ENTER();
	tmp = ((Usart *)hw)->US_WPMR;
	tmp &= ~US_WPMR_WPKEY_Msk;
	tmp |= US_WPMR_WPKEY(data);
	((Usart *)hw)->US_WPMR = tmp;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_WPMR_WPKEY_bf(const void *const hw, hri_usart_us_wpmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR &= ~US_WPMR_WPKEY(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_WPMR_WPKEY_bf(const void *const hw, hri_usart_us_wpmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR ^= US_WPMR_WPKEY(mask);
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_wpmr_reg_t hri_usart_read_US_WPMR_WPKEY_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_WPMR;
	tmp = (tmp & US_WPMR_WPKEY_Msk) >> US_WPMR_WPKEY_Pos;
	return tmp;
}

static inline void hri_usart_set_US_WPMR_reg(const void *const hw, hri_usart_us_wpmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR |= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_wpmr_reg_t hri_usart_get_US_WPMR_reg(const void *const hw, hri_usart_us_wpmr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usart *)hw)->US_WPMR;
	tmp &= mask;
	return tmp;
}

static inline void hri_usart_write_US_WPMR_reg(const void *const hw, hri_usart_us_wpmr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_clear_US_WPMR_reg(const void *const hw, hri_usart_us_wpmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR &= ~mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_toggle_US_WPMR_reg(const void *const hw, hri_usart_us_wpmr_reg_t mask)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_WPMR ^= mask;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline hri_usart_us_wpmr_reg_t hri_usart_read_US_WPMR_reg(const void *const hw)
{
	return ((Usart *)hw)->US_WPMR;
}

static inline void hri_usart_write_US_CR_reg(const void *const hw, hri_usart_us_cr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_CR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usart_write_US_THR_reg(const void *const hw, hri_usart_us_thr_reg_t data)
{
	USART_CRITICAL_SECTION_ENTER();
	((Usart *)hw)->US_THR = data;
	USART_CRITICAL_SECTION_LEAVE();
}

/* Below section is for legacy hri apis name, not recommended to use below left side apis in application */
#define hri_usart_set_US_IMR_RXBRK_bit(a) hri_usart_set_US_IMR_USART_RXBRK_bit(a)
#define hri_usart_get_US_IMR_RXBRK_bit(a) hri_usart_get_US_IMR_USART_RXBRK_bit(a)
#define hri_usart_write_US_IMR_RXBRK_bit(a, b) hri_usart_write_US_IMR_USART_RXBRK_bit(a, b)
#define hri_usart_clear_US_IMR_RXBRK_bit(a) hri_usart_clear_US_IMR_USART_RXBRK_bit(a)
#define hri_usart_set_US_IMR_FRAME_bit(a) hri_usart_set_US_IMR_USART_LIN_FRAME_bit(a)
#define hri_usart_get_US_IMR_FRAME_bit(a) hri_usart_get_US_IMR_USART_LIN_FRAME_bit(a)
#define hri_usart_write_US_IMR_FRAME_bit(a, b) hri_usart_write_US_IMR_USART_LIN_FRAME_bit(a, b)
#define hri_usart_clear_US_IMR_FRAME_bit(a) hri_usart_clear_US_IMR_USART_LIN_FRAME_bit(a)
#define hri_usart_set_US_IMR_PARE_bit(a) hri_usart_set_US_IMR_USART_LIN_PARE_bit(a)
#define hri_usart_get_US_IMR_PARE_bit(a) hri_usart_get_US_IMR_USART_LIN_PARE_bit(a)
#define hri_usart_write_US_IMR_PARE_bit(a, b) hri_usart_write_US_IMR_USART_LIN_PARE_bit(a, b)
#define hri_usart_clear_US_IMR_PARE_bit(a) hri_usart_clear_US_IMR_USART_LIN_PARE_bit(a)
#define hri_usart_set_US_IMR_TIMEOUT_bit(a) hri_usart_set_US_IMR_USART_LIN_TIMEOUT_bit(a)
#define hri_usart_get_US_IMR_TIMEOUT_bit(a) hri_usart_get_US_IMR_USART_LIN_TIMEOUT_bit(a)
#define hri_usart_write_US_IMR_TIMEOUT_bit(a, b) hri_usart_write_US_IMR_USART_LIN_TIMEOUT_bit(a, b)
#define hri_usart_clear_US_IMR_TIMEOUT_bit(a) hri_usart_clear_US_IMR_USART_LIN_TIMEOUT_bit(a)
#define hri_usart_set_US_IMR_ITER_bit(a) hri_usart_set_US_IMR_USART_ITER_bit(a)
#define hri_usart_get_US_IMR_ITER_bit(a) hri_usart_get_US_IMR_USART_ITER_bit(a)
#define hri_usart_write_US_IMR_ITER_bit(a, b) hri_usart_write_US_IMR_USART_ITER_bit(a, b)
#define hri_usart_clear_US_IMR_ITER_bit(a) hri_usart_clear_US_IMR_USART_ITER_bit(a)
#define hri_usart_set_US_IMR_NACK_bit(a) hri_usart_set_US_IMR_USART_NACK_bit(a)
#define hri_usart_get_US_IMR_NACK_bit(a) hri_usart_get_US_IMR_USART_NACK_bit(a)
#define hri_usart_write_US_IMR_NACK_bit(a, b) hri_usart_write_US_IMR_USART_NACK_bit(a, b)
#define hri_usart_clear_US_IMR_NACK_bit(a) hri_usart_clear_US_IMR_USART_NACK_bit(a)
#define hri_usart_set_US_IMR_CTSIC_bit(a) hri_usart_set_US_IMR_USART_CTSIC_bit(a)
#define hri_usart_get_US_IMR_CTSIC_bit(a) hri_usart_get_US_IMR_USART_CTSIC_bit(a)
#define hri_usart_write_US_IMR_CTSIC_bit(a, b) hri_usart_write_US_IMR_USART_CTSIC_bit(a, b)
#define hri_usart_clear_US_IMR_CTSIC_bit(a) hri_usart_clear_US_IMR_USART_CTSIC_bit(a)
#define hri_usart_set_US_IMR_MANE_bit(a) hri_usart_set_US_IMR_USART_MANE_bit(a)
#define hri_usart_get_US_IMR_MANE_bit(a) hri_usart_get_US_IMR_USART_MANE_bit(a)
#define hri_usart_write_US_IMR_MANE_bit(a, b) hri_usart_write_US_IMR_USART_MANE_bit(a, b)
#define hri_usart_clear_US_IMR_MANE_bit(a) hri_usart_clear_US_IMR_USART_MANE_bit(a)
#define hri_usart_get_US_CSR_RXBRK_bit(a) hri_usart_get_US_CSR_USART_RXBRK_bit(a)
#define hri_usart_get_US_CSR_FRAME_bit(a) hri_usart_get_US_CSR_USART_LIN_FRAME_bit(a)
#define hri_usart_get_US_CSR_PARE_bit(a) hri_usart_get_US_CSR_USART_LIN_PARE_bit(a)
#define hri_usart_get_US_CSR_TIMEOUT_bit(a) hri_usart_get_US_CSR_USART_LIN_TIMEOUT_bit(a)
#define hri_usart_get_US_CSR_ITER_bit(a) hri_usart_get_US_CSR_USART_ITER_bit(a)
#define hri_usart_get_US_CSR_NACK_bit(a) hri_usart_get_US_CSR_USART_NACK_bit(a)
#define hri_usart_get_US_CSR_CTSIC_bit(a) hri_usart_get_US_CSR_USART_CTSIC_bit(a)
#define hri_usart_get_US_CSR_RI_bit(a) hri_usart_get_US_CSR_USART_RI_bit(a)
#define hri_usart_get_US_CSR_DSR_bit(a) hri_usart_get_US_CSR_USART_DSR_bit(a)
#define hri_usart_get_US_CSR_DCD_bit(a) hri_usart_get_US_CSR_USART_DCD_bit(a)
#define hri_usart_get_US_CSR_CTS_bit(a) hri_usart_get_US_CSR_USART_CTS_bit(a)
#define hri_usart_get_US_CSR_MANERR_bit(a) hri_usart_get_US_CSR_USART_MANERR_bit(a)
#define hri_usart_set_US_MR_SYNC_bit(a) hri_usart_set_US_MR_USART_SYNC_bit(a)
#define hri_usart_get_US_MR_SYNC_bit(a) hri_usart_get_US_MR_USART_SYNC_bit(a)
#define hri_usart_write_US_MR_SYNC_bit(a, b) hri_usart_write_US_MR_USART_SYNC_bit(a, b)
#define hri_usart_clear_US_MR_SYNC_bit(a) hri_usart_clear_US_MR_USART_SYNC_bit(a)
#define hri_usart_toggle_US_MR_SYNC_bit(a) hri_usart_toggle_US_MR_USART_SYNC_bit(a)
#define hri_usart_set_US_MR_MSBF_bit(a) hri_usart_set_US_MR_USART_MSBF_bit(a)
#define hri_usart_get_US_MR_MSBF_bit(a) hri_usart_get_US_MR_USART_MSBF_bit(a)
#define hri_usart_write_US_MR_MSBF_bit(a, b) hri_usart_write_US_MR_USART_MSBF_bit(a, b)
#define hri_usart_clear_US_MR_MSBF_bit(a) hri_usart_clear_US_MR_USART_MSBF_bit(a)
#define hri_usart_toggle_US_MR_MSBF_bit(a) hri_usart_toggle_US_MR_USART_MSBF_bit(a)
#define hri_usart_set_US_MR_MODE9_bit(a) hri_usart_set_US_MR_USART_MODE9_bit(a)
#define hri_usart_get_US_MR_MODE9_bit(a) hri_usart_get_US_MR_USART_MODE9_bit(a)
#define hri_usart_write_US_MR_MODE9_bit(a, b) hri_usart_write_US_MR_USART_MODE9_bit(a, b)
#define hri_usart_clear_US_MR_MODE9_bit(a) hri_usart_clear_US_MR_USART_MODE9_bit(a)
#define hri_usart_toggle_US_MR_MODE9_bit(a) hri_usart_toggle_US_MR_USART_MODE9_bit(a)
#define hri_usart_set_US_MR_OVER_bit(a) hri_usart_set_US_MR_USART_OVER_bit(a)
#define hri_usart_get_US_MR_OVER_bit(a) hri_usart_get_US_MR_USART_OVER_bit(a)
#define hri_usart_write_US_MR_OVER_bit(a, b) hri_usart_write_US_MR_USART_OVER_bit(a, b)
#define hri_usart_clear_US_MR_OVER_bit(a) hri_usart_clear_US_MR_USART_OVER_bit(a)
#define hri_usart_toggle_US_MR_OVER_bit(a) hri_usart_toggle_US_MR_USART_OVER_bit(a)
#define hri_usart_set_US_MR_INACK_bit(a) hri_usart_set_US_MR_USART_INACK_bit(a)
#define hri_usart_get_US_MR_INACK_bit(a) hri_usart_get_US_MR_USART_INACK_bit(a)
#define hri_usart_write_US_MR_INACK_bit(a, b) hri_usart_write_US_MR_USART_INACK_bit(a, b)
#define hri_usart_clear_US_MR_INACK_bit(a) hri_usart_clear_US_MR_USART_INACK_bit(a)
#define hri_usart_toggle_US_MR_INACK_bit(a) hri_usart_toggle_US_MR_USART_INACK_bit(a)
#define hri_usart_set_US_MR_DSNACK_bit(a) hri_usart_set_US_MR_USART_DSNACK_bit(a)
#define hri_usart_get_US_MR_DSNACK_bit(a) hri_usart_get_US_MR_USART_DSNACK_bit(a)
#define hri_usart_write_US_MR_DSNACK_bit(a, b) hri_usart_write_US_MR_USART_DSNACK_bit(a, b)
#define hri_usart_clear_US_MR_DSNACK_bit(a) hri_usart_clear_US_MR_USART_DSNACK_bit(a)
#define hri_usart_toggle_US_MR_DSNACK_bit(a) hri_usart_toggle_US_MR_USART_DSNACK_bit(a)
#define hri_usart_set_US_MR_INVDATA_bit(a) hri_usart_set_US_MR_USART_INVDATA_bit(a)
#define hri_usart_get_US_MR_INVDATA_bit(a) hri_usart_get_US_MR_USART_INVDATA_bit(a)
#define hri_usart_write_US_MR_INVDATA_bit(a, b) hri_usart_write_US_MR_USART_INVDATA_bit(a, b)
#define hri_usart_clear_US_MR_INVDATA_bit(a) hri_usart_clear_US_MR_USART_INVDATA_bit(a)
#define hri_usart_toggle_US_MR_INVDATA_bit(a) hri_usart_toggle_US_MR_USART_INVDATA_bit(a)
#define hri_usart_set_US_MR_FILTER_bit(a) hri_usart_set_US_MR_USART_FILTER_bit(a)
#define hri_usart_get_US_MR_FILTER_bit(a) hri_usart_get_US_MR_USART_FILTER_bit(a)
#define hri_usart_write_US_MR_FILTER_bit(a, b) hri_usart_write_US_MR_USART_FILTER_bit(a, b)
#define hri_usart_clear_US_MR_FILTER_bit(a) hri_usart_clear_US_MR_USART_FILTER_bit(a)
#define hri_usart_toggle_US_MR_FILTER_bit(a) hri_usart_toggle_US_MR_USART_FILTER_bit(a)
#define hri_usart_set_US_MR_MAN_bit(a) hri_usart_set_US_MR_USART_MAN_bit(a)
#define hri_usart_get_US_MR_MAN_bit(a) hri_usart_get_US_MR_USART_MAN_bit(a)
#define hri_usart_write_US_MR_MAN_bit(a, b) hri_usart_write_US_MR_USART_MAN_bit(a, b)
#define hri_usart_clear_US_MR_MAN_bit(a) hri_usart_clear_US_MR_USART_MAN_bit(a)
#define hri_usart_toggle_US_MR_MAN_bit(a) hri_usart_toggle_US_MR_USART_MAN_bit(a)
#define hri_usart_set_US_MR_MODSYNC_bit(a) hri_usart_set_US_MR_USART_MODSYNC_bit(a)
#define hri_usart_get_US_MR_MODSYNC_bit(a) hri_usart_get_US_MR_USART_MODSYNC_bit(a)
#define hri_usart_write_US_MR_MODSYNC_bit(a, b) hri_usart_write_US_MR_USART_MODSYNC_bit(a, b)
#define hri_usart_clear_US_MR_MODSYNC_bit(a) hri_usart_clear_US_MR_USART_MODSYNC_bit(a)
#define hri_usart_toggle_US_MR_MODSYNC_bit(a) hri_usart_toggle_US_MR_USART_MODSYNC_bit(a)
#define hri_usart_set_US_MR_ONEBIT_bit(a) hri_usart_set_US_MR_USART_ONEBIT_bit(a)
#define hri_usart_get_US_MR_ONEBIT_bit(a) hri_usart_get_US_MR_USART_ONEBIT_bit(a)
#define hri_usart_write_US_MR_ONEBIT_bit(a, b) hri_usart_write_US_MR_USART_ONEBIT_bit(a, b)
#define hri_usart_clear_US_MR_ONEBIT_bit(a) hri_usart_clear_US_MR_USART_ONEBIT_bit(a)
#define hri_usart_toggle_US_MR_ONEBIT_bit(a) hri_usart_toggle_US_MR_USART_ONEBIT_bit(a)
#define hri_usart_set_US_MR_PAR_bf(a, b) hri_usart_set_US_MR_USART_PAR_bf(a, b)
#define hri_usart_get_US_MR_PAR_bf(a, b) hri_usart_get_US_MR_USART_PAR_bf(a, b)
#define hri_usart_write_US_MR_PAR_bf(a, b) hri_usart_write_US_MR_USART_PAR_bf(a, b)
#define hri_usart_clear_US_MR_PAR_bf(a, b) hri_usart_clear_US_MR_USART_PAR_bf(a, b)
#define hri_usart_toggle_US_MR_PAR_bf(a, b) hri_usart_toggle_US_MR_USART_PAR_bf(a, b)
#define hri_usart_read_US_MR_PAR_bf(a) hri_usart_read_US_MR_USART_PAR_bf(a)
#define hri_usart_set_US_MR_NBSTOP_bf(a, b) hri_usart_set_US_MR_USART_NBSTOP_bf(a, b)
#define hri_usart_get_US_MR_NBSTOP_bf(a, b) hri_usart_get_US_MR_USART_NBSTOP_bf(a, b)
#define hri_usart_write_US_MR_NBSTOP_bf(a, b) hri_usart_write_US_MR_USART_NBSTOP_bf(a, b)
#define hri_usart_clear_US_MR_NBSTOP_bf(a, b) hri_usart_clear_US_MR_USART_NBSTOP_bf(a, b)
#define hri_usart_toggle_US_MR_NBSTOP_bf(a, b) hri_usart_toggle_US_MR_USART_NBSTOP_bf(a, b)
#define hri_usart_read_US_MR_NBSTOP_bf(a) hri_usart_read_US_MR_USART_NBSTOP_bf(a)
#define hri_usart_set_US_MR_CHMODE_bf(a, b) hri_usart_set_US_MR_USART_CHMODE_bf(a, b)
#define hri_usart_get_US_MR_CHMODE_bf(a, b) hri_usart_get_US_MR_USART_CHMODE_bf(a, b)
#define hri_usart_write_US_MR_CHMODE_bf(a, b) hri_usart_write_US_MR_USART_CHMODE_bf(a, b)
#define hri_usart_clear_US_MR_CHMODE_bf(a, b) hri_usart_clear_US_MR_USART_CHMODE_bf(a, b)
#define hri_usart_toggle_US_MR_CHMODE_bf(a, b) hri_usart_toggle_US_MR_USART_CHMODE_bf(a, b)
#define hri_usart_read_US_MR_CHMODE_bf(a) hri_usart_read_US_MR_USART_CHMODE_bf(a)
#define hri_usart_set_US_TTGR_TG_bf(a, b) hri_usart_set_US_TTGR_USART_TG_bf(a, b)
#define hri_usart_get_US_TTGR_TG_bf(a, b) hri_usart_get_US_TTGR_USART_TG_bf(a, b)
#define hri_usart_write_US_TTGR_TG_bf(a, b) hri_usart_write_US_TTGR_USART_TG_bf(a, b)
#define hri_usart_clear_US_TTGR_TG_bf(a, b) hri_usart_clear_US_TTGR_USART_TG_bf(a, b)
#define hri_usart_toggle_US_TTGR_TG_bf(a, b) hri_usart_toggle_US_TTGR_USART_TG_bf(a, b)
#define hri_usart_read_US_TTGR_TG_bf(a) hri_usart_read_US_TTGR_USART_TG_bf(a)

#ifdef __cplusplus
}
#endif

#endif /* _HRI_USART_E70B_H_INCLUDED */
#endif /* _SAME70_USART_COMPONENT_ */
