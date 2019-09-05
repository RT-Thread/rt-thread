;******************** (C) COPYRIGHT 2017 STMicroelectronics ********************
;* File Name          : startup_stm32f100xe.s
;* Author             : MCD Application Team
;* Description        : STM32F100xE Devices vector table for MDK-ARM toolchain. 
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the clock system and also configure the external 
;*                        SRAM mounted on STM32100E-EVAL board to be used as data 
;*                        memory (optional, to be enabled by user)
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M3 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;******************************************************************************
;* @attention
;*
;* Copyright (c) 2017 STMicroelectronics.
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

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
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

__Vectors       DCD     __initial_sp                    ; Top of Stack
                DCD     Reset_Handler                   ; Reset Handler
                DCD     NMI_Handler                     ; NMI Handler
                DCD     HardFault_Handler               ; Hard Fault Handler
                DCD     MemManage_Handler               ; MPU Fault Handler
                DCD     BusFault_Handler                ; Bus Fault Handler
                DCD     UsageFault_Handler              ; Usage Fault Handler
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     SVC_Handler                     ; SVCall Handler
                DCD     DebugMon_Handler                ; Debug Monitor Handler
                DCD     0                               ; Reserved
                DCD     PendSV_Handler                  ; PendSV Handler
                DCD     SysTick_Handler                 ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler                 ; Window Watchdog
                DCD     PVD_IRQHandler                  ; PVD through EXTI Line detect
                DCD     TAMPER_IRQHandler               ; Tamper
                DCD     RTC_IRQHandler                  ; RTC
                DCD     FLASH_IRQHandler                ; Flash
                DCD     RCC_IRQHandler                  ; RCC
                DCD     EXTI0_IRQHandler                ; EXTI Line 0
                DCD     EXTI1_IRQHandler                ; EXTI Line 1
                DCD     EXTI2_IRQHandler                ; EXTI Line 2
                DCD     EXTI3_IRQHandler                ; EXTI Line 3
                DCD     EXTI4_IRQHandler                ; EXTI Line 4
                DCD     DMA1_Channel1_IRQHandler        ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler        ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler        ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler        ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler        ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler        ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler        ; DMA1 Channel 7
                DCD     ADC1_IRQHandler                 ; ADC1
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     EXTI9_5_IRQHandler              ; EXTI Line 9..5
                DCD     TIM1_BRK_TIM15_IRQHandler       ; TIM1 Break and TIM15
                DCD     TIM1_UP_TIM16_IRQHandler        ; TIM1 Update and TIM16
                DCD     TIM1_TRG_COM_TIM17_IRQHandler   ; TIM1 Trigger and Commutation and TIM17
                DCD     TIM1_CC_IRQHandler              ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler                 ; TIM2
                DCD     TIM3_IRQHandler                 ; TIM3
                DCD     TIM4_IRQHandler                 ; TIM4
                DCD     I2C1_EV_IRQHandler              ; I2C1 Event
                DCD     I2C1_ER_IRQHandler              ; I2C1 Error
                DCD     I2C2_EV_IRQHandler              ; I2C2 Event
                DCD     I2C2_ER_IRQHandler              ; I2C2 Error
                DCD     SPI1_IRQHandler                 ; SPI1
                DCD     SPI2_IRQHandler                 ; SPI2
                DCD     USART1_IRQHandler               ; USART1
                DCD     USART2_IRQHandler               ; USART2
                DCD     USART3_IRQHandler               ; USART3
                DCD     EXTI15_10_IRQHandler            ; EXTI Line 15..10
                DCD     RTC_Alarm_IRQHandler             ; RTC Alarm through EXTI Line
                DCD     CEC_IRQHandler                  ; HDMI CEC
                DCD     TIM12_IRQHandler                ; TIM12
                DCD     TIM13_IRQHandler                ; TIM13 
                DCD     TIM14_IRQHandler                ; TIM14
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     TIM5_IRQHandler                 ; TIM5
                DCD     SPI3_IRQHandler                 ; SPI3
                DCD     UART4_IRQHandler                ; UART4
                DCD     UART5_IRQHandler                ; UART5
                DCD     TIM6_DAC_IRQHandler             ; TIM6 and DAC underrun
                DCD     TIM7_IRQHandler                 ; TIM7
                DCD     DMA2_Channel1_IRQHandler        ; DMA2 Channel1
                DCD     DMA2_Channel2_IRQHandler        ; DMA2 Channel2
                DCD     DMA2_Channel3_IRQHandler        ; DMA2 Channel3
                DCD     DMA2_Channel4_5_IRQHandler      ; DMA2 Channel4 & Channel5
                DCD     DMA2_Channel5_IRQHandler        ; DMA2 Channel5                
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler    PROC
                 EXPORT  Reset_Handler             [WEAK]
     IMPORT  __main
     IMPORT  SystemInit
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                      [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                 [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler               [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                      [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                 [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                   [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                  [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler                  [WEAK]
                EXPORT  PVD_IRQHandler                   [WEAK]
                EXPORT  TAMPER_IRQHandler                [WEAK]
                EXPORT  RTC_IRQHandler                   [WEAK]
                EXPORT  FLASH_IRQHandler                 [WEAK]
                EXPORT  RCC_IRQHandler                   [WEAK]
                EXPORT  EXTI0_IRQHandler                 [WEAK]
                EXPORT  EXTI1_IRQHandler                 [WEAK]
                EXPORT  EXTI2_IRQHandler                 [WEAK]
                EXPORT  EXTI3_IRQHandler                 [WEAK]
                EXPORT  EXTI4_IRQHandler                 [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler         [WEAK]
                EXPORT  ADC1_IRQHandler                  [WEAK]
                EXPORT  EXTI9_5_IRQHandler               [WEAK]
                EXPORT  TIM1_BRK_TIM15_IRQHandler        [WEAK]
                EXPORT  TIM1_UP_TIM16_IRQHandler         [WEAK]
                EXPORT  TIM1_TRG_COM_TIM17_IRQHandler    [WEAK]
                EXPORT  TIM1_CC_IRQHandler               [WEAK]
                EXPORT  TIM2_IRQHandler                  [WEAK]
                EXPORT  TIM3_IRQHandler                  [WEAK]
                EXPORT  TIM4_IRQHandler                  [WEAK]
                EXPORT  I2C1_EV_IRQHandler               [WEAK]
                EXPORT  I2C1_ER_IRQHandler               [WEAK]
                EXPORT  I2C2_EV_IRQHandler               [WEAK]
                EXPORT  I2C2_ER_IRQHandler               [WEAK]
                EXPORT  SPI1_IRQHandler                  [WEAK]
                EXPORT  SPI2_IRQHandler                  [WEAK]
                EXPORT  USART1_IRQHandler                [WEAK]
                EXPORT  USART2_IRQHandler                [WEAK]
                EXPORT  USART3_IRQHandler                [WEAK]
                EXPORT  EXTI15_10_IRQHandler             [WEAK]
                EXPORT  RTC_Alarm_IRQHandler             [WEAK]
                EXPORT  CEC_IRQHandler                   [WEAK]
                EXPORT  TIM12_IRQHandler                 [WEAK]
                EXPORT  TIM13_IRQHandler                 [WEAK]
                EXPORT  TIM14_IRQHandler                 [WEAK]
                EXPORT  TIM5_IRQHandler                  [WEAK]
                EXPORT  SPI3_IRQHandler                  [WEAK]
                EXPORT  UART4_IRQHandler                 [WEAK]
                EXPORT  UART5_IRQHandler                 [WEAK]
                EXPORT  TIM6_DAC_IRQHandler              [WEAK]
                EXPORT  TIM7_IRQHandler                  [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler         [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler         [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler         [WEAK]
                EXPORT  DMA2_Channel4_5_IRQHandler       [WEAK]
                EXPORT  DMA2_Channel5_IRQHandler         [WEAK]

WWDG_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_TIM15_IRQHandler
TIM1_UP_TIM16_IRQHandler
TIM1_TRG_COM_TIM17_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTC_Alarm_IRQHandler
CEC_IRQHandler
TIM12_IRQHandler
TIM13_IRQHandler
TIM14_IRQHandler
TIM5_IRQHandler
SPI3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
TIM6_DAC_IRQHandler
TIM7_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_5_IRQHandler
DMA2_Channel5_IRQHandler
                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB           
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
