;-----------------------------------------------------------------------
;
; This file contains the M16C C startup routine and must usually
; be tailored to suit customer's hardware.
;
; Copyright 2002 IAR Systems. All rights reserved.
;
; $Revision: 1.16 $
;
;-----------------------------------------------------------------------

        MODULE  ?cstart

        PUBLIC  __program_start
        PUBLIC  __data16_init
        PUBLIC  __data16_zero
        PUBLIC  ?cstart_call_ctors

        EXTERN  main
        EXTERN  exit
        EXTERN  __call_ctors
        EXTERN  __low_level_init
        EXTERN  ?GENERIC_MOVE_LONG_L08
        EXTERN  RelocatableVectTbl

        ;------------------------------------------------------
        ; Useful macros
        ;------------------------------------------------------

        ; Load 24-bit constant value to (high,low)
LD24    MACRO   value,high,low
        MOV.B   #BYTE3(value),high
        MOV.W   #LWRD(value),low
        ENDM

        ; Load 32-bit constant value to (high,low)
LD32    MACRO   value,high,low
        MOV.W   #HWRD(value),high
        MOV.W   #LWRD(value),low
        ENDM

        ; Load a stack-pointer with last even address of segment
LDSTACK MACRO   segment,reg
        LDC     #sfe(segment), reg
        ENDM


        ;------------------------------------------------------
        ; __program_start - Reset vector should point to here.
        ;
        ; Calls __low_level_init to perform initialization
        ; before initializing segments and calling main.
        ; If the function returns 0 no segment initialization
        ; should take place.
        ;
        ; Link with your own version of __low_level_init to
        ; override the default action: do nothing but return 1.
        ;------------------------------------------------------

        RSEG    CSTACK
        RSEG    ISTACK
        RSEG    CSTART:CODE:NOROOT
	REQUIRE	call_main

__program_start:
        LDC     #sfe(ISTACK),   ISP                             ; Set up interrupt stack
        FCLR    U                                               ; Select interrupt stack
        LDC     #sfe(CSTACK),   SP                              ; Set up C         stack
        LDINTB  #RelocatableVectTbl                             ; Set up INTB register
        JSR.A   __low_level_init                                ; Call __low_level_init

        ;-----------------------------------------------------------
        ; Run-time test whether we should do segment initialization
        ;-----------------------------------------------------------
        TST.B   R0L,            R0L
        JNE     do_segment_init
        JMP     skip_segment_init

do_segment_init:

        ;------------------------------------------------------
        ; Perform segment initialization of DATA16 memory.
        ;------------------------------------------------------

        RSEG    DATA16_Z
        RSEG    CSTART:CODE:NOROOT

__data16_zero:
        MOV.W   #sizeof(DATA16_Z), R3
        MOV.W   #sfb(DATA16_Z),    A1
        MOV.B   #0, R0L
        SSTR.B

        RSEG    DATA16_I
        RSEG    DATA16_ID
        RSEG    CSTART:CODE:NOROOT

__data16_init:
        MOV.W   #sizeof(DATA16_ID), R3
        MOV.W   #sfb(DATA16_I),     A1
        LD24    sfb(DATA16_ID),     R1H, A0
        SMOVF.B



        RSEG    CSTART:CODE:NOROOT
skip_segment_init:
        ; Fall through to next required CSTART segment part


        ;------------------------------------------------------
        ; Call constructors
        ;------------------------------------------------------

        RSEG    DIFUNCT
        RSEG    CSTART:CODE:NOROOT

        PUBLIC  ?cstart_call_ctors
        EXTERN  __call_ctors

?cstart_call_ctors:
        PUSH.W  #HWRD(sfe(DIFUNCT))
        PUSH.W  #LWRD(sfe(DIFUNCT))
        LD32    sfb(DIFUNCT),R2,R0
        JSR.A   __call_ctors


        ; Fall through to next required CSTART segment part


        ;------------------------------------------------------
        ; Call main and exit
        ;------------------------------------------------------

        ; This segment part is marked as ROOT, since it must
        ; be preserved by the linker.
        ;
        RSEG    CSTART:CODE:NOROOT

call_main:
        MOV.W   #0, R0  ; Call main with argc = 0
        JSR.A   main
        JMP.A   exit    ; Argument to exit is return value of main

        ;------------------------------------------------------
        ; Fixed interrupt table.
        ;
        ; We install all fixed interrupts in a segment called
        ; INTVEC1. All fixed interrupts have a hard coded name.
        ; Write an interrupt handler in C using this name, with
        ; no vector specification, and it will replace the
        ; default handler.
        ;------------------------------------------------------

        EXTERN  __undefined_instruction_handler
        EXTERN  __overflow_handler
        EXTERN  __break_instruction_handler
        EXTERN  __address_match_handler
        EXTERN  __single_step_handler
        EXTERN  __watchdog_timer_handler
        EXTERN  __DBC_handler
        EXTERN  __NMI_handler

        ; Labels for the ID Code Check Function.
        ; (To be initialized in the linker file)
        EXTERN  _ID_CODE_1
        EXTERN  _ID_CODE_2
        EXTERN  _ID_CODE_3
        EXTERN  _ID_CODE_4
        EXTERN  _ID_CODE_5
        EXTERN  _ID_CODE_6
        EXTERN  _ID_CODE_7
        EXTERN  _OFS_VALUE

	PUBLIC ??intvec_start

        COMMON INTVEC1:NOROOT
