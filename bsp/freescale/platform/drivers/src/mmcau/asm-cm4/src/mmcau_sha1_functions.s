#*******************************************************************************
#*******************************************************************************
#
# Copyright (c) Freescale Semiconductor, Inc 2011.
#
# FILE NAME      : mmcau_sha1_functions.s
# VERSION        : $Id: mmcau_sha1_functions.s.rca 1.5 Thu Nov 21 14:17:37 2013 b40907 Experimental $
# TYPE           : Source Cortex-Mx assembly library code
# DEPARTMENT     : MSG R&D Core and Platforms
# AUTHOR         : David Schimke
# AUTHOR'S EMAIL : David.Schimke@freescale.com
# -----------------------------------------------------------------------------
# Release history
# VERSION  Date       AUTHOR           DESCRIPTION
#          08-2010    David Schimke    Initial Release
#          12-2010    David Schimke    Remove "global" on data objects
#          01-2011    David Schimke    Header added
#          11-2013    Teejay Ciancio   Cleanup
#
#*******************************************************************************
#*******************************************************************************

    .include "cau2_defines.hdr"
    .equ    MMCAU_PPB_DIRECT,0xe0081000
    .equ    MMCAU_PPB_INDIRECT,0xe0081800
    .equ    MMCAU_1_CMD, 0x80000000
    .equ    MMCAU_2_CMDS, 0x80100000

    .syntax unified

#*******************************************************************************
#*******************************************************************************
#
# SHA1: Initializes the SHA1 state variables
#   arguments
#           *sha1_state pointer to 160-bit block of SHA1 state variables:
#                           a,b,c,d,e
#
#   calling convention
#   void    mmcau_sha1_initialize_output (const unsigned int *sha1_state)

    .global _mmcau_sha1_initialize_output
    .global mmcau_sha1_initialize_output
    .type   mmcau_sha1_initialize_output, %function
    .align  4

_mmcau_sha1_initialize_output:
mmcau_sha1_initialize_output:

    stmdb   sp!, {r4-r5}                            @ save registers

    movw    r1, #:lower16:sha1_initial_h            @ r1 -> initial data
    movt    r1, #:upper16:sha1_initial_h

# copy initial data into hash output buffer
    ldmia   r1, {r1-r5}                             @ get sha1[0-4]
    stmia   r0, {r1-r5}                             @ copy to sha1_state[0-4]

    ldmia   sp!, {r4-r5}                            @ restore registers
    bx      lr


#*******************************************************************************
#*******************************************************************************
#
# SHA1: Perform the hash and generate SHA1 state variables for one or more
#       input message blocks
#
#   arguments
#           *msg_data   pointer to start of input message data
#           num_blks    number of 512-bit blocks to process
#           *sha1_state pointer to 160-bit block of SHA1 state variables:
#                           a,b,c,d,e
#
#   NOTE    Input message and digest output blocks must not overlap
#
#   calling convention
#   void    mmcau_sha1_hash_n (const unsigned char *msg_data,
#                              const int            num_blks,
#                              unsigned int        *sha1_state)

    .global _mmcau_sha1_hash_n
    .global mmcau_sha1_hash_n
    .type   mmcau_sha1_hash_n, %function
    .align  4

_mmcau_sha1_hash_n:
mmcau_sha1_hash_n:

#  register allocation
# --------------------
#  r0      = scratch / input pointer (arg0)
#  r1      = scratch / input num_blks (arg1)
#  r2      = scratch / output pointer (arg2)
#  r3      = scratch
#  r4      = scratch
#  r5      = scratch / mmcau_1_cmd(SHS)
#  r6      = scratch / mmcau_2_cmds(HASH+HFC,ADRA+CA4)
#  r7      = scratch
#  r8      = scratch / mmcau_2_cmds(HASH+HFP,ADRA+CA4)
#  r9      = scratch / mmcau_2_cmds(HASH+HFM,ADRA+CA4)
# r10 (sl) = scratch / pointer to sha1_k
# r11 (fp) = pointer to MMCAU_PPB_DIRECT

    stmdb   sp!, {r4-fp}                            @ save registers on stack

    sub     sp, $384                                @ reserve stack space

    movw    fp, #:lower16:MMCAU_PPB_DIRECT          @ fp -> MMCAU_PPB_DIRECT
    movt    fp, #:upper16:MMCAU_PPB_DIRECT

    add     r8, fp, $0x800+((LDR+CA0)<<2)           @ r8 = INDIRECT (LDR+CA0)
    add     r9, sp, $28                             @ r9 -> sha1_state (stack)

