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
 * @file pcie_phy.c
 * @brief PCIE PHY driver.
 */

#include "sdk.h"
#include "soc_memory_map.h"
#include "pcie/pcie_common.h"
#include "registers/regspciepl.h"
#include "registers/regspciephy.h"

#define PCIE_PHY_CR_ACK_POLLING_TIMES	0x100

//! phy control bus bit definition
#define PCIE_CR_CTL_DATA_LOC 0
#define PCIE_CR_CTL_CAP_ADR_LOC 16
#define PCIE_CR_CTL_CAP_DAT_LOC 17
#define PCIE_CR_CTL_WR_LOC 18
#define PCIE_CR_CTL_RD_LOC 19
#define PCIE_CR_STAT_DATA_LOC 0
#define PCIE_CR_STAT_ACK_LOC 16

/***************** PCI-e phy variable and routines ***************/
static int pcie_phy_cr_ack_polling(int32_t max_iterations, int32_t exp_val)
{
    uint32_t val;
    int wait_counter;

    wait_counter = 0;
    do {
	val = (HW_PCIE_PL_PHY_STATUS_RD() >> PCIE_CR_STAT_ACK_LOC) & 0x01;
        wait_counter++;
    } while ((wait_counter < max_iterations) && (val != exp_val));

    if (val != exp_val)
        return -1;

    return 0;
}

static int pcie_phy_cr_cap_addr(uint32_t addr)
{
    int val;

    // write addr
    val = (addr & 0xFFFF) << PCIE_CR_CTL_DATA_LOC;
    HW_PCIE_PL_PHY_CTRL_WR(val);
    // capture addr
    val |= (0x1 << PCIE_CR_CTL_CAP_ADR_LOC);
    HW_PCIE_PL_PHY_CTRL_WR(val);

    // wait for ack
    if (0 != pcie_phy_cr_ack_polling(PCIE_PHY_CR_ACK_POLLING_TIMES, 1)) {
        return -1;
    }
    // deassert cap addr
    val = (addr & 0xFFFF) << PCIE_CR_CTL_DATA_LOC;
    HW_PCIE_PL_PHY_CTRL_WR(val);
    // wait for ack de-assetion
    if (0 != pcie_phy_cr_ack_polling(PCIE_PHY_CR_ACK_POLLING_TIMES, 0)) {
        return -1;
    }

    return 0;
}

int pcie_phy_cr_read(uint32_t addr, uint32_t * data)
{
    int32_t val;

    if (0 != pcie_phy_cr_cap_addr(addr)) {
        return -1;
    }
    // assert rd signal
    val = 0x1 << PCIE_CR_CTL_RD_LOC;
    HW_PCIE_PL_PHY_CTRL_WR(val);
    // wait for ack
    if (0 != pcie_phy_cr_ack_polling(PCIE_PHY_CR_ACK_POLLING_TIMES, 1)) {
        return -1;
    }
    // read data
    val = HW_PCIE_PL_PHY_STATUS_RD();
    *data = (val >> PCIE_CR_STAT_DATA_LOC) & 0xFFFF;

    // deassert rd signal
    val = 0x0;
    HW_PCIE_PL_PHY_CTRL_WR(val);
    // wait for ack de-assetion
    if (0 != pcie_phy_cr_ack_polling(PCIE_PHY_CR_ACK_POLLING_TIMES, 0)) {
        return -1;
    }

    return 0;
}

int pcie_phy_cr_write(uint32_t addr, uint32_t data)
{
    int32_t val;

    if (0 != pcie_phy_cr_cap_addr(addr)) {
        return -1;
    }

    val = (data & 0xFFFF) << PCIE_CR_CTL_DATA_LOC;
    HW_PCIE_PL_PHY_CTRL_WR(val);
    // capture data
    val |= (0x1 << PCIE_CR_CTL_CAP_DAT_LOC);
    HW_PCIE_PL_PHY_CTRL_WR(val);
    // wait for ack
    if (0 != pcie_phy_cr_ack_polling(PCIE_PHY_CR_ACK_POLLING_TIMES, 1)) {
        return -1;
    }
    // deassert cap data
    val = (data & 0xFFFF) << PCIE_CR_CTL_DATA_LOC;
    HW_PCIE_PL_PHY_CTRL_WR(val);
    // wait for ack de-assetion
    if (0 != pcie_phy_cr_ack_polling(PCIE_PHY_CR_ACK_POLLING_TIMES, 0)) {
        return -1;
    }
    // assert wr signal
    val = 0x1 << PCIE_CR_CTL_WR_LOC;
    HW_PCIE_PL_PHY_CTRL_WR(val);
    // wait for ack
    if (0 != pcie_phy_cr_ack_polling(PCIE_PHY_CR_ACK_POLLING_TIMES, 1)) {
        return -1;
    }
    // deassert wr signal
    val = (data & 0xFFFF) << PCIE_CR_CTL_DATA_LOC;
    HW_PCIE_PL_PHY_CTRL_WR(val);
    // wait for ack de-assetion
    if (0 != pcie_phy_cr_ack_polling(PCIE_PHY_CR_ACK_POLLING_TIMES, 0)) {
        return -1;
    }
    val = 0x0;
    HW_PCIE_PL_PHY_CTRL_WR(val);

    return 0;
}
