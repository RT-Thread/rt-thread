;******************************************************************************
;* File Name          : startup_stm32mp15xx.s
;* Author             : MCD Application Team
;* Description        : STM32MP15xx devices vector table for MDK-ARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM4 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>
;****************************************************************************** 
;* @attention
;*
;* &copy; Copyright (c) 2019 STMicroelectronics. 
;* All rights reserved.
;*
;* This software component is licensed by ST under BSD 3-Clause license,
;* the "License"; You may not use this file except in compliance with the 
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/BSD-3-Clause
;*
;******************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
__stack_limit
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD      __initial_sp                        ;     Top of Stack
                DCD      Reset_Handler                       ;     Reset Handler
                DCD      NMI_Handler                         ; -14 NMI Handler
                DCD      HardFault_Handler                   ; -13 Hard Fault Handler
                DCD      MemManage_Handler                   ; -12 MPU Fault Handler
                DCD      BusFault_Handler                    ; -11 Bus Fault Handler
                DCD      UsageFault_Handler                  ; -10 Usage Fault Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      SVC_Handler                         ;  -5 SVCall Handler
                DCD      DebugMon_Handler                    ;  -4 Debug Monitor Handler
                DCD      0                                   ;     Reserved
                DCD      PendSV_Handler                      ;  -2 PendSV Handler
                DCD      SysTick_Handler                     ;  -1 SysTick Handler

                ; Interrupts
                DCD     WWDG1_IRQHandler                     ;
                DCD     PVD_AVD_IRQHandler                   ;
                DCD     TAMP_IRQHandler                      ;
                DCD     RTC_WKUP_ALARM_IRQHandler            ;
                DCD     RESERVED4_IRQHandler                 ;
                DCD     RCC_IRQHandler                       ;
                DCD     EXTI0_IRQHandler                     ;
                DCD     EXTI1_IRQHandler                     ;
                DCD     EXTI2_IRQHandler                     ;
                DCD     EXTI3_IRQHandler                     ;
                DCD     EXTI4_IRQHandler                     ;
                DCD     DMA1_Stream0_IRQHandler              ;
                DCD     DMA1_Stream1_IRQHandler              ;
                DCD     DMA1_Stream2_IRQHandler              ;
                DCD     DMA1_Stream3_IRQHandler              ;
                DCD     DMA1_Stream4_IRQHandler              ;
                DCD     DMA1_Stream5_IRQHandler              ;
                DCD     DMA1_Stream6_IRQHandler              ;
                DCD     ADC1_IRQHandler                      ;
                DCD     FDCAN1_IT0_IRQHandler                ;
                DCD     FDCAN2_IT0_IRQHandler                ;
                DCD     FDCAN1_IT1_IRQHandler                ;
                DCD     FDCAN2_IT1_IRQHandler                ;
                DCD     EXTI5_IRQHandler                     ;
                DCD     TIM1_BRK_IRQHandler                  ;
                DCD     TIM1_UP_IRQHandler                   ;
                DCD     TIM1_TRG_COM_IRQHandler              ;
                DCD     TIM1_CC_IRQHandler                   ;
                DCD     TIM2_IRQHandler                      ;
                DCD     TIM3_IRQHandler                      ;
                DCD     TIM4_IRQHandler                      ;
                DCD     I2C1_EV_IRQHandler                   ;
                DCD     I2C1_ER_IRQHandler                   ;
                DCD     I2C2_EV_IRQHandler                   ;
                DCD     I2C2_ER_IRQHandler                   ;
                DCD     SPI1_IRQHandler                      ;
                DCD     SPI2_IRQHandler                      ;
                DCD     USART1_IRQHandler                    ;
                DCD     USART2_IRQHandler                    ;
                DCD     USART3_IRQHandler                    ;
                DCD     EXTI10_IRQHandler                    ;
                DCD     RTC_TIMESTAMP_IRQHandler             ;
                DCD     EXTI11_IRQHandler                    ;
                DCD     TIM8_BRK_IRQHandler                  ;
                DCD     TIM8_UP_IRQHandler                   ;
                DCD     TIM8_TRG_COM_IRQHandler              ;
                DCD     TIM8_CC_IRQHandler                   ;
                DCD     DMA1_Stream7_IRQHandler              ;
                DCD     FMC_IRQHandler                       ;
                DCD     SDMMC1_IRQHandler                    ;
                DCD     TIM5_IRQHandler                      ;
                DCD     SPI3_IRQHandler                      ;
                DCD     UART4_IRQHandler                     ;
                DCD     UART5_IRQHandler                     ;
                DCD     TIM6_IRQHandler                      ;
                DCD     TIM7_IRQHandler                      ;
                DCD     DMA2_Stream0_IRQHandler              ;
                DCD     DMA2_Stream1_IRQHandler              ;
                DCD     DMA2_Stream2_IRQHandler              ;
                DCD     DMA2_Stream3_IRQHandler              ;
                DCD     DMA2_Stream4_IRQHandler              ;
                DCD     ETH1_IRQHandler                      ;
                DCD     ETH1_WKUP_IRQHandler                 ;
                DCD     FDCAN_CAL_IRQHandler                 ;
                DCD     EXTI6_IRQHandler                     ;
                DCD     EXTI7_IRQHandler                     ;
                DCD     EXTI8_IRQHandler                     ;
                DCD     EXTI9_IRQHandler                     ;
                DCD     DMA2_Stream5_IRQHandler              ;
                DCD     DMA2_Stream6_IRQHandler              ;
                DCD     DMA2_Stream7_IRQHandler              ;
                DCD     USART6_IRQHandler                    ;
                DCD     I2C3_EV_IRQHandler                   ;
                DCD     I2C3_ER_IRQHandler                   ;
                DCD     USBH_OHCI_IRQHandler                 ;
                DCD     USBH_EHCI_IRQHandler                 ;
                DCD     EXTI12_IRQHandler                    ;
                DCD     EXTI13_IRQHandler                    ;
                DCD     DCMI_IRQHandler                      ;
                DCD     CRYP1_IRQHandler                     ;
                DCD     HASH1_IRQHandler                     ;
                DCD     FPU_IRQHandler                       ;
                DCD     UART7_IRQHandler                     ;
                DCD     UART8_IRQHandler                     ;
                DCD     SPI4_IRQHandler                      ;
                DCD     SPI5_IRQHandler                      ;
                DCD     SPI6_IRQHandler                      ;
                DCD     SAI1_IRQHandler                      ;
                DCD     LTDC_IRQHandler                      ;
                DCD     LTDC_ER_IRQHandler                   ;
                DCD     ADC2_IRQHandler                      ;
                DCD     SAI2_IRQHandler                      ;
                DCD     QUADSPI_IRQHandler                   ;
                DCD     LPTIM1_IRQHandler                    ;
                DCD     CEC_IRQHandler                       ;
                DCD     I2C4_EV_IRQHandler                   ;
                DCD     I2C4_ER_IRQHandler                   ;
                DCD     SPDIF_RX_IRQHandler                  ;
                DCD     OTG_IRQHandler                       ;
                DCD     RESERVED99_IRQHandler                ;
                DCD     IPCC_RX0_IRQHandler                  ;
                DCD     IPCC_TX0_IRQHandler                  ;
                DCD     DMAMUX1_OVR_IRQHandler               ;
                DCD     IPCC_RX1_IRQHandler                  ;
                DCD     IPCC_TX1_IRQHandler                  ;
                DCD     CRYP2_IRQHandler                     ;
                DCD     HASH2_IRQHandler                     ;
                DCD     I2C5_EV_IRQHandler                   ;
                DCD     I2C5_ER_IRQHandler                   ;
                DCD     GPU_IRQHandler                       ;
                DCD     DFSDM1_FLT0_IRQHandler               ;
                DCD     DFSDM1_FLT1_IRQHandler               ;
                DCD     DFSDM1_FLT2_IRQHandler               ;
                DCD     DFSDM1_FLT3_IRQHandler               ;
                DCD     SAI3_IRQHandler                      ;
                DCD     DFSDM1_FLT4_IRQHandler               ;
                DCD     TIM15_IRQHandler                     ;
                DCD     TIM16_IRQHandler                     ;
                DCD     TIM17_IRQHandler                     ;
                DCD     TIM12_IRQHandler                     ;
                DCD     MDIOS_IRQHandler                     ;
                DCD     EXTI14_IRQHandler                    ;
                DCD     MDMA_IRQHandler                      ;
                DCD     DSI_IRQHandler                       ;
                DCD     SDMMC2_IRQHandler                    ;
                DCD     HSEM_IT2_IRQHandler                  ;
                DCD     DFSDM1_FLT5_IRQHandler               ;
                DCD     EXTI15_IRQHandler                    ;
                DCD     nCTIIRQ1_IRQHandler                  ;
                DCD     nCTIIRQ2_IRQHandler                  ;
                DCD     TIM13_IRQHandler                     ;
                DCD     TIM14_IRQHandler                     ;
                DCD     DAC_IRQHandler                       ;
                DCD     RNG1_IRQHandler                      ;
                DCD     RNG2_IRQHandler                      ;
                DCD     I2C6_EV_IRQHandler                   ; 
                DCD     I2C6_ER_IRQHandler                   ;
                DCD     SDMMC3_IRQHandler                    ;
                DCD     LPTIM2_IRQHandler                    ;
                DCD     LPTIM3_IRQHandler                    ;
                DCD     LPTIM4_IRQHandler                    ;
                DCD     LPTIM5_IRQHandler                    ;
                DCD     ETH1_LPI_IRQHandler                  ;
                DCD     RESERVED143_IRQHandler               ;
                DCD     MPU_SEV_IRQHandler                   ;
                DCD     RCC_WAKEUP_IRQHandler                ;
                DCD     SAI4_IRQHandler                      ;
                DCD     DTS_IRQHandler                       ;
                DCD     RESERVED148_IRQHandler               ;
                DCD     WAKEUP_PIN_IRQHandler                ;

                SPACE    (73 * 4)                            ; Interrupts 151 .. 224 are left out
