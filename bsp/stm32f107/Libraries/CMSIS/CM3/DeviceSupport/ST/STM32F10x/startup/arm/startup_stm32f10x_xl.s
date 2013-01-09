;******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
;* File Name          : startup_stm32f10x_xl.s
;* Author             : MCD Application Team
;* Version            : V3.5.0
;* Date               : 11-March-2011
;* Description        : STM32F10x XL-Density Devices vector table for MDK-ARM 
;*                      toolchain. 
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure the clock system and also configure the external 
;*                        SRAM mounted on STM3210E-EVAL board to be used as data 
;*                        memory (optional, to be enabled by user)
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM3 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>   
;*******************************************************************************
; THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
; WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
; AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
; INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
; CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
; INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;*******************************************************************************

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

__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MPU Fault Handler
                DCD     BusFault_Handler           ; Bus Fault Handler
                DCD     UsageFault_Handler         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler               ; Window Watchdog
                DCD     PVD_IRQHandler                ; PVD through EXTI Line detect
                DCD     TAMPER_IRQHandler             ; Tamper
                DCD     RTC_IRQHandler                ; RTC
                DCD     FLASH_IRQHandler              ; Flash
                DCD     RCC_IRQHandler                ; RCC
                DCD     EXTI0_IRQHandler              ; EXTI Line 0
                DCD     EXTI1_IRQHandler              ; EXTI Line 1
                DCD     EXTI2_IRQHandler              ; EXTI Line 2
                DCD     EXTI3_IRQHandler              ; EXTI Line 3
                DCD     EXTI4_IRQHandler              ; EXTI Line 4
                DCD     DMA1_Channel1_IRQHandler      ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler      ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler      ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler      ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler      ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler      ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler      ; DMA1 Channel 7
                DCD     ADC1_2_IRQHandler             ; ADC1 & ADC2
                DCD     USB_HP_CAN1_TX_IRQHandler     ; USB High Priority or CAN1 TX
                DCD     USB_LP_CAN1_RX0_IRQHandler    ; USB Low  Priority or CAN1 RX0
                DCD     CAN1_RX1_IRQHandler           ; CAN1 RX1
                DCD     CAN1_SCE_IRQHandler           ; CAN1 SCE
                DCD     EXTI9_5_IRQHandler            ; EXTI Line 9..5
                DCD     TIM1_BRK_TIM9_IRQHandler      ; TIM1 Break and TIM9
                DCD     TIM1_UP_TIM10_IRQHandler      ; TIM1 Update and TIM10
                DCD     TIM1_TRG_COM_TIM11_IRQHandler ; TIM1 Trigger and Commutation and TIM11
                DCD     TIM1_CC_IRQHandler            ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler               ; TIM2
                DCD     TIM3_IRQHandler               ; TIM3
                DCD     TIM4_IRQHandler               ; TIM4
                DCD     I2C1_EV_IRQHandler            ; I2C1 Event
                DCD     I2C1_ER_IRQHandler            ; I2C1 Error
                DCD     I2C2_EV_IRQHandler            ; I2C2 Event
                DCD     I2C2_ER_IRQHandler            ; I2C2 Error
                DCD     SPI1_IRQHandler               ; SPI1
                DCD     SPI2_IRQHandler               ; SPI2
                DCD     USART1_IRQHandler             ; USART1
                DCD     USART2_IRQHandler             ; USART2
                DCD     USART3_IRQHandler             ; USART3
                DCD     EXTI15_10_IRQHandler          ; EXTI Line 15..10
                DCD     RTCAlarm_IRQHandler           ; RTC Alarm through EXTI Line
                DCD     USBWakeUp_IRQHandler          ; USB Wakeup from suspend
                DCD     TIM8_BRK_TIM12_IRQHandler     ; TIM8 Break and TIM12
                DCD     TIM8_UP_TIM13_IRQHandler      ; TIM8 Update and TIM13
                DCD     TIM8_TRG_COM_TIM14_IRQHandler ; TIM8 Trigger and Commutation and TIM14
                DCD     TIM8_CC_IRQHandler            ; TIM8 Capture Compare
                DCD     ADC3_IRQHandler               ; ADC3
                DCD     FSMC_IRQHandler               ; FSMC
                DCD     SDIO_IRQHandler               ; SDIO
                DCD     TIM5_IRQHandler               ; TIM5
                DCD     SPI3_IRQHandler               ; SPI3
                DCD     UART4_IRQHandler              ; UART4
                DCD     UART5_IRQHandler              ; UART5
                DCD     TIM6_IRQHandler               ; TIM6
                DCD     TIM7_IRQHandler               ; TIM7
                DCD     DMA2_Channel1_IRQHandler      ; DMA2 Channel1
                DCD     DMA2_Channel2_IRQHandler      ; DMA2 Channel2
                DCD     DMA2_Channel3_IRQHandler      ; DMA2 Channel3
                DCD     DMA2_Channel4_5_IRQHandler    ; DMA2 Channel4 & Channel5
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY
                
