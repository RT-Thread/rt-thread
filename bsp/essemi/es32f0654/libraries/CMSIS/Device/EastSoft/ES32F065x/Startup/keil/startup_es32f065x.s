;*******************************************************************************
; file       : startup_es32f065x.s
; description: es32f065x Device Startup File
; author     : AE Team
; data       : 29 Aug 2017
; note
;          Change Logs:
;          Date            Author          Notes
;          29 Aug 2017     AE Team         The first version
;
; Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
;
; SPDX-License-Identifier: Apache-2.0
;
; Licensed under the Apache License, Version 2.0 (the License); you may
; not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
; www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an AS IS BASIS, WITHOUT
; WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
;*********************************************************************************

;Stack Configuration------------------------------------------------------------
Stack_Size      EQU     0x00000400
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp
;-------------------------------------------------------------------------------

;Heap Configuration-------------------------------------------------------------
Heap_Size       EQU     0x00000000
                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit
;-------------------------------------------------------------------------------
                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset-------------------------------------
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp                      ;0,  load top of stack
                DCD     Reset_Handler                     ;1,  reset handler
                DCD     NMI_Handler                       ;2,  nmi handler
                DCD     HardFault_Handler                 ;3,  hard fault handler
                DCD     0                                 ;4,  MPU Fault Handler
                DCD     0                                 ;5,  Bus Fault Handler
                DCD     0                                 ;6,  Usage Fault Handler
                DCD     0                                 ;7,  Reserved
                DCD     0                                 ;8,  Reserved
                DCD     0                                 ;9,  Reserved
                DCD     0                                 ;10, Reserved
                DCD     SVC_Handler                       ;11, svcall handler
                DCD     DebugMon_Handler                  ;12, Debug Monitor Handler
                DCD     0                                 ;13, Reserved
                DCD     PendSV_Handler                    ;14, pendsv handler
                DCD     SysTick_Handler                   ;15, systick handler
                DCD     WWDG_IWDG_Handler                 ;16, irq0    WWDG_IWDG handler
                DCD     LVD_Handler                       ;17, irq1    LVD handler
                DCD     RTC_TSENSE_Handler                  ;18, irq2    RTC handler
                DCD     CRYPT_TRNG_Handler                ;19, irq3    CRYPT handler
                DCD     CMU_Handler                       ;20, irq4    CMU handler
                DCD     EXTI0_3_Handler                   ;21, irq5    EXTI0_3 handler
                DCD     EXTI4_7_Handler                   ;22, irq6    EXTI4_7 handler
                DCD     EXTI8_11_Handler                  ;23, irq7    EXTI8_11 handler
                DCD     EXTI12_15_Handler                 ;24, irq8    EXTI12_15 handler
                DCD     DMA_Handler                       ;25, irq9    DMA handler
                DCD     CAN0_Handler                      ;26, irq10   CAN0_CRYPT_TRNG handler
                DCD     LPTIM0_SPI2_Handler               ;27, irq11   LPTIM0_SPI2 handler
                DCD     ADC_ACMP_Handler                  ;28, irq12   ADC_ACMP handler
                DCD     AD16C4T0_BRK_UP_TRIG_COM_Handler  ;29, irq13   AD16C4T0_BRK_UP_TRIG_COM handler
                DCD     AD16C4T0_CC_Handler               ;30, irq14   AD16C4T0_CC handler
                DCD     BS16T0_Handler		          ;31, irq15   BS16T0 handler
                DCD     0             			  ;32, irq16   Reserved
                DCD     GP16C2T0_Handler                  ;33, irq17   GP16C2T0 handler
                DCD     GP16C2T1_Handler                  ;34, irq18   GP16C2T1 handler
                DCD     BS16T1_UART2_Handler              ;35, irq19   BS16T1_UART2 handler
                DCD     BS16T2_UART3_Handler              ;36, irq20   BS16T2_UART3 handler
                DCD     GP16C4T0_LCD_Handler              ;37, irq21   GP16C4T0_LCD handler
                DCD     BS16T3_DAC0_Handler               ;38, irq22   BS16T3_DAC0  handler
                DCD     I2C0_Handler                      ;39, irq23   I2C0 handler
                DCD     I2C1_Handler                      ;40, irq24   I2C1 handler
                DCD     SPI0_Handler                      ;41, irq25   SPI0 handler
                DCD     SPI1_Handler                      ;42, irq26   SPI1 handler
                DCD     UART0_Handler                     ;43, irq27   UART0 handler
                DCD     UART1_Handler                     ;44, irq28   UART1 handler
                DCD     USART0_Handler                    ;45, irq29   USART0 handler
                DCD     USART1_Handler                    ;46, irq30   USART1 handler
                DCD     LPUART0_Handler                   ;47, irq31   LPUART0 handler

;-------------------------------------------------------------------------------
                AREA    INT, CODE, READONLY             ;code begin

;Reset Handler----------------------------------------------
Reset_Handler   PROC
	EXPORT  Reset_Handler                  [WEAK]
	IMPORT  __main
	LDR     R0, =__main
	BX      R0
	NOP
	ALIGN
	ENDP

;system int-------------------------------------------------
NMI_Handler     PROC                           ;int 2
	EXPORT  NMI_Handler                    [WEAK]
	B       .
	ENDP

HardFault_Handler \
	PROC                                   ;int3
	EXPORT  HardFault_Handler              [WEAK]
	B       .
	ENDP

SVC_Handler \
	PROC                                   ;int11
	EXPORT  SVC_Handler                    [WEAK]
	B       .
	ENDP

DebugMon_Handler \
	PROC                                   ;int12
	EXPORT  DebugMon_Handler               [WEAK]
	B       .
	ENDP

