/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __CP15_H__
#define __CP15_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    // Clean/Invalidate/Clean and Invalidate
    // [ref]
    //   1) DDI0406C_d_armv7ar_arm.pdf: B2.2.6 About ARMv7 cache and branch predictor maintenance functionality
    //      Terminology for Clean, Invalidate, and Clean and Invalidate operations

    void rt_cpu_icache_invalidate_buf(void* pBuf, uint32_t size);

    void rt_cpu_dcache_invalidate(void);
    void rt_cpu_dcache_clean(void);
    void rt_cpu_dcache_clean_invalidate(void);

    void rt_cpu_dcache_invalidate_buf(void* pBuf, uint32_t size);
    void rt_cpu_dcache_clean_buf(void* pBuf, uint32_t size);
    void rt_cpu_dcache_clean_invalidate_buf(void* pBuf, uint32_t size);

#define CP15_SCTLR_AFE              (1 << 29)   // Access flag enable. 1/0 = Access permissions: use AP[2:1]/AP[2:0]
#define CP15_SCTLR_TRE              (1 << 28)   // TEX remap enable
#define CP15_SCTLR_I                (1 << 12)   // icache enable
#define CP15_SCTLR_Z                (1 << 11)   // Branch prediction enable
#define CP15_SCTLR_C                (1 << 2)    // dcache enable
#define CP15_SCTLR_A                (1 << 1)    // Alignment check enable
    void rt_cpu_ctl_feature_disable(uint32_t features);
    void rt_cpu_ctl_feature_enable(uint32_t features);
    uint32_t rt_cpu_ctl_feature_get(void);

    void rt_cpu_branch_prediction_enable(void);
    void rt_cpu_branch_prediction_disable(void);

    void rt_cpu_icache_disable(void);
    void rt_cpu_icache_enable(void);

    void rt_cpu_dcache_disable(void);
    void rt_cpu_dcache_enable(void);

    void rt_cpu_cache_disable(void);
    void rt_cpu_cache_enable(void);

    void rt_cpu_mmu_disable(void);
    void rt_cpu_mmu_enable(void);

    void rt_cpu_auxctl_feature_enable(uint32_t enFlag);
    void rt_cpu_auxctl_feature_disable(uint32_t disFlag);

    void rt_cpu_tlb_set(uint32_t ttb);
    void rt_cpu_tlb_invalidate(void);
    void rt_cpu_vector_set_base(uint32_t addr);
    void rt_cpu_domain_access_client_set(void);

    void rt_hw_cpu_dcache_enable(void);
    void rt_hw_cpu_icache_enable(void);

#ifdef __cplusplus
}
#endif

#endif // __CP15_H__
