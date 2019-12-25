/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef NRFX_ATOMIC_INTERNAL_H__
#define NRFX_ATOMIC_INTERNAL_H__

#include <nrfx.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Only Cortex-M cores > 3 support LDREX/STREX instructions. */
#if ((__CORTEX_M >= 0x03U) || (__CORTEX_SC >= 300U)) == 0
#error "Unsupported core version"
#endif

#if defined ( __CC_ARM )
static __asm uint32_t nrfx_atomic_internal_mov(nrfx_atomic_u32_t * p_ptr,
                                               uint32_t value,
                                               uint32_t * p_new)
{
    /* The base standard specifies that arguments are passed in core registers r0-r3 and on the stack.
     * Registers r4 and r5 must be saved on the stack. Note that only even number of register pushes are
     * allowed. This is a requirement of the Procedure Call Standard for the ARM Architecture [AAPCS].
     */
    push  {r4, r5}
    mov   r4, r0

loop_mov
    ldrex r0, [r4]
    mov   r5, r1
    strex r3, r5, [r4]
    cmp   r3, #0
    bne   loop_mov

    str   r5, [r2]
    pop   {r4, r5}
    bx    lr
}


static __asm uint32_t nrfx_atomic_internal_orr(nrfx_atomic_u32_t * p_ptr,
                                              uint32_t value,
                                              uint32_t * p_new)
{
    push  {r4, r5}
    mov   r4, r0

loop_orr
    ldrex r0, [r4]
    orr   r5, r0, r1
    strex r3, r5, [r4]
    cmp   r3, #0
    bne   loop_orr

    str   r5, [r2]
    pop   {r4, r5}
    bx    lr
}

static __asm uint32_t nrfx_atomic_internal_and(nrfx_atomic_u32_t * p_ptr,
                                              uint32_t value,
                                              uint32_t * p_new)
{
    push  {r4, r5}
    mov   r4, r0

loop_and
    ldrex r0, [r4]
    and   r5, r0, r1
    strex r3, r5, [r4]
    cmp   r3, #0
    bne   loop_and

    str   r5, [r2]
    pop   {r4, r5}
    bx    lr
}

static __asm uint32_t nrfx_atomic_internal_eor(nrfx_atomic_u32_t * p_ptr,
                                              uint32_t value,
                                              uint32_t * p_new)
{
    push  {r4, r5}
    mov   r4, r0

loop_eor
    ldrex r0, [r4]
    eor   r5, r0, r1
    strex r3, r5, [r4]
    cmp   r3, #0
    bne   loop_eor

    str   r5, [r2]
    pop   {r4, r5}
    bx    lr
}

static __asm uint32_t nrfx_atomic_internal_add(nrfx_atomic_u32_t * p_ptr,
                                              uint32_t value,
                                              uint32_t * p_new)
{
    push  {r4, r5}
    mov   r4, r0

loop_add
    ldrex r0, [r4]
    add   r5, r0, r1
    strex r3, r5, [r4]
    cmp   r3, #0
    bne   loop_add

    str   r5, [r2]
    pop   {r4, r5}
    bx    lr
}

static __asm uint32_t nrfx_atomic_internal_sub(nrfx_atomic_u32_t * p_ptr,
                                              uint32_t value,
                                              uint32_t * p_new)
{
    push  {r4, r5}
    mov   r4, r0

loop_sub
    ldrex r0, [r4]
    sub   r5, r0, r1
    strex r3, r5, [r4]
    cmp   r3, #0
    bne   loop_sub

    str   r5, [r2]
    pop   {r4, r5}
    bx    lr
}

static __asm bool nrfx_atomic_internal_cmp_exch(nrfx_atomic_u32_t * p_data,
                                               uint32_t *         p_expected,
                                               uint32_t           value)
{
#define RET_REG  r0
#define P_EXPC   r1
#define VALUE    r2
#define STR_RES  r3
#define P_DATA   r4
#define EXPC_VAL r5
#define ACT_VAL  r6

    push {r4-r6}
    mov  P_DATA, r0
    mov  RET_REG, #0

loop_cmp_exch
    ldrex   ACT_VAL, [P_DATA]
    ldr     EXPC_VAL, [P_EXPC]
    cmp     ACT_VAL, EXPC_VAL
    ittee   eq
    strexeq STR_RES, VALUE, [P_DATA]
    moveq   RET_REG, #1
    strexne STR_RES, ACT_VAL, [P_DATA]
    strne   ACT_VAL, [P_EXPC]
    cmp     STR_RES, #0
    itt     ne
    movne   RET_REG, #0
    bne     loop_cmp_exch

    pop {r4-r6}
    bx    lr

#undef RET_REG
#undef P_EXPC
#undef VALUE
#undef STR_RES
#undef P_DATA
#undef EXPC_VAL
#undef ACT_VAL
}

