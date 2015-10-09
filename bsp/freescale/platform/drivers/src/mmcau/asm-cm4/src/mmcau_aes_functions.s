#*******************************************************************************
#*******************************************************************************
#
# Copyright (c) Freescale Semiconductor, Inc 2011.
#
# FILE NAME      : mmcau_aes_functions.s
# VERSION        : $Id: mmcau_aes_functions.s.rca 1.4 Thu Nov 21 14:17:01 2013 b40907 Experimental $
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
#                                      set_key and decrypt; also, some cleanup
#
#*******************************************************************************
#*******************************************************************************

    .include "cau2_defines.hdr"
    .equ    MMCAU_PPB_DIRECT,  0xe0081000
    .equ    MMCAU_PPB_INDIRECT,0xe0081800
    .equ    MMCAU_1_CMD,       0x80000000
    .equ    MMCAU_2_CMDS,      0x80100000
    .equ    MMCAU_3_CMDS,      0x80100200

    .syntax unified

#*******************************************************************************
#*******************************************************************************
#
# AES: Performs an AES key expansion
#   arguments
#           *key        pointer to input key (128, 192, 256 bits in length)
#           key_size    key_size in bits (128, 192, 256)
#           *key_sch    pointer to key schedule output (44, 52, 60 longwords)
#
#   calling convention
#   void    mmcau_aes_set_key (const unsigned char *key,
#                              const int            key_size,
#                              unsigned char       *key_sch)

#  register allocation
# --------------------
#  r0      = scratch / input  *key (arg0)
#  r1      = scratch / input  size (arg1)
#  r2      = scratch / output *key_sch (arg2)
#  r3      = scratch
#  r4      = scratch
#  r5      = scratch
#  r6      = scratch
#  r7      = scratch
#  r8      = scratch
#  r9      = scratch
# r10 (sl) = scratch / pointer to rcon
# r11 (fp) = scratch / mmcau_1_cmd(AESS+CAA)
# r12 (ip) = scratch / MMCAU_PPB_DIRECT
# r13 (sp) = stack pointer
# r14 (lr) = scratch / link register

    .global _mmcau_aes_set_key
    .global mmcau_aes_set_key
    .type   mmcau_aes_set_key, %function
    .align  4

_mmcau_aes_set_key:
mmcau_aes_set_key:

    stmdb   sp!, {r4-ip,lr}                         @ save registers on stack

# prepare for AES operations register load
    movw    r8, #:lower16:setkey_reg_data
    movt    r8, #:upper16:setkey_reg_data

    ldmia   r0!, {r4-r7}                            @ copy key[0-3]
    rev     r4, r4                                  @ byte reverse
    rev     r5, r5                                  @ byte reverse
    rev     r6, r6                                  @ byte reverse
    rev     r7, r7                                  @ byte reverse
    stmia   r2!, {r4-r7}                            @ to key_sch[0-3]

# load registers needed for mmcau commands from setkey_reg_data:
    ldmia   r8, {sl-ip}                             @ setup AES operations

    cmp     r1, #128                                @ if key_size = 128
    beq     expand_128                              @ then go expand_128
    cmp     r1, #192                                @ else if size = 192
    beq     expand_192                              @ then go expand_192

expand_256:
    ldmia   r0, {r1,r3,r8-r9}                       @ copy key[4-7]
    rev     r1, r1                                  @ byte reverse
    rev     r3, r3                                  @ byte reverse
    rev     r8, r8                                  @ byte reverse
    rev     r9, r9                                  @ byte reverse
    stmia   r2!, {r1,r3,r8-r9}                      @ to key_sch[4-7]


    ldr     r0, [sl], $4                            @ get rcon[0]; sl++
    ror     lr, r9, $24                             @ rotate left by 8
    str     lr, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[7])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     lr, r0                                  @ XOR rcon[0]

