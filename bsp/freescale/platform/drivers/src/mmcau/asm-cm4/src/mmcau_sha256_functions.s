#*******************************************************************************
#*******************************************************************************
#
# Copyright (c) Freescale Semiconductor, Inc 2011.
#
# FILE NAME      : mmcau_sha256_functions.s
# VERSION        : $Id: mmcau_sha256_functions.s.rca 1.6 Thu Nov 21 14:18:00 2013 b40907 Experimental $
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
    .equ    MMCAU_1_CMD,0x80000000
    .equ    MMCAU_3_CMDS,0x80100200

    .syntax unified

#*******************************************************************************
#*******************************************************************************
#
# SHA256: Initializes the hash output and checks the CAU hardware revision
#   arguments
#           *output     pointer to 256-bit message digest output
#
#   calling convention
#   int     mmcau_sha256_initialize_output (const unsigned int *output)

    .global _mmcau_sha256_initialize_output
    .global mmcau_sha256_initialize_output
    .type   mmcau_sha256_initialize_output, %function
    .align  4

_mmcau_sha256_initialize_output:
mmcau_sha256_initialize_output:

    stmdb   sp!, {r4-r8}                            @ save registers

    movw    r1, #:lower16:sha256_initial_h          @ r1 -> initial data
    movt    r1, #:upper16:sha256_initial_h

# copy initial data into message digest output buffer
    ldmia   r1, {r1-r8}                             @ get sha256_initial[0-7]
    stmia   r0, {r1-r8}                             @ copy to output[0-7]

    ldmia   sp!, {r4-r8}                            @ restore registers
    mov     r0, $0                                  @ clear return value in r0
    bx      lr

#*******************************************************************************
#*******************************************************************************
#
# SHA256: Perform the hash for one or more input message blocks and generate the
#         message digest output
#
#   arguments
#           *msg_data     pointer to start of input message data
#           num_blks      number of 512-bit blocks to process
#           *sha256_state pointer to 256-bit message digest.
#
#   NOTE    Input message and digest output blocks must not overlap
#
#   calling convention
#   void    mmcau_sha256_hash_n (const unsigned char *msg_data,
#                                const int            num_blks,
#                                unsigned int        *sha256_state)
    .global _mmcau_sha256_hash_n
    .global mmcau_sha256_hash_n
    .type   mmcau_sha256_hash_n, %function
    .align  4

_mmcau_sha256_hash_n:
mmcau_sha256_hash_n:

#  register allocation
# --------------------
#  r0      = scratch / input pointer (arg0)
#  r1      = scratch / input num_blks (arg1)
#  r2      = scratch / output pointer (arg2)
#  r3      = scratch
#  r4      = scratch
#  r5      = scratch / mmcau_1_cmd(HASH+HF2U)
#  r6      = scratch / mmcau_1_cmd(HASH+HF2V)
#  r7      = scratch / mmcau_1_cmd(SHS2)
#  r8      = scratch / mmcau_3_cmds(MVAR+CA8,HASH+HF2S,HASH+HF2M)
#  r9      = scratch / mmcau_3_cmds(ADRA+CA7,HASH+HF2T,HASH+HF2C)
# r10 (sl) = scratch / pointer to sha256_k
# r11 (fp) = scratch / loop counter
# r12 (ip) = pointer to MMCAU_PPB_DIRECT
# r14 (lr) = link reg / indirect_cmd(ADR+CA0)

    stmdb   sp!, {r4-ip}                            @ save registers on stack

    movw    ip, #:lower16:MMCAU_PPB_DIRECT          @ ip -> MMCAU_PPB_DIRECT
    movt    ip, #:upper16:MMCAU_PPB_DIRECT

    sub     sp, $320                                @ reserve stack space
    str     r2, [sp, $20]                           @ save r2 on stack
    mov     fp, r1                                  @ fp = num_blks

# initialize the CAU data registers with the current contents of output[]
    ldmia   r2, {r1-r8}                             @ get output[0-7]

    add     r9, ip, $0x800+(LDR+CA0)<<2             @ r9 -> mmcau_1_cmd(LDR+CA0)
    stmia   r9, {r1-r8}                             @ load CA0-CA7

