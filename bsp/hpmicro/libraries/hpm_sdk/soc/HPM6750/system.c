/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_l1c_drv.h"

#ifndef CONFIG_DISABLE_GLOBAL_IRQ_ON_STARTUP
#define CONFIG_DISABLE_GLOBAL_IRQ_ON_STARTUP 0
#endif

void enable_plic_feature(void)
{
    uint32_t plic_feature = 0;
#ifndef USE_NONVECTOR_MODE
    /* enabled vector mode and preemptive priority interrupt */
    plic_feature |= HPM_PLIC_FEATURE_VECTORED_MODE;
#endif
#if !defined(DISABLE_IRQ_PREEMPTIVE) || (DISABLE_IRQ_PREEMPTIVE == 0)
    /* enabled preemptive priority interrupt */
    plic_feature |= HPM_PLIC_FEATURE_PREEMPTIVE_PRIORITY_IRQ;
#endif
    __plic_set_feature(HPM_PLIC_BASE, plic_feature);
}

__attribute__((weak)) void system_init(void)
{
    disable_global_irq(CSR_MSTATUS_MIE_MASK);
    disable_irq_from_intc();
    enable_plic_feature();
    enable_irq_from_intc();
#if !CONFIG_DISABLE_GLOBAL_IRQ_ON_STARTUP
    enable_global_irq(CSR_MSTATUS_MIE_MASK);
#endif

#ifndef CONFIG_NOT_ENALBE_ACCESS_TO_CYCLE_CSR
    uint32_t mcounteren = read_csr(CSR_MCOUNTEREN);
    write_csr(CSR_MCOUNTEREN, mcounteren | 1); /* Enable MCYCLE */
#endif
#ifndef CONFIG_NOT_ENABLE_ICACHE
    l1c_ic_enable();
#endif
#ifndef CONFIG_NOT_ENABLE_DCACHE
    l1c_dc_enable();
    l1c_dc_invalidate_all();
#endif
}
