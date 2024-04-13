;*******************************************************************************
;* File Name          : startup_stm32h7s7xx.s
;* Author             : MCD Application Team
;* Description        : STM32H7S7xx Crypto devices vector table for MDK-ARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M7 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************
;* @attention
;*
;* Copyright (c) 2023 STMicroelectronics.
;* All rights reserved.
;*
;* This software is licensed under terms that can be found in the LICENSE file
;* in the root directory of this software component.
;* If no LICENSE file comes with this software, it is provided AS-IS.
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

__Vectors       DCD     __initial_sp                     ; Top of Stack
                DCD     Reset_Handler                    ; Reset Handler
                DCD     NMI_Handler                      ; NMI Handler
                DCD     HardFault_Handler                ; Hard Fault Handler
                DCD     MemManage_Handler                ; MPU Fault Handler
                DCD     BusFault_Handler                 ; Bus Fault Handler
                DCD     UsageFault_Handler               ; Usage Fault Handler
                DCD     0                                ; Reserved
                DCD     0                                ; Reserved
                DCD     0                                ; Reserved
                DCD     0                                ; Reserved
                DCD     SVC_Handler                      ; SVCall Handler
                DCD     DebugMon_Handler                 ; Debug Monitor Handler
                DCD     0                                ; Reserved
                DCD     PendSV_Handler                   ; PendSV Handler
                DCD     SysTick_Handler                  ; SysTick Handler
                ; External Interrupts
                DCD     PVD_PVM_IRQHandler               ; PVD/PVM through EXTI Line detection
                DCD     0                                ; Reserved
                DCD     DTS_IRQHandler                   ; Digital Temperature Sensor
                DCD     IWDG_IRQHandler                  ; Internal Watchdog
                DCD     WWDG_IRQHandler                  ; Window Watchdog
                DCD     RCC_IRQHandler                   ; RCC global interrupts through EXTI Line detection
                DCD     0                                ; Reserved
                DCD     0                                ; Reserved
                DCD     FLASH_IRQHandler                 ; FLASH interrupts
                DCD     RAMECC_IRQHandler                ; RAMECC interrupts
                DCD     FPU_IRQHandler                   ; FPU
                DCD     0                                ; Reserved
                DCD     0                                ; Reserved
                DCD     TAMP_IRQHandler                  ; Tamper and TimeStamp interrupts through EXTI Line detection
                DCD     0                                ; Reserved
                DCD     0                                ; Reserved
                DCD     EXTI0_IRQHandler                 ; EXTI Line0
                DCD     EXTI1_IRQHandler                 ; EXTI Line1
                DCD     EXTI2_IRQHandler                 ; EXTI Line2
                DCD     EXTI3_IRQHandler                 ; EXTI Line3
                DCD     EXTI4_IRQHandler                 ; EXTI Line4
                DCD     EXTI5_IRQHandler                 ; EXTI Line5
                DCD     EXTI6_IRQHandler                 ; EXTI Line6
                DCD     EXTI7_IRQHandler                 ; EXTI Line7
                DCD     EXTI8_IRQHandler                 ; EXTI Line8
                DCD     EXTI9_IRQHandler                 ; EXTI Line9
                DCD     EXTI10_IRQHandler                ; EXTI Line10
                DCD     EXTI11_IRQHandler                ; EXTI Line11
                DCD     EXTI12_IRQHandler                ; EXTI Line12
                DCD     EXTI13_IRQHandler                ; EXTI Line13
                DCD     EXTI14_IRQHandler                ; EXTI Line14
                DCD     EXTI15_IRQHandler                ; EXTI Line15
                DCD     RTC_IRQHandler                   ; RTC wakeup and alarm interrupts through EXTI Line detection
                DCD     SAES_IRQHandler                  ; SAES
                DCD     CRYP_IRQHandler                  ; CRYP
                DCD     PKA_IRQHandler                   ; PKA
                DCD     HASH_IRQHandler                  ; HASH
                DCD     RNG_IRQHandler                   ; RNG
                DCD     ADC1_2_IRQHandler                ; ADC1 & ADC2
                DCD     GPDMA1_Channel0_IRQHandler       ; GPDMA1 Channel 0
                DCD     GPDMA1_Channel1_IRQHandler       ; GPDMA1 Channel 1
                DCD     GPDMA1_Channel2_IRQHandler       ; GPDMA1 Channel 2
                DCD     GPDMA1_Channel3_IRQHandler       ; GPDMA1 Channel 3
                DCD     GPDMA1_Channel4_IRQHandler       ; GPDMA1 Channel 4
                DCD     GPDMA1_Channel5_IRQHandler       ; GPDMA1 Channel 5
                DCD     GPDMA1_Channel6_IRQHandler       ; GPDMA1 Channel 6
                DCD     GPDMA1_Channel7_IRQHandler       ; GPDMA1 Channel 7
                DCD     TIM1_BRK_IRQHandler              ; TIM1 Break
                DCD     TIM1_UP_IRQHandler               ; TIM1 Update
                DCD     TIM1_TRG_COM_IRQHandler          ; TIM1 Trigger and Commutation
                DCD     TIM1_CC_IRQHandler               ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler                  ; TIM2
                DCD     TIM3_IRQHandler                  ; TIM3
                DCD     TIM4_IRQHandler                  ; TIM4
                DCD     TIM5_IRQHandler                  ; TIM5
                DCD     TIM6_IRQHandler                  ; TIM6
                DCD     TIM7_IRQHandler                  ; TIM7
                DCD     TIM9_IRQHandler                  ; TIM9
                DCD     SPI1_IRQHandler                  ; SPI1
                DCD     SPI2_IRQHandler                  ; SPI2
                DCD     SPI3_IRQHandler                  ; SPI3
                DCD     SPI4_IRQHandler                  ; SPI4
                DCD     SPI5_IRQHandler                  ; SPI5
                DCD     SPI6_IRQHandler                  ; SPI6
                DCD     HPDMA1_Channel0_IRQHandler       ; HPDMA1 Channel 0
                DCD     HPDMA1_Channel1_IRQHandler       ; HPDMA1 Channel 1
                DCD     HPDMA1_Channel2_IRQHandler       ; HPDMA1 Channel 2
                DCD     HPDMA1_Channel3_IRQHandler       ; HPDMA1 Channel 3
                DCD     HPDMA1_Channel4_IRQHandler       ; HPDMA1 Channel 4
                DCD     HPDMA1_Channel5_IRQHandler       ; HPDMA1 Channel 5
                DCD     HPDMA1_Channel6_IRQHandler       ; HPDMA1 Channel 6
                DCD     HPDMA1_Channel7_IRQHandler       ; HPDMA1 Channel 7
                DCD     SAI1_A_IRQHandler                ; Serial Audio Interface 1 block A
                DCD     SAI1_B_IRQHandler                ; Serial Audio Interface 1 block B
                DCD     SAI2_A_IRQHandler                ; Serial Audio Interface 2 block A
                DCD     SAI2_B_IRQHandler                ; Serial Audio Interface 2 block B
                DCD     I2C1_EV_IRQHandler               ; I2C1 Event
                DCD     I2C1_ER_IRQHandler               ; I2C1 Error
                DCD     I2C2_EV_IRQHandler               ; I2C2 Event
                DCD     I2C2_ER_IRQHandler               ; I2C2 Error
                DCD     I2C3_EV_IRQHandler               ; I2C3 Event
                DCD     I2C3_ER_IRQHandler               ; I2C3 Error
                DCD     USART1_IRQHandler                ; USART1
                DCD     USART2_IRQHandler                ; USART2
                DCD     USART3_IRQHandler                ; USART3
                DCD     UART4_IRQHandler                 ; UART4
                DCD     UART5_IRQHandler                 ; UART5
                DCD     UART7_IRQHandler                 ; UART7
                DCD     UART8_IRQHandler                 ; UART8
                DCD     I3C1_EV_IRQHandler               ; I3C1 Event
                DCD     I3C1_ER_IRQHandler               ; I3C1 Error
                DCD     OTG_HS_IRQHandler                ; USB OTG HS
                DCD     ETH_IRQHandler                   ; Ethernet
                DCD     CORDIC_IRQHandler                ; CORDIC
                DCD     GFXTIM_IRQHandler                ; GFXTIM
                DCD     DCMIPP_IRQHandler                ; DCMIPP
                DCD     LTDC_IRQHandler                  ; LTDC
                DCD     LTDC_ER_IRQHandler               ; LTDC error
                DCD     DMA2D_IRQHandler                 ; DMA2D
                DCD     JPEG_IRQHandler                  ; JPEG
                DCD     GFXMMU_IRQHandler                ; GFXMMU
                DCD     I3C1_WKUP_IRQHandler             ; I3C1 wakeup
                DCD     MCE1_IRQHandler                  ; MCE1
                DCD     MCE2_IRQHandler                  ; MCE2
                DCD     MCE3_IRQHandler                  ; MCE3
                DCD     XSPI1_IRQHandler                 ; XSPI1
                DCD     XSPI2_IRQHandler                 ; XSPI2
                DCD     FMC_IRQHandler                   ; FMC
                DCD     SDMMC1_IRQHandler                ; SDMMC1
                DCD     SDMMC2_IRQHandler                ; SDMMC2
                DCD     0                                ; Reserved
                DCD     0                                ; Reserved
                DCD     OTG_FS_IRQHandler                ; USB OTG FS
                DCD     TIM12_IRQHandler                 ; TIM12
                DCD     TIM13_IRQHandler                 ; TIM13
                DCD     TIM14_IRQHandler                 ; TIM14
                DCD     TIM15_IRQHandler                 ; TIM15
                DCD     TIM16_IRQHandler                 ; TIM16
                DCD     TIM17_IRQHandler                 ; TIM17
                DCD     LPTIM1_IRQHandler                ; LP TIM1
                DCD     LPTIM2_IRQHandler                ; LP TIM2
                DCD     LPTIM3_IRQHandler                ; LP TIM3
                DCD     LPTIM4_IRQHandler                ; LP TIM4
                DCD     LPTIM5_IRQHandler                ; LP TIM5
                DCD     SPDIF_RX_IRQHandler              ; SPDIF_RX
                DCD     MDIOS_IRQHandler                 ; MDIOS
                DCD     ADF1_FLT0_IRQHandler             ; ADF1 Filter 0
                DCD     CRS_IRQHandler                   ; CRS
                DCD     UCPD1_IRQHandler                 ; UCPD1
                DCD     CEC_IRQHandler                   ; HDMI_CEC
                DCD     PSSI_IRQHandler                  ; PSSI
                DCD     LPUART1_IRQHandler               ; LP UART1
                DCD     WAKEUP_PIN_IRQHandler            ; Wake-up pins interrupt
                DCD     GPDMA1_Channel8_IRQHandler       ; GPDMA1 Channel 8
                DCD     GPDMA1_Channel9_IRQHandler       ; GPDMA1 Channel 9
                DCD     GPDMA1_Channel10_IRQHandler      ; GPDMA1 Channel 10
                DCD     GPDMA1_Channel11_IRQHandler      ; GPDMA1 Channel 11
                DCD     GPDMA1_Channel12_IRQHandler      ; GPDMA1 Channel 12
                DCD     GPDMA1_Channel13_IRQHandler      ; GPDMA1 Channel 13
                DCD     GPDMA1_Channel14_IRQHandler      ; GPDMA1 Channel 14
                DCD     GPDMA1_Channel15_IRQHandler      ; GPDMA1 Channel 15
                DCD     HPDMA1_Channel8_IRQHandler       ; HPDMA1 Channel 8
                DCD     HPDMA1_Channel9_IRQHandler       ; HPDMA1 Channel 9
                DCD     HPDMA1_Channel10_IRQHandler      ; HPDMA1 Channel 10
                DCD     HPDMA1_Channel11_IRQHandler      ; HPDMA1 Channel 11
                DCD     HPDMA1_Channel12_IRQHandler      ; HPDMA1 Channel 12
                DCD     HPDMA1_Channel13_IRQHandler      ; HPDMA1 Channel 13
                DCD     HPDMA1_Channel14_IRQHandler      ; HPDMA1 Channel 14
                DCD     HPDMA1_Channel15_IRQHandler      ; HPDMA1 Channel 15
                DCD     GPU2D_IRQHandler                 ; GPU2D
                DCD     GPU2D_ER_IRQHandler              ; GPU2D error
                DCD     ICACHE_IRQHandler                ; ICACHE
                DCD     FDCAN1_IT0_IRQHandler            ; FDCAN1 Interrupt 0
                DCD     FDCAN1_IT1_IRQHandler            ; FDCAN1 Interrupt 1
                DCD     FDCAN2_IT0_IRQHandler            ; FDCAN2 Interrupt 0
                DCD     FDCAN2_IT1_IRQHandler            ; FDCAN2 Interrupt 1


