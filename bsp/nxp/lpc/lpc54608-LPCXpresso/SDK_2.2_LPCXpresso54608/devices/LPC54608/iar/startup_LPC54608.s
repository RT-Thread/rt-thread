;/*****************************************************************************
; * @file:    startup_LPC54608.s
; * @purpose: CMSIS Cortex-M4 Core Device Startup File
; *           LPC54608
; * @version: 1.1
; * @date:    2016-11-25
; *----------------------------------------------------------------------------
; *
; * Copyright 1997 - 2016 Freescale Semiconductor.
; * Copyright 2016 - 2017 NXP
; *
; Redistribution and use in source and binary forms, with or without modification,
; are permitted provided that the following conditions are met:
;
; o Redistributions of source code must retain the above copyright notice, this list
;   of conditions and the following disclaimer.
;
; o Redistributions in binary form must reproduce the above copyright notice, this
;   list of conditions and the following disclaimer in the documentation and/or
;   other materials provided with the distribution.
;
; o Neither the name of the copyright holder nor the names of its
;   contributors may be used to endorse or promote products derived from this
;   software without specific prior written permission.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
; ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
; ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
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
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector_table_0x1c
        DCD     0
        DCD     0xFFFFFFFF ;ECRP
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     WDT_BOD_IRQHandler  ; Windowed watchdog timer, Brownout detect
        DCD     DMA0_IRQHandler  ; DMA controller
        DCD     GINT0_IRQHandler  ; GPIO group 0
        DCD     GINT1_IRQHandler  ; GPIO group 1
        DCD     PIN_INT0_IRQHandler  ; Pin interrupt 0 or pattern match engine slice 0
        DCD     PIN_INT1_IRQHandler  ; Pin interrupt 1or pattern match engine slice 1
        DCD     PIN_INT2_IRQHandler  ; Pin interrupt 2 or pattern match engine slice 2
        DCD     PIN_INT3_IRQHandler  ; Pin interrupt 3 or pattern match engine slice 3
        DCD     UTICK0_IRQHandler  ; Micro-tick Timer
        DCD     MRT0_IRQHandler  ; Multi-rate timer
        DCD     CTIMER0_IRQHandler  ; Standard counter/timer CTIMER0
        DCD     CTIMER1_IRQHandler  ; Standard counter/timer CTIMER1
        DCD     SCT0_IRQHandler  ; SCTimer/PWM
        DCD     CTIMER3_IRQHandler  ; Standard counter/timer CTIMER3
        DCD     FLEXCOMM0_IRQHandler  ; Flexcomm Interface 0 (USART, SPI, I2C, FLEXCOMM)
        DCD     FLEXCOMM1_IRQHandler  ; Flexcomm Interface 1 (USART, SPI, I2C, FLEXCOMM)
        DCD     FLEXCOMM2_IRQHandler  ; Flexcomm Interface 2 (USART, SPI, I2C, FLEXCOMM)
        DCD     FLEXCOMM3_IRQHandler  ; Flexcomm Interface 3 (USART, SPI, I2C, FLEXCOMM)
        DCD     FLEXCOMM4_IRQHandler  ; Flexcomm Interface 4 (USART, SPI, I2C, FLEXCOMM)
        DCD     FLEXCOMM5_IRQHandler  ; Flexcomm Interface 5 (USART, SPI, I2C,, FLEXCOMM)
        DCD     FLEXCOMM6_IRQHandler  ; Flexcomm Interface 6 (USART, SPI, I2C, I2S,, FLEXCOMM)
        DCD     FLEXCOMM7_IRQHandler  ; Flexcomm Interface 7 (USART, SPI, I2C, I2S,, FLEXCOMM)
        DCD     ADC0_SEQA_IRQHandler  ; ADC0 sequence A completion.
        DCD     ADC0_SEQB_IRQHandler  ; ADC0 sequence B completion.
        DCD     ADC0_THCMP_IRQHandler  ; ADC0 threshold compare and error.
        DCD     DMIC0_IRQHandler  ; Digital microphone and DMIC subsystem
        DCD     HWVAD0_IRQHandler  ; Hardware Voice Activity Detector
        DCD     USB0_NEEDCLK_IRQHandler  ; USB Activity Wake-up Interrupt
        DCD     USB0_IRQHandler  ; USB device
        DCD     RTC_IRQHandler  ; RTC alarm and wake-up interrupts
        DCD     Reserved46_IRQHandler  ; Reserved interrupt
        DCD     Reserved47_IRQHandler  ; Reserved interrupt
        DCD     PIN_INT4_IRQHandler  ; Pin interrupt 4 or pattern match engine slice 4 int
        DCD     PIN_INT5_IRQHandler  ; Pin interrupt 5 or pattern match engine slice 5 int
        DCD     PIN_INT6_IRQHandler  ; Pin interrupt 6 or pattern match engine slice 6 int
        DCD     PIN_INT7_IRQHandler  ; Pin interrupt 7 or pattern match engine slice 7 int
        DCD     CTIMER2_IRQHandler  ; Standard counter/timer CTIMER2
        DCD     CTIMER4_IRQHandler  ; Standard counter/timer CTIMER4
        DCD     RIT_IRQHandler  ; Repetitive Interrupt Timer
        DCD     SPIFI0_IRQHandler  ; SPI flash interface
        DCD     FLEXCOMM8_IRQHandler  ; Flexcomm Interface 8 (USART, SPI, I2C, FLEXCOMM)
        DCD     FLEXCOMM9_IRQHandler  ; Flexcomm Interface 9 (USART, SPI, I2C, FLEXCOMM)
        DCD     SDIO_IRQHandler  ; SD/MMC
        DCD     CAN0_IRQ0_IRQHandler  ; CAN0 interrupt0
        DCD     CAN0_IRQ1_IRQHandler  ; CAN0 interrupt1
        DCD     CAN1_IRQ0_IRQHandler  ; CAN1 interrupt0
        DCD     CAN1_IRQ1_IRQHandler  ; CAN1 interrupt1
        DCD     USB1_IRQHandler  ; USB1 interrupt
        DCD     USB1_NEEDCLK_IRQHandler  ; USB1 activity
        DCD     ETHERNET_IRQHandler  ; Ethernet
        DCD     ETHERNET_PMT_IRQHandler  ; Ethernet power management interrupt
        DCD     ETHERNET_MACLP_IRQHandler  ; Ethernet MAC interrupt
        DCD     EEPROM_IRQHandler  ; EEPROM interrupt
        DCD     LCD_IRQHandler  ; LCD interrupt
        DCD     SHA_IRQHandler  ; SHA interrupt
        DCD     SMARTCARD0_IRQHandler  ; Smart card 0 interrupt
        DCD     SMARTCARD1_IRQHandler  ; Smart card 1 interrupt
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU 	__Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                LDR     r0, =SystemInit
                BLX     r0
                LDR     r0, =__iar_program_start
                BX      r0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
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

        PUBWEAK WDT_BOD_IRQHandler
        PUBWEAK WDT_BOD_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WDT_BOD_IRQHandler
        LDR     R0, =WDT_BOD_DriverIRQHandler
        BX      R0
        PUBWEAK DMA0_IRQHandler
        PUBWEAK DMA0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA0_IRQHandler
        LDR     R0, =DMA0_DriverIRQHandler
        BX      R0
        PUBWEAK GINT0_IRQHandler
        PUBWEAK GINT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GINT0_IRQHandler
        LDR     R0, =GINT0_DriverIRQHandler
        BX      R0
        PUBWEAK GINT1_IRQHandler
        PUBWEAK GINT1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GINT1_IRQHandler
        LDR     R0, =GINT1_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT0_IRQHandler
        PUBWEAK PIN_INT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT0_IRQHandler
        LDR     R0, =PIN_INT0_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT1_IRQHandler
        PUBWEAK PIN_INT1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT1_IRQHandler
        LDR     R0, =PIN_INT1_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT2_IRQHandler
        PUBWEAK PIN_INT2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT2_IRQHandler
        LDR     R0, =PIN_INT2_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT3_IRQHandler
        PUBWEAK PIN_INT3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT3_IRQHandler
        LDR     R0, =PIN_INT3_DriverIRQHandler
        BX      R0
        PUBWEAK UTICK0_IRQHandler
        PUBWEAK UTICK0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UTICK0_IRQHandler
        LDR     R0, =UTICK0_DriverIRQHandler
        BX      R0
        PUBWEAK MRT0_IRQHandler
        PUBWEAK MRT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MRT0_IRQHandler
        LDR     R0, =MRT0_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER0_IRQHandler
        PUBWEAK CTIMER0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER0_IRQHandler
        LDR     R0, =CTIMER0_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER1_IRQHandler
        PUBWEAK CTIMER1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER1_IRQHandler
        LDR     R0, =CTIMER1_DriverIRQHandler
        BX      R0
        PUBWEAK SCT0_IRQHandler
        PUBWEAK SCT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SCT0_IRQHandler
        LDR     R0, =SCT0_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER3_IRQHandler
        PUBWEAK CTIMER3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER3_IRQHandler
        LDR     R0, =CTIMER3_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM0_IRQHandler
        PUBWEAK FLEXCOMM0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM0_IRQHandler
        LDR     R0, =FLEXCOMM0_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM1_IRQHandler
        PUBWEAK FLEXCOMM1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM1_IRQHandler
        LDR     R0, =FLEXCOMM1_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM2_IRQHandler
        PUBWEAK FLEXCOMM2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM2_IRQHandler
        LDR     R0, =FLEXCOMM2_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM3_IRQHandler
        PUBWEAK FLEXCOMM3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM3_IRQHandler
        LDR     R0, =FLEXCOMM3_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM4_IRQHandler
        PUBWEAK FLEXCOMM4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM4_IRQHandler
        LDR     R0, =FLEXCOMM4_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM5_IRQHandler
        PUBWEAK FLEXCOMM5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM5_IRQHandler
        LDR     R0, =FLEXCOMM5_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM6_IRQHandler
        PUBWEAK FLEXCOMM6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM6_IRQHandler
        LDR     R0, =FLEXCOMM6_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM7_IRQHandler
        PUBWEAK FLEXCOMM7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM7_IRQHandler
        LDR     R0, =FLEXCOMM7_DriverIRQHandler
        BX      R0
        PUBWEAK ADC0_SEQA_IRQHandler
        PUBWEAK ADC0_SEQA_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC0_SEQA_IRQHandler
        LDR     R0, =ADC0_SEQA_DriverIRQHandler
        BX      R0
        PUBWEAK ADC0_SEQB_IRQHandler
        PUBWEAK ADC0_SEQB_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC0_SEQB_IRQHandler
        LDR     R0, =ADC0_SEQB_DriverIRQHandler
        BX      R0
        PUBWEAK ADC0_THCMP_IRQHandler
        PUBWEAK ADC0_THCMP_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC0_THCMP_IRQHandler
        LDR     R0, =ADC0_THCMP_DriverIRQHandler
        BX      R0
        PUBWEAK DMIC0_IRQHandler
        PUBWEAK DMIC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMIC0_IRQHandler
        LDR     R0, =DMIC0_DriverIRQHandler
        BX      R0
        PUBWEAK HWVAD0_IRQHandler
        PUBWEAK HWVAD0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
HWVAD0_IRQHandler
        LDR     R0, =HWVAD0_DriverIRQHandler
        BX      R0
        PUBWEAK USB0_NEEDCLK_IRQHandler
        PUBWEAK USB0_NEEDCLK_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB0_NEEDCLK_IRQHandler
        LDR     R0, =USB0_NEEDCLK_DriverIRQHandler
        BX      R0
        PUBWEAK USB0_IRQHandler
        PUBWEAK USB0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB0_IRQHandler
        LDR     R0, =USB0_DriverIRQHandler
        BX      R0
        PUBWEAK RTC_IRQHandler
        PUBWEAK RTC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
RTC_IRQHandler
        LDR     R0, =RTC_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved46_IRQHandler
        PUBWEAK Reserved46_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved46_IRQHandler
        LDR     R0, =Reserved46_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved47_IRQHandler
        PUBWEAK Reserved47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved47_IRQHandler
        LDR     R0, =Reserved47_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT4_IRQHandler
        PUBWEAK PIN_INT4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT4_IRQHandler
        LDR     R0, =PIN_INT4_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT5_IRQHandler
        PUBWEAK PIN_INT5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT5_IRQHandler
        LDR     R0, =PIN_INT5_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT6_IRQHandler
        PUBWEAK PIN_INT6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT6_IRQHandler
        LDR     R0, =PIN_INT6_DriverIRQHandler
        BX      R0
        PUBWEAK PIN_INT7_IRQHandler
        PUBWEAK PIN_INT7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PIN_INT7_IRQHandler
        LDR     R0, =PIN_INT7_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER2_IRQHandler
        PUBWEAK CTIMER2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER2_IRQHandler
        LDR     R0, =CTIMER2_DriverIRQHandler
        BX      R0
        PUBWEAK CTIMER4_IRQHandler
        PUBWEAK CTIMER4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER4_IRQHandler
        LDR     R0, =CTIMER4_DriverIRQHandler
        BX      R0
        PUBWEAK RIT_IRQHandler
        PUBWEAK RIT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
RIT_IRQHandler
        LDR     R0, =RIT_DriverIRQHandler
        BX      R0
        PUBWEAK SPIFI0_IRQHandler
        PUBWEAK SPIFI0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPIFI0_IRQHandler
        LDR     R0, =SPIFI0_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM8_IRQHandler
        PUBWEAK FLEXCOMM8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM8_IRQHandler
        LDR     R0, =FLEXCOMM8_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM9_IRQHandler
        PUBWEAK FLEXCOMM9_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM9_IRQHandler
        LDR     R0, =FLEXCOMM9_DriverIRQHandler
        BX      R0
        PUBWEAK SDIO_IRQHandler
        PUBWEAK SDIO_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SDIO_IRQHandler
        LDR     R0, =SDIO_DriverIRQHandler
        BX      R0
        PUBWEAK CAN0_IRQ0_IRQHandler
        PUBWEAK CAN0_IRQ0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_IRQ0_IRQHandler
        LDR     R0, =CAN0_IRQ0_DriverIRQHandler
        BX      R0
        PUBWEAK CAN0_IRQ1_IRQHandler
        PUBWEAK CAN0_IRQ1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_IRQ1_IRQHandler
        LDR     R0, =CAN0_IRQ1_DriverIRQHandler
        BX      R0
        PUBWEAK CAN1_IRQ0_IRQHandler
        PUBWEAK CAN1_IRQ0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_IRQ0_IRQHandler
        LDR     R0, =CAN1_IRQ0_DriverIRQHandler
        BX      R0
        PUBWEAK CAN1_IRQ1_IRQHandler
        PUBWEAK CAN1_IRQ1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_IRQ1_IRQHandler
        LDR     R0, =CAN1_IRQ1_DriverIRQHandler
        BX      R0
        PUBWEAK USB1_IRQHandler
        PUBWEAK USB1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB1_IRQHandler
        LDR     R0, =USB1_DriverIRQHandler
        BX      R0
        PUBWEAK USB1_NEEDCLK_IRQHandler
        PUBWEAK USB1_NEEDCLK_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB1_NEEDCLK_IRQHandler
        LDR     R0, =USB1_NEEDCLK_DriverIRQHandler
        BX      R0
        PUBWEAK ETHERNET_IRQHandler
        PUBWEAK ETHERNET_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ETHERNET_IRQHandler
        LDR     R0, =ETHERNET_DriverIRQHandler
        BX      R0
        PUBWEAK ETHERNET_PMT_IRQHandler
        PUBWEAK ETHERNET_PMT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ETHERNET_PMT_IRQHandler
        LDR     R0, =ETHERNET_PMT_DriverIRQHandler
        BX      R0
        PUBWEAK ETHERNET_MACLP_IRQHandler
        PUBWEAK ETHERNET_MACLP_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ETHERNET_MACLP_IRQHandler
        LDR     R0, =ETHERNET_MACLP_DriverIRQHandler
        BX      R0
        PUBWEAK EEPROM_IRQHandler
        PUBWEAK EEPROM_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EEPROM_IRQHandler
        LDR     R0, =EEPROM_DriverIRQHandler
        BX      R0
        PUBWEAK LCD_IRQHandler
        PUBWEAK LCD_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LCD_IRQHandler
        LDR     R0, =LCD_DriverIRQHandler
        BX      R0
        PUBWEAK SHA_IRQHandler
        PUBWEAK SHA_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SHA_IRQHandler
        LDR     R0, =SHA_DriverIRQHandler
        BX      R0
        PUBWEAK SMARTCARD0_IRQHandler
        PUBWEAK SMARTCARD0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SMARTCARD0_IRQHandler
        LDR     R0, =SMARTCARD0_DriverIRQHandler
        BX      R0
        PUBWEAK SMARTCARD1_IRQHandler
        PUBWEAK SMARTCARD1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SMARTCARD1_IRQHandler
        LDR     R0, =SMARTCARD1_DriverIRQHandler
        BX      R0
WDT_BOD_DriverIRQHandler
DMA0_DriverIRQHandler
GINT0_DriverIRQHandler
GINT1_DriverIRQHandler
PIN_INT0_DriverIRQHandler
PIN_INT1_DriverIRQHandler
PIN_INT2_DriverIRQHandler
PIN_INT3_DriverIRQHandler
UTICK0_DriverIRQHandler
MRT0_DriverIRQHandler
CTIMER0_DriverIRQHandler
CTIMER1_DriverIRQHandler
SCT0_DriverIRQHandler
CTIMER3_DriverIRQHandler
FLEXCOMM0_DriverIRQHandler
FLEXCOMM1_DriverIRQHandler
FLEXCOMM2_DriverIRQHandler
FLEXCOMM3_DriverIRQHandler
FLEXCOMM4_DriverIRQHandler
FLEXCOMM5_DriverIRQHandler
FLEXCOMM6_DriverIRQHandler
FLEXCOMM7_DriverIRQHandler
ADC0_SEQA_DriverIRQHandler
ADC0_SEQB_DriverIRQHandler
ADC0_THCMP_DriverIRQHandler
DMIC0_DriverIRQHandler
HWVAD0_DriverIRQHandler
USB0_NEEDCLK_DriverIRQHandler
USB0_DriverIRQHandler
RTC_DriverIRQHandler
Reserved46_DriverIRQHandler
Reserved47_DriverIRQHandler
PIN_INT4_DriverIRQHandler
PIN_INT5_DriverIRQHandler
PIN_INT6_DriverIRQHandler
PIN_INT7_DriverIRQHandler
CTIMER2_DriverIRQHandler
CTIMER4_DriverIRQHandler
RIT_DriverIRQHandler
SPIFI0_DriverIRQHandler
FLEXCOMM8_DriverIRQHandler
FLEXCOMM9_DriverIRQHandler
SDIO_DriverIRQHandler
CAN0_IRQ0_DriverIRQHandler
CAN0_IRQ1_DriverIRQHandler
CAN1_IRQ0_DriverIRQHandler
CAN1_IRQ1_DriverIRQHandler
USB1_DriverIRQHandler
USB1_NEEDCLK_DriverIRQHandler
ETHERNET_DriverIRQHandler
ETHERNET_PMT_DriverIRQHandler
ETHERNET_MACLP_DriverIRQHandler
EEPROM_DriverIRQHandler
LCD_DriverIRQHandler
SHA_DriverIRQHandler
SMARTCARD0_DriverIRQHandler
SMARTCARD1_DriverIRQHandler
DefaultISR
        B .

        END
