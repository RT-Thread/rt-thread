;/*****************************************************************************
; * @file:    startup_LPC55S36.s
; * @purpose: CMSIS Cortex-M33 Core Device Startup File
; *           LPC55S36
; * @version: 1.1
; * @date:    2021-8-4
; *----------------------------------------------------------------------------
; *
; Copyright 1997-2016 Freescale Semiconductor, Inc.
; Copyright 2016-2021 NXP
; All rights reserved.
;
; SPDX-License-Identifier: BSD-3-Clause
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

__iar_init$$done:              ; The vector table is not needed
                      ; until after copy initialization is done

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector_table_0x1c
        DCD     SecureFault_Handler
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     WDT_BOD_IRQHandler  ; Windowed watchdog timer, Brownout detect, Flash interrupt
        DCD     DMA0_IRQHandler  ; DMA0 controller
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
        DCD     FLEXCOMM0_IRQHandler  ; Flexcomm Interface 0 (USART, SPI, I2C, I2S, FLEXCOMM)
        DCD     FLEXCOMM1_IRQHandler  ; Flexcomm Interface 1 (USART, SPI, I2C, I2S, FLEXCOMM)
        DCD     FLEXCOMM2_IRQHandler  ; Flexcomm Interface 2 (USART, SPI, I2C, I2S, FLEXCOMM)
        DCD     FLEXCOMM3_IRQHandler  ; Flexcomm Interface 3 (USART, SPI, I2C, I2S, FLEXCOMM)
        DCD     FLEXCOMM4_IRQHandler  ; Flexcomm Interface 4 (USART, SPI, I2C, I2S, FLEXCOMM)
        DCD     FLEXCOMM5_IRQHandler  ; Flexcomm Interface 5 (USART, SPI, I2C, I2S, FLEXCOMM)
        DCD     FLEXCOMM6_IRQHandler  ; Flexcomm Interface 6 (USART, SPI, I2C, I2S, FLEXCOMM)
        DCD     FLEXCOMM7_IRQHandler  ; Flexcomm Interface 7 (USART, SPI, I2C, I2S, FLEXCOMM)
        DCD     ADC0_IRQHandler  ; ADC0
        DCD     ADC1_IRQHandler  ; ADC1
        DCD     ACMP_IRQHandler  ; ACMP interrupts
        DCD     DMIC_IRQHandler  ; Digital microphone and DMIC subsystem
        DCD     HWVAD0_IRQHandler  ; Hardware Voice Activity Detector
        DCD     USB0_NEEDCLK_IRQHandler  ; USB Activity Wake-up Interrupt
        DCD     USB0_IRQHandler  ; USB device
        DCD     RTC_IRQHandler  ; RTC alarm and wake-up interrupts
        DCD     EZH_ARCH_B0_IRQHandler  ; EZH interrupt
        DCD     WAKEUP_IRQHandler  ; Wakeup interrupt
        DCD     PIN_INT4_IRQHandler  ; Pin interrupt 4 or pattern match engine slice 4 int
        DCD     PIN_INT5_IRQHandler  ; Pin interrupt 5 or pattern match engine slice 5 int
        DCD     PIN_INT6_IRQHandler  ; Pin interrupt 6 or pattern match engine slice 6 int
        DCD     PIN_INT7_IRQHandler  ; Pin interrupt 7 or pattern match engine slice 7 int
        DCD     CTIMER2_IRQHandler  ; Standard counter/timer CTIMER2
        DCD     CTIMER4_IRQHandler  ; Standard counter/timer CTIMER4
        DCD     OS_EVENT_IRQHandler  ; OS_EVENT_TIMER and OS_EVENT_WAKEUP interrupts
        DCD     FlexSPI0_IRQHandler  ; FlexSPI interrupt
        DCD     Reserved56_IRQHandler  ; Reserved interrupt
        DCD     Reserved57_IRQHandler  ; Reserved interrupt
        DCD     Reserved58_IRQHandler  ; Reserved interrupt
        DCD     CAN0_IRQ0_IRQHandler  ; CAN0 interrupt0
        DCD     CAN0_IRQ1_IRQHandler  ; CAN0 interrupt1
        DCD     SPI_FILTER_IRQHandler  ; SPI Filter interrupt
        DCD     Reserved62_IRQHandler  ; Reserved interrupt
        DCD     Reserved63_IRQHandler  ; Reserved interrupt
        DCD     Reserved64_IRQHandler  ; Reserved interrupt
        DCD     SEC_HYPERVISOR_CALL_IRQHandler  ; SEC_HYPERVISOR_CALL interrupt
        DCD     SEC_GPIO_INT0_IRQ0_IRQHandler  ; SEC_GPIO_INT00 interrupt
        DCD     SEC_GPIO_INT0_IRQ1_IRQHandler  ; SEC_GPIO_INT01 interrupt
        DCD     Freqme_IRQHandler  ; frequency measure interrupt
        DCD     SEC_VIO_IRQHandler  ; SEC_VIO interrupt
        DCD     SHA_IRQHandler  ; SHA interrupt
        DCD     PKC_IRQHandler  ; CASPER interrupt
        DCD     PUF_IRQHandler  ; PUF interrupt
        DCD     POWERQUAD_IRQHandler  ; PowerQuad interrupt
        DCD     DMA1_IRQHandler  ; DMA1 interrupt
        DCD     FLEXCOMM8_IRQHandler  ; LSPI_HS interrupt
        DCD     CDOG_IRQHandler  ; CodeWDG interrupt
        DCD     Reserved77_IRQHandler  ; Reserved interrupt
        DCD     I3C0_IRQHandler  ; I3C interrupt
        DCD     Reserved79_IRQHandler  ; Reserved interrupt
        DCD     Reserved80_IRQHandler  ; Reserved interrupt
        DCD     CSS_IRQ1_IRQHandler  ; CSS_IRQ1
        DCD     Tamper_IRQHandler  ; Tamper
        DCD     Analog_Glitch_IRQHandler  ; Analog_Glitch
        DCD     Reserved84_IRQHandler  ; Reserved interrupt
        DCD     Reserved85_IRQHandler  ; Reserved interrupt
        DCD     Reserved86_IRQHandler  ; Reserved interrupt
        DCD     Reserved87_IRQHandler  ; Reserved interrupt
        DCD     Reserved88_IRQHandler  ; Reserved interrupt
        DCD     Reserved89_IRQHandler  ; Reserved interrupt
        DCD     DAC0_IRQHandler  ; dac0 interrupt
        DCD     DAC1_IRQHandler  ; dac1 interrupt
        DCD     DAC2_IRQHandler  ; dac2 interrupt
        DCD     HSCMP0_IRQHandler  ; hscmp0 interrupt
        DCD     HSCMP1_IRQHandler  ; hscmp1 interrupt
        DCD     HSCMP2_IRQHandler  ; hscmp2 interrupt
        DCD     FLEXPWM0_CAPTURE_IRQHandler  ; flexpwm0_capture interrupt
        DCD     FLEXPWM0_FAULT_IRQHandler  ; flexpwm0_fault interrupt
        DCD     FLEXPWM0_RELOAD_ERROR_IRQHandler  ; flexpwm0_reload_error interrupt
        DCD     FLEXPWM0_COMPARE0_IRQHandler  ; flexpwm0_compare0 interrupt
        DCD     FLEXPWM0_RELOAD0_IRQHandler  ; flexpwm0_reload0 interrupt
        DCD     FLEXPWM0_COMPARE1_IRQHandler  ; flexpwm0_compare1 interrupt
        DCD     FLEXPWM0_RELOAD1_IRQHandler  ; flexpwm0_reload1 interrupt
        DCD     FLEXPWM0_COMPARE2_IRQHandler  ; flexpwm0_compare2 interrupt
        DCD     FLEXPWM0_RELOAD2_IRQHandler  ; flexpwm0_reload2 interrupt
        DCD     FLEXPWM0_COMPARE3_IRQHandler  ; flexpwm0_compare3 interrupt
        DCD     FLEXPWM0_RELOAD3_IRQHandler  ; flexpwm0_reload3 interrupt
        DCD     FLEXPWM1_CAPTURE_IRQHandler  ; flexpwm1_capture interrupt
        DCD     FLEXPWM1_FAULT_IRQHandler  ; flexpwm1_fault interrupt
        DCD     FLEXPWM1_RELOAD_ERROR_IRQHandler  ; flexpwm1_reload_error interrupt
        DCD     FLEXPWM1_COMPARE0_IRQHandler  ; flexpwm1_compare0 interrupt
        DCD     FLEXPWM1_RELOAD0_IRQHandler  ; flexpwm1_reload0 interrupt
        DCD     FLEXPWM1_COMPARE1_IRQHandler  ; flexpwm1_compare1 interrupt
        DCD     FLEXPWM1_RELOAD1_IRQHandler  ; flexpwm1_reload1 interrupt
        DCD     FLEXPWM1_COMPARE2_IRQHandler  ; flexpwm1_compare2 interrupt
        DCD     FLEXPWM1_RELOAD2_IRQHandler  ; flexpwm1_reload2 interrupt
        DCD     FLEXPWM1_COMPARE3_IRQHandler  ; flexpwm1_compare3 interrupt
        DCD     FLEXPWM1_RELOAD3_IRQHandler  ; flexpwm1_reload3 interrupt
        DCD     ENC0_COMPARE_IRQHandler  ; enc0_compare interrupt
        DCD     ENC0_HOME_IRQHandler  ; enc0_home interrupt
        DCD     ENC0_WDG_IRQHandler  ; enc0_wdg interrupt
        DCD     ENC0_IDX_IRQHandler  ; enc0_idx interrupt
        DCD     ENC1_COMPARE_IRQHandler  ; enc1_compare interrupt
        DCD     ENC1_HOME_IRQHandler  ; enc1_home interrupt
        DCD     ENC1_WDG_IRQHandler  ; enc1_wdg interrupt
        DCD     ENC1_IDX_IRQHandler  ; enc1_idx interrupt
        DCD     ITRC0_IRQHandler  ; itrc0 interrupt
        DCD     Reserved127_IRQHandler  ; Reserved interrupt
        DCD     CSSV2_ERR_IRQHandler  ; cssv2_err interrupt
        DCD     PKC_ERR_IRQHandler  ; pkc_err interrupt
        DCD     Reserved130_IRQHandler  ; Reserved interrupt
        DCD     Reserved131_IRQHandler  ; Reserved interrupt
        DCD     Reserved132_IRQHandler  ; Reserved interrupt
        DCD     Reserved133_IRQHandler  ; Reserved interrupt
        DCD     FLASH_IRQHandler  ; flash interrupt
        DCD     RAM_PARITY_ECC_ERR_IRQHandler  ; ram_parity_ecc_err interrupt
__Vectors_End


__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        CPSID   I               ; Mask interrupts
        LDR     R0, =0xE000ED08
        LDR     R1, =__vector_table
        STR     R1, [R0]
        LDR     R2, [R1]
        MSR     MSP, R2
        LDR     R0, =sfb(CSTACK)
        MSR     MSPLIM, R0
        CPSIE   I               ; Unmask interrupts
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

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

        PUBWEAK SecureFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SecureFault_Handler
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
        PUBWEAK ADC0_IRQHandler
        PUBWEAK ADC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC0_IRQHandler
        LDR     R0, =ADC0_DriverIRQHandler
        BX      R0
        PUBWEAK ADC1_IRQHandler
        PUBWEAK ADC1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC1_IRQHandler
        LDR     R0, =ADC1_DriverIRQHandler
        BX      R0
        PUBWEAK ACMP_IRQHandler
        PUBWEAK ACMP_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ACMP_IRQHandler
        LDR     R0, =ACMP_DriverIRQHandler
        BX      R0
        PUBWEAK DMIC_IRQHandler
        PUBWEAK DMIC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMIC_IRQHandler
        LDR     R0, =DMIC_DriverIRQHandler
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
        PUBWEAK EZH_ARCH_B0_IRQHandler
        PUBWEAK EZH_ARCH_B0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EZH_ARCH_B0_IRQHandler
        LDR     R0, =EZH_ARCH_B0_DriverIRQHandler
        BX      R0
        PUBWEAK WAKEUP_IRQHandler
        PUBWEAK WAKEUP_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WAKEUP_IRQHandler
        LDR     R0, =WAKEUP_DriverIRQHandler
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
        PUBWEAK OS_EVENT_IRQHandler
        PUBWEAK OS_EVENT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
OS_EVENT_IRQHandler
        LDR     R0, =OS_EVENT_DriverIRQHandler
        BX      R0
        PUBWEAK FlexSPI0_IRQHandler
        PUBWEAK FlexSPI0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FlexSPI0_IRQHandler
        LDR     R0, =FlexSPI0_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved56_IRQHandler
        PUBWEAK Reserved56_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved56_IRQHandler
        LDR     R0, =Reserved56_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved57_IRQHandler
        PUBWEAK Reserved57_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved57_IRQHandler
        LDR     R0, =Reserved57_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved58_IRQHandler
        PUBWEAK Reserved58_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved58_IRQHandler
        LDR     R0, =Reserved58_DriverIRQHandler
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
        PUBWEAK SPI_FILTER_IRQHandler
        PUBWEAK SPI_FILTER_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI_FILTER_IRQHandler
        LDR     R0, =SPI_FILTER_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved62_IRQHandler
        PUBWEAK Reserved62_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved62_IRQHandler
        LDR     R0, =Reserved62_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved63_IRQHandler
        PUBWEAK Reserved63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved63_IRQHandler
        LDR     R0, =Reserved63_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved64_IRQHandler
        PUBWEAK Reserved64_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved64_IRQHandler
        LDR     R0, =Reserved64_DriverIRQHandler
        BX      R0
        PUBWEAK SEC_HYPERVISOR_CALL_IRQHandler
        PUBWEAK SEC_HYPERVISOR_CALL_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SEC_HYPERVISOR_CALL_IRQHandler
        LDR     R0, =SEC_HYPERVISOR_CALL_DriverIRQHandler
        BX      R0
        PUBWEAK SEC_GPIO_INT0_IRQ0_IRQHandler
        PUBWEAK SEC_GPIO_INT0_IRQ0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SEC_GPIO_INT0_IRQ0_IRQHandler
        LDR     R0, =SEC_GPIO_INT0_IRQ0_DriverIRQHandler
        BX      R0
        PUBWEAK SEC_GPIO_INT0_IRQ1_IRQHandler
        PUBWEAK SEC_GPIO_INT0_IRQ1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SEC_GPIO_INT0_IRQ1_IRQHandler
        LDR     R0, =SEC_GPIO_INT0_IRQ1_DriverIRQHandler
        BX      R0
        PUBWEAK Freqme_IRQHandler
        PUBWEAK Freqme_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Freqme_IRQHandler
        LDR     R0, =Freqme_DriverIRQHandler
        BX      R0
        PUBWEAK SEC_VIO_IRQHandler
        PUBWEAK SEC_VIO_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SEC_VIO_IRQHandler
        LDR     R0, =SEC_VIO_DriverIRQHandler
        BX      R0
        PUBWEAK SHA_IRQHandler
        PUBWEAK SHA_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SHA_IRQHandler
        LDR     R0, =SHA_DriverIRQHandler
        BX      R0
        PUBWEAK PKC_IRQHandler
        PUBWEAK PKC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PKC_IRQHandler
        LDR     R0, =PKC_DriverIRQHandler
        BX      R0
        PUBWEAK PUF_IRQHandler
        PUBWEAK PUF_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PUF_IRQHandler
        LDR     R0, =PUF_DriverIRQHandler
        BX      R0
        PUBWEAK POWERQUAD_IRQHandler
        PUBWEAK POWERQUAD_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
POWERQUAD_IRQHandler
        LDR     R0, =POWERQUAD_DriverIRQHandler
        BX      R0
        PUBWEAK DMA1_IRQHandler
        PUBWEAK DMA1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA1_IRQHandler
        LDR     R0, =DMA1_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXCOMM8_IRQHandler
        PUBWEAK FLEXCOMM8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXCOMM8_IRQHandler
        LDR     R0, =FLEXCOMM8_DriverIRQHandler
        BX      R0
        PUBWEAK CDOG_IRQHandler
        PUBWEAK CDOG_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CDOG_IRQHandler
        LDR     R0, =CDOG_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved77_IRQHandler
        PUBWEAK Reserved77_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved77_IRQHandler
        LDR     R0, =Reserved77_DriverIRQHandler
        BX      R0
        PUBWEAK I3C0_IRQHandler
        PUBWEAK I3C0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I3C0_IRQHandler
        LDR     R0, =I3C0_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved79_IRQHandler
        PUBWEAK Reserved79_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved79_IRQHandler
        LDR     R0, =Reserved79_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved80_IRQHandler
        PUBWEAK Reserved80_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved80_IRQHandler
        LDR     R0, =Reserved80_DriverIRQHandler
        BX      R0
        PUBWEAK CSS_IRQ1_IRQHandler
        PUBWEAK CSS_IRQ1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CSS_IRQ1_IRQHandler
        LDR     R0, =CSS_IRQ1_DriverIRQHandler
        BX      R0
        PUBWEAK Tamper_IRQHandler
        PUBWEAK Tamper_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Tamper_IRQHandler
        LDR     R0, =Tamper_DriverIRQHandler
        BX      R0
        PUBWEAK Analog_Glitch_IRQHandler
        PUBWEAK Analog_Glitch_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Analog_Glitch_IRQHandler
        LDR     R0, =Analog_Glitch_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved84_IRQHandler
        PUBWEAK Reserved84_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved84_IRQHandler
        LDR     R0, =Reserved84_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved85_IRQHandler
        PUBWEAK Reserved85_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved85_IRQHandler
        LDR     R0, =Reserved85_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved86_IRQHandler
        PUBWEAK Reserved86_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved86_IRQHandler
        LDR     R0, =Reserved86_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved87_IRQHandler
        PUBWEAK Reserved87_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved87_IRQHandler
        LDR     R0, =Reserved87_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved88_IRQHandler
        PUBWEAK Reserved88_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved88_IRQHandler
        LDR     R0, =Reserved88_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved89_IRQHandler
        PUBWEAK Reserved89_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved89_IRQHandler
        LDR     R0, =Reserved89_DriverIRQHandler
        BX      R0
        PUBWEAK DAC0_IRQHandler
        PUBWEAK DAC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DAC0_IRQHandler
        LDR     R0, =DAC0_DriverIRQHandler
        BX      R0
        PUBWEAK DAC1_IRQHandler
        PUBWEAK DAC1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DAC1_IRQHandler
        LDR     R0, =DAC1_DriverIRQHandler
        BX      R0
        PUBWEAK DAC2_IRQHandler
        PUBWEAK DAC2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DAC2_IRQHandler
        LDR     R0, =DAC2_DriverIRQHandler
        BX      R0
        PUBWEAK HSCMP0_IRQHandler
        PUBWEAK HSCMP0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
HSCMP0_IRQHandler
        LDR     R0, =HSCMP0_DriverIRQHandler
        BX      R0
        PUBWEAK HSCMP1_IRQHandler
        PUBWEAK HSCMP1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
HSCMP1_IRQHandler
        LDR     R0, =HSCMP1_DriverIRQHandler
        BX      R0
        PUBWEAK HSCMP2_IRQHandler
        PUBWEAK HSCMP2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
HSCMP2_IRQHandler
        LDR     R0, =HSCMP2_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_CAPTURE_IRQHandler
        PUBWEAK FLEXPWM0_CAPTURE_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_CAPTURE_IRQHandler
        LDR     R0, =FLEXPWM0_CAPTURE_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_FAULT_IRQHandler
        PUBWEAK FLEXPWM0_FAULT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_FAULT_IRQHandler
        LDR     R0, =FLEXPWM0_FAULT_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_RELOAD_ERROR_IRQHandler
        PUBWEAK FLEXPWM0_RELOAD_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_RELOAD_ERROR_IRQHandler
        LDR     R0, =FLEXPWM0_RELOAD_ERROR_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_COMPARE0_IRQHandler
        PUBWEAK FLEXPWM0_COMPARE0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_COMPARE0_IRQHandler
        LDR     R0, =FLEXPWM0_COMPARE0_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_RELOAD0_IRQHandler
        PUBWEAK FLEXPWM0_RELOAD0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_RELOAD0_IRQHandler
        LDR     R0, =FLEXPWM0_RELOAD0_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_COMPARE1_IRQHandler
        PUBWEAK FLEXPWM0_COMPARE1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_COMPARE1_IRQHandler
        LDR     R0, =FLEXPWM0_COMPARE1_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_RELOAD1_IRQHandler
        PUBWEAK FLEXPWM0_RELOAD1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_RELOAD1_IRQHandler
        LDR     R0, =FLEXPWM0_RELOAD1_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_COMPARE2_IRQHandler
        PUBWEAK FLEXPWM0_COMPARE2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_COMPARE2_IRQHandler
        LDR     R0, =FLEXPWM0_COMPARE2_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_RELOAD2_IRQHandler
        PUBWEAK FLEXPWM0_RELOAD2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_RELOAD2_IRQHandler
        LDR     R0, =FLEXPWM0_RELOAD2_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_COMPARE3_IRQHandler
        PUBWEAK FLEXPWM0_COMPARE3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_COMPARE3_IRQHandler
        LDR     R0, =FLEXPWM0_COMPARE3_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM0_RELOAD3_IRQHandler
        PUBWEAK FLEXPWM0_RELOAD3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_RELOAD3_IRQHandler
        LDR     R0, =FLEXPWM0_RELOAD3_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_CAPTURE_IRQHandler
        PUBWEAK FLEXPWM1_CAPTURE_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_CAPTURE_IRQHandler
        LDR     R0, =FLEXPWM1_CAPTURE_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_FAULT_IRQHandler
        PUBWEAK FLEXPWM1_FAULT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_FAULT_IRQHandler
        LDR     R0, =FLEXPWM1_FAULT_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_RELOAD_ERROR_IRQHandler
        PUBWEAK FLEXPWM1_RELOAD_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_RELOAD_ERROR_IRQHandler
        LDR     R0, =FLEXPWM1_RELOAD_ERROR_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_COMPARE0_IRQHandler
        PUBWEAK FLEXPWM1_COMPARE0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_COMPARE0_IRQHandler
        LDR     R0, =FLEXPWM1_COMPARE0_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_RELOAD0_IRQHandler
        PUBWEAK FLEXPWM1_RELOAD0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_RELOAD0_IRQHandler
        LDR     R0, =FLEXPWM1_RELOAD0_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_COMPARE1_IRQHandler
        PUBWEAK FLEXPWM1_COMPARE1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_COMPARE1_IRQHandler
        LDR     R0, =FLEXPWM1_COMPARE1_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_RELOAD1_IRQHandler
        PUBWEAK FLEXPWM1_RELOAD1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_RELOAD1_IRQHandler
        LDR     R0, =FLEXPWM1_RELOAD1_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_COMPARE2_IRQHandler
        PUBWEAK FLEXPWM1_COMPARE2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_COMPARE2_IRQHandler
        LDR     R0, =FLEXPWM1_COMPARE2_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_RELOAD2_IRQHandler
        PUBWEAK FLEXPWM1_RELOAD2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_RELOAD2_IRQHandler
        LDR     R0, =FLEXPWM1_RELOAD2_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_COMPARE3_IRQHandler
        PUBWEAK FLEXPWM1_COMPARE3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_COMPARE3_IRQHandler
        LDR     R0, =FLEXPWM1_COMPARE3_DriverIRQHandler
        BX      R0
        PUBWEAK FLEXPWM1_RELOAD3_IRQHandler
        PUBWEAK FLEXPWM1_RELOAD3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_RELOAD3_IRQHandler
        LDR     R0, =FLEXPWM1_RELOAD3_DriverIRQHandler
        BX      R0
        PUBWEAK ENC0_COMPARE_IRQHandler
        PUBWEAK ENC0_COMPARE_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENC0_COMPARE_IRQHandler
        LDR     R0, =ENC0_COMPARE_DriverIRQHandler
        BX      R0
        PUBWEAK ENC0_HOME_IRQHandler
        PUBWEAK ENC0_HOME_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENC0_HOME_IRQHandler
        LDR     R0, =ENC0_HOME_DriverIRQHandler
        BX      R0
        PUBWEAK ENC0_WDG_IRQHandler
        PUBWEAK ENC0_WDG_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENC0_WDG_IRQHandler
        LDR     R0, =ENC0_WDG_DriverIRQHandler
        BX      R0
        PUBWEAK ENC0_IDX_IRQHandler
        PUBWEAK ENC0_IDX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENC0_IDX_IRQHandler
        LDR     R0, =ENC0_IDX_DriverIRQHandler
        BX      R0
        PUBWEAK ENC1_COMPARE_IRQHandler
        PUBWEAK ENC1_COMPARE_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENC1_COMPARE_IRQHandler
        LDR     R0, =ENC1_COMPARE_DriverIRQHandler
        BX      R0
        PUBWEAK ENC1_HOME_IRQHandler
        PUBWEAK ENC1_HOME_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENC1_HOME_IRQHandler
        LDR     R0, =ENC1_HOME_DriverIRQHandler
        BX      R0
        PUBWEAK ENC1_WDG_IRQHandler
        PUBWEAK ENC1_WDG_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENC1_WDG_IRQHandler
        LDR     R0, =ENC1_WDG_DriverIRQHandler
        BX      R0
        PUBWEAK ENC1_IDX_IRQHandler
        PUBWEAK ENC1_IDX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENC1_IDX_IRQHandler
        LDR     R0, =ENC1_IDX_DriverIRQHandler
        BX      R0
        PUBWEAK ITRC0_IRQHandler
        PUBWEAK ITRC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ITRC0_IRQHandler
        LDR     R0, =ITRC0_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved127_IRQHandler
        PUBWEAK Reserved127_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved127_IRQHandler
        LDR     R0, =Reserved127_DriverIRQHandler
        BX      R0
        PUBWEAK CSSV2_ERR_IRQHandler
        PUBWEAK CSSV2_ERR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CSSV2_ERR_IRQHandler
        LDR     R0, =CSSV2_ERR_DriverIRQHandler
        BX      R0
        PUBWEAK PKC_ERR_IRQHandler
        PUBWEAK PKC_ERR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PKC_ERR_IRQHandler
        LDR     R0, =PKC_ERR_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved130_IRQHandler
        PUBWEAK Reserved130_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved130_IRQHandler
        LDR     R0, =Reserved130_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved131_IRQHandler
        PUBWEAK Reserved131_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved131_IRQHandler
        LDR     R0, =Reserved131_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved132_IRQHandler
        PUBWEAK Reserved132_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved132_IRQHandler
        LDR     R0, =Reserved132_DriverIRQHandler
        BX      R0
        PUBWEAK Reserved133_IRQHandler
        PUBWEAK Reserved133_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved133_IRQHandler
        LDR     R0, =Reserved133_DriverIRQHandler
        BX      R0
        PUBWEAK FLASH_IRQHandler
        PUBWEAK FLASH_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLASH_IRQHandler
        LDR     R0, =FLASH_DriverIRQHandler
        BX      R0
        PUBWEAK RAM_PARITY_ECC_ERR_IRQHandler
        PUBWEAK RAM_PARITY_ECC_ERR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
RAM_PARITY_ECC_ERR_IRQHandler
        LDR     R0, =RAM_PARITY_ECC_ERR_DriverIRQHandler
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
ADC0_DriverIRQHandler
ADC1_DriverIRQHandler
ACMP_DriverIRQHandler
DMIC_DriverIRQHandler
HWVAD0_DriverIRQHandler
USB0_NEEDCLK_DriverIRQHandler
USB0_DriverIRQHandler
RTC_DriverIRQHandler
EZH_ARCH_B0_DriverIRQHandler
WAKEUP_DriverIRQHandler
PIN_INT4_DriverIRQHandler
PIN_INT5_DriverIRQHandler
PIN_INT6_DriverIRQHandler
PIN_INT7_DriverIRQHandler
CTIMER2_DriverIRQHandler
CTIMER4_DriverIRQHandler
OS_EVENT_DriverIRQHandler
FlexSPI0_DriverIRQHandler
Reserved56_DriverIRQHandler
Reserved57_DriverIRQHandler
Reserved58_DriverIRQHandler
CAN0_IRQ0_DriverIRQHandler
CAN0_IRQ1_DriverIRQHandler
SPI_FILTER_DriverIRQHandler
Reserved62_DriverIRQHandler
Reserved63_DriverIRQHandler
Reserved64_DriverIRQHandler
SEC_HYPERVISOR_CALL_DriverIRQHandler
SEC_GPIO_INT0_IRQ0_DriverIRQHandler
SEC_GPIO_INT0_IRQ1_DriverIRQHandler
Freqme_DriverIRQHandler
SEC_VIO_DriverIRQHandler
SHA_DriverIRQHandler
PKC_DriverIRQHandler
PUF_DriverIRQHandler
POWERQUAD_DriverIRQHandler
DMA1_DriverIRQHandler
FLEXCOMM8_DriverIRQHandler
CDOG_DriverIRQHandler
Reserved77_DriverIRQHandler
I3C0_DriverIRQHandler
Reserved79_DriverIRQHandler
Reserved80_DriverIRQHandler
CSS_IRQ1_DriverIRQHandler
Tamper_DriverIRQHandler
Analog_Glitch_DriverIRQHandler
Reserved84_DriverIRQHandler
Reserved85_DriverIRQHandler
Reserved86_DriverIRQHandler
Reserved87_DriverIRQHandler
Reserved88_DriverIRQHandler
Reserved89_DriverIRQHandler
DAC0_DriverIRQHandler
DAC1_DriverIRQHandler
DAC2_DriverIRQHandler
HSCMP0_DriverIRQHandler
HSCMP1_DriverIRQHandler
HSCMP2_DriverIRQHandler
FLEXPWM0_CAPTURE_DriverIRQHandler
FLEXPWM0_FAULT_DriverIRQHandler
FLEXPWM0_RELOAD_ERROR_DriverIRQHandler
FLEXPWM0_COMPARE0_DriverIRQHandler
FLEXPWM0_RELOAD0_DriverIRQHandler
FLEXPWM0_COMPARE1_DriverIRQHandler
FLEXPWM0_RELOAD1_DriverIRQHandler
FLEXPWM0_COMPARE2_DriverIRQHandler
FLEXPWM0_RELOAD2_DriverIRQHandler
FLEXPWM0_COMPARE3_DriverIRQHandler
FLEXPWM0_RELOAD3_DriverIRQHandler
FLEXPWM1_CAPTURE_DriverIRQHandler
FLEXPWM1_FAULT_DriverIRQHandler
FLEXPWM1_RELOAD_ERROR_DriverIRQHandler
FLEXPWM1_COMPARE0_DriverIRQHandler
FLEXPWM1_RELOAD0_DriverIRQHandler
FLEXPWM1_COMPARE1_DriverIRQHandler
FLEXPWM1_RELOAD1_DriverIRQHandler
FLEXPWM1_COMPARE2_DriverIRQHandler
FLEXPWM1_RELOAD2_DriverIRQHandler
FLEXPWM1_COMPARE3_DriverIRQHandler
FLEXPWM1_RELOAD3_DriverIRQHandler
ENC0_COMPARE_DriverIRQHandler
ENC0_HOME_DriverIRQHandler
ENC0_WDG_DriverIRQHandler
ENC0_IDX_DriverIRQHandler
ENC1_COMPARE_DriverIRQHandler
ENC1_HOME_DriverIRQHandler
ENC1_WDG_DriverIRQHandler
ENC1_IDX_DriverIRQHandler
ITRC0_DriverIRQHandler
Reserved127_DriverIRQHandler
CSSV2_ERR_DriverIRQHandler
PKC_ERR_DriverIRQHandler
Reserved130_DriverIRQHandler
Reserved131_DriverIRQHandler
Reserved132_DriverIRQHandler
Reserved133_DriverIRQHandler
FLASH_DriverIRQHandler
RAM_PARITY_ECC_ERR_DriverIRQHandler
DefaultISR
        B .

        END
