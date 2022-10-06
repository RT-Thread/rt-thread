@******************************************************************************
@
@ cp15.S - CP15 coprocesser configuration APIs
@
@******************************************************************************
@
@ Copyright (C) 2010 Texas InSTRuments Incorporated - http://www.ti.com/
@
@
@  RediSTRibution and use in source and binary forms, with or without
@  modification, are permitted provided that the following conditions
@  are met:
@
@    RediSTRibutions of source code must retain the above copyright
@    notice, this list of conditions and the following disclaimer.
@
@    RediSTRibutions in binary form must reproduce the above copyright
@    notice, this list of conditions and the following disclaimer in the
@    documentation and/or other materials provided with the
@    diSTRibution.
@
@    Neither the name of Texas InSTRuments Incorporated nor the names of
@    its contributors may be used to endorse or promote products derived
@    from this software without specific prior written permission.
@
@  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
@  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
@  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
@  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
@  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
@  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
@  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
@  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
@  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
@  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
@  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
@
@******************************************************************************

@****************************** Global Symbols*********************************
        .global CP15ICacheDisable
        .global CP15DCacheDisable
        .global CP15ICacheEnable
        .global CP15DCacheEnable
        .global CP15ICacheFlush
        .global CP15DCacheCleanFlush
        .global CP15DCacheClean
        .global CP15DCacheFlush
        .global CP15DCacheCleanBuff
        .global CP15DCacheCleanFlushBuff
        .global CP15DCacheFlushBuff
        .global CP15ICacheFlushBuff
        .global CP15Ttb0Set
        .global CP15TlbInvalidate
        .global CP15MMUDisable
        .global CP15MMUEnable
        .global CP15VectorBaseAddrSet
        .global CP15BranchPredictorInvalidate
        .global CP15BranchPredictionEnable
        .global CP15BranchPredictionDisable
        .global CP15DomainAccessClientSet
        .global CP15ControlFeatureDisable
        .global CP15ControlFeatureEnable
        .global CP15TtbCtlTtb0Config
        .global CP15AuxControlFeatureEnable
        .global CP15AuxControlFeatureDisable
        .global CP15MainIdPrimPartNumGet

@**************************** Code section ************************************
        .text

        @ This code is assembled for ARM instructions
        .code 32


@*****************************************************************************
@ This API disable the InSTRuction cache.
@*****************************************************************************
CP15ICacheDisable:
    PUSH    {lr}
    MRC     p15, #0, r0, c1, c0, #0
    BIC     r0,  r0, #0x00001000
    MCR     p15, #0, r0, c1, c0, #0
    BL      CP15ICacheFlush
    POP     {lr}
    BX      lr

@*****************************************************************************
@ This API disable the Data cache.
@*****************************************************************************
CP15DCacheDisable:
    PUSH    {r4-r11, lr}
    MRC     p15, #0, r0, c1, c0, #0
    BIC     r0,  r0, #0x00000004
    MCR     p15, #0, r0, c1, c0, #0
    BL      CP15DCacheCleanFlush
    POP     {r4-r11, lr}
    BX      lr

@*****************************************************************************
@ This API enables I-cache
@*****************************************************************************
CP15ICacheEnable:
    MRC     p15, #0, r0, c1, c0, #0
    ORR     r0,  r0, #0x00001000
    MCR     p15, #0, r0, c1, c0, #0 
    BX      lr

@*****************************************************************************
@ This API enable the Data cache.
@*****************************************************************************
CP15DCacheEnable:
    MRC     p15, #0, r0, c1, c0, #0 
    ORR     r0,  r0, #0x00000004
    MCR     p15, #0, r0, c1, c0, #0
    BX      lr

@*****************************************************************************
@ This API Invalidates the entire Data/Unified Cache
@*****************************************************************************
CP15DCacheFlush:
    PUSH    {r4-r11}
    DMB
    MRC     p15, #1, r0, c0, c0, #1  @ Read CLID register
    ANDS    r3, r0, #0x7000000       @ Get Level of Coherency
    MOV     r3, r3, lsr #23
    BEQ     ffinished
    MOV     r10, #0
floop1:
    ADD     r2, r10, r10, lsr #1
    MOV     r1, r0, lsr r2
    AND     r1, r1, #7
    CMP     r1, #2
    BLT     fskip
    MCR     p15, #2, r10, c0, c0, #0
    ISB
    MRC     p15, #1, r1, c0, c0, #0
    AND     r2, r1, #7
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


