		.org 0x200
		.global Reset_Handler,hard_fault_handler,svc_handler,pendsv_handler,systick,irq0,irq1,irq2,irq3,irq4,irq5,irq6,irq7,irq8,irq9,irq10,irq11,irq12,irq13,irq14,irq15,irq16,irq17,irq18,irq19,irq20,irq21,irq22,irq23,irq24,irq25,irq26,irq27,irq28,irq29,irq30,irq31
		
		.long


Reset_Handler:
		ldr r0,=hardware_init
		bx r0	
		.thumb_func
		
hard_fault_handler:
		ldr r0,=HARD_FAULT_IRQHandler       
		bx r0
		nop
		.thumb_func
		
svc_handler:
		ldr r0,=SVC_IRQHandler
		bx r0
		nop
		.thumb_func

pendsv_handler:
		ldr r0,=PENDSV_IRQHandler
		bx r0
		nop
		.thumb_func
systick:
		ldr r0,=SYSTICK_IRQHandler
		bx r0
		nop
		.thumb_func
irq0: 		
		mov r0,#4*0
		b isr
		.thumb_func
irq1: 		
		mov r0,#4*1
		b isr
		.thumb_func
irq2: 		
		mov r0,#4*2
		b isr
		.thumb_func
irq3: 		
		mov r0,#4*3
		b isr
		.thumb_func
irq4: 		
		mov r0,#4*4
		b isr
		.thumb_func
irq5: 		
		mov r0,#4*5
		b isr
		.thumb_func
irq6: 		
		mov r0,#4*6
		b isr
		.thumb_func
irq7: 		
		mov r0,#4*7
		b isr
		.thumb_func
irq8: 		
		mov r0,#4*8
		b isr
		.thumb_func
irq9: 		
		mov r0,#4*9
		b isr
		.thumb_func
irq10:	
		mov r0,#4*10
		b isr
		.thumb_func
irq11:	
		mov r0,#4*11
		b isr
		.thumb_func
irq12:	
		mov r0,#4*12
		b isr
		.thumb_func
irq13:	
		mov r0,#4*13
		b isr
		.thumb_func
irq14:	
		mov r0,#4*14
		b isr
		.thumb_func
irq15:	
		mov r0,#4*15
		b isr
		.thumb_func
irq16:	
		mov r0,#4*16
		b isr
		.thumb_func
irq17:	
		mov r0,#4*17
		b isr
		.thumb_func
irq18:	
		mov r0,#4*18
		b isr
		.thumb_func
irq19:	
		mov r0,#4*19
		b isr
		.thumb_func
irq20:	
		mov r0,#4*20
		b isr
		.thumb_func
irq21:	
		mov r0,#4*21
		b isr
		.thumb_func
irq22:	mov r0,#4*22
		b isr
		.thumb_func
irq23:	
		mov r0,#4*23
		b isr
		.thumb_func
irq24:	
		mov r0,#4*24
		b isr
		.thumb_func
irq25:	mov r0,#4*25
		b isr
		.thumb_func
irq26:	
		mov r0,#4*26
		b isr
		.thumb_func
irq27:	
		mov r0,#4*27
		b isr
		.thumb_func
irq28:	
		mov r0,#4*28
		b isr
		.thumb_func
irq29:	
		mov r0,#4*29
		b isr
		.thumb_func
irq30:	
		mov r0,#4*30
		b isr
		.thumb_func
irq31:	
		mov r0,#4*31
		b isr
		.thumb_func

		

isr:
		ldr r1,=isr_table
		ldr r0,[r0, r1]
		bx r0




	.align 4
