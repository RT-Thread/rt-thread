/**
 * \file
 *
 * \brief SAM MTB
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

#ifdef _SAMC21_MTB_COMPONENT_
#ifndef _HRI_MTB_C21_H_INCLUDED_
#define _HRI_MTB_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_MTB_CRITICAL_SECTIONS)
#define MTB_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define MTB_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define MTB_CRITICAL_SECTION_ENTER()
#define MTB_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_mtb_authstatus_reg_t;
typedef uint32_t hri_mtb_base_reg_t;
typedef uint32_t hri_mtb_cid0_reg_t;
typedef uint32_t hri_mtb_cid1_reg_t;
typedef uint32_t hri_mtb_cid2_reg_t;
typedef uint32_t hri_mtb_cid3_reg_t;
typedef uint32_t hri_mtb_claimset_reg_t;
typedef uint32_t hri_mtb_devarch_reg_t;
typedef uint32_t hri_mtb_devid_reg_t;
typedef uint32_t hri_mtb_devtype_reg_t;
typedef uint32_t hri_mtb_flow_reg_t;
typedef uint32_t hri_mtb_itctrl_reg_t;
typedef uint32_t hri_mtb_lockaccess_reg_t;
typedef uint32_t hri_mtb_lockstatus_reg_t;
typedef uint32_t hri_mtb_master_reg_t;
typedef uint32_t hri_mtb_pid0_reg_t;
typedef uint32_t hri_mtb_pid1_reg_t;
typedef uint32_t hri_mtb_pid2_reg_t;
typedef uint32_t hri_mtb_pid3_reg_t;
typedef uint32_t hri_mtb_pid4_reg_t;
typedef uint32_t hri_mtb_pid5_reg_t;
typedef uint32_t hri_mtb_pid6_reg_t;
typedef uint32_t hri_mtb_pid7_reg_t;
typedef uint32_t hri_mtb_position_reg_t;

static inline void hri_mtb_set_CLAIM_reg(const void *const hw, hri_mtb_claimset_reg_t mask)
{
	((Mtb *)hw)->CLAIMSET.reg = mask;
}

static inline hri_mtb_claimset_reg_t hri_mtb_get_CLAIM_reg(const void *const hw, hri_mtb_claimset_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->CLAIMSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_claimset_reg_t hri_mtb_read_CLAIM_reg(const void *const hw)
{
	return ((Mtb *)hw)->CLAIMSET.reg;
}

static inline void hri_mtb_write_CLAIM_reg(const void *const hw, hri_mtb_claimset_reg_t data)
{
	((Mtb *)hw)->CLAIMSET.reg = data;
	((Mtb *)hw)->CLAIMCLR.reg = ~data;
}

static inline void hri_mtb_clear_CLAIM_reg(const void *const hw, hri_mtb_claimset_reg_t mask)
{
	((Mtb *)hw)->CLAIMCLR.reg = mask;
}

static inline hri_mtb_base_reg_t hri_mtb_get_BASE_reg(const void *const hw, hri_mtb_base_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->BASE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_base_reg_t hri_mtb_read_BASE_reg(const void *const hw)
{
	return ((Mtb *)hw)->BASE.reg;
}

static inline hri_mtb_lockstatus_reg_t hri_mtb_get_LOCKSTATUS_reg(const void *const hw, hri_mtb_lockstatus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->LOCKSTATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_lockstatus_reg_t hri_mtb_read_LOCKSTATUS_reg(const void *const hw)
{
	return ((Mtb *)hw)->LOCKSTATUS.reg;
}

static inline hri_mtb_authstatus_reg_t hri_mtb_get_AUTHSTATUS_reg(const void *const hw, hri_mtb_authstatus_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->AUTHSTATUS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_authstatus_reg_t hri_mtb_read_AUTHSTATUS_reg(const void *const hw)
{
	return ((Mtb *)hw)->AUTHSTATUS.reg;
}

static inline hri_mtb_devarch_reg_t hri_mtb_get_DEVARCH_reg(const void *const hw, hri_mtb_devarch_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->DEVARCH.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_devarch_reg_t hri_mtb_read_DEVARCH_reg(const void *const hw)
{
	return ((Mtb *)hw)->DEVARCH.reg;
}

static inline hri_mtb_devid_reg_t hri_mtb_get_DEVID_reg(const void *const hw, hri_mtb_devid_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->DEVID.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_devid_reg_t hri_mtb_read_DEVID_reg(const void *const hw)
{
	return ((Mtb *)hw)->DEVID.reg;
}

static inline hri_mtb_devtype_reg_t hri_mtb_get_DEVTYPE_reg(const void *const hw, hri_mtb_devtype_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->DEVTYPE.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_devtype_reg_t hri_mtb_read_DEVTYPE_reg(const void *const hw)
{
	return ((Mtb *)hw)->DEVTYPE.reg;
}

static inline hri_mtb_pid4_reg_t hri_mtb_get_PID4_reg(const void *const hw, hri_mtb_pid4_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->PID4.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_pid4_reg_t hri_mtb_read_PID4_reg(const void *const hw)
{
	return ((Mtb *)hw)->PID4.reg;
}

static inline hri_mtb_pid5_reg_t hri_mtb_get_PID5_reg(const void *const hw, hri_mtb_pid5_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->PID5.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_pid5_reg_t hri_mtb_read_PID5_reg(const void *const hw)
{
	return ((Mtb *)hw)->PID5.reg;
}

static inline hri_mtb_pid6_reg_t hri_mtb_get_PID6_reg(const void *const hw, hri_mtb_pid6_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->PID6.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_pid6_reg_t hri_mtb_read_PID6_reg(const void *const hw)
{
	return ((Mtb *)hw)->PID6.reg;
}

static inline hri_mtb_pid7_reg_t hri_mtb_get_PID7_reg(const void *const hw, hri_mtb_pid7_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->PID7.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_pid7_reg_t hri_mtb_read_PID7_reg(const void *const hw)
{
	return ((Mtb *)hw)->PID7.reg;
}

static inline hri_mtb_pid0_reg_t hri_mtb_get_PID0_reg(const void *const hw, hri_mtb_pid0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->PID0.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_pid0_reg_t hri_mtb_read_PID0_reg(const void *const hw)
{
	return ((Mtb *)hw)->PID0.reg;
}

static inline hri_mtb_pid1_reg_t hri_mtb_get_PID1_reg(const void *const hw, hri_mtb_pid1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->PID1.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_pid1_reg_t hri_mtb_read_PID1_reg(const void *const hw)
{
	return ((Mtb *)hw)->PID1.reg;
}

static inline hri_mtb_pid2_reg_t hri_mtb_get_PID2_reg(const void *const hw, hri_mtb_pid2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->PID2.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_pid2_reg_t hri_mtb_read_PID2_reg(const void *const hw)
{
	return ((Mtb *)hw)->PID2.reg;
}

static inline hri_mtb_pid3_reg_t hri_mtb_get_PID3_reg(const void *const hw, hri_mtb_pid3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->PID3.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_pid3_reg_t hri_mtb_read_PID3_reg(const void *const hw)
{
	return ((Mtb *)hw)->PID3.reg;
}

static inline hri_mtb_cid0_reg_t hri_mtb_get_CID0_reg(const void *const hw, hri_mtb_cid0_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->CID0.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_cid0_reg_t hri_mtb_read_CID0_reg(const void *const hw)
{
	return ((Mtb *)hw)->CID0.reg;
}

static inline hri_mtb_cid1_reg_t hri_mtb_get_CID1_reg(const void *const hw, hri_mtb_cid1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->CID1.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_cid1_reg_t hri_mtb_read_CID1_reg(const void *const hw)
{
	return ((Mtb *)hw)->CID1.reg;
}

static inline hri_mtb_cid2_reg_t hri_mtb_get_CID2_reg(const void *const hw, hri_mtb_cid2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->CID2.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_cid2_reg_t hri_mtb_read_CID2_reg(const void *const hw)
{
	return ((Mtb *)hw)->CID2.reg;
}

static inline hri_mtb_cid3_reg_t hri_mtb_get_CID3_reg(const void *const hw, hri_mtb_cid3_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->CID3.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_mtb_cid3_reg_t hri_mtb_read_CID3_reg(const void *const hw)
{
	return ((Mtb *)hw)->CID3.reg;
}

static inline void hri_mtb_set_POSITION_reg(const void *const hw, hri_mtb_position_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->POSITION.reg |= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_position_reg_t hri_mtb_get_POSITION_reg(const void *const hw, hri_mtb_position_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->POSITION.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mtb_write_POSITION_reg(const void *const hw, hri_mtb_position_reg_t data)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->POSITION.reg = data;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_clear_POSITION_reg(const void *const hw, hri_mtb_position_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->POSITION.reg &= ~mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_toggle_POSITION_reg(const void *const hw, hri_mtb_position_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->POSITION.reg ^= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_position_reg_t hri_mtb_read_POSITION_reg(const void *const hw)
{
	return ((Mtb *)hw)->POSITION.reg;
}

static inline void hri_mtb_set_MASTER_reg(const void *const hw, hri_mtb_master_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->MASTER.reg |= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_master_reg_t hri_mtb_get_MASTER_reg(const void *const hw, hri_mtb_master_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->MASTER.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mtb_write_MASTER_reg(const void *const hw, hri_mtb_master_reg_t data)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->MASTER.reg = data;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_clear_MASTER_reg(const void *const hw, hri_mtb_master_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->MASTER.reg &= ~mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_toggle_MASTER_reg(const void *const hw, hri_mtb_master_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->MASTER.reg ^= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_master_reg_t hri_mtb_read_MASTER_reg(const void *const hw)
{
	return ((Mtb *)hw)->MASTER.reg;
}

static inline void hri_mtb_set_FLOW_reg(const void *const hw, hri_mtb_flow_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->FLOW.reg |= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_flow_reg_t hri_mtb_get_FLOW_reg(const void *const hw, hri_mtb_flow_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->FLOW.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mtb_write_FLOW_reg(const void *const hw, hri_mtb_flow_reg_t data)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->FLOW.reg = data;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_clear_FLOW_reg(const void *const hw, hri_mtb_flow_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->FLOW.reg &= ~mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_toggle_FLOW_reg(const void *const hw, hri_mtb_flow_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->FLOW.reg ^= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_flow_reg_t hri_mtb_read_FLOW_reg(const void *const hw)
{
	return ((Mtb *)hw)->FLOW.reg;
}

static inline void hri_mtb_set_ITCTRL_reg(const void *const hw, hri_mtb_itctrl_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->ITCTRL.reg |= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_itctrl_reg_t hri_mtb_get_ITCTRL_reg(const void *const hw, hri_mtb_itctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->ITCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mtb_write_ITCTRL_reg(const void *const hw, hri_mtb_itctrl_reg_t data)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->ITCTRL.reg = data;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_clear_ITCTRL_reg(const void *const hw, hri_mtb_itctrl_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->ITCTRL.reg &= ~mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_toggle_ITCTRL_reg(const void *const hw, hri_mtb_itctrl_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->ITCTRL.reg ^= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_itctrl_reg_t hri_mtb_read_ITCTRL_reg(const void *const hw)
{
	return ((Mtb *)hw)->ITCTRL.reg;
}

static inline void hri_mtb_set_LOCKACCESS_reg(const void *const hw, hri_mtb_lockaccess_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->LOCKACCESS.reg |= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_lockaccess_reg_t hri_mtb_get_LOCKACCESS_reg(const void *const hw, hri_mtb_lockaccess_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mtb *)hw)->LOCKACCESS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_mtb_write_LOCKACCESS_reg(const void *const hw, hri_mtb_lockaccess_reg_t data)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->LOCKACCESS.reg = data;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_clear_LOCKACCESS_reg(const void *const hw, hri_mtb_lockaccess_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->LOCKACCESS.reg &= ~mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mtb_toggle_LOCKACCESS_reg(const void *const hw, hri_mtb_lockaccess_reg_t mask)
{
	MTB_CRITICAL_SECTION_ENTER();
	((Mtb *)hw)->LOCKACCESS.reg ^= mask;
	MTB_CRITICAL_SECTION_LEAVE();
}

static inline hri_mtb_lockaccess_reg_t hri_mtb_read_LOCKACCESS_reg(const void *const hw)
{
	return ((Mtb *)hw)->LOCKACCESS.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_MTB_C21_H_INCLUDED */
#endif /* _SAMC21_MTB_COMPONENT_ */
