;==============================================================================================
;	star_rvds.s	for Keil MDK 4.10
;
;   SEP4020 start up code
;
; Change Logs:
; Date           Author       Notes
; 2010-03-17     zchong 
;=============================================================================================

PMU_PLTR        EQU     0x10001000     	; PLL的稳定过渡时间
PMU_PMCR        EQU     0x10001004      ; 系统主时钟PLL的控制寄存器
PMU_PUCR        EQU     0x10001008      ; USB时钟PLL的控制寄存器
PMU_PCSR        EQU     0x1000100C      ; 内部模块时钟源供给的控制寄存器
PMU_PDSLOW      EQU     0x10001010      ; SLOW状态下时钟的分频因子
PMU_PMDR        EQU     0x10001014      ; 芯片工作模式寄存器
PMU_RCTR        EQU     0x10001018      ; Reset控制寄存器
PMU_CLRWAKUP    EQU     0x1000101C      ; WakeUp清除寄存器

RTC_CTR			EQU	 	0x1000200C		; RTC控制寄存器

INTC_IER		EQU		0x10000000		; IRQ中断允许寄存器
INTC_IMR		EQU		0x10000008		; IRQ中断屏蔽寄存器
INTC_IFSR		EQU		0x10000030		; IRQ中断最终状态寄存器
INTC_FIER		EQU 	0x100000C0		; FIQ中断允许寄存器
INTC_FIMR		EQU		0x100000C4		; FIQ中断屏蔽寄存器

EMI_CSACONF     EQU     0x11000000     	; CSA参数配置寄存器
EMI_CSECONF     EQU     0x11000010      ; CSE参数配置寄存器
EMI_CSFCONF     EQU     0x11000014      ; CSF参数配置寄存器
EMI_SDCONF1     EQU     0x11000018      ; SDRAM时序配置寄存器1
EMI_SDCONF2     EQU     0x1100001C      ; SDRAM时序配置寄存器2, SDRAM初始化用到的配置信息
EMI_REMAPCONF   EQU     0x11000020      ; 片选空间及地址映射REMAP配置寄存器

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled
NOINT     		EQU     0xc0
MASK_MODE		EQU		0x0000003F
MODE_SVC32		EQU		0x00000013

; Internal Memory Base Addresses
FLASH_BASE      EQU     0x20000000   
RAM_BASE        EQU     0x04000000
SDRAM_BASE      EQU     0x30000000

; Stack
Unused_Stack_Size  EQU     0x00000100
Svc_Stack_Size  EQU     0x00001000
Abt_Stack_Size  EQU     0x00000000
Fiq_Stack_Size  EQU     0x00000000
Irq_Stack_Size  EQU     0x00001000
Usr_Stack_Size  EQU     0x00000000

;SVC STACK
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Svc_Stack    	SPACE   Svc_Stack_Size
__initial_sp
Svc_Stack_Top

;IRQ STACK
				AREA	STACK, NOINIT, READWRITE, ALIGN=3
Irq_Stack		SPACE	Irq_Stack_Size
Irq_Stack_Top

;UNUSED STACK
				AREA	STACK, NOINIT, READWRITE, ALIGN=3
Unused_Stack	SPACE	Unused_Stack_Size
Unused_Stack_Top


; Heap
Heap_Size       EQU     0x0000100

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
				EXPORT	Heap_Mem
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                
;  Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM

;  Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.
			EXPORT Entry_Point
Entry_Point
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
SWI_Handler     B		SWI_Handler
PAbt_Handler    B       Abort_Handler
DAbt_Handler    B       Abort_Handler
FIQ_Handler     B       FIQ_Handler

Abort_Handler	PROC
				ARM
				EXPORT	Abort_Handler
DeadLoop	BHI	DeadLoop    ; Abort happened in irq mode, halt system.
				ENDP


; Reset Handler
				;IMPORT	__user_initial_stackheap
                EXPORT  Reset_Handler
Reset_Handler

;****************************************************************
;* Shutdown watchdog
;****************************************************************
				LDR		R0,=RTC_CTR	
				LDR		R1,=0x0			
				STR		R1,[R0]	