@*****************************************************************************
@ This API cleans the entire D Cache to PoC
@*****************************************************************************
CP15DCacheClean:
    PUSH    {r4-r11}
    DMB
    MRC     p15, #1, r0, c0, c0, #1  @ Read CLID register
    ANDS    r3, r0, #0x7000000       @ Get Level of Coherency
    MOV     r3, r3, lsr #23
    BEQ     cfinished
    MOV     r10, #0
cloop1:
    ADD     r2, r10, r10, lsr #1
    MOV     r1, r0, lsr r2
    AND     r1, r1, #7
    CMP     r1, #2
    BLT     cskip
    MCR     p15, #2, r10, c0, c0, #0
    ISB
    MRC     p15, #1, r1, c0, c0, #0
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

@*****************************************************************************
@ This API cleans and invalidates the entire D Cache to PoC
@*****************************************************************************
CP15DCacheCleanFlush:
    PUSH    {r4-r11} 
    DMB
    MRC     p15, #1, r0, c0, c0, #1  @ Read CLID register
    ANDS    r3, r0, #0x7000000       @ Get Level of Coherency
    MOV     r3, r3, lsr #23  
    BEQ     finished  
    MOV     r10, #0 
loop1:
    ADD     r2, r10, r10, lsr #1 
    MOV     r1, r0, lsr r2
    AND     r1, r1, #7 
    CMP     r1, #2  
    BLT     skip 
    MCR     p15, #2, r10, c0, c0, #0 
    ISB 
    MRC     p15, #1, r1, c0, c0, #0 
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

@*****************************************************************************
@ This API invalidates entire I Cache
@*****************************************************************************
CP15ICacheFlush:
    MOV     r0, #0
    MCR     p15, #0, r0, c7, c5, #0
    DSB
    BX      lr

@*****************************************************************************
@ This API cleans the D-cache/Unified  lines corresponding to the buffer 
@ pointer upto the specified length to PoC.
@ r0 - Start Address 
@ r1 - Number of bytes to be cleaned
@*****************************************************************************
CP15DCacheCleanBuff:
    PUSH    {r14}
    ADD     r14, r0, r1               @ Calculate the end address
    DMB
    MRC     p15, #0, r2, c0, c0, #1   @ Read Cache Type Register
    UBFX    r2, r2, #16, #4           @ Extract the DMinLine
    MOV     r3, #2
    ADD     r3, r3, r2
    MOV     r2, #1
    LSL     r2, r2, r3                @ Calculate the line size
   
    SUB     r3, r2, #1                @ Calculate the mask
    BIC     r0, r0, r3                @ Align to cache line boundary   
    TST     r3, r14
    BIC     r14, r14, r3
    MCRNE   p15, #0, r14, c7, c10, #1 @ Clean D/Unified to PoC by MVA

cleanloop:    
    MCR     p15, #0, r0 , c7, c10, #1 @ Clean D/Unified to PoC by MVA
    ADDS    r0, r0, r2                @ Go to next line
    CMP     r0, r14 
    BLT     cleanloop
 
    POP     {r14}
    DSB
    BX      lr

@*****************************************************************************
@ This API cleans and invalidates the D-cache/Unified  lines corresponding to 
@ the buffer pointer upto the specified length to PoC.
@ r0 - Start Address 
@ r1 - Number of bytes to be cleaned and flushed
@*****************************************************************************
CP15DCacheCleanFlushBuff:
    PUSH    {r14}
    ADD     r14, r0, r1               @ Calculate the end address
    DMB
    MRC     p15, #0, r2, c0, c0, #1   @ Read Cache Type Register
    UBFX    r2, r2, #16, #4           @ Extract the DMinLine
    MOV     r3, #2
    ADD     r3, r3, r2
    MOV     r2, #1
    LSL     r2, r2, r3                @ Calculate the line size
   
    SUB     r3, r2, #1                @ Calculate the mask
    BIC     r0, r0, r3                @ Align to cache line boundary   
    TST     r3, r14
    BIC     r14, r14, r3
    MCRNE   p15, #0, r14, c7, c14, #1 @ Clean and Flush D/U line to PoC

cleanflushloop:    
    MCR     p15, #0, r0 , c7, c14, #1 @ Clean and Flush D/U line to PoC 
    ADDS    r0, r0, r2                @ Go to next line
    CMP     r0, r14 
    BLT     cleanflushloop
 
    POP     {r14}
    DSB
    BX      lr

