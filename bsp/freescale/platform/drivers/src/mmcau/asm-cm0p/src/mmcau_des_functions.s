# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# Copyright (c) Freescale Semiconductor, Inc 2013.
#
# FILE NAME         : mmcau_des_functions.s
# VERSION           : $Id:  $
# TYPE              : Source Cortex-M0+ assembly library code
# DEPARTMENT        : MCG R&D Cores and Platforms
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
    .equ          MMCAU_3_CMDS, 0x80100200


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_DES_CHK_PARITY
#   Check key parity
#
#   ARGUMENTS
#   *key            pointer to 64-bit DES key with parity bits
#    return         0   no error
#                  -1   parity error
#
#   CALLING CONVENTION
#   int mmcau_des_chk_parity (const unsigned char *key)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_des_chk_parity)
#   -----------+------------------------------------------------------------
#          r0  |  *key          (arg0)
#              |
#        > r0  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global     _mmcau_des_chk_parity
    .global     mmcau_des_chk_parity
    .type       mmcau_des_chk_parity, %function
    .align      4

_mmcau_des_chk_parity:
mmcau_des_chk_parity:

# load the 64-bit key into the CAU's CA0/CA1 regs
    ldr     r3, =MMCAU_PPB_INDIRECT+((LDR+CA0)<<2)
    ldmia   r0!, {r1-r2}                    @ load key
    str     r1, [r3, #0<<2]                 @ store lower half in CA0
    str     r2, [r3, #1<<2]                 @ store upper half in CA1

    ldr     r1, =MMCAU_PPB_DIRECT
    ldr     r2, =MMCAU_1_CMD+((DESK+CP)<<22)
    str     r2, [r1]                        @ perform the key schedule

# CASR[31:28] contain the version number, we left-shift that off
# CASR[27:2] and CASR[0] are always 0
# CASR[1] is the DPE bit, which equals 1 if parity error or 0 if no error
    ldr     r0, [r3, #(((STR+CASR)-(LDR+CA0))<<2)]  @ load CASR
    lsls    r0, #4                                  @ shift off version number
    beq     mmcau_des_chk_parity_end                @ check the DPE bit

# if parity error,
    movs    r0, #1
    negs    r0, r0                                  @ return -1

# else (no error),
mmcau_des_chk_parity_end: 
    bx  lr                                          @ return 0


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_DES_ENCRYPT
#   Encrypts a single 8-byte block
#
#   ARGUMENTS
#   *in             pointer to 8-byte block of input plaintext
#   *key            pointer to 64-bit DES key with parity bits
#   *out            pointer to 8-byte block of output ciphertext
#
#   NOTE
#   Input and output blocks may overlap
#
#   CALLING CONVENTION
#   void mmcau_des_encrypt     (const unsigned char     *in,
#                               const unsigned char     *key,
#                               unsigned char           *out)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_des_encrypt)
#   -----------+------------------------------------------------------------
#          r0  |  *in           (arg0)
#          r1  |  *key          (arg1)
#          r2  |  *out          (arg2)
#              |
#        > r2  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_des_encrypt
    .global mmcau_des_encrypt
    .type   mmcau_des_encrypt, %function
    .align  4

_mmcau_des_encrypt:
mmcau_des_encrypt:

# store regs r4-r7, we need to restore them at the end of the routine
    push    {r4-r7}                         @ store regs

# load the 64-bit key into the CAU's CA0/CA1 regs
# load the 64-bit plaintext input block into the CAU's CA2/CA3 regs
    ldr     r7, =MMCAU_PPB_INDIRECT+((LDR+CA0)<<2)
    ldmia   r1!, {r3-r4}                    @ load key
    rev     r3, r3
    rev     r4, r4
    ldmia   r0!, {r5-r6}                    @ load plaintext
    rev     r5, r5
    rev     r6, r6
    stmia   r7!, {r3-r6}                    @ store in CA[0-3]

# send a series of 17 direct cau commands to perform the DES round operations
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESK,DESR+IP+KSL1,DESR+KSL2)      1- 3
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL2)    4- 6
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL1)    7- 9
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL2)   10-12
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL2)   13-15
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(DESR+KSL1,DESR+FP)               16-17
    ldr     r0, =encrypt_reg_data
    ldmia   r0, {r0-r1, r3-r6}              @ load commands
    str     r3, [r0]                        @ send commands  1- 3
    str     r4, [r0]                        @    " "         4- 6
    str     r5, [r0]                        @    " "         7- 9
    str     r4, [r0]                        @    " "        10-12
    str     r4, [r0]                        @    " "        13-15
    str     r6, [r0]                        @    " "        16-17