__Vectors_End

__Vectors_Size  EQU    __Vectors_End - __Vectors

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

                EXPORT  PVD_PVM_IRQHandler               [WEAK]
                EXPORT  DTS_IRQHandler                   [WEAK]
                EXPORT  IWDG_IRQHandler                  [WEAK]
                EXPORT  WWDG_IRQHandler                  [WEAK]
                EXPORT  RCC_IRQHandler                   [WEAK]
                EXPORT  FLASH_IRQHandler                 [WEAK]
                EXPORT  RAMECC_IRQHandler                [WEAK]
                EXPORT  FPU_IRQHandler                   [WEAK]
                EXPORT  TAMP_IRQHandler                  [WEAK]
                EXPORT  EXTI0_IRQHandler                 [WEAK]
                EXPORT  EXTI1_IRQHandler                 [WEAK]
                EXPORT  EXTI2_IRQHandler                 [WEAK]
                EXPORT  EXTI3_IRQHandler                 [WEAK]
                EXPORT  EXTI4_IRQHandler                 [WEAK]
                EXPORT  EXTI5_IRQHandler                 [WEAK]
                EXPORT  EXTI6_IRQHandler                 [WEAK]
                EXPORT  EXTI7_IRQHandler                 [WEAK]
                EXPORT  EXTI8_IRQHandler                 [WEAK]
                EXPORT  EXTI9_IRQHandler                 [WEAK]
                EXPORT  EXTI10_IRQHandler                [WEAK]
                EXPORT  EXTI11_IRQHandler                [WEAK]
                EXPORT  EXTI12_IRQHandler                [WEAK]
                EXPORT  EXTI13_IRQHandler                [WEAK]
                EXPORT  EXTI14_IRQHandler                [WEAK]
                EXPORT  EXTI15_IRQHandler                [WEAK]
                EXPORT  RTC_IRQHandler                   [WEAK]
                EXPORT  SAES_IRQHandler                  [WEAK]
                EXPORT  CRYP_IRQHandler                  [WEAK]
                EXPORT  PKA_IRQHandler                   [WEAK]
                EXPORT  HASH_IRQHandler                  [WEAK]
                EXPORT  RNG_IRQHandler                   [WEAK]
                EXPORT  ADC1_2_IRQHandler                [WEAK]
                EXPORT  GPDMA1_Channel0_IRQHandler       [WEAK]
                EXPORT  GPDMA1_Channel1_IRQHandler       [WEAK]
                EXPORT  GPDMA1_Channel2_IRQHandler       [WEAK]
                EXPORT  GPDMA1_Channel3_IRQHandler       [WEAK]
                EXPORT  GPDMA1_Channel4_IRQHandler       [WEAK]
                EXPORT  GPDMA1_Channel5_IRQHandler       [WEAK]
                EXPORT  GPDMA1_Channel6_IRQHandler       [WEAK]
                EXPORT  GPDMA1_Channel7_IRQHandler       [WEAK]
                EXPORT  TIM1_BRK_IRQHandler              [WEAK]
                EXPORT  TIM1_UP_IRQHandler               [WEAK]
                EXPORT  TIM1_TRG_COM_IRQHandler          [WEAK]
                EXPORT  TIM1_CC_IRQHandler               [WEAK]
                EXPORT  TIM2_IRQHandler                  [WEAK]
                EXPORT  TIM3_IRQHandler                  [WEAK]
                EXPORT  TIM4_IRQHandler                  [WEAK]
                EXPORT  TIM5_IRQHandler                  [WEAK]
                EXPORT  TIM6_IRQHandler                  [WEAK]
                EXPORT  TIM7_IRQHandler                  [WEAK]
                EXPORT  TIM9_IRQHandler                  [WEAK]
                EXPORT  SPI1_IRQHandler                  [WEAK]
                EXPORT  SPI2_IRQHandler                  [WEAK]
                EXPORT  SPI3_IRQHandler                  [WEAK]
                EXPORT  SPI4_IRQHandler                  [WEAK]
                EXPORT  SPI5_IRQHandler                  [WEAK]
                EXPORT  SPI6_IRQHandler                  [WEAK]
                EXPORT  HPDMA1_Channel0_IRQHandler       [WEAK]
                EXPORT  HPDMA1_Channel1_IRQHandler       [WEAK]
                EXPORT  HPDMA1_Channel2_IRQHandler       [WEAK]
                EXPORT  HPDMA1_Channel3_IRQHandler       [WEAK]
                EXPORT  HPDMA1_Channel4_IRQHandler       [WEAK]
                EXPORT  HPDMA1_Channel5_IRQHandler       [WEAK]
                EXPORT  HPDMA1_Channel6_IRQHandler       [WEAK]
                EXPORT  HPDMA1_Channel7_IRQHandler       [WEAK]
                EXPORT  SAI1_A_IRQHandler                [WEAK]
                EXPORT  SAI1_B_IRQHandler                [WEAK]
                EXPORT  SAI2_A_IRQHandler                [WEAK]
                EXPORT  SAI2_B_IRQHandler                [WEAK]
                EXPORT  I2C1_EV_IRQHandler               [WEAK]
                EXPORT  I2C1_ER_IRQHandler               [WEAK]
                EXPORT  I2C2_EV_IRQHandler               [WEAK]
                EXPORT  I2C2_ER_IRQHandler               [WEAK]
                EXPORT  I2C3_EV_IRQHandler               [WEAK]
                EXPORT  I2C3_ER_IRQHandler               [WEAK]
                EXPORT  USART1_IRQHandler                [WEAK]
                EXPORT  USART2_IRQHandler                [WEAK]
                EXPORT  USART3_IRQHandler                [WEAK]
                EXPORT  UART4_IRQHandler                 [WEAK]
                EXPORT  UART5_IRQHandler                 [WEAK]
                EXPORT  UART7_IRQHandler                 [WEAK]
                EXPORT  UART8_IRQHandler                 [WEAK]
                EXPORT  I3C1_EV_IRQHandler               [WEAK]
                EXPORT  I3C1_ER_IRQHandler               [WEAK]
                EXPORT  OTG_HS_IRQHandler                [WEAK]
                EXPORT  ETH_IRQHandler                   [WEAK]
                EXPORT  CORDIC_IRQHandler                [WEAK]
                EXPORT  GFXTIM_IRQHandler                [WEAK]
                EXPORT  DCMIPP_IRQHandler                [WEAK]
                EXPORT  LTDC_IRQHandler                  [WEAK]
                EXPORT  LTDC_ER_IRQHandler               [WEAK]
                EXPORT  DMA2D_IRQHandler                 [WEAK]
                EXPORT  JPEG_IRQHandler                  [WEAK]
                EXPORT  GFXMMU_IRQHandler                [WEAK]
                EXPORT  I3C1_WKUP_IRQHandler             [WEAK]
                EXPORT  MCE1_IRQHandler                  [WEAK]
                EXPORT  MCE2_IRQHandler                  [WEAK]
                EXPORT  MCE3_IRQHandler                  [WEAK]
                EXPORT  XSPI1_IRQHandler                 [WEAK]
                EXPORT  XSPI2_IRQHandler                 [WEAK]
                EXPORT  FMC_IRQHandler                   [WEAK]
                EXPORT  SDMMC1_IRQHandler                [WEAK]
                EXPORT  SDMMC2_IRQHandler                [WEAK]
                EXPORT  OTG_FS_IRQHandler                [WEAK]
                EXPORT  TIM12_IRQHandler                 [WEAK]
                EXPORT  TIM13_IRQHandler                 [WEAK]
                EXPORT  TIM14_IRQHandler                 [WEAK]
                EXPORT  TIM15_IRQHandler                 [WEAK]
                EXPORT  TIM16_IRQHandler                 [WEAK]
                EXPORT  TIM17_IRQHandler                 [WEAK]
                EXPORT  LPTIM1_IRQHandler                [WEAK]
                EXPORT  LPTIM2_IRQHandler                [WEAK]
                EXPORT  LPTIM3_IRQHandler                [WEAK]
                EXPORT  LPTIM4_IRQHandler                [WEAK]
                EXPORT  LPTIM5_IRQHandler                [WEAK]
                EXPORT  SPDIF_RX_IRQHandler              [WEAK]
                EXPORT  MDIOS_IRQHandler                 [WEAK]
                EXPORT  ADF1_FLT0_IRQHandler             [WEAK]
                EXPORT  CRS_IRQHandler                   [WEAK]
                EXPORT  UCPD1_IRQHandler                 [WEAK]
                EXPORT  CEC_IRQHandler                   [WEAK]
                EXPORT  PSSI_IRQHandler                  [WEAK]
                EXPORT  LPUART1_IRQHandler               [WEAK]
                EXPORT  WAKEUP_PIN_IRQHandler            [WEAK]
                EXPORT  GPDMA1_Channel8_IRQHandler       [WEAK]
                EXPORT  GPDMA1_Channel9_IRQHandler       [WEAK]
                EXPORT  GPDMA1_Channel10_IRQHandler      [WEAK]
                EXPORT  GPDMA1_Channel11_IRQHandler      [WEAK]
                EXPORT  GPDMA1_Channel12_IRQHandler      [WEAK]
                EXPORT  GPDMA1_Channel13_IRQHandler      [WEAK]
                EXPORT  GPDMA1_Channel14_IRQHandler      [WEAK]
                EXPORT  GPDMA1_Channel15_IRQHandler      [WEAK]
                EXPORT  HPDMA1_Channel8_IRQHandler       [WEAK]
                EXPORT  HPDMA1_Channel9_IRQHandler       [WEAK]
                EXPORT  HPDMA1_Channel10_IRQHandler      [WEAK]
                EXPORT  HPDMA1_Channel11_IRQHandler      [WEAK]
                EXPORT  HPDMA1_Channel12_IRQHandler      [WEAK]
                EXPORT  HPDMA1_Channel13_IRQHandler      [WEAK]
                EXPORT  HPDMA1_Channel14_IRQHandler      [WEAK]
                EXPORT  HPDMA1_Channel15_IRQHandler      [WEAK]
                EXPORT  GPU2D_IRQHandler                 [WEAK]
                EXPORT  GPU2D_ER_IRQHandler              [WEAK]
                EXPORT  ICACHE_IRQHandler                [WEAK]
                EXPORT  FDCAN1_IT0_IRQHandler            [WEAK]
                EXPORT  FDCAN1_IT1_IRQHandler            [WEAK]
                EXPORT  FDCAN2_IT0_IRQHandler            [WEAK]
                EXPORT  FDCAN2_IT1_IRQHandler            [WEAK]

