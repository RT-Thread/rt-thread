/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-05     Bernard      the first version
 */

    // [ref] 
    //   1) DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.3 c0, Cache Type Register
    //      Bit     Field                       Description
    //      31-28   0b1000
    //      27-24   Cache writeback granule     Log2 of the number of words of the maximum size of memory that can be overwritten as a result 
    //                                          of the eviction of a cache entry that has had a memory location within it modified
    //      23-20   Reverse
    //      19-16   DMinLine                    Number of words of smallest line length in L1 or L2 data cache
    //      15-14   L1 Ipolicy                  VIPT instruction cache support
    //      13-4    Reverse
    //      3-0     IMinLine                    Number of words of smallest line length in L1 or L2 instruction cache
    //      MRC p15, 0, <Rd>, c0, c0, 1 ; Read Cache Type Register
    //   2) DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c5  0           Invalidate all instruction caches to PoU. Also flushes branch target cache.     SBZ
    //      c5  1           Invalidate instruction cache line by MVA to PoC.                                MVA
    //      c5  4           Prefetch flush. The prefetch buffer is flushed.                                 SBZ
    //      c5  6           Invalidate entire branch predictor array.                                       SBZ
    //      c5  7           Invalidate MVA from branch predictor array                                      MVA
    //      c6  1           Invalidate Data or Unified cache line by MVA to PoC.                            MVA
    //      c6  2           Invalidate Data or Unified cache line by Set/Way.                               Set/Way
    //      c10 1           Clean Data or Unified cache line by MVA to PoC.                                 MVA
    //      c10 2           Clean Data or Unified cache line by Set/Way.                                    Set/Way
    //      c11 1           Clean Data or Unified cache line by MVA to PoU.                                 MVA
    //      c14 1           Clean and Invalidate Data or Unified cache line by MVA to PoC.                  MVA
    //      c14 2           Clean and Invalidate Data or Unified cache line by Set/Way.                     Set/Way
    //
    // icache invalidate by address
    // r0 - start address
    // r1 - byte number
    .globl  rt_cpu_icache_invalidate_buf
rt_cpu_icache_invalidate_buf:
    PUSH    {r14}
    ADD     r14, r0, r1                 // calculate end address
    DMB
    MRC     p15, #0, r2, c0, c0, #1     // Read Cache Type Register
    UBFX    r2, r2, #0, #4              // get IminLine(bit[3-0])
    MOV     r3, #2
    ADD     r3, r3, r2
    MOV     r2, #1
    LSL     r2, r2, r3                  // line size
   
    SUB     r3, r2, #1                  // mask
    BIC     r0, r0, r3                  // align down
    TST     r3, r14
    BIC     r14, r14, r3
    MCRNE   p15, #0, r14, c7, c5, #1    // Invalidate instruction cache line by MVA to PoC
iflushloop:
    MCR     p15, #0, r0, c7, c5, #1     // Invalidate instruction cache line by MVA to PoC
    ADDS    r0, r0, r2                  // next line
    CMP     r0, r14 
    BLT     iflushloop
 
    POP     {r14}
    DSB
    BX      lr

    // [ref]
    //   1) DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.21 c0, Cache Level ID Register
    //      Bit     Field                       Description
    //      31-30   Reverse
    //      29-27   LoU                         b001 = level of unification
    //      26-24   LoC                         b010 = level of coherency
    //      23-21   CL 8                        b000 = no cache at Cache Level (CL) 8
    //      20-18   CL 7                        b000 = no cache at CL 7
    //      17-15   CL 6                        b000 = no cache at CL 6
    //      14-12   CL 5                        b000 = no cache at CL 5
    //      11-9    CL 4                        b000 = no cache at CL 4
    //      8-6     CL 3                        b000 = no cache at CL 3
    //      5-3     CL 2                        b000 = no cache at CL 2
    //                                          b100 = unified cache at CL 2
    //      2-0     CL 1                        b011 = separate instruction and data cache at CL 1
    //      MRC p15, 1, <Rd>, c0, c0, 1 ; Read Cache Level ID Register
    //   2) DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.24 c0, Cache Size Selection Register
    //      Bit     Field                       Description
    //      31-4    Reverse
    //      3-1     Level                       Cache level selected
    //                                          b000 = level 1
    //                                          b001 = level 2
    //                                          b010 - b111 = reserved
    //      0       InD                         Instruction (1) or Data/Unified (0)
    //      MRC p15, 2, <Rd>, c0, c0, 0 ; Read Cache Size Selection Register
    //      MCR p15, 2, <Rd>, c0, c0, 0 ; Write Cache Size Selection Register
    //   3) DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.23 c0, Cache Size Identification Registers
    //      Bit     Field                       Description
    //      31      WT                          1 = write-through supported. 0 = not supported
    //      30      WB                          1 = write-back supported. 0 = not supported
    //      29      RA                          1 = read allocation supported. 0 = not supported
    //      28      WA                          1 = write allocation supported. 0 = not supported
    //      27-13   NumSets                     Indicates number of sets - 1
    //      12-3    Associativity               Indicates number of ways - 1
    //      2-0     LineSize                    Indicates (log2(number of words in cache line)) - 2.
    //      MRC p15, 1, <Rd>, c0, c0, 0; Cache Size Identification Register
    //
    // dcache invalidate by address
    // r0 - start address
    // r1 - byte number
    .globl  rt_cpu_dcache_invalidate
