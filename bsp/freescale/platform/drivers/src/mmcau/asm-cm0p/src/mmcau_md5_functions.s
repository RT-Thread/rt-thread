# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# Copyright (c) Freescale Semiconductor, Inc 2013.
#
# FILE NAME         : mmcau_md5_functions.s
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


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_MD5_INITIALIZE_OUTPUT
#   Initializes the MD5 state variables
#
#   ARGUMENTS
#   *md5_state      pointer to 120-bit block of md5 state variables: a,b,c,d
#
#   CALLING CONVENTION
#   void mmcau_md5_initialize_output (const unsigned int *md5_state)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_md5_initialize_output)
#   -----------+------------------------------------------------------------
#          r0  |  *md5_state    (arg0)
#              |
#        > r0  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_md5_initialize_output
    .global mmcau_md5_initialize_output
    .type   mmcau_md5_initialize_output, %function
    .align  4

_mmcau_md5_initialize_output:
mmcau_md5_initialize_output:

# store reg r4, we need to restore it at the end of the routine
    push    {r4}                            @ store reg

    ldr     r1, =md5_initial_h
    ldmia   r1, {r1-r4}                     @ load md5_initial_h[0-3]
    stmia   r0!, {r1-r4}                    @ store in md5_state[0-3]

    pop     {r4}                            @ restore reg
    bx      lr                              @ exit routine


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_MD5_HASH_N
#   Updates MD5 state variables for one or more input message blocks
#
#   ARGUMENTS
#   *msg_data       pointer to start of input message data
#   num_blks        number of 512-bit blocks to process
#   *md5_state      pointer to 128-bit block of MD5 state variables: a,b,c,d
#
#   CALLING CONVENTION
#   void mmucau_md5_hash_n     (const unsigned char     *msg_data,
#                               const int                num_blks,
#                               unsigned char           *md5_state)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_md5_hash_n)
#   -----------+------------------------------------------------------------
#          r0  |  *msg_data     (arg0)
#          r1  |  num_blks      (arg1)
#          r2  |  *md5_state    (arg2)
#              |
#        > r2  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_md5_hash_n
    .global mmcau_md5_hash_n
    .type   mmcau_md5_hash_n, %function
    .align  4

_mmcau_md5_hash_n:
mmcau_md5_hash_n:

# store num_blks and *md5_state, we need them later in the routine
# store regs r4-r7, we need to restore them at the end of the routine
    push    {r1-r2, r4-r7}                  @ store num_blks, *md5_state, regs

# initialize CAU data regs with current contents of md5_state[0-3]
    ldmia   r2, {r1-r4}                     @ load md5_state[0-3]

    ldr     r7, =md5_t                      @ set *md5_t
    b       next_blk
    .ltorg


    .align  2
next_blk:

#    REGISTER  |  ALLOCATION (throughout next_blk)
#   -----------+------------------------------------------------------------
#          r0  |  *msg_data (arg0)
#          r1  |  a / num_blks (arg1)
#          r2  |  b / *md5_state (arg2)
#          r3  |  c
#          r4  |  d
#          r5  |  scratch
#          r6  |  scratch
#          r7  |  *md5_t