# calculation for key_sch[8-11]
    eor     r4, lr                                  @ XOR key_sch[0]
    eor     r5, r4                                  @ key_sch[1]^key_sch[8]
    eor     r6, r5                                  @ key_sch[2]^key_sch[9]
    eor     r7, r6                                  @ key_sch[3]^key_sch[10]
    stmia   r2!, {r4-r7}                            @ store key_sch[8-11]

    str     r7, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[11])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA

# calculation for key_sch[12-15]
    eor     r1, lr                                  @ XOR key_sch[4]
    eor     r3, r1                                  @ key_sch[5]^key_sch[12]
    eor     r8, r3                                  @ key_sch[6]^key_sch[13]
    eor     r9, r8                                  @ key_sch[7]^key_sch[14]
    stmia   r2!, {r1,r3,r8-r9}                      @ store key_sch[12-15]

    ldr     r0, [sl], $4                            @ get rcon[1]; sl++
    ror     lr, r9, $24                             @ rotate left by 8
    str     lr, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[15])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     lr, r0                                  @ XOR rcon[1]

# calculation for key_sch[16-19]
    eor     r4, lr                                  @ XOR key_sch[8]
    eor     r5, r4                                  @ key_sch[9]^key_sch[16]
    eor     r6, r5                                  @ key_sch[10]^key_sch[17]
    eor     r7, r6                                  @ key_sch[11]^key_sch[18]
    stmia   r2!, {r4-r7}                            @ store key_sch[16-19]

    str     r7, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[19])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA

# calculation for key_sch[20-23]
    eor     r1, lr                                  @ XOR key_sch[12]
    eor     r3, r1                                  @ key_sch[13]^key_sch[20]
    eor     r8, r3                                  @ key_sch[14]^key_sch[21]
    eor     r9, r8                                  @ key_sch[15]^key_sch[22]
    stmia   r2!, {r1,r3,r8-r9}                      @ store key_sch[20-23]

    ldr     r0, [sl], $4                            @ get rcon[2]; sl++
    ror     lr, r9, $24                             @ rotate left by 8
    str     lr, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[23])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     lr, r0                                  @ XOR rcon[2]

# calculation for key_sch[24-27]
    eor     r4, lr                                  @ XOR key_sch[16]
    eor     r5, r4                                  @ key_sch[17]^key_sch[24]
    eor     r6, r5                                  @ key_sch[18]^key_sch[25]
    eor     r7, r6                                  @ key_sch[19]^key_sch[26]
    stmia   r2!, {r4-r7}                            @ store key_sch[24-27]

    str     r7, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[27])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA

# calculation for key_sch[28-31]
    eor     r1, lr                                  @ XOR key_sch[20]
    eor     r3, r1                                  @ key_sch[21]^key_sch[28]
    eor     r8, r3                                  @ key_sch[22]^key_sch[29]
    eor     r9, r8                                  @ key_sch[23]^key_sch[30]
    stmia   r2!, {r1,r3,r8-r9}                      @ store key_sch[28-31]

    ldr     r0, [sl], $4                            @ get rcon[3]; sl++
    ror     lr, r9, $24                             @ rotate left by 8
    str     lr, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[31])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     lr, r0                                  @ XOR rcon[3]

# calculation for key_sch[32-35]
    eor     r4, lr                                  @ XOR key_sch[24]
    eor     r5, r4                                  @ key_sch[25]^key_sch[32]
    eor     r6, r5                                  @ key_sch[26]^key_sch[33]
    eor     r7, r6                                  @ key_sch[27]^key_sch[34]
    stmia   r2!, {r4-r7}                            @ store key_sch[32-35]

    str     r7, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[35])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA

# calculation for key_sch[36-39]
    eor     r1, lr                                  @ XOR key_sch[28]
    eor     r3, r1                                  @ key_sch[29]^key_sch[36]
    eor     r8, r3                                  @ key_sch[30]^key_sch[37]
    eor     r9, r8                                  @ key_sch[31]^key_sch[38]
    stmia   r2!, {r1,r3,r8-r9}                      @ store key_sch[36-39]

    ldr     r0, [sl], $4                            @ get rcon[4]; sl++
    ror     lr, r9, $24                             @ rotate left by 8
    str     lr, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[39])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     lr, r0                                  @ XOR rcon[4]