# initialize the CAU data registers with the current contents of sha1_state[]
    ldmia   r2, {r3-r7}                             @ get sha1_state[0-4]
    stmia   r8, {r3-r7}                             @ load CA0-CA4

    .align  2
next_blk:
    stmia   r9, {r3-r7}                             @ copy sha1_state to stack

    ror     r5, r3, $27                             @ rotate CA0 by 5
    str     r5, [fp, $0x800+((LDR+CAA)<<2)]         @ load into CAA

    movw    r5, #:lower16:MMCAU_1_CMD+(SHS)<<22
    movw    r6, #:lower16:MMCAU_2_CMDS+(HASH+HFC)<<22+(ADRA+CA4)<<11
    movw    sl, #:lower16:sha1_k
    movt    r5, #:upper16:MMCAU_1_CMD+(SHS)<<22
    movt    r6, #:upper16:MMCAU_2_CMDS+(HASH+HFC)<<22+(ADRA+CA4)<<11
    movt    sl, #:upper16:sha1_k

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#   for (j = 0; j < 16; j++, k++)
#   {
#       w[i] = byterev(msg_data[k]);                           // m[k] -> w[i]
#       *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFC,ADRA+CA4); // +Ch(b,c,d),+e
#       *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[0];        // add k[0]
#       *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = w[i++];           // add w[i]
#       *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(SHS);                // shift regs
#   }
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# -- (loop unrolled)

    ldr     r7, [sl], $4                            @ get k[0]; sl++

    ldr     r3, [r0], $4                            @ r3 = input[0]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $64]                           @ w[0] = m[0]
    add     r4, r7                                  @ add k[0] to w[0]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[1]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $68]                           @ w[1] = m[1]
    add     r4, r7                                  @ add k[0] to w[1]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[2]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $72]                           @ w[2] = m[2]
    add     r4, r7                                  @ add k[0] to w[2]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[3]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $76]                           @ w[3] = m[3]
    add     r4, r7                                  @ add k[0] to w[3]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[4]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $80]                           @ w[4] = m[4]
    add     r4, r7                                  @ add k[0] to w[4]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[5]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $84]                           @ w[5] = m[5]
    add     r4, r7                                  @ add k[0] to w[5]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[6]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $88]                           @ w[6] = m[6]
    add     r4, r7                                  @ add k[0] to w[6]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[7]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $92]                           @ w[7] = m[7]
    add     r4, r7                                  @ add k[0] to w[7]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[8]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $96]                           @ w[8] = m[8]
    add     r4, r7                                  @ add k[0] to w[8]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[9]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $100]                          @ w[9] = m[9]
    add     r4, r7                                  @ add k[0] to w[9]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[10]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $104]                          @ w[10] = m[10]
    add     r4, r7                                  @ add k[0] to w[10]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[11]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $108]                          @ w[11] = m[11]
    add     r4, r7                                  @ add k[0] to w[11]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[12]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $112]                          @ w[12] = m[12]
    add     r4, r7                                  @ add k[0] to w[12]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[13]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $116]                          @ w[13] = m[13]
    add     r4, r7                                  @ add k[0] to w[13]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[14]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $120]                          @ w[14] = m[14]
    add     r4, r7                                  @ add k[0] to w[14]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

    ldr     r3, [r0], $4                            @ r3 = input[15]
    rev     r4, r3                                  @ byte reverse
    str     r6, [fp]                                @ +Ch(b,c,d), +e
    str     r4, [sp, $124]                          @ w[15] = m[15]
    add     r4, r7                                  @ add k[0] to w[15]
    str     r4, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift registers

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# for (j = 0; j < 4; j++)
# {
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFC,ADRA+CA4); // +Ch(b,c,d), +e
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[0];        // +k[0]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA5))  = w[i-16];          // ld w[i-16] -> CA5
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-14];          // xor w[i-14]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-8];           // xor w[i-8]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-3];           // xor w[i-3]
#   *(MMCAU_PPB_INDIRECT + (ROTL+CA5)) = 1;                // rotate by 1
#   w[i++] = *(MMCAU_PPB_INDIRECT + (STR+CA5));            // store w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(ADRA+CA5,SHS);      // +w[i], shift regs
# }
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# -- (loop unrolled)

    str     r6, [fp]                                @ +Ch(b,c,d), +e
    ldr     r4, [sp, $64]                           @ r4 = w[0]
    ldr     r3, [sp, $72]                           @ r3 = w[2]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $96]                           @ r3 = w[8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $116]                          @ r3 = w[13]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $128]                          @ store w[16]
    add     r3, r7                                  @ add k[0] to w[16]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r6, [fp]                                @ +Ch(b,c,d), +e
    ldr     r4, [sp, $68]                           @ r4 = w[1]
    ldr     r3, [sp, $76]                           @ r3 = w[3]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $100]                          @ r3 = w[9]
    eor     r4, r3                                  @ XOR w[i-9]
    ldr     r3, [sp, $120]                          @ r3 = w[14]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $132]                          @ store w[17]
    add     r3, r7                                  @ add k[0] to w[17]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r6, [fp]                                @ +Ch(b,c,d), +e
    ldr     r4, [sp, $72]                           @ r4 = w[2]
    ldr     r3, [sp, $80]                           @ r3 = w[4]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $104]                          @ r4 = w[10]
    eor     r4, r3                                  @ XOR w[i-9]
    ldr     r3, [sp, $124]                          @ r3 = w[15]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $136]                          @ store w[18]
    add     r3, r7                                  @ add k[0] to w[18]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r6, [fp]                                @ +Ch(b,c,d), +e
    ldr     r4, [sp, $76]                           @ r4 = w[3]
    ldr     r3, [sp, $84]                           @ r3 = w[5]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $108]                          @ r4 = w[11]
    eor     r4, r3                                  @ XOR w[i-9]
    ldr     r3, [sp, $128]                          @ r3 = w[16]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $140]                          @ store w[19]
    add     r3, r7                                  @ add k[0] to w[19]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# for (j = 0; j < 20; j++)
