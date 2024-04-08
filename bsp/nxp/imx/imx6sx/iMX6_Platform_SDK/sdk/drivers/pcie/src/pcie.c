/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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
 * @file pcie.c
 * @brief PCIE driver.
 */

#include "sdk.h"
#include "soc_memory_map.h"
#include "iomux_register.h"
#include "pcie/pcie_common.h"
#include "registers/regspcierc.h"
#include "registers/regspciepl.h"
#include "registers/regspciephy.h"
#include "pcie/pcie_phy.h"

#define DEBUG_ENABLE	1

#if PCIE_DEBUG_ENABLE
#define TRACE(fmt, args...)	printf(fmt,##args)
#else
#define TRACE(fmt, args...)
#endif

extern void hal_delay_us(uint32_t usecs);

void (*pcie_func_clk_setup) (uint32_t enable) = NULL;
void (*pcie_func_pwr_setup) (uint32_t enable) = NULL;
void (*pcie_func_card_pwr_setup) (uint32_t enable) = NULL;
void (*pcie_func_card_ref_clk_setup) (uint32_t enable) = NULL;
void (*pcie_func_card_rst) (void) = NULL;

/********** IOMUX GPR variables and routines *******************/
static const pcie_iomux_gpr_field_t pcie_iomux_gpr_fields[] = {
    {IOMUXC_GPR12, (1 << 9), 9},    //    .apps_pm_xmt_pme(iomuxc_gpr12[9]),
    {IOMUXC_GPR12, (0xf << 12), 12},    //    .device_type(iomuxc_gpr12[15:12]),
    {IOMUXC_GPR12, (0xf << 17), 17},    //    .diag_status_bus_select(iomuxc_gpr12[20:17]),
    {IOMUXC_GPR1, (1 << 14), 14},   //    .sys_int(iomuxc_gpr1[14]),
    {IOMUXC_GPR12, (1 << 16), 16},  //    .apps_pm_xmt_turnoff(iomuxc_gpr12[16]),
    {IOMUXC_GPR12, (1 << 10), 10},  //    .app_ltssm_enable(iomuxc_gpr12[10]),
    {IOMUXC_GPR12, (1 << 11), 11},  //    .app_init_rst(iomuxc_gpr12[11]),
    {IOMUXC_GPR1, (1 << 16), 16},   //    .ref_ssp_en(iomuxc_gpr1[16]), 
    {IOMUXC_GPR12, (7 << 21), 21},  //    .diag_ctrl_bus(iomuxc_gpr12[23:21]),
    {IOMUXC_GPR1, (1 << 26), 26},   //    .app_req_entr_l1(iomuxc_gpr1_26),
    {IOMUXC_GPR1, (1 << 27), 27},   //    .app_ready_entr_l23(iomuxc_gpr1_27),
    {IOMUXC_GPR1, (1 << 28), 28},   //    .app_req_exit_l1(iomuxc_gpr1_28),
    {IOMUXC_GPR1, (1 << 30), 30},   //    .app_clk_req_n(iomuxc_gpr1_30),
    {IOMUXC_GPR1, (((uint32_t) 1) << 31), 31},  //    .cfg_l1_clk_removal_en(iomuxc_gpr1_31),
    {IOMUXC_GPR1, (1 << 18), 18},   //    .test_powerdown(iomuxc_gpr1_18),
    {IOMUXC_GPR12, (0x1f << 4), 4}, //    .los_level(iomuxc_gpr12[8:4]),
    {IOMUXC_GPR8, (0x3f << 0), 0},  //    .pcs_tx_deemph_gen1(iomuxc_gpr8[5:0]),
    {IOMUXC_GPR8, (0x3f << 6), 6},  //    .pcs_tx_deemph_gen2_3p5db(iomuxc_gpr8[11:6]),
    {IOMUXC_GPR8, (0x3f << 12), 12},    //    .pcs_tx_deemph_gen2_6db(iomuxc_gpr8[17:12]),
    {IOMUXC_GPR8, (0x7f << 18), 18},    //    .pcs_tx_swing_full(iomuxc_gpr8[24:18]),
    {IOMUXC_GPR8, (((uint32_t) 0x7f) << 25), 25},   //    .pcs_tx_swing_low(iomuxc_gpr8[31:25]),
};

static void pcie_gpr_write_field(pcie_iomux_gpr_field_type_e field, uint32_t val)
{
    uint32_t v, addr, mask, offset;

    addr = pcie_iomux_gpr_fields[field].addr;
    mask = pcie_iomux_gpr_fields[field].mask;
    offset = pcie_iomux_gpr_fields[field].offset;

    v = reg32_read(addr);
    v &= ~mask;
    v |= ((val << offset) & mask);
    reg32_write(addr, v);
}

