/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "cp15.h"

// VMSA CP15 c7 register summary
// [ref]DDI0406C_d_armv7ar_arm.pdf: B3.17.1 CP15 register summary by coprocessor register number
//                                  VMSA CP15 c7 register summary, Cache maintenance, address translation, and other functions
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.2.8 c7 registers
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
//      CRn     opc1    CRm     opc2    Operation                                                               cortex-a9   cortex-a8
//      c7      0       c0      4       UNPREDICTABLE, was Wait For Interrupt (CP15WFI) in ARMv6                Deprecated
//                      c1      0       ICIALLUIS, Invalidate all instruction caches to PoU Inner Shareable     surpported  
//                              6       BPIALLIS, Invalidate all branch predictors Inner Shareable              surpported
//                      c4      0       PAR, Physical Address Register                                          surpported
//                      c5      0       ICIALLU, Invalidate all instruction caches to PoU                       surpported  surpported
//                              1       ICIMVAU, Invalidate instruction caches by MVA to PoU                    surpported  surpported
//                              4       CP15ISB, Instruction Synchronization Barrier operation                  surpported  surpported
//                              6       BPIALL, Invalidate all branch predictors                                surpported  surpported
//                              7       BPIMVA, Invalidate MVA from branch predictors                                       surpported
//                      c6      1       DCIMVAC, Invalidate data cache line by MVA to PoC                       surpported  surpported
//                              2       DCISW, Invalidate data cache line by set/way                            surpported  surpported
//                      c8      0       ATS1CPR, PL1 read translation                                           surpported
//                              1       ATS1CPW, PL1 write translation                                          surpported
//                              2       ATS1CUR, unprivileged read translation                                  surpported
//                              3       ATS1CUW, unprivileged write translation                                 surpported
//                              4       ATS12NSOPR, PL1 read translation                                        surpported
//                              5       ATS12NSOPW, PL1 write translation                                       surpported
//                              6       ATS12NSOUR, unprivileged read translation                               surpported
//                              7       ATS12NSOUW, unprivileged write translation                              surpported
//                      c10     1       DCCMVAC, Clean data cache line by MVA to PoC                            surpported  surpported
//                              2       DCCSW, Clean data cache line by set/way                                 surpported  surpported
//                              4       CP15DSB, Data Synchronization Barrier operation                         Deprecated
//                              5       CP15DMB, Data Memory Barrier operation                                  Deprecated
//                      c11     1       DCCMVAU, Clean data cache line by MVA to PoU                            surpported  surpported
//                      c13     1       UNPREDICTABLE, was Prefetch instruction by MVA in ARMv6
//                      c14     1       DCCIMVAC, Clean and invalidate data cache line by MVA to PoC            surpported  surpported
//                              2       DCCISW, Clean and invalidate data cache line by set/way                 surpported  surpported
//              4       c8      0       ATS1HR, Hyp mode read translation
//                              1       ATS1HW, Hyp mode write translation
#define _ARM_CP_ICIMVAU_W(mva)      _ARM_CP_W(p15, 0, mva, c7, c5, 1)       // Invalidate instruction caches by MVA to PoU
#define _ARM_CP_DCIMVAC_W(mva)      _ARM_CP_W(p15, 0, mva, c7, c6, 1)       // Invalidate data cache line by MVA to PoC
#define _ARM_CP_DCCMVAC_W(mva)      _ARM_CP_W(p15, 0, mva, c7, c10, 1)      // Clean data cache line by MVA to PoC
#define _ARM_CP_DCCIMVAC_W(mva)     _ARM_CP_W(p15, 0, mva, c7, c14, 1)      // Clean and invalidate data cache line by MVA to PoC

#define _ARM_CP_ICIALLUIS_W(sbz)    _ARM_CP_W(p15, 0, sbz, c7, c1, 0)       // Invalidate all instruction caches to PoU Inner Shareable
#define _ARM_CP_ICIALLU_W(sbz)      _ARM_CP_W(p15, 0, sbz, c7, c5, 0)       // Invalidate all instruction caches to PoU

#define _ARM_CP_DCISW_W(setway)     _ARM_CP_W(p15, 0, setway, c7, c6, 2)    // Invalidate data cache line by set/way
#define _ARM_CP_DCCSW_W(setway)     _ARM_CP_W(p15, 0, setway, c7, c10, 2)   // Clean data cache line by set/way
#define _ARM_CP_DCCISW_W(setway)    _ARM_CP_W(p15, 0, setway, c7, c14, 2)   // Clean and invalidate data cache line by set/way

#define _ARM_CP_BPIALL_W(sbz)       _ARM_CP_W(p15, 0, sbz, c7, c5, 6)       // Invalidate all branch predictors

void rt_cpu_branch_predictor_invalidate(void)
{
    uint32_t sbz = 0;
    _ARM_CP_BPIALL_W(sbz); // Invalidate all branch predictors
    _ARM_ISB();
}