# calculation for key_sch[40-43]
    eor     r4, lr                                  @ XOR key_sch[32]
    eor     r5, r4                                  @ key_sch[33]^key_sch[40]
    eor     r6, r5                                  @ key_sch[34]^key_sch[41]
    eor     r7, r6                                  @ key_sch[35]^key_sch[42]
    stmia   r2!, {r4-r7}                            @ store key_sch[40-43]

    str     r7, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[43])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA

# calculation for key_sch[44-47]
    eor     r1, lr                                  @ XOR key_sch[36]
    eor     r3, r1                                  @ key_sch[37]^key_sch[44]
    eor     r8, r3                                  @ key_sch[38]^key_sch[45]
    eor     r9, r8                                  @ key_sch[39]^key_sch[46]
    stmia   r2!, {r1,r3,r8-r9}                      @ store key_sch[44-47]

    ldr     r0, [sl], $4                            @ get rcon[5]; sl++
    ror     lr, r9, $24                             @ rotate left by 8
    str     lr, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[47])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     lr, r0                                  @ XOR rcon[5]

# calculation for key_sch[48-51]
    eor     r4, lr                                  @ XOR key_sch[40]
    eor     r5, r4                                  @ key_sch[41]^key_sch[48]
    eor     r6, r5                                  @ key_sch[42]^key_sch[49]
    eor     r7, r6                                  @ key_sch[43]^key_sch[50]
    stmia   r2!, {r4-r7}                            @ store key_sch[48-51]

    str     r7, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[51])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA

# calculation for key_sch[52-55]
    eor     r1, lr                                  @ XOR key_sch[44]
    eor     r3, r1                                  @ key_sch[45]^key_sch[52]
    eor     r8, r3                                  @ key_sch[46]^key_sch[53]
    eor     r9, r8                                  @ key_sch[47]^key_sch[54]
    stmia   r2!, {r1,r3,r8-r9}                      @ store key_sch[52-55]

    ldr     r0, [sl], $4                            @ get rcon[6]; sl++
    ror     lr, r9, $24                             @ rotate left by 8
    str     lr, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[55])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     lr, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     lr, r0                                  @ XOR rcon[6]

# calculation for key_sch[56-59]
    eor     r4, lr                                  @ XOR key_sch[48]
    eor     r5, r4                                  @ key_sch[49]^key_sch[56]
    eor     r6, r5                                  @ key_sch[50]^key_sch[57]
    eor     r7, r6                                  @ key_sch[51]^key_sch[58]
    stmia   r2!, {r4-r7}                            @ store key_sch[56-59]

    ldmia   sp!, {r4-ip,pc}                         @ restore regs and return

expand_192:
    ldmia   r0, {r8-r9}                             @ copy key[4-5]
    rev     r8, r8                                  @ byte reverse
    rev     r9, r9                                  @ byte reverse
    stmia   r2!, {r8-r9}                            @ to key_sch[4-5]

    ldr     r0, [sl], $4                            @ get rcon[0]; sl++
    ror     r3, r9, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[5])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[0]

# calculation for key_sch[6-11]
    eor     r4, r3                                  @ XOR key_sch[0]
    eor     r5, r4                                  @ key_sch[1]^key_sch[6]
    eor     r6, r5                                  @ key_sch[2]^key_sch[7]
    eor     r7, r6                                  @ key_sch[3]^key_sch[8]
    eor     r8, r7                                  @ key_sch[4]^key_sch[9]
    eor     r9, r8                                  @ key_sch[5]^key_sch[10]
    stmia   r2!, {r4-r9}                            @ store key_sch[6-11]

    ldr     r0, [sl], $4                            @ get rcon[1]; sl++
    ror     r3, r9, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[11])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[1]

