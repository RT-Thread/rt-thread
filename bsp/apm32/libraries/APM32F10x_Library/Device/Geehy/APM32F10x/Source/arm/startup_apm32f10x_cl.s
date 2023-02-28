;/*!
; * @file        startup_apm32f10x_cl.s
; *
; * @brief       CMSIS Cortex-M3 based Core Device Startup File for Device startup_apm32f10x_cl
; *
; * @version     V1.0.0
; *
; * @date        2022-07-25
; *
; * @attention
; *
; *  Copyright (C) 2020-2022 Geehy Semiconductor
; *
; *  You may not use this file except in compliance with the
; *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
; *
; *  The program is only for reference, which is distributed in the hope
; *  that it will be useful and instructional for customers to develop
; *  their software. Unless required by applicable law or agreed to in
; *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
; *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
; *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
; *  and limitations under the License.
; */

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

__Vectors       DCD     __initial_sp                 ; Top of Stack
                DCD     Reset_Handler                ; Reset Handler
                DCD     NMI_Handler                  ; NMI Handler
                DCD     HardFault_Handler            ; Hard Fault Handler
                DCD     MemManage_Handler            ; MPU Fault Handler
                DCD     BusFault_Handler             ; Bus Fault Handler
                DCD     UsageFault_Handler           ; Usage Fault Handler
                DCD     0                            ; Reserved
                DCD     0                            ; Reserved
                DCD     0                            ; Reserved
                DCD     0                            ; Reserved
                DCD     SVC_Handler                  ; SVCall Handler
                DCD     DebugMon_Handler             ; Debug Monitor Handler
                DCD     0                            ; Reserved
                DCD     PendSV_Handler               ; PendSV Handler
                DCD     SysTick_Handler              ; SysTick Handler

                ; External Interrupts
                DCD     WWDT_IRQHandler              ; Window Watchdog
                DCD     PVD_IRQHandler               ; PVD through EINT Line detect
                DCD     TAMPER_IRQHandler            ; Tamper
                DCD     RTC_IRQHandler               ; RTC
                DCD     FLASH_IRQHandler             ; Flash
                DCD     RCM_IRQHandler               ; RCM
                DCD     EINT0_IRQHandler             ; EINT Line 0
                DCD     EINT1_IRQHandler             ; EINT Line 1
                DCD     EINT2_IRQHandler             ; EINT Line 2
                DCD     EINT3_IRQHandler             ; EINT Line 3
                DCD     EINT4_IRQHandler             ; EINT Line 4
                DCD     DMA1_Channel1_IRQHandler     ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler     ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler     ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler     ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler     ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler     ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler     ; DMA1 Channel 7
                DCD     ADC1_2_IRQHandler            ; ADC1 & ADC2
                DCD     CAN1_TX_IRQHandler           ; CAN1 TX
                DCD     CAN1_RX0_IRQHandler          ; CAN1 RX0
                DCD     CAN1_RX1_IRQHandler          ; CAN1 RX1
                DCD     CAN1_SCE_IRQHandler          ; CAN1 SCE
                DCD     EINT9_5_IRQHandler           ; EINT Line 9..5
                DCD     TMR1_BRK_IRQHandler          ; TMR1 Break
                DCD     TMR1_UP_IRQHandler           ; TMR1 Update
                DCD     TMR1_TRG_COM_IRQHandler      ; TMR1 Trigger and Commutation
                DCD     TMR1_CC_IRQHandler           ; TMR1 Capture Compare
                DCD     TMR2_IRQHandler              ; TMR2
                DCD     TMR3_IRQHandler              ; TMR3
                DCD     TMR4_IRQHandler              ; TMR4
                DCD     I2C1_EV_IRQHandler           ; I2C1 Event
                DCD     I2C1_ER_IRQHandler           ; I2C1 Error
                DCD     I2C2_EV_IRQHandler           ; I2C2 Event
                DCD     I2C2_ER_IRQHandler           ; I2C2 Error
                DCD     SPI1_IRQHandler              ; SPI1
                DCD     SPI2_IRQHandler              ; SPI2
                DCD     USART1_IRQHandler            ; USART1
                DCD     USART2_IRQHandler            ; USART2
                DCD     USART3_IRQHandler            ; USART3
                DCD     EINT15_10_IRQHandler         ; EINT Line 15..10
                DCD     RTCAlarm_IRQHandler          ; RTC Alarm through EINT Line
                DCD     OTG_FS_WKUP_IRQHandler       ; USBD Wakeup from suspend
                DCD     0                            ; Reserved
                DCD     0                            ; Reserved
                DCD     0                            ; Reserved
                DCD     0                            ; Reserved
                DCD     0                            ; Reserved
                DCD     0                            ; Reserved
                DCD     0                            ; Reserved
                DCD     TMR5_IRQHandler              ; TMR5
                DCD     SPI3_IRQHandler              ; SPI3
                DCD     UART4_IRQHandler             ; UART4
                DCD     UART5_IRQHandler             ; UART5
                DCD     TMR6_IRQHandler              ; TMR6
                DCD     TMR7_IRQHandler              ; TMR7
                DCD     DMA2_Channel1_IRQHandler     ; DMA2 Channel1
                DCD     DMA2_Channel2_IRQHandler     ; DMA2 Channel2
                DCD     DMA2_Channel3_IRQHandler     ; DMA2 Channel3
                DCD     DMA2_Channel4_IRQHandler     ; DMA2 Channel4
                DCD     DMA2_Channel5_IRQHandler     ; DMA2 Channel5
                DCD     ETH_IRQHandler               ; ETH
                DCD     ETH_WKUP_IRQHandler          ; ETH Wake up
                DCD     CAN2_TX_IRQHandler           ; CAN2 TX
                DCD     CAN2_RX0_IRQHandler          ; CAN2 RX0
                DCD     CAN2_RX1_IRQHandler          ; CAN2 RX1
                DCD     CAN2_SCE_IRQHandler          ; CAN2 SCE
                DCD     OTG_FS_IRQHandler            ; OTG FS
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler                [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                  [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler            [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler            [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler             [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler           [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                  [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler             [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler               [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler              [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDT_IRQHandler              [WEAK]
                EXPORT  PVD_IRQHandler               [WEAK]
                EXPORT  TAMPER_IRQHandler            [WEAK]
                EXPORT  RTC_IRQHandler               [WEAK]
                EXPORT  FLASH_IRQHandler             [WEAK]
                EXPORT  RCM_IRQHandler               [WEAK]
                EXPORT  EINT0_IRQHandler             [WEAK]
                EXPORT  EINT1_IRQHandler             [WEAK]
                EXPORT  EINT2_IRQHandler             [WEAK]
                EXPORT  EINT3_IRQHandler             [WEAK]
                EXPORT  EINT4_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler     [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler     [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler     [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler     [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler     [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler     [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler     [WEAK]
                EXPORT  ADC1_2_IRQHandler            [WEAK]
                EXPORT  CAN1_TX_IRQHandler           [WEAK]
                EXPORT  CAN1_RX0_IRQHandler          [WEAK]
                EXPORT  CAN1_RX1_IRQHandler          [WEAK]
                EXPORT  CAN1_SCE_IRQHandler          [WEAK]
                EXPORT  EINT9_5_IRQHandler           [WEAK]
                EXPORT  TMR1_BRK_IRQHandler          [WEAK]
                EXPORT  TMR1_UP_IRQHandler           [WEAK]
                EXPORT  TMR1_TRG_COM_IRQHandler      [WEAK]
                EXPORT  TMR1_CC_IRQHandler           [WEAK]
                EXPORT  TMR2_IRQHandler              [WEAK]
                EXPORT  TMR3_IRQHandler              [WEAK]
                EXPORT  TMR4_IRQHandler              [WEAK]
                EXPORT  I2C1_EV_IRQHandler           [WEAK]
                EXPORT  I2C1_ER_IRQHandler           [WEAK]
                EXPORT  I2C2_EV_IRQHandler           [WEAK]
                EXPORT  I2C2_ER_IRQHandler           [WEAK]
                EXPORT  SPI1_IRQHandler              [WEAK]
                EXPORT  SPI2_IRQHandler              [WEAK]
                EXPORT  USART1_IRQHandler            [WEAK]
                EXPORT  USART2_IRQHandler            [WEAK]
                EXPORT  USART3_IRQHandler            [WEAK]
                EXPORT  EINT15_10_IRQHandler         [WEAK]
                EXPORT  RTCAlarm_IRQHandler          [WEAK]
                EXPORT  OTG_FS_WKUP_IRQHandler       [WEAK]
                EXPORT  TMR5_IRQHandler              [WEAK]
                EXPORT  SPI3_IRQHandler              [WEAK]
                EXPORT  UART4_IRQHandler             [WEAK]
                EXPORT  UART5_IRQHandler             [WEAK]
                EXPORT  TMR6_IRQHandler              [WEAK]
                EXPORT  TMR7_IRQHandler              [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler     [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler     [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler     [WEAK]
                EXPORT  DMA2_Channel4_IRQHandler     [WEAK]
                EXPORT  DMA2_Channel5_IRQHandler     [WEAK]
                EXPORT  ETH_IRQHandler               [WEAK]
                EXPORT  ETH_WKUP_IRQHandler          [WEAK]
                EXPORT  CAN2_TX_IRQHandler           [WEAK]
                EXPORT  CAN2_RX0_IRQHandler          [WEAK]
                EXPORT  CAN2_RX1_IRQHandler          [WEAK]
                EXPORT  CAN2_SCE_IRQHandler          [WEAK]
                EXPORT  OTG_FS_IRQHandler            [WEAK]

WWDT_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCM_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
EINT4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_2_IRQHandler
CAN1_TX_IRQHandler
CAN1_RX0_IRQHandler
CAN1_RX1_IRQHandler
CAN1_SCE_IRQHandler
EINT9_5_IRQHandler
TMR1_BRK_IRQHandler
TMR1_UP_IRQHandler
TMR1_TRG_COM_IRQHandler
TMR1_CC_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
TMR4_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EINT15_10_IRQHandler
RTCAlarm_IRQHandler
OTG_FS_WKUP_IRQHandler
TMR5_IRQHandler
SPI3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
TMR6_IRQHandler
TMR7_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_IRQHandler
DMA2_Channel5_IRQHandler
ETH_IRQHandler
ETH_WKUP_IRQHandler
CAN2_TX_IRQHandler
CAN2_RX0_IRQHandler
CAN2_RX1_IRQHandler
CAN2_SCE_IRQHandler
OTG_FS_IRQHandler
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

                 LDR     R0, = Heap_Mem
                 LDR     R1, = (Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem  + Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;*******************************END OF FILE************************************

