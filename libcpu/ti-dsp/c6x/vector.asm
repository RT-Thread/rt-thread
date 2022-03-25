;
; Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
;
; SPDX-License-Identifier: Apache-2.0
;
; Change Logs:
; Date           Author       Notes
; 2021-11-16     Dystopia     the first version
;

;-----------------------------------------------------------
;           interrupt vector table for C6000 DSP
;-----------------------------------------------------------

;-----------------------------------------------------------
;                       extern function
;-----------------------------------------------------------
    .ref _c_int00       ; entry point
    .ref _nmi_handler
    .ref _bad_handler
    .ref _int4_handler
    .ref _int5_handler
    .ref _int6_handler
    .ref _int7_handler
    .ref _int8_handler
    .ref _int9_handler
    .ref _int10_handler
    .ref _int11_handler
    .ref _int12_handler
    .ref _int13_handler
    .ref _int14_handler
    .ref _int15_handler

;-----------------------------------------------------------
;                       macro definition
;-----------------------------------------------------------

;
; create interrupt vector for reset (interrupt 0)
;
VEC_RESET .macro addr
    MVKL  addr,B0
    MVKH  addr,B0
    B     B0
    MVC   PCE1,B0
    NOP   4
    .align 32
    .endm

;
; create interrupt vector for other used interrupts
;
IRQVEC  .macro  __name, __isr
    .align 32
    .hidden __name
    .global __name
__name:
    B   .S2 __isr
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
        .endm
;
;-----------------------------------------------------------
;

;
; vector table
;
    .sect ".vecs"
    .align 32
    .global vector
vector:
    VEC_RESET       _c_int00
    IRQVEC NMI,     _nmi_handler
    IRQVEC AINT,    _bad_handler
    IRQVEC MSGINT,  _bad_handler
    IRQVEC INT4,    _int4_handler
    IRQVEC INT5,    _int5_handler
    IRQVEC INT6,    _int6_handler
    IRQVEC INT7,    _int7_handler
    IRQVEC INT8,    _int8_handler
    IRQVEC INT9,    _int9_handler
    IRQVEC INT10,   _int10_handler
    IRQVEC INT11,   _int11_handler
    IRQVEC INT12,   _int12_handler
    IRQVEC INT13,   _int13_handler
    IRQVEC INT14,   _int14_handler
    IRQVEC INT15,   _int15_handler

    .end
