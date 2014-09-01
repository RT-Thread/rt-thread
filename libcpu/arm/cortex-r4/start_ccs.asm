;-------------------------------------------------------------------------------
; sys_core.asm
;
; (c) Texas Instruments 2009-2013, All rights reserved.
;

    .text
    .arm

    .ref _c_int00

    .def     _reset
    .asmfunc
_reset
;-------------------------------------------------------------------------------
; Initialize CPU Registers
; After reset, the CPU is in the Supervisor mode (M = 10011)
        mov r0, lr
        mov r1, #0x0000
        mov r2, #0x0000
        mov r3, #0x0000
        mov r4, #0x0000
        mov r5, #0x0000
        mov r6, #0x0000
        mov r7, #0x0000
        mov r8, #0x0000
        mov r9, #0x0000
        mov r10, #0x0000
        mov r11, #0x0000
        mov r12, #0x0000
        mov r13, #0x0000
        mrs r1, cpsr
        msr spsr_cxsf, r1
        ; Switch to FIQ mode (M = 10001)
        cps #17
        mov lr, r0
        mov r8, #0x0000
        mov r9, #0x0000
        mov r10, #0x0000
        mov r11, #0x0000
        mov r12, #0x0000
        mrs r1, cpsr
        msr spsr_cxsf, r1
        ; Switch to IRQ mode (M = 10010)
        cps #18
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch to Abort mode (M = 10111)
        cps #23
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch to Undefined Instruction Mode (M = 11011)
        cps #27
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch to System Mode ( Shares User Mode registers ) (M = 11111)
        cps #31
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch back to Supervisor Mode (M = 10011)
        cps #19

        ; Turn on FPV coprocessor
        mrc   p15,     #0x00,      r2,       c1, c0, #0x02
        orr   r2,      r2,         #0xF00000
        mcr   p15,     #0x00,      r2,       c1, c0, #0x02

        .if (RT_VFP_LAZY_STACKING) = 0
        fmrx  r2,      fpexc
        orr   r2,      r2,   #0x40000000
        fmxr  fpexc,   r2

        fmdrr d0,         r1,     r1
        fmdrr d1,         r1,     r1
        fmdrr d2,         r1,     r1
        fmdrr d3,         r1,     r1
        fmdrr d4,         r1,     r1
        fmdrr d5,         r1,     r1
        fmdrr d6,         r1,     r1
        fmdrr d7,         r1,     r1
        fmdrr d8,         r1,     r1
        fmdrr d9,         r1,     r1
        fmdrr d10,        r1,     r1
        fmdrr d11,        r1,     r1
        fmdrr d12,        r1,     r1
        fmdrr d13,        r1,     r1
        fmdrr d14,        r1,     r1
        fmdrr d15,        r1,     r1
        .endif

;-------------------------------------------------------------------------------
; Initialize Stack Pointers
        cps   #17
        ldr   sp,       fiqSp
        cps   #18
        ldr   sp,       irqSp
        cps   #23
        ldr   sp,       abortSp
        cps   #27
        ldr   sp,       undefSp
        cps   #31
        ldr   sp,       userSp
        cps   #19
        ldr   sp,       svcSp

        bl    next1
next1
        bl    next2
next2
        bl    next3
next3
        bl    next4
next4
        ldr  lr, int00ad
        bx   lr

int00ad .word _c_int00
userSp  .word 0x08000000+0x00001000
svcSp   .word 0x08000000+0x00001000+0x00000100
fiqSp   .word 0x08000000+0x00001000+0x00000100+0x00000100
irqSp   .word 0x08000000+0x00001000+0x00000100+0x00000100+0x00000100
abortSp .word 0x08000000+0x00001000+0x00000100+0x00000100+0x00000100+0x00000100
undefSp .word 0x08000000+0x00001000+0x00000100+0x00000100+0x00000100+0x00000100+0x00000100

    .endasmfunc

;-------------------------------------------------------------------------------
; Enable RAM ECC Support

    .def     _coreEnableRamEcc_
    .asmfunc

_coreEnableRamEcc_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Disable RAM ECC Support

    .def     _coreDisableRamEcc_
    .asmfunc

_coreDisableRamEcc_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable Flash ECC Support

    .def     _coreEnableFlashEcc_
    .asmfunc