@*****************************************************************************
@ This API invalidates the D-cache/Unified  lines corresponding to 
@ the buffer pointer upto the specified length to PoC.
@ r0 - Start Address 
@ r1 - Number of bytes to be flushed
@*****************************************************************************
CP15DCacheFlushBuff:
    PUSH    {r14}
    ADD     r14, r0, r1               @ Calculate the end address
    DMB
    MRC     p15, #0, r2, c0, c0, #1   @ Read Cache Type Register
    UBFX    r2, r2, #16, #4           @ Extract the DMinLine
    MOV     r3, #2
    ADD     r3, r3, r2
    MOV     r2, #1
    LSL     r2, r2, r3                @ Calculate the line size
   
    SUB     r3, r2, #1                @ Calculate the mask
    TST     r3, r0 
    BIC     r0, r0, r3                @ Align to cache line boundary   
    MCRNE   p15, #0, r0, c7, c14, #1  @ Clean and Flush D/U line to PoC 
    ADDNE   r0, r0, r2
    TST     r3, r14 
    BIC     r14, r14, r3              
    MCRNE   p15, #0, r14, c7, c14, #1 @ Clean and Flush D/U line to PoC 
    B       dflushcmp

dflushloop:
    MCR     p15, #0, r0 , c7, c6, #1  @ Flush D/U line to PoC    
    ADDS    r0, r0, r2                @ Go to next line

dflushcmp:
    CMP     r0, r14
    BLT     dflushloop
    POP     {r14}
    DSB
    BX      lr

@*****************************************************************************
@ This API invlidates I-cache lines from the star address till the length   
@ specified to PoU.
@ r0 - Start Address 
@ r1 - Number of bytes to be cleaned
@*****************************************************************************
CP15ICacheFlushBuff:
    PUSH    {r14}
    ADD     r14, r0, r1               @ Calculate the end address
    DMB
    MRC     p15, #0, r2, c0, c0, #1   @ Read Cache Type Register
    UBFX    r2, r2, #0, #4            @ Extract the DMinLine
    MOV     r3, #2
    ADD     r3, r3, r2
    MOV     r2, #1
    LSL     r2, r2, r3                @ Calculate the line size
   
    SUB     r3, r2, #1                @ Calculate the mask
    BIC     r0, r0, r3                @ Align to cache line boundary   
    TST     r3, r14
    BIC     r14, r14, r3
    MCRNE   p15, #0, r14, c7, c5, #1  @ Invalidate by MVA to PoU

iflushloop:    
    MCR     p15, #0, r0, c7, c5, #1   @ Invalidate by MVA to PoU
    ADDS    r0, r0, r2                @ Go to next line
    CMP     r0, r14 
    BLT     iflushloop
 
    POP     {r14}
    DSB
    BX      lr

@*****************************************************************************
@ Sets TTB0 Register
@ r0 - Translation Table Base Address
@*****************************************************************************
CP15Ttb0Set:
    MCR     p15, #0, r0, c2, c0, #0
    DMB
    BX      lr

@*****************************************************************************
@ This API Invalidates the TLB
@*****************************************************************************
CP15TlbInvalidate:
    MCR     p15, #0, r0, c8, c7, #0    @ r0 value will be ignored
    DSB
    BX      lr

@*****************************************************************************
@ This API Disables MMU. 
@*****************************************************************************
CP15MMUDisable:
    MCR     p15, #0, r0, c8, c7, #0    @ Invalidate TLB  
    MRC     p15, #0, r0, c1, c0, #0    
    BIC     r0, r0, #1      
    MCR     p15, #0, r0, c1, c0, #0    @ Clear MMU bit
    DSB  
    BX      lr

@*****************************************************************************
@ This API Enables MMU. 
@*****************************************************************************
CP15MMUEnable:
    MRC     p15, #0, r0, c1, c0, #0
    ORR     r0, r0, #0x001
    MCR     p15, #0, r0, c1, c0, #0    @ Set MMU Enable bit
    DSB
    BX      lr

@*****************************************************************************
@ This API sets the interrupt vector table base address 
@ r0 - Interrput Vector Base Address
@*****************************************************************************
CP15VectorBaseAddrSet:
    MCR     p15, #0, r0, c12, c0, #0
    DSB
    BX      lr

