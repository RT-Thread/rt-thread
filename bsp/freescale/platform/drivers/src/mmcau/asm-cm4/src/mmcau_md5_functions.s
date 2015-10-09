#*******************************************************************************
#*******************************************************************************
#
# Copyright (c) Freescale Semiconductor, Inc 2011.
#
# FILE NAME      : mmcau_md5_functions.s
# VERSION        : $Id: mmcau_md5_functions.s.rca 1.6 Thu Nov 21 14:18:27 2013 b40907 Experimental $
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

    .syntax unified

#*******************************************************************************
#*******************************************************************************
#
# MD5: Initializes the MD5 state variables
#   arguments
#           *md5_state pointer to 120-bit block of md5 state variables:
#                           a,b,c,d
#
#   calling convention
#   void    mmcau_md5_initialize_output (const unsigned int *md5_state)

    .global _mmcau_md5_initialize_output
    .global mmcau_md5_initialize_output
    .type   mmcau_md5_initialize_output, %function
    .align  4

_mmcau_md5_initialize_output:
mmcau_md5_initialize_output:

    stmdb   sp!, {r4}                               @ save registers

    movw    r1, #:lower16:md5_initial_h             @ r1 -> initial data
    movt    r1, #:upper16:md5_initial_h

# copy initial data into hash output buffer
    ldmia   r1, {r1-r4}                             @ get md5[0-3]
    stmia   r0, {r1-r4}                             @ copy to md5_state[0-3]

    ldmia   sp!, {r4}                               @ restore registers
    bx      lr


#*******************************************************************************
#*******************************************************************************
#
# MD5: Updates MD5 state variables for one or more input message blocks
#
#   arguments
#           *msg_data   pointer to start of input message data
#           num_blks    number of 512-bit blocks to process
#           *md5_state  pointer to 128-bit block of MD5 state variables: a,b,c,d
#
#   calling convention
#   void    mmucau_md5_hash_n (const unsigned char *msg_data,
#                              const int            num_blks,
#                              unsigned char       *md5_state)

    .global _mmcau_md5_hash_n
    .global mmcau_md5_hash_n
    .type   mmcau_md5_hash_n, %function
    .align  4

_mmcau_md5_hash_n:
mmcau_md5_hash_n:

#  register allocation
# --------------------
#  r0      = input pointer (arg0)
#  r1      = a / input num_blks (arg1)
#  r2      = b / output pointer (arg2)
#  r3      = c
#  r4      = d
#  r5      = scratch
#  r6      = scratch
#  r7      = pointer to md5_t
#  r8      = output pointer
#  r9      = input num_blks
# r10 (sl) = not used
# r11 (fp) = not used
# r12 (ip) = not used
# r13 (sp) = stack pointer
# r14 (lr) = link register

    stmdb   sp!, {r4-r9}                            @ save registers on stack

    mov     r9, r1                                  @ r9 = num_blks
    mov     r8, r2                                  @ r8 = output pointer

    ldmia   r8, {r1-r4}                             @ get md5_state[0-3]

    movw    r7, #:lower16:md5_t                     @ r7 -> md5_t
    movt    r7, #:upper16:md5_t

    .align  2
next_blk:

