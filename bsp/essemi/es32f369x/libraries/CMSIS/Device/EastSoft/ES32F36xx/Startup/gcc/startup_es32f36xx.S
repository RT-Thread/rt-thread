/**
  ******************************************************************************
  * @file      startup_es32f36xx.s
  * @author    AE Team
  * @brief     ES32F36xx devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M3 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          23 Jan 2019     AE Team         The first version
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
  .arch armv7-m
  .cpu cortex-m3
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
  
  ldr r0, =0x55AA6996
  ldr r1, =0x40080000
  str r0, [r1]
  
  ldr r0, =0x5A962814
  ldr r1, =0x40080100
  str r0, [r1]
  ldr r0, =0xE7CB69A5
  str r0, [r1]
  
  ldr r0, =0x40083C00
  ldr r1, [r0]
  ldr r2, =0xffff
  and r1, r2
  ldr r2, =0x55AA0000
  orr r1, r2
  str r1, [r0]
  str r1, [r0]
  str r1, [r0]
  str r1, [r0]
  str r1, [r0]
  str r1, [r0]
  str r1, [r0]
  str r1, [r0]
  str r1, [r0]
  str r1, [r0]
  
  mov r0, r0
  mov r0, r0
  
  ldr r0, =0x123456
  ldr r1, =0x40080100
  str r0, [r1]
  
  ldr r0, =0x40080404
  ldr r1, =0x4000000
  str r1, [r0]
  
  ldr r0, =0x123456
  ldr r1, =0x40080000
  str r0, [r1]

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
  .word  MemManage_Handler              /* 4,  MPU Fault Handler */
  .word  BusFault_Handler               /* 5,  Bus Fault Handler */
  .word  UsageFault_Handler             /* 6,  Usage Fault Handler */
  .word  0                              /* 7,  Reserved */
  .word  0                              /* 8,  Reserved */
  .word  0                              /* 9,  Reserved */
  .word  0                              /* 10, Reserved */
  .word  SVC_Handler                    /* 11, svcall handler */
  .word  DebugMon_Handler               /* 12, Debug Monitor Handler */
  .word  0                              /* 13, Reserved */
  .word  PendSV_Handler                 /* 14, pendsv handler */
  .word  SysTick_Handler                /* 15, systick handler */
  .word  WWDG_Handler                   /* 16, irq0    WWDG handler */
  .word  IWDG_Handler                   /* 17, irq1    IWDG handler */
  .word  LVD_Handler                    /* 18, irq2    LVD handler */
  .word  RTC_Handler                    /* 19, irq3    RTC handler */
  .word  0                              /* 20, irq4    Reserved */
  .word  0                              /* 21, irq5    Reserved */
  .word  CMU_Handler                    /* 22, irq6    CMU handler */
  .word  ADC0_Handler                   /* 23, irq7    ADC0 handler */
  .word  CAN0_TX_Handler                /* 24, irq8    CAN0_TX handler */
  .word  CAN0_RX0_Handler               /* 25, irq9    CAN0_RX0 handler */
  .word  CAN0_RX1_Handler               /* 26, irq10   CAN0_RX1 handler */
  .word  CAN0_EXCEPTION_Handler         /* 27, irq11   CAN0_EXCEPTION handler */
  .word  AD16C4T0_BRK_Handler           /* 28, irq12   AD16C4T0_BRK handler */
  .word  AD16C4T0_UP_Handler            /* 29, irq13   AD16C4T0_UP handler */
  .word  AD16C4T0_TRIG_COM_Handler      /* 30, irq14   AD16C4T0_TRIG_COM handler */
  .word  AD16C4T0_CC_Handler            /* 31, irq15   AD16C4T0_CC handler */
  .word  AD16C4T1_BRK_Handler           /* 32, irq16   AD16C4T1_BRK handler */
  .word  AD16C4T1_UP_Handler            /* 33, irq17   AD16C4T1_UP handler */
  .word  AD16C4T1_TRIG_COM_Handler      /* 34, irq18   AD16C4T1_TRIG_COM handler */
  .word  AD16C4T1_CC_Handler            /* 35, irq19   AD16C4T1_CC handler */
  .word  GP32C4T0_Handler               /* 36, irq20   GP32C4T0 handler */
  .word  GP32C4T1_Handler               /* 37, irq21   GP32C4T1 handler */
  .word  BS16T0_Handler                 /* 38, irq22   BS16T0  handler */
  .word  BS16T1_Handler                 /* 39, irq23   BS16T1 handler */
  .word  GP16C4T0_Handler               /* 40, irq24   GP16C4T0 handler */
  .word  GP16C4T1_Handler               /* 41, irq25   GP16C4T1 handler */
  .word  0                              /* 42, irq26   Reserved */
  .word  DAC0_CH0_Handler               /* 43, irq27   DAC0_CH0 handler */
  .word  I2C0_EV_Handler                /* 44, irq28   I2C0_EV handler */
  .word  I2C0_ERR_Handler               /* 45, irq29   I2C0_ERR handler */
  .word  I2C1_EV_Handler                /* 46  irq30   I2C1_EV handler */
  .word  I2C1_ERR_Handler               /* 47, irq31   I2C1_ERR handler */
  .word  SPI0_I2S0_Handler              /* 48, irq32   SPI0_I2S0 handler */
  .word  SPI1_I2S1_Handler              /* 49, irq33   SPI1_I2S1 handler */
  .word  UART0_Handler                  /* 50, irq34   UART0 handler */
  .word  UART1_Handler                  /* 51, irq35   UART1 handler */
  .word  UART2_Handler                  /* 52, irq36   UART2 handler */
  .word  UART3_Handler                  /* 53, irq37   UART3 handler */
  .word  UART4_Handler                  /* 54, irq38   UART4 handler */
  .word  UART5_Handler                  /* 55, irq39   UART5 handler */
  .word  0                              /* 56, irq40   Reserved */
  .word  0                              /* 57, irq41   Reserved */
  .word  CRYPT_Handler                  /* 58, irq42   CRYPT handler */
  .word  ACMP0_Handler                  /* 59, irq43   ACMP0 handler */
  .word  ACMP1_Handler                  /* 60, irq44   ACMP1 handler */
  .word  SPI2_I2S2_Handler              /* 61, irq45   SPI2_I2S2 handler */
  .word  0                              /* 62, irq46   Reserved */
  .word  EBI_Handler                    /* 63, irq47   EBI handler */
  .word  TRNG_Handler                   /* 64, irq48   TRNG handler */
  .word  TSENSE_Handler                 /* 65, irq49   TSENSE handler */
  .word  EXTI0_Handler                  /* 66, irq50   EXTI0 handler */
  .word  EXTI1_Handler                  /* 67, irq51   EXTI1 handler */
  .word  EXTI2_Handler                  /* 68, irq52   EXTI2 handler */
  .word  EXTI3_Handler                  /* 69, irq53   EXTI3 handler */
  .word  EXTI4_Handler                  /* 70, irq54   EXTI4 handler */
  .word  EXTI5_Handler                  /* 71, irq55   EXTI5 handler */
  .word  EXTI6_Handler                  /* 72, irq56   EXTI6 handler */
  .word  EXTI7_Handler                  /* 73, irq57   EXTI7 handler */
  .word  EXTI8_Handler                  /* 74, irq58   EXTI8 handler */
  .word  EXTI9_Handler                  /* 75, irq59   EXTI9 handler */
  .word  EXTI10_Handler                 /* 76, irq60   EXTI10 handler */
  .word  EXTI11_Handler                 /* 77, irq61   EXTI11 handler */
  .word  EXTI12_Handler                 /* 78, irq62   EXTI12 handler */
  .word  EXTI13_Handler                 /* 79, irq63   EXTI13 handler */
  .word  EXTI14_Handler                 /* 80, irq64   EXTI14 handler */
  .word  EXTI15_Handler                 /* 81, irq65   EXTI15 handler */
  .word  DMA_Handler                    /* 82, irq66   DMA handler */
  .word  ADC1_Handler                   /* 83, irq67   ADC1 handler */
  .word  DAC0_CH1_Handler               /* 84, irq68   DAC0_CH1 handler */
  .word  QSPI_Handler                   /* 85, irq69   QSPI handler */
  .word  USB_INT_Handler                /* 86, irq70   USB_INT handler */
  .word  USB_DMA_Handler                /* 87, irq71   USB_DMA handler */
  .word  ACMP2_Handler                  /* 88, irq72   ACMP2 handler */

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

  .weak      MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler

  .weak      BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak      UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak      DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      WWDG_Handler
  .thumb_set WWDG_Handler,Default_Handler

  .weak      IWDG_Handler
  .thumb_set IWDG_Handler,Default_Handler

  .weak      LVD_Handler
  .thumb_set LVD_Handler,Default_Handler

  .weak      RTC_Handler
  .thumb_set RTC_Handler,Default_Handler

  .weak      CMU_Handler
  .thumb_set CMU_Handler,Default_Handler

  .weak      ADC0_Handler
  .thumb_set ADC0_Handler,Default_Handler

  .weak      CAN0_TX_Handler
  .thumb_set CAN0_TX_Handler,Default_Handler

  .weak      CAN0_RX0_Handler
  .thumb_set CAN0_RX0_Handler,Default_Handler

  .weak      CAN0_RX1_Handler
  .thumb_set CAN0_RX1_Handler,Default_Handler

  .weak      CAN0_EXCEPTION_Handler
  .thumb_set CAN0_EXCEPTION_Handler,Default_Handler

  .weak      AD16C4T0_BRK_Handler
  .thumb_set AD16C4T0_BRK_Handler,Default_Handler

  .weak      AD16C4T0_UP_Handler
  .thumb_set AD16C4T0_UP_Handler,Default_Handler

  .weak      AD16C4T0_TRIG_COM_Handler
  .thumb_set AD16C4T0_TRIG_COM_Handler,Default_Handler

  .weak      AD16C4T0_CC_Handler
  .thumb_set AD16C4T0_CC_Handler,Default_Handler

  .weak      AD16C4T1_BRK_Handler
  .thumb_set AD16C4T1_BRK_Handler,Default_Handler

  .weak      AD16C4T1_UP_Handler
  .thumb_set AD16C4T1_UP_Handler,Default_Handler

  .weak      AD16C4T1_TRIG_COM_Handler
  .thumb_set AD16C4T1_TRIG_COM_Handler,Default_Handler

  .weak      AD16C4T1_CC_Handler
  .thumb_set AD16C4T1_CC_Handler,Default_Handler

  .weak      GP32C4T0_Handler
  .thumb_set GP32C4T0_Handler,Default_Handler

  .weak      GP32C4T1_Handler
  .thumb_set GP32C4T1_Handler,Default_Handler

  .weak      BS16T0_Handler
  .thumb_set BS16T0_Handler,Default_Handler

  .weak      BS16T1_Handler
  .thumb_set BS16T1_Handler,Default_Handler

  .weak      GP16C4T0_Handler
  .thumb_set GP16C4T0_Handler,Default_Handler

  .weak      GP16C4T1_Handler
  .thumb_set GP16C4T1_Handler,Default_Handler

  .weak      DAC0_CH0_Handler
  .thumb_set DAC0_CH0_Handler,Default_Handler

  .weak      I2C0_EV_Handler
  .thumb_set I2C0_EV_Handler,Default_Handler

  .weak      I2C0_ERR_Handler
  .thumb_set I2C0_ERR_Handler,Default_Handler

  .weak      I2C1_EV_Handler
  .thumb_set I2C1_EV_Handler,Default_Handler

  .weak      I2C1_ERR_Handler
  .thumb_set I2C1_ERR_Handler,Default_Handler

  .weak      SPI0_I2S0_Handler
  .thumb_set SPI0_I2S0_Handler,Default_Handler

  .weak      SPI1_I2S1_Handler
  .thumb_set SPI1_I2S1_Handler,Default_Handler

  .weak      UART0_Handler
  .thumb_set UART0_Handler,Default_Handler

  .weak      UART1_Handler
  .thumb_set UART1_Handler,Default_Handler

  .weak      UART2_Handler
  .thumb_set UART2_Handler,Default_Handler

  .weak      UART3_Handler
  .thumb_set UART3_Handler,Default_Handler

  .weak      UART4_Handler
  .thumb_set UART4_Handler,Default_Handler

  .weak      UART5_Handler
  .thumb_set UART5_Handler,Default_Handler

  .weak      CRYPT_Handler
  .thumb_set CRYPT_Handler,Default_Handler

  .weak      ACMP0_Handler
  .thumb_set ACMP0_Handler,Default_Handler

  .weak      ACMP1_Handler
  .thumb_set ACMP1_Handler,Default_Handler

  .weak      SPI2_I2S2_Handler
  .thumb_set SPI2_I2S2_Handler,Default_Handler

  .weak      EBI_Handler
  .thumb_set EBI_Handler,Default_Handler

  .weak      TRNG_Handler
  .thumb_set TRNG_Handler,Default_Handler

  .weak      TSENSE_Handler
  .thumb_set TSENSE_Handler,Default_Handler

  .weak      EXTI0_Handler
  .thumb_set EXTI0_Handler,Default_Handler

  .weak      EXTI1_Handler
  .thumb_set EXTI1_Handler,Default_Handler

  .weak      EXTI2_Handler
  .thumb_set EXTI2_Handler,Default_Handler

  .weak      EXTI3_Handler
  .thumb_set EXTI3_Handler,Default_Handler

  .weak      EXTI4_Handler
  .thumb_set EXTI4_Handler,Default_Handler

  .weak      EXTI5_Handler
  .thumb_set EXTI5_Handler,Default_Handler

  .weak      EXTI6_Handler
  .thumb_set EXTI6_Handler,Default_Handler

  .weak      EXTI7_Handler
  .thumb_set EXTI7_Handler,Default_Handler

  .weak      EXTI8_Handler
  .thumb_set EXTI8_Handler,Default_Handler

  .weak      EXTI9_Handler
  .thumb_set EXTI9_Handler,Default_Handler

  .weak      EXTI10_Handler
  .thumb_set EXTI10_Handler,Default_Handler

  .weak      EXTI11_Handler
  .thumb_set EXTI11_Handler,Default_Handler

  .weak      EXTI12_Handler
  .thumb_set EXTI12_Handler,Default_Handler

  .weak      EXTI13_Handler
  .thumb_set EXTI13_Handler,Default_Handler

  .weak      EXTI14_Handler
  .thumb_set EXTI14_Handler,Default_Handler

  .weak      EXTI15_Handler
  .thumb_set EXTI15_Handler,Default_Handler

  .weak      DMA_Handler
  .thumb_set DMA_Handler,Default_Handler

  .weak      ADC1_Handler
  .thumb_set ADC1_Handler,Default_Handler

  .weak      DAC0_CH1_Handler
  .thumb_set DAC0_CH1_Handler,Default_Handler

  .weak      QSPI_Handler
  .thumb_set QSPI_Handler,Default_Handler

  .weak      USB_INT_Handler
  .thumb_set USB_INT_Handler,Default_Handler

  .weak      USB_DMA_Handler
  .thumb_set USB_DMA_Handler,Default_Handler

  .weak      ACMP2_Handler
  .thumb_set ACMP2_Handler,Default_Handler

