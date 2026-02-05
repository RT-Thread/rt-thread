#include "cpuport.h"
#include "riscv_encoding.h"

.macro SAVE_CSR_CONTEXT
    addi  sp, sp,  -16
    csrrwi  x0, CSR_PUSHMCAUSE, 1
    csrrwi  x0, CSR_PUSHMEPC, 2
    csrrwi  x0, CSR_PUSHMSUBM, 3
.endm

.macro RESTORE_CSR_CONTEXT
    LOAD x5,  3*REGBYTES(sp)
    csrw CSR_MSUBM, x5
    LOAD x5,  2*REGBYTES(sp)
    csrw CSR_MEPC, x5
    LOAD x5,  1*REGBYTES(sp)
    csrw CSR_MCAUSE, x5
    addi  sp, sp,  16
.endm

.macro DISABLE_MIE
    csrc CSR_MSTATUS, MSTATUS_MIE
.endm

	.globl rt_hw_do_after_save_above
	.type rt_hw_do_after_save_above,@function
rt_hw_do_after_save_above:
	addi  sp, sp,  -4
    STORE ra,  0 * REGBYTES(sp)
    csrr  a0, mcause
    csrr  a1, mepc
    mv    a2, sp

    SAVE_CSR_CONTEXT

    csrrw ra, CSR_JALMNXTI, ra


    DISABLE_MIE
    RESTORE_CSR_CONTEXT

	li   t0,    0x08
	csrc mstatus, t0

    LOAD  ra,  0 * REGBYTES(sp)
    addi  sp, sp,  4
    ret