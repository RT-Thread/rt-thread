/* ${REA_DISCLAIMER_PLACEHOLDER} */

#define BLOCK_SIZE_LARGE        32
#define BLOCK_SIZE_SMALL        16

        .syntax unified

        .text
        .thumb

/************************************************************************************//**
 * @brief Optimized fast_memcpy for ARM Cortex-M33
 *
 * void * fast_memcpy(void *dst, const void *src, size_t n);
 ***************************************************************************************/
        .thumb_func
        .align  1
        .globl  fast_memcpy
        .type   fast_memcpy, %function
fast_memcpy:
        /* save r0, as the return value must be "dst" */
        mov     r12, r0

        /* check if both src and dst are 32-bit aligned */
        movs    r3, r0
        orrs    r3, r1
        lsls    r3, r3, #30
        bne     .fast_memcpy_bytewise_copy

        /* check buffer size to select larger-block or small-block copying */
        cmp     r2, #BLOCK_SIZE_LARGE
        bcc     .fast_memcpy_small_block

        push    {r4-r10}
        /*
         * Decrement n in advance: we'll check for sign change and then add BLOCK_SIZE_LARGE.
         * Assumes that n is less than 2GiB, i.e. its MSBit on entry is 0.
         */
        subs    r2, #BLOCK_SIZE_LARGE
.fast_memcpy_large_block_copy:
        ldmia   r1!, {r3-r10}
        stmia   r0!, {r3-r10}
        subs    r2, #BLOCK_SIZE_LARGE
        bpl     .fast_memcpy_large_block_copy
        adds    r2, #BLOCK_SIZE_LARGE
        pop     {r4-r10}

.fast_memcpy_small_block:
        /* check buffer size to select small-block or word copying */
        cmp     r2, #BLOCK_SIZE_SMALL
        bcc     .fast_memcpy_word_copy

        push    {r4-r6}
        /*
         * Decrement n in advance: we'll check for sign change and then add BLOCK_SIZE.
         * Assumes that n is less than 2GiB, i.e. its MSBit on entry is 0.
         */
        subs    r2, #BLOCK_SIZE_SMALL
.fast_memcpy_small_block_copy:
        ldmia   r1!, {r3-r6}
        stmia   r0!, {r3-r6}
        subs    r2, #BLOCK_SIZE_SMALL
        bpl     .fast_memcpy_small_block_copy
        adds    r2, #BLOCK_SIZE_SMALL
        pop     {r4-r6}

        /* too little left for block copying, try word copying */
.fast_memcpy_word_copy:
        cmp     r2, #3
        bls     .fast_memcpy_bytewise_copy

        /* decrement n in advance: we'll check for sign change and then add 4 */
        subs    r2, #4
.fast_memcpy_word_copy_loop:
        ldmia   r1!, {r3}
        stmia   r0!, {r3}
        subs    r2, #4
        bpl     .fast_memcpy_word_copy_loop
        adds    r2, #4

.fast_memcpy_bytewise_copy:
        /*
         * Whatever is left can only be copied byte-by-byte
         * (either less than 4 bytes left, or at least one pointer
         * is not 32-bit aligned).
         */
        cmp     r2, #0
        beq     .fast_memcpy_exit
        push    {r4}
        movs    r4, #0
.fast_memcpy_byte_copy:
        ldrb    r3, [r1, r4]
        strb    r3, [r0, r4]
        adds    r4, #1
        cmp     r4, r2
        bne     .fast_memcpy_byte_copy
        pop     {r4}

.fast_memcpy_exit:
        mov     r0, r12
        bx      lr

        .pool
        .size   fast_memcpy, . - fast_memcpy
