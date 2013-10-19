;-------------------------------------------------------------------------------
; sys_intvecs.asm
;
; (c) Texas Instruments 2009-2013, All rights reserved.
;

    .sect ".intvecs"
    .arm

;-------------------------------------------------------------------------------
; import reference for interrupt routines

    .ref _reset
    .ref _dabort
    .ref turnon_VFP
    .ref IRQ_Handler

    .def resetEntry

;-------------------------------------------------------------------------------
; interrupt vectors

resetEntry
        b   _reset
        b   turnon_VFP
svcEntry
        b   svcEntry
prefetchEntry
        b   prefetchEntry
        b   _dabort
reservedEntry
        b   reservedEntry
        b   IRQ_Handler
        ldr pc,[pc,#-0x1b0]

;-------------------------------------------------------------------------------
