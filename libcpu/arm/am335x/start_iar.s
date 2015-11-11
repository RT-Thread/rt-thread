/*
 * File      : start_iar.s
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-06     zchong      the first version 
 */

        MODULE  ?cstartup
        
        ; --------------------
; Mode, correspords to bits 0-5 in CPSR

MODE_MSK DEFINE 0x1F            ; Bit mask for mode bits in CPSR
I_Bit    DEFINE 0x80            ; when I bit is set, IRQ is disabled
F_Bit    DEFINE 0x40            ; when F bit is set, FIQ is disabled

USR_MODE DEFINE 0x10            ; User mode
FIQ_MODE DEFINE 0x11            ; Fast Interrupt Request mode
IRQ_MODE DEFINE 0x12            ; Interrupt Request mode
SVC_MODE DEFINE 0x13            ; Supervisor mode
ABT_MODE DEFINE 0x17            ; Abort mode
UND_MODE DEFINE 0x1B            ; Undefined Instruction mode
SYS_MODE DEFINE 0x1F            ; System mode

        
        ;; Forward declaration of sections.
        SECTION IRQ_STACK:DATA:NOROOT(3)
        SECTION FIQ_STACK:DATA:NOROOT(3)
        SECTION SVC_STACK:DATA:NOROOT(3)
        SECTION ABT_STACK:DATA:NOROOT(3)
        SECTION UND_STACK:DATA:NOROOT(3)
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .text:CODE
        
        
        SECTION .intvec:CODE:NOROOT(5)

        PUBLIC  __vector
        PUBLIC  __iar_program_start


__iar_init$$done:               ; The vector table is not needed
                                ; until after copy initialization is done

__vector:                       ; Make this a DATA label, so that stack usage
                                ; analysis doesn't consider it an uncalled fun
        ARM

        ; All default exception handlers (except reset) are
        ; defined as weak symbol definitions.
        ; If a handler is defined by the application it will take precedence.
        LDR     PC,Reset_Addr           ; Reset
        LDR     PC,Undefined_Addr       ; Undefined instructions
        LDR     PC,SWI_Addr             ; Software interrupt (SWI/SVC)
        LDR     PC,Prefetch_Addr        ; Prefetch abort
        LDR     PC,Abort_Addr           ; Data abort
        DCD     0                       ; RESERVED
        LDR     PC,IRQ_Addr             ; IRQ
        LDR     PC,FIQ_Addr             ; FIQ

        DATA

Reset_Addr:     DCD   __iar_program_start
Undefined_Addr: DCD   Undefined_Handler
SWI_Addr:       DCD   SWI_Handler
Prefetch_Addr:  DCD   Prefetch_Handler
Abort_Addr:     DCD   Abort_Handler
IRQ_Addr:       DCD   IRQ_Handler
FIQ_Addr:       DCD   FIQ_Handler


; --------------------------------------------------
; ?cstartup -- low-level system initialization code.
;
; After a reset execution starts here, the mode is ARM, supervisor
; with interrupts disabled.
;

        SECTION .text:CODE:NOROOT(2)

        EXTERN  rt_hw_trap_udef
        EXTERN  rt_hw_trap_swi
        EXTERN  rt_hw_trap_pabt
        EXTERN  rt_hw_trap_dabt
        EXTERN  rt_hw_trap_fiq
        EXTERN  rt_hw_trap_irq
        EXTERN  rt_interrupt_enter
        EXTERN  rt_interrupt_leave
        EXTERN  rt_thread_switch_interrupt_flag
        EXTERN  rt_interrupt_from_thread
        EXTERN  rt_interrupt_to_thread
        EXTERN  rt_current_thread
        EXTERN  vmm_thread
        EXTERN  vmm_virq_check
        
        EXTERN  __cmain
        REQUIRE __vector
        EXTWEAK __iar_init_core
        EXTWEAK __iar_init_vfp


        ARM

__iar_program_start:
?cstartup:

;
; Add initialization needed before setup of stackpointers here.
;

;
; Initialize the stack pointers.
; The pattern below can be used for any of the exception stacks:
; FIQ, IRQ, SVC, ABT, UND, SYS.
; The USR mode uses the same stack as SYS.
; The stack segments must be defined in the linker command file,
; and be declared above.
;

        MRS     r0, cpsr                ; Original PSR value

        ;; Set up the interrupt stack pointer.
        BIC     r0, r0, #MODE_MSK       ; Clear the mode bits
        ORR     r0, r0, #IRQ_MODE       ; Set IRQ mode bits
        MSR     cpsr_c, r0              ; Change the mode
        LDR     sp, =SFE(IRQ_STACK)     ; End of IRQ_STACK
        BIC     sp,sp,#0x7              ; Make sure SP is 8 aligned

        ;; Set up the fast interrupt stack pointer.
        BIC     r0, r0, #MODE_MSK       ; Clear the mode bits
        ORR     r0, r0, #FIQ_MODE       ; Set FIR mode bits
        MSR     cpsr_c, r0              ; Change the mode
        LDR     sp, =SFE(FIQ_STACK)     ; End of FIQ_STACK
        BIC     sp,sp,#0x7              ; Make sure SP is 8 aligned
        
        BIC     r0,r0,#MODE_MSK         ; Clear the mode bits
        ORR     r0,r0,#ABT_MODE         ; Set Abort mode bits
        MSR     cpsr_c,r0               ; Change the mode
        LDR     sp,=SFE(ABT_STACK)      ; End of ABT_STACK
        BIC     sp,sp,#0x7              ; Make sure SP is 8 aligned

        BIC     r0,r0,#MODE_MSK         ; Clear the mode bits
        ORR     r0,r0,#UND_MODE         ; Set Undefined mode bits
        MSR     cpsr_c,r0               ; Change the mode
        LDR     sp,=SFE(UND_STACK)      ; End of UND_STACK
        BIC     sp,sp,#0x7              ; Make sure SP is 8 aligned

        ;; Set up the normal stack pointer.
        BIC     r0 ,r0, #MODE_MSK       ; Clear the mode bits
        ORR     r0 ,r0, #SVC_MODE       ; Set System mode bits
        MSR     cpsr_c, r0              ; Change the mode
        LDR     sp, =SFE(SVC_STACK)     ; End of SVC_STACK
        BIC     sp,sp,#0x7              ; Make sure SP is 8 aligned

        ;; Turn on core features assumed to be enabled.
        BL      __iar_init_core

        ;; Initialize VFP (if needed).
        BL      __iar_init_vfp


        ;; Continue to __cmain for C-level initialization.
        B       __cmain

      
