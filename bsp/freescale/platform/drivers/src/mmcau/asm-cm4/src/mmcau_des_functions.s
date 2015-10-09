#*******************************************************************************
#*******************************************************************************
#
# Copyright (c) Freescale Semiconductor, Inc 2011.
#
# FILE NAME      : mmcau_des_functions.s
# VERSION        : $Id: mmcau_des_functions.s.rca 1.4 Thu Nov 21 14:17:23 2013 b40907 Experimental $
# TYPE           : Source Cortex-Mx assembly library code
# DEPARTMENT     : MSG R&D Core and Platforms
# AUTHOR         : David Schimke
# AUTHOR'S EMAIL : David.Schimke@freescale.com
# AUTHOR         : Anthony (Teejay) Ciancio
# AUTHOR'S EMAIL : teejay.ciancio@freescale.com
# -----------------------------------------------------------------------------
# Release history
# VERSION  Date       AUTHOR           DESCRIPTION
#          08-2010    David Schimke    Initial Release
#          12-2010    David Schimke    Remove "global" on data objects
#          01-2011    David Schimke    Add byte reverse to correct double word
#                                      read of byte arrays for little endian,
#                                      header added
#          11-2013    Teejay Ciancio   Small performance improvements to
#                                      encrypt and decrypt
#
#*******************************************************************************
#*******************************************************************************

    .include "cau2_defines.hdr"
    .equ    MMCAU_PPB_DIRECT,0xe0081000
    .equ    MMCAU_PPB_INDIRECT,0xe0081800
    .equ    MMCAU_1_CMD,0x80000000
    .equ    MMCAU_2_CMDS,0x80100000
    .equ    MMCAU_3_CMDS,0x80100200

    .syntax unified

#*******************************************************************************
#*******************************************************************************
#
# DES: Check key parity
#   arguments
#           *key        pointer to 64-bit DES key with parity bits
#
#   return
#           0           no error
#          -1           parity error
#
#   calling convention
#   int     mmcau_des_chk_parity (const unsigned char *key)

    .global _mmcau_des_chk_parity
    .global mmcau_des_chk_parity
    .type   mmcau_des_chk_parity, %function
    .align  4

_mmcau_des_chk_parity:
mmcau_des_chk_parity:

# load the 64-bit key into the CAU's CA0/CA1 registers
    movw    r3, #:lower16:(MMCAU_PPB_INDIRECT+(LDR+CA0)<<2)
    ldmia   r0, {r1-r2}                             @ get key[0-1]
    movt    r3, #:upper16:(MMCAU_PPB_INDIRECT+(LDR+CA0)<<2)
    stmia   r3, {r1-r2}                             @ to CA0 & CA1

# perform the key schedule and check the parity bits
    movw    r1, #:lower16:MMCAU_PPB_DIRECT          @ r1 -> MMCAU_PPB_DIRECT
    movw    r2, #:lower16:(MMCAU_1_CMD+(DESK+CP)<<22)@ r2 = mmcau_1_cmd(DESK+CP)
    movt    r1, #:upper16:MMCAU_PPB_DIRECT
    movt    r2, #:upper16:(MMCAU_1_CMD+(DESK+CP)<<22)
    str     r2, [r1]                                @ mmcau_1_cmd(DESK+CP)

# the CASR[DPE] reflects the DES key parity check
    ldr     r0, [r3, $((STR+CASR)-(LDR+CA0))<<2]    @ get CAU status in r0
    ands    r0, $2                                  @ test the DPE bit
    it      ne                                      @ if DPE set
    movne   r0, $-1                                 @ then return -1

    bx  lr


#*******************************************************************************
#*******************************************************************************
#
# DES: Encrypts a single 8-byte block
#   arguments
#           *in         pointer to 8-byte block of input plaintext
#           *key        pointer to 64-bit DES key with parity bits
#           *out        pointer to 8-byte block of output ciphertext
#
#   NOTE    Input and output blocks may overlap
#
#   calling convention
#   void    mmcau_des_encrypt (const unsigned char *in,
#                              const unsigned char *key,
#                              unsigned char       *out)

    .global _mmcau_des_encrypt
    .global mmcau_des_encrypt
    .type   mmcau_des_encrypt, %function
    .align  4

_mmcau_des_encrypt:
mmcau_des_encrypt:

