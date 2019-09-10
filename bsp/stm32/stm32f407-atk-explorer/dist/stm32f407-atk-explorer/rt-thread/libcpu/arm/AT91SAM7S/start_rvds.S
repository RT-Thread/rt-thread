;/*****************************************************************************/
;/* SAM7.S: Startup file for Atmel AT91SAM7 device series                     */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */ 
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2006 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


;/*
; *  The SAM7.S code is executed after CPU Reset. This file may be 
; *  translated with the following SET symbols. In uVision these SET 
; *  symbols are entered under Options - ASM - Define.
; *
; *  REMAP: when set the startup code remaps exception vectors from
; *  on-chip RAM to address 0.
; *
; *  RAM_INTVEC: when set the startup code copies exception vectors 
; *  from on-chip Flash to on-chip RAM.
; */


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled


; Internal Memory Base Addresses
FLASH_BASE      EQU     0x00100000   
RAM_BASE        EQU     0x00200000


;// <h> Stack Configuration (Stack Sizes in Bytes)
;//   <o0> Undefined Mode      <0x0-0xFFFFFFFF:8>
;//   <o1> Supervisor Mode     <0x0-0xFFFFFFFF:8>
;//   <o2> Abort Mode          <0x0-0xFFFFFFFF:8>
;//   <o3> Fast Interrupt Mode <0x0-0xFFFFFFFF:8>
;//   <o4> Interrupt Mode      <0x0-0xFFFFFFFF:8>
;//   <o5> User/System Mode    <0x0-0xFFFFFFFF:8>
;// </h>

UND_Stack_Size  EQU     0x00000000
SVC_Stack_Size  EQU     0x00000100
ABT_Stack_Size  EQU     0x00000000
FIQ_Stack_Size  EQU     0x00000000
IRQ_Stack_Size  EQU     0x00000100
USR_Stack_Size  EQU     0x00000100

ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)

                AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF>
;// </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


; Reset Controller (RSTC) definitions
RSTC_BASE       EQU     0xFFFFFD00      ; RSTC Base Address
RSTC_MR         EQU     0x08            ; RSTC_MR Offset

;/*
;// <e> Reset Controller (RSTC)
;//   <o1.0>     URSTEN: User Reset Enable
;//              <i> Enables NRST Pin to generate Reset
;//   <o1.8..11> ERSTL: External Reset Length <0-15>
;//              <i> External Reset Time in 2^(ERSTL+1) Slow Clock Cycles
;// </e>
;*/
RSTC_SETUP      EQU     1
RSTC_MR_Val     EQU     0xA5000401


; Embedded Flash Controller (EFC) definitions
EFC_BASE        EQU     0xFFFFFF00      ; EFC Base Address
EFC0_FMR        EQU     0x60            ; EFC0_FMR Offset
EFC1_FMR        EQU     0x70            ; EFC1_FMR Offset

;// <e> Embedded Flash Controller 0 (EFC0)
;//   <o1.16..23> FMCN: Flash Microsecond Cycle Number <0-255>
;//               <i> Number of Master Clock Cycles in 1us
;//   <o1.8..9>   FWS: Flash Wait State
;//               <0=> Read: 1 cycle / Write: 2 cycles
;//               <1=> Read: 2 cycle / Write: 3 cycles
;//               <2=> Read: 3 cycle / Write: 4 cycles
;//               <3=> Read: 4 cycle / Write: 4 cycles
;// </e>
EFC0_SETUP      EQU     1
EFC0_FMR_Val    EQU     0x00320100

;// <e> Embedded Flash Controller 1 (EFC1)
;//   <o1.16..23> FMCN: Flash Microsecond Cycle Number <0-255>
;//               <i> Number of Master Clock Cycles in 1us
;//   <o1.8..9>   FWS: Flash Wait State
;//               <0=> Read: 1 cycle / Write: 2 cycles
;//               <1=> Read: 2 cycle / Write: 3 cycles
;//               <2=> Read: 3 cycle / Write: 4 cycles
;//               <3=> Read: 4 cycle / Write: 4 cycles
;// </e>
EFC1_SETUP      EQU     0
EFC1_FMR_Val    EQU     0x00320100


; Watchdog Timer (WDT) definitions
WDT_BASE        EQU     0xFFFFFD40      ; WDT Base Address
WDT_MR          EQU     0x04            ; WDT_MR Offset

