#include "cpuport.h"

	.globl rt_hw_do_after_save_above
	.type rt_hw_do_after_save_above,@function
rt_hw_do_after_save_above:
    addi  sp, sp,  -4
    STORE ra,  0 * REGBYTES(sp)

	csrr    t1, mcause
    andi    t1, t1, 0x3FF
    /* get ISR */
    la      t2, interrupt_entry
    jalr    t2
    
    LOAD  ra,  0 * REGBYTES(sp)
    addi  sp, sp,  4
    ret