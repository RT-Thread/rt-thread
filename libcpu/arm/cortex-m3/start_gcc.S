/******************************************************************//**
 * @file 		start_gcc.S
 * @brief 	Context switch functions
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2010-12-21 	onelife 		Initial creation for EFM32
 *********************************************************************/
 
/******************************************************************//**
* @addtogroup cortex-m3
* @{
*********************************************************************/

	.syntax unified
	.cpu 	cortex-m3
	.fpu 	softvfp
	.thumb

/* start address for the initialization values of the .data section. 
defined in linker script */
	.word _sidata
/* start address for the .data section. defined in linker script */  
	.word _sdata
/* end address for the .data section. defined in linker script */
	.word _edata
/* start address for the .bss section. defined in linker script */
	.word _sbss
/* end address for the .bss section. defined in linker script */
	.word _ebss


/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/    
  .section .isr_vector, "a", %progbits
  .global g_pfnVectors
  .type g_pfnVectors, %object
g_pfnVectors:
  .word  Initial_spTop
  .word  Reset_Handler
  .word  NMI_Handler
  .word  rt_hw_hard_fault
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  rt_hw_pend_sv
  .word  rt_hw_timer_handler
  /* External Interrupts */
  .word  DMA_IRQHandler				/* 0: DMA Interrupt (efm32_dma.c) */
  .word  GPIO_EVEN_IRQHandler		/* 1: GPIO_EVEN Interrupt */
  .word  TIMER0_IRQHandler			/* 2: TIMER0 Interrupt */
  .word  USART0_RX_IRQHandler		/* 3: USART0_RX Interrupt */
  .word  USART0_TX_IRQHandler		/* 4: USART0_TX Interrupt */
  .word  ACMP0_IRQHandler			/* 5: ACMP0 Interrupt */
  .word  ADC0_IRQHandler			/* 6: ADC0 Interrupt */
  .word  DAC0_IRQHandler			/* 7: DAC0 Interrupt */
  .word  I2C0_IRQHandler			/* 8: I2C0 Interrupt */
  .word  GPIO_ODD_IRQHandler		/* 9: GPIO_ODD Interrupt */
  .word  TIMER1_IRQHandler			/* 10: TIMER1 Interrupt */
  .word  TIMER2_IRQHandler			/* 11: TIMER2 Interrupt */
  .word  USART1_RX_IRQHandler		/* 12: USART1_RX Interrupt */
  .word  USART1_TX_IRQHandler		/* 13: USART1_TX Interrupt */
  .word  USART2_RX_IRQHandler		/* 14: USART2_RX Interrupt */
  .word  USART2_TX_IRQHandler		/* 15: USART2_TX Interrupt */
  .word  UART0_RX_IRQHandler		/* 16: UART0_RX Interrupt */
  .word  UART0_TX_IRQHandler		/* 17: UART0_TX Interrupt */
  .word  LEUART0_IRQHandler			/* 18: LEUART0 Interrupt */
  .word  LEUART1_IRQHandler			/* 19: LEUART1 Interrupt */
  .word  LETIMER0_IRQHandler		/* 20: LETIMER0 Interrupt */
  .word  PCNT0_IRQHandler			/* 21: PCNT0 Interrupt */
  .word  PCNT1_IRQHandler			/* 22: PCNT1 Interrupt */
  .word  PCNT2_IRQHandler			/* 23: PCNT2 Interrupt */
  .word  RTC_IRQHandler				/* 24: RTC Interrupt */
  .word  CMU_IRQHandler				/* 25: CMU Interrupt */
  .word  VCMP_IRQHandler			/* 26: VCMP Interrupt */
  .word  LCD_IRQHandler				/* 27: LCD Interrupt */
  .word  MSC_IRQHandler				/* 28: MSC Interrupt */
  .word  AES_IRQHandler				/* 29: AES Interrupt */
  .size	g_pfnVectors, .-g_pfnVectors

/**
 * @brief  Top of stack pointer
*/
	.section .bss.init
	.equ Stack_Size, 0x00000200
	.space Stack_Size
Initial_spTop:

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval  None
*/
	.thumb
	.thumb_func
	.section .text.Reset_Handler, "ax", %progbits
	.weak Reset_Handler
	.global Reset_Handler
	.type Reset_Handler, %function
Reset_Handler:  
	/* restore original stack pointer */  
	ldr  r0, =Initial_spTop
	msr  msp, r0
	/* Copy the data segment initializers from flash to SRAM */  
	movs  r1, #0
	b  LoopCopyDataInit

CopyDataInit:
	ldr  r3, =_sidata
	ldr  r3, [r3, r1]
	str  r3, [r0, r1]
	adds  r1, r1, #4
    
LoopCopyDataInit:
	ldr  r0, =_sdata
	ldr  r3, =_edata
	adds  r2, r0, r1
	cmp  r2, r3
	bcc  CopyDataInit
	ldr  r2, =_sbss
	b  LoopFillZerobss