# {
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFP,ADRA+CA4); // +Par(b,c,d), +e
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[1];        // +k[1]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA5))  = w[i-16];          // ld w[i-16] -> CA5
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-14];          // xor w[i-14]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-8];           // xor w[i-8]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-3];           // xor w[i-3]
#   *(MMCAU_PPB_INDIRECT + (ROTL+CA5)) = 1;                // rotate by 1
#   w[i++] = *(MMCAU_PPB_INDIRECT + (STR+CA5));            // store w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(ADRA+CA5,SHS);      // +w[i], shift regs
# }
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    movw    r8, #:lower16:MMCAU_2_CMDS+(HASH+HFP)<<22+(ADRA+CA4)<<11
    movt    r8, #:upper16:MMCAU_2_CMDS+(HASH+HFP)<<22+(ADRA+CA4)<<11
    ldr     r7, [sl], $4                            @ get k[1]; sl++

# -- (loop unrolled)

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $80]                           @ r4 = w[i-16]
    ldr     r3, [sp, $88]                           @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $112]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $132]                          @ r4 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $144]                          @ store w[20]
    add     r3, r7                                  @ add k[1] to w[20]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $84]                           @ r4 = w[i-16]
    ldr     r3, [sp, $92]                           @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $116]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $136]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $148]                          @ store w[21]
    add     r3, r7                                  @ add k[1] to w[21]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $88]                           @ r4 = w[i-16]
    ldr     r3, [sp, $96]                           @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $120]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $140]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $152]                          @ store w[22]
    add     r3, r7                                  @ add k[1] to w[22]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $92]                           @ r4 = w[i-16]
    ldr     r3, [sp, $100]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $124]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $144]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $156]                          @ store w[23]
    add     r3, r7                                  @ add k[1] to w[23]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $96]                           @ r4 = w[i-16]
    ldr     r3, [sp, $104]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $128]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $148]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $160]                          @ store w[24]
    add     r3, r7                                  @ add k[1] to w[24]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $100]                          @ r4 = w[i-16]
    ldr     r3, [sp, $108]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $132]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $152]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $164]                          @ store w[25]
    add     r3, r7                                  @ add k[1] to w[25]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $104]                          @ r4 = w[i-16]
    ldr     r3, [sp, $112]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $136]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $156]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $168]                          @ store w[26]
    add     r3, r7                                  @ add k[1] to w[26]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $108]                          @ r4 = w[i-16]
    ldr     r3, [sp, $116]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $140]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $160]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $172]                          @ store w[27]
    add     r3, r7                                  @ add k[1] to w[27]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $112]                          @ r4 = w[i-16]
    ldr     r3, [sp, $120]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $144]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $164]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $176]                          @ store w[28]
    add     r3, r7                                  @ add k[1] to w[28]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $116]                          @ r4 = w[i-16]
    ldr     r3, [sp, $124]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $148]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $168]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $180]                          @ store w[29]
    add     r3, r7                                  @ add k[1] to w[29]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $120]                          @ r4 = w[i-16]
    ldr     r3, [sp, $128]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $152]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $172]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $184]                          @ store w[30]
    add     r3, r7                                  @ add k[1] to w[30]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $124]                          @ r4 = w[i-16]
    ldr     r3, [sp, $132]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $156]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $176]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $188]                          @ store w[31]
    add     r3, r7                                  @ add k[1] to w[31]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $128]                          @ r4 = w[i-16]
    ldr     r3, [sp, $136]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $160]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $180]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $192]                          @ store w[32]
    add     r3, r7                                  @ add k[1] to w[32]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $132]                          @ r4 = w[i-16]
    ldr     r3, [sp, $140]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $164]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $184]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $196]                          @ store w[33]
    add     r3, r7                                  @ add k[1] to w[33]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $136]                          @ r4 = w[i-16]
    ldr     r3, [sp, $144]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $168]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $188]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $200]                          @ store w[34]
    add     r3, r7                                  @ add k[1] to w[34]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $140]                          @ r4 = w[i-16]
    ldr     r3, [sp, $148]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $172]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $192]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $204]                          @ store w[35]
    add     r3, r7                                  @ add k[1] to w[35]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $144]                          @ r4 = w[i-16]
    ldr     r3, [sp, $152]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $176]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $196]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $208]                          @ store w[36]
    add     r3, r7                                  @ add k[1] to w[36]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $148]                          @ r4 = w[i-16]
    ldr     r3, [sp, $156]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $180]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $200]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $212]                          @ store w[37]
    add     r3, r7                                  @ add k[1] to w[37]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $152]                          @ r4 = w[i-16]
    ldr     r3, [sp, $160]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $184]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $204]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $216]                          @ store w[38]
    add     r3, r7                                  @ add k[1] to w[38]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $156]                          @ r4 = w[i-16]
    ldr     r3, [sp, $164]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $188]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $208]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $220]                          @ store w[39]
    add     r3, r7                                  @ add k[1] to w[39]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# for (j = 0; j < 20; j++)
