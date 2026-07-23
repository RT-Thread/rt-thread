;/******************************************************************************
;* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
;*
;* This software is owned and published by:
;* Huada Semiconductor Co.,Ltd ("HDSC").
;*
;* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
;* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
;*
;* This software contains source code for use with HDSC
;* components. This software is licensed by HDSC to be adapted only
;* for use in systems utilizing HDSC components. HDSC shall not be
;* responsible for misuse or illegal use of this software for devices not
;* supported herein. HDSC is providing this software "AS IS" and will
;* not be responsible for issues arising from incorrect user implementation
;* of the software.
;*
;* Disclaimer:
;* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
;* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
;* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
;* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
;* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
;* WARRANTY OF NONINFRINGEMENT.
;* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
;* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
;* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
;* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
;* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
;* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
;* SAVINGS OR PROFITS,
;* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
;* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
;* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
;* FROM, THE SOFTWARE.
;*
;* This software may be replicated in part or whole for the licensed use,
;* with the restriction that this Disclaimer and Copyright notice must be
;* included with each copy of this software, whether used in part or whole,
;* at all times.
;*/
;/*****************************************************************************/

;/*****************************************************************************/
;/*  Startup for ARM                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2019-03-01                                                   */
;/*  Target-mcu  {MCU_PN_H}                                                   */
;/*****************************************************************************/

; Stack Configuration
; Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Heap Configuration
;  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>

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

__Vectors                       
                DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset        
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

                DCD     PORTA_IRQHandler
                DCD     PORTB_IRQHandler
                DCD     PORTC_E_IRQHandler
                DCD     PORTD_F_IRQHandler
                DCD     DMAC_IRQHandler
                DCD     TIM3_IRQHandler
                DCD     UART0_2_IRQHandler
                DCD     UART1_3_IRQHandler
                DCD     LPUART0_IRQHandler
                DCD     LPUART1_IRQHandler
                DCD     SPI0_IRQHandler
                DCD     SPI1_IRQHandler
                DCD     I2C0_IRQHandler
                DCD     I2C1_IRQHandler
                DCD     TIM0_IRQHandler
                DCD     TIM1_IRQHandler
                DCD     TIM2_IRQHandler
                DCD     LPTIM0_1_IRQHandler
                DCD     TIM4_IRQHandler
                DCD     TIM5_IRQHandler
                DCD     TIM6_IRQHandler
                DCD     PCA_IRQHandler
                DCD     WDT_IRQHandler
                DCD     RTC_IRQHandler
                DCD     ADC_DAC_IRQHandler
                DCD     PCNT_IRQHandler
                DCD     VC0_IRQHandler
                DCD     VC1_2_IRQHandler
                DCD     LVD_IRQHandler
                DCD     LCD_IRQHandler
                DCD     FLASH_RAM_IRQHandler
                DCD     CLKTRIM_IRQHandler

                

__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

               ;reset NVIC if in rom debug
                LDR     R0, =0x20000000
                LDR     R2, =0x0
                MOVS    R1, #0                 ; for warning, 
                ADD     R1, PC,#0              ; for A1609W, 
                CMP     R1, R0
                BLS     RAMCODE

              ; ram code base address. 
                ADD     R2, R0,R2
RAMCODE
              ; reset Vector table address.
                LDR     R0, =0xE000ED08 
                STR     R2, [R0]

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
                
                
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  PORTA_IRQHandler                [WEAK]
                EXPORT  PORTB_IRQHandler                [WEAK]
                EXPORT  PORTC_E_IRQHandler              [WEAK]
                EXPORT  PORTD_F_IRQHandler              [WEAK]
                EXPORT  DMAC_IRQHandler                 [WEAK]
                EXPORT  TIM3_IRQHandler                 [WEAK]
                EXPORT  UART0_2_IRQHandler              [WEAK]
                EXPORT  UART1_3_IRQHandler              [WEAK]
                EXPORT  LPUART0_IRQHandler              [WEAK]
                EXPORT  LPUART1_IRQHandler              [WEAK]
                EXPORT  SPI0_IRQHandler                 [WEAK]
                EXPORT  SPI1_IRQHandler                 [WEAK]
                EXPORT  I2C0_IRQHandler                 [WEAK]
                EXPORT  I2C1_IRQHandler                 [WEAK]
                EXPORT  TIM0_IRQHandler                 [WEAK]
                EXPORT  TIM1_IRQHandler                 [WEAK]
                EXPORT  TIM2_IRQHandler                 [WEAK]
                EXPORT  LPTIM0_1_IRQHandler             [WEAK]
                EXPORT  TIM4_IRQHandler                 [WEAK]
                EXPORT  TIM5_IRQHandler                 [WEAK]
                EXPORT  TIM6_IRQHandler                 [WEAK]
                EXPORT  PCA_IRQHandler                  [WEAK]
                EXPORT  WDT_IRQHandler                  [WEAK]
                EXPORT  RTC_IRQHandler                  [WEAK]
                EXPORT  ADC_DAC_IRQHandler              [WEAK]
                EXPORT  PCNT_IRQHandler                 [WEAK]
                EXPORT  VC0_IRQHandler                  [WEAK]
                EXPORT  VC1_2_IRQHandler                [WEAK]
                EXPORT  LVD_IRQHandler                  [WEAK]
                EXPORT  LCD_IRQHandler                  [WEAK]
                EXPORT  FLASH_RAM_IRQHandler            [WEAK]
                EXPORT  CLKTRIM_IRQHandler              [WEAK]
PORTA_IRQHandler
PORTB_IRQHandler
PORTC_E_IRQHandler
PORTD_F_IRQHandler
DMAC_IRQHandler
TIM3_IRQHandler
UART0_2_IRQHandler
UART1_3_IRQHandler
LPUART0_IRQHandler
LPUART1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
TIM0_IRQHandler
TIM1_IRQHandler
TIM2_IRQHandler
LPTIM0_1_IRQHandler
TIM4_IRQHandler
TIM5_IRQHandler
TIM6_IRQHandler
PCA_IRQHandler
WDT_IRQHandler
RTC_IRQHandler
ADC_DAC_IRQHandler
PCNT_IRQHandler
VC0_IRQHandler
VC1_2_IRQHandler
LVD_IRQHandler
LCD_IRQHandler
FLASH_RAM_IRQHandler
CLKTRIM_IRQHandler

                
               B .

                ENDP


                ALIGN


; User Initial Stack & Heap

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