; Reset handler
Reset_Handler   PROC
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
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler               [WEAK]
                EXPORT  PVD_IRQHandler                [WEAK]
                EXPORT  TAMPER_IRQHandler             [WEAK]
                EXPORT  RTC_IRQHandler                [WEAK]
                EXPORT  FLASH_IRQHandler              [WEAK]
                EXPORT  RCC_IRQHandler                [WEAK]
                EXPORT  EXTI0_IRQHandler              [WEAK]
                EXPORT  EXTI1_IRQHandler              [WEAK]
                EXPORT  EXTI2_IRQHandler              [WEAK]
                EXPORT  EXTI3_IRQHandler              [WEAK]
                EXPORT  EXTI4_IRQHandler              [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler      [WEAK]
                EXPORT  ADC1_2_IRQHandler             [WEAK]
                EXPORT  USB_HP_CAN1_TX_IRQHandler     [WEAK]
                EXPORT  USB_LP_CAN1_RX0_IRQHandler    [WEAK]
                EXPORT  CAN1_RX1_IRQHandler           [WEAK]
                EXPORT  CAN1_SCE_IRQHandler           [WEAK]
                EXPORT  EXTI9_5_IRQHandler            [WEAK]
                EXPORT  TIM1_BRK_TIM9_IRQHandler      [WEAK]
                EXPORT  TIM1_UP_TIM10_IRQHandler      [WEAK]
                EXPORT  TIM1_TRG_COM_TIM11_IRQHandler [WEAK]
                EXPORT  TIM1_CC_IRQHandler            [WEAK]
                EXPORT  TIM2_IRQHandler               [WEAK]
                EXPORT  TIM3_IRQHandler               [WEAK]
                EXPORT  TIM4_IRQHandler               [WEAK]
                EXPORT  I2C1_EV_IRQHandler            [WEAK]
                EXPORT  I2C1_ER_IRQHandler            [WEAK]
                EXPORT  I2C2_EV_IRQHandler            [WEAK]
                EXPORT  I2C2_ER_IRQHandler            [WEAK]
                EXPORT  SPI1_IRQHandler               [WEAK]
                EXPORT  SPI2_IRQHandler               [WEAK]
                EXPORT  USART1_IRQHandler             [WEAK]
                EXPORT  USART2_IRQHandler             [WEAK]
                EXPORT  USART3_IRQHandler             [WEAK]
                EXPORT  EXTI15_10_IRQHandler          [WEAK]
                EXPORT  RTCAlarm_IRQHandler           [WEAK]
                EXPORT  USBWakeUp_IRQHandler          [WEAK]
                EXPORT  TIM8_BRK_TIM12_IRQHandler     [WEAK]
                EXPORT  TIM8_UP_TIM13_IRQHandler      [WEAK]
                EXPORT  TIM8_TRG_COM_TIM14_IRQHandler [WEAK]
                EXPORT  TIM8_CC_IRQHandler            [WEAK]
                EXPORT  ADC3_IRQHandler               [WEAK]
                EXPORT  FSMC_IRQHandler               [WEAK]
                EXPORT  SDIO_IRQHandler               [WEAK]
                EXPORT  TIM5_IRQHandler               [WEAK]
                EXPORT  SPI3_IRQHandler               [WEAK]
                EXPORT  UART4_IRQHandler              [WEAK]
                EXPORT  UART5_IRQHandler              [WEAK]
                EXPORT  TIM6_IRQHandler               [WEAK]
                EXPORT  TIM7_IRQHandler               [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler      [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler      [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler      [WEAK]
                EXPORT  DMA2_Channel4_5_IRQHandler    [WEAK]

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
ADC1_2_IRQHandler
USB_HP_CAN1_TX_IRQHandler
USB_LP_CAN1_RX0_IRQHandler
CAN1_RX1_IRQHandler
CAN1_SCE_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_TIM9_IRQHandler
TIM1_UP_TIM10_IRQHandler
TIM1_TRG_COM_TIM11_IRQHandler
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
RTCAlarm_IRQHandler
USBWakeUp_IRQHandler
TIM8_BRK_TIM12_IRQHandler
TIM8_UP_TIM13_IRQHandler
TIM8_TRG_COM_TIM14_IRQHandler
TIM8_CC_IRQHandler
ADC3_IRQHandler
FSMC_IRQHandler
SDIO_IRQHandler
TIM5_IRQHandler
SPI3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
TIM6_IRQHandler
TIM7_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_5_IRQHandler
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

;******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE*****
