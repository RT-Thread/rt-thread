;/**************************************************************************//**
; * @file     startup_SAME70.s
; * @brief    CMSIS Core Device Startup File for
; *           Atmel SAME70 Device Series
; * @version  V1.00
; * @date     19. January 2015
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2011 - 2015 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


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

__Vectors       DCD     __initial_sp              ;     Top of Stack
                DCD     Reset_Handler             ;     Reset Handler
                DCD     NMI_Handler               ;     NMI Handler
                DCD     HardFault_Handler         ;     Hard Fault Handler
                DCD     MemManage_Handler         ;     MPU Fault Handler
                DCD     BusFault_Handler          ;     Bus Fault Handler
                DCD     UsageFault_Handler        ;     Usage Fault Handler
                DCD     0                         ;     Reserved
                DCD     0                         ;     Reserved
                DCD     0                         ;     Reserved
                DCD     0                         ;     Reserved
                DCD     SVC_Handler               ;     SVCall Handler
                DCD     DebugMon_Handler          ;     Debug Monitor Handler
                DCD     0                         ;     Reserved
                DCD     PendSV_Handler            ;     PendSV Handler
                DCD     SysTick_Handler           ;     SysTick Handler

                ; External Interrupts
                DCD     SUPC_Handler              ;  0 Supply Controller
                DCD     RSTC_Handler              ;  1 Reset Controller
                DCD     RTC_Handler               ;  2 Real Time Clock
                DCD     RTT_Handler               ;  3 Real Time Timer
                DCD     WDT_Handler               ;  4 Watchdog Timer
                DCD     PMC_Handler               ;  5 Power Management Controller
                DCD     EFC_Handler               ;  6 Enhanced Embedded Flash Controller
                DCD     UART0_Handler             ;  7 UART 0
                DCD     UART1_Handler             ;  8 UART 1
                DCD     0                         ;  9 Reserved
                DCD     PIOA_Handler              ; 10 Parallel I/O Controller A
                DCD     PIOB_Handler              ; 11 Parallel I/O Controller B
                DCD     PIOC_Handler              ; 12 Parallel I/O Controller C
                DCD     USART0_Handler            ; 13 USART 0
                DCD     USART1_Handler            ; 14 USART 1
                DCD     USART2_Handler            ; 15 USART 2
                DCD     PIOD_Handler              ; 16 Parallel I/O Controller D
                DCD     PIOE_Handler              ; 17 Parallel I/O Controller E
                DCD     HSMCI_Handler             ; 18 Multimedia Card Interface
                DCD     TWIHS0_Handler            ; 19 Two Wire Interface 0 HS
                DCD     TWIHS1_Handler            ; 20 Two Wire Interface 1 HS
                DCD     SPI0_Handler              ; 21 Serial Peripheral Interface 0
                DCD     SSC_Handler               ; 22 Synchronous Serial Controller
                DCD     TC0_Handler               ; 23 Timer/Counter 0
                DCD     TC1_Handler               ; 24 Timer/Counter 1
                DCD     TC2_Handler               ; 25 Timer/Counter 2
                DCD     TC3_Handler               ; 26 Timer/Counter 3
                DCD     TC4_Handler               ; 27 Timer/Counter 4
                DCD     TC5_Handler               ; 28 Timer/Counter 5
                DCD     AFEC0_Handler             ; 29 Analog Front End 0
                DCD     DACC_Handler              ; 30 Digital To Analog Converter
                DCD     PWM0_Handler              ; 31 Pulse Width Modulation 0
                DCD     ICM_Handler               ; 32 Integrity Check Monitor
                DCD     ACC_Handler               ; 33 Analog Comparator
                DCD     USBHS_Handler             ; 34 USB Host / Device Controller
                DCD     MCAN0_Handler             ; 35 MCAN Controller 0
                DCD     0                         ; 36 Reserved
                DCD     MCAN1_Handler             ; 37 MCAN Controller 1
                DCD     0                         ; 38 Reserved
                DCD     GMAC_Handler              ; 39 Ethernet MAC
                DCD     AFEC1_Handler             ; 40 Analog Front End 1
                DCD     TWIHS2_Handler            ; 41 Two Wire Interface 2 HS
                DCD     SPI1_Handler              ; 42 Serial Peripheral Interface 1
                DCD     QSPI_Handler              ; 43 Quad I/O Serial Peripheral Interface
                DCD     UART2_Handler             ; 44 UART 2
                DCD     UART3_Handler             ; 45 UART 3
                DCD     UART4_Handler             ; 46 UART 4
                DCD     TC6_Handler               ; 47 Timer/Counter 6
                DCD     TC7_Handler               ; 48 Timer/Counter 7
                DCD     TC8_Handler               ; 49 Timer/Counter 8
                DCD     TC9_Handler               ; 50 Timer/Counter 9
                DCD     TC10_Handler              ; 51 Timer/Counter 10
                DCD     TC11_Handler              ; 52 Timer/Counter 11
                DCD     0                         ; 53 Reserved
                DCD     0                         ; 54 Reserved
                DCD     0                         ; 55 Reserved
                DCD     AES_Handler               ; 56 AES
                DCD     TRNG_Handler              ; 57 True Random Generator
                DCD     XDMAC_Handler             ; 58 DMA
                DCD     ISI_Handler               ; 59 Camera Interface
                DCD     PWM1_Handler              ; 60 Pulse Width Modulation 1
                DCD     0                         ; 61 Reserved
                DCD     SDRAMC_Handler            ; 62 SDRAM Controller
                DCD     RSWDT_Handler             ; 63 Reinforced Secure Watchdog Timer
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

NMI_Handler     PROC
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
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
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
                EXPORT  SUPC_Handler              [WEAK]
                EXPORT  RSTC_Handler              [WEAK]
                EXPORT  RTC_Handler               [WEAK]
                EXPORT  RTT_Handler               [WEAK]
                EXPORT  WDT_Handler               [WEAK]
                EXPORT  PMC_Handler               [WEAK]
                EXPORT  EFC_Handler               [WEAK]
                EXPORT  UART0_Handler             [WEAK]
                EXPORT  UART1_Handler             [WEAK]
                EXPORT  PIOA_Handler              [WEAK]
                EXPORT  PIOB_Handler              [WEAK]
                EXPORT  PIOC_Handler              [WEAK]
                EXPORT  USART0_Handler            [WEAK]
                EXPORT  USART1_Handler            [WEAK]
                EXPORT  USART2_Handler            [WEAK]
                EXPORT  PIOD_Handler              [WEAK]
                EXPORT  PIOE_Handler              [WEAK]
                EXPORT  HSMCI_Handler             [WEAK]
                EXPORT  TWIHS0_Handler            [WEAK]
                EXPORT  TWIHS1_Handler            [WEAK]
                EXPORT  SPI0_Handler              [WEAK]
                EXPORT  SSC_Handler               [WEAK]
                EXPORT  TC0_Handler               [WEAK]
                EXPORT  TC1_Handler               [WEAK]
                EXPORT  TC2_Handler               [WEAK]
                EXPORT  TC3_Handler               [WEAK]
                EXPORT  TC4_Handler               [WEAK]
                EXPORT  TC5_Handler               [WEAK]
                EXPORT  AFEC0_Handler             [WEAK]
                EXPORT  DACC_Handler              [WEAK]
                EXPORT  PWM0_Handler              [WEAK]
                EXPORT  ICM_Handler               [WEAK]
                EXPORT  ACC_Handler               [WEAK]
                EXPORT  USBHS_Handler             [WEAK]
                EXPORT  MCAN0_Handler             [WEAK]
                EXPORT  MCAN1_Handler             [WEAK]
                EXPORT  GMAC_Handler              [WEAK]
                EXPORT  AFEC1_Handler             [WEAK]
                EXPORT  TWIHS2_Handler            [WEAK]
                EXPORT  SPI1_Handler              [WEAK]
                EXPORT  QSPI_Handler              [WEAK]
                EXPORT  UART2_Handler             [WEAK]
                EXPORT  UART3_Handler             [WEAK]
                EXPORT  UART4_Handler             [WEAK]
                EXPORT  TC6_Handler               [WEAK]
                EXPORT  TC7_Handler               [WEAK]
                EXPORT  TC8_Handler               [WEAK]
                EXPORT  TC9_Handler               [WEAK]
                EXPORT  TC10_Handler              [WEAK]
                EXPORT  TC11_Handler              [WEAK]
                EXPORT  AES_Handler               [WEAK]
                EXPORT  TRNG_Handler              [WEAK]
                EXPORT  XDMAC_Handler             [WEAK]
                EXPORT  ISI_Handler               [WEAK]
                EXPORT  PWM1_Handler              [WEAK]
                EXPORT  SDRAMC_Handler            [WEAK]
                EXPORT  RSWDT_Handler             [WEAK]

SUPC_Handler
RSTC_Handler
RTC_Handler
RTT_Handler
WDT_Handler
PMC_Handler
EFC_Handler
UART0_Handler
UART1_Handler
PIOA_Handler
PIOB_Handler
PIOC_Handler
USART0_Handler
USART1_Handler
USART2_Handler
PIOD_Handler
PIOE_Handler
HSMCI_Handler
TWIHS0_Handler
TWIHS1_Handler
SPI0_Handler
SSC_Handler
TC0_Handler
TC1_Handler
TC2_Handler
TC3_Handler
TC4_Handler
TC5_Handler
AFEC0_Handler
DACC_Handler
PWM0_Handler
ICM_Handler
ACC_Handler
USBHS_Handler
MCAN0_Handler
MCAN1_Handler
GMAC_Handler
AFEC1_Handler
TWIHS2_Handler
SPI1_Handler
QSPI_Handler
UART2_Handler
UART3_Handler
UART4_Handler
TC6_Handler
TC7_Handler
TC8_Handler
TC9_Handler
TC10_Handler
TC11_Handler
AES_Handler
TRNG_Handler
XDMAC_Handler
ISI_Handler
PWM1_Handler
SDRAMC_Handler
RSWDT_Handler
                B       .

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