rt_cpu_dcache_invalidate:
    PUSH    {r4-r11}
    DMB
    MRC     p15, #1, r0, c0, c0, #1     // Read CLIDR
    ANDS    r3, r0, #0x7000000
    MOV     r3, r3, lsr #24             // LoC
    MOV     r3, r3, lsl #1
    BEQ     ffinished
    MOV     r10, #0
floop1:
    ADD     r2, r10, r10, lsr #1
    MOV     r1, r0, lsr r2
    AND     r1, r1, #7
    CMP     r1, #2
    BLT     fskip
    MCR     p15, #2, r10, c0, c0, #0    // Write Cache Size Selection Register
    ISB
    MRC     p15, #1, r1, c0, c0, #0     // Cache Size Identification Registers
    AND     r2, r1, #7                  // line size
    ADD     r2, r2, #4
    LDR     r4, _FLD_MAX_WAY
    ANDS    r4, r4, r1, lsr #3
    CLZ     r5, r4
    LDR     r7, _FLD_MAX_IDX
    ANDS    r7, r7, r1, lsr #13
floop2:
    MOV     r9, r4
floop3:
    ORR     r11, r10, r9, lsl r5
    ORR     r11, r11, r7, lsl r2
    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c6  2           Invalidate Data or Unified cache line by Set/Way.                               Set/Way
    MCR     p15, #0, r11, c7, c6, #2
    SUBS    r9, r9, #1
    BGE     floop3
    SUBS    r7, r7, #1
    BGE     floop2
fskip:
    ADD     r10, r10, #2
    CMP     r3, r10
    BGT     floop1

ffinished:
    DSB
    ISB
    POP     {r4-r11}
    BX      lr

    // dcache clean
    .globl  rt_cpu_dcache_clean
rt_cpu_dcache_clean:
    PUSH    {r4-r11}
    DMB
    MRC     p15, #1, r0, c0, c0, #1     // Read CLIDR
    ANDS    r3, r0, #0x7000000
    MOV     r3, r3, lsr #24             // LoC
    MOV     r3, r3, lsl #1
    BEQ     cfinished
    MOV     r10, #0
cloop1:
    ADD     r2, r10, r10, lsr #1
    MOV     r1, r0, lsr r2
    AND     r1, r1, #7
    CMP     r1, #2
    BLT     cskip
    MCR     p15, #2, r10, c0, c0, #0    // Write Cache Size Selection Register
    ISB
    MRC     p15, #1, r1, c0, c0, #0     // Cache Size Identification Registers
    AND     r2, r1, #7
    ADD     r2, r2, #4
    LDR     r4, _FLD_MAX_WAY
    ANDS    r4, r4, r1, lsr #3
    CLZ     r5, r4
    LDR     r7, _FLD_MAX_IDX
    ANDS    r7, r7, r1, lsr #13
