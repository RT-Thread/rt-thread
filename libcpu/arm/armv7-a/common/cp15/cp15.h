/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __CP15_H__
#define __CP15_H__

#include <rtdef.h>
#include <armv7.h>
#include <asmopr.h>
#include <bitopr.h>

typedef enum {
    CORTEX_TYPE_UNKNOWN,
    CORTEX_TYPE_A5,
    CORTEX_TYPE_A7,
    CORTEX_TYPE_A8,
    CORTEX_TYPE_A9,
    CORTEX_TYPE_A15,
    CORTEX_TYPE_A17,
} CORTEX_TYPE;

#ifdef __cplusplus
extern "C" {
#endif

    CORTEX_TYPE armv7_get_cortex_type(void);

    /*
     * Clean/Invalidate/Clean and Invalidate
     * [ref]
     *   1) DDI0406C_d_armv7ar_arm.pdf: B2.2.6 About ARMv7 cache and branch predictor maintenance functionality
     *      Terminology for Clean, Invalidate, and Clean and Invalidate operations
     */

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

    /*
     * SCTLR, System Control Register
     * [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.130 SCTLR, System Control Register, VMSA
     *      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.9 System Control Register
     *      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.25 c1, Control Register
     *      Bit     Field           Description                                                     cortex-a9   cortex-a8
     *      31      reverse
     *      30      TE              0/1 = Enables ARM/Thumb exception generation                    supported   supported
     *      29      AFE             0 = AP[0] behavior defined; 1 = access flag behavior defined    supported   supported
     *      28      TRE             0/1 = TEX remap disabled/enable                                 supported   supported
     *      27      NMFI            0/1 = FIQ exceptions can/cannot be masked by software           supported   supported
     *      26      reverse
     *      25      EE              0/1 = CPSR E bit is set to 0/1 on an exception                  supported   supported
     *      24      VE              0/1 = FIQ and IRQ vectors from/not from the vector table
     *      23      reverse
     *      22      U               In ARMv7 this bit is RAO/SBOP,
     *      21      FI              Fast interrupts configuration enable
     *      20      UWXN            if implementation includes the Virtualization Extensions
     *      19      WXN             if implementation includes the Virtualization Extensions
     *      18      reverse
     *      17      HA              0/1 = Hardware Access flag disable/enable                       supported   supported
     *      16-15   reverse
     *      14      RR              0/1 = Normal replacement strategy/Predictable strategy          supported
     *      13      V               0/1 = Normal/High exception vectors selected                    supported   supported
     *      12      I               0/1 = instruction caching disabled/enable                       supported   supported
     *      11      Z               0/1 = program flow prediction disabled/enable                   supported   supported
     *      10      SW              0/1 = SWP and SWPB are UNDEFINED/DEFINED                        supported
     *      9-8     reverse         
     *      7       B               In ARMv7 this bit is RAZ/SBZP
     *      6       reverse         
     *      5       CP15BEN         0/1 = CP15 barrier operations disabled/enable
     *      4-3     reverse         
     *      2       C               0/1 = data caching disabled/enable                              supported   supported
     *      1       A               0/1 = strict alignment fault checking disabled/enabled          supported   supported
     *      0       M               0/1 = MMU disabled/enable                                       supported   supported
     */
#define CP15_SCTLR_AFE              _B(29)      /* 0 = AP[0] behavior defined; 1 = access flag behavior defined */
#define CP15_SCTLR_TRE              _B(28)      /* TEX remap disabled/enable */
#define CP15_SCTLR_V                _B(13)      /* Vectors bit. 0/1 = Low exception vectors(0x00000000)/High exception vectors(0xFFFF0000) */
#define CP15_SCTLR_I                _B(12)      /* 0/1 = instruction caching disabled/enable */
#define CP15_SCTLR_Z                _B(11)      /* 0/1 = program flow prediction disabled/enable */
#define CP15_SCTLR_C                _B(2)       /* 0/1 = data caching disabled/enable */
#define CP15_SCTLR_A                _B(1)       /* 0/1 = strict alignment fault checking disabled/enabled */
#define CP15_SCTLR_M                _B(0)       /* 0/1 = MMU disabled/enable */
    void rt_cpu_ctl_feature_disable(uint32_t features);
    void rt_cpu_ctl_feature_enable(uint32_t features);
    uint32_t rt_cpu_ctl_feature_get(void);

    void rt_cpu_cache_disable(void);
    void rt_cpu_cache_enable(void);

    void rt_cpu_mmu_disable(void);
    void rt_cpu_mmu_enable(void);

    /*
     * A9 ACTLR
     * [ref]DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.10 Auxiliary Control Register
     *      Bit     Field                                   Description
     *      31-10   reverse
     *      9       Parity_on                               Support for parity checking. 0(reset value)/1 = Disabled/Enabled
     *      8       Alloc in one way                        Enable allocation in one cache way only. 
     *                                                      For use with memory copy operations to reduce cache pollution.The reset value is zero.
     *      7       EXCL                                    Exclusive cache bit. 0(reset value)/1 = Disabled/Enabled
     *      6       SMP                                     Signals if the Cortex-A9 processor is taking part in coherency or not
     *      5-4     reverse
     *      3       Write full line of zeros mode           Enable write full line of zeros mode. The reset value is zero
     *      2       L1 prefetch enable                      Dside prefetch. 0(reset value)/1 = Disabled/Enabled
     *      1       L2 prefetch enable                      Prefetch hint enable. The reset value is zero
     *      0       FW                                      Cache and TLB maintenance broadcast. 0(reset value)/1 = Disabled/Enabled
     */
#define CP15_ACTLR_A9_PARITY_ON             _B(9)
#define CP15_ACTLR_A9_ALLOC_IN_ONE_WAY      _B(8)
#define CP15_ACTLR_A9_EXCL                  _B(7)
#define CP15_ACTLR_A9_SMP                   _B(6)
#define CP15_ACTLR_A9_WRITE_FULL_LINE       _B(3)
#define CP15_ACTLR_A9_L1_PREFETCH_ENABLE    _B(2)
#define CP15_ACTLR_A9_L2_PREFETCH_ENABLE    _B(1)
#define CP15_ACTLR_A9_FW                    _B(0)

    /*
     * A8 ACTLR
     * [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.26 c1, Auxiliary Control Register
     *      Bit     Field                                   Description
     *      31      L2 hardware reset disable               the L2 valid RAM contents are not reset by hardware
     *      30      L1 hardware reset disable               the L1 valid RAM contents are not reset by hardware
     *      29-21   reverse
     *      20      Cache maintenance pipeline              non-pipelined cache maintenance operations
     *      19      Clock stop request disable              disables the CLKSTOPREQ functionality
     *      18      CP14/CP15 instruction serialization     enforces serialization of CP14 and CP15 instructions
     *      17      CP14/CP15 wait on idle                  enforces wait on idle for serialized CP14 or CP15 instructions
     *      16      CP14/CP15 pipeline flush                imposes a pipeline flush on CP14 and CP15 instructions
     *      15      Force ETM clock                         Forces ETM clock enable active
     *      14      Force NEON clock                        Forces NEON clock enable active
     *      13      Force main clock                        Forces the main processor clock enable active
     *      12      Force NEON single issue                 Forces single issue of Advanced SIMD instructions
     *      11      Force load/store single issue           Forces single issue of load/store instructions
     *      10      Force single issue                      Forces single issue of all instructions
     *      9       PLDNOP                                  PLD instructions are executed as NOP instructions
     *      8       WFINOP                                  executes WFI instructions as NOP instruction
     *      7       Disable branch size mispredicts         executes the CP15 Invalidate All and Invalidate by MVA instructions as specified and prevents BTB branch size mispredicts.
     *      6       IBE                                     executes the CP15 Invalidate All and Invalidate by MVA instructions as specified
     *      5       L1NEON                                  enables caching NEON data within the L1 data and L2 cache
     *      4       ASA                                     enables speculative accesses
     *      3       L1PE                                    L1 cache parity enabled
     *      2       reverse
     *      1       L2EN                                    L2 cache enabled
     *      0       L1ALIAS                                 L1 data cache hardware alias support disabled
     */
#define CP15_ACTLR_A8_L2EN                  _B(1)

    void rt_cpu_auxctl_feature_enable(uint32_t enFlag);
    void rt_cpu_auxctl_feature_disable(uint32_t disFlag);

    void rt_cpu_tlb_set(uint32_t ttb);
    void rt_cpu_tlb_invalidate(void);
    void rt_cpu_vector_set_base(uint32_t addr);
    void rt_cpu_domain_access_client_set(void);

    uint32_t rt_cpu_cbar_get(void);

    void rt_cpu_vfp_neon_access_enable(void);
    uint32_t rt_cpu_fpscr_get_default(void);
    void rt_cpu_fpscr_init(void);

    uint32_t rt_hw_cpu_id(void);

#ifdef __cplusplus
}
#endif

#endif