# prepare for SHA256 operations register load
    movw    sl, #:lower16:sha256_reg_data
    movt    sl, #:upper16:sha256_reg_data
    str     sl, [sp, $8]                            @ save sl on stack

    add     r9,  sp, $28                            @ r9 -> stack copy of output

    .align  2
next_blk:

    stmia   r9, {r1-r8}                             @ save output on stack

# load registers needed for mmcau commands from sha256_reg_data:
    ldr     sl, [sp, $8]                            @ sl -> sha256_reg_data
    ldmia   sl, {r5-sl}                             @ setup sha256 operations


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#   i = 0;
#   for (j = 0; j < 16; j++, i++)
#   {
#       w[i] = byterev(input[i]);                          // copy m[i] to w[i]
#       *(MMCAU_PPB_INDIRECT + (LDR+CAA))  = w[i];         // +w[i]+h+SIGMA1(e)
#                                                          // add Ch(e,f,g)
#       *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(ADRA+CA7,HASH+HF2T,HASH+HF2C);
#       *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha256_k[i];  // +k[i]+t1+SIGMA0(e)
#                                                          // add Maj(a,b,c)
#       *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(MVAR+CA8,HASH+HF2S,HASH+HF2M);
#       *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(SHS2);           // shift registers
#   }
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


# -- input 0

    ldr     r2, [r0], $4                            @ r2 = input[0]; r0++
    rev     r1, r2                                  @ byte reverse
    str     r1, [sp, $64]                           @ w[0] (on stack) = m[0]
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[i]
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    ldr     r3, [sl], $4                            @ get k[1]; sl++
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[1]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

