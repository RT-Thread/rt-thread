/* ${REA_DISCLAIMER_PLACEHOLDER} */

        .syntax unified

        .text
        .thumb

/************************************************************************************//**
 * @brief Optimized fast_memset for ARM Cortex-M33
 *
 * void * fast_memset(void *b, int c, size_t len);
 ***************************************************************************************/
        .thumb_func
        .align  1
        .globl  fast_memset
        .type   fast_memset, %function
fast_memset:
        push    {r4-r6, lr}
        mov     r12, r0              /* preserve return value */

        cbz     r2, .Ldone

/* ------------------------------------------------------------
 * Align destination to 4 bytes (byte stores)
 * ------------------------------------------------------------ */
.Lalign:
        tst     r0, #3
        beq     .Lbuild
        strb    r1, [r0], #1
        subs    r2, r2, #1
        bne     .Lalign
        b       .Ldone

/* ------------------------------------------------------------
 * Build 0xCCCCCCCC fill word
 * ------------------------------------------------------------ */
.Lbuild:
        uxtb    r1, r1
        orr     r3, r1, r1, lsl #8
        orr     r3, r3, r3, lsl #16
        mov     r4, r3
        mov     r5, r3
        mov     r6, r3

/* ============================================================
 * Case 1: n >= 32 bytes
 * 2 × STMIA (16B each)
 * ============================================================ */
.Lcase32:
        cmp     r2, #32
        blo     .Lcase16

.Lloop32:
        stmia   r0!, {r3-r6}          /* 16 bytes */
        stmia   r0!, {r3-r6}          /* 16 bytes */
        subs    r2, r2, #32
        cmp     r2, #32
        bhs     .Lloop32

/* ============================================================
 * Case 2: 16 <= n < 32
 * ============================================================ */
.Lcase16:
        cmp     r2, #16
        blo     .Lcase4
        stmia   r0!, {r3-r6}
        subs    r2, r2, #16

/* ============================================================
 * Case 3: 4 <= n < 16
 * ============================================================ */
.Lcase4:
        cmp     r2, #4
        blo     .Lcase1

.Lword_loop:
        str     r3, [r0], #4
        subs    r2, r2, #4
        cmp     r2, #4
        bhs     .Lword_loop

/* ============================================================
 * Case 4: n < 4
 * ============================================================ */
.Lcase1:
        cbz     r2, .Ldone
.Lbyte_loop:
        strb    r1, [r0], #1
        subs    r2, r2, #1
        bne     .Lbyte_loop

.Ldone:
        mov     r0, r12
        pop     {r4-r6, pc}

        .pool
        .size   fast_memset, . - fast_memset
