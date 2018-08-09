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
        DCD     MemoryManagement_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0                         ; Reserved
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     POWER_CLOCK_IRQHandler
        DCD     RADIO_IRQHandler
        DCD     UARTE0_UART0_IRQHandler
        DCD     SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler
        DCD     SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler
        DCD     NFCT_IRQHandler
        DCD     GPIOTE_IRQHandler
        DCD     SAADC_IRQHandler
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
        DCD     COMP_LPCOMP_IRQHandler
        DCD     SWI0_EGU0_IRQHandler
        DCD     SWI1_EGU1_IRQHandler
        DCD     SWI2_EGU2_IRQHandler
        DCD     SWI3_EGU3_IRQHandler
        DCD     SWI4_EGU4_IRQHandler
        DCD     SWI5_EGU5_IRQHandler
        DCD     TIMER3_IRQHandler
        DCD     TIMER4_IRQHandler
        DCD     PWM0_IRQHandler
        DCD     PDM_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     MWU_IRQHandler
        DCD     PWM1_IRQHandler
        DCD     PWM2_IRQHandler
        DCD     SPIM2_SPIS2_SPI2_IRQHandler
        DCD     RTC2_IRQHandler
        DCD     I2S_IRQHandler
        DCD     FPU_IRQHandler
        DCD     USBD_IRQHandler
        DCD     UARTE1_IRQHandler
        DCD     QSPI_IRQHandler
        DCD     CRYPTOCELL_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     PWM3_IRQHandler
        DCD     0                         ; Reserved
        DCD     SPIM3_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved

__Vectors_End
__Vectors                           EQU   __vector_table
__Vectors_Size                      EQU   __Vectors_End - __Vectors


; Default handlers.
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler

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

        PUBWEAK MemoryManagement_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemoryManagement_Handler
        B .

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B .

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
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

        PUBWEAK  UARTE0_UART0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UARTE0_UART0_IRQHandler
        B .

        PUBWEAK  SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler
        B .

        PUBWEAK  SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler
        B .

        PUBWEAK  NFCT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
NFCT_IRQHandler
        B .

        PUBWEAK  GPIOTE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOTE_IRQHandler
        B .

        PUBWEAK  SAADC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SAADC_IRQHandler
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

        PUBWEAK  COMP_LPCOMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
COMP_LPCOMP_IRQHandler
        B .

        PUBWEAK  SWI0_EGU0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI0_EGU0_IRQHandler
        B .

        PUBWEAK  SWI1_EGU1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI1_EGU1_IRQHandler
        B .

        PUBWEAK  SWI2_EGU2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI2_EGU2_IRQHandler
        B .

        PUBWEAK  SWI3_EGU3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI3_EGU3_IRQHandler
        B .

        PUBWEAK  SWI4_EGU4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI4_EGU4_IRQHandler
        B .

        PUBWEAK  SWI5_EGU5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SWI5_EGU5_IRQHandler
        B .

        PUBWEAK  TIMER3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER3_IRQHandler
        B .

        PUBWEAK  TIMER4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER4_IRQHandler
        B .

        PUBWEAK  PWM0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM0_IRQHandler
        B .

        PUBWEAK  PDM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PDM_IRQHandler
        B .

        PUBWEAK  MWU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MWU_IRQHandler
        B .

        PUBWEAK  PWM1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM1_IRQHandler
        B .

        PUBWEAK  PWM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM2_IRQHandler
        B .

        PUBWEAK  SPIM2_SPIS2_SPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPIM2_SPIS2_SPI2_IRQHandler
        B .

        PUBWEAK  RTC2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC2_IRQHandler
        B .

        PUBWEAK  I2S_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2S_IRQHandler
        B .

        PUBWEAK  FPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPU_IRQHandler
        B .

        PUBWEAK  USBD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USBD_IRQHandler
        B .

        PUBWEAK  UARTE1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UARTE1_IRQHandler
        B .

        PUBWEAK  QSPI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
QSPI_IRQHandler
        B .

        PUBWEAK  CRYPTOCELL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CRYPTOCELL_IRQHandler
        B .

        PUBWEAK  PWM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM3_IRQHandler
        B .

        PUBWEAK  SPIM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPIM3_IRQHandler
        B .


        END


