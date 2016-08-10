# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# Copyright (c) Freescale Semiconductor, Inc 2013.
#
# FILE NAME         : mmcau_sha1_functions.s
# VERSION           : $Id:  $
# TYPE              : Source Cortex-M0+ assembly library code
# DEPARTMENT        : MCG R&D Core and Platforms
# AUTHOR            : Anthony (Teejay) Ciancio
# AUTHOR EMAIL      : teejay.ciancio@freescale.com
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
# VERSION   DATE        AUTHOR          DESCRIPTION
# *******   ****        ******          ***********
# 1.0       2013-11     Ciancio         initial release, using the ARMv6-M ISA
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


    .include "cau2_defines.hdr"
    .syntax unified


    .equ      MMCAU_PPB_DIRECT, 0xf0005000
    .equ    MMCAU_PPB_INDIRECT, 0xf0005800
    .equ           MMCAU_1_CMD, 0x80000000
    .equ          MMCAU_2_CMDS, 0x80100000


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_SHA1_INITIALIZE_OUTPUT
#   Initializes the SHA1 state variables
#
#   ARGUMENTS
#   *sha1_state     pointer to 160-bit block of SHA1 state variables: a,b,c,d,e
#
#   CALLING CONVENTION
#   void mmcau_sha1_initialize_output (const unsigned int *sha1_state)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_sha1_initialize_output)
#   -----------+------------------------------------------------------------
#          r0  |  *sha1_state   (arg0)
#              |
#        > r0  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_sha1_initialize_output
    .global mmcau_sha1_initialize_output
    .type   mmcau_sha1_initialize_output, %function
    .align  4

_mmcau_sha1_initialize_output:
mmcau_sha1_initialize_output:

# store regs r4-r5, we need to restore them at the end of the routine
    push    {r4-r5}                         @ store regs

# initialize the hash variables, a-e, both in memory and in the CAU
    ldr     r1, =sha1_initial_h
    ldmia   r1, {r1-r5}                     @ load sha1_initial_h[0-4]
    stmia   r0!, {r1-r5}                    @ store in sha1_state[0-4]

    pop     {r4-r5}                         @ restore regs
    bx      lr                              @ exit routine


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_SHA1_HASH_N
#   Perform the hash and generate SHA1 state variables for one or more input
#   message blocks
#
#   ARGUMENTS
#   *msg_data       pointer to start of input message data
#   num_blks        number of 512-bit blocks to process
#   *sha1_state     pointer to 160-bit block of SHA1 state variables: a,b,c,d,e
#
#   NOTE
#   Input message and digest output blocks must not overlap
#
#   CALLING CONVENTION
#   void mmcau_sha1_hash_n     (const unsigned char     *msg_data,
#                               const int               num_blks,
#                               unsigned int            *sha1_state)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_sha1_hash_n)
#   -----------+------------------------------------------------------------
#          r0  |  *msg_data     (arg0)
#          r1  |  num_blks      (arg1)
#          r2  |  *sha1_state   (arg2)
#              |
#        > r2  |  irrelevant
#
#
#       STACK  |  ALLOCATION (throughout mmcau_sha1_hash_n)
#   -----------+------------------------------------------------------------
#        #356  |  *sha1_state
#        #352  |  num_blks
#        #348  |  *msg_data
#        #344  |  *sha1_k
#    #24-#340  |  w[i]
#      #0-#20  |  sha1_state[0-4]
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_sha1_hash_n
    .global mmcau_sha1_hash_n
    .type   mmcau_sha1_hash_n, %function
    .align  4

_mmcau_sha1_hash_n:
mmcau_sha1_hash_n:

# store *msg_data, num_blks, and *sha1_state, we need them later in the routine
# store regs r4-r7, we need to restore them at the end of the routine
    push    {r0-r2, r4-r7}      @ store *msg_data, num_blks, *sha1_state, regs

# initialize the hash variables, a-e, in the CAU
    ldr     r1, =MMCAU_PPB_INDIRECT+((LDR+CA0)<<2)
    ldmia   r2!, {r3-r7}                    @ load sha1_state[0-4]
    stmia   r1!, {r3-r7}                    @ store in CA[0-4]

    sub     sp, #348                        @ reserve stack


    .align  2
