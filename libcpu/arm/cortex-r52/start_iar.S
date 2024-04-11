;/*
; * Copyright (c) 2006-2022, RT-Thread Development Team
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Change Logs:
; * Date           Author       Notes
; * 2024-03-11    Wangyuqiang   first version
; */
;@-------------------------------------------------------------------------------
;@ sys_core.asm
;@
;@ (c) Texas Instruments 2009-2013, All rights reserved.
;@

; Constants  
Mode_USR        EQU     0x10  
Mode_FIQ        EQU     0x11  
Mode_IRQ        EQU     0x12  
Mode_SVC        EQU     0x13  
Mode_ABT        EQU     0x17  
Mode_UND        EQU     0x1B  
Mode_SYS        EQU     0x1F  
  
I_Bit           EQU     0x80  
F_Bit           EQU     0x40  

UND_Stack_Size  EQU     0x00000000  
SVC_Stack_Size  EQU     0x00000000  
ABT_Stack_Size  EQU     0x00000000  
FIQ_Stack_Size  EQU     0x00001000  
IRQ_Stack_Size  EQU     0x00001000
        
    IMPORT _c_int00
    IMPORT rt_hw_trap_svc
    IMPORT rt_hw_trap_pabt
    IMPORT rt_hw_trap_dabt
    IMPORT rt_hw_trap_resv
    IMPORT system_init
    IMPORT __iar_program_start
  
; Define sections
    SECTION .text:CODE:REORDER:NOROOT(2)
  
    ; Define stack start and top  
    EXPORT stack_start  
    EXPORT stack_top  
  
    ; Align stack start to a 4-byte boundary (32-bit word)
    ALIGNRAM 5
stack_start:
    ; Reserve stack memory  
    REPT (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + FIQ_Stack_Size + IRQ_Stack_Size)  
        DCB 0   ; Define a byte of data and clear it to zero  
    ENDR  
  
    ; Define stack top label  
stack_top:  
  
; Define code section  
    SECTION .text:CODE:REORDER:NOROOT(2)
  
    ; Specify ARM mode
    THUMB

;@-------------------------------------------------------------------------------
;@ Enable RAM ECC Support

    EXPORT     _coreEnableRamEcc_
_coreEnableRamEcc_:

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

;@-------------------------------------------------------------------------------
;@ Disable RAM ECC Support

    EXPORT     _coreDisableRamEcc_
_coreDisableRamEcc_:

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

;@-------------------------------------------------------------------------------
;@ Enable Flash ECC Support

    EXPORT     _coreEnableFlashEcc_
_coreEnableFlashEcc_:

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x02000000
        dmb
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

;@-------------------------------------------------------------------------------
;@ Disable Flash ECC Support

    EXPORT     _coreDisableFlashEcc_
_coreDisableFlashEcc_:

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x02000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

;@-------------------------------------------------------------------------------
;@ Get data fault status register

    EXPORT     _coreGetDataFault_
_coreGetDataFault_:

        mrc   p15, #0, r0, c5, c0,  #0
        bx    lr

;@-------------------------------------------------------------------------------
;@ Clear data fault status register

    EXPORT     _coreClearDataFault_
_coreClearDataFault_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0,  #0
        ldmfd sp!, {r0}
        bx    lr

;@-------------------------------------------------------------------------------
;@ Get instruction fault status register

    EXPORT     _coreGetInstructionFault_
_coreGetInstructionFault_:

        mrc   p15, #0, r0, c5, c0, #1
        bx    lr

;@-------------------------------------------------------------------------------
;@ Clear instruction fault status register

    EXPORT     _coreClearInstructionFault_
_coreClearInstructionFault_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0, #1
        ldmfd sp!, {r0}
        bx    lr

;@-------------------------------------------------------------------------------
;@ Get data fault address register

    EXPORT     _coreGetDataFaultAddress_
_coreGetDataFaultAddress_:

        mrc   p15, #0, r0, c6, c0,  #0
        bx    lr

;@-------------------------------------------------------------------------------
;@ Clear data fault address register

    EXPORT     _coreClearDataFaultAddress_
_coreClearDataFaultAddress_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0,  #0
        ldmfd sp!, {r0}
        bx    lr

;@-------------------------------------------------------------------------------
;@ Get instruction fault address register

    EXPORT     _coreGetInstructionFaultAddress_
_coreGetInstructionFaultAddress_:

        mrc   p15, #0, r0, c6, c0, #2
        bx    lr

;@-------------------------------------------------------------------------------
;@ Clear instruction fault address register

    EXPORT     _coreClearInstructionFaultAddress_