# store the 64-bit ciphertext output block into memory
    ldmia   r1, {r0-r1}                     @ load ciphertext
    rev     r0, r0
    rev     r1, r1
    stmia   r2!, {r0-r1}                    @ store in out[0-1]

    pop     {r4-r7}                         @ restore regs
    bx      lr                              @ exit routine


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_DES_DECRYPT
#   Decrypts a single 8-byte block
#
#   ARGUMENTS
#   *in             pointer to 8-byte block of input ciphertext
#   *key            pointer to 64-bit DES key with parity bits
#   *out            pointer to 8-byte block of output plaintext
#
#   NOTE
#   Input and output blocks may overlap
#
#   CALLING CONVENTION
#   void mmcau_des_decrypt     (const unsigned char     *in,
#                               const unsigned char     *key,
#                               unsigned char           *out)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_des_decrypt)
#   -----------+------------------------------------------------------------
#          r0  |  *in           (arg0)
#          r1  |  *key          (arg1)
#          r2  |  *out          (arg2)
#              |
#        > r2  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_des_decrypt
    .global mmcau_des_decrypt
    .type   mmcau_des_decrypt, %function
    .align  4

_mmcau_des_decrypt:
mmcau_des_decrypt:

# store regs r4-r7, we need to restore them at the end of the routine
    push    {r4-r7}                         @ store regs

# load the 64-bit key into the CAU's CA0/CA1 regs
# load the 64-bit ciphertext input block into the CAU's CA2/CA3 regs
    ldr     r7, =MMCAU_PPB_INDIRECT+((LDR+CA0)<<2)
    ldmia   r1!, {r3-r4}                    @ load key
    rev     r3, r3
    rev     r4, r4
    ldmia   r0!, {r5-r6}                    @ load ciphertext
    rev     r5, r5
    rev     r6, r6
    stmia   r7!, {r3-r6}                    @ store in CA[0-3]

# send a series of 17 direct cau commands to perform the DES round operations
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESK+DC,DESR+IP+KSR1,DESR+KSR2)   1- 3
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR2)    4- 6
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR1)    7- 9
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR2)   10-12
#   *(MMCAU_PPB_DIRECT) = mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR2)   13-15
#   *(MMCAU_PPB_DIRECT) = mmcau_2_cmds(DESR+KSR1,DESR+FP)               16-17
    ldr     r0, =decrypt_reg_data
    ldmia   r0, {r0-r1, r3-r6}              @ load commands
    str     r3, [r0]                        @ send commands  1- 3
    str     r4, [r0]                        @    " "         4- 6
    str     r5, [r0]                        @    " "         7- 9
    str     r4, [r0]                        @    " "        10-12
    str     r4, [r0]                        @    " "        13-15
    str     r6, [r0]                        @    " "        16-17

# store the 64-bit plaintext output block into memory
    ldmia   r1, {r0-r1}                     @ load plaintext
    rev     r0, r0
    rev     r1, r1
    stmia   r2!, {r0-r1}                    @ store in out[0-1]

    pop     {r4-r7}                         @ restore regs
    bx      lr                              @ exit routine


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .data


    .type   encrypt_reg_data, %object
    .align  4

encrypt_reg_data:
    .word   MMCAU_PPB_DIRECT                                            @ r0
    .word   MMCAU_PPB_INDIRECT+((STR+CA2)<<2)                           @ r1
    .word   MMCAU_3_CMDS+((DESK)<<22)+((DESR+IP+KSL1)<<11)+DESR+KSL2    @ r3
    .word   MMCAU_3_CMDS+((DESR+KSL2)<<22)+((DESR+KSL2)<<11)+DESR+KSL2  @ r4
    .word   MMCAU_3_CMDS+((DESR+KSL2)<<22)+((DESR+KSL2)<<11)+DESR+KSL1  @ r5
    .word   MMCAU_2_CMDS+((DESR+KSL1)<<22)+((DESR+FP)<<11)              @ r6


    .type   decrypt_reg_data, %object
    .align  4

decrypt_reg_data:
    .word   MMCAU_PPB_DIRECT                                            @ r0
    .word   MMCAU_PPB_INDIRECT+((STR+CA2)<<2)                           @ r1
    .word   MMCAU_3_CMDS+((DESK+DC)<<22)+((DESR+IP+KSR1)<<11)+DESR+KSR2	@ r3
    .word   MMCAU_3_CMDS+((DESR+KSR2)<<22)+((DESR+KSR2)<<11)+DESR+KSR2  @ r4
    .word   MMCAU_3_CMDS+((DESR+KSR2)<<22)+((DESR+KSR2)<<11)+DESR+KSR1  @ r5
    .word   MMCAU_2_CMDS+((DESR+KSR1)<<22)+((DESR+FP)<<11)              @ r6