#  register allocation
# --------------------
#  r0      = scratch / *in  (arg0) / pointer to MMCAU_PPB_DIRECT
#  r1      = scratch / *key (arg1) / MMCAU_PPB_INDIRECT+(STR+CA2)<<2
#  r2      = scratch / *out (arg2)
#  r3      = scratch / mmcau_3_cmds(DESK,DESR+IP+KSL1,DESR+KSL2)
#  r4      = scratch / mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL2)
#  r5      = scratch / mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL1)
#  r6      = scratch / mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL2)
#  r7      = scratch / mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL2)
# r13 (sp) = stack pointer
# r14 (lr) = link register

    stmdb   sp!, {r4-r7}                            @ save registers on stack

# load the 64-bit key into the CAU's CA0/CA1 registers
# and the 64-bit plaintext input block into CA2/CA3
    movw    r7, #:lower16:(MMCAU_PPB_INDIRECT+((LDR+CA0)<<2))
    movt    r7, #:upper16:(MMCAU_PPB_INDIRECT+((LDR+CA0)<<2))
    ldmia   r1, {r3-r4}                             @ copy key[0-1]
    rev     r3, r3                                  @ byte reverse
    rev     r4, r4                                  @ byte reverse
    ldmia   r0, {r5-r6}                             @ and plaintext[0-1]
    rev     r5, r5                                  @ byte reverse
    rev     r6, r6                                  @ byte reverse
    stmia   r7, {r3-r6}                             @ into CA0-CA3

# load registers for mmcau commands
    movw    r0, #:lower16:encrypt_reg_data          @ get pointer to commands
    movt    r0, #:upper16:encrypt_reg_data
    ldmia   r0, {r0-r1,r3-r7}                       @ load into registers

#  send a series of 17 direct cau commands to perform the DES round operations
#   *(MMCAU_PPB_DIRECT + 0) = mmcau_3_cmds(DESK,DESR+IP+KSL1,DESR+KSL2);
#   *(MMCAU_PPB_DIRECT + 1) = mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL2);
#   *(MMCAU_PPB_DIRECT + 2) = mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL1);
#   *(MMCAU_PPB_DIRECT + 3) = mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL2);
#   *(MMCAU_PPB_DIRECT + 4) = mmcau_3_cmds(DESR+KSL2,DESR+KSL2,DESR+KSL2);
#   *(MMCAU_PPB_DIRECT + 5) = mmcau_2_cmds(DESR+KSL1,DESR+FP);

    stmia   r0, {r3-r6}
    stmia   r0, {r6-r7}

# get ciphertext[0-1] from CA2/3 and save to output[0-1]
    ldmia   r1, {r0-r1}                             @ get ciphertext[0-1]
    rev     r0, r0                                  @ byte reverse
    rev     r1, r1                                  @ byte reverse
    stmia   r2, {r0-r1}                             @ save to output[0-1]

    ldmia   sp!, {r4-r7}                            @ restore regs and return
    bx      lr

#*******************************************************************************
#*******************************************************************************
#
# DES: Decrypts a single 8-byte block
#   arguments
#           *in         pointer to 8-byte block of input ciphertext
#           *key        pointer to 64-bit DES key with parity bits
#           *out        pointer to 8-byte block of output plaintext
#
#   NOTE    Input and output blocks may overlap
#
#   calling convention
#   void    mmcau_des_decrypt (const unsigned char *in,
#                              const unsigned char *key,
#                                    unsigned char *out)

    .global _mmcau_des_decrypt
    .global mmcau_des_decrypt
    .type   mmcau_des_decrypt, %function
    .align  4

_mmcau_des_decrypt:
mmcau_des_decrypt:

#  register allocation
# --------------------
#  r0      = scratch / *in  (arg0) / pointer to MMCAU_PPB_DIRECT
#  r1      = scratch / *key (arg1) / MMCAU_PPB_INDIRECT+(STR+CA2)<<2
#  r2      = scratch / *out (arg2)
#  r3      = scratch / mmcau_3_cmds(DESK+DC,DESR+IP+KSR1,DESR+KSR2)
#  r4      = scratch / mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR2)
#  r5      = scratch / mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR1)
#  r6      = scratch / mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR2)
#  r7      = scratch / mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR2)
# r13 (sp) = stack pointer
# r14 (lr) = link register

    stmdb   sp!, {r4-r7}                            @ save registers on stack

