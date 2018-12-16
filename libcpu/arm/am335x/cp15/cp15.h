/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __CP15_H__
#define __CP15_H__

#include <rtdef.h>

typedef enum {
    CORTEX_TYPE_UNKNOWN,
    CORTEX_TYPE_A8,
    CORTEX_TYPE_A9,
} CORTEX_TYPE;

#ifdef __cplusplus
extern "C" {
#endif

    CORTEX_TYPE armv7_get_cortex_type(void);

    // Clean/Invalidate/Clean and Invalidate
    // [ref]
    //   1) DDI0406C_d_armv7ar_arm.pdf: B2.2.6 About ARMv7 cache and branch predictor maintenance functionality
    //      Terminology for Clean, Invalidate, and Clean and Invalidate operations

    void rt_cpu_branch_predictor_invalidate(void);
    void rt_cpu_icache_invalidate_inner_shareable(void);
    void rt_cpu_icache_invalidate(void);
    void rt_cpu_icache_invalidate_buf(const void* pBuf, uint32_t size);

    void rt_cpu_dcache_invalidate(void);
    void rt_cpu_dcache_clean(void);
    void rt_cpu_dcache_clean_invalidate(void);

    void rt_cpu_dcache_invalidate_buf(const void* pBuf, uint32_t size);
    void rt_cpu_dcache_clean_buf(const void* pBuf, uint32_t size);
    void rt_cpu_dcache_clean_invalidate_buf(const void* pBuf, uint32_t size);

#define CP15_SCTLR_AFE              (1 << 29)   // 0 = AP[0] behavior defined; 1 = access flag behavior defined
#define CP15_SCTLR_TRE              (1 << 28)   // TEX remap disabled/enable
#define CP15_SCTLR_I                (1 << 12)   // 0/1 = instruction caching disabled/enable
#define CP15_SCTLR_Z                (1 << 11)   // 0/1 = program flow prediction disabled/enable
#define CP15_SCTLR_C                (1 << 2)    // 0/1 = data caching disabled/enable
#define CP15_SCTLR_A                (1 << 1)    // 0/1 = strict alignment fault checking disabled/enabled
#define CP15_SCTLR_M                (1 << 0)    // 0/1 = MMU disabled/enable
    void rt_cpu_ctl_feature_disable(uint32_t features);
    void rt_cpu_ctl_feature_enable(uint32_t features);
    uint32_t rt_cpu_ctl_feature_get(void);

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

#ifdef __cplusplus
}
#endif

#endif // __CP15_H__