# {
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFM,ADRA+CA4); // +Maj(b,c,d), +e
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[2];        // +k[2]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA5))  = w[i-16];          // ld w[i-16] -> CA5
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-14];          // xor w[i-14]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-8];           // xor w[i-8]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-3];           // xor w[i-3]
#   *(MMCAU_PPB_INDIRECT + (ROTL+CA5)) = 1;                // rotate by 1
#   w[i++] = *(MMCAU_PPB_INDIRECT + (STR+CA5));            // store w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(ADRA+CA5,SHS);      // +w[i], shift regs
# }
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    movw    r9, #:lower16:MMCAU_2_CMDS+(HASH+HFM)<<22+(ADRA+CA4)<<11
    movt    r9, #:upper16:MMCAU_2_CMDS+(HASH+HFM)<<22+(ADRA+CA4)<<11
    ldr     r7, [sl], $4                            @ get k[2]; sl++

# -- (loop unrolled)

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $160]                          @ r4 = w[i-16]
    ldr     r3, [sp, $168]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $192]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $212]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $224]                          @ store w[40]
    add     r3, r7                                  @ add k[2] to w[40]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $164]                          @ r4 = w[i-16]
    ldr     r3, [sp, $172]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $196]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $216]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $228]                          @ store w[41]
    add     r3, r7                                  @ add k[2] to w[41]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $168]                          @ r4 = w[i-16]
    ldr     r3, [sp, $176]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $200]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $220]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $232]                          @ store w[42]
    add     r3, r7                                  @ add k[2] to w[42]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $172]                          @ r4 = w[i-16]
    ldr     r3, [sp, $180]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $204]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $224]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $236]                          @ store w[43]
    add     r3, r7                                  @ add k[2] to w[43]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $176]                          @ r4 = w[i-16]
    ldr     r3, [sp, $184]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $208]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $228]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $240]                          @ store w[44]
    add     r3, r7                                  @ add k[2] to w[44]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $180]                          @ r4 = w[i-16]
    ldr     r3, [sp, $188]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $212]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $232]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $244]                          @ store w[45]
    add     r3, r7                                  @ add k[2] to w[45]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $184]                          @ r4 = w[i-16]
    ldr     r3, [sp, $192]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $216]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $236]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $248]                          @ store w[46]
    add     r3, r7                                  @ add k[2] to w[46]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $188]                          @ r4 = w[i-16]
    ldr     r3, [sp, $196]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $220]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $240]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $252]                          @ store w[47]
    add     r3, r7                                  @ add k[2] to w[47]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $192]                          @ r4 = w[i-16]
    ldr     r3, [sp, $200]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $224]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $244]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $256]                          @ store w[48]
    add     r3, r7                                  @ add k[2] to w[48]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $196]                          @ r4 = w[i-16]
    ldr     r3, [sp, $204]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $228]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $248]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $260]                          @ store w[49]
    add     r3, r7                                  @ add k[2] to w[49]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $200]                          @ r4 = w[i-16]
    ldr     r3, [sp, $208]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $232]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $252]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $264]                          @ store w[50]
    add     r3, r7                                  @ add k[2] to w[50]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add w[50] to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $204]                          @ r4 = w[i-16]
    ldr     r3, [sp, $212]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $236]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $256]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $268]                          @ store w[51]
    add     r3, r7                                  @ add k[2] to w[51]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $208]                          @ r4 = w[i-16]
    ldr     r3, [sp, $216]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $240]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $260]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $272]                          @ store w[52]
    add     r3, r7                                  @ add k[2] to w[52]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $212]                          @ r4 = w[i-16]
    ldr     r3, [sp, $220]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $244]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $264]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $276]                          @ store w[53]
    add     r3, r7                                  @ add k[2] to w[53]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $216]                          @ r4 = w[i-16]
    ldr     r3, [sp, $224]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $248]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $268]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $280]                          @ store w[54]
    add     r3, r7                                  @ add k[2] to w[54]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $220]                          @ r4 = w[i-16]
    ldr     r3, [sp, $228]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $252]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $272]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $284]                          @ store w[55]
    add     r3, r7                                  @ add k[2] to w[55]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $224]                          @ r4 = w[i-16]
    ldr     r3, [sp, $232]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $256]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $276]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $288]                          @ store w[56]
    add     r3, r7                                  @ add k[2] to w[56]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $228]                          @ r4 = w[i-16]
    ldr     r3, [sp, $236]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $260]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $280]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $292]                          @ store w[57]
    add     r3, r7                                  @ add k[2] to w[57]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $232]                          @ r4 = w[i-16]
    ldr     r3, [sp, $240]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $264]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $284]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $296]                          @ store w[58]
    add     r3, r7                                  @ add k[2] to w[58]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r9, [fp]                                @ +Maj(b,c,d), +e
    ldr     r4, [sp, $236]                          @ r4 = w[i-16]
    ldr     r3, [sp, $244]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $268]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $288]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $300]                          @ store w[59]
    add     r3, r7                                  @ add k[2] to w[59]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# for (j = 0; j < 20; j++)