PVD_PVM_IRQHandler
DTS_IRQHandler
IWDG_IRQHandler
WWDG_IRQHandler
RCC_IRQHandler
FLASH_IRQHandler
RAMECC_IRQHandler
FPU_IRQHandler
TAMP_IRQHandler
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
RTC_IRQHandler
SAES_IRQHandler
CRYP_IRQHandler
PKA_IRQHandler
HASH_IRQHandler
RNG_IRQHandler
ADC1_2_IRQHandler
GPDMA1_Channel0_IRQHandler
GPDMA1_Channel1_IRQHandler
GPDMA1_Channel2_IRQHandler
GPDMA1_Channel3_IRQHandler
GPDMA1_Channel4_IRQHandler
GPDMA1_Channel5_IRQHandler
GPDMA1_Channel6_IRQHandler
GPDMA1_Channel7_IRQHandler
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
TIM9_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
SPI3_IRQHandler
SPI4_IRQHandler
SPI5_IRQHandler
SPI6_IRQHandler
HPDMA1_Channel0_IRQHandler
HPDMA1_Channel1_IRQHandler
HPDMA1_Channel2_IRQHandler
HPDMA1_Channel3_IRQHandler
HPDMA1_Channel4_IRQHandler
HPDMA1_Channel5_IRQHandler
HPDMA1_Channel6_IRQHandler
HPDMA1_Channel7_IRQHandler
SAI1_A_IRQHandler
SAI1_B_IRQHandler
SAI2_A_IRQHandler
SAI2_B_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
I2C3_EV_IRQHandler
I2C3_ER_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
UART7_IRQHandler
UART8_IRQHandler
I3C1_EV_IRQHandler
I3C1_ER_IRQHandler
OTG_HS_IRQHandler
ETH_IRQHandler
CORDIC_IRQHandler
GFXTIM_IRQHandler
DCMIPP_IRQHandler
LTDC_IRQHandler
LTDC_ER_IRQHandler
DMA2D_IRQHandler
JPEG_IRQHandler
GFXMMU_IRQHandler
I3C1_WKUP_IRQHandler
MCE1_IRQHandler
MCE2_IRQHandler
MCE3_IRQHandler
XSPI1_IRQHandler
XSPI2_IRQHandler
FMC_IRQHandler
SDMMC1_IRQHandler
SDMMC2_IRQHandler
OTG_FS_IRQHandler
TIM12_IRQHandler
TIM13_IRQHandler
TIM14_IRQHandler
TIM15_IRQHandler
TIM16_IRQHandler
TIM17_IRQHandler
LPTIM1_IRQHandler
LPTIM2_IRQHandler
LPTIM3_IRQHandler
LPTIM4_IRQHandler
LPTIM5_IRQHandler
SPDIF_RX_IRQHandler
MDIOS_IRQHandler
ADF1_FLT0_IRQHandler
CRS_IRQHandler
UCPD1_IRQHandler
CEC_IRQHandler
PSSI_IRQHandler
LPUART1_IRQHandler
WAKEUP_PIN_IRQHandler
GPDMA1_Channel8_IRQHandler
GPDMA1_Channel9_IRQHandler
GPDMA1_Channel10_IRQHandler
GPDMA1_Channel11_IRQHandler
GPDMA1_Channel12_IRQHandler
GPDMA1_Channel13_IRQHandler
GPDMA1_Channel14_IRQHandler
GPDMA1_Channel15_IRQHandler
HPDMA1_Channel8_IRQHandler
HPDMA1_Channel9_IRQHandler
HPDMA1_Channel10_IRQHandler
HPDMA1_Channel11_IRQHandler
HPDMA1_Channel12_IRQHandler
HPDMA1_Channel13_IRQHandler
HPDMA1_Channel14_IRQHandler
HPDMA1_Channel15_IRQHandler
GPU2D_IRQHandler
GPU2D_ER_IRQHandler
ICACHE_IRQHandler
FDCAN1_IT0_IRQHandler
FDCAN1_IT1_IRQHandler
FDCAN2_IT0_IRQHandler
FDCAN2_IT1_IRQHandler

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
