; -------------------------------------------------------------------------
;  @file:    startup_MCXA153.s
;  @purpose: CMSIS Cortex-M33 Core Device Startup File
;            MCXA153
;  @version: 1.0
;  @date:    2022-3-29
;  @build:   b240401
; -------------------------------------------------------------------------
;
; Copyright 1997-2016 Freescale Semiconductor, Inc.
; Copyright 2016-2024 NXP
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

        DCD     NMI_Handler                                   ;NMI Handler
        DCD     HardFault_Handler                             ;Hard Fault Handler
        DCD     MemManage_Handler                             ;MPU Fault Handler
        DCD     BusFault_Handler                              ;Bus Fault Handler
        DCD     UsageFault_Handler                            ;Usage Fault Handler
__vector_table_0x1c
        DCD     SecureFault_Handler                           ;Secure Fault Handler
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     SVC_Handler                                   ;SVCall Handler
        DCD     DebugMon_Handler                              ;Debug Monitor Handler
        DCD     0                                             ;Reserved
        DCD     PendSV_Handler                                ;PendSV Handler
        DCD     SysTick_Handler                               ;SysTick Handler

                                                              ;External Interrupts
        DCD     Reserved16_IRQHandler                         ;OR IRQ1 to IRQ53
        DCD     CMC_IRQHandler                                ;Core Mode Controller interrupt
        DCD     DMA_CH0_IRQHandler                            ;DMA3_0_CH0 error or transfer complete
        DCD     DMA_CH1_IRQHandler                            ;DMA3_0_CH1 error or transfer complete
        DCD     DMA_CH2_IRQHandler                            ;DMA3_0_CH2 error or transfer complete
        DCD     DMA_CH3_IRQHandler                            ;DMA3_0_CH3 error or transfer complete
        DCD     Reserved22_IRQHandler                         ;Reserved interrupt
        DCD     Reserved23_IRQHandler                         ;Reserved interrupt
        DCD     Reserved24_IRQHandler                         ;Reserved interrupt
        DCD     Reserved25_IRQHandler                         ;Reserved interrupt
        DCD     ERM0_SINGLE_BIT_IRQHandler                    ;ERM Single Bit error interrupt
        DCD     ERM0_MULTI_BIT_IRQHandler                     ;ERM Multi Bit error interrupt
        DCD     FMU0_IRQHandler                               ;Flash Management Unit interrupt
        DCD     GLIKEY0_IRQHandler                            ;GLIKEY Interrupt
        DCD     MBC0_IRQHandler                               ;MBC secure violation interrupt
        DCD     SCG0_IRQHandler                               ;System Clock Generator interrupt
        DCD     SPC0_IRQHandler                               ;System Power Controller interrupt
        DCD     Reserved33_IRQHandler                         ;Reserved interrupt
        DCD     WUU0_IRQHandler                               ;Wake Up Unit interrupt
        DCD     Reserved35_IRQHandler                         ;Reserved interrupt
        DCD     Reserved36_IRQHandler                         ;Reserved interrupt
        DCD     Reserved37_IRQHandler                         ;Reserved interrupt
        DCD     Reserved38_IRQHandler                         ;Reserved interrupt
        DCD     Reserved39_IRQHandler                         ;Reserved interrupt
        DCD     I3C0_IRQHandler                               ;Improved Inter Integrated Circuit interrupt 0
        DCD     Reserved41_IRQHandler                         ;Reserved interrupt
        DCD     LPI2C0_IRQHandler                             ;Low-Power Inter Integrated Circuit interrupt
        DCD     Reserved43_IRQHandler                         ;Reserved interrupt
        DCD     LPSPI0_IRQHandler                             ;Low-Power Serial Peripheral Interface interrupt
        DCD     LPSPI1_IRQHandler                             ;Low-Power Serial Peripheral Interface interrupt
        DCD     Reserved46_IRQHandler                         ;Reserved interrupt
        DCD     LPUART0_IRQHandler                            ;Low-Power Universal Asynchronous Receive/Transmit interrupt
        DCD     LPUART1_IRQHandler                            ;Low-Power Universal Asynchronous Receive/Transmit interrupt
        DCD     LPUART2_IRQHandler                            ;Low-Power Universal Asynchronous Receive/Transmit interrupt
        DCD     Reserved50_IRQHandler                         ;Reserved interrupt
        DCD     Reserved51_IRQHandler                         ;Reserved interrupt
        DCD     USB0_IRQHandler                               ;Universal Serial Bus - Full Speed interrupt
        DCD     Reserved53_IRQHandler                         ;Reserved interrupt
        DCD     CDOG0_IRQHandler                              ;Code Watchdog Timer 0 interrupt
        DCD     CTIMER0_IRQHandler                            ;Standard counter/timer 0 interrupt
        DCD     CTIMER1_IRQHandler                            ;Standard counter/timer 1 interrupt
        DCD     CTIMER2_IRQHandler                            ;Standard counter/timer 2 interrupt
        DCD     Reserved58_IRQHandler                         ;Reserved interrupt
        DCD     Reserved59_IRQHandler                         ;Reserved interrupt
        DCD     FLEXPWM0_RELOAD_ERROR_IRQHandler              ;FlexPWM0_reload_error interrupt
        DCD     FLEXPWM0_FAULT_IRQHandler                     ;FlexPWM0_fault interrupt
        DCD     FLEXPWM0_SUBMODULE0_IRQHandler                ;FlexPWM0 Submodule 0 capture/compare/reload interrupt
        DCD     FLEXPWM0_SUBMODULE1_IRQHandler                ;FlexPWM0 Submodule 1 capture/compare/reload interrupt
        DCD     FLEXPWM0_SUBMODULE2_IRQHandler                ;FlexPWM0 Submodule 2 capture/compare/reload interrupt
        DCD     Reserved65_IRQHandler                         ;Reserved interrupt
        DCD     QDC0_COMPARE_IRQHandler                       ;Compare
        DCD     QDC0_HOME_IRQHandler                          ;Home
        DCD     QDC0_WATCHDOG_IRQHandler                      ;Watchdog / Simultaneous A and B Change
        DCD     QDC0_INDEX_IRQHandler                         ;Index / Roll Over / Roll Under
        DCD     FREQME0_IRQHandler                            ;Frequency Measurement interrupt
        DCD     LPTMR0_IRQHandler                             ;Low Power Timer 0 interrupt
        DCD     Reserved72_IRQHandler                         ;Reserved interrupt
        DCD     OS_EVENT_IRQHandler                           ;OS event timer interrupt
        DCD     WAKETIMER0_IRQHandler                         ;Wake Timer Interrupt
        DCD     UTICK0_IRQHandler                             ;Micro-Tick Timer interrupt
        DCD     WWDT0_IRQHandler                              ;Windowed Watchdog Timer 0 interrupt
        DCD     Reserved77_IRQHandler                         ;Reserved interrupt
        DCD     ADC0_IRQHandler                               ;Analog-to-Digital Converter interrupt
        DCD     Reserved79_IRQHandler                         ;Reserved interrupt
        DCD     CMP0_IRQHandler                               ;Comparator interrupt
        DCD     CMP1_IRQHandler                               ;Comparator interrupt
        DCD     Reserved82_IRQHandler                         ;Reserved interrupt
        DCD     Reserved83_IRQHandler                         ;Reserved interrupt
        DCD     Reserved84_IRQHandler                         ;Reserved interrupt
        DCD     Reserved85_IRQHandler                         ;Reserved interrupt
        DCD     Reserved86_IRQHandler                         ;Reserved interrupt
        DCD     GPIO0_IRQHandler                              ;General Purpose Input/Output interrupt 0
        DCD     GPIO1_IRQHandler                              ;General Purpose Input/Output interrupt 1
        DCD     GPIO2_IRQHandler                              ;General Purpose Input/Output interrupt 2
        DCD     GPIO3_IRQHandler                              ;General Purpose Input/Output interrupt 3
        DCD     Reserved91_IRQHandler                         ;Reserved interrupt
        DCD     Reserved92_IRQHandler                         ;Reserved interrupt
        DCD     Reserved93_IRQHandler                         ;Reserved interrupt
        DCD     Reserved94_IRQHandler                         ;Reserved interrupt
        DCD     Reserved95_IRQHandler                         ;Reserved interrupt
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

        PUBWEAK Reserved16_IRQHandler
        PUBWEAK Reserved16_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved16_IRQHandler
        LDR     R0, =Reserved16_DriverIRQHandler
        BX      R0

        PUBWEAK CMC_IRQHandler
        PUBWEAK CMC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CMC_IRQHandler
        LDR     R0, =CMC_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_CH0_IRQHandler
        PUBWEAK DMA_CH0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_CH0_IRQHandler
        LDR     R0, =DMA_CH0_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_CH1_IRQHandler
        PUBWEAK DMA_CH1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_CH1_IRQHandler
        LDR     R0, =DMA_CH1_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_CH2_IRQHandler
        PUBWEAK DMA_CH2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_CH2_IRQHandler
        LDR     R0, =DMA_CH2_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_CH3_IRQHandler
        PUBWEAK DMA_CH3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_CH3_IRQHandler
        LDR     R0, =DMA_CH3_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved22_IRQHandler
        PUBWEAK Reserved22_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved22_IRQHandler
        LDR     R0, =Reserved22_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved23_IRQHandler
        PUBWEAK Reserved23_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved23_IRQHandler
        LDR     R0, =Reserved23_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved24_IRQHandler
        PUBWEAK Reserved24_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved24_IRQHandler
        LDR     R0, =Reserved24_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved25_IRQHandler
        PUBWEAK Reserved25_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved25_IRQHandler
        LDR     R0, =Reserved25_DriverIRQHandler
        BX      R0

        PUBWEAK ERM0_SINGLE_BIT_IRQHandler
        PUBWEAK ERM0_SINGLE_BIT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ERM0_SINGLE_BIT_IRQHandler
        LDR     R0, =ERM0_SINGLE_BIT_DriverIRQHandler
        BX      R0

        PUBWEAK ERM0_MULTI_BIT_IRQHandler
        PUBWEAK ERM0_MULTI_BIT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ERM0_MULTI_BIT_IRQHandler
        LDR     R0, =ERM0_MULTI_BIT_DriverIRQHandler
        BX      R0

        PUBWEAK FMU0_IRQHandler
        PUBWEAK FMU0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FMU0_IRQHandler
        LDR     R0, =FMU0_DriverIRQHandler
        BX      R0

        PUBWEAK GLIKEY0_IRQHandler
        PUBWEAK GLIKEY0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GLIKEY0_IRQHandler
        LDR     R0, =GLIKEY0_DriverIRQHandler
        BX      R0

        PUBWEAK MBC0_IRQHandler
        PUBWEAK MBC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MBC0_IRQHandler
        LDR     R0, =MBC0_DriverIRQHandler
        BX      R0

        PUBWEAK SCG0_IRQHandler
        PUBWEAK SCG0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SCG0_IRQHandler
        LDR     R0, =SCG0_DriverIRQHandler
        BX      R0

        PUBWEAK SPC0_IRQHandler
        PUBWEAK SPC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPC0_IRQHandler
        LDR     R0, =SPC0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved33_IRQHandler
        PUBWEAK Reserved33_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved33_IRQHandler
        LDR     R0, =Reserved33_DriverIRQHandler
        BX      R0

        PUBWEAK WUU0_IRQHandler
        PUBWEAK WUU0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WUU0_IRQHandler
        LDR     R0, =WUU0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved35_IRQHandler
        PUBWEAK Reserved35_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved35_IRQHandler
        LDR     R0, =Reserved35_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved36_IRQHandler
        PUBWEAK Reserved36_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved36_IRQHandler
        LDR     R0, =Reserved36_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved37_IRQHandler
        PUBWEAK Reserved37_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved37_IRQHandler
        LDR     R0, =Reserved37_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved38_IRQHandler
        PUBWEAK Reserved38_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved38_IRQHandler
        LDR     R0, =Reserved38_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved39_IRQHandler
        PUBWEAK Reserved39_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved39_IRQHandler
        LDR     R0, =Reserved39_DriverIRQHandler
        BX      R0

        PUBWEAK I3C0_IRQHandler
        PUBWEAK I3C0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I3C0_IRQHandler
        LDR     R0, =I3C0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved41_IRQHandler
        PUBWEAK Reserved41_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved41_IRQHandler
        LDR     R0, =Reserved41_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C0_IRQHandler
        PUBWEAK LPI2C0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C0_IRQHandler
        LDR     R0, =LPI2C0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved43_IRQHandler
        PUBWEAK Reserved43_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved43_IRQHandler
        LDR     R0, =Reserved43_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI0_IRQHandler
        PUBWEAK LPSPI0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI0_IRQHandler
        LDR     R0, =LPSPI0_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI1_IRQHandler
        PUBWEAK LPSPI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI1_IRQHandler
        LDR     R0, =LPSPI1_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved46_IRQHandler
        PUBWEAK Reserved46_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved46_IRQHandler
        LDR     R0, =Reserved46_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART0_IRQHandler
        PUBWEAK LPUART0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART0_IRQHandler
        LDR     R0, =LPUART0_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART1_IRQHandler
        PUBWEAK LPUART1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART1_IRQHandler
        LDR     R0, =LPUART1_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART2_IRQHandler
        PUBWEAK LPUART2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART2_IRQHandler
        LDR     R0, =LPUART2_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved50_IRQHandler
        PUBWEAK Reserved50_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved50_IRQHandler
        LDR     R0, =Reserved50_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved51_IRQHandler
        PUBWEAK Reserved51_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved51_IRQHandler
        LDR     R0, =Reserved51_DriverIRQHandler
        BX      R0

        PUBWEAK USB0_IRQHandler
        PUBWEAK USB0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB0_IRQHandler
        LDR     R0, =USB0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved53_IRQHandler
        PUBWEAK Reserved53_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved53_IRQHandler
        LDR     R0, =Reserved53_DriverIRQHandler
        BX      R0

        PUBWEAK CDOG0_IRQHandler
        PUBWEAK CDOG0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CDOG0_IRQHandler
        LDR     R0, =CDOG0_DriverIRQHandler
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

        PUBWEAK CTIMER2_IRQHandler
        PUBWEAK CTIMER2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER2_IRQHandler
        LDR     R0, =CTIMER2_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved58_IRQHandler
        PUBWEAK Reserved58_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved58_IRQHandler
        LDR     R0, =Reserved58_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved59_IRQHandler
        PUBWEAK Reserved59_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved59_IRQHandler
        LDR     R0, =Reserved59_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM0_RELOAD_ERROR_IRQHandler
        PUBWEAK FLEXPWM0_RELOAD_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_RELOAD_ERROR_IRQHandler
        LDR     R0, =FLEXPWM0_RELOAD_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM0_FAULT_IRQHandler
        PUBWEAK FLEXPWM0_FAULT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_FAULT_IRQHandler
        LDR     R0, =FLEXPWM0_FAULT_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM0_SUBMODULE0_IRQHandler
        PUBWEAK FLEXPWM0_SUBMODULE0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_SUBMODULE0_IRQHandler
        LDR     R0, =FLEXPWM0_SUBMODULE0_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM0_SUBMODULE1_IRQHandler
        PUBWEAK FLEXPWM0_SUBMODULE1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_SUBMODULE1_IRQHandler
        LDR     R0, =FLEXPWM0_SUBMODULE1_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM0_SUBMODULE2_IRQHandler
        PUBWEAK FLEXPWM0_SUBMODULE2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_SUBMODULE2_IRQHandler
        LDR     R0, =FLEXPWM0_SUBMODULE2_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved65_IRQHandler
        PUBWEAK Reserved65_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved65_IRQHandler
        LDR     R0, =Reserved65_DriverIRQHandler
        BX      R0

        PUBWEAK QDC0_COMPARE_IRQHandler
        PUBWEAK QDC0_COMPARE_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC0_COMPARE_IRQHandler
        LDR     R0, =QDC0_COMPARE_DriverIRQHandler
        BX      R0

        PUBWEAK QDC0_HOME_IRQHandler
        PUBWEAK QDC0_HOME_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC0_HOME_IRQHandler
        LDR     R0, =QDC0_HOME_DriverIRQHandler
        BX      R0

        PUBWEAK QDC0_WATCHDOG_IRQHandler
        PUBWEAK QDC0_WATCHDOG_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC0_WATCHDOG_IRQHandler
        LDR     R0, =QDC0_WATCHDOG_DriverIRQHandler
        BX      R0

        PUBWEAK QDC0_INDEX_IRQHandler
        PUBWEAK QDC0_INDEX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC0_INDEX_IRQHandler
        LDR     R0, =QDC0_INDEX_DriverIRQHandler
        BX      R0

        PUBWEAK FREQME0_IRQHandler
        PUBWEAK FREQME0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FREQME0_IRQHandler
        LDR     R0, =FREQME0_DriverIRQHandler
        BX      R0

        PUBWEAK LPTMR0_IRQHandler
        PUBWEAK LPTMR0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPTMR0_IRQHandler
        LDR     R0, =LPTMR0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved72_IRQHandler
        PUBWEAK Reserved72_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved72_IRQHandler
        LDR     R0, =Reserved72_DriverIRQHandler
        BX      R0

        PUBWEAK OS_EVENT_IRQHandler
        PUBWEAK OS_EVENT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