isr_table:
		.long USB_IRQHandler
		.long IIC_IRQHandler
		.long QSPI_IRQHandler
		.long SPI0_IRQHandler
		.long SPI1_IRQHandler
		.long UART0_IRQHandler
		.long UART1_IRQHandler
		.long MEMCP_IRQHandler
		.long RSA_IRQHandler
		.long SCI0_IRQHandler
		.long SCI1_IRQHandler
		.long BT_IRQHandler
		.long GPIO_IRQHandler
		.long TIMER0_IRQHandler
		.long TIMER1_IRQHandler
		.long TIMER2_IRQHandler
		.long TIMER3_IRQHandler
		.long TIMER4_IRQHandler
		.long TIMER5_IRQHandler
		.long TIMER6_IRQHandler
		.long TIMER7_IRQHandler
		.long TIMER8_IRQHandler
		.long SM4_IRQHandler
		.long SEC_IRQHandler
		.long MSR_IRQHandler
		.long TRNG_IRQHandler
		.long WDT_IRQHandler
	
		.thumb
		.thumb_func
hardware_init:
		ldr	r1, =__exidx_start
		ldr	r2, =__data_start__
		ldr	r3, =__data_end__

		sub	r3, r2
		ble	.L_loop1_done

	.L_loop1:
		sub	r3, #4
		ldr	r0, [r1,r3]
		str	r0, [r2,r3]
		bgt	.L_loop1

	.L_loop1_done:



	/*  Single BSS section scheme.
	 *
	 *  The BSS section is specified by following symbols
	 *    _sbss: start of the BSS section.
	 *    _ebss: end of the BSS section.
	 *
	 *  Both addresses must be aligned to 4 bytes boundary.
	 */
		ldr	r1, =__bss_start__
		ldr	r2, =__bss_end__

		mov	r0, #0

		sub	r2, r1
		ble	.L_loop3_done

	.L_loop3:
		sub	r2, #4
		str	r0, [r1, r2]
		bgt	.L_loop3
	.L_loop3_done:
		ldr	r0,=0x12345
		ldr	r3,=0x1111
		bl	main
		
		
		.globl delay
		.syntax unified
delay:
		subs r0,#1
		bne delay
		nop
		bx lr


		




.align	1
.thumb_func
.weak	Default_Handler
.type	Default_Handler, %function

Default_Handler:
	b	.
	.size	Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
 
	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
	.endm
	
	def_irq_handler HARD_FAULT_IRQHandler
	def_irq_handler SVC_IRQHandler
	def_irq_handler PENDSV_IRQHandler
	def_irq_handler SYSTICK_IRQHandler
	def_irq_handler	USB_IRQHandler
	def_irq_handler	IIC_IRQHandler
	def_irq_handler	QSPI_IRQHandler
	def_irq_handler	SPI0_IRQHandler
	def_irq_handler	SPI1_IRQHandler
	def_irq_handler	UART0_IRQHandler
	def_irq_handler	UART1_IRQHandler
	def_irq_handler MEMCP_IRQHandler
	def_irq_handler RSA_IRQHandler
	def_irq_handler SCI0_IRQHandler
	def_irq_handler SCI1_IRQHandler
	def_irq_handler BT_IRQHandler
	def_irq_handler GPIO_IRQHandler
	def_irq_handler EXTI0_IRQHandler
	def_irq_handler EXTI1_IRQHandler
	def_irq_handler EXTI2_IRQHandler
	def_irq_handler TIMER0_IRQHandler
	def_irq_handler TIMER1_IRQHandler
	def_irq_handler TIMER2_IRQHandler
	def_irq_handler TIMER3_IRQHandler
  def_irq_handler TIMER4_IRQHandler
  def_irq_handler TIMER5_IRQHandler
  def_irq_handler TIMER6_IRQHandler
  def_irq_handler TIMER7_IRQHandler
  def_irq_handler TIMER8_IRQHandler
  def_irq_handler SM4_IRQHandler
  def_irq_handler SEC_IRQHandler
  def_irq_handler MSR_IRQHandler
  def_irq_handler TRNG_IRQHandler
  def_irq_handler WDT_IRQHandler
  



	

