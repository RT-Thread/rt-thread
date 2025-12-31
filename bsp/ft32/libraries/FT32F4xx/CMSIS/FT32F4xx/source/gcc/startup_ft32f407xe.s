/**
  ******************************************************************************
  * @file      startup_ft32f072xb.s
  * @author    MCD Application Team
  * @brief     FT32F407xE devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M0 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2006-2025 Fremontmicro
  * All rights reserved.
  *
  * This software component is licensed by FMD under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m4
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

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
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

  .word  WWDG_Handler
  .word  PVD_Handler
  .word  TAMP_STAMP_Handler
  .word  RTC_Handler
  .word  FLASH_Handler
  .word  RCC_Handler
  .word  EXTI0_Handler
  .word  EXTI1_Handler
  .word  EXTI2_Handler
  .word  EXTI3_Handler
  .word  EXTI4_Handler
  .word  DMA1_CH0_Handler
  .word  DMA1_CH1_Handler
  .word  DMA1_CH2_Handler
  .word  DMA1_CH3_Handler
  .word  DMA1_CH4_Handler
  .word  DMA1_CH5_Handler
  .word  DMA1_CH6_Handler
  .word  ADC_Handler
  .word  CAN1_Handler
  .word  CAN2_Handler
  .word  CAN3_Handler
  .word  CAN4_Handler
  .word  EXTI9_5_Handler
  .word  TIM1_BRK_TIM9_Handler
  .word  TIM1_UP_TIM1O_Handler
  .word  TIM1_TRG_COM_TIM11_Handler
  .word  TIM1_CC_Handler
  .word  TIM2_Handler
  .word  TIM3_Handler
  .word  TIM4_Handler
  .word  I2C1_Handler
  .word  I2C2_Handler
  .word  QSPI_Handler
  .word  SPI1_Handler
  .word  SPI2_Handler
  .word  USART1_Handler
  .word  USART2_Handler
  .word  USART3_Handler
  .word  EXTI15_10_Handler
  .word  RTCAlarm_Handler
  .word  OTG_FS_WKUP_Handler
  .word  TIM8_BRK_TIM12_Handler
  .word  TIM8_UP_TIM13_Handler
  .word  TIM8_TRG_COM_TIM14_Handler
  .word  TIM8_CC_Handler
  .word  DMA1_CH7_Handler
  .word  FMC_Handler
  .word  SDIO_Handler
  .word  TIM5_Handler
  .word  SPI3_Handler
  .word  UART4_Handler
  .word  UART5_Handler
  .word  TIM6_DAC_Handler
  .word  TIM7_Handler
  .word  DMA2_CH0_Handler
  .word  DMA2_CH1_Handler
  .word  DMA2_CH2_Handler
  .word  DMA2_CH3_Handler
  .word  DMA2_CH4_Handler
  .word  OTG_FS_Handler
  .word  DMA2_CH5_Handler
  .word  DMA2_CH6_Handler
  .word  DMA2_CH7_Handler
  .word  USART6_Handler
  .word  I2C3_Handler
  .word  OTG_HS_EP1_OUT_Handler
  .word  OTG_HS_EP1_IN_Handler
  .word  OTG_HS_WKUP_Handler
  .word  OTG_HS_Handler
  .word  RNG_Handler
  .word  FPU_Handler
  .word  CRS_Handler
  .word  SPDIF_Handler
  .word  SSI_AC97_Handler
  .word  ETH_WKUP_Handler
  .word  LPUART_Handler
  .word  LPTIM_Handler
  .word  ETH_SBD_Handler
  .word  ETH_PERCHTX_Handler
  .word  ETH_PERCHRX_Handler
  .word  EPWM1_Handler
  .word  EPWM1_TZ_Handler
  .word  EPWM2_Handler
  .word  EPWM2_TZ_Handler
  .word  EPWM3_Handler
  .word  EPWM3_TZ_Handler
  .word  EPWM4_Handler
  .word  EPWM4_TZ_Handler
  .word  ECAP_Handler
  .word  EQEP_Handler
  .word  DLL_CAL_Handler
  .word  COMP1_Handler
  .word  COMP2_Handler
  .word  COMP3_Handler
  .word  COMP4_Handler
  .word  COMP5_Handler
  .word  COMP6_Handler
  .word  ICACHE_Handler
  .word  DCACHE_Handler
  .word  UART7_Handler

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

  .weak      PVD_Handler
  .thumb_set PVD_Handler,Default_Handler

  .weak      TAMP_STAMP_Handler
  .thumb_set TAMP_STAMP_Handler,Default_Handler

  .weak      RTC_Handler
  .thumb_set RTC_Handler,Default_Handler

  .weak      FLASH_Handler
  .thumb_set FLASH_Handler,Default_Handler

  .weak      RCC_Handler
  .thumb_set RCC_Handler,Default_Handler

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

  .weak      DMA1_CH0_Handler
  .thumb_set DMA1_CH0_Handler,Default_Handler

  .weak      DMA1_CH1_Handler
  .thumb_set DMA1_CH1_Handler,Default_Handler

  .weak      DMA1_CH2_Handler
  .thumb_set DMA1_CH2_Handler,Default_Handler

  .weak      DMA1_CH3_Handler
  .thumb_set DMA1_CH3_Handler,Default_Handler

  .weak      DMA1_CH4_Handler
  .thumb_set DMA1_CH4_Handler,Default_Handler

  .weak      DMA1_CH5_Handler
  .thumb_set DMA1_CH5_Handler,Default_Handler

  .weak      DMA1_CH6_Handler
  .thumb_set DMA1_CH6_Handler,Default_Handler

  .weak      ADC_Handler
  .thumb_set ADC_Handler,Default_Handler

  .weak      CAN1_Handler
  .thumb_set CAN1_Handler,Default_Handler

  .weak      CAN2_Handler
  .thumb_set CAN2_Handler,Default_Handler

  .weak      CAN3_Handler
  .thumb_set CAN3_Handler,Default_Handler

  .weak      CAN4_Handler
  .thumb_set CAN4_Handler,Default_Handler

  .weak      EXTI9_5_Handler
  .thumb_set EXTI9_5_Handler,Default_Handler

  .weak      TIM1_BRK_TIM9_Handler
  .thumb_set TIM1_BRK_TIM9_Handler,Default_Handler

  .weak      TIM1_UP_TIM1O_Handler
  .thumb_set TIM1_UP_TIM1O_Handler,Default_Handler

  .weak      TIM1_TRG_COM_TIM11_Handler
  .thumb_set TIM1_TRG_COM_TIM11_Handler,Default_Handler

  .weak      TIM1_CC_Handler
  .thumb_set TIM1_CC_Handler,Default_Handler

  .weak      TIM2_Handler
  .thumb_set TIM2_Handler,Default_Handler

  .weak      TIM3_Handler
  .thumb_set TIM3_Handler,Default_Handler

  .weak      TIM4_Handler
  .thumb_set TIM4_Handler,Default_Handler

  .weak      I2C1_Handler
  .thumb_set I2C1_Handler,Default_Handler

  .weak      I2C2_Handler
  .thumb_set I2C2_Handler,Default_Handler

  .weak      QSPI_Handler
  .thumb_set QSPI_Handler,Default_Handler

  .weak      SPI1_Handler
  .thumb_set SPI1_Handler,Default_Handler

  .weak      SPI2_Handler
  .thumb_set SPI2_Handler,Default_Handler

  .weak      USART1_Handler
  .thumb_set USART1_Handler,Default_Handler

  .weak      USART2_Handler
  .thumb_set USART2_Handler,Default_Handler

  .weak      USART3_Handler
  .thumb_set USART3_Handler,Default_Handler

  .weak      EXTI15_10_Handler
  .thumb_set EXTI15_10_Handler,Default_Handler

  .weak      RTCAlarm_Handler
  .thumb_set RTCAlarm_Handler,Default_Handler

  .weak      OTG_FS_WKUP_Handler
  .thumb_set OTG_FS_WKUP_Handler,Default_Handler

  .weak      TIM8_BRK_TIM12_Handler
  .thumb_set TIM8_BRK_TIM12_Handler,Default_Handler

  .weak      TIM8_UP_TIM13_Handler
  .thumb_set TIM8_UP_TIM13_Handler,Default_Handler

  .weak      TIM8_TRG_COM_TIM14_Handler
  .thumb_set TIM8_TRG_COM_TIM14_Handler,Default_Handler

  .weak      TIM8_CC_Handler
  .thumb_set TIM8_CC_Handler,Default_Handler

  .weak      DMA1_CH7_Handler
  .thumb_set DMA1_CH7_Handler,Default_Handler

  .weak      FMC_Handler
  .thumb_set FMC_Handler,Default_Handler

  .weak      SDIO_Handler
  .thumb_set SDIO_Handler,Default_Handler

  .weak      TIM5_Handler
  .thumb_set TIM5_Handler,Default_Handler

  .weak      SPI3_Handler
  .thumb_set SPI3_Handler,Default_Handler

  .weak      UART4_Handler
  .thumb_set UART4_Handler,Default_Handler

  .weak      UART5_Handler
  .thumb_set UART5_Handler,Default_Handler

  .weak      TIM6_DAC_Handler
  .thumb_set TIM6_DAC_Handler,Default_Handler

  .weak      TIM7_Handler
  .thumb_set TIM7_Handler,Default_Handler

  .weak      DMA2_CH0_Handler
  .thumb_set DMA2_CH0_Handler,Default_Handler

  .weak      DMA2_CH1_Handler
  .thumb_set DMA2_CH1_Handler,Default_Handler

  .weak      DMA2_CH2_Handler
  .thumb_set DMA2_CH2_Handler,Default_Handler

  .weak      DMA2_CH3_Handler
  .thumb_set DMA2_CH3_Handler,Default_Handler

  .weak      DMA2_CH4_Handler
  .thumb_set DMA2_CH4_Handler,Default_Handler

  .weak      OTG_FS_Handler
  .thumb_set OTG_FS_Handler,Default_Handler

  .weak      DMA2_CH5_Handler
  .thumb_set DMA2_CH5_Handler,Default_Handler

  .weak      DMA2_CH6_Handler
  .thumb_set DMA2_CH6_Handler,Default_Handler

  .weak      DMA2_CH7_Handler
  .thumb_set DMA2_CH7_Handler,Default_Handler

  .weak      USART6_Handler
  .thumb_set USART6_Handler,Default_Handler

  .weak      I2C3_Handler
  .thumb_set I2C3_Handler,Default_Handler

  .weak      OTG_HS_EP1_OUT_Handler
  .thumb_set OTG_HS_EP1_OUT_Handler,Default_Handler

  .weak      OTG_HS_EP1_IN_Handler
  .thumb_set OTG_HS_EP1_IN_Handler,Default_Handler

  .weak      OTG_HS_WKUP_Handler
  .thumb_set OTG_HS_WKUP_Handler,Default_Handler

  .weak      OTG_HS_Handler
  .thumb_set OTG_HS_Handler,Default_Handler

  .weak      RNG_Handler
  .thumb_set RNG_Handler,Default_Handler

  .weak      FPU_Handler
  .thumb_set FPU_Handler,Default_Handler

  .weak      CRS_Handler
  .thumb_set CRS_Handler,Default_Handler

  .weak      SPDIF_Handler
  .thumb_set SPDIF_Handler,Default_Handler

  .weak      SSI_AC97_Handler
  .thumb_set SSI_AC97_Handler,Default_Handler

  .weak      ETH_WKUP_Handler
  .thumb_set ETH_WKUP_Handler,Default_Handler

  .weak      LPUART_Handler
  .thumb_set LPUART_Handler,Default_Handler

  .weak      LPTIM_Handler
  .thumb_set LPTIM_Handler,Default_Handler

  .weak      ETH_SBD_Handler
  .thumb_set ETH_SBD_Handler,Default_Handler

  .weak      ETH_PERCHTX_Handler
  .thumb_set ETH_PERCHTX_Handler,Default_Handler

  .weak      ETH_PERCHRX_Handler
  .thumb_set ETH_PERCHRX_Handler,Default_Handler

  .weak      EPWM1_Handler
  .thumb_set EPWM1_Handler,Default_Handler

  .weak      EPWM1_TZ_Handler
  .thumb_set EPWM1_TZ_Handler,Default_Handler

  .weak      EPWM2_Handler
  .thumb_set EPWM2_Handler,Default_Handler

  .weak      EPWM2_TZ_Handler
  .thumb_set EPWM2_TZ_Handler,Default_Handler

  .weak      EPWM3_Handler
  .thumb_set EPWM3_Handler,Default_Handler

  .weak      EPWM3_TZ_Handler
  .thumb_set EPWM3_TZ_Handler,Default_Handler

  .weak      EPWM4_Handler
  .thumb_set EPWM4_Handler,Default_Handler

  .weak      EPWM4_TZ_Handler
  .thumb_set EPWM4_TZ_Handler,Default_Handler

  .weak      ECAP_Handler
  .thumb_set ECAP_Handler,Default_Handler

  .weak      EQEP_Handler
  .thumb_set EQEP_Handler,Default_Handler

  .weak      DLL_CAL_Handler
  .thumb_set DLL_CAL_Handler,Default_Handler

  .weak      COMP1_Handler
  .thumb_set COMP1_Handler,Default_Handler

  .weak      COMP2_Handler
  .thumb_set COMP2_Handler,Default_Handler

  .weak      COMP3_Handler
  .thumb_set COMP3_Handler,Default_Handler

  .weak      COMP4_Handler
  .thumb_set COMP4_Handler,Default_Handler

  .weak      COMP5_Handler
  .thumb_set COMP5_Handler,Default_Handler

  .weak      COMP6_Handler
  .thumb_set COMP6_Handler,Default_Handler

  .weak      ICACHE_Handler
  .thumb_set ICACHE_Handler,Default_Handler

  .weak      DCACHE_Handler
  .thumb_set DCACHE_Handler,Default_Handler

  .weak      UART7_Handler
  .thumb_set UART7_Handler,Default_Handler

/************************ (C) COPYRIGHT Fremontmicro *****END OF FILE****/