# 16 rounds with F(x,y,z) = (x & y) | (~x & z)

    bic.w   r5, r4, r2                              @ ~b & d
    and.w   r6, r3, r2                              @ b & c
    orrs    r5, r6                                  @ F(b,c,d)
    add     r1, r5                                  @ a += F(b,c,d)
    ldr     r6, [r0]                                @ input[0]
    add     r1, r6                                  @ a += input[0]
    ldr     r6, [r7]                                @ t[0]
    add     r1, r6                                  @ a += t[0]
    add.w   r1, r2, r1, ror #25                     @ a = b + ROTL(a,7)

    bic.w   r5, r3, r1                              @ ~a & c
    and.w   r6, r2, r1                              @ a & b
    orrs    r5, r6                                  @ F(a,b,c)
    add     r4, r5                                  @ d += F(a,b,c)
    ldr     r6, [r0, $1<<2]                         @ input[1]
    add     r4, r6                                  @ d += input[1]
    ldr     r6, [r7, $1<<2]                         @ t[1]
    add     r4, r6                                  @ d += t[1]
    add.w   r4, r1, r4, ror #20                     @ d = a + ROTL(d,12)

    bic.w   r5, r2, r4                              @ ~d & b
    and.w   r6, r1, r4                              @ d & a
    orrs    r5, r6                                  @ F(d,a,b)
    add     r3, r5                                  @ c += F(d,a,b)
    ldr     r6, [r0, $2<<2]                         @ input[2]
    add     r3, r6                                  @ c += input[2]
    ldr     r6, [r7, $2<<2]                         @ t[2]
    add     r3, r6                                  @ c += t[2]
    add.w   r3, r4, r3, ror #15                     @ c = d + ROTL(c,17)

    bic.w   r5, r1, r3                              @ ~c & a
    and.w   r6, r4, r3                              @ c & d
    orrs    r5, r6                                  @ F(c,d,a)
    add     r2, r5                                  @ b += F(c,d,a)
    ldr     r6, [r0, $3<<2]                         @ input[3]
    add     r2, r6                                  @ b += input[3]
    ldr     r6, [r7, $3<<2]                         @ t[3]
    add     r2, r6                                  @ b += t[3]
    add.w   r2, r3, r2, ror #10                     @ b = c + ROTL(b,22)

    bic.w   r5, r4, r2                              @ ~b & d
    and.w   r6, r3, r2                              @ b & c
    orrs    r5, r6                                  @ F(b,c,d)
    add     r1, r5                                  @ a += F(b,c,d)
    ldr     r6, [r0, $4<<2]                         @ input[4]
    add     r1, r6                                  @ a += input[4]
    ldr     r6, [r7, $4<<2]                         @ t[4]
    add     r1, r6                                  @ a += t[4]
    add.w   r1, r2, r1, ror #25                     @ a = b + ROTL(a,7)

    bic.w   r5, r3, r1                              @ ~a & c
    and.w   r6, r2, r1                              @ a & b
    orrs    r5, r6                                  @ F(a,b,c)
    add     r4, r5                                  @ d += F(a,b,c)
    ldr     r6, [r0, $5<<2]                         @ input[5]
    add     r4, r6                                  @ d += input[5]
    ldr     r6, [r7, $5<<2]                         @ t[5]
    add     r4, r6                                  @ d += t[5]
    add.w   r4, r1, r4, ror #20                     @ d = a + ROTL(d,12)

    bic.w   r5, r2, r4                              @ ~d & b
    and.w   r6, r1, r4                              @ d & a
    orrs    r5, r6                                  @ F(d,a,b)
    add     r3, r5                                  @ c += F(d,a,b)
    ldr     r6, [r0, $6<<2]                         @ input[6]
    add     r3, r6                                  @ c += input[6]
    ldr     r6, [r7, $6<<2]                         @ t[6]
    add     r3, r6                                  @ c += t[6]
    add.w   r3, r4, r3, ror #15                     @ c = d + ROTL(c,17)

    bic.w   r5, r1, r3                              @ ~c & a
    and.w   r6, r4, r3                              @ c & d
    orrs    r5, r6                                  @ F(c,d,a)
    add     r2, r5                                  @ b += F(c,d,a)
    ldr     r6, [r0, $7<<2]                         @ input[7]
    add     r2, r6                                  @ b += input[7]
    ldr     r6, [r7, $7<<2]                         @ t[7]
    add     r2, r6                                  @ b += t[7]
    add.w   r2, r3, r2, ror #10                     @ b = c + ROTL(b,22)

    bic.w   r5, r4, r2                              @ ~b & d
    and.w   r6, r3, r2                              @ b & c
    orrs    r5, r6                                  @ F(b,c,d)
    add     r1, r5                                  @ a += F(b,c,d)
    ldr     r6, [r0, $8<<2]                         @ input[8]
    add     r1, r6                                  @ a += input[8]
    ldr     r6, [r7, $8<<2]                         @ t[8]
    add     r1, r6                                  @ a += t[8]
    add.w   r1, r2, r1, ror #25                     @ a = b + ROTL(a,7)

    bic.w   r5, r3, r1                              @ ~a & c
    and.w   r6, r2, r1                              @ a & b
    orrs    r5, r6                                  @ F(a,b,c)
    add     r4, r5                                  @ d += F(a,b,c)
    ldr     r6, [r0, $9<<2]                         @ input[9]
    add     r4, r6                                  @ d += input[9]
    ldr     r6, [r7, $9<<2]                         @ t[9]
    add     r4, r6                                  @ d += t[9]
    add.w   r4, r1, r4, ror #20                     @ d = a + ROTL(d,12)

    bic.w   r5, r2, r4                              @ ~d & b
    and.w   r6, r1, r4                              @ d & a
    orrs    r5, r6                                  @ F(d,a,b)
    add     r3, r5                                  @ c += F(d,a,b)
    ldr     r6, [r0, $10<<2]                        @ input[10]
    add     r3, r6                                  @ c += input[10]
    ldr     r6, [r7, $10<<2]                        @ t[10]
    add     r3, r6                                  @ c += t[10]
    add.w   r3, r4, r3, ror #15                     @ c = d + ROTL(c,17)

    bic.w   r5, r1, r3                              @ ~c & a
    and.w   r6, r4, r3                              @ c & d
    orrs    r5, r6                                  @ F(c,d,a)
    add     r2, r5                                  @ b += F(c,d,a)
    ldr     r6, [r0, $11<<2]                        @ input[11]
    add     r2, r6                                  @ b += input[11]
    ldr     r6, [r7, $11<<2]                        @ t[11]
    add     r2, r6                                  @ b += t[11]
    add.w   r2, r3, r2, ror #10                     @ b = c + ROTL(b,22)

    bic.w   r5, r4, r2                              @ ~b & d
    and.w   r6, r3, r2                              @ b & c
    orrs    r5, r6                                  @ F(b,c,d)
    add     r1, r5                                  @ a += F(b,c,d)
    ldr     r6, [r0, $12<<2]                        @ input[12]
    add     r1, r6                                  @ a += input[12]
    ldr     r6, [r7, $12<<2]                        @ t[12]
    add     r1, r6                                  @ a += t[12]
    add.w   r1, r2, r1, ror #25                     @ a = b + ROTL(a,7)

    bic.w   r5, r3, r1                              @ ~a & c
    and.w   r6, r2, r1                              @ a & b
    orrs    r5, r6                                  @ F(a,b,c)
    add     r4, r5                                  @ d += F(a,b,c)
    ldr     r6, [r0, $13<<2]                        @ input[13]
    add     r4, r6                                  @ d += input[13]
    ldr     r6, [r7, $13<<2]                        @ t[13]
    add     r4, r6                                  @ d += t[13]
    add.w   r4, r1, r4, ror #20                     @ d = a + ROTL(d,12)

    bic.w   r5, r2, r4                              @ ~d & b
    and.w   r6, r1, r4                              @ d & a
    orrs    r5, r6                                  @ F(d,a,b)
    add     r3, r5                                  @ c += F(d,a,b)
    ldr     r6, [r0, $14<<2]                        @ input[14]
    add     r3, r6                                  @ c += input[14]
    ldr     r6, [r7, $14<<2]                        @ t[14]
    add     r3, r6                                  @ c += t[14]
    add.w   r3, r4, r3, ror #15                     @ c = d + ROTL(c,17)

    bic.w   r5, r1, r3                              @ ~c & a
    and.w   r6, r4, r3                              @ c & d
    orrs    r5, r6                                  @ F(c,d,a)
    add     r2, r5                                  @ b += F(c,d,a)
    ldr     r6, [r0, $15<<2]                        @ input[15]
    add     r2, r6                                  @ b += input[15]
    ldr     r6, [r7, $15<<2]                        @ t[15]
    add     r2, r6                                  @ b += t[15]
    add.w   r2, r3, r2, ror #10                     @ b = c + ROTL(b,22)