/* Zero fill the bss segment. */  
FillZerobss:
	movs  r3, #0
	str  r3, [r2], #4

LoopFillZerobss:
	ldr  r3, = _ebss
	cmp  r2, r3
	bcc  FillZerobss
	/* Call the application's entry point.*/
	bl  main
	bx  lr    
	.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param None     
 * @retval None       
*/
	.thumb
	.thumb_func
	.section .text.Default_Handler, "ax", %progbits
	.global Default_Handler
	.type Default_Handler, %function
Default_Handler:
Infinite_Loop:
	b  Infinite_Loop
	.size Default_Handler, .-Default_Handler

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler. 
* As they are weak aliases, any function with the same name will override 
* this definition.
*
*******************************************************************************/
  .weak			NMI_Handler
  .thumb_set	NMI_Handler, Default_Handler
  
  .weak			MemManage_Handler
  .thumb_set	MemManage_Handler, Default_Handler
  
  .weak			BusFault_Handler
  .thumb_set	BusFault_Handler, Default_Handler

  .weak			UsageFault_Handler
  .thumb_set	UsageFault_Handler, Default_Handler

  .weak			SVC_Handler
  .thumb_set	SVC_Handler, Default_Handler

  .weak			DebugMon_Handler
  .thumb_set	DebugMon_Handler ,Default_Handler
  
  .weak  		DMA_IRQHandler
  .thumb_set 	DMA_IRQHandler, Default_Handler
  
  .weak  		GPIO_EVEN_IRQHandler
  .thumb_set 	GPIO_EVEN_IRQHandler, Default_Handler
  
  .weak  		TIMER0_IRQHandler
  .thumb_set 	TIMER0_IRQHandler, Default_Handler

  .weak  		USART0_RX_IRQHandler
  .thumb_set 	USART0_RX_IRQHandler, Default_Handler

  .weak  		USART0_TX_IRQHandler
  .thumb_set 	USART0_TX_IRQHandler, Default_Handler

  .weak  		ACMP0_IRQHandler
  .thumb_set 	ACMP0_IRQHandler, Default_Handler

  .weak  		ADC0_IRQHandler
  .thumb_set 	ADC0_IRQHandler, Default_Handler

  .weak  		DAC0_IRQHandler
  .thumb_set 	DAC0_IRQHandler, Default_Handler

  .weak  		I2C0_IRQHandler
  .thumb_set 	I2C0_IRQHandler, Default_Handler

  .weak  		GPIO_ODD_IRQHandler
  .thumb_set 	GPIO_ODD_IRQHandler, Default_Handler

  .weak  		TIMER1_IRQHandler
  .thumb_set 	TIMER1_IRQHandler, Default_Handler

  .weak  		TIMER2_IRQHandler
  .thumb_set 	TIMER2_IRQHandler, Default_Handler

  .weak  		USART1_RX_IRQHandler
  .thumb_set 	USART1_RX_IRQHandler, Default_Handler

  .weak  		USART1_TX_IRQHandler
  .thumb_set 	USART1_TX_IRQHandler, Default_Handler

  .weak  		USART2_RX_IRQHandler
  .thumb_set 	USART2_RX_IRQHandler, Default_Handler

  .weak  		USART2_TX_IRQHandler
  .thumb_set 	USART2_TX_IRQHandler, Default_Handler

  .weak  		UART0_RX_IRQHandler
  .thumb_set 	UART0_RX_IRQHandler, Default_Handler
  
  .weak  		UART0_TX_IRQHandler
  .thumb_set 	UART0_TX_IRQHandler, Default_Handler

  .weak  		LEUART0_IRQHandler
  .thumb_set 	LEUART0_IRQHandler, Default_Handler

  .weak  		LEUART1_IRQHandler
  .thumb_set 	LEUART1_IRQHandler, Default_Handler

  .weak  		LETIMER0_IRQHandler
  .thumb_set 	LETIMER0_IRQHandler, Default_Handler

  .weak  		PCNT0_IRQHandler
  .thumb_set 	PCNT0_IRQHandler, Default_Handler

  .weak  		PCNT1_IRQHandler
  .thumb_set 	PCNT1_IRQHandler, Default_Handler

  .weak  		PCNT2_IRQHandler
  .thumb_set 	PCNT2_IRQHandler, Default_Handler

  .weak  		RTC_IRQHandler
  .thumb_set 	RTC_IRQHandler, Default_Handler

  .weak  		CMU_IRQHandler
  .thumb_set 	CMU_IRQHandler, Default_Handler

  .weak  		VCMP_IRQHandler
  .thumb_set 	VCMP_IRQHandler, Default_Handler

  .weak  		LCD_IRQHandler
  .thumb_set 	LCD_IRQHandler, Default_Handler

  .weak  		MSC_IRQHandler
  .thumb_set 	MSC_IRQHandler, Default_Handler

  .weak  		AES_IRQHandler
  .thumb_set 	AES_IRQHandler, Default_Handler

/******************************************************************//**
 * @}
*********************************************************************/