OS_EVENT_IRQHandler
        LDR     R0, =OS_EVENT_DriverIRQHandler
        BX      R0

        PUBWEAK WAKETIMER0_IRQHandler
        PUBWEAK WAKETIMER0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WAKETIMER0_IRQHandler
        LDR     R0, =WAKETIMER0_DriverIRQHandler
        BX      R0

        PUBWEAK UTICK0_IRQHandler
        PUBWEAK UTICK0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UTICK0_IRQHandler
        LDR     R0, =UTICK0_DriverIRQHandler
        BX      R0

        PUBWEAK WWDT0_IRQHandler
        PUBWEAK WWDT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WWDT0_IRQHandler
        LDR     R0, =WWDT0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved77_IRQHandler
        PUBWEAK Reserved77_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved77_IRQHandler
        LDR     R0, =Reserved77_DriverIRQHandler
        BX      R0

        PUBWEAK ADC0_IRQHandler
        PUBWEAK ADC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC0_IRQHandler
        LDR     R0, =ADC0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved79_IRQHandler
        PUBWEAK Reserved79_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved79_IRQHandler
        LDR     R0, =Reserved79_DriverIRQHandler
        BX      R0

        PUBWEAK CMP0_IRQHandler
        PUBWEAK CMP0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CMP0_IRQHandler
        LDR     R0, =CMP0_DriverIRQHandler
        BX      R0

        PUBWEAK CMP1_IRQHandler
        PUBWEAK CMP1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CMP1_IRQHandler
        LDR     R0, =CMP1_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved82_IRQHandler
        PUBWEAK Reserved82_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved82_IRQHandler
        LDR     R0, =Reserved82_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved83_IRQHandler
        PUBWEAK Reserved83_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved83_IRQHandler
        LDR     R0, =Reserved83_DriverIRQHandler
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

        PUBWEAK GPIO0_IRQHandler
        PUBWEAK GPIO0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO0_IRQHandler
        LDR     R0, =GPIO0_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO1_IRQHandler
        PUBWEAK GPIO1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO1_IRQHandler
        LDR     R0, =GPIO1_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO2_IRQHandler
        PUBWEAK GPIO2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO2_IRQHandler
        LDR     R0, =GPIO2_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO3_IRQHandler
        PUBWEAK GPIO3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO3_IRQHandler
        LDR     R0, =GPIO3_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved91_IRQHandler
        PUBWEAK Reserved91_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved91_IRQHandler
        LDR     R0, =Reserved91_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved92_IRQHandler
        PUBWEAK Reserved92_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved92_IRQHandler
        LDR     R0, =Reserved92_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved93_IRQHandler
        PUBWEAK Reserved93_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved93_IRQHandler
        LDR     R0, =Reserved93_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved94_IRQHandler
        PUBWEAK Reserved94_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved94_IRQHandler
        LDR     R0, =Reserved94_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved95_IRQHandler
        PUBWEAK Reserved95_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved95_IRQHandler
        LDR     R0, =Reserved95_DriverIRQHandler
        BX      R0