# 16 rounds with G(x,y,z) = (x & z) | (y & ~z)

    bic.w   r5, r3, r4                              @ ~d & c
    and.w   r6, r2, r4                              @ d & b
    orrs    r5, r6                                  @ G(b,c,d)
    add     r1, r5                                  @ a += G(b,c,d)
    ldr     r6, [r0, $1<<2]                         @ input[1]
    add     r1, r6                                  @ a += input[1]
    ldr     r6, [r7, $16<<2]                        @ t[16]
    add     r1, r6                                  @ a += t[16]
    add.w   r1, r2, r1, ror #27                     @ a = b + ROTL(a,5)

    bic.w   r5, r2, r3                              @ ~c & b
    and.w   r6, r1, r3                              @ c & a
    orrs    r5, r6                                  @ G(a,b,c)
    add     r4, r5                                  @ d += G(a,b,c)
    ldr     r6, [r0, $6<<2]                         @ input[6]
    add     r4, r6                                  @ d += input[6]
    ldr     r6, [r7, $17<<2]                        @ t[17]
    add     r4, r6                                  @ d += t[17]
    add.w   r4, r1, r4, ror #23                     @ d = a + ROTL(d,9)

    bic.w   r5, r1, r2                              @ ~b & a
    and.w   r6, r4, r2                              @ b & d
    orrs    r5, r6                                  @ G(d,a,b)
    add     r3, r5                                  @ c += G(d,a,b)
    ldr     r6, [r0, $11<<2]                        @ input[11]
    add     r3, r6                                  @ c += input[11]
    ldr     r6, [r7, $18<<2]                        @ t[18]
    add     r3, r6                                  @ c += t[18]
    add.w   r3, r4, r3, ror #18                     @ c = d + ROTL(c,14)

    bic.w   r5, r4, r1                              @ ~a & d
    and.w   r6, r3, r1                              @ a & c
    orrs    r5, r6                                  @ G(d,a,b)
    add     r2, r5                                  @ b += G(c,d,a)
    ldr     r6, [r0]                                @ input[0]
    add     r2, r6                                  @ b += input[0]
    ldr     r6, [r7, $19<<2]                        @ t[19]
    add     r2, r6                                  @ b += t[19]
    add.w   r2, r3, r2, ror #12                     @ b = c + ROTL(b,20)

    bic.w   r5, r3, r4                              @ ~d & c
    and.w   r6, r2, r4                              @ d & b
    orrs    r5, r6                                  @ G(b,c,d)
    add     r1, r5                                  @ a += G(b,c,d)
    ldr     r6, [r0, $5<<2]                         @ input[5]
    add     r1, r6                                  @ a += input[5]
    ldr     r6, [r7, $20<<2]                        @ t[20]
    add     r1, r6                                  @ a += t[20]
    add.w   r1, r2, r1, ror #27                     @ a = b + ROTL(a,5)

    bic.w   r5, r2, r3                              @ ~c & b
    and.w   r6, r1, r3                              @ c & a
    orrs    r5, r6                                  @ G(a,b,c)
    add     r4, r5                                  @ d += G(a,b,c)
    ldr     r6, [r0, $10<<2]                        @ input[10]
    add     r4, r6                                  @ d += input[10]
    ldr     r6, [r7, $21<<2]                        @ t[21]
    add     r4, r6                                  @ d += t[21]
    add.w   r4, r1, r4, ror #23                     @ d = a + ROTL(d,9)

    bic.w   r5, r1, r2                              @ ~b & a
    and.w   r6, r4, r2                              @ b & d
    orrs    r5, r6                                  @ G(d,a,b)
    add     r3, r5                                  @ c += G(d,a,b)
    ldr     r6, [r0, $15<<2]                        @ input[15]
    add     r3, r6                                  @ c += input[15]
    ldr     r6, [r7, $22<<2]                        @ t[22]
    add     r3, r6                                  @ c += t[22]
    add.w   r3, r4, r3, ror #18                     @ c = d + ROTL(c,14)

    bic.w   r5, r4, r1                              @ ~a & d
    and.w   r6, r3, r1                              @ a & c
    orrs    r5, r6                                  @ G(d,a,b)
    add     r2, r5                                  @ b += G(c,d,a)
    ldr     r6, [r0, $4<<2]                         @ input[4]
    add     r2, r6                                  @ b += input[4]
    ldr     r6, [r7, $23<<2]                        @ t[23]
    add     r2, r6                                  @ b += t[23]
    add.w   r2, r3, r2, ror #12                     @ b = c + ROTL(b,20)

    bic.w   r5, r3, r4                              @ ~d & c
    and.w   r6, r2, r4                              @ d & b
    orrs    r5, r6                                  @ G(b,c,d)
    add     r1, r5                                  @ a += G(b,c,d)
    ldr     r6, [r0, $9<<2]                         @ input[9]
    add     r1, r6                                  @ a += input[9]
    ldr     r6, [r7, $24<<2]                        @ t[24]
    add     r1, r6                                  @ a += t[24]
    add.w   r1, r2, r1, ror #27                     @ a = b + ROTL(a,5)

    bic.w   r5, r2, r3                              @ ~c & b
    and.w   r6, r1, r3                              @ c & a
    orrs    r5, r6                                  @ G(a,b,c)
    add     r4, r5                                  @ d += G(a,b,c)
    ldr     r6, [r0, $14<<2]                        @ input[14]
    add     r4, r6                                  @ d += input[14]
    ldr     r6, [r7, $25<<2]                        @ t[25]
    add     r4, r6                                  @ d += t[25]
    add.w   r4, r1, r4, ror #23                     @ d = a + ROTL(d,9)

    bic.w   r5, r1, r2                              @ ~b & a
    and.w   r6, r4, r2                              @ b & d
    orrs    r5, r6                                  @ G(d,a,b)
    add     r3, r5                                  @ c += G(d,a,b)
    ldr     r6, [r0, $3<<2]                         @ input[3]
    add     r3, r6                                  @ c += input[3]
    ldr     r6, [r7, $26<<2]                        @ t[26]
    add     r3, r6                                  @ c += t[26]
    add.w   r3, r4, r3, ror #18                     @ c = d + ROTL(c,14)

    bic.w   r5, r4, r1                              @ ~a & d
    and.w   r6, r3, r1                              @ a & c
    orrs    r5, r6                                  @ G(d,a,b)
    add     r2, r5                                  @ b += G(c,d,a)
    ldr     r6, [r0, $8<<2]                         @ input[8]
    add     r2, r6                                  @ b += input[8]
    ldr     r6, [r7, $27<<2]                        @ t[27]
    add     r2, r6                                  @ b += t[27]
    add.w   r2, r3, r2, ror #12                     @ b = c + ROTL(b,20)

    bic.w   r5, r3, r4                              @ ~d & c
    and.w   r6, r2, r4                              @ d & b
    orrs    r5, r6                                  @ G(b,c,d)
    add     r1, r5                                  @ a += G(b,c,d)
    ldr     r6, [r0, $13<<2]                        @ input[13]
    add     r1, r6                                  @ a += input[13]
    ldr     r6, [r7, $28<<2]                        @ t[28]
    add     r1, r6                                  @ a += t[28]
    add.w   r1, r2, r1, ror #27                     @ a = b + ROTL(a,5)

    bic.w   r5, r2, r3                              @ ~c & b
    and.w   r6, r1, r3                              @ c & a
    orrs    r5, r6                                  @ G(a,b,c)
    add     r4, r5                                  @ d += G(a,b,c)
    ldr     r6, [r0, $2<<2]                         @ input[2]
    add     r4, r6                                  @ d += input[2]
    ldr     r6, [r7, $29<<2]                        @ t[29]
    add     r4, r6                                  @ d += t[29]
    add.w   r4, r1, r4, ror #23                     @ d = a + ROTL(d,9)

    bic.w   r5, r1, r2                              @ ~b & a
    and.w   r6, r4, r2                              @ b & d
    orrs    r5, r6                                  @ G(d,a,b)
    add     r3, r5                                  @ c += G(d,a,b)
    ldr     r6, [r0, $7<<2]                         @ input[7]
    add     r3, r6                                  @ c += input[7]
    ldr     r6, [r7, $30<<2]                        @ t[30]
    add     r3, r6                                  @ c += t[30]
    add.w   r3, r4, r3, ror #18                     @ c = d + ROTL(c,14)

    bic.w   r5, r4, r1                              @ ~a & d
    and.w   r6, r3, r1                              @ a & c
    orrs    r5, r6                                  @ G(d,a,b)
    add     r2, r5                                  @ b += G(c,d,a)
    ldr     r6, [r0, $12<<2]                        @ input[12]
    add     r2, r6                                  @ b += input[12]
    ldr     r6, [r7, $31<<2]                        @ t[31]
    add     r2, r6                                  @ b += t[31]
    add.w   r2, r3, r2, ror #12                     @ b = c + ROTL(b,20)

