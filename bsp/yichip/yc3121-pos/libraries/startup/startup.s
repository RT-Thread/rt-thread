Stack_Size      EQU     0x0000100

                AREA    STACK, NOINIT, READWRITE, ALIGN=4
Stack_Mem       SPACE   Stack_Size
__initial_sp    EQU		0x30000


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000
                AREA    HEAP, NOINIT, READWRITE, ALIGN=4
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB

				
; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
				IMPORT systick	
				IMPORT irq0 
				IMPORT irq1 
				IMPORT irq2 
				IMPORT irq3 
				IMPORT irq4 
				IMPORT irq5 
				IMPORT irq6 
				IMPORT irq7 
				IMPORT irq8 
				IMPORT irq9 
				IMPORT irq10
				IMPORT irq11
				IMPORT irq12
				IMPORT irq13
				IMPORT irq14
				IMPORT irq15
				IMPORT irq16
				IMPORT irq17
				IMPORT irq18
				IMPORT irq19
				IMPORT irq20
				IMPORT irq21
				IMPORT irq22
				IMPORT irq23
				IMPORT irq24
				IMPORT irq25
				IMPORT irq26
				IMPORT irq27
				IMPORT irq28
				IMPORT irq29
				IMPORT irq30
				IMPORT irq31
				IMPORT hard_fault_handler
					
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     reset_handler             ; Reset Handler
                DCD     nmi_handler               ; NMI Handler
                DCD     hard_fault_handler        ; Hard Fault Handler					
				DCD		0						  ;	
				DCD		0						  ;
				DCD		0						  ;
				DCD		0						  ;
				DCD		0						  ;
				DCD		0						  ;
				DCD		0						  ;
				DCD		0						  ;
				DCD		0						  ;
				DCD		0						  ;
				DCD		0						  ;
				DCD		systick					  ;	
				DCD		irq0                       ;
				DCD		irq1                       ;
				DCD		irq2                       ;
				DCD		irq3                       ;
				DCD		irq4                       ;
				DCD		irq5                       ;
				DCD		irq6                       ;
				DCD		irq7                       ;
				DCD		irq8                       ;
				DCD		irq9                       ;
				DCD		irq10                      ;
				DCD		irq11                      ;
				DCD		irq12                      ;
				DCD		irq13                      ;
				DCD		irq14                      ;
				DCD		irq15                      ;
				DCD		irq16                      ;
				DCD		irq17                      ;
				DCD		irq18                      ;
				DCD		irq19                      ;
				DCD		irq20                      ;
				DCD		irq21                      ;
				DCD		irq22                      ;
				DCD		irq23                      ;
				DCD		irq24                      ;
				DCD		irq25                      ;
				DCD		irq26                      ;
				DCD		irq27                      ;
				DCD		irq28                      ;
				DCD		irq29                      ;
				DCD		irq30                      ;
				DCD		irq31                      ;
__Vectors_End					
					
__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY	,ALIGN=4				
					
					
					
; Reset Handler

reset_handler   PROC
                EXPORT  reset_handler             [WEAK]
                IMPORT  Reset_Handler
;				bl		Reset_Handler
;				movs	r0,#0x3
				
				LDR 	R0, =Reset_Handler
				BX 		R0
				nop
                ENDP					
										
					
		
delay			PROC
				EXPORT delay
				subs r0,#1
				bne delay
				nop
				bx lr
				ENDP

nmi_handler		PROC
				EXPORT  nmi_handler             [WEAK]
				b nmi_handler
				ENDP
					
				ALIGN

               AREA  |.INIT_STACK_HEAP|, CODE,READONLY,ALIGN=4
; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
					
                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, = __initial_sp
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF
					
				END		