static uint32_t pcie_gpr_read_field(pcie_iomux_gpr_field_type_e field)
{
    uint32_t v, addr, mask, offset;

    addr = pcie_iomux_gpr_fields[field].addr;
    mask = pcie_iomux_gpr_fields[field].mask;
    offset = pcie_iomux_gpr_fields[field].offset;

    v = readl(addr);
    v &= mask;
    v = v >> offset;

    return v;
}

static int wait_link_up(int wait_ms)
{
    uint32_t val, rx_valid, ltssm;
    int count;

    count = wait_ms;
    do {
	val = HW_PCIE_PL_DEBUG1_RD() & (0x01 << (36 - 32));	//link is debug bit 36 debug 1 start in bit 32
        count--;
        hal_delay_us(3000);

	pcie_phy_cr_read(HW_PCIE_PHY_RX_ASIC_OUT_ADDR, &rx_valid);
	ltssm = HW_PCIE_PL_DEBUG0_RD() & 0x3F;
	/*
    	 * If the link up stuck, reset the phy. This is recommonded by IP vendor.
	 */
	if ((ltssm == 0x0D) && ((rx_valid & 0x01) == 0)) {
		pcie_phy_cr_write(HW_PCIE_PHY_RX_OVRD_IN_LO_ADDR, 0x0028);
		hal_delay_us(3000);
		pcie_phy_cr_write(HW_PCIE_PHY_RX_OVRD_IN_LO_ADDR, 0x0000);
	}
    } while (!val && (count > 0));

    if (!val)
        return -1;

    return 0;
}

/**************** Common routines **************************/

uint32_t pcie_map_space(uint32_t viewport, uint32_t tlp_type,
                        uint32_t addr_base_cpu_side, uint32_t addr_base_pcie_side, uint32_t size)
{
    HW_PCIE_PL_IATUVR_WR((viewport & 0x0F) | (0 << 31));
    HW_PCIE_PL_IATURLBA_WR(addr_base_cpu_side);
    HW_PCIE_PL_IATURUBA_WR(0);
    HW_PCIE_PL_IATURLA_WR(addr_base_cpu_side + size - 1);
    HW_PCIE_PL_IATURUTA_WR(0);
    HW_PCIE_PL_IATURLTA_WR(addr_base_pcie_side); 
    HW_PCIE_PL_IATURC1_WR(tlp_type & 0x0F);
    HW_PCIE_PL_IATURC2_WR(((unsigned int)(1 << 31)));

    return addr_base_cpu_side;
}

int pcie_init(pcie_dm_mode_e dev_mode)
{
    uint32_t val;

    pcie_gpr_write_field(diag_status_bus_select, 0xb);

    pcie_gpr_write_field(app_ltssm_enable, 0);

    // configure constant input signal to the pcie ctrl and phy
    pcie_gpr_write_field(device_type, dev_mode);

    pcie_gpr_write_field(los_level, 9); //phy Loss-Of-Signal detection level. process dependent.
    pcie_gpr_write_field(tx_deemph_gen1, 0);   // typical setting for PCIe 1.1 operation - package dependen
    pcie_gpr_write_field(tx_deemph_gen2_3p5db, 0); // setting for PCI2 2.0 operation with low de-emphasis setting - package dependen
    pcie_gpr_write_field(tx_deemph_gen2_6db, 20);   // typical setting for PCIe 2.0 operation - package dependen
    pcie_gpr_write_field(tx_swing_full, 127);   // For the default 1.0V amplitude - package dependent
    pcie_gpr_write_field(tx_swing_low, 127);    // to support PCIe Mobile Mode

    if (dev_mode == PCIE_DM_MODE_RC) {
        if (NULL != pcie_func_pwr_setup) {
            pcie_func_pwr_setup(1);
        }
        if (NULL != pcie_func_clk_setup) {
            pcie_func_clk_setup(1);
        }
        if (NULL != pcie_func_card_pwr_setup) {
            pcie_func_card_pwr_setup(1);
        }
        // wait for the power stable
        hal_delay_us(1000 * 10);

        if (NULL != pcie_func_card_ref_clk_setup) {
            pcie_func_card_ref_clk_setup(1);
        }
        if (NULL != pcie_func_card_rst) {
            pcie_func_card_rst();
        }
    }
    // enable ref clk of the phy within i.mx6x
    pcie_gpr_write_field(ref_ssp_en, 1);
    // wait for a while, then access the controller's registers.
    hal_delay_us(1000);

    //start link up       
    pcie_gpr_write_field(app_ltssm_enable, 1);

    if (0 != wait_link_up(2000)) {
        printf("Link timeout.\n");
        return -1;
    }
    //enable master, io, memory
    val = HW_PCIE_RC_COMMAND_RD();
    val |= BM_PCIE_RC_COMMAND_I_O_SPACE_ENABLE |
	BM_PCIE_RC_COMMAND_MEMORY_SPACE_ENABLE |
	BM_PCIE_RC_COMMAND_BUS_MASTER_ENABLE;
    HW_PCIE_RC_COMMAND_WR(val);

    return 0;
}
