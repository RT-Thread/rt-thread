;/*****************************************************************************
; * @file:    startup_LPC54114_cm0plus.s
; * @purpose: CMSIS Cortex-M0 Core Device Startup File
; *           LPC54114_cm0plus
; * @version: 1.0
; * @date:    2016-4-29
; *----------------------------------------------------------------------------
; *
; * The Clear BSD License
; * Copyright 1997 - 2016 Freescale Semiconductor.
; * Copyright 2016 - 2017 NXP
; *
; * All rights reserved.
; * 
; Redistribution and use in source and binary forms, with or without modification,
; are permitted (subject to the limitations in the disclaimer below) provided
;  that the following conditions are met:
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
; NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S' PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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
        DCD     0
        DCD     0
        DCD     0
__vector_table_0x1c
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
        DCD     FLEXCOMM0_IRQHandler  ; Flexcomm Interface 0 (USART, SPI, I2C)
        DCD     FLEXCOMM1_IRQHandler  ; Flexcomm Interface 1 (USART, SPI, I2C)
        DCD     FLEXCOMM2_IRQHandler  ; Flexcomm Interface 2 (USART, SPI, I2C)
        DCD     FLEXCOMM3_IRQHandler  ; Flexcomm Interface 3 (USART, SPI, I2C)
        DCD     FLEXCOMM4_IRQHandler  ; Flexcomm Interface 4 (USART, SPI, I2C)
        DCD     FLEXCOMM5_IRQHandler  ; Flexcomm Interface 5 (USART, SPI, I2C)
        DCD     FLEXCOMM6_IRQHandler  ; Flexcomm Interface 6 (USART, SPI, I2C, I2S)
        DCD     FLEXCOMM7_IRQHandler  ; Flexcomm Interface 7 (USART, SPI, I2C, I2S)
        DCD     ADC0_SEQA_IRQHandler  ; ADC0 sequence A completion.
        DCD     ADC0_SEQB_IRQHandler  ; ADC0 sequence B completion.
        DCD     ADC0_THCMP_IRQHandler  ; ADC0 threshold compare and error.
        DCD     DMIC0_IRQHandler  ; Digital microphone and DMIC subsystem
        DCD     HWVAD0_IRQHandler  ; Hardware Voice Activity Detector
        DCD     USB0_NEEDCLK_IRQHandler  ; USB Activity Wake-up Interrupt
        DCD     USB0_IRQHandler  ; USB device
        DCD     RTC_IRQHandler  ; RTC alarm and wake-up interrupts
        DCD     IOH_IRQHandler  ; IOH
        DCD     MAILBOX_IRQHandler  ; Mailbox interrupt (present on selected devices)
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU 	__Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

#if !defined(SLAVEBOOT)
        DATA
cpu_id          EQU     0xE000ED00 ; CPUID Base Register (System control block register)
cpu_ctrl        EQU     0x40000800
coproc_boot     EQU     0x40000804
coproc_stack    EQU     0x40000808
rel_vals
                DC32    cpu_id, cpu_ctrl, coproc_boot, coproc_stack
                DC16    0xFFF, 0xC24
#endif

        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
; Reset Handler - shared for both cores
Reset_Handler

#if !defined(SLAVEBOOT)
; Both the M0+ and M4 core come via this shared startup code,
                ; but the M0+ and M4 core have different vector tables.
                ; Determine if the core executing this code is the master or
                ; the slave and handle each core state individually.
shared_boot_entry
                LDR     r6, =rel_vals
                MOVS    r4, #0            ; Flag for slave core (0)
                MOVS    r5, #1

                ; Determine which core (M0+ or M4) this code is running on
                ; r2 = (((*cpu_id) >> 4) & 0xFFF); (M4 core == 0xC24)
get_current_core_id
                LDR     r0, [r6, #0]
                LDR     r1, [r0]                        ; r1 = CPU ID status
                LSRS    r1, r1, #4                      ; Right justify 12 CPU ID bits
                LDRH    r2, [r6, #16]                   ; Mask for CPU ID bits
                ANDS    r2, r1, r2                      ; r2 = ARM COrtex CPU ID
                LDRH    r3, [r6, #18]                   ; Mask for CPU ID bits
                CMP     r3, r2                          ; Core ID matches M4 identifier
                BNE     get_master_status
                MOV     r4, r5                          ; Set flag for master core (1)

                ; Determine if M4 core is the master or slave
                ; r3 = ((*cpu_ctrl) & 1); (0 == m0+, 1 == M4)
get_master_status
                LDR     r0, [r6, #4]
                LDR     r3, [r0]                        ; r3 = SYSCON co-processor CPU control status
                ANDS    r3, r3, r5                      ; r3 = (Bit 0: 1 = M4 is master, 0 = M4 is slave)

                ; Select boot based on selected master core and core ID
select_boot
                EORS    r3, r3, r4                      ; r4 = (Bit 0: 0 = master, 1 = slave)
                BNE     slave_boot
                B       normal_boot

                ; Slave boot
slave_boot
                LDR     r0, [r6, #8]
                LDR     r2, [r0]                        ; r1 = SYSCON co-processor boot address
                CMP     r2, #0                          ; Slave boot address = 0 (not set up)?
                BEQ     cpu_sleep
                LDR     r0, [r6, #12]
                LDR     r1, [r0]                        ; r5 = SYSCON co-processor stack address
                MOV     sp, r1                          ; Update slave CPU stack pointer
                ; Be sure to update VTOR for the slave MCU to point to the
                ; slave vector table in boot memory
                BX      r2                              ; Jump to slave boot address

                ; Slave isn't yet setup for system boot from the master
                ; so sleep until the master sets it up and then reboots it
cpu_sleep
                MOV     sp, r5                          ; Will force exception if something happens
cpu_sleep_wfi
                WFI                                     ; Sleep forever until master reboots
                B       cpu_sleep_wfi
#endif ; defined(SLAVEBOOT)

                ; Normal boot for master/slave
normal_boot
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
        PUBWEAK IOH_IRQHandler
        PUBWEAK IOH_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
IOH_IRQHandler
        LDR     R0, =IOH_DriverIRQHandler
        BX      R0
        PUBWEAK MAILBOX_IRQHandler
        PUBWEAK MAILBOX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MAILBOX_IRQHandler
        LDR     R0, =MAILBOX_DriverIRQHandler
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
IOH_DriverIRQHandler
MAILBOX_DriverIRQHandler
DefaultISR
        B .

        END