__Vectors_End
__Vectors_Size  EQU      __Vectors_End - __Vectors


                AREA     |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT   Reset_Handler             [WEAK]
                IMPORT   SystemInit
                IMPORT   __main

                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =__main
                BX       R0
                ENDP


; Macro to define default exception/interrupt handlers.
; Default handler are weak symbols with an endless loop.
; They can be overwritten by real handlers.
                MACRO
                Set_Default_Handler  $Handler_Name
$Handler_Name   PROC
                EXPORT   $Handler_Name             [WEAK]
                B        .
                ENDP
                MEND


; Default exception/interrupt handler

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  HardFault_Handler
                Set_Default_Handler  MemManage_Handler
                Set_Default_Handler  BusFault_Handler
                Set_Default_Handler  UsageFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  DebugMon_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  WWDG1_IRQHandler                  ; Window WatchDog 1
                Set_Default_Handler  PVD_AVD_IRQHandler                ; PVD and AVD through EXTI Line detection                   
                Set_Default_Handler  TAMP_IRQHandler                   ; Tamper and TimeStamps through the EXTI line
                Set_Default_Handler  RTC_WKUP_ALARM_IRQHandler         ; RTC Wakeup and Alarm through the EXTI line
                Set_Default_Handler  RESERVED4_IRQHandler              ; Reserved
                Set_Default_Handler  RCC_IRQHandler                    ; RCC                                             
                Set_Default_Handler  EXTI0_IRQHandler                  ; EXTI Line0                                             
                Set_Default_Handler  EXTI1_IRQHandler                  ; EXTI Line1                                             
                Set_Default_Handler  EXTI2_IRQHandler                  ; EXTI Line2                                             
                Set_Default_Handler  EXTI3_IRQHandler                  ; EXTI Line3                                             
                Set_Default_Handler  EXTI4_IRQHandler                  ; EXTI Line4               
                Set_Default_Handler  DMA1_Stream0_IRQHandler           ; DMA1 Stream 0              
                Set_Default_Handler  DMA1_Stream1_IRQHandler           ; DMA1 Stream 1                                                 
                Set_Default_Handler  DMA1_Stream2_IRQHandler           ; DMA1 Stream 2                                                 
                Set_Default_Handler  DMA1_Stream3_IRQHandler           ; DMA1 Stream 3                                                 
                Set_Default_Handler  DMA1_Stream4_IRQHandler           ; DMA1 Stream 4                                                 
                Set_Default_Handler  DMA1_Stream5_IRQHandler           ; DMA1 Stream 5              
                Set_Default_Handler  DMA1_Stream6_IRQHandler           ; DMA1 Stream 6               
                Set_Default_Handler  ADC1_IRQHandler                   ; ADC1                                          
                Set_Default_Handler  FDCAN1_IT0_IRQHandler             ; FDCAN1 Interrupt line 0              
                Set_Default_Handler  FDCAN2_IT0_IRQHandler             ; FDCAN2 Interrupt line 0
                Set_Default_Handler  FDCAN1_IT1_IRQHandler             ; FDCAN1 Interrupt line 1
                Set_Default_Handler  FDCAN2_IT1_IRQHandler             ; FDCAN2 Interrupt line 1
                Set_Default_Handler  EXTI5_IRQHandler                  ; External Line5 interrupts through AIEC
                Set_Default_Handler  TIM1_BRK_IRQHandler               ; TIM1 Break interrupt
                Set_Default_Handler  TIM1_UP_IRQHandler                ; TIM1 Update Interrupt
                Set_Default_Handler  TIM1_TRG_COM_IRQHandler           ; TIM1 Trigger and Commutation Interrupt
                Set_Default_Handler  TIM1_CC_IRQHandler                ; TIM1 Capture Compare                                   
                Set_Default_Handler  TIM2_IRQHandler                   ; TIM2                                            
                Set_Default_Handler  TIM3_IRQHandler                   ; TIM3                                            
                Set_Default_Handler  TIM4_IRQHandler                   ; TIM4                                            
                Set_Default_Handler  I2C1_EV_IRQHandler                ; I2C1 Event                                             
                Set_Default_Handler  I2C1_ER_IRQHandler                ; I2C1 Error                                             
                Set_Default_Handler  I2C2_EV_IRQHandler                ; I2C2 Event                                             
                Set_Default_Handler  I2C2_ER_IRQHandler                ; I2C2 Error                                               
                Set_Default_Handler  SPI1_IRQHandler                   ; SPI1                                            
                Set_Default_Handler  SPI2_IRQHandler                   ; SPI2                                            
                Set_Default_Handler  USART1_IRQHandler                 ; USART1                                          
                Set_Default_Handler  USART2_IRQHandler                 ; USART2                                          
                Set_Default_Handler  USART3_IRQHandler                 ; USART3                                          
                Set_Default_Handler  EXTI10_IRQHandler                 ; External Line10 interrupts through AIEC
                Set_Default_Handler  RTC_TIMESTAMP_IRQHandler          ; RTC TimeStamp through EXTI Line
                Set_Default_Handler  EXTI11_IRQHandler                 ; External Line11 interrupts through AIEC
                Set_Default_Handler  TIM8_BRK_IRQHandler               ; TIM8 Break Interrupt
                Set_Default_Handler  TIM8_UP_IRQHandler                ; TIM8 Update Interrupt
                Set_Default_Handler  TIM8_TRG_COM_IRQHandler           ; TIM8 Trigger and Commutation Interrupt
                Set_Default_Handler  TIM8_CC_IRQHandler                ; TIM8 Capture Compare Interrupt
                Set_Default_Handler  DMA1_Stream7_IRQHandler           ; DMA1 Stream7                                           
                Set_Default_Handler  FMC_IRQHandler                    ; FMC                             
                Set_Default_Handler  SDMMC1_IRQHandler                 ; SDMMC1
                Set_Default_Handler  TIM5_IRQHandler                   ; TIM5                            
                Set_Default_Handler  SPI3_IRQHandler                   ; SPI3                            
                Set_Default_Handler  UART4_IRQHandler                  ; UART4                           
                Set_Default_Handler  UART5_IRQHandler                  ; UART5                           
                Set_Default_Handler  TIM6_IRQHandler                   ; TIM6
                Set_Default_Handler  TIM7_IRQHandler                   ; TIM7           
                Set_Default_Handler  DMA2_Stream0_IRQHandler           ; DMA2 Stream 0                   
                Set_Default_Handler  DMA2_Stream1_IRQHandler           ; DMA2 Stream 1                   
                Set_Default_Handler  DMA2_Stream2_IRQHandler           ; DMA2 Stream 2                   
                Set_Default_Handler  DMA2_Stream3_IRQHandler           ; DMA2 Stream 3                   
                Set_Default_Handler  DMA2_Stream4_IRQHandler           ; DMA2 Stream 4                   
                Set_Default_Handler  ETH1_IRQHandler                   ; Ethernet                        
                Set_Default_Handler  ETH1_WKUP_IRQHandler              ; Ethernet Wakeup through EXTI line              
                Set_Default_Handler  FDCAN_CAL_IRQHandler              ; FDCAN Calibration
                Set_Default_Handler  EXTI6_IRQHandler                  ; EXTI Line6 interrupts through AIEC
                Set_Default_Handler  EXTI7_IRQHandler                  ; EXTI Line7 interrupts through AIEC
                Set_Default_Handler  EXTI8_IRQHandler                  ; EXTI Line8 interrupts through AIEC
                Set_Default_Handler  EXTI9_IRQHandler                  ; EXTI Line9 interrupts through AIEC
                Set_Default_Handler  DMA2_Stream5_IRQHandler           ; DMA2 Stream 5                   
                Set_Default_Handler  DMA2_Stream6_IRQHandler           ; DMA2 Stream 6                   
                Set_Default_Handler  DMA2_Stream7_IRQHandler           ; DMA2 Stream 7                   
                Set_Default_Handler  USART6_IRQHandler                 ; USART6                           
                Set_Default_Handler  I2C3_EV_IRQHandler                ; I2C3 event                             
                Set_Default_Handler  I2C3_ER_IRQHandler                ; I2C3 error                             
                Set_Default_Handler  USBH_OHCI_IRQHandler              ; USB Host OHCI
                Set_Default_Handler  USBH_EHCI_IRQHandler              ; USB Host EHCI
                Set_Default_Handler  EXTI12_IRQHandler                 ; EXTI Line12 interrupts through AIEC
                Set_Default_Handler  EXTI13_IRQHandler                 ; EXTI Line13 interrupts through AIEC
                Set_Default_Handler  DCMI_IRQHandler                   ; DCMI                            
                Set_Default_Handler  CRYP1_IRQHandler                  ; Crypto1 global interrupt
                Set_Default_Handler  HASH1_IRQHandler                  ; Crypto Hash1 interrupt
                Set_Default_Handler  FPU_IRQHandler                    ; FPU
                Set_Default_Handler  UART7_IRQHandler                  ; UART7
                Set_Default_Handler  UART8_IRQHandler                  ; UART8
                Set_Default_Handler  SPI4_IRQHandler                   ; SPI4
                Set_Default_Handler  SPI5_IRQHandler                   ; SPI5
                Set_Default_Handler  SPI6_IRQHandler                   ; SPI6
                Set_Default_Handler  SAI1_IRQHandler                   ; SAI1
                Set_Default_Handler  LTDC_IRQHandler                   ; LTDC
                Set_Default_Handler  LTDC_ER_IRQHandler                ; LTDC error
                Set_Default_Handler  ADC2_IRQHandler                   ; ADC2
                Set_Default_Handler  SAI2_IRQHandler                   ; SAI2
                Set_Default_Handler  QUADSPI_IRQHandler                ; QUADSPI
                Set_Default_Handler  LPTIM1_IRQHandler                 ; LPTIM1 global interrupt
                Set_Default_Handler  CEC_IRQHandler                    ; HDMI_CEC
                Set_Default_Handler  I2C4_EV_IRQHandler                ; I2C4 Event                             
                Set_Default_Handler  I2C4_ER_IRQHandler                ; I2C4 Error 
                Set_Default_Handler  SPDIF_RX_IRQHandler               ; SPDIF_RX
                Set_Default_Handler  OTG_IRQHandler                    ; USB On The Go HS global interrupt
                Set_Default_Handler  RESERVED99_IRQHandler             ; Reserved
                Set_Default_Handler  IPCC_RX0_IRQHandler               ; Mailbox RX0 Free interrupt
                Set_Default_Handler  IPCC_TX0_IRQHandler               ; Mailbox TX0 Free interrupt
                Set_Default_Handler  DMAMUX1_OVR_IRQHandler            ; DMAMUX1 Overrun interrupt
                Set_Default_Handler  IPCC_RX1_IRQHandler               ; Mailbox RX1 Free interrupt
                Set_Default_Handler  IPCC_TX1_IRQHandler               ; Mailbox TX1 Free interrupt
                Set_Default_Handler  CRYP2_IRQHandler                  ; Crypto2 global interrupt
                Set_Default_Handler  HASH2_IRQHandler                  ; Crypto Hash2 interrupt
                Set_Default_Handler  I2C5_EV_IRQHandler                ; I2C5 Event Interrupt
                Set_Default_Handler  I2C5_ER_IRQHandler                ; I2C5 Error Interrupt
                Set_Default_Handler  GPU_IRQHandler                    ; GPU Global Interrupt
                Set_Default_Handler  DFSDM1_FLT0_IRQHandler            ; DFSDM Filter0 Interrupt
                Set_Default_Handler  DFSDM1_FLT1_IRQHandler            ; DFSDM Filter1 Interrupt
                Set_Default_Handler  DFSDM1_FLT2_IRQHandler            ; DFSDM Filter2 Interrupt
                Set_Default_Handler  DFSDM1_FLT3_IRQHandler            ; DFSDM Filter3 Interrupt
                Set_Default_Handler  SAI3_IRQHandler                   ; SAI3 global Interrupt
                Set_Default_Handler  DFSDM1_FLT4_IRQHandler            ; DFSDM Filter4 Interrupt
                Set_Default_Handler  TIM15_IRQHandler                  ; TIM15 global Interrupt
                Set_Default_Handler  TIM16_IRQHandler                  ; TIM16 global Interrupt
                Set_Default_Handler  TIM17_IRQHandler                  ; TIM17 global Interrupt
                Set_Default_Handler  TIM12_IRQHandler                  ; TIM12 global Interrupt
                Set_Default_Handler  MDIOS_IRQHandler                  ; MDIOS global Interrupt
                Set_Default_Handler  EXTI14_IRQHandler                 ; EXTI Line14 interrupts through AIEC
                Set_Default_Handler  MDMA_IRQHandler                   ; MDMA global Interrupt
                Set_Default_Handler  DSI_IRQHandler                    ; DSI global Interrupt
                Set_Default_Handler  SDMMC2_IRQHandler                 ; SDMMC2 global Interrupt
                Set_Default_Handler  HSEM_IT2_IRQHandler               ; HSEM global Interrupt
                Set_Default_Handler  DFSDM1_FLT5_IRQHandler            ; DFSDM Filter5 Interrupt
                Set_Default_Handler  EXTI15_IRQHandler                 ; EXTI Line15 interrupts through AIEC
                Set_Default_Handler  nCTIIRQ1_IRQHandler               ; Cortex-M4 CTI interrupt 1
                Set_Default_Handler  nCTIIRQ2_IRQHandler               ; Cortex-M4 CTI interrupt 2
                Set_Default_Handler  TIM13_IRQHandler                  ; TIM13 global interrupt
                Set_Default_Handler  TIM14_IRQHandler                  ; TIM14 global interrupt
                Set_Default_Handler  DAC_IRQHandler                    ; DAC1 and DAC2 underrun error interrupts
                Set_Default_Handler  RNG1_IRQHandler                   ; RNG1 interrupt
                Set_Default_Handler  RNG2_IRQHandler                   ; RNG2 interrupt
                Set_Default_Handler  I2C6_EV_IRQHandler                ; I2C6 Event Interrupt
                Set_Default_Handler  I2C6_ER_IRQHandler                ; I2C6 Error Interrupt
                Set_Default_Handler  SDMMC3_IRQHandler                 ; SDMMC3 global Interrupt
                Set_Default_Handler  LPTIM2_IRQHandler                 ; LPTIM2 global interrupt
                Set_Default_Handler  LPTIM3_IRQHandler                 ; LPTIM3 global interrupt
                Set_Default_Handler  LPTIM4_IRQHandler                 ; LPTIM4 global interrupt
                Set_Default_Handler  LPTIM5_IRQHandler                 ; LPTIM5 global interrupt
                Set_Default_Handler  ETH1_LPI_IRQHandler               ; Reserved
                Set_Default_Handler  RESERVED143_IRQHandler            ; Reserved
                Set_Default_Handler  MPU_SEV_IRQHandler                ; MPU Send Event through AIEC
                Set_Default_Handler  RCC_WAKEUP_IRQHandler             ; RCC Wake up interrupt
                Set_Default_Handler  SAI4_IRQHandler                   ; SAI4 global interrupt
                Set_Default_Handler  DTS_IRQHandler                    ; Temperature sensor interrupt
                Set_Default_Handler  RESERVED148_IRQHandler            ; Reserved
                Set_Default_Handler  WAKEUP_PIN_IRQHandler             ; Interrupt for all 6 wake-up pins

                ALIGN


; User setup Stack & Heap

                EXPORT   __stack_limit
                EXPORT   __initial_sp
                IF       Heap_Size != 0                      ; Heap is provided
                EXPORT   __heap_base
                EXPORT   __heap_limit
                ENDIF

                END
