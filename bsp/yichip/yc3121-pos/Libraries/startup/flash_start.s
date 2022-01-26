			AREA    |.flash_start|, CODE, READONLY  ,ALIGN=4

Reset_Handler PROC
			EXPORT  Reset_Handler
			IMPORT  __main
			LDR 	R0, =__main
			BX 		R0
			ENDP	


hard_fault_handler PROC
			EXPORT  hard_fault_handler 
            IMPORT HardFault_Handler
			ldr r0,=HardFault_Handler       
			bx r0
			nop
			ENDP
		
svc_handler PROC
			EXPORT  svc_handler         
			ldr r0,=SVC_IRQHandler
			bx r0
			nop
			ENDP

pendsv_handler PROC
			EXPORT  pendsv_handler
            IMPORT  PendSV_Handler
			ldr r0,=PendSV_Handler
			bx r0
			nop
			ENDP
		
systick 	PROC
			EXPORT systick 
            IMPORT SysTick_Handler
			ldr r0,=SysTick_Handler
			bx r0
			nop
			ENDP
		
irq0 		PROC
			EXPORT irq0
			movs r0,#4*0
			b isr
			ENDP
				
irq1 		PROC
			EXPORT irq1
			movs r0,#4*1
			b isr
			ENDP
				
irq2 		PROC
			EXPORT irq2
			movs r0,#4*2
			b isr
			ENDP
				
irq3 		PROC
			EXPORT irq3
			movs r0,#4*3
			b isr
			ENDP

irq4 		PROC
			EXPORT irq4
			movs r0,#4*4
			b isr
			ENDP
				
irq5 		PROC
			EXPORT irq5
			movs r0,#4*5
			b isr
			ENDP
				
irq6 		PROC
			EXPORT irq6
			movs r0,#4*6
			b isr
			ENDP
				
irq7 		PROC
			EXPORT irq7
			movs r0,#4*7
			b isr
			ENDP

irq8 		PROC
			EXPORT irq8
			movs r0,#4*8
			b isr
			ENDP
				
irq9 		PROC
			EXPORT irq9
			movs r0,#4*9
			b isr
			ENDP
				
irq10 		PROC
			EXPORT irq10
			movs r0,#4*10
			b isr
			ENDP
				
irq11 		PROC
			EXPORT irq11
			movs r0,#4*11
			b isr
			ENDP

irq12 		PROC
			EXPORT irq12
			movs r0,#4*12
			b isr
			ENDP
				
irq13 		PROC
			EXPORT irq13
			movs r0,#4*13
			b isr
			ENDP
				
irq14 		PROC
			EXPORT irq14
			movs r0,#4*14
			b isr
			ENDP
				
irq15 		PROC
			EXPORT irq15
			movs r0,#4*15
			b isr
			ENDP
				
irq16 		PROC
			EXPORT irq16
			movs r0,#4*16
			b isr
			ENDP
				
irq17 		PROC
			EXPORT irq17
			movs r0,#4*17
			b isr
			ENDP
				
irq18 		PROC
			EXPORT irq18
			movs r0,#4*18
			b isr
			ENDP
				
irq19 		PROC
			EXPORT irq19
			movs r0,#4*19
			b isr
			ENDP

irq20 		PROC
			EXPORT irq20
			movs r0,#4*20
			b isr
			ENDP
				
irq21 		PROC
			EXPORT irq21
			movs r0,#4*21
			b isr
			ENDP
				
irq22 		PROC
			EXPORT irq22
			movs r0,#4*22
			b isr
			ENDP
				
irq23 		PROC
			EXPORT irq23
			movs r0,#4*23
			b isr
			ENDP

irq24 		PROC
			EXPORT irq24
			movs r0,#4*24
			b isr
			ENDP
				
irq25 		PROC
			EXPORT irq25
			movs r0,#4*25
			b isr
			ENDP
				
irq26 		PROC
			EXPORT irq26
			movs r0,#4*26
			b isr
			ENDP
				
irq27 		PROC
			EXPORT irq27
			movs r0,#4*27
			b isr
			ENDP

irq28 		PROC
			EXPORT irq28
			movs r0,#4*28
			b isr
			ENDP
				
irq29 		PROC
			EXPORT irq29
			movs r0,#4*29
			b isr
			ENDP
				
irq30		PROC
			EXPORT irq30
			movs r0,#4*30
			b isr
			ENDP
				
irq31 		PROC
			EXPORT irq31
			movs r0,#4*31
			b isr
			ENDP				
				

isr    		PROC
			ldr r1,=isr_table
			ldr r0,[r0, r1]
			bx r0
			ENDP
					
				ALIGN	
NMI_IRQHandler  		PROC
						EXPORT      NMI_IRQHandler				[WEAK]
						B	.
						ENDP

HARD_FAULT_IRQHandler   PROC
						EXPORT      HARD_FAULT_IRQHandler		[WEAK]
						B	.
						ENDP

SVC_IRQHandler   		PROC
						EXPORT      SVC_IRQHandler				[WEAK]
						B	.
						ENDP

PENDSV_IRQHandler   	PROC
						EXPORT      PENDSV_IRQHandler			[WEAK]
						B	.
						ENDP
							