static __asm uint32_t nrfx_atomic_internal_sub_hs(nrfx_atomic_u32_t * p_ptr,
                                                 uint32_t value,
                                                 uint32_t * p_new)
{
    push  {r4, r5}
    mov   r4, r0

loop_sub_ge
    ldrex r0, [r4]
    cmp   r0, r1
    ite   hs
    subhs r5, r0, r1
    movlo r5, r0
    strex r3, r5, [r4]
    cmp   r3, #0
    bne   loop_sub_ge

    str   r5, [r2]
    pop   {r4, r5}
    bx    lr
}


#define NRFX_ATOMIC_OP(asm_op, old_val, new_val, ptr, value)          \
        old_val = nrfx_atomic_internal_##asm_op(ptr, value, &new_val)

#elif defined ( __ICCARM__ ) || defined ( __GNUC__ )

/**
 * @brief Atomic operation generic macro.
 *
 * @param[in]  asm_op   Operation: mov, orr, and, eor, add, sub.
 * @param[out] old_val  Atomic object output (uint32_t), value before operation.
 * @param[out] new_val  Atomic object output (uint32_t), value after operation.
 * @param[in]  value    Atomic operation operand.
 */
#define NRFX_ATOMIC_OP(asm_op, old_val, new_val, ptr, value)    \
{                                                               \
    uint32_t tmp_reg;                                           \
            __ASM volatile(                                     \
    "1:     ldrex   %["#old_val"], [%["#ptr"]]\n"               \
    NRFX_ATOMIC_OP_##asm_op(new_val, old_val, value)            \
    "       strex   %[tmp_reg], %["#new_val"], [%["#ptr"]]\n"   \
    "       teq     %[tmp_reg], #0\n"                           \
    "       bne.n     1b"                                       \
            :                                                   \
        [old_val] "=&r" (old_val),                              \
        [new_val] "=&r" (new_val),                              \
        [tmp_reg] "=&r" (tmp_reg)                               \
            :                                                   \
        [ptr]   "r" (ptr),                                      \
        [value] "r" (value)                                     \
            : "cc");                                            \
    (void)tmp_reg;                                              \
}

#define NRFX_ATOMIC_OP_mov(new_val, old_val, value) "mov %["#new_val"], %["#value"]\n"
#define NRFX_ATOMIC_OP_orr(new_val, old_val, value) "orr %["#new_val"], %["#old_val"], %["#value"]\n"
#define NRFX_ATOMIC_OP_and(new_val, old_val, value) "and %["#new_val"], %["#old_val"], %["#value"]\n"
#define NRFX_ATOMIC_OP_eor(new_val, old_val, value) "eor %["#new_val"], %["#old_val"], %["#value"]\n"
#define NRFX_ATOMIC_OP_add(new_val, old_val, value) "add %["#new_val"], %["#old_val"], %["#value"]\n"
#define NRFX_ATOMIC_OP_sub(new_val, old_val, value) "sub %["#new_val"], %["#old_val"], %["#value"]\n"
#define NRFX_ATOMIC_OP_sub_hs(new_val, old_val, value)    \
    "cmp %["#old_val"], %["#value"]\n "                   \
    "ite hs\n"                                            \
    "subhs %["#new_val"], %["#old_val"], %["#value"]\n"   \
    "movlo %["#new_val"], %["#old_val"]\n"

static inline bool nrfx_atomic_internal_cmp_exch(nrfx_atomic_u32_t * p_data,
                                                uint32_t *         p_expected,
                                                uint32_t           value)
{
    bool res = false;
    /* Temporary register used in the inline asm code for getting the result
     * of the strex* operations (no need to initialize it).
     */
    uint32_t tmp_reg;
    uint32_t act_val = 0;
    uint32_t exp_val = 0;
    __ASM volatile(
    "1:     ldrex   %[act_val], [%[ptr]]\n"
    "       ldr     %[exp_val], [%[expc]]\n"
    "       cmp     %[act_val], %[exp_val]\n"
    "       ittee   eq\n"
    "       strexeq %[tmp_reg], %[value], [%[ptr]]\n"
    "       moveq   %[res], #1\n"
    "       strexne %[tmp_reg], %[act_val], [%[ptr]]\n"
    "       strne   %[act_val], [%[expc]]\n"
    "       cmp     %[tmp_reg], #0\n"
    "       itt     ne\n"
    "       movne   %[res], #0\n"
    "       bne.n   1b"
            :
        [res]     "=&r" (res),
        [exp_val] "=&r" (exp_val),
        [act_val] "=&r" (act_val),
        [tmp_reg] "=&r" (tmp_reg)
            :
                "0" (res),
                "1" (exp_val),
                "2" (act_val),
        [expc]  "r" (p_expected),
        [ptr]   "r" (p_data),
        [value] "r" (value)
            : "cc");
    (void)tmp_reg;
    return res;
}

#else
#error "Unsupported compiler"
#endif

#ifdef __cplusplus
}
#endif

#endif // NRFX_ATOMIC_INTERNAL_H__
