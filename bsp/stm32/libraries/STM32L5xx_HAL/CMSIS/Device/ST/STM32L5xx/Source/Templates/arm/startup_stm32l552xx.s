;*******************************************************************************
;* File Name          : startup_stm32l552xx.s
;* Author             : MCD Application Team
;* Description        : STM32L552xx Ultra Low Power devices vector table for MDK-ARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M33 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************
;*
;* <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
;* All rights reserved.</center></h2>
;*
;* This software component is licensed by ST under Apache License, Version 2.0,
;* the "License"; You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/Apache-2.0
;*
;*******************************************************************************
;* <<< Use Configuration Wizard in Context Menu >>>
;
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

Heap_Size       EQU     0x00000000

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

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     SecureFault_Handler       ; Secure Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler           ; Window WatchDog
                DCD     PVD_PVM_IRQHandler        ; PVD/PVM1/PVM2/PVM3/PVM4 through EXTI Line detection
                DCD     RTC_IRQHandler            ; RTC non-secure interrupts through the EXTI line
                DCD     RTC_S_IRQHandler          ; RTC secure interrupts through the EXTI line
                DCD     TAMP_IRQHandler           ; Tamper non-secure interrupts through the EXTI line
                DCD     TAMP_S_IRQHandler         ; Tamper secure interrupts through the EXTI line
                DCD     FLASH_IRQHandler          ; FLASH non-secure interrupts
                DCD     FLASH_S_IRQHandler        ; FLASH secure global interrupts
                DCD     GTZC_IRQHandler           ; GTZC global interrupts
                DCD     RCC_IRQHandler            ; RCC non-secure global interrupts
                DCD     RCC_S_IRQHandler          ; RCC secure global interrupts
                DCD     EXTI0_IRQHandler          ; EXTI Line0
                DCD     EXTI1_IRQHandler          ; EXTI Line1
                DCD     EXTI2_IRQHandler          ; EXTI Line2
                DCD     EXTI3_IRQHandler          ; EXTI Line3
                DCD     EXTI4_IRQHandler          ; EXTI Line4
                DCD     EXTI5_IRQHandler          ; EXTI Line5
                DCD     EXTI6_IRQHandler          ; EXTI Line6
                DCD     EXTI7_IRQHandler          ; EXTI Line7
                DCD     EXTI8_IRQHandler          ; EXTI Line8
                DCD     EXTI9_IRQHandler          ; EXTI Line9
                DCD     EXTI10_IRQHandler         ; EXTI Line10
                DCD     EXTI11_IRQHandler         ; EXTI Line11
                DCD     EXTI12_IRQHandler         ; EXTI Line12
                DCD     EXTI13_IRQHandler         ; EXTI Line13
                DCD     EXTI14_IRQHandler         ; EXTI Line14
                DCD     EXTI15_IRQHandler         ; EXTI Line15
                DCD     DMAMUX1_IRQHandler        ; DMAMUX1 non-secure
                DCD     DMAMUX1_S_IRQHandler      ; DMAMUX1 secure
                DCD     DMA1_Channel1_IRQHandler  ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler  ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler  ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler  ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler  ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler  ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler  ; DMA1 Channel 7
                DCD     DMA1_Channel8_IRQHandler  ; DMA1 Channel 8
                DCD     ADC1_2_IRQHandler         ; ADC1 & ADC2
                DCD     DAC_IRQHandler            ; DAC1&2 underrun errors
                DCD     FDCAN1_IT0_IRQHandler     ; FDCAN1 Interrupt 0
                DCD     FDCAN1_IT1_IRQHandler     ; FDCAN1 Interrupt 1
                DCD     TIM1_BRK_IRQHandler       ; TIM1 Break
                DCD     TIM1_UP_IRQHandler        ; TIM1 Update
                DCD     TIM1_TRG_COM_IRQHandler   ; TIM1 Trigger and Commutation
                DCD     TIM1_CC_IRQHandler        ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler           ; TIM2
                DCD     TIM3_IRQHandler           ; TIM3
                DCD     TIM4_IRQHandler           ; TIM4
                DCD     TIM5_IRQHandler           ; TIM5
                DCD     TIM6_IRQHandler           ; TIM6
                DCD     TIM7_IRQHandler           ; TIM7
                DCD     TIM8_BRK_IRQHandler       ; TIM8 Break
                DCD     TIM8_UP_IRQHandler        ; TIM8 Update
                DCD     TIM8_TRG_COM_IRQHandler   ; TIM8 Trigger and Commutation
                DCD     TIM8_CC_IRQHandler        ; TIM8 Capture Compare
                DCD     I2C1_EV_IRQHandler        ; I2C1 Event
                DCD     I2C1_ER_IRQHandler        ; I2C1 Error
                DCD     I2C2_EV_IRQHandler        ; I2C2 Event
                DCD     I2C2_ER_IRQHandler        ; I2C2 Error
                DCD     SPI1_IRQHandler           ; SPI1
                DCD     SPI2_IRQHandler           ; SPI2
                DCD     USART1_IRQHandler         ; USART1
                DCD     USART2_IRQHandler         ; USART2
                DCD     USART3_IRQHandler         ; USART3
                DCD     UART4_IRQHandler          ; UART4
                DCD     UART5_IRQHandler          ; UART5
                DCD     LPUART1_IRQHandler        ; LP UART1
                DCD     LPTIM1_IRQHandler         ; LP TIM1
                DCD     LPTIM2_IRQHandler         ; LP TIM2
                DCD     TIM15_IRQHandler          ; TIM15
                DCD     TIM16_IRQHandler          ; TIM16
                DCD     TIM17_IRQHandler          ; TIM17
                DCD     COMP_IRQHandler           ; COMP1&2
                DCD     USB_FS_IRQHandler         ; USB FS
                DCD     CRS_IRQHandler            ; CRS
                DCD     FMC_IRQHandler            ; FMC
                DCD     OCTOSPI1_IRQHandler       ; OctoSPI1 global interrupt
                DCD     0                         ; Reserved
                DCD     SDMMC1_IRQHandler         ; SDMMC1
                DCD     0                         ; Reserved
                DCD     DMA2_Channel1_IRQHandler  ; DMA2 Channel 1
                DCD     DMA2_Channel2_IRQHandler  ; DMA2 Channel 2
                DCD     DMA2_Channel3_IRQHandler  ; DMA2 Channel 3
                DCD     DMA2_Channel4_IRQHandler  ; DMA2 Channel 4
                DCD     DMA2_Channel5_IRQHandler  ; DMA2 Channel 5
                DCD     DMA2_Channel6_IRQHandler  ; DMA2 Channel 6
                DCD     DMA2_Channel7_IRQHandler  ; DMA2 Channel 7
                DCD     DMA2_Channel8_IRQHandler  ; DMA2 Channel 8
                DCD     I2C3_EV_IRQHandler        ; I2C3 event
                DCD     I2C3_ER_IRQHandler        ; I2C3 error
                DCD     SAI1_IRQHandler           ; Serial Audio Interface 1 global interrupt
                DCD     SAI2_IRQHandler           ; Serial Audio Interface 2 global interrupt
                DCD     TSC_IRQHandler            ; Touch Sense Controller global interrupt
                DCD     0                         ; Reserved
                DCD     RNG_IRQHandler            ; RNG global interrupt
                DCD     FPU_IRQHandler            ; FPU
                DCD     HASH_IRQHandler           ; HASH
                DCD     0                         ; Reserved
                DCD     LPTIM3_IRQHandler         ; LP TIM3
                DCD     SPI3_IRQHandler           ; SPI3
                DCD     I2C4_ER_IRQHandler        ; I2C4 error
                DCD     I2C4_EV_IRQHandler        ; I2C4 event
                DCD     DFSDM1_FLT0_IRQHandler    ; DFSDM1 Filter 0 global Interrupt
                DCD     DFSDM1_FLT1_IRQHandler    ; DFSDM1 Filter 1 global Interrupt
                DCD     DFSDM1_FLT2_IRQHandler    ; DFSDM1 Filter 2 global Interrupt
                DCD     DFSDM1_FLT3_IRQHandler    ; DFSDM1 Filter 3 global Interrupt
                DCD     UCPD1_IRQHandler          ; UCPD1
                DCD     ICACHE_IRQHandler         ; ICACHE
                DCD     0                         ; Reserved
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler\
                PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SecureFault_Handler\
                PROC
                EXPORT  SecureFault_Handler       [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler           [WEAK]
                EXPORT  PVD_PVM_IRQHandler        [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  RTC_S_IRQHandler          [WEAK]
                EXPORT  TAMP_IRQHandler           [WEAK]
                EXPORT  TAMP_S_IRQHandler         [WEAK]
                EXPORT  FLASH_IRQHandler          [WEAK]
                EXPORT  FLASH_S_IRQHandler        [WEAK]
                EXPORT  GTZC_IRQHandler           [WEAK]
                EXPORT  RCC_IRQHandler            [WEAK]
                EXPORT  RCC_S_IRQHandler          [WEAK]
                EXPORT  EXTI0_IRQHandler          [WEAK]
                EXPORT  EXTI1_IRQHandler          [WEAK]
                EXPORT  EXTI2_IRQHandler          [WEAK]
                EXPORT  EXTI3_IRQHandler          [WEAK]
                EXPORT  EXTI4_IRQHandler          [WEAK]
                EXPORT  EXTI5_IRQHandler          [WEAK]
                EXPORT  EXTI6_IRQHandler          [WEAK]
                EXPORT  EXTI7_IRQHandler          [WEAK]
                EXPORT  EXTI8_IRQHandler          [WEAK]
                EXPORT  EXTI9_IRQHandler          [WEAK]
                EXPORT  EXTI10_IRQHandler         [WEAK]
                EXPORT  EXTI11_IRQHandler         [WEAK]
                EXPORT  EXTI12_IRQHandler         [WEAK]
                EXPORT  EXTI13_IRQHandler         [WEAK]
                EXPORT  EXTI14_IRQHandler         [WEAK]
                EXPORT  EXTI15_IRQHandler         [WEAK]
                EXPORT  DMAMUX1_IRQHandler        [WEAK]
                EXPORT  DMAMUX1_S_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler  [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler  [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler  [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler  [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler  [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler  [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler  [WEAK]
                EXPORT  DMA1_Channel8_IRQHandler  [WEAK]
                EXPORT  ADC1_2_IRQHandler         [WEAK]
                EXPORT  DAC_IRQHandler            [WEAK]
                EXPORT  FDCAN1_IT0_IRQHandler     [WEAK]
                EXPORT  FDCAN1_IT1_IRQHandler     [WEAK]
                EXPORT  TIM1_BRK_IRQHandler       [WEAK]
                EXPORT  TIM1_UP_IRQHandler        [WEAK]
                EXPORT  TIM1_TRG_COM_IRQHandler   [WEAK]
                EXPORT  TIM1_CC_IRQHandler        [WEAK]
                EXPORT  TIM2_IRQHandler           [WEAK]
                EXPORT  TIM3_IRQHandler           [WEAK]
                EXPORT  TIM4_IRQHandler           [WEAK]
                EXPORT  TIM5_IRQHandler           [WEAK]
                EXPORT  TIM6_IRQHandler           [WEAK]
                EXPORT  TIM7_IRQHandler           [WEAK]
                EXPORT  TIM8_BRK_IRQHandler       [WEAK]
                EXPORT  TIM8_UP_IRQHandler        [WEAK]
                EXPORT  TIM8_TRG_COM_IRQHandler   [WEAK]
                EXPORT  TIM8_CC_IRQHandler        [WEAK]
                EXPORT  I2C1_EV_IRQHandler        [WEAK]
                EXPORT  I2C1_ER_IRQHandler        [WEAK]
                EXPORT  I2C2_EV_IRQHandler        [WEAK]
                EXPORT  I2C2_ER_IRQHandler        [WEAK]
                EXPORT  SPI1_IRQHandler           [WEAK]
                EXPORT  SPI2_IRQHandler           [WEAK]
                EXPORT  USART1_IRQHandler         [WEAK]
                EXPORT  USART2_IRQHandler         [WEAK]
                EXPORT  USART3_IRQHandler         [WEAK]
                EXPORT  UART4_IRQHandler          [WEAK]
                EXPORT  UART5_IRQHandler          [WEAK]
                EXPORT  LPUART1_IRQHandler        [WEAK]
                EXPORT  LPTIM1_IRQHandler         [WEAK]
                EXPORT  LPTIM2_IRQHandler         [WEAK]
                EXPORT  TIM15_IRQHandler          [WEAK]
                EXPORT  TIM16_IRQHandler          [WEAK]
                EXPORT  TIM17_IRQHandler          [WEAK]
                EXPORT  COMP_IRQHandler           [WEAK]
                EXPORT  USB_FS_IRQHandler         [WEAK]
                EXPORT  CRS_IRQHandler            [WEAK]
                EXPORT  FMC_IRQHandler            [WEAK]
                EXPORT  OCTOSPI1_IRQHandler       [WEAK]
                EXPORT  SDMMC1_IRQHandler         [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler  [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler  [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler  [WEAK]
                EXPORT  DMA2_Channel4_IRQHandler  [WEAK]
                EXPORT  DMA2_Channel5_IRQHandler  [WEAK]
                EXPORT  DMA2_Channel6_IRQHandler  [WEAK]
                EXPORT  DMA2_Channel7_IRQHandler  [WEAK]
                EXPORT  DMA2_Channel8_IRQHandler  [WEAK]
                EXPORT  I2C3_EV_IRQHandler        [WEAK]
                EXPORT  I2C3_ER_IRQHandler        [WEAK]
                EXPORT  SAI1_IRQHandler           [WEAK]
                EXPORT  SAI2_IRQHandler           [WEAK]
                EXPORT  TSC_IRQHandler            [WEAK]
                EXPORT  RNG_IRQHandler            [WEAK]
                EXPORT  FPU_IRQHandler            [WEAK]
                EXPORT  HASH_IRQHandler           [WEAK]
                EXPORT  LPTIM3_IRQHandler         [WEAK]
                EXPORT  SPI3_IRQHandler           [WEAK]
                EXPORT  I2C4_ER_IRQHandler        [WEAK]
                EXPORT  I2C4_EV_IRQHandler        [WEAK]
                EXPORT  DFSDM1_FLT0_IRQHandler    [WEAK]
                EXPORT  DFSDM1_FLT1_IRQHandler    [WEAK]
                EXPORT  DFSDM1_FLT2_IRQHandler    [WEAK]
                EXPORT  DFSDM1_FLT3_IRQHandler    [WEAK]
                EXPORT  UCPD1_IRQHandler          [WEAK]
                EXPORT  ICACHE_IRQHandler         [WEAK]

WWDG_IRQHandler
PVD_PVM_IRQHandler
RTC_IRQHandler
RTC_S_IRQHandler
TAMP_IRQHandler
TAMP_S_IRQHandler
FLASH_IRQHandler
FLASH_S_IRQHandler
GTZC_IRQHandler
RCC_IRQHandler
RCC_S_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
EXTI5_IRQHandler
EXTI6_IRQHandler
EXTI7_IRQHandler
EXTI8_IRQHandler
EXTI9_IRQHandler
EXTI10_IRQHandler
EXTI11_IRQHandler
EXTI12_IRQHandler
EXTI13_IRQHandler
EXTI14_IRQHandler
EXTI15_IRQHandler
DMAMUX1_IRQHandler
DMAMUX1_S_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
DMA1_Channel8_IRQHandler
ADC1_2_IRQHandler
DAC_IRQHandler
FDCAN1_IT0_IRQHandler
FDCAN1_IT1_IRQHandler
TIM1_BRK_IRQHandler
TIM1_UP_IRQHandler
TIM1_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
TIM5_IRQHandler
TIM6_IRQHandler
TIM7_IRQHandler
TIM8_BRK_IRQHandler
TIM8_UP_IRQHandler
TIM8_TRG_COM_IRQHandler
TIM8_CC_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
LPUART1_IRQHandler
LPTIM1_IRQHandler
LPTIM2_IRQHandler
TIM15_IRQHandler
TIM16_IRQHandler
TIM17_IRQHandler
COMP_IRQHandler
USB_FS_IRQHandler
CRS_IRQHandler
FMC_IRQHandler
OCTOSPI1_IRQHandler
SDMMC1_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_IRQHandler
DMA2_Channel5_IRQHandler
DMA2_Channel6_IRQHandler
DMA2_Channel7_IRQHandler
DMA2_Channel8_IRQHandler
I2C3_EV_IRQHandler
I2C3_ER_IRQHandler
SAI1_IRQHandler
SAI2_IRQHandler
TSC_IRQHandler
RNG_IRQHandler
FPU_IRQHandler
HASH_IRQHandler
LPTIM3_IRQHandler
SPI3_IRQHandler
I2C4_ER_IRQHandler
I2C4_EV_IRQHandler
DFSDM1_FLT0_IRQHandler
DFSDM1_FLT1_IRQHandler
DFSDM1_FLT2_IRQHandler
DFSDM1_FLT3_IRQHandler
UCPD1_IRQHandler
ICACHE_IRQHandler
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

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF

                END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
