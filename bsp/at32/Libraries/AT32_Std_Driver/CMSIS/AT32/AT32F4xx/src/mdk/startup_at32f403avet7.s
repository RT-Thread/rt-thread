;**************************************************************************
;* File Name    : startup_at32f403avet7.s
;* Description  : at32f4xx startup file for keil
;* Date         : 2019-09-26
;* Version      : V1.0.4
;**************************************************************************
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

__Vectors       DCD     __initial_sp                        ; Top of Stack
                DCD     Reset_Handler                       ; Reset Handler
                DCD     NMI_Handler                         ; NMI Handler
                DCD     HardFault_Handler                   ; Hard Fault Handler
                DCD     MemManage_Handler                   ; MPU Fault Handler
                DCD     BusFault_Handler                    ; Bus Fault Handler
                DCD     UsageFault_Handler                  ; Usage Fault Handler
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     SVC_Handler                         ; SVCall Handler
                DCD     DebugMon_Handler                    ; Debug Monitor Handler
                DCD     0                                   ; Reserved
                DCD     PendSV_Handler                      ; PendSV Handler
                DCD     SysTick_Handler                     ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler                     ; Window Watchdog
                DCD     PVD_IRQHandler                      ; PVD through EXTI Line detect
                DCD     TAMPER_IRQHandler                   ; Tamper
                DCD     RTC_IRQHandler                      ; RTC
                DCD     FLASH_IRQHandler                    ; Flash
                DCD     RCC_IRQHandler                      ; RCC
                DCD     EXTI0_IRQHandler                    ; EXTI Line 0
                DCD     EXTI1_IRQHandler                    ; EXTI Line 1
                DCD     EXTI2_IRQHandler                    ; EXTI Line 2
                DCD     EXTI3_IRQHandler                    ; EXTI Line 3
                DCD     EXTI4_IRQHandler                    ; EXTI Line 4
                DCD     DMA1_Channel1_IRQHandler            ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler            ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler            ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler            ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler            ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler            ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler            ; DMA1 Channel 7
                DCD     ADC1_2_IRQHandler                   ; ADC1 & ADC2
                DCD     USB_HP_CAN1_TX_IRQHandler           ; USB High Priority or CAN1 TX
                DCD     USB_LP_CAN1_RX0_IRQHandler          ; USB Low  Priority or CAN1 RX0 
                DCD     CAN1_RX1_IRQHandler                 ; CAN1 RX1 
                DCD     CAN1_SCE_IRQHandler                 ; CAN1 SCE
                DCD     EXTI9_5_IRQHandler                  ; EXTI Line [9:5]
                DCD     TMR1_BRK_TMR9_IRQHandler            ; TMR1 Break and TMR9
                DCD     TMR1_OV_TMR10_IRQHandler            ; TMR1 Update and TMR10
                DCD     TMR1_TRG_COM_TMR11_IRQHandler      ; TMR1 Trigger and Commutation and TMR11
                DCD     TMR1_CC_IRQHandler                  ; TMR1 Capture Compare
                DCD     TMR2_GLOBAL_IRQHandler              ; TMR2
                DCD     TMR3_GLOBAL_IRQHandler              ; TMR3
                DCD     TMR4_GLOBAL_IRQHandler              ; TMR4
                DCD     I2C1_EV_IRQHandler                  ; I2C1 Event
                DCD     I2C1_ER_IRQHandler                  ; I2C1 Error
                DCD     I2C2_EV_IRQHandler                  ; I2C2 Event
                DCD     I2C2_ER_IRQHandler                  ; I2C2 Error
                DCD     SPI1_IRQHandler                     ; SPI1
                DCD     SPI2_I2S2EXT_IRQHandler             ; SPI2 & I2S2EXT
                DCD     USART1_IRQHandler                   ; USART1
                DCD     USART2_IRQHandler                   ; USART2
                DCD     USART3_IRQHandler                   ; USART3
                DCD     EXTI15_10_IRQHandler                ; EXTI Line [15:10]
                DCD     RTCAlarm_IRQHandler                 ; RTC Alarm through EXTI Line
                DCD     USBWakeUp_IRQHandler                ; USB Wakeup from suspend
                DCD     TMR8_BRK_TMR12_IRQHandler           ; TMR8 Break and TMR12
                DCD     TMR8_OV_TMR13_IRQHandler            ; TMR8 Update and TMR13
                DCD     TMR8_TRG_COM_TMR14_IRQHandler      ; TMR8 Trigger and Commutation and TMR14
                DCD     TMR8_CC_IRQHandler                  ; TMR8 Capture Compare
                DCD     ADC3_IRQHandler                     ; ADC3
                DCD     XMC_IRQHandler                      ; XMC
                DCD     SDIO1_IRQHandler                    ; SDIO1
                DCD     TMR5_GLOBAL_IRQHandler              ; TMR5
                DCD     SPI3_I2S3EXT_IRQHandler             ; SPI3 & I2S3EXT
                DCD     UART4_IRQHandler                    ; UART4
                DCD     UART5_IRQHandler                    ; UART5
                DCD     TMR6_GLOBAL_IRQHandler              ; TMR6
                DCD     TMR7_GLOBAL_IRQHandler              ; TMR7
                DCD     DMA2_Channel1_IRQHandler            ; DMA2 Channel1
                DCD     DMA2_Channel2_IRQHandler            ; DMA2 Channel2
                DCD     DMA2_Channel3_IRQHandler            ; DMA2 Channel3
                DCD     DMA2_Channel4_5_IRQHandler          ; DMA2 Channel4 & Channel5
                DCD     SDIO2_IRQHandler                    ; SDIO2
                DCD     I2C3_EV_IRQHandler                  ; I2C3 Event
                DCD     I2C3_ER_IRQHandler                  ; I2C3 Error
                DCD     SPI4_IRQHandler                     ; SPI4
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     0                                   ; Reserved
                DCD     CAN2_TX_IRQHandler                  ; CAN2 TX
                DCD     CAN2_RX0_IRQHandler                 ; CAN2 RX0 
                DCD     CAN2_RX1_IRQHandler                 ; CAN2 RX1 
                DCD     CAN2_SCE_IRQHandler                 ; CAN2 SCE
                DCD     ACC_IRQHandler                      ; ACC
                DCD     USB_HP_IRQHandler                   ; USB HP
                DCD     USB_LP_IRQHandler                   ; USB LP
                DCD     DMA2_Channel6_7_IRQHandler          ; DMA2 Channel6 & Channel7
                DCD     USART6_IRQHandler                   ; USART6
                DCD     UART7_IRQHandler                    ; UART7
                DCD     UART8_IRQHandler                    ; UART8
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler                       [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                         [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                   [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                   [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                    [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler                  [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                         [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                      [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                     [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler                     [WEAK]
                EXPORT  PVD_IRQHandler                      [WEAK]
                EXPORT  TAMPER_IRQHandler                   [WEAK]
                EXPORT  RTC_IRQHandler                      [WEAK]
                EXPORT  FLASH_IRQHandler                    [WEAK]
                EXPORT  RCC_IRQHandler                      [WEAK]
                EXPORT  EXTI0_IRQHandler                    [WEAK]
                EXPORT  EXTI1_IRQHandler                    [WEAK]
                EXPORT  EXTI2_IRQHandler                    [WEAK]
                EXPORT  EXTI3_IRQHandler                    [WEAK]
                EXPORT  EXTI4_IRQHandler                    [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler            [WEAK]
                EXPORT  ADC1_2_IRQHandler                   [WEAK]
                EXPORT  USB_HP_CAN1_TX_IRQHandler           [WEAK]
                EXPORT  USB_LP_CAN1_RX0_IRQHandler          [WEAK]
                EXPORT  CAN1_RX1_IRQHandler                 [WEAK]
                EXPORT  CAN1_SCE_IRQHandler                 [WEAK]
                EXPORT  EXTI9_5_IRQHandler                  [WEAK]
                EXPORT  TMR1_BRK_TMR9_IRQHandler            [WEAK]
                EXPORT  TMR1_OV_TMR10_IRQHandler            [WEAK]
                EXPORT  TMR1_TRG_COM_TMR11_IRQHandler      [WEAK]
                EXPORT  TMR1_CC_IRQHandler                  [WEAK]
                EXPORT  TMR2_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR3_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR4_GLOBAL_IRQHandler              [WEAK]
                EXPORT  I2C1_EV_IRQHandler                  [WEAK]
                EXPORT  I2C1_ER_IRQHandler                  [WEAK]
                EXPORT  I2C2_EV_IRQHandler                  [WEAK]
                EXPORT  I2C2_ER_IRQHandler                  [WEAK]
                EXPORT  SPI1_IRQHandler                     [WEAK]
                EXPORT  SPI2_I2S2EXT_IRQHandler             [WEAK]
                EXPORT  USART1_IRQHandler                   [WEAK]
                EXPORT  USART2_IRQHandler                   [WEAK]
                EXPORT  USART3_IRQHandler                   [WEAK]
                EXPORT  EXTI15_10_IRQHandler                [WEAK]
                EXPORT  RTCAlarm_IRQHandler                 [WEAK]
                EXPORT  USBWakeUp_IRQHandler                [WEAK]
                EXPORT  TMR8_BRK_TMR12_IRQHandler           [WEAK]
                EXPORT  TMR8_OV_TMR13_IRQHandler            [WEAK]
                EXPORT  TMR8_TRG_COM_TMR14_IRQHandler      [WEAK]
                EXPORT  TMR8_CC_IRQHandler                  [WEAK]
                EXPORT  ADC3_IRQHandler                     [WEAK]
                EXPORT  XMC_IRQHandler                      [WEAK]
                EXPORT  SDIO1_IRQHandler                    [WEAK]
                EXPORT  TMR5_GLOBAL_IRQHandler              [WEAK]
                EXPORT  SPI3_I2S3EXT_IRQHandler             [WEAK]
                EXPORT  UART4_IRQHandler                    [WEAK]
                EXPORT  UART5_IRQHandler                    [WEAK]
                EXPORT  TMR6_GLOBAL_IRQHandler              [WEAK]
                EXPORT  TMR7_GLOBAL_IRQHandler              [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel4_5_IRQHandler          [WEAK]
                EXPORT  SDIO2_IRQHandler                    [WEAK]
                EXPORT  I2C3_EV_IRQHandler                  [WEAK]
                EXPORT  I2C3_ER_IRQHandler                  [WEAK]
                EXPORT  SPI4_IRQHandler                     [WEAK]
                EXPORT  CAN2_TX_IRQHandler                  [WEAK]
                EXPORT  CAN2_RX0_IRQHandler                 [WEAK]
                EXPORT  CAN2_RX1_IRQHandler                 [WEAK]
                EXPORT  CAN2_SCE_IRQHandler                 [WEAK]
                EXPORT  ACC_IRQHandler                      [WEAK]
                EXPORT  USB_HP_IRQHandler                   [WEAK]
                EXPORT  USB_LP_IRQHandler                   [WEAK]
                EXPORT  DMA2_Channel6_7_IRQHandler          [WEAK]
                EXPORT  USART6_IRQHandler                   [WEAK]
                EXPORT  UART7_IRQHandler                    [WEAK]
                EXPORT  UART8_IRQHandler                    [WEAK]

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
TMR1_BRK_TMR9_IRQHandler
TMR1_OV_TMR10_IRQHandler
TMR1_TRG_COM_TMR11_IRQHandler
TMR1_CC_IRQHandler
TMR2_GLOBAL_IRQHandler
TMR3_GLOBAL_IRQHandler
TMR4_GLOBAL_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_I2S2EXT_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTCAlarm_IRQHandler
USBWakeUp_IRQHandler
TMR8_BRK_TMR12_IRQHandler
TMR8_OV_TMR13_IRQHandler
TMR8_TRG_COM_TMR14_IRQHandler
TMR8_CC_IRQHandler
ADC3_IRQHandler
XMC_IRQHandler
SDIO1_IRQHandler
TMR5_GLOBAL_IRQHandler
SPI3_I2S3EXT_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
TMR6_GLOBAL_IRQHandler
TMR7_GLOBAL_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_5_IRQHandler
SDIO2_IRQHandler
I2C3_EV_IRQHandler
I2C3_ER_IRQHandler
SPI4_IRQHandler
CAN2_TX_IRQHandler
CAN2_RX0_IRQHandler 
CAN2_RX1_IRQHandler 
CAN2_SCE_IRQHandler
ACC_IRQHandler
USB_HP_IRQHandler
USB_LP_IRQHandler
DMA2_Channel6_7_IRQHandler
USART6_IRQHandler
UART7_IRQHandler
UART8_IRQHandler
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
