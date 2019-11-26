/**
  ******************************************************************************
  * @file      startup_stm32l010x6.s
  * @author    MCD Application Team
  * @brief     STM32L010x6 Devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M0+ processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * 
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m0plus
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:  
   ldr   r0, =_estack
   mov   sp, r0          /* set stack pointer */

/*Check if boot space corresponds to system memory*/

    LDR R0,=0x00000004
    LDR R1, [R0]
    LSRS R1, R1, #24
    LDR R2,=0x1F
    CMP R1, R2
    BNE ApplicationStart

 /*SYSCFG clock enable*/
    LDR R0,=0x40021034
    LDR R1,=0x00000001
    STR R1, [R0]

/*Set CFGR1 register with flash memory remap at address 0*/
    LDR R0,=0x40010000
    LDR R1,=0x00000000
    STR R1, [R0]

ApplicationStart:
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
  str  r3, [r2]
  adds r2, r2, #4


LoopFillZerobss:
  ldr  r3, = _ebss
  cmp  r2, r3
  bcc  FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
/* bl __libc_init_array */
/* Call the application's entry point.*/
  bl entry

LoopForever:
    b LoopForever


.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  .word     WWDG_IRQHandler                   /* Window WatchDog              */
  .word     0                                 /* Reserved                     */
  .word     RTC_IRQHandler                    /* RTC through the EXTI line     */
  .word     FLASH_IRQHandler                  /* FLASH                        */
  .word     RCC_IRQHandler                    /* RCC                          */
  .word     EXTI0_1_IRQHandler                /* EXTI Line 0 and 1            */
  .word     EXTI2_3_IRQHandler                /* EXTI Line 2 and 3            */
  .word     EXTI4_15_IRQHandler               /* EXTI Line 4 to 15            */
  .word     0                                 /* Reserved                     */
  .word     DMA1_Channel1_IRQHandler          /* DMA1 Channel 1               */
  .word     DMA1_Channel2_3_IRQHandler        /* DMA1 Channel 2 and Channel 3 */
  .word     DMA1_Channel4_5_6_7_IRQHandler    /* DMA1 Channel 4, Channel 5, Channel 6 and Channel 7*/
  .word     ADC1_IRQHandler                   /* ADC1                         */
  .word     LPTIM1_IRQHandler                 /* LPTIM1                       */
  .word     0                                 /* Reserved                     */
  .word     TIM2_IRQHandler                   /* TIM2                         */
  .word     0                                 /* Reserved                     */
  .word     0                                 /* Reserved                     */
  .word     0                                 /* Reserved                     */
  .word     0                                 /* Reserved                     */
  .word     TIM21_IRQHandler                  /* TIM21                        */
  .word     0                                 /* Reserved                     */
  .word     0                                 /* Reserved                     */
  .word     I2C1_IRQHandler                   /* I2C1                         */
  .word     0                                 /* Reserved                     */
  .word     SPI1_IRQHandler                   /* SPI1                         */
  .word     0                                 /* Reserved                     */
  .word     0                                 /* Reserved                     */
  .word     USART2_IRQHandler                 /* USART2                       */
  .word     LPUART1_IRQHandler                /* LPUART1                      */
  .word     0                                 /* Reserved                     */
  .word     0                                 /* Reserved                     */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

   .weak      NMI_Handler
   .thumb_set NMI_Handler,Default_Handler

   .weak      HardFault_Handler
   .thumb_set HardFault_Handler,Default_Handler

   .weak      SVC_Handler
   .thumb_set SVC_Handler,Default_Handler

   .weak      PendSV_Handler
   .thumb_set PendSV_Handler,Default_Handler

   .weak      SysTick_Handler
   .thumb_set SysTick_Handler,Default_Handler

   .weak      WWDG_IRQHandler
   .thumb_set WWDG_IRQHandler,Default_Handler

   .weak      RTC_IRQHandler
   .thumb_set RTC_IRQHandler,Default_Handler

   .weak      FLASH_IRQHandler
   .thumb_set FLASH_IRQHandler,Default_Handler

   .weak      RCC_IRQHandler
   .thumb_set RCC_IRQHandler,Default_Handler

   .weak      EXTI0_1_IRQHandler
   .thumb_set EXTI0_1_IRQHandler,Default_Handler

   .weak      EXTI2_3_IRQHandler
   .thumb_set EXTI2_3_IRQHandler,Default_Handler

   .weak      EXTI4_15_IRQHandler
   .thumb_set EXTI4_15_IRQHandler,Default_Handler

   .weak      DMA1_Channel1_IRQHandler
   .thumb_set DMA1_Channel1_IRQHandler,Default_Handler

   .weak      DMA1_Channel2_3_IRQHandler
   .thumb_set DMA1_Channel2_3_IRQHandler,Default_Handler

   .weak      DMA1_Channel4_5_6_7_IRQHandler
   .thumb_set DMA1_Channel4_5_6_7_IRQHandler,Default_Handler

   .weak      ADC1_IRQHandler
   .thumb_set ADC1_IRQHandler,Default_Handler

   .weak      LPTIM1_IRQHandler
   .thumb_set LPTIM1_IRQHandler,Default_Handler

   .weak      TIM2_IRQHandler
   .thumb_set TIM2_IRQHandler,Default_Handler

   .weak      TIM21_IRQHandler
   .thumb_set TIM21_IRQHandler,Default_Handler

   .weak      I2C1_IRQHandler
   .thumb_set I2C1_IRQHandler,Default_Handler

   .weak      SPI1_IRQHandler
   .thumb_set SPI1_IRQHandler,Default_Handler

   .weak      USART2_IRQHandler
   .thumb_set USART2_IRQHandler,Default_Handler

   .weak      LPUART1_IRQHandler
   .thumb_set LPUART1_IRQHandler,Default_Handler




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

