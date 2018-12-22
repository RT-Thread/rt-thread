/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//! @addtogroup diag_pcie
//! @{

/*!
 * @file pcie_common.h
 * @brief Common macro and definitions.
 */

#ifndef __PCIE_COMMON_H__
#define __PCIE_COMMON_H__

#include "sdk.h"

#define SZ_1K	0x400
#define SZ_2K	0x800
#define SZ_4K	0x1000
#define SZ_8K	0x2000
#define SZ_16K	0x4000
#define SZ_32K	0x8000
#define SZ_64K	0x10000

#define PCIE_DBI_BASE_ADDR 		0x01FFC000
#define PCIE_DBI_ADDR_END		0x01FFFFFF
#define PCIE_ARB_BASE_ADDR		0x01000000
#define PCIE_ARB_ADDR_END		0x01FFBFFF

//! @brief Structure for GPR field
typedef struct {
    uint32_t addr;              // field register address 
    uint32_t mask;              // field mask
    uint32_t offset;            // field offset
} pcie_iomux_gpr_field_t, *pcie_iomux_gpr_field_p;

//! @brief GPR fields related with PCIE
typedef enum {
    apps_pm_xmt_pme,
    device_type,
    diag_status_bus_select,
    sys_int,
    apps_pm_xmt_turnoff,
    app_ltssm_enable,
    app_init_rst,
    ref_ssp_en,
    diag_ctrl_bus,
    app_req_entr_l1,
    app_ready_entr_l23,
    app_req_exit_l1,
    app_clk_req_n,
    cfg_l1_clk_removal_en,
    phy_test_powerdown,
    los_level,
    tx_deemph_gen1,
    tx_deemph_gen2_3p5db,
    tx_deemph_gen2_6db,
    tx_swing_full,
    tx_swing_low
} pcie_iomux_gpr_field_type_e;

//! @brief PCIE access types
typedef enum {
    TLP_TYPE_MemRdWr = 0,
    TLP_TYPE_MemRdLk = 1,
    TLP_TYPE_IORdWr = 2,
    TLP_TYPE_CfgRdWr0 = 4,
    TLP_TYPE_CfgRdWr1 = 5
} pcie_tlp_type_e;

//! @brief PCIE access directions
typedef enum {
    PCIE_IATU_VP_DIR_INBOUND,
    PCIE_IATU_VP_DIR_OUTBOUND,
    PCIE_IATU_VP_DIR_MAX,
} pcie_iatu_vp_dir_e;

//! @brief IATU viewports
typedef enum {
    PCIE_IATU_VIEWPORT_0,
    PCIE_IATU_VIEWPORT_1,
    PCIE_IATU_VIEWPORT_2,
    PCIE_IATU_VIEWPORT_3,

    PCIE_IATU_VIEWPORT_MAX,
} pcie_iatu_vp_e;

//! @brief PCIE link types
typedef enum {
    NO_LINK,
    GEN1_LINK,
    GEN2_LINK,
    GEN3_LINK,
} pcie_link_type_e;

//! @brief PCIE configuration header types
typedef enum {
    CONFIG_HEADER_TYPE0,
    CONFIG_HEADER_TYPE1,
} pcie_config_header_type_e;

//! @brief PCIE work modes
typedef enum {
    PCIE_DM_MODE_EP = 0,
    PCIE_DM_MODE_RC = 0x4,
} pcie_dm_mode_e;

//! @brief PCIE space types
typedef enum {
    PCIE_SPACE_TYPE_CFG,
    PCIE_SPACE_TYPE_MEM,
    PCIE_SPACE_TYPE_IO,
} pcie_space_type_e;

//! @brief PCIE space property types
typedef enum {
    PCIE_MEM_PROT_BIT_32 = 0x00 << 1,
    PCIE_MEM_PROT_BIT_64 = 0x10 << 1,
    PCIE_MEM_PROT_PREFETCH_YES = 0x01 << 3,
    PCIE_MEM_PROT_PREFETCH_NO = 0x00 << 3,
} pcie_space_prot_e;

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

/*! 
 * @brief This function initialized the PCIE controller.
 *
 * @param    dev_mode the Mode of the PCIE controller, root complex or endpoint	
 *
 * @return   0 if succeed, -1 if failed
 */
int pcie_init(pcie_dm_mode_e dev_mode);

/*! 
 * @brief Map endpoint's space to CPU side.
 *
 * @param    viewport 	the viewport number of iATU	
 * @param    tlp_type 	the type of the transaction layer package
 * @param	 addr_base_cpu_side: base address in CPU side
 * @param	 addr_base_pcie_side: base address in PCIE side
 * @param	 size: the size of the space to be mapped
 *
 * @return   base address in CPU side
 */
uint32_t pcie_map_space(uint32_t viewport,
                        uint32_t tlp_type,
                        uint32_t addr_base_cpu_side, uint32_t addr_base_pcie_side, uint32_t size);

#endif // PCIE_H
