#include "cpuport.h"

.globl rt_hw_do_after_save_above
.type rt_hw_do_after_save_above,@function
rt_hw_do_after_save_above:
addi  sp, sp,  -4
    STORE ra,  0 * REGBYTES(sp)
        
    csrr  a0, mscratch
    call  do_irq
        
    LOAD  ra,  0 * REGBYTES(sp)
    addi  sp, sp,  4
    ret
    