_coreClearInstructionFaultAddress_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0, #2
        ldmfd sp!, {r0}
        bx    lr

;@-------------------------------------------------------------------------------
;@ Get auxiliary data fault status register

    EXPORT     _coreGetAuxiliaryDataFault_
_coreGetAuxiliaryDataFault_:

        mrc   p15, #0, r0, c5, c1, #0
        bx    lr



;@-------------------------------------------------------------------------------
;@ Clear auxiliary data fault status register

    EXPORT     _coreClearAuxiliaryDataFault_
_coreClearAuxiliaryDataFault_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c1, #0
        ldmfd sp!, {r0}
        bx    lr



;@-------------------------------------------------------------------------------
;@ Get auxiliary instruction fault status register

    EXPORT     _coreGetAuxiliaryInstructionFault_
_coreGetAuxiliaryInstructionFault_:

        mrc   p15, #0, r0, c5, c1, #1
        bx    lr


;@-------------------------------------------------------------------------------
;@ Clear auxiliary instruction fault status register

    EXPORT     _coreClearAuxiliaryInstructionFault_
_coreClearAuxiliaryInstructionFault_:

        stmfd sp!, {r0}
        mov   r0,  #0
        mrc   p15, #0, r0, c5, c1, #1
        ldmfd sp!, {r0}
        bx    lr

;@-------------------------------------------------------------------------------
;@ Work Around for Errata CORTEX-R4#57:
;@
;@ Errata Description:
;@            Conditional VMRS APSR_Nzcv, FPSCR May Evaluate With Incorrect Flags
;@ Workaround:
;@            Disable out-of-order single-precision floating point
;@            multiply-accumulate instruction completion

    EXPORT     _errata_CORTEXR4_57_
_errata_CORTEXR4_57_:

        push {r0}
        mrc p15, #0, r0, c15, c0, #0 ;@ Read Secondary Auxiliary Control Register
        orr r0, r0, #0x10000         ;@ Set BIT 16 (Set DOOFMACS)
        mcr p15, #0, r0, c15, c0, #0 ;@ Write Secondary Auxiliary Control Register
        pop {r0}
        bx lr

;@-------------------------------------------------------------------------------
;@ Work Around for Errata CORTEX-R4#66:
;@
;@ Errata Description:
;@            Register Corruption During A Load-Multiple Instruction At
;@            an Exception Vector
;@ Workaround:
;@            Disable out-of-order completion for divide instructions in
;@            Auxiliary Control register

    EXPORT     _errata_CORTEXR4_66_
_errata_CORTEXR4_66_:

        push {r0}
        mrc p15, #0, r0, c1, c0, #1 ;@ Read Auxiliary Control register
          orr r0, r0, #0x80           ;@ Set BIT 7 (Disable out-of-order completion
                                    ;@ for divide instructions.)
           mcr p15, #0, r0, c1, c0, #1 ;@ Write Auxiliary Control register
        pop {r0}
        bx lr
    EXPORT     turnon_VFP
turnon_VFP:
        ;@ Enable FPV
        stmdb sp!,     {r0}
        fmrx  r0,      fpexc
        orr   r0,      r0,   #0x40000000
        fmxr  fpexc,   r0
        ldmia sp!,     {r0}
        subs  pc,      lr,   #4

    macro push_svc_reg
        sub     sp, sp, #17 * 4         ;@/* Sizeof(struct rt_hw_exp_stack)  */
        stmia   sp, {r0 - r12}          ;@/* Calling r0-r12                  */
        mov     r0, sp
        mrs     r6, spsr                ;@/* Save CPSR                       */
        str     lr, [r0, #15*4]         ;@/* Push PC                         */
        str     r6, [r0, #16*4]         ;@/* Push CPSR                       */
        cps     #Mode_SVC
        str     sp, [r0, #13*4]         ;@/* Save calling SP                 */
        str     lr, [r0, #14*4]         ;@/* Save calling PC                 */
    endm

    EXPORT  SVC_Handler
SVC_Handler:
        push_svc_reg
        bl      rt_hw_trap_svc
        b       .

    EXPORT  Prefetch_Handler
Prefetch_Handler:
        push_svc_reg
        bl      rt_hw_trap_pabt
        b       .

    EXPORT  Abort_Handler
Abort_Handler:
        push_svc_reg
        bl      rt_hw_trap_dabt
        b       .

    EXPORT  Reserved_Handler
Reserved_Handler:
        push_svc_reg
        bl      rt_hw_trap_resv
        b       .
  END