;****************************************************************
;* shutdown interrupts
;****************************************************************	
				MRS		R0, CPSR
				BIC		R0, R0, #MASK_MODE
				ORR		R0, R0, #MODE_SVC32
				ORR 	R0, R0, #I_Bit
				ORR 	R0, R0, #F_Bit
				MSR		CPSR_c, r0
			
				LDR		R0,=INTC_IER			
				LDR		R1,=0x0 	
				STR		R1,[R0]
				LDR		R0,=INTC_IMR
				LDR		R1,=0xFFFFFFFF			
				STR		R1,[R0]	
			
				LDR		R0,=INTC_FIER			
				LDR		R1,=0x0 	
				STR		R1,[R0]
				LDR		R0,=INTC_FIMR
				LDR		R1,=0x0F				
				STR		R1,[R0]

;****************************************************************
;* Initialize Stack Pointer
;****************************************************************
			
			    LDR		SP, =Svc_Stack_Top	;init SP_svc
				
			    MOV		R4, #0xD2			;chmod to irq and init SP_irq
			    MSR		cpsr_c, R4   
			    LDR		SP, =Irq_Stack_Top
				
			    MOV		R4, #0XD1			;chomod to fiq and init SP_fiq
			    MSR		cpsr_c, R4   
			    LDR		SP, =Unused_Stack_Top  
				
			    MOV		R4, #0XD7			;chomod to abt and init SP_ABT
			    MSR		cpsr_c, R4   
			    LDR		SP, =Unused_Stack_Top 
				
			    MOV		R4, #0XDB			;chomod to undf and init SP_UNDF
			    MSR		cpsr_c, R4   
			    LDR		SP, =Unused_Stack_Top 	
			    
			                                ;chomod to abt and init SP_sys
			    MOV 	R4, #0xDF           ;all interrupts disabled      
			    MSR		cpsr_c, R4       ;SYSTEM mode, @32-bit code mode     
			    LDR		SP, =Unused_Stack_Top   	
			    
			    MOV		R4, #0XD3           ;chmod to svc modle, CPSR IRQ bit  is disable
			    MSR		cpsr_c, R4
			
			
			
;****************************************************************
;* Initialize PMU & System Clock
;****************************************************************
			
			    LDR    R4,    =PMU_PCSR         ; 打所有模块时钟
			    LDR    R5,    =0x0001ffff                 
			    STR    R5,    [ R4 ] 
			
			    LDR    R4,    =PMU_PLTR         ; 配置PLL稳定过度时间为保守值50us*100M.
			    LDR    R5,    =0x00fa00fa
			    STR    R5,    [ R4 ] 
			   
			    LDR    R4,    =PMU_PMDR         ; 由SLOW模式进入NORMAL模式
			    LDR    R5,    =0x00000001                
			    STR    R5,    [ R4 ] 
			    
			    LDR    R4,    =PMU_PMCR         ; 配置系统时钟为80MHz       
			    LDR    R5,    =0x00004009       ; 400b -- 88M
			    STR    R5,    [ R4 ] 
			    
			    ;PMU_PMCR寄存器第15位需要有从低到高的翻转，才能触发PLL的时钟配置
			    LDR    R4,    =PMU_PMCR        
			    LDR    R5,    =0x0000c009               
			    STR    R5,    [ R4 ]
			    
;****************************************************************
;* 初始化EMI
;****************************************************************

				IF		:DEF:INIT_EMI

		    	LDR    	R4,    =EMI_CSACONF     ; CSA片选时序参数配置
		    	LDR    	R5,    =0x08a6a6a1                 
		    	STR    	R5,    [ R4 ]     
		 
		    	LDR    	R4,    =EMI_CSECONF     ; CSE片选时序参数配置,最保守配置
		    	LDR    	R5,    =0x8cfffff1                 
		    	STR    	R5,    [ R4 ]
		 
		    	LDR    	R4,    =EMI_SDCONF1     ; SDRAM参数配置1
		    	LDR    	R5,    =0x1E104177                 
		    	STR    	R5,    [ R4 ] 
		
		    	LDR    	R4,    =EMI_SDCONF2     ; SDRAM参数配置2
		    	LDR   	R5,    =0x80001860                 
		    	STR    	R5,    [ R4 ]
				 
				ENDIF

; Copy Exception Vectors to Internal RAM 

				IF      :DEF:RAM_INTVEC

				ADR     R8, 	Vectors         ; Source
				LDR     R9, 	=RAM_BASE       ; Destination
				LDMIA   R8!, 	{R0-R7}        	; Load Vectors 
				STMIA   R9!, 	{R0-R7}        	; Store Vectors 
				LDMIA   R8!, 	{R0-R7}        	; Load Handler Addresses 
				STMIA   R9!, 	{R0-R7}        	; Store Handler Addresses

				ENDIF

