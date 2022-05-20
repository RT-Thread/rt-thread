/**
 * \file
 *
 * \brief SAM USBHS
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

#ifdef _SAME70_USBHS_COMPONENT_
#ifndef _HRI_USBHS_E70B_H_INCLUDED_
#define _HRI_USBHS_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_USBHS_CRITICAL_SECTIONS)
#define USBHS_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define USBHS_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define USBHS_CRITICAL_SECTION_ENTER()
#define USBHS_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_usbhs_ctrl_reg_t;
typedef uint32_t hri_usbhs_devctrl_reg_t;
typedef uint32_t hri_usbhs_devdmaaddress_reg_t;
typedef uint32_t hri_usbhs_devdmacontrol_reg_t;
typedef uint32_t hri_usbhs_devdmanxtdsc_reg_t;
typedef uint32_t hri_usbhs_devdmastatus_reg_t;
typedef uint32_t hri_usbhs_devept_reg_t;
typedef uint32_t hri_usbhs_deveptcfg_reg_t;
typedef uint32_t hri_usbhs_deveptidr_reg_t;
typedef uint32_t hri_usbhs_deveptier_reg_t;
typedef uint32_t hri_usbhs_deveptifr_reg_t;
typedef uint32_t hri_usbhs_deveptimr_reg_t;
typedef uint32_t hri_usbhs_deveptisr_reg_t;
typedef uint32_t hri_usbhs_devfnum_reg_t;
typedef uint32_t hri_usbhs_devicr_reg_t;
typedef uint32_t hri_usbhs_devifr_reg_t;
typedef uint32_t hri_usbhs_devimr_reg_t;
typedef uint32_t hri_usbhs_devisr_reg_t;
typedef uint32_t hri_usbhs_hstaddr1_reg_t;
typedef uint32_t hri_usbhs_hstaddr2_reg_t;
typedef uint32_t hri_usbhs_hstaddr3_reg_t;
typedef uint32_t hri_usbhs_hstctrl_reg_t;
typedef uint32_t hri_usbhs_hstdmaaddress_reg_t;
typedef uint32_t hri_usbhs_hstdmacontrol_reg_t;
typedef uint32_t hri_usbhs_hstdmanxtdsc_reg_t;
typedef uint32_t hri_usbhs_hstdmastatus_reg_t;
typedef uint32_t hri_usbhs_hstfnum_reg_t;
typedef uint32_t hri_usbhs_hsticr_reg_t;
typedef uint32_t hri_usbhs_hstifr_reg_t;
typedef uint32_t hri_usbhs_hstimr_reg_t;
typedef uint32_t hri_usbhs_hstisr_reg_t;
typedef uint32_t hri_usbhs_hstpip_reg_t;
typedef uint32_t hri_usbhs_hstpipcfg_reg_t;
typedef uint32_t hri_usbhs_hstpiperr_reg_t;
typedef uint32_t hri_usbhs_hstpipidr_reg_t;
typedef uint32_t hri_usbhs_hstpipier_reg_t;
typedef uint32_t hri_usbhs_hstpipifr_reg_t;
typedef uint32_t hri_usbhs_hstpipimr_reg_t;
typedef uint32_t hri_usbhs_hstpipinrq_reg_t;
typedef uint32_t hri_usbhs_hstpipisr_reg_t;
typedef uint32_t hri_usbhs_sfr_reg_t;
typedef uint32_t hri_usbhs_sr_reg_t;
typedef uint32_t hri_usbhsdevdma_devdmaaddress_reg_t;
typedef uint32_t hri_usbhsdevdma_devdmacontrol_reg_t;
typedef uint32_t hri_usbhsdevdma_devdmanxtdsc_reg_t;
typedef uint32_t hri_usbhsdevdma_devdmastatus_reg_t;
typedef uint32_t hri_usbhshstdma_hstdmaaddress_reg_t;
typedef uint32_t hri_usbhshstdma_hstdmacontrol_reg_t;
typedef uint32_t hri_usbhshstdma_hstdmanxtdsc_reg_t;
typedef uint32_t hri_usbhshstdma_hstdmastatus_reg_t;

static inline bool hri_usbhs_get_DEVEPTISR_TXINI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_TXINI) >> USBHS_DEVEPTISR_TXINI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_TXINI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_TXINI;
}

static inline bool hri_usbhs_get_DEVEPTISR_RXOUTI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_RXOUTI) >> USBHS_DEVEPTISR_RXOUTI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_RXOUTI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_RXOUTI;
}

static inline bool hri_usbhs_get_DEVEPTISR_CTRL_RXSTPI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_CTRL_RXSTPI) >> USBHS_DEVEPTISR_CTRL_RXSTPI_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_BLK_RXSTPI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_BLK_RXSTPI) >> USBHS_DEVEPTISR_BLK_RXSTPI_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_INTRPT_RXSTPI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_INTRPT_RXSTPI) >> USBHS_DEVEPTISR_INTRPT_RXSTPI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_CTRL_RXSTPI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_CTRL_RXSTPI;
}

static inline void hri_usbhs_clear_DEVEPTISR_BLK_RXSTPI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_BLK_RXSTPI;
}

static inline void hri_usbhs_clear_DEVEPTISR_INTRPT_RXSTPI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_INTRPT_RXSTPI;
}

static inline bool hri_usbhs_get_DEVEPTISR_ISO_UNDERFI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_ISO_UNDERFI) >> USBHS_DEVEPTISR_ISO_UNDERFI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_ISO_UNDERFI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_ISO_UNDERFI;
}

static inline bool hri_usbhs_get_DEVEPTISR_CTRL_NAKOUTI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_CTRL_NAKOUTI) >> USBHS_DEVEPTISR_CTRL_NAKOUTI_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_BLK_NAKOUTI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_BLK_NAKOUTI) >> USBHS_DEVEPTISR_BLK_NAKOUTI_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_INTRPT_NAKOUTI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_INTRPT_NAKOUTI)
	       >> USBHS_DEVEPTISR_INTRPT_NAKOUTI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_CTRL_NAKOUTI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_CTRL_NAKOUTI;
}

static inline void hri_usbhs_clear_DEVEPTISR_BLK_NAKOUTI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_BLK_NAKOUTI;
}

static inline void hri_usbhs_clear_DEVEPTISR_INTRPT_NAKOUTI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_INTRPT_NAKOUTI;
}

static inline bool hri_usbhs_get_DEVEPTISR_ISO_HBISOINERRI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_ISO_HBISOINERRI)
	       >> USBHS_DEVEPTISR_ISO_HBISOINERRI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_ISO_HBISOINERRI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_ISO_HBISOINERRI;
}

static inline bool hri_usbhs_get_DEVEPTISR_CTRL_NAKINI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_CTRL_NAKINI) >> USBHS_DEVEPTISR_CTRL_NAKINI_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_BLK_NAKINI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_BLK_NAKINI) >> USBHS_DEVEPTISR_BLK_NAKINI_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_INTRPT_NAKINI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_INTRPT_NAKINI) >> USBHS_DEVEPTISR_INTRPT_NAKINI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_CTRL_NAKINI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_CTRL_NAKINI;
}

static inline void hri_usbhs_clear_DEVEPTISR_BLK_NAKINI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_BLK_NAKINI;
}

static inline void hri_usbhs_clear_DEVEPTISR_INTRPT_NAKINI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_INTRPT_NAKINI;
}

static inline bool hri_usbhs_get_DEVEPTISR_ISO_HBISOFLUSHI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_ISO_HBISOFLUSHI)
	       >> USBHS_DEVEPTISR_ISO_HBISOFLUSHI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_ISO_HBISOFLUSHI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_ISO_HBISOFLUSHI;
}

static inline bool hri_usbhs_get_DEVEPTISR_OVERFI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_OVERFI) >> USBHS_DEVEPTISR_OVERFI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_OVERFI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_OVERFI;
}

static inline bool hri_usbhs_get_DEVEPTISR_CTRL_STALLEDI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_CTRL_STALLEDI) >> USBHS_DEVEPTISR_CTRL_STALLEDI_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_BLK_STALLEDI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_BLK_STALLEDI) >> USBHS_DEVEPTISR_BLK_STALLEDI_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_INTRPT_STALLEDI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_INTRPT_STALLEDI)
	       >> USBHS_DEVEPTISR_INTRPT_STALLEDI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_CTRL_STALLEDI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_CTRL_STALLEDI;
}

static inline void hri_usbhs_clear_DEVEPTISR_BLK_STALLEDI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_BLK_STALLEDI;
}

static inline void hri_usbhs_clear_DEVEPTISR_INTRPT_STALLEDI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_INTRPT_STALLEDI;
}

static inline bool hri_usbhs_get_DEVEPTISR_ISO_CRCERRI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_ISO_CRCERRI) >> USBHS_DEVEPTISR_ISO_CRCERRI_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_ISO_CRCERRI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_ISO_CRCERRI;
}

static inline bool hri_usbhs_get_DEVEPTISR_SHORTPACKET_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_SHORTPACKET) >> USBHS_DEVEPTISR_SHORTPACKET_Pos;
}

static inline void hri_usbhs_clear_DEVEPTISR_SHORTPACKET_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = USBHS_DEVEPTISR_SHORTPACKET;
}

static inline bool hri_usbhs_get_DEVEPTISR_ISO_ERRORTRANS_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_ISO_ERRORTRANS)
	       >> USBHS_DEVEPTISR_ISO_ERRORTRANS_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_RWALL_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_RWALL) >> USBHS_DEVEPTISR_RWALL_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_CTRL_CTRLDIR_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_CTRL_CTRLDIR) >> USBHS_DEVEPTISR_CTRL_CTRLDIR_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_BLK_CTRLDIR_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_BLK_CTRLDIR) >> USBHS_DEVEPTISR_BLK_CTRLDIR_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_INTRPT_CTRLDIR_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_INTRPT_CTRLDIR)
	       >> USBHS_DEVEPTISR_INTRPT_CTRLDIR_Pos;
}

static inline bool hri_usbhs_get_DEVEPTISR_CFGOK_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTISR[index] & USBHS_DEVEPTISR_CFGOK) >> USBHS_DEVEPTISR_CFGOK_Pos;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_get_DEVEPTISR_DTSEQ_bf(const void *const hw, uint8_t index,
                                                                         hri_usbhs_deveptisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
	tmp = (tmp & USBHS_DEVEPTISR_DTSEQ(mask)) >> USBHS_DEVEPTISR_DTSEQ_Pos;
	return tmp;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_read_DEVEPTISR_DTSEQ_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
	tmp = (tmp & USBHS_DEVEPTISR_DTSEQ_Msk) >> USBHS_DEVEPTISR_DTSEQ_Pos;
	return tmp;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_get_DEVEPTISR_NBUSYBK_bf(const void *const hw, uint8_t index,
                                                                           hri_usbhs_deveptisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
	tmp = (tmp & USBHS_DEVEPTISR_NBUSYBK(mask)) >> USBHS_DEVEPTISR_NBUSYBK_Pos;
	return tmp;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_read_DEVEPTISR_NBUSYBK_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
	tmp = (tmp & USBHS_DEVEPTISR_NBUSYBK_Msk) >> USBHS_DEVEPTISR_NBUSYBK_Pos;
	return tmp;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_get_DEVEPTISR_CURRBK_bf(const void *const hw, uint8_t index,
                                                                          hri_usbhs_deveptisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
	tmp = (tmp & USBHS_DEVEPTISR_CURRBK(mask)) >> USBHS_DEVEPTISR_CURRBK_Pos;
	return tmp;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_read_DEVEPTISR_CURRBK_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
	tmp = (tmp & USBHS_DEVEPTISR_CURRBK_Msk) >> USBHS_DEVEPTISR_CURRBK_Pos;
	return tmp;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_get_DEVEPTISR_BYCT_bf(const void *const hw, uint8_t index,
                                                                        hri_usbhs_deveptisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
	tmp = (tmp & USBHS_DEVEPTISR_BYCT(mask)) >> USBHS_DEVEPTISR_BYCT_Pos;
	return tmp;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_read_DEVEPTISR_BYCT_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
	tmp = (tmp & USBHS_DEVEPTISR_BYCT_Msk) >> USBHS_DEVEPTISR_BYCT_Pos;
	return tmp;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_get_DEVEPTISR_reg(const void *const hw, uint8_t index,
                                                                    hri_usbhs_deveptisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_deveptisr_reg_t hri_usbhs_read_DEVEPTISR_reg(const void *const hw, uint8_t index)
{
	return ((Usbhs *)hw)->USBHS_DEVEPTISR[index];
}

static inline void hri_usbhs_clear_DEVEPTISR_reg(const void *const hw, uint8_t index, hri_usbhs_deveptisr_reg_t mask)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = mask;
}

static inline void hri_usbhs_write_DEVEPTICR_reg(const void *const hw, uint8_t index, hri_usbhs_deveptisr_reg_t data)
{
	((Usbhs *)hw)->USBHS_DEVEPTICR[index] = data;
}

static inline bool hri_usbhs_get_HSTPIPISR_RXINI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_RXINI) >> USBHS_HSTPIPISR_RXINI_Pos;
}

static inline void hri_usbhs_clear_HSTPIPISR_RXINI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_RXINI;
}

static inline bool hri_usbhs_get_HSTPIPISR_TXOUTI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_TXOUTI) >> USBHS_HSTPIPISR_TXOUTI_Pos;
}

static inline void hri_usbhs_clear_HSTPIPISR_TXOUTI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_TXOUTI;
}

static inline bool hri_usbhs_get_HSTPIPISR_CTRL_TXSTPI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_CTRL_TXSTPI) >> USBHS_HSTPIPISR_CTRL_TXSTPI_Pos;
}

static inline bool hri_usbhs_get_HSTPIPISR_BLK_TXSTPI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_BLK_TXSTPI) >> USBHS_HSTPIPISR_BLK_TXSTPI_Pos;
}

static inline void hri_usbhs_clear_HSTPIPISR_CTRL_TXSTPI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_CTRL_TXSTPI;
}

static inline void hri_usbhs_clear_HSTPIPISR_BLK_TXSTPI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_BLK_TXSTPI;
}

static inline bool hri_usbhs_get_HSTPIPISR_ISO_UNDERFI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_ISO_UNDERFI) >> USBHS_HSTPIPISR_ISO_UNDERFI_Pos;
}

static inline bool hri_usbhs_get_HSTPIPISR_INTRPT_UNDERFI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_INTRPT_UNDERFI)
	       >> USBHS_HSTPIPISR_INTRPT_UNDERFI_Pos;
}

static inline void hri_usbhs_clear_HSTPIPISR_ISO_UNDERFI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_ISO_UNDERFI;
}

static inline void hri_usbhs_clear_HSTPIPISR_INTRPT_UNDERFI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_INTRPT_UNDERFI;
}

static inline bool hri_usbhs_get_HSTPIPISR_PERRI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_PERRI) >> USBHS_HSTPIPISR_PERRI_Pos;
}

static inline bool hri_usbhs_get_HSTPIPISR_NAKEDI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_NAKEDI) >> USBHS_HSTPIPISR_NAKEDI_Pos;
}

static inline void hri_usbhs_clear_HSTPIPISR_NAKEDI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_NAKEDI;
}

static inline bool hri_usbhs_get_HSTPIPISR_OVERFI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_OVERFI) >> USBHS_HSTPIPISR_OVERFI_Pos;
}

static inline void hri_usbhs_clear_HSTPIPISR_OVERFI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_OVERFI;
}

static inline bool hri_usbhs_get_HSTPIPISR_CTRL_RXSTALLDI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_CTRL_RXSTALLDI)
	       >> USBHS_HSTPIPISR_CTRL_RXSTALLDI_Pos;
}

static inline bool hri_usbhs_get_HSTPIPISR_BLK_RXSTALLDI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_BLK_RXSTALLDI) >> USBHS_HSTPIPISR_BLK_RXSTALLDI_Pos;
}

static inline bool hri_usbhs_get_HSTPIPISR_INTRPT_RXSTALLDI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_INTRPT_RXSTALLDI)
	       >> USBHS_HSTPIPISR_INTRPT_RXSTALLDI_Pos;
}

static inline void hri_usbhs_clear_HSTPIPISR_CTRL_RXSTALLDI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_CTRL_RXSTALLDI;
}

static inline void hri_usbhs_clear_HSTPIPISR_BLK_RXSTALLDI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_BLK_RXSTALLDI;
}

static inline void hri_usbhs_clear_HSTPIPISR_INTRPT_RXSTALLDI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_INTRPT_RXSTALLDI;
}

static inline bool hri_usbhs_get_HSTPIPISR_ISO_CRCERRI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_ISO_CRCERRI) >> USBHS_HSTPIPISR_ISO_CRCERRI_Pos;
}

static inline void hri_usbhs_clear_HSTPIPISR_ISO_CRCERRI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_ISO_CRCERRI;
}

static inline bool hri_usbhs_get_HSTPIPISR_SHORTPACKETI_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_SHORTPACKETI) >> USBHS_HSTPIPISR_SHORTPACKETI_Pos;
}

static inline void hri_usbhs_clear_HSTPIPISR_SHORTPACKETI_bit(const void *const hw, uint8_t index)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = USBHS_HSTPIPISR_SHORTPACKETI;
}

static inline bool hri_usbhs_get_HSTPIPISR_RWALL_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_RWALL) >> USBHS_HSTPIPISR_RWALL_Pos;
}

static inline bool hri_usbhs_get_HSTPIPISR_CFGOK_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPISR[index] & USBHS_HSTPIPISR_CFGOK) >> USBHS_HSTPIPISR_CFGOK_Pos;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_get_HSTPIPISR_DTSEQ_bf(const void *const hw, uint8_t index,
                                                                         hri_usbhs_hstpipisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
	tmp = (tmp & USBHS_HSTPIPISR_DTSEQ(mask)) >> USBHS_HSTPIPISR_DTSEQ_Pos;
	return tmp;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_read_HSTPIPISR_DTSEQ_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
	tmp = (tmp & USBHS_HSTPIPISR_DTSEQ_Msk) >> USBHS_HSTPIPISR_DTSEQ_Pos;
	return tmp;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_get_HSTPIPISR_NBUSYBK_bf(const void *const hw, uint8_t index,
                                                                           hri_usbhs_hstpipisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
	tmp = (tmp & USBHS_HSTPIPISR_NBUSYBK(mask)) >> USBHS_HSTPIPISR_NBUSYBK_Pos;
	return tmp;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_read_HSTPIPISR_NBUSYBK_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
	tmp = (tmp & USBHS_HSTPIPISR_NBUSYBK_Msk) >> USBHS_HSTPIPISR_NBUSYBK_Pos;
	return tmp;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_get_HSTPIPISR_CURRBK_bf(const void *const hw, uint8_t index,
                                                                          hri_usbhs_hstpipisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
	tmp = (tmp & USBHS_HSTPIPISR_CURRBK(mask)) >> USBHS_HSTPIPISR_CURRBK_Pos;
	return tmp;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_read_HSTPIPISR_CURRBK_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
	tmp = (tmp & USBHS_HSTPIPISR_CURRBK_Msk) >> USBHS_HSTPIPISR_CURRBK_Pos;
	return tmp;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_get_HSTPIPISR_PBYCT_bf(const void *const hw, uint8_t index,
                                                                         hri_usbhs_hstpipisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
	tmp = (tmp & USBHS_HSTPIPISR_PBYCT(mask)) >> USBHS_HSTPIPISR_PBYCT_Pos;
	return tmp;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_read_HSTPIPISR_PBYCT_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
	tmp = (tmp & USBHS_HSTPIPISR_PBYCT_Msk) >> USBHS_HSTPIPISR_PBYCT_Pos;
	return tmp;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_get_HSTPIPISR_reg(const void *const hw, uint8_t index,
                                                                    hri_usbhs_hstpipisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_hstpipisr_reg_t hri_usbhs_read_HSTPIPISR_reg(const void *const hw, uint8_t index)
{
	return ((Usbhs *)hw)->USBHS_HSTPIPISR[index];
}

static inline void hri_usbhs_clear_HSTPIPISR_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipisr_reg_t mask)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = mask;
}

static inline void hri_usbhs_write_HSTPIPICR_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipisr_reg_t data)
{
	((Usbhs *)hw)->USBHS_HSTPIPICR[index] = data;
}

static inline bool hri_usbhs_get_SR_RDERRI_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_SR & USBHS_SR_RDERRI) >> USBHS_SR_RDERRI_Pos;
}

static inline void hri_usbhs_clear_SR_RDERRI_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_SCR = USBHS_SR_RDERRI;
}

static inline bool hri_usbhs_get_SR_CLKUSABLE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_SR & USBHS_SR_CLKUSABLE) >> USBHS_SR_CLKUSABLE_Pos;
}

static inline hri_usbhs_sr_reg_t hri_usbhs_get_SR_SPEED_bf(const void *const hw, hri_usbhs_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_SR;
	tmp = (tmp & USBHS_SR_SPEED(mask)) >> USBHS_SR_SPEED_Pos;
	return tmp;
}

static inline hri_usbhs_sr_reg_t hri_usbhs_read_SR_SPEED_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_SR;
	tmp = (tmp & USBHS_SR_SPEED_Msk) >> USBHS_SR_SPEED_Pos;
	return tmp;
}

static inline hri_usbhs_sr_reg_t hri_usbhs_get_SR_reg(const void *const hw, hri_usbhs_sr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_SR;
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_sr_reg_t hri_usbhs_read_SR_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_SR;
}

static inline void hri_usbhs_clear_SR_reg(const void *const hw, hri_usbhs_sr_reg_t mask)
{
	((Usbhs *)hw)->USBHS_SCR = mask;
}

static inline void hri_usbhs_write_SCR_reg(const void *const hw, hri_usbhs_sr_reg_t data)
{
	((Usbhs *)hw)->USBHS_SCR = data;
}

static inline void hri_usbhs_set_DEVIMR_SUSPE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_SUSPE;
}

static inline bool hri_usbhs_get_DEVIMR_SUSPE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_SUSPE) >> USBHS_DEVIMR_SUSPE_Pos;
}

static inline void hri_usbhs_write_DEVIMR_SUSPE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_SUSPE;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_SUSPE;
	}
}

static inline void hri_usbhs_clear_DEVIMR_SUSPE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_SUSPE;
}

static inline void hri_usbhs_set_DEVIMR_MSOFE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_MSOFE;
}

static inline bool hri_usbhs_get_DEVIMR_MSOFE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_MSOFE) >> USBHS_DEVIMR_MSOFE_Pos;
}

static inline void hri_usbhs_write_DEVIMR_MSOFE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_MSOFE;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_MSOFE;
	}
}

static inline void hri_usbhs_clear_DEVIMR_MSOFE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_MSOFE;
}

static inline void hri_usbhs_set_DEVIMR_SOFE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_SOFE;
}

static inline bool hri_usbhs_get_DEVIMR_SOFE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_SOFE) >> USBHS_DEVIMR_SOFE_Pos;
}

static inline void hri_usbhs_write_DEVIMR_SOFE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_SOFE;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_SOFE;
	}
}

static inline void hri_usbhs_clear_DEVIMR_SOFE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_SOFE;
}

static inline void hri_usbhs_set_DEVIMR_EORSTE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_EORSTE;
}

static inline bool hri_usbhs_get_DEVIMR_EORSTE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_EORSTE) >> USBHS_DEVIMR_EORSTE_Pos;
}

static inline void hri_usbhs_write_DEVIMR_EORSTE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_EORSTE;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_EORSTE;
	}
}

static inline void hri_usbhs_clear_DEVIMR_EORSTE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_EORSTE;
}

static inline void hri_usbhs_set_DEVIMR_WAKEUPE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_WAKEUPE;
}

static inline bool hri_usbhs_get_DEVIMR_WAKEUPE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_WAKEUPE) >> USBHS_DEVIMR_WAKEUPE_Pos;
}

static inline void hri_usbhs_write_DEVIMR_WAKEUPE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_WAKEUPE;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_WAKEUPE;
	}
}

static inline void hri_usbhs_clear_DEVIMR_WAKEUPE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_WAKEUPE;
}

static inline void hri_usbhs_set_DEVIMR_EORSME_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_EORSME;
}

static inline bool hri_usbhs_get_DEVIMR_EORSME_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_EORSME) >> USBHS_DEVIMR_EORSME_Pos;
}

static inline void hri_usbhs_write_DEVIMR_EORSME_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_EORSME;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_EORSME;
	}
}

static inline void hri_usbhs_clear_DEVIMR_EORSME_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_EORSME;
}

static inline void hri_usbhs_set_DEVIMR_UPRSME_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_UPRSME;
}

static inline bool hri_usbhs_get_DEVIMR_UPRSME_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_UPRSME) >> USBHS_DEVIMR_UPRSME_Pos;
}

static inline void hri_usbhs_write_DEVIMR_UPRSME_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_UPRSME;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_UPRSME;
	}
}

static inline void hri_usbhs_clear_DEVIMR_UPRSME_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_UPRSME;
}

static inline void hri_usbhs_set_DEVIMR_PEP_0_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_0;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_0_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_0) >> USBHS_DEVIMR_PEP_0_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_0;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_0;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_0_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_0;
}

static inline void hri_usbhs_set_DEVIMR_PEP_1_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_1;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_1_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_1) >> USBHS_DEVIMR_PEP_1_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_1;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_1;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_1_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_1;
}

static inline void hri_usbhs_set_DEVIMR_PEP_2_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_2;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_2_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_2) >> USBHS_DEVIMR_PEP_2_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_2;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_2;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_2_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_2;
}

static inline void hri_usbhs_set_DEVIMR_PEP_3_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_3;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_3_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_3) >> USBHS_DEVIMR_PEP_3_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_3;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_3;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_3_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_3;
}

static inline void hri_usbhs_set_DEVIMR_PEP_4_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_4;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_4_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_4) >> USBHS_DEVIMR_PEP_4_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_4;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_4;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_4_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_4;
}

static inline void hri_usbhs_set_DEVIMR_PEP_5_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_5;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_5_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_5) >> USBHS_DEVIMR_PEP_5_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_5;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_5;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_5_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_5;
}

static inline void hri_usbhs_set_DEVIMR_PEP_6_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_6;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_6_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_6) >> USBHS_DEVIMR_PEP_6_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_6;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_6;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_6_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_6;
}

static inline void hri_usbhs_set_DEVIMR_PEP_7_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_7;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_7_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_7) >> USBHS_DEVIMR_PEP_7_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_7;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_7;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_7_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_7;
}

static inline void hri_usbhs_set_DEVIMR_PEP_8_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_8;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_8_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_8) >> USBHS_DEVIMR_PEP_8_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_8;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_8;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_8_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_8;
}

static inline void hri_usbhs_set_DEVIMR_PEP_9_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_9;
}

static inline bool hri_usbhs_get_DEVIMR_PEP_9_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_PEP_9) >> USBHS_DEVIMR_PEP_9_Pos;
}

static inline void hri_usbhs_write_DEVIMR_PEP_9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_9;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_PEP_9;
	}
}

static inline void hri_usbhs_clear_DEVIMR_PEP_9_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_PEP_9;
}

static inline void hri_usbhs_set_DEVIMR_DMA_1_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_1;
}

static inline bool hri_usbhs_get_DEVIMR_DMA_1_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_DMA_1) >> USBHS_DEVIMR_DMA_1_Pos;
}

static inline void hri_usbhs_write_DEVIMR_DMA_1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_1;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_1;
	}
}

static inline void hri_usbhs_clear_DEVIMR_DMA_1_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_1;
}

static inline void hri_usbhs_set_DEVIMR_DMA_2_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_2;
}

static inline bool hri_usbhs_get_DEVIMR_DMA_2_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_DMA_2) >> USBHS_DEVIMR_DMA_2_Pos;
}

static inline void hri_usbhs_write_DEVIMR_DMA_2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_2;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_2;
	}
}

static inline void hri_usbhs_clear_DEVIMR_DMA_2_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_2;
}

static inline void hri_usbhs_set_DEVIMR_DMA_3_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_3;
}

static inline bool hri_usbhs_get_DEVIMR_DMA_3_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_DMA_3) >> USBHS_DEVIMR_DMA_3_Pos;
}

static inline void hri_usbhs_write_DEVIMR_DMA_3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_3;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_3;
	}
}

static inline void hri_usbhs_clear_DEVIMR_DMA_3_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_3;
}

static inline void hri_usbhs_set_DEVIMR_DMA_4_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_4;
}

static inline bool hri_usbhs_get_DEVIMR_DMA_4_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_DMA_4) >> USBHS_DEVIMR_DMA_4_Pos;
}

static inline void hri_usbhs_write_DEVIMR_DMA_4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_4;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_4;
	}
}

static inline void hri_usbhs_clear_DEVIMR_DMA_4_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_4;
}

static inline void hri_usbhs_set_DEVIMR_DMA_5_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_5;
}

static inline bool hri_usbhs_get_DEVIMR_DMA_5_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_DMA_5) >> USBHS_DEVIMR_DMA_5_Pos;
}

static inline void hri_usbhs_write_DEVIMR_DMA_5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_5;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_5;
	}
}

static inline void hri_usbhs_clear_DEVIMR_DMA_5_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_5;
}

static inline void hri_usbhs_set_DEVIMR_DMA_6_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_6;
}

static inline bool hri_usbhs_get_DEVIMR_DMA_6_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_DMA_6) >> USBHS_DEVIMR_DMA_6_Pos;
}

static inline void hri_usbhs_write_DEVIMR_DMA_6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_6;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_6;
	}
}

static inline void hri_usbhs_clear_DEVIMR_DMA_6_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_6;
}

static inline void hri_usbhs_set_DEVIMR_DMA_7_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_7;
}

static inline bool hri_usbhs_get_DEVIMR_DMA_7_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVIMR & USBHS_DEVIMR_DMA_7) >> USBHS_DEVIMR_DMA_7_Pos;
}

static inline void hri_usbhs_write_DEVIMR_DMA_7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_7;
	} else {
		((Usbhs *)hw)->USBHS_DEVIER = USBHS_DEVIMR_DMA_7;
	}
}

static inline void hri_usbhs_clear_DEVIMR_DMA_7_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_DEVIDR = USBHS_DEVIMR_DMA_7;
}

static inline void hri_usbhs_set_DEVIMR_reg(const void *const hw, hri_usbhs_devimr_reg_t mask)
{
	((Usbhs *)hw)->USBHS_DEVIER = mask;
}

static inline hri_usbhs_devimr_reg_t hri_usbhs_get_DEVIMR_reg(const void *const hw, hri_usbhs_devimr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVIMR;
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_devimr_reg_t hri_usbhs_read_DEVIMR_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_DEVIMR;
}

static inline void hri_usbhs_write_DEVIMR_reg(const void *const hw, hri_usbhs_devimr_reg_t data)
{
	((Usbhs *)hw)->USBHS_DEVIER = data;
	((Usbhs *)hw)->USBHS_DEVIDR = ~data;
}

static inline void hri_usbhs_clear_DEVIMR_reg(const void *const hw, hri_usbhs_devimr_reg_t mask)
{
	((Usbhs *)hw)->USBHS_DEVIDR = mask;
}

static inline void hri_usbhs_set_HSTIMR_DCONNIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DCONNIE;
}

static inline bool hri_usbhs_get_HSTIMR_DCONNIE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_DCONNIE) >> USBHS_HSTIMR_DCONNIE_Pos;
}

static inline void hri_usbhs_write_HSTIMR_DCONNIE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DCONNIE;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DCONNIE;
	}
}

static inline void hri_usbhs_clear_HSTIMR_DCONNIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DCONNIE;
}

static inline void hri_usbhs_set_HSTIMR_DDISCIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DDISCIE;
}

static inline bool hri_usbhs_get_HSTIMR_DDISCIE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_DDISCIE) >> USBHS_HSTIMR_DDISCIE_Pos;
}

static inline void hri_usbhs_write_HSTIMR_DDISCIE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DDISCIE;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DDISCIE;
	}
}

static inline void hri_usbhs_clear_HSTIMR_DDISCIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DDISCIE;
}

static inline void hri_usbhs_set_HSTIMR_RSTIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_RSTIE;
}

static inline bool hri_usbhs_get_HSTIMR_RSTIE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_RSTIE) >> USBHS_HSTIMR_RSTIE_Pos;
}

static inline void hri_usbhs_write_HSTIMR_RSTIE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_RSTIE;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_RSTIE;
	}
}

static inline void hri_usbhs_clear_HSTIMR_RSTIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_RSTIE;
}

static inline void hri_usbhs_set_HSTIMR_RSMEDIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_RSMEDIE;
}

static inline bool hri_usbhs_get_HSTIMR_RSMEDIE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_RSMEDIE) >> USBHS_HSTIMR_RSMEDIE_Pos;
}

static inline void hri_usbhs_write_HSTIMR_RSMEDIE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_RSMEDIE;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_RSMEDIE;
	}
}

static inline void hri_usbhs_clear_HSTIMR_RSMEDIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_RSMEDIE;
}

static inline void hri_usbhs_set_HSTIMR_RXRSMIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_RXRSMIE;
}

static inline bool hri_usbhs_get_HSTIMR_RXRSMIE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_RXRSMIE) >> USBHS_HSTIMR_RXRSMIE_Pos;
}

static inline void hri_usbhs_write_HSTIMR_RXRSMIE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_RXRSMIE;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_RXRSMIE;
	}
}

static inline void hri_usbhs_clear_HSTIMR_RXRSMIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_RXRSMIE;
}

static inline void hri_usbhs_set_HSTIMR_HSOFIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_HSOFIE;
}

static inline bool hri_usbhs_get_HSTIMR_HSOFIE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_HSOFIE) >> USBHS_HSTIMR_HSOFIE_Pos;
}

static inline void hri_usbhs_write_HSTIMR_HSOFIE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_HSOFIE;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_HSOFIE;
	}
}

static inline void hri_usbhs_clear_HSTIMR_HSOFIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_HSOFIE;
}

static inline void hri_usbhs_set_HSTIMR_HWUPIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_HWUPIE;
}

static inline bool hri_usbhs_get_HSTIMR_HWUPIE_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_HWUPIE) >> USBHS_HSTIMR_HWUPIE_Pos;
}

static inline void hri_usbhs_write_HSTIMR_HWUPIE_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_HWUPIE;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_HWUPIE;
	}
}

static inline void hri_usbhs_clear_HSTIMR_HWUPIE_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_HWUPIE;
}

static inline void hri_usbhs_set_HSTIMR_PEP_0_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_0;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_0_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_0) >> USBHS_HSTIMR_PEP_0_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_0;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_0;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_0_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_0;
}

static inline void hri_usbhs_set_HSTIMR_PEP_1_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_1;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_1_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_1) >> USBHS_HSTIMR_PEP_1_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_1;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_1;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_1_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_1;
}

static inline void hri_usbhs_set_HSTIMR_PEP_2_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_2;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_2_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_2) >> USBHS_HSTIMR_PEP_2_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_2;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_2;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_2_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_2;
}

static inline void hri_usbhs_set_HSTIMR_PEP_3_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_3;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_3_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_3) >> USBHS_HSTIMR_PEP_3_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_3;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_3;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_3_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_3;
}

static inline void hri_usbhs_set_HSTIMR_PEP_4_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_4;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_4_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_4) >> USBHS_HSTIMR_PEP_4_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_4;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_4;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_4_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_4;
}

static inline void hri_usbhs_set_HSTIMR_PEP_5_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_5;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_5_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_5) >> USBHS_HSTIMR_PEP_5_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_5;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_5;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_5_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_5;
}

static inline void hri_usbhs_set_HSTIMR_PEP_6_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_6;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_6_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_6) >> USBHS_HSTIMR_PEP_6_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_6;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_6;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_6_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_6;
}

static inline void hri_usbhs_set_HSTIMR_PEP_7_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_7;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_7_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_7) >> USBHS_HSTIMR_PEP_7_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_7;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_7;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_7_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_7;
}

static inline void hri_usbhs_set_HSTIMR_PEP_8_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_8;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_8_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_8) >> USBHS_HSTIMR_PEP_8_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_8;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_8;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_8_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_8;
}

static inline void hri_usbhs_set_HSTIMR_PEP_9_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_9;
}

static inline bool hri_usbhs_get_HSTIMR_PEP_9_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_PEP_9) >> USBHS_HSTIMR_PEP_9_Pos;
}

static inline void hri_usbhs_write_HSTIMR_PEP_9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_9;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_PEP_9;
	}
}

static inline void hri_usbhs_clear_HSTIMR_PEP_9_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_PEP_9;
}

static inline void hri_usbhs_set_HSTIMR_DMA_0_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_0;
}

static inline bool hri_usbhs_get_HSTIMR_DMA_0_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_DMA_0) >> USBHS_HSTIMR_DMA_0_Pos;
}

static inline void hri_usbhs_write_HSTIMR_DMA_0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_0;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_0;
	}
}

static inline void hri_usbhs_clear_HSTIMR_DMA_0_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_0;
}

static inline void hri_usbhs_set_HSTIMR_DMA_1_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_1;
}

static inline bool hri_usbhs_get_HSTIMR_DMA_1_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_DMA_1) >> USBHS_HSTIMR_DMA_1_Pos;
}

static inline void hri_usbhs_write_HSTIMR_DMA_1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_1;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_1;
	}
}

static inline void hri_usbhs_clear_HSTIMR_DMA_1_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_1;
}

static inline void hri_usbhs_set_HSTIMR_DMA_2_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_2;
}

static inline bool hri_usbhs_get_HSTIMR_DMA_2_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_DMA_2) >> USBHS_HSTIMR_DMA_2_Pos;
}

static inline void hri_usbhs_write_HSTIMR_DMA_2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_2;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_2;
	}
}

static inline void hri_usbhs_clear_HSTIMR_DMA_2_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_2;
}

static inline void hri_usbhs_set_HSTIMR_DMA_3_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_3;
}

static inline bool hri_usbhs_get_HSTIMR_DMA_3_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_DMA_3) >> USBHS_HSTIMR_DMA_3_Pos;
}

static inline void hri_usbhs_write_HSTIMR_DMA_3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_3;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_3;
	}
}

static inline void hri_usbhs_clear_HSTIMR_DMA_3_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_3;
}

static inline void hri_usbhs_set_HSTIMR_DMA_4_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_4;
}

static inline bool hri_usbhs_get_HSTIMR_DMA_4_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_DMA_4) >> USBHS_HSTIMR_DMA_4_Pos;
}

static inline void hri_usbhs_write_HSTIMR_DMA_4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_4;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_4;
	}
}

static inline void hri_usbhs_clear_HSTIMR_DMA_4_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_4;
}

static inline void hri_usbhs_set_HSTIMR_DMA_5_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_5;
}

static inline bool hri_usbhs_get_HSTIMR_DMA_5_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_DMA_5) >> USBHS_HSTIMR_DMA_5_Pos;
}

static inline void hri_usbhs_write_HSTIMR_DMA_5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_5;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_5;
	}
}

static inline void hri_usbhs_clear_HSTIMR_DMA_5_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_5;
}

static inline void hri_usbhs_set_HSTIMR_DMA_6_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_6;
}

static inline bool hri_usbhs_get_HSTIMR_DMA_6_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTIMR & USBHS_HSTIMR_DMA_6) >> USBHS_HSTIMR_DMA_6_Pos;
}

static inline void hri_usbhs_write_HSTIMR_DMA_6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_6;
	} else {
		((Usbhs *)hw)->USBHS_HSTIER = USBHS_HSTIMR_DMA_6;
	}
}

static inline void hri_usbhs_clear_HSTIMR_DMA_6_bit(const void *const hw)
{
	((Usbhs *)hw)->USBHS_HSTIDR = USBHS_HSTIMR_DMA_6;
}

static inline void hri_usbhs_set_HSTIMR_reg(const void *const hw, hri_usbhs_hstimr_reg_t mask)
{
	((Usbhs *)hw)->USBHS_HSTIER = mask;
}

static inline hri_usbhs_hstimr_reg_t hri_usbhs_get_HSTIMR_reg(const void *const hw, hri_usbhs_hstimr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTIMR;
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_hstimr_reg_t hri_usbhs_read_HSTIMR_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_HSTIMR;
}

static inline void hri_usbhs_write_HSTIMR_reg(const void *const hw, hri_usbhs_hstimr_reg_t data)
{
	((Usbhs *)hw)->USBHS_HSTIER = data;
	((Usbhs *)hw)->USBHS_HSTIDR = ~data;
}

static inline void hri_usbhs_clear_HSTIMR_reg(const void *const hw, hri_usbhs_hstimr_reg_t mask)
{
	((Usbhs *)hw)->USBHS_HSTIDR = mask;
}

static inline bool hri_usbhs_get_DEVISR_SUSP_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_SUSP) > 0;
}

static inline bool hri_usbhs_get_DEVISR_MSOF_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_MSOF) > 0;
}

static inline bool hri_usbhs_get_DEVISR_SOF_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_SOF) > 0;
}

static inline bool hri_usbhs_get_DEVISR_EORST_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_EORST) > 0;
}

static inline bool hri_usbhs_get_DEVISR_WAKEUP_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_WAKEUP) > 0;
}

static inline bool hri_usbhs_get_DEVISR_EORSM_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_EORSM) > 0;
}

static inline bool hri_usbhs_get_DEVISR_UPRSM_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_UPRSM) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_0_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_0) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_1_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_1) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_2_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_2) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_3_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_3) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_4_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_4) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_5_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_5) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_6_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_6) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_7_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_7) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_8_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_8) > 0;
}

static inline bool hri_usbhs_get_DEVISR_PEP_9_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_PEP_9) > 0;
}

static inline bool hri_usbhs_get_DEVISR_DMA_1_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_DMA_1) > 0;
}

static inline bool hri_usbhs_get_DEVISR_DMA_2_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_DMA_2) > 0;
}

static inline bool hri_usbhs_get_DEVISR_DMA_3_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_DMA_3) > 0;
}

static inline bool hri_usbhs_get_DEVISR_DMA_4_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_DMA_4) > 0;
}

static inline bool hri_usbhs_get_DEVISR_DMA_5_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_DMA_5) > 0;
}

static inline bool hri_usbhs_get_DEVISR_DMA_6_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_DMA_6) > 0;
}

static inline bool hri_usbhs_get_DEVISR_DMA_7_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVISR & USBHS_DEVISR_DMA_7) > 0;
}

static inline hri_usbhs_devisr_reg_t hri_usbhs_get_DEVISR_reg(const void *const hw, hri_usbhs_devisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVISR;
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_devisr_reg_t hri_usbhs_read_DEVISR_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_DEVISR;
}

static inline bool hri_usbhs_get_DEVFNUM_FNCERR_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVFNUM & USBHS_DEVFNUM_FNCERR) > 0;
}

static inline hri_usbhs_devfnum_reg_t hri_usbhs_get_DEVFNUM_MFNUM_bf(const void *const hw, hri_usbhs_devfnum_reg_t mask)
{
	return (((Usbhs *)hw)->USBHS_DEVFNUM & USBHS_DEVFNUM_MFNUM(mask)) >> USBHS_DEVFNUM_MFNUM_Pos;
}

static inline hri_usbhs_devfnum_reg_t hri_usbhs_read_DEVFNUM_MFNUM_bf(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVFNUM & USBHS_DEVFNUM_MFNUM_Msk) >> USBHS_DEVFNUM_MFNUM_Pos;
}

static inline hri_usbhs_devfnum_reg_t hri_usbhs_get_DEVFNUM_FNUM_bf(const void *const hw, hri_usbhs_devfnum_reg_t mask)
{
	return (((Usbhs *)hw)->USBHS_DEVFNUM & USBHS_DEVFNUM_FNUM(mask)) >> USBHS_DEVFNUM_FNUM_Pos;
}

static inline hri_usbhs_devfnum_reg_t hri_usbhs_read_DEVFNUM_FNUM_bf(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_DEVFNUM & USBHS_DEVFNUM_FNUM_Msk) >> USBHS_DEVFNUM_FNUM_Pos;
}

static inline hri_usbhs_devfnum_reg_t hri_usbhs_get_DEVFNUM_reg(const void *const hw, hri_usbhs_devfnum_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVFNUM;
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_devfnum_reg_t hri_usbhs_read_DEVFNUM_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_DEVFNUM;
}

static inline bool hri_usbhs_get_DEVEPTIMR_TXINE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_TXINE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_RXOUTE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_RXOUTE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_CTRL_RXSTPE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_CTRL_RXSTPE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_BLK_RXSTPE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_BLK_RXSTPE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_INTRPT_RXSTPE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_INTRPT_RXSTPE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_ISO_UNDERFE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_ISO_UNDERFE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_CTRL_NAKOUTE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_CTRL_NAKOUTE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_BLK_NAKOUTE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_BLK_NAKOUTE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_INTRPT_NAKOUTE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_INTRPT_NAKOUTE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_ISO_HBISOINERRE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_ISO_HBISOINERRE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_CTRL_NAKINE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_CTRL_NAKINE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_BLK_NAKINE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_BLK_NAKINE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_INTRPT_NAKINE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_INTRPT_NAKINE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_ISO_HBISOFLUSHE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_ISO_HBISOFLUSHE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_OVERFE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_OVERFE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_CTRL_STALLEDE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_CTRL_STALLEDE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_BLK_STALLEDE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_BLK_STALLEDE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_INTRPT_STALLEDE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_INTRPT_STALLEDE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_ISO_CRCERRE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_ISO_CRCERRE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_SHORTPACKETE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_SHORTPACKETE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_ISO_MDATAE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_ISO_MDATAE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_ISO_DATAXE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_ISO_DATAXE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_ISO_ERRORTRANSE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_ISO_ERRORTRANSE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_NBUSYBKE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_NBUSYBKE) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_KILLBK_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_KILLBK) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_FIFOCON_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_FIFOCON) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_EPDISHDMA_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_EPDISHDMA) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_CTRL_NYETDIS_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_CTRL_NYETDIS) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_BLK_NYETDIS_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_BLK_NYETDIS) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_INTRPT_NYETDIS_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_INTRPT_NYETDIS) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_RSTDT_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_RSTDT) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_CTRL_STALLRQ_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_CTRL_STALLRQ) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_BLK_STALLRQ_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_BLK_STALLRQ) > 0;
}

static inline bool hri_usbhs_get_DEVEPTIMR_INTRPT_STALLRQ_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_DEVEPTIMR[index] & USBHS_DEVEPTIMR_INTRPT_STALLRQ) > 0;
}

static inline hri_usbhs_deveptimr_reg_t hri_usbhs_get_DEVEPTIMR_reg(const void *const hw, uint8_t index,
                                                                    hri_usbhs_deveptimr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTIMR[index];
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_deveptimr_reg_t hri_usbhs_read_DEVEPTIMR_reg(const void *const hw, uint8_t index)
{
	return ((Usbhs *)hw)->USBHS_DEVEPTIMR[index];
}

static inline bool hri_usbhs_get_HSTISR_DCONNI_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_DCONNI) > 0;
}

static inline bool hri_usbhs_get_HSTISR_DDISCI_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_DDISCI) > 0;
}

static inline bool hri_usbhs_get_HSTISR_RSTI_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_RSTI) > 0;
}

static inline bool hri_usbhs_get_HSTISR_RSMEDI_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_RSMEDI) > 0;
}

static inline bool hri_usbhs_get_HSTISR_RXRSMI_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_RXRSMI) > 0;
}

static inline bool hri_usbhs_get_HSTISR_HSOFI_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_HSOFI) > 0;
}

static inline bool hri_usbhs_get_HSTISR_HWUPI_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_HWUPI) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_0_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_0) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_1_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_1) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_2_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_2) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_3_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_3) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_4_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_4) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_5_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_5) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_6_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_6) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_7_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_7) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_8_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_8) > 0;
}

static inline bool hri_usbhs_get_HSTISR_PEP_9_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_PEP_9) > 0;
}

static inline bool hri_usbhs_get_HSTISR_DMA_0_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_DMA_0) > 0;
}

static inline bool hri_usbhs_get_HSTISR_DMA_1_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_DMA_1) > 0;
}

static inline bool hri_usbhs_get_HSTISR_DMA_2_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_DMA_2) > 0;
}

static inline bool hri_usbhs_get_HSTISR_DMA_3_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_DMA_3) > 0;
}

static inline bool hri_usbhs_get_HSTISR_DMA_4_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_DMA_4) > 0;
}

static inline bool hri_usbhs_get_HSTISR_DMA_5_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_DMA_5) > 0;
}

static inline bool hri_usbhs_get_HSTISR_DMA_6_bit(const void *const hw)
{
	return (((Usbhs *)hw)->USBHS_HSTISR & USBHS_HSTISR_DMA_6) > 0;
}

static inline hri_usbhs_hstisr_reg_t hri_usbhs_get_HSTISR_reg(const void *const hw, hri_usbhs_hstisr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTISR;
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_hstisr_reg_t hri_usbhs_read_HSTISR_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_HSTISR;
}

static inline bool hri_usbhs_get_HSTPIPIMR_RXINE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_RXINE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_TXOUTE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_TXOUTE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_CTRL_TXSTPE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_CTRL_TXSTPE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_BLK_TXSTPE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_BLK_TXSTPE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_ISO_UNDERFIE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_ISO_UNDERFIE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_INTRPT_UNDERFIE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_INTRPT_UNDERFIE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_PERRE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_PERRE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_NAKEDE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_NAKEDE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_OVERFIE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_OVERFIE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_CTRL_RXSTALLDE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_CTRL_RXSTALLDE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_BLK_RXSTALLDE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_BLK_RXSTALLDE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_INTRPT_RXSTALLDE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_INTRPT_RXSTALLDE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_ISO_CRCERRE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_ISO_CRCERRE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_SHORTPACKETIE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_SHORTPACKETIE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_NBUSYBKE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_NBUSYBKE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_FIFOCON_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_FIFOCON) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_PDISHDMA_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_PDISHDMA) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_PFREEZE_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_PFREEZE) > 0;
}

static inline bool hri_usbhs_get_HSTPIPIMR_RSTDT_bit(const void *const hw, uint8_t index)
{
	return (((Usbhs *)hw)->USBHS_HSTPIPIMR[index] & USBHS_HSTPIPIMR_RSTDT) > 0;
}

static inline hri_usbhs_hstpipimr_reg_t hri_usbhs_get_HSTPIPIMR_reg(const void *const hw, uint8_t index,
                                                                    hri_usbhs_hstpipimr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPIMR[index];
	tmp &= mask;
	return tmp;
}

static inline hri_usbhs_hstpipimr_reg_t hri_usbhs_read_HSTPIPIMR_reg(const void *const hw, uint8_t index)
{
	return ((Usbhs *)hw)->USBHS_HSTPIPIMR[index];
}

static inline void hri_usbhs_set_DEVCTRL_ADDEN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_ADDEN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVCTRL_ADDEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_ADDEN) >> USBHS_DEVCTRL_ADDEN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVCTRL_ADDEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_ADDEN;
	tmp |= value << USBHS_DEVCTRL_ADDEN_Pos;
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_ADDEN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_ADDEN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_ADDEN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_ADDEN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVCTRL_DETACH_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_DETACH;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVCTRL_DETACH_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_DETACH) >> USBHS_DEVCTRL_DETACH_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVCTRL_DETACH_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_DETACH;
	tmp |= value << USBHS_DEVCTRL_DETACH_Pos;
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_DETACH_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_DETACH;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_DETACH_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_DETACH;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVCTRL_RMWKUP_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_RMWKUP;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVCTRL_RMWKUP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_RMWKUP) >> USBHS_DEVCTRL_RMWKUP_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVCTRL_RMWKUP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_RMWKUP;
	tmp |= value << USBHS_DEVCTRL_RMWKUP_Pos;
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_RMWKUP_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_RMWKUP;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_RMWKUP_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_RMWKUP;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVCTRL_LS_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_LS;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVCTRL_LS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_LS) >> USBHS_DEVCTRL_LS_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVCTRL_LS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_LS;
	tmp |= value << USBHS_DEVCTRL_LS_Pos;
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_LS_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_LS;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_LS_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_LS;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVCTRL_TSTJ_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_TSTJ;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVCTRL_TSTJ_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_TSTJ) >> USBHS_DEVCTRL_TSTJ_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVCTRL_TSTJ_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_TSTJ;
	tmp |= value << USBHS_DEVCTRL_TSTJ_Pos;
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_TSTJ_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_TSTJ;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_TSTJ_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_TSTJ;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVCTRL_TSTK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_TSTK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVCTRL_TSTK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_TSTK) >> USBHS_DEVCTRL_TSTK_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVCTRL_TSTK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_TSTK;
	tmp |= value << USBHS_DEVCTRL_TSTK_Pos;
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_TSTK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_TSTK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_TSTK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_TSTK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVCTRL_TSTPCKT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_TSTPCKT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVCTRL_TSTPCKT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_TSTPCKT) >> USBHS_DEVCTRL_TSTPCKT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVCTRL_TSTPCKT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_TSTPCKT;
	tmp |= value << USBHS_DEVCTRL_TSTPCKT_Pos;
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_TSTPCKT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_TSTPCKT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_TSTPCKT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_TSTPCKT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVCTRL_OPMODE2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_OPMODE2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVCTRL_OPMODE2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_OPMODE2) >> USBHS_DEVCTRL_OPMODE2_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVCTRL_OPMODE2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_OPMODE2;
	tmp |= value << USBHS_DEVCTRL_OPMODE2_Pos;
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_OPMODE2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_OPMODE2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_OPMODE2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_OPMODE2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVCTRL_UADD_bf(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_UADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devctrl_reg_t hri_usbhs_get_DEVCTRL_UADD_bf(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_UADD(mask)) >> USBHS_DEVCTRL_UADD_Pos;
	return tmp;
}

static inline void hri_usbhs_write_DEVCTRL_UADD_bf(const void *const hw, hri_usbhs_devctrl_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_UADD_Msk;
	tmp |= USBHS_DEVCTRL_UADD(data);
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_UADD_bf(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_UADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_UADD_bf(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_UADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devctrl_reg_t hri_usbhs_read_DEVCTRL_UADD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_UADD_Msk) >> USBHS_DEVCTRL_UADD_Pos;
	return tmp;
}

static inline void hri_usbhs_set_DEVCTRL_SPDCONF_bf(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= USBHS_DEVCTRL_SPDCONF(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devctrl_reg_t hri_usbhs_get_DEVCTRL_SPDCONF_bf(const void *const       hw,
                                                                       hri_usbhs_devctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_SPDCONF(mask)) >> USBHS_DEVCTRL_SPDCONF_Pos;
	return tmp;
}

static inline void hri_usbhs_write_DEVCTRL_SPDCONF_bf(const void *const hw, hri_usbhs_devctrl_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= ~USBHS_DEVCTRL_SPDCONF_Msk;
	tmp |= USBHS_DEVCTRL_SPDCONF(data);
	((Usbhs *)hw)->USBHS_DEVCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_SPDCONF_bf(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~USBHS_DEVCTRL_SPDCONF(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_SPDCONF_bf(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= USBHS_DEVCTRL_SPDCONF(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devctrl_reg_t hri_usbhs_read_DEVCTRL_SPDCONF_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp = (tmp & USBHS_DEVCTRL_SPDCONF_Msk) >> USBHS_DEVCTRL_SPDCONF_Pos;
	return tmp;
}

static inline void hri_usbhs_set_DEVCTRL_reg(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devctrl_reg_t hri_usbhs_get_DEVCTRL_reg(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVCTRL;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_DEVCTRL_reg(const void *const hw, hri_usbhs_devctrl_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVCTRL_reg(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVCTRL_reg(const void *const hw, hri_usbhs_devctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVCTRL ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devctrl_reg_t hri_usbhs_read_DEVCTRL_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_DEVCTRL;
}

static inline void hri_usbhs_set_DEVEPT_EPEN0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN0) >> USBHS_DEVEPT_EPEN0_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN0;
	tmp |= value << USBHS_DEVEPT_EPEN0_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPEN1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN1) >> USBHS_DEVEPT_EPEN1_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN1;
	tmp |= value << USBHS_DEVEPT_EPEN1_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPEN2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN2) >> USBHS_DEVEPT_EPEN2_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN2;
	tmp |= value << USBHS_DEVEPT_EPEN2_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPEN3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN3) >> USBHS_DEVEPT_EPEN3_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN3;
	tmp |= value << USBHS_DEVEPT_EPEN3_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPEN4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN4) >> USBHS_DEVEPT_EPEN4_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN4;
	tmp |= value << USBHS_DEVEPT_EPEN4_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPEN5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN5) >> USBHS_DEVEPT_EPEN5_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN5;
	tmp |= value << USBHS_DEVEPT_EPEN5_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPEN6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN6) >> USBHS_DEVEPT_EPEN6_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN6;
	tmp |= value << USBHS_DEVEPT_EPEN6_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPEN7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN7) >> USBHS_DEVEPT_EPEN7_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN7;
	tmp |= value << USBHS_DEVEPT_EPEN7_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPEN8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN8) >> USBHS_DEVEPT_EPEN8_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN8;
	tmp |= value << USBHS_DEVEPT_EPEN8_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPEN9_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPEN9;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPEN9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPEN9) >> USBHS_DEVEPT_EPEN9_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPEN9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPEN9;
	tmp |= value << USBHS_DEVEPT_EPEN9_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPEN9_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPEN9;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPEN9_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPEN9;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST0) >> USBHS_DEVEPT_EPRST0_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST0;
	tmp |= value << USBHS_DEVEPT_EPRST0_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST1) >> USBHS_DEVEPT_EPRST1_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST1;
	tmp |= value << USBHS_DEVEPT_EPRST1_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST2) >> USBHS_DEVEPT_EPRST2_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST2;
	tmp |= value << USBHS_DEVEPT_EPRST2_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST3) >> USBHS_DEVEPT_EPRST3_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST3;
	tmp |= value << USBHS_DEVEPT_EPRST3_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST4) >> USBHS_DEVEPT_EPRST4_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST4;
	tmp |= value << USBHS_DEVEPT_EPRST4_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST5) >> USBHS_DEVEPT_EPRST5_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST5;
	tmp |= value << USBHS_DEVEPT_EPRST5_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST6) >> USBHS_DEVEPT_EPRST6_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST6;
	tmp |= value << USBHS_DEVEPT_EPRST6_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST7) >> USBHS_DEVEPT_EPRST7_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST7;
	tmp |= value << USBHS_DEVEPT_EPRST7_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST8) >> USBHS_DEVEPT_EPRST8_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST8;
	tmp |= value << USBHS_DEVEPT_EPRST8_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_EPRST9_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST9;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPT_EPRST9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp = (tmp & USBHS_DEVEPT_EPRST9) >> USBHS_DEVEPT_EPRST9_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPT_EPRST9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= ~USBHS_DEVEPT_EPRST9;
	tmp |= value << USBHS_DEVEPT_EPRST9_Pos;
	((Usbhs *)hw)->USBHS_DEVEPT = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_EPRST9_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~USBHS_DEVEPT_EPRST9;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_EPRST9_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= USBHS_DEVEPT_EPRST9;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPT_reg(const void *const hw, hri_usbhs_devept_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devept_reg_t hri_usbhs_get_DEVEPT_reg(const void *const hw, hri_usbhs_devept_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPT;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_DEVEPT_reg(const void *const hw, hri_usbhs_devept_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPT_reg(const void *const hw, hri_usbhs_devept_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPT_reg(const void *const hw, hri_usbhs_devept_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPT ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devept_reg_t hri_usbhs_read_DEVEPT_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_DEVEPT;
}

static inline void hri_usbhs_set_DEVEPTCFG_ALLOC_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] |= USBHS_DEVEPTCFG_ALLOC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPTCFG_ALLOC_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_ALLOC) >> USBHS_DEVEPTCFG_ALLOC_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPTCFG_ALLOC_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp &= ~USBHS_DEVEPTCFG_ALLOC;
	tmp |= value << USBHS_DEVEPTCFG_ALLOC_Pos;
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPTCFG_ALLOC_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] &= ~USBHS_DEVEPTCFG_ALLOC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPTCFG_ALLOC_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] ^= USBHS_DEVEPTCFG_ALLOC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPTCFG_EPDIR_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] |= USBHS_DEVEPTCFG_EPDIR;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPTCFG_EPDIR_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_EPDIR) >> USBHS_DEVEPTCFG_EPDIR_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPTCFG_EPDIR_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp &= ~USBHS_DEVEPTCFG_EPDIR;
	tmp |= value << USBHS_DEVEPTCFG_EPDIR_Pos;
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPTCFG_EPDIR_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] &= ~USBHS_DEVEPTCFG_EPDIR;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPTCFG_EPDIR_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] ^= USBHS_DEVEPTCFG_EPDIR;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPTCFG_AUTOSW_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] |= USBHS_DEVEPTCFG_AUTOSW;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVEPTCFG_AUTOSW_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_AUTOSW) >> USBHS_DEVEPTCFG_AUTOSW_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVEPTCFG_AUTOSW_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp &= ~USBHS_DEVEPTCFG_AUTOSW;
	tmp |= value << USBHS_DEVEPTCFG_AUTOSW_Pos;
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPTCFG_AUTOSW_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] &= ~USBHS_DEVEPTCFG_AUTOSW;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPTCFG_AUTOSW_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] ^= USBHS_DEVEPTCFG_AUTOSW;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVEPTCFG_EPBK_bf(const void *const hw, uint8_t index, hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] |= USBHS_DEVEPTCFG_EPBK(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_get_DEVEPTCFG_EPBK_bf(const void *const hw, uint8_t index,
                                                                        hri_usbhs_deveptcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_EPBK(mask)) >> USBHS_DEVEPTCFG_EPBK_Pos;
	return tmp;
}

static inline void hri_usbhs_write_DEVEPTCFG_EPBK_bf(const void *const hw, uint8_t index,
                                                     hri_usbhs_deveptcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp &= ~USBHS_DEVEPTCFG_EPBK_Msk;
	tmp |= USBHS_DEVEPTCFG_EPBK(data);
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPTCFG_EPBK_bf(const void *const hw, uint8_t index,
                                                     hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] &= ~USBHS_DEVEPTCFG_EPBK(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPTCFG_EPBK_bf(const void *const hw, uint8_t index,
                                                      hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] ^= USBHS_DEVEPTCFG_EPBK(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_read_DEVEPTCFG_EPBK_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_EPBK_Msk) >> USBHS_DEVEPTCFG_EPBK_Pos;
	return tmp;
}

static inline void hri_usbhs_set_DEVEPTCFG_EPSIZE_bf(const void *const hw, uint8_t index,
                                                     hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] |= USBHS_DEVEPTCFG_EPSIZE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_get_DEVEPTCFG_EPSIZE_bf(const void *const hw, uint8_t index,
                                                                          hri_usbhs_deveptcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_EPSIZE(mask)) >> USBHS_DEVEPTCFG_EPSIZE_Pos;
	return tmp;
}

static inline void hri_usbhs_write_DEVEPTCFG_EPSIZE_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_deveptcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp &= ~USBHS_DEVEPTCFG_EPSIZE_Msk;
	tmp |= USBHS_DEVEPTCFG_EPSIZE(data);
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPTCFG_EPSIZE_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] &= ~USBHS_DEVEPTCFG_EPSIZE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPTCFG_EPSIZE_bf(const void *const hw, uint8_t index,
                                                        hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] ^= USBHS_DEVEPTCFG_EPSIZE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_read_DEVEPTCFG_EPSIZE_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_EPSIZE_Msk) >> USBHS_DEVEPTCFG_EPSIZE_Pos;
	return tmp;
}

static inline void hri_usbhs_set_DEVEPTCFG_EPTYPE_bf(const void *const hw, uint8_t index,
                                                     hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] |= USBHS_DEVEPTCFG_EPTYPE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_get_DEVEPTCFG_EPTYPE_bf(const void *const hw, uint8_t index,
                                                                          hri_usbhs_deveptcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_EPTYPE(mask)) >> USBHS_DEVEPTCFG_EPTYPE_Pos;
	return tmp;
}

static inline void hri_usbhs_write_DEVEPTCFG_EPTYPE_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_deveptcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp &= ~USBHS_DEVEPTCFG_EPTYPE_Msk;
	tmp |= USBHS_DEVEPTCFG_EPTYPE(data);
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPTCFG_EPTYPE_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] &= ~USBHS_DEVEPTCFG_EPTYPE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPTCFG_EPTYPE_bf(const void *const hw, uint8_t index,
                                                        hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] ^= USBHS_DEVEPTCFG_EPTYPE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_read_DEVEPTCFG_EPTYPE_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_EPTYPE_Msk) >> USBHS_DEVEPTCFG_EPTYPE_Pos;
	return tmp;
}

static inline void hri_usbhs_set_DEVEPTCFG_NBTRANS_bf(const void *const hw, uint8_t index,
                                                      hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] |= USBHS_DEVEPTCFG_NBTRANS(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_get_DEVEPTCFG_NBTRANS_bf(const void *const hw, uint8_t index,
                                                                           hri_usbhs_deveptcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_NBTRANS(mask)) >> USBHS_DEVEPTCFG_NBTRANS_Pos;
	return tmp;
}

static inline void hri_usbhs_write_DEVEPTCFG_NBTRANS_bf(const void *const hw, uint8_t index,
                                                        hri_usbhs_deveptcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp &= ~USBHS_DEVEPTCFG_NBTRANS_Msk;
	tmp |= USBHS_DEVEPTCFG_NBTRANS(data);
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPTCFG_NBTRANS_bf(const void *const hw, uint8_t index,
                                                        hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] &= ~USBHS_DEVEPTCFG_NBTRANS(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPTCFG_NBTRANS_bf(const void *const hw, uint8_t index,
                                                         hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] ^= USBHS_DEVEPTCFG_NBTRANS(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_read_DEVEPTCFG_NBTRANS_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp = (tmp & USBHS_DEVEPTCFG_NBTRANS_Msk) >> USBHS_DEVEPTCFG_NBTRANS_Pos;
	return tmp;
}

static inline void hri_usbhs_set_DEVEPTCFG_reg(const void *const hw, uint8_t index, hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_get_DEVEPTCFG_reg(const void *const hw, uint8_t index,
                                                                    hri_usbhs_deveptcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_DEVEPTCFG_reg(const void *const hw, uint8_t index, hri_usbhs_deveptcfg_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVEPTCFG_reg(const void *const hw, uint8_t index, hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVEPTCFG_reg(const void *const hw, uint8_t index, hri_usbhs_deveptcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTCFG[index] ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_deveptcfg_reg_t hri_usbhs_read_DEVEPTCFG_reg(const void *const hw, uint8_t index)
{
	return ((Usbhs *)hw)->USBHS_DEVEPTCFG[index];
}

static inline void hri_usbhs_set_HSTCTRL_SOFE_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL |= USBHS_HSTCTRL_SOFE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTCTRL_SOFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp = (tmp & USBHS_HSTCTRL_SOFE) >> USBHS_HSTCTRL_SOFE_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTCTRL_SOFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp &= ~USBHS_HSTCTRL_SOFE;
	tmp |= value << USBHS_HSTCTRL_SOFE_Pos;
	((Usbhs *)hw)->USBHS_HSTCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTCTRL_SOFE_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL &= ~USBHS_HSTCTRL_SOFE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTCTRL_SOFE_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL ^= USBHS_HSTCTRL_SOFE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTCTRL_RESET_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL |= USBHS_HSTCTRL_RESET;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTCTRL_RESET_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp = (tmp & USBHS_HSTCTRL_RESET) >> USBHS_HSTCTRL_RESET_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTCTRL_RESET_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp &= ~USBHS_HSTCTRL_RESET;
	tmp |= value << USBHS_HSTCTRL_RESET_Pos;
	((Usbhs *)hw)->USBHS_HSTCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTCTRL_RESET_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL &= ~USBHS_HSTCTRL_RESET;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTCTRL_RESET_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL ^= USBHS_HSTCTRL_RESET;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTCTRL_RESUME_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL |= USBHS_HSTCTRL_RESUME;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTCTRL_RESUME_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp = (tmp & USBHS_HSTCTRL_RESUME) >> USBHS_HSTCTRL_RESUME_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTCTRL_RESUME_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp &= ~USBHS_HSTCTRL_RESUME;
	tmp |= value << USBHS_HSTCTRL_RESUME_Pos;
	((Usbhs *)hw)->USBHS_HSTCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTCTRL_RESUME_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL &= ~USBHS_HSTCTRL_RESUME;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTCTRL_RESUME_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL ^= USBHS_HSTCTRL_RESUME;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTCTRL_SPDCONF_bf(const void *const hw, hri_usbhs_hstctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL |= USBHS_HSTCTRL_SPDCONF(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstctrl_reg_t hri_usbhs_get_HSTCTRL_SPDCONF_bf(const void *const       hw,
                                                                       hri_usbhs_hstctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp = (tmp & USBHS_HSTCTRL_SPDCONF(mask)) >> USBHS_HSTCTRL_SPDCONF_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTCTRL_SPDCONF_bf(const void *const hw, hri_usbhs_hstctrl_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp &= ~USBHS_HSTCTRL_SPDCONF_Msk;
	tmp |= USBHS_HSTCTRL_SPDCONF(data);
	((Usbhs *)hw)->USBHS_HSTCTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTCTRL_SPDCONF_bf(const void *const hw, hri_usbhs_hstctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL &= ~USBHS_HSTCTRL_SPDCONF(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTCTRL_SPDCONF_bf(const void *const hw, hri_usbhs_hstctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL ^= USBHS_HSTCTRL_SPDCONF(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstctrl_reg_t hri_usbhs_read_HSTCTRL_SPDCONF_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp = (tmp & USBHS_HSTCTRL_SPDCONF_Msk) >> USBHS_HSTCTRL_SPDCONF_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTCTRL_reg(const void *const hw, hri_usbhs_hstctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstctrl_reg_t hri_usbhs_get_HSTCTRL_reg(const void *const hw, hri_usbhs_hstctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTCTRL;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTCTRL_reg(const void *const hw, hri_usbhs_hstctrl_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTCTRL_reg(const void *const hw, hri_usbhs_hstctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTCTRL_reg(const void *const hw, hri_usbhs_hstctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTCTRL ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstctrl_reg_t hri_usbhs_read_HSTCTRL_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_HSTCTRL;
}

static inline void hri_usbhs_set_HSTPIP_PEN0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PEN0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PEN0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PEN0) >> USBHS_HSTPIP_PEN0_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PEN0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PEN0;
	tmp |= value << USBHS_HSTPIP_PEN0_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PEN0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PEN0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PEN0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PEN0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PEN1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PEN1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PEN1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PEN1) >> USBHS_HSTPIP_PEN1_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PEN1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PEN1;
	tmp |= value << USBHS_HSTPIP_PEN1_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PEN1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PEN1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PEN1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PEN1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PEN2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PEN2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PEN2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PEN2) >> USBHS_HSTPIP_PEN2_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PEN2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PEN2;
	tmp |= value << USBHS_HSTPIP_PEN2_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PEN2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PEN2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PEN2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PEN2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PEN3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PEN3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PEN3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PEN3) >> USBHS_HSTPIP_PEN3_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PEN3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PEN3;
	tmp |= value << USBHS_HSTPIP_PEN3_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PEN3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PEN3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PEN3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PEN3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PEN4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PEN4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PEN4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PEN4) >> USBHS_HSTPIP_PEN4_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PEN4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PEN4;
	tmp |= value << USBHS_HSTPIP_PEN4_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PEN4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PEN4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PEN4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PEN4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PEN5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PEN5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PEN5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PEN5) >> USBHS_HSTPIP_PEN5_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PEN5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PEN5;
	tmp |= value << USBHS_HSTPIP_PEN5_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PEN5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PEN5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PEN5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PEN5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PEN6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PEN6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PEN6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PEN6) >> USBHS_HSTPIP_PEN6_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PEN6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PEN6;
	tmp |= value << USBHS_HSTPIP_PEN6_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PEN6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PEN6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PEN6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PEN6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PEN7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PEN7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PEN7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PEN7) >> USBHS_HSTPIP_PEN7_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PEN7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PEN7;
	tmp |= value << USBHS_HSTPIP_PEN7_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PEN7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PEN7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PEN7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PEN7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PEN8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PEN8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PEN8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PEN8) >> USBHS_HSTPIP_PEN8_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PEN8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PEN8;
	tmp |= value << USBHS_HSTPIP_PEN8_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PEN8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PEN8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PEN8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PEN8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PRST0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PRST0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PRST0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PRST0) >> USBHS_HSTPIP_PRST0_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PRST0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PRST0;
	tmp |= value << USBHS_HSTPIP_PRST0_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PRST0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PRST0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PRST0_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PRST0;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PRST1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PRST1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PRST1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PRST1) >> USBHS_HSTPIP_PRST1_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PRST1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PRST1;
	tmp |= value << USBHS_HSTPIP_PRST1_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PRST1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PRST1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PRST1_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PRST1;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PRST2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PRST2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PRST2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PRST2) >> USBHS_HSTPIP_PRST2_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PRST2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PRST2;
	tmp |= value << USBHS_HSTPIP_PRST2_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PRST2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PRST2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PRST2_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PRST2;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PRST3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PRST3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PRST3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PRST3) >> USBHS_HSTPIP_PRST3_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PRST3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PRST3;
	tmp |= value << USBHS_HSTPIP_PRST3_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PRST3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PRST3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PRST3_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PRST3;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PRST4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PRST4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PRST4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PRST4) >> USBHS_HSTPIP_PRST4_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PRST4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PRST4;
	tmp |= value << USBHS_HSTPIP_PRST4_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PRST4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PRST4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PRST4_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PRST4;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PRST5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PRST5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PRST5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PRST5) >> USBHS_HSTPIP_PRST5_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PRST5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PRST5;
	tmp |= value << USBHS_HSTPIP_PRST5_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PRST5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PRST5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PRST5_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PRST5;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PRST6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PRST6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PRST6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PRST6) >> USBHS_HSTPIP_PRST6_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PRST6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PRST6;
	tmp |= value << USBHS_HSTPIP_PRST6_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PRST6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PRST6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PRST6_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PRST6;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PRST7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PRST7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PRST7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PRST7) >> USBHS_HSTPIP_PRST7_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PRST7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PRST7;
	tmp |= value << USBHS_HSTPIP_PRST7_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PRST7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PRST7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PRST7_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PRST7;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_PRST8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= USBHS_HSTPIP_PRST8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIP_PRST8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp = (tmp & USBHS_HSTPIP_PRST8) >> USBHS_HSTPIP_PRST8_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIP_PRST8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= ~USBHS_HSTPIP_PRST8;
	tmp |= value << USBHS_HSTPIP_PRST8_Pos;
	((Usbhs *)hw)->USBHS_HSTPIP = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_PRST8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~USBHS_HSTPIP_PRST8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_PRST8_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= USBHS_HSTPIP_PRST8;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIP_reg(const void *const hw, hri_usbhs_hstpip_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpip_reg_t hri_usbhs_get_HSTPIP_reg(const void *const hw, hri_usbhs_hstpip_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIP;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIP_reg(const void *const hw, hri_usbhs_hstpip_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIP_reg(const void *const hw, hri_usbhs_hstpip_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIP_reg(const void *const hw, hri_usbhs_hstpip_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIP ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpip_reg_t hri_usbhs_read_HSTPIP_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_HSTPIP;
}

static inline void hri_usbhs_set_HSTFNUM_MFNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM |= USBHS_HSTFNUM_MFNUM(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstfnum_reg_t hri_usbhs_get_HSTFNUM_MFNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp = (tmp & USBHS_HSTFNUM_MFNUM(mask)) >> USBHS_HSTFNUM_MFNUM_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTFNUM_MFNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp &= ~USBHS_HSTFNUM_MFNUM_Msk;
	tmp |= USBHS_HSTFNUM_MFNUM(data);
	((Usbhs *)hw)->USBHS_HSTFNUM = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTFNUM_MFNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM &= ~USBHS_HSTFNUM_MFNUM(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTFNUM_MFNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM ^= USBHS_HSTFNUM_MFNUM(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstfnum_reg_t hri_usbhs_read_HSTFNUM_MFNUM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp = (tmp & USBHS_HSTFNUM_MFNUM_Msk) >> USBHS_HSTFNUM_MFNUM_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTFNUM_FNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM |= USBHS_HSTFNUM_FNUM(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstfnum_reg_t hri_usbhs_get_HSTFNUM_FNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp = (tmp & USBHS_HSTFNUM_FNUM(mask)) >> USBHS_HSTFNUM_FNUM_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTFNUM_FNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp &= ~USBHS_HSTFNUM_FNUM_Msk;
	tmp |= USBHS_HSTFNUM_FNUM(data);
	((Usbhs *)hw)->USBHS_HSTFNUM = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTFNUM_FNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM &= ~USBHS_HSTFNUM_FNUM(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTFNUM_FNUM_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM ^= USBHS_HSTFNUM_FNUM(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstfnum_reg_t hri_usbhs_read_HSTFNUM_FNUM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp = (tmp & USBHS_HSTFNUM_FNUM_Msk) >> USBHS_HSTFNUM_FNUM_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTFNUM_FLENHIGH_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM |= USBHS_HSTFNUM_FLENHIGH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstfnum_reg_t hri_usbhs_get_HSTFNUM_FLENHIGH_bf(const void *const       hw,
                                                                        hri_usbhs_hstfnum_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp = (tmp & USBHS_HSTFNUM_FLENHIGH(mask)) >> USBHS_HSTFNUM_FLENHIGH_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTFNUM_FLENHIGH_bf(const void *const hw, hri_usbhs_hstfnum_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp &= ~USBHS_HSTFNUM_FLENHIGH_Msk;
	tmp |= USBHS_HSTFNUM_FLENHIGH(data);
	((Usbhs *)hw)->USBHS_HSTFNUM = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTFNUM_FLENHIGH_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM &= ~USBHS_HSTFNUM_FLENHIGH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTFNUM_FLENHIGH_bf(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM ^= USBHS_HSTFNUM_FLENHIGH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstfnum_reg_t hri_usbhs_read_HSTFNUM_FLENHIGH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp = (tmp & USBHS_HSTFNUM_FLENHIGH_Msk) >> USBHS_HSTFNUM_FLENHIGH_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTFNUM_reg(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstfnum_reg_t hri_usbhs_get_HSTFNUM_reg(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTFNUM;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTFNUM_reg(const void *const hw, hri_usbhs_hstfnum_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTFNUM_reg(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTFNUM_reg(const void *const hw, hri_usbhs_hstfnum_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTFNUM ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstfnum_reg_t hri_usbhs_read_HSTFNUM_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_HSTFNUM;
}

static inline void hri_usbhs_set_HSTADDR1_HSTADDRP0_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 |= USBHS_HSTADDR1_HSTADDRP0(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_get_HSTADDR1_HSTADDRP0_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp = (tmp & USBHS_HSTADDR1_HSTADDRP0(mask)) >> USBHS_HSTADDR1_HSTADDRP0_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR1_HSTADDRP0_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp &= ~USBHS_HSTADDR1_HSTADDRP0_Msk;
	tmp |= USBHS_HSTADDR1_HSTADDRP0(data);
	((Usbhs *)hw)->USBHS_HSTADDR1 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR1_HSTADDRP0_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 &= ~USBHS_HSTADDR1_HSTADDRP0(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR1_HSTADDRP0_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 ^= USBHS_HSTADDR1_HSTADDRP0(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_read_HSTADDR1_HSTADDRP0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp = (tmp & USBHS_HSTADDR1_HSTADDRP0_Msk) >> USBHS_HSTADDR1_HSTADDRP0_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR1_HSTADDRP1_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 |= USBHS_HSTADDR1_HSTADDRP1(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_get_HSTADDR1_HSTADDRP1_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp = (tmp & USBHS_HSTADDR1_HSTADDRP1(mask)) >> USBHS_HSTADDR1_HSTADDRP1_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR1_HSTADDRP1_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp &= ~USBHS_HSTADDR1_HSTADDRP1_Msk;
	tmp |= USBHS_HSTADDR1_HSTADDRP1(data);
	((Usbhs *)hw)->USBHS_HSTADDR1 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR1_HSTADDRP1_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 &= ~USBHS_HSTADDR1_HSTADDRP1(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR1_HSTADDRP1_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 ^= USBHS_HSTADDR1_HSTADDRP1(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_read_HSTADDR1_HSTADDRP1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp = (tmp & USBHS_HSTADDR1_HSTADDRP1_Msk) >> USBHS_HSTADDR1_HSTADDRP1_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR1_HSTADDRP2_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 |= USBHS_HSTADDR1_HSTADDRP2(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_get_HSTADDR1_HSTADDRP2_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp = (tmp & USBHS_HSTADDR1_HSTADDRP2(mask)) >> USBHS_HSTADDR1_HSTADDRP2_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR1_HSTADDRP2_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp &= ~USBHS_HSTADDR1_HSTADDRP2_Msk;
	tmp |= USBHS_HSTADDR1_HSTADDRP2(data);
	((Usbhs *)hw)->USBHS_HSTADDR1 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR1_HSTADDRP2_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 &= ~USBHS_HSTADDR1_HSTADDRP2(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR1_HSTADDRP2_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 ^= USBHS_HSTADDR1_HSTADDRP2(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_read_HSTADDR1_HSTADDRP2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp = (tmp & USBHS_HSTADDR1_HSTADDRP2_Msk) >> USBHS_HSTADDR1_HSTADDRP2_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR1_HSTADDRP3_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 |= USBHS_HSTADDR1_HSTADDRP3(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_get_HSTADDR1_HSTADDRP3_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp = (tmp & USBHS_HSTADDR1_HSTADDRP3(mask)) >> USBHS_HSTADDR1_HSTADDRP3_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR1_HSTADDRP3_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp &= ~USBHS_HSTADDR1_HSTADDRP3_Msk;
	tmp |= USBHS_HSTADDR1_HSTADDRP3(data);
	((Usbhs *)hw)->USBHS_HSTADDR1 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR1_HSTADDRP3_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 &= ~USBHS_HSTADDR1_HSTADDRP3(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR1_HSTADDRP3_bf(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 ^= USBHS_HSTADDR1_HSTADDRP3(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_read_HSTADDR1_HSTADDRP3_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp = (tmp & USBHS_HSTADDR1_HSTADDRP3_Msk) >> USBHS_HSTADDR1_HSTADDRP3_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR1_reg(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_get_HSTADDR1_reg(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR1;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR1_reg(const void *const hw, hri_usbhs_hstaddr1_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR1_reg(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR1_reg(const void *const hw, hri_usbhs_hstaddr1_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR1 ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr1_reg_t hri_usbhs_read_HSTADDR1_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_HSTADDR1;
}

static inline void hri_usbhs_set_HSTADDR2_HSTADDRP4_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 |= USBHS_HSTADDR2_HSTADDRP4(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_get_HSTADDR2_HSTADDRP4_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp = (tmp & USBHS_HSTADDR2_HSTADDRP4(mask)) >> USBHS_HSTADDR2_HSTADDRP4_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR2_HSTADDRP4_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp &= ~USBHS_HSTADDR2_HSTADDRP4_Msk;
	tmp |= USBHS_HSTADDR2_HSTADDRP4(data);
	((Usbhs *)hw)->USBHS_HSTADDR2 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR2_HSTADDRP4_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 &= ~USBHS_HSTADDR2_HSTADDRP4(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR2_HSTADDRP4_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 ^= USBHS_HSTADDR2_HSTADDRP4(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_read_HSTADDR2_HSTADDRP4_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp = (tmp & USBHS_HSTADDR2_HSTADDRP4_Msk) >> USBHS_HSTADDR2_HSTADDRP4_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR2_HSTADDRP5_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 |= USBHS_HSTADDR2_HSTADDRP5(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_get_HSTADDR2_HSTADDRP5_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp = (tmp & USBHS_HSTADDR2_HSTADDRP5(mask)) >> USBHS_HSTADDR2_HSTADDRP5_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR2_HSTADDRP5_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp &= ~USBHS_HSTADDR2_HSTADDRP5_Msk;
	tmp |= USBHS_HSTADDR2_HSTADDRP5(data);
	((Usbhs *)hw)->USBHS_HSTADDR2 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR2_HSTADDRP5_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 &= ~USBHS_HSTADDR2_HSTADDRP5(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR2_HSTADDRP5_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 ^= USBHS_HSTADDR2_HSTADDRP5(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_read_HSTADDR2_HSTADDRP5_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp = (tmp & USBHS_HSTADDR2_HSTADDRP5_Msk) >> USBHS_HSTADDR2_HSTADDRP5_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR2_HSTADDRP6_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 |= USBHS_HSTADDR2_HSTADDRP6(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_get_HSTADDR2_HSTADDRP6_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp = (tmp & USBHS_HSTADDR2_HSTADDRP6(mask)) >> USBHS_HSTADDR2_HSTADDRP6_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR2_HSTADDRP6_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp &= ~USBHS_HSTADDR2_HSTADDRP6_Msk;
	tmp |= USBHS_HSTADDR2_HSTADDRP6(data);
	((Usbhs *)hw)->USBHS_HSTADDR2 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR2_HSTADDRP6_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 &= ~USBHS_HSTADDR2_HSTADDRP6(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR2_HSTADDRP6_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 ^= USBHS_HSTADDR2_HSTADDRP6(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_read_HSTADDR2_HSTADDRP6_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp = (tmp & USBHS_HSTADDR2_HSTADDRP6_Msk) >> USBHS_HSTADDR2_HSTADDRP6_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR2_HSTADDRP7_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 |= USBHS_HSTADDR2_HSTADDRP7(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_get_HSTADDR2_HSTADDRP7_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp = (tmp & USBHS_HSTADDR2_HSTADDRP7(mask)) >> USBHS_HSTADDR2_HSTADDRP7_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR2_HSTADDRP7_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp &= ~USBHS_HSTADDR2_HSTADDRP7_Msk;
	tmp |= USBHS_HSTADDR2_HSTADDRP7(data);
	((Usbhs *)hw)->USBHS_HSTADDR2 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR2_HSTADDRP7_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 &= ~USBHS_HSTADDR2_HSTADDRP7(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR2_HSTADDRP7_bf(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 ^= USBHS_HSTADDR2_HSTADDRP7(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_read_HSTADDR2_HSTADDRP7_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp = (tmp & USBHS_HSTADDR2_HSTADDRP7_Msk) >> USBHS_HSTADDR2_HSTADDRP7_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR2_reg(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_get_HSTADDR2_reg(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR2;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR2_reg(const void *const hw, hri_usbhs_hstaddr2_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR2_reg(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR2_reg(const void *const hw, hri_usbhs_hstaddr2_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR2 ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr2_reg_t hri_usbhs_read_HSTADDR2_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_HSTADDR2;
}

static inline void hri_usbhs_set_HSTADDR3_HSTADDRP8_bf(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 |= USBHS_HSTADDR3_HSTADDRP8(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr3_reg_t hri_usbhs_get_HSTADDR3_HSTADDRP8_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR3;
	tmp = (tmp & USBHS_HSTADDR3_HSTADDRP8(mask)) >> USBHS_HSTADDR3_HSTADDRP8_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR3_HSTADDRP8_bf(const void *const hw, hri_usbhs_hstaddr3_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR3;
	tmp &= ~USBHS_HSTADDR3_HSTADDRP8_Msk;
	tmp |= USBHS_HSTADDR3_HSTADDRP8(data);
	((Usbhs *)hw)->USBHS_HSTADDR3 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR3_HSTADDRP8_bf(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 &= ~USBHS_HSTADDR3_HSTADDRP8(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR3_HSTADDRP8_bf(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 ^= USBHS_HSTADDR3_HSTADDRP8(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr3_reg_t hri_usbhs_read_HSTADDR3_HSTADDRP8_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR3;
	tmp = (tmp & USBHS_HSTADDR3_HSTADDRP8_Msk) >> USBHS_HSTADDR3_HSTADDRP8_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR3_HSTADDRP9_bf(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 |= USBHS_HSTADDR3_HSTADDRP9(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr3_reg_t hri_usbhs_get_HSTADDR3_HSTADDRP9_bf(const void *const        hw,
                                                                           hri_usbhs_hstaddr3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR3;
	tmp = (tmp & USBHS_HSTADDR3_HSTADDRP9(mask)) >> USBHS_HSTADDR3_HSTADDRP9_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR3_HSTADDRP9_bf(const void *const hw, hri_usbhs_hstaddr3_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR3;
	tmp &= ~USBHS_HSTADDR3_HSTADDRP9_Msk;
	tmp |= USBHS_HSTADDR3_HSTADDRP9(data);
	((Usbhs *)hw)->USBHS_HSTADDR3 = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR3_HSTADDRP9_bf(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 &= ~USBHS_HSTADDR3_HSTADDRP9(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR3_HSTADDRP9_bf(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 ^= USBHS_HSTADDR3_HSTADDRP9(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr3_reg_t hri_usbhs_read_HSTADDR3_HSTADDRP9_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR3;
	tmp = (tmp & USBHS_HSTADDR3_HSTADDRP9_Msk) >> USBHS_HSTADDR3_HSTADDRP9_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTADDR3_reg(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr3_reg_t hri_usbhs_get_HSTADDR3_reg(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTADDR3;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTADDR3_reg(const void *const hw, hri_usbhs_hstaddr3_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTADDR3_reg(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTADDR3_reg(const void *const hw, hri_usbhs_hstaddr3_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTADDR3 ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstaddr3_reg_t hri_usbhs_read_HSTADDR3_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_HSTADDR3;
}

static inline void hri_usbhs_set_HSTPIPCFG_ALLOC_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_ALLOC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIPCFG_ALLOC_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_ALLOC) >> USBHS_HSTPIPCFG_ALLOC_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_ALLOC_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_ALLOC;
	tmp |= value << USBHS_HSTPIPCFG_ALLOC_Pos;
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_ALLOC_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_ALLOC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_ALLOC_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_ALLOC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIPCFG_AUTOSW_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_AUTOSW;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIPCFG_AUTOSW_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_AUTOSW) >> USBHS_HSTPIPCFG_AUTOSW_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_AUTOSW_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_AUTOSW;
	tmp |= value << USBHS_HSTPIPCFG_AUTOSW_Pos;
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_AUTOSW_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_AUTOSW;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_AUTOSW_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_AUTOSW;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIPCFG_CTRL_BULK_PINGEN_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_CTRL_BULK_PINGEN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIPCFG_CTRL_BULK_PINGEN_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_CTRL_BULK_PINGEN) >> USBHS_HSTPIPCFG_CTRL_BULK_PINGEN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_CTRL_BULK_PINGEN_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_CTRL_BULK_PINGEN;
	tmp |= value << USBHS_HSTPIPCFG_CTRL_BULK_PINGEN_Pos;
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_CTRL_BULK_PINGEN_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_CTRL_BULK_PINGEN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_CTRL_BULK_PINGEN_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_CTRL_BULK_PINGEN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIPCFG_PBK_bf(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_PBK(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_get_HSTPIPCFG_PBK_bf(const void *const hw, uint8_t index,
                                                                       hri_usbhs_hstpipcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PBK(mask)) >> USBHS_HSTPIPCFG_PBK_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_PBK_bf(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_PBK_Msk;
	tmp |= USBHS_HSTPIPCFG_PBK(data);
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_PBK_bf(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_PBK(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_PBK_bf(const void *const hw, uint8_t index,
                                                     hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_PBK(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_read_HSTPIPCFG_PBK_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PBK_Msk) >> USBHS_HSTPIPCFG_PBK_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTPIPCFG_PSIZE_bf(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_PSIZE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_get_HSTPIPCFG_PSIZE_bf(const void *const hw, uint8_t index,
                                                                         hri_usbhs_hstpipcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PSIZE(mask)) >> USBHS_HSTPIPCFG_PSIZE_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_PSIZE_bf(const void *const hw, uint8_t index,
                                                      hri_usbhs_hstpipcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_PSIZE_Msk;
	tmp |= USBHS_HSTPIPCFG_PSIZE(data);
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_PSIZE_bf(const void *const hw, uint8_t index,
                                                      hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_PSIZE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_PSIZE_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_PSIZE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_read_HSTPIPCFG_PSIZE_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PSIZE_Msk) >> USBHS_HSTPIPCFG_PSIZE_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTPIPCFG_PTOKEN_bf(const void *const hw, uint8_t index,
                                                     hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_PTOKEN(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_get_HSTPIPCFG_PTOKEN_bf(const void *const hw, uint8_t index,
                                                                          hri_usbhs_hstpipcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PTOKEN(mask)) >> USBHS_HSTPIPCFG_PTOKEN_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_PTOKEN_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_hstpipcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_PTOKEN_Msk;
	tmp |= USBHS_HSTPIPCFG_PTOKEN(data);
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_PTOKEN_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_PTOKEN(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_PTOKEN_bf(const void *const hw, uint8_t index,
                                                        hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_PTOKEN(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_read_HSTPIPCFG_PTOKEN_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PTOKEN_Msk) >> USBHS_HSTPIPCFG_PTOKEN_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTPIPCFG_PTYPE_bf(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_PTYPE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_get_HSTPIPCFG_PTYPE_bf(const void *const hw, uint8_t index,
                                                                         hri_usbhs_hstpipcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PTYPE(mask)) >> USBHS_HSTPIPCFG_PTYPE_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_PTYPE_bf(const void *const hw, uint8_t index,
                                                      hri_usbhs_hstpipcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_PTYPE_Msk;
	tmp |= USBHS_HSTPIPCFG_PTYPE(data);
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_PTYPE_bf(const void *const hw, uint8_t index,
                                                      hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_PTYPE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_PTYPE_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_PTYPE(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_read_HSTPIPCFG_PTYPE_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PTYPE_Msk) >> USBHS_HSTPIPCFG_PTYPE_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTPIPCFG_PEPNUM_bf(const void *const hw, uint8_t index,
                                                     hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_PEPNUM(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_get_HSTPIPCFG_PEPNUM_bf(const void *const hw, uint8_t index,
                                                                          hri_usbhs_hstpipcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PEPNUM(mask)) >> USBHS_HSTPIPCFG_PEPNUM_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_PEPNUM_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_hstpipcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_PEPNUM_Msk;
	tmp |= USBHS_HSTPIPCFG_PEPNUM(data);
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_PEPNUM_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_PEPNUM(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_PEPNUM_bf(const void *const hw, uint8_t index,
                                                        hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_PEPNUM(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_read_HSTPIPCFG_PEPNUM_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_PEPNUM_Msk) >> USBHS_HSTPIPCFG_PEPNUM_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTPIPCFG_INTFRQ_bf(const void *const hw, uint8_t index,
                                                     hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_INTFRQ(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_get_HSTPIPCFG_INTFRQ_bf(const void *const hw, uint8_t index,
                                                                          hri_usbhs_hstpipcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_INTFRQ(mask)) >> USBHS_HSTPIPCFG_INTFRQ_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_INTFRQ_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_hstpipcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_INTFRQ_Msk;
	tmp |= USBHS_HSTPIPCFG_INTFRQ(data);
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_INTFRQ_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_INTFRQ(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_INTFRQ_bf(const void *const hw, uint8_t index,
                                                        hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_INTFRQ(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_read_HSTPIPCFG_INTFRQ_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_INTFRQ_Msk) >> USBHS_HSTPIPCFG_INTFRQ_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTPIPCFG_CTRL_BULK_BINTERVAL_bf(const void *const hw, uint8_t index,
                                                                  hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= USBHS_HSTPIPCFG_CTRL_BULK_BINTERVAL(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t
hri_usbhs_get_HSTPIPCFG_CTRL_BULK_BINTERVAL_bf(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_CTRL_BULK_BINTERVAL(mask)) >> USBHS_HSTPIPCFG_CTRL_BULK_BINTERVAL_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_CTRL_BULK_BINTERVAL_bf(const void *const hw, uint8_t index,
                                                                    hri_usbhs_hstpipcfg_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= ~USBHS_HSTPIPCFG_CTRL_BULK_BINTERVAL_Msk;
	tmp |= USBHS_HSTPIPCFG_CTRL_BULK_BINTERVAL(data);
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_CTRL_BULK_BINTERVAL_bf(const void *const hw, uint8_t index,
                                                                    hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~USBHS_HSTPIPCFG_CTRL_BULK_BINTERVAL(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_CTRL_BULK_BINTERVAL_bf(const void *const hw, uint8_t index,
                                                                     hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= USBHS_HSTPIPCFG_CTRL_BULK_BINTERVAL(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_read_HSTPIPCFG_CTRL_BULK_BINTERVAL_bf(const void *const hw,
                                                                                        uint8_t           index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp = (tmp & USBHS_HSTPIPCFG_CTRL_BULK_BINTERVAL_Msk) >> USBHS_HSTPIPCFG_CTRL_BULK_BINTERVAL_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTPIPCFG_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_get_HSTPIPCFG_reg(const void *const hw, uint8_t index,
                                                                    hri_usbhs_hstpipcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPCFG_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPCFG_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPCFG_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipcfg_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPCFG[index] ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipcfg_reg_t hri_usbhs_read_HSTPIPCFG_reg(const void *const hw, uint8_t index)
{
	return ((Usbhs *)hw)->USBHS_HSTPIPCFG[index];
}

static inline void hri_usbhs_set_HSTPIPINRQ_INMODE_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] |= USBHS_HSTPIPINRQ_INMODE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIPINRQ_INMODE_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPINRQ[index];
	tmp = (tmp & USBHS_HSTPIPINRQ_INMODE) >> USBHS_HSTPIPINRQ_INMODE_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIPINRQ_INMODE_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPINRQ[index];
	tmp &= ~USBHS_HSTPIPINRQ_INMODE;
	tmp |= value << USBHS_HSTPIPINRQ_INMODE_Pos;
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPINRQ_INMODE_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] &= ~USBHS_HSTPIPINRQ_INMODE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPINRQ_INMODE_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] ^= USBHS_HSTPIPINRQ_INMODE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIPINRQ_INRQ_bf(const void *const hw, uint8_t index,
                                                    hri_usbhs_hstpipinrq_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] |= USBHS_HSTPIPINRQ_INRQ(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipinrq_reg_t hri_usbhs_get_HSTPIPINRQ_INRQ_bf(const void *const hw, uint8_t index,
                                                                          hri_usbhs_hstpipinrq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPINRQ[index];
	tmp = (tmp & USBHS_HSTPIPINRQ_INRQ(mask)) >> USBHS_HSTPIPINRQ_INRQ_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPINRQ_INRQ_bf(const void *const hw, uint8_t index,
                                                      hri_usbhs_hstpipinrq_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPINRQ[index];
	tmp &= ~USBHS_HSTPIPINRQ_INRQ_Msk;
	tmp |= USBHS_HSTPIPINRQ_INRQ(data);
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPINRQ_INRQ_bf(const void *const hw, uint8_t index,
                                                      hri_usbhs_hstpipinrq_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] &= ~USBHS_HSTPIPINRQ_INRQ(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPINRQ_INRQ_bf(const void *const hw, uint8_t index,
                                                       hri_usbhs_hstpipinrq_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] ^= USBHS_HSTPIPINRQ_INRQ(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipinrq_reg_t hri_usbhs_read_HSTPIPINRQ_INRQ_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPINRQ[index];
	tmp = (tmp & USBHS_HSTPIPINRQ_INRQ_Msk) >> USBHS_HSTPIPINRQ_INRQ_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTPIPINRQ_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipinrq_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipinrq_reg_t hri_usbhs_get_HSTPIPINRQ_reg(const void *const hw, uint8_t index,
                                                                      hri_usbhs_hstpipinrq_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPINRQ[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPINRQ_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipinrq_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPINRQ_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipinrq_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPINRQ_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipinrq_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPINRQ[index] ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpipinrq_reg_t hri_usbhs_read_HSTPIPINRQ_reg(const void *const hw, uint8_t index)
{
	return ((Usbhs *)hw)->USBHS_HSTPIPINRQ[index];
}

static inline void hri_usbhs_set_HSTPIPERR_DATATGL_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] |= USBHS_HSTPIPERR_DATATGL;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIPERR_DATATGL_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp = (tmp & USBHS_HSTPIPERR_DATATGL) >> USBHS_HSTPIPERR_DATATGL_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIPERR_DATATGL_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp &= ~USBHS_HSTPIPERR_DATATGL;
	tmp |= value << USBHS_HSTPIPERR_DATATGL_Pos;
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPERR_DATATGL_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] &= ~USBHS_HSTPIPERR_DATATGL;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPERR_DATATGL_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] ^= USBHS_HSTPIPERR_DATATGL;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIPERR_DATAPID_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] |= USBHS_HSTPIPERR_DATAPID;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIPERR_DATAPID_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp = (tmp & USBHS_HSTPIPERR_DATAPID) >> USBHS_HSTPIPERR_DATAPID_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIPERR_DATAPID_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp &= ~USBHS_HSTPIPERR_DATAPID;
	tmp |= value << USBHS_HSTPIPERR_DATAPID_Pos;
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPERR_DATAPID_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] &= ~USBHS_HSTPIPERR_DATAPID;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPERR_DATAPID_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] ^= USBHS_HSTPIPERR_DATAPID;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIPERR_PID_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] |= USBHS_HSTPIPERR_PID;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIPERR_PID_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp = (tmp & USBHS_HSTPIPERR_PID) >> USBHS_HSTPIPERR_PID_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIPERR_PID_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp &= ~USBHS_HSTPIPERR_PID;
	tmp |= value << USBHS_HSTPIPERR_PID_Pos;
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPERR_PID_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] &= ~USBHS_HSTPIPERR_PID;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPERR_PID_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] ^= USBHS_HSTPIPERR_PID;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIPERR_TIMEOUT_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] |= USBHS_HSTPIPERR_TIMEOUT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIPERR_TIMEOUT_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp = (tmp & USBHS_HSTPIPERR_TIMEOUT) >> USBHS_HSTPIPERR_TIMEOUT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIPERR_TIMEOUT_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp &= ~USBHS_HSTPIPERR_TIMEOUT;
	tmp |= value << USBHS_HSTPIPERR_TIMEOUT_Pos;
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPERR_TIMEOUT_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] &= ~USBHS_HSTPIPERR_TIMEOUT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPERR_TIMEOUT_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] ^= USBHS_HSTPIPERR_TIMEOUT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIPERR_CRC16_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] |= USBHS_HSTPIPERR_CRC16;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTPIPERR_CRC16_bit(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp = (tmp & USBHS_HSTPIPERR_CRC16) >> USBHS_HSTPIPERR_CRC16_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTPIPERR_CRC16_bit(const void *const hw, uint8_t index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp &= ~USBHS_HSTPIPERR_CRC16;
	tmp |= value << USBHS_HSTPIPERR_CRC16_Pos;
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPERR_CRC16_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] &= ~USBHS_HSTPIPERR_CRC16;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPERR_CRC16_bit(const void *const hw, uint8_t index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] ^= USBHS_HSTPIPERR_CRC16;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTPIPERR_COUNTER_bf(const void *const hw, uint8_t index,
                                                      hri_usbhs_hstpiperr_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] |= USBHS_HSTPIPERR_COUNTER(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpiperr_reg_t hri_usbhs_get_HSTPIPERR_COUNTER_bf(const void *const hw, uint8_t index,
                                                                           hri_usbhs_hstpiperr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp = (tmp & USBHS_HSTPIPERR_COUNTER(mask)) >> USBHS_HSTPIPERR_COUNTER_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPERR_COUNTER_bf(const void *const hw, uint8_t index,
                                                        hri_usbhs_hstpiperr_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp &= ~USBHS_HSTPIPERR_COUNTER_Msk;
	tmp |= USBHS_HSTPIPERR_COUNTER(data);
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPERR_COUNTER_bf(const void *const hw, uint8_t index,
                                                        hri_usbhs_hstpiperr_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] &= ~USBHS_HSTPIPERR_COUNTER(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPERR_COUNTER_bf(const void *const hw, uint8_t index,
                                                         hri_usbhs_hstpiperr_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] ^= USBHS_HSTPIPERR_COUNTER(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpiperr_reg_t hri_usbhs_read_HSTPIPERR_COUNTER_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp = (tmp & USBHS_HSTPIPERR_COUNTER_Msk) >> USBHS_HSTPIPERR_COUNTER_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTPIPERR_reg(const void *const hw, uint8_t index, hri_usbhs_hstpiperr_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpiperr_reg_t hri_usbhs_get_HSTPIPERR_reg(const void *const hw, uint8_t index,
                                                                    hri_usbhs_hstpiperr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTPIPERR_reg(const void *const hw, uint8_t index, hri_usbhs_hstpiperr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTPIPERR_reg(const void *const hw, uint8_t index, hri_usbhs_hstpiperr_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTPIPERR_reg(const void *const hw, uint8_t index, hri_usbhs_hstpiperr_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPERR[index] ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstpiperr_reg_t hri_usbhs_read_HSTPIPERR_reg(const void *const hw, uint8_t index)
{
	return ((Usbhs *)hw)->USBHS_HSTPIPERR[index];
}

static inline void hri_usbhs_set_CTRL_RDERRE_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL |= USBHS_CTRL_RDERRE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_CTRL_RDERRE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp = (tmp & USBHS_CTRL_RDERRE) >> USBHS_CTRL_RDERRE_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_CTRL_RDERRE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp &= ~USBHS_CTRL_RDERRE;
	tmp |= value << USBHS_CTRL_RDERRE_Pos;
	((Usbhs *)hw)->USBHS_CTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_CTRL_RDERRE_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL &= ~USBHS_CTRL_RDERRE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_CTRL_RDERRE_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL ^= USBHS_CTRL_RDERRE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_CTRL_VBUSHWC_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL |= USBHS_CTRL_VBUSHWC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_CTRL_VBUSHWC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp = (tmp & USBHS_CTRL_VBUSHWC) >> USBHS_CTRL_VBUSHWC_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_CTRL_VBUSHWC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp &= ~USBHS_CTRL_VBUSHWC;
	tmp |= value << USBHS_CTRL_VBUSHWC_Pos;
	((Usbhs *)hw)->USBHS_CTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_CTRL_VBUSHWC_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL &= ~USBHS_CTRL_VBUSHWC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_CTRL_VBUSHWC_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL ^= USBHS_CTRL_VBUSHWC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_CTRL_FRZCLK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL |= USBHS_CTRL_FRZCLK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_CTRL_FRZCLK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp = (tmp & USBHS_CTRL_FRZCLK) >> USBHS_CTRL_FRZCLK_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_CTRL_FRZCLK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp &= ~USBHS_CTRL_FRZCLK;
	tmp |= value << USBHS_CTRL_FRZCLK_Pos;
	((Usbhs *)hw)->USBHS_CTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_CTRL_FRZCLK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL &= ~USBHS_CTRL_FRZCLK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_CTRL_FRZCLK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL ^= USBHS_CTRL_FRZCLK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_CTRL_USBE_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL |= USBHS_CTRL_USBE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_CTRL_USBE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp = (tmp & USBHS_CTRL_USBE) >> USBHS_CTRL_USBE_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_CTRL_USBE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp &= ~USBHS_CTRL_USBE;
	tmp |= value << USBHS_CTRL_USBE_Pos;
	((Usbhs *)hw)->USBHS_CTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_CTRL_USBE_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL &= ~USBHS_CTRL_USBE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_CTRL_USBE_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL ^= USBHS_CTRL_USBE;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_CTRL_UID_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL |= USBHS_CTRL_UID;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_CTRL_UID_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp = (tmp & USBHS_CTRL_UID) >> USBHS_CTRL_UID_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_CTRL_UID_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp &= ~USBHS_CTRL_UID;
	tmp |= value << USBHS_CTRL_UID_Pos;
	((Usbhs *)hw)->USBHS_CTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_CTRL_UID_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL &= ~USBHS_CTRL_UID;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_CTRL_UID_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL ^= USBHS_CTRL_UID;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_CTRL_UIMOD_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL |= USBHS_CTRL_UIMOD;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_CTRL_UIMOD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp = (tmp & USBHS_CTRL_UIMOD) >> USBHS_CTRL_UIMOD_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_CTRL_UIMOD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp &= ~USBHS_CTRL_UIMOD;
	tmp |= value << USBHS_CTRL_UIMOD_Pos;
	((Usbhs *)hw)->USBHS_CTRL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_CTRL_UIMOD_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL &= ~USBHS_CTRL_UIMOD;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_CTRL_UIMOD_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL ^= USBHS_CTRL_UIMOD;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_CTRL_reg(const void *const hw, hri_usbhs_ctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_ctrl_reg_t hri_usbhs_get_CTRL_reg(const void *const hw, hri_usbhs_ctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->USBHS_CTRL;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_CTRL_reg(const void *const hw, hri_usbhs_ctrl_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_CTRL_reg(const void *const hw, hri_usbhs_ctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_CTRL_reg(const void *const hw, hri_usbhs_ctrl_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_CTRL ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_ctrl_reg_t hri_usbhs_read_CTRL_reg(const void *const hw)
{
	return ((Usbhs *)hw)->USBHS_CTRL;
}

static inline void hri_usbhs_write_DEVICR_reg(const void *const hw, hri_usbhs_devicr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVICR = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_DEVIFR_reg(const void *const hw, hri_usbhs_devifr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVIFR = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_DEVEPTIFR_reg(const void *const hw, uint8_t index, hri_usbhs_deveptifr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTIFR[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_DEVEPTIER_reg(const void *const hw, uint8_t index, hri_usbhs_deveptier_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTIER[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_DEVEPTIDR_reg(const void *const hw, uint8_t index, hri_usbhs_deveptidr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_DEVEPTIDR[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_HSTICR_reg(const void *const hw, hri_usbhs_hsticr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTICR = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_HSTIFR_reg(const void *const hw, hri_usbhs_hstifr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTIFR = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_HSTPIPIFR_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipifr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPIFR[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_HSTPIPIER_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipier_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPIER[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_HSTPIPIDR_reg(const void *const hw, uint8_t index, hri_usbhs_hstpipidr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_HSTPIPIDR[index] = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_write_SFR_reg(const void *const hw, hri_usbhs_sfr_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->USBHS_SFR = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_set_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const            hw,
                                                                   hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC |= USBHS_DEVDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmanxtdsc_reg_t
hri_usbhsdevdma_get_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, hri_usbhs_devdmanxtdsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC;
	tmp = (tmp & USBHS_DEVDMANXTDSC_NXT_DSC_ADD(mask)) >> USBHS_DEVDMANXTDSC_NXT_DSC_ADD_Pos;
	return tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const            hw,
                                                                     hri_usbhs_devdmanxtdsc_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC;
	tmp &= ~USBHS_DEVDMANXTDSC_NXT_DSC_ADD_Msk;
	tmp |= USBHS_DEVDMANXTDSC_NXT_DSC_ADD(data);
	((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const            hw,
                                                                     hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC &= ~USBHS_DEVDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const            hw,
                                                                      hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC ^= USBHS_DEVDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmanxtdsc_reg_t hri_usbhsdevdma_read_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC;
	tmp = (tmp & USBHS_DEVDMANXTDSC_NXT_DSC_ADD_Msk) >> USBHS_DEVDMANXTDSC_NXT_DSC_ADD_Pos;
	return tmp;
}

static inline void hri_usbhsdevdma_set_DEVDMANXTDSC_reg(const void *const hw, hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmanxtdsc_reg_t hri_usbhsdevdma_get_DEVDMANXTDSC_reg(const void *const            hw,
                                                                                hri_usbhs_devdmanxtdsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMANXTDSC_reg(const void *const hw, hri_usbhs_devdmanxtdsc_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMANXTDSC_reg(const void *const hw, hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMANXTDSC_reg(const void *const hw, hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmanxtdsc_reg_t hri_usbhsdevdma_read_DEVDMANXTDSC_reg(const void *const hw)
{
	return ((UsbhsDevdma *)hw)->USBHS_DEVDMANXTDSC;
}

static inline void hri_usbhsdevdma_set_DEVDMAADDRESS_BUFF_ADD_bf(const void *const             hw,
                                                                 hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS |= USBHS_DEVDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmaaddress_reg_t
hri_usbhsdevdma_get_DEVDMAADDRESS_BUFF_ADD_bf(const void *const hw, hri_usbhs_devdmaaddress_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS;
	tmp = (tmp & USBHS_DEVDMAADDRESS_BUFF_ADD(mask)) >> USBHS_DEVDMAADDRESS_BUFF_ADD_Pos;
	return tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMAADDRESS_BUFF_ADD_bf(const void *const             hw,
                                                                   hri_usbhs_devdmaaddress_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS;
	tmp &= ~USBHS_DEVDMAADDRESS_BUFF_ADD_Msk;
	tmp |= USBHS_DEVDMAADDRESS_BUFF_ADD(data);
	((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMAADDRESS_BUFF_ADD_bf(const void *const             hw,
                                                                   hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS &= ~USBHS_DEVDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMAADDRESS_BUFF_ADD_bf(const void *const             hw,
                                                                    hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS ^= USBHS_DEVDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmaaddress_reg_t hri_usbhsdevdma_read_DEVDMAADDRESS_BUFF_ADD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS;
	tmp = (tmp & USBHS_DEVDMAADDRESS_BUFF_ADD_Msk) >> USBHS_DEVDMAADDRESS_BUFF_ADD_Pos;
	return tmp;
}

static inline void hri_usbhsdevdma_set_DEVDMAADDRESS_reg(const void *const hw, hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmaaddress_reg_t hri_usbhsdevdma_get_DEVDMAADDRESS_reg(const void *const             hw,
                                                                                  hri_usbhs_devdmaaddress_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMAADDRESS_reg(const void *const hw, hri_usbhs_devdmaaddress_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMAADDRESS_reg(const void *const hw, hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMAADDRESS_reg(const void *const hw, hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmaaddress_reg_t hri_usbhsdevdma_read_DEVDMAADDRESS_reg(const void *const hw)
{
	return ((UsbhsDevdma *)hw)->USBHS_DEVDMAADDRESS;
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_CHANN_ENB) >> USBHS_DEVDMACONTROL_CHANN_ENB_Pos;
	return (bool)tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_CHANN_ENB;
	tmp |= value << USBHS_DEVDMACONTROL_CHANN_ENB_Pos;
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_LDNXT_DSC) >> USBHS_DEVDMACONTROL_LDNXT_DSC_Pos;
	return (bool)tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_LDNXT_DSC;
	tmp |= value << USBHS_DEVDMACONTROL_LDNXT_DSC_Pos;
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_END_TR_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMACONTROL_END_TR_EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_END_TR_EN) >> USBHS_DEVDMACONTROL_END_TR_EN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_END_TR_EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_END_TR_EN;
	tmp |= value << USBHS_DEVDMACONTROL_END_TR_EN_Pos;
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_END_TR_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_END_TR_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_END_B_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMACONTROL_END_B_EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_END_B_EN) >> USBHS_DEVDMACONTROL_END_B_EN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_END_B_EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_END_B_EN;
	tmp |= value << USBHS_DEVDMACONTROL_END_B_EN_Pos;
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_END_B_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_END_B_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_END_TR_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMACONTROL_END_TR_IT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_END_TR_IT) >> USBHS_DEVDMACONTROL_END_TR_IT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_END_TR_IT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_END_TR_IT;
	tmp |= value << USBHS_DEVDMACONTROL_END_TR_IT_Pos;
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_END_TR_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_END_TR_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_END_BUFFIT) >> USBHS_DEVDMACONTROL_END_BUFFIT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_END_BUFFIT;
	tmp |= value << USBHS_DEVDMACONTROL_END_BUFFIT_Pos;
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_DESC_LD_IT) >> USBHS_DEVDMACONTROL_DESC_LD_IT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_DESC_LD_IT;
	tmp |= value << USBHS_DEVDMACONTROL_DESC_LD_IT_Pos;
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_BURST_LCK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMACONTROL_BURST_LCK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_BURST_LCK) >> USBHS_DEVDMACONTROL_BURST_LCK_Pos;
	return (bool)tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_BURST_LCK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_BURST_LCK;
	tmp |= value << USBHS_DEVDMACONTROL_BURST_LCK_Pos;
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_BURST_LCK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_BURST_LCK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const             hw,
                                                                    hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmacontrol_reg_t
hri_usbhsdevdma_get_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const hw, hri_usbhs_devdmacontrol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_BUFF_LENGTH(mask)) >> USBHS_DEVDMACONTROL_BUFF_LENGTH_Pos;
	return tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const             hw,
                                                                      hri_usbhs_devdmacontrol_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_BUFF_LENGTH_Msk;
	tmp |= USBHS_DEVDMACONTROL_BUFF_LENGTH(data);
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const             hw,
                                                                      hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const             hw,
                                                                       hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmacontrol_reg_t hri_usbhsdevdma_read_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_BUFF_LENGTH_Msk) >> USBHS_DEVDMACONTROL_BUFF_LENGTH_Pos;
	return tmp;
}

static inline void hri_usbhsdevdma_set_DEVDMACONTROL_reg(const void *const hw, hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmacontrol_reg_t hri_usbhsdevdma_get_DEVDMACONTROL_reg(const void *const             hw,
                                                                                  hri_usbhs_devdmacontrol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhsdevdma_write_DEVDMACONTROL_reg(const void *const hw, hri_usbhs_devdmacontrol_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_clear_DEVDMACONTROL_reg(const void *const hw, hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhsdevdma_toggle_DEVDMACONTROL_reg(const void *const hw, hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmacontrol_reg_t hri_usbhsdevdma_read_DEVDMACONTROL_reg(const void *const hw)
{
	return ((UsbhsDevdma *)hw)->USBHS_DEVDMACONTROL;
}

static inline bool hri_usbhsdevdma_get_DEVDMASTATUS_CHANN_ENB_bit(const void *const hw)
{
	return (((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_CHANN_ENB) >> USBHS_DEVDMASTATUS_CHANN_ENB_Pos;
}

static inline void hri_usbhsdevdma_clear_DEVDMASTATUS_CHANN_ENB_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMASTATUS_CHANN_ACT_bit(const void *const hw)
{
	return (((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_CHANN_ACT) >> USBHS_DEVDMASTATUS_CHANN_ACT_Pos;
}

static inline void hri_usbhsdevdma_clear_DEVDMASTATUS_CHANN_ACT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_CHANN_ACT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMASTATUS_END_TR_ST_bit(const void *const hw)
{
	return (((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_END_TR_ST) >> USBHS_DEVDMASTATUS_END_TR_ST_Pos;
}

static inline void hri_usbhsdevdma_clear_DEVDMASTATUS_END_TR_ST_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_END_TR_ST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMASTATUS_END_BF_ST_bit(const void *const hw)
{
	return (((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_END_BF_ST) >> USBHS_DEVDMASTATUS_END_BF_ST_Pos;
}

static inline void hri_usbhsdevdma_clear_DEVDMASTATUS_END_BF_ST_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_END_BF_ST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhsdevdma_get_DEVDMASTATUS_DESC_LDST_bit(const void *const hw)
{
	return (((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_DESC_LDST) >> USBHS_DEVDMASTATUS_DESC_LDST_Pos;
}

static inline void hri_usbhsdevdma_clear_DEVDMASTATUS_DESC_LDST_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_DESC_LDST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmastatus_reg_t
hri_usbhsdevdma_get_DEVDMASTATUS_BUFF_COUNT_bf(const void *const hw, hri_usbhs_devdmastatus_reg_t mask)
{
	return (((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_BUFF_COUNT(mask))
	       >> USBHS_DEVDMASTATUS_BUFF_COUNT_Pos;
}

static inline void hri_usbhsdevdma_clear_DEVDMASTATUS_BUFF_COUNT_bf(const void *const            hw,
                                                                    hri_usbhs_devdmastatus_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_BUFF_COUNT(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmastatus_reg_t hri_usbhsdevdma_read_DEVDMASTATUS_BUFF_COUNT_bf(const void *const hw)
{
	return (((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_BUFF_COUNT_Msk)
	       >> USBHS_DEVDMASTATUS_BUFF_COUNT_Pos;
}

static inline hri_usbhs_devdmastatus_reg_t hri_usbhsdevdma_get_DEVDMASTATUS_reg(const void *const            hw,
                                                                                hri_usbhs_devdmastatus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhsdevdma_clear_DEVDMASTATUS_reg(const void *const hw, hri_usbhs_devdmastatus_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS = mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmastatus_reg_t hri_usbhsdevdma_read_DEVDMASTATUS_reg(const void *const hw)
{
	return ((UsbhsDevdma *)hw)->USBHS_DEVDMASTATUS;
}

static inline void hri_usbhs_set_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                             hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC |= USBHS_DEVDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmanxtdsc_reg_t hri_usbhs_get_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw,
                                                                                     uint8_t           submodule_index,
                                                                                     hri_usbhs_devdmanxtdsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC;
	tmp = (tmp & USBHS_DEVDMANXTDSC_NXT_DSC_ADD(mask)) >> USBHS_DEVDMANXTDSC_NXT_DSC_ADD_Pos;
	return tmp;
}

static inline void hri_usbhs_write_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                               hri_usbhs_devdmanxtdsc_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC;
	tmp &= ~USBHS_DEVDMANXTDSC_NXT_DSC_ADD_Msk;
	tmp |= USBHS_DEVDMANXTDSC_NXT_DSC_ADD(data);
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                               hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC &= ~USBHS_DEVDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                                hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC ^= USBHS_DEVDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmanxtdsc_reg_t hri_usbhs_read_DEVDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw,
                                                                                      uint8_t           submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC;
	tmp = (tmp & USBHS_DEVDMANXTDSC_NXT_DSC_ADD_Msk) >> USBHS_DEVDMANXTDSC_NXT_DSC_ADD_Pos;
	return tmp;
}

static inline void hri_usbhs_set_DEVDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                  hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmanxtdsc_reg_t hri_usbhs_get_DEVDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                                          hri_usbhs_devdmanxtdsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_DEVDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                    hri_usbhs_devdmanxtdsc_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                    hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_devdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmanxtdsc_reg_t hri_usbhs_read_DEVDMANXTDSC_reg(const void *const hw,
                                                                           uint8_t           submodule_index)
{
	return ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMANXTDSC;
}

static inline void hri_usbhs_set_DEVDMAADDRESS_BUFF_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                           hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS |= USBHS_DEVDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmaaddress_reg_t hri_usbhs_get_DEVDMAADDRESS_BUFF_ADD_bf(const void *const hw,
                                                                                    uint8_t           submodule_index,
                                                                                    hri_usbhs_devdmaaddress_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS;
	tmp = (tmp & USBHS_DEVDMAADDRESS_BUFF_ADD(mask)) >> USBHS_DEVDMAADDRESS_BUFF_ADD_Pos;
	return tmp;
}

static inline void hri_usbhs_write_DEVDMAADDRESS_BUFF_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                             hri_usbhs_devdmaaddress_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS;
	tmp &= ~USBHS_DEVDMAADDRESS_BUFF_ADD_Msk;
	tmp |= USBHS_DEVDMAADDRESS_BUFF_ADD(data);
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMAADDRESS_BUFF_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                             hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS &= ~USBHS_DEVDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMAADDRESS_BUFF_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                              hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS ^= USBHS_DEVDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmaaddress_reg_t hri_usbhs_read_DEVDMAADDRESS_BUFF_ADD_bf(const void *const hw,
                                                                                     uint8_t           submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS;
	tmp = (tmp & USBHS_DEVDMAADDRESS_BUFF_ADD_Msk) >> USBHS_DEVDMAADDRESS_BUFF_ADD_Pos;
	return tmp;
}

static inline void hri_usbhs_set_DEVDMAADDRESS_reg(const void *const hw, uint8_t submodule_index,
                                                   hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmaaddress_reg_t
hri_usbhs_get_DEVDMAADDRESS_reg(const void *const hw, uint8_t submodule_index, hri_usbhs_devdmaaddress_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_DEVDMAADDRESS_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_devdmaaddress_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMAADDRESS_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMAADDRESS_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_usbhs_devdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmaaddress_reg_t hri_usbhs_read_DEVDMAADDRESS_reg(const void *const hw,
                                                                             uint8_t           submodule_index)
{
	return ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMAADDRESS;
}

static inline void hri_usbhs_set_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_CHANN_ENB) >> USBHS_DEVDMACONTROL_CHANN_ENB_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_CHANN_ENB;
	tmp |= value << USBHS_DEVDMACONTROL_CHANN_ENB_Pos;
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_LDNXT_DSC) >> USBHS_DEVDMACONTROL_LDNXT_DSC_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_LDNXT_DSC;
	tmp |= value << USBHS_DEVDMACONTROL_LDNXT_DSC_Pos;
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_END_TR_EN) >> USBHS_DEVDMACONTROL_END_TR_EN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_END_TR_EN;
	tmp |= value << USBHS_DEVDMACONTROL_END_TR_EN_Pos;
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_END_B_EN) >> USBHS_DEVDMACONTROL_END_B_EN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_END_B_EN;
	tmp |= value << USBHS_DEVDMACONTROL_END_B_EN_Pos;
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_END_TR_IT) >> USBHS_DEVDMACONTROL_END_TR_IT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_END_TR_IT;
	tmp |= value << USBHS_DEVDMACONTROL_END_TR_IT_Pos;
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_END_BUFFIT) >> USBHS_DEVDMACONTROL_END_BUFFIT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index,
                                                                bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_END_BUFFIT;
	tmp |= value << USBHS_DEVDMACONTROL_END_BUFFIT_Pos;
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_DESC_LD_IT) >> USBHS_DEVDMACONTROL_DESC_LD_IT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index,
                                                                bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_DESC_LD_IT;
	tmp |= value << USBHS_DEVDMACONTROL_DESC_LD_IT_Pos;
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_BURST_LCK) >> USBHS_DEVDMACONTROL_BURST_LCK_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_BURST_LCK;
	tmp |= value << USBHS_DEVDMACONTROL_BURST_LCK_Pos;
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                                              hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= USBHS_DEVDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmacontrol_reg_t
hri_usbhs_get_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                           hri_usbhs_devdmacontrol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_BUFF_LENGTH(mask)) >> USBHS_DEVDMACONTROL_BUFF_LENGTH_Pos;
	return tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                                                hri_usbhs_devdmacontrol_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= ~USBHS_DEVDMACONTROL_BUFF_LENGTH_Msk;
	tmp |= USBHS_DEVDMACONTROL_BUFF_LENGTH(data);
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                                                hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~USBHS_DEVDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                                                 hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= USBHS_DEVDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmacontrol_reg_t hri_usbhs_read_DEVDMACONTROL_BUFF_LENGTH_bf(const void *const hw,
                                                                                        uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp = (tmp & USBHS_DEVDMACONTROL_BUFF_LENGTH_Msk) >> USBHS_DEVDMACONTROL_BUFF_LENGTH_Pos;
	return tmp;
}

static inline void hri_usbhs_set_DEVDMACONTROL_reg(const void *const hw, uint8_t submodule_index,
                                                   hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmacontrol_reg_t
hri_usbhs_get_DEVDMACONTROL_reg(const void *const hw, uint8_t submodule_index, hri_usbhs_devdmacontrol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_DEVDMACONTROL_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_devdmacontrol_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_DEVDMACONTROL_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_DEVDMACONTROL_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_usbhs_devdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmacontrol_reg_t hri_usbhs_read_DEVDMACONTROL_reg(const void *const hw,
                                                                             uint8_t           submodule_index)
{
	return ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMACONTROL;
}

static inline bool hri_usbhs_get_DEVDMASTATUS_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_CHANN_ENB)
	       >> USBHS_DEVDMASTATUS_CHANN_ENB_Pos;
}

static inline void hri_usbhs_clear_DEVDMASTATUS_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMASTATUS_CHANN_ACT_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_CHANN_ACT)
	       >> USBHS_DEVDMASTATUS_CHANN_ACT_Pos;
}

static inline void hri_usbhs_clear_DEVDMASTATUS_CHANN_ACT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_CHANN_ACT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMASTATUS_END_TR_ST_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_END_TR_ST)
	       >> USBHS_DEVDMASTATUS_END_TR_ST_Pos;
}

static inline void hri_usbhs_clear_DEVDMASTATUS_END_TR_ST_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_END_TR_ST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMASTATUS_END_BF_ST_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_END_BF_ST)
	       >> USBHS_DEVDMASTATUS_END_BF_ST_Pos;
}

static inline void hri_usbhs_clear_DEVDMASTATUS_END_BF_ST_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_END_BF_ST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_DEVDMASTATUS_DESC_LDST_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_DESC_LDST)
	       >> USBHS_DEVDMASTATUS_DESC_LDST_Pos;
}

static inline void hri_usbhs_clear_DEVDMASTATUS_DESC_LDST_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_DESC_LDST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmastatus_reg_t hri_usbhs_get_DEVDMASTATUS_BUFF_COUNT_bf(const void *const hw,
                                                                                    uint8_t           submodule_index,
                                                                                    hri_usbhs_devdmastatus_reg_t mask)
{
	return (((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_BUFF_COUNT(mask))
	       >> USBHS_DEVDMASTATUS_BUFF_COUNT_Pos;
}

static inline void hri_usbhs_clear_DEVDMASTATUS_BUFF_COUNT_bf(const void *const hw, uint8_t submodule_index,
                                                              hri_usbhs_devdmastatus_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS = USBHS_DEVDMASTATUS_BUFF_COUNT(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmastatus_reg_t hri_usbhs_read_DEVDMASTATUS_BUFF_COUNT_bf(const void *const hw,
                                                                                     uint8_t           submodule_index)
{
	return (((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS & USBHS_DEVDMASTATUS_BUFF_COUNT_Msk)
	       >> USBHS_DEVDMASTATUS_BUFF_COUNT_Pos;
}

static inline hri_usbhs_devdmastatus_reg_t hri_usbhs_get_DEVDMASTATUS_reg(const void *const hw, uint8_t submodule_index,
                                                                          hri_usbhs_devdmastatus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_clear_DEVDMASTATUS_reg(const void *const hw, uint8_t submodule_index,
                                                    hri_usbhs_devdmastatus_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS = mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_devdmastatus_reg_t hri_usbhs_read_DEVDMASTATUS_reg(const void *const hw,
                                                                           uint8_t           submodule_index)
{
	return ((Usbhs *)hw)->UsbhsDevdma[submodule_index].USBHS_DEVDMASTATUS;
}

static inline void hri_usbhshstdma_set_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const            hw,
                                                                   hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC |= USBHS_HSTDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmanxtdsc_reg_t
hri_usbhshstdma_get_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC;
	tmp = (tmp & USBHS_HSTDMANXTDSC_NXT_DSC_ADD(mask)) >> USBHS_HSTDMANXTDSC_NXT_DSC_ADD_Pos;
	return tmp;
}

static inline void hri_usbhshstdma_write_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const            hw,
                                                                     hri_usbhs_hstdmanxtdsc_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC;
	tmp &= ~USBHS_HSTDMANXTDSC_NXT_DSC_ADD_Msk;
	tmp |= USBHS_HSTDMANXTDSC_NXT_DSC_ADD(data);
	((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const            hw,
                                                                     hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC &= ~USBHS_HSTDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const            hw,
                                                                      hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC ^= USBHS_HSTDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmanxtdsc_reg_t hri_usbhshstdma_read_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC;
	tmp = (tmp & USBHS_HSTDMANXTDSC_NXT_DSC_ADD_Msk) >> USBHS_HSTDMANXTDSC_NXT_DSC_ADD_Pos;
	return tmp;
}

static inline void hri_usbhshstdma_set_HSTDMANXTDSC_reg(const void *const hw, hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmanxtdsc_reg_t hri_usbhshstdma_get_HSTDMANXTDSC_reg(const void *const            hw,
                                                                                hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhshstdma_write_HSTDMANXTDSC_reg(const void *const hw, hri_usbhs_hstdmanxtdsc_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMANXTDSC_reg(const void *const hw, hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMANXTDSC_reg(const void *const hw, hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmanxtdsc_reg_t hri_usbhshstdma_read_HSTDMANXTDSC_reg(const void *const hw)
{
	return ((UsbhsHstdma *)hw)->USBHS_HSTDMANXTDSC;
}

static inline void hri_usbhshstdma_set_HSTDMAADDRESS_BUFF_ADD_bf(const void *const             hw,
                                                                 hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS |= USBHS_HSTDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmaaddress_reg_t
hri_usbhshstdma_get_HSTDMAADDRESS_BUFF_ADD_bf(const void *const hw, hri_usbhs_hstdmaaddress_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS;
	tmp = (tmp & USBHS_HSTDMAADDRESS_BUFF_ADD(mask)) >> USBHS_HSTDMAADDRESS_BUFF_ADD_Pos;
	return tmp;
}

static inline void hri_usbhshstdma_write_HSTDMAADDRESS_BUFF_ADD_bf(const void *const             hw,
                                                                   hri_usbhs_hstdmaaddress_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS;
	tmp &= ~USBHS_HSTDMAADDRESS_BUFF_ADD_Msk;
	tmp |= USBHS_HSTDMAADDRESS_BUFF_ADD(data);
	((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMAADDRESS_BUFF_ADD_bf(const void *const             hw,
                                                                   hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS &= ~USBHS_HSTDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMAADDRESS_BUFF_ADD_bf(const void *const             hw,
                                                                    hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS ^= USBHS_HSTDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmaaddress_reg_t hri_usbhshstdma_read_HSTDMAADDRESS_BUFF_ADD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS;
	tmp = (tmp & USBHS_HSTDMAADDRESS_BUFF_ADD_Msk) >> USBHS_HSTDMAADDRESS_BUFF_ADD_Pos;
	return tmp;
}

static inline void hri_usbhshstdma_set_HSTDMAADDRESS_reg(const void *const hw, hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmaaddress_reg_t hri_usbhshstdma_get_HSTDMAADDRESS_reg(const void *const             hw,
                                                                                  hri_usbhs_hstdmaaddress_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhshstdma_write_HSTDMAADDRESS_reg(const void *const hw, hri_usbhs_hstdmaaddress_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMAADDRESS_reg(const void *const hw, hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMAADDRESS_reg(const void *const hw, hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmaaddress_reg_t hri_usbhshstdma_read_HSTDMAADDRESS_reg(const void *const hw)
{
	return ((UsbhsHstdma *)hw)->USBHS_HSTDMAADDRESS;
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_CHANN_ENB) >> USBHS_HSTDMACONTROL_CHANN_ENB_Pos;
	return (bool)tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_CHANN_ENB;
	tmp |= value << USBHS_HSTDMACONTROL_CHANN_ENB_Pos;
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_LDNXT_DSC) >> USBHS_HSTDMACONTROL_LDNXT_DSC_Pos;
	return (bool)tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_LDNXT_DSC;
	tmp |= value << USBHS_HSTDMACONTROL_LDNXT_DSC_Pos;
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_END_TR_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMACONTROL_END_TR_EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_END_TR_EN) >> USBHS_HSTDMACONTROL_END_TR_EN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_END_TR_EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_END_TR_EN;
	tmp |= value << USBHS_HSTDMACONTROL_END_TR_EN_Pos;
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_END_TR_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_END_TR_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_END_B_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMACONTROL_END_B_EN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_END_B_EN) >> USBHS_HSTDMACONTROL_END_B_EN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_END_B_EN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_END_B_EN;
	tmp |= value << USBHS_HSTDMACONTROL_END_B_EN_Pos;
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_END_B_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_END_B_EN_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_END_TR_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMACONTROL_END_TR_IT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_END_TR_IT) >> USBHS_HSTDMACONTROL_END_TR_IT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_END_TR_IT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_END_TR_IT;
	tmp |= value << USBHS_HSTDMACONTROL_END_TR_IT_Pos;
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_END_TR_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_END_TR_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_END_BUFFIT) >> USBHS_HSTDMACONTROL_END_BUFFIT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_END_BUFFIT;
	tmp |= value << USBHS_HSTDMACONTROL_END_BUFFIT_Pos;
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_DESC_LD_IT) >> USBHS_HSTDMACONTROL_DESC_LD_IT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_DESC_LD_IT;
	tmp |= value << USBHS_HSTDMACONTROL_DESC_LD_IT_Pos;
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_BURST_LCK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMACONTROL_BURST_LCK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_BURST_LCK) >> USBHS_HSTDMACONTROL_BURST_LCK_Pos;
	return (bool)tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_BURST_LCK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_BURST_LCK;
	tmp |= value << USBHS_HSTDMACONTROL_BURST_LCK_Pos;
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_BURST_LCK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_BURST_LCK_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const             hw,
                                                                    hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmacontrol_reg_t
hri_usbhshstdma_get_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const hw, hri_usbhs_hstdmacontrol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_BUFF_LENGTH(mask)) >> USBHS_HSTDMACONTROL_BUFF_LENGTH_Pos;
	return tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const             hw,
                                                                      hri_usbhs_hstdmacontrol_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_BUFF_LENGTH_Msk;
	tmp |= USBHS_HSTDMACONTROL_BUFF_LENGTH(data);
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const             hw,
                                                                      hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const             hw,
                                                                       hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmacontrol_reg_t hri_usbhshstdma_read_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_BUFF_LENGTH_Msk) >> USBHS_HSTDMACONTROL_BUFF_LENGTH_Pos;
	return tmp;
}

static inline void hri_usbhshstdma_set_HSTDMACONTROL_reg(const void *const hw, hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmacontrol_reg_t hri_usbhshstdma_get_HSTDMACONTROL_reg(const void *const             hw,
                                                                                  hri_usbhs_hstdmacontrol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhshstdma_write_HSTDMACONTROL_reg(const void *const hw, hri_usbhs_hstdmacontrol_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_clear_HSTDMACONTROL_reg(const void *const hw, hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhshstdma_toggle_HSTDMACONTROL_reg(const void *const hw, hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmacontrol_reg_t hri_usbhshstdma_read_HSTDMACONTROL_reg(const void *const hw)
{
	return ((UsbhsHstdma *)hw)->USBHS_HSTDMACONTROL;
}

static inline bool hri_usbhshstdma_get_HSTDMASTATUS_CHANN_ENB_bit(const void *const hw)
{
	return (((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_CHANN_ENB) >> USBHS_HSTDMASTATUS_CHANN_ENB_Pos;
}

static inline void hri_usbhshstdma_clear_HSTDMASTATUS_CHANN_ENB_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMASTATUS_CHANN_ACT_bit(const void *const hw)
{
	return (((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_CHANN_ACT) >> USBHS_HSTDMASTATUS_CHANN_ACT_Pos;
}

static inline void hri_usbhshstdma_clear_HSTDMASTATUS_CHANN_ACT_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_CHANN_ACT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMASTATUS_END_TR_ST_bit(const void *const hw)
{
	return (((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_END_TR_ST) >> USBHS_HSTDMASTATUS_END_TR_ST_Pos;
}

static inline void hri_usbhshstdma_clear_HSTDMASTATUS_END_TR_ST_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_END_TR_ST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMASTATUS_END_BF_ST_bit(const void *const hw)
{
	return (((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_END_BF_ST) >> USBHS_HSTDMASTATUS_END_BF_ST_Pos;
}

static inline void hri_usbhshstdma_clear_HSTDMASTATUS_END_BF_ST_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_END_BF_ST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhshstdma_get_HSTDMASTATUS_DESC_LDST_bit(const void *const hw)
{
	return (((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_DESC_LDST) >> USBHS_HSTDMASTATUS_DESC_LDST_Pos;
}

static inline void hri_usbhshstdma_clear_HSTDMASTATUS_DESC_LDST_bit(const void *const hw)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_DESC_LDST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmastatus_reg_t
hri_usbhshstdma_get_HSTDMASTATUS_BUFF_COUNT_bf(const void *const hw, hri_usbhs_hstdmastatus_reg_t mask)
{
	return (((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_BUFF_COUNT(mask))
	       >> USBHS_HSTDMASTATUS_BUFF_COUNT_Pos;
}

static inline void hri_usbhshstdma_clear_HSTDMASTATUS_BUFF_COUNT_bf(const void *const            hw,
                                                                    hri_usbhs_hstdmastatus_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_BUFF_COUNT(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmastatus_reg_t hri_usbhshstdma_read_HSTDMASTATUS_BUFF_COUNT_bf(const void *const hw)
{
	return (((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_BUFF_COUNT_Msk)
	       >> USBHS_HSTDMASTATUS_BUFF_COUNT_Pos;
}

static inline hri_usbhs_hstdmastatus_reg_t hri_usbhshstdma_get_HSTDMASTATUS_reg(const void *const            hw,
                                                                                hri_usbhs_hstdmastatus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhshstdma_clear_HSTDMASTATUS_reg(const void *const hw, hri_usbhs_hstdmastatus_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS = mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmastatus_reg_t hri_usbhshstdma_read_HSTDMASTATUS_reg(const void *const hw)
{
	return ((UsbhsHstdma *)hw)->USBHS_HSTDMASTATUS;
}

static inline void hri_usbhs_set_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                             hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC |= USBHS_HSTDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmanxtdsc_reg_t hri_usbhs_get_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw,
                                                                                     uint8_t           submodule_index,
                                                                                     hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC;
	tmp = (tmp & USBHS_HSTDMANXTDSC_NXT_DSC_ADD(mask)) >> USBHS_HSTDMANXTDSC_NXT_DSC_ADD_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                               hri_usbhs_hstdmanxtdsc_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC;
	tmp &= ~USBHS_HSTDMANXTDSC_NXT_DSC_ADD_Msk;
	tmp |= USBHS_HSTDMANXTDSC_NXT_DSC_ADD(data);
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                               hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC &= ~USBHS_HSTDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                                hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC ^= USBHS_HSTDMANXTDSC_NXT_DSC_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmanxtdsc_reg_t hri_usbhs_read_HSTDMANXTDSC_NXT_DSC_ADD_bf(const void *const hw,
                                                                                      uint8_t           submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC;
	tmp = (tmp & USBHS_HSTDMANXTDSC_NXT_DSC_ADD_Msk) >> USBHS_HSTDMANXTDSC_NXT_DSC_ADD_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                  hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmanxtdsc_reg_t hri_usbhs_get_HSTDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                                          hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                    hri_usbhs_hstdmanxtdsc_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                    hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMANXTDSC_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_hstdmanxtdsc_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmanxtdsc_reg_t hri_usbhs_read_HSTDMANXTDSC_reg(const void *const hw,
                                                                           uint8_t           submodule_index)
{
	return ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMANXTDSC;
}

static inline void hri_usbhs_set_HSTDMAADDRESS_BUFF_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                           hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS |= USBHS_HSTDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmaaddress_reg_t hri_usbhs_get_HSTDMAADDRESS_BUFF_ADD_bf(const void *const hw,
                                                                                    uint8_t           submodule_index,
                                                                                    hri_usbhs_hstdmaaddress_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS;
	tmp = (tmp & USBHS_HSTDMAADDRESS_BUFF_ADD(mask)) >> USBHS_HSTDMAADDRESS_BUFF_ADD_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTDMAADDRESS_BUFF_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                             hri_usbhs_hstdmaaddress_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS;
	tmp &= ~USBHS_HSTDMAADDRESS_BUFF_ADD_Msk;
	tmp |= USBHS_HSTDMAADDRESS_BUFF_ADD(data);
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMAADDRESS_BUFF_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                             hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS &= ~USBHS_HSTDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMAADDRESS_BUFF_ADD_bf(const void *const hw, uint8_t submodule_index,
                                                              hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS ^= USBHS_HSTDMAADDRESS_BUFF_ADD(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmaaddress_reg_t hri_usbhs_read_HSTDMAADDRESS_BUFF_ADD_bf(const void *const hw,
                                                                                     uint8_t           submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS;
	tmp = (tmp & USBHS_HSTDMAADDRESS_BUFF_ADD_Msk) >> USBHS_HSTDMAADDRESS_BUFF_ADD_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTDMAADDRESS_reg(const void *const hw, uint8_t submodule_index,
                                                   hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmaaddress_reg_t
hri_usbhs_get_HSTDMAADDRESS_reg(const void *const hw, uint8_t submodule_index, hri_usbhs_hstdmaaddress_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTDMAADDRESS_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_hstdmaaddress_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMAADDRESS_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMAADDRESS_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_usbhs_hstdmaaddress_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmaaddress_reg_t hri_usbhs_read_HSTDMAADDRESS_reg(const void *const hw,
                                                                             uint8_t           submodule_index)
{
	return ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMAADDRESS;
}

static inline void hri_usbhs_set_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_CHANN_ENB) >> USBHS_HSTDMACONTROL_CHANN_ENB_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_CHANN_ENB;
	tmp |= value << USBHS_HSTDMACONTROL_CHANN_ENB_Pos;
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_LDNXT_DSC) >> USBHS_HSTDMACONTROL_LDNXT_DSC_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_LDNXT_DSC;
	tmp |= value << USBHS_HSTDMACONTROL_LDNXT_DSC_Pos;
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_LDNXT_DSC_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_LDNXT_DSC;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_END_TR_EN) >> USBHS_HSTDMACONTROL_END_TR_EN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_END_TR_EN;
	tmp |= value << USBHS_HSTDMACONTROL_END_TR_EN_Pos;
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_END_TR_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_END_TR_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_END_B_EN) >> USBHS_HSTDMACONTROL_END_B_EN_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_END_B_EN;
	tmp |= value << USBHS_HSTDMACONTROL_END_B_EN_Pos;
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_END_B_EN_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_END_B_EN;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_END_TR_IT) >> USBHS_HSTDMACONTROL_END_TR_IT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_END_TR_IT;
	tmp |= value << USBHS_HSTDMACONTROL_END_TR_IT_Pos;
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_END_TR_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_END_TR_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_END_BUFFIT) >> USBHS_HSTDMACONTROL_END_BUFFIT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index,
                                                                bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_END_BUFFIT;
	tmp |= value << USBHS_HSTDMACONTROL_END_BUFFIT_Pos;
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_END_BUFFIT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_END_BUFFIT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_DESC_LD_IT) >> USBHS_HSTDMACONTROL_DESC_LD_IT_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index,
                                                                bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_DESC_LD_IT;
	tmp |= value << USBHS_HSTDMACONTROL_DESC_LD_IT_Pos;
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_DESC_LD_IT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_DESC_LD_IT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_BURST_LCK) >> USBHS_HSTDMACONTROL_BURST_LCK_Pos;
	return (bool)tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index,
                                                               bool value)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_BURST_LCK;
	tmp |= value << USBHS_HSTDMACONTROL_BURST_LCK_Pos;
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_BURST_LCK_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_BURST_LCK;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_set_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                                              hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= USBHS_HSTDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmacontrol_reg_t
hri_usbhs_get_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                           hri_usbhs_hstdmacontrol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_BUFF_LENGTH(mask)) >> USBHS_HSTDMACONTROL_BUFF_LENGTH_Pos;
	return tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                                                hri_usbhs_hstdmacontrol_reg_t data)
{
	uint32_t tmp;
	USBHS_CRITICAL_SECTION_ENTER();
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= ~USBHS_HSTDMACONTROL_BUFF_LENGTH_Msk;
	tmp |= USBHS_HSTDMACONTROL_BUFF_LENGTH(data);
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = tmp;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                                                hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~USBHS_HSTDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const hw, uint8_t submodule_index,
                                                                 hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= USBHS_HSTDMACONTROL_BUFF_LENGTH(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmacontrol_reg_t hri_usbhs_read_HSTDMACONTROL_BUFF_LENGTH_bf(const void *const hw,
                                                                                        uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp = (tmp & USBHS_HSTDMACONTROL_BUFF_LENGTH_Msk) >> USBHS_HSTDMACONTROL_BUFF_LENGTH_Pos;
	return tmp;
}

static inline void hri_usbhs_set_HSTDMACONTROL_reg(const void *const hw, uint8_t submodule_index,
                                                   hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL |= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmacontrol_reg_t
hri_usbhs_get_HSTDMACONTROL_reg(const void *const hw, uint8_t submodule_index, hri_usbhs_hstdmacontrol_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_write_HSTDMACONTROL_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_hstdmacontrol_reg_t data)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL = data;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_clear_HSTDMACONTROL_reg(const void *const hw, uint8_t submodule_index,
                                                     hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL &= ~mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline void hri_usbhs_toggle_HSTDMACONTROL_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_usbhs_hstdmacontrol_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL ^= mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmacontrol_reg_t hri_usbhs_read_HSTDMACONTROL_reg(const void *const hw,
                                                                             uint8_t           submodule_index)
{
	return ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMACONTROL;
}

static inline bool hri_usbhs_get_HSTDMASTATUS_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_CHANN_ENB)
	       >> USBHS_HSTDMASTATUS_CHANN_ENB_Pos;
}

static inline void hri_usbhs_clear_HSTDMASTATUS_CHANN_ENB_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_CHANN_ENB;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMASTATUS_CHANN_ACT_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_CHANN_ACT)
	       >> USBHS_HSTDMASTATUS_CHANN_ACT_Pos;
}

static inline void hri_usbhs_clear_HSTDMASTATUS_CHANN_ACT_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_CHANN_ACT;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMASTATUS_END_TR_ST_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_END_TR_ST)
	       >> USBHS_HSTDMASTATUS_END_TR_ST_Pos;
}

static inline void hri_usbhs_clear_HSTDMASTATUS_END_TR_ST_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_END_TR_ST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMASTATUS_END_BF_ST_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_END_BF_ST)
	       >> USBHS_HSTDMASTATUS_END_BF_ST_Pos;
}

static inline void hri_usbhs_clear_HSTDMASTATUS_END_BF_ST_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_END_BF_ST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_usbhs_get_HSTDMASTATUS_DESC_LDST_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_DESC_LDST)
	       >> USBHS_HSTDMASTATUS_DESC_LDST_Pos;
}

static inline void hri_usbhs_clear_HSTDMASTATUS_DESC_LDST_bit(const void *const hw, uint8_t submodule_index)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_DESC_LDST;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmastatus_reg_t hri_usbhs_get_HSTDMASTATUS_BUFF_COUNT_bf(const void *const hw,
                                                                                    uint8_t           submodule_index,
                                                                                    hri_usbhs_hstdmastatus_reg_t mask)
{
	return (((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_BUFF_COUNT(mask))
	       >> USBHS_HSTDMASTATUS_BUFF_COUNT_Pos;
}

static inline void hri_usbhs_clear_HSTDMASTATUS_BUFF_COUNT_bf(const void *const hw, uint8_t submodule_index,
                                                              hri_usbhs_hstdmastatus_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS = USBHS_HSTDMASTATUS_BUFF_COUNT(mask);
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmastatus_reg_t hri_usbhs_read_HSTDMASTATUS_BUFF_COUNT_bf(const void *const hw,
                                                                                     uint8_t           submodule_index)
{
	return (((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS & USBHS_HSTDMASTATUS_BUFF_COUNT_Msk)
	       >> USBHS_HSTDMASTATUS_BUFF_COUNT_Pos;
}

static inline hri_usbhs_hstdmastatus_reg_t hri_usbhs_get_HSTDMASTATUS_reg(const void *const hw, uint8_t submodule_index,
                                                                          hri_usbhs_hstdmastatus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS;
	tmp &= mask;
	return tmp;
}

static inline void hri_usbhs_clear_HSTDMASTATUS_reg(const void *const hw, uint8_t submodule_index,
                                                    hri_usbhs_hstdmastatus_reg_t mask)
{
	USBHS_CRITICAL_SECTION_ENTER();
	((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS = mask;
	USBHS_CRITICAL_SECTION_LEAVE();
}

static inline hri_usbhs_hstdmastatus_reg_t hri_usbhs_read_HSTDMASTATUS_reg(const void *const hw,
                                                                           uint8_t           submodule_index)
{
	return ((Usbhs *)hw)->UsbhsHstdma[submodule_index].USBHS_HSTDMASTATUS;
}

/* Below section is for legacy hri apis name, not recommended to use below left side apis in application */
#define hri_usbhs_get_DEVEPTISR_RXSTPI_bit(a, b) hri_usbhs_get_DEVEPTISR_CTRL_RXSTPI_bit(a, b)
#define hri_usbhs_clear_DEVEPTISR_RXSTPI_bit(a, b) hri_usbhs_clear_DEVEPTISR_CTRL_RXSTPI_bit(a, b)
#define hri_usbhs_get_DEVEPTISR_NAKOUTI_bit(a, b) hri_usbhs_get_DEVEPTISR_CTRL_NAKOUTI_bit(a, b)
#define hri_usbhs_clear_DEVEPTISR_NAKOUTI_bit(a, b) hri_usbhs_clear_DEVEPTISR_CTRL_NAKOUTI_bit(a, b)
#define hri_usbhs_get_DEVEPTISR_NAKINI_bit(a, b) hri_usbhs_get_DEVEPTISR_CTRL_NAKINI_bit(a, b)
#define hri_usbhs_clear_DEVEPTISR_NAKINI_bit(a, b) hri_usbhs_clear_DEVEPTISR_CTRL_NAKINI_bit(a, b)
#define hri_usbhs_get_DEVEPTISR_STALLEDI_bit(a, b) hri_usbhs_get_DEVEPTISR_CTRL_STALLEDI_bit(a, b)
#define hri_usbhs_clear_DEVEPTISR_STALLEDI_bit(a, b) hri_usbhs_clear_DEVEPTISR_CTRL_STALLEDI_bit(a, b)
#define hri_usbhs_get_DEVEPTISR_CTRLDIR_bit(a, b) hri_usbhs_get_DEVEPTISR_CTRL_CTRLDIR_bit(a, b)
#define hri_usbhs_get_HSTPIPISR_TXSTPI_bit(a, b) hri_usbhs_get_HSTPIPISR_CTRL_TXSTPI_bit(a, b)
#define hri_usbhs_clear_HSTPIPISR_TXSTPI_bit(a, b) hri_usbhs_clear_HSTPIPISR_CTRL_TXSTPI_bit(a, b)
#define hri_usbhs_get_HSTPIPISR_RXSTALLDI_bit(a, b) hri_usbhs_get_HSTPIPISR_CTRL_RXSTALLDI_bit(a, b)
#define hri_usbhs_clear_HSTPIPISR_RXSTALLDI_bit(a, b) hri_usbhs_clear_HSTPIPISR_CTRL_RXSTALLDI_bit(a, b)
#define hri_usbhs_get_DEVEPTIMR_RXSTPE_bit(a, b) hri_usbhs_get_DEVEPTIMR_CTRL_RXSTPE_bit(a, b)
#define hri_usbhs_get_DEVEPTIMR_NAKOUTE_bit(a, b) hri_usbhs_get_DEVEPTIMR_CTRL_NAKOUTE_bit(a, b)
#define hri_usbhs_get_DEVEPTIMR_NAKINE_bit(a, b) hri_usbhs_get_DEVEPTIMR_CTRL_NAKINE_bit(a, b)
#define hri_usbhs_get_DEVEPTIMR_STALLEDE_bit(a, b) hri_usbhs_get_DEVEPTIMR_CTRL_STALLEDE_bit(a, b)
#define hri_usbhs_get_DEVEPTIMR_NYETDIS_bit(a, b) hri_usbhs_get_DEVEPTIMR_CTRL_NYETDIS_bit(a, b)
#define hri_usbhs_get_DEVEPTIMR_STALLRQ_bit(a, b) hri_usbhs_get_DEVEPTIMR_CTRL_STALLRQ_bit(a, b)
#define hri_usbhs_get_HSTPIPIMR_TXSTPE_bit(a, b) hri_usbhs_get_HSTPIPIMR_CTRL_TXSTPE_bit(a, b)
#define hri_usbhs_get_HSTPIPIMR_RXSTALLDE_bit(a, b) hri_usbhs_get_HSTPIPIMR_CTRL_RXSTALLDE_bit(a, b)

#ifdef __cplusplus
}
#endif

#endif /* _HRI_USBHS_E70B_H_INCLUDED */
#endif /* _SAME70_USBHS_COMPONENT_ */
