;==============================================================================================
;	star_rvds.s	for Keil MDK 4.10
;
;   SEP4020 start up code
;
; Change Logs:
; Date           Author       Notes
; 2010-03-17     zchong 
;=============================================================================================

;

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

; Stack
UND_Stack_Size  EQU     0x00000000
SVC_Stack_Size  EQU     0x00000400
ABT_Stack_Size  EQU     0x00000000
FIQ_Stack_Size  EQU     0x00000000
IRQ_Stack_Size  EQU     0x00000100
USR_Stack_Size  EQU     0x00000000

ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)

                AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top

; Heap
Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


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

;****************************************************************
;* 关闭看门狗
;****************************************************************
		LDR		R0,=RTC_CTR	
		LDR		R1,=0x0			
		STR		R1,[R0]	

;****************************************************************
;* 关中断
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
;* 初始化PMU模块, 配置系统时钟
;****************************************************************
		LDR	   	R4,    =PMU_PCSR        ; 打开所有模块时钟
		LDR    	R5,    =0x0001ffff                 
  	  	STR    	R5,    [ R4 ] 

		LDR    	R4,    =PMU_PLTR        ; 配置PLL稳定过度时间为保守值50us*100M.
		LDR    	R5,    =0x00fa00fa
		STR    	R5,    [ R4 ] 
   
    	LDR    	R4,    =PMU_PMDR        ; 由SLOW模式进入NORMAL模式
	   	LDR    	R5,    =0x00000001                
    	STR    	R5,    [ R4 ] 
    
    	LDR    	R4,    =PMU_PMCR        ; 配置系统时钟为72MHz 2*Fin*9=2*4*9=72MHz
    	LDR    	R5,    =0x00004009      ; MFCN 0->1 trigger PLL to reconfigure event when mode isn''t SLOW        
    	STR    	R5,    [ R4 ]
    	LDR    	R4,    =PMU_PMCR        ; 
    	LDR    	R5,    =0x0000c009                 
    	STR    	R5,    [ R4 ]
    
;****************************************************************
;* 初始化EMI
;****************************************************************
;    	LDR    	R4,    =EMI_CSACONF     ; CSA片选时序参数配置
;    	LDR    	R5,    =0x08a6a6a1                 
;    	STR    	R5,    [ R4 ]     
 
;    	LDR    	R4,    =EMI_CSECONF     ; CSE片选时序参数配置,最保守配置
;    	LDR    	R5,    =0x8cfffff1                 
;    	STR    	R5,    [ R4 ]
 
;    	LDR    	R4,    =EMI_SDCONF1     ; SDRAM参数配置1
;    	LDR    	R5,    =0x1E104177                 
;    	STR    	R5,    [ R4 ] 

;    	LDR    	R4,    =EMI_SDCONF2     ; SDRAM参数配置2
;    	LDR   	R5,    =0x80001860                 
;    	STR    	R5,    [ R4 ]


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
		MOV     R1, 	#0x80000000
		STR     R1, 	[R0, #0]   ; Remap
	ENDIF


; Setup Stack for each mode

		LDR     R0, 	=Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
		MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
		MOV     SP, 	R0
		SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
		MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
		MOV     SP, 	R0
		SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
		MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
		MOV     SP, 	R0
		SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
		MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
		MOV     SP, 	R0
		SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
		MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
		MOV     SP, 	R0
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
		LDR     R0, 	=__main
		BX      R0

	IMPORT rt_interrupt_enter
	IMPORT rt_interrupt_leave
	IMPORT rt_thread_switch_interrput_flag
	IMPORT rt_interrupt_from_thread
	IMPORT rt_interrupt_to_thread
	IMPORT rt_hw_trap_irq
	IMPORT rt_hw_trap_abort
	IMPORT rt_interrupt_nest

Abort_Handler	PROC
		EXPORT	Abort_Handler
		STMFD	SP!, 	{R0-R12,LR}
		LDR		R0, 	=rt_interrupt_nest
		LDR		R1, 	[R0]
		CMP		R1, 	#0
DeadLoop	BHI	DeadLoop    ; Abort happened in irq mode, halt system.
		BL		rt_interrupt_enter
		BL		rt_hw_trap_abort
		BL		rt_interrupt_leave
		B		SWITCH
				ENDP
				
IRQ_Handler		PROC
		EXPORT IRQ_Handler
		STMFD	SP!,	{R0-R12,LR}
		BL		rt_interrupt_enter
		BL		rt_hw_trap_irq
		BL		rt_interrupt_leave

				; if rt_thread_switch_interrput_flag set, jump to
				; rt_hw_context_switch_interrupt_do and don't return
SWITCH			
		LDR		R0, 	=rt_thread_switch_interrput_flag
		LDR		R1, 	[R0]
		CMP		R1, 	#1
		BEQ		rt_hw_context_switch_interrupt_do

		LDMFD	SP!, 	{R0-R12,LR}
		SUBS	PC, 	LR, #4
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
		MSR     cpsr_c, #I_Bit:OR:F_Bit:OR:Mode_SVC

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
