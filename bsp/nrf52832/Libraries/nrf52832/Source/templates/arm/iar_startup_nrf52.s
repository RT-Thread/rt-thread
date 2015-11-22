;; Copyright (c) 2015, Nordic Semiconductor ASA
;; All rights reserved.
;; 
;; Redistribution and use in source and binary forms, with or without
;; modification, are permitted provided that the following conditions are met:
;; 
;; * Redistributions of source code must retain the above copyright notice, this
;;   list of conditions and the following disclaimer.
;; 
;; * Redistributions in binary form must reproduce the above copyright notice,
;;   this list of conditions and the following disclaimer in the documentation
;;   and/or other materials provided with the distribution.
;; 
;; * Neither the name of Nordic Semiconductor ASA nor the names of its
;;   contributors may be used to endorse or promote products derived from
;;   this software without specific prior written permission.
;; 
;; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
;; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
;; FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
;; DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
;; SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
;; CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
;; OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;; OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



;; NOTE: Template files (including this one) are application specific and therefore 
;; expected to be copied into the application project folder prior to its use!

;; Description message

        MODULE  ?cstartup

        ;; Stack size default : Defined in *.icf (linker file). Can be modified inside EW.
        ;; Heap size default : Defined in *.icf (linker file). Can be modified inside EW.

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

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
        DCD     0
        DCD     0
        DCD     0
;__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     0
        DCD     0
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

        END