# 16 rounds with H(x,y,z) = x ^ y ^ z

    eor.w   r5, r2, r3                              @ b ^ c
    eors    r5, r4                                  @ H(b,c,d)
    add     r1, r5                                  @ a += H(b,c,d)
    ldr     r6, [r0, $5<<2]                         @ input[5]
    add     r1, r6                                  @ a += input[5]
    ldr     r6, [r7, $32<<2]                        @ t[32]
    add     r1, r6                                  @ a += t[32]
    add.w   r1, r2, r1, ror #28                     @ a = b + ROTL(a,4)

    eor.w   r5, r1, r2                              @ a ^ b
    eors    r5, r3                                  @ H(a,b,c)
    add     r4, r5                                  @ d += H(a,b,c)
    ldr     r6, [r0, $8<<2]                         @ input[8]
    add     r4, r6                                  @ d += input[8]
    ldr     r6, [r7, $33<<2]                        @ t[33]
    add     r4, r6                                  @ d += t[33]
    add.w   r4, r1, r4, ror #21                     @ d = a + ROTL(d,11)

    eor.w   r5, r4, r1                              @ d ^ a
    eors    r5, r2                                  @ H(d,a,b)
    add     r3, r5                                  @ c += H(d,a,b)
    ldr     r6, [r0, $11<<2]                        @ input[11]
    add     r3, r6                                  @ c += input[11]
    ldr     r6, [r7, $34<<2]                        @ t[34]
    add     r3, r6                                  @ c += t[34]
    add.w   r3, r4, r3, ror #16                     @ c = d + ROTL(c,16)

    eor.w   r5, r3, r4                              @ c ^ d
    eors    r5, r1                                  @ H(c,d,a)
    add     r2, r5                                  @ b += H(c,d,a)
    ldr     r6, [r0, $14<<2]                        @ input[14]
    add     r2, r6                                  @ b += input[14]
    ldr     r6, [r7, $35<<2]                        @ t[35]
    add     r2, r6                                  @ b += t[35]
    add.w   r2, r3, r2, ror #9                      @ b = c + ROTL(d,23)

    eor.w   r5, r2, r3                              @ b ^ c
    eors    r5, r4                                  @ H(b,c,d)
    add     r1, r5                                  @ a += H(b,c,d)
    ldr     r6, [r0, $1<<2]                         @ input[1]
    add     r1, r6                                  @ a += input[1]
    ldr     r6, [r7, $36<<2]                        @ t[36]
    add     r1, r6                                  @ a += t[36]
    add.w   r1, r2, r1, ror #28                     @ a = b + ROTL(a,4)

    eor.w   r5, r1, r2                              @ a ^ b
    eors    r5, r3                                  @ H(a,b,c)
    add     r4, r5                                  @ d += H(a,b,c)
    ldr     r6, [r0, $4<<2]                         @ input[4]
    add     r4, r6                                  @ d += input[4]
    ldr     r6, [r7, $37<<2]                        @ t[37]
    add     r4, r6                                  @ d += t[37]
    add.w   r4, r1, r4, ror #21                     @ d = a + ROTL(d,11)

    eor.w   r5, r4, r1                              @ d ^ a
    eors    r5, r2                                  @ H(d,a,b)
    add     r3, r5                                  @ c += H(d,a,b)
    ldr     r6, [r0, $7<<2]                         @ input[7]
    add     r3, r6                                  @ c += input[7]
    ldr     r6, [r7, $38<<2]                        @ t[38]
    add     r3, r6                                  @ c += t[38]
    add.w   r3, r4, r3, ror #16                     @ c = d + ROTL(c,16)

    eor.w   r5, r3, r4                              @ c ^ d
    eors    r5, r1                                  @ H(c,d,a)
    add     r2, r5                                  @ b += H(c,d,a)
    ldr     r6, [r0, $10<<2]                        @ input[10]
    add     r2, r6                                  @ b += input[10]
    ldr     r6, [r7, $39<<2]                        @ t[39]
    add     r2, r6                                  @ b += t[39]
    add.w   r2, r3, r2, ror #9                      @ b = c + ROTL(d,23)

    eor.w   r5, r2, r3                              @ b ^ c
    eors    r5, r4                                  @ H(b,c,d)
    add     r1, r5                                  @ a += H(b,c,d)
    ldr     r6, [r0, $13<<2]                        @ input[13]
    add     r1, r6                                  @ a += input[13]
    ldr     r6, [r7, $40<<2]                        @ t[40]
    add     r1, r6                                  @ a += t[40]
    add.w   r1, r2, r1, ror #28                     @ a = b + ROTL(a,4)

    eor.w   r5, r1, r2                              @ a ^ b
    eors    r5, r3                                  @ H(a,b,c)
    add     r4, r5                                  @ d += H(a,b,c)
    ldr     r6, [r0]                                @ input[0]
    add     r4, r6                                  @ d += input[0]
    ldr     r6, [r7, $41<<2]                        @ t[41]
    add     r4, r6                                  @ d += t[41]
    add.w   r4, r1, r4, ror #21                     @ d = a + ROTL(d,11)

    eor.w   r5, r4, r1                              @ d ^ a
    eors    r5, r2                                  @ H(d,a,b)
    add     r3, r5                                  @ c += H(d,a,b)
    ldr     r6, [r0, $3<<2]                         @ input[3]
    add     r3, r6                                  @ c += input[3]
    ldr     r6, [r7, $42<<2]                        @ t[42]
    add     r3, r6                                  @ c += t[42]
    add.w   r3, r4, r3, ror #16                     @ c = d + ROTL(c,16)

    eor.w   r5, r3, r4                              @ c ^ d
    eors    r5, r1                                  @ H(c,d,a)
    add     r2, r5                                  @ b += H(c,d,a)
    ldr     r6, [r0, $6<<2]                         @ input[6]
    add     r2, r6                                  @ b += input[6]
    ldr     r6, [r7, $43<<2]                        @ t[43]
    add     r2, r6                                  @ b += t[43]
    add.w   r2, r3, r2, ror #9                      @ b = c + ROTL(d,23)

    eor.w   r5, r2, r3                              @ b ^ c
    eors    r5, r4                                  @ H(b,c,d)
    add     r1, r5                                  @ a += H(b,c,d)
    ldr     r6, [r0, $9<<2]                         @ input[9]
    add     r1, r6                                  @ a += input[9]
    ldr     r6, [r7, $44<<2]                        @ t[44]
    add     r1, r6                                  @ a += t[44]
    add.w   r1, r2, r1, ror #28                     @ a = b + ROTL(a,4)

    eor.w   r5, r1, r2                              @ a ^ b
    eors    r5, r3                                  @ H(a,b,c)
    add     r4, r5                                  @ d += H(a,b,c)
    ldr     r6, [r0, $12<<2]                        @ input[12]
    add     r4, r6                                  @ d += input[12]
    ldr     r6, [r7, $45<<2]                        @ t[45]
    add     r4, r6                                  @ d += t[45]
    add.w   r4, r1, r4, ror #21                     @ d = a + ROTL(d,11)

    eor.w   r5, r4, r1                              @ d ^ a
    eors    r5, r2                                  @ H(d,a,b)
    add     r3, r5                                  @ c += H(d,a,b)
    ldr     r6, [r0, $15<<2]                        @ input[15]
    add     r3, r6                                  @ c += input[15]
    ldr     r6, [r7, $46<<2]                        @ t[46]
    add     r3, r6                                  @ c += t[46]
    add.w   r3, r4, r3, ror #16                     @ c = d + ROTL(c,16)

    eor.w   r5, r3, r4                              @ c ^ d
    eors    r5, r1                                  @ H(c,d,a)
    add     r2, r5                                  @ b += H(c,d,a)
    ldr     r6, [r0, $2<<2]                         @ input[2]
    add     r2, r6                                  @ b += input[2]
    ldr     r6, [r7, $47<<2]                        @ t[47]
    add     r2, r6                                  @ b += t[47]
    add.w   r2, r3, r2, ror #9                      @ b = c + ROTL(d,23)

