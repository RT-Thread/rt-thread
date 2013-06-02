;-------------------------------------------------------------------------------
; sys_pmu.asm
;
; (c) Texas Instruments 2009-2013, All rights reserved.
;

    .text
    .arm


;-------------------------------------------------------------------------------
; Initialize Pmu
; Note: It will reset all counters

    .def     _pmuInit_
    .asmfunc

_pmuInit_

        stmfd sp!, {r0}
        ; set control register
        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #(1 << 4) + 6 + 1
        mcr   p15, #0, r0, c9, c12, #0
        ; clear flags
		mov   r0,  #0
		sub   r1,  r1,  #1
		mcr   p15, #0, r0, c9, c12, #3 
        ; select counter 0 event
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mov   r0,  #0x11
        mcr   p15, #0, r0, c9, c13, #1 ; select event
        ; select counter 1 event
		mov   r0,  #1
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mov   r0,  #0x11
        mcr   p15, #0, r0, c9, c13, #1 ; select event
        ; select counter 2 event
		mov   r0,  #2
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mov   r0,  #0x11
        mcr   p15, #0, r0, c9, c13, #1 ; select event
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable Counters Global [Cycle, Event [0..2]]
; Note: It will reset all counters

    .def     _pmuEnableCountersGlobal_
    .asmfunc

_pmuEnableCountersGlobal_

        stmfd sp!, {r0}
        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #7
        mcr   p15, #0, r0, c9, c12, #0
        ldmfd sp!, {r0}		
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Disable Counters Global [Cycle, Event [0..2]]

    .def     _pmuDisableCountersGlobal_
    .asmfunc

_pmuDisableCountersGlobal_

        stmfd sp!, {r0}
        mrc   p15, #0, r0, c9, c12, #0 
        bic   r0,  r0, #1
        mcr   p15, #0, r0, c9, c12, #0
        ldmfd sp!, {r0}		
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Reset Cycle Counter

    .def     _pmuResetCycleCounter_
    .asmfunc

_pmuResetCycleCounter_

        stmfd sp!, {r0}
        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #4
        mcr   p15, #0, r0, c9, c12, #0
        ldmfd sp!, {r0}		
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Reset Event Counters [0..2]

    .def     _pmuResetEventCounters_
    .asmfunc

_pmuResetEventCounters_

        stmfd sp!, {r0}
        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #2
        mcr   p15, #0, r0, c9, c12, #0
        ldmfd sp!, {r0}		
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Reset Cycle Counter abd Event Counters [0..2]

    .def     _pmuResetCounters_
    .asmfunc

_pmuResetCounters_

        stmfd sp!, {r0}
        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #6
        mcr   p15, #0, r0, c9, c12, #0
        ldmfd sp!, {r0}		
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Start Counters [Cycle, 0..2]

    .def     _pmuStartCounters_
    .asmfunc

_pmuStartCounters_

        mcr   p15, #0, r0, c9, c12, #1
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Stop Counters [Cycle, 0..2]

    .def     _pmuStopCounters_
    .asmfunc

_pmuStopCounters_

        mcr   p15, #0, r0, c9, c12, #2
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Set Count event

    .def     _pmuSetCountEvent_
    .asmfunc

_pmuSetCountEvent_
 
        lsr   r0,  r0, #1
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mcr   p15, #0, r1, c9, c13, #1 ; select event
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Get Cycle Count

    .def     _pmuGetCycleCount_
    .asmfunc

_pmuGetCycleCount_

        mrc   p15, #0, r0, c9, c13, #0
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Get Event Counter Count Value

    .def     _pmuGetEventCount_
    .asmfunc

_pmuGetEventCount_

        lsr   r0,  r0, #1
        mcr   p15, #0, r0, c9, c12, #5 ; select counter
        mrc   p15, #0, r0, c9, c13, #2 ; read event counter
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Get Overflow Flags

    .def     _pmuGetOverflow_
    .asmfunc

_pmuGetOverflow_

        mrc   p15, #0, r0, c9, c12, #3 ; read overflow
		mov   r1,  #0
		sub   r1,  r1,  #1
		mcr   p15, #0, r1, c9, c12, #3 ; clear flags
        bx    lr

    .endasmfunc

    

;-------------------------------------------------------------------------------