cloop2:
    MOV     r9, r4
cloop3:
    ORR     r11, r10, r9, lsl r5
    ORR     r11, r11, r7, lsl r2
    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c10 2           Clean Data or Unified cache line by Set/Way.                                    Set/Way
    MCR     p15, #0, r11, c7, c10, #2
    SUBS    r9, r9, #1
    BGE     cloop3
    SUBS    r7, r7, #1
    BGE     cloop2
cskip:
    ADD     r10, r10, #2
    CMP     r3, r10
    BGT     cloop1

cfinished:
    DSB
    ISB
    POP     {r4-r11}
    BX      lr

    // dcache clean and invalidate
    .globl  rt_cpu_dcache_clean_invalidate
rt_cpu_dcache_clean_invalidate:
    PUSH    {r4-r11} 
    DMB
    MRC     p15, #1, r0, c0, c0, #1     // Read CLIDR
    ANDS    r3, r0, #0x7000000
    MOV     r3, r3, lsr #24             // LoC
    MOV     r3, r3, lsl #1
    BEQ     finished
    MOV     r10, #0 
loop1:
    ADD     r2, r10, r10, lsr #1 
    MOV     r1, r0, lsr r2
    AND     r1, r1, #7 
    CMP     r1, #2  
    BLT     skip 
    MCR     p15, #2, r10, c0, c0, #0    // Write Cache Size Selection Register
    ISB 
    MRC     p15, #1, r1, c0, c0, #0     // Cache Size Identification Registers
    AND     r2, r1, #7 
    ADD     r2, r2, #4   
    LDR     r4, _FLD_MAX_WAY 
    ANDS    r4, r4, r1, lsr #3
    CLZ     r5, r4
    LDR     r7, _FLD_MAX_IDX
    ANDS    r7, r7, r1, lsr #13 
loop2:
    MOV     r9, r4   
loop3:
    ORR     r11, r10, r9, lsl r5  
    ORR     r11, r11, r7, lsl r2 
    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c14 2           Clean and Invalidate Data or Unified cache line by Set/Way.                     Set/Way
    MCR     p15, #0, r11, c7, c14, #2
    SUBS    r9, r9, #1 
    BGE     loop3 
    SUBS    r7, r7, #1 
    BGE     loop2 
skip:
    ADD     r10, r10, #2 
    CMP     r3, r10 
    BGT     loop1 

finished:
    DSB
    ISB                        
    POP     {r4-r11} 
    BX      lr
_FLD_MAX_WAY:
    .word   0x3ff
_FLD_MAX_IDX:
    .word   0x7ff

    // dcache invalidate by address
    // r0 - start address
    // r1 - byte number
    .globl  rt_cpu_dcache_invalidate_buf
rt_cpu_dcache_invalidate_buf:
    PUSH    {r14}
    ADD     r14, r0, r1                 // cal end address
    DMB
    MRC     p15, #0, r2, c0, c0, #1     // Read Cache Type Register
    UBFX    r2, r2, #16, #4             // get DminLine(bit[19-16])
    MOV     r3, #2
    ADD     r3, r3, r2
    MOV     r2, #1
    LSL     r2, r2, r3                  // line size
   
    SUB     r3, r2, #1                  // mask
    TST     r3, r0 
    BIC     r0, r0, r3                  // align down
    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c6  2           Invalidate Data or Unified cache line by Set/Way.                               Set/Way
    MCRNE   p15, #0, r0, c7, c6, #2
    ADDNE   r0, r0, r2
    TST     r3, r14 
    BIC     r14, r14, r3              
    MCRNE   p15, #0, r14, c7, c6, #2
    B       dflushcmp

dflushloop:
    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c6  1           Invalidate Data or Unified cache line by MVA to PoC.                            MVA
    MCR     p15, #0, r0 , c7, c6, #1
    ADDS    r0, r0, r2                  // next line

dflushcmp:
    CMP     r0, r14
    BLT     dflushloop
    POP     {r14}
    DSB
    BX      lr

    // dcache clean by address
    // r0 - start address
    // r1 - byte number
    .globl  rt_cpu_dcache_clean_buf
