;/*****************************************************************************
; * @file:    startup_LPC54608.s
; * @purpose: CMSIS Cortex-M4 Core Device Startup File for the
; *           LPC54608
; * @version: 1.1
; * @date:    2016-11-25
; *
; * Copyright 1997 - 2016 Freescale Semiconductor, Inc.
; * Copyright 2016 - 2017 NXP
; *
; * Redistribution and use in source and binary forms, with or without modification,
; * are permitted provided that the following conditions are met:
; *
; * o Redistributions of source code must retain the above copyright notice, this list
; *   of conditions and the following disclaimer.
; *
; * o Redistributions in binary form must reproduce the above copyright notice, this
; *   list of conditions and the following disclaimer in the documentation and/or
; *   other materials provided with the distribution.
; *
; * o Neither the name of the copyright holder nor the names of its
; *   contributors may be used to endorse or promote products derived from this
; *   software without specific prior written permission.
; *
; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; *
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                IMPORT  |Image$$ARM_LIB_STACK$$ZI$$Limit|

__Vectors       DCD     |Image$$ARM_LIB_STACK$$ZI$$Limit| ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler

                DCD     NMI_Handler
                DCD     HardFault_Handler
                DCD     MemManage_Handler
                DCD     BusFault_Handler
                DCD     UsageFault_Handler
__vector_table_0x1c
                DCD     0                         ; Checksum of the first 7 words
                DCD     0xFFFFFFFF                ; ECRP
                DCD     0                         ; Enhanced image marker, set to 0x0 for legacy boot
                DCD     0                         ; Pointer to enhanced boot block, set to 0x0 for legacy boot
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

                AREA    |.text|, CODE, READONLY

; Reset Handler
Reset_Handler   PROC
                EXPORT  Reset_Handler               [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                LDR     r0, =SystemInit
                BLX     r0
                LDR     r0, =__main
                BX      r0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP

HardFault_Handler \
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP

MemManage_Handler     PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP

BusFault_Handler PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP

UsageFault_Handler PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP

SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP

DebugMon_Handler PROC
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

WDT_BOD_IRQHandler\
                PROC
                EXPORT     WDT_BOD_IRQHandler        [WEAK]
                LDR        R0, =WDT_BOD_DriverIRQHandler
                BX         R0
                ENDP

DMA0_IRQHandler\
                PROC
                EXPORT     DMA0_IRQHandler        [WEAK]
                LDR        R0, =DMA0_DriverIRQHandler
                BX         R0
                ENDP

GINT0_IRQHandler\
                PROC
                EXPORT     GINT0_IRQHandler        [WEAK]
                LDR        R0, =GINT0_DriverIRQHandler
                BX         R0
                ENDP

GINT1_IRQHandler\
                PROC
                EXPORT     GINT1_IRQHandler        [WEAK]
                LDR        R0, =GINT1_DriverIRQHandler
                BX         R0
                ENDP

PIN_INT0_IRQHandler\
                PROC
                EXPORT     PIN_INT0_IRQHandler        [WEAK]
                LDR        R0, =PIN_INT0_DriverIRQHandler
                BX         R0
                ENDP

PIN_INT1_IRQHandler\
                PROC
                EXPORT     PIN_INT1_IRQHandler        [WEAK]
                LDR        R0, =PIN_INT1_DriverIRQHandler
                BX         R0
                ENDP

PIN_INT2_IRQHandler\
                PROC
                EXPORT     PIN_INT2_IRQHandler        [WEAK]
                LDR        R0, =PIN_INT2_DriverIRQHandler
                BX         R0
                ENDP

PIN_INT3_IRQHandler\
                PROC
                EXPORT     PIN_INT3_IRQHandler        [WEAK]
                LDR        R0, =PIN_INT3_DriverIRQHandler
                BX         R0
                ENDP

UTICK0_IRQHandler\
                PROC
                EXPORT     UTICK0_IRQHandler        [WEAK]
                LDR        R0, =UTICK0_DriverIRQHandler
                BX         R0
                ENDP

MRT0_IRQHandler\
                PROC
                EXPORT     MRT0_IRQHandler        [WEAK]
                LDR        R0, =MRT0_DriverIRQHandler
                BX         R0
                ENDP

CTIMER0_IRQHandler\
                PROC
                EXPORT     CTIMER0_IRQHandler        [WEAK]
                LDR        R0, =CTIMER0_DriverIRQHandler
                BX         R0
                ENDP

CTIMER1_IRQHandler\
                PROC
                EXPORT     CTIMER1_IRQHandler        [WEAK]
                LDR        R0, =CTIMER1_DriverIRQHandler
                BX         R0
                ENDP

SCT0_IRQHandler\
                PROC
                EXPORT     SCT0_IRQHandler        [WEAK]
                LDR        R0, =SCT0_DriverIRQHandler
                BX         R0
                ENDP

CTIMER3_IRQHandler\
                PROC
                EXPORT     CTIMER3_IRQHandler        [WEAK]
                LDR        R0, =CTIMER3_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM0_IRQHandler\
                PROC
                EXPORT     FLEXCOMM0_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM0_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM1_IRQHandler\
                PROC
                EXPORT     FLEXCOMM1_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM1_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM2_IRQHandler\
                PROC
                EXPORT     FLEXCOMM2_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM2_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM3_IRQHandler\
                PROC
                EXPORT     FLEXCOMM3_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM3_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM4_IRQHandler\
                PROC
                EXPORT     FLEXCOMM4_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM4_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM5_IRQHandler\
                PROC
                EXPORT     FLEXCOMM5_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM5_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM6_IRQHandler\
                PROC
                EXPORT     FLEXCOMM6_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM6_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM7_IRQHandler\
                PROC
                EXPORT     FLEXCOMM7_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM7_DriverIRQHandler
                BX         R0
                ENDP

ADC0_SEQA_IRQHandler\
                PROC
                EXPORT     ADC0_SEQA_IRQHandler        [WEAK]
                LDR        R0, =ADC0_SEQA_DriverIRQHandler
                BX         R0
                ENDP

ADC0_SEQB_IRQHandler\
                PROC
                EXPORT     ADC0_SEQB_IRQHandler        [WEAK]
                LDR        R0, =ADC0_SEQB_DriverIRQHandler
                BX         R0
                ENDP

ADC0_THCMP_IRQHandler\
                PROC
                EXPORT     ADC0_THCMP_IRQHandler        [WEAK]
                LDR        R0, =ADC0_THCMP_DriverIRQHandler
                BX         R0
                ENDP

DMIC0_IRQHandler\
                PROC
                EXPORT     DMIC0_IRQHandler        [WEAK]
                LDR        R0, =DMIC0_DriverIRQHandler
                BX         R0
                ENDP

HWVAD0_IRQHandler\
                PROC
                EXPORT     HWVAD0_IRQHandler        [WEAK]
                LDR        R0, =HWVAD0_DriverIRQHandler
                BX         R0
                ENDP

USB0_NEEDCLK_IRQHandler\
                PROC
                EXPORT     USB0_NEEDCLK_IRQHandler        [WEAK]
                LDR        R0, =USB0_NEEDCLK_DriverIRQHandler
                BX         R0
                ENDP

USB0_IRQHandler\
                PROC
                EXPORT     USB0_IRQHandler        [WEAK]
                LDR        R0, =USB0_DriverIRQHandler
                BX         R0
                ENDP

RTC_IRQHandler\
                PROC
                EXPORT     RTC_IRQHandler        [WEAK]
                LDR        R0, =RTC_DriverIRQHandler
                BX         R0
                ENDP

Reserved46_IRQHandler\
                PROC
                EXPORT     Reserved46_IRQHandler        [WEAK]
                LDR        R0, =Reserved46_DriverIRQHandler
                BX         R0
                ENDP

Reserved47_IRQHandler\
                PROC
                EXPORT     Reserved47_IRQHandler        [WEAK]
                LDR        R0, =Reserved47_DriverIRQHandler
                BX         R0
                ENDP

PIN_INT4_IRQHandler\
                PROC
                EXPORT     PIN_INT4_IRQHandler        [WEAK]
                LDR        R0, =PIN_INT4_DriverIRQHandler
                BX         R0
                ENDP

PIN_INT5_IRQHandler\
                PROC
                EXPORT     PIN_INT5_IRQHandler        [WEAK]
                LDR        R0, =PIN_INT5_DriverIRQHandler
                BX         R0
                ENDP

PIN_INT6_IRQHandler\
                PROC
                EXPORT     PIN_INT6_IRQHandler        [WEAK]
                LDR        R0, =PIN_INT6_DriverIRQHandler
                BX         R0
                ENDP

PIN_INT7_IRQHandler\
                PROC
                EXPORT     PIN_INT7_IRQHandler        [WEAK]
                LDR        R0, =PIN_INT7_DriverIRQHandler
                BX         R0
                ENDP

CTIMER2_IRQHandler\
                PROC
                EXPORT     CTIMER2_IRQHandler        [WEAK]
                LDR        R0, =CTIMER2_DriverIRQHandler
                BX         R0
                ENDP

CTIMER4_IRQHandler\
                PROC
                EXPORT     CTIMER4_IRQHandler        [WEAK]
                LDR        R0, =CTIMER4_DriverIRQHandler
                BX         R0
                ENDP

RIT_IRQHandler\
                PROC
                EXPORT     RIT_IRQHandler        [WEAK]
                LDR        R0, =RIT_DriverIRQHandler
                BX         R0
                ENDP

SPIFI0_IRQHandler\
                PROC
                EXPORT     SPIFI0_IRQHandler        [WEAK]
                LDR        R0, =SPIFI0_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM8_IRQHandler\
                PROC
                EXPORT     FLEXCOMM8_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM8_DriverIRQHandler
                BX         R0
                ENDP

FLEXCOMM9_IRQHandler\
                PROC
                EXPORT     FLEXCOMM9_IRQHandler        [WEAK]
                LDR        R0, =FLEXCOMM9_DriverIRQHandler
                BX         R0
                ENDP

SDIO_IRQHandler\
                PROC
                EXPORT     SDIO_IRQHandler        [WEAK]
                LDR        R0, =SDIO_DriverIRQHandler
                BX         R0
                ENDP

CAN0_IRQ0_IRQHandler\
                PROC
                EXPORT     CAN0_IRQ0_IRQHandler        [WEAK]
                LDR        R0, =CAN0_IRQ0_DriverIRQHandler
                BX         R0
                ENDP

CAN0_IRQ1_IRQHandler\
                PROC
                EXPORT     CAN0_IRQ1_IRQHandler        [WEAK]
                LDR        R0, =CAN0_IRQ1_DriverIRQHandler
                BX         R0
                ENDP

CAN1_IRQ0_IRQHandler\
                PROC
                EXPORT     CAN1_IRQ0_IRQHandler        [WEAK]
                LDR        R0, =CAN1_IRQ0_DriverIRQHandler
                BX         R0
                ENDP

CAN1_IRQ1_IRQHandler\
                PROC
                EXPORT     CAN1_IRQ1_IRQHandler        [WEAK]
                LDR        R0, =CAN1_IRQ1_DriverIRQHandler
                BX         R0
                ENDP

USB1_IRQHandler\
                PROC
                EXPORT     USB1_IRQHandler        [WEAK]
                LDR        R0, =USB1_DriverIRQHandler
                BX         R0
                ENDP

USB1_NEEDCLK_IRQHandler\
                PROC
                EXPORT     USB1_NEEDCLK_IRQHandler        [WEAK]
                LDR        R0, =USB1_NEEDCLK_DriverIRQHandler
                BX         R0
                ENDP

ETHERNET_IRQHandler\
                PROC
                EXPORT     ETHERNET_IRQHandler        [WEAK]
                LDR        R0, =ETHERNET_DriverIRQHandler
                BX         R0
                ENDP

ETHERNET_PMT_IRQHandler\
                PROC
                EXPORT     ETHERNET_PMT_IRQHandler        [WEAK]
                LDR        R0, =ETHERNET_PMT_DriverIRQHandler
                BX         R0
                ENDP

ETHERNET_MACLP_IRQHandler\
                PROC
                EXPORT     ETHERNET_MACLP_IRQHandler        [WEAK]
                LDR        R0, =ETHERNET_MACLP_DriverIRQHandler
                BX         R0
                ENDP

EEPROM_IRQHandler\
                PROC
                EXPORT     EEPROM_IRQHandler        [WEAK]
                LDR        R0, =EEPROM_DriverIRQHandler
                BX         R0
                ENDP

LCD_IRQHandler\
                PROC
                EXPORT     LCD_IRQHandler        [WEAK]
                LDR        R0, =LCD_DriverIRQHandler
                BX         R0
                ENDP

SHA_IRQHandler\
                PROC
                EXPORT     SHA_IRQHandler        [WEAK]
                LDR        R0, =SHA_DriverIRQHandler
                BX         R0
                ENDP

SMARTCARD0_IRQHandler\
                PROC
                EXPORT     SMARTCARD0_IRQHandler        [WEAK]
                LDR        R0, =SMARTCARD0_DriverIRQHandler
                BX         R0
                ENDP

SMARTCARD1_IRQHandler\
                PROC
                EXPORT     SMARTCARD1_IRQHandler        [WEAK]
                LDR        R0, =SMARTCARD1_DriverIRQHandler
                BX         R0
                ENDP

Default_Handler PROC
                EXPORT     WDT_BOD_DriverIRQHandler        [WEAK]
                EXPORT     DMA0_DriverIRQHandler        [WEAK]
                EXPORT     GINT0_DriverIRQHandler        [WEAK]
                EXPORT     GINT1_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT0_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT1_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT2_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT3_DriverIRQHandler        [WEAK]
                EXPORT     UTICK0_DriverIRQHandler        [WEAK]
                EXPORT     MRT0_DriverIRQHandler        [WEAK]
                EXPORT     CTIMER0_DriverIRQHandler        [WEAK]
                EXPORT     CTIMER1_DriverIRQHandler        [WEAK]
                EXPORT     SCT0_DriverIRQHandler        [WEAK]
                EXPORT     CTIMER3_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM0_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM1_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM2_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM3_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM4_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM5_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM6_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM7_DriverIRQHandler        [WEAK]
                EXPORT     ADC0_SEQA_DriverIRQHandler        [WEAK]
                EXPORT     ADC0_SEQB_DriverIRQHandler        [WEAK]
                EXPORT     ADC0_THCMP_DriverIRQHandler        [WEAK]
                EXPORT     DMIC0_DriverIRQHandler        [WEAK]
                EXPORT     HWVAD0_DriverIRQHandler        [WEAK]
                EXPORT     USB0_NEEDCLK_DriverIRQHandler        [WEAK]
                EXPORT     USB0_DriverIRQHandler        [WEAK]
                EXPORT     RTC_DriverIRQHandler        [WEAK]
                EXPORT     Reserved46_DriverIRQHandler        [WEAK]
                EXPORT     Reserved47_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT4_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT5_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT6_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT7_DriverIRQHandler        [WEAK]
                EXPORT     CTIMER2_DriverIRQHandler        [WEAK]
                EXPORT     CTIMER4_DriverIRQHandler        [WEAK]
                EXPORT     RIT_DriverIRQHandler        [WEAK]
                EXPORT     SPIFI0_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM8_DriverIRQHandler        [WEAK]
                EXPORT     FLEXCOMM9_DriverIRQHandler        [WEAK]
                EXPORT     SDIO_DriverIRQHandler        [WEAK]
                EXPORT     CAN0_IRQ0_DriverIRQHandler        [WEAK]
                EXPORT     CAN0_IRQ1_DriverIRQHandler        [WEAK]
                EXPORT     CAN1_IRQ0_DriverIRQHandler        [WEAK]
                EXPORT     CAN1_IRQ1_DriverIRQHandler        [WEAK]
                EXPORT     USB1_DriverIRQHandler        [WEAK]
                EXPORT     USB1_NEEDCLK_DriverIRQHandler        [WEAK]
                EXPORT     ETHERNET_DriverIRQHandler        [WEAK]
                EXPORT     ETHERNET_PMT_DriverIRQHandler        [WEAK]
                EXPORT     ETHERNET_MACLP_DriverIRQHandler        [WEAK]
                EXPORT     EEPROM_DriverIRQHandler        [WEAK]
                EXPORT     LCD_DriverIRQHandler        [WEAK]
                EXPORT     SHA_DriverIRQHandler        [WEAK]
                EXPORT     SMARTCARD0_DriverIRQHandler        [WEAK]
                EXPORT     SMARTCARD1_DriverIRQHandler        [WEAK]

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

                B       .

                ENDP


                ALIGN


                END

