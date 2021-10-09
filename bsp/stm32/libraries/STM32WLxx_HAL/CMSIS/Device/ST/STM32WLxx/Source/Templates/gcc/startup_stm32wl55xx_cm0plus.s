/**
  ******************************************************************************
  * @file      startup_stm32wl55xx_cm0plus.s
  * @author    MCD Application Team
  * @brief     STM32WL55xx devices Cortex-M0+ vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address,
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M0+ processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020(-2021) STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

.syntax unified
.cpu cortex-m0plus
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
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Call the clock system initialization function.*/
  bl  SystemInit

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit

/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever

  .size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
  .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler

/******************************************************************************
*
* The STM32WL55xx Cortex-M0+ vector table.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word	0
  .word	0
  .word	0
  .word	0
  .word	0
  .word	0
  .word	0
  .word	SVC_Handler
  .word	0
  .word	0
  .word	PendSV_Handler
  .word	SysTick_Handler
  .word	TZIC_ILA_IRQHandler                  			/* TZIC ILA Interrupt                                 */
  .word	PVD_PVM_IRQHandler                   			/* PVD and PVM interrupt through EXTI                 */
  .word	RTC_LSECSS_IRQHandler                			/* RTC Tamper, RTC TimeStamp, LSECSS and RTC SSRU int.*/
  .word	RCC_FLASH_C1SEV_IRQHandler           			/* RCC and FLASH and CPU1 M4 SEV Interrupt            */
  .word	EXTI1_0_IRQHandler                   			/* EXTI Line 1:0 Interrupt                            */
  .word	EXTI3_2_IRQHandler                   			/* EXTI Line 3:2 Interrupt                            */
  .word	EXTI15_4_IRQHandler                  			/* EXTI Line 15:4 interrupt                           */
  .word	ADC_COMP_DAC_IRQHandler              			/* ADC, COMP1, COMP2, DAC Interrupt                   */
  .word	DMA1_Channel1_2_3_IRQHandler         			/* DMA1 Channel 1 to 3 Interrupt                      */
  .word	DMA1_Channel4_5_6_7_IRQHandler       			/* DMA1 Channels 4,5,6,7 Interrupt                    */
  .word	DMA2_DMAMUX1_OVR_IRQHandler          			/* DMA2 Channels[1..7] and DMAMUX Overrun Interrupts  */
  .word	LPTIM1_IRQHandler                    			/* LPTIM1 Global Interrupt                            */
  .word	LPTIM2_IRQHandler                    			/* LPTIM2 Global Interrupt                            */
  .word	LPTIM3_IRQHandler                    			/* LPTIM3 Global Interrupt                            */
  .word	TIM1_IRQHandler                      			/* TIM1 Global Interrupt                              */
  .word	TIM2_IRQHandler                      			/* TIM2 Global Interrupt                              */
  .word	TIM16_IRQHandler                     			/* TIM16 Global Interrupt                             */
  .word	TIM17_IRQHandler                     			/* TIM17 Global Interrupt                             */
  .word	IPCC_C2_RX_C2_TX_IRQHandler          			/* IPCC RX Occupied and TX Free Interrupt Interrupt   */
  .word	HSEM_IRQHandler                      			/* Semaphore Interrupt                                */
  .word	RNG_IRQHandler                       			/* RNG Interrupt                                      */
  .word	AES_PKA_IRQHandler                   			/* COMP1 and COMP2 interrupt through EXTI             */
  .word	I2C1_IRQHandler                      			/* I2C1 Event and Error Interrupt                     */
  .word	I2C2_IRQHandler                      			/* I2C2 Event and Error Interrupt                     */
  .word	I2C3_IRQHandler                      			/* I2C3 Event and Error Interrupt                     */
  .word	SPI1_IRQHandler                      			/* SPI1 Interrupt                                     */
  .word	SPI2_IRQHandler                      			/* SPI2 Interrupt                                     */
  .word	USART1_IRQHandler                    			/* USART1 Interrupt                                   */
  .word	USART2_IRQHandler                    			/* USART2 Interrupt                                   */
  .word	LPUART1_IRQHandler                   			/* LPUART1 Interrupt                                  */
  .word	SUBGHZSPI_IRQHandler                 			/* SUBGHZSPI Interrupt                                */
  .word	SUBGHZ_Radio_IRQHandler              			/* SUBGHZ Radio Interrupt                             */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

	.weak	NMI_Handler
	.thumb_set NMI_Handler,Default_Handler

	.weak	HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler

	.weak	SVC_Handler
	.thumb_set SVC_Handler,Default_Handler

	.weak	PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler

	.weak	SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler

	.weak	TZIC_ILA_IRQHandler
	.thumb_set TZIC_ILA_IRQHandler,Default_Handler

	.weak	PVD_PVM_IRQHandler
	.thumb_set PVD_PVM_IRQHandler,Default_Handler

	.weak	RTC_LSECSS_IRQHandler
	.thumb_set RTC_LSECSS_IRQHandler,Default_Handler

	.weak	RCC_FLASH_C1SEV_IRQHandler
	.thumb_set RCC_FLASH_C1SEV_IRQHandler,Default_Handler

	.weak	EXTI1_0_IRQHandler
	.thumb_set EXTI1_0_IRQHandler,Default_Handler

	.weak	EXTI3_2_IRQHandler
	.thumb_set EXTI3_2_IRQHandler,Default_Handler

	.weak	EXTI15_4_IRQHandler
	.thumb_set EXTI15_4_IRQHandler,Default_Handler

	.weak	ADC_COMP_DAC_IRQHandler
	.thumb_set ADC_COMP_DAC_IRQHandler,Default_Handler

	.weak	DMA1_Channel1_2_3_IRQHandler
	.thumb_set DMA1_Channel1_2_3_IRQHandler,Default_Handler

	.weak	DMA1_Channel4_5_6_7_IRQHandler
	.thumb_set DMA1_Channel4_5_6_7_IRQHandler,Default_Handler

	.weak	DMA2_DMAMUX1_OVR_IRQHandler
	.thumb_set DMA2_DMAMUX1_OVR_IRQHandler,Default_Handler

	.weak	LPTIM1_IRQHandler
	.thumb_set LPTIM1_IRQHandler,Default_Handler

	.weak	LPTIM2_IRQHandler
	.thumb_set LPTIM2_IRQHandler,Default_Handler

	.weak	LPTIM3_IRQHandler
	.thumb_set LPTIM3_IRQHandler,Default_Handler

	.weak	TIM1_IRQHandler
	.thumb_set TIM1_IRQHandler,Default_Handler

	.weak	TIM2_IRQHandler
	.thumb_set TIM2_IRQHandler,Default_Handler

	.weak	TIM16_IRQHandler
	.thumb_set TIM16_IRQHandler,Default_Handler

	.weak	TIM17_IRQHandler
	.thumb_set TIM17_IRQHandler,Default_Handler

	.weak	IPCC_C2_RX_C2_TX_IRQHandler
	.thumb_set IPCC_C2_RX_C2_TX_IRQHandler,Default_Handler

	.weak	HSEM_IRQHandler
	.thumb_set HSEM_IRQHandler,Default_Handler

	.weak	RNG_IRQHandler
	.thumb_set RNG_IRQHandler,Default_Handler

	.weak	AES_PKA_IRQHandler
	.thumb_set AES_PKA_IRQHandler,Default_Handler

	.weak	I2C1_IRQHandler
	.thumb_set I2C1_IRQHandler,Default_Handler

	.weak	I2C2_IRQHandler
	.thumb_set I2C2_IRQHandler,Default_Handler

	.weak	I2C3_IRQHandler
	.thumb_set I2C3_IRQHandler,Default_Handler

	.weak	SPI1_IRQHandler
	.thumb_set SPI1_IRQHandler,Default_Handler

	.weak	SPI2_IRQHandler
	.thumb_set SPI2_IRQHandler,Default_Handler

	.weak	USART1_IRQHandler
	.thumb_set USART1_IRQHandler,Default_Handler

	.weak	USART2_IRQHandler
	.thumb_set USART2_IRQHandler,Default_Handler

	.weak	LPUART1_IRQHandler
	.thumb_set LPUART1_IRQHandler,Default_Handler

	.weak	SUBGHZSPI_IRQHandler
	.thumb_set SUBGHZSPI_IRQHandler,Default_Handler

	.weak	SUBGHZ_Radio_IRQHandler
	.thumb_set SUBGHZ_Radio_IRQHandler,Default_Handler

	.weak	SystemInit

/************************ (C) COPYRIGHT STMicroelectonics *****END OF FILE****/