rt_cpu_dcache_clean_buf:
    PUSH    {r14}
    ADD     r14, r0, r1                 // cal end address
    DMB
    MRC     p15, #0, r2, c0, c0, #1     // Read Cache Type Register
    UBFX    r2, r2, #16, #4             // get DminLine(bit[19-16])
    MOV     r3, #2
    ADD     r3, r3, r2
    MOV     r2, #1
    LSL     r2, r2, r3                  // line size
   
    SUB     r3, r2, #1                  // mask
    BIC     r0, r0, r3                  // align down
    TST     r3, r14
    BIC     r14, r14, r3
    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c10 1           Clean Data or Unified cache line by MVA to PoC.                                 MVA
    MCRNE   p15, #0, r14, c7, c10, #1

cleanloop:
    MCR     p15, #0, r0 , c7, c10, #1
    ADDS    r0, r0, r2                  // next line
    CMP     r0, r14 
    BLT     cleanloop
 
    POP     {r14}
    DSB
    BX      lr

    // dcache clean and invalidate by address
    // r0 - start address
    // r1 - byte number
    .globl  rt_cpu_dcache_clean_invalidate_buf
rt_cpu_dcache_clean_invalidate_buf:
    PUSH    {r14}
    ADD     r14, r0, r1                 // cal end address
    DMB
    MRC     p15, #0, r2, c0, c0, #1     // Read Cache Type Register
    UBFX    r2, r2, #16, #4             // get DminLine(bit[19-16])
    MOV     r3, #2
    ADD     r3, r3, r2
    MOV     r2, #1
    LSL     r2, r2, r3                  // line size
   
    SUB     r3, r2, #1                  // mask
    BIC     r0, r0, r3                  // align down
    TST     r3, r14
    BIC     r14, r14, r3
    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c14 1           Clean and Invalidate Data or Unified cache line by MVA to PoC.                  MVA
    MCRNE   p15, #0, r14, c7, c14, #1

cleanflushloop:
    MCR     p15, #0, r0 , c7, c14, #1
    ADDS    r0, r0, r2                  // next line
    CMP     r0, r14 
    BLT     cleanflushloop
 
    POP     {r14}
    DSB
    BX      lr

    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.2 c0, Main ID Register
    //      Bit     Field                       Description
    //      31-24   Implementor                 Indicates the implementor, ARM:0x41.
    //      23-20   Variant                     Indicates the variant number, or major revision, of the processor:0x3.
    //      19-16   Architecture                Indicates that the architecture is given in the feature registers:0xF.
    //      15-4    Primary part number         Indicates the part number, Cortex-A8:0xC08.
    //      3-0     Revision                    Indicates the revision number, or minor revision, of the processor:0x2.
    //      MRC p15, 0, <Rd>, c0, c0, 0 ; Read Main ID Register
    //
    // get Main ID Register(midr)
    .globl  rt_cpu_midr_get
rt_cpu_midr_get:
    MRC     p15, #0, r0, c0, c0, #0
    UBFX    r0, r0, #4, #12             // pick bit[15-4](12 bits), bit[15-4]: Primary part number
    BX      lr
_CPUMAINID:
    .word   0x80C                       // value of Main ID Register

    // all cache disable
    .globl  rt_cpu_cache_disable
rt_cpu_cache_disable:
    PUSH    {r4-r11, lr}
    BL      rt_cpu_branch_prediction_disable
    BL      rt_cpu_icache_disable
    BL      rt_cpu_dcache_disable
    BL      rt_cpu_midr_get
    LDR     r1, _CPUMAINID 
    CMP     r0, r1
    MOVEQ   r0, #2                      // L2EN
    BLEQ    rt_cpu_auxctl_feature_disable
    POP     {r4-r11, lr}
    BX      lr

    // all cache enable
    .globl  rt_cpu_cache_enable
