/**
 * \file
 *
 * \brief SAM DSU
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAML10_DSU_COMPONENT_
#ifndef _HRI_DSU_L10_H_INCLUDED_
#define _HRI_DSU_L10_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_DSU_CRITICAL_SECTIONS)
#define DSU_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define DSU_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define DSU_CRITICAL_SECTION_ENTER()
#define DSU_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_dsu_addr_reg_t;
typedef uint32_t hri_dsu_bcc_reg_t;
typedef uint32_t hri_dsu_cfg_reg_t;
typedef uint32_t hri_dsu_cid0_reg_t;
typedef uint32_t hri_dsu_cid1_reg_t;
typedef uint32_t hri_dsu_cid2_reg_t;
typedef uint32_t hri_dsu_cid3_reg_t;
typedef uint32_t hri_dsu_data_reg_t;
typedef uint32_t hri_dsu_dcc_reg_t;
typedef uint32_t hri_dsu_dcfg_reg_t;
typedef uint32_t hri_dsu_did_reg_t;
typedef uint32_t hri_dsu_end_reg_t;
typedef uint32_t hri_dsu_entry0_reg_t;
typedef uint32_t hri_dsu_entry1_reg_t;
typedef uint32_t hri_dsu_length_reg_t;
typedef uint32_t hri_dsu_memtype_reg_t;
typedef uint32_t hri_dsu_pid0_reg_t;
typedef uint32_t hri_dsu_pid1_reg_t;
typedef uint32_t hri_dsu_pid2_reg_t;
typedef uint32_t hri_dsu_pid3_reg_t;
typedef uint32_t hri_dsu_pid4_reg_t;
typedef uint32_t hri_dsu_pid5_reg_t;
typedef uint32_t hri_dsu_pid6_reg_t;
typedef uint32_t hri_dsu_pid7_reg_t;
typedef uint8_t  hri_dsu_ctrl_reg_t;
typedef uint8_t  hri_dsu_statusa_reg_t;
typedef uint8_t  hri_dsu_statusb_reg_t;
typedef uint8_t  hri_dsu_statusc_reg_t;

static inline bool hri_dsu_get_STATUSB_DBGPRES_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSB.reg & DSU_STATUSB_DBGPRES_Msk) >> DSU_STATUSB_DBGPRES_Pos;
}

static inline bool hri_dsu_get_STATUSB_HPE_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSB.reg & DSU_STATUSB_HPE_Msk) >> DSU_STATUSB_HPE_Pos;
}

static inline bool hri_dsu_get_STATUSB_DCCD0_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSB.reg & DSU_STATUSB_DCCD0_Msk) >> DSU_STATUSB_DCCD0_Pos;
}

static inline bool hri_dsu_get_STATUSB_DCCD1_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSB.reg & DSU_STATUSB_DCCD1_Msk) >> DSU_STATUSB_DCCD1_Pos;
}

static inline bool hri_dsu_get_STATUSB_BCCD0_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSB.reg & DSU_STATUSB_BCCD0_Msk) >> DSU_STATUSB_BCCD0_Pos;
}

static inline bool hri_dsu_get_STATUSB_BCCD1_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSB.reg & DSU_STATUSB_BCCD1_Msk) >> DSU_STATUSB_BCCD1_Pos;
}

static inline hri_dsu_statusb_reg_t hri_dsu_get_STATUSB_DAL_bf(const void *const hw, hri_dsu_statusb_reg_t mask)
{
	return (((Dsu *)hw)->STATUSB.reg & DSU_STATUSB_DAL(mask)) >> DSU_STATUSB_DAL_Pos;
}

static inline hri_dsu_statusb_reg_t hri_dsu_read_STATUSB_DAL_bf(const void *const hw)
{
	return (((Dsu *)hw)->STATUSB.reg & DSU_STATUSB_DAL_Msk) >> DSU_STATUSB_DAL_Pos;
}

static inline hri_dsu_statusb_reg_t hri_dsu_get_STATUSB_reg(const void *const hw, hri_dsu_statusb_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Dsu *)hw)->STATUSB.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_statusb_reg_t hri_dsu_read_STATUSB_reg(const void *const hw)
{
	return ((Dsu *)hw)->STATUSB.reg;
}

static inline hri_dsu_statusc_reg_t hri_dsu_get_STATUSC_reg(const void *const hw, hri_dsu_statusc_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Dsu *)hw)->STATUSC.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_statusc_reg_t hri_dsu_read_STATUSC_reg(const void *const hw)
{
	return ((Dsu *)hw)->STATUSC.reg;
}

static inline hri_dsu_did_reg_t hri_dsu_get_DID_DEVSEL_bf(const void *const hw, hri_dsu_did_reg_t mask)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_DEVSEL(mask)) >> DSU_DID_DEVSEL_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_read_DID_DEVSEL_bf(const void *const hw)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_DEVSEL_Msk) >> DSU_DID_DEVSEL_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_get_DID_REVISION_bf(const void *const hw, hri_dsu_did_reg_t mask)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_REVISION(mask)) >> DSU_DID_REVISION_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_read_DID_REVISION_bf(const void *const hw)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_REVISION_Msk) >> DSU_DID_REVISION_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_get_DID_DIE_bf(const void *const hw, hri_dsu_did_reg_t mask)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_DIE(mask)) >> DSU_DID_DIE_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_read_DID_DIE_bf(const void *const hw)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_DIE_Msk) >> DSU_DID_DIE_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_get_DID_SERIES_bf(const void *const hw, hri_dsu_did_reg_t mask)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_SERIES(mask)) >> DSU_DID_SERIES_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_read_DID_SERIES_bf(const void *const hw)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_SERIES_Msk) >> DSU_DID_SERIES_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_get_DID_FAMILY_bf(const void *const hw, hri_dsu_did_reg_t mask)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_FAMILY(mask)) >> DSU_DID_FAMILY_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_read_DID_FAMILY_bf(const void *const hw)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_FAMILY_Msk) >> DSU_DID_FAMILY_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_get_DID_PROCESSOR_bf(const void *const hw, hri_dsu_did_reg_t mask)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_PROCESSOR(mask)) >> DSU_DID_PROCESSOR_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_read_DID_PROCESSOR_bf(const void *const hw)
{
	return (((Dsu *)hw)->DID.reg & DSU_DID_PROCESSOR_Msk) >> DSU_DID_PROCESSOR_Pos;
}

static inline hri_dsu_did_reg_t hri_dsu_get_DID_reg(const void *const hw, hri_dsu_did_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DID.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_did_reg_t hri_dsu_read_DID_reg(const void *const hw)
{
	return ((Dsu *)hw)->DID.reg;
}

static inline bool hri_dsu_get_ENTRY0_EPRES_bit(const void *const hw)
{
	return (((Dsu *)hw)->ENTRY0.reg & DSU_ENTRY0_EPRES_Msk) >> DSU_ENTRY0_EPRES_Pos;
}

static inline bool hri_dsu_get_ENTRY0_FMT_bit(const void *const hw)
{
	return (((Dsu *)hw)->ENTRY0.reg & DSU_ENTRY0_FMT_Msk) >> DSU_ENTRY0_FMT_Pos;
}

static inline hri_dsu_entry0_reg_t hri_dsu_get_ENTRY0_ADDOFF_bf(const void *const hw, hri_dsu_entry0_reg_t mask)
{
	return (((Dsu *)hw)->ENTRY0.reg & DSU_ENTRY0_ADDOFF(mask)) >> DSU_ENTRY0_ADDOFF_Pos;
}

static inline hri_dsu_entry0_reg_t hri_dsu_read_ENTRY0_ADDOFF_bf(const void *const hw)
{
	return (((Dsu *)hw)->ENTRY0.reg & DSU_ENTRY0_ADDOFF_Msk) >> DSU_ENTRY0_ADDOFF_Pos;
}

static inline hri_dsu_entry0_reg_t hri_dsu_get_ENTRY0_reg(const void *const hw, hri_dsu_entry0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->ENTRY0.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_entry0_reg_t hri_dsu_read_ENTRY0_reg(const void *const hw)
{
	return ((Dsu *)hw)->ENTRY0.reg;
}

static inline hri_dsu_entry1_reg_t hri_dsu_get_ENTRY1_reg(const void *const hw, hri_dsu_entry1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->ENTRY1.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_entry1_reg_t hri_dsu_read_ENTRY1_reg(const void *const hw)
{
	return ((Dsu *)hw)->ENTRY1.reg;
}

static inline hri_dsu_end_reg_t hri_dsu_get_END_END_bf(const void *const hw, hri_dsu_end_reg_t mask)
{
	return (((Dsu *)hw)->END.reg & DSU_END_END(mask)) >> DSU_END_END_Pos;
}

static inline hri_dsu_end_reg_t hri_dsu_read_END_END_bf(const void *const hw)
{
	return (((Dsu *)hw)->END.reg & DSU_END_END_Msk) >> DSU_END_END_Pos;
}

static inline hri_dsu_end_reg_t hri_dsu_get_END_reg(const void *const hw, hri_dsu_end_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->END.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_end_reg_t hri_dsu_read_END_reg(const void *const hw)
{
	return ((Dsu *)hw)->END.reg;
}

static inline bool hri_dsu_get_MEMTYPE_SMEMP_bit(const void *const hw)
{
	return (((Dsu *)hw)->MEMTYPE.reg & DSU_MEMTYPE_SMEMP_Msk) >> DSU_MEMTYPE_SMEMP_Pos;
}

static inline hri_dsu_memtype_reg_t hri_dsu_get_MEMTYPE_reg(const void *const hw, hri_dsu_memtype_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->MEMTYPE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_memtype_reg_t hri_dsu_read_MEMTYPE_reg(const void *const hw)
{
	return ((Dsu *)hw)->MEMTYPE.reg;
}

static inline hri_dsu_pid4_reg_t hri_dsu_get_PID4_JEPCC_bf(const void *const hw, hri_dsu_pid4_reg_t mask)
{
	return (((Dsu *)hw)->PID4.reg & DSU_PID4_JEPCC(mask)) >> DSU_PID4_JEPCC_Pos;
}

static inline hri_dsu_pid4_reg_t hri_dsu_read_PID4_JEPCC_bf(const void *const hw)
{
	return (((Dsu *)hw)->PID4.reg & DSU_PID4_JEPCC_Msk) >> DSU_PID4_JEPCC_Pos;
}

static inline hri_dsu_pid4_reg_t hri_dsu_get_PID4_FKBC_bf(const void *const hw, hri_dsu_pid4_reg_t mask)
{
	return (((Dsu *)hw)->PID4.reg & DSU_PID4_FKBC(mask)) >> DSU_PID4_FKBC_Pos;
}

static inline hri_dsu_pid4_reg_t hri_dsu_read_PID4_FKBC_bf(const void *const hw)
{
	return (((Dsu *)hw)->PID4.reg & DSU_PID4_FKBC_Msk) >> DSU_PID4_FKBC_Pos;
}

static inline hri_dsu_pid4_reg_t hri_dsu_get_PID4_reg(const void *const hw, hri_dsu_pid4_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->PID4.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_pid4_reg_t hri_dsu_read_PID4_reg(const void *const hw)
{
	return ((Dsu *)hw)->PID4.reg;
}

static inline hri_dsu_pid5_reg_t hri_dsu_get_PID5_reg(const void *const hw, hri_dsu_pid5_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->PID5.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_pid5_reg_t hri_dsu_read_PID5_reg(const void *const hw)
{
	return ((Dsu *)hw)->PID5.reg;
}

static inline hri_dsu_pid6_reg_t hri_dsu_get_PID6_reg(const void *const hw, hri_dsu_pid6_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->PID6.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_pid6_reg_t hri_dsu_read_PID6_reg(const void *const hw)
{
	return ((Dsu *)hw)->PID6.reg;
}

static inline hri_dsu_pid7_reg_t hri_dsu_get_PID7_reg(const void *const hw, hri_dsu_pid7_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->PID7.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_pid7_reg_t hri_dsu_read_PID7_reg(const void *const hw)
{
	return ((Dsu *)hw)->PID7.reg;
}

static inline hri_dsu_pid0_reg_t hri_dsu_get_PID0_PARTNBL_bf(const void *const hw, hri_dsu_pid0_reg_t mask)
{
	return (((Dsu *)hw)->PID0.reg & DSU_PID0_PARTNBL(mask)) >> DSU_PID0_PARTNBL_Pos;
}

static inline hri_dsu_pid0_reg_t hri_dsu_read_PID0_PARTNBL_bf(const void *const hw)
{
	return (((Dsu *)hw)->PID0.reg & DSU_PID0_PARTNBL_Msk) >> DSU_PID0_PARTNBL_Pos;
}

static inline hri_dsu_pid0_reg_t hri_dsu_get_PID0_reg(const void *const hw, hri_dsu_pid0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->PID0.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_pid0_reg_t hri_dsu_read_PID0_reg(const void *const hw)
{
	return ((Dsu *)hw)->PID0.reg;
}

static inline hri_dsu_pid1_reg_t hri_dsu_get_PID1_PARTNBH_bf(const void *const hw, hri_dsu_pid1_reg_t mask)
{
	return (((Dsu *)hw)->PID1.reg & DSU_PID1_PARTNBH(mask)) >> DSU_PID1_PARTNBH_Pos;
}

static inline hri_dsu_pid1_reg_t hri_dsu_read_PID1_PARTNBH_bf(const void *const hw)
{
	return (((Dsu *)hw)->PID1.reg & DSU_PID1_PARTNBH_Msk) >> DSU_PID1_PARTNBH_Pos;
}

static inline hri_dsu_pid1_reg_t hri_dsu_get_PID1_JEPIDCL_bf(const void *const hw, hri_dsu_pid1_reg_t mask)
{
	return (((Dsu *)hw)->PID1.reg & DSU_PID1_JEPIDCL(mask)) >> DSU_PID1_JEPIDCL_Pos;
}

static inline hri_dsu_pid1_reg_t hri_dsu_read_PID1_JEPIDCL_bf(const void *const hw)
{
	return (((Dsu *)hw)->PID1.reg & DSU_PID1_JEPIDCL_Msk) >> DSU_PID1_JEPIDCL_Pos;
}

static inline hri_dsu_pid1_reg_t hri_dsu_get_PID1_reg(const void *const hw, hri_dsu_pid1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->PID1.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_pid1_reg_t hri_dsu_read_PID1_reg(const void *const hw)
{
	return ((Dsu *)hw)->PID1.reg;
}

static inline bool hri_dsu_get_PID2_JEPU_bit(const void *const hw)
{
	return (((Dsu *)hw)->PID2.reg & DSU_PID2_JEPU_Msk) >> DSU_PID2_JEPU_Pos;
}

static inline hri_dsu_pid2_reg_t hri_dsu_get_PID2_JEPIDCH_bf(const void *const hw, hri_dsu_pid2_reg_t mask)
{
	return (((Dsu *)hw)->PID2.reg & DSU_PID2_JEPIDCH(mask)) >> DSU_PID2_JEPIDCH_Pos;
}

static inline hri_dsu_pid2_reg_t hri_dsu_read_PID2_JEPIDCH_bf(const void *const hw)
{
	return (((Dsu *)hw)->PID2.reg & DSU_PID2_JEPIDCH_Msk) >> DSU_PID2_JEPIDCH_Pos;
}

static inline hri_dsu_pid2_reg_t hri_dsu_get_PID2_REVISION_bf(const void *const hw, hri_dsu_pid2_reg_t mask)
{
	return (((Dsu *)hw)->PID2.reg & DSU_PID2_REVISION(mask)) >> DSU_PID2_REVISION_Pos;
}

static inline hri_dsu_pid2_reg_t hri_dsu_read_PID2_REVISION_bf(const void *const hw)
{
	return (((Dsu *)hw)->PID2.reg & DSU_PID2_REVISION_Msk) >> DSU_PID2_REVISION_Pos;
}

static inline hri_dsu_pid2_reg_t hri_dsu_get_PID2_reg(const void *const hw, hri_dsu_pid2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->PID2.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_pid2_reg_t hri_dsu_read_PID2_reg(const void *const hw)
{
	return ((Dsu *)hw)->PID2.reg;
}

static inline hri_dsu_pid3_reg_t hri_dsu_get_PID3_CUSMOD_bf(const void *const hw, hri_dsu_pid3_reg_t mask)
{
	return (((Dsu *)hw)->PID3.reg & DSU_PID3_CUSMOD(mask)) >> DSU_PID3_CUSMOD_Pos;
}

static inline hri_dsu_pid3_reg_t hri_dsu_read_PID3_CUSMOD_bf(const void *const hw)
{
	return (((Dsu *)hw)->PID3.reg & DSU_PID3_CUSMOD_Msk) >> DSU_PID3_CUSMOD_Pos;
}

static inline hri_dsu_pid3_reg_t hri_dsu_get_PID3_REVAND_bf(const void *const hw, hri_dsu_pid3_reg_t mask)
{
	return (((Dsu *)hw)->PID3.reg & DSU_PID3_REVAND(mask)) >> DSU_PID3_REVAND_Pos;
}

static inline hri_dsu_pid3_reg_t hri_dsu_read_PID3_REVAND_bf(const void *const hw)
{
	return (((Dsu *)hw)->PID3.reg & DSU_PID3_REVAND_Msk) >> DSU_PID3_REVAND_Pos;
}

static inline hri_dsu_pid3_reg_t hri_dsu_get_PID3_reg(const void *const hw, hri_dsu_pid3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->PID3.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_pid3_reg_t hri_dsu_read_PID3_reg(const void *const hw)
{
	return ((Dsu *)hw)->PID3.reg;
}

static inline hri_dsu_cid0_reg_t hri_dsu_get_CID0_PREAMBLEB0_bf(const void *const hw, hri_dsu_cid0_reg_t mask)
{
	return (((Dsu *)hw)->CID0.reg & DSU_CID0_PREAMBLEB0(mask)) >> DSU_CID0_PREAMBLEB0_Pos;
}

static inline hri_dsu_cid0_reg_t hri_dsu_read_CID0_PREAMBLEB0_bf(const void *const hw)
{
	return (((Dsu *)hw)->CID0.reg & DSU_CID0_PREAMBLEB0_Msk) >> DSU_CID0_PREAMBLEB0_Pos;
}

static inline hri_dsu_cid0_reg_t hri_dsu_get_CID0_reg(const void *const hw, hri_dsu_cid0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->CID0.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_cid0_reg_t hri_dsu_read_CID0_reg(const void *const hw)
{
	return ((Dsu *)hw)->CID0.reg;
}

static inline hri_dsu_cid1_reg_t hri_dsu_get_CID1_PREAMBLE_bf(const void *const hw, hri_dsu_cid1_reg_t mask)
{
	return (((Dsu *)hw)->CID1.reg & DSU_CID1_PREAMBLE(mask)) >> DSU_CID1_PREAMBLE_Pos;
}

static inline hri_dsu_cid1_reg_t hri_dsu_read_CID1_PREAMBLE_bf(const void *const hw)
{
	return (((Dsu *)hw)->CID1.reg & DSU_CID1_PREAMBLE_Msk) >> DSU_CID1_PREAMBLE_Pos;
}

static inline hri_dsu_cid1_reg_t hri_dsu_get_CID1_CCLASS_bf(const void *const hw, hri_dsu_cid1_reg_t mask)
{
	return (((Dsu *)hw)->CID1.reg & DSU_CID1_CCLASS(mask)) >> DSU_CID1_CCLASS_Pos;
}

static inline hri_dsu_cid1_reg_t hri_dsu_read_CID1_CCLASS_bf(const void *const hw)
{
	return (((Dsu *)hw)->CID1.reg & DSU_CID1_CCLASS_Msk) >> DSU_CID1_CCLASS_Pos;
}

static inline hri_dsu_cid1_reg_t hri_dsu_get_CID1_reg(const void *const hw, hri_dsu_cid1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->CID1.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_cid1_reg_t hri_dsu_read_CID1_reg(const void *const hw)
{
	return ((Dsu *)hw)->CID1.reg;
}

static inline hri_dsu_cid2_reg_t hri_dsu_get_CID2_PREAMBLEB2_bf(const void *const hw, hri_dsu_cid2_reg_t mask)
{
	return (((Dsu *)hw)->CID2.reg & DSU_CID2_PREAMBLEB2(mask)) >> DSU_CID2_PREAMBLEB2_Pos;
}

static inline hri_dsu_cid2_reg_t hri_dsu_read_CID2_PREAMBLEB2_bf(const void *const hw)
{
	return (((Dsu *)hw)->CID2.reg & DSU_CID2_PREAMBLEB2_Msk) >> DSU_CID2_PREAMBLEB2_Pos;
}

static inline hri_dsu_cid2_reg_t hri_dsu_get_CID2_reg(const void *const hw, hri_dsu_cid2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->CID2.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_cid2_reg_t hri_dsu_read_CID2_reg(const void *const hw)
{
	return ((Dsu *)hw)->CID2.reg;
}

static inline hri_dsu_cid3_reg_t hri_dsu_get_CID3_PREAMBLEB3_bf(const void *const hw, hri_dsu_cid3_reg_t mask)
{
	return (((Dsu *)hw)->CID3.reg & DSU_CID3_PREAMBLEB3(mask)) >> DSU_CID3_PREAMBLEB3_Pos;
}

static inline hri_dsu_cid3_reg_t hri_dsu_read_CID3_PREAMBLEB3_bf(const void *const hw)
{
	return (((Dsu *)hw)->CID3.reg & DSU_CID3_PREAMBLEB3_Msk) >> DSU_CID3_PREAMBLEB3_Pos;
}

static inline hri_dsu_cid3_reg_t hri_dsu_get_CID3_reg(const void *const hw, hri_dsu_cid3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->CID3.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_dsu_cid3_reg_t hri_dsu_read_CID3_reg(const void *const hw)
{
	return ((Dsu *)hw)->CID3.reg;
}

static inline void hri_dsu_set_ADDR_AMOD_bf(const void *const hw, hri_dsu_addr_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg |= DSU_ADDR_AMOD(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_addr_reg_t hri_dsu_get_ADDR_AMOD_bf(const void *const hw, hri_dsu_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->ADDR.reg;
	tmp = (tmp & DSU_ADDR_AMOD(mask)) >> DSU_ADDR_AMOD_Pos;
	return tmp;
}

static inline void hri_dsu_write_ADDR_AMOD_bf(const void *const hw, hri_dsu_addr_reg_t data)
{
	uint32_t tmp;
	DSU_CRITICAL_SECTION_ENTER();
	tmp = ((Dsu *)hw)->ADDR.reg;
	tmp &= ~DSU_ADDR_AMOD_Msk;
	tmp |= DSU_ADDR_AMOD(data);
	((Dsu *)hw)->ADDR.reg = tmp;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_ADDR_AMOD_bf(const void *const hw, hri_dsu_addr_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg &= ~DSU_ADDR_AMOD(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_ADDR_AMOD_bf(const void *const hw, hri_dsu_addr_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg ^= DSU_ADDR_AMOD(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_addr_reg_t hri_dsu_read_ADDR_AMOD_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->ADDR.reg;
	tmp = (tmp & DSU_ADDR_AMOD_Msk) >> DSU_ADDR_AMOD_Pos;
	return tmp;
}

static inline void hri_dsu_set_ADDR_ADDR_bf(const void *const hw, hri_dsu_addr_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg |= DSU_ADDR_ADDR(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_addr_reg_t hri_dsu_get_ADDR_ADDR_bf(const void *const hw, hri_dsu_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->ADDR.reg;
	tmp = (tmp & DSU_ADDR_ADDR(mask)) >> DSU_ADDR_ADDR_Pos;
	return tmp;
}

static inline void hri_dsu_write_ADDR_ADDR_bf(const void *const hw, hri_dsu_addr_reg_t data)
{
	uint32_t tmp;
	DSU_CRITICAL_SECTION_ENTER();
	tmp = ((Dsu *)hw)->ADDR.reg;
	tmp &= ~DSU_ADDR_ADDR_Msk;
	tmp |= DSU_ADDR_ADDR(data);
	((Dsu *)hw)->ADDR.reg = tmp;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_ADDR_ADDR_bf(const void *const hw, hri_dsu_addr_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg &= ~DSU_ADDR_ADDR(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_ADDR_ADDR_bf(const void *const hw, hri_dsu_addr_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg ^= DSU_ADDR_ADDR(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_addr_reg_t hri_dsu_read_ADDR_ADDR_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->ADDR.reg;
	tmp = (tmp & DSU_ADDR_ADDR_Msk) >> DSU_ADDR_ADDR_Pos;
	return tmp;
}

static inline void hri_dsu_set_ADDR_reg(const void *const hw, hri_dsu_addr_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg |= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_addr_reg_t hri_dsu_get_ADDR_reg(const void *const hw, hri_dsu_addr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->ADDR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_dsu_write_ADDR_reg(const void *const hw, hri_dsu_addr_reg_t data)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg = data;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_ADDR_reg(const void *const hw, hri_dsu_addr_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg &= ~mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_ADDR_reg(const void *const hw, hri_dsu_addr_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->ADDR.reg ^= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_addr_reg_t hri_dsu_read_ADDR_reg(const void *const hw)
{
	return ((Dsu *)hw)->ADDR.reg;
}

static inline void hri_dsu_set_LENGTH_LENGTH_bf(const void *const hw, hri_dsu_length_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->LENGTH.reg |= DSU_LENGTH_LENGTH(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_length_reg_t hri_dsu_get_LENGTH_LENGTH_bf(const void *const hw, hri_dsu_length_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->LENGTH.reg;
	tmp = (tmp & DSU_LENGTH_LENGTH(mask)) >> DSU_LENGTH_LENGTH_Pos;
	return tmp;
}

static inline void hri_dsu_write_LENGTH_LENGTH_bf(const void *const hw, hri_dsu_length_reg_t data)
{
	uint32_t tmp;
	DSU_CRITICAL_SECTION_ENTER();
	tmp = ((Dsu *)hw)->LENGTH.reg;
	tmp &= ~DSU_LENGTH_LENGTH_Msk;
	tmp |= DSU_LENGTH_LENGTH(data);
	((Dsu *)hw)->LENGTH.reg = tmp;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_LENGTH_LENGTH_bf(const void *const hw, hri_dsu_length_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->LENGTH.reg &= ~DSU_LENGTH_LENGTH(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_LENGTH_LENGTH_bf(const void *const hw, hri_dsu_length_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->LENGTH.reg ^= DSU_LENGTH_LENGTH(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_length_reg_t hri_dsu_read_LENGTH_LENGTH_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->LENGTH.reg;
	tmp = (tmp & DSU_LENGTH_LENGTH_Msk) >> DSU_LENGTH_LENGTH_Pos;
	return tmp;
}

static inline void hri_dsu_set_LENGTH_reg(const void *const hw, hri_dsu_length_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->LENGTH.reg |= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_length_reg_t hri_dsu_get_LENGTH_reg(const void *const hw, hri_dsu_length_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->LENGTH.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_dsu_write_LENGTH_reg(const void *const hw, hri_dsu_length_reg_t data)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->LENGTH.reg = data;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_LENGTH_reg(const void *const hw, hri_dsu_length_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->LENGTH.reg &= ~mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_LENGTH_reg(const void *const hw, hri_dsu_length_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->LENGTH.reg ^= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_length_reg_t hri_dsu_read_LENGTH_reg(const void *const hw)
{
	return ((Dsu *)hw)->LENGTH.reg;
}

static inline void hri_dsu_set_DATA_DATA_bf(const void *const hw, hri_dsu_data_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DATA.reg |= DSU_DATA_DATA(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_data_reg_t hri_dsu_get_DATA_DATA_bf(const void *const hw, hri_dsu_data_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DATA.reg;
	tmp = (tmp & DSU_DATA_DATA(mask)) >> DSU_DATA_DATA_Pos;
	return tmp;
}

static inline void hri_dsu_write_DATA_DATA_bf(const void *const hw, hri_dsu_data_reg_t data)
{
	uint32_t tmp;
	DSU_CRITICAL_SECTION_ENTER();
	tmp = ((Dsu *)hw)->DATA.reg;
	tmp &= ~DSU_DATA_DATA_Msk;
	tmp |= DSU_DATA_DATA(data);
	((Dsu *)hw)->DATA.reg = tmp;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_DATA_DATA_bf(const void *const hw, hri_dsu_data_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DATA.reg &= ~DSU_DATA_DATA(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_DATA_DATA_bf(const void *const hw, hri_dsu_data_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DATA.reg ^= DSU_DATA_DATA(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_data_reg_t hri_dsu_read_DATA_DATA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DATA.reg;
	tmp = (tmp & DSU_DATA_DATA_Msk) >> DSU_DATA_DATA_Pos;
	return tmp;
}

static inline void hri_dsu_set_DATA_reg(const void *const hw, hri_dsu_data_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DATA.reg |= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_data_reg_t hri_dsu_get_DATA_reg(const void *const hw, hri_dsu_data_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DATA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_dsu_write_DATA_reg(const void *const hw, hri_dsu_data_reg_t data)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DATA.reg = data;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_DATA_reg(const void *const hw, hri_dsu_data_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DATA.reg &= ~mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_DATA_reg(const void *const hw, hri_dsu_data_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DATA.reg ^= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_data_reg_t hri_dsu_read_DATA_reg(const void *const hw)
{
	return ((Dsu *)hw)->DATA.reg;
}

static inline void hri_dsu_set_DCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCC[index].reg |= DSU_DCC_DATA(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_dcc_reg_t hri_dsu_get_DCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DCC[index].reg;
	tmp = (tmp & DSU_DCC_DATA(mask)) >> DSU_DCC_DATA_Pos;
	return tmp;
}

static inline void hri_dsu_write_DCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t data)
{
	uint32_t tmp;
	DSU_CRITICAL_SECTION_ENTER();
	tmp = ((Dsu *)hw)->DCC[index].reg;
	tmp &= ~DSU_DCC_DATA_Msk;
	tmp |= DSU_DCC_DATA(data);
	((Dsu *)hw)->DCC[index].reg = tmp;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_DCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCC[index].reg &= ~DSU_DCC_DATA(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_DCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCC[index].reg ^= DSU_DCC_DATA(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_dcc_reg_t hri_dsu_read_DCC_DATA_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DCC[index].reg;
	tmp = (tmp & DSU_DCC_DATA_Msk) >> DSU_DCC_DATA_Pos;
	return tmp;
}

static inline void hri_dsu_set_DCC_reg(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCC[index].reg |= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_dcc_reg_t hri_dsu_get_DCC_reg(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DCC[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_dsu_write_DCC_reg(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t data)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCC[index].reg = data;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_DCC_reg(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCC[index].reg &= ~mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_DCC_reg(const void *const hw, uint8_t index, hri_dsu_dcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCC[index].reg ^= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_dcc_reg_t hri_dsu_read_DCC_reg(const void *const hw, uint8_t index)
{
	return ((Dsu *)hw)->DCC[index].reg;
}

static inline void hri_dsu_set_CFG_LQOS_bf(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg |= DSU_CFG_LQOS(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_cfg_reg_t hri_dsu_get_CFG_LQOS_bf(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->CFG.reg;
	tmp = (tmp & DSU_CFG_LQOS(mask)) >> DSU_CFG_LQOS_Pos;
	return tmp;
}

static inline void hri_dsu_write_CFG_LQOS_bf(const void *const hw, hri_dsu_cfg_reg_t data)
{
	uint32_t tmp;
	DSU_CRITICAL_SECTION_ENTER();
	tmp = ((Dsu *)hw)->CFG.reg;
	tmp &= ~DSU_CFG_LQOS_Msk;
	tmp |= DSU_CFG_LQOS(data);
	((Dsu *)hw)->CFG.reg = tmp;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_CFG_LQOS_bf(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg &= ~DSU_CFG_LQOS(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_CFG_LQOS_bf(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg ^= DSU_CFG_LQOS(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_cfg_reg_t hri_dsu_read_CFG_LQOS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->CFG.reg;
	tmp = (tmp & DSU_CFG_LQOS_Msk) >> DSU_CFG_LQOS_Pos;
	return tmp;
}

static inline void hri_dsu_set_CFG_DCCDMALEVEL_bf(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg |= DSU_CFG_DCCDMALEVEL(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_cfg_reg_t hri_dsu_get_CFG_DCCDMALEVEL_bf(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->CFG.reg;
	tmp = (tmp & DSU_CFG_DCCDMALEVEL(mask)) >> DSU_CFG_DCCDMALEVEL_Pos;
	return tmp;
}

static inline void hri_dsu_write_CFG_DCCDMALEVEL_bf(const void *const hw, hri_dsu_cfg_reg_t data)
{
	uint32_t tmp;
	DSU_CRITICAL_SECTION_ENTER();
	tmp = ((Dsu *)hw)->CFG.reg;
	tmp &= ~DSU_CFG_DCCDMALEVEL_Msk;
	tmp |= DSU_CFG_DCCDMALEVEL(data);
	((Dsu *)hw)->CFG.reg = tmp;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_CFG_DCCDMALEVEL_bf(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg &= ~DSU_CFG_DCCDMALEVEL(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_CFG_DCCDMALEVEL_bf(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg ^= DSU_CFG_DCCDMALEVEL(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_cfg_reg_t hri_dsu_read_CFG_DCCDMALEVEL_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->CFG.reg;
	tmp = (tmp & DSU_CFG_DCCDMALEVEL_Msk) >> DSU_CFG_DCCDMALEVEL_Pos;
	return tmp;
}

static inline void hri_dsu_set_CFG_reg(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg |= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_cfg_reg_t hri_dsu_get_CFG_reg(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->CFG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_dsu_write_CFG_reg(const void *const hw, hri_dsu_cfg_reg_t data)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg = data;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_CFG_reg(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg &= ~mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_CFG_reg(const void *const hw, hri_dsu_cfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CFG.reg ^= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_cfg_reg_t hri_dsu_read_CFG_reg(const void *const hw)
{
	return ((Dsu *)hw)->CFG.reg;
}

static inline void hri_dsu_set_BCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->BCC[index].reg |= DSU_BCC_DATA(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_bcc_reg_t hri_dsu_get_BCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->BCC[index].reg;
	tmp = (tmp & DSU_BCC_DATA(mask)) >> DSU_BCC_DATA_Pos;
	return tmp;
}

static inline void hri_dsu_write_BCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t data)
{
	uint32_t tmp;
	DSU_CRITICAL_SECTION_ENTER();
	tmp = ((Dsu *)hw)->BCC[index].reg;
	tmp &= ~DSU_BCC_DATA_Msk;
	tmp |= DSU_BCC_DATA(data);
	((Dsu *)hw)->BCC[index].reg = tmp;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_BCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->BCC[index].reg &= ~DSU_BCC_DATA(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_BCC_DATA_bf(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->BCC[index].reg ^= DSU_BCC_DATA(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_bcc_reg_t hri_dsu_read_BCC_DATA_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->BCC[index].reg;
	tmp = (tmp & DSU_BCC_DATA_Msk) >> DSU_BCC_DATA_Pos;
	return tmp;
}

static inline void hri_dsu_set_BCC_reg(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->BCC[index].reg |= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_bcc_reg_t hri_dsu_get_BCC_reg(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->BCC[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_dsu_write_BCC_reg(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t data)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->BCC[index].reg = data;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_BCC_reg(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->BCC[index].reg &= ~mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_BCC_reg(const void *const hw, uint8_t index, hri_dsu_bcc_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->BCC[index].reg ^= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_bcc_reg_t hri_dsu_read_BCC_reg(const void *const hw, uint8_t index)
{
	return ((Dsu *)hw)->BCC[index].reg;
}

static inline void hri_dsu_set_DCFG_DCFG_bf(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCFG[index].reg |= DSU_DCFG_DCFG(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_dcfg_reg_t hri_dsu_get_DCFG_DCFG_bf(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DCFG[index].reg;
	tmp = (tmp & DSU_DCFG_DCFG(mask)) >> DSU_DCFG_DCFG_Pos;
	return tmp;
}

static inline void hri_dsu_write_DCFG_DCFG_bf(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t data)
{
	uint32_t tmp;
	DSU_CRITICAL_SECTION_ENTER();
	tmp = ((Dsu *)hw)->DCFG[index].reg;
	tmp &= ~DSU_DCFG_DCFG_Msk;
	tmp |= DSU_DCFG_DCFG(data);
	((Dsu *)hw)->DCFG[index].reg = tmp;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_DCFG_DCFG_bf(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCFG[index].reg &= ~DSU_DCFG_DCFG(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_DCFG_DCFG_bf(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCFG[index].reg ^= DSU_DCFG_DCFG(mask);
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_dcfg_reg_t hri_dsu_read_DCFG_DCFG_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DCFG[index].reg;
	tmp = (tmp & DSU_DCFG_DCFG_Msk) >> DSU_DCFG_DCFG_Pos;
	return tmp;
}

static inline void hri_dsu_set_DCFG_reg(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCFG[index].reg |= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_dcfg_reg_t hri_dsu_get_DCFG_reg(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Dsu *)hw)->DCFG[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_dsu_write_DCFG_reg(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t data)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCFG[index].reg = data;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_clear_DCFG_reg(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCFG[index].reg &= ~mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline void hri_dsu_toggle_DCFG_reg(const void *const hw, uint8_t index, hri_dsu_dcfg_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->DCFG[index].reg ^= mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_dcfg_reg_t hri_dsu_read_DCFG_reg(const void *const hw, uint8_t index)
{
	return ((Dsu *)hw)->DCFG[index].reg;
}

static inline bool hri_dsu_get_STATUSA_DONE_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSA.reg & DSU_STATUSA_DONE_Msk) >> DSU_STATUSA_DONE_Pos;
}

static inline void hri_dsu_clear_STATUSA_DONE_bit(const void *const hw)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->STATUSA.reg = DSU_STATUSA_DONE_Msk;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dsu_get_STATUSA_CRSTEXT_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSA.reg & DSU_STATUSA_CRSTEXT_Msk) >> DSU_STATUSA_CRSTEXT_Pos;
}

static inline void hri_dsu_clear_STATUSA_CRSTEXT_bit(const void *const hw)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->STATUSA.reg = DSU_STATUSA_CRSTEXT_Msk;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dsu_get_STATUSA_BERR_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSA.reg & DSU_STATUSA_BERR_Msk) >> DSU_STATUSA_BERR_Pos;
}

static inline void hri_dsu_clear_STATUSA_BERR_bit(const void *const hw)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->STATUSA.reg = DSU_STATUSA_BERR_Msk;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dsu_get_STATUSA_FAIL_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSA.reg & DSU_STATUSA_FAIL_Msk) >> DSU_STATUSA_FAIL_Pos;
}

static inline void hri_dsu_clear_STATUSA_FAIL_bit(const void *const hw)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->STATUSA.reg = DSU_STATUSA_FAIL_Msk;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dsu_get_STATUSA_PERR_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSA.reg & DSU_STATUSA_PERR_Msk) >> DSU_STATUSA_PERR_Pos;
}

static inline void hri_dsu_clear_STATUSA_PERR_bit(const void *const hw)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->STATUSA.reg = DSU_STATUSA_PERR_Msk;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_dsu_get_STATUSA_BREXT_bit(const void *const hw)
{
	return (((Dsu *)hw)->STATUSA.reg & DSU_STATUSA_BREXT_Msk) >> DSU_STATUSA_BREXT_Pos;
}

static inline void hri_dsu_clear_STATUSA_BREXT_bit(const void *const hw)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->STATUSA.reg = DSU_STATUSA_BREXT_Msk;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_statusa_reg_t hri_dsu_get_STATUSA_reg(const void *const hw, hri_dsu_statusa_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Dsu *)hw)->STATUSA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_dsu_clear_STATUSA_reg(const void *const hw, hri_dsu_statusa_reg_t mask)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->STATUSA.reg = mask;
	DSU_CRITICAL_SECTION_LEAVE();
}

static inline hri_dsu_statusa_reg_t hri_dsu_read_STATUSA_reg(const void *const hw)
{
	return ((Dsu *)hw)->STATUSA.reg;
}

static inline void hri_dsu_write_CTRL_reg(const void *const hw, hri_dsu_ctrl_reg_t data)
{
	DSU_CRITICAL_SECTION_ENTER();
	((Dsu *)hw)->CTRL.reg = data;
	DSU_CRITICAL_SECTION_LEAVE();
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_DSU_L10_H_INCLUDED */
#endif /* _SAML10_DSU_COMPONENT_ */
