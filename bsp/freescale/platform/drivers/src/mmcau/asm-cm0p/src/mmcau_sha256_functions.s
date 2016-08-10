# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# Copyright (c) Freescale Semiconductor, Inc 2013.
#
# FILE NAME         : mmcau_sha256_functions.s
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
    .equ          MMCAU_3_CMDS, 0x80100200


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_SHA256_INITIALIZE_OUTPUT
#   Initializes the hash output and checks the CAU hardware revision
#   
#   ARGUMENTS
#   *output         pointer to 256-bit message digest output
#
#   CALLING CONVENTION
#   int mmcau_sha256_initialize_output (const unsigned int *output)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_sha256_initialize_output)
#   -----------+------------------------------------------------------------
#          r0  |  *output       (arg0)
#              |
#        > r0  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_sha256_initialize_output
    .global mmcau_sha256_initialize_output
    .type   mmcau_sha256_initialize_output, %function
    .align  4

_mmcau_sha256_initialize_output:
mmcau_sha256_initialize_output:

# store regs r4-r7, we need to restore them at the end of the routine
    push    {r4-r7}                         @ store regs

    ldr     r3, =sha256_initial_h
    ldmia   r3!, {r4-r7}                    @ load sha256_initial_h[0-3]
    stmia   r0!, {r4-r7}                    @ store in output[0-3]
    ldmia   r3!, {r4-r7}                    @ load sha256_initial_h[4-7]
    stmia   r0!, {r4-r7}                    @ store in output[4-7]

    movs    r0, #0                          @ clear the return value
    pop     {r4-r7}                         @ restore regs
    bx      lr                              @ exit routine


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_SHA256_HASH_N
#   Perform the hash for one or more input message blocks and generate the
#   message digest output
#
#   ARGUMENTS
#   *input          pointer to start of input message data
#   num_blks        number of 512-bit blocks to process
#   *output         pointer to 256-bit message digest
#
#   NOTE
#   Input message and digest output blocks must not overlap
#
#   CALLING CONVENTION
#   void mmcau_sha256_hash_n   (const unsigned char     *input,
#                               const int               num_blks,
#                               unsigned int            *output)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_sha256_hash_n)
#   -----------+------------------------------------------------------------
#          r0  |  *input        (arg0)
#          r1  |  num_blks      (arg1)
#          r2  |  *output       (arg2)
#
#        > r2  |  irrelevant
#
#
#       STACK  |  ALLOCATION (throughout mmcau_sha256_hash_n)
#   -----------+------------------------------------------------------------
#        #268  |  *output
#        #264  |  num_blks
#        #260  |  *input
#        #256  |  mmcau_3_cmds(ADRA+CA7,HASH+HF2T,HASH+HF2C)
#    #64-#252  |  w[i] in loop
#      #0-#60  |  w[0-15] in next_blk
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_sha256_hash_n
    .global mmcau_sha256_hash_n
    .type   mmcau_sha256_hash_n, %function
    .align  4

_mmcau_sha256_hash_n:
mmcau_sha256_hash_n:

# store *input, num_blks, and *output, we need them later in the routine
# store regs r4-r10, we need to restore them at the end of the routine
    push    {r4-r7, lr}     @ store low regs and link reg
    mov     r3, r8
    mov     r4, r9
    mov     r5, sl
    mov     r6, fp
    mov     r7, ip
    push    {r0-r2, r3-r7}  @ store *input, num_blks, *output, high regs

    sub     sp, #260        @ reserve stack

# initialize the CAU data regs with the current contents of output[0-7]
    ldr     r1, =MMCAU_PPB_INDIRECT+((LDR+CA0)<<2)
    ldmia   r2!, {r4-r7}                    @ load output[0-3]
    stmia   r1!, {r4-r7}                    @ store in CA[0-3]
    ldmia   r2!, {r4-r7}                    @ load output[4-7]
    stmia   r1!, {r4-r7}                    @ store in CA[4-7]

