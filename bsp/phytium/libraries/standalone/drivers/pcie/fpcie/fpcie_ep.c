/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fpcie_ep.c
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:57:59
 * Description: This file is for pcie endpoint device operation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */

#include "fpcie.h"
#include "fpcie_hw.h"
#include "ftypes.h"
#include "fpcie_common.h"
#include <math.h>
#include <string.h>
#include "fkernel.h"
#include "fdebug.h"


/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define FPCIE_EP_DEBUG_TAG "FPCIE_EP"
#define FPCIE_EP_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIE_EP_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_EP_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIE_EP_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_EP_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIE_EP_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_EP_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FPCIE_EP_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

int FPcieEpSetBar(FPcie *instance_p, u32 peu_num, u32 bar_num, u64 bar_mem_addr, u64 bar_mem_size, int flags)
{
    u32 addr0, addr1, reg, cfg, b, aperture, ctrl;
    u64 sz;
    uintptr_t base_addr;
    FASSERT(instance_p != NULL);
    base_addr = *(uintptr_t *)(&instance_p->config.control_c0_address + peu_num);

    /* BAR size is 2^(aperture + 7) */
    sz = max(bar_mem_size, (u64)FPCIE_EP_MIN_APERTURE);
    /*
     * roundup_pow_of_two() returns an unsigned long, which is not suited
     * for 64bit values.
     */

    sz = 1ULL << fls(sz - 1);
    aperture = log2(sz) - 7; /* 128B -> 0, 256B -> 1, 512B -> 2, ... */

    if ((flags & FPCIE_BASE_ADDRESS_SPACE) == FPCIE_BASE_ADDRESS_SPACE)
    {
        ctrl = FPCIE_LM_BAR_CFG_CTRL_IO_32BITS;
    }
    else
    {
        boolean is_prefetch = !!(flags & FPCIE_BASE_ADDRESS_MEM_PREFETCH);
        boolean is_64bits = sz > SZ_2G;

        if (is_64bits && (bar_num & 1))
        {
            return FPCIE_ERR_INVALID_PARAM;
        }

        if (is_64bits && !(flags & FPCIE_BASE_ADDRESS_MEM_TYPE_64))
        {
            flags |= FPCIE_BASE_ADDRESS_MEM_TYPE_64;
        }

        if (is_64bits && is_prefetch)
        {
            ctrl = FPCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_64BITS;
        }
        else if (is_prefetch)
        {
            ctrl = FPCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_32BITS;
        }
        else if (is_64bits)
        {
            ctrl = FPCIE_LM_BAR_CFG_CTRL_MEM_64BITS;
        }
        else
        {
            ctrl = FPCIE_LM_BAR_CFG_CTRL_MEM_32BITS;
        }
    }

    addr0 = LOWER_32_BITS(bar_mem_addr);
    addr1 = UPPER_32_BITS(bar_mem_addr);

    FPCIE_WRITEREG(base_addr, FPCIE_AT_IB_EP_FUNC_BAR_ADDR0(0, bar_num), addr0);
    FPCIE_WRITEREG(base_addr, FPCIE_AT_IB_EP_FUNC_BAR_ADDR1(0, bar_num), addr1);

    if (bar_num < FPCIE_BAR_4)
    {
        reg = FPCIE_LM_EP_FUNC_BAR_CFG0(0);
        b = reg;
    }
    else
    {
        reg = FPCIE_LM_EP_FUNC_BAR_CFG0(0);
        b = reg - FPCIE_BAR_4;
    }

    cfg = FPCIE_READREG(base_addr, reg);
    cfg &= ~(FPCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
             FPCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
    cfg |= (FPCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE(b, aperture) |
            FPCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl));

    FPCIE_WRITEREG(base_addr, reg, cfg);

    return FT_SUCCESS;
}