# calculation for key_sch[12-17]
    eor     r4, r3                                  @ XOR key_sch[6]
    eor     r5, r4                                  @ key_sch[7]^key_sch[12]
    eor     r6, r5                                  @ key_sch[8]^key_sch[13]
    eor     r7, r6                                  @ key_sch[9]^key_sch[14]
    eor     r8, r7                                  @ key_sch[10]^key_sch[15]
    eor     r9, r8                                  @ key_sch[11]^key_sch[16]
    stmia   r2!, {r4-r9}                            @ store key_sch[12-17]

    ldr     r0, [sl], $4                            @ get rcon[2]; sl++
    ror     r3, r9, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[17])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[2]

# calculation for key_sch[18-23]
    eor     r4, r3                                  @ XOR key_sch[12]
    eor     r5, r4                                  @ key_sch[13]^key_sch[18]
    eor     r6, r5                                  @ key_sch[14]^key_sch[19]
    eor     r7, r6                                  @ key_sch[15]^key_sch[20]
    eor     r8, r7                                  @ key_sch[16]^key_sch[21]
    eor     r9, r8                                  @ key_sch[17]^key_sch[22]
    stmia   r2!, {r4-r9}                            @ store key_sch[18-23]

    ldr     r0, [sl], $4                            @ get rcon[3]; sl++
    ror     r3, r9, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[23])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[3]

# calculation for key_sch[24-29]
    eor     r4, r3                                  @ XOR key_sch[18]
    eor     r5, r4                                  @ key_sch[19]^key_sch[24]
    eor     r6, r5                                  @ key_sch[20]^key_sch[25]
    eor     r7, r6                                  @ key_sch[21]^key_sch[26]
    eor     r8, r7                                  @ key_sch[22]^key_sch[27]
    eor     r9, r8                                  @ key_sch[23]^key_sch[28]
    stmia   r2!, {r4-r9}                            @ store key_sch[24-29]

    ldr     r0, [sl], $4                            @ get rcon[4]; sl++
    ror     r3, r9, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[29])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[4]

# calculation for key_sch[30-35]
    eor     r4, r3                                  @ XOR key_sch[24]
    eor     r5, r4                                  @ key_sch[25]^key_sch[30]
    eor     r6, r5                                  @ key_sch[26]^key_sch[31]
    eor     r7, r6                                  @ key_sch[27]^key_sch[32]
    eor     r8, r7                                  @ key_sch[28]^key_sch[33]
    eor     r9, r8                                  @ key_sch[29]^key_sch[34]
    stmia   r2!, {r4-r9}                            @ store key_sch[30-35]

    ldr     r0, [sl], $4                            @ get rcon[5]; sl++
    ror     r3, r9, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[35])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[5]

# calculation for key_sch[36-41]
    eor     r4, r3                                  @ XOR key_sch[30]
    eor     r5, r4                                  @ key_sch[31]^key_sch[36]
    eor     r6, r5                                  @ key_sch[32]^key_sch[37]
    eor     r7, r6                                  @ key_sch[33]^key_sch[38]
    eor     r8, r7                                  @ key_sch[34]^key_sch[39]
    eor     r9, r8                                  @ key_sch[35]^key_sch[40]
    stmia   r2!, {r4-r9}                            @ store key_sch[36-41]

    ldr     r0, [sl], $4                            @ get rcon[6]; sl++
    ror     r3, r9, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[41])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[6]

# calculation for key_sch[42-47]
    eor     r4, r3                                  @ XOR key_sch[36]
    eor     r5, r4                                  @ key_sch[37]^key_sch[42]
    eor     r6, r5                                  @ key_sch[38]^key_sch[43]
    eor     r7, r6                                  @ key_sch[39]^key_sch[44]
    eor     r8, r7                                  @ key_sch[40]^key_sch[45]
    eor     r9, r8                                  @ key_sch[41]^key_sch[46]
    stmia   r2!, {r4-r9}                            @ store key_sch[42-47]

    ldr     r0, [sl], $4                            @ get rcon[7]; sl++
    ror     r3, r9, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[47])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[7]