# prepare for next_blk
    ldr     r1, =sha256_reg_data+3<<2       @ get *sha256_reg_data[3]
    ldmia   r1, {r1-r7}                     @ load sha256_reg_data[3-9]
    mov     r9, r5                          @ store mmcau_indirect_cmd(LDR+CAA)
    mov     sl, r6                          @ store mmcau_indirect_cmd(ADR+CAA)
    mov     fp, r7                          @ store mmcau_indirect_cmd(STR+CAA)
    ldr     r5, =MMCAU_PPB_DIRECT


    .align  2
next_blk:

#   i = 0;
#       for (j = 0; j < 16; j++, i++)
#       {
#           w[i] = byterev(input[i]);                   // copy m[i] to w[i]
#           *(MMCAU_PPB_INDIRECT + (LDR+CAA)) = w[i];   // +w[i]+h+SIGMA1(e)
#                                                       // add Ch(e,f,g)
#           *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(ADRA+CA7,HASH+HF2T,HASH+HF2C);
#                                                       // +k[i]+t1+SIGMA0(e)
#           *(MMCAU_PPB_INDIRECT + (ADR+CAA)) = sha256_k[i];
#                                                       // add Maj(a,b,c)
#           *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(MVAR+CA8,HASH+HF2S,HASH+HF2M);
#           *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(SHS2);    // shift regs
#       }
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (throughout next_blk)
#   -----------+------------------------------------------------------------
#          r0  |  *input
#          r1  |  mmcau_1_cmd(SHS2)
#          r2  |  mmcau_3_cmds(MVAR+CA8,HASH+HF2S,HASH+HF2M)
#          r3  |  mmcau_3_cmds(ADRA+CA7,HASH+HF2T,HASH+HF2C)
#          r4  |  *sha256_k
#          r5  |  *mmcau_direct_cmd()
#          r6  |  scratch
#          r7  |  scratch
#          r8  |  not used
#          r9  |  mmcau_indirect_cmd(LDR+CAA)
#    (sl) r10  |  mmcau_indirect_cmd(ADR+CAA)
#    (fp) r11  |  mmcau_indirect_cmd(STR+CAA)
#    (ip) r12  |  mmcau_1_cmd(SHS2)
#    (sp) r13  |  stack pointer
#    (lr) r14  |  mmcau_3_cmds(ADRA+CA7,HASH+HF2T,HASH+HF2M)

    ldmia   r0!, {r7}                       @ m[0], *input++
    rev     r7, r7                          @ w[0]
    str     r7, [sp, #0<<2]                 @ store w[0]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[i]
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    ldmia   r4!, {r7}                       @ k[0], *sha256_k++
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[0]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[1], *input++
    rev     r7, r7                          @ w[1]
    str     r7, [sp, #1<<2]                 @ store w[1]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[1]
    ldmia   r4!, {r7}                       @ k[1], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[1]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[2], *input++
    rev     r7, r7                          @ w[2]
    str     r7, [sp, #2<<2]                 @ store w[2]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[2]
    ldmia   r4!, {r7}                       @ k[2], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[2]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[3], *input++
    rev     r7, r7                          @ w[3]
    str     r7, [sp, #3<<2]                 @ store w[3]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[3]
    ldmia   r4!, {r7}                       @ k[3], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[3]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[4], *input++
    rev     r7, r7                          @ w[4]
    str     r7, [sp, #4<<2]                 @ store w[4]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[4]
    ldmia   r4!, {r7}                       @ k[4], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[4]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[5], *input++
    rev     r7, r7                          @ w[5]
    str     r7, [sp, #5<<2]                 @ store w[5]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[5]
    ldmia   r4!, {r7}                       @ k[5], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[5]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[6], *input++
    rev     r7, r7                          @ w[6]
    str     r7, [sp, #6<<2]                 @ store w[6]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[6]
    ldmia   r4!, {r7}                       @ k[6], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[6]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[7], *input++
    rev     r7, r7                          @ w[7]
    str     r7, [sp, #7<<2]                 @ store w[7]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[7]
    ldmia   r4!, {r7}                       @ k[7], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[7]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[8], *input++
    rev     r7, r7                          @ w[8]
    str     r7, [sp, #8<<2]                 @ store w[8]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[8]
    ldmia   r4!, {r7}                       @ k[8], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[8]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[9], *input++
    rev     r7, r7                          @ w[9]
    str     r7, [sp, #9<<2]                 @ store w[9]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[9]
    ldmia   r4!, {r7}                       @ k[9], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[9]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[10], *input++
    rev     r7, r7                          @ w[10]
    str     r7, [sp, #10<<2]                @ store w[10]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[10]
    ldmia   r4!, {r7}                       @ k[10], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[10]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[11], *input++
    rev     r7, r7                          @ w[11]
    str     r7, [sp, #11<<2]                @ store w[11]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[11]
    ldmia   r4!, {r7}                       @ k[11], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[11]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[12], *input++
    rev     r7, r7                          @ w[12]
    str     r7, [sp, #12<<2]                @ store w[12]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[12]
    ldmia   r4!, {r7}                       @ k[12], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[12]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[13], *input++
    rev     r7, r7                          @ w[13]
    str     r7, [sp, #13<<2]                @ store w[13]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[13]
    ldmia   r4!, {r7}                       @ k[13], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[13]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[14], *input++
    rev     r7, r7                          @ w[14]
    str     r7, [sp, #14<<2]                @ store w[14]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[14]
    ldmia   r4!, {r7}                       @ k[14], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[14]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

    ldmia   r0!, {r7}                       @ m[15], *input++
    rev     r7, r7                          @ w[15]
    str     r7, [sp, #15<<2]                @ store w[15]
    mov     r6, r9                          @ mmcau_indirect_cmd(LDR+CAA)
    str     r7, [r6]                        @ add w[15]
    ldmia   r4!, {r7}                       @ k[15], *sha256_k++
    str     r3, [r5]                        @ +h, +SIGMA1(e), +Ch(e,f,g)
    mov     r6, sl                          @ mmcau_indirect_cmd(ADR+CAA)
    str     r7, [r6]                        @ add k[15]
    str     r2, [r5]                        @ t1, +SIGMA0(e), +Maj(a,b,c)
    str     r1, [r5]                        @ shift registers

# prepare for loop
    str     r0, [sp, #260]                  @ store *input
    mov     ip, r1                          @ store SHS2
    mov     lr, r2                          @ store HF2M
    str     r3, [sp, #256]                  @ store HF2C
    ldr     r0, =sha256_reg_data            @ get *sha256_reg_data
    ldmia   r0, {r0-r2}                     @ load sha256_reg_data[0-2]
    add     r3, sp, #0                      @ get *w[0]
    movs    r6, #48                         @ set number of loops = 48


loop:

#   for (j = 0; j < 48; j++, i++)
#   {
#   *(MMCAU_PPB_INDIRECT + (LDR+CAA))  = w[i-16];       // [i-16]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA8))  = w[i-15];       // [i-15]
#   *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(HASH+HF2U);       // + Sigma2(w[i-15])
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = w[i-7];        // add w[i-7]
#   *(MMCAU_PPB_INDIRECT + (LDR+CA8))  = w[i-2];        // load w[i-2]
#   *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(HASH+HF2V);       // + Sigma1(w[i-2])
#   w[i] = *(MMCAU_PPB_INDIRECT + (STR+CAA));           // store w[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(ADRA+CA7,HASH+HF2T,HASH+HF2C);
#   *(MMCAU_PPB_INDIRECT + (ADR+CAA))  = sha256_k[i];   // add k[i]
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(MVAR+CA8,HASH+HF2S,HASH+HF2M);
#   *(MMCAU_PPB_DIRECT) = mmcau_1_cmd(SHS2);            // shift registers
#   }
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION
#   -----------+------------------------------------------------------------
#          r0  |  mmcau_1_cmd(HASH+HF2U)
#          r1  |  mmcau_1_cmd(SHS2)
#          r2  |  mmcau_indirect_cmd(LDR+CA8)
#          r3  |  *w[0]
#          r4  |  *sha256_k
#          r5  |  *mmcau_direct_cmd()
#          r6  |  scratch
#          r7  |  scratch
#          r8  |  loop count
#          r9  |  mmcau_indirect_cmd(LDR+CAA)
#    (sl) r10  |  mmcau_indirect_cmd(ADR+CAA)
#    (fp) r11  |  mmcau_indirect_cmd(STR+CAA)
#    (ip) r12  |  mmcau_1_cmd(SHS2)
#    (sp) r13  |  stack pointer
#    (lr) r14  |  mmcau_3_cmds(ADRA+CA7,HASH+HF2T,HASH+HF2M)

    mov     r8, r6                          @ store loop count
    ldmia   r3!, {r6}                       @ w[i-16], *w[0]++
    mov     r7, r9                          @ (LDR+CAA)
    str     r6, [r7]                        @ CAA += w[i-16]
    ldr     r6, [r3, #0<<2]                 @ w[i-15]
    str     r6, [r2]                        @ CA8 += w[i-15]
    str     r0, [r5]                        @ (HASH+HF2U)
    ldr     r6, [r3, #8<<2]                 @ w[i-7]
    mov     r7, sl                          @ (ADR+CAA)
    str     r6, [r7]                        @ CAA += w[i-7]
    ldr     r6, [r3, #13<<2]                @ w[i-2]
    str     r6, [r2]                        @ CA8 += w[i-2]
    str     r1, [r5]                        @ (HASH+HF2V)
    mov     r7, fp                          @ (STR+CAA)
    ldr     r6, [r7]                        @ w[i]
    str     r6, [r3, #15<<2]                @ store w[i]
    ldr     r7, [sp, #256]                  @ (ADRA+CA7,HASH+HF2T,HASH+HF2C)
    str     r7, [r5]                        @ +h, SIGMA1(e) & Ch(e,f,g)
    ldmia   r4!, {r6}                       @ k[i], *sha256_k++
    mov     r7, sl                          @ (ADR+CAA)
    str     r6, [r7]                        @ add k[i]
    mov     r7, lr                          @ (MVAR+CA8,HASH+HF2S,HASH+HF2M)
    str     r7, [r5]                        @ t1, + SIGMA0(e) + Maj(a,b,c)
    mov     r7, ip                          @ (SHS2)
    str     r7, [r5]                        @ shift reGs


# find out if loop should be repeated
    mov     r6, r8                          @ restore loop count
    subs    r6, #1                          @ decrement loop count
    bne     loop                            @ check loop count

# after going through the loop for the last time
    ldr     r2, =MMCAU_PPB_INDIRECT+((ADR+CA0)<<2)
    ldr     r3, [sp, #268]                  @ restore *output
    ldmia   r3!, {r4-r7}                    @ load output[0-3]
    stmia   r2!, {r4-r7}                    @ add to CA[0-3]
    ldmia   r3!, {r4-r7}                    @ load output[4-7]
    stmia   r2!, {r4-r7}                    @ add to CA[4-7]
    subs    r2, #96                         @ mmcau_indirect_cmd(STR+CA0)
    subs    r3, #8<<2                       @ reset *output
    ldmia   r2!, {r4-r7}                    @ load new CA[0-3]
    stmia   r3!, {r4-r7}                    @ store in output[0-3]
    ldmia   r2!, {r4-r7}                    @ load new CA[4-7]
    stmia   r3!, {r4-r7}                    @ store in output[4-7]


# find out if next_blk should be repeated
    ldr     r1, [sp, #264]                  @ restore num_blks
    subs    r1, #1                          @ decrement num_blks
    bne     repeat_next_blk                 @ check num_blks

# if num_blks = 0,
    add     sp, #272                        @ unreserve stack
    pop     {r3-r7}                         @ restore high regs
    mov     r8, r3
    mov     r9, r4
    mov     sl, r5
    mov     fp, r6
    mov     ip, r7
    pop     {r4-r7, pc}                     @ restore low regs, exit routine

# else (num_blks > 0),
repeat_next_blk:
    str     r1, [sp, #264]                  @ store num_blks
    ldr     r0, [sp, #260]                  @ restore *input
    ldr     r1, =sha256_reg_data+3<<2       @ get *sha256_reg_data[3]
    ldmia   r1, {r1-r4}                     @ load sha256_reg_data[3-6]
    ldr     r5, =MMCAU_PPB_DIRECT
    b       next_blk                        @ repeat next_blk


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_SHA256_UPDATE
#   Updates SHA256 state variables for one or more input message blocks
#
#   ARGUMENTS
#   *input          pointer to start of input message data
#   num_blks        number of 512-bit blocks to process
#   *output         pointer to 256-bit message digest
#
#   CALLING CONVENTION
#   void mmcau_sha256_update   (const unsigned char     *input,
#                               const int               num_blks,
#                               unsigned int            *output)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#   
#    REGISTER  |  ALLOCATION (at the start of mmcau_sha256_update)
#   -----------+------------------------------------------------------------
#          r0  |  *input        (arg0)
#          r1  |  num_blks      (arg1)
#          r2  |  *output       (arg2)
#              |
#        > r2  |  irrelevant  
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_sha256_update
    .global mmcau_sha256_update
    .type   mmcau_sha256_update, %function
    .align  4

_mmcau_sha256_update:
mmcau_sha256_update:

# store regs r4-r7 and r14, we need to restore them at the end of the routine
    push    {r4-r7, lr}                     @ store regs

    ldr     r3, =sha256_initial_h
    ldmia   r3!, {r4-r7}                    @ load sha256_initial_h[0-3]
    stmia   r2!, {r4-r7}                    @ store in output[0-3]
    ldmia   r3!, {r4-r7}                    @ load sha256_initial_h[4-7]
    stmia   r2!, {r4-r7}                    @ store in output[4-7]
    subs    r2, #32                         @ reset *output

    bl      mmcau_sha256_hash_n             @ do mmcau_sha256_hash_n

    pop     {r4-r7, pc}                     @ restore regs, exit routine


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_SHA256_HASH
#   Perform the hash and generate SHA256 state variables for one input
#   Message block.
#
#   ARGUMENTS
#   *input          pointer to start of input message data
#   *output         pointer to 256-bit message digest
#
#   NOTE
#   Input message and digest output blocks must not overlap
#
#   CALLING CONVENTION
#   void mmcau_sha256_hash     (const unsigned char     *input, 
#                               unsigned int            *output)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#   
#    REGISTER  |  ALLOCATION (at the start of mmcau_sha256_hash)
#   -----------+------------------------------------------------------------
#          r0  |  *input        (arg0)
#          r1  |  *output       (arg1)
#              |
#        > r1  |  irrelevant  
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_sha256_hash
    .global mmcau_sha256_hash
    .type   mmcau_sha256_hash, %function
    .align  4

_mmcau_sha256_hash:
mmcau_sha256_hash:

    mov     r2, r1                          @ move arg1 (*output) to arg2
    movs    r1, #1                          @ set arg1 (num_blks) = 1

    b       mmcau_sha256_hash_n             @ do mmcau_sha256_hash_n


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .data


    .type   sha256_reg_data, %object
    .align  4

sha256_reg_data:
    .word   MMCAU_1_CMD+((HASH+HF2U)<<22)                               @ r0
    .word   MMCAU_1_CMD+((HASH+HF2V)<<22)                               @ r1
    .word   MMCAU_PPB_INDIRECT+((LDR+CA8)<<2)                           @ r2
    .word   MMCAU_1_CMD+((SHS2)<<22)                                    @ r1
    .word   MMCAU_3_CMDS+((MVAR+CA8)<<22)+((HASH+HF2S)<<11)+HASH+HF2M   @ r2
    .word   MMCAU_3_CMDS+((ADRA+CA7)<<22)+((HASH+HF2T)<<11)+HASH+HF2C   @ r3
    .word   sha256_k                                                    @ r4
    .word   MMCAU_PPB_INDIRECT+((LDR+CAA)<<2)                           @ r5
    .word   MMCAU_PPB_INDIRECT+((ADR+CAA)<<2)                           @ r6
    .word   MMCAU_PPB_INDIRECT+((STR+CAA)<<2)                           @ r7


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