rt_cpu_cache_enable:
    PUSH    {r4-r11, lr}
    BL      rt_cpu_icache_enable
    BL      rt_cpu_midr_get
    LDR     r1, _CPUMAINID 
    CMP     r0, r1
    MOVEQ   r0, #2                      // L2EN
    BLEQ    rt_cpu_auxctl_feature_enable
    BL      rt_cpu_dcache_invalidate
    BL      rt_cpu_dcache_enable
    BL      rt_cpu_branch_prediction_enable
    POP     {r4-r11, lr}
    BX      lr

    // [ref] DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.33 c2, Translation Table Base Control Register
    //      Bit     Field           Description
    //      31-6    Reverse
    //      5       PD1             Specifies occurrence of a translation table walk on a TLB miss when using Translation Table Base Register 1.
    //      4       PD0             Specifies occurrence of a translation table walk on a TLB miss when using Translation Table Base Register 0.
    //      3       Reverse
    //      2-0     N               Specifies the boundary size of Translation Table Base Register 0:
    //                              b000 = 16KB, reset value
    //                              b001 = 8KB
    //                              b010 = 4KB
    //                              b011 = 2KB
    //                              b100 = 1KB
    //                              b101 = 512B
    //                              b110 = 256B
    //                              b111 = 128B
    //      MRC p15, 0, <Rd>, c2, c0, 2 ; Read Translation Table Base Control Register
    //      MCR p15, 0, <Rd>, c2, c0, 2 ; Write Translation Table Base Control Register
    // [ref] DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.31 c2, Translation Table Base Register 0
    //      Bit         Field                       Description
    //      31-(14-N)   Translation table base 0    Holds the translation table base address, the physical address of the first level translation table.
    //      (13-N)-5    Reverse
    //      4-3         RGN                         Indicates the outer cacheable attributes for translation table walking:
    //                                              b00 = outer noncacheable
    //                                              b01 = write-back, write allocate
    //                                              b10 = write-through, no allocate on write
    //                                              b11 = write-back, no allocate on write.
    //      MRC p15, 0, <Rd>, c2, c0, 0 ; Read Translation Table Base Register
    //      MCR p15, 0, <Rd>, c2, c0, 0 ; Write Translation Table Base Register
    //
    // set translation table base
    .globl  rt_cpu_tlb_set
rt_cpu_tlb_set:
    MOV     r1, #0
    MCR     p15, #0, r1, c2, c0, #2
    DSB
    BIC     r0, r0, #0x00FF
    BIC     r0, r0, #0x3F00
    ORR     r0, r0, #(0x1 << 3)
    MCR     p15, #0, r0, c2, c0, #0
    DMB
    BX      lr

    // [ref] DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.41 c8, TLB operations
    //      MCR p15, 0, <Rd>, c8, c5, 0 ; Invalidate Inst-TLB
    //      MCR p15, 0, <Rd>, c8, c5, 1 ; Invalidate Inst-TLB entry (MVA)
    //      MCR p15, 0, <Rd>, c8, c5, 2 ; Invalidate Inst-TLB (ASID)
    //      MCR p15, 0, <Rd>, c8, c6, 0 ; Invalidate Data-TLB
    //      MCR p15, 0, <Rd>, c8, c6, 1 ; Invalidate Data-TLB entry (MVA)
    //      MCR p15, 0, <Rd>, c8, c6, 2 ; Invalidate Data-TLB (ASID)
    //      MCR p15, 0, <Rd>, c8, c7, 0 ; Invalidate Inst-TLB and Data-TLB
    //      MCR p15, 0, <Rd>, c8, c7, 1 ; Invalidate Inst-TLB and Data-TLB entry (MVA)
    //      MCR p15, 0, <Rd>, c8, c7, 2 ; Invalidate Inst-TLB and Data-TLB (ASID)
    //
    // Invalidate Inst-TLB and Data-TLB
    .globl  rt_cpu_tlb_invalidate
rt_cpu_tlb_invalidate:
    MCR     p15, #0, r0, c8, c7, #0
    DSB
    BX      lr

    // [ref] DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.68 c12, Secure or Nonsecure Vector Base Address Register
    //      Bit     Field                   Description
    //      31-5    Vector base address     Holds the base address
    //      4-0     Reverse
    .globl  rt_cpu_vector_set_base