Reserved16_DriverIRQHandler
CMC_DriverIRQHandler
DMA_CH0_DriverIRQHandler
DMA_CH1_DriverIRQHandler
DMA_CH2_DriverIRQHandler
DMA_CH3_DriverIRQHandler
Reserved22_DriverIRQHandler
Reserved23_DriverIRQHandler
Reserved24_DriverIRQHandler
Reserved25_DriverIRQHandler
ERM0_SINGLE_BIT_DriverIRQHandler
ERM0_MULTI_BIT_DriverIRQHandler
FMU0_DriverIRQHandler
GLIKEY0_DriverIRQHandler
MBC0_DriverIRQHandler
SCG0_DriverIRQHandler
SPC0_DriverIRQHandler
Reserved33_DriverIRQHandler
WUU0_DriverIRQHandler
Reserved35_DriverIRQHandler
Reserved36_DriverIRQHandler
Reserved37_DriverIRQHandler
Reserved38_DriverIRQHandler
Reserved39_DriverIRQHandler
I3C0_DriverIRQHandler
Reserved41_DriverIRQHandler
LPI2C0_DriverIRQHandler
Reserved43_DriverIRQHandler
LPSPI0_DriverIRQHandler
LPSPI1_DriverIRQHandler
Reserved46_DriverIRQHandler
LPUART0_DriverIRQHandler
LPUART1_DriverIRQHandler
LPUART2_DriverIRQHandler
Reserved50_DriverIRQHandler
Reserved51_DriverIRQHandler
USB0_DriverIRQHandler
Reserved53_DriverIRQHandler
CDOG0_DriverIRQHandler
CTIMER0_DriverIRQHandler
CTIMER1_DriverIRQHandler
CTIMER2_DriverIRQHandler
Reserved58_DriverIRQHandler
Reserved59_DriverIRQHandler
FLEXPWM0_RELOAD_ERROR_DriverIRQHandler
FLEXPWM0_FAULT_DriverIRQHandler
FLEXPWM0_SUBMODULE0_DriverIRQHandler
FLEXPWM0_SUBMODULE1_DriverIRQHandler
FLEXPWM0_SUBMODULE2_DriverIRQHandler
Reserved65_DriverIRQHandler
QDC0_COMPARE_DriverIRQHandler
QDC0_HOME_DriverIRQHandler
QDC0_WATCHDOG_DriverIRQHandler
QDC0_INDEX_DriverIRQHandler
FREQME0_DriverIRQHandler
LPTMR0_DriverIRQHandler
Reserved72_DriverIRQHandler
OS_EVENT_DriverIRQHandler
WAKETIMER0_DriverIRQHandler
UTICK0_DriverIRQHandler
WWDT0_DriverIRQHandler
Reserved77_DriverIRQHandler
ADC0_DriverIRQHandler
Reserved79_DriverIRQHandler
CMP0_DriverIRQHandler
CMP1_DriverIRQHandler
Reserved82_DriverIRQHandler
Reserved83_DriverIRQHandler
Reserved84_DriverIRQHandler
Reserved85_DriverIRQHandler
Reserved86_DriverIRQHandler
GPIO0_DriverIRQHandler
GPIO1_DriverIRQHandler
GPIO2_DriverIRQHandler
GPIO3_DriverIRQHandler
Reserved91_DriverIRQHandler
Reserved92_DriverIRQHandler
Reserved93_DriverIRQHandler
Reserved94_DriverIRQHandler
Reserved95_DriverIRQHandler
DefaultISR
        B .

        END