# calculation for key_sch[48-51]
    eor     r4, r3                                  @ XOR key_sch[42]
    eor     r5, r4                                  @ key_sch[43]^key_sch[48]
    eor     r6, r5                                  @ key_sch[44]^key_sch[49]
    eor     r7, r6                                  @ key_sch[45]^key_sch[50]
    stmia   r2!, {r4-r7}                            @ store key_sch[48-51]

    ldmia   sp!, {r4-ip,pc}                         @ restore regs and return

expand_128:
    ldr     r0, [sl]                                @ get rcon[0]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[3])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[0]

# calculation for key_sch[4-7]
    eor     r4, r3                                  @ XOR key_sch[0]
    eor     r5, r4                                  @ key_sch[1]^key_sch[4]
    eor     r6, r5                                  @ key_sch[2]^key_sch[5]
    eor     r7, r6                                  @ key_sch[3]^key_sch[6]
    stmia   r2!, {r4-r7}                            @ store key_sch[4-7]

    ldr     r0, [sl, $1<<2]                         @ get rcon[1]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[7])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[1]

# calculation for key_sch[8-11]
    eor     r4, r3                                  @ XOR key_sch[4]
    eor     r5, r4                                  @ key_sch[5]^key_sch[8]
    eor     r6, r5                                  @ key_sch[6]^key_sch[9]
    eor     r7, r6                                  @ key_sch[7]^key_sch[10]
    stmia   r2!, {r4-r7}                            @ store key_sch[8-11]

    ldr     r0, [sl, $2<<2]                         @ get rcon[2]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[11])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[2]

# calculation for key_sch[12-15]
    eor     r4, r3                                  @ XOR key_sch[8]
    eor     r5, r4                                  @ key_sch[9]^key_sch[12]
    eor     r6, r5                                  @ key_sch[10]^key_sch[13]
    eor     r7, r6                                  @ key_sch[11]^key_sch[14]
    stmia   r2!, {r4-r7}                            @ store key_sch[12-15]

    ldr     r0, [sl, $3<<2]                         @ get rcon[3]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[15])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[3]

# calculation for key_sch[16-19]
    eor     r4, r3                                  @ XOR key_sch[12]
    eor     r5, r4                                  @ key_sch[13]^key_sch[16]
    eor     r6, r5                                  @ key_sch[14]^key_sch[17]
    eor     r7, r6                                  @ key_sch[15]^key_sch[18]
    stmia   r2!, {r4-r7}                            @ store key_sch[16-19]

    ldr     r0, [sl, $4<<2]                         @ get rcon[4]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[19])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[4]

# calculation for key_sch[20-23]
    eor     r4, r3                                  @ XOR key_sch[16]
    eor     r5, r4                                  @ key_sch[17]^key_sch[20]
    eor     r6, r5                                  @ key_sch[18]^key_sch[21]
    eor     r7, r6                                  @ key_sch[19]^key_sch[22]
    stmia   r2!, {r4-r7}                            @ store key_sch[20-23]

    ldr     r0, [sl, $5<<2]                         @ get rcon[5]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[23])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[5]

# calculation for key_sch[24-27]
    eor     r4, r3                                  @ XOR key_sch[20]
    eor     r5, r4                                  @ key_sch[21]^key_sch[24]
    eor     r6, r5                                  @ key_sch[22]^key_sch[25]
    eor     r7, r6                                  @ key_sch[23]^key_sch[26]
    stmia   r2!, {r4-r7}                            @ store key_sch[24-27]

    ldr     r0, [sl, $6<<2]                         @ get rcon[6]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[27])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[6]

# calculation for key_sch[28-31]
    eor     r4, r3                                  @ XOR key_sch[24]
    eor     r5, r4                                  @ key_sch[25]^key_sch[28]
    eor     r6, r5                                  @ key_sch[26]^key_sch[29]
    eor     r7, r6                                  @ key_sch[27]^key_sch[30]
    stmia   r2!, {r4-r7}                            @ store key_sch[28-31]

    ldr     r0, [sl, $7<<2]                         @ get rcon[7]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[31])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[7]

