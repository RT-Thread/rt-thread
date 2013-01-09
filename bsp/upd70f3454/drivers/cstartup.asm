;-----------------------------------------------------------------------------
;       This file contains the startup code used by the V850 C/C++ compiler.
;
;       Copyright (c) 1998-2009 IAR Systems AB.
;
;       $Revision: 5028 $
;
;-----------------------------------------------------------------------------

;
; Naming covention of labels in this file:
;
;  ?xxx   - External labels only accessed from assembler.
;  __xxx  - External labels accessed from or defined in C.
;  xxx    - Labels local to one module (note: this file contains
;           several modules).
;  main   - The starting point of the user program.
;

#include "lxx.h"
#include "cfi.h"

            CASEON

#define A0  R1
#define A1  R5
#define A2  R6

;---------------------------------------------------------------;
; Call Frame Informatio                                         ;
;---------------------------------------------------------------;

            CFNAMES
            CFCOMMON

;---------------------------------------------------------------;
; Reset Vector                                                  ;
;---------------------------------------------------------------;

            MODULE      ?RESET

            PUBLIC      ?creset
            EXTERN      __program_start

            COMMON      INTVEC:CODE:ROOT(2)

?creset:
            MOV         __program_start, R1
            JMP         [R1]

            ENDMOD

;---------------------------------------------------------------;
; Module start.                                                 ;
;---------------------------------------------------------------;

            MODULE      __program_start

            PUBLIC      __program_start
            PUBLIC      ?cstartup
            EXTERN      ?creset
            REQUIRE     ?creset

;---------------------------------------------------------------;
; Forward declarations of segments used in this module.         ;
;---------------------------------------------------------------;

            RSEG        CODE:CODE:NOROOT(2)
            RSEG        CSTACK:DATA(2)

;---------------------------------------------------------------;
; The startup code.                                             ;
;---------------------------------------------------------------;

            RSEG        CSTART:CODE:NOROOT(1)

            ;;
            ;; The startup sequence contained in the final linked
            ;; application will consist of a mosaic containing
            ;; modules and segment parts defined in this file.
            ;;
            ;; The only part which is required is the call to
            ;; the function "main".
            ;;

            EXTERN      ?cstart_call_main
            REQUIRE     ?cstart_call_main

            EXTERN      __cstart_low_level_init
            REQUIRE     __cstart_low_level_init

            PUBLIC      ?BTT_cstart_begin
?BTT_cstart_begin:

?cstartup:
__program_start:

;---------------------------------------------------------------;
; Set up the stack and the global pointer.                      ;
;---------------------------------------------------------------;

#if __CORE__ == __CORE_V850__
            ;; If an interrupt is issued beteween the MOVEA and
            ;; MOVHI instructions the SP will point into
            ;; nowhere.  To fix this problem we build the new SP
            ;; value in R1 and moves it with an atomic operation
            ;; to SP.
            MOVE_M      SFE CSTACK, R1
            MOV         R1, SP
#else
            MOVE_M      SFE CSTACK, SP
#endif

            EXTERN      ?BREL_BASE
            MOVE_M      ?BREL_BASE + 0x8000, GP

            EXTERN      ?BREL_CBASE
            MOVE_M      ?BREL_CBASE + 0x8000, R25

;---------------------------------------------------------------;
; Setup constant registers.                                     ;
;---------------------------------------------------------------;

            RSEG        CSTART:CODE:NOROOT(1)
            PUBLIC      ?INIT_REG

?INIT_REG:  MOV         255, R18
            ORI         65535, zero, R19

            ENDMOD


;---------------------------------------------------------------;
; Initialize the saddr base pointers.                           ;
;---------------------------------------------------------------;

            MODULE      ?INIT_SADDR_BASE

            RTMODEL     "__reg_ep", "saddr"

            RSEG        CSTART:CODE:NOROOT(1)
            PUBLIC      ?INIT_SADDR_BASE

?INIT_SADDR_BASE:
            EXTERN      ?SADDR_BASE
            MOVE_M      ?SADDR_BASE, EP

            ENDMOD


