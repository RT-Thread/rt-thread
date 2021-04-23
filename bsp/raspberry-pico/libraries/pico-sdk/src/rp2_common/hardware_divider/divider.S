#include "pico/asm_helper.S"
#include "hardware/regs/addressmap.h"
#include "hardware/regs/sio.h"

.syntax unified
.cpu cortex-m0plus
.thumb

// tag::hw_div_s32[]

.macro __divider_delay
    // delay 8 cycles
    b 1f
1:  b 1f
1:  b 1f
1:  b 1f
1:
.endm

.align 2

regular_func_with_section hw_divider_divmod_s32
    ldr r3, =(SIO_BASE)
    str r0, [r3, #SIO_DIV_SDIVIDEND_OFFSET]
    str r1, [r3, #SIO_DIV_SDIVISOR_OFFSET]
    __divider_delay
    // return 64 bit value so we can efficiently return both (note quotient must be read last)
    ldr r1, [r3, #SIO_DIV_REMAINDER_OFFSET]
    ldr r0, [r3, #SIO_DIV_QUOTIENT_OFFSET]
    bx lr
// end::hw_div_s32[]

.align 2

// tag::hw_div_u32[]
regular_func_with_section hw_divider_divmod_u32
    ldr r3, =(SIO_BASE)
    str r0, [r3, #SIO_DIV_UDIVIDEND_OFFSET]
    str r1, [r3, #SIO_DIV_UDIVISOR_OFFSET]
    __divider_delay
    // return 64 bit value so we can efficiently return both (note quotient must be read last)
    ldr r1, [r3, #SIO_DIV_REMAINDER_OFFSET]
    ldr r0, [r3, #SIO_DIV_QUOTIENT_OFFSET]
    bx lr
// end::hw_div_u32[]

#if SIO_DIV_CSR_READY_LSB == 0
.equ SIO_DIV_CSR_READY_SHIFT_FOR_CARRY, 1
#else
#error need to change SHIFT above
#endif

regular_func_with_section hw_divider_save_state
    push {r4, r5, lr}
    ldr r5, =SIO_BASE
    ldr r4, [r5, #SIO_DIV_CSR_OFFSET]
    # wait for results as we can't save signed-ness of operation
1:
    lsrs r4, #SIO_DIV_CSR_READY_SHIFT_FOR_CARRY
    bcc 1b
    ldr r1, [r5, #SIO_DIV_UDIVIDEND_OFFSET]
    ldr r2, [r5, #SIO_DIV_UDIVISOR_OFFSET]
    ldr r3, [r5, #SIO_DIV_REMAINDER_OFFSET]
    ldr r4, [r5, #SIO_DIV_QUOTIENT_OFFSET]
    stmia r0!, {r1-r4}
    pop {r4, r5, pc}

regular_func_with_section hw_divider_restore_state
    push {r4, r5, lr}
    ldr r5, =SIO_BASE
    ldmia r0!, {r1-r4}
    str r1, [r5, #SIO_DIV_UDIVIDEND_OFFSET]
    str r2, [r5, #SIO_DIV_UDIVISOR_OFFSET]
    str r3, [r5, #SIO_DIV_REMAINDER_OFFSET]
    str r4, [r5, #SIO_DIV_QUOTIENT_OFFSET]
    pop {r4, r5, pc}
