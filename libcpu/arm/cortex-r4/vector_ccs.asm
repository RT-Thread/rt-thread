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
    .ref turnon_VFP
    .ref vector_svc
    .ref vector_pabort
    .ref vector_dabort
    .ref vector_resv
    .ref IRQ_Handler

;-------------------------------------------------------------------------------
; interrupt vectors
    .def resetEntry
resetEntry
        b   _reset
        b   turnon_VFP
        b   vector_svc
        b   vector_pabort
        b   vector_dabort
        b   vector_resv
        b   IRQ_Handler
        ldr pc,[pc,#-0x1b0]

;-------------------------------------------------------------------------------