PendSV_Handler  PROC                           ;int14
	EXPORT  PendSV_Handler                 [WEAK]
	B       .
	ENDP

SysTick_Handler \
	PROC                                   ;int15
	EXPORT  SysTick_Handler                [WEAK]
	B       .
	ENDP

;peripheral module int -----------------------------------------------
WWDG_IWDG_Handler \
	PROC                                   ;int16
	EXPORT  WWDG_IWDG_Handler              [WEAK]
	B       .
	ENDP

LVD_Handler \
	PROC                                   ;int17
	EXPORT  LVD_Handler                    [WEAK]
	B       .
	ENDP

RTC_TSENSE_Handler \
	PROC                                   ;int18
	EXPORT  RTC_TSENSE_Handler             [WEAK]
	B       .
	ENDP

CRYPT_TRNG_Handler \
	PROC                                   ;int19
	EXPORT  CRYPT_TRNG_Handler             [WEAK]
	B       .
	ENDP

CMU_Handler \
	PROC                                   ;int20
	EXPORT  CMU_Handler                    [WEAK]
	B       .
	ENDP

EXTI0_3_Handler \
	PROC                                   ;int21
	EXPORT  EXTI0_3_Handler                [WEAK]
	B       .
	ENDP

EXTI4_7_Handler \
	PROC                                   ;int22
	EXPORT  EXTI4_7_Handler                [WEAK]
	B       .
	ENDP

EXTI8_11_Handler \
	PROC                                   ;int23
	EXPORT  EXTI8_11_Handler               [WEAK]
	B       .
	ENDP

EXTI12_15_Handler \
	PROC                                   ;int24
	EXPORT  EXTI12_15_Handler              [WEAK]
	B       .
	ENDP

DMA_Handler \
	PROC                                   ;int25
	EXPORT  DMA_Handler                    [WEAK]
	B       .
	ENDP

CAN0_Handler \
	PROC                                   ;int26
	EXPORT  CAN0_Handler                   [WEAK]
	B       .
	ENDP

LPTIM0_SPI2_Handler \
	PROC                                   ;int27
	EXPORT  LPTIM0_SPI2_Handler            [WEAK]
	B       .
	ENDP

ADC_ACMP_Handler \
	PROC                                   ;int28
	EXPORT  ADC_ACMP_Handler               [WEAK]
	B       .
	ENDP

AD16C4T0_BRK_UP_TRIG_COM_Handler \
	PROC                                     ;int29
	EXPORT  AD16C4T0_BRK_UP_TRIG_COM_Handler [WEAK]
	B       .
	ENDP

AD16C4T0_CC_Handler \
	PROC                                   ;int30
	EXPORT  AD16C4T0_CC_Handler            [WEAK]
	B       .
	ENDP

BS16T0_Handler \
	PROC                                   ;int31
	EXPORT  BS16T0_Handler [WEAK]
	B       .
	ENDP

GP16C2T0_Handler PROC                           ;int33
	EXPORT  GP16C2T0_Handler                [WEAK]
	B       .
	ENDP

GP16C2T1_Handler  PROC                          ;int34
	EXPORT  GP16C2T1_Handler                [WEAK]
	B       .
	ENDP

BS16T1_UART2_Handler \
	PROC                                   ;int35
	EXPORT  BS16T1_UART2_Handler           [WEAK]
	B       .
	ENDP

BS16T2_UART3_Handler \
	PROC                                   ;int36
	EXPORT  BS16T2_UART3_Handler           [WEAK]
	B       .
	ENDP

GP16C4T0_LCD_Handler \
	PROC                                   ;int37
	EXPORT  GP16C4T0_LCD_Handler           [WEAK]
	B       .
	ENDP

BS16T3_DAC0_Handler \
	PROC                                   ;int38
	EXPORT  BS16T3_DAC0_Handler            [WEAK]
	B       .
	ENDP

I2C0_Handler \
	PROC                                   ;int39
	EXPORT  I2C0_Handler                   [WEAK]
	B       .
	ENDP

I2C1_Handler \
	PROC                                   ;int40
	EXPORT  I2C1_Handler                   [WEAK]
	B       .
	ENDP

SPI0_Handler \
	PROC                                   ;int41
	EXPORT  SPI0_Handler                   [WEAK]
	B       .
	ENDP

SPI1_Handler \
	PROC                                   ;int42
	EXPORT  SPI1_Handler                   [WEAK]
	B       .
	ENDP

UART0_Handler \
	PROC                                   ;int43
	EXPORT  UART0_Handler                  [WEAK]
	B       .
	ENDP

UART1_Handler \
	PROC                                   ;int44
	EXPORT  UART1_Handler                  [WEAK]
	B       .
	ENDP

USART0_Handler \
	PROC                                   ;int45
	EXPORT  USART0_Handler                 [WEAK]
	B       .
	ENDP

USART1_Handler \
	PROC                                   ;int46
	EXPORT  USART1_Handler                 [WEAK]
	B       .
	ENDP

LPUART0_Handler \
	PROC                                   ;int47
	EXPORT  LPUART0_Handler                [WEAK]
	B       .
	ENDP

; User Initial Stack & Heap-----------------------------------------------------
	ALIGN
	IF      :DEF:__MICROLIB

	EXPORT  __initial_sp
	EXPORT  __heap_base
	EXPORT  __heap_limit

	ELSE

	IMPORT  __use_two_region_memory
	EXPORT  __user_initial_stackheap
__user_initial_stackheap
	LDR     R0, =  Heap_Mem
	LDR     R1, = (Stack_Mem + Stack_Size)
	LDR     R2, = (Heap_Mem +  Heap_Size)
	LDR     R3, = Stack_Mem
	BX      LR

	ALIGN

	ENDIF

	END