int FPcieEpCleanBar(FPcie *instance_p, u32 peu_num, u32 bar_num)
{
    u32 reg, cfg, b, ctrl;
    uintptr_t base_addr;
    base_addr = *(uintptr_t *)(&instance_p->config.control_c0_address + peu_num);

    if (bar_num < FPCIE_BAR_4)
    {
        reg = FPCIE_LM_EP_FUNC_BAR_CFG0(0);
        b = bar_num;
    }
    else
    {
        reg = FPCIE_LM_EP_FUNC_BAR_CFG1(0);
        b = bar_num - FPCIE_BAR_4;
    }

    ctrl = FPCIE_LM_BAR_CFG_CTRL_DISABLED;
    cfg = FPCIE_READREG(base_addr, reg);
    cfg &= ~(FPCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
             FPCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
    cfg |= FPCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl);
    FPCIE_WRITEREG(base_addr, reg, cfg);

    return FT_SUCCESS;
}

static int GetOneInData(u64 data)
{
    int n = 63;
    while (!(data & GENMASK_ULL(63, 63)))
    {
        n--;
        data <<= 1;
    }

    return n;
}

int FPcieEpMapAddr(FPcie *instance_p, u32 peu_num, u64 phy_addr, u64 pcie_addr, u64 size)
{
    u32 addr0, addr1;
    u64 pcie_addr_limit;
    u64 reg;
    uintptr_t config_address;
    uintptr_t control_address;

    FASSERT(instance_p != NULL);

    if (peu_num < FPCIE_PEU1_C0)
    {
        config_address = instance_p->config.peu0_config_address;
    }
    else
    {
        config_address = instance_p->config.peu1_config_address;
    }

    control_address = *(uintptr_t *)(&instance_p->config.control_c0_address + peu_num);
    pcie_addr_limit = pcie_addr + size;

    if (phy_addr < 0x1000000000)
    {
        addr0 = ((pcie_addr >> 16) & FPCIE_C0_PREF_BASE_MASK) | (pcie_addr_limit & FPCIE_C0_PREF_LIMIT_MASK);
        reg = FPCIE_REG_EP_C0_PREF_BASE_LIMIT_OFFSET_GET(config_address, peu_num);
        FPCIE_WRITEREG(reg, 0, addr0);
    }
    else
    {
        addr0 = (((pcie_addr & 0xFFFFFFFF) >> 15) & 0xFFF0) | (pcie_addr_limit & 0xFFF00000);
        addr1 = ((pcie_addr >> 32) & 0xFF) | ((pcie_addr_limit >> 24) & 0xFF00);
        reg = FPCIE_REG_EP_C0_MEM_BASE_LIMIT_OFFSET_GET(config_address, peu_num);
        FPCIE_WRITEREG(reg, 0, addr0);
        FPCIE_WRITEREG(reg + 4, 0, addr1);
    }

    addr0 = (phy_addr & 0xFFFFFF00) | (GetOneInData(size - 1) & 0x3F);
    addr1 = (phy_addr >> 32);
    FPCIE_WRITEREG(control_address, FPCIE_REG_OUTBOUND_R0_PATR0_OFFSET, addr0);
    FPCIE_WRITEREG(control_address, FPCIE_REG_OUTBOUND_R0_PATR1_OFFSET, addr1);

    FPCIE_WRITEREG(control_address, FPCIE_REG_OUTBOUND_R0_PHDR0_OFFSET, 2);
    FPCIE_WRITEREG(control_address, FPCIE_REG_OUTBOUND_R0_PHDR1_OFFSET, 0);
    FPCIE_WRITEREG(control_address, FPCIE_REG_OUTBOUND_R0_PHDR2_OFFSET, 0);

    addr0 = (pcie_addr & 0xFFFFFF00) | (GetOneInData(size - 1) & 0x3F);
    addr1 = (pcie_addr >> 32);
    FPCIE_WRITEREG(control_address, FPCIE_REG_OUTBOUND_R0_ARBA0_OFFSET, addr0);
    FPCIE_WRITEREG(control_address, FPCIE_REG_OUTBOUND_R0_ARBA1_OFFSET, addr1);

    return FT_SUCCESS;
}