// CCSIDR, Cache Size ID Registers
// [ref]DDI0406C_d_armv7ar_arm.pdf: CCSIDR, Cache Size ID Registers, VMSA
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.5 Cache Size Identification Register
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.23 c0, Cache Size Identification Registers
//      Bit     Field               Description
//      31      WT                  1/0 = write-through supported/not supported
//      30      WB                  1/0 = write-back supported/not supported
//      29      RA                  1/0 = read allocation supported/not supported
//      28      WA                  1/0 = write allocation supported/not supported
//      27-13   NumSets             Indicates number of sets - 1
//      12-3    Associativity       Indicates number of ways - 1
//      2-0     LineSize            Indicates (log2(number of words in cache line)) - 2.
//                                  b001 Eight words per line.
//      MRC p15, 1, <Rd>, c0, c0, 0; Cache Size Identification Register
#define _ARM_CP_CCSIDR_R(ccsidr)    _ARM_CP_R(p15, 1, ccsidr, c0, c0, 0)
rt_inline void armv7_cache_get_set_way(uint32_t* pSetMask, uint32_t* pWayMask, uint32_t* pLog2LineSize)
{
    uint32_t ccsidr;
    _ARM_CP_CCSIDR_R(ccsidr);
    *pSetMask = _E_B_B(ccsidr, 27, 13);
    *pWayMask = _E_B_B(ccsidr, 12, 3);
    *pLog2LineSize = _E_B_B(ccsidr, 2, 0) + 4;
    return;
}

// CTR, Cache Type Register
// [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.42 CTR, Cache Type Register, VMSA
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.2.1 c0 registers
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.3 c0, Cache Type Register
//      Bit     Field               Description
//      31-29   0b100               0b100 ARMv7 format
//      28      Reverse             RAZ
//      27-24   CWG                 Cache Write-back Granule. The maximum size of memory that can be overwritten as a result of the
//                                  eviction of a cache entry that has had a memory location in it modified, encoded as Log2 of the
//                                  number of words.
//      23-20   ERG                 Exclusives Reservation Granule. The maximum size of the reservation granule that has been
//                                  implemented for the Load-Exclusive and Store-Exclusive instructions, encoded as Log2 of the
//                                  number of words.
//      19-16   DMinLine            Log2 of the number of words in the smallest cache line of all the data caches and unified caches that
//                                  are controlled by the processor.
//      15-14   L1Ip                Level 1 instruction cache policy. Indicates the indexing and tagging policy for the L1 instruction cache.
//      13-4    Reverse             RAZ
//      3-0     IMinLine            Log2 of the number of words in the smallest cache line of all the instruction caches that are 
//                                  controlled by the processor.
//      MRC p15, 0, <Rd>, c0, c0, 1 ; Read Cache Type Register
#define _ARM_CP_CTR_R(ctr) _ARM_CP_R(p15, 0, ctr, c0, c0, 1)
rt_inline uint32_t armv7_icache_get_line_size(void)
{
    uint32_t ctr;
    _ARM_DMB();
    _ARM_CP_CTR_R(ctr);
    uint32_t iMinLine = _E_B_B(ctr, 3, 0);
    return 1 << (iMinLine + 2);
}
rt_inline uint32_t armv7_dcache_get_line_size(void)
{
    uint32_t ctr;
    _ARM_DMB();
    _ARM_CP_CTR_R(ctr);
    uint32_t dMinLine = _E_B_B(ctr, 19, 16);
    return 1 << (dMinLine + 2);
}

// Invalidate all instruction caches to PoU Inner Shareable
void rt_cpu_icache_invalidate_inner_shareable(void)
{
    if (armv7_get_cortex_type() == CORTEX_TYPE_A9) {
        uint32_t sbz = 0;
        _ARM_CP_ICIALLUIS_W(sbz); // Invalidate all instruction caches to PoU Inner Shareable
        _ARM_ISB();
        return;
    }
    return;
}

// Invalidate all instruction caches to PoU
void rt_cpu_icache_invalidate(void)
{
    uint32_t sbz = 0;
    _ARM_CP_ICIALLU_W(sbz); // Invalidate all instruction caches to PoU
    _ARM_ISB();
    return;
}

// Invalidate instruction caches by MVA to PoU
void rt_cpu_icache_invalidate_buf(const void* pBuf, uint32_t bufSize)
{
    uint32_t lineSize = armv7_icache_get_line_size();

    const void* pBufLimit = (const void *)((uint32_t)pBuf + bufSize);
    do {
        uint32_t mva = RT_ALIGN_DOWN((uint32_t)pBuf, lineSize);
        _ARM_CP_ICIMVAU_W(mva); // Invalidate instruction caches by MVA to PoU
        pBuf = (const void *)((uint32_t)pBuf + lineSize);
    } while (pBuf < pBufLimit);

    _ARM_ISB();
    return;
}

