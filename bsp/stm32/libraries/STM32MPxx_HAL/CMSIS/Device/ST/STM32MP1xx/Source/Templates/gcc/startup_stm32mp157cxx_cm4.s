/**
  ******************************************************************************
  * @file      startup_stm32mp157c_cm4.s
  * @author    MCD Application Team
  * @brief     STM32MP15xx Devices vector table for GCC based toolchain. 
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
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

  .section .startup_copro_fw.Reset_Handler,"ax"
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack      /* set stack pointer */

/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      _sidata: End of code section, i.e., begin of data sections to copy from.
 *      _sdata/_edata: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */
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
 // ldr r0, =SystemInit
 // blx r0
/* Call static constructors */
 bl __libc_init_array
 // ldr r0, =__libc_init_array
 // blx r0
/* Call the application's entry point.*/
  bl entry
  //ldr r0, =main
  //blx r0

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
* The minimal vector table for a Cortex M4.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack                           // Top of Stack
  .word  Reset_Handler                     // Reset Handler
  .word  NMI_Handler                       // NMI Handler
  .word  HardFault_Handler                 // Hard Fault Handler
  .word  MemManage_Handler                 // MPU Fault Handler
  .word  BusFault_Handler                  // Bus Fault Handler
  .word  UsageFault_Handler                // Usage Fault Handler
  .word  0                                 // Reserved
  .word  0                                 // Reserved
  .word  0                                 // Reserved
  .word  0                                 // Reserved
  .word  SVC_Handler                       // SVCall Handler
  .word  DebugMon_Handler                  // Debug Monitor Handler
  .word  0                                 // Reserved
  .word  PendSV_Handler                    // PendSV Handler
  .word  SysTick_Handler                   // SysTick Handler

                // External Interrupts
  .word  WWDG1_IRQHandler                  // Window WatchDog 1
  .word  PVD_AVD_IRQHandler                // PVD and AVD through EXTI Line detection                        
  .word  TAMP_IRQHandler                   // Tamper and TimeStamps through the EXTI line
  .word  RTC_WKUP_ALARM_IRQHandler         // RTC Wakeup and Alarm through the EXTI line
  .word  RESERVED4_IRQHandler              // Reserved
  .word  RCC_IRQHandler                    // RCC                                             
  .word  EXTI0_IRQHandler                  // EXTI Line0                                             
  .word  EXTI1_IRQHandler                  // EXTI Line1                                             
  .word  EXTI2_IRQHandler                  // EXTI Line2                                             
  .word  EXTI3_IRQHandler                  // EXTI Line3                                             
  .word  EXTI4_IRQHandler                  // EXTI Line4 
  .word  DMA1_Stream0_IRQHandler           // DMA1 Stream 0
  .word  DMA1_Stream1_IRQHandler           // DMA1 Stream 1                                   
  .word  DMA1_Stream2_IRQHandler           // DMA1 Stream 2                                   
  .word  DMA1_Stream3_IRQHandler           // DMA1 Stream 3                                   
  .word  DMA1_Stream4_IRQHandler           // DMA1 Stream 4                                   
  .word  DMA1_Stream5_IRQHandler           // DMA1 Stream 5
  .word  DMA1_Stream6_IRQHandler           // DMA1 Stream 6 
  .word  ADC1_IRQHandler                   // ADC1                             
  .word  FDCAN1_IT0_IRQHandler        // FDCAN1 Interrupt line 0
  .word  FDCAN2_IT0_IRQHandler        // FDCAN2 Interrupt line 0
  .word  FDCAN1_IT1_IRQHandler        // FDCAN1 Interrupt line 1
  .word  FDCAN2_IT1_IRQHandler        // FDCAN2 Interrupt line 1
  .word  EXTI5_IRQHandler                  // External Line5 interrupts through AIEC
  .word  TIM1_BRK_IRQHandler               // TIM1 Break interrupt
  .word  TIM1_UP_IRQHandler                 // TIM1 Update Interrupt
  .word  TIM1_TRG_COM_IRQHandler           // TIM1 Trigger and Commutation Interrupt
  .word  TIM1_CC_IRQHandler                // TIM1 Capture Compare                                   
  .word  TIM2_IRQHandler                   // TIM2                                            
  .word  TIM3_IRQHandler                   // TIM3                                            
  .word  TIM4_IRQHandler                   // TIM4                                            
  .word  I2C1_EV_IRQHandler                // I2C1 Event                                             
  .word  I2C1_ER_IRQHandler                // I2C1 Error                                             
  .word  I2C2_EV_IRQHandler                // I2C2 Event                                             
  .word  I2C2_ER_IRQHandler                // I2C2 Error                                               
  .word  SPI1_IRQHandler                   // SPI1                                            
  .word  SPI2_IRQHandler                   // SPI2                                            
  .word  USART1_IRQHandler                 // USART1                                          
  .word  USART2_IRQHandler                 // USART2                                          
  .word  USART3_IRQHandler                 // USART3                                          
  .word  EXTI10_IRQHandler                 // External Line10 interrupts through AIEC
  .word  RTC_TIMESTAMP_IRQHandler          // RTC TimeStamp through EXTI Line
  .word  EXTI11_IRQHandler                 // External Line11 interrupts through AIEC
  .word  TIM8_BRK_IRQHandler               // TIM8 Break Interrupt
  .word  TIM8_UP_IRQHandler                // TIM8 Update Interrupt
  .word  TIM8_TRG_COM_IRQHandler           // TIM8 Trigger and Commutation Interrupt
  .word  TIM8_CC_IRQHandler                // TIM8 Capture Compare Interrupt
  .word  DMA1_Stream7_IRQHandler           // DMA1 Stream7                                           
  .word  FMC_IRQHandler                    // FMC                             
  .word  SDMMC1_IRQHandler                 // SDMMC1
  .word  TIM5_IRQHandler                   // TIM5                            
  .word  SPI3_IRQHandler                   // SPI3                            
  .word  UART4_IRQHandler                  // UART4                           
  .word  UART5_IRQHandler                  // UART5                           
  .word  TIM6_IRQHandler                   // TIM6
  .word  TIM7_IRQHandler                   // TIM7           
  .word  DMA2_Stream0_IRQHandler           // DMA2 Stream 0                   
  .word  DMA2_Stream1_IRQHandler           // DMA2 Stream 1                   
  .word  DMA2_Stream2_IRQHandler           // DMA2 Stream 2                   
  .word  DMA2_Stream3_IRQHandler           // DMA2 Stream 3                   
  .word  DMA2_Stream4_IRQHandler           // DMA2 Stream 4                   
  .word  ETH1_IRQHandler                    // Ethernet                        
  .word  ETH1_WKUP_IRQHandler               // Ethernet Wakeup through EXTI line              
  .word  FDCAN_CAL_IRQHandler               // FDCAN Calibration
  .word  EXTI6_IRQHandler                  // EXTI Line6 interrupts through AIEC
  .word  EXTI7_IRQHandler                  // EXTI Line7 interrupts through AIEC
  .word  EXTI8_IRQHandler                  // EXTI Line8 interrupts through AIEC
  .word  EXTI9_IRQHandler                  // EXTI Line9 interrupts through AIEC
  .word  DMA2_Stream5_IRQHandler           // DMA2 Stream 5                   
  .word  DMA2_Stream6_IRQHandler           // DMA2 Stream 6                   
  .word  DMA2_Stream7_IRQHandler           // DMA2 Stream 7                   
  .word  USART6_IRQHandler                 // USART6                           
  .word  I2C3_EV_IRQHandler                // I2C3 event                             
  .word  I2C3_ER_IRQHandler                // I2C3 error                             
  .word  USBH_OHCI_IRQHandler              // USB Host OHCI
  .word  USBH_EHCI_IRQHandler              // USB Host EHCI
  .word  EXTI12_IRQHandler                 // EXTI Line12 interrupts through AIEC
  .word  EXTI13_IRQHandler                 // EXTI Line13 interrupts through AIEC
  .word  DCMI_IRQHandler                   // DCMI                            
  .word  CRYP1_IRQHandler                  // Crypto1 global interrupt
  .word  HASH1_IRQHandler                  // Crypto Hash1 interrupt
  .word  FPU_IRQHandler                    // FPU
  .word  UART7_IRQHandler                  // UART7
  .word  UART8_IRQHandler                  // UART8
  .word  SPI4_IRQHandler                   // SPI4
  .word  SPI5_IRQHandler                   // SPI5
  .word  SPI6_IRQHandler                   // SPI6
  .word  SAI1_IRQHandler                   // SAI1
  .word  LTDC_IRQHandler                   // LTDC
  .word  LTDC_ER_IRQHandler                // LTDC error
  .word  ADC2_IRQHandler                   // ADC2 
  .word  SAI2_IRQHandler                   // SAI2
  .word  QUADSPI_IRQHandler                // QUADSPI
  .word  LPTIM1_IRQHandler                 // LPTIM1 global interrupt
  .word  CEC_IRQHandler                    // HDMI_CEC
  .word  I2C4_EV_IRQHandler                // I2C4 Event                             
  .word  I2C4_ER_IRQHandler                // I2C4 Error 
  .word  SPDIF_RX_IRQHandler               // SPDIF_RX
  .word  OTG_IRQHandler                    // USB On The Go HS global interrupt
  .word  RESERVED99_IRQHandler             // Reserved
  .word  IPCC_RX0_IRQHandler               // Mailbox RX0 Free interrupt
  .word  IPCC_TX0_IRQHandler               // Mailbox TX0 Free interrupt
  .word  DMAMUX1_OVR_IRQHandler            // DMAMUX1 Overrun interrupt
  .word  IPCC_RX1_IRQHandler               // Mailbox RX1 Free interrupt
  .word  IPCC_TX1_IRQHandler               // Mailbox TX1 Free interrupt
  .word  CRYP2_IRQHandler                  // Crypto2 global interrupt
  .word  HASH2_IRQHandler                  // Crypto Hash2 interrupt
  .word  I2C5_EV_IRQHandler                // I2C5 Event Interrupt
  .word  I2C5_ER_IRQHandler                // I2C5 Error Interrupt
  .word  GPU_IRQHandler                    // GPU Global Interrupt
  .word  DFSDM1_FLT0_IRQHandler            // DFSDM Filter0 Interrupt
  .word  DFSDM1_FLT1_IRQHandler            // DFSDM Filter1 Interrupt
  .word  DFSDM1_FLT2_IRQHandler            // DFSDM Filter2 Interrupt
  .word  DFSDM1_FLT3_IRQHandler            // DFSDM Filter3 Interrupt
  .word  SAI3_IRQHandler                   // SAI3 global Interrupt
  .word  DFSDM1_FLT4_IRQHandler            // DFSDM Filter4 Interrupt
  .word  TIM15_IRQHandler                  // TIM15 global Interrupt
  .word  TIM16_IRQHandler                  // TIM16 global Interrupt
  .word  TIM17_IRQHandler                  // TIM17 global Interrupt
  .word  TIM12_IRQHandler                  // TIM12 global Interrupt
  .word  MDIOS_IRQHandler                  // MDIOS global Interrupt
  .word  EXTI14_IRQHandler                 // EXTI Line14 interrupts through AIEC
  .word  MDMA_IRQHandler                   // MDMA global Interrupt
  .word  DSI_IRQHandler                    // DSI global Interrupt
  .word  SDMMC2_IRQHandler                 // SDMMC2 global Interrupt
  .word  HSEM_IT2_IRQHandler               // HSEM global Interrupt
  .word  DFSDM1_FLT5_IRQHandler            // DFSDM Filter5 Interrupt
  .word  EXTI15_IRQHandler                 // EXTI Line15 interrupts through AIEC
  .word  nCTIIRQ1_IRQHandler               // Cortex-M4 CTI interrupt 1
  .word  nCTIIRQ2_IRQHandler               // Cortex-M4 CTI interrupt 2
  .word  TIM13_IRQHandler                  // TIM13 global interrupt
  .word  TIM14_IRQHandler                  // TIM14 global interrupt
  .word  DAC_IRQHandler                    // DAC1 and DAC2 underrun error interrupts
  .word  RNG1_IRQHandler                   // RNG1 interrupt
  .word  RNG2_IRQHandler                   // RNG2 interrupt
  .word  I2C6_EV_IRQHandler                // I2C6 Event Interrupt
  .word  I2C6_ER_IRQHandler                // I2C6 Error Interrupt
  .word  SDMMC3_IRQHandler                 // SDMMC3 global Interrupt
  .word  LPTIM2_IRQHandler                 // LPTIM2 global interrupt
  .word  LPTIM3_IRQHandler                 // LPTIM3 global interrupt
  .word  LPTIM4_IRQHandler                 // LPTIM4 global interrupt
  .word  LPTIM5_IRQHandler                 // LPTIM5 global interrupt
  .word  ETH1_LPI_IRQHandler               // ETH1_LPI interrupt 
  .word  RESERVED143_IRQHandler            // Reserved
  .word  MPU_SEV_IRQHandler                // MPU Send Event through AIEC
  .word  RCC_WAKEUP_IRQHandler             // RCC Wake up interrupt
  .word  SAI4_IRQHandler                   // SAI4 global interrupt
  .word  DTS_IRQHandler                    // Temperature sensor interrupt
  .word  RESERVED148_IRQHandler            // Reserved
  .word  WAKEUP_PIN_IRQHandler             // Interrupt for all 6 wake-up pins

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

  .weak      RESERVED4_IRQHandler
  .thumb_set RESERVED4_IRQHandler,Default_Handler

  .weak      RESERVED99_IRQHandler
  .thumb_set RESERVED99_IRQHandler,Default_Handler

  .weak      ETH1_LPI_IRQHandler
  .thumb_set ETH1_LPI_IRQHandler,Default_Handler

  .weak      RESERVED143_IRQHandler
  .thumb_set RESERVED143_IRQHandler,Default_Handler

  .weak      WWDG1_IRQHandler
  .thumb_set WWDG1_IRQHandler,Default_Handler

  .weak      PVD_AVD_IRQHandler                      
  .thumb_set PVD_AVD_IRQHandler,Default_Handler
                           
  .weak      TAMP_IRQHandler
  .thumb_set TAMP_IRQHandler,Default_Handler
     
  .weak      RTC_WKUP_ALARM_IRQHandler
  .thumb_set RTC_WKUP_ALARM_IRQHandler,Default_Handler
                                                        
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
                                                                               
  .weak      DMA1_Stream0_IRQHandler
  .thumb_set DMA1_Stream0_IRQHandler,Default_Handler

  .weak      DMA1_Stream1_IRQHandler             
  .thumb_set DMA1_Stream1_IRQHandler,Default_Handler
                          
  .weak      DMA1_Stream2_IRQHandler             
  .thumb_set DMA1_Stream2_IRQHandler,Default_Handler
                       
  .weak      DMA1_Stream3_IRQHandler             
  .thumb_set DMA1_Stream3_IRQHandler,Default_Handler
                      
  .weak      DMA1_Stream4_IRQHandler             
  .thumb_set DMA1_Stream4_IRQHandler,Default_Handler
                          
  .weak      DMA1_Stream5_IRQHandler             
  .thumb_set DMA1_Stream5_IRQHandler,Default_Handler
                            
  .weak      DMA1_Stream6_IRQHandler             
  .thumb_set DMA1_Stream6_IRQHandler,Default_Handler
  
  .weak      ADC1_IRQHandler                      
  .thumb_set ADC1_IRQHandler,Default_Handler
  
  .weak      ADC2_IRQHandler                      
  .thumb_set ADC2_IRQHandler,Default_Handler
                            
  .weak      FDCAN1_IT0_IRQHandler
  .thumb_set FDCAN1_IT0_IRQHandler,Default_Handler

  .weak      FDCAN2_IT0_IRQHandler
  .thumb_set FDCAN2_IT0_IRQHandler,Default_Handler

  .weak      FDCAN1_IT1_IRQHandler
  .thumb_set FDCAN1_IT1_IRQHandler,Default_Handler
                                              
  .weak      FDCAN2_IT1_IRQHandler
  .thumb_set FDCAN2_IT1_IRQHandler,Default_Handler

  .weak      FDCAN_CAL_IRQHandler
  .thumb_set FDCAN_CAL_IRQHandler,Default_Handler
                                                                                      
  .weak      EXTI5_IRQHandler
  .thumb_set EXTI5_IRQHandler,Default_Handler
                                      
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
                                           
  .weak      EXTI10_IRQHandler
  .thumb_set EXTI10_IRQHandler,Default_Handler
                                    
  .weak      RTC_TIMESTAMP_IRQHandler
  .thumb_set RTC_TIMESTAMP_IRQHandler,Default_Handler
                    
  .weak      EXTI11_IRQHandler
  .thumb_set EXTI11_IRQHandler,Default_Handler

  .weak      TIM8_BRK_IRQHandler
  .thumb_set TIM8_BRK_IRQHandler,Default_Handler
                   
  .weak      TIM8_UP_IRQHandler
  .thumb_set TIM8_UP_IRQHandler,Default_Handler
                   
  .weak      TIM8_TRG_COM_IRQHandler
  .thumb_set TIM8_TRG_COM_IRQHandler,Default_Handler
   
  .weak      TIM8_CC_IRQHandler                  
  .thumb_set TIM8_CC_IRQHandler,Default_Handler
                                     
  .weak      DMA1_Stream7_IRQHandler             
  .thumb_set DMA1_Stream7_IRQHandler,Default_Handler
                                            
  .weak      FMC_IRQHandler                      
  .thumb_set FMC_IRQHandler,Default_Handler
                                               
  .weak      SDMMC1_IRQHandler
  .thumb_set SDMMC1_IRQHandler,Default_Handler
                                               
  .weak      TIM5_IRQHandler                     
  .thumb_set TIM5_IRQHandler,Default_Handler
                                               
  .weak      SPI3_IRQHandler                     
  .thumb_set SPI3_IRQHandler,Default_Handler
                                               
  .weak      UART4_IRQHandler                    
  .thumb_set UART4_IRQHandler,Default_Handler
                                              
  .weak      UART5_IRQHandler                    
  .thumb_set UART5_IRQHandler,Default_Handler
                                              
  .weak      TIM6_IRQHandler
  .thumb_set TIM6_IRQHandler,Default_Handler
                     
  .weak      TIM7_IRQHandler                     
  .thumb_set TIM7_IRQHandler,Default_Handler
                      
  .weak      DMA2_Stream0_IRQHandler             
  .thumb_set DMA2_Stream0_IRQHandler,Default_Handler
                                    
  .weak      DMA2_Stream1_IRQHandler             
  .thumb_set DMA2_Stream1_IRQHandler,Default_Handler
                                     
  .weak      DMA2_Stream2_IRQHandler             
  .thumb_set DMA2_Stream2_IRQHandler,Default_Handler
                                      
  .weak      DMA2_Stream3_IRQHandler             
  .thumb_set DMA2_Stream3_IRQHandler,Default_Handler
                                      
  .weak      DMA2_Stream4_IRQHandler             
  .thumb_set DMA2_Stream4_IRQHandler,Default_Handler
                                   
  .weak      ETH1_IRQHandler                      
  .thumb_set ETH1_IRQHandler,Default_Handler
                                           
  .weak      ETH1_WKUP_IRQHandler                 
  .thumb_set ETH1_WKUP_IRQHandler,Default_Handler
  
  .weak      ETH1_LPI_IRQHandler                 
  .thumb_set ETH1_LPI_IRQHandler,Default_Handler 
                       
  .weak      EXTI6_IRQHandler
  .thumb_set EXTI6_IRQHandler,Default_Handler
                                         
  .weak      EXTI7_IRQHandler
  .thumb_set EXTI7_IRQHandler,Default_Handler

  .weak      EXTI8_IRQHandler
  .thumb_set EXTI8_IRQHandler,Default_Handler

  .weak      EXTI9_IRQHandler
  .thumb_set EXTI9_IRQHandler,Default_Handler

  .weak      DMA2_Stream5_IRQHandler             
  .thumb_set DMA2_Stream5_IRQHandler,Default_Handler
                                     
  .weak      DMA2_Stream6_IRQHandler             
  .thumb_set DMA2_Stream6_IRQHandler,Default_Handler
                                     
  .weak      DMA2_Stream7_IRQHandler             
  .thumb_set DMA2_Stream7_IRQHandler,Default_Handler
                                     
  .weak      USART6_IRQHandler                   
  .thumb_set USART6_IRQHandler,Default_Handler
                                             
  .weak      I2C3_EV_IRQHandler                  
  .thumb_set I2C3_EV_IRQHandler,Default_Handler
                                                
  .weak      I2C3_ER_IRQHandler                  
  .thumb_set I2C3_ER_IRQHandler,Default_Handler
                                                
  .weak      USBH_OHCI_IRQHandler
  .thumb_set USBH_OHCI_IRQHandler,Default_Handler
                        
  .weak      USBH_EHCI_IRQHandler
  .thumb_set USBH_EHCI_IRQHandler,Default_Handler
                        
  .weak      EXTI12_IRQHandler
  .thumb_set EXTI12_IRQHandler,Default_Handler

  .weak      EXTI13_IRQHandler
  .thumb_set EXTI13_IRQHandler,Default_Handler
                                        
  .weak      DCMI_IRQHandler                     
  .thumb_set DCMI_IRQHandler,Default_Handler
                                               
  .weak      CRYP1_IRQHandler
  .thumb_set CRYP1_IRQHandler,Default_Handler

  .weak      HASH1_IRQHandler
  .thumb_set HASH1_IRQHandler,Default_Handler

  .weak      FPU_IRQHandler                      
  .thumb_set FPU_IRQHandler,Default_Handler
  
  .weak      UART7_IRQHandler                    
  .thumb_set UART7_IRQHandler,Default_Handler
  
  .weak      UART8_IRQHandler                    
  .thumb_set UART8_IRQHandler,Default_Handler
  
  .weak      SPI4_IRQHandler                     
  .thumb_set SPI4_IRQHandler,Default_Handler
  
  .weak      SPI5_IRQHandler                     
  .thumb_set SPI5_IRQHandler,Default_Handler
  
  .weak      SPI6_IRQHandler                     
  .thumb_set SPI6_IRQHandler,Default_Handler
  
  .weak      SAI1_IRQHandler                     
  .thumb_set SAI1_IRQHandler,Default_Handler
  
  .weak      LTDC_IRQHandler                     
  .thumb_set LTDC_IRQHandler,Default_Handler
  
  .weak      LTDC_ER_IRQHandler                  
  .thumb_set LTDC_ER_IRQHandler,Default_Handler
  
  .weak      SAI2_IRQHandler                     
  .thumb_set SAI2_IRQHandler,Default_Handler
     
  .weak      QUADSPI_IRQHandler                  
  .thumb_set QUADSPI_IRQHandler,Default_Handler
  
  .weak      LPTIM1_IRQHandler
  .thumb_set LPTIM1_IRQHandler,Default_Handler
  
  .weak      CEC_IRQHandler                      
  .thumb_set CEC_IRQHandler,Default_Handler
     
  .weak      I2C4_EV_IRQHandler                  
  .thumb_set I2C4_EV_IRQHandler,Default_Handler
  
  .weak      I2C4_ER_IRQHandler                  
  .thumb_set I2C4_ER_IRQHandler,Default_Handler
   
  .weak      SPDIF_RX_IRQHandler                 
  .thumb_set SPDIF_RX_IRQHandler,Default_Handler

  .weak      OTG_IRQHandler
  .thumb_set OTG_IRQHandler,Default_Handler
  
  .weak      IPCC_RX0_IRQHandler
  .thumb_set IPCC_RX0_IRQHandler,Default_Handler

  .weak      IPCC_TX0_IRQHandler
  .thumb_set IPCC_TX0_IRQHandler,Default_Handler

  .weak      DMAMUX1_OVR_IRQHandler
  .thumb_set DMAMUX1_OVR_IRQHandler,Default_Handler

  .weak      IPCC_RX1_IRQHandler
  .thumb_set IPCC_RX1_IRQHandler,Default_Handler
  
  .weak      IPCC_TX1_IRQHandler
  .thumb_set IPCC_TX1_IRQHandler,Default_Handler

  .weak      CRYP2_IRQHandler
  .thumb_set CRYP2_IRQHandler,Default_Handler

  .weak      HASH2_IRQHandler
  .thumb_set HASH2_IRQHandler,Default_Handler

  .weak      I2C5_EV_IRQHandler
  .thumb_set I2C5_EV_IRQHandler,Default_Handler

  .weak      I2C5_ER_IRQHandler
  .thumb_set I2C5_ER_IRQHandler,Default_Handler

  .weak      GPU_IRQHandler
  .thumb_set GPU_IRQHandler,Default_Handler

  .weak      DFSDM1_FLT0_IRQHandler
  .thumb_set DFSDM1_FLT0_IRQHandler,Default_Handler
                                               
  .weak      DFSDM1_FLT1_IRQHandler
  .thumb_set DFSDM1_FLT1_IRQHandler,Default_Handler
                                               
  .weak      DFSDM1_FLT2_IRQHandler
  .thumb_set DFSDM1_FLT2_IRQHandler,Default_Handler
                                               
  .weak      DFSDM1_FLT3_IRQHandler
  .thumb_set DFSDM1_FLT3_IRQHandler,Default_Handler
                                               
  .weak      SAI3_IRQHandler                        
  .thumb_set SAI3_IRQHandler,Default_Handler

  .weak      DFSDM1_FLT4_IRQHandler
  .thumb_set DFSDM1_FLT4_IRQHandler,Default_Handler
                                               
  .weak      TIM15_IRQHandler                       
  .thumb_set TIM15_IRQHandler,Default_Handler
                                               
  .weak      TIM16_IRQHandler                       
  .thumb_set TIM16_IRQHandler,Default_Handler
                                                
  .weak      TIM17_IRQHandler                       
  .thumb_set TIM17_IRQHandler,Default_Handler

  .weak      TIM12_IRQHandler                       
  .thumb_set TIM12_IRQHandler,Default_Handler
  
  .weak      MDIOS_IRQHandler                       
  .thumb_set MDIOS_IRQHandler,Default_Handler
                                                
  .weak      EXTI14_IRQHandler
  .thumb_set EXTI14_IRQHandler,Default_Handler
                                                 
  .weak      MDMA_IRQHandler                        
  .thumb_set MDMA_IRQHandler,Default_Handler
                                                 
  .weak      DSI_IRQHandler                         
  .thumb_set DSI_IRQHandler,Default_Handler 
                                                
  .weak      SDMMC2_IRQHandler                      
  .thumb_set SDMMC2_IRQHandler,Default_Handler

  .weak      HSEM_IT2_IRQHandler
  .thumb_set HSEM_IT2_IRQHandler,Default_Handler

  .weak      DFSDM1_FLT5_IRQHandler
  .thumb_set DFSDM1_FLT5_IRQHandler,Default_Handler
                                                 
  .weak      EXTI15_IRQHandler
  .thumb_set EXTI15_IRQHandler,Default_Handler

  .weak      nCTIIRQ1_IRQHandler
  .thumb_set nCTIIRQ1_IRQHandler,Default_Handler

  .weak      nCTIIRQ2_IRQHandler
  .thumb_set nCTIIRQ2_IRQHandler,Default_Handler

  .weak      TIM13_IRQHandler
  .thumb_set TIM13_IRQHandler,Default_Handler

  .weak      TIM14_IRQHandler
  .thumb_set TIM14_IRQHandler,Default_Handler

  .weak      DAC_IRQHandler
  .thumb_set DAC_IRQHandler,Default_Handler

  .weak      RNG1_IRQHandler
  .thumb_set RNG1_IRQHandler,Default_Handler

  .weak      RNG2_IRQHandler
  .thumb_set RNG2_IRQHandler,Default_Handler

  .weak      I2C6_EV_IRQHandler
  .thumb_set I2C6_EV_IRQHandler,Default_Handler

  .weak      I2C6_ER_IRQHandler
  .thumb_set I2C6_ER_IRQHandler,Default_Handler

  .weak      SDMMC3_IRQHandler
  .thumb_set SDMMC3_IRQHandler,Default_Handler
                                                
  .weak      LPTIM2_IRQHandler
  .thumb_set LPTIM2_IRQHandler,Default_Handler
                                             
  .weak      LPTIM3_IRQHandler
  .thumb_set LPTIM3_IRQHandler,Default_Handler
                                        
  .weak      LPTIM4_IRQHandler
  .thumb_set LPTIM4_IRQHandler,Default_Handler
                                              
  .weak      LPTIM5_IRQHandler
  .thumb_set LPTIM5_IRQHandler,Default_Handler

  .weak      MPU_SEV_IRQHandler
  .thumb_set MPU_SEV_IRQHandler,Default_Handler

  .weak      RCC_WAKEUP_IRQHandler
  .thumb_set RCC_WAKEUP_IRQHandler,Default_Handler

  .weak      SAI4_IRQHandler
  .thumb_set SAI4_IRQHandler,Default_Handler

  .weak      DTS_IRQHandler
  .thumb_set DTS_IRQHandler,Default_Handler

  .weak      RESERVED148_IRQHandler
  .thumb_set RESERVED148_IRQHandler,Default_Handler
 
  .weak      WAKEUP_PIN_IRQHandler
  .thumb_set WAKEUP_PIN_IRQHandler,Default_Handler

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

