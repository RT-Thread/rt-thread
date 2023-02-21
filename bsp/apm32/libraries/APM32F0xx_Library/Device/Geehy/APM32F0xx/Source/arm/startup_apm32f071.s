;/*!
; * @file       startup_apm32f071.s
; *
; * @brief      CMSIS Cortex-M0 PLUS based Core Device Startup File for Device startup_apm32f071
; *
; * @version    V1.0.2
; *
; * @date       2022-02-21
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
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
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

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts
                DCD     WWDT_IRQHandler                ; Window Watchdog
                DCD     PVD_VDDIO2_IRQHandler          ; PVD and VDDIO2 through EINT Line detect
                DCD     RTC_IRQHandler                 ; RTC through EINT Line
                DCD     FLASH_IRQHandler               ; FLASH
                DCD     RCM_CRS_IRQHandler             ; RCM and CRS
                DCD     EINT0_1_IRQHandler             ; EINT Line 0 and 1
                DCD     EINT2_3_IRQHandler             ; EINT Line 2 and 3
                DCD     EINT4_15_IRQHandler            ; EINT Line 4 to 15
                DCD     TSC_IRQHandler                 ; TSC
                DCD     DMA1_CH1_IRQHandler            ; DMA1 Channel 1
                DCD     DMA1_CH2_3_IRQHandler          ; DMA1 Channel 2 and Channel 3
                DCD     DMA1_CH4_5_6_7_IRQHandler      ; DMA1 Channel 4, Channel 5, Channel 6 and Channel 7
                DCD     ADC1_COMP_IRQHandler           ; ADC1, COMP1 and COMP2
                DCD     TMR1_BRK_UP_TRG_COM_IRQHandler ; TMR1 Break, Update, Trigger and Commutation
                DCD     TMR1_CC_IRQHandler             ; TMR1 Capture Compare
                DCD     TMR2_IRQHandler                ; TMR2
                DCD     TMR3_IRQHandler                ; TMR3
                DCD     TMR6_DAC_IRQHandler            ; TMR6 and DAC
                DCD     TMR7_IRQHandler                ; TMR7
                DCD     TMR14_IRQHandler               ; TMR14
                DCD     TMR15_IRQHandler               ; TMR15
                DCD     TMR16_IRQHandler               ; TMR16
                DCD     TMR17_IRQHandler               ; TMR17
                DCD     I2C1_IRQHandler                ; I2C1
                DCD     I2C2_IRQHandler                ; I2C2
                DCD     SPI1_IRQHandler                ; SPI1
                DCD     SPI2_IRQHandler                ; SPI2
                DCD     USART1_IRQHandler              ; USART1
                DCD     USART2_IRQHandler              ; USART2
                DCD     USART3_4_IRQHandler            ; USART3 and USART4
                DCD     CEC_IRQHandler                 ; CEC

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler   PROC
                EXPORT  Reset_Handler                 [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDT_IRQHandler                [WEAK]
                EXPORT  PVD_VDDIO2_IRQHandler          [WEAK]
                EXPORT  RTC_IRQHandler                 [WEAK]
                EXPORT  FLASH_IRQHandler               [WEAK]
                EXPORT  RCM_CRS_IRQHandler             [WEAK]
                EXPORT  EINT0_1_IRQHandler             [WEAK]
                EXPORT  EINT2_3_IRQHandler             [WEAK]
                EXPORT  EINT4_15_IRQHandler            [WEAK]
                EXPORT  TSC_IRQHandler                 [WEAK]
                EXPORT  DMA1_CH1_IRQHandler            [WEAK]
                EXPORT  DMA1_CH2_3_IRQHandler          [WEAK]
                EXPORT  DMA1_CH4_5_6_7_IRQHandler      [WEAK]
                EXPORT  ADC1_COMP_IRQHandler           [WEAK]
                EXPORT  TMR1_BRK_UP_TRG_COM_IRQHandler [WEAK]
                EXPORT  TMR1_CC_IRQHandler             [WEAK]
                EXPORT  TMR2_IRQHandler                [WEAK]
                EXPORT  TMR3_IRQHandler                [WEAK]
                EXPORT  TMR6_DAC_IRQHandler            [WEAK]
                EXPORT  TMR7_IRQHandler                [WEAK]
                EXPORT  TMR14_IRQHandler               [WEAK]
                EXPORT  TMR15_IRQHandler               [WEAK]
                EXPORT  TMR16_IRQHandler               [WEAK]
                EXPORT  TMR17_IRQHandler               [WEAK]
                EXPORT  I2C1_IRQHandler                [WEAK]
                EXPORT  I2C2_IRQHandler                [WEAK]
                EXPORT  SPI1_IRQHandler                [WEAK]
                EXPORT  SPI2_IRQHandler                [WEAK]
                EXPORT  USART1_IRQHandler              [WEAK]
                EXPORT  USART2_IRQHandler              [WEAK]
                EXPORT  USART3_4_IRQHandler            [WEAK]
                EXPORT  CEC_IRQHandler                 [WEAK]


WWDT_IRQHandler
PVD_VDDIO2_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCM_CRS_IRQHandler
EINT0_1_IRQHandler
EINT2_3_IRQHandler
EINT4_15_IRQHandler
TSC_IRQHandler
DMA1_CH1_IRQHandler
DMA1_CH2_3_IRQHandler
DMA1_CH4_5_6_7_IRQHandler
ADC1_COMP_IRQHandler
TMR1_BRK_UP_TRG_COM_IRQHandler
TMR1_CC_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
TMR6_DAC_IRQHandler
TMR7_IRQHandler
TMR14_IRQHandler
TMR15_IRQHandler
TMR16_IRQHandler
TMR17_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_4_IRQHandler
CEC_IRQHandler

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