// CLIDR, Cache Level ID Register
// [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.20 CLIDR, Cache Level ID Register, VMSA
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.6 Cache Level ID Register
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.21 c0, Cache Level ID Register
//      Bit     Field               Description
//      31-30   Reverse             UNK
//      29-27   LoUU                Level of Unification Uniprocessor for the cache hierarchy
//      26-24   LoC                 Level of Coherence for the cache hierarchy
//      23-21   LoUIS               Level of Unification Inner Shareable for the cache hierarchy
//      20-18   Ctype7              Ctype7~Ctype1: Cache Type fields. Indicate the type of cache implemented at each level.
//      17-15   Ctype6                  0b000 = No cache
//      14-12   Ctype5                  0b001 = Instruction cache only
//      11-9    Ctype4                  0b010 = Data cache only
//      8-6     Ctype3                  0b011 = Separate instruction and data caches
//      5-3     Ctype2
//      2-0     Ctype1
//      MRC p15, 1, <Rt>, c0, c0, 1 ; Read CLIDR into Rt
#define _ARM_CP_CLIDR_R(clidr) _ARM_CP_R(p15, 1, clidr, c0, c0, 1)

// CSSELR
// [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.41 CSSELR, Cache Size Selection Register, VMSA
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.8 Cache Size Selection Register
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.24 c0, Cache Size Selection Register
//      Bit     Field                       Description
//      31-4    Reverse
//      3-1     Level                       Cache level of required cache. 
//                                          Permitted values are from 0b000, indicating Level 1 cache, to 0b110 indicating Level 7 cache.
//      0       InD                         Instruction not Data bit:
//                                          0 = Data cache
//                                          1 = Instruction cache.
//      MRC p15, 2, <Rd>, c0, c0, 0 ; Read Cache Size Selection Register(CSSELR)
//      MCR p15, 2, <Rd>, c0, c0, 0 ; Write Cache Size Selection Register(CSSELR)
#define _ARM_CP_CSSELR_R(csselr) _ARM_CP_R(p15, 2, csselr, c0, c0, 0)
#define _ARM_CP_CSSELR_W(csselr) _ARM_CP_W(p15, 2, csselr, c0, c0, 0)

// Set/way
// [ref]DDI0406C_d_armv7ar_arm.pdf: B6.2.1 Cache and branch predictor maintenance operations, PMSA
//      Set/way
//      Bit         Field               Description
//      31-(32-A)   Way                 The way number of the line in the set
//      (31-A)-B    SBZ
//      (B-1)-L     Set                 The cache set the line belongs to
//      (L-1)-4     SBZ
//      3-1         Level               ((Cache level to operate on)¨C1). For example, this field is 0 for operations on L1 cache
//      0           0
//      Where:
//      A Is Log2(ASSOCIATIVITY), rounded up to the next integer if necessary.
//      B Is(L + S).
//      L Is Log2(LINELEN).
//      S Is Log2(NSETS), rounded up to the next integer if necessary

// Invalidate data cache
void rt_cpu_dcache_invalidate(void)
{
    uint32_t clidr;
    _ARM_DMB();
    _ARM_CP_CLIDR_R(clidr);
    uint32_t loc = _E_B_B(clidr, 26, 24);

    for (uint32_t i = 0; i < loc; i++, clidr >>= 3) {
        uint32_t ctype = clidr & 0x7;
        if (ctype >= 0b010) {
            uint32_t csselr = _L(i, 1);
            _ARM_CP_CSSELR_W(csselr); // Write Cache Size Selection Register
            _ARM_ISB();

            uint32_t setMask;
            uint32_t wayMask;
            uint32_t log2LineSize;
            armv7_cache_get_set_way(&setMask, &wayMask, &log2LineSize);

            uint32_t wayShift;
            _ARM_CLZ(wayShift, wayMask); // 32-A, A=Log2(ASSOCIATIVITY)
            int32_t sets = (int32_t)setMask;
            while (sets >= 0) {
                int32_t ways = wayMask;
                while (ways >= 0) {
                    uint32_t wayset = _L(ways, wayShift) | _L(sets, log2LineSize) | csselr; // ref Set/way
                    _ARM_CP_DCISW_W(wayset); // Invalidate data cache line by set/way
                    ways--;
                }
                sets--;
            }
        }
    }

    _ARM_DSB();
    _ARM_ISB();
}