; Remap on-chip RAM to address 0

				IF      :DEF:REMAP

				LDR     R0, 	=EMI_REMAPCONF
				IF		:DEF:RAM_INTVEC
				MOV     R1, 	#0x80000000
				ELSE
				MOV		R1,		#0x0000000b
				ENDIF
				STR     R1, 	[R0, #0]   ; Remap

				ENDIF

;***************************************************************
;* Open irq interrupt											 
;***************************************************************
	
			    MRS		R4, cpsr
			    BIC		R4, R4, #0x80  		    ; set bit7 to zero
			    MSR		cpsr_c, R4

; Enter the C code
				IMPORT  __main
				LDR		R0,=__main
				BX		R0


                IMPORT rt_interrupt_enter
                IMPORT rt_interrupt_leave
                IMPORT rt_thread_switch_interrupt_flag
                IMPORT rt_interrupt_from_thread
                IMPORT rt_interrupt_to_thread
                IMPORT rt_hw_trap_irq

IRQ_Handler     PROC
                EXPORT IRQ_Handler
                STMFD   sp!, {r0-r12,lr}
                BL  rt_interrupt_enter
                BL  rt_hw_trap_irq
                BL  rt_interrupt_leave

                ; if rt_thread_switch_interrupt_flag set, jump to
                ; rt_hw_context_switch_interrupt_do and don't return
                LDR r0, =rt_thread_switch_interrupt_flag
                LDR r1, [r0]
                CMP r1, #1
                BEQ rt_hw_context_switch_interrupt_do

                LDMFD   sp!, {r0-r12,lr}
                SUBS    pc, lr, #4
                ENDP

; /*
; * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
; */
rt_hw_context_switch_interrupt_do   PROC
                EXPORT rt_hw_context_switch_interrupt_do
                MOV     r1,  #0         ; clear flag
                STR     r1,  [r0]

                LDMFD   sp!, {r0-r12,lr}; reload saved registers
                STMFD   sp!, {r0-r3}    ; save r0-r3
                MOV     r1,  sp
                ADD     sp,  sp, #16    ; restore sp
                SUB     r2,  lr, #4     ; save old task's pc to r2

                MRS     r3,  spsr       ; get cpsr of interrupt thread

                ; switch to SVC mode and no interrupt
                MSR     cpsr_c, #I_Bit :OR F_Bit :OR Mode_SVC

                STMFD   sp!, {r2}       ; push old task's pc
                STMFD   sp!, {r4-r12,lr}; push old task's lr,r12-r4
                MOV     r4,  r1         ; Special optimised code below
                MOV     r5,  r3
                LDMFD   r4!, {r0-r3}
                STMFD   sp!, {r0-r3}    ; push old task's r3-r0
                STMFD   sp!, {r5}       ; push old task's cpsr
                MRS     r4,  spsr
                STMFD   sp!, {r4}       ; push old task's spsr

                LDR     r4,  =rt_interrupt_from_thread
                LDR     r5,  [r4]
                STR     sp,  [r5]       ; store sp in preempted tasks's TCB

                LDR     r6,  =rt_interrupt_to_thread
                LDR     r6,  [r6]
                LDR     sp,  [r6]       ; get new task's stack pointer

                LDMFD   sp!, {r4}       ; pop new task's spsr
                MSR     spsr_cxsf, r4
                LDMFD   sp!, {r4}       ; pop new task's psr
                MSR     cpsr_cxsf, r4

                LDMFD   sp!, {r0-r12,lr,pc} ; pop new task's r0-r12,lr & pc
                ENDP



				ALIGN		
				IF      :DEF:__MICROLIB
		
				EXPORT  __heap_base
				EXPORT  __heap_limit
				EXPORT __initial_sp
		
				ELSE	;__MICROLIB 
; User Initial Stack & Heap
				AREA    |.text|, CODE, READONLY
		
				IMPORT  __use_two_region_memory
				EXPORT  __user_initial_stackheap
__user_initial_stackheap
		
				LDR     R0, =  Heap_Mem
				LDR     R1, = (Svc_Stack + 	   Svc_Stack_Size)
				LDR     R2, = (Heap_Mem +      Heap_Size)
				LDR     R3, = Svc_Stack
				BX      LR
				ALIGN
				ENDIF
				END