# calculation for key_sch[32-35]
    eor     r4, r3                                  @ XOR key_sch[28]
    eor     r5, r4                                  @ key_sch[29]^key_sch[32]
    eor     r6, r5                                  @ key_sch[30]^key_sch[33]
    eor     r7, r6                                  @ key_sch[31]^key_sch[34]
    stmia   r2!, {r4-r7}                            @ store key_sch[32-35]

    ldr     r0, [sl, $8<<2]                         @ get rcon[8]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[35])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[8]

# calculation for key_sch[36-39]
    eor     r4, r3                                  @ XOR key_sch[32]
    eor     r5, r4                                  @ key_sch[33]^key_sch[36]
    eor     r6, r5                                  @ key_sch[34]^key_sch[37]
    eor     r7, r6                                  @ key_sch[35]^key_sch[38]
    stmia   r2!, {r4-r7}                            @ store key_sch[36-39]

    ldr     r0, [sl, $9<<2]                         @ get rcon[9]
    ror     r3, r7, $24                             @ rotate left by 8
    str     r3, [ip, $0x800+(LDR+CAA)<<2]           @ ROTL(key_sch[39])-> acc
    str     fp, [ip]                                @ AES SubBytes
    ldr     r3, [ip, $0x800+(STR+CAA)<<2]           @ get CAA
    eor     r3, r0                                  @ XOR rcon[9]

# calculation for key_sch[40-43]
    eor     r4, r3                                  @ XOR key_sch[36]
    eor     r5, r4                                  @ key_sch[37]^key_sch[40]
    eor     r6, r5                                  @ key_sch[38]^key_sch[41]
    eor     r7, r6                                  @ key_sch[39]^key_sch[42]
    stmia   r2!, {r4-r7}                            @ store key_sch[40-43]

    ldmia   sp!, {r4-ip,pc}                         @ restore regs and return


#*******************************************************************************
#*******************************************************************************
#
# AES: Encrypts a single 16-byte block
#   arguments
#           *in         pointer to 16-byte block of input plaintext
#           *key_sch    pointer to key schedule (44, 52, 60 longwords)
#           nr          number of AES rounds (10, 12, 14 = f(key_schedule))
#           *out        pointer to 16-byte block of output ciphertext
#
#
#   calling convention
#   void    mmcau_aes_encrypt (const unsigned char *in,
#                              const unsigned char *key_sch,
#                              const int            nr,
#                              unsigned char       *out)

    .global _mmcau_aes_encrypt
    .global mmcau_aes_encrypt
    .type   mmcau_aes_encrypt, %function
    .align  4

_mmcau_aes_encrypt:
mmcau_aes_encrypt:

#  register allocation
# --------------------
#  r0      = scratch / input  *in  / mmcau_3_cmds(AESS+CA0,AESS+CA1,AESS+CA2)
#  r1      = scratch / input  *key_sch
#  r2      = scratch / input   nr
#  r3      = scratch / output *out
#  r4      = scratch
#  r5      = scratch
#  r6      = scratch
#  r7      = scratch
#  r8      = scratch / mmcau_2_cmds(AESS+CA3,AESR)
#  r9      = scratch / mmcau_indirect_cmd(AESC+CA0)
# r10 (sl) = scratch / mmcau_indirect_cmd(STR+CA0)
# r11 (fp) = scratch / mmcau_indirect_cmd(LDR+CA0)
# r12 (ip) = scratch / pointer to MMCAU_PPB_DIRECT
# r13 (sp) = stack pointer
# r14 (lr) = link register

    stmdb   sp!, {r4-ip}                            @ save registers on stack

# load the 16 plain text bytes (4 words) into r4-r7
    ldmia   r0, {r4-r7}                             @ get plaintext[0-3]
    rev     r4, r4                                  @ byte reverse
    rev     r5, r5                                  @ byte reverse
    rev     r6, r6                                  @ byte reverse
    rev     r7, r7                                  @ byte reverse

# prepare for AES operations register load
    movw    r0, #:lower16:encrypt_reg_data
    movt    r0, #:upper16:encrypt_reg_data

