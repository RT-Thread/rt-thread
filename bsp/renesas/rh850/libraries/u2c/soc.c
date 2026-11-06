/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include <rthw.h>
#include "soc.h"

static void u2c_module_release(rt_ubase_t swmress, rt_ubase_t msr,
                               rt_uint32_t bit)
{
    while ((HWREG32(swmress) & bit) != 0U)
    {
    }
    HWREG32(SOC_MSRKCPROT) = SOC_KCPROT_ENABLE;
    HWREG32(msr) &= ~bit;
    while ((HWREG32(msr) & bit) != 0U)
    {
    }
    HWREG32(SOC_MSRKCPROT) = SOC_KCPROT_DISABLE;
}

void soc_init(void)
{
    HWREG32(SOC_CLKKCPROT1) = SOC_KCPROT_ENABLE;
    HWREG32(SOC_CKS_RLINC) = SOC_CKS_RLIN_HSB;
    while ((HWREG32(SOC_CKS_RLINS) & 0x7U) != SOC_CKS_RLIN_HSB)
    {
    }
    HWREG32(SOC_CLKKCPROT1) = SOC_KCPROT_DISABLE;

    u2c_module_release(SOC_SWMRESS_RLIN3, SOC_MSR_RLIN3, SOC_MSR_RLIN311_BIT);
    u2c_module_release(SOC_SWMRESS_OSTM, SOC_MSR_OSTM, SOC_MSR_OSTM0_BIT);
}
