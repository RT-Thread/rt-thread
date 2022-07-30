;/*!
; * @file       startup_apm32f41x.s
; *
; * @brief      CMSIS Cortex-M4 based Core Device Startup File for Device startup_apm32f41x
; *
; * @version     V1.0.2
; *
; * @date        2022-06-23
; *
; * @attention
; *
; *  Copyright (C) 2021-2022 Geehy Semiconductor
; *
; *  You may not use this file except in compliance with the
; *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
; *
; *  The program is only for reference, which is distributed in the hope
; *  that it will be usefull and instructional for customers to develop
; *  their software. Unless required by applicable law or agreed to in
; *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
; *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
; *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
; *  and limitations under the License.
; */

  .syntax unified
  .cpu cortex-m4
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
/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack     /* set stack pointer */

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

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
    /* bl __libc_init_array */
/* Call the application's entry point.*/
  bl  entry
  bx  lr
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None
 * @retval None
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M4. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
*******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
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
  .word  PendSV_Handler
  .word  SysTick_Handler

  /* External Interrupts */
  .word     WWDT_IRQHandler                   /* Window WatchDog             */
  .word     PVD_IRQHandler                    /* PVD through EINT Line detection */
  .word     TAMP_STAMP_IRQHandler             /* Tamper and TimeStamps through the EINT line */
  .word     RTC_WKUP_IRQHandler               /* RTC Wakeup through the EINT line */
  .word     FLASH_IRQHandler                  /* FLASH                        */
  .word     RCM_IRQHandler                    /* RCC                          */
  .word     EINT0_IRQHandler                  /* EINT Line0                   */
  .word     EINT1_IRQHandler                  /* EINT Line1                   */
  .word     EINT2_IRQHandler                  /* EINT Line2                   */
  .word     EINT3_IRQHandler                  /* EINT Line3                   */
  .word     EINT4_IRQHandler                  /* EINT Line4                   */
  .word     DMA1_STR0_IRQHandler              /* DMA1 Stream 0                */
  .word     DMA1_STR1_IRQHandler              /* DMA1 Stream 1                */
  .word     DMA1_STR2_IRQHandler              /* DMA1 Stream 2                */
  .word     DMA1_STR3_IRQHandler              /* DMA1 Stream 3                */
  .word     DMA1_STR4_IRQHandler              /* DMA1 Stream 4                */
  .word     DMA1_STR5_IRQHandler              /* DMA1 Stream 5                */
  .word     DMA1_STR6_IRQHandler              /* DMA1 Stream 6                */
  .word     ADC_IRQHandler                    /* ADC1, ADC2 and ADC3s         */
  .word     CAN1_TX_IRQHandler                /* CAN1 TX                      */
  .word     CAN1_RX0_IRQHandler               /* CAN1 RX0                     */
  .word     CAN1_RX1_IRQHandler               /* CAN1 RX1                     */
  .word     CAN1_SCE_IRQHandler               /* CAN1 SCE                     */
  .word     EINT9_5_IRQHandler                /* External Line[9:5]s          */
  .word     TMR1_BRK_TMR9_IRQHandler          /* TMR1 Break and TMR9          */
  .word     TMR1_UP_TMR10_IRQHandler          /* TMR1 Update and TMR10        */
  .word     TMR1_TRG_COM_TMR11_IRQHandler     /* TMR1 Trigger and Commutation and TMR11 */
  .word     TMR1_CC_IRQHandler                /* TMR1 Capture Compare         */
  .word     TMR2_IRQHandler                   /* TMR2                         */
  .word     TMR3_IRQHandler                   /* TMR3                         */
  .word     TMR4_IRQHandler                   /* TMR4                         */
  .word     I2C1_EV_IRQHandler                /* I2C1 Event                   */
  .word     I2C1_ER_IRQHandler                /* I2C1 Error                   */
  .word     I2C2_EV_IRQHandler                /* I2C2 Event                   */
  .word     I2C2_ER_IRQHandler                /* I2C2 Error                   */
  .word     SPI1_IRQHandler                   /* SPI1                         */
  .word     SPI2_IRQHandler                   /* SPI2                         */
  .word     USART1_IRQHandler                 /* USART1                       */
  .word     USART2_IRQHandler                 /* USART2                       */
  .word     USART3_IRQHandler                 /* USART3                       */
  .word     EINT15_10_IRQHandler              /* External Line[15:10]s        */
  .word     RTC_Alarm_IRQHandler              /* RTC Alarm (A and B) through EINT Line */
  .word     OTG_FS_WKUP_IRQHandler            /* USB OTG FS Wakeup through EINT line */
  .word     TMR8_BRK_TMR12_IRQHandler         /* TMR8 Break and TMR12         */
  .word     TMR8_UP_TMR13_IRQHandler          /* TMR8 Update and TMR13        */
  .word     TMR8_TRG_COM_TMR14_IRQHandler     /* TMR8 Trigger and Commutation and TMR14 */
  .word     TMR8_CC_IRQHandler                /* TMR8 Capture Compare         */
  .word     DMA1_STR7_IRQHandler              /* DMA1 Stream7                 */
  .word     EMMC_IRQHandler                   /* EMMC                         */
  .word     SDIO_IRQHandler                   /* SDIO                         */
  .word     TMR5_IRQHandler                   /* TMR5                         */
  .word     SPI3_IRQHandler                   /* SPI3                         */
  .word     UART4_IRQHandler                  /* UART4                        */
  .word     UART5_IRQHandler                  /* UART5                        */
  .word     TMR6_DAC_IRQHandler               /* TMR6 and DAC1&2 underrun errors */
  .word     TMR7_IRQHandler                   /* TMR7                         */
  .word     DMA2_STR0_IRQHandler              /* DMA2 Stream 0                */
  .word     DMA2_STR1_IRQHandler              /* DMA2 Stream 1                */
  .word     DMA2_STR2_IRQHandler              /* DMA2 Stream 2                */
  .word     DMA2_STR3_IRQHandler              /* DMA2 Stream 3                */
  .word     DMA2_STR4_IRQHandler              /* DMA2 Stream 4                */
  .word     ETH_IRQHandler                    /* Ethernet                     */
  .word     ETH_WKUP_IRQHandler               /* Ethernet Wakeup through EINT line */
  .word     CAN2_TX_IRQHandler                /* CAN2 TX                      */
  .word     CAN2_RX0_IRQHandler               /* CAN2 RX0                     */
  .word     CAN2_RX1_IRQHandler               /* CAN2 RX1                     */
  .word     CAN2_SCE_IRQHandler               /* CAN2 SCE                     */
  .word     OTG_FS_IRQHandler                 /* USB OTG FS                   */
  .word     DMA2_STR5_IRQHandler              /* DMA2 Stream 5                */
  .word     DMA2_STR6_IRQHandler              /* DMA2 Stream 6                */
  .word     DMA2_STR7_IRQHandler              /* DMA2 Stream 7                */
  .word     USART6_IRQHandler                 /* USART6                       */
  .word     I2C3_EV_IRQHandler                /* I2C3 event                   */
  .word     I2C3_ER_IRQHandler                /* I2C3 error                   */
  .word     OTG_HS1_EP1_OUT_IRQHandler        /* USB OTG HS1 End Point 1 Out  */
  .word     OTG_HS1_EP1_IN_IRQHandler         /* USB OTG HS1 End Point 1 In   */
  .word     OTG_HS1_WKUP_IRQHandler           /* USB OTG HS1 Wakeup through EINT */
  .word     OTG_HS1_IRQHandler                /* USB OTG HS1                  */
  .word     DCI_IRQHandler                    /* DCI                          */
  .word     CRYP_IRQHandler                   /* CRYP crypto                  */
  .word     HASH_RNG_IRQHandler               /* Hash and Rng                 */
  .word     FPU_IRQHandler                    /* FPU                          */
  .word     SM3_IRQHandler                    /* SM3                          */
  .word     SM4_IRQHandler                    /* SM4                          */
  .word     BN_IRQHandler                     /* BN                           */

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

   .weak      WWDT_IRQHandler
   .thumb_set WWDT_IRQHandler,Default_Handler

   .weak      PVD_IRQHandler
   .thumb_set PVD_IRQHandler,Default_Handler

   .weak      TAMP_STAMP_IRQHandler
   .thumb_set TAMP_STAMP_IRQHandler,Default_Handler

   .weak      RTC_WKUP_IRQHandler
   .thumb_set RTC_WKUP_IRQHandler,Default_Handler

   .weak      FLASH_IRQHandler
   .thumb_set FLASH_IRQHandler,Default_Handler

   .weak      RCM_IRQHandler
   .thumb_set RCM_IRQHandler,Default_Handler

   .weak      EINT0_IRQHandler
   .thumb_set EINT0_IRQHandler,Default_Handler

   .weak      EINT1_IRQHandler
   .thumb_set EINT1_IRQHandler,Default_Handler

   .weak      EINT2_IRQHandler
   .thumb_set EINT2_IRQHandler,Default_Handler

   .weak      EINT3_IRQHandler
   .thumb_set EINT3_IRQHandler,Default_Handler

   .weak      EINT4_IRQHandler
   .thumb_set EINT4_IRQHandler,Default_Handler

   .weak      DMA1_STR0_IRQHandler
   .thumb_set DMA1_STR0_IRQHandler,Default_Handler

   .weak      DMA1_STR1_IRQHandler
   .thumb_set DMA1_STR1_IRQHandler,Default_Handler

   .weak      DMA1_STR2_IRQHandler
   .thumb_set DMA1_STR2_IRQHandler,Default_Handler

   .weak      DMA1_STR3_IRQHandler
   .thumb_set DMA1_STR3_IRQHandler,Default_Handler

   .weak      DMA1_STR4_IRQHandler
   .thumb_set DMA1_STR4_IRQHandler,Default_Handler

   .weak      DMA1_STR5_IRQHandler
   .thumb_set DMA1_STR5_IRQHandler,Default_Handler

   .weak      DMA1_STR6_IRQHandler
   .thumb_set DMA1_STR6_IRQHandler,Default_Handler

   .weak      ADC_IRQHandler
   .thumb_set ADC_IRQHandler,Default_Handler

   .weak      CAN1_TX_IRQHandler
   .thumb_set CAN1_TX_IRQHandler,Default_Handler

   .weak      CAN1_RX0_IRQHandler
   .thumb_set CAN1_RX0_IRQHandler,Default_Handler

   .weak      CAN1_RX1_IRQHandler
   .thumb_set CAN1_RX1_IRQHandler,Default_Handler

   .weak      CAN1_SCE_IRQHandler
   .thumb_set CAN1_SCE_IRQHandler,Default_Handler

   .weak      EINT9_5_IRQHandler
   .thumb_set EINT9_5_IRQHandler,Default_Handler

   .weak      TMR1_BRK_TMR9_IRQHandler
   .thumb_set TMR1_BRK_TMR9_IRQHandler,Default_Handler

   .weak      TMR1_UP_TMR10_IRQHandler
   .thumb_set TMR1_UP_TMR10_IRQHandler,Default_Handler

   .weak      TMR1_TRG_COM_TMR11_IRQHandler
   .thumb_set TMR1_TRG_COM_TMR11_IRQHandler,Default_Handler

   .weak      TMR1_CC_IRQHandler
   .thumb_set TMR1_CC_IRQHandler,Default_Handler

   .weak      TMR2_IRQHandler
   .thumb_set TMR2_IRQHandler,Default_Handler

   .weak      TMR3_IRQHandler
   .thumb_set TMR3_IRQHandler,Default_Handler

   .weak      TMR4_IRQHandler
   .thumb_set TMR4_IRQHandler,Default_Handler

   .weak      I2C1_EV_IRQHandler
   .thumb_set I2C1_EV_IRQHandler,Default_Handler

   .weak      I2C1_ER_IRQHandler
   .thumb_set I2C1_ER_IRQHandler,Default_Handler

   .weak      I2C2_EV_IRQHandler
   .thumb_set I2C2_EV_IRQHandler,Default_Handler

   .weak      I2C2_ER_IRQHandler
   .thumb_set I2C2_ER_IRQHandler,Default_Handler

   .weak      SPI1_IRQHandler
   .thumb_set SPI1_IRQHandler,Default_Handler

   .weak      SPI2_IRQHandler
   .thumb_set SPI2_IRQHandler,Default_Handler

   .weak      USART1_IRQHandler
   .thumb_set USART1_IRQHandler,Default_Handler

   .weak      USART2_IRQHandler
   .thumb_set USART2_IRQHandler,Default_Handler

   .weak      USART3_IRQHandler
   .thumb_set USART3_IRQHandler,Default_Handler

   .weak      EINT15_10_IRQHandler
   .thumb_set EINT15_10_IRQHandler,Default_Handler

   .weak      RTC_Alarm_IRQHandler
   .thumb_set RTC_Alarm_IRQHandler,Default_Handler

   .weak      OTG_FS_WKUP_IRQHandler
   .thumb_set OTG_FS_WKUP_IRQHandler,Default_Handler

   .weak      TMR8_BRK_TMR12_IRQHandler
   .thumb_set TMR8_BRK_TMR12_IRQHandler,Default_Handler

   .weak      TMR8_UP_TMR13_IRQHandler
   .thumb_set TMR8_UP_TMR13_IRQHandler,Default_Handler

   .weak      TMR8_TRG_COM_TMR14_IRQHandler
   .thumb_set TMR8_TRG_COM_TMR14_IRQHandler,Default_Handler

   .weak      TMR8_CC_IRQHandler
   .thumb_set TMR8_CC_IRQHandler,Default_Handler

   .weak      DMA1_STR7_IRQHandler
   .thumb_set DMA1_STR7_IRQHandler,Default_Handler

   .weak      EMMC_IRQHandler
   .thumb_set EMMC_IRQHandler,Default_Handler

   .weak      SDIO_IRQHandler
   .thumb_set SDIO_IRQHandler,Default_Handler

   .weak      TMR5_IRQHandler
   .thumb_set TMR5_IRQHandler,Default_Handler

   .weak      SPI3_IRQHandler
   .thumb_set SPI3_IRQHandler,Default_Handler

   .weak      UART4_IRQHandler
   .thumb_set UART4_IRQHandler,Default_Handler

   .weak      UART5_IRQHandler
   .thumb_set UART5_IRQHandler,Default_Handler

   .weak      TMR6_DAC_IRQHandler
   .thumb_set TMR6_DAC_IRQHandler,Default_Handler

   .weak      TMR7_IRQHandler
   .thumb_set TMR7_IRQHandler,Default_Handler

   .weak      DMA2_STR0_IRQHandler
   .thumb_set DMA2_STR0_IRQHandler,Default_Handler

   .weak      DMA2_STR1_IRQHandler
   .thumb_set DMA2_STR1_IRQHandler,Default_Handler

   .weak      DMA2_STR2_IRQHandler
   .thumb_set DMA2_STR2_IRQHandler,Default_Handler

   .weak      DMA2_STR3_IRQHandler
   .thumb_set DMA2_STR3_IRQHandler,Default_Handler

   .weak      DMA2_STR4_IRQHandler
   .thumb_set DMA2_STR4_IRQHandler,Default_Handler

   .weak      ETH_IRQHandler
   .thumb_set ETH_IRQHandler,Default_Handler

   .weak      ETH_WKUP_IRQHandler
   .thumb_set ETH_WKUP_IRQHandler,Default_Handler

   .weak      CAN2_TX_IRQHandler
   .thumb_set CAN2_TX_IRQHandler,Default_Handler

   .weak      CAN2_RX0_IRQHandler
   .thumb_set CAN2_RX0_IRQHandler,Default_Handler

   .weak      CAN2_RX1_IRQHandler
   .thumb_set CAN2_RX1_IRQHandler,Default_Handler

   .weak      CAN2_SCE_IRQHandler
   .thumb_set CAN2_SCE_IRQHandler,Default_Handler

   .weak      OTG_FS_IRQHandler
   .thumb_set OTG_FS_IRQHandler,Default_Handler

   .weak      DMA2_STR5_IRQHandler
   .thumb_set DMA2_STR5_IRQHandler,Default_Handler

   .weak      DMA2_STR6_IRQHandler
   .thumb_set DMA2_STR6_IRQHandler,Default_Handler

   .weak      DMA2_STR7_IRQHandler
   .thumb_set DMA2_STR7_IRQHandler,Default_Handler

   .weak      USART6_IRQHandler
   .thumb_set USART6_IRQHandler,Default_Handler

   .weak      I2C3_EV_IRQHandler
   .thumb_set I2C3_EV_IRQHandler,Default_Handler

   .weak      I2C3_ER_IRQHandler
   .thumb_set I2C3_ER_IRQHandler,Default_Handler

   .weak      OTG_HS1_EP1_OUT_IRQHandler
   .thumb_set OTG_HS1_EP1_OUT_IRQHandler,Default_Handler

   .weak      OTG_HS1_EP1_IN_IRQHandler
   .thumb_set OTG_HS1_EP1_IN_IRQHandler,Default_Handler

   .weak      OTG_HS1_WKUP_IRQHandler
   .thumb_set OTG_HS1_WKUP_IRQHandler,Default_Handler

   .weak      OTG_HS1_IRQHandler
   .thumb_set OTG_HS1_IRQHandler,Default_Handler

   .weak      DCI_IRQHandler
   .thumb_set DCI_IRQHandler,Default_Handler

   .weak      CRYP_IRQHandler
   .thumb_set CRYP_IRQHandler,Default_Handler

   .weak      HASH_RNG_IRQHandler
   .thumb_set HASH_RNG_IRQHandler,Default_Handler

   .weak      FPU_IRQHandler
   .thumb_set FPU_IRQHandler,Default_Handler

   .weak      SM3_IRQHandler
   .thumb_set SM3_IRQHandler,Default_Handler

   .weak      SM4_IRQHandler
   .thumb_set SM4_IRQHandler,Default_Handler

   .weak      BN_IRQHandler
   .thumb_set BN_IRQHandler,Default_Handler