# load the 64-bit key into the CAU's CA0/CA1 registers
# and the 64-bit ciphertext input block into CA2/CA3
    movw    r7, #:lower16:(MMCAU_PPB_INDIRECT+((LDR+CA0)<<2))
    movt    r7, #:upper16:(MMCAU_PPB_INDIRECT+((LDR+CA0)<<2))
    ldmia   r1, {r3-r4}                             @ copy key[0-1]
    rev     r3, r3                                  @ byte reverse
    rev     r4, r4                                  @ byte reverse
    ldmia   r0, {r5-r6}                             @ and ciphertext[0-1]
    rev     r5, r5                                  @ byte reverse
    rev     r6, r6                                  @ byte reverse
    stmia   r7, {r3-r6}                             @ into CA0-CA3

# load registers for mmcau commands
    movw    r0, #:lower16:decrypt_reg_data          @ get pointer to commands
    movt    r0, #:upper16:decrypt_reg_data
    ldmia   r0, {r0-r1,r3-r7}                       @ load into registers

#  send a series of 17 direct cau commands to perform the DES round operations
#   *(MMCAU_PPB_DIRECT + 0) = mmcau_3_cmds(DESK+DC,DESR+IP+KSR1,DESR+KSR2);
#   *(MMCAU_PPB_DIRECT + 1) = mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR2);
#   *(MMCAU_PPB_DIRECT + 2) = mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR1);
#   *(MMCAU_PPB_DIRECT + 3) = mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR2);
#   *(MMCAU_PPB_DIRECT + 4) = mmcau_3_cmds(DESR+KSR2,DESR+KSR2,DESR+KSR2);
#   *(MMCAU_PPB_DIRECT + 5) = mmcau_2_cmds(DESR+KSR1,DESR+FP);

    stmia   r0, {r3-r6}
    stmia   r0, {r6-r7}

# get plaintext[0-1] from CA2/3 and store to output[0-1]
    ldmia   r1, {r0-r1}                             @ get plaintext[0-1]
    rev     r0, r0                                  @ byte reverse
    rev     r1, r1                                  @ byte reverse
    stmia   r2, {r0-r1}                             @ save to output[0-1]

    ldmia   sp!, {r4-r7}                            @ restore regs and return
    bx      lr


    .data
    .type   encrypt_reg_data, %object
    .align  4

encrypt_reg_data:
    .word   MMCAU_PPB_DIRECT                                        @r0
    .word   MMCAU_PPB_INDIRECT+((STR+CA2)<<2)                       @r1
    .word   MMCAU_3_CMDS+(DESK)<<22+(DESR+IP+KSL1)<<11+DESR+KSL2    @r3
    .word   MMCAU_3_CMDS+(DESR+KSL2)<<22+(DESR+KSL2)<<11+DESR+KSL2  @r4
    .word   MMCAU_3_CMDS+(DESR+KSL2)<<22+(DESR+KSL2)<<11+DESR+KSL1  @r5
    .word   MMCAU_3_CMDS+(DESR+KSL2)<<22+(DESR+KSL2)<<11+DESR+KSL2  @r6
    .word   MMCAU_2_CMDS+(DESR+KSL1)<<22+(DESR+FP)<<11              @r7

    .type   decrypt_reg_data, %object
    .align  4

decrypt_reg_data:
    .word   MMCAU_PPB_DIRECT                                        @r0
    .word   MMCAU_PPB_INDIRECT+((STR+CA2)<<2)                       @r1
    .word   MMCAU_3_CMDS+(DESK+DC)<<22+(DESR+IP+KSR1)<<11+DESR+KSR2 @r3
    .word   MMCAU_3_CMDS+(DESR+KSR2)<<22+(DESR+KSR2)<<11+DESR+KSR2  @r4
    .word   MMCAU_3_CMDS+(DESR+KSR2)<<22+(DESR+KSR2)<<11+DESR+KSR1  @r5
    .word   MMCAU_3_CMDS+(DESR+KSR2)<<22+(DESR+KSR2)<<11+DESR+KSR2  @r6
    .word   MMCAU_2_CMDS+(DESR+KSR1)<<22+(DESR+FP)<<11              @r7