rt_cpu_vector_set_base:
    MCR     p15, #0, r0, c12, c0, #0
    DSB
    BX      lr

    // [ref] DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.34 c3, Domain Access Control Register
    //      Bit         Field           Description
    //      (2n+1)-2n   Dn(n=15-0)      0b00 = No access. Any access generates a domain fault
    //                                  0b01 = Client. Accesses are checked against the access permission bits in the TLB entry.
    //                                  0b10 = Reserved. Any access generates a domain fault
    //                                  0b11 = Manager. not generate an abort
    //
    // D15-D0: set client access(Accesses are checked against the access permission bits in the TLB entry)
    .globl  rt_cpu_domain_access_client_set
rt_cpu_domain_access_client_set:
    LDR     r0, _CLIENTD 
    MCR     p15, #0, r0, c3, c0, #0
    DSB
    BX      lr
_CLIENTD:
    .word   0x55555555

    // [ref] DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.25 c1, Control Register
    //      Bit     Field           Description
    //      31      reverse
    //      30      TE              0/1 = Enables ARM/Thumb exception generation
    //      29      AFE             0 = AP[0] behavior defined; 1 = access flag behavior defined
    //      28      TRE             0/1 = TEX remap disabled/enable
    //      27      NMFI            0/1 = FIQ exceptions can/cannot be masked by software
    //      26      reverse
    //      25      EE              0/1 = CPSR E bit is set to 0/1 on an exception
    //      24-14   reverse
    //      13      V               0/1 = Normal/High exception vectors selected
    //      12      I               0/1 = instruction caching disabled/enable
    //      11      Z               0/1 = program flow prediction disabled/enable
    //      10-3    reverse         
    //      2       C               0/1 = data caching disabled/enable
    //      1       A               0/1 = strict alignment fault checking disabled/enabled
    //      0       M               0/1 = MMU disabled/enable
    //
    // get cpu feature from control register
    .globl  rt_cpu_ctl_feature_get
rt_cpu_ctl_feature_get:
    MRC     p15, #0, r0, c1, c0, #0 
    BX      lr
    // disable cpu feature
    .globl  rt_cpu_ctl_feature_disable
rt_cpu_ctl_feature_disable:
    MRC     p15, #0, r1, c1, c0, #0 
    BIC     r0, r1, r0  
    MCR     p15, #0, r0, c1, c0, #0
    DSB
    BX      lr
    // enable cpu feature
    .globl  rt_cpu_ctl_feature_enable
rt_cpu_ctl_feature_enable:
    MRC     p15, #0, r1, c1, c0, #0 
    ORR     r0, r1, r0  
    MCR     p15, #0, r0, c1, c0, #0
    DSB
    BX      lr

    // mmu disable
    .globl  rt_cpu_mmu_disable
rt_cpu_mmu_disable:
    PUSH    {lr}
    MOV     r0, #1      // bit0(M)
    BL      rt_cpu_ctl_feature_disable
    POP     {lr}
    BX      lr
    // mmu enable
    .globl  rt_cpu_mmu_enable
rt_cpu_mmu_enable:
    PUSH    {lr}
    MOV     r0, #1      // bit0(M)
    BL      rt_cpu_ctl_feature_enable
    POP     {lr}
    BX      lr

    // Invalidate entire branch predictor array
_branch_prediction_invalidate:
    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c5  6           Invalidate entire branch predictor array.                                       SBZ
    MCR     p15, #0, r0, c7, c5, #6
    ISB
    BX      lr

    // program flow prediction disable
    .globl  rt_cpu_branch_prediction_disable
rt_cpu_branch_prediction_disable:
    PUSH    {lr}
    MOV     r0, #0x00000800      // bit11(Z)
    BL      rt_cpu_ctl_feature_disable
    BL      _branch_prediction_invalidate
    POP     {lr}
    BX      lr
    // program flow prediction enable
    .globl  rt_cpu_branch_prediction_enable
rt_cpu_branch_prediction_enable:
    PUSH    {lr}
    MOV     r0, #0x00000800      // bit11(Z)
    BL      rt_cpu_ctl_feature_enable
    POP     {lr}
    BX      lr

    // Invalidate all instruction caches to PoU. Also flushes branch target cache
