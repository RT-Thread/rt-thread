/**
  ******************************************************************************
  * @file      startup_at32f407rgt7.s
  * @author    Artery Tek
  * @version   V1.0.0
  * @date      2019-10-12
  * @brief     AT32F4xx Devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Configure the clock system and the external SRAM to
  *                  be used as data memory (optional, to be enabled by user)
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M4 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  */

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
 * @retval None
*/

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:

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
* The minimal vector table for a Cortex M3. Note that the proper constructs
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
  .word  WWDG_IRQHandler                     /* Window Watchdog                         */
  .word  PVD_IRQHandler                      /* PVD through EXTI Line detect            */
  .word  TAMPER_IRQHandler                   /* Tamper                                  */
  .word  RTC_IRQHandler                      /* RTC                                     */
  .word  FLASH_IRQHandler                    /* Flash                                   */
  .word  RCC_IRQHandler                      /* RCC                                     */
  .word  EXTI0_IRQHandler                    /* EXTI Line 0                             */
  .word  EXTI1_IRQHandler                    /* EXTI Line 1                             */
  .word  EXTI2_IRQHandler                    /* EXTI Line 2                             */
  .word  EXTI3_IRQHandler                    /* EXTI Line 3                             */
  .word  EXTI4_IRQHandler                    /* EXTI Line 4                             */
  .word  DMA1_Channel1_IRQHandler            /* DMA1 Channel 1                          */
  .word  DMA1_Channel2_IRQHandler            /* DMA1 Channel 2                          */
  .word  DMA1_Channel3_IRQHandler            /* DMA1 Channel 3                          */
  .word  DMA1_Channel4_IRQHandler            /* DMA1 Channel 4                          */
  .word  DMA1_Channel5_IRQHandler            /* DMA1 Channel 5                          */
  .word  DMA1_Channel6_IRQHandler            /* DMA1 Channel 6                          */
  .word  DMA1_Channel7_IRQHandler            /* DMA1 Channel 7                          */
  .word  ADC1_2_IRQHandler                   /* ADC1 & ADC2                             */
  .word  USB_HP_CAN1_TX_IRQHandler           /* USB High Priority or CAN1 TX            */
  .word  USB_LP_CAN1_RX0_IRQHandler          /* USB Low  Priority or CAN1 RX0           */
  .word  CAN1_RX1_IRQHandler                 /* CAN1 RX1                                */
  .word  CAN1_SCE_IRQHandler                 /* CAN1 SCE                                */
  .word  EXTI9_5_IRQHandler                  /* EXTI Line [9:5]                         */
  .word  TMR1_BRK_TMR9_IRQHandler            /* TMR1 Break and TMR9                     */
  .word  TMR1_OV_TMR10_IRQHandler            /* TMR1 Update and TMR10                   */
  .word  TMR1_TRG_COM_TMR11_IRQHandler       /* TMR1 Trigger and Commutation and TMR11  */
  .word  TMR1_CC_IRQHandler                  /* TMR1 Capture Compare                    */
  .word  TMR2_GLOBAL_IRQHandler              /* TMR2                                    */
  .word  TMR3_GLOBAL_IRQHandler              /* TMR3                                    */
  .word  TMR4_GLOBAL_IRQHandler              /* TMR4                                    */
  .word  I2C1_EV_IRQHandler                  /* I2C1 Event                              */
  .word  I2C1_ER_IRQHandler                  /* I2C1 Error                              */
  .word  I2C2_EV_IRQHandler                  /* I2C2 Event                              */
  .word  I2C2_ER_IRQHandler                  /* I2C2 Error                              */
  .word  SPI1_IRQHandler                     /* SPI1                                    */
  .word  SPI2_I2S2EXT_IRQHandler             /* SPI2 & I2S2EXT                          */
  .word  USART1_IRQHandler                   /* USART1                                  */
  .word  USART2_IRQHandler                   /* USART2                                  */
  .word  USART3_IRQHandler                   /* USART3                                  */
  .word  EXTI15_10_IRQHandler                /* EXTI Line [15:10]                       */
  .word  RTCAlarm_IRQHandler                 /* RTC Alarm through EXTI Line             */
  .word  USBWakeUp_IRQHandler                /* USB Wakeup from suspend                 */
  .word  TMR8_BRK_TMR12_IRQHandler           /* TMR8 Break and TMR12                    */
  .word  TMR8_OV_TMR13_IRQHandler            /* TMR8 Update and TMR13                   */
  .word  TMR8_TRG_COM_TMR14_IRQHandler       /* TMR8 Trigger and Commutation and TMR14  */
  .word  TMR8_CC_IRQHandler                  /* TMR8 Capture Compare                    */
  .word  ADC3_IRQHandler                     /* ADC3                                    */
  .word  XMC_IRQHandler                      /* XMC                                     */
  .word  SDIO1_IRQHandler                    /* SDIO1                                   */
  .word  TMR5_GLOBAL_IRQHandler              /* TMR5                                    */
  .word  SPI3_I2S3EXT_IRQHandler             /* SPI3 & I2S3EXT                          */
  .word  UART4_IRQHandler                    /* UART4                                   */
  .word  UART5_IRQHandler                    /* UART5                                   */
  .word  TMR6_GLOBAL_IRQHandler              /* TMR6                                    */
  .word  TMR7_GLOBAL_IRQHandler              /* TMR7                                    */
  .word  DMA2_Channel1_IRQHandler            /* DMA2 Channel1                           */
  .word  DMA2_Channel2_IRQHandler            /* DMA2 Channel2                           */
  .word  DMA2_Channel3_IRQHandler            /* DMA2 Channel3                           */
  .word  DMA2_Channel4_5_IRQHandler          /* DMA2 Channel4 & Channel5                */
  .word  SDIO2_IRQHandler                    /* SDIO2                                   */
  .word  I2C3_EV_IRQHandler                  /* I2C3 Event                              */
  .word  I2C3_ER_IRQHandler                  /* I2C3 Error                              */
  .word  SPI4_IRQHandler                     /* SPI4                                    */
  .word  0                                   /* Reserved                                */
  .word  0                                   /* Reserved                                */
  .word  0                                   /* Reserved                                */
  .word  0                                   /* Reserved                                */
  .word  CAN2_TX_IRQHandler                  /* CAN2 TX                                 */
  .word  CAN2_RX0_IRQHandler                 /* CAN2 RX0                                */
  .word  CAN2_RX1_IRQHandler                 /* CAN2 RX1                                */
  .word  CAN2_SCE_IRQHandler                 /* CAN2 SCE                                */
  .word  ACC_IRQHandler                      /* ACC                                     */
  .word  USB_HP_IRQHandler                   /* USB HP                                  */
  .word  USB_LP_IRQHandler                   /* USB LP                                  */
  .word  DMA2_Channel6_7_IRQHandler          /* DMA2 Channel6 & Channel7                */
  .word  USART6_IRQHandler                   /* USART6                                  */
  .word  UART7_IRQHandler                    /* UART7                                   */
  .word  UART8_IRQHandler                    /* UART8                                   */
  .word  ETH_IRQHandler                      /* ETH                                     */
  .word  ETH_WKUP_IRQHandler                 /* ETH Wakeup                              */

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
  
   .weak      WWDG_IRQHandler
   .thumb_set WWDG_IRQHandler,Default_Handler      

   .weak      PVD_IRQHandler
   .thumb_set PVD_IRQHandler,Default_Handler

   .weak      TAMPER_IRQHandler
   .thumb_set TAMPER_IRQHandler,Default_Handler

   .weak      RTC_IRQHandler
   .thumb_set RTC_IRQHandler,Default_Handler

   .weak      FLASH_IRQHandler
   .thumb_set FLASH_IRQHandler,Default_Handler

   .weak      RCC_IRQHandler
   .thumb_set RCC_IRQHandler,Default_Handler

   .weak      EXTI0_IRQHandler
   .thumb_set EXTI0_IRQHandler,Default_Handler

   .weak      EXTI1_IRQHandler
   .thumb_set EXTI1_IRQHandler,Default_Handler

   .weak      EXTI2_IRQHandler
   .thumb_set EXTI2_IRQHandler,Default_Handler 

   .weak      EXTI3_IRQHandler
   .thumb_set EXTI3_IRQHandler,Default_Handler

   .weak      EXTI4_IRQHandler
   .thumb_set EXTI4_IRQHandler,Default_Handler

   .weak      DMA1_Channel1_IRQHandler
   .thumb_set DMA1_Channel1_IRQHandler,Default_Handler

   .weak      DMA1_Channel2_IRQHandler
   .thumb_set DMA1_Channel2_IRQHandler,Default_Handler

   .weak      DMA1_Channel3_IRQHandler
   .thumb_set DMA1_Channel3_IRQHandler,Default_Handler

   .weak      DMA1_Channel4_IRQHandler
   .thumb_set DMA1_Channel4_IRQHandler,Default_Handler 

   .weak      DMA1_Channel5_IRQHandler
   .thumb_set DMA1_Channel5_IRQHandler,Default_Handler

   .weak      DMA1_Channel6_IRQHandler
   .thumb_set DMA1_Channel6_IRQHandler,Default_Handler

   .weak      DMA1_Channel7_IRQHandler
   .thumb_set DMA1_Channel7_IRQHandler,Default_Handler

   .weak      ADC1_2_IRQHandler
   .thumb_set ADC1_2_IRQHandler,Default_Handler

   .weak      USB_HP_CAN1_TX_IRQHandler
   .thumb_set USB_HP_CAN1_TX_IRQHandler,Default_Handler

   .weak      USB_LP_CAN1_RX0_IRQHandler
   .thumb_set USB_LP_CAN1_RX0_IRQHandler,Default_Handler

   .weak      CAN1_RX1_IRQHandler
   .thumb_set CAN1_RX1_IRQHandler,Default_Handler

   .weak      CAN1_SCE_IRQHandler
   .thumb_set CAN1_SCE_IRQHandler,Default_Handler

   .weak      EXTI9_5_IRQHandler
   .thumb_set EXTI9_5_IRQHandler,Default_Handler

   .weak      TMR1_BRK_TMR9_IRQHandler
   .thumb_set TMR1_BRK_TMR9_IRQHandler,Default_Handler

   .weak      TMR1_OV_TMR10_IRQHandler
   .thumb_set TMR1_OV_TMR10_IRQHandler,Default_Handler

   .weak      TMR1_TRG_COM_TMR11_IRQHandler
   .thumb_set TMR1_TRG_COM_TMR11_IRQHandler,Default_Handler

   .weak      TMR1_CC_IRQHandler
   .thumb_set TMR1_CC_IRQHandler,Default_Handler

   .weak      TMR2_GLOBAL_IRQHandler
   .thumb_set TMR2_GLOBAL_IRQHandler,Default_Handler

   .weak      TMR3_GLOBAL_IRQHandler
   .thumb_set TMR3_GLOBAL_IRQHandler,Default_Handler

   .weak      TMR4_GLOBAL_IRQHandler
   .thumb_set TMR4_GLOBAL_IRQHandler,Default_Handler

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

   .weak      SPI2_I2S2EXT_IRQHandler
   .thumb_set SPI2_I2S2EXT_IRQHandler,Default_Handler

   .weak      USART1_IRQHandler
   .thumb_set USART1_IRQHandler,Default_Handler

   .weak      USART2_IRQHandler
   .thumb_set USART2_IRQHandler,Default_Handler

   .weak      USART3_IRQHandler
   .thumb_set USART3_IRQHandler,Default_Handler

   .weak      EXTI15_10_IRQHandler
   .thumb_set EXTI15_10_IRQHandler,Default_Handler

   .weak      RTCAlarm_IRQHandler
   .thumb_set RTCAlarm_IRQHandler,Default_Handler

   .weak      USBWakeUp_IRQHandler
   .thumb_set USBWakeUp_IRQHandler,Default_Handler

   .weak      TMR8_BRK_TMR12_IRQHandler
   .thumb_set TMR8_BRK_TMR12_IRQHandler,Default_Handler

   .weak      TMR8_OV_TMR13_IRQHandler
   .thumb_set TMR8_OV_TMR13_IRQHandler,Default_Handler

   .weak      TMR8_TRG_COM_TMR14_IRQHandler
   .thumb_set TMR8_TRG_COM_TMR14_IRQHandler,Default_Handler

   .weak      TMR8_CC_IRQHandler
   .thumb_set TMR8_CC_IRQHandler,Default_Handler

   .weak      ADC3_IRQHandler
   .thumb_set ADC3_IRQHandler,Default_Handler

   .weak      XMC_IRQHandler
   .thumb_set XMC_IRQHandler,Default_Handler

   .weak      SDIO1_IRQHandler
   .thumb_set SDIO1_IRQHandler,Default_Handler

   .weak      TMR5_GLOBAL_IRQHandler
   .thumb_set TMR5_GLOBAL_IRQHandler,Default_Handler

   .weak      SPI3_I2S3EXT_IRQHandler
   .thumb_set SPI3_I2S3EXT_IRQHandler,Default_Handler

   .weak      UART4_IRQHandler
   .thumb_set UART4_IRQHandler,Default_Handler

   .weak      UART5_IRQHandler
   .thumb_set UART5_IRQHandler,Default_Handler

   .weak      TMR6_GLOBAL_IRQHandler
   .thumb_set TMR6_GLOBAL_IRQHandler,Default_Handler

   .weak      TMR7_GLOBAL_IRQHandler
   .thumb_set TMR7_GLOBAL_IRQHandler,Default_Handler

   .weak      DMA2_Channel1_IRQHandler
   .thumb_set DMA2_Channel1_IRQHandler,Default_Handler

   .weak      DMA2_Channel2_IRQHandler
   .thumb_set DMA2_Channel2_IRQHandler,Default_Handler

   .weak      DMA2_Channel3_IRQHandler
   .thumb_set DMA2_Channel3_IRQHandler,Default_Handler

   .weak      DMA2_Channel4_5_IRQHandler
   .thumb_set DMA2_Channel4_5_IRQHandler,Default_Handler

   .weak      SDIO2_IRQHandler
   .thumb_set SDIO2_IRQHandler,Default_Handler

   .weak      I2C3_EV_IRQHandler
   .thumb_set I2C3_EV_IRQHandler,Default_Handler

   .weak      I2C3_ER_IRQHandler
   .thumb_set I2C3_ER_IRQHandler,Default_Handler

   .weak      SPI4_IRQHandler
   .thumb_set SPI4_IRQHandler,Default_Handler

   .weak      CAN2_TX_IRQHandler
   .thumb_set CAN2_TX_IRQHandler,Default_Handler

   .weak      CAN2_RX0_IRQHandler 
   .thumb_set CAN2_RX0_IRQHandler ,Default_Handler

   .weak      CAN2_RX1_IRQHandler 
   .thumb_set CAN2_RX1_IRQHandler ,Default_Handler

   .weak      CAN2_SCE_IRQHandler
   .thumb_set CAN2_SCE_IRQHandler,Default_Handler

   .weak      ACC_IRQHandler
   .thumb_set ACC_IRQHandler,Default_Handler

   .weak      USB_HP_IRQHandler
   .thumb_set USB_HP_IRQHandler,Default_Handler

   .weak      USB_LP_IRQHandler
   .thumb_set USB_LP_IRQHandler,Default_Handler

   .weak      DMA2_Channel6_7_IRQHandler
   .thumb_set DMA2_Channel6_7_IRQHandler,Default_Handler

   .weak      USART6_IRQHandler
   .thumb_set USART6_IRQHandler,Default_Handler

   .weak      UART7_IRQHandler
   .thumb_set UART7_IRQHandler,Default_Handler

   .weak      UART8_IRQHandler
   .thumb_set UART8_IRQHandler,Default_Handler

   .weak      ETH_IRQHandler
   .thumb_set ETH_IRQHandler,Default_Handler

   .weak      ETH_WKUP_IRQHandler
   .thumb_set ETH_WKUP_IRQHandler,Default_Handler

/************************ (C) COPYRIGHT Artery Tek *****END OF FILE****/