_coreEnableFlashEcc_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x02000000
        dmb
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Disable Flash ECC Support

    .def     _coreDisableFlashEcc_
    .asmfunc

_coreDisableFlashEcc_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x02000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Get data fault status register

    .def     _coreGetDataFault_
    .asmfunc

_coreGetDataFault_

        mrc   p15, #0, r0, c5, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear data fault status register

    .def     _coreClearDataFault_
    .asmfunc

_coreClearDataFault_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0,  #0
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get instruction fault status register

    .def     _coreGetInstructionFault_
    .asmfunc

_coreGetInstructionFault_

        mrc   p15, #0, r0, c5, c0, #1
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear instruction fault status register

    .def     _coreClearInstructionFault_
    .asmfunc

_coreClearInstructionFault_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0, #1
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get data fault address register

    .def     _coreGetDataFaultAddress_
    .asmfunc

_coreGetDataFaultAddress_

        mrc   p15, #0, r0, c6, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear data fault address register

    .def     _coreClearDataFaultAddress_
    .asmfunc

_coreClearDataFaultAddress_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0,  #0
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get instruction fault address register

    .def     _coreGetInstructionFaultAddress_
    .asmfunc

_coreGetInstructionFaultAddress_

        mrc   p15, #0, r0, c6, c0, #2
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear instruction fault address register

    .def     _coreClearInstructionFaultAddress_
    .asmfunc

_coreClearInstructionFaultAddress_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0, #2
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get auxiliary data fault status register

    .def     _coreGetAuxiliaryDataFault_
    .asmfunc

_coreGetAuxiliaryDataFault_

        mrc   p15, #0, r0, c5, c1, #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear auxiliary data fault status register

    .def     _coreClearAuxiliaryDataFault_
    .asmfunc

_coreClearAuxiliaryDataFault_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c1, #0
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get auxiliary instruction fault status register

    .def     _coreGetAuxiliaryInstructionFault_
    .asmfunc

_coreGetAuxiliaryInstructionFault_

        mrc   p15, #0, r0, c5, c1, #1
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Clear auxiliary instruction fault status register

    .def     _coreClearAuxiliaryInstructionFault_
    .asmfunc

_coreClearAuxiliaryInstructionFault_

        stmfd sp!, {r0}
        mov   r0,  #0
        mrc   p15, #0, r0, c5, c1, #1
        ldmfd sp!, {r0}
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Clear ESM CCM errorss

       .def _esmCcmErrorsClear_
       .asmfunc

_esmCcmErrorsClear_

        stmfd sp!, {r0-r2}
        ldr   r0, ESMSR1_REG    ; load the ESMSR1 status register address
        ldr   r2, ESMSR1_ERR_CLR
        str   r2, [r0]         ; clear the ESMSR1 register

        ldr   r0, ESMSR2_REG    ; load the ESMSR2 status register address
        ldr   r2, ESMSR2_ERR_CLR
        str   r2, [r0]         ; clear the ESMSR2 register

        ldr   r0, ESMSSR2_REG    ; load the ESMSSR2 status register address
        ldr   r2, ESMSSR2_ERR_CLR
        str   r2, [r0]             ; clear the ESMSSR2 register

        ldr   r0, ESMKEY_REG    ; load the ESMKEY register address
        mov   r2, #0x5             ; load R2 with 0x5
        str   r2, [r0]             ; clear the ESMKEY register

        ldr   r0, VIM_INTREQ    ; load the INTREQ register address
        ldr   r2, VIM_INT_CLR
        str   r2, [r0]         ; clear the INTREQ register
        ldr   r0, CCMR4_STAT_REG    ; load the CCMR4 status register address
        ldr   r2, CCMR4_ERR_CLR
        str   r2, [r0]         ; clear the CCMR4 status register
        ldmfd sp!, {r0-r2}
        bx    lr

ESMSR1_REG        .word 0xFFFFF518
ESMSR2_REG        .word 0xFFFFF51C
ESMSR3_REG        .word 0xFFFFF520
ESMKEY_REG        .word 0xFFFFF538
ESMSSR2_REG       .word 0xFFFFF53C
CCMR4_STAT_REG    .word 0xFFFFF600
ERR_CLR_WRD       .word 0xFFFFFFFF
CCMR4_ERR_CLR     .word 0x00010000
ESMSR1_ERR_CLR    .word 0x80000000
ESMSR2_ERR_CLR    .word 0x00000004
ESMSSR2_ERR_CLR   .word 0x00000004
VIM_INT_CLR       .word 0x00000001
VIM_INTREQ        .word 0xFFFFFE20

        .endasmfunc

