@-------------------------------------------------------------------------------
@ sys_intvecs.asm
@
@ (c) Texas Instruments 2009-2013, All rights reserved.
@

.section .vectors, "ax"
.code 32

@-------------------------------------------------------------------------------
@ import reference for interrupt routines

    .globl _reset
    .globl _dabort
    .globl turnon_VFP
    .globl IRQ_Handler


.globl system_vectors
system_vectors:
        b   _reset
        b   turnon_VFP
svcEntry:
        b   svcEntry
prefetchEntry:
        b   prefetchEntry
        b   _dabort
reservedEntry:
        b   reservedEntry
        b   IRQ_Handler
        ldr pc,[pc,#-0x1b0]