Undefined_Handler:
        SUB     sp, sp, #72
        STMIA   sp, {r0 - r12}          ;/* Calling r0-r12                  */
        ADD     r8, sp, #60

        MRS     r1, cpsr
        MRS     r2, spsr
        ORR     r2,r2, #I_Bit | F_Bit
        MSR     cpsr_c, r2
        MOV     r0, r0
        STMDB   r8, {sp, lr}            ;/* Calling SP, LR                  */
        MSR     cpsr_c, r1              ;/* return to Undefined Instruction mode  */

        STR     lr, [r8, #0]            ;/* Save calling PC                 */
        MRS     r6, spsr
        STR     r6, [r8, #4]            ;/* Save CPSR                       */
        STR     r0, [r8, #8]            ;/* Save OLD_R0                     */
        MOV     r0, sp

        BL      rt_hw_trap_udef

        LDMIA    sp, {r0 - r12}         ;/* Calling r0 - r2  */
        MOV      r0, r0
        LDR      lr, [sp, #60]          ;/* Get PC   */
        ADD      sp, sp, #72
        MOVS     pc, lr                 ;/* return & move spsr_svc into cpsr */

SWI_Handler:
        BL      rt_hw_trap_swi

Prefetch_Handler:
        BL      rt_hw_trap_pabt

Abort_Handler:
        SUB     sp, sp, #72
        STMIA   sp, {r0 - r12}          ;/* Calling r0-r12                  */
        ADD     r8, sp, #60
        STMDB   r8, {sp, lr}            ;/* Calling SP, LR                  */
        STR     lr, [r8, #0]            ;/* Save calling PC                 */
        MRS     r6, spsr
        STR     r6, [r8, #4]            ;/* Save CPSR                       */
        STR     r0, [r8, #8]            ;/* Save OLD_R0                     */
        MOV     r0, sp

        BL      rt_hw_trap_dabt

        LDMIA    sp, {r0 - r12}         ;/* Calling r0 - r2  */
        MOV      r0, r0
        LDR      lr, [sp, #60]          ;/* Get PC   */
        ADD      sp, sp, #72
        MOVS     pc, lr                 ;/* return & move spsr_svc into cpsr */
         
FIQ_Handler:
        STMFD   sp!,{r0-r7,lr}
        BL      rt_hw_trap_fiq
        LDMFD   sp!,{r0-r7,lr}
        SUBS    pc,lr,#4

IRQ_Handler:
        STMFD   sp!, {r0-r12,lr}

        BL      rt_interrupt_enter
        BL      rt_hw_trap_irq
        BL      rt_interrupt_leave

        ; if rt_thread_switch_interrupt_flag set, jump to
        ; rt_hw_context_switch_interrupt_do and don't return
        LDR     r0, =rt_thread_switch_interrupt_flag
        LDR     r1, [r0]
        CMP     r1, #1
        BEQ     rt_hw_context_switch_interrupt_do

        LDMFD   sp!, {r0-r12,lr}
        SUBS    pc, lr, #4

rt_hw_context_switch_interrupt_do:
        MOV     r1,  #0         ; clear flag
        STR     r1,  [r0]

        LDMFD   sp!, {r0-r12,lr}; reload saved registers
        STMFD   sp,  {r0-r2}    ; save r0-r2

        MRS     r0,  spsr       ; get cpsr of interrupt thread

        SUB     r1,  sp, #4*3
        SUB     r2,  lr, #4     ; save old task's pc to r2

        ; switch to SVC mode with no interrupt
        MSR     cpsr_c, #I_Bit | F_Bit | SVC_MODE

        STMFD   sp!, {r2}       ; push old task's pc
        STMFD   sp!, {r3-r12,lr}; push old task's lr,r12-r4
        LDMFD   r1,  {r1-r3}    ; restore r0-r2 of the interrupt thread
        STMFD   sp!, {r1-r3}    ; push old task's r0-r2
        STMFD   sp!, {r0}       ; push old task's cpsr

        LDR     r4,  =rt_interrupt_from_thread
        LDR     r5,  [r4]
        STR     sp,  [r5]       ; store sp in preempted tasks's TCB

        LDR     r6,  =rt_interrupt_to_thread
        LDR     r6,  [r6]
        LDR     sp,  [r6]       ; get new task's stack pointer

        LDMFD   sp!, {r4}       ; pop new task's cpsr to spsr
        MSR     spsr_cxsf, r4

        LDMFD   sp!, {r0-r12,lr,pc}^ ; pop new task's r0-r12,lr & pc, copy spsr to cpsr
    
     END
