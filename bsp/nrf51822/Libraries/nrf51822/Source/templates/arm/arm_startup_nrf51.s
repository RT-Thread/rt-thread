; Copyright (c) 2013, Nordic Semiconductor ASA
; All rights reserved.
; 
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions are met:
; 
; * Redistributions of source code must retain the above copyright notice, this
;   list of conditions and the following disclaimer.
; 
; * Redistributions in binary form must reproduce the above copyright notice,
;   this list of conditions and the following disclaimer in the documentation
;   and/or other materials provided with the distribution.
; 
; * Neither the name of Nordic Semiconductor ASA nor the names of its
;   contributors may be used to endorse or promote products derived from
;   this software without specific prior written permission.
; 
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
; FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
; DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
; SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
; CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
; OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
; OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
; NOTE: Template files (including this one) are application specific and therefore 
; expected to be copied into the application project folder prior to its use!

; Description message

Stack_Size      EQU     0x00000400
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

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
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD      POWER_CLOCK_IRQHandler ;POWER_CLOCK
                DCD      RADIO_IRQHandler ;RADIO
                DCD      UART0_IRQHandler ;UART0
                DCD      SPI0_TWI0_IRQHandler ;SPI0_TWI0
                DCD      SPI1_TWI1_IRQHandler ;SPI1_TWI1
                DCD      0 ;Reserved
                DCD      GPIOTE_IRQHandler ;GPIOTE
                DCD      ADC_IRQHandler ;ADC
                DCD      TIMER0_IRQHandler ;TIMER0
                DCD      TIMER1_IRQHandler ;TIMER1
                DCD      TIMER2_IRQHandler ;TIMER2
                DCD      RTC0_IRQHandler ;RTC0
                DCD      TEMP_IRQHandler ;TEMP
                DCD      RNG_IRQHandler ;RNG
                DCD      ECB_IRQHandler ;ECB
                DCD      CCM_AAR_IRQHandler ;CCM_AAR
                DCD      WDT_IRQHandler ;WDT
                DCD      RTC1_IRQHandler ;RTC1
                DCD      QDEC_IRQHandler ;QDEC
                DCD      LPCOMP_IRQHandler ;LPCOMP
                DCD      SWI0_IRQHandler ;SWI0
                DCD      SWI1_IRQHandler ;SWI1
                DCD      SWI2_IRQHandler ;SWI2
                DCD      SWI3_IRQHandler ;SWI3
                DCD      SWI4_IRQHandler ;SWI4
                DCD      SWI5_IRQHandler ;SWI5
                DCD      0 ;Reserved
                DCD      0 ;Reserved
                DCD      0 ;Reserved
                DCD      0 ;Reserved
                DCD      0 ;Reserved
                DCD      0 ;Reserved


__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset Handler

NRF_POWER_RAMON_ADDRESS            EQU   0x40000524  ; NRF_POWER->RAMON address
NRF_POWER_RAMONB_ADDRESS           EQU   0x40000554  ; NRF_POWER->RAMONB address
NRF_POWER_RAMONx_RAMxON_ONMODE_Msk EQU   0x3         ; All RAM blocks on in onmode bit mask

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                
                MOVS    R1, #NRF_POWER_RAMONx_RAMxON_ONMODE_Msk
                
                LDR     R0, =NRF_POWER_RAMON_ADDRESS
                LDR     R2, [R0]
                ORRS    R2, R2, R1
                STR     R2, [R0]
                
                LDR     R0, =NRF_POWER_RAMONB_ADDRESS
                LDR     R2, [R0]
                ORRS    R2, R2, R1
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

                EXPORT   POWER_CLOCK_IRQHandler [WEAK]
                EXPORT   RADIO_IRQHandler [WEAK]
                EXPORT   UART0_IRQHandler [WEAK]
                EXPORT   SPI0_TWI0_IRQHandler [WEAK]
                EXPORT   SPI1_TWI1_IRQHandler [WEAK]
                EXPORT   GPIOTE_IRQHandler [WEAK]
                EXPORT   ADC_IRQHandler [WEAK]
                EXPORT   TIMER0_IRQHandler [WEAK]
                EXPORT   TIMER1_IRQHandler [WEAK]
                EXPORT   TIMER2_IRQHandler [WEAK]
                EXPORT   RTC0_IRQHandler [WEAK]
                EXPORT   TEMP_IRQHandler [WEAK]
                EXPORT   RNG_IRQHandler [WEAK]
                EXPORT   ECB_IRQHandler [WEAK]
                EXPORT   CCM_AAR_IRQHandler [WEAK]
                EXPORT   WDT_IRQHandler [WEAK]
                EXPORT   RTC1_IRQHandler [WEAK]
                EXPORT   QDEC_IRQHandler [WEAK]
                EXPORT   LPCOMP_IRQHandler [WEAK]
                EXPORT   SWI0_IRQHandler [WEAK]
                EXPORT   SWI1_IRQHandler [WEAK]
                EXPORT   SWI2_IRQHandler [WEAK]
                EXPORT   SWI3_IRQHandler [WEAK]
                EXPORT   SWI4_IRQHandler [WEAK]
                EXPORT   SWI5_IRQHandler [WEAK]
POWER_CLOCK_IRQHandler
RADIO_IRQHandler
UART0_IRQHandler
SPI0_TWI0_IRQHandler
SPI1_TWI1_IRQHandler
GPIOTE_IRQHandler
ADC_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
RTC0_IRQHandler
TEMP_IRQHandler
RNG_IRQHandler
ECB_IRQHandler
CCM_AAR_IRQHandler
WDT_IRQHandler
RTC1_IRQHandler
QDEC_IRQHandler
LPCOMP_IRQHandler
SWI0_IRQHandler
SWI1_IRQHandler
SWI2_IRQHandler
SWI3_IRQHandler
SWI4_IRQHandler
SWI5_IRQHandler

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

                LDR     R0, = Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem + Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END