# -- repeat for inputs 1 to 15 -- (loop unrolled)

    ldr     r2, [r0], $4                            @ r2 = input[1]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[1]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[1]
    str     r1, [sp, $68]                           @ w[1] (on stack) = m[1]
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[1]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[2]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[2]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[2]
    str     r1, [sp, $72]                           @ m[2] -> w[2] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[2]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[3]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[3]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[3]
    str     r1, [sp, $76]                           @ m[3] -> w[3] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[3]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[4]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[4]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[4]
    str     r1, [sp, $80]                           @ m[4] -> w[4] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[4]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[5]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[5]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[5]
    str     r1, [sp, $84]                           @ m[5] -> w[5] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[5]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[6]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[6]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[6]
    str     r1, [sp, $88]                           @ m[6] -> w[6] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[6]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[7]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[7]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[7]
    str     r1, [sp, $92]                           @ m[7] -> w[7] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[7]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[8]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[8]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[8]
    str     r1, [sp, $96]                           @ m[8] -> w[8] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[8]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[9]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[9]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[9]
    str     r1, [sp, $100]                          @ m[9] -> w[9] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[9]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[10]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[10]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[10]
    str     r1, [sp, $104]                          @ m[10] -> w[10] (on stack
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[10]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[11]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[11]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[11]
    str     r1, [sp, $108]                          @ m[11] -> w[11] (on stack
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[11]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[12]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[12]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[12]
    str     r1, [sp, $112]                          @ m[12] -> w[12] (on stack
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[12]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[13]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[13]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[13]
    str     r1, [sp, $116]                          @ m[13] -> w[13] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[13]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[14]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[14]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[14]
    str     r1, [sp, $120]                          @ m[14] -> w[14] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[14]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers

    ldr     r2, [r0], $4                            @ r2 = input[15]; r0++
    rev     r1, r2                                  @ byte reverse
    ldr     r3, [sl], $4                            @ get k[15]; sl++
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ add w[15]
    str     r1, [sp, $124]                          @ m[15] -> w[15] (on stack)
    str     r9, [ip]                                @ +h,+SIGMA1(e),+Ch(e,f,g)
    str     r3, [ip, $0x800+(ADR+CAA)<<2]           @ add k[15]
    str     r8, [ip]                                @ t1,+SIGMA0(e),+Maj(a,b,c)
    str     r7, [ip]                                @ shift registers


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#   for (j = 0; j < 48; j++, i++)
#   {
#       *(MMCAU_PPB_INDIRECT + (LDR+CAA))  = w[i-16];       // [i-16]
#       *(MMCAU_PPB_INDIRECT + (LDR+CA8))  = w[i-15];       // [i-15]
#       *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(HASH+HF2U);       // + Sigma2(w[i-15])
#       *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = w[i-7];        // add w[i-7]
#       *(MMCAU_PPB_INDIRECT + (LDR+CA8))  = w[i-2];        // load w[i-2]
#       *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(HASH+HF2V);       // + Sigma1(w[i-2])
#       w[i] = *(MMCAU_PPB_INDIRECT + (STR+CAA));           // store w[i]
#       *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(ADRA+CA7,HASH+HF2T,HASH+HF2C);
#       *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha256_k[i];   // add k[i]
#       *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(MVAR+CA8,HASH+HF2S,HASH+HF2M);
#       *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(SHS2);            // shift registers
#   }
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    mov     r2, $48                                 @ loop end
    add     r3, sp, $128                            @ r3 -> w[16]

    .align  2
loop:
    ldr     r1, [r3, $(-16<<2)]                     @ get w[i-16] off stack
    str     r1, [ip, $0x800+(LDR+CAA)<<2]           @ CAA  = w[i-16]
    ldr     r1, [r3, $(-15<<2)]                     @ get w[i-15] off stack
    str     r1, [ip, $0x800+(LDR+CA8)<<2]           @ CA8  = w[i-15]
    str     r5, [ip]                                @ (HASH+HF2U)
    ldr     r1, [r3, $(-7<<2)]                      @ get w[i-7] off stack
    str     r1, [ip, $0x800+(ADR+CAA)<<2]           @ CAA += w[i-7]
    ldr     r1, [r3, $(-2<<2)]                      @ get w[i-2] off stack
    str     r1, [ip, $0x800+(LDR+CA8)<<2]           @ CA8  = w[i-2]
    str     r6, [ip]                                @ (HASH+HF2V)
    ldr     r1, [ip, $0x800+(STR+CAA)<<2]           @ r1 = w[i] [STR+CAA]
    str     r1, [r3], $4                            @ store w[i] on stack; r3++
    str     r9, [ip]                                @ +h, SIGMA1(e) & Ch(e,f,g)
    ldr     r1, [sl], $4                            @ get k[i]; sl++
    str     r1, [ip, $0x800+(ADR+CAA)<<2]           @ add k[i]
    str     r8, [ip]                                @ t1, +SIGMA0(e) +Maj(a,b,c)
    str     r7, [ip]                                @ shift registers
    subs    r2, $1                                  @ decrement loop count
    bne.n   loop

    add     r9, sp, $28                             @ r9 = output[0] on stack
    add     sl, ip, $0x800+(ADR+CA0)<<2             @ r8 = indirect_cmd(ADR+CA0)
    ldmia   r9, {r1-r8}                             @ get current outputs
    stmia   sl, {r1-r8}                             @ add output[i] to CA[i]
    add     sl, ip, $0x800+(STR+CA0)<<2             @ sl = indirect_cmd(STR+CA0)
    ldmia   sl, {r1-r8}                             @ get new CA[i]; i = 0-7

    subs    fp, $1                                  @ decrement num_blks
    bne     next_blk

    ldr     r9, [sp, $20]                           @ get saved output pointer
    add     sp, $320                                @ restore stack
    stmia   r9, {r1-r8}                             @ store CA[i] to output[i]
    ldmia   sp!, {r4-ip}                            @ restore regs and return
    bx      lr

#*******************************************************************************
#*******************************************************************************
#
# SHA256: Updates SHA256 state variables for one or more input message blocks
#
#   arguments:
#           *msg_data     pointer to start of input message data
#           num_blks      number of 512-bit blocks to process
#           *sha256_state pointer to 256-bit message digest.
#
#   calling convention
#   void    mmcau_sha256_update (const unsigned char *msg_data,
#                                const int            num_blks,
#                                unsigned int        *sha256_state)


    .global _mmcau_sha256_update
    .global mmcau_sha256_update
    .type   mmcau_sha256_update, %function
    .align  4

_mmcau_sha256_update:
mmcau_sha256_update:

    stmdb   sp!, {r4-fp, lr}                        @ save registers on stack

    movw    r4, #:lower16:sha256_initial_h          @ r4 -> initial data
    movt    r4, #:upper16:sha256_initial_h

# copy initial data into hash output buffer
    ldmia   r4, {r4-fp}                             @ get sha256[0-7]
    stmia   r2, {r4-fp}                             @ copy to sha256_state[0-7]

    bl      mmcau_sha256_hash_n                     @ call hash_n routine

    ldmia   sp!, {r4-fp,pc}                         @ restore regs and return


#*******************************************************************************
#*******************************************************************************
#
# SHA256: Perform the hash and generate SHA256 state variables for one input
#       message block.
#
#   arguments
#           *msg_data     pointer to start of input message data
#           *sha256_state pointer to 256-bit message digest.
#
#   NOTE    Input message and digest output blocks must not overlap
#
#   calling convention
#   void    mmcau_sha256_hash (const unsigned char *msg_data,
#                              unsigned int        *sha256_state)

    .global _mmcau_sha256_hash
    .global mmcau_sha256_hash
    .type   mmcau_sha256_hash, %function
    .align  4

_mmcau_sha256_hash:
mmcau_sha256_hash:

    mov     r2, r1                                  @ move arg1 to arg2
    mov     r1, $1                                  @ set arg1 = 1
    b       mmcau_sha256_hash_n                     @ use hash_n w/num_blks = 1

#*******************************************************************************

    .data
    .type   sha256_reg_data, %object
    .align  4

sha256_reg_data:
    .word   MMCAU_1_CMD+(HASH+HF2U)<<22                          @ r5
    .word   MMCAU_1_CMD+(HASH+HF2V)<<22                          @ r6
    .word   MMCAU_1_CMD+(SHS2)<<22                               @ r7
    .word   MMCAU_3_CMDS+(MVAR+CA8)<<22+(HASH+HF2S)<<11+HASH+HF2M @ r8
    .word   MMCAU_3_CMDS+(ADRA+CA7)<<22+(HASH+HF2T)<<11+HASH+HF2C @ r9
    .word   sha256_k                                            @ sl

    .type   sha256_initial_h, %object
    .align  4

sha256_initial_h:
    .word   0x6a09e667
    .word   0xbb67ae85
    .word   0x3c6ef372
    .word   0xa54ff53a
    .word   0x510e527f
    .word   0x9b05688c
    .word   0x1f83d9ab
    .word   0x5be0cd19

    .type   sha256_k, %object
    .align  4

sha256_k:
    .word   0x428a2f98
    .word   0x71374491
    .word   0xb5c0fbcf
    .word   0xe9b5dba5
    .word   0x3956c25b
    .word   0x59f111f1
    .word   0x923f82a4
    .word   0xab1c5ed5
    .word   0xd807aa98
    .word   0x12835b01
    .word   0x243185be
    .word   0x550c7dc3
    .word   0x72be5d74
    .word   0x80deb1fe
    .word   0x9bdc06a7
    .word   0xc19bf174
    .word   0xe49b69c1
    .word   0xefbe4786
    .word   0x0fc19dc6
    .word   0x240ca1cc
    .word   0x2de92c6f
    .word   0x4a7484aa
    .word   0x5cb0a9dc
    .word   0x76f988da
    .word   0x983e5152
    .word   0xa831c66d
    .word   0xb00327c8
    .word   0xbf597fc7
    .word   0xc6e00bf3
    .word   0xd5a79147
    .word   0x06ca6351
    .word   0x14292967
    .word   0x27b70a85
    .word   0x2e1b2138
    .word   0x4d2c6dfc
    .word   0x53380d13
    .word   0x650a7354
    .word   0x766a0abb
    .word   0x81c2c92e
    .word   0x92722c85
    .word   0xa2bfe8a1
    .word   0xa81a664b
    .word   0xc24b8b70
    .word   0xc76c51a3
    .word   0xd192e819
    .word   0xd6990624
    .word   0xf40e3585
    .word   0x106aa070
    .word   0x19a4c116
    .word   0x1e376c08
    .word   0x2748774c
    .word   0x34b0bcb5
    .word   0x391c0cb3
    .word   0x4ed8aa4a
    .word   0x5b9cca4f
    .word   0x682e6ff3
    .word   0x748f82ee
    .word   0x78a5636f
    .word   0x84c87814
    .word   0x8cc70208
    .word   0x90befffa
    .word   0xa4506ceb
    .word   0xbef9a3f7
    .word   0xc67178f2