;// <e> Watchdog Timer (WDT)
;//   <o1.0..11>  WDV: Watchdog Counter Value <0-4095>
;//   <o1.16..27> WDD: Watchdog Delta Value <0-4095>
;//   <o1.12>     WDFIEN: Watchdog Fault Interrupt Enable
;//   <o1.13>     WDRSTEN: Watchdog Reset Enable
;//   <o1.14>     WDRPROC: Watchdog Reset Processor
;//   <o1.28>     WDDBGHLT: Watchdog Debug Halt
;//   <o1.29>     WDIDLEHLT: Watchdog Idle Halt
;//   <o1.15>     WDDIS: Watchdog Disable
;// </e>
WDT_SETUP       EQU     1
WDT_MR_Val      EQU     0x00008000


; Power Mangement Controller (PMC) definitions
PMC_BASE        EQU     0xFFFFFC00      ; PMC Base Address
PMC_MOR         EQU     0x20            ; PMC_MOR Offset
PMC_MCFR        EQU     0x24            ; PMC_MCFR Offset
PMC_PLLR        EQU     0x2C            ; PMC_PLLR Offset
PMC_MCKR        EQU     0x30            ; PMC_MCKR Offset
PMC_SR          EQU     0x68            ; PMC_SR Offset
PMC_MOSCEN      EQU     (1<<0)          ; Main Oscillator Enable
PMC_OSCBYPASS   EQU     (1<<1)          ; Main Oscillator Bypass
PMC_OSCOUNT     EQU     (0xFF<<8)       ; Main OScillator Start-up Time
PMC_DIV         EQU     (0xFF<<0)       ; PLL Divider
PMC_PLLCOUNT    EQU     (0x3F<<8)       ; PLL Lock Counter
PMC_OUT         EQU     (0x03<<14)      ; PLL Clock Frequency Range
PMC_MUL         EQU     (0x7FF<<16)     ; PLL Multiplier
PMC_USBDIV      EQU     (0x03<<28)      ; USB Clock Divider
PMC_CSS         EQU     (3<<0)          ; Clock Source Selection
PMC_PRES        EQU     (7<<2)          ; Prescaler Selection
PMC_MOSCS       EQU     (1<<0)          ; Main Oscillator Stable
PMC_LOCK        EQU     (1<<2)          ; PLL Lock Status
PMC_MCKRDY      EQU     (1<<3)          ; Master Clock Status

;// <e> Power Mangement Controller (PMC)
;//   <h> Main Oscillator
;//     <o1.0>      MOSCEN: Main Oscillator Enable
;//     <o1.1>      OSCBYPASS: Oscillator Bypass
;//     <o1.8..15>  OSCCOUNT: Main Oscillator Startup Time <0-255>
;//   </h>
;//   <h> Phase Locked Loop (PLL)
;//     <o2.0..7>   DIV: PLL Divider <0-255>
;//     <o2.16..26> MUL: PLL Multiplier <0-2047>
;//                 <i> PLL Output is multiplied by MUL+1
;//     <o2.14..15> OUT: PLL Clock Frequency Range
;//                 <0=> 80..160MHz  <1=> Reserved
;//                 <2=> 150..220MHz <3=> Reserved
;//     <o2.8..13>  PLLCOUNT: PLL Lock Counter <0-63>
;//     <o2.28..29> USBDIV: USB Clock Divider
;//                 <0=> None  <1=> 2  <2=> 4  <3=> Reserved
;//   </h>
;//   <o3.0..1>   CSS: Clock Source Selection
;//               <0=> Slow Clock
;//               <1=> Main Clock
;//               <2=> Reserved
;//               <3=> PLL Clock
;//   <o3.2..4>   PRES: Prescaler
;//               <0=> None
;//               <1=> Clock / 2    <2=> Clock / 4
;//               <3=> Clock / 8    <4=> Clock / 16
;//               <5=> Clock / 32   <6=> Clock / 64
;//               <7=> Reserved
;// </e>
PMC_SETUP       EQU     1
PMC_MOR_Val     EQU     0x00000601
PMC_PLLR_Val    EQU     0x00191C05
PMC_MCKR_Val    EQU     0x00000007


                PRESERVE8
                

; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM


; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

