#ifndef _SBI_ASM_H
#define _SBI_ASM_H

.macro SBI_CALL which
    li a7, \which
    ecall
    nop
.endm

#endif /* _SBI_ASM_H */
