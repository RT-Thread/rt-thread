;/*****************************************************************************/
;/* STARTUP.S: Startup file for Philips LPC2000                               */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */ 
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2007 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


;/*
; *  The STARTUP.S code is executed after CPU Reset. This file may be 
; *  translated with the following SET symbols. In uVision these SET 
; *  symbols are entered under Options - ASM - Define.
; *
; *  REMAP: when set the startup code initializes the register MEMMAP 
; *  which overwrites the settings of the CPU configuration pins. The 
; *  startup and interrupt vectors are remapped from:
; *     0x00000000  default setting (not remapped)
; *     0x80000000  when EXTMEM_MODE is used
; *     0x40000000  when RAM_MODE is used
; *
; *  EXTMEM_MODE: when set the device is configured for code execution
; *  from external memory starting at address 0x80000000.
; *
; *  RAM_MODE: when set the device is configured for code execution
; *  from on-chip RAM starting at address 0x40000000.
; *
; *  EXTERNAL_MODE: when set the PIN2SEL values are written that enable
; *  the external BUS at startup.
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


; VPBDIV definitions
VPBDIV          EQU     0xE01FC100      ; VPBDIV Address

;// <e> VPBDIV Setup
;// <i> Peripheral Bus Clock Rate
;//   <o1.0..1>   VPBDIV: VPB Clock
;//               <0=> VPB Clock = CPU Clock / 4
;//               <1=> VPB Clock = CPU Clock
;//               <2=> VPB Clock = CPU Clock / 2
;//   <o1.4..5>   XCLKDIV: XCLK Pin
;//               <0=> XCLK Pin = CPU Clock / 4
;//               <1=> XCLK Pin = CPU Clock
;//               <2=> XCLK Pin = CPU Clock / 2
;// </e>
VPBDIV_SETUP    EQU     0
VPBDIV_Val      EQU     0x00000000


; Phase Locked Loop (PLL) definitions
PLL_BASE        EQU     0xE01FC080      ; PLL Base Address
PLLCON_OFS      EQU     0x00            ; PLL Control Offset
PLLCFG_OFS      EQU     0x04            ; PLL Configuration Offset
PLLSTAT_OFS     EQU     0x08            ; PLL Status Offset
PLLFEED_OFS     EQU     0x0C            ; PLL Feed Offset
PLLCON_PLLE     EQU     (1<<0)          ; PLL Enable
PLLCON_PLLC     EQU     (1<<1)          ; PLL Connect
PLLCFG_MSEL     EQU     (0x1F<<0)       ; PLL Multiplier
PLLCFG_PSEL     EQU     (0x03<<5)       ; PLL Divider
PLLSTAT_PLOCK   EQU     (1<<10)         ; PLL Lock Status

;// <e> PLL Setup
;//   <o1.0..4>   MSEL: PLL Multiplier Selection
;//               <1-32><#-1>
;//               <i> M Value
;//   <o1.5..6>   PSEL: PLL Divider Selection
;//               <0=> 1   <1=> 2   <2=> 4   <3=> 8
;//               <i> P Value
;// </e>
PLL_SETUP       EQU     1
PLLCFG_Val      EQU     0x00000024


; Memory Accelerator Module (MAM) definitions
MAM_BASE        EQU     0xE01FC000      ; MAM Base Address
MAMCR_OFS       EQU     0x00            ; MAM Control Offset
MAMTIM_OFS      EQU     0x04            ; MAM Timing Offset

;// <e> MAM Setup
;//   <o1.0..1>   MAM Control
;//               <0=> Disabled
;//               <1=> Partially Enabled
;//               <2=> Fully Enabled
;//               <i> Mode
;//   <o2.0..2>   MAM Timing
;//               <0=> Reserved  <1=> 1   <2=> 2   <3=> 3
;//               <4=> 4         <5=> 5   <6=> 6   <7=> 7
;//               <i> Fetch Cycles
;// </e>
MAM_SETUP       EQU     1
MAMCR_Val       EQU     0x00000002
MAMTIM_Val      EQU     0x00000004


; External Memory Controller (EMC) definitions
EMC_BASE        EQU     0xFFE00000      ; EMC Base Address
BCFG0_OFS       EQU     0x00            ; BCFG0 Offset
BCFG1_OFS       EQU     0x04            ; BCFG1 Offset
BCFG2_OFS       EQU     0x08            ; BCFG2 Offset
BCFG3_OFS       EQU     0x0C            ; BCFG3 Offset

;// <e> External Memory Controller (EMC)
EMC_SETUP       EQU     0

;//   <e> Bank Configuration 0 (BCFG0)
;//     <o1.0..3>   IDCY: Idle Cycles <0-15>
;//     <o1.5..9>   WST1: Wait States 1 <0-31>
;//     <o1.11..15> WST2: Wait States 2 <0-31>
;//     <o1.10>     RBLE: Read Byte Lane Enable
;//     <o1.26>     WP: Write Protect
;//     <o1.27>     BM: Burst ROM
;//     <o1.28..29> MW: Memory Width  <0=>  8-bit  <1=> 16-bit
;//                                   <2=> 32-bit  <3=> Reserved
;//   </e>
BCFG0_SETUP EQU         0
BCFG0_Val   EQU         0x0000FBEF

;//   <e> Bank Configuration 1 (BCFG1)
;//     <o1.0..3>   IDCY: Idle Cycles <0-15>
;//     <o1.5..9>   WST1: Wait States 1 <0-31>
;//     <o1.11..15> WST2: Wait States 2 <0-31>
;//     <o1.10>     RBLE: Read Byte Lane Enable
;//     <o1.26>     WP: Write Protect
;//     <o1.27>     BM: Burst ROM
;//     <o1.28..29> MW: Memory Width  <0=>  8-bit  <1=> 16-bit
;//                                   <2=> 32-bit  <3=> Reserved
;//   </e>
BCFG1_SETUP EQU         0
BCFG1_Val   EQU         0x0000FBEF

;//   <e> Bank Configuration 2 (BCFG2)
;//     <o1.0..3>   IDCY: Idle Cycles <0-15>
;//     <o1.5..9>   WST1: Wait States 1 <0-31>
;//     <o1.11..15> WST2: Wait States 2 <0-31>
;//     <o1.10>     RBLE: Read Byte Lane Enable
;//     <o1.26>     WP: Write Protect
;//     <o1.27>     BM: Burst ROM
;//     <o1.28..29> MW: Memory Width  <0=>  8-bit  <1=> 16-bit
;//                                   <2=> 32-bit  <3=> Reserved
;//   </e>
BCFG2_SETUP EQU         0
BCFG2_Val   EQU         0x0000FBEF

;//   <e> Bank Configuration 3 (BCFG3)
;//     <o1.0..3>   IDCY: Idle Cycles <0-15>
;//     <o1.5..9>   WST1: Wait States 1 <0-31>
;//     <o1.11..15> WST2: Wait States 2 <0-31>
;//     <o1.10>     RBLE: Read Byte Lane Enable
;//     <o1.26>     WP: Write Protect
;//     <o1.27>     BM: Burst ROM
;//     <o1.28..29> MW: Memory Width  <0=>  8-bit  <1=> 16-bit
;//                                   <2=> 32-bit  <3=> Reserved
;//   </e>
BCFG3_SETUP EQU         0
BCFG3_Val   EQU         0x0000FBEF

;// </e> End of EMC


; External Memory Pins definitions
PINSEL2         EQU     0xE002C014      ; PINSEL2 Address
PINSEL2_Val     EQU     0x0E6149E4      ; CS0..3, OE, WE, BLS0..3, 
                                        ; D0..31, A2..23, JTAG Pins


                PRESERVE8
                

; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM


; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

Vectors         LDR     PC, Reset_Addr         
                LDR     PC, Undef_Addr
                LDR     PC, SWI_Addr
                LDR     PC, PAbt_Addr
                LDR     PC, DAbt_Addr
                NOP                            ; Reserved Vector 
               	LDR     PC, IRQ_Addr
                LDR     PC, FIQ_Addr

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


; Setup External Memory Pins
                IF      :DEF:EXTERNAL_MODE
                LDR     R0, =PINSEL2
                LDR     R1, =PINSEL2_Val
                STR     R1, [R0]
                ENDIF


; Setup External Memory Controller
                IF      EMC_SETUP <> 0
                LDR     R0, =EMC_BASE

                IF      BCFG0_SETUP <> 0
                LDR     R1, =BCFG0_Val
                STR     R1, [R0, #BCFG0_OFS]
                ENDIF

                IF      BCFG1_SETUP <> 0
                LDR     R1, =BCFG1_Val
                STR     R1, [R0, #BCFG1_OFS]
                ENDIF

                IF      BCFG2_SETUP <> 0
                LDR     R1, =BCFG2_Val
                STR     R1, [R0, #BCFG2_OFS]
                ENDIF

                IF      BCFG3_SETUP <> 0
                LDR     R1, =BCFG3_Val
                STR     R1, [R0, #BCFG3_OFS]
                ENDIF

                ENDIF   ; EMC_SETUP


; Setup VPBDIV
                IF      VPBDIV_SETUP <> 0
                LDR     R0, =VPBDIV
                LDR     R1, =VPBDIV_Val
                STR     R1, [R0]
                ENDIF


; Setup PLL
                IF      PLL_SETUP <> 0
                LDR     R0, =PLL_BASE
                MOV     R1, #0xAA
                MOV     R2, #0x55

;  Configure and Enable PLL
                MOV     R3, #PLLCFG_Val
                STR     R3, [R0, #PLLCFG_OFS] 
                MOV     R3, #PLLCON_PLLE
                STR     R3, [R0, #PLLCON_OFS]
                STR     R1, [R0, #PLLFEED_OFS]
                STR     R2, [R0, #PLLFEED_OFS]

;  Wait until PLL Locked
PLL_Loop        LDR     R3, [R0, #PLLSTAT_OFS]
                ANDS    R3, R3, #PLLSTAT_PLOCK
                BEQ     PLL_Loop

;  Switch to PLL Clock
                MOV     R3, #(PLLCON_PLLE:OR:PLLCON_PLLC)
                STR     R3, [R0, #PLLCON_OFS]
                STR     R1, [R0, #PLLFEED_OFS]
                STR     R2, [R0, #PLLFEED_OFS]
                ENDIF   ; PLL_SETUP


; Setup MAM
                IF      MAM_SETUP <> 0
                LDR     R0, =MAM_BASE
                MOV     R1, #MAMTIM_Val
                STR     R1, [R0, #MAMTIM_OFS] 
                MOV     R1, #MAMCR_Val
                STR     R1, [R0, #MAMCR_OFS] 
                ENDIF   ; MAM_SETUP


; Memory Mapping (when Interrupt Vectors are in RAM)
MEMMAP          EQU     0xE01FC040      ; Memory Mapping Control
                IF      :DEF:REMAP
                LDR     R0, =MEMMAP
                IF      :DEF:EXTMEM_MODE
                MOV     R1, #3
                ELIF    :DEF:RAM_MODE
                MOV     R1, #2
                ELSE
                MOV     R1, #1
                ENDIF
                STR     R1, [R0]
                ENDIF


; Initialise Interrupt System
;  ...


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
                ; SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
				; RT-Thread does not use user mode
                ; MSR     CPSR_c, #Mode_USR
                IF      :DEF:__MICROLIB

                EXPORT __initial_sp

                ELSE

                ; MOV     SP, R0
                ; SUB     SL, SP, #USR_Stack_Size

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
				IMPORT rt_hw_context_switch_interrupt_do

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
                LDR     R1, =(Stack_Mem + USR_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDIF

                END
