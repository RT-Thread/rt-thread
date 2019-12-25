; Copyright (c) 2009-2018 ARM Limited. All rights reserved.
; 
;     SPDX-License-Identifier: Apache-2.0
; 
; Licensed under the Apache License, Version 2.0 (the License); you may
; not use this file except in compliance with the License.
; You may obtain a copy of the License at
; 
;     www.apache.org/licenses/LICENSE-2.0
; 
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an AS IS BASIS, WITHOUT
; WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
; 
; NOTICE: This file has been modified by Nordic Semiconductor ASA.

; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.

        MODULE  ?cstartup

#if defined(__STARTUP_CONFIG)

        #include "startup_config.h"

        #ifndef __STARTUP_CONFIG_STACK_ALIGNEMENT
        #define __STARTUP_CONFIG_STACK_ALIGNEMENT 3
        #endif
        
        SECTION CSTACK:DATA:NOROOT(__STARTUP_CONFIG_STACK_ALIGNEMENT)
        DS8 __STARTUP_CONFIG_STACK_SIZE

        SECTION HEAP:DATA:NOROOT(3)
        DS8 __STARTUP_CONFIG_HEAP_SIZE

#else

        ;; Stack size default : Defined in *.icf (linker file). Can be modified inside EW.
        ;; Heap size default : Defined in *.icf (linker file). Can be modified inside EW.

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

#endif


        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler
        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     SVC_Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     POWER_CLOCK_IRQHandler
        DCD     RADIO_IRQHandler
        DCD     UART0_IRQHandler
        DCD     SPI0_TWI0_IRQHandler
        DCD     SPI1_TWI1_IRQHandler
        DCD     0                         ; Reserved
        DCD     GPIOTE_IRQHandler
        DCD     ADC_IRQHandler
        DCD     TIMER0_IRQHandler
        DCD     TIMER1_IRQHandler
        DCD     TIMER2_IRQHandler
        DCD     RTC0_IRQHandler
        DCD     TEMP_IRQHandler
        DCD     RNG_IRQHandler
        DCD     ECB_IRQHandler
        DCD     CCM_AAR_IRQHandler
        DCD     WDT_IRQHandler
        DCD     RTC1_IRQHandler
        DCD     QDEC_IRQHandler
        DCD     LPCOMP_IRQHandler
        DCD     SWI0_IRQHandler
        DCD     SWI1_IRQHandler
        DCD     SWI2_IRQHandler
        DCD     SWI3_IRQHandler
        DCD     SWI4_IRQHandler
        DCD     SWI5_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved

__Vectors_End
__Vectors                           EQU   __vector_table
__Vectors_Size                      EQU   __Vectors_End - __Vectors

NRF_POWER_RAMON_ADDRESS              EQU   0x40000524  ; NRF_POWER->RAMON address
NRF_POWER_RAMONB_ADDRESS             EQU   0x40000554  ; NRF_POWER->RAMONB address
NRF_POWER_RAMONx_RAMxON_ONMODE_Msk   EQU   0x3         ; All RAM blocks on in onmode bit mask

; Default handlers.
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
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
        LDR     R0, =__iar_program_start
        BX      R0

        ; Dummy exception handlers


        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .


       ; Dummy interrupt handlers

        PUBWEAK  POWER_CLOCK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
POWER_CLOCK_IRQHandler
        B .

        PUBWEAK  RADIO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RADIO_IRQHandler
        B .

        PUBWEAK  UART0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART0_IRQHandler
        B .

        PUBWEAK  SPI0_TWI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI0_TWI0_IRQHandler
        B .

        PUBWEAK  SPI1_TWI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_TWI1_IRQHandler
        B .

        PUBWEAK  GPIOTE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOTE_IRQHandler
        B .

        PUBWEAK  ADC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC_IRQHandler
        B .

        PUBWEAK  TIMER0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER0_IRQHandler
        B .

        PUBWEAK  TIMER1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER1_IRQHandler
        B .

        PUBWEAK  TIMER2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER2_IRQHandler
        B .

        PUBWEAK  RTC0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC0_IRQHandler
        B .

        PUBWEAK  TEMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TEMP_IRQHandler
        B .

        PUBWEAK  RNG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RNG_IRQHandler
        B .

        PUBWEAK  ECB_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ECB_IRQHandler
        B .

        PUBWEAK  CCM_AAR_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CCM_AAR_IRQHandler
        B .

        PUBWEAK  WDT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDT_IRQHandler
        B .

        PUBWEAK  RTC1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC1_IRQHandler
        B .

        PUBWEAK  QDEC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
QDEC_IRQHandler
        B .

        PUBWEAK  LPCOMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPCOMP_IRQHandler
        B .

        PUBWEAK  SWI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI0_IRQHandler
        B .

        PUBWEAK  SWI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI1_IRQHandler
        B .

        PUBWEAK  SWI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI2_IRQHandler
        B .

        PUBWEAK  SWI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI3_IRQHandler
        B .

        PUBWEAK  SWI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI4_IRQHandler
        B .

        PUBWEAK  SWI5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI5_IRQHandler
        B .

        END