# {
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFP,ADRA+CA4); // +Par(b,c,d), +e
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[3];        // +k[3]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA5))  = w[i-16];          // ld w[i-16] -> CA5
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-14];          // xor w[i-14]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-8];           // xor w[i-8]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-3];           // xor w[i-3]
#   *(MMCAU_PPB_INDIRECT + (ROTL+CA5)) = 1;                // rotate by 1
#   w[i++] = *(MMCAU_PPB_INDIRECT + (STR+CA5));            // store w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(ADRA+CA5,SHS);      // +w[i], shift regs
# }
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    ldr     r7, [sl]                                @ get k[3]

# -- (loop unrolled)

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $240]                          @ r4 = w[i-16]
    ldr     r3, [sp, $248]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $272]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $292]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $304]                          @ store w[60]
    add     r3, r7                                  @ add k[3] to w[60]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $244]                          @ r4 = w[i-16]
    ldr     r3, [sp, $252]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $276]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $296]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $308]                          @ store w[61]
    add     r3, r7                                  @ add k[3] to w[61]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $248]                          @ r4 = w[i-16]
    ldr     r3, [sp, $256]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $280]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $300]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $312]                          @ store w[62]
    add     r3, r7                                  @ add k[3] to w[62]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $252]                          @ r4 = w[i-16]
    ldr     r3, [sp, $260]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $284]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $304]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $316]                          @ store w[63]
    add     r3, r7                                  @ add k[3] to w[63]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $256]                          @ r4 = w[i-16]
    ldr     r3, [sp, $264]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $288]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $308]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $320]                          @ store w[64]
    add     r3, r7                                  @ add k[3] to w[64]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $260]                          @ r4 = w[i-16]
    ldr     r3, [sp, $268]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $292]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $312]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $324]                          @ store w[65]
    add     r3, r7                                  @ add k[3] to w[65]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $264]                          @ r4 = w[i-16]
    ldr     r3, [sp, $272]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $296]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $316]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $328]                          @ store w[66]
    add     r3, r7                                  @ add k[3] to w[66]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $268]                          @ r4 = w[i-16]
    ldr     r3, [sp, $276]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $300]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $320]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $332]                          @ store w[67]
    add     r3, r7                                  @ add k[3] to w[67]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $272]                          @ r4 = w[i-16]
    ldr     r3, [sp, $280]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $304]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $324]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $336]                          @ store w[68]
    add     r3, r7                                  @ add k[3] to w[68]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $276]                          @ r4 = w[i-16]
    ldr     r3, [sp, $284]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $308]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $328]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $340]                          @ store w[69]
    add     r3, r7                                  @ add k[3] to w[69]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $280]                          @ r4 = w[i-16]
    ldr     r3, [sp, $288]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $312]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $332]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $344]                          @ store w[70]
    add     r3, r7                                  @ add k[3] to w[70]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $284]                          @ r4 = w[i-16]
    ldr     r3, [sp, $292]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $316]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $336]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $348]                          @ store w[71]
    add     r3, r7                                  @ add k[3] to w[71]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $288]                          @ r4 = w[i-16]
    ldr     r3, [sp, $296]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $320]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $340]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $352]                          @ store w[72]
    add     r3, r7                                  @ add k[3] to w[72]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $292]                          @ r4 = w[i-16]
    ldr     r3, [sp, $300]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $324]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $344]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $356]                          @ store w[73]
    add     r3, r7                                  @ add k[3] to w[73]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $296]                          @ r4 = w[i-16]
    ldr     r3, [sp, $304]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $328]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $348]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $360]                          @ store w[74]
    add     r3, r7                                  @ add k[3] to w[74]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $300]                          @ r4 = w[i-16]
    ldr     r3, [sp, $308]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $332]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $352]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $364]                          @ store w[75]
    add     r3, r7                                  @ add k[3] to w[75]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $304]                          @ r4 = w[i-16]
    ldr     r3, [sp, $312]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $336]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $356]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $368]                          @ store w[76]
    add     r3, r7                                  @ add k[3] to w[76]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $308]                          @ r4 = w[i-16]
    ldr     r3, [sp, $316]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $340]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $360]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $372]                          @ store w[77]
    add     r3, r7                                  @ add k[3] to w[77]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $312]                          @ r4 = w[i-16]
    ldr     r3, [sp, $320]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $344]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $364]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $376]                          @ store w[78]
    add     r3, r7                                  @ add k[3] to w[78]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    str     r8, [fp]                                @ +Par(b,c,d), +e
    ldr     r4, [sp, $316]                          @ r4 = w[i-16]
    ldr     r3, [sp, $324]                          @ r3 = w[i-14]
    eor     r4, r3                                  @ XOR w[i-14]
    ldr     r3, [sp, $348]                          @ r3 = w[i-8]
    eor     r4, r3                                  @ XOR w[i-8]
    ldr     r3, [sp, $368]                          @ r3 = w[i-3]
    eor     r4, r3                                  @ XOR w[i-3]
    ror     r3, r4, $31                             @ rotate left by 1
    str     r3, [sp, $380]                          @ store w[79]
    add     r3, r7                                  @ add k[3] to w[79]
    str     r3, [fp, $0x800+((ADR+CAA)<<2)]         @ add sum to CAA
    str     r5, [fp]                                @ shift regs

    add     r9, sp, $28                             @ r9 -> output[0] on stack
    add     r8, fp, $0x800+((ADR+CA0)<<2)           @ r8 = indirect_cmd ADR+CA0
    add     sl, fp, $0x800+((STR+CA0)<<2)           @ sl = indirect_cmd STR+CA0

    ldmia   r9, {r3-r7}                             @ get current outputs
    stmia   r8, {r3-r7}                             @ add output[i] to CA[4:0]
    ldmia   sl, {r3-r7}                             @ get CA[4:0]

    subs    r1, $1                                  @ decrement num_blks
    bne     next_blk

    add     sp, $384                                @ unreserve stack space
    stmia   r2, {r3-r7}                             @ store CA[i] to output[i]
    ldmia   sp!, {r4-fp}                            @ restore regs and return
    bx      lr