Vectors         LDR     PC,Reset_Addr         
                LDR     PC,Undef_Addr
                LDR     PC,SWI_Addr
                LDR     PC,PAbt_Addr
                LDR     PC,DAbt_Addr
                NOP                            ; Reserved Vector
                LDR     PC,IRQ_Addr
                LDR     PC,FIQ_Addr

Reset_Addr      DCD     Reset_Handler
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SWI_Handler
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD     0                      ; Reserved Address
IRQ_Addr        DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler

Undef_Handler   B       Undef_Handler
SWI_Handler     B       SWI_Handler
PAbt_Handler    B       PAbt_Handler
DAbt_Handler    B       DAbt_Handler
FIQ_Handler     B       FIQ_Handler


; Reset Handler

                EXPORT  Reset_Handler
Reset_Handler   


; Setup RSTC
                IF      RSTC_SETUP != 0
                LDR     R0, =RSTC_BASE
                LDR     R1, =RSTC_MR_Val
                STR     R1, [R0, #RSTC_MR]
                ENDIF


; Setup EFC0
                IF      EFC0_SETUP != 0
                LDR     R0, =EFC_BASE
                LDR     R1, =EFC0_FMR_Val
                STR     R1, [R0, #EFC0_FMR]
                ENDIF

; Setup EFC1
                IF      EFC1_SETUP != 0
                LDR     R0, =EFC_BASE
                LDR     R1, =EFC1_FMR_Val
                STR     R1, [R0, #EFC1_FMR]
                ENDIF

; Setup WDT
                IF      WDT_SETUP != 0
                LDR     R0, =WDT_BASE
                LDR     R1, =WDT_MR_Val
                STR     R1, [R0, #WDT_MR]
                ENDIF


; Setup PMC
                IF      PMC_SETUP != 0
                LDR     R0, =PMC_BASE

;  Setup Main Oscillator
                LDR     R1, =PMC_MOR_Val
                STR     R1, [R0, #PMC_MOR]

;  Wait until Main Oscillator is stablilized
                IF      (PMC_MOR_Val:AND:PMC_MOSCEN) != 0
MOSCS_Loop      LDR     R2, [R0, #PMC_SR]
                ANDS    R2, R2, #PMC_MOSCS
                BEQ     MOSCS_Loop
                ENDIF

;  Setup the PLL
                IF      (PMC_PLLR_Val:AND:PMC_MUL) != 0
                LDR     R1, =PMC_PLLR_Val
                STR     R1, [R0, #PMC_PLLR]

;  Wait until PLL is stabilized
PLL_Loop        LDR     R2, [R0, #PMC_SR]
                ANDS    R2, R2, #PMC_LOCK
                BEQ     PLL_Loop
                ENDIF

;  Select Clock
                IF      (PMC_MCKR_Val:AND:PMC_CSS) == 1     ; Main Clock Selected
                LDR     R1, =PMC_MCKR_Val
                AND     R1, #PMC_CSS
                STR     R1, [R0, #PMC_MCKR]
WAIT_Rdy1       LDR     R2, [R0, #PMC_SR]
                ANDS    R2, R2, #PMC_MCKRDY
                BEQ     WAIT_Rdy1
                LDR     R1, =PMC_MCKR_Val
                STR     R1, [R0, #PMC_MCKR]
WAIT_Rdy2       LDR     R2, [R0, #PMC_SR]
                ANDS    R2, R2, #PMC_MCKRDY
                BEQ     WAIT_Rdy2
                ELIF    (PMC_MCKR_Val:AND:PMC_CSS) == 3     ; PLL  Clock Selected
                LDR     R1, =PMC_MCKR_Val
                AND     R1, #PMC_PRES
                STR     R1, [R0, #PMC_MCKR]
WAIT_Rdy1       LDR     R2, [R0, #PMC_SR]
                ANDS    R2, R2, #PMC_MCKRDY
                BEQ     WAIT_Rdy1
                LDR     R1, =PMC_MCKR_Val
                STR     R1, [R0, #PMC_MCKR]
WAIT_Rdy2       LDR     R2, [R0, #PMC_SR]
                ANDS    R2, R2, #PMC_MCKRDY
                BEQ     WAIT_Rdy2
                ENDIF   ; Select Clock
                ENDIF   ; PMC_SETUP


; Copy Exception Vectors to Internal RAM

                IF      :DEF:RAM_INTVEC
                ADR     R8, Vectors         ; Source
                LDR     R9, =RAM_BASE       ; Destination
                LDMIA   R8!, {R0-R7}        ; Load Vectors 
                STMIA   R9!, {R0-R7}        ; Store Vectors 
                LDMIA   R8!, {R0-R7}        ; Load Handler Addresses 
                STMIA   R9!, {R0-R7}        ; Store Handler Addresses
                ENDIF


; Remap on-chip RAM to address 0

MC_BASE EQU     0xFFFFFF00      ; MC Base Address
MC_RCR  EQU     0x00            ; MC_RCR Offset

                IF      :DEF:REMAP
                LDR     R0, =MC_BASE
                MOV     R1, #1
                STR     R1, [R0, #MC_RCR]   ; Remap
                ENDIF


; Setup Stack for each mode

                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                ; MSR     CPSR_c, #Mode_USR
                IF      :DEF:__MICROLIB

                EXPORT __initial_sp

                ELSE

                ; No usr mode stack here.
                ;MOV     SP, R0
                ;SUB     SL, SP, #USR_Stack_Size

                ENDIF


; Enter the C code

                IMPORT  __main
                LDR     R0, =__main
                BX      R0

				IMPORT rt_interrupt_enter
				IMPORT rt_interrupt_leave
				IMPORT rt_thread_switch_interrupt_flag
				IMPORT rt_interrupt_from_thread
				IMPORT rt_interrupt_to_thread
				IMPORT rt_hw_trap_irq

IRQ_Handler		PROC
				EXPORT IRQ_Handler
				STMFD	sp!, {r0-r12,lr}
				BL	rt_interrupt_enter
				BL	rt_hw_trap_irq
				BL	rt_interrupt_leave

				; if rt_thread_switch_interrupt_flag set, jump to
				; rt_hw_context_switch_interrupt_do and don't return
				LDR	r0, =rt_thread_switch_interrupt_flag
				LDR	r1, [r0]
				CMP	r1, #1
				BEQ	rt_hw_context_switch_interrupt_do

				LDMFD	sp!, {r0-r12,lr}
				SUBS	pc, lr, #4
				ENDP

; /*
; * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
; */
rt_hw_context_switch_interrupt_do	PROC
				EXPORT rt_hw_context_switch_interrupt_do
				MOV		r1,  #0			; clear flag
				STR		r1,  [r0]

				LDMFD	sp!, {r0-r12,lr}; reload saved registers
				STMFD	sp!, {r0-r3}	; save r0-r3
				MOV		r1,  sp
				ADD		sp,  sp, #16	; restore sp
				SUB		r2,  lr, #4		; save old task's pc to r2

				MRS		r3,  spsr		; get cpsr of interrupt thread

				; switch to SVC mode and no interrupt
                MSR     cpsr_c, #I_Bit|F_Bit|Mode_SVC

				STMFD	sp!, {r2}		; push old task's pc
				STMFD	sp!, {r4-r12,lr}; push old task's lr,r12-r4
				MOV		r4,  r1			; Special optimised code below
				MOV		r5,  r3
				LDMFD	r4!, {r0-r3}
				STMFD	sp!, {r0-r3}	; push old task's r3-r0
				STMFD	sp!, {r5}		; push old task's cpsr
				MRS		r4,  spsr
				STMFD	sp!, {r4}		; push old task's spsr

				LDR		r4,  =rt_interrupt_from_thread
				LDR		r5,  [r4]
				STR		sp,  [r5]		; store sp in preempted tasks's TCB

				LDR		r6,  =rt_interrupt_to_thread
				LDR		r6,  [r6]
				LDR		sp,  [r6]		; get new task's stack pointer
			
				LDMFD	sp!, {r4}		; pop new task's spsr
				MSR		spsr_cxsf, r4
				LDMFD	sp!, {r4}		; pop new task's psr
				MSR		cpsr_cxsf, r4

				LDMFD	sp!, {r0-r12,lr,pc}	; pop new task's r0-r12,lr & pc
				ENDP

                IF      :DEF:__MICROLIB

                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE
; User Initial Stack & Heap
                AREA    |.text|, CODE, READONLY

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, = (Stack_Mem + IRQ_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDIF

                END