# 16 rounds with I(x,y,z) = y ^ (x | ~z)

    orn     r5, r2, r4                              @ b | ~d
    eors    r5, r3                                  @ I(b,c,d)
    add     r1, r5                                  @ a += I(b,c,d)
    ldr     r6, [r0]                                @ input[0]
    add     r1, r6                                  @ a += input[0]
    ldr     r6, [r7, $48<<2]                        @ t[48]
    add     r1, r6                                  @ a += t[48]
    add.w   r1, r2, r1, ror #26                     @ a = b + ROTL(a,6)

    orn     r5, r1, r3                              @ a | ~c
    eors    r5, r2                                  @ I(a,b,c)
    add     r4, r5                                  @ d += I(a,b,c)
    ldr     r6, [r0, $7<<2]                         @ input[7]
    add     r4, r6                                  @ d += input[7]
    ldr     r6, [r7, $49<<2]                        @ t[49]
    add     r4, r6                                  @ d += t[49]
    add.w   r4, r1, r4, ror #22                     @ d = a + ROTL(d,10)

    orn     r5, r4, r2                              @ d | ~b
    eors    r5, r1                                  @ I(d,a,b)
    add     r3, r5                                  @ c += I(d,a,b)
    ldr     r6, [r0, $14<<2]                        @ input[14]
    add     r3, r6                                  @ c += input[14]
    ldr     r6, [r7, $50<<2]                        @ t[50]
    add     r3, r6                                  @ c += t[50]
    add.w   r3, r4, r3, ror #17                     @ c = d + ROTL(c,15)

    orn     r5, r3, r1                              @ c | ~a
    eors    r5, r4                                  @ I(c,d,a)
    add     r2, r5                                  @ b += I(c,d,a)
    ldr     r6, [r0, $5<<2]                         @ input[5]
    add     r2, r6                                  @ b += input[5]
    ldr     r6, [r7, $51<<2]                        @ t[51]
    add     r2, r6                                  @ b += t[51]
    add.w   r2, r3, r2, ror #11                     @ b = c + ROTL(b,21)

    orn     r5, r2, r4                              @ b | ~d
    eors    r5, r3                                  @ I(b,c,d)
    add     r1, r5                                  @ a += I(b,c,d)
    ldr     r6, [r0, $12<<2]                        @ input[12]
    add     r1, r6                                  @ a += input[12]
    ldr     r6, [r7, $52<<2]                        @ t[52]
    add     r1, r6                                  @ a += t[52]
    add.w   r1, r2, r1, ror #26                     @ a = b + ROTL(a,6)

    orn     r5, r1, r3                              @ a | ~c
    eors    r5, r2                                  @ I(a,b,c)
    add     r4, r5                                  @ d += I(a,b,c)
    ldr     r6, [r0, $3<<2]                         @ input[3]
    add     r4, r6                                  @ d += input[3]
    ldr     r6, [r7, $53<<2]                        @ t[53]
    add     r4, r6                                  @ d += t[53]
    add.w   r4, r1, r4, ror #22                     @ d = a + ROTL(d,10)

    orn     r5, r4, r2                              @ d | ~b
    eors    r5, r1                                  @ I(d,a,b)
    add     r3, r5                                  @ c += I(d,a,b)
    ldr     r6, [r0, $10<<2]                        @ input[10]
    add     r3, r6                                  @ c += input[10]
    ldr     r6, [r7, $54<<2]                        @ t[54]
    add     r3, r6                                  @ c += t[54]
    add.w   r3, r4, r3, ror #17                     @ c = d + ROTL(c,15)

    orn     r5, r3, r1                              @ c | ~a
    eors    r5, r4                                  @ I(c,d,a)
    add     r2, r5                                  @ b += I(c,d,a)
    ldr     r6, [r0, $1<<2]                         @ input[1]
    add     r2, r6                                  @ b += input[1]
    ldr     r6, [r7, $55<<2]                        @ t[55]
    add     r2, r6                                  @ b += t[55]
    add.w   r2, r3, r2, ror #11                     @ b = c + ROTL(b,21)

    orn     r5, r2, r4                              @ b | ~d
    eors    r5, r3                                  @ I(b,c,d)
    add     r1, r5                                  @ a += I(b,c,d)
    ldr     r6, [r0, $8<<2]                         @ input[8]
    add     r1, r6                                  @ a += input[8]
    ldr     r6, [r7, $56<<2]                        @ t[56]
    add     r1, r6                                  @ a += t[56]
    add.w   r1, r2, r1, ror #26                     @ a = b + ROTL(a,6)

    orn     r5, r1, r3                              @ a | ~c
    eors    r5, r2                                  @ I(a,b,c)
    add     r4, r5                                  @ d += I(a,b,c)
    ldr     r6, [r0, $15<<2]                        @ input[15]
    add     r4, r6                                  @ d += input[15]
    ldr     r6, [r7, $57<<2]                        @ t[57]
    add     r4, r6                                  @ d += t[57]
    add.w   r4, r1, r4, ror #22                     @ d = a + ROTL(d,10)

    orn     r5, r4, r2                              @ d | ~b
    eors    r5, r1                                  @ I(d,a,b)
    add     r3, r5                                  @ c += I(d,a,b)
    ldr     r6, [r0, $6<<2]                         @ input[6]
    add     r3, r6                                  @ c += input[6]
    ldr     r6, [r7, $58<<2]                        @ t[58]
    add     r3, r6                                  @ c += t[58]
    add.w   r3, r4, r3, ror #17                     @ c = d + ROTL(c,15)

    orn     r5, r3, r1                              @ c | ~a
    eors    r5, r4                                  @ I(c,d,a)
    add     r2, r5                                  @ b += I(c,d,a)
    ldr     r6, [r0, $13<<2]                        @ input[13]
    add     r2, r6                                  @ b += input[13]
    ldr     r6, [r7, $59<<2]                        @ t[59]
    add     r2, r6                                  @ b += t[59]
    add.w   r2, r3, r2, ror #11                     @ b = c + ROTL(b,21)

    orn     r5, r2, r4                              @ b | ~d
    eors    r5, r3                                  @ I(b,c,d)
    add     r1, r5                                  @ a += I(b,c,d)
    ldr     r6, [r0, $4<<2]                         @ input[4]
    add     r1, r6                                  @ a += input[4]
    ldr     r6, [r7, $60<<2]                        @ t[60]
    add     r1, r6                                  @ a += t[60]
    add.w   r1, r2, r1, ror #26                     @ a = b + ROTL(a,6)

    orn     r5, r1, r3                              @ a | ~c
    eors    r5, r2                                  @ I(a,b,c)
    add     r4, r5                                  @ d += I(a,b,c)
    ldr     r6, [r0, $11<<2]                        @ input[11]
    add     r4, r6                                  @ d += input[11]
    ldr     r6, [r7, $61<<2]                        @ t[61]
    add     r4, r6                                  @ d += t[61]
    add.w   r4, r1, r4, ror #22                     @ d = a + ROTL(d,10)

    orn     r5, r4, r2                              @ d | ~b
    eors    r5, r1                                  @ I(d,a,b)
    add     r3, r5                                  @ c += I(d,a,b)
    ldr     r6, [r0, $2<<2]                         @ input[2]
    add     r3, r6                                  @ c += input[2]
    ldr     r6, [r7, $62<<2]                        @ t[62]
    add     r3, r6                                  @ c += t[62]
    add.w   r3, r4, r3, ror #17                     @ c = d + ROTL(c,15)

    orn     r5, r3, r1                              @ c | ~a
    eors    r5, r4                                  @ I(c,d,a)
    add     r2, r5                                  @ b += I(c,d,a)
    ldr     r6, [r0, $9<<2]                         @ input[9]
    add     r2, r6                                  @ b += input[9]
    ldr     r6, [r7, $63<<2]                        @ t[63]
    add     r2, r6                                  @ b += t[63]
    add.w   r2, r3, r2, ror #11                     @ b = c + ROTL(b,21)

    ldr     r5, [r8]                                @ get original md5_stats[0]
    add     r1, r5
    ldr     r5, [r8, $1<<2]                         @ get original md5_stats[1]
    add     r2, r5
    ldr     r5, [r8, $2<<2]                         @ get original md5_stats[2]
    add     r3, r5
    ldr     r5, [r8, $3<<2]                         @ get original md5_stats[3]
    add     r4, r5

    stmia   r8, {r1-r4}                             @ store new md5_state[0-3]

    add     r0, $64                                 @ input ptr -> next block
    subs    r9, $1                                  @ decrement num_blks
    bne     next_blk

    ldmia   sp!, {r4-r9}                            @ restore regs and return
    bx      lr


