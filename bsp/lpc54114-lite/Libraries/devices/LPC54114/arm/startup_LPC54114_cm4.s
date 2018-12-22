;/*****************************************************************************
; * @file:    startup_LPC54114_cm4.s
; * @purpose: CMSIS Cortex-M4 Core Device Startup File for the
; *           LPC54114_cm4
; * @version: 1.0
; * @date:    2016-4-29
; *
; * The Clear BSD License
; * Copyright 1997 - 2016 Freescale Semiconductor, Inc.
; * Copyright 2016 - 2017 NXP
; *
; * All rights reserved.
; * 
; * Redistribution and use in source and binary forms, with or without modification,
; * are permitted (subject to the limitations in the disclaimer below) provided
; *  that the following conditions are met:
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
; * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S' PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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
                DCD     0
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
                DCD     PIN_INT4_IRQHandler  ; Pin interrupt 4 or pattern match engine slice 4 int
                DCD     PIN_INT5_IRQHandler  ; Pin interrupt 5 or pattern match engine slice 5 int
                DCD     PIN_INT6_IRQHandler  ; Pin interrupt 6 or pattern match engine slice 6 int
                DCD     PIN_INT7_IRQHandler  ; Pin interrupt 7 or pattern match engine slice 7 int
                DCD     CTIMER2_IRQHandler  ; Standard counter/timer CTIMER2
                DCD     CTIMER4_IRQHandler  ; Standard counter/timer CTIMER4
                DCD     Reserved54_IRQHandler  ; Reserved interrupt
                DCD     SPIFI0_IRQHandler  ; SPI flash interface

;     <h> Code Read Protection level (CRP)
;       <o>    CRP_Level:
;                       <0xFFFFFFFF=> Disabled
;                       <0x4E697370=> NO_ISP
;                       <0x12345678=> CRP1
;                       <0x87654321=> CRP2
;                       <0x43218765=> CRP3 (Are you sure?)
;     </h>
CRP_Level       EQU     0xFFFFFFFF

                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF

                AREA    |.text|, CODE, READONLY

cpu_id          EQU     0xE000ED00
cpu_ctrl        EQU     0x40000800
coproc_boot     EQU     0x40000804
coproc_stack    EQU     0x40000808

rel_vals
                DCD     cpu_id, cpu_ctrl, coproc_boot, coproc_stack
                DCW     0xFFF, 0xC24

; Reset Handler - shared for both cores
Reset_Handler   PROC
                EXPORT  Reset_Handler               [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                IF      :LNOT::DEF:SLAVEBOOT
                ; Both the M0+ and M4 core come via this shared startup code,
                ; but the M0+ and M4 core have different vector tables.
                ; Determine if the core executing this code is the master or
                ; the slave and handle each core state individually.
shared_boot_entry
                LDR     r6, =rel_vals
                MOVS    r4, #0                          ; Flag for slave core (0)
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
                ENDIF

                ; Normal boot for master/slave
normal_boot
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

IOH_IRQHandler\
                PROC
                EXPORT     IOH_IRQHandler        [WEAK]
                LDR        R0, =IOH_DriverIRQHandler
                BX         R0
                ENDP

MAILBOX_IRQHandler\
                PROC
                EXPORT     MAILBOX_IRQHandler        [WEAK]
                LDR        R0, =MAILBOX_DriverIRQHandler
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

Reserved54_IRQHandler\
                PROC
                EXPORT     Reserved54_IRQHandler        [WEAK]
                LDR        R0, =Reserved54_DriverIRQHandler
                BX         R0
                ENDP

SPIFI0_IRQHandler\
                PROC
                EXPORT     SPIFI0_IRQHandler        [WEAK]
                LDR        R0, =SPIFI0_DriverIRQHandler
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
                EXPORT     IOH_DriverIRQHandler        [WEAK]
                EXPORT     MAILBOX_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT4_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT5_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT6_DriverIRQHandler        [WEAK]
                EXPORT     PIN_INT7_DriverIRQHandler        [WEAK]
                EXPORT     CTIMER2_DriverIRQHandler        [WEAK]
                EXPORT     CTIMER4_DriverIRQHandler        [WEAK]
                EXPORT     Reserved54_DriverIRQHandler        [WEAK]
                EXPORT     SPIFI0_DriverIRQHandler        [WEAK]

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
PIN_INT4_DriverIRQHandler
PIN_INT5_DriverIRQHandler
PIN_INT6_DriverIRQHandler
PIN_INT7_DriverIRQHandler
CTIMER2_DriverIRQHandler
CTIMER4_DriverIRQHandler
Reserved54_DriverIRQHandler
SPIFI0_DriverIRQHandler

                B       .

                ENDP


                ALIGN


                END