@*****************************************************************************
@ This API invalidates the branch predictor 
@*****************************************************************************
CP15BranchPredictorInvalidate:
    MCR     p15, #0, r0, c7, c5, #6
    ISB
    BX      lr

@*****************************************************************************
@ This API enables the branch predictor 
@*****************************************************************************
CP15BranchPredictionEnable:
    MRC     p15, #0, r0, c1, c0, #0
    ORR     r0, r0, #0x00000800
    MCR     p15, #0, r0, c1, c0, #0
    BX      lr

@*****************************************************************************
@ This API disables the branch predictor 
@*****************************************************************************
CP15BranchPredictionDisable:
    MRC     p15, #0, r0, c1, c0, #0
    BIC     r0, r0, #0x00000800
    MCR     p15, #0, r0, c1, c0, #0
    BX      lr

@*****************************************************************************
@ This API sets the domain access to 'client' 
@*****************************************************************************
CP15DomainAccessClientSet:
    LDR     r0, _CLIENTD 
    MCR     p15, #0, r0, c3, c0, #0
    DSB
    BX      lr


@*****************************************************************************
@ This API Disables specified features in CP15 control register
@  r0 -  features   Features to disable in Coprocessor 15 control
@                       register. 
@               'features' can take any OR a combination of the
@               below  values. 
@                CP15_CONTROL_TEXREMAP - TEX remap flag 
@                CP15_CONTROL_ACCESSFLAG - Access flag Control 
@                CP15_CONTROL_ALIGN_CHCK - Alignment Fault Checking 
@                CP15_CONTROL_MMU - To enable MMU 
@ 
@ Note: Other fields of the CP15 c1 control register are not given here
@       as they are not of importance for StarterWare. However, optionally
@       they can also be ADDed.
@
@*****************************************************************************
CP15ControlFeatureDisable:
    MRC     p15, #0, r1, c1, c0, #0 
    BIC     r0, r1, r0  
    MCR     p15, #0, r0, c1, c0, #0
    DSB
    BX      lr

@*****************************************************************************
@ This API Enables specified features in CP15 control register
@  r0 -  features   Features to disable in Coprocessor 15 control
@                       register. 
@               'features' can take any OR a combination of the
@               below  values. 
@                CP15_CONTROL_TEXREMAP - TEX remap flag 
@                CP15_CONTROL_ACCESSFLAG - Access flag Control 
@                CP15_CONTROL_ALIGN_CHCK - Alignment Fault Checking 
@                CP15_CONTROL_MMU - To enable MMU 
@ 
@ Note: Other fields of the CP15 c1 control register are not given here
@       as they are not of importance for StarterWare. However, optionally
@       they can also be ADDed.
@
@*****************************************************************************
CP15ControlFeatureEnable:
    MRC     p15, #0, r1, c1, c0, #0 
    ORR     r0, r1, r0  
    MCR     p15, #0, r0, c1, c0, #0
    DSB
    BX      lr

@*****************************************************************************
@ This API Configures the TTB control register to use only TTB0
@*****************************************************************************
CP15TtbCtlTtb0Config:
    MOV     r0, #0x0
    MCR     p15, #0, r0, c2, c0, #2
    DSB
    BX      lr

@*****************************************************************************
@ This API Sets the specified fields in Auxiliary Control Register
@ r0 - Bit Mask for the bits to be set in Auxiliary Control Register
@*****************************************************************************
CP15AuxControlFeatureEnable:
    MRC     p15, #0, r1, c1, c0, #1 
    ORR     r0,  r0, r1
    MCR     p15, #0, r0, c1, c0, #1
    DSB
    BX      lr

@*****************************************************************************
@ This API Clears the specified fields in Auxiliary Control Register
@ r0 - Bit Mask for the bits to be cleared in Auxiliary Control Register
@*****************************************************************************
CP15AuxControlFeatureDisable:
    MRC     p15, #0, r1, c1, c0, #1 
    BIC     r0,  r1, r0
    MCR     p15, #0, r0, c1, c0, #1
    DSB
    BX      lr

@*****************************************************************************
@ This API returns the main ID register in r0
@*****************************************************************************
CP15MainIdPrimPartNumGet:
    MRC     p15, #0, r0, c0, c0, #0
    UBFX    r0, r0, #4, #12
    BX      lr

_CLIENTD: 
   .word  0x55555555
_FLD_MAX_WAY:
   .word  0x3ff
_FLD_MAX_IDX:
   .word  0x7ff

@
@ End of the file
@
    .end