#*******************************************************************************
#*******************************************************************************
#
# MD5: Updates MD5 state variables for one or more input message blocks
#   arguments
#           *msg_data   pointer to start of input message data
#           num_blks    number of 512-bit blocks to process
#           *md5_state  pointer to 120-bit block of MD5 state variables:
#                           a,b,c,d
#
#   calling convention
#   void    mmcau_md5_update  (const unsigned char *msg_data,
#                              const int            num_blks,
#                              unsigned char       *md5_state)


    .global _mmcau_md5_update
    .global mmcau_md5_update
    .type   mmcau_md5_update, %function
    .align  4

_mmcau_md5_update:
mmcau_md5_update:

    push    {r4-r7,lr}

    movw    r4, #:lower16:md5_initial_h             @ r4 -> initial data
    movt    r4, #:upper16:md5_initial_h

# copy initial data into hash output buffer
    ldmia   r4, {r4-r7}                             @ get md5[0-3]
    stmia   r2, {r4-r7}                             @ copy to md5_state[0-3]

    bl      mmcau_md5_hash_n                        @ call hash_n routine

    pop     {r4-r7,pc}

#*******************************************************************************
#*******************************************************************************
#
# MD5: Updates MD5 state variables for one input message block
#
#   arguments
#           *msg_data   pointer to start of input message data
#           *md5_state  pointer to 128-bit block of MD5 state variables: a,b,c,d
#
#   calling convention
#   void    mmucau_md5_hash (const unsigned char *msg_data,
#                            unsigned char       *md5_state)

    .global _mmcau_md5_hash
    .global mmcau_md5_hash
    .type   mmcau_md5_hash, %function
    .align  4