next_blk:

    add     r2, sp, #0                      @ set *sha1_state (on stack)
    stmia   r2!, {r3-r7}                    @ store sha1_state[0-4]

    ldr     r4, =MMCAU_PPB_INDIRECT+((LDR+CAA)<<2)
    movs    r1, #27
    rors    r3, r1                          @ ROTL(a,5)
    str     r3, [r4]                        @ store in CAA

# prepare regs for loops
    ldr     r1, =sha1_k
    ldr     r2, =MMCAU_PPB_DIRECT
    adds    r4, #128                        @ mmcau_indirect_cmd(ADR+CAA)
    ldr     r5, =MMCAU_1_CMD+((SHS)<<22)
    ldr     r6, =MMCAU_2_CMDS+((HASH+HFC)<<22)+((ADRA+CA4)<<11)
    ldr     r7, [r1, #0<<2]                 @ load k[0]
    str     r1, [sp, #344]                  @ store *sha1_k


#   for (j = 0; j < 16; j++, k++)
#   {
#   w[i] = byterev(msg_data[k]);                            // w[i] = m[k]
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFC,ADRA+CA4);  // + Ch(), + e
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[0];         // + k[0]
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = w[i++];            // + w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(SHS);                 // shift regs
#   }
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (throughout the first loop)
#   -----------+------------------------------------------------------------
#          r0  |  *msg_data
#          r1  |  scratch
#          r2  |  *mmcau_direct_cmd()
#          r3  |  scratch
#          r4  |  mmcau_indirect_cmd(ADR+CAA)
#          r5  |  mmcau_1_cmd(SHS)
#          r6  |  mmcau_2_cmds(HASH+HFC,ADRA+CA4)
#          r7  |  k[0]

    ldmia   r0!, {r1}                       @ m[0], *msg_data++
    rev     r1, r1                          @ w[0]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #0<<2+24]             @ store w[0]
    add     r1, r7                          @ w[0] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[1], *msg_data++
    rev     r1, r1                          @ w[1]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #1<<2+24]             @ store w[1]
    add     r1, r7                          @ w[1] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[2], *msg_data++
    rev     r1, r1                          @ w[2]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #2<<2+24]             @ store w[2]
    add     r1, r7                          @ w[2] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[3], *msg_data++
    rev     r1, r1                          @ w[3]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #3<<2+24]             @ store w[3]
    add     r1, r7                          @ w[3] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[4], *msg_data++
    rev     r1, r1                          @ w[4]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #4<<2+24]             @ store w[4]
    add     r1, r7                          @ w[4] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[5], *msg_data++
    rev     r1, r1                          @ w[5]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #5<<2+24]             @ store w[5]
    add     r1, r7                          @ w[5] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[6], *msg_data++
    rev     r1, r1                          @ w[6]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #6<<2+24]             @ store w[6]
    add     r1, r7                          @ w[6] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[7], *msg_data++
    rev     r1, r1                          @ w[7]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #7<<2+24]             @ store w[7]
    add     r1, r7                          @ w[7] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[8], *msg_data++
    rev     r1, r1                          @ w[8]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #8<<2+24]             @ store w[8]
    add     r1, r7                          @ w[8] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[9], *msg_data++
    rev     r1, r1                          @ w[9]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp,  #9<<2+24]             @ store w[9]
    add     r1, r7                          @ w[9] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[10], *msg_data++
    rev     r1, r1                          @ w[10]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp, #10<<2+24]             @ store w[10]
    add     r1, r7                          @ w[10] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[11], *msg_data++
    rev     r1, r1                          @ w[11]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp, #11<<2+24]             @ store w[11]
    add     r1, r7                          @ w[11] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[12], *msg_data++
    rev     r1, r1                          @ w[12]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp, #12<<2+24]             @ store w[12]
    add     r1, r7                          @ w[12] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[13], *msg_data++
    rev     r1, r1                          @ w[13]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp, #13<<2+24]             @ store w[13]
    add     r1, r7                          @ w[13] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[14], *msg_data++
    rev     r1, r1                          @ w[14]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp, #14<<2+24]             @ store w[14]
    add     r1, r7                          @ w[14] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    ldmia   r0!, {r1}                       @ m[15], *msg_data++
    rev     r1, r1                          @ w[15]
    str     r6, [r2]                        @ + Ch(), + e
    str     r1, [sp, #15<<2+24]             @ store w[15]
    add     r1, r7                          @ w[15] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift registers

    str     r0, [sp, #348]                  @ store *msg_data
    movs    r3, #31                         @ set the amount to rotate


#   for (j = 0; j < 4; j++)
#   {
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFC,ADRA+CA4);  // + Ch(), + e
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[0];         // + k[0]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA5))  = w[i-16];           // CA5 = w[i-16]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-14];           // xor w[i-14]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-8];            // xor w[i-8]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-3];            // xor w[i-3]
#   *(MMCAU_PPB_INDIRECT + (ROTL+CA5)) = 1;                 // rotate 1
#   w[i++] = *(MMCAU_PPB_INDIRECT + (STR+CA5));             // store w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(ADRA+CA5,SHS);       // + w[i], shift
#   }
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (throughout the second loop)
#   -----------+------------------------------------------------------------
#          r0  |  scratch
#          r1  |  scratch
#          r2  |  *mmcau_direct_cmd()
#          r3  |  amount to rotate = #31
#          r4  |  mmcau_indirect_cmd(ADR+CAA)
#          r5  |  mmcau_1_cmd(SHS)
#          r6  |  mmcau_2_cmds(HASH+HFC,ADRA+CA4)
#          r7  |  k[0]

    str     r6, [r2]                        @ + Ch(), + e
    ldr     r1, [sp,  #0<<2+24]             @ w[0]
    ldr     r0, [sp,  #2<<2+24]             @ w[2]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp,  #8<<2+24]             @ w[8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #13<<2+24]             @ w[13]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #16<<2+24]             @ store w[16]
    add     r1, r7                          @ w[16] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Ch(), + e
    ldr     r1, [sp,  #1<<2+24]             @ w[1]
    ldr     r0, [sp,  #3<<2+24]             @ w[3]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #9<<2+24]              @ w[9]
    eors    r1, r0                          @ XOR w[i-9]
    ldr     r0, [sp, #14<<2+24]             @ w[14]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #17<<2+24]             @ store w[17]
    add     r1, r7                          @ w[17] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Ch(), + e
    ldr     r1, [sp,  #2<<2+24]             @ w[2]
    ldr     r0, [sp,  #4<<2+24]             @ w[4]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #10<<2+24]             @ w[10]
    eors    r1, r0                          @ XOR w[i-9]
    ldr     r0, [sp, #15<<2+24]             @ w[15]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #18<<2+24]             @ store w[18]
    add     r1, r7                          @ w[18] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Ch(), + e
    ldr     r1, [sp,  #3<<2+24]             @ w[3]
    ldr     r0, [sp,  #5<<2+24]             @ w[5]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #11<<2+24]             @ w[11]
    eors    r1, r0                          @ XOR w[i-9]
    ldr     r0, [sp, #16<<2+24]             @ w[16]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #19<<2+24]             @ store w[19]
    add     r1, r7                          @ w[19] + k[0]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    ldr     r1, [sp, #344]                  @ restore *sha1_k
    ldr     r6, =MMCAU_2_CMDS+((HASH+HFP)<<22)+((ADRA+CA4)<<11)
    ldr     r7, [r1, #1<<2]                 @ load k[1]


#   for (j = 0; j < 20; j++)
#   {
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFP,ADRA+CA4);  // + Parity(), + e
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[1];         // + k[1]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA5))  = w[i-16];           // CA5 = w[i-16]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-14];           // xor w[i-14]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-8];            // xor w[i-8]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-3];            // xor w[i-3]
#   *(MMCAU_PPB_INDIRECT + (ROTL+CA5)) = 1;                 // rotate 1
#   w[i++] = *(MMCAU_PPB_INDIRECT + (STR+CA5));             // store w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(ADRA+CA5,SHS);       // + w[i], shift
#   }
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (throughout the third loop)
#   -----------+------------------------------------------------------------
#          r0  |  scratch
#          r1  |  scratch
#          r2  |  *mmcau_direct_cmd()
#          r3  |  amount to rotate = #31
#          r4  |  mmcau_indirect_cmd(ADR+CAA)
#          r5  |  mmcau_1_cmd(SHS)
#          r6  |  mmcau_2_cmds(HASH+HFP,ADRA+CA4)
#          r7  |  k[1]

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp,  #4<<2+24]             @ w[i-16]
    ldr     r0, [sp,  #6<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #12<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #17<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #20<<2+24]             @ store w[20]
    add     r1, r7                          @ w[20] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp,  #5<<2+24]             @ w[i-16]
    ldr     r0, [sp,  #7<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #13<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #18<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #21<<2+24]             @ store w[21]
    add     r1, r7                          @ w[21] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp,  #6<<2+24]             @ w[i-16]
    ldr     r0, [sp,  #8<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #14<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #19<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #22<<2+24]             @ store w[22]
    add     r1, r7                          @ w[22] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp,  #7<<2+24]             @ w[i-16]
    ldr     r0, [sp,  #9<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #15<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #20<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #23<<2+24]             @ store w[23]
    add     r1, r7                          @ w[23] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp,  #8<<2+24]             @ w[i-16]
    ldr     r0, [sp, #10<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #16<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #21<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #24<<2+24]             @ store w[24]
    add     r1, r7                          @ w[24] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp,  #9<<2+24]             @ w[i-16]
    ldr     r0, [sp, #11<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #17<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #22<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #25<<2+24]             @ store w[25]
    add     r1, r7                          @ w[25] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #10<<2+24]             @ w[i-16]
    ldr     r0, [sp, #12<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #18<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #23<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #26<<2+24]             @ store w[26]
    add     r1, r7                          @ w[26] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #11<<2+24]             @ w[i-16]
    ldr     r0, [sp, #13<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #19<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #24<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #27<<2+24]             @ store w[27]
    add     r1, r7                          @ w[27] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #12<<2+24]             @ w[i-16]
    ldr     r0, [sp, #14<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #20<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #25<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #28<<2+24]             @ store w[28]
    add     r1, r7                          @ w[28] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #13<<2+24]             @ w[i-16]
    ldr     r0, [sp, #15<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #21<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #26<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #29<<2+24]             @ store w[29]
    add     r1, r7                          @ w[29] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #14<<2+24]             @ w[i-16]
    ldr     r0, [sp, #16<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #22<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #27<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #30<<2+24]             @ store w[30]
    add     r1, r7                          @ w[30] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #15<<2+24]             @ w[i-16]
    ldr     r0, [sp, #17<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #23<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #28<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #31<<2+24]             @ store w[31]
    add     r1, r7                          @ w[31] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #16<<2+24]             @ w[i-16]
    ldr     r0, [sp, #18<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #24<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #29<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #32<<2+24]             @ store w[32]
    add     r1, r7                          @ w[32] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #17<<2+24]             @ w[i-16]
    ldr     r0, [sp, #19<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #25<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #30<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #33<<2+24]             @ store w[33]
    add     r1, r7                          @ w[33] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #18<<2+24]             @ w[i-16]
    ldr     r0, [sp, #20<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #26<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #31<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #34<<2+24]             @ store w[34]
    add     r1, r7                          @ w[34] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #19<<2+24]             @ w[i-16]
    ldr     r0, [sp, #21<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #27<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #32<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #35<<2+24]             @ store w[35]
    add     r1, r7                          @ w[35] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #20<<2+24]             @ w[i-16]
    ldr     r0, [sp, #22<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #28<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #33<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #36<<2+24]             @ store w[36]
    add     r1, r7                          @ w[36] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #21<<2+24]             @ w[i-16]
    ldr     r0, [sp, #23<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #29<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #34<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #37<<2+24]             @ store w[37]
    add     r1, r7                          @ w[37] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #22<<2+24]             @ w[i-16]
    ldr     r0, [sp, #24<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #30<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #35<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #38<<2+24]             @ store w[38]
    add     r1, r7                          @ w[38] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #23<<2+24]             @ w[i-16]
    ldr     r0, [sp, #25<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #31<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #36<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #39<<2+24]             @ store w[39]
    add     r1, r7                          @ w[39] + k[1]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    ldr     r1, [sp, #344]                  @ restore *sha1_k
    ldr     r6, =MMCAU_2_CMDS+((HASH+HFM)<<22)+((ADRA+CA4)<<11)
    ldr     r7, [r1, #2<<2]                 @ load k[2]
    b       next_blk_continued
    .ltorg


next_blk_continued:

#   for (j = 0; j < 20; j++)
#   {
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFM,ADRA+CA4);  // + Maj(), + e
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[2];         // + k[2]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA5))  = w[i-16];           // CA5 = w[i-16]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-14];           // xor w[i-14]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-8];            // xor w[i-8]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-3];            // xor w[i-3]
#   *(MMCAU_PPB_INDIRECT + (ROTL+CA5)) = 1;                 // rotate 1
#   w[i++] = *(MMCAU_PPB_INDIRECT + (STR+CA5));             // store w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(ADRA+CA5,SHS);       // + w[i], shift
#   }
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (throughout the fourth loop)
#   -----------+------------------------------------------------------------
#          r0  |  scratch
#          r1  |  amount to rotate = #31
#          r2  |  *mmcau_direct_cmd()
#          r3  |  scratch
#          r4  |  mmcau_indirect_cmd(ADR+CAA)
#          r5  |  mmcau_1_cmd(SHS)
#          r6  |  mmcau_2_cmds(HASH+HFP,ADRA+CA4)
#          r7  |  k[2]

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #24<<2+24]             @ w[i-16]
    ldr     r0, [sp, #26<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #32<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #37<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #40<<2+24]             @ store w[40]
    add     r1, r7                          @ w[40] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #25<<2+24]             @ w[i-16]
    ldr     r0, [sp, #27<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #33<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #38<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #41<<2+24]             @ store w[41]
    add     r1, r7                          @ w[41] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #26<<2+24]             @ w[i-16]
    ldr     r0, [sp, #28<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #34<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #39<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #42<<2+24]             @ store w[42]
    add     r1, r7                          @ w[42] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #27<<2+24]             @ w[i-16]
    ldr     r0, [sp, #29<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #35<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #40<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #43<<2+24]             @ store w[43]
    add     r1, r7                          @ w[43] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #28<<2+24]             @ w[i-16]
    ldr     r0, [sp, #30<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #36<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #41<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #44<<2+24]             @ store w[44]
    add     r1, r7                          @ w[44] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #29<<2+24]             @ w[i-16]
    ldr     r0, [sp, #31<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #37<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #42<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #45<<2+24]             @ store w[45]
    add     r1, r7                          @ w[45] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #30<<2+24]             @ w[i-16]
    ldr     r0, [sp, #32<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #38<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #43<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #46<<2+24]             @ store w[46]
    add     r1, r7                          @ w[46] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #31<<2+24]             @ w[i-16]
    ldr     r0, [sp, #33<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #39<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #44<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #47<<2+24]             @ store w[47]
    add     r1, r7                          @ w[47] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #32<<2+24]             @ w[i-16]
    ldr     r0, [sp, #34<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #40<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #45<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #48<<2+24]             @ store w[48]
    add     r1, r7                          @ w[48] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #33<<2+24]             @ w[i-16]
    ldr     r0, [sp, #35<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #41<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #46<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #49<<2+24]             @ store w[49]
    add     r1, r7                          @ w[49] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #34<<2+24]             @ w[i-16]
    ldr     r0, [sp, #36<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #42<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #47<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #50<<2+24]             @ store w[50]
    add     r1, r7                          @ w[50] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #35<<2+24]             @ w[i-16]
    ldr     r0, [sp, #37<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #43<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #48<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #51<<2+24]             @ store w[51]
    add     r1, r7                          @ w[51] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #36<<2+24]             @ w[i-16]
    ldr     r0, [sp, #38<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #44<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #49<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #52<<2+24]             @ store w[52]
    add     r1, r7                          @ w[52] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #37<<2+24]             @ w[i-16]
    ldr     r0, [sp, #39<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #45<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #50<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #53<<2+24]             @ store w[53]
    add     r1, r7                          @ w[53] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #38<<2+24]             @ w[i-16]
    ldr     r0, [sp, #40<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #46<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #51<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #54<<2+24]             @ store w[54]
    add     r1, r7                          @ w[54] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #39<<2+24]             @ w[i-16]
    ldr     r0, [sp, #41<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #47<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #52<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #55<<2+24]             @ store w[55]
    add     r1, r7                          @ w[55] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #40<<2+24]             @ w[i-16]
    ldr     r0, [sp, #42<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #48<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #53<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #56<<2+24]             @ store w[56]
    add     r1, r7                          @ w[56] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #41<<2+24]             @ w[i-16]
    ldr     r0, [sp, #43<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #49<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #54<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #57<<2+24]             @ store w[57]
    add     r1, r7                          @ w[57] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #42<<2+24]             @ w[i-16]
    ldr     r0, [sp, #44<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #50<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #55<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #58<<2+24]             @ store w[58]
    add     r1, r7                          @ w[58] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Maj(), + e
    ldr     r1, [sp, #43<<2+24]             @ w[i-16]
    ldr     r0, [sp, #45<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #51<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #56<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #59<<2+24]             @ store w[59]
    add     r1, r7                          @ w[59] + k[2]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    ldr     r1, [sp, #344]                  @ restore *sha1_k
    ldr     r6, =MMCAU_2_CMDS+((HASH+HFP)<<22)+((ADRA+CA4)<<11)
    ldr     r7, [r1, #3<<2]                 @ load k[3]


#   for (j = 0; j < 20; j++)
#   {
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(HASH+HFP,ADRA+CA4);  // + Par(), + e
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha1_k[3];         // + k[3]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA5))  = w[i-16];           // CA5 = w[i-16]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-14];           // xor w[i-14]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-8];            // xor w[i-8]
#   *(MMCAU_PPB_INDIRECT + (XOR+CA5))  = w[i-3];            // xor w[i-3]
#   *(MMCAU_PPB_INDIRECT + (ROTL+CA5)) = 1;                 // rotate 1
#   w[i++] = *(MMCAU_PPB_INDIRECT + (STR+CA5));             // store w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(ADRA+CA5,SHS);       // + w[i], shift
#   }
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (throughout the fifth/last loop)
#   -----------+------------------------------------------------------------
#          r0  |  scratch
#          r1  |  scratch
#          r2  |  *mmcau_direct_cmd()
#          r3  |  amount to rotate = #31
#          r4  |  mmcau_indirect_cmd(ADR+CAA)
#          r5  |  mmcau_1_cmd(SHS)
#          r6  |  mmcau_2_cmds(HASH+HFP,ADRA+CA4)
#          r7  |  k[3]

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #44<<2+24]             @ w[i-16]
    ldr     r0, [sp, #46<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #52<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #57<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #60<<2+24]             @ store w[60]
    add     r1, r7                          @ w[60] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #45<<2+24]             @ w[i-16]
    ldr     r0, [sp, #47<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #53<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #58<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #61<<2+24]             @ store w[61]
    add     r1, r7                          @ w[61] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #46<<2+24]             @ w[i-16]
    ldr     r0, [sp, #48<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #54<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #59<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #62<<2+24]             @ store w[62]
    add     r1, r7                          @ w[62] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #47<<2+24]             @ w[i-16]
    ldr     r0, [sp, #49<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #55<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #60<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #63<<2+24]             @ store w[63]
    add     r1, r7                          @ w[63] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #48<<2+24]             @ w[i-16]
    ldr     r0, [sp, #50<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #56<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #61<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #64<<2+24]             @ store w[64]
    add     r1, r7                          @ w[64] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #49<<2+24]             @ w[i-16]
    ldr     r0, [sp, #51<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #57<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #62<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #65<<2+24]             @ store w[65]
    add     r1, r7                          @ w[65] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #50<<2+24]             @ w[i-16]
    ldr     r0, [sp, #52<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #58<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #63<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #66<<2+24]             @ store w[66]
    add     r1, r7                          @ w[66] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #51<<2+24]             @ w[i-16]
    ldr     r0, [sp, #53<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #59<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #64<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #67<<2+24]             @ store w[67]
    add     r1, r7                          @ w[67] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #52<<2+24]             @ w[i-16]
    ldr     r0, [sp, #54<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #60<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #65<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #68<<2+24]             @ store w[68]
    add     r1, r7                          @ w[68] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #53<<2+24]             @ w[i-16]
    ldr     r0, [sp, #55<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #61<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #66<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #69<<2+24]             @ store w[69]
    add     r1, r7                          @ w[69] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #54<<2+24]             @ w[i-16]
    ldr     r0, [sp, #56<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #62<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #67<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #70<<2+24]             @ store w[70]
    add     r1, r7                          @ w[70] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #55<<2+24]             @ w[i-16]
    ldr     r0, [sp, #57<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #63<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #68<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #71<<2+24]             @ store w[71]
    add     r1, r7                          @ w[71] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #56<<2+24]             @ w[i-16]
    ldr     r0, [sp, #58<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #64<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #69<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #72<<2+24]             @ store w[72]
    add     r1, r7                          @ w[72] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #57<<2+24]             @ w[i-16]
    ldr     r0, [sp, #59<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #65<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #70<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #73<<2+24]             @ store w[73]
    add     r1, r7                          @ w[73] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #58<<2+24]             @ w[i-16]
    ldr     r0, [sp, #60<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #66<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #71<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #74<<2+24]             @ store w[74]
    add     r1, r7                          @ w[74] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #59<<2+24]             @ w[i-16]
    ldr     r0, [sp, #61<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #67<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #72<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #75<<2+24]             @ store w[75]
    add     r1, r7                          @ w[75] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #60<<2+24]             @ w[i-16]
    ldr     r0, [sp, #62<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #68<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #73<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #76<<2+24]             @ store w[76]
    add     r1, r7                          @ w[76] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #61<<2+24]             @ w[i-16]
    ldr     r0, [sp, #63<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #69<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #74<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #77<<2+24]             @ store w[77]
    add     r1, r7                          @ w[77] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #62<<2+24]             @ w[i-16]
    ldr     r0, [sp, #64<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #70<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #75<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #78<<2+24]             @ store w[78]
    add     r1, r7                          @ w[78] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

    str     r6, [r2]                        @ + Par(), + e
    ldr     r1, [sp, #63<<2+24]             @ w[i-16]
    ldr     r0, [sp, #65<<2+24]             @ w[i-14]
    eors    r1, r0                          @ XOR w[i-14]
    ldr     r0, [sp, #71<<2+24]             @ w[i-8]
    eors    r1, r0                          @ XOR w[i-8]
    ldr     r0, [sp, #76<<2+24]             @ w[i-3]
    eors    r1, r0                          @ XOR w[i-3]
    rors    r1, r3                          @ rotate left by 1
    str     r1, [sp, #79<<2+24]             @ store w[79]
    add     r1, r7                          @ w[79] + k[3]
    str     r1, [r4]                        @ add sum to CAA
    str     r5, [r2]                        @ shift regs

# after going through the loops
    add     r3, sp, #0                      @ get *sha1_state (on stack)
    ldr     r1, =MMCAU_PPB_INDIRECT+((ADR+CA0)<<2)
    ldmia   r3, {r3-r7}                     @ load sha1_state[0-4]
    stmia   r1!, {r3-r7}                    @ add to CA[0-4]
    subs    r1, #84                         @ mmcau_indirect_cmd(STR+CA0)
    ldmia   r1!, {r3-r7}                    @ load sums

# find out if next_blk should be repeated
    ldr     r1, [sp, #352]                  @ restore num_blks
    subs    r1, #1                          @ decrement num_blks
    bne     next_blk_repeat                 @ check num_blks

# if num_blks = 0,
    ldr     r2, [sp, #356]                  @ restore *sha1_state
    stmia   r2!, {r3-r7}                    @ store CA[0-4] to sha1_state[0-4]
    add     sp, #360                        @ unreserve stack
    pop     {r4-r7}                         @ restore regs
    bx      lr                              @ exit routine

# else,
next_blk_repeat:
    ldr     r0, [sp, #348]                  @ restore *msg_data
    str     r1, [sp, #352]                  @ store num_blks
    b       next_blk                        @ repeat next_blk


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_SHA1_UPDATE
#   Updates SHA1 state variables for one or more input message blocks
#
#   ARGUMENTS   
#   *msg_data       pointer to start of input message data
#   num_blks        number of 512-bit blocks to process
#   *sha1_state     pointer to 160-bit block of SHA1 state variables: a,b,c,d,e
#
#   CALLING CONVENTION
#   void mmcau_sha1_update     (const unsigned char     *msg_data,
#                               const int               num_blks,
#                               unsigned int            *sha1_state)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_sha1_update)
#   -----------+------------------------------------------------------------
#          r0  |  *msg_data     (arg0)
#          r1  |  num_blks      (arg1)
#          r2  |  *sha1_state   (arg2)
#              |
#        > r2  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_sha1_update
    .global mmcau_sha1_update
    .type   mmcau_sha1_update, %function
    .align  4

_mmcau_sha1_update:
mmcau_sha1_update:

# store regs r4-r7 and r14, we need to restore them at the end of the routine
    push    {r4-r7, lr}                     @ store regs

    ldr     r3, =sha1_initial_h
    ldmia   r3, {r3-r7}                     @ load sha1_initial_h[0-4]
    stmia   r2!, {r3-r7}                    @ store in sha1_state[0-4]
    subs    r2, #5<<2                       @ reset *sha1_state

    bl      mmcau_sha1_hash_n               @ do mmcau_sha1_hash_n

    pop     {r4-r7, pc}                     @ restore regs, exit routine


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_SHA1_HASH
#   Perform the hash and generate SHA1 state variables for one input message 
#   block
#
#   ARGUMENTS
#   *msg_data       pointer to start of input message data
#   *sha1_state     pointer to 160-bit block of SHA1 state variables: a,b,c,d,e
#
#   NOTE
#   Input message and digest output blocks must not overlap
#
#   CALLING CONVENTION
#   void mmcau_sha1_hash    (const unsigned char    *msg_data,
#                           unsigned int            *sha1_state)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_sha1_hash_n)
#   -----------+------------------------------------------------------------
#          r0  |  *msg_data     (arg0)
#          r1  |  *sha1_state   (arg1)
#              |
#        > r1  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_sha1_hash
    .global mmcau_sha1_hash
    .type   mmcau_sha1_hash, %function
    .align  4

_mmcau_sha1_hash:
mmcau_sha1_hash:

    mov     r2, r1                          @ move arg1 (*sha1_state) to arg2
    movs    r1, #1                          @ set arg1 (num_blks) = 1

    ldr     r3, =mmcau_sha1_hash_n+1
    bx      r3                              @ do mmcau_sha1_hash_n


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .data


    .type   sha1_initial_h, %object
    .align  4

sha1_initial_h:
    .word   0x67452301  @ initial a
    .word   0xefcdab89  @ initial b
    .word   0x98badcfe  @ initial c
    .word   0x10325476  @ initial d
    .word   0xc3d2e1f0  @ initial e


    .type   sha1_k, %object
    .align  4

sha1_k:
    .word   0x5a827999
    .word   0x6ed9eba1
    .word   0x8f1bbcdc
    .word   0xca62c1d6
