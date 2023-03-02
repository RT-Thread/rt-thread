#include "cpuport.h"

	.globl rt_hw_do_after_save_above
	.type rt_hw_do_after_save_above,@function
rt_hw_do_after_save_above:
	addi  sp, sp,  -4
    STORE ra,  0 * REGBYTES(sp)
    csrr  a0, mcause
    csrr  a1, mepc
    mv    a2, sp
    csrrw ra, 0x07ED, ra

	li   t0,    0x08
	csrc mstatus, t0

    LOAD  ra,  0 * REGBYTES(sp)
    addi  sp, sp,  4
    ret