;---------------------------------------------------------------;
; If hardware must be initialized from C or if watch dog timer  ;
; must be handled or if the segment init should not be          ;
; performed it can now be done in `__low_level_init'.           ;
;---------------------------------------------------------------;
; Call the user function __low_level_init, if defined.          ;
; It is the responsibility of __low_level_init to require       ;
; __cstart_low_level_init in order to be called by cstartup.    ;
;---------------------------------------------------------------;

            MODULE      ?CSTART_LOW_LEVEL_INIT
            RSEG        CSTART:CODE:NOROOT(1)

            PUBLIC      __cstart_low_level_init
            EXTERN      __low_level_init
            REQUIRE     __low_level_init
            EXTERN      ?no_seg_init

__cstart_low_level_init:
            CALL_FUNC   __low_level_init, LP, R1
            ANDI        0xFF, R1, R1
            BZ          ?no_seg_init

            ENDMOD


;---------------------------------------------------------------;
; Segment initialization code. Copy initialized ROMmed code to  ;
; RAM and ?seg_clear uninitialized variables.                   ;
;---------------------------------------------------------------;

            MODULE      ?INIT_MEMORY

;---------------------------------------------------------------;
; Zero out NEAR_Z                                               ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_NEAR_Z

            RSEG        NEAR_Z(2)
            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_clear
?INIT_NEAR_Z:

            MOVE_M      SFB NEAR_Z, A0
            MOVE_M      SFE NEAR_Z, A1
            JARL        ?seg_clear, LP


;---------------------------------------------------------------;
; Zero out BREL_Z                                               ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_BREL_Z

            RSEG        BREL_Z(2)
            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_clear
?INIT_BREL_Z:

            MOVE_M      SFB BREL_Z, A0
            MOVE_M      SFE BREL_Z, A1
            JARL        ?seg_clear, LP

;---------------------------------------------------------------;
; Zero out SADDR7_Z                                             ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_SADDR7_Z

            RSEG        SADDR7_Z(2)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_clear
?INIT_SADDR7_Z:

            MOVE_M      SFB SADDR7_Z, A0
            MOVE_M      SFE SADDR7_Z, A1
            JARL        ?seg_clear, LP


;---------------------------------------------------------------;
; Zero out SADDR8_Z                                             ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_SADDR8_Z

            RSEG        SADDR8_Z(2)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_clear
?INIT_SADDR8_Z:

            MOVE_M      SFB SADDR8_Z, A0
            MOVE_M      SFE SADDR8_Z, A1
            JARL        ?seg_clear, LP


;---------------------------------------------------------------;
; Zero out BREL23_Z                                             ;
;---------------------------------------------------------------;

#if __CORE__ >= __CORE_V850E2M__

            PUBLIC      ?INIT_BREL23_Z

            RSEG        BREL23_Z(2)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_clear
?INIT_BREL23_Z:

            MOVE_M      SFB BREL23_Z, A0
            MOVE_M      SFE BREL23_Z, A1
            JARL        ?seg_clear, LP
#endif

;---------------------------------------------------------------;
; Zero out HUGE_Z                                               ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_HUGE_Z

            RSEG        HUGE_Z(2)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_clear
?INIT_HUGE_Z:

            MOVE_M      SFB HUGE_Z, A0
            MOVE_M      SFE HUGE_Z, A1
            JARL        ?seg_clear, LP

;---------------------------------------------------------------;
; Copy NEAR_ID into NEAR_I                                      ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_NEAR_I

            RSEG        NEAR_I(2)
            RSEG        NEAR_ID(2)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_copy
?INIT_NEAR_I:

            MOVE_M      SFB NEAR_ID, A0
            MOVE_M      SFE NEAR_ID, A1
            MOVE_M      SFB NEAR_I, A2
            JARL        ?seg_copy, LP

;---------------------------------------------------------------;
; Copy BREL_ID into BREL_I                                      ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_BREL_I

            RSEG        BREL_I(2)
            RSEG        BREL_ID(2)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_copy
?INIT_BREL_I:

            MOVE_M      SFB BREL_ID, A0
            MOVE_M      SFE BREL_ID, A1
            MOVE_M      SFB BREL_I, A2
            JARL        ?seg_copy, LP

;---------------------------------------------------------------;
; Copy SADDR7_ID into SADDR7_I                                  ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_SADDR7_I

            RSEG        SADDR7_I(2)
            RSEG        SADDR7_ID(2)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_copy
?INIT_SADDR7_I:

            MOVE_M      SFB SADDR7_ID, A0
            MOVE_M      SFE SADDR7_ID, A1
            MOVE_M      SFB SADDR7_I, A2
            JARL        ?seg_copy, LP

;---------------------------------------------------------------;
; Copy SADDR8_ID into SADDR8_I                                  ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_SADDR8_I

            RSEG        SADDR8_I(2)
            RSEG        SADDR8_ID(2)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_copy
?INIT_SADDR8_I:

            MOVE_M      SFB SADDR8_ID, A0
            MOVE_M      SFE SADDR8_ID, A1
            MOVE_M      SFB SADDR8_I, A2
            JARL        ?seg_copy, LP

;---------------------------------------------------------------;
; Copy BREL23_ID into BREL23_I                                  ;
;---------------------------------------------------------------;

#if __CORE__ >= __CORE_V850E2M__

            PUBLIC      ?INIT_BREL23_I

            RSEG        BREL23_I(1)
            RSEG        BREL23_ID(1)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_copy

?INIT_BREL23_I:

            MOVE_M      SFB BREL23_ID, A0
            MOVE_M      SFE BREL23_ID, A1
            MOVE_M      SFB BREL23_I, A2
            JARL        ?seg_copy, LP

#endif

;---------------------------------------------------------------;
; Copy HUGE_ID into HUGE_I                                      ;
;---------------------------------------------------------------;
            PUBLIC      ?INIT_HUGE_I

            RSEG        HUGE_I(1)
            RSEG        HUGE_ID(1)

            RSEG        CSTART:CODE:NOROOT(1)

            EXTERN      ?seg_copy

?INIT_HUGE_I:

            MOVE_M      SFB HUGE_ID, A0
            MOVE_M      SFE HUGE_ID, A1
            MOVE_M      SFB HUGE_I, A2
            JARL        ?seg_copy, LP


;---------------------------------------------------------------;
; Destination label when skipping data initialization.          ;
;---------------------------------------------------------------;
            PUBLIC      ?no_seg_init

            RSEG        CSTART:CODE:NOROOT(1)

?no_seg_init:

            ENDMOD


;---------------------------------------------------------------;
; Calculate code distance (PIC only).                           ;
;---------------------------------------------------------------;

            MODULE      ?INIT_PIC
            PUBLIC      ?INIT_PIC

            RSEG        CSTART:CODE:NOROOT(1)

            RTMODEL     "__code_model", "pic"

            EXTERN      ?CODE_DISTANCE
            EXTERN_LS_M

?INIT_PIC:
            JARL        ref_point, A1
ref_point:  MOVE_M      ref_point, A2
            SUB         A2, A1
            ;; Expands to correct store instruction/sequence.
            STORE_M     A1, ?CODE_DISTANCE, A2
            ;; Note: A1 (the value of ?CODE_DISTANCE) is used below!

            ENDMOD


#if __CORE__ >= __CORE_V850E2M__

;---------------------------------------------------------------;
; Initialize the BSEL system register bank selector.            ;
;---------------------------------------------------------------;

            MODULE      ?INIT_BSEL
            RSEG        CSTART:CODE:NOROOT(1)
            PUBLIC      ?INIT_BSEL

?INIT_BSEL:
            LDSR        R0, 31          ; BSEL

            ENDMOD

#endif


#if __CORE__ >= __CORE_V850E__

;---------------------------------------------------------------;
; Initialize the CALLT base pointers.                           ;
;---------------------------------------------------------------;


            MODULE      ?INIT_CALLT
            PUBLIC      ?INIT_CALLT
            EXTERN      ?CALLT_BASE
            COMMON      CLTVEC(2)
            RSEG        CSTART:CODE:NOROOT(1)

            RTMODEL     "__cpu", "v850e"

            REQUIRE     ?CALLT_BASE

            ;; The Call table base pointer
?INIT_CALLT:
            MOVE_M      SFB CLTVEC, A2
#ifdef CODE_MODEL_PIC
            EXTERN      ?CODE_DISTANCE
            REQUIRE     ?CODE_DISTANCE

            ;; Add the value of ?CODE_DISTANCE calculated above
            ADD         A1, A2
#endif
#if __CORE__ >= __CORE_V850E2M__
            EXTERN      ?INIT_BSEL
            REQUIRE     ?INIT_BSEL
#endif
            LDSR        A2, 20          ; CTBP

            ENDMOD
#endif


#if __CORE__ >= __CORE_V850E2M__

;---------------------------------------------------------------;
; Initialize the SYSCALL base pointers.                         ;
;---------------------------------------------------------------;

            MODULE      ?INIT_SYSCALL
            PUBLIC      ?INIT_SYSCALL
            EXTERN      ?INIT_BSEL
            EXTERN      ?SYSCALL_BASE
            COMMON      SYSCALLVEC(2)

            RSEG        CSTART:CODE:NOROOT(1)

            REQUIRE     ?INIT_BSEL
            REQUIRE     ?SYSCALL_BASE

            ;; The syscall table base pointer
?INIT_SYSCALL:
            MOVE_M      SFB SYSCALLVEC, A2
#ifdef CODE_MODEL_PIC
            EXTERN      ?CODE_DISTANCE
            REQUIRE     ?CODE_DISTANCE

            ;; Add the value of ?CODE_DISTANCE calculated above
            ADD         A1, A2
#endif
            LDSR        A2, 12          ; SCBP

            MOVE_M      ((SFE SYSCALLVEC - SFB SYSCALLVEC)/4) - 1, A2
            LDSR        A2, 11          ; SCCFG

            ENDMOD

#endif

;---------------------------------------------------------------;
; This segment part is required by the compiler when it is      ;
; necessary to call constructors of global objects.             ;
;---------------------------------------------------------------;

            MODULE      ?CALL_MAIN
            RSEG        DIFUNCT(2)
            RSEG        CSTART:CODE:NOROOT(1)
            PUBLIC      ?cstart_call_ctors

            EXTERN      __call_ctors

?cstart_call_ctors:
            MOVE_M      SFB DIFUNCT, R1
            MOVE_M      SFE DIFUNCT, R5

            CALL_FUNC   __call_ctors, LP, R6


;---------------------------------------------------------------;
; Call C main() with no parameters.                             ;
;---------------------------------------------------------------;

            RSEG        CSTART:CODE:NOROOT(1)
            PUBLIC      ?cstart_call_main

            EXTERN      main
            EXTERN      exit
            EXTERN      __exit

?cstart_call_main:
            CALL_FUNC   main, LP, R6

;---------------------------------------------------------------;
; If we come here we have returned from main with a 'return'    ;
; statement, not with a call to exit() or abort().              ;
; In this case we must call exit() here for a nice ending.      ;
; Note: The return value of main() is the argument to exit().   ;
;---------------------------------------------------------------;
            CALL_FUNC   exit, LP, R6

;---------------------------------------------------------------;
; We should never come here, but just in case.                  ;
;---------------------------------------------------------------;

            MOV         __exit, LP
            JMP         [LP]

            PUBLIC      ?BTT_cstart_end
?BTT_cstart_end:


;---------------------------------------------------------------;
; Copy a chunk of memory.                                       ;
;       A0 = Start of from block                                ;
;       A1 = End of from block (+1)                             ;
;       A2 = Start of to block                                  ;
;---------------------------------------------------------------;

            PUBLIC      ?seg_copy
            PUBLIC      ?seg_clear

            RSEG        CSTART:CODE:NOROOT(1)
            REQUIRE     done

cp_cont:    LD.B        0[A0], R7
            ADD         1, A0
            ST.B        R7, 0[A2]
            ADD         1, A2

            ;; Note: The entry point is here.
?seg_copy:  CMP         A0, A1
            BNE         cp_cont

            RSEG        CSTART:CODE:NOROOT(1)

done:       JMP         [LP]

;---------------------------------------------------------------;
; Clear a chunk of memory.                                      ;
;       A0 = Start of block                                     ;
;       A1 = End of block (+1)                                  ;
;---------------------------------------------------------------;

            RSEG        CSTART:CODE:NOROOT(1)
            REQUIRE     done

?seg_clear: CMP         A0, A1
            BE          done
cl_cont:    ST.B        zero, 0[A0]
            ADD         1, A0
            BR          ?seg_clear

            ENDMOD


;---------------------------------------------------------------;
; _exit code                                                    ;
;                                                               ;
; Call destructors (if required), then fall through to __exit.  ;
;---------------------------------------------------------------;

            MODULE      ?_exit
            PUBLIC      _exit
            PUBLIC      ?BTT_exit_begin
            EXTERN      ?exit_restore2
            RSEG        RCODE:CODE:NOROOT(1)

?BTT_exit_begin:
_exit:
            REQUIRE     ?exit_restore2
            ;; If any of the two pieces of code "__cstart_call_dtors"
            ;; or "__cstart_closeall" is called we need to save the
            ;; argument to "_exit".  However, since we never will
            ;; from this function we can use a permanent register
            ;; rather than storing the value on the stack.

            RSEG        RCODE:CODE:NOROOT(1)
            EXTERN      ?exit_restore
            PUBLIC      ?exit_save
?exit_save:
            REQUIRE     ?exit_restore

            MOV         R1, R29

            RSEG        RCODE:CODE:NOROOT(1)
            PUBLIC      __cstart_call_dtors
            EXTERN      __call_dtors
            REQUIRE     ?exit_save

            ;; This label is required by "__record_needed_destruction".

__cstart_call_dtors:
            CALL_FUNC   __call_dtors, LP, R1

            ENDMOD

            ;; A new module is needed so that a non-terminal-IO program
            ;; doesn't include this, which requires __putchar.

            MODULE      ?__cstart_closeall
            RSEG        RCODE:CODE:NOROOT(1)

            ;; When stdio is used, the following piece of code is
            ;; required by the _Closreg macro.

            PUBLIC      __cstart_closeall
            EXTERN      ?exit_save
            REQUIRE     ?exit_save

            ;; This label is required by _Closreg

__cstart_closeall:
            EXTERN      _Close_all
            CALL_FUNC   _Close_all, LP, R1

            ENDMOD

            ;; Restore the argument previously stored by the "save" section
            ;; above.

            MODULE      ?_exit_end
            RSEG        RCODE:CODE:NOROOT(1)

            PUBLIC      ?exit_restore
            EXTERN      ?exit_restore2

?exit_restore:
            REQUIRE     ?exit_restore2
            MOV         R29, R1

            ENDMOD

            MODULE      ?_exit_end2
            PUBLIC      ?BTT_exit_end
            RSEG        RCODE:CODE:NOROOT(1)

            PUBLIC      ?exit_restore2
            EXTERN      __exit
?exit_restore2:

            MOV         __exit, LP
            JMP         [LP]

?BTT_exit_end:
            ENDMOD


;---------------------------------------------------------------;
; Define the base of the base relative (brel) data for RAM.     ;
;                                                               ;
; This empty segment should be places in front of the brel      ;
; RAM data segments.                                            ;
;---------------------------------------------------------------;

            MODULE      ?BREL_BASE
            PUBLIC      ?BREL_BASE

            RSEG        BREL_BASE:DATA:NOROOT(2)

?BREL_BASE:

            ENDMOD


;---------------------------------------------------------------;
; Define the base of the base relative (brel) data for ROM.     ;
;                                                               ;
; This empty segment should be places in front of the brel      ;
; ROM data segment.                                             ;
;---------------------------------------------------------------;

            MODULE      ?BREL_CBASE
            PUBLIC      ?BREL_CBASE

            RSEG        BREL_CBASE:CONST:NOROOT(2)

?BREL_CBASE:

            ENDMOD


;---------------------------------------------------------------;
; Define the base of the short addressing (saddr) data.         ;
;                                                               ;
; This empty segment should be places in front of the saddr     ;
; data segments.                                                ;
;---------------------------------------------------------------;

            MODULE      ?SADDR_BASE

            RTMODEL     "__reg_ep", "saddr"

            PUBLIC      ?SADDR_BASE
            RSEG        SADDR_BASE:CONST:NOROOT(2)

            EXTERN      ?INIT_SADDR_BASE
            REQUIRE     ?INIT_SADDR_BASE

?SADDR_BASE:

            ENDMOD


;---------------------------------------------------------------;
; The base of the CALLT vector.                                 ;
;---------------------------------------------------------------;

            MODULE      ?CALLT_BASE

            PUBLIC      ?CALLT_BASE
            COMMON      CLTVEC:CONST:NOROOT(2)
            DATA
?CALLT_BASE:

            ENDMOD


#if __CORE__ >= __CORE_V850E2M__

;---------------------------------------------------------------;
; The base of the SYSCALL vector.                               ;
;---------------------------------------------------------------;

            MODULE      ?SYSCALL_BASE

            PUBLIC      ?SYSCALL_BASE
            COMMON      SYSCALLVEC:CONST:NOROOT(2)
            DATA
?SYSCALL_BASE:

            ENDMOD

#endif

;---------------------------------------------------------------;
; The distance the code has been moved when using position      ;
; independent code.                                             ;
;---------------------------------------------------------------;

            MODULE      ?CODE_DISTANCE

            RTMODEL     "__code_model", "pic"

            PUBLIC      ?CODE_DISTANCE
            RSEG        LIBRARY_N:DATA:NOROOT(2)

            EXTERN      ?INIT_PIC
            REQUIRE     ?INIT_PIC

?CODE_DISTANCE:
            DS          4

            ENDMOD


;---------------------------------------------------------------;
; A dummy "low level init" that will be used if the user        ;
; hasn't defined this function.                                 ;
;---------------------------------------------------------------;

            MODULE      ?__low_level_init_stub
            PUBLIC      __low_level_init
            RSEG        RCODE:CODE:NOROOT
__low_level_init:
            MOV         1, R1
            JMP         [LP]

            ENDMOD

            END
