/**
  ******************************************************************************
  * @file      startup_M051Series.s
  * @author    RT-Thread Develop Team
  * @version   V1.0.0
  * @date      2014-11-24
  * @brief     M051Series Devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M0 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
*/
    
  .syntax unified
  .cpu cortex-m0
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

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

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

    .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:

  /* Unlock Register */
  ldr     r0, =0x50000100
  ldr     r1, =0x59
  str     r1, [R0]
  ldr     r1, =0x16
  str     r1, [R0]
  ldr     r1, =0x88
  str     r1, [r0]

  /* Init POR */
  ldr     r2, =0x50000024
  ldr     r1, =0x00005AA5
  str     r1, [r2]

  /* Lock register */
  movs r1, #0
  str r1, [r0] 

  /* Copy the data segment initializers from flash to SRAM */  
  movs r1, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r3, =_sidata
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4
    
LoopCopyDataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyDataInit
  ldr r2, =_sbss
  b LoopFillZerobss
/* Zero fill the bss segment. */  
FillZerobss:
  movs r3, #0
  str r3, [r2, #4]
  adds r2, r2, #4
    
LoopFillZerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss
  /* Call the clock system intitialization function.*/
  bl  SystemInit
  /* Call the application's entry point.*/
  bl main
  bx lr
.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/*******************************************************************************
*
* The minimal vector table for a Cortex M0. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*******************************************************************************/
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word 0
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler
  /* External Interrupts */
  /* maximum of 32 External Interrupts are possible */
  .word BOD_IRQHandler  
  .word WDT_IRQHandler  
  .word EINT0_IRQHandler
  .word EINT1_IRQHandler
  .word GPIOP0P1_IRQHandler 
  .word GPIOP2P3P4_IRQHandler
  .word PWMA_IRQHandler 
  .word PWMB_IRQHandler 
  .word TMR0_IRQHandler 
  .word TMR1_IRQHandler 
  .word TMR2_IRQHandler 
  .word TMR3_IRQHandler 
  .word UART0_IRQHandler
  .word UART1_IRQHandler
  .word SPI0_IRQHandler 
  .word SPI1_IRQHandler 
  .word 0 
  .word 0 
  .word I2C0_IRQHandler 
  .word I2C1_IRQHandler 
  .word 0 
  .word 0
  .word 0 
  .word 0  
  .word 0  
  .word ACMP01_IRQHandler 
  .word ACMP23_IRQHandler
  .word 0 
  .word PWRWU_IRQHandler
  .word ADC_IRQHandler
  .word 0  
  .word RTC_IRQHandler  

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler. 
* As they are weak aliases, any function with the same name will override 
* this definition.
*
*******************************************************************************/
    
  .weak NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak BOD_IRQHandler
  .thumb_set BOD_IRQHandler,Default_Handler

  .weak WDT_IRQHandler
  .thumb_set WDT_IRQHandler,Default_Handler
  
  .weak EINT0_IRQHandler
  .thumb_set EINT0_IRQHandler,Default_Handler
  
  .weak EINT1_IRQHandler
  .thumb_set EINT1_IRQHandler,Default_Handler
  
  .weak GPIOP0P1_IRQHandler
  .thumb_set GPIOP0P1_IRQHandler,Default_Handler
  
  .weak GPIOP2P3P4_IRQHandler
  .thumb_set GPIOP2P3P4_IRQHandler,Default_Handler
  
  .weak PWMA_IRQHandler
  .thumb_set PWMA_IRQHandler,Default_Handler
  
  .weak PWMB_IRQHandler
  .thumb_set PWMB_IRQHandler,Default_Handler
  
  .weak TMR0_IRQHandler
  .thumb_set TMR0_IRQHandler,Default_Handler
  
  .weak TMR1_IRQHandler
  .thumb_set TMR1_IRQHandler,Default_Handler
  
  .weak TMR2_IRQHandler
  .thumb_set TMR2_IRQHandler,Default_Handler
  
  .weak TMR3_IRQHandler
  .thumb_set TMR3_IRQHandler,Default_Handler
  
  .weak UART0_IRQHandler
  .thumb_set UART0_IRQHandler,Default_Handler
   
  .weak UART1_IRQHandler
  .thumb_set UART1_IRQHandler,Default_Handler
  
  .weak SPI0_IRQHandler
  .thumb_set SPI0_IRQHandler,Default_Handler
  
  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler
  
  .weak I2C0_IRQHandler
  .thumb_set I2C0_IRQHandler,Default_Handler
  
  .weak I2C1_IRQHandler
  .thumb_set I2C1_IRQHandler,Default_Handler
  
  .weak ACMP01_IRQHandler
  .thumb_set ACMP01_IRQHandler,Default_Handler
  
  .weak ACMP23_IRQHandler
  .thumb_set ACMP23_IRQHandler,Default_Handler
  
  .weak PWRWU_IRQHandler
  .thumb_set PWRWU_IRQHandler,Default_Handler
  
  .weak ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Default_Handler
  
  .weak RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Default_Handler

/************************ END OF FILE ***********************/