# XOR the first 4 keys into the 16 plain text bytes
    ldmia   r1!, {r8-fp}                            @ get key_sch[0-3]; r1++
    eor     r4, r8
    eor     r5, r9
    eor     r6, sl
    eor     r7, fp

# load registers needed for mmcau commands from encrypt_reg_data:
    ldmia   r0, {r0,r8-ip}                          @ setup AES operations

# load the XOR results into the CAU's CA0 - CA3 registers
    stmia   fp, {r4-r7}                             @ load CA0-CA3

# send a series of cau commands to perform the encryption
    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    cmp     r2, $10                                 @ if aes128, finish
    beq     encrypt_end

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    cmp     r2, $12                                 @ if aes192, finish
    beq     encrypt_end

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows
    ldmia   r1!, {r4-r7}                            @ get next 4 keys; r1++
    stmia   r9, {r4-r7}                             @ MixColumns

encrypt_end:
    str     r0, [ip]                                @ SubBytes
    str     r8, [ip]                                @ SubBytes, ShiftRows

# XOR the last 4 keys into CAO - CA3 ciphertext output
    ldmia   sl, {r4-r7}                             @ get CA0 - CA3
    ldmia   r1, {r8-fp}                             @ get key_sch[j]-[j+3]
    eor     r4, r8
    eor     r5, r9
    eor     r6, sl
    eor     r7, fp

# store the 16-byte ciphertext output block into memory
    rev     r4, r4                                  @ byte reverse
    rev     r5, r5                                  @ byte reverse
    rev     r6, r6                                  @ byte reverse
    rev     r7, r7                                  @ byte reverse
    stmia   r3, {r4-r7}                             @ save to output[0-3]

    ldmia   sp!, {r4-ip}                            @ restore regs and return
    bx      lr

#*******************************************************************************
#*******************************************************************************
#
# AES: Decrypts a single 16-byte block
#   arguments
#           *in         pointer to 16-byte block of input chiphertext
#           *key_sch    pointer to key schedule (44, 52, 60 longwords)
#           nr          number of AES rounds (10, 12, 14 = f(key_schedule))
#           *out        pointer to 16-byte block of output plaintext
#
#
#   calling convention
#   void    mmcau_aes_decrypt (const unsigned char *in,
#                              const unsigned char *key_sch,
#                              const int            nr,
#                              unsigned char       *out)

    .global _mmcau_aes_decrypt
    .global mmcau_aes_decrypt
    .type   mmcau_aes_decrypt, %function
    .align  4

_mmcau_aes_decrypt:
mmcau_aes_decrypt:

#  register allocation
# --------------------
#  r0      = scratch / input  *in  / mmcau_3_cmds(AESIR,AESIS+CA3,AESIS+CA2)
#  r1      = scratch / input  *key_sch
#  r2      = scratch / input   nr
#  r3      = scratch / output *out
#  r4      = scratch
#  r5      = scratch
#  r6      = scratch
#  r7      = scratch
#  r8      = scratch / mmcau_2_cmds(AESIS+CA1,AESIS+CA0)
#  r9      = scratch / mmcau_indirect_cmd(AESIC+CA0)
# r10 (sl) = scratch / mmcau_indirect_cmd(STR+CA0)
# r11 (fp) = scratch / mmcau_indirect_cmd(LDR+CA0)
# r12 (ip) = scratch / pointer to MMCAU_PPB_DIRECT
# r13 (sp) = stack pointer
# r14 (lr) = link register

    stmdb   sp!, {r4-ip}                            @ save registers on stack

# load the 16 cipher bytes (4 words) into r4-r7
    ldmia   r0, {r4-r7}                             @ get in[0-3]
    rev     r4, r4                                  @ byte reverse
    rev     r5, r5                                  @ byte reverse
    rev     r6, r6                                  @ byte reverse
    rev     r7, r7                                  @ byte reverse

# prepare for AES operations register load
    movw    r0, #:lower16:decrypt_reg_data
    movt    r0, #:upper16:decrypt_reg_data

