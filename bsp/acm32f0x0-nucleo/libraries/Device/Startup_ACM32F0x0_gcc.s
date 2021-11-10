/*******************************************************************************
;* File Name          : Startup_ACM32F0x0_gcc.s
;* Version            : V1.0.0
;* Date               : 2021
;* Description        : ACM32F0x0 Devices vector table for GCC toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the clock system
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the SC000 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************/

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
  /* bl  SystemInit */
/* Call the application's entry point.*/
  bl entry
LoopForever:
    b LoopForever
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
  .word MemManage_Handler
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
  .word WDT_IRQHandler                  /* 0:  WDT_IRQHandler   */
  .word RTC_IRQHandler                  /* 1:  RTC_IRQHandler    */
  .word EFC_IRQHandler                  /* 2:  EFC_IRQHandler    */
  .word GPIOAB_IRQHandler               /* 3:  GPIOAB_IRQHandler */
  .word GPIOCD_IRQHandler               /* 4:  GPIOCD_IRQHandler */
  .word EXTI_IRQHandler                 /* 5:  EXTI_IRQHandler   */
  .word SRAM_PARITY_IRQHandler          /* 6:  SRAM_PARITY_IRQHandler */
  .word CLKRDY_IRQHandler               /* 7:  CLKRDY_IRQHandler */
  .word LCD_IRQHandler                  /* 8:  LCD_IRQHandler    */
  .word DMA_IRQHandler                  /* 9:  DMA_IRQHandler    */
  .word UART3_IRQHandler                /* 10: UART3_IRQHandler  */
  .word TKEY_IRQHandler                 /* 11: TKEY_IRQHandler   */
  .word ADC_IRQHandler                  /* 12: ADC_IRQHandler    */
  .word TIM1_BRK_UP_TRG_COM_IRQHandler  /* 13: TIM1_BRK_UP_TRG_COM_IRQHandler */
  .word TIM1_CC_IRQHandler              /* 14: TIM1_CC_IRQHandler */
  .word RSV_IRQHandler                  /* 15: Reserved          */
  .word TIM3_IRQHandler                 /* 16: TIM3_IRQHandler   */
  .word TIM6_IRQHandler                 /* 17: TIM6_IRQHandler   */
  .word RSV_IRQHandler                  /* 18: Reserved          */
  .word TIM14_IRQHandler                /* 19: TIM14_IRQHandler  */
  .word TIM15_IRQHandler                /* 20: TIM15_IRQHandler  */
  .word TIM16_IRQHandler                /* 21: TIM16_IRQHandler  */
  .word TIM17_IRQHandler                /* 22: TIM17_IRQHandler  */
  .word I2C1_IRQHandler                 /* 23: I2C1_IRQHandler   */
  .word I2C2_IRQHandler                 /* 24: I2C2_IRQHandler   */
  .word SPI1_IRQHandler                 /* 25: SPI1_IRQHandler   */
  .word SPI2_IRQHandler                 /* 26: SPI2_IRQHandler   */
  .word UART1_IRQHandler                /* 27: UART1_IRQHandler  */
  .word UART2_IRQHandler                /* 28: UART2_IRQHandler  */
  .word LPUART_IRQHandler               /* 29: LPUART_IRQHandler */
  .word CAN1_IRQHandler                 /* 30: CAN1_IRQHandler   */
  .word AES_IRQHandler                  /* 31: AES_IRQHandler    */

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

  .weak SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

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

  .weak EXTI_IRQHandler
  .thumb_set EXTI_IRQHandler,Default_Handler

  .weak SRAM_PARITY_IRQHandler
  .thumb_set SRAM_PARITY_IRQHandler,Default_Handler

  .weak CLKRDY_IRQHandler
  .thumb_set CLKRDY_IRQHandler,Default_Handler

  .weak LCD_IRQHandler
  .thumb_set LCD_IRQHandler,Default_Handler

  .weak DMA_IRQHandler
  .thumb_set DMA_IRQHandler,Default_Handler

  .weak UART3_IRQHandler
  .thumb_set UART3_IRQHandler,Default_Handler

  .weak TKEY_IRQHandler
  .thumb_set TKEY_IRQHandler,Default_Handler

  .weak ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Default_Handler

  .weak TIM1_BRK_UP_TRG_COM_IRQHandler
  .thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler,Default_Handler

  .weak TIM1_CC_IRQHandler
  .thumb_set TIM1_CC_IRQHandler,Default_Handler

  .weak TIM3_IRQHandler
  .thumb_set TIM3_IRQHandler,Default_Handler

  .weak TIM6_IRQHandler
  .thumb_set TIM6_IRQHandler,Default_Handler

  .weak RSV_IRQHandler
  .thumb_set RSV_IRQHandler,Default_Handler

  .weak TIM14_IRQHandler
  .thumb_set TIM14_IRQHandler,Default_Handler

  .weak TIM15_IRQHandler
  .thumb_set TIM15_IRQHandler,Default_Handler

  .weak TIM16_IRQHandler
  .thumb_set TIM16_IRQHandler,Default_Handler

  .weak TIM17_IRQHandler
  .thumb_set TIM17_IRQHandler,Default_Handler

  .weak I2C1_IRQHandler
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

  .weak CAN1_IRQHandler
  .thumb_set CAN1_IRQHandler,Default_Handler

  .weak AES_IRQHandler
  .thumb_set AES_IRQHandler,Default_Handler

/************************ (C) COPYRIGHT AisinoChip *****END OF FILE****/
