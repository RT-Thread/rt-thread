/**
  ******************************************************************************
  * @file      startup_es32f065x.s
  * @author    AE Team
  * @brief     ES32F065x devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M0 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          10 Dec 2018     AE Team         The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */

  .syntax unified
  .arch armv6-m
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

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

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

  bl __libc_init_array

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
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack                        /* 0,  load top of stack */
  .word  Reset_Handler                  /* 1,  reset handler */
  .word  NMI_Handler                    /* 2,  nmi handler */
  .word  HardFault_Handler              /* 3,  hard fault handler */
  .word  0                              /* 4,  Reserved */
  .word  0                              /* 5,  Reserved */
  .word  0                              /* 6,  Reserved */
  .word  0                              /* 7,  Reserved */
  .word  0                              /* 8,  Reserved */
  .word  0                              /* 9,  Reserved */
  .word  0                              /* 10, Reserved */
  .word  SVC_Handler                    /* 11, svcall handler */
  .word  DebugMon_Handler               /* 12, Debug Monitor Handler */
  .word  0                              /* 13, Reserved */
  .word  PendSV_Handler                 /* 14, pendsv handler */
  .word  SysTick_Handler                /* 15, systick handler */
  .word  WWDG_IWDG_Handler                   /* 16, irq0    WWDG_IWDG handler */
  .word  LVD_Handler                   /* 17, irq1    LVD handler */
  .word  RTC_TSENSE_Handler                    /* 18, irq2    RTC handler */
  .word  CRYPT_TRNG_Handler                    /* 19, irq3    CRYPT handler */
  .word  CMU_Handler                              /* 20, irq4    CMU handler */
  .word  EXTI0_3_Handler                              /* 21, irq5    EXTI0_3 handler */
  .word  EXTI4_7_Handler                    /* 22, irq6    EXTI4_7 handler */
  .word  EXTI8_11_Handler                   /* 23, irq7    EXTI8_11 handler */
  .word  EXTI12_15_Handler                /* 24, irq8    EXTI12_15 handler */
  .word  DMA_Handler               /* 25, irq9    DMA handler */
  .word  CAN0_Handler               /* 26, irq10   CAN0_CRYPT_TRNG handler */
  .word  LPTIM0_SPI2_Handler         /* 27, irq11   LPTIM0_SPI2 handler */
  .word  ADC_ACMP_Handler           /* 28, irq12   ADC_ACMP handler */
  .word  AD16C4T0_BRK_UP_TRIG_COM_Handler            /* 29, irq13   AD16C4T0_BRK_UP_TRIG_COM handler */
  .word  AD16C4T0_CC_Handler      /* 30, irq14   AD16C4T0_CC handler */
  .word  BS16T0_Handler            /* 31, irq15   BS16T0 handler */
  .word  0           /* 32, irq16  Reserved */
  .word  GP16C2T0_Handler            /* 33, irq17   GP16C2T0 handler */
  .word  GP16C2T1_Handler      /* 34, irq18   GP16C2T1 handler */
  .word  BS16T1_UART2_Handler            /* 35, irq19   BS16T1_UART2 handler */
  .word  BS16T2_UART3_Handler               /* 36, irq20   BS16T2_UART3 handler */
  .word  GP16C4T0_LCD_Handler               /* 37, irq21   GP16C4T0_LCD handler */
  .word  BS16T3_DAC0_Handler                 /* 38, irq22   BS16T3_DAC0  handler */
  .word  I2C0_Handler                 /* 39, irq23   I2C0 handler */
  .word  I2C1_Handler               /* 40, irq24   I2C1 handler */
  .word  SPI0_Handler               /* 41, irq25   SPI0 handler */
  .word  SPI1_Handler                              /* 42, irq26   SPI1 handler */
  .word  UART0_Handler                /* 43, irq27   UART0 handler */
  .word  UART1_Handler                /* 44, irq28   UART1 handler */
  .word  USART0_Handler               /* 45, irq29   USART0 handler */
  .word  USART1_Handler                /* 46  irq30   USART1 handler */
  .word  LPUART0_Handler               /* 47, irq31   LPUART0 handler */

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
  
   .weak      DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

   .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler
  
   .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

   .weak      WWDG_IWDG_Handler
  .thumb_set WWDG_IWDG_Handler,Default_Handler
  
   .weak      LVD_Handler
  .thumb_set LVD_Handler,Default_Handler

   .weak      RTC_TSENSE_Handler
  .thumb_set RTC_TSENSE_Handler,Default_Handler
  
   .weak      CRYPT_TRNG_Handler
  .thumb_set CRYPT_TRNG_Handler,Default_Handler

   .weak      CMU_Handler
  .thumb_set CMU_Handler,Default_Handler
  
   .weak      EXTI0_3_Handler
  .thumb_set EXTI0_3_Handler,Default_Handler

   .weak      EXTI4_7_Handler
  .thumb_set EXTI4_7_Handler,Default_Handler
  
   .weak      EXTI8_11_Handler
  .thumb_set EXTI8_11_Handler,Default_Handler

  .weak      EXTI12_15_Handler
  .thumb_set EXTI12_15_Handler,Default_Handler
  
   .weak      DMA_Handler
  .thumb_set DMA_Handler,Default_Handler

   .weak      CAN0_Handler
  .thumb_set CAN0_Handler,Default_Handler
  
   .weak      LPTIM0_SPI2_Handler
  .thumb_set LPTIM0_SPI2_Handler,Default_Handler

   .weak      ADC_ACMP_Handler
  .thumb_set ADC_ACMP_Handler,Default_Handler
  
   .weak      AD16C4T0_BRK_UP_TRIG_COM_Handler
  .thumb_set AD16C4T0_BRK_UP_TRIG_COM_Handler,Default_Handler

   .weak      AD16C4T0_CC_Handler
  .thumb_set AD16C4T0_CC_Handler,Default_Handler
  
   .weak      BS16T0_Handler
  .thumb_set BS16T0_Handler,Default_Handler

   .weak      GP16C2T0_Handler
  .thumb_set GP16C2T0_Handler,Default_Handler
  
   .weak      GP16C2T1_Handler
  .thumb_set GP16C2T1_Handler,Default_Handler

   .weak      BS16T1_UART2_Handler
  .thumb_set BS16T1_UART2_Handler,Default_Handler
  
   .weak      BS16T2_UART3_Handler
  .thumb_set BS16T2_UART3_Handler,Default_Handler

  .weak      GP16C4T0_LCD_Handler
  .thumb_set GP16C4T0_LCD_Handler,Default_Handler
  
   .weak      BS16T3_DAC0_Handler
  .thumb_set BS16T3_DAC0_Handler,Default_Handler

   .weak      I2C0_Handler
  .thumb_set I2C0_Handler,Default_Handler
  
   .weak      I2C1_Handler
  .thumb_set I2C1_Handler,Default_Handler

   .weak      SPI0_Handler
  .thumb_set SPI0_Handler,Default_Handler
  
   .weak      SPI1_Handler
  .thumb_set SPI1_Handler,Default_Handler

   .weak      UART0_Handler
  .thumb_set UART0_Handler,Default_Handler
  
   .weak      UART1_Handler
  .thumb_set UART1_Handler,Default_Handler

   .weak      USART0_Handler
  .thumb_set USART0_Handler,Default_Handler
  
   .weak      USART1_Handler
  .thumb_set USART1_Handler,Default_Handler

   .weak      LPUART0_Handler
  .thumb_set LPUART0_Handler,Default_Handler
 