// Clean data cache
void rt_cpu_dcache_clean(void)
{
    uint32_t clidr;
    _ARM_DMB();
    _ARM_CP_CLIDR_R(clidr);
    uint32_t loc = _E_B_B(clidr, 26, 24);

    for (uint32_t i = 0; i < loc; i++, clidr >>= 3) {
        uint32_t ctype = clidr & 0x7;
        if (ctype >= 0b010) {
            uint32_t csselr = _L(i, 1);
            _ARM_CP_CSSELR_W(csselr); // Write Cache Size Selection Register
            _ARM_ISB();

            uint32_t setMask;
            uint32_t wayMask;
            uint32_t log2LineSize;
            armv7_cache_get_set_way(&setMask, &wayMask, &log2LineSize);

            uint32_t wayShift;
            _ARM_CLZ(wayShift, wayMask); // 32-A, A=Log2(ASSOCIATIVITY)
            int32_t sets = (int32_t)setMask;
            while (sets >= 0) {
                int32_t ways = wayMask;
                while (ways >= 0) {
                    uint32_t wayset = _L(ways, wayShift) | _L(sets, log2LineSize) | csselr; // ref Set/way
                    _ARM_CP_DCCSW_W(wayset); // Clean data cache line by set/way
                    ways--;
                }
                sets--;
            }
        }
    }

    _ARM_DSB();
    _ARM_ISB();
}

// Clean&Invalidate data cache
void rt_cpu_dcache_clean_invalidate(void)
{
    uint32_t clidr;
    _ARM_DMB();
    _ARM_CP_CLIDR_R(clidr);
    uint32_t loc = _E_B_B(clidr, 26, 24);

    for (uint32_t i = 0; i < loc; i++, clidr >>= 3) {
        uint32_t ctype = clidr & 0x7;
        if (ctype >= 0b010) {
            uint32_t csselr = _L(i, 1);
            _ARM_CP_CSSELR_W(csselr); // Write Cache Size Selection Register
            _ARM_ISB();

            uint32_t setMask;
            uint32_t wayMask;
            uint32_t log2LineSize;
            armv7_cache_get_set_way(&setMask, &wayMask, &log2LineSize);

            uint32_t wayShift;
            _ARM_CLZ(wayShift, wayMask); // 32-A, A=Log2(ASSOCIATIVITY)
            int32_t sets = (int32_t)setMask;
            while (sets >= 0) {
                int32_t ways = wayMask;
                while (ways >= 0) {
                    uint32_t wayset = _L(ways, wayShift) | _L(sets, log2LineSize) | csselr; // ref set/way
                    _ARM_CP_DCCISW_W(wayset); // Clean and invalidate data cache line by set/way
                    ways--;
                }
                sets--;
            }
        }
    }

    _ARM_DSB();
    _ARM_ISB();
}

// Invalidate data cache line by MVA to PoC
void rt_cpu_dcache_invalidate_buf(const void* pBuf, uint32_t bufSize)
{
    uint32_t lineSize = armv7_dcache_get_line_size();

    uint32_t mvaLimit = RT_ALIGN_DOWN((uint32_t)pBuf + bufSize, lineSize);
    uint32_t mva = RT_ALIGN_DOWN((uint32_t)pBuf, lineSize);
    _ARM_CP_DCCIMVAC_W(mva); // Clean and invalidate data cache line by MVA to PoC
    if (mva != mvaLimit) {
        mva += lineSize;
        while (mva < mvaLimit) {
            _ARM_CP_DCIMVAC_W(mva); // Invalidate data cache line by MVA to PoC
            mva += lineSize;
        }
        _ARM_CP_DCCIMVAC_W(mva); // Clean and invalidate data cache line by MVA to PoC
    }

    _ARM_ISB();
    return;
}

// Clean data cache line by MVA to PoC
void rt_cpu_dcache_clean_buf(const void* pBuf, uint32_t bufSize)
{
    uint32_t lineSize = armv7_dcache_get_line_size();

    const void* pBufLimit = (const void *)((uint32_t)pBuf + bufSize);
    do {
        uint32_t mva = RT_ALIGN_DOWN((uint32_t)pBuf, lineSize);
        _ARM_CP_DCCMVAC_W(mva); // Clean data cache line by MVA to PoC
        pBuf = (const void *)((uint32_t)pBuf + lineSize);
    } while (pBuf < pBufLimit);

    _ARM_ISB();
    return;
}

// Clean and invalidate data cache line by MVA to PoC
void rt_cpu_dcache_clean_invalidate_buf(const void* pBuf, uint32_t bufSize)
{
    uint32_t lineSize = armv7_dcache_get_line_size();

    const void* pBufLimit = (const void *)((uint32_t)pBuf + bufSize);
    do {
        uint32_t mva = RT_ALIGN_DOWN((uint32_t)pBuf, lineSize);
        _ARM_CP_DCCIMVAC_W(mva); // Clean and invalidate data cache line by MVA to PoC
        pBuf = (const void *)((uint32_t)pBuf + lineSize);
    } while (pBuf < pBufLimit);

    _ARM_ISB();
    return;
}
