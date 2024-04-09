/**
  ******************************************************************************
  * @file      startup_stm32h7s7xx.s
  * @author    MCD Application Team
  * @brief     STM32H7R7xx Devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m7
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
  bl  main

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
* The STM32H7R7xx vector table. Note that the proper constructs
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
  .word     PVD_PVM_IRQHandler                /* PVD/PVM through EXTI Line detection */
  .word     0                                 /* Reserved */
  .word     DTS_IRQHandler                    /* Digital Temperature Sensor */
  .word     IWDG_IRQHandler                   /* Internal Watchdog */
  .word     WWDG_IRQHandler                   /* Window Watchdog   */
  .word     RCC_IRQHandler                    /* RCC global interrupts through EXTI Line detection */
  .word     0                                 /* Reserved    */
  .word     0                                 /* Reserved    */
  .word     FLASH_IRQHandler                  /* FLASH interrupts  */
  .word     RAMECC_IRQHandler                 /* RAMECC interrupts */
  .word     FPU_IRQHandler                    /* FPU */
  .word     0                                 /* Reserved */
  .word     0                                 /* Reserved */
  .word     TAMP_IRQHandler                   /* Tamper and TimeStamp interrupts */
  .word     0                                 /* Reserved    */
  .word     0                                 /* Reserved    */
  .word     EXTI0_IRQHandler                  /* EXTI Line0  */
  .word     EXTI1_IRQHandler                  /* EXTI Line1  */
  .word     EXTI2_IRQHandler                  /* EXTI Line2  */
  .word     EXTI3_IRQHandler                  /* EXTI Line3  */
  .word     EXTI4_IRQHandler                  /* EXTI Line4  */
  .word     EXTI5_IRQHandler                  /* EXTI Line5  */
  .word     EXTI6_IRQHandler                  /* EXTI Line6  */
  .word     EXTI7_IRQHandler                  /* EXTI Line7  */
  .word     EXTI8_IRQHandler                  /* EXTI Line8  */
  .word     EXTI9_IRQHandler                  /* EXTI Line9  */
  .word     EXTI10_IRQHandler                 /* EXTI Line10 */
  .word     EXTI11_IRQHandler                 /* EXTI Line11 */
  .word     EXTI12_IRQHandler                 /* EXTI Line12 */
  .word     EXTI13_IRQHandler                 /* EXTI Line13 */
  .word     EXTI14_IRQHandler                 /* EXTI Line14 */
  .word     EXTI15_IRQHandler                 /* EXTI Line15 */
  .word     RTC_IRQHandler                    /* RTC wakeup and alarm interrupts */
  .word     0                                 /* Reserved    */
  .word     0                                 /* Reserved    */
  .word     PKA_IRQHandler                    /* PKA  */
  .word     HASH_IRQHandler                   /* HASH */
  .word     RNG_IRQHandler                    /* RNG  */
  .word     ADC1_2_IRQHandler                 /* ADC1 & ADC2      */
  .word     GPDMA1_Channel0_IRQHandler        /* GPDMA1 Channel 0 */
  .word     GPDMA1_Channel1_IRQHandler        /* GPDMA1 Channel 1 */
  .word     GPDMA1_Channel2_IRQHandler        /* GPDMA1 Channel 2 */
  .word     GPDMA1_Channel3_IRQHandler        /* GPDMA1 Channel 3 */
  .word     GPDMA1_Channel4_IRQHandler        /* GPDMA1 Channel 4 */
  .word     GPDMA1_Channel5_IRQHandler        /* GPDMA1 Channel 5 */
  .word     GPDMA1_Channel6_IRQHandler        /* GPDMA1 Channel 6 */
  .word     GPDMA1_Channel7_IRQHandler        /* GPDMA1 Channel 7 */
  .word     TIM1_BRK_IRQHandler               /* TIM1 Break  */
  .word     TIM1_UP_IRQHandler                /* TIM1 Update */
  .word     TIM1_TRG_COM_IRQHandler           /* TIM1 Trigger and Commutation */
  .word     TIM1_CC_IRQHandler                /* TIM1 Capture Compare         */
  .word     TIM2_IRQHandler                   /* TIM2 */
  .word     TIM3_IRQHandler                   /* TIM3 */
  .word     TIM4_IRQHandler                   /* TIM4 */
  .word     TIM5_IRQHandler                   /* TIM5 */
  .word     TIM6_IRQHandler                   /* TIM6 */
  .word     TIM7_IRQHandler                   /* TIM7 */
  .word     TIM9_IRQHandler                   /* TIM9 */
  .word     SPI1_IRQHandler                   /* SPI1 */
  .word     SPI2_IRQHandler                   /* SPI2 */
  .word     SPI3_IRQHandler                   /* SPI3 */
  .word     SPI4_IRQHandler                   /* SPI4 */
  .word     SPI5_IRQHandler                   /* SPI5 */
  .word     SPI6_IRQHandler                   /* SPI6 */
  .word     HPDMA1_Channel0_IRQHandler        /* HPDMA1 Channel 0 */
  .word     HPDMA1_Channel1_IRQHandler        /* HPDMA1 Channel 1 */
  .word     HPDMA1_Channel2_IRQHandler        /* HPDMA1 Channel 2 */
  .word     HPDMA1_Channel3_IRQHandler        /* HPDMA1 Channel 3 */
  .word     HPDMA1_Channel4_IRQHandler        /* HPDMA1 Channel 4 */
  .word     HPDMA1_Channel5_IRQHandler        /* HPDMA1 Channel 5 */
  .word     HPDMA1_Channel6_IRQHandler        /* HPDMA1 Channel 6 */
  .word     HPDMA1_Channel7_IRQHandler        /* HPDMA1 Channel 7 */
  .word     SAI1_A_IRQHandler                 /* Serial Audio Interface 1 block A */
  .word     SAI1_B_IRQHandler                 /* Serial Audio Interface 1 block B */
  .word     SAI2_A_IRQHandler                 /* Serial Audio Interface 2 block A */
  .word     SAI2_B_IRQHandler                 /* Serial Audio Interface 2 block B */
  .word     I2C1_EV_IRQHandler                /* I2C1 Event */
  .word     I2C1_ER_IRQHandler                /* I2C1 Error */
  .word     I2C2_EV_IRQHandler                /* I2C2 Event */
  .word     I2C2_ER_IRQHandler                /* I2C2 Error */
  .word     I2C3_EV_IRQHandler                /* I2C3 Event */
  .word     I2C3_ER_IRQHandler                /* I2C3 Error */
  .word     USART1_IRQHandler                 /* USART1 */
  .word     USART2_IRQHandler                 /* USART2 */
  .word     USART3_IRQHandler                 /* USART3 */
  .word     UART4_IRQHandler                  /* UART4 */
  .word     UART5_IRQHandler                  /* UART5 */
  .word     UART7_IRQHandler                  /* UART7 */
  .word     UART8_IRQHandler                  /* UART8 */
  .word     I3C1_EV_IRQHandler                /* I3C1 Event */
  .word     I3C1_ER_IRQHandler                /* I3C1 Error */
  .word     OTG_HS_IRQHandler                 /* USB OTG HS */
  .word     ETH_IRQHandler                    /* Ethernet */
  .word     CORDIC_IRQHandler                 /* CORDIC */
  .word     GFXTIM_IRQHandler                 /* GFXTIM */
  .word     DCMIPP_IRQHandler                 /* DCMIPP */
  .word     LTDC_IRQHandler                   /* LTDC   */
  .word     LTDC_ER_IRQHandler                /* LTDC error  */
  .word     DMA2D_IRQHandler                  /* DMA2D  */
  .word     JPEG_IRQHandler                   /* JPEG   */
  .word     GFXMMU_IRQHandler                 /* GFXMMU */
  .word     I3C1_WKUP_IRQHandler              /* I3C1 wakeup */
  .word     0                                 /* Reserved    */
  .word     0                                 /* Reserved    */
  .word     0                                 /* Reserved    */
  .word     XSPI1_IRQHandler                  /* XSPI1 */
  .word     XSPI2_IRQHandler                  /* XSPI2 */
  .word     FMC_IRQHandler                    /* FMC */
  .word     SDMMC1_IRQHandler                 /* SDMMC1 */
  .word     SDMMC2_IRQHandler                 /* SDMMC2 */
  .word     0                                 /* Reserved */
  .word     0                                 /* Reserved */
  .word     OTG_FS_IRQHandler                 /* USB OTG FS */
  .word     TIM12_IRQHandler                  /* TIM12 */
  .word     TIM13_IRQHandler                  /* TIM13 */
  .word     TIM14_IRQHandler                  /* TIM14 */
  .word     TIM15_IRQHandler                  /* TIM15 */
  .word     TIM16_IRQHandler                  /* TIM16 */
  .word     TIM17_IRQHandler                  /* TIM17 */
  .word     LPTIM1_IRQHandler                 /* LP TIM1 */
  .word     LPTIM2_IRQHandler                 /* LP TIM2 */
  .word     LPTIM3_IRQHandler                 /* LP TIM3 */
  .word     LPTIM4_IRQHandler                 /* LP TIM4 */
  .word     LPTIM5_IRQHandler                 /* LP TIM5 */
  .word     SPDIF_RX_IRQHandler               /* SPDIF_RX */
  .word     MDIOS_IRQHandler                  /* MDIOS */
  .word     ADF1_FLT0_IRQHandler              /* ADF1 Filter 0 */
  .word     CRS_IRQHandler                    /* CRS */
  .word     UCPD1_IRQHandler                  /* UCPD1 */
  .word     CEC_IRQHandler                    /* HDMI_CEC */
  .word     PSSI_IRQHandler                   /* PSSI */
  .word     LPUART1_IRQHandler                /* LP UART1 */
  .word     WAKEUP_PIN_IRQHandler             /* Wake-up pins interrupt */
  .word     GPDMA1_Channel8_IRQHandler        /* GPDMA1 Channel 8  */
  .word     GPDMA1_Channel9_IRQHandler        /* GPDMA1 Channel 9  */
  .word     GPDMA1_Channel10_IRQHandler       /* GPDMA1 Channel 10 */
  .word     GPDMA1_Channel11_IRQHandler       /* GPDMA1 Channel 11 */
  .word     GPDMA1_Channel12_IRQHandler       /* GPDMA1 Channel 12 */
  .word     GPDMA1_Channel13_IRQHandler       /* GPDMA1 Channel 13 */
  .word     GPDMA1_Channel14_IRQHandler       /* GPDMA1 Channel 14 */
  .word     GPDMA1_Channel15_IRQHandler       /* GPDMA1 Channel 15 */
  .word     HPDMA1_Channel8_IRQHandler        /* HPDMA1 Channel 8  */
  .word     HPDMA1_Channel9_IRQHandler        /* HPDMA1 Channel 9  */
  .word     HPDMA1_Channel10_IRQHandler       /* HPDMA1 Channel 10 */
  .word     HPDMA1_Channel11_IRQHandler       /* HPDMA1 Channel 11 */
  .word     HPDMA1_Channel12_IRQHandler       /* HPDMA1 Channel 12 */
  .word     HPDMA1_Channel13_IRQHandler       /* HPDMA1 Channel 13 */
  .word     HPDMA1_Channel14_IRQHandler       /* HPDMA1 Channel 14 */
  .word     HPDMA1_Channel15_IRQHandler       /* HPDMA1 Channel 15 */
  .word     GPU2D_IRQHandler                  /* GPU2D */
  .word     GPU2D_ER_IRQHandler               /* GPU2D error */
  .word     ICACHE_IRQHandler                 /* ICACHE */
  .word     FDCAN1_IT0_IRQHandler             /* FDCAN1 Interrupt 0 */
  .word     FDCAN1_IT1_IRQHandler             /* FDCAN1 Interrupt 1 */
  .word     FDCAN2_IT0_IRQHandler             /* FDCAN2 Interrupt 0 */
  .word     FDCAN2_IT1_IRQHandler             /* FDCAN2 Interrupt 1 */

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

   .weak      PVD_PVM_IRQHandler
   .thumb_set PVD_PVM_IRQHandler,Default_Handler

   .weak      DTS_IRQHandler
   .thumb_set DTS_IRQHandler,Default_Handler

   .weak      IWDG_IRQHandler
   .thumb_set IWDG_IRQHandler,Default_Handler

   .weak      WWDG_IRQHandler
   .thumb_set WWDG_IRQHandler,Default_Handler

   .weak      RCC_IRQHandler
   .thumb_set RCC_IRQHandler,Default_Handler

   .weak      FLASH_IRQHandler
   .thumb_set FLASH_IRQHandler,Default_Handler

   .weak      RAMECC_IRQHandler
   .thumb_set RAMECC_IRQHandler,Default_Handler

   .weak      FPU_IRQHandler
   .thumb_set FPU_IRQHandler,Default_Handler

   .weak      TAMP_IRQHandler
   .thumb_set TAMP_IRQHandler,Default_Handler

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

   .weak      EXTI5_IRQHandler
   .thumb_set EXTI5_IRQHandler,Default_Handler

   .weak      EXTI6_IRQHandler
   .thumb_set EXTI6_IRQHandler,Default_Handler

   .weak      EXTI7_IRQHandler
   .thumb_set EXTI7_IRQHandler,Default_Handler

   .weak      EXTI8_IRQHandler
   .thumb_set EXTI8_IRQHandler,Default_Handler

   .weak      EXTI9_IRQHandler
   .thumb_set EXTI9_IRQHandler,Default_Handler

   .weak      EXTI10_IRQHandler
   .thumb_set EXTI10_IRQHandler,Default_Handler

   .weak      EXTI11_IRQHandler
   .thumb_set EXTI11_IRQHandler,Default_Handler

   .weak      EXTI12_IRQHandler
   .thumb_set EXTI12_IRQHandler,Default_Handler

   .weak      EXTI13_IRQHandler
   .thumb_set EXTI13_IRQHandler,Default_Handler

   .weak      EXTI14_IRQHandler
   .thumb_set EXTI14_IRQHandler,Default_Handler

   .weak      EXTI15_IRQHandler
   .thumb_set EXTI15_IRQHandler,Default_Handler

   .weak      RTC_IRQHandler
   .thumb_set RTC_IRQHandler,Default_Handler

   .weak      PKA_IRQHandler
   .thumb_set PKA_IRQHandler,Default_Handler

   .weak      HASH_IRQHandler
   .thumb_set HASH_IRQHandler,Default_Handler

   .weak      RNG_IRQHandler
   .thumb_set RNG_IRQHandler,Default_Handler

   .weak      ADC1_2_IRQHandler
   .thumb_set ADC1_2_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel0_IRQHandler
   .thumb_set GPDMA1_Channel0_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel1_IRQHandler
   .thumb_set GPDMA1_Channel1_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel2_IRQHandler
   .thumb_set GPDMA1_Channel2_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel3_IRQHandler
   .thumb_set GPDMA1_Channel3_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel4_IRQHandler
   .thumb_set GPDMA1_Channel4_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel5_IRQHandler
   .thumb_set GPDMA1_Channel5_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel6_IRQHandler
   .thumb_set GPDMA1_Channel6_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel7_IRQHandler
   .thumb_set GPDMA1_Channel7_IRQHandler,Default_Handler

   .weak      TIM1_BRK_IRQHandler
   .thumb_set TIM1_BRK_IRQHandler,Default_Handler

   .weak      TIM1_UP_IRQHandler
   .thumb_set TIM1_UP_IRQHandler,Default_Handler

   .weak      TIM1_TRG_COM_IRQHandler
   .thumb_set TIM1_TRG_COM_IRQHandler,Default_Handler

   .weak      TIM1_CC_IRQHandler
   .thumb_set TIM1_CC_IRQHandler,Default_Handler

   .weak      TIM2_IRQHandler
   .thumb_set TIM2_IRQHandler,Default_Handler

   .weak      TIM3_IRQHandler
   .thumb_set TIM3_IRQHandler,Default_Handler

   .weak      TIM4_IRQHandler
   .thumb_set TIM4_IRQHandler,Default_Handler

   .weak      TIM5_IRQHandler
   .thumb_set TIM5_IRQHandler,Default_Handler

   .weak      TIM6_IRQHandler
   .thumb_set TIM6_IRQHandler,Default_Handler

   .weak      TIM7_IRQHandler
   .thumb_set TIM7_IRQHandler,Default_Handler

   .weak      TIM9_IRQHandler
   .thumb_set TIM9_IRQHandler,Default_Handler

   .weak      SPI1_IRQHandler
   .thumb_set SPI1_IRQHandler,Default_Handler

   .weak      SPI2_IRQHandler
   .thumb_set SPI2_IRQHandler,Default_Handler

   .weak      SPI3_IRQHandler
   .thumb_set SPI3_IRQHandler,Default_Handler

   .weak      SPI4_IRQHandler
   .thumb_set SPI4_IRQHandler,Default_Handler

   .weak      SPI5_IRQHandler
   .thumb_set SPI5_IRQHandler,Default_Handler

   .weak      SPI6_IRQHandler
   .thumb_set SPI6_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel0_IRQHandler
   .thumb_set HPDMA1_Channel0_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel1_IRQHandler
   .thumb_set HPDMA1_Channel1_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel2_IRQHandler
   .thumb_set HPDMA1_Channel2_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel3_IRQHandler
   .thumb_set HPDMA1_Channel3_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel4_IRQHandler
   .thumb_set HPDMA1_Channel4_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel5_IRQHandler
   .thumb_set HPDMA1_Channel5_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel6_IRQHandler
   .thumb_set HPDMA1_Channel6_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel7_IRQHandler
   .thumb_set HPDMA1_Channel7_IRQHandler,Default_Handler

   .weak      SAI1_A_IRQHandler
   .thumb_set SAI1_A_IRQHandler,Default_Handler

   .weak      SAI1_B_IRQHandler
   .thumb_set SAI1_B_IRQHandler,Default_Handler

   .weak      SAI2_A_IRQHandler
   .thumb_set SAI2_A_IRQHandler,Default_Handler

   .weak      SAI2_B_IRQHandler
   .thumb_set SAI2_B_IRQHandler,Default_Handler

   .weak      I2C1_EV_IRQHandler
   .thumb_set I2C1_EV_IRQHandler,Default_Handler

   .weak      I2C1_ER_IRQHandler
   .thumb_set I2C1_ER_IRQHandler,Default_Handler

   .weak      I2C2_EV_IRQHandler
   .thumb_set I2C2_EV_IRQHandler,Default_Handler

   .weak      I2C2_ER_IRQHandler
   .thumb_set I2C2_ER_IRQHandler,Default_Handler

   .weak      I2C3_EV_IRQHandler
   .thumb_set I2C3_EV_IRQHandler,Default_Handler

   .weak      I2C3_ER_IRQHandler
   .thumb_set I2C3_ER_IRQHandler,Default_Handler

   .weak      USART1_IRQHandler
   .thumb_set USART1_IRQHandler,Default_Handler

   .weak      USART2_IRQHandler
   .thumb_set USART2_IRQHandler,Default_Handler

   .weak      USART3_IRQHandler
   .thumb_set USART3_IRQHandler,Default_Handler

   .weak      UART4_IRQHandler
   .thumb_set UART4_IRQHandler,Default_Handler

   .weak      UART5_IRQHandler
   .thumb_set UART5_IRQHandler,Default_Handler

   .weak      UART7_IRQHandler
   .thumb_set UART7_IRQHandler,Default_Handler

   .weak      UART8_IRQHandler
   .thumb_set UART8_IRQHandler,Default_Handler

   .weak      I3C1_EV_IRQHandler
   .thumb_set I3C1_EV_IRQHandler,Default_Handler

   .weak      I3C1_ER_IRQHandler
   .thumb_set I3C1_ER_IRQHandler,Default_Handler

   .weak      OTG_HS_IRQHandler
   .thumb_set OTG_HS_IRQHandler,Default_Handler

   .weak      ETH_IRQHandler
   .thumb_set ETH_IRQHandler,Default_Handler

   .weak      CORDIC_IRQHandler
   .thumb_set CORDIC_IRQHandler,Default_Handler

   .weak      GFXTIM_IRQHandler
   .thumb_set GFXTIM_IRQHandler,Default_Handler

   .weak      DCMIPP_IRQHandler
   .thumb_set DCMIPP_IRQHandler,Default_Handler

   .weak      LTDC_IRQHandler
   .thumb_set LTDC_IRQHandler,Default_Handler

   .weak      LTDC_ER_IRQHandler
   .thumb_set LTDC_ER_IRQHandler,Default_Handler

   .weak      DMA2D_IRQHandler
   .thumb_set DMA2D_IRQHandler,Default_Handler

   .weak      JPEG_IRQHandler
   .thumb_set JPEG_IRQHandler,Default_Handler

   .weak      GFXMMU_IRQHandler
   .thumb_set GFXMMU_IRQHandler,Default_Handler

   .weak      I3C1_WKUP_IRQHandler
   .thumb_set I3C1_WKUP_IRQHandler,Default_Handler

   .weak      XSPI1_IRQHandler
   .thumb_set XSPI1_IRQHandler,Default_Handler

   .weak      XSPI2_IRQHandler
   .thumb_set XSPI2_IRQHandler,Default_Handler

   .weak      FMC_IRQHandler
   .thumb_set FMC_IRQHandler,Default_Handler

   .weak      SDMMC1_IRQHandler
   .thumb_set SDMMC1_IRQHandler,Default_Handler

   .weak      SDMMC2_IRQHandler
   .thumb_set SDMMC2_IRQHandler,Default_Handler

   .weak      OTG_FS_IRQHandler
   .thumb_set OTG_FS_IRQHandler,Default_Handler

   .weak      TIM12_IRQHandler
   .thumb_set TIM12_IRQHandler,Default_Handler

   .weak      TIM13_IRQHandler
   .thumb_set TIM13_IRQHandler,Default_Handler

   .weak      TIM14_IRQHandler
   .thumb_set TIM14_IRQHandler,Default_Handler

   .weak      TIM15_IRQHandler
   .thumb_set TIM15_IRQHandler,Default_Handler

   .weak      TIM16_IRQHandler
   .thumb_set TIM16_IRQHandler,Default_Handler

   .weak      TIM17_IRQHandler
   .thumb_set TIM17_IRQHandler,Default_Handler

   .weak      LPTIM1_IRQHandler
   .thumb_set LPTIM1_IRQHandler,Default_Handler

   .weak      LPTIM2_IRQHandler
   .thumb_set LPTIM2_IRQHandler,Default_Handler

   .weak      LPTIM3_IRQHandler
   .thumb_set LPTIM3_IRQHandler,Default_Handler

   .weak      LPTIM4_IRQHandler
   .thumb_set LPTIM4_IRQHandler,Default_Handler

   .weak      LPTIM5_IRQHandler
   .thumb_set LPTIM5_IRQHandler,Default_Handler

   .weak      SPDIF_RX_IRQHandler
   .thumb_set SPDIF_RX_IRQHandler,Default_Handler

   .weak      MDIOS_IRQHandler
   .thumb_set MDIOS_IRQHandler,Default_Handler

   .weak      ADF1_FLT0_IRQHandler
   .thumb_set ADF1_FLT0_IRQHandler,Default_Handler

   .weak      CRS_IRQHandler
   .thumb_set CRS_IRQHandler,Default_Handler

   .weak      UCPD1_IRQHandler
   .thumb_set UCPD1_IRQHandler,Default_Handler

   .weak      CEC_IRQHandler
   .thumb_set CEC_IRQHandler,Default_Handler

   .weak      PSSI_IRQHandler
   .thumb_set PSSI_IRQHandler,Default_Handler

   .weak      LPUART1_IRQHandler
   .thumb_set LPUART1_IRQHandler,Default_Handler

   .weak      WAKEUP_PIN_IRQHandler
   .thumb_set WAKEUP_PIN_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel8_IRQHandler
   .thumb_set GPDMA1_Channel8_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel9_IRQHandler
   .thumb_set GPDMA1_Channel9_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel10_IRQHandler
   .thumb_set GPDMA1_Channel10_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel11_IRQHandler
   .thumb_set GPDMA1_Channel11_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel12_IRQHandler
   .thumb_set GPDMA1_Channel12_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel13_IRQHandler
   .thumb_set GPDMA1_Channel13_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel14_IRQHandler
   .thumb_set GPDMA1_Channel14_IRQHandler,Default_Handler

   .weak      GPDMA1_Channel15_IRQHandler
   .thumb_set GPDMA1_Channel15_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel8_IRQHandler
   .thumb_set HPDMA1_Channel8_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel9_IRQHandler
   .thumb_set HPDMA1_Channel9_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel10_IRQHandler
   .thumb_set HPDMA1_Channel10_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel11_IRQHandler
   .thumb_set HPDMA1_Channel11_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel12_IRQHandler
   .thumb_set HPDMA1_Channel12_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel13_IRQHandler
   .thumb_set HPDMA1_Channel13_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel14_IRQHandler
   .thumb_set HPDMA1_Channel14_IRQHandler,Default_Handler

   .weak      HPDMA1_Channel15_IRQHandler
   .thumb_set HPDMA1_Channel15_IRQHandler,Default_Handler

   .weak      GPU2D_IRQHandler
   .thumb_set GPU2D_IRQHandler,Default_Handler

   .weak      GPU2D_ER_IRQHandler
   .thumb_set GPU2D_ER_IRQHandler,Default_Handler

   .weak      ICACHE_IRQHandler
   .thumb_set ICACHE_IRQHandler,Default_Handler

   .weak      FDCAN1_IT0_IRQHandler
   .thumb_set FDCAN1_IT0_IRQHandler,Default_Handler

   .weak      FDCAN1_IT1_IRQHandler
   .thumb_set FDCAN1_IT1_IRQHandler,Default_Handler

   .weak      FDCAN2_IT0_IRQHandler
   .thumb_set FDCAN2_IT0_IRQHandler,Default_Handler

   .weak      FDCAN2_IT1_IRQHandler
   .thumb_set FDCAN2_IT1_IRQHandler,Default_Handler

   .weak      SystemInit