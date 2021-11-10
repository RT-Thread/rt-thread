/*********************** (C) COPYRIGHT 2020 Aisinochip *************************
;* File Name          : Startup_ACM32F4.s
;* Author             : AisinoChip Firmware Team
;* Version            : V1.0.0
;* Date               : 2020
;* Description        : ACM32F4 Devices vector table for GCC toolchain. 
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the clock system
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M33 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;********************************************************************************
;* @attention
;*
;* Copyright (c) 2020 AisinoChip.
;* All rights reserved.
;*******************************************************************************/

  .syntax unified
  .cpu cortex-m33
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

/*.equ  BootRAM, 0xF108F85F */

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
  str r3, [r2], #4

LoopFillZerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss

/* Call the clock system intitialization function.*/
  /*  bl  SystemInit */
/* Call static constructors */
  /*  bl __libc_init_array */
/* Call the application's entry point.*/
  bl entry
  bx lr
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
* The minimal vector table for a Cortex M3.  Note that the proper constructs
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
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler

  /* External Interrupts */
  .word WDT_IRQHandler
  .word RTC_IRQHandler
  .word EFC_IRQHandler
  .word GPIOAB_IRQHandler
  .word GPIOCD_IRQHandler
  .word EXIT_IRQHandler
  .word SRAM_PAPITY_IRQHandler
  .word CLKRDY_IRQHandler
  .word UART4_IRQHandler
  .word DMA_IRQHandler
  .word UART3_IRQHandler
  .word RSV_IRQHandler
  .word ADC_IRQHandler
  .word TIM1_BRK_UP_TRG_COM_IRQHandler
  .word TIM1_CC_IRQHandler
  .word TIM2_IRQHandler
  .word TIM3_IRQHandler
  .word TIM6_IRQHandler
  .word TIM7_IRQHandler
  .word TIM14_IRQHandler
  .word TIM15_IRQHandler
  .word TIM16_IRQHandler
  .word TIM17_IRQHandler
  .word I2C1_IRQHandler
  .word I2C2_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_IRQHandler
  .word UART1_IRQHandler
  .word UART2_IRQHandler
  .word LPUART_IRQHandler
  .word SPI3_IRQHandler
  .word AES_IRQHandler
  .word USB_IRQHandler
  .word DAC_IRQHandler
  .word I2S_IRQHandler
  .word GPIOEF_IRQHandler
  .word CAN1_IRQHandler
  .word CAN2_IRQHandler
  .word FPU_IRQHandler
  .word TIM4_IRQHandler
  .word SPI4_IRQHandler

                          

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

  .weak MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler

  .weak BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak WDT_IRQHandler
  .thumb_set WDT_IRQHandler,Default_Handler

  .weak RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Default_Handler

  .weak EFC_IRQHandler
  .thumb_set EFC_IRQHandler,Default_Handler

  .weak GPIOAB_IRQHandler
  .thumb_set GPIOAB_IRQHandler,Default_Handler

  .weak GPIOCD_IRQHandler
  .thumb_set GPIOCD_IRQHandler,Default_Handler

  .weak EXIT_IRQHandler
  .thumb_set EXIT_IRQHandler,Default_Handler

  .weak SRAM_PAPITY_IRQHandler
  .thumb_set SRAM_PAPITY_IRQHandler,Default_Handler

  .weak CLKRDY_IRQHandler
  .thumb_set CLKRDY_IRQHandler,Default_Handler

  .weak UART4_IRQHandler
  .thumb_set UART4_IRQHandler,Default_Handler

  .weak DMA_IRQHandler
  .thumb_set DMA_IRQHandler,Default_Handler

  .weak UART3_IRQHandler
  .thumb_set UART3_IRQHandler,Default_Handler

  .weak RSV_IRQHandler
  .thumb_set RSV_IRQHandler,Default_Handler

  .weak ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Default_Handler

  .weak TIM1_BRK_UP_TRG_COM_IRQHandler
  .thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler,Default_Handler

  .weak TIM1_CC_IRQHandler
  .thumb_set TIM1_CC_IRQHandler,Default_Handler

  .weak TIM2_IRQHandler
  .thumb_set TIM2_IRQHandler,Default_Handler

  .weak TIM3_IRQHandler
  .thumb_set TIM3_IRQHandler,Default_Handler

  .weak TIM6_IRQHandler
  .thumb_set TIM6_IRQHandler,Default_Handler

  .weak TIM7_IRQHandler
  .thumb_set TIM7_IRQHandler,Default_Handler

  .weak TIM14_IRQHandler
  .thumb_set TIM14_IRQHandler,Default_Handler

  .weak TIM15_IRQHandler
  .thumb_set TIM15_IRQHandler,Default_Handler

  .weak TIM16_IRQHandler
  .thumb_set TIM16_IRQHandler,Default_Handler

  .weak TIM17_IRQHandler
  .thumb_set TIM17_IRQHandler,Default_Handler

  .weak I2C1_IRQHandler
  .thumb_set I2C1_IRQHandler,Default_Handler

  .weak I2C2_IRQHandler
  .thumb_set I2C2_IRQHandler,Default_Handler

  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler

  .weak UART1_IRQHandler
  .thumb_set UART1_IRQHandler,Default_Handler

  .weak UART2_IRQHandler
  .thumb_set UART2_IRQHandler,Default_Handler

  .weak LPUART_IRQHandler
  .thumb_set LPUART_IRQHandler,Default_Handler

  .weak SPI3_IRQHandler
  .thumb_set SPI3_IRQHandler,Default_Handler

  .weak AES_IRQHandler
  .thumb_set AES_IRQHandler,Default_Handler

  .weak USB_IRQHandler
  .thumb_set USB_IRQHandler,Default_Handler

  .weak DAC_IRQHandler
  .thumb_set DAC_IRQHandler,Default_Handler

  .weak I2S_IRQHandler
  .thumb_set I2S_IRQHandler,Default_Handler

  .weak GPIOEF_IRQHandler
  .thumb_set GPIOEF_IRQHandler,Default_Handler

  .weak CAN1_IRQHandler
  .thumb_set CAN1_IRQHandler,Default_Handler

  .weak CAN2_IRQHandler
  .thumb_set CAN2_IRQHandler,Default_Handler

  .weak FPU_IRQHandler
  .thumb_set FPU_IRQHandler,Default_Handler

  .weak TIM4_IRQHandler
  .thumb_set TIM4_IRQHandler,Default_Handler

  .weak SPI4_IRQHandler
  .thumb_set SPI4_IRQHandler,Default_Handler