_mmcau_md5_hash:
mmcau_md5_hash:

    mov    r2, r1                                   @ arg1 (*md5_state) to arg2
    mov    r1, $1                                   @ num_blks = 1
    b      mmcau_md5_hash_n                         @ call hash_n routine


#*******************************************************************************

    .data
    .type   md5_initial_h, %object
    .align  4

md5_initial_h:
    .word   0x67452301                              @ initial a
    .word   0xefcdab89                              @ initial b
    .word   0x98badcfe                              @ initial c
    .word   0x10325476                              @ initial d

    .type   md5_t, %object
    .align  4
md5_t:
    .word   0xd76aa478
    .word   0xe8c7b756
    .word   0x242070db
    .word   0xc1bdceee
    .word   0xf57c0faf
    .word   0x4787c62a
    .word   0xa8304613
    .word   0xfd469501
    .word   0x698098d8
    .word   0x8b44f7af
    .word   0xffff5bb1
    .word   0x895cd7be
    .word   0x6b901122
    .word   0xfd987193
    .word   0xa679438e
    .word   0x49b40821
    .word   0xf61e2562
    .word   0xc040b340
    .word   0x265e5a51
    .word   0xe9b6c7aa
    .word   0xd62f105d
    .word   0x02441453
    .word   0xd8a1e681
    .word   0xe7d3fbc8
    .word   0x21e1cde6
    .word   0xc33707d6
    .word   0xf4d50d87
    .word   0x455a14ed
    .word   0xa9e3e905
    .word   0xfcefa3f8
    .word   0x676f02d9
    .word   0x8d2a4c8a
    .word   0xfffa3942
    .word   0x8771f681
    .word   0x6d9d6122
    .word   0xfde5380c
    .word   0xa4beea44
    .word   0x4bdecfa9
    .word   0xf6bb4b60
    .word   0xbebfbc70
    .word   0x289b7ec6
    .word   0xeaa127fa
    .word   0xd4ef3085
    .word   0x04881d05
    .word   0xd9d4d039
    .word   0xe6db99e5
    .word   0x1fa27cf8
    .word   0xc4ac5665
    .word   0xf4292244
    .word   0x432aff97
    .word   0xab9423a7
    .word   0xfc93a039
    .word   0x655b59c3
    .word   0x8f0ccc92
    .word   0xffeff47d
    .word   0x85845dd1
    .word   0x6fa87e4f
    .word   0xfe2ce6e0
    .word   0xa3014314
    .word   0x4e0811a1
    .word   0xf7537e82
    .word   0xbd3af235
    .word   0x2ad7d2bb
    .word   0xeb86d391