SYSTICK_IRQHandler   	PROC
						EXPORT      SYSTICK_IRQHandler			[WEAK]
						B	.
						ENDP
					
EXTI0_IRQHandler   		PROC
						EXPORT      EXTI0_IRQHandler			[WEAK]
						B	.
						ENDP
							
EXTI1_IRQHandler   		PROC
						EXPORT      EXTI1_IRQHandler			[WEAK]
						B	.
						ENDP
							
EXTI2_IRQHandler   		PROC
						EXPORT      EXTI2_IRQHandler			[WEAK]
						B	.
						ENDP
							
EXTI3_IRQHandler   		PROC
						EXPORT      EXTI3_IRQHandler			[WEAK]
						B	.
						ENDP
							
EXTI4_IRQHandler   		PROC
						EXPORT      EXTI4_IRQHandler			[WEAK]
						B	.
						ENDP
							
EXTI5_IRQHandler   		PROC
						EXPORT      EXTI5_IRQHandler			[WEAK]
						B	.
						ENDP	
					
Default_Handler PROC
; ToDo:  Add here the export definition for the device specific external interrupts handler
                EXPORT		USB_IRQHandler	 	[WEAK]
				EXPORT		IIC_IRQHandler   	[WEAK]
				EXPORT		QSPI_IRQHandler  	[WEAK]
				EXPORT		SPI0_IRQHandler  	[WEAK]
				EXPORT		SPI1_IRQHandler  	[WEAK]
				EXPORT		UART0_IRQHandler 	[WEAK]
				EXPORT		UART1_IRQHandler 	[WEAK]
				EXPORT 		MEMCP_IRQHandler 	[WEAK]				
				EXPORT		RSA_IRQHandler   	[WEAK]
				EXPORT		SCI0_IRQHandler  	[WEAK]
				EXPORT		SCI1_IRQHandler  	[WEAK]
				EXPORT		BT_IRQHandler 		[WEAK]
				EXPORT		GPIO_IRQHandler    	[WEAK]
				EXPORT		TIMER0_IRQHandler	[WEAK]
				EXPORT		TIMER1_IRQHandler	[WEAK]
				EXPORT		TIMER2_IRQHandler	[WEAK]
				EXPORT		TIMER3_IRQHandler	[WEAK]
				EXPORT		TIMER4_IRQHandler	[WEAK]
				EXPORT		TIMER5_IRQHandler	[WEAK]
				EXPORT		TIMER6_IRQHandler	[WEAK]
				EXPORT		TIMER7_IRQHandler	[WEAK]
				EXPORT		TIMER8_IRQHandler 	[WEAK]
				EXPORT		SM4_IRQHandler   	[WEAK]	
				EXPORT		SEC_IRQHandler		[WEAK]	
				EXPORT		MSR_IRQHandler		[WEAK]	
				EXPORT		TRNG_IRQHandler		[WEAK]	
				EXPORT 		WDT_IRQHandler		[WEAK]

; ToDo:  Add here the names for the device specific external interrupts handler
USB_IRQHandler	 	
IIC_IRQHandler   	
QSPI_IRQHandler  	
SPI0_IRQHandler  	
SPI1_IRQHandler  	
UART0_IRQHandler 	
UART1_IRQHandler 	
MEMCP_IRQHandler 	
RSA_IRQHandler   	
SCI0_IRQHandler  	
SCI1_IRQHandler  	
BT_IRQHandler 		
GPIO_IRQHandler    	
TIMER0_IRQHandler	
TIMER1_IRQHandler	
TIMER2_IRQHandler	
TIMER3_IRQHandler	
TIMER4_IRQHandler	
TIMER5_IRQHandler	
TIMER6_IRQHandler	
TIMER7_IRQHandler	
TIMER8_IRQHandler 	
SM4_IRQHandler   	
SEC_IRQHandler		
MSR_IRQHandler		
TRNG_IRQHandler		
WDT_IRQHandler		
                B       .
                ENDP
					
					
					
			EXPORT isr_table				
isr_table	DCD     USB_IRQHandler	 
			DCD 	IIC_IRQHandler   
			DCD 	QSPI_IRQHandler  
			DCD 	SPI0_IRQHandler  
			DCD 	SPI1_IRQHandler  
			DCD 	UART0_IRQHandler 
			DCD 	UART1_IRQHandler 
			DCD 	MEMCP_IRQHandler 
			DCD 	RSA_IRQHandler   
			DCD 	SCI0_IRQHandler  
			DCD 	SCI1_IRQHandler  
			DCD 	BT_IRQHandler 
			DCD 	GPIO_IRQHandler         
			DCD 	TIMER0_IRQHandler
			DCD 	TIMER1_IRQHandler
			DCD 	TIMER2_IRQHandler
			DCD 	TIMER3_IRQHandler
			DCD 	TIMER4_IRQHandler
			DCD 	TIMER5_IRQHandler
			DCD 	TIMER6_IRQHandler
			DCD 	TIMER7_IRQHandler
			DCD 	TIMER8_IRQHandler 
			DCD 	SM4_IRQHandler   
			DCD 	SEC_IRQHandler
			DCD 	MSR_IRQHandler
			DCD 	TRNG_IRQHandler
			DCD 	WDT_IRQHandler
			END
			
			



		