??intvec_start:
        DC24    __undefined_instruction_handler
        DC8     _ID_CODE_1
        DC24    __overflow_handler
        DC8     _ID_CODE_2
        DC24    __break_instruction_handler
        DC8     0
        DC24    __address_match_handler
        DC8     _ID_CODE_3
        DC24    __single_step_handler
        DC8     _ID_CODE_4
        DC24    __watchdog_timer_handler
        DC8     _ID_CODE_5
        DC24    __DBC_handler
        DC8     _ID_CODE_6
        DC24    __NMI_handler
        DC8     _ID_CODE_7
        DC24    __program_start              ; Reset vector
        DC8     _OFS_VALUE                                 

        ENDMOD


        ;------------------------------------------------------
        ; Default handlers for fixed interrupts
        ;------------------------------------------------------

        MODULE  __undefined_instruction
        EXTERN  ??reit
        REQUIRE ??reit
        PUBLIC  __undefined_instruction_handler
        RSEG    CSTART:CODE:NOROOT(1)
__undefined_instruction_handler:
        ; Fall through to ??reit
        ENDMOD

        MODULE  __overflow
        EXTERN  ??reit
        REQUIRE ??reit
        PUBLIC  __overflow_handler
        RSEG    CSTART:CODE:NOROOT(1)
__overflow_handler:
        ; Fall through to ??reit
        ENDMOD

        MODULE  __break_instruction
        EXTERN  ??reit
        REQUIRE ??reit
        PUBLIC  __break_instruction_handler
        RSEG    CSTART:CODE:NOROOT(1)
__break_instruction_handler:
        ; Fall through to ??reit
        ENDMOD

        MODULE  __address_match
        EXTERN  ??reit
        REQUIRE ??reit
        PUBLIC  __address_match_handler
        RSEG    CSTART:CODE:NOROOT(1)
__address_match_handler:
        ; Fall through to ??reit
        ENDMOD

        MODULE  __single_step
        EXTERN  ??reit
        REQUIRE ??reit
        PUBLIC  __single_step_handler
        RSEG    CSTART:CODE:NOROOT(1)
__single_step_handler:
        ; Fall through to ??reit
        ENDMOD

        MODULE  __watchdog_timer
        EXTERN  ??reit
        REQUIRE ??reit
        PUBLIC  __watchdog_timer_handler
        RSEG    CSTART:CODE:NOROOT(1)
__watchdog_timer_handler:
        ; Fall through to ??reit
        ENDMOD

        MODULE  __DBC
        EXTERN  ??reit
        REQUIRE ??reit
        PUBLIC  __DBC_handler
        RSEG    CSTART:CODE:NOROOT(1)
__DBC_handler:
        ; Fall through to ??reit
        ENDMOD

        MODULE  __NMI
        EXTERN  ??reit
        REQUIRE ??reit
        PUBLIC  __NMI_handler
        RSEG    CSTART:CODE:NOROOT(1)
__NMI_handler:
        ; Fall through to ??reit
        ENDMOD

        ;------------------------------------------------------
        ; Return from interrupt
        ;------------------------------------------------------
        MODULE    __reit
        PUBLIC  ??reit
        RSEG    CSTART:CODE:NOROOT(1)
	EXTERN ??intvec_start
	REQUIRE ??intvec_start
??reit:
        REIT

        ENDMOD


        ;------------------------------------------------------
        ; FUNCTION: __low_level_init
        ;
        ; You can replace this routine by linking with your
        ; own version.
        ;
        ; The default action is to do nothing and return 1.
        ;------------------------------------------------------

        MODULE  __low_level_init
        PUBLIC  __low_level_init
        RSEG    CSTART:CODE:NOROOT

__low_level_init:
        MOV.B   #1,R0L
        RTS

        ENDMOD


        ;------------------------------------------------------
        ;  __overflow - This variable is used by the intrinsic
        ;               functions __RMPA_W_overflow and
        ;               __RMPA_B_overflow.
        ;------------------------------------------------------

        MODULE  __overflow
        PUBLIC  __overflow
        EXTERN  __data13_zero

        RSEG    DATA13_Z:NEAR:NOROOT

__overflow:
        DC8     0
        REQUIRE __data13_zero

        END
