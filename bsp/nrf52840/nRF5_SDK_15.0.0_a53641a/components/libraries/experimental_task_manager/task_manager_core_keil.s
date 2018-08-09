; Copyright (c) 2017 - 2017, Nordic Semiconductor ASA
; 
; All rights reserved.
; 
; Redistribution and use in source and binary forms, with or without modification,
; are permitted provided that the following conditions are met:
; 
; 1. Redistributions of source code must retain the above copyright notice, this
;    list of conditions and the following disclaimer.
; 
; 2. Redistributions in binary form, except as embedded into a Nordic
;    Semiconductor ASA integrated circuit in a product or a software update for
;    such product, must reproduce the above copyright notice, this list of
;    conditions and the following disclaimer in the documentation and/or other
;    materials provided with the distribution.
; 
; 3. Neither the name of Nordic Semiconductor ASA nor the names of its
;    contributors may be used to endorse or promote products derived from this
;    software without specific prior written permission.
; 
; 4. This software, with or without modification, must only be used with a
;    Nordic Semiconductor ASA integrated circuit.
; 
; 5. Any software provided in binary form under this license must not be reverse
;    engineered, decompiled, modified and/or disassembled.
; 
; THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
; OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
; OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
; LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
; CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
; GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
; HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
; LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
; OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;

                PRESERVE8
                THUMB
                AREA        |.text|, CODE, READONLY

task_switch     PROC
                EXPORT      task_switch
                IMPORT      task_schedule

                MRS         R0, CONTROL             ; Fetch CONTROL register to R0

                IF :DEF: FLOAT_ABI_HARD
                TST         R0, #(1 << 2)           ; Check FPCA flag.
                ITTT        NE
                VMRSNE      R1, FPSCR               ; If FPCA set, fetch FPSCR.
                STMDBNE     SP!, {R0, R1}           ; If FPCA set, save FPSCR (also pad stack to 8-byte alignment)
                VSTMDBNE    SP!, {S0-S31}           ; If FPCA set, save FPU registers.
                ENDIF

                STMDB       SP!, {R0}               ; Save CONTROL register.
                AND         R0, R0, #~(1 << 2)      ; Clear FPCA bit.
                MSR         CONTROL, R0             ; Update CONTROL register.

                STMDB       SP!, {R0, R4-R12, LR}   ; Save CPU registers. Reserve space for R0, needed to pass argument to new task.

                MOV         R0, SP                  ; Call task scheduler with current stack pointer as argument.
                LDR         R1, =task_schedule      ;
                BLX         R1                      ;

                MOV         SP, R0                  ; Switch to new stack, returned by task scheduler.

                LDMIA       SP!, {R3, R4-R12, LR}   ; Restore CPU registers. Argument to new task is in R3.
                LDMIA       SP!, {R0}               ; Restore CONTROL register.
                MSR         CONTROL, R0             ; Update CONTROL register.

                IF :DEF: FLOAT_ABI_HARD
                TST         R0, #(1 << 2)           ; Check FPCA flag.
                ITTT        NE
                VLDMIANE    SP!, {S0-S31}           ; If FPCA set, restore FPU registers.
                LDMIANE     SP!, {R0, R1}           ; If FPCA set, restore FPSCR (also remove padding).
                VMSRNE      FPSCR, R1               ; If FPCA set, update FPSCR
                ENDIF

                MOV         R0, R3                  ; Place optional task argument in R0.
                BX          LR                      ; Return to new task.

                ENDP
                END