# the key_sch pointer (r1) is adjusted to define the end of the elements
# the adjustment factor = f(nr) is defined by the expression:
#   end of key_sch = 4 x (nr + 1) for nr = {10, 12, 14}
    add     r1, r1, r2, LSL $4

# XOR the last 4 keys into the 4 cipher words
    ldmia   r1, {r8-fp}                             @ get last 4 keys
    eor     r4, r8
    eor     r5, r9
    eor     r6, sl
    eor     r7, fp

# load registers needed for mmcau commands from decrypt_reg_data:
    ldmia   r0, {r0,r8-ip}                          @ setup AES operations

# load the 16 cipher bytes (4 words) into the CAU's CA0 - CA3 registers
    stmia   fp, {r4-r7}                             @ load CA0-CA3

# send a series of cau commands to perform the decryption

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    cmp     r2, $10                                 @ if aes128, finish
    beq     decrypt_end

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    cmp     r2, $12                                 @ if aes192, finish
    beq     decrypt_end

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

    ldmdb   r1!, {r4-r7}                            @ key_sch[i] to [i+4]; r1--
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes
    stmia   r9, {r4-r7}                             @ MixColumns

decrypt_end:
    str     r0, [ip]                                @ InvShiftRows,InvSubBytes
    str     r8, [ip]                                @ InvSubBytes

# XOR the first 4 keys into CAO - CA3 plaintext output
    ldmia   sl, {r4-r7}                             @ get CA0 - CA3
    ldmdb   r1!, {r8-fp}                            @ key_sch[i] to [i+4]; r1--
    eor     r4, r8
    eor     r5, r9
    eor     r6, sl
    eor     r7, fp

# store the 16-byte plain text output block into memory
    rev     r4, r4                                  @ byte reverse
    rev     r5, r5                                  @ byte reverse
    rev     r6, r6                                  @ byte reverse
    rev     r7, r7                                  @ byte reverse
    stmia   r3, {r4-r7}                             @ save to output[0-3]

    ldmia   sp!, {r4-ip}                            @ restore regs and return
    bx      lr

#*******************************************************************************

    .data
    .type   setkey_reg_data, %object
    .align  4

setkey_reg_data:
    .word   rcon                                                @ sl
    .word   MMCAU_1_CMD+(AESS+CAA)<<22                          @ fp
    .word   MMCAU_PPB_DIRECT                                    @ ip

    .type   encrypt_reg_data, %object
    .align  4

encrypt_reg_data:
    .word   MMCAU_3_CMDS+(AESS+CA0)<<22+(AESS+CA1)<<11+AESS+CA2 @ r0
    .word   MMCAU_2_CMDS+(AESS+CA3)<<22+(AESR)<<11              @ r8
    .word   MMCAU_PPB_INDIRECT+(AESC+CA0)<<2                    @ r9
    .word   MMCAU_PPB_INDIRECT+(STR+CA0)<<2                     @ sl
    .word   MMCAU_PPB_INDIRECT+(LDR+CA0)<<2                     @ fp
    .word   MMCAU_PPB_DIRECT                                    @ ip

    .type   decrypt_reg_data, %object
    .align  4

decrypt_reg_data:
    .word   MMCAU_3_CMDS+(AESIR)<<22+(AESIS+CA3)<<11+AESIS+CA2  @ r0
    .word   MMCAU_2_CMDS+(AESIS+CA1)<<22+(AESIS+CA0)<<11        @ r8
    .word   MMCAU_PPB_INDIRECT+(AESIC+CA0)<<2                   @ r9
    .word   MMCAU_PPB_INDIRECT+(STR+CA0)<<2                     @ sl
    .word   MMCAU_PPB_INDIRECT+(LDR+CA0)<<2                     @ fp
    .word   MMCAU_PPB_DIRECT                                    @ ip

    .type   rcon, %object
    .align  4

rcon:
    .word 0x01000000
    .word 0x02000000
    .word 0x04000000
    .word 0x08000000
    .word 0x10000000
    .word 0x20000000
    .word 0x40000000
    .word 0x80000000
    .word 0x1b000000
    .word 0x36000000