# 16 rounds of F(x,y,z) = (x & y) | (~x & z)
# ******************************************
    mov     r5, r2                          @ b
    mvns    r6, r2                          @ ~b
    ands    r5, r3                          @ b & c
    ands    r6, r4                          @ ~b & d
    orrs    r5, r6                          @ F(b,c,d)
    add     r1, r5                          @ a += F(b,c,d)
    ldr     r6, [r0, #0<<2]                 @ load msg_data[0]
    add     r1, r6                          @ a += msg_data[0]
    ldmia   r7!, {r5}                       @ load md5_t[0], *md5_t++
    add     r1, r5                          @ a += md5_t[0]
    movs    r6, #25                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,7)
    add     r1, r2                          @ a = b + ROTL(a,7)

    mov     r5, r1                          @ a
    mvns    r6, r1                          @ ~a
    ands    r5, r2                          @ a & b
    ands    r6, r3                          @ ~a & c
    orrs    r5, r6                          @ F(a,b,c)
    add     r4, r5                          @ d += F(a,b,c)
    ldr     r6, [r0, #1<<2]                 @ load msg_data[1]
    add     r4, r6                          @ d += msg_data[1]
    ldmia   r7!, {r5}                       @ load md5_t[1], *md5_t++
    add     r4, r5                          @ d += md5_t[1]
    movs    r6, #20                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,12)
    add     r4, r1                          @ d = a + ROTL(d,12)

    mov     r5, r4                          @ d
    mvns    r6, r4                          @ ~d
    ands    r5, r1                          @ d & a
    ands    r6, r2                          @ ~d & b
    orrs    r5, r6                          @ F(d,a,b)
    add     r3, r5                          @ c += F(d,a,b)
    ldr     r6, [r0, #2<<2]                 @ load msg_data[2]
    add     r3, r6                          @ c += msg_data[2]
    ldmia   r7!, {r5}                       @ load md5_t[2], *md5_t++
    add     r3, r5                          @ c += md5_t[2]
    movs    r6, #15                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,17)
    add     r3, r4                          @ c = d + ROTL(c,17)

    mov     r5, r3                          @ c
    mvns    r6, r3                          @ ~c
    ands    r5, r4                          @ c & d
    ands    r6, r1                          @ ~c & a
    orrs    r5, r6                          @ F(c,d,a)
    add     r2, r5                          @ b += F(c,d,a)
    ldr     r6, [r0, #3<<2]                 @ load msg_data[3]
    add     r2, r6                          @ b += msg_data[3]
    ldmia   r7!, {r5}                       @ load md5_t[3], *md5_t++
    add     r2, r5                          @ b += md5_t[3]
    movs    r6, #10                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,22)
    add     r2, r3                          @ b = c + ROTL(b,22)

    mov     r5, r2                          @ b
    mvns    r6, r2                          @ ~b
    ands    r5, r3                          @ b & c
    ands    r6, r4                          @ ~b & d
    orrs    r5, r6                          @ F(b,c,d)
    add     r1, r5                          @ a += F(b,c,d)
    ldr     r6, [r0, #4<<2]                 @ load msg_data[4]
    add     r1, r6                          @ a += msg_data[4]
    ldmia   r7!, {r5}                       @ load md5_t[4], *md5_t++
    add     r1, r5                          @ a += md5_t[4]
    movs    r6, #25                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,7)
    add     r1, r2                          @ a = b + ROTL(a,7)

    mov     r5, r1                          @ a
    mvns    r6, r1                          @ ~a
    ands    r5, r2                          @ a & b
    ands    r6, r3                          @ ~a & c
    orrs    r5, r6                          @ F(a,b,c)
    add     r4, r5                          @ d += F(a,b,c)
    ldr     r6, [r0, #5<<2]                 @ load msg_data[5]
    add     r4, r6                          @ d += msg_data[5]
    ldmia   r7!, {r5}                       @ load md5_t[5], *md5_t++
    add     r4, r5                          @ d += md5_t[5]
    movs    r6, #20                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,12)
    add     r4, r1                          @ d = a + ROTL(d,12)

    mov     r5, r4                          @ d
    mvns    r6, r4                          @ ~d
    ands    r5, r1                          @ d & a
    ands    r6, r2                          @ ~d & b
    orrs    r5, r6                          @ F(d,a,b)
    add     r3, r5                          @ c += F(d,a,b)
    ldr     r6, [r0, #6<<2]                 @ load msg_data[6]
    add     r3, r6                          @ c += msg_data[6]
    ldmia   r7!, {r5}                       @ load md5_t[6], *md5_t++
    add     r3, r5                          @ c += md5_t[6]
    movs    r6, #15                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,17)
    add     r3, r4                          @ c = d + ROTL(c,17)

    mov     r5, r3                          @ c
    mvns    r6, r3                          @ ~c
    ands    r5, r4                          @ c & d
    ands    r6, r1                          @ ~c & a
    orrs    r5, r6                          @ F(c,d,a)
    add     r2, r5                          @ b += F(c,d,a)
    ldr     r6, [r0, #7<<2]                 @ load msg_data[7]
    add     r2, r6                          @ b += msg_data[7]
    ldmia   r7!, {r5}                       @ load md5_t[7], *md5_t++
    add     r2, r5                          @ b += md5_t[7]
    movs    r6, #10                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,22)
    add     r2, r3                          @ b = c + ROTL(b,22)

    mov     r5, r2                          @ b
    mvns    r6, r2                          @ ~b
    ands    r5, r3                          @ b & c
    ands    r6, r4                          @ ~b & d
    orrs    r5, r6                          @ F(b,c,d)
    add     r1, r5                          @ a += F(b,c,d)
    ldr     r6, [r0, #8<<2]                 @ load msg_data[8]
    add     r1, r6                          @ a += msg_data[8]
    ldmia   r7!, {r5}                       @ load md5_t[8], *md5_t++
    add     r1, r5                          @ a += md5_t[8]
    movs    r6, #25                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,7)
    add     r1, r2                          @ a = b + ROTL(a,7)

    mov     r5, r1                          @ a
    mvns    r6, r1                          @ ~a
    ands    r5, r2                          @ a & b
    ands    r6, r3                          @ ~a & c
    orrs    r5, r6                          @ F(a,b,c)
    add     r4, r5                          @ d += F(a,b,c)
    ldr     r6, [r0, #9<<2]                 @ load msg_data[9]
    add     r4, r6                          @ d += msg_data[9]
    ldmia   r7!, {r5}                       @ load md5_t[9], *md5_t++
    add     r4, r5                          @ d += md5_t[9]
    movs    r6, #20                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,12)
    add     r4, r1                          @ d = a + ROTL(d,12)

    mov     r5, r4                          @ d
    mvns    r6, r4                          @ ~d
    ands    r5, r1                          @ d & a
    ands    r6, r2                          @ ~d & b
    orrs    r5, r6                          @ F(d,a,b)
    add     r3, r5                          @ c += F(d,a,b)
    ldr     r6, [r0, #10<<2]                @ load msg_data[10]
    add     r3, r6                          @ c += msg_data[10]
    ldmia   r7!, {r5}                       @ load md5_t[10], *md5_t++
    add     r3, r5                          @ c += md5_t[10]
    movs    r6, #15                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,17)
    add     r3, r4                          @ c = d + ROTL(c,17)

    mov     r5, r3                          @ c
    mvns    r6, r3                          @ ~c
    ands    r5, r4                          @ c & d
    ands    r6, r1                          @ ~c & a
    orrs    r5, r6                          @ F(c,d,a)
    add     r2, r5                          @ b += F(c,d,a)
    ldr     r6, [r0, #11<<2]                @ load msg_data[11]
    add     r2, r6                          @ b += msg_data[11]
    ldmia   r7!, {r5}                       @ load md5_t[11], *md5_t++
    add     r2, r5                          @ b += md5_t[11]
    movs    r6, #10                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,22)
    add     r2, r3                          @ b = c + ROTL(b,22)

    mov     r5, r2                          @ b
    mvns    r6, r2                          @ ~b
    ands    r5, r3                          @ b & c
    ands    r6, r4                          @ ~b & d
    orrs    r5, r6                          @ F(b,c,d)
    add     r1, r5                          @ a += F(b,c,d)
    ldr     r6, [r0, #12<<2]                @ load msg_data[12]
    add     r1, r6                          @ a += msg_data[12]
    ldmia   r7!, {r5}                       @ load md5_t[12], *md5_t++
    add     r1, r5                          @ a += md5_t[12]
    movs    r6, #25                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,7)
    add     r1, r2                          @ a = b + ROTL(a,7)

    mov     r5, r1                          @ a
    mvns    r6, r1                          @ ~a
    ands    r5, r2                          @ a & b
    ands    r6, r3                          @ ~a & c
    orrs    r5, r6                          @ F(a,b,c)
    add     r4, r5                          @ d += F(a,b,c)
    ldr     r6, [r0, #13<<2]                @ load msg_data[13]
    add     r4, r6                          @ d += msg_data[13]
    ldmia   r7!, {r5}                       @ load md5_t[13], *md5_t++
    add     r4, r5                          @ d += md5_t[13]
    movs    r6, #20                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,12)
    add     r4, r1                          @ d = a + ROTL(d,12)

    mov     r5, r4                          @ d
    mvns    r6, r4                          @ ~d
    ands    r5, r1                          @ d & a
    ands    r6, r2                          @ ~d & b
    orrs    r5, r6                          @ F(d,a,b)
    add     r3, r5                          @ c += F(d,a,b)
    ldr     r6, [r0, #14<<2]                @ load msg_data[14]
    add     r3, r6                          @ c += msg_data[14]
    ldmia   r7!, {r5}                       @ load md5_t[14], *md5_t++
    add     r3, r5                          @ c += md5_t[14]
    movs    r6, #15                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,17)
    add     r3, r4                          @ c = d + ROTL(c,17)

    mov     r5, r3                          @ c
    mvns    r6, r3                          @ ~c
    ands    r5, r4                          @ c & d
    ands    r6, r1                          @ ~c & a
    orrs    r5, r6                          @ F(c,d,a)
    add     r2, r5                          @ b += F(c,d,a)
    ldr     r6, [r0, #15<<2]                @ load msg_data[15]
    add     r2, r6                          @ b += msg_data[15]
    ldmia   r7!, {r5}                       @ load md5_t[15], *md5_t++
    add     r2, r5                          @ b += md5_t[15]
    movs    r6, #10                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,22)
    add     r2, r3                          @ b = c + ROTL(b,22)

# 16 rounds of G(x,y,z) = (x & z) | (y & ~z)
# ******************************************
    mov     r5, r4                          @ d
    mvns    r6, r4                          @ ~d
    ands    r5, r2                          @ b & d
    ands    r6, r3                          @ c & ~d
    orrs    r5, r6                          @ G(b,c,d)
    add     r1, r5                          @ a += G(b,c,d)
    ldr     r6, [r0, #1<<2]                 @ load msg_data[1]
    add     r1, r6                          @ a += msg_data[1]
    ldmia   r7!, {r5}                       @ load md5_t[16], *md5_t++
    add     r1, r5                          @ a += md5_t[16]
    movs    r6, #27                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,5)
    add     r1, r2                          @ a = b + ROTL(a,5)

    mov     r5, r3                          @ c
    mvns    r6, r3                          @ ~c
    ands    r5, r1                          @ c & a
    ands    r6, r2                          @ b & ~c
    orrs    r5, r6                          @ G(a,b,c)
    add     r4, r5                          @ d += G(a,b,c)
    ldr     r6, [r0, #6<<2]                 @ load msg_data[6]
    add     r4, r6                          @ d += msg_data[6]
    ldmia   r7!, {r5}                       @ load md5_t[17], *md5_t++
    add     r4, r5                          @ d += md5_t[17]
    movs    r6, #23                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,9)
    add     r4, r1                          @ d = a + ROTL(d,9)

    mov     r5, r2                          @ b
    mvns    r6, r2                          @ ~b
    ands    r5, r4                          @ b & d
    ands    r6, r1                          @ a & ~b
    orrs    r5, r6                          @ G(d,a,b)
    add     r3, r5                          @ c += G(d,a,b)
    ldr     r6, [r0, #11<<2]                @ load msg_data[11]
    add     r3, r6                          @ c += msg_data[11]
    ldmia   r7!, {r5}                       @ load md5_t[18], *md5_t++
    add     r3, r5                          @ c += md5_t[18]
    movs    r6, #18                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,14)
    add     r3, r4                          @ c = d + ROTL(c,14)

    mov     r5, r1                          @ a
    mvns    r6, r1                          @ ~a
    ands    r5, r3                          @ a & c
    ands    r6, r4                          @ d & ~a
    orrs    r5, r6                          @ G(c,d,a)
    add     r2, r5                          @ b += G(c,d,a)
    ldr     r6, [r0, #0<<2]                 @ load msg_data[0]
    add     r2, r6                          @ b += msg_data[0]
    ldmia   r7!, {r5}                       @ load md5_t[19], *md5_t++
    add     r2, r5                          @ b += md5_t[19]
    movs    r6, #12                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,20)
    add     r2, r3                          @ b = c + ROTL(b,20)

    mov     r5, r4                          @ d
    mvns    r6, r4                          @ ~d
    ands    r5, r2                          @ b & d
    ands    r6, r3                          @ c & ~d
    orrs    r5, r6                          @ G(b,c,d)
    add     r1, r5                          @ a += G(b,c,d)
    ldr     r6, [r0, #5<<2]                 @ load msg_data[5]
    add     r1, r6                          @ a += msg_data[5]
    ldmia   r7!, {r5}                       @ load md5_t[20], *md5_t++
    add     r1, r5                          @ a += md5_t[20]
    movs    r6, #27                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,5)
    add     r1, r2                          @ a = b + ROTL(a,5)

    mov     r5, r3                          @ c
    mvns    r6, r3                          @ ~c
    ands    r5, r1                          @ c & a
    ands    r6, r2                          @ b & ~c
    orrs    r5, r6                          @ G(a,b,c)
    add     r4, r5                          @ d += G(a,b,c)
    ldr     r6, [r0, #10<<2]                @ load msg_data[10]
    add     r4, r6                          @ d += msg_data[10]
    ldmia   r7!, {r5}                       @ load md5_t[21], *md5_t++
    add     r4, r5                          @ d += md5_t[21]
    movs    r6, #23                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,9)
    add     r4, r1                          @ d = a + ROTL(d,9)

    mov     r5, r2                          @ b
    mvns    r6, r2                          @ ~b
    ands    r5, r4                          @ b & d
    ands    r6, r1                          @ a & ~b
    orrs    r5, r6                          @ G(d,a,b)
    add     r3, r5                          @ c += G(d,a,b)
    ldr     r6, [r0, #15<<2]                @ load msg_data[15]
    add     r3, r6                          @ c += msg_data[15]
    ldmia   r7!, {r5}                       @ load md5_t[22], *md5_t++
    add     r3, r5                          @ c += md5_t[22]
    movs    r6, #18                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,14)
    add     r3, r4                          @ c = d + ROTL(c,14)

    mov     r5, r1                          @ a
    mvns    r6, r1                          @ ~a
    ands    r5, r3                          @ a & c
    ands    r6, r4                          @ d & ~a
    orrs    r5, r6                          @ G(c,d,a)
    add     r2, r5                          @ b += G(c,d,a)
    ldr     r6, [r0, #4<<2]                 @ load msg_data[4]
    add     r2, r6                          @ b += msg_data[4]
    ldmia   r7!, {r5}                       @ load md5_t[23], *md5_t++
    add     r2, r5                          @ b += md5_t[23]
    movs    r6, #12                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,20)
    add     r2, r3                          @ b = c + ROTL(b,20)

    mov     r5, r4                          @ d
    mvns    r6, r4                          @ ~d
    ands    r5, r2                          @ b & d
    ands    r6, r3                          @ c & ~d
    orrs    r5, r6                          @ G(b,c,d)
    add     r1, r5                          @ a += G(b,c,d)
    ldr     r6, [r0, #9<<2]                 @ load msg_data[9]
    add     r1, r6                          @ a += msg_data[9]
    ldmia   r7!, {r5}                       @ load md5_t[24], *md5_t++
    add     r1, r5                          @ a += md5_t[24]
    movs    r6, #27                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,5)
    add     r1, r2                          @ a = b + ROTL(a,5)

    mov     r5, r3                          @ c
    mvns    r6, r3                          @ ~c
    ands    r5, r1                          @ c & a
    ands    r6, r2                          @ b & ~c
    orrs    r5, r6                          @ G(a,b,c)
    add     r4, r5                          @ d += G(a,b,c)
    ldr     r6, [r0, #14<<2]                @ load msg_data[14]
    add     r4, r6                          @ d += msg_data[14]
    ldmia   r7!, {r5}                       @ load md5_t[25], *md5_t++
    add     r4, r5                          @ d += md5_t[25]
    movs    r6, #23                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,9)
    add     r4, r1                          @ d = a + ROTL(d,9)

    mov     r5, r2                          @ b
    mvns    r6, r2                          @ ~b
    ands    r5, r4                          @ b & d
    ands    r6, r1                          @ a & ~b
    orrs    r5, r6                          @ G(d,a,b)
    add     r3, r5                          @ c += G(d,a,b)
    ldr     r6, [r0, #3<<2]                 @ load msg_data[3]
    add     r3, r6                          @ c += msg_data[3]
    ldmia   r7!, {r5}                       @ load md5_t[26], *md5_t++
    add     r3, r5                          @ c += md5_t[26]
    movs    r6, #18                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,14)
    add     r3, r4                          @ c = d + ROTL(c,14)

    mov     r5, r1                          @ a
    mvns    r6, r1                          @ ~a
    ands    r5, r3                          @ a & c
    ands    r6, r4                          @ d & ~a
    orrs    r5, r6                          @ G(c,d,a)
    add     r2, r5                          @ b += G(c,d,a)
    ldr     r6, [r0, #8<<2]                 @ load msg_data[8]
    add     r2, r6                          @ b += msg_data[8]
    ldmia   r7!, {r5}                       @ load md5_t[27], *md5_t++
    add     r2, r5                          @ b += md5_t[27]
    movs    r6, #12                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,20)
    add     r2, r3                          @ b = c + ROTL(b,20)

    mov     r5, r4                          @ d
    mvns    r6, r4                          @ ~d
    ands    r5, r2                          @ b & d
    ands    r6, r3                          @ c & ~d
    orrs    r5, r6                          @ G(b,c,d)
    add     r1, r5                          @ a += G(b,c,d)
    ldr     r6, [r0, #13<<2]                @ load msg_data[13]
    add     r1, r6                          @ a += msg_data[13]
    ldmia   r7!, {r5}                       @ load md5_t[28], *md5_t++
    add     r1, r5                          @ a += md5_t[28]
    movs    r6, #27                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,5)
    add     r1, r2                          @ a = b + ROTL(a,5)

    mov     r5, r3                          @ c
    mvns    r6, r3                          @ ~c
    ands    r5, r1                          @ c & a
    ands    r6, r2                          @ b & ~c
    orrs    r5, r6                          @ G(a,b,c)
    add     r4, r5                          @ d += G(a,b,c)
    ldr     r6, [r0, #2<<2]                 @ load msg_data[2]
    add     r4, r6                          @ d += msg_data[2]
    ldmia   r7!, {r5}                       @ load md5_t[29], *md5_t++
    add     r4, r5                          @ d += md5_t[29]
    movs    r6, #23                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,9)
    add     r4, r1                          @ d = a + ROTL(d,9)

    mov     r5, r2                          @ b
    mvns    r6, r2                          @ ~b
    ands    r5, r4                          @ b & d
    ands    r6, r1                          @ a & ~b
    orrs    r5, r6                          @ G(d,a,b)
    add     r3, r5                          @ c += G(d,a,b)
    ldr     r6, [r0, #7<<2]                 @ load msg_data[7]
    add     r3, r6                          @ c += msg_data[7]
    ldmia   r7!, {r5}                       @ load md5_t[30], *md5_t++
    add     r3, r5                          @ c += md5_t[30]
    movs    r6, #18                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,14)
    add     r3, r4                          @ c = d + ROTL(c,14)

    mov     r5, r1                          @ a
    mvns    r6, r1                          @ ~a
    ands    r5, r3                          @ a & c
    ands    r6, r4                          @ d & ~a
    orrs    r5, r6                          @ G(c,d,a)
    add     r2, r5                          @ b += G(c,d,a)
    ldr     r6, [r0, #12<<2]                @ load msg_data[12]
    add     r2, r6                          @ b += msg_data[12]
    ldmia   r7!, {r5}                       @ load md5_t[31], *md5_t++
    add     r2, r5                          @ b += md5_t[31]
    movs    r6, #12                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,20)
    add     r2, r3                          @ b = c + ROTL(b,20)

# 16 rounds of H(x,y,z) = x ^ y ^ z
# *********************************
    mov     r5, r2                          @ b
    eors    r5, r3                          @ b ^ c
    eors    r5, r4                          @ H(b,c,d)
    add     r1, r5                          @ a += H(b,c,d)
    ldr     r6, [r0, #5<<2]                 @ load msg_data[5]
    add     r1, r6                          @ a += msg_data[5]
    ldmia   r7!, {r5}                       @ load md5_t[32], *md5_t++
    add     r1, r5                          @ a += md5_t[32]
    movs    r6, #28                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,4)
    add     r1, r2                          @ a = b + ROTL(a,4)

    mov     r5, r1                          @ a
    eors    r5, r2                          @ a ^ b
    eors    r5, r3                          @ H(a,b,c)
    add     r4, r5                          @ d += H(a,b,c)
    ldr     r6, [r0, #8<<2]                 @ load msg_data[8]
    add     r4, r6                          @ d += msg_data[8]
    ldmia   r7!, {r5}                       @ load md5_t[33], *md5_t++
    add     r4, r5                          @ d += md5_t[33]
    movs    r6, #21                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,11)
    add     r4, r1                          @ d = a + ROTL(d,11)

    mov     r5, r4                          @ d
    eors    r5, r1                          @ d ^ a
    eors    r5, r2                          @ H(d,a,b)
    add     r3, r5                          @ c += H(d,a,b)
    ldr     r6, [r0, #11<<2]                @ load msg_data[11]
    add     r3, r6                          @ c += msg_data[11]
    ldmia   r7!, {r5}                       @ load md5_t[34], *md5_t++
    add     r3, r5                          @ c += md5_t[34]
    movs    r6, #16                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,16)
    add     r3, r4                          @ c = d + ROTL(c,16)

    mov     r5, r3                          @ c
    eors    r5, r4                          @ c ^ d
    eors    r5, r1                          @ H(c,d,a)
    add     r2, r5                          @ b += H(c,d,a)
    ldr     r6, [r0, #14<<2]                @ load msg_data[14]
    add     r2, r6                          @ b += msg_data[14]
    ldmia   r7!, {r5}                       @ load md5_t[35], *md5_t++
    add     r2, r5                          @ b += md5_t[35]
    movs    r6, #9                          @ amount to rotate
    rors    r2, r6                          @ ROTL(b,23)
    add     r2, r3                          @ b = c + ROTL(b,23)

    mov     r5, r2                          @ b
    eors    r5, r3                          @ b ^ c
    eors    r5, r4                          @ H(b,c,d)
    add     r1, r5                          @ a += H(b,c,d)
    ldr     r6, [r0, #1<<2]                 @ load msg_data[1]
    add     r1, r6                          @ a += msg_data[1]
    ldmia   r7!, {r5}                       @ load md5_t[36], *md5_t++
    add     r1, r5                          @ a += md5_t[36]
    movs    r6, #28                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,4)
    add     r1, r2                          @ a = b + ROTL(a,4)

    mov     r5, r1                          @ a
    eors    r5, r2                          @ a ^ b
    eors    r5, r3                          @ H(a,b,c)
    add     r4, r5                          @ d += H(a,b,c)
    ldr     r6, [r0, #4<<2]                 @ load msg_data[4]
    add     r4, r6                          @ d += msg_data[4]
    ldmia   r7!, {r5}                       @ load md5_t[37], *md5_t++
    add     r4, r5                          @ d += md5_t[37]
    movs    r6, #21                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,11)
    add     r4, r1                          @ d = a + ROTL(d,11)

    mov     r5, r4                          @ d
    eors    r5, r1                          @ d ^ a
    eors    r5, r2                          @ H(d,a,b)
    add     r3, r5                          @ c += H(d,a,b)
    ldr     r6, [r0, #7<<2]                 @ load msg_data[7]
    add     r3, r6                          @ c += msg_data[7]
    ldmia   r7!, {r5}                       @ load md5_t[38], *md5_t++
    add     r3, r5                          @ c += md5_t[38]
    movs    r6, #16                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,16)
    add     r3, r4                          @ c = d + ROTL(c,16)

    mov     r5, r3                          @ c
    eors    r5, r4                          @ c ^ d
    eors    r5, r1                          @ H(c,d,a)
    add     r2, r5                          @ b += H(c,d,a)
    ldr     r6, [r0, #10<<2]                @ load msg_data[10]
    add     r2, r6                          @ b += msg_data[10]
    ldmia   r7!, {r5}                       @ load md5_t[39], *md5_t++
    add     r2, r5                          @ b += md5_t[39]
    movs    r6, #9                          @ amount to rotate
    rors    r2, r6                          @ ROTL(b,23)
    add     r2, r3                          @ b = c + ROTL(b,23)

    mov     r5, r2                          @ b
    eors    r5, r3                          @ b ^ c
    eors    r5, r4                          @ H(b,c,d)
    add     r1, r5                          @ a += H(b,c,d)
    ldr     r6, [r0, #13<<2]                @ load msg_data[13]
    add     r1, r6                          @ a += msg_data[13]
    ldmia   r7!, {r5}                       @ load md5_t[40], *md5_t++
    add     r1, r5                          @ a += md5_t[40]
    movs    r6, #28                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,4)
    add     r1, r2                          @ a = b + ROTL(a,4)

    mov     r5, r1                          @ a
    eors    r5, r2                          @ a ^ b
    eors    r5, r3                          @ H(a,b,c)
    add     r4, r5                          @ d += H(a,b,c)
    ldr     r6, [r0, #0<<2]                 @ load msg_data[0]
    add     r4, r6                          @ d += msg_data[0]
    ldmia   r7!, {r5}                       @ load md5_t[41], *md5_t++
    add     r4, r5                          @ d += md5_t[41]
    movs    r6, #21                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,11)
    add     r4, r1                          @ d = a + ROTL(d,11)

    mov     r5, r4                          @ d
    eors    r5, r1                          @ d ^ a
    eors    r5, r2                          @ H(d,a,b)
    add     r3, r5                          @ c += H(d,a,b)
    ldr     r6, [r0, #3<<2]                 @ load msg_data[3]
    add     r3, r6                          @ c += msg_data[3]
    ldmia   r7!, {r5}                       @ load md5_t[42], *md5_t++
    add     r3, r5                          @ c += md5_t[42]
    movs    r6, #16                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,16)
    add     r3, r4                          @ c = d + ROTL(c,16)

    mov     r5, r3                          @ c
    eors    r5, r4                          @ c ^ d
    eors    r5, r1                          @ H(c,d,a)
    add     r2, r5                          @ b += H(c,d,a)
    ldr     r6, [r0, #6<<2]                 @ load msg_data[6]
    add     r2, r6                          @ b += msg_data[6]
    ldmia   r7!, {r5}                       @ load md5_t[43], *md5_t++
    add     r2, r5                          @ b += md5_t[43]
    movs    r6, #9                          @ amount to rotate
    rors    r2, r6                          @ ROTL(b,23)
    add     r2, r3                          @ b = c + ROTL(b,23)

    mov     r5, r2                          @ b
    eors    r5, r3                          @ b ^ c
    eors    r5, r4                          @ H(b,c,d)
    add     r1, r5                          @ a += H(b,c,d)
    ldr     r6, [r0, #9<<2]                 @ load msg_data[9]
    add     r1, r6                          @ a += msg_data[9]
    ldmia   r7!, {r5}                       @ load md5_t[44], *md5_t++
    add     r1, r5                          @ a += md5_t[44]
    movs    r6, #28                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,4)
    add     r1, r2                          @ a = b + ROTL(a,4)

    mov     r5, r1                          @ a
    eors    r5, r2                          @ a ^ b
    eors    r5, r3                          @ H(a,b,c)
    add     r4, r5                          @ d += H(a,b,c)
    ldr     r6, [r0, #12<<2]                @ load msg_data[12]
    add     r4, r6                          @ d += msg_data[12]
    ldmia   r7!, {r5}                       @ load md5_t[45], *md5_t++
    add     r4, r5                          @ d += md5_t[45]
    movs    r6, #21                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,11)
    add     r4, r1                          @ d = a + ROTL(d,11)

    mov     r5, r4                          @ d
    eors    r5, r1                          @ d ^ a
    eors    r5, r2                          @ H(d,a,b)
    add     r3, r5                          @ c += H(d,a,b)
    ldr     r6, [r0, #15<<2]                @ load msg_data[15]
    add     r3, r6                          @ c += msg_data[15]
    ldmia   r7!, {r5}                       @ load md5_t[46], *md5_t++
    add     r3, r5                          @ c += md5_t[46]
    movs    r6, #16                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,16)
    add     r3, r4                          @ c = d + ROTL(c,16)

    mov     r5, r3                          @ c
    eors    r5, r4                          @ c ^ d
    eors    r5, r1                          @ H(c,d,a)
    add     r2, r5                          @ b += H(c,d,a)
    ldr     r6, [r0, #2<<2]                 @ load msg_data[2]
    add     r2, r6                          @ b += msg_data[2]
    ldmia   r7!, {r5}                       @ load md5_t[47], *md5_t++
    add     r2, r5                          @ b += md5_t[47]
    movs    r6, #9                          @ amount to rotate
    rors    r2, r6                          @ ROTL(b,23)
    add     r2, r3                          @ b = c + ROTL(b,23)

# 16 rounds of I(x,y,z) = y ^ (x | ~z)
# ************************************
    mvns    r5, r4                          @ ~d
    orrs    r5, r2                          @ b | ~d
    eors    r5, r3                          @ I(b,c,d)
    add     r1, r5                          @ a += I(b,c,d)
    ldr     r6, [r0, #0<<2]                 @ load msg_data[0]
    add     r1, r6                          @ a += msg_data[0]
    ldmia   r7!, {r5}                       @ load md5_t[48], *md5_t++
    add     r1, r5                          @ a += md5_t[48]
    movs    r6, #26                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,6)
    add     r1, r2                          @ a = b + ROTL(a,6)

    mvns    r5, r3                          @ ~c
    orrs    r5, r1                          @ a | ~c
    eors    r5, r2                          @ I(a,b,c)
    add     r4, r5                          @ d += I(a,b,c)
    ldr     r6, [r0, #7<<2]                 @ load msg_data[7]
    add     r4, r6                          @ d += msg_data[7]
    ldmia   r7!, {r5}                       @ load md5_t[49], *md5_t++
    add     r4, r5                          @ d += md5_t[49]
    movs    r6, #22                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,10)
    add     r4, r1                          @ d = a + ROTL(d,10)

    mvns    r5, r2                          @ ~b
    orrs    r5, r4                          @ d | ~b
    eors    r5, r1                          @ I(d,a,b)
    add     r3, r5                          @ c += I(d,a,b)
    ldr     r6, [r0, #14<<2]                @ load msg_data[14]
    add     r3, r6                          @ c += msg_data[14]
    ldmia   r7!, {r5}                       @ load md5_t[50], *md5_t++
    add     r3, r5                          @ c += md5_t[50]
    movs    r6, #17                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,15)
    add     r3, r4                          @ c = d + ROTL(c,15)

    mvns    r5, r1                          @ ~a
    orrs    r5, r3                          @ c | ~a
    eors    r5, r4                          @ I(c,d,a)
    add     r2, r5                          @ b += I(c,d,a)
    ldr     r6, [r0, #5<<2]                 @ load msg_data[5]
    add     r2, r6                          @ b += msg_data[5]
    ldmia   r7!, {r5}                       @ load md5_t[51], *md5_t++
    add     r2, r5                          @ b += md5_t[51]
    movs    r6, #11                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,21)
    add     r2, r3                          @ b = c + ROTL(b,21)

    mvns    r5, r4                          @ ~d
    orrs    r5, r2                          @ b | ~d
    eors    r5, r3                          @ I(b,c,d)
    add     r1, r5                          @ a += I(b,c,d)
    ldr     r6, [r0, #12<<2]                @ load msg_data[12]
    add     r1, r6                          @ a += msg_data[12]
    ldmia   r7!, {r5}                       @ load md5_t[52], *md5_t++
    add     r1, r5                          @ a += md5_t[52]
    movs    r6, #26                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,6)
    add     r1, r2                          @ a = b + ROTL(a,6)

    mvns    r5, r3                          @ ~c
    orrs    r5, r1                          @ a | ~c
    eors    r5, r2                          @ I(a,b,c)
    add     r4, r5                          @ d += I(a,b,c)
    ldr     r6, [r0, #3<<2]                 @ load msg_data[3]
    add     r4, r6                          @ d += msg_data[3]
    ldmia   r7!, {r5}                       @ load md5_t[53], *md5_t++
    add     r4, r5                          @ d += md5_t[53]
    movs    r6, #22                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,10)
    add     r4, r1                          @ d = a + ROTL(d,10)

    mvns    r5, r2                          @ ~b
    orrs    r5, r4                          @ d | ~b
    eors    r5, r1                          @ I(d,a,b)
    add     r3, r5                          @ c += I(d,a,b)
    ldr     r6, [r0, #10<<2]                @ load msg_data[10]
    add     r3, r6                          @ c += msg_data[10]
    ldmia   r7!, {r5}                       @ load md5_t[54], *md5_t++
    add     r3, r5                          @ c += md5_t[54]
    movs    r6, #17                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,15)
    add     r3, r4                          @ c = d + ROTL(c,15)

    mvns    r5, r1                          @ ~a
    orrs    r5, r3                          @ c | ~a
    eors    r5, r4                          @ I(c,d,a)
    add     r2, r5                          @ b += I(c,d,a)
    ldr     r6, [r0, #1<<2]                 @ load msg_data[1]
    add     r2, r6                          @ b += msg_data[1]
    ldmia   r7!, {r5}                       @ load md5_t[55], *md5_t++
    add     r2, r5                          @ b += md5_t[55]
    movs    r6, #11                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,21)
    add     r2, r3                          @ b = c + ROTL(b,21)

    mvns    r5, r4                          @ ~d
    orrs    r5, r2                          @ b | ~d
    eors    r5, r3                          @ I(b,c,d)
    add     r1, r5                          @ a += I(b,c,d)
    ldr     r6, [r0, #8<<2]                 @ load msg_data[8]
    add     r1, r6                          @ a += msg_data[8]
    ldmia   r7!, {r5}                       @ load md5_t[56], *md5_t++
    add     r1, r5                          @ a += md5_t[56]
    movs    r6, #26                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,6)
    add     r1, r2                          @ a = b + ROTL(a,6)

    mvns    r5, r3                          @ ~c
    orrs    r5, r1                          @ a | ~c
    eors    r5, r2                          @ I(a,b,c)
    add     r4, r5                          @ d += I(a,b,c)
    ldr     r6, [r0, #15<<2]                @ load msg_data[15]
    add     r4, r6                          @ d += msg_data[15]
    ldmia   r7!, {r5}                       @ load md5_t[57], *md5_t++
    add     r4, r5                          @ d += md5_t[57]
    movs    r6, #22                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,10)
    add     r4, r1                          @ d = a + ROTL(d,10)

    mvns    r5, r2                          @ ~b
    orrs    r5, r4                          @ d | ~b
    eors    r5, r1                          @ I(d,a,b)
    add     r3, r5                          @ c += I(d,a,b)
    ldr     r6, [r0, #6<<2]                 @ load msg_data[6]
    add     r3, r6                          @ c += msg_data[6]
    ldmia   r7!, {r5}                       @ load md5_t[58], *md5_t++
    add     r3, r5                          @ c += md5_t[58]
    movs    r6, #17                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,15)
    add     r3, r4                          @ c = d + ROTL(c,15)

    mvns    r5, r1                          @ ~a
    orrs    r5, r3                          @ c | ~a
    eors    r5, r4                          @ I(c,d,a)
    add     r2, r5                          @ b += I(c,d,a)
    ldr     r6, [r0, #13<<2]                @ load msg_data[13]
    add     r2, r6                          @ b += msg_data[13]
    ldmia   r7!, {r5}                       @ load md5_t[59], *md5_t++
    add     r2, r5                          @ b += md5_t[59]
    movs    r6, #11                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,21)
    add     r2, r3                          @ b = c + ROTL(b,21)

    mvns    r5, r4                          @ ~d
    orrs    r5, r2                          @ b | ~d
    eors    r5, r3                          @ I(b,c,d)
    add     r1, r5                          @ a += I(b,c,d)
    ldr     r6, [r0, #4<<2]                 @ load msg_data[4]
    add     r1, r6                          @ a += msg_data[4]
    ldmia   r7!, {r5}                       @ load md5_t[60], *md5_t++
    add     r1, r5                          @ a += md5_t[60]
    movs    r6, #26                         @ amount to rotate
    rors    r1, r6                          @ ROTL(a,6)
    add     r1, r2                          @ a = b + ROTL(a,6)

    mvns    r5, r3                          @ ~c
    orrs    r5, r1                          @ a | ~c
    eors    r5, r2                          @ I(a,b,c)
    add     r4, r5                          @ d += I(a,b,c)
    ldr     r6, [r0, #11<<2]                @ load msg_data[11]
    add     r4, r6                          @ d += msg_data[11]
    ldmia   r7!, {r5}                       @ load md5_t[61], *md5_t++
    add     r4, r5                          @ d += md5_t[61]
    movs    r6, #22                         @ amount to rotate
    rors    r4, r6                          @ ROTL(d,10)
    add     r4, r1                          @ d = a + ROTL(d,10)

    mvns    r5, r2                          @ ~b
    orrs    r5, r4                          @ d | ~b
    eors    r5, r1                          @ I(d,a,b)
    add     r3, r5                          @ c += I(d,a,b)
    ldr     r6, [r0, #2<<2]                 @ load msg_data[2]
    add     r3, r6                          @ c += msg_data[2]
    ldmia   r7!, {r5}                       @ load md5_t[62], *md5_t++
    add     r3, r5                          @ c += md5_t[62]
    movs    r6, #17                         @ amount to rotate
    rors    r3, r6                          @ ROTL(c,15)
    add     r3, r4                          @ c = d + ROTL(c,15)

    mvns    r5, r1                          @ ~a
    orrs    r5, r3                          @ c | ~a
    eors    r5, r4                          @ I(c,d,a)
    add     r2, r5                          @ b += I(c,d,a)
    ldr     r6, [r0, #9<<2]                 @ load msg_data[9]
    add     r2, r6                          @ b += msg_data[9]
    ldmia   r7!, {r5}                       @ load md5_t[63], *md5_t++
    add     r2, r5                          @ b += md5_t[63]
    movs    r6, #11                         @ amount to rotate
    rors    r2, r6                          @ ROTL(b,21)
    add     r2, r3                          @ b = c + ROTL(b,21)

# after 16 rounds of F, G, H, and I, update md5_state
    ldr     r6, [sp, #4]                    @ restore *md5_state
    ldr     r5, [r6, #0<<2]                 @ load md5_state[0]
    add     r1, r5                          @ a += md5_state[0]
    ldr     r5, [r6, #1<<2]                 @ load md5_state[1]
    add     r2, r5                          @ b += md5_state[1]
    ldr     r5, [r6, #2<<2]                 @ load md5_state[2]
    add     r3, r5                          @ c += md5_state[2]
    ldr     r5, [r6, #3<<2]                 @ load md5_state[3]
    add     r4, r5                          @ d += md5_state[3]
    stmia   r6!, {r1-r4}                    @ store updated md5_state[0-3]

# check if we need to repeat num_blks
    ldr     r5, [sp, #0]                    @ restore num_blks
    subs    r5, #1                          @ decrement num_blks
    bne     next_blk_repeat                 @ check num_blks

# if num_blks = 0,
    add     sp, #8                          @ set sp = *{r4-r7}
    pop     {r4-r7}                         @ restore regs
    bx      lr                              @ exit routine

# else (num_blks > 0),
next_blk_repeat:
    adds    r0, #64                         @ *msg_data -> next block of data
    str     r5, [sp, #0]                    @ store num_blks
    ldr     r7, =md5_t                      @ reset *md5_t
    b       next_blk                        @ repeat next_blk


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_MD5_UPDATE
#   Updates MD5 state variables for one or more input message blocks
#
#   ARGUMENTS
#   *msg_data       pointer to start of input message data
#   num_blks        number of 512-bit blocks to process
#   *md5_state      pointer to 120-bit block of MD5 state variables: a,b,c,d
#
#   CALLING CONVENTION
#   void mmcau_md5_update      (const unsigned char     *msg_data,
#                               const int               num_blks,
#                               unsigned char           *md5_state)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_md5_update)
#   -----------+------------------------------------------------------------
#          r0  |  *msg_data     (arg0)
#          r1  |  num_blks      (arg1)
#          r2  |  *md5_state    (arg2)
#              |
#        > r2  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_md5_update
    .global mmcau_md5_update
    .type   mmcau_md5_update, %function
    .align  4

_mmcau_md5_update:
mmcau_md5_update:

# store regs r4-r7 and r14, we need to restore them at the end of the routine
    push    {r4-r7, lr}                     @ store regs

    ldr     r4, =md5_initial_h
    ldmia   r4, {r4-r7}                     @ load md5_initial_h[0-3]
    stmia   r2!, {r4-r7}                    @ store in md5_state[0-3]
    subs    r2, #4<<2                       @ reset *md5_state

    bl      mmcau_md5_hash_n                @ do mmcau_md5_hash_n

    pop     {r4-r7, pc}                     @ restore regs, exit routine


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   MMCAU_MD5_HASH
#   Updates MD5 state variables for one input message block
#
#   ARGUMENTS
#   *msg_data       pointer to start of input message data
#   *md5_state      pointer to 128-bit block of MD5 state variables: a,b,c,d
#
#   CALLING CONVENTION
#   void mmucau_md5_hash       (const unsigned char     *msg_data,
#                               unsigned char           *md5_state)
#
#  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
#
#    REGISTER  |  ALLOCATION (at the start of mmcau_md5_hash)
#   -----------+------------------------------------------------------------
#          r0  |  *msg_data     (arg0)
#          r1  |  *md5_state    (arg1)
#              |
#        > r1  |  irrelevant
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .global _mmcau_md5_hash
    .global mmcau_md5_hash
    .type   mmcau_md5_hash, %function
    .align  4

_mmcau_md5_hash:
mmcau_md5_hash:

    mov     r2, r1                          @ move arg1 (*md5_state) to arg2
    movs    r1, #1                          @ set arg1 (num_blks) = 1

    b       mmcau_md5_hash_n                @ do mmcau_md5_hash_n


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    .data


    .type   md5_initial_h, %object
    .align  4

md5_initial_h:
    .word   0x67452301	@ initial a
    .word   0xefcdab89  @ initial b
    .word   0x98badcfe  @ initial c
    .word   0x10325476  @ initial d


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