_icache_invalidate:
    MOV     r0, #0
    // [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.40 c7, Cache operations
    //      CRm Opcode_2    Function                                                                        Data
    //      c5  0           Invalidate all instruction caches to PoU. Also flushes branch target cache.     SBZ
    MCR     p15, #0, r0, c7, c5, #0
    DSB
    BX      lr

    // instruction caching disabled
    .globl  rt_cpu_icache_disable
rt_cpu_icache_disable:
    PUSH    {lr}
    MOV     r0, #0x00001000      // bit12(I)
    BL      rt_cpu_ctl_feature_disable
    BL      _icache_invalidate
    POP     {lr}
    BX      lr
    // instruction caching enable
    .globl  rt_cpu_icache_enable
rt_cpu_icache_enable:
    PUSH    {lr}
    MOV     r0, #0x00001000      // bit12(I)
    BL      rt_cpu_ctl_feature_enable
    POP     {lr}
    BX      lr

    // data caching disabled
    .globl  rt_cpu_dcache_disable
rt_cpu_dcache_disable:
    PUSH    {lr}
    MOV     r0, #0x00000004      // bit2(C)
    BL      rt_cpu_ctl_feature_disable
    BL      rt_cpu_dcache_clean_invalidate
    POP     {lr}
    BX      lr

    // data caching enable
    .globl  rt_cpu_dcache_enable
rt_cpu_dcache_enable:
    PUSH    {lr}
    MOV     r0, #0x00000004      // bit2(C)
    BL      rt_cpu_ctl_feature_enable
    POP     {lr}
    BX      lr

    // [ref] DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.26 c1, Auxiliary Control Register
    //      Bit     Field                                   Description
    //      31      L2 hardware reset disable               the L2 valid RAM contents are not reset by hardware
    //      30      L1 hardware reset disable               the L1 valid RAM contents are not reset by hardware
    //      29-21   reverse
    //      20      Cache maintenance pipeline              non-pipelined cache maintenance operations
    //      19      Clock stop request disable              disables the CLKSTOPREQ functionality
    //      18      CP14/CP15 instruction serialization     enforces serialization of CP14 and CP15 instructions
    //      17      CP14/CP15 wait on idle                  enforces wait on idle for serialized CP14 or CP15 instructions
    //      16      CP14/CP15 pipeline flush                imposes a pipeline flush on CP14 and CP15 instructions
    //      15      Force ETM clock                         Forces ETM clock enable active
    //      14      Force NEON clock                        Forces NEON clock enable active
    //      13      Force main clock                        Forces the main processor clock enable active
    //      12      Force NEON single issue                 Forces single issue of Advanced SIMD instructions
    //      11      Force load/store single issue           Forces single issue of load/store instructions
    //      10      Force single issue                      Forces single issue of all instructions
    //      9       PLDNOP                                  PLD instructions are executed as NOP instructions
    //      8       WFINOP                                  executes WFI instructions as NOP instruction
    //      7       Disable branch size mispredicts         executes the CP15 Invalidate All and Invalidate by MVA instructions as specified and prevents BTB branch size mispredicts.
    //      6       IBE                                     executes the CP15 Invalidate All and Invalidate by MVA instructions as specified
    //      5       L1NEON                                  enables caching NEON data within the L1 data and L2 cache
    //      4       ASA                                     enables speculative accesses
    //      3       L1PE                                    L1 cache parity enabled
    //      2       reverse
    //      1       L2EN                                    L2 cache enabled
    //      0       L1ALIAS                                 L1 data cache hardware alias support disabled
    .globl  rt_cpu_auxctl_feature_enable
rt_cpu_auxctl_feature_enable:
    MRC     p15, #0, r1, c1, c0, #1
    ORR     r0,  r0, r1
    MCR     p15, #0, r0, c1, c0, #1
    DSB
    BX      lr
    .globl  rt_cpu_auxctl_feature_disable
rt_cpu_auxctl_feature_disable:
    MRC     p15, #0, r1, c1, c0, #1
    BIC     r0,  r1, r0
    MCR     p15, #0, r0, c1, c0, #1
    DSB
    BX      lr
