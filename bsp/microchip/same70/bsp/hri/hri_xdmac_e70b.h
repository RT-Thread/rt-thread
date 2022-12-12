/**
 * \file
 *
 * \brief SAM XDMAC
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

#ifdef _SAME70_XDMAC_COMPONENT_
#ifndef _HRI_XDMAC_E70B_H_INCLUDED_
#define _HRI_XDMAC_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_XDMAC_CRITICAL_SECTIONS)
#define XDMAC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define XDMAC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define XDMAC_CRITICAL_SECTION_ENTER()
#define XDMAC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_xdmac_cbc_reg_t;
typedef uint32_t hri_xdmac_cc_reg_t;
typedef uint32_t hri_xdmac_cda_reg_t;
typedef uint32_t hri_xdmac_cds_msp_reg_t;
typedef uint32_t hri_xdmac_cdus_reg_t;
typedef uint32_t hri_xdmac_cim_reg_t;
typedef uint32_t hri_xdmac_cis_reg_t;
typedef uint32_t hri_xdmac_cnda_reg_t;
typedef uint32_t hri_xdmac_cndc_reg_t;
typedef uint32_t hri_xdmac_csa_reg_t;
typedef uint32_t hri_xdmac_csus_reg_t;
typedef uint32_t hri_xdmac_cubc_reg_t;
typedef uint32_t hri_xdmac_gcfg_reg_t;
typedef uint32_t hri_xdmac_gim_reg_t;
typedef uint32_t hri_xdmac_gis_reg_t;
typedef uint32_t hri_xdmac_grs_reg_t;
typedef uint32_t hri_xdmac_grwr_reg_t;
typedef uint32_t hri_xdmac_grws_reg_t;
typedef uint32_t hri_xdmac_gs_reg_t;
typedef uint32_t hri_xdmac_gswf_reg_t;
typedef uint32_t hri_xdmac_gswr_reg_t;
typedef uint32_t hri_xdmac_gsws_reg_t;
typedef uint32_t hri_xdmac_gtype_reg_t;
typedef uint32_t hri_xdmac_gwac_reg_t;
typedef uint32_t hri_xdmac_gws_reg_t;
typedef uint32_t hri_xdmacchid_cbc_reg_t;
typedef uint32_t hri_xdmacchid_cc_reg_t;
typedef uint32_t hri_xdmacchid_cda_reg_t;
typedef uint32_t hri_xdmacchid_cds_msp_reg_t;
typedef uint32_t hri_xdmacchid_cdus_reg_t;
typedef uint32_t hri_xdmacchid_cis_reg_t;
typedef uint32_t hri_xdmacchid_cnda_reg_t;
typedef uint32_t hri_xdmacchid_cndc_reg_t;
typedef uint32_t hri_xdmacchid_csa_reg_t;
typedef uint32_t hri_xdmacchid_csus_reg_t;
typedef uint32_t hri_xdmacchid_cubc_reg_t;
typedef uint32_t hri_xdmacchid_xdmac_cim_reg_t;

static inline void hri_xdmacchid_set_CIM_BIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_BIM;
}

static inline bool hri_xdmacchid_get_CIM_BIM_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIM & XDMAC_CIM_BIM) >> XDMAC_CIM_BIM_Pos;
}

static inline void hri_xdmacchid_write_CIM_BIM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_BIM;
	} else {
		((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_BIM;
	}
}

static inline void hri_xdmacchid_clear_CIM_BIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_BIM;
}

static inline void hri_xdmacchid_set_CIM_LIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_LIM;
}

static inline bool hri_xdmacchid_get_CIM_LIM_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIM & XDMAC_CIM_LIM) >> XDMAC_CIM_LIM_Pos;
}

static inline void hri_xdmacchid_write_CIM_LIM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_LIM;
	} else {
		((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_LIM;
	}
}

static inline void hri_xdmacchid_clear_CIM_LIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_LIM;
}

static inline void hri_xdmacchid_set_CIM_DIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_DIM;
}

static inline bool hri_xdmacchid_get_CIM_DIM_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIM & XDMAC_CIM_DIM) >> XDMAC_CIM_DIM_Pos;
}

static inline void hri_xdmacchid_write_CIM_DIM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_DIM;
	} else {
		((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_DIM;
	}
}

static inline void hri_xdmacchid_clear_CIM_DIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_DIM;
}

static inline void hri_xdmacchid_set_CIM_FIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_FIM;
}

static inline bool hri_xdmacchid_get_CIM_FIM_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIM & XDMAC_CIM_FIM) >> XDMAC_CIM_FIM_Pos;
}

static inline void hri_xdmacchid_write_CIM_FIM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_FIM;
	} else {
		((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_FIM;
	}
}

static inline void hri_xdmacchid_clear_CIM_FIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_FIM;
}

static inline void hri_xdmacchid_set_CIM_RBEIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_RBEIM;
}

static inline bool hri_xdmacchid_get_CIM_RBEIM_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIM & XDMAC_CIM_RBEIM) >> XDMAC_CIM_RBEIM_Pos;
}

static inline void hri_xdmacchid_write_CIM_RBEIM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_RBEIM;
	} else {
		((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_RBEIM;
	}
}

static inline void hri_xdmacchid_clear_CIM_RBEIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_RBEIM;
}

static inline void hri_xdmacchid_set_CIM_WBEIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_WBEIM;
}

static inline bool hri_xdmacchid_get_CIM_WBEIM_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIM & XDMAC_CIM_WBEIM) >> XDMAC_CIM_WBEIM_Pos;
}

static inline void hri_xdmacchid_write_CIM_WBEIM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_WBEIM;
	} else {
		((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_WBEIM;
	}
}

static inline void hri_xdmacchid_clear_CIM_WBEIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_WBEIM;
}

static inline void hri_xdmacchid_set_CIM_ROIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_ROIM;
}

static inline bool hri_xdmacchid_get_CIM_ROIM_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIM & XDMAC_CIM_ROIM) >> XDMAC_CIM_ROIM_Pos;
}

static inline void hri_xdmacchid_write_CIM_ROIM_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_ROIM;
	} else {
		((XdmacChid *)hw)->XDMAC_CIE = XDMAC_CIM_ROIM;
	}
}

static inline void hri_xdmacchid_clear_CIM_ROIM_bit(const void *const hw)
{
	((XdmacChid *)hw)->XDMAC_CID = XDMAC_CIM_ROIM;
}

static inline void hri_xdmacchid_set_CIM_reg(const void *const hw, hri_xdmac_cim_reg_t mask)
{
	((XdmacChid *)hw)->XDMAC_CIE = mask;
}

static inline hri_xdmac_cim_reg_t hri_xdmacchid_get_CIM_reg(const void *const hw, hri_xdmac_cim_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CIM;
	tmp &= mask;
	return tmp;
}

static inline hri_xdmac_cim_reg_t hri_xdmacchid_read_CIM_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CIM;
}

static inline void hri_xdmacchid_write_CIM_reg(const void *const hw, hri_xdmac_cim_reg_t data)
{
	((XdmacChid *)hw)->XDMAC_CIE = data;
	((XdmacChid *)hw)->XDMAC_CID = ~data;
}

static inline void hri_xdmacchid_clear_CIM_reg(const void *const hw, hri_xdmac_cim_reg_t mask)
{
	((XdmacChid *)hw)->XDMAC_CID = mask;
}

static inline bool hri_xdmacchid_get_CIS_BIS_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIS & XDMAC_CIS_BIS) > 0;
}

static inline bool hri_xdmacchid_get_CIS_LIS_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIS & XDMAC_CIS_LIS) > 0;
}

static inline bool hri_xdmacchid_get_CIS_DIS_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIS & XDMAC_CIS_DIS) > 0;
}

static inline bool hri_xdmacchid_get_CIS_FIS_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIS & XDMAC_CIS_FIS) > 0;
}

static inline bool hri_xdmacchid_get_CIS_RBEIS_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIS & XDMAC_CIS_RBEIS) > 0;
}

static inline bool hri_xdmacchid_get_CIS_WBEIS_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIS & XDMAC_CIS_WBEIS) > 0;
}

static inline bool hri_xdmacchid_get_CIS_ROIS_bit(const void *const hw)
{
	return (((XdmacChid *)hw)->XDMAC_CIS & XDMAC_CIS_ROIS) > 0;
}

static inline hri_xdmac_cis_reg_t hri_xdmacchid_get_CIS_reg(const void *const hw, hri_xdmac_cis_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CIS;
	tmp &= mask;
	return tmp;
}

static inline hri_xdmac_cis_reg_t hri_xdmacchid_read_CIS_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CIS;
}

static inline void hri_xdmacchid_set_CSA_SA_bf(const void *const hw, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSA |= XDMAC_CSA_SA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csa_reg_t hri_xdmacchid_get_CSA_SA_bf(const void *const hw, hri_xdmac_csa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CSA;
	tmp = (tmp & XDMAC_CSA_SA(mask)) >> XDMAC_CSA_SA_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CSA_SA_bf(const void *const hw, hri_xdmac_csa_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CSA;
	tmp &= ~XDMAC_CSA_SA_Msk;
	tmp |= XDMAC_CSA_SA(data);
	((XdmacChid *)hw)->XDMAC_CSA = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CSA_SA_bf(const void *const hw, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSA &= ~XDMAC_CSA_SA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CSA_SA_bf(const void *const hw, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSA ^= XDMAC_CSA_SA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csa_reg_t hri_xdmacchid_read_CSA_SA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CSA;
	tmp = (tmp & XDMAC_CSA_SA_Msk) >> XDMAC_CSA_SA_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CSA_reg(const void *const hw, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSA |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csa_reg_t hri_xdmacchid_get_CSA_reg(const void *const hw, hri_xdmac_csa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CSA;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CSA_reg(const void *const hw, hri_xdmac_csa_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSA = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CSA_reg(const void *const hw, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSA &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CSA_reg(const void *const hw, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSA ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csa_reg_t hri_xdmacchid_read_CSA_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CSA;
}

static inline void hri_xdmacchid_set_CDA_DA_bf(const void *const hw, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDA |= XDMAC_CDA_DA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cda_reg_t hri_xdmacchid_get_CDA_DA_bf(const void *const hw, hri_xdmac_cda_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDA;
	tmp = (tmp & XDMAC_CDA_DA(mask)) >> XDMAC_CDA_DA_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CDA_DA_bf(const void *const hw, hri_xdmac_cda_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CDA;
	tmp &= ~XDMAC_CDA_DA_Msk;
	tmp |= XDMAC_CDA_DA(data);
	((XdmacChid *)hw)->XDMAC_CDA = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CDA_DA_bf(const void *const hw, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDA &= ~XDMAC_CDA_DA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CDA_DA_bf(const void *const hw, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDA ^= XDMAC_CDA_DA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cda_reg_t hri_xdmacchid_read_CDA_DA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDA;
	tmp = (tmp & XDMAC_CDA_DA_Msk) >> XDMAC_CDA_DA_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CDA_reg(const void *const hw, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDA |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cda_reg_t hri_xdmacchid_get_CDA_reg(const void *const hw, hri_xdmac_cda_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDA;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CDA_reg(const void *const hw, hri_xdmac_cda_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDA = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CDA_reg(const void *const hw, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDA &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CDA_reg(const void *const hw, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDA ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cda_reg_t hri_xdmacchid_read_CDA_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CDA;
}

static inline void hri_xdmacchid_set_CNDA_NDAIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA |= XDMAC_CNDA_NDAIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CNDA_NDAIF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDA;
	tmp = (tmp & XDMAC_CNDA_NDAIF) >> XDMAC_CNDA_NDAIF_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CNDA_NDAIF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CNDA;
	tmp &= ~XDMAC_CNDA_NDAIF;
	tmp |= value << XDMAC_CNDA_NDAIF_Pos;
	((XdmacChid *)hw)->XDMAC_CNDA = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CNDA_NDAIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA &= ~XDMAC_CNDA_NDAIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CNDA_NDAIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA ^= XDMAC_CNDA_NDAIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CNDA_NDA_bf(const void *const hw, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA |= XDMAC_CNDA_NDA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cnda_reg_t hri_xdmacchid_get_CNDA_NDA_bf(const void *const hw, hri_xdmac_cnda_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDA;
	tmp = (tmp & XDMAC_CNDA_NDA(mask)) >> XDMAC_CNDA_NDA_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CNDA_NDA_bf(const void *const hw, hri_xdmac_cnda_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CNDA;
	tmp &= ~XDMAC_CNDA_NDA_Msk;
	tmp |= XDMAC_CNDA_NDA(data);
	((XdmacChid *)hw)->XDMAC_CNDA = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CNDA_NDA_bf(const void *const hw, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA &= ~XDMAC_CNDA_NDA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CNDA_NDA_bf(const void *const hw, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA ^= XDMAC_CNDA_NDA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cnda_reg_t hri_xdmacchid_read_CNDA_NDA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDA;
	tmp = (tmp & XDMAC_CNDA_NDA_Msk) >> XDMAC_CNDA_NDA_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CNDA_reg(const void *const hw, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cnda_reg_t hri_xdmacchid_get_CNDA_reg(const void *const hw, hri_xdmac_cnda_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDA;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CNDA_reg(const void *const hw, hri_xdmac_cnda_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CNDA_reg(const void *const hw, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CNDA_reg(const void *const hw, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDA ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cnda_reg_t hri_xdmacchid_read_CNDA_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CNDA;
}

static inline void hri_xdmacchid_set_CNDC_NDE_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC |= XDMAC_CNDC_NDE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CNDC_NDE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDE) >> XDMAC_CNDC_NDE_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CNDC_NDE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp &= ~XDMAC_CNDC_NDE;
	tmp |= value << XDMAC_CNDC_NDE_Pos;
	((XdmacChid *)hw)->XDMAC_CNDC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CNDC_NDE_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC &= ~XDMAC_CNDC_NDE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CNDC_NDE_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC ^= XDMAC_CNDC_NDE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CNDC_NDSUP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC |= XDMAC_CNDC_NDSUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CNDC_NDSUP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDSUP) >> XDMAC_CNDC_NDSUP_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CNDC_NDSUP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp &= ~XDMAC_CNDC_NDSUP;
	tmp |= value << XDMAC_CNDC_NDSUP_Pos;
	((XdmacChid *)hw)->XDMAC_CNDC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CNDC_NDSUP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC &= ~XDMAC_CNDC_NDSUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CNDC_NDSUP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC ^= XDMAC_CNDC_NDSUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CNDC_NDDUP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC |= XDMAC_CNDC_NDDUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CNDC_NDDUP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDDUP) >> XDMAC_CNDC_NDDUP_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CNDC_NDDUP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp &= ~XDMAC_CNDC_NDDUP;
	tmp |= value << XDMAC_CNDC_NDDUP_Pos;
	((XdmacChid *)hw)->XDMAC_CNDC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CNDC_NDDUP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC &= ~XDMAC_CNDC_NDDUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CNDC_NDDUP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC ^= XDMAC_CNDC_NDDUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CNDC_NDVIEW_bf(const void *const hw, hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC |= XDMAC_CNDC_NDVIEW(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cndc_reg_t hri_xdmacchid_get_CNDC_NDVIEW_bf(const void *const hw, hri_xdmac_cndc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDVIEW(mask)) >> XDMAC_CNDC_NDVIEW_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CNDC_NDVIEW_bf(const void *const hw, hri_xdmac_cndc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp &= ~XDMAC_CNDC_NDVIEW_Msk;
	tmp |= XDMAC_CNDC_NDVIEW(data);
	((XdmacChid *)hw)->XDMAC_CNDC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CNDC_NDVIEW_bf(const void *const hw, hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC &= ~XDMAC_CNDC_NDVIEW(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CNDC_NDVIEW_bf(const void *const hw, hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC ^= XDMAC_CNDC_NDVIEW(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cndc_reg_t hri_xdmacchid_read_CNDC_NDVIEW_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDVIEW_Msk) >> XDMAC_CNDC_NDVIEW_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CNDC_reg(const void *const hw, hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cndc_reg_t hri_xdmacchid_get_CNDC_reg(const void *const hw, hri_xdmac_cndc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CNDC;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CNDC_reg(const void *const hw, hri_xdmac_cndc_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CNDC_reg(const void *const hw, hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CNDC_reg(const void *const hw, hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CNDC ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cndc_reg_t hri_xdmacchid_read_CNDC_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CNDC;
}

static inline void hri_xdmacchid_set_CUBC_UBLEN_bf(const void *const hw, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CUBC |= XDMAC_CUBC_UBLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cubc_reg_t hri_xdmacchid_get_CUBC_UBLEN_bf(const void *const hw, hri_xdmac_cubc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CUBC;
	tmp = (tmp & XDMAC_CUBC_UBLEN(mask)) >> XDMAC_CUBC_UBLEN_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CUBC_UBLEN_bf(const void *const hw, hri_xdmac_cubc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CUBC;
	tmp &= ~XDMAC_CUBC_UBLEN_Msk;
	tmp |= XDMAC_CUBC_UBLEN(data);
	((XdmacChid *)hw)->XDMAC_CUBC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CUBC_UBLEN_bf(const void *const hw, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CUBC &= ~XDMAC_CUBC_UBLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CUBC_UBLEN_bf(const void *const hw, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CUBC ^= XDMAC_CUBC_UBLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cubc_reg_t hri_xdmacchid_read_CUBC_UBLEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CUBC;
	tmp = (tmp & XDMAC_CUBC_UBLEN_Msk) >> XDMAC_CUBC_UBLEN_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CUBC_reg(const void *const hw, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CUBC |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cubc_reg_t hri_xdmacchid_get_CUBC_reg(const void *const hw, hri_xdmac_cubc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CUBC;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CUBC_reg(const void *const hw, hri_xdmac_cubc_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CUBC = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CUBC_reg(const void *const hw, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CUBC &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CUBC_reg(const void *const hw, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CUBC ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cubc_reg_t hri_xdmacchid_read_CUBC_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CUBC;
}

static inline void hri_xdmacchid_set_CBC_BLEN_bf(const void *const hw, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CBC |= XDMAC_CBC_BLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cbc_reg_t hri_xdmacchid_get_CBC_BLEN_bf(const void *const hw, hri_xdmac_cbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CBC;
	tmp = (tmp & XDMAC_CBC_BLEN(mask)) >> XDMAC_CBC_BLEN_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CBC_BLEN_bf(const void *const hw, hri_xdmac_cbc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CBC;
	tmp &= ~XDMAC_CBC_BLEN_Msk;
	tmp |= XDMAC_CBC_BLEN(data);
	((XdmacChid *)hw)->XDMAC_CBC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CBC_BLEN_bf(const void *const hw, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CBC &= ~XDMAC_CBC_BLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CBC_BLEN_bf(const void *const hw, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CBC ^= XDMAC_CBC_BLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cbc_reg_t hri_xdmacchid_read_CBC_BLEN_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CBC;
	tmp = (tmp & XDMAC_CBC_BLEN_Msk) >> XDMAC_CBC_BLEN_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CBC_reg(const void *const hw, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CBC |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cbc_reg_t hri_xdmacchid_get_CBC_reg(const void *const hw, hri_xdmac_cbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CBC;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CBC_reg(const void *const hw, hri_xdmac_cbc_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CBC = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CBC_reg(const void *const hw, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CBC &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CBC_reg(const void *const hw, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CBC ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cbc_reg_t hri_xdmacchid_read_CBC_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CBC;
}

static inline void hri_xdmacchid_set_CC_TYPE_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_TYPE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CC_TYPE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_TYPE) >> XDMAC_CC_TYPE_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CC_TYPE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_TYPE;
	tmp |= value << XDMAC_CC_TYPE_Pos;
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_TYPE_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_TYPE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_TYPE_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_TYPE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CC_DSYNC_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_DSYNC;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CC_DSYNC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DSYNC) >> XDMAC_CC_DSYNC_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CC_DSYNC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_DSYNC;
	tmp |= value << XDMAC_CC_DSYNC_Pos;
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_DSYNC_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_DSYNC;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_DSYNC_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_DSYNC;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CC_SWREQ_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_SWREQ;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CC_SWREQ_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_SWREQ) >> XDMAC_CC_SWREQ_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CC_SWREQ_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_SWREQ;
	tmp |= value << XDMAC_CC_SWREQ_Pos;
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_SWREQ_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_SWREQ;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_SWREQ_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_SWREQ;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CC_MEMSET_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_MEMSET;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CC_MEMSET_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_MEMSET) >> XDMAC_CC_MEMSET_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CC_MEMSET_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_MEMSET;
	tmp |= value << XDMAC_CC_MEMSET_Pos;
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_MEMSET_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_MEMSET;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_MEMSET_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_MEMSET;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CC_SIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_SIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CC_SIF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_SIF) >> XDMAC_CC_SIF_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CC_SIF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_SIF;
	tmp |= value << XDMAC_CC_SIF_Pos;
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_SIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_SIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_SIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_SIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CC_DIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_DIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CC_DIF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DIF) >> XDMAC_CC_DIF_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CC_DIF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_DIF;
	tmp |= value << XDMAC_CC_DIF_Pos;
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_DIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_DIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_DIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_DIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CC_INITD_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_INITD;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CC_INITD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_INITD) >> XDMAC_CC_INITD_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CC_INITD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_INITD;
	tmp |= value << XDMAC_CC_INITD_Pos;
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_INITD_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_INITD;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_INITD_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_INITD;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CC_RDIP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_RDIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CC_RDIP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_RDIP) >> XDMAC_CC_RDIP_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CC_RDIP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_RDIP;
	tmp |= value << XDMAC_CC_RDIP_Pos;
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_RDIP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_RDIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_RDIP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_RDIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CC_WRIP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_WRIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmacchid_get_CC_WRIP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_WRIP) >> XDMAC_CC_WRIP_Pos;
	return (bool)tmp;
}

static inline void hri_xdmacchid_write_CC_WRIP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_WRIP;
	tmp |= value << XDMAC_CC_WRIP_Pos;
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_WRIP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_WRIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_WRIP_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_WRIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_set_CC_MBSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_MBSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_get_CC_MBSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_MBSIZE(mask)) >> XDMAC_CC_MBSIZE_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CC_MBSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_MBSIZE_Msk;
	tmp |= XDMAC_CC_MBSIZE(data);
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_MBSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_MBSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_MBSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_MBSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_read_CC_MBSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_MBSIZE_Msk) >> XDMAC_CC_MBSIZE_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CC_CSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_CSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_get_CC_CSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_CSIZE(mask)) >> XDMAC_CC_CSIZE_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CC_CSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_CSIZE_Msk;
	tmp |= XDMAC_CC_CSIZE(data);
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_CSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_CSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_CSIZE_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_CSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_read_CC_CSIZE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_CSIZE_Msk) >> XDMAC_CC_CSIZE_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CC_DWIDTH_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_DWIDTH(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_get_CC_DWIDTH_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DWIDTH(mask)) >> XDMAC_CC_DWIDTH_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CC_DWIDTH_bf(const void *const hw, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_DWIDTH_Msk;
	tmp |= XDMAC_CC_DWIDTH(data);
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_DWIDTH_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_DWIDTH(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_DWIDTH_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_DWIDTH(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_read_CC_DWIDTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DWIDTH_Msk) >> XDMAC_CC_DWIDTH_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CC_SAM_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_SAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_get_CC_SAM_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_SAM(mask)) >> XDMAC_CC_SAM_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CC_SAM_bf(const void *const hw, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_SAM_Msk;
	tmp |= XDMAC_CC_SAM(data);
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_SAM_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_SAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_SAM_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_SAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_read_CC_SAM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_SAM_Msk) >> XDMAC_CC_SAM_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CC_DAM_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_DAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_get_CC_DAM_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DAM(mask)) >> XDMAC_CC_DAM_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CC_DAM_bf(const void *const hw, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_DAM_Msk;
	tmp |= XDMAC_CC_DAM(data);
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_DAM_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_DAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_DAM_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_DAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_read_CC_DAM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DAM_Msk) >> XDMAC_CC_DAM_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CC_PERID_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= XDMAC_CC_PERID(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_get_CC_PERID_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_PERID(mask)) >> XDMAC_CC_PERID_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CC_PERID_bf(const void *const hw, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= ~XDMAC_CC_PERID_Msk;
	tmp |= XDMAC_CC_PERID(data);
	((XdmacChid *)hw)->XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_PERID_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~XDMAC_CC_PERID(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_PERID_bf(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= XDMAC_CC_PERID(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_read_CC_PERID_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp = (tmp & XDMAC_CC_PERID_Msk) >> XDMAC_CC_PERID_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CC_reg(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_get_CC_reg(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CC;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CC_reg(const void *const hw, hri_xdmac_cc_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CC_reg(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CC_reg(const void *const hw, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CC ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmacchid_read_CC_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CC;
}

static inline void hri_xdmacchid_set_CDS_MSP_SDS_MSP_bf(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP |= XDMAC_CDS_MSP_SDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmacchid_get_CDS_MSP_SDS_MSP_bf(const void *const       hw,
                                                                           hri_xdmac_cds_msp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDS_MSP;
	tmp = (tmp & XDMAC_CDS_MSP_SDS_MSP(mask)) >> XDMAC_CDS_MSP_SDS_MSP_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CDS_MSP_SDS_MSP_bf(const void *const hw, hri_xdmac_cds_msp_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CDS_MSP;
	tmp &= ~XDMAC_CDS_MSP_SDS_MSP_Msk;
	tmp |= XDMAC_CDS_MSP_SDS_MSP(data);
	((XdmacChid *)hw)->XDMAC_CDS_MSP = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CDS_MSP_SDS_MSP_bf(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP &= ~XDMAC_CDS_MSP_SDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CDS_MSP_SDS_MSP_bf(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP ^= XDMAC_CDS_MSP_SDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmacchid_read_CDS_MSP_SDS_MSP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDS_MSP;
	tmp = (tmp & XDMAC_CDS_MSP_SDS_MSP_Msk) >> XDMAC_CDS_MSP_SDS_MSP_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CDS_MSP_DDS_MSP_bf(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP |= XDMAC_CDS_MSP_DDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmacchid_get_CDS_MSP_DDS_MSP_bf(const void *const       hw,
                                                                           hri_xdmac_cds_msp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDS_MSP;
	tmp = (tmp & XDMAC_CDS_MSP_DDS_MSP(mask)) >> XDMAC_CDS_MSP_DDS_MSP_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CDS_MSP_DDS_MSP_bf(const void *const hw, hri_xdmac_cds_msp_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CDS_MSP;
	tmp &= ~XDMAC_CDS_MSP_DDS_MSP_Msk;
	tmp |= XDMAC_CDS_MSP_DDS_MSP(data);
	((XdmacChid *)hw)->XDMAC_CDS_MSP = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CDS_MSP_DDS_MSP_bf(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP &= ~XDMAC_CDS_MSP_DDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CDS_MSP_DDS_MSP_bf(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP ^= XDMAC_CDS_MSP_DDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmacchid_read_CDS_MSP_DDS_MSP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDS_MSP;
	tmp = (tmp & XDMAC_CDS_MSP_DDS_MSP_Msk) >> XDMAC_CDS_MSP_DDS_MSP_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CDS_MSP_reg(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmacchid_get_CDS_MSP_reg(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDS_MSP;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CDS_MSP_reg(const void *const hw, hri_xdmac_cds_msp_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CDS_MSP_reg(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CDS_MSP_reg(const void *const hw, hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDS_MSP ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmacchid_read_CDS_MSP_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CDS_MSP;
}

static inline void hri_xdmacchid_set_CSUS_SUBS_bf(const void *const hw, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSUS |= XDMAC_CSUS_SUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csus_reg_t hri_xdmacchid_get_CSUS_SUBS_bf(const void *const hw, hri_xdmac_csus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CSUS;
	tmp = (tmp & XDMAC_CSUS_SUBS(mask)) >> XDMAC_CSUS_SUBS_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CSUS_SUBS_bf(const void *const hw, hri_xdmac_csus_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CSUS;
	tmp &= ~XDMAC_CSUS_SUBS_Msk;
	tmp |= XDMAC_CSUS_SUBS(data);
	((XdmacChid *)hw)->XDMAC_CSUS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CSUS_SUBS_bf(const void *const hw, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSUS &= ~XDMAC_CSUS_SUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CSUS_SUBS_bf(const void *const hw, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSUS ^= XDMAC_CSUS_SUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csus_reg_t hri_xdmacchid_read_CSUS_SUBS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CSUS;
	tmp = (tmp & XDMAC_CSUS_SUBS_Msk) >> XDMAC_CSUS_SUBS_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CSUS_reg(const void *const hw, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSUS |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csus_reg_t hri_xdmacchid_get_CSUS_reg(const void *const hw, hri_xdmac_csus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CSUS;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CSUS_reg(const void *const hw, hri_xdmac_csus_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSUS = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CSUS_reg(const void *const hw, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSUS &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CSUS_reg(const void *const hw, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CSUS ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csus_reg_t hri_xdmacchid_read_CSUS_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CSUS;
}

static inline void hri_xdmacchid_set_CDUS_DUBS_bf(const void *const hw, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDUS |= XDMAC_CDUS_DUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cdus_reg_t hri_xdmacchid_get_CDUS_DUBS_bf(const void *const hw, hri_xdmac_cdus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDUS;
	tmp = (tmp & XDMAC_CDUS_DUBS(mask)) >> XDMAC_CDUS_DUBS_Pos;
	return tmp;
}

static inline void hri_xdmacchid_write_CDUS_DUBS_bf(const void *const hw, hri_xdmac_cdus_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((XdmacChid *)hw)->XDMAC_CDUS;
	tmp &= ~XDMAC_CDUS_DUBS_Msk;
	tmp |= XDMAC_CDUS_DUBS(data);
	((XdmacChid *)hw)->XDMAC_CDUS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CDUS_DUBS_bf(const void *const hw, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDUS &= ~XDMAC_CDUS_DUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CDUS_DUBS_bf(const void *const hw, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDUS ^= XDMAC_CDUS_DUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cdus_reg_t hri_xdmacchid_read_CDUS_DUBS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDUS;
	tmp = (tmp & XDMAC_CDUS_DUBS_Msk) >> XDMAC_CDUS_DUBS_Pos;
	return tmp;
}

static inline void hri_xdmacchid_set_CDUS_reg(const void *const hw, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDUS |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cdus_reg_t hri_xdmacchid_get_CDUS_reg(const void *const hw, hri_xdmac_cdus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((XdmacChid *)hw)->XDMAC_CDUS;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmacchid_write_CDUS_reg(const void *const hw, hri_xdmac_cdus_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDUS = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_clear_CDUS_reg(const void *const hw, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDUS &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmacchid_toggle_CDUS_reg(const void *const hw, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((XdmacChid *)hw)->XDMAC_CDUS ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cdus_reg_t hri_xdmacchid_read_CDUS_reg(const void *const hw)
{
	return ((XdmacChid *)hw)->XDMAC_CDUS;
}

static inline void hri_xdmac_set_CIM_BIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_BIM;
}

static inline bool hri_xdmac_get_CIM_BIM_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIM & XDMAC_CIM_BIM) >> XDMAC_CIM_BIM_Pos;
}

static inline void hri_xdmac_write_CIM_BIM_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_BIM;
	} else {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_BIM;
	}
}

static inline void hri_xdmac_clear_CIM_BIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_BIM;
}

static inline void hri_xdmac_set_CIM_LIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_LIM;
}

static inline bool hri_xdmac_get_CIM_LIM_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIM & XDMAC_CIM_LIM) >> XDMAC_CIM_LIM_Pos;
}

static inline void hri_xdmac_write_CIM_LIM_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_LIM;
	} else {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_LIM;
	}
}

static inline void hri_xdmac_clear_CIM_LIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_LIM;
}

static inline void hri_xdmac_set_CIM_DIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_DIM;
}

static inline bool hri_xdmac_get_CIM_DIM_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIM & XDMAC_CIM_DIM) >> XDMAC_CIM_DIM_Pos;
}

static inline void hri_xdmac_write_CIM_DIM_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_DIM;
	} else {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_DIM;
	}
}

static inline void hri_xdmac_clear_CIM_DIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_DIM;
}

static inline void hri_xdmac_set_CIM_FIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_FIM;
}

static inline bool hri_xdmac_get_CIM_FIM_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIM & XDMAC_CIM_FIM) >> XDMAC_CIM_FIM_Pos;
}

static inline void hri_xdmac_write_CIM_FIM_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_FIM;
	} else {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_FIM;
	}
}

static inline void hri_xdmac_clear_CIM_FIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_FIM;
}

static inline void hri_xdmac_set_CIM_RBEIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_RBEIM;
}

static inline bool hri_xdmac_get_CIM_RBEIM_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIM & XDMAC_CIM_RBEIM) >> XDMAC_CIM_RBEIM_Pos;
}

static inline void hri_xdmac_write_CIM_RBEIM_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_RBEIM;
	} else {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_RBEIM;
	}
}

static inline void hri_xdmac_clear_CIM_RBEIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_RBEIM;
}

static inline void hri_xdmac_set_CIM_WBEIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_WBEIM;
}

static inline bool hri_xdmac_get_CIM_WBEIM_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIM & XDMAC_CIM_WBEIM) >> XDMAC_CIM_WBEIM_Pos;
}

static inline void hri_xdmac_write_CIM_WBEIM_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_WBEIM;
	} else {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_WBEIM;
	}
}

static inline void hri_xdmac_clear_CIM_WBEIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_WBEIM;
}

static inline void hri_xdmac_set_CIM_ROIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_ROIM;
}

static inline bool hri_xdmac_get_CIM_ROIM_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIM & XDMAC_CIM_ROIM) >> XDMAC_CIM_ROIM_Pos;
}

static inline void hri_xdmac_write_CIM_ROIM_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_ROIM;
	} else {
		((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = XDMAC_CIM_ROIM;
	}
}

static inline void hri_xdmac_clear_CIM_ROIM_bit(const void *const hw, uint8_t submodule_index)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = XDMAC_CIM_ROIM;
}

static inline void hri_xdmac_set_CIM_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cim_reg_t mask)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = mask;
}

static inline hri_xdmac_cim_reg_t hri_xdmac_get_CIM_reg(const void *const hw, uint8_t submodule_index,
                                                        hri_xdmac_cim_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIM;
	tmp &= mask;
	return tmp;
}

static inline hri_xdmac_cim_reg_t hri_xdmac_read_CIM_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIM;
}

static inline void hri_xdmac_write_CIM_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cim_reg_t data)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIE = data;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = ~data;
}

static inline void hri_xdmac_clear_CIM_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cim_reg_t mask)
{
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CID = mask;
}

static inline bool hri_xdmac_get_CIS_BIS_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIS & XDMAC_CIS_BIS) > 0;
}

static inline bool hri_xdmac_get_CIS_LIS_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIS & XDMAC_CIS_LIS) > 0;
}

static inline bool hri_xdmac_get_CIS_DIS_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIS & XDMAC_CIS_DIS) > 0;
}

static inline bool hri_xdmac_get_CIS_FIS_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIS & XDMAC_CIS_FIS) > 0;
}

static inline bool hri_xdmac_get_CIS_RBEIS_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIS & XDMAC_CIS_RBEIS) > 0;
}

static inline bool hri_xdmac_get_CIS_WBEIS_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIS & XDMAC_CIS_WBEIS) > 0;
}

static inline bool hri_xdmac_get_CIS_ROIS_bit(const void *const hw, uint8_t submodule_index)
{
	return (((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIS & XDMAC_CIS_ROIS) > 0;
}

static inline hri_xdmac_cis_reg_t hri_xdmac_get_CIS_reg(const void *const hw, uint8_t submodule_index,
                                                        hri_xdmac_cis_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIS;
	tmp &= mask;
	return tmp;
}

static inline hri_xdmac_cis_reg_t hri_xdmac_read_CIS_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CIS;
}

static inline void hri_xdmac_set_CSA_SA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA |= XDMAC_CSA_SA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csa_reg_t hri_xdmac_get_CSA_SA_bf(const void *const hw, uint8_t submodule_index,
                                                          hri_xdmac_csa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA;
	tmp = (tmp & XDMAC_CSA_SA(mask)) >> XDMAC_CSA_SA_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CSA_SA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_csa_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA;
	tmp &= ~XDMAC_CSA_SA_Msk;
	tmp |= XDMAC_CSA_SA(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CSA_SA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA &= ~XDMAC_CSA_SA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CSA_SA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA ^= XDMAC_CSA_SA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csa_reg_t hri_xdmac_read_CSA_SA_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA;
	tmp = (tmp & XDMAC_CSA_SA_Msk) >> XDMAC_CSA_SA_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CSA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csa_reg_t hri_xdmac_get_CSA_reg(const void *const hw, uint8_t submodule_index,
                                                        hri_xdmac_csa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CSA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_csa_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CSA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CSA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_csa_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csa_reg_t hri_xdmac_read_CSA_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSA;
}

static inline void hri_xdmac_set_CDA_DA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA |= XDMAC_CDA_DA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cda_reg_t hri_xdmac_get_CDA_DA_bf(const void *const hw, uint8_t submodule_index,
                                                          hri_xdmac_cda_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA;
	tmp = (tmp & XDMAC_CDA_DA(mask)) >> XDMAC_CDA_DA_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CDA_DA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cda_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA;
	tmp &= ~XDMAC_CDA_DA_Msk;
	tmp |= XDMAC_CDA_DA(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CDA_DA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA &= ~XDMAC_CDA_DA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CDA_DA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA ^= XDMAC_CDA_DA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cda_reg_t hri_xdmac_read_CDA_DA_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA;
	tmp = (tmp & XDMAC_CDA_DA_Msk) >> XDMAC_CDA_DA_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CDA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cda_reg_t hri_xdmac_get_CDA_reg(const void *const hw, uint8_t submodule_index,
                                                        hri_xdmac_cda_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CDA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cda_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CDA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CDA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cda_reg_t hri_xdmac_read_CDA_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDA;
}

static inline void hri_xdmac_set_CNDA_NDAIF_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA |= XDMAC_CNDA_NDAIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CNDA_NDAIF_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA;
	tmp = (tmp & XDMAC_CNDA_NDAIF) >> XDMAC_CNDA_NDAIF_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CNDA_NDAIF_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA;
	tmp &= ~XDMAC_CNDA_NDAIF;
	tmp |= value << XDMAC_CNDA_NDAIF_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CNDA_NDAIF_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA &= ~XDMAC_CNDA_NDAIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CNDA_NDAIF_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA ^= XDMAC_CNDA_NDAIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CNDA_NDA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA |= XDMAC_CNDA_NDA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cnda_reg_t hri_xdmac_get_CNDA_NDA_bf(const void *const hw, uint8_t submodule_index,
                                                             hri_xdmac_cnda_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA;
	tmp = (tmp & XDMAC_CNDA_NDA(mask)) >> XDMAC_CNDA_NDA_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CNDA_NDA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cnda_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA;
	tmp &= ~XDMAC_CNDA_NDA_Msk;
	tmp |= XDMAC_CNDA_NDA(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CNDA_NDA_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA &= ~XDMAC_CNDA_NDA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CNDA_NDA_bf(const void *const hw, uint8_t submodule_index,
                                                hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA ^= XDMAC_CNDA_NDA(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cnda_reg_t hri_xdmac_read_CNDA_NDA_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA;
	tmp = (tmp & XDMAC_CNDA_NDA_Msk) >> XDMAC_CNDA_NDA_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CNDA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cnda_reg_t hri_xdmac_get_CNDA_reg(const void *const hw, uint8_t submodule_index,
                                                          hri_xdmac_cnda_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CNDA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cnda_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CNDA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CNDA_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cnda_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cnda_reg_t hri_xdmac_read_CNDA_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDA;
}

static inline void hri_xdmac_set_CNDC_NDE_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC |= XDMAC_CNDC_NDE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CNDC_NDE_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDE) >> XDMAC_CNDC_NDE_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CNDC_NDE_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp &= ~XDMAC_CNDC_NDE;
	tmp |= value << XDMAC_CNDC_NDE_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CNDC_NDE_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC &= ~XDMAC_CNDC_NDE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CNDC_NDE_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC ^= XDMAC_CNDC_NDE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CNDC_NDSUP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC |= XDMAC_CNDC_NDSUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CNDC_NDSUP_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDSUP) >> XDMAC_CNDC_NDSUP_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CNDC_NDSUP_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp &= ~XDMAC_CNDC_NDSUP;
	tmp |= value << XDMAC_CNDC_NDSUP_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CNDC_NDSUP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC &= ~XDMAC_CNDC_NDSUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CNDC_NDSUP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC ^= XDMAC_CNDC_NDSUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CNDC_NDDUP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC |= XDMAC_CNDC_NDDUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CNDC_NDDUP_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDDUP) >> XDMAC_CNDC_NDDUP_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CNDC_NDDUP_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp &= ~XDMAC_CNDC_NDDUP;
	tmp |= value << XDMAC_CNDC_NDDUP_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CNDC_NDDUP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC &= ~XDMAC_CNDC_NDDUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CNDC_NDDUP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC ^= XDMAC_CNDC_NDDUP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CNDC_NDVIEW_bf(const void *const hw, uint8_t submodule_index,
                                                hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC |= XDMAC_CNDC_NDVIEW(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cndc_reg_t hri_xdmac_get_CNDC_NDVIEW_bf(const void *const hw, uint8_t submodule_index,
                                                                hri_xdmac_cndc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDVIEW(mask)) >> XDMAC_CNDC_NDVIEW_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CNDC_NDVIEW_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_xdmac_cndc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp &= ~XDMAC_CNDC_NDVIEW_Msk;
	tmp |= XDMAC_CNDC_NDVIEW(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CNDC_NDVIEW_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC &= ~XDMAC_CNDC_NDVIEW(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CNDC_NDVIEW_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC ^= XDMAC_CNDC_NDVIEW(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cndc_reg_t hri_xdmac_read_CNDC_NDVIEW_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp = (tmp & XDMAC_CNDC_NDVIEW_Msk) >> XDMAC_CNDC_NDVIEW_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CNDC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cndc_reg_t hri_xdmac_get_CNDC_reg(const void *const hw, uint8_t submodule_index,
                                                          hri_xdmac_cndc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CNDC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cndc_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CNDC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CNDC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cndc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cndc_reg_t hri_xdmac_read_CNDC_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CNDC;
}

static inline void hri_xdmac_set_CUBC_UBLEN_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC |= XDMAC_CUBC_UBLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cubc_reg_t hri_xdmac_get_CUBC_UBLEN_bf(const void *const hw, uint8_t submodule_index,
                                                               hri_xdmac_cubc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC;
	tmp = (tmp & XDMAC_CUBC_UBLEN(mask)) >> XDMAC_CUBC_UBLEN_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CUBC_UBLEN_bf(const void *const hw, uint8_t submodule_index,
                                                 hri_xdmac_cubc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC;
	tmp &= ~XDMAC_CUBC_UBLEN_Msk;
	tmp |= XDMAC_CUBC_UBLEN(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CUBC_UBLEN_bf(const void *const hw, uint8_t submodule_index,
                                                 hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC &= ~XDMAC_CUBC_UBLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CUBC_UBLEN_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC ^= XDMAC_CUBC_UBLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cubc_reg_t hri_xdmac_read_CUBC_UBLEN_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC;
	tmp = (tmp & XDMAC_CUBC_UBLEN_Msk) >> XDMAC_CUBC_UBLEN_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CUBC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cubc_reg_t hri_xdmac_get_CUBC_reg(const void *const hw, uint8_t submodule_index,
                                                          hri_xdmac_cubc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CUBC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cubc_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CUBC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CUBC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cubc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cubc_reg_t hri_xdmac_read_CUBC_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CUBC;
}

static inline void hri_xdmac_set_CBC_BLEN_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC |= XDMAC_CBC_BLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cbc_reg_t hri_xdmac_get_CBC_BLEN_bf(const void *const hw, uint8_t submodule_index,
                                                            hri_xdmac_cbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC;
	tmp = (tmp & XDMAC_CBC_BLEN(mask)) >> XDMAC_CBC_BLEN_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CBC_BLEN_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cbc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC;
	tmp &= ~XDMAC_CBC_BLEN_Msk;
	tmp |= XDMAC_CBC_BLEN(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CBC_BLEN_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC &= ~XDMAC_CBC_BLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CBC_BLEN_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC ^= XDMAC_CBC_BLEN(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cbc_reg_t hri_xdmac_read_CBC_BLEN_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC;
	tmp = (tmp & XDMAC_CBC_BLEN_Msk) >> XDMAC_CBC_BLEN_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CBC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cbc_reg_t hri_xdmac_get_CBC_reg(const void *const hw, uint8_t submodule_index,
                                                        hri_xdmac_cbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CBC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cbc_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CBC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CBC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cbc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cbc_reg_t hri_xdmac_read_CBC_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CBC;
}

static inline void hri_xdmac_set_CC_TYPE_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_TYPE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CC_TYPE_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_TYPE) >> XDMAC_CC_TYPE_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CC_TYPE_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_TYPE;
	tmp |= value << XDMAC_CC_TYPE_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_TYPE_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_TYPE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_TYPE_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_TYPE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CC_DSYNC_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_DSYNC;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CC_DSYNC_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DSYNC) >> XDMAC_CC_DSYNC_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CC_DSYNC_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_DSYNC;
	tmp |= value << XDMAC_CC_DSYNC_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_DSYNC_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_DSYNC;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_DSYNC_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_DSYNC;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CC_SWREQ_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_SWREQ;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CC_SWREQ_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_SWREQ) >> XDMAC_CC_SWREQ_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CC_SWREQ_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_SWREQ;
	tmp |= value << XDMAC_CC_SWREQ_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_SWREQ_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_SWREQ;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_SWREQ_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_SWREQ;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CC_MEMSET_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_MEMSET;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CC_MEMSET_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_MEMSET) >> XDMAC_CC_MEMSET_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CC_MEMSET_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_MEMSET;
	tmp |= value << XDMAC_CC_MEMSET_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_MEMSET_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_MEMSET;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_MEMSET_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_MEMSET;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CC_SIF_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_SIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CC_SIF_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_SIF) >> XDMAC_CC_SIF_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CC_SIF_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_SIF;
	tmp |= value << XDMAC_CC_SIF_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_SIF_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_SIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_SIF_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_SIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CC_DIF_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_DIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CC_DIF_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DIF) >> XDMAC_CC_DIF_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CC_DIF_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_DIF;
	tmp |= value << XDMAC_CC_DIF_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_DIF_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_DIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_DIF_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_DIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CC_INITD_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_INITD;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CC_INITD_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_INITD) >> XDMAC_CC_INITD_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CC_INITD_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_INITD;
	tmp |= value << XDMAC_CC_INITD_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_INITD_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_INITD;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_INITD_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_INITD;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CC_RDIP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_RDIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CC_RDIP_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_RDIP) >> XDMAC_CC_RDIP_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CC_RDIP_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_RDIP;
	tmp |= value << XDMAC_CC_RDIP_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_RDIP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_RDIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_RDIP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_RDIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CC_WRIP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_WRIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_CC_WRIP_bit(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_WRIP) >> XDMAC_CC_WRIP_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_CC_WRIP_bit(const void *const hw, uint8_t submodule_index, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_WRIP;
	tmp |= value << XDMAC_CC_WRIP_Pos;
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_WRIP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_WRIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_WRIP_bit(const void *const hw, uint8_t submodule_index)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_WRIP;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_CC_MBSIZE_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_MBSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_get_CC_MBSIZE_bf(const void *const hw, uint8_t submodule_index,
                                                            hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_MBSIZE(mask)) >> XDMAC_CC_MBSIZE_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CC_MBSIZE_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_MBSIZE_Msk;
	tmp |= XDMAC_CC_MBSIZE(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_MBSIZE_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_MBSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_MBSIZE_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_MBSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_read_CC_MBSIZE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_MBSIZE_Msk) >> XDMAC_CC_MBSIZE_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CC_CSIZE_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_CSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_get_CC_CSIZE_bf(const void *const hw, uint8_t submodule_index,
                                                           hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_CSIZE(mask)) >> XDMAC_CC_CSIZE_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CC_CSIZE_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_CSIZE_Msk;
	tmp |= XDMAC_CC_CSIZE(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_CSIZE_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_CSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_CSIZE_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_CSIZE(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_read_CC_CSIZE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_CSIZE_Msk) >> XDMAC_CC_CSIZE_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CC_DWIDTH_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_DWIDTH(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_get_CC_DWIDTH_bf(const void *const hw, uint8_t submodule_index,
                                                            hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DWIDTH(mask)) >> XDMAC_CC_DWIDTH_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CC_DWIDTH_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_DWIDTH_Msk;
	tmp |= XDMAC_CC_DWIDTH(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_DWIDTH_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_DWIDTH(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_DWIDTH_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_DWIDTH(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_read_CC_DWIDTH_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DWIDTH_Msk) >> XDMAC_CC_DWIDTH_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CC_SAM_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_SAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_get_CC_SAM_bf(const void *const hw, uint8_t submodule_index,
                                                         hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_SAM(mask)) >> XDMAC_CC_SAM_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CC_SAM_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_SAM_Msk;
	tmp |= XDMAC_CC_SAM(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_SAM_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_SAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_SAM_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_SAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_read_CC_SAM_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_SAM_Msk) >> XDMAC_CC_SAM_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CC_DAM_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_DAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_get_CC_DAM_bf(const void *const hw, uint8_t submodule_index,
                                                         hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DAM(mask)) >> XDMAC_CC_DAM_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CC_DAM_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_DAM_Msk;
	tmp |= XDMAC_CC_DAM(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_DAM_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_DAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_DAM_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_DAM(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_read_CC_DAM_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_DAM_Msk) >> XDMAC_CC_DAM_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CC_PERID_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= XDMAC_CC_PERID(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_get_CC_PERID_bf(const void *const hw, uint8_t submodule_index,
                                                           hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_PERID(mask)) >> XDMAC_CC_PERID_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CC_PERID_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= ~XDMAC_CC_PERID_Msk;
	tmp |= XDMAC_CC_PERID(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_PERID_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~XDMAC_CC_PERID(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_PERID_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= XDMAC_CC_PERID(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_read_CC_PERID_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp = (tmp & XDMAC_CC_PERID_Msk) >> XDMAC_CC_PERID_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_get_CC_reg(const void *const hw, uint8_t submodule_index,
                                                      hri_xdmac_cc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CC_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cc_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cc_reg_t hri_xdmac_read_CC_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CC;
}

static inline void hri_xdmac_set_CDS_MSP_SDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP |= XDMAC_CDS_MSP_SDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmac_get_CDS_MSP_SDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                                       hri_xdmac_cds_msp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP;
	tmp = (tmp & XDMAC_CDS_MSP_SDS_MSP(mask)) >> XDMAC_CDS_MSP_SDS_MSP_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CDS_MSP_SDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_xdmac_cds_msp_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP;
	tmp &= ~XDMAC_CDS_MSP_SDS_MSP_Msk;
	tmp |= XDMAC_CDS_MSP_SDS_MSP(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CDS_MSP_SDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP &= ~XDMAC_CDS_MSP_SDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CDS_MSP_SDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP ^= XDMAC_CDS_MSP_SDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmac_read_CDS_MSP_SDS_MSP_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP;
	tmp = (tmp & XDMAC_CDS_MSP_SDS_MSP_Msk) >> XDMAC_CDS_MSP_SDS_MSP_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CDS_MSP_DDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP |= XDMAC_CDS_MSP_DDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmac_get_CDS_MSP_DDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                                       hri_xdmac_cds_msp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP;
	tmp = (tmp & XDMAC_CDS_MSP_DDS_MSP(mask)) >> XDMAC_CDS_MSP_DDS_MSP_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CDS_MSP_DDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_xdmac_cds_msp_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP;
	tmp &= ~XDMAC_CDS_MSP_DDS_MSP_Msk;
	tmp |= XDMAC_CDS_MSP_DDS_MSP(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CDS_MSP_DDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP &= ~XDMAC_CDS_MSP_DDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CDS_MSP_DDS_MSP_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP ^= XDMAC_CDS_MSP_DDS_MSP(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmac_read_CDS_MSP_DDS_MSP_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP;
	tmp = (tmp & XDMAC_CDS_MSP_DDS_MSP_Msk) >> XDMAC_CDS_MSP_DDS_MSP_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CDS_MSP_reg(const void *const hw, uint8_t submodule_index,
                                             hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmac_get_CDS_MSP_reg(const void *const hw, uint8_t submodule_index,
                                                                hri_xdmac_cds_msp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CDS_MSP_reg(const void *const hw, uint8_t submodule_index,
                                               hri_xdmac_cds_msp_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CDS_MSP_reg(const void *const hw, uint8_t submodule_index,
                                               hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CDS_MSP_reg(const void *const hw, uint8_t submodule_index,
                                                hri_xdmac_cds_msp_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cds_msp_reg_t hri_xdmac_read_CDS_MSP_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDS_MSP;
}

static inline void hri_xdmac_set_CSUS_SUBS_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS |= XDMAC_CSUS_SUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csus_reg_t hri_xdmac_get_CSUS_SUBS_bf(const void *const hw, uint8_t submodule_index,
                                                              hri_xdmac_csus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS;
	tmp = (tmp & XDMAC_CSUS_SUBS(mask)) >> XDMAC_CSUS_SUBS_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CSUS_SUBS_bf(const void *const hw, uint8_t submodule_index,
                                                hri_xdmac_csus_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS;
	tmp &= ~XDMAC_CSUS_SUBS_Msk;
	tmp |= XDMAC_CSUS_SUBS(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CSUS_SUBS_bf(const void *const hw, uint8_t submodule_index,
                                                hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS &= ~XDMAC_CSUS_SUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CSUS_SUBS_bf(const void *const hw, uint8_t submodule_index,
                                                 hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS ^= XDMAC_CSUS_SUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csus_reg_t hri_xdmac_read_CSUS_SUBS_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS;
	tmp = (tmp & XDMAC_CSUS_SUBS_Msk) >> XDMAC_CSUS_SUBS_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CSUS_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csus_reg_t hri_xdmac_get_CSUS_reg(const void *const hw, uint8_t submodule_index,
                                                          hri_xdmac_csus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CSUS_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_csus_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CSUS_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CSUS_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_csus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_csus_reg_t hri_xdmac_read_CSUS_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CSUS;
}

static inline void hri_xdmac_set_CDUS_DUBS_bf(const void *const hw, uint8_t submodule_index, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS |= XDMAC_CDUS_DUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cdus_reg_t hri_xdmac_get_CDUS_DUBS_bf(const void *const hw, uint8_t submodule_index,
                                                              hri_xdmac_cdus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS;
	tmp = (tmp & XDMAC_CDUS_DUBS(mask)) >> XDMAC_CDUS_DUBS_Pos;
	return tmp;
}

static inline void hri_xdmac_write_CDUS_DUBS_bf(const void *const hw, uint8_t submodule_index,
                                                hri_xdmac_cdus_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS;
	tmp &= ~XDMAC_CDUS_DUBS_Msk;
	tmp |= XDMAC_CDUS_DUBS(data);
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CDUS_DUBS_bf(const void *const hw, uint8_t submodule_index,
                                                hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS &= ~XDMAC_CDUS_DUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CDUS_DUBS_bf(const void *const hw, uint8_t submodule_index,
                                                 hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS ^= XDMAC_CDUS_DUBS(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cdus_reg_t hri_xdmac_read_CDUS_DUBS_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS;
	tmp = (tmp & XDMAC_CDUS_DUBS_Msk) >> XDMAC_CDUS_DUBS_Pos;
	return tmp;
}

static inline void hri_xdmac_set_CDUS_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cdus_reg_t hri_xdmac_get_CDUS_reg(const void *const hw, uint8_t submodule_index,
                                                          hri_xdmac_cdus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_CDUS_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cdus_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_CDUS_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_CDUS_reg(const void *const hw, uint8_t submodule_index, hri_xdmac_cdus_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_cdus_reg_t hri_xdmac_read_CDUS_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Xdmac *)hw)->XdmacChid[submodule_index].XDMAC_CDUS;
}

static inline void hri_xdmac_set_GIM_IM0_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM0;
}

static inline bool hri_xdmac_get_GIM_IM0_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM0) >> XDMAC_GIM_IM0_Pos;
}

static inline void hri_xdmac_write_GIM_IM0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM0;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM0;
	}
}

static inline void hri_xdmac_clear_GIM_IM0_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM0;
}

static inline void hri_xdmac_set_GIM_IM1_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM1;
}

static inline bool hri_xdmac_get_GIM_IM1_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM1) >> XDMAC_GIM_IM1_Pos;
}

static inline void hri_xdmac_write_GIM_IM1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM1;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM1;
	}
}

static inline void hri_xdmac_clear_GIM_IM1_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM1;
}

static inline void hri_xdmac_set_GIM_IM2_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM2;
}

static inline bool hri_xdmac_get_GIM_IM2_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM2) >> XDMAC_GIM_IM2_Pos;
}

static inline void hri_xdmac_write_GIM_IM2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM2;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM2;
	}
}

static inline void hri_xdmac_clear_GIM_IM2_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM2;
}

static inline void hri_xdmac_set_GIM_IM3_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM3;
}

static inline bool hri_xdmac_get_GIM_IM3_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM3) >> XDMAC_GIM_IM3_Pos;
}

static inline void hri_xdmac_write_GIM_IM3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM3;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM3;
	}
}

static inline void hri_xdmac_clear_GIM_IM3_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM3;
}

static inline void hri_xdmac_set_GIM_IM4_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM4;
}

static inline bool hri_xdmac_get_GIM_IM4_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM4) >> XDMAC_GIM_IM4_Pos;
}

static inline void hri_xdmac_write_GIM_IM4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM4;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM4;
	}
}

static inline void hri_xdmac_clear_GIM_IM4_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM4;
}

static inline void hri_xdmac_set_GIM_IM5_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM5;
}

static inline bool hri_xdmac_get_GIM_IM5_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM5) >> XDMAC_GIM_IM5_Pos;
}

static inline void hri_xdmac_write_GIM_IM5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM5;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM5;
	}
}

static inline void hri_xdmac_clear_GIM_IM5_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM5;
}

static inline void hri_xdmac_set_GIM_IM6_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM6;
}

static inline bool hri_xdmac_get_GIM_IM6_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM6) >> XDMAC_GIM_IM6_Pos;
}

static inline void hri_xdmac_write_GIM_IM6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM6;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM6;
	}
}

static inline void hri_xdmac_clear_GIM_IM6_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM6;
}

static inline void hri_xdmac_set_GIM_IM7_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM7;
}

static inline bool hri_xdmac_get_GIM_IM7_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM7) >> XDMAC_GIM_IM7_Pos;
}

static inline void hri_xdmac_write_GIM_IM7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM7;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM7;
	}
}

static inline void hri_xdmac_clear_GIM_IM7_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM7;
}

static inline void hri_xdmac_set_GIM_IM8_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM8;
}

static inline bool hri_xdmac_get_GIM_IM8_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM8) >> XDMAC_GIM_IM8_Pos;
}

static inline void hri_xdmac_write_GIM_IM8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM8;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM8;
	}
}

static inline void hri_xdmac_clear_GIM_IM8_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM8;
}

static inline void hri_xdmac_set_GIM_IM9_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM9;
}

static inline bool hri_xdmac_get_GIM_IM9_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM9) >> XDMAC_GIM_IM9_Pos;
}

static inline void hri_xdmac_write_GIM_IM9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM9;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM9;
	}
}

static inline void hri_xdmac_clear_GIM_IM9_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM9;
}

static inline void hri_xdmac_set_GIM_IM10_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM10;
}

static inline bool hri_xdmac_get_GIM_IM10_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM10) >> XDMAC_GIM_IM10_Pos;
}

static inline void hri_xdmac_write_GIM_IM10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM10;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM10;
	}
}

static inline void hri_xdmac_clear_GIM_IM10_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM10;
}

static inline void hri_xdmac_set_GIM_IM11_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM11;
}

static inline bool hri_xdmac_get_GIM_IM11_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM11) >> XDMAC_GIM_IM11_Pos;
}

static inline void hri_xdmac_write_GIM_IM11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM11;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM11;
	}
}

static inline void hri_xdmac_clear_GIM_IM11_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM11;
}

static inline void hri_xdmac_set_GIM_IM12_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM12;
}

static inline bool hri_xdmac_get_GIM_IM12_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM12) >> XDMAC_GIM_IM12_Pos;
}

static inline void hri_xdmac_write_GIM_IM12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM12;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM12;
	}
}

static inline void hri_xdmac_clear_GIM_IM12_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM12;
}

static inline void hri_xdmac_set_GIM_IM13_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM13;
}

static inline bool hri_xdmac_get_GIM_IM13_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM13) >> XDMAC_GIM_IM13_Pos;
}

static inline void hri_xdmac_write_GIM_IM13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM13;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM13;
	}
}

static inline void hri_xdmac_clear_GIM_IM13_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM13;
}

static inline void hri_xdmac_set_GIM_IM14_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM14;
}

static inline bool hri_xdmac_get_GIM_IM14_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM14) >> XDMAC_GIM_IM14_Pos;
}

static inline void hri_xdmac_write_GIM_IM14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM14;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM14;
	}
}

static inline void hri_xdmac_clear_GIM_IM14_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM14;
}

static inline void hri_xdmac_set_GIM_IM15_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM15;
}

static inline bool hri_xdmac_get_GIM_IM15_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM15) >> XDMAC_GIM_IM15_Pos;
}

static inline void hri_xdmac_write_GIM_IM15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM15;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM15;
	}
}

static inline void hri_xdmac_clear_GIM_IM15_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM15;
}

static inline void hri_xdmac_set_GIM_IM16_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM16;
}

static inline bool hri_xdmac_get_GIM_IM16_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM16) >> XDMAC_GIM_IM16_Pos;
}

static inline void hri_xdmac_write_GIM_IM16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM16;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM16;
	}
}

static inline void hri_xdmac_clear_GIM_IM16_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM16;
}

static inline void hri_xdmac_set_GIM_IM17_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM17;
}

static inline bool hri_xdmac_get_GIM_IM17_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM17) >> XDMAC_GIM_IM17_Pos;
}

static inline void hri_xdmac_write_GIM_IM17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM17;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM17;
	}
}

static inline void hri_xdmac_clear_GIM_IM17_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM17;
}

static inline void hri_xdmac_set_GIM_IM18_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM18;
}

static inline bool hri_xdmac_get_GIM_IM18_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM18) >> XDMAC_GIM_IM18_Pos;
}

static inline void hri_xdmac_write_GIM_IM18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM18;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM18;
	}
}

static inline void hri_xdmac_clear_GIM_IM18_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM18;
}

static inline void hri_xdmac_set_GIM_IM19_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM19;
}

static inline bool hri_xdmac_get_GIM_IM19_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM19) >> XDMAC_GIM_IM19_Pos;
}

static inline void hri_xdmac_write_GIM_IM19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM19;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM19;
	}
}

static inline void hri_xdmac_clear_GIM_IM19_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM19;
}

static inline void hri_xdmac_set_GIM_IM20_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM20;
}

static inline bool hri_xdmac_get_GIM_IM20_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM20) >> XDMAC_GIM_IM20_Pos;
}

static inline void hri_xdmac_write_GIM_IM20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM20;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM20;
	}
}

static inline void hri_xdmac_clear_GIM_IM20_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM20;
}

static inline void hri_xdmac_set_GIM_IM21_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM21;
}

static inline bool hri_xdmac_get_GIM_IM21_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM21) >> XDMAC_GIM_IM21_Pos;
}

static inline void hri_xdmac_write_GIM_IM21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM21;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM21;
	}
}

static inline void hri_xdmac_clear_GIM_IM21_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM21;
}

static inline void hri_xdmac_set_GIM_IM22_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM22;
}

static inline bool hri_xdmac_get_GIM_IM22_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM22) >> XDMAC_GIM_IM22_Pos;
}

static inline void hri_xdmac_write_GIM_IM22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM22;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM22;
	}
}

static inline void hri_xdmac_clear_GIM_IM22_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM22;
}

static inline void hri_xdmac_set_GIM_IM23_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM23;
}

static inline bool hri_xdmac_get_GIM_IM23_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIM & XDMAC_GIM_IM23) >> XDMAC_GIM_IM23_Pos;
}

static inline void hri_xdmac_write_GIM_IM23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM23;
	} else {
		((Xdmac *)hw)->XDMAC_GIE = XDMAC_GIM_IM23;
	}
}

static inline void hri_xdmac_clear_GIM_IM23_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GID = XDMAC_GIM_IM23;
}

static inline void hri_xdmac_set_GIM_reg(const void *const hw, hri_xdmac_gim_reg_t mask)
{
	((Xdmac *)hw)->XDMAC_GIE = mask;
}

static inline hri_xdmac_gim_reg_t hri_xdmac_get_GIM_reg(const void *const hw, hri_xdmac_gim_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GIM;
	tmp &= mask;
	return tmp;
}

static inline hri_xdmac_gim_reg_t hri_xdmac_read_GIM_reg(const void *const hw)
{
	return ((Xdmac *)hw)->XDMAC_GIM;
}

static inline void hri_xdmac_write_GIM_reg(const void *const hw, hri_xdmac_gim_reg_t data)
{
	((Xdmac *)hw)->XDMAC_GIE = data;
	((Xdmac *)hw)->XDMAC_GID = ~data;
}

static inline void hri_xdmac_clear_GIM_reg(const void *const hw, hri_xdmac_gim_reg_t mask)
{
	((Xdmac *)hw)->XDMAC_GID = mask;
}

static inline void hri_xdmac_set_GS_ST0_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST0;
}

static inline bool hri_xdmac_get_GS_ST0_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST0) >> XDMAC_GS_ST0_Pos;
}

static inline void hri_xdmac_write_GS_ST0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST0;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST0;
	}
}

static inline void hri_xdmac_clear_GS_ST0_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST0;
}

static inline void hri_xdmac_set_GS_ST1_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST1;
}

static inline bool hri_xdmac_get_GS_ST1_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST1) >> XDMAC_GS_ST1_Pos;
}

static inline void hri_xdmac_write_GS_ST1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST1;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST1;
	}
}

static inline void hri_xdmac_clear_GS_ST1_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST1;
}

static inline void hri_xdmac_set_GS_ST2_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST2;
}

static inline bool hri_xdmac_get_GS_ST2_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST2) >> XDMAC_GS_ST2_Pos;
}

static inline void hri_xdmac_write_GS_ST2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST2;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST2;
	}
}

static inline void hri_xdmac_clear_GS_ST2_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST2;
}

static inline void hri_xdmac_set_GS_ST3_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST3;
}

static inline bool hri_xdmac_get_GS_ST3_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST3) >> XDMAC_GS_ST3_Pos;
}

static inline void hri_xdmac_write_GS_ST3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST3;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST3;
	}
}

static inline void hri_xdmac_clear_GS_ST3_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST3;
}

static inline void hri_xdmac_set_GS_ST4_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST4;
}

static inline bool hri_xdmac_get_GS_ST4_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST4) >> XDMAC_GS_ST4_Pos;
}

static inline void hri_xdmac_write_GS_ST4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST4;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST4;
	}
}

static inline void hri_xdmac_clear_GS_ST4_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST4;
}

static inline void hri_xdmac_set_GS_ST5_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST5;
}

static inline bool hri_xdmac_get_GS_ST5_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST5) >> XDMAC_GS_ST5_Pos;
}

static inline void hri_xdmac_write_GS_ST5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST5;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST5;
	}
}

static inline void hri_xdmac_clear_GS_ST5_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST5;
}

static inline void hri_xdmac_set_GS_ST6_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST6;
}

static inline bool hri_xdmac_get_GS_ST6_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST6) >> XDMAC_GS_ST6_Pos;
}

static inline void hri_xdmac_write_GS_ST6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST6;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST6;
	}
}

static inline void hri_xdmac_clear_GS_ST6_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST6;
}

static inline void hri_xdmac_set_GS_ST7_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST7;
}

static inline bool hri_xdmac_get_GS_ST7_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST7) >> XDMAC_GS_ST7_Pos;
}

static inline void hri_xdmac_write_GS_ST7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST7;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST7;
	}
}

static inline void hri_xdmac_clear_GS_ST7_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST7;
}

static inline void hri_xdmac_set_GS_ST8_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST8;
}

static inline bool hri_xdmac_get_GS_ST8_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST8) >> XDMAC_GS_ST8_Pos;
}

static inline void hri_xdmac_write_GS_ST8_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST8;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST8;
	}
}

static inline void hri_xdmac_clear_GS_ST8_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST8;
}

static inline void hri_xdmac_set_GS_ST9_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST9;
}

static inline bool hri_xdmac_get_GS_ST9_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST9) >> XDMAC_GS_ST9_Pos;
}

static inline void hri_xdmac_write_GS_ST9_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST9;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST9;
	}
}

static inline void hri_xdmac_clear_GS_ST9_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST9;
}

static inline void hri_xdmac_set_GS_ST10_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST10;
}

static inline bool hri_xdmac_get_GS_ST10_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST10) >> XDMAC_GS_ST10_Pos;
}

static inline void hri_xdmac_write_GS_ST10_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST10;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST10;
	}
}

static inline void hri_xdmac_clear_GS_ST10_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST10;
}

static inline void hri_xdmac_set_GS_ST11_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST11;
}

static inline bool hri_xdmac_get_GS_ST11_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST11) >> XDMAC_GS_ST11_Pos;
}

static inline void hri_xdmac_write_GS_ST11_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST11;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST11;
	}
}

static inline void hri_xdmac_clear_GS_ST11_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST11;
}

static inline void hri_xdmac_set_GS_ST12_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST12;
}

static inline bool hri_xdmac_get_GS_ST12_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST12) >> XDMAC_GS_ST12_Pos;
}

static inline void hri_xdmac_write_GS_ST12_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST12;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST12;
	}
}

static inline void hri_xdmac_clear_GS_ST12_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST12;
}

static inline void hri_xdmac_set_GS_ST13_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST13;
}

static inline bool hri_xdmac_get_GS_ST13_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST13) >> XDMAC_GS_ST13_Pos;
}

static inline void hri_xdmac_write_GS_ST13_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST13;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST13;
	}
}

static inline void hri_xdmac_clear_GS_ST13_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST13;
}

static inline void hri_xdmac_set_GS_ST14_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST14;
}

static inline bool hri_xdmac_get_GS_ST14_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST14) >> XDMAC_GS_ST14_Pos;
}

static inline void hri_xdmac_write_GS_ST14_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST14;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST14;
	}
}

static inline void hri_xdmac_clear_GS_ST14_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST14;
}

static inline void hri_xdmac_set_GS_ST15_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST15;
}

static inline bool hri_xdmac_get_GS_ST15_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST15) >> XDMAC_GS_ST15_Pos;
}

static inline void hri_xdmac_write_GS_ST15_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST15;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST15;
	}
}

static inline void hri_xdmac_clear_GS_ST15_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST15;
}

static inline void hri_xdmac_set_GS_ST16_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST16;
}

static inline bool hri_xdmac_get_GS_ST16_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST16) >> XDMAC_GS_ST16_Pos;
}

static inline void hri_xdmac_write_GS_ST16_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST16;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST16;
	}
}

static inline void hri_xdmac_clear_GS_ST16_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST16;
}

static inline void hri_xdmac_set_GS_ST17_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST17;
}

static inline bool hri_xdmac_get_GS_ST17_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST17) >> XDMAC_GS_ST17_Pos;
}

static inline void hri_xdmac_write_GS_ST17_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST17;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST17;
	}
}

static inline void hri_xdmac_clear_GS_ST17_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST17;
}

static inline void hri_xdmac_set_GS_ST18_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST18;
}

static inline bool hri_xdmac_get_GS_ST18_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST18) >> XDMAC_GS_ST18_Pos;
}

static inline void hri_xdmac_write_GS_ST18_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST18;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST18;
	}
}

static inline void hri_xdmac_clear_GS_ST18_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST18;
}

static inline void hri_xdmac_set_GS_ST19_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST19;
}

static inline bool hri_xdmac_get_GS_ST19_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST19) >> XDMAC_GS_ST19_Pos;
}

static inline void hri_xdmac_write_GS_ST19_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST19;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST19;
	}
}

static inline void hri_xdmac_clear_GS_ST19_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST19;
}

static inline void hri_xdmac_set_GS_ST20_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST20;
}

static inline bool hri_xdmac_get_GS_ST20_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST20) >> XDMAC_GS_ST20_Pos;
}

static inline void hri_xdmac_write_GS_ST20_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST20;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST20;
	}
}

static inline void hri_xdmac_clear_GS_ST20_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST20;
}

static inline void hri_xdmac_set_GS_ST21_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST21;
}

static inline bool hri_xdmac_get_GS_ST21_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST21) >> XDMAC_GS_ST21_Pos;
}

static inline void hri_xdmac_write_GS_ST21_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST21;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST21;
	}
}

static inline void hri_xdmac_clear_GS_ST21_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST21;
}

static inline void hri_xdmac_set_GS_ST22_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST22;
}

static inline bool hri_xdmac_get_GS_ST22_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST22) >> XDMAC_GS_ST22_Pos;
}

static inline void hri_xdmac_write_GS_ST22_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST22;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST22;
	}
}

static inline void hri_xdmac_clear_GS_ST22_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST22;
}

static inline void hri_xdmac_set_GS_ST23_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST23;
}

static inline bool hri_xdmac_get_GS_ST23_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GS & XDMAC_GS_ST23) >> XDMAC_GS_ST23_Pos;
}

static inline void hri_xdmac_write_GS_ST23_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST23;
	} else {
		((Xdmac *)hw)->XDMAC_GE = XDMAC_GS_ST23;
	}
}

static inline void hri_xdmac_clear_GS_ST23_bit(const void *const hw)
{
	((Xdmac *)hw)->XDMAC_GD = XDMAC_GS_ST23;
}

static inline void hri_xdmac_set_GS_reg(const void *const hw, hri_xdmac_gs_reg_t mask)
{
	((Xdmac *)hw)->XDMAC_GE = mask;
}

static inline hri_xdmac_gs_reg_t hri_xdmac_get_GS_reg(const void *const hw, hri_xdmac_gs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GS;
	tmp &= mask;
	return tmp;
}

static inline hri_xdmac_gs_reg_t hri_xdmac_read_GS_reg(const void *const hw)
{
	return ((Xdmac *)hw)->XDMAC_GS;
}

static inline void hri_xdmac_write_GS_reg(const void *const hw, hri_xdmac_gs_reg_t data)
{
	((Xdmac *)hw)->XDMAC_GE = data;
	((Xdmac *)hw)->XDMAC_GD = ~data;
}

static inline void hri_xdmac_clear_GS_reg(const void *const hw, hri_xdmac_gs_reg_t mask)
{
	((Xdmac *)hw)->XDMAC_GD = mask;
}

static inline hri_xdmac_gtype_reg_t hri_xdmac_get_GTYPE_NB_CH_bf(const void *const hw, hri_xdmac_gtype_reg_t mask)
{
	return (((Xdmac *)hw)->XDMAC_GTYPE & XDMAC_GTYPE_NB_CH(mask)) >> XDMAC_GTYPE_NB_CH_Pos;
}

static inline hri_xdmac_gtype_reg_t hri_xdmac_read_GTYPE_NB_CH_bf(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GTYPE & XDMAC_GTYPE_NB_CH_Msk) >> XDMAC_GTYPE_NB_CH_Pos;
}

static inline hri_xdmac_gtype_reg_t hri_xdmac_get_GTYPE_FIFO_SZ_bf(const void *const hw, hri_xdmac_gtype_reg_t mask)
{
	return (((Xdmac *)hw)->XDMAC_GTYPE & XDMAC_GTYPE_FIFO_SZ(mask)) >> XDMAC_GTYPE_FIFO_SZ_Pos;
}

static inline hri_xdmac_gtype_reg_t hri_xdmac_read_GTYPE_FIFO_SZ_bf(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GTYPE & XDMAC_GTYPE_FIFO_SZ_Msk) >> XDMAC_GTYPE_FIFO_SZ_Pos;
}

static inline hri_xdmac_gtype_reg_t hri_xdmac_get_GTYPE_NB_REQ_bf(const void *const hw, hri_xdmac_gtype_reg_t mask)
{
	return (((Xdmac *)hw)->XDMAC_GTYPE & XDMAC_GTYPE_NB_REQ(mask)) >> XDMAC_GTYPE_NB_REQ_Pos;
}

static inline hri_xdmac_gtype_reg_t hri_xdmac_read_GTYPE_NB_REQ_bf(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GTYPE & XDMAC_GTYPE_NB_REQ_Msk) >> XDMAC_GTYPE_NB_REQ_Pos;
}

static inline hri_xdmac_gtype_reg_t hri_xdmac_get_GTYPE_reg(const void *const hw, hri_xdmac_gtype_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GTYPE;
	tmp &= mask;
	return tmp;
}

static inline hri_xdmac_gtype_reg_t hri_xdmac_read_GTYPE_reg(const void *const hw)
{
	return ((Xdmac *)hw)->XDMAC_GTYPE;
}

static inline bool hri_xdmac_get_GIS_IS0_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS0) > 0;
}

static inline bool hri_xdmac_get_GIS_IS1_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS1) > 0;
}

static inline bool hri_xdmac_get_GIS_IS2_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS2) > 0;
}

static inline bool hri_xdmac_get_GIS_IS3_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS3) > 0;
}

static inline bool hri_xdmac_get_GIS_IS4_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS4) > 0;
}

static inline bool hri_xdmac_get_GIS_IS5_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS5) > 0;
}

static inline bool hri_xdmac_get_GIS_IS6_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS6) > 0;
}

static inline bool hri_xdmac_get_GIS_IS7_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS7) > 0;
}

static inline bool hri_xdmac_get_GIS_IS8_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS8) > 0;
}

static inline bool hri_xdmac_get_GIS_IS9_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS9) > 0;
}

static inline bool hri_xdmac_get_GIS_IS10_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS10) > 0;
}

static inline bool hri_xdmac_get_GIS_IS11_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS11) > 0;
}

static inline bool hri_xdmac_get_GIS_IS12_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS12) > 0;
}

static inline bool hri_xdmac_get_GIS_IS13_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS13) > 0;
}

static inline bool hri_xdmac_get_GIS_IS14_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS14) > 0;
}

static inline bool hri_xdmac_get_GIS_IS15_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS15) > 0;
}

static inline bool hri_xdmac_get_GIS_IS16_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS16) > 0;
}

static inline bool hri_xdmac_get_GIS_IS17_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS17) > 0;
}

static inline bool hri_xdmac_get_GIS_IS18_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS18) > 0;
}

static inline bool hri_xdmac_get_GIS_IS19_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS19) > 0;
}

static inline bool hri_xdmac_get_GIS_IS20_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS20) > 0;
}

static inline bool hri_xdmac_get_GIS_IS21_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS21) > 0;
}

static inline bool hri_xdmac_get_GIS_IS22_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS22) > 0;
}

static inline bool hri_xdmac_get_GIS_IS23_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GIS & XDMAC_GIS_IS23) > 0;
}

static inline hri_xdmac_gis_reg_t hri_xdmac_get_GIS_reg(const void *const hw, hri_xdmac_gis_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GIS;
	tmp &= mask;
	return tmp;
}

static inline hri_xdmac_gis_reg_t hri_xdmac_read_GIS_reg(const void *const hw)
{
	return ((Xdmac *)hw)->XDMAC_GIS;
}

static inline bool hri_xdmac_get_GSWS_SWRS0_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS0) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS1_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS1) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS2_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS2) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS3_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS3) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS4_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS4) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS5_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS5) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS6_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS6) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS7_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS7) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS8_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS8) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS9_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS9) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS10_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS10) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS11_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS11) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS12_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS12) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS13_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS13) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS14_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS14) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS15_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS15) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS16_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS16) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS17_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS17) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS18_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS18) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS19_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS19) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS20_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS20) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS21_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS21) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS22_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS22) > 0;
}

static inline bool hri_xdmac_get_GSWS_SWRS23_bit(const void *const hw)
{
	return (((Xdmac *)hw)->XDMAC_GSWS & XDMAC_GSWS_SWRS23) > 0;
}

static inline hri_xdmac_gsws_reg_t hri_xdmac_get_GSWS_reg(const void *const hw, hri_xdmac_gsws_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GSWS;
	tmp &= mask;
	return tmp;
}

static inline hri_xdmac_gsws_reg_t hri_xdmac_read_GSWS_reg(const void *const hw)
{
	return ((Xdmac *)hw)->XDMAC_GSWS;
}

static inline void hri_xdmac_set_GCFG_CGDISREG_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG |= XDMAC_GCFG_CGDISREG;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GCFG_CGDISREG_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp = (tmp & XDMAC_GCFG_CGDISREG) >> XDMAC_GCFG_CGDISREG_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GCFG_CGDISREG_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp &= ~XDMAC_GCFG_CGDISREG;
	tmp |= value << XDMAC_GCFG_CGDISREG_Pos;
	((Xdmac *)hw)->XDMAC_GCFG = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GCFG_CGDISREG_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG &= ~XDMAC_GCFG_CGDISREG;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GCFG_CGDISREG_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG ^= XDMAC_GCFG_CGDISREG;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GCFG_CGDISPIPE_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG |= XDMAC_GCFG_CGDISPIPE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GCFG_CGDISPIPE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp = (tmp & XDMAC_GCFG_CGDISPIPE) >> XDMAC_GCFG_CGDISPIPE_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GCFG_CGDISPIPE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp &= ~XDMAC_GCFG_CGDISPIPE;
	tmp |= value << XDMAC_GCFG_CGDISPIPE_Pos;
	((Xdmac *)hw)->XDMAC_GCFG = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GCFG_CGDISPIPE_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG &= ~XDMAC_GCFG_CGDISPIPE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GCFG_CGDISPIPE_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG ^= XDMAC_GCFG_CGDISPIPE;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GCFG_CGDISFIFO_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG |= XDMAC_GCFG_CGDISFIFO;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GCFG_CGDISFIFO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp = (tmp & XDMAC_GCFG_CGDISFIFO) >> XDMAC_GCFG_CGDISFIFO_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GCFG_CGDISFIFO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp &= ~XDMAC_GCFG_CGDISFIFO;
	tmp |= value << XDMAC_GCFG_CGDISFIFO_Pos;
	((Xdmac *)hw)->XDMAC_GCFG = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GCFG_CGDISFIFO_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG &= ~XDMAC_GCFG_CGDISFIFO;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GCFG_CGDISFIFO_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG ^= XDMAC_GCFG_CGDISFIFO;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GCFG_CGDISIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG |= XDMAC_GCFG_CGDISIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GCFG_CGDISIF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp = (tmp & XDMAC_GCFG_CGDISIF) >> XDMAC_GCFG_CGDISIF_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GCFG_CGDISIF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp &= ~XDMAC_GCFG_CGDISIF;
	tmp |= value << XDMAC_GCFG_CGDISIF_Pos;
	((Xdmac *)hw)->XDMAC_GCFG = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GCFG_CGDISIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG &= ~XDMAC_GCFG_CGDISIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GCFG_CGDISIF_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG ^= XDMAC_GCFG_CGDISIF;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GCFG_BXKBEN_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG |= XDMAC_GCFG_BXKBEN;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GCFG_BXKBEN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp = (tmp & XDMAC_GCFG_BXKBEN) >> XDMAC_GCFG_BXKBEN_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GCFG_BXKBEN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp &= ~XDMAC_GCFG_BXKBEN;
	tmp |= value << XDMAC_GCFG_BXKBEN_Pos;
	((Xdmac *)hw)->XDMAC_GCFG = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GCFG_BXKBEN_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG &= ~XDMAC_GCFG_BXKBEN;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GCFG_BXKBEN_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG ^= XDMAC_GCFG_BXKBEN;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GCFG_reg(const void *const hw, hri_xdmac_gcfg_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gcfg_reg_t hri_xdmac_get_GCFG_reg(const void *const hw, hri_xdmac_gcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GCFG;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_GCFG_reg(const void *const hw, hri_xdmac_gcfg_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GCFG_reg(const void *const hw, hri_xdmac_gcfg_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GCFG_reg(const void *const hw, hri_xdmac_gcfg_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GCFG ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gcfg_reg_t hri_xdmac_read_GCFG_reg(const void *const hw)
{
	return ((Xdmac *)hw)->XDMAC_GCFG;
}

static inline void hri_xdmac_set_GWAC_PW0_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC |= XDMAC_GWAC_PW0(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_get_GWAC_PW0_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp = (tmp & XDMAC_GWAC_PW0(mask)) >> XDMAC_GWAC_PW0_Pos;
	return tmp;
}

static inline void hri_xdmac_write_GWAC_PW0_bf(const void *const hw, hri_xdmac_gwac_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp &= ~XDMAC_GWAC_PW0_Msk;
	tmp |= XDMAC_GWAC_PW0(data);
	((Xdmac *)hw)->XDMAC_GWAC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWAC_PW0_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC &= ~XDMAC_GWAC_PW0(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWAC_PW0_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC ^= XDMAC_GWAC_PW0(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_read_GWAC_PW0_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp = (tmp & XDMAC_GWAC_PW0_Msk) >> XDMAC_GWAC_PW0_Pos;
	return tmp;
}

static inline void hri_xdmac_set_GWAC_PW1_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC |= XDMAC_GWAC_PW1(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_get_GWAC_PW1_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp = (tmp & XDMAC_GWAC_PW1(mask)) >> XDMAC_GWAC_PW1_Pos;
	return tmp;
}

static inline void hri_xdmac_write_GWAC_PW1_bf(const void *const hw, hri_xdmac_gwac_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp &= ~XDMAC_GWAC_PW1_Msk;
	tmp |= XDMAC_GWAC_PW1(data);
	((Xdmac *)hw)->XDMAC_GWAC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWAC_PW1_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC &= ~XDMAC_GWAC_PW1(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWAC_PW1_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC ^= XDMAC_GWAC_PW1(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_read_GWAC_PW1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp = (tmp & XDMAC_GWAC_PW1_Msk) >> XDMAC_GWAC_PW1_Pos;
	return tmp;
}

static inline void hri_xdmac_set_GWAC_PW2_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC |= XDMAC_GWAC_PW2(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_get_GWAC_PW2_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp = (tmp & XDMAC_GWAC_PW2(mask)) >> XDMAC_GWAC_PW2_Pos;
	return tmp;
}

static inline void hri_xdmac_write_GWAC_PW2_bf(const void *const hw, hri_xdmac_gwac_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp &= ~XDMAC_GWAC_PW2_Msk;
	tmp |= XDMAC_GWAC_PW2(data);
	((Xdmac *)hw)->XDMAC_GWAC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWAC_PW2_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC &= ~XDMAC_GWAC_PW2(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWAC_PW2_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC ^= XDMAC_GWAC_PW2(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_read_GWAC_PW2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp = (tmp & XDMAC_GWAC_PW2_Msk) >> XDMAC_GWAC_PW2_Pos;
	return tmp;
}

static inline void hri_xdmac_set_GWAC_PW3_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC |= XDMAC_GWAC_PW3(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_get_GWAC_PW3_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp = (tmp & XDMAC_GWAC_PW3(mask)) >> XDMAC_GWAC_PW3_Pos;
	return tmp;
}

static inline void hri_xdmac_write_GWAC_PW3_bf(const void *const hw, hri_xdmac_gwac_reg_t data)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp &= ~XDMAC_GWAC_PW3_Msk;
	tmp |= XDMAC_GWAC_PW3(data);
	((Xdmac *)hw)->XDMAC_GWAC = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWAC_PW3_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC &= ~XDMAC_GWAC_PW3(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWAC_PW3_bf(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC ^= XDMAC_GWAC_PW3(mask);
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_read_GWAC_PW3_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp = (tmp & XDMAC_GWAC_PW3_Msk) >> XDMAC_GWAC_PW3_Pos;
	return tmp;
}

static inline void hri_xdmac_set_GWAC_reg(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_get_GWAC_reg(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWAC;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_GWAC_reg(const void *const hw, hri_xdmac_gwac_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWAC_reg(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWAC_reg(const void *const hw, hri_xdmac_gwac_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWAC ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gwac_reg_t hri_xdmac_read_GWAC_reg(const void *const hw)
{
	return ((Xdmac *)hw)->XDMAC_GWAC;
}

static inline void hri_xdmac_set_GRS_RS0_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS0;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS0) >> XDMAC_GRS_RS0_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS0;
	tmp |= value << XDMAC_GRS_RS0_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS0_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS0;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS0_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS0;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS1_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS1;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS1) >> XDMAC_GRS_RS1_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS1;
	tmp |= value << XDMAC_GRS_RS1_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS1_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS1;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS1_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS1;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS2_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS2;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS2) >> XDMAC_GRS_RS2_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS2;
	tmp |= value << XDMAC_GRS_RS2_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS2_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS2;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS2_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS2;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS3_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS3;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS3) >> XDMAC_GRS_RS3_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS3;
	tmp |= value << XDMAC_GRS_RS3_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS3_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS3;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS3_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS3;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS4_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS4;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS4) >> XDMAC_GRS_RS4_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS4;
	tmp |= value << XDMAC_GRS_RS4_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS4_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS4;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS4_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS4;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS5_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS5;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS5) >> XDMAC_GRS_RS5_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS5;
	tmp |= value << XDMAC_GRS_RS5_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS5_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS5;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS5_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS5;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS6_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS6;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS6) >> XDMAC_GRS_RS6_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS6;
	tmp |= value << XDMAC_GRS_RS6_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS6_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS6;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS6_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS6;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS7_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS7;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS7) >> XDMAC_GRS_RS7_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS7;
	tmp |= value << XDMAC_GRS_RS7_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS7_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS7;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS7_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS7;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS8_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS8;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS8) >> XDMAC_GRS_RS8_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS8;
	tmp |= value << XDMAC_GRS_RS8_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS8_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS8;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS8_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS8;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS9_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS9;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS9) >> XDMAC_GRS_RS9_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS9;
	tmp |= value << XDMAC_GRS_RS9_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS9_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS9;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS9_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS9;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS10_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS10;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS10) >> XDMAC_GRS_RS10_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS10;
	tmp |= value << XDMAC_GRS_RS10_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS10_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS10;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS10_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS10;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS11_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS11;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS11) >> XDMAC_GRS_RS11_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS11;
	tmp |= value << XDMAC_GRS_RS11_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS11_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS11;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS11_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS11;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS12_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS12;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS12) >> XDMAC_GRS_RS12_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS12;
	tmp |= value << XDMAC_GRS_RS12_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS12_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS12;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS12_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS12;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS13_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS13;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS13) >> XDMAC_GRS_RS13_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS13;
	tmp |= value << XDMAC_GRS_RS13_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS13_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS13;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS13_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS13;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS14_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS14;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS14) >> XDMAC_GRS_RS14_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS14;
	tmp |= value << XDMAC_GRS_RS14_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS14_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS14;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS14_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS14;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS15_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS15;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS15) >> XDMAC_GRS_RS15_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS15;
	tmp |= value << XDMAC_GRS_RS15_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS15_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS15;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS15_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS15;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS16_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS16;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS16) >> XDMAC_GRS_RS16_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS16;
	tmp |= value << XDMAC_GRS_RS16_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS16_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS16;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS16_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS16;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS17_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS17;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS17) >> XDMAC_GRS_RS17_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS17;
	tmp |= value << XDMAC_GRS_RS17_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS17_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS17;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS17_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS17;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS18_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS18;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS18) >> XDMAC_GRS_RS18_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS18;
	tmp |= value << XDMAC_GRS_RS18_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS18_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS18;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS18_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS18;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS19_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS19;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS19) >> XDMAC_GRS_RS19_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS19;
	tmp |= value << XDMAC_GRS_RS19_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS19_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS19;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS19_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS19;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS20_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS20;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS20) >> XDMAC_GRS_RS20_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS20;
	tmp |= value << XDMAC_GRS_RS20_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS20_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS20;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS20_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS20;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS21_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS21;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS21) >> XDMAC_GRS_RS21_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS21;
	tmp |= value << XDMAC_GRS_RS21_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS21_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS21;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS21_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS21;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS22_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS22;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS22) >> XDMAC_GRS_RS22_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS22;
	tmp |= value << XDMAC_GRS_RS22_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS22_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS22;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS22_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS22;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_RS23_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= XDMAC_GRS_RS23;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GRS_RS23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp = (tmp & XDMAC_GRS_RS23) >> XDMAC_GRS_RS23_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GRS_RS23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= ~XDMAC_GRS_RS23;
	tmp |= value << XDMAC_GRS_RS23_Pos;
	((Xdmac *)hw)->XDMAC_GRS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_RS23_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~XDMAC_GRS_RS23;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_RS23_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= XDMAC_GRS_RS23;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GRS_reg(const void *const hw, hri_xdmac_grs_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_grs_reg_t hri_xdmac_get_GRS_reg(const void *const hw, hri_xdmac_grs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GRS;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_GRS_reg(const void *const hw, hri_xdmac_grs_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GRS_reg(const void *const hw, hri_xdmac_grs_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GRS_reg(const void *const hw, hri_xdmac_grs_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRS ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_grs_reg_t hri_xdmac_read_GRS_reg(const void *const hw)
{
	return ((Xdmac *)hw)->XDMAC_GRS;
}

static inline void hri_xdmac_set_GWS_WS0_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS0;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS0) >> XDMAC_GWS_WS0_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS0;
	tmp |= value << XDMAC_GWS_WS0_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS0_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS0;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS0_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS0;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS1_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS1;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS1) >> XDMAC_GWS_WS1_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS1;
	tmp |= value << XDMAC_GWS_WS1_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS1_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS1;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS1_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS1;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS2_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS2;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS2) >> XDMAC_GWS_WS2_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS2;
	tmp |= value << XDMAC_GWS_WS2_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS2_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS2;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS2_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS2;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS3_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS3;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS3) >> XDMAC_GWS_WS3_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS3;
	tmp |= value << XDMAC_GWS_WS3_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS3_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS3;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS3_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS3;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS4_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS4;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS4) >> XDMAC_GWS_WS4_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS4;
	tmp |= value << XDMAC_GWS_WS4_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS4_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS4;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS4_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS4;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS5_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS5;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS5) >> XDMAC_GWS_WS5_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS5;
	tmp |= value << XDMAC_GWS_WS5_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS5_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS5;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS5_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS5;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS6_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS6;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS6) >> XDMAC_GWS_WS6_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS6;
	tmp |= value << XDMAC_GWS_WS6_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS6_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS6;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS6_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS6;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS7_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS7;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS7) >> XDMAC_GWS_WS7_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS7;
	tmp |= value << XDMAC_GWS_WS7_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS7_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS7;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS7_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS7;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS8_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS8;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS8) >> XDMAC_GWS_WS8_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS8;
	tmp |= value << XDMAC_GWS_WS8_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS8_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS8;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS8_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS8;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS9_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS9;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS9) >> XDMAC_GWS_WS9_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS9;
	tmp |= value << XDMAC_GWS_WS9_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS9_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS9;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS9_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS9;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS10_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS10;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS10) >> XDMAC_GWS_WS10_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS10;
	tmp |= value << XDMAC_GWS_WS10_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS10_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS10;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS10_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS10;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS11_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS11;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS11) >> XDMAC_GWS_WS11_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS11;
	tmp |= value << XDMAC_GWS_WS11_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS11_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS11;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS11_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS11;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS12_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS12;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS12) >> XDMAC_GWS_WS12_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS12;
	tmp |= value << XDMAC_GWS_WS12_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS12_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS12;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS12_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS12;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS13_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS13;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS13) >> XDMAC_GWS_WS13_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS13;
	tmp |= value << XDMAC_GWS_WS13_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS13_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS13;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS13_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS13;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS14_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS14;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS14) >> XDMAC_GWS_WS14_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS14;
	tmp |= value << XDMAC_GWS_WS14_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS14_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS14;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS14_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS14;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS15_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS15;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS15) >> XDMAC_GWS_WS15_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS15;
	tmp |= value << XDMAC_GWS_WS15_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS15_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS15;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS15_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS15;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS16_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS16;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS16) >> XDMAC_GWS_WS16_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS16;
	tmp |= value << XDMAC_GWS_WS16_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS16_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS16;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS16_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS16;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS17_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS17;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS17) >> XDMAC_GWS_WS17_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS17;
	tmp |= value << XDMAC_GWS_WS17_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS17_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS17;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS17_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS17;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS18_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS18;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS18) >> XDMAC_GWS_WS18_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS18;
	tmp |= value << XDMAC_GWS_WS18_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS18_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS18;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS18_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS18;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS19_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS19;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS19) >> XDMAC_GWS_WS19_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS19;
	tmp |= value << XDMAC_GWS_WS19_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS19_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS19;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS19_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS19;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS20_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS20;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS20) >> XDMAC_GWS_WS20_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS20;
	tmp |= value << XDMAC_GWS_WS20_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS20_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS20;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS20_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS20;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS21_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS21;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS21) >> XDMAC_GWS_WS21_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS21;
	tmp |= value << XDMAC_GWS_WS21_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS21_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS21;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS21_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS21;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS22_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS22;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS22) >> XDMAC_GWS_WS22_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS22;
	tmp |= value << XDMAC_GWS_WS22_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS22_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS22;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS22_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS22;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_WS23_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= XDMAC_GWS_WS23;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_xdmac_get_GWS_WS23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp = (tmp & XDMAC_GWS_WS23) >> XDMAC_GWS_WS23_Pos;
	return (bool)tmp;
}

static inline void hri_xdmac_write_GWS_WS23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	XDMAC_CRITICAL_SECTION_ENTER();
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= ~XDMAC_GWS_WS23;
	tmp |= value << XDMAC_GWS_WS23_Pos;
	((Xdmac *)hw)->XDMAC_GWS = tmp;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_WS23_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~XDMAC_GWS_WS23;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_WS23_bit(const void *const hw)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= XDMAC_GWS_WS23;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_set_GWS_reg(const void *const hw, hri_xdmac_gws_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS |= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gws_reg_t hri_xdmac_get_GWS_reg(const void *const hw, hri_xdmac_gws_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Xdmac *)hw)->XDMAC_GWS;
	tmp &= mask;
	return tmp;
}

static inline void hri_xdmac_write_GWS_reg(const void *const hw, hri_xdmac_gws_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_clear_GWS_reg(const void *const hw, hri_xdmac_gws_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS &= ~mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_toggle_GWS_reg(const void *const hw, hri_xdmac_gws_reg_t mask)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GWS ^= mask;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline hri_xdmac_gws_reg_t hri_xdmac_read_GWS_reg(const void *const hw)
{
	return ((Xdmac *)hw)->XDMAC_GWS;
}

static inline void hri_xdmac_write_GRWS_reg(const void *const hw, hri_xdmac_grws_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRWS = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_write_GRWR_reg(const void *const hw, hri_xdmac_grwr_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GRWR = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_write_GSWR_reg(const void *const hw, hri_xdmac_gswr_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GSWR = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_xdmac_write_GSWF_reg(const void *const hw, hri_xdmac_gswf_reg_t data)
{
	XDMAC_CRITICAL_SECTION_ENTER();
	((Xdmac *)hw)->XDMAC_GSWF = data;
	XDMAC_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_XDMAC_E70B_H_INCLUDED */
#endif /* _SAME70_XDMAC_COMPONENT_ */