;-------------------------------------------------------------------------------
; Work Around for Errata CORTEX-R4#57:
;
; Errata Description:
;            Conditional VMRS APSR_Nzcv, FPSCR May Evaluate With Incorrect Flags
; Workaround:
;            Disable out-of-order single-precision floating point
;            multiply-accumulate instruction completion

        .def     _errata_CORTEXR4_57_
        .asmfunc

_errata_CORTEXR4_57_

        push {r0}
        mrc p15, #0, r0, c15, c0, #0 ; Read Secondary Auxiliary Control Register
        orr r0, r0, #0x10000         ; Set BIT 16 (Set DOOFMACS)
        mcr p15, #0, r0, c15, c0, #0 ; Write Secondary Auxiliary Control Register
        pop {r0}
        bx lr
    .endasmfunc

;-------------------------------------------------------------------------------
; Work Around for Errata CORTEX-R4#66:
;
; Errata Description:
;            Register Corruption During A Load-Multiple Instruction At
;            an Exception Vector
; Workaround:
;            Disable out-of-order completion for divide instructions in
;            Auxiliary Control register

        .def     _errata_CORTEXR4_66_
        .asmfunc

_errata_CORTEXR4_66_

        push {r0}
        mrc p15, #0, r0, c1, c0, #1 ; Read Auxiliary Control register
          orr r0, r0, #0x80           ; Set BIT 7 (Disable out-of-order completion
                                    ; for divide instructions.)
           mcr p15, #0, r0, c1, c0, #1 ; Write Auxiliary Control register
        pop {r0}
        bx lr
    .endasmfunc

    .def     turnon_VFP
    .asmfunc
turnon_VFP
        ; Enable FPV
        STMDB sp!,     {r0}
        fmrx  r0,      fpexc
        orr   r0,      r0,   #0x40000000
        fmxr  fpexc,   r0
        LDMIA sp!,     {r0}
        subs  pc,      lr,   #4
    .endasmfunc

_push_svc_reg    .macro
        sub     sp, sp, #17 * 4         ;/* Sizeof(struct rt_hw_exp_stack)  */
        stmia   sp, {r0 - r12}          ;/* Calling r0-r12                  */
        mov     r0, sp
        mrs     r6, spsr                ;/* Save CPSR                       */
        str     lr, [r0, #15*4]         ;/* Push PC                         */
        str     r6, [r0, #16*4]         ;/* Push CPSR                       */
        cps     #0x13
        str     sp, [r0, #13*4]         ;/* Save calling SP                 */
        str     lr, [r0, #14*4]         ;/* Save calling PC                 */
	.endm

	.ref    rt_hw_trap_svc
    .def	vector_svc
    .asmfunc
vector_svc:
        _push_svc_reg
        bl      rt_hw_trap_svc
		sub     pc, pc, #-4
    .endasmfunc

	.ref    rt_hw_trap_pabt
    .def	vector_pabort
    .asmfunc
vector_pabort:
        _push_svc_reg
        bl      rt_hw_trap_pabt
		sub     pc, pc, #-4
    .endasmfunc

	.ref    rt_hw_trap_dabt
    .def	vector_dabort
    .asmfunc
vector_dabort:
        _push_svc_reg
        bl      rt_hw_trap_dabt
		sub     pc, pc, #-4
    .endasmfunc

	.ref    rt_hw_trap_resv
    .def	vector_resv
    .asmfunc
vector_resv:
        _push_svc_reg
        bl      rt_hw_trap_resv
		sub     pc, pc, #-4
    .endasmfunc

;-------------------------------------------------------------------------------
; C++ construct table pointers

    .def    __TI_PINIT_Base, __TI_PINIT_Limit
    .weak   SHT$$INIT_ARRAY$$Base, SHT$$INIT_ARRAY$$Limit

__TI_PINIT_Base  .long SHT$$INIT_ARRAY$$Base
__TI_PINIT_Limit .long SHT$$INIT_ARRAY$$Limit

;-------------------------------------------------------------------------------