#*******************************************************************************
#*******************************************************************************
#
# SHA1: Updates SHA1 state variables for one or more input message blocks
#   arguments
#           *msg_data   pointer to start of input message data
#           num_blks    number of 512-bit blocks to process
#           *sha1_state pointer to 160-bit block of SHA1 state variables:
#                           a,b,c,d,e
#
#   calling convention
#   void    mmcau_sha1_update (const unsigned char *msg_data,
#                              const int            num_blks,
#                              unsigned int        *sha1_state)


    .global _mmcau_sha1_update
    .global mmcau_sha1_update
    .type   mmcau_sha1_update, %function
    .align  4

_mmcau_sha1_update:
mmcau_sha1_update:

    stmdb   sp!, {r3-r7, lr}                        @ save registers on stack

    movw    r3, #:lower16:sha1_initial_h            @ r3 -> initial data
    movt    r3, #:upper16:sha1_initial_h

# copy initial data into hash output buffer
    ldmia   r3, {r3-r7}                             @ get initial sha1[0-4]
    stmia   r2, {r3-r7}                             @ copy to sha1_state[0-4]

    bl      mmcau_sha1_hash_n                       @ call hash_n routine

    ldmia   sp!, {r3-r7, pc}                        @ restore regs and return

#*******************************************************************************
#*******************************************************************************
#
# SHA1: Perform the hash and generate SHA1 state variables for one input
#       message block.
#
#   arguments
#           *msg_data   pointer to start of input message data
#           *sha1_state pointer to 160-bit block of SHA1 state variables:
#                           a,b,c,d,e
#
#   NOTE    Input message and digest output blocks must not overlap
#
#   calling convention
#   void    mmcau_sha1_hash (const unsigned char *msg_data,
#                            unsigned int        *sha1_state)

    .global _mmcau_sha1_hash
    .global mmcau_sha1_hash
    .type   mmcau_sha1_hash, %function
    .align  4

_mmcau_sha1_hash:
mmcau_sha1_hash:

    mov    r2, r1                                   @ arg2 = arg1 (*sha1_state)
    mov    r1, $1                                   @ arg1 = num_blks = 1
    b      mmcau_sha1_hash_n                        @ branch to hash_n routine

#*******************************************************************************

    .data
    .type   sha1_initial_h, %object
    .align  4

sha1_initial_h:
    .word   0x67452301
    .word   0xefcdab89
    .word   0x98badcfe
    .word   0x10325476
    .word   0xc3d2e1f0

    .type   sha1_k, %object
    .align  4

sha1_k:
    .word   0x5a827999
    .word   0x6ed9eba1
    .word   0x8f1bbcdc
    .word   0xca62c1d6
