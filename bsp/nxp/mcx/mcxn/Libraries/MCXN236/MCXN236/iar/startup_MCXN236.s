; -------------------------------------------------------------------------
;  @file:    startup_MCXN236.s
;  @purpose: CMSIS Cortex-M33 Core Device Startup File
;            MCXN236
;  @version: 1.0
;  @date:    2023-10-1
;  @build:   b240409
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
        DCD     OR_IRQHandler                                 ;OR IRQ
        DCD     EDMA_0_CH0_IRQHandler                         ;eDMA_0_CH0 error or transfer complete
        DCD     EDMA_0_CH1_IRQHandler                         ;eDMA_0_CH1 error or transfer complete
        DCD     EDMA_0_CH2_IRQHandler                         ;eDMA_0_CH2 error or transfer complete
        DCD     EDMA_0_CH3_IRQHandler                         ;eDMA_0_CH3 error or transfer complete
        DCD     EDMA_0_CH4_IRQHandler                         ;eDMA_0_CH4 error or transfer complete
        DCD     EDMA_0_CH5_IRQHandler                         ;eDMA_0_CH5 error or transfer complete
        DCD     EDMA_0_CH6_IRQHandler                         ;eDMA_0_CH6 error or transfer complete
        DCD     EDMA_0_CH7_IRQHandler                         ;eDMA_0_CH7 error or transfer complete
        DCD     EDMA_0_CH8_IRQHandler                         ;eDMA_0_CH8 error or transfer complete
        DCD     EDMA_0_CH9_IRQHandler                         ;eDMA_0_CH9 error or transfer complete
        DCD     EDMA_0_CH10_IRQHandler                        ;eDMA_0_CH10 error or transfer complete
        DCD     EDMA_0_CH11_IRQHandler                        ;eDMA_0_CH11 error or transfer complete
        DCD     EDMA_0_CH12_IRQHandler                        ;eDMA_0_CH12 error or transfer complete
        DCD     EDMA_0_CH13_IRQHandler                        ;eDMA_0_CH13 error or transfer complete
        DCD     EDMA_0_CH14_IRQHandler                        ;eDMA_0_CH14 error or transfer complete
        DCD     EDMA_0_CH15_IRQHandler                        ;eDMA_0_CH15 error or transfer complete
        DCD     GPIO00_IRQHandler                             ;GPIO0 interrupt 0
        DCD     GPIO01_IRQHandler                             ;GPIO0 interrupt 1
        DCD     GPIO10_IRQHandler                             ;GPIO1 interrupt 0
        DCD     GPIO11_IRQHandler                             ;GPIO1 interrupt 1
        DCD     GPIO20_IRQHandler                             ;GPIO2 interrupt 0
        DCD     GPIO21_IRQHandler                             ;GPIO2 interrupt 1
        DCD     GPIO30_IRQHandler                             ;GPIO3 interrupt 0
        DCD     GPIO31_IRQHandler                             ;GPIO3 interrupt 1
        DCD     GPIO40_IRQHandler                             ;GPIO4 interrupt 0
        DCD     GPIO41_IRQHandler                             ;GPIO4 interrupt 1
        DCD     GPIO50_IRQHandler                             ;GPIO5 interrupt 0
        DCD     GPIO51_IRQHandler                             ;GPIO5 interrupt 1
        DCD     UTICK0_IRQHandler                             ;Micro-Tick Timer interrupt
        DCD     MRT0_IRQHandler                               ;Multi-Rate Timer interrupt
        DCD     CTIMER0_IRQHandler                            ;Standard counter/timer 0 interrupt
        DCD     CTIMER1_IRQHandler                            ;Standard counter/timer 1 interrupt
        DCD     Reserved49_IRQHandler                         ;Reserved interrupt
        DCD     CTIMER2_IRQHandler                            ;Standard counter/timer 2 interrupt
        DCD     LP_FLEXCOMM0_IRQHandler                       ;LP_FLEXCOMM0 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt)
        DCD     LP_FLEXCOMM1_IRQHandler                       ;LP_FLEXCOMM1 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt)
        DCD     LP_FLEXCOMM2_IRQHandler                       ;LP_FLEXCOMM2 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt)
        DCD     LP_FLEXCOMM3_IRQHandler                       ;LP_FLEXCOMM3 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt)
        DCD     LP_FLEXCOMM4_IRQHandler                       ;LP_FLEXCOMM4 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt)
        DCD     LP_FLEXCOMM5_IRQHandler                       ;LP_FLEXCOMM5 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt)
        DCD     LP_FLEXCOMM6_IRQHandler                       ;LP_FLEXCOMM6 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt)
        DCD     LP_FLEXCOMM7_IRQHandler                       ;LP_FLEXCOMM7 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt)
        DCD     Reserved59_IRQHandler                         ;Reserved interrupt
        DCD     Reserved60_IRQHandler                         ;Reserved interrupt
        DCD     ADC0_IRQHandler                               ;Analog-to-Digital Converter 0 - General Purpose interrupt
        DCD     ADC1_IRQHandler                               ;Analog-to-Digital Converter 1 - General Purpose interrupt
        DCD     PINT0_IRQHandler                              ;Pin Interrupt Pattern Match Interrupt
        DCD     PDM_EVENT_IRQHandler                          ;Microphone Interface interrupt
        DCD     Reserved65_IRQHandler                         ;Reserved interrupt
        DCD     Reserved66_IRQHandler                         ;Reserved interrupt
        DCD     USB0_DCD_IRQHandler                           ;Universal Serial Bus - Device Charge Detect interrupt
        DCD     RTC_IRQHandler                                ;RTC Subsystem interrupt (RTC interrupt or Wake timer interrupt)
        DCD     SMARTDMA_IRQHandler                           ;SmartDMA_IRQ
        DCD     Reserved70_IRQHandler                         ;Reserved interrupt
        DCD     CTIMER3_IRQHandler                            ;Standard counter/timer 3 interrupt
        DCD     CTIMER4_IRQHandler                            ;Standard counter/timer 4 interrupt
        DCD     OS_EVENT_IRQHandler                           ;OS event timer interrupt
        DCD     Reserved74_IRQHandler                         ;Reserved interrupt
        DCD     SAI0_IRQHandler                               ;Serial Audio Interface 0 interrupt
        DCD     SAI1_IRQHandler                               ;Serial Audio Interface 1 interrupt
        DCD     Reserved77_IRQHandler                         ;Reserved interrupt
        DCD     CAN0_IRQHandler                               ;Controller Area Network 0 interrupt
        DCD     CAN1_IRQHandler                               ;Controller Area Network 1 interrupt
        DCD     Reserved80_IRQHandler                         ;Reserved interrupt
        DCD     Reserved81_IRQHandler                         ;Reserved interrupt
        DCD     USB1_HS_PHY_IRQHandler                        ;USBHS DCD or USBHS Phy interrupt
        DCD     USB1_HS_IRQHandler                            ;USB High Speed OTG Controller interrupt
        DCD     SEC_HYPERVISOR_CALL_IRQHandler                ;AHB Secure Controller hypervisor call interrupt
        DCD     Reserved85_IRQHandler                         ;Reserved interrupt
        DCD     Reserved86_IRQHandler                         ;Reserved interrupt
        DCD     Freqme_IRQHandler                             ;Frequency Measurement interrupt
        DCD     SEC_VIO_IRQHandler                            ;Secure violation interrupt (Memory Block Checker interrupt or secure AHB matrix violation interrupt)
        DCD     ELS_IRQHandler                                ;ELS interrupt
        DCD     PKC_IRQHandler                                ;PKC interrupt
        DCD     PUF_IRQHandler                                ;Physical Unclonable Function interrupt
        DCD     Reserved92_IRQHandler                         ;Reserved interrupt
        DCD     EDMA_1_CH0_IRQHandler                         ;eDMA_1_CH0 error or transfer complete
        DCD     EDMA_1_CH1_IRQHandler                         ;eDMA_1_CH1 error or transfer complete
        DCD     EDMA_1_CH2_IRQHandler                         ;eDMA_1_CH2 error or transfer complete
        DCD     EDMA_1_CH3_IRQHandler                         ;eDMA_1_CH3 error or transfer complete
        DCD     EDMA_1_CH4_IRQHandler                         ;eDMA_1_CH4 error or transfer complete
        DCD     EDMA_1_CH5_IRQHandler                         ;eDMA_1_CH5 error or transfer complete
        DCD     EDMA_1_CH6_IRQHandler                         ;eDMA_1_CH6 error or transfer complete
        DCD     EDMA_1_CH7_IRQHandler                         ;eDMA_1_CH7 error or transfer complete
        DCD     Reserved101_IRQHandler                        ;Reserved interrupt
        DCD     Reserved102_IRQHandler                        ;Reserved interrupt
        DCD     Reserved103_IRQHandler                        ;Reserved interrupt
        DCD     Reserved104_IRQHandler                        ;Reserved interrupt
        DCD     Reserved105_IRQHandler                        ;Reserved interrupt
        DCD     Reserved106_IRQHandler                        ;Reserved interrupt
        DCD     Reserved107_IRQHandler                        ;Reserved interrupt
        DCD     Reserved108_IRQHandler                        ;Reserved interrupt
        DCD     CDOG0_IRQHandler                              ;Code Watchdog Timer 0 interrupt
        DCD     CDOG1_IRQHandler                              ;Code Watchdog Timer 1 interrupt
        DCD     I3C0_IRQHandler                               ;Improved Inter Integrated Circuit interrupt 0
        DCD     I3C1_IRQHandler                               ;Improved Inter Integrated Circuit interrupt 1
        DCD     Reserved113_IRQHandler                        ;Reserved interrupt
        DCD     GDET_IRQHandler                               ;Digital Glitch Detect 0 interrupt  or Digital Glitch Detect 1 interrupt
        DCD     VBAT0_IRQHandler                              ;VBAT interrupt( VBAT interrupt or digital tamper interrupt)
        DCD     EWM0_IRQHandler                               ;External Watchdog Monitor interrupt
        DCD     Reserved117_IRQHandler                        ;Reserved interrupt
        DCD     Reserved118_IRQHandler                        ;Reserved interrupt
        DCD     Reserved119_IRQHandler                        ;Reserved interrupt
        DCD     Reserved120_IRQHandler                        ;Reserved interrupt
        DCD     FLEXIO_IRQHandler                             ;Flexible Input/Output interrupt
        DCD     Reserved122_IRQHandler                        ;Reserved interrupt
        DCD     Reserved123_IRQHandler                        ;Reserved interrupt
        DCD     Reserved124_IRQHandler                        ;Reserved interrupt
        DCD     HSCMP0_IRQHandler                             ;High-Speed comparator0 interrupt
        DCD     HSCMP1_IRQHandler                             ;High-Speed comparator1 interrupt
        DCD     Reserved127_IRQHandler                        ;Reserved interrupt
        DCD     FLEXPWM0_RELOAD_ERROR_IRQHandler              ;FlexPWM0_reload_error interrupt
        DCD     FLEXPWM0_FAULT_IRQHandler                     ;FlexPWM0_fault interrupt
        DCD     FLEXPWM0_SUBMODULE0_IRQHandler                ;FlexPWM0 Submodule 0 capture/compare/reload interrupt
        DCD     FLEXPWM0_SUBMODULE1_IRQHandler                ;FlexPWM0 Submodule 1 capture/compare/reload interrupt
        DCD     FLEXPWM0_SUBMODULE2_IRQHandler                ;FlexPWM0 Submodule 2 capture/compare/reload interrupt
        DCD     FLEXPWM0_SUBMODULE3_IRQHandler                ;FlexPWM0 Submodule 3 capture/compare/reload interrupt
        DCD     FLEXPWM1_RELOAD_ERROR_IRQHandler              ;FlexPWM1_reload_error interrupt
        DCD     FLEXPWM1_FAULT_IRQHandler                     ;FlexPWM1_fault interrupt
        DCD     FLEXPWM1_SUBMODULE0_IRQHandler                ;FlexPWM1 Submodule 0 capture/compare/reload interrupt
        DCD     FLEXPWM1_SUBMODULE1_IRQHandler                ;FlexPWM1 Submodule 1 capture/compare/reload interrupt
        DCD     FLEXPWM1_SUBMODULE2_IRQHandler                ;FlexPWM1 Submodule 2 capture/compare/reload interrupt
        DCD     FLEXPWM1_SUBMODULE3_IRQHandler                ;FlexPWM1 Submodule 3 capture/compare/reload interrupt
        DCD     QDC0_COMPARE_IRQHandler                       ;QDC0_Compare interrupt
        DCD     QDC0_HOME_IRQHandler                          ;QDC0_Home interrupt
        DCD     QDC0_WDG_SAB_IRQHandler                       ;QDC0_WDG_IRQ/SAB interrupt
        DCD     QDC0_IDX_IRQHandler                           ;QDC0_IDX interrupt
        DCD     QDC1_COMPARE_IRQHandler                       ;QDC1_Compare interrupt
        DCD     QDC1_HOME_IRQHandler                          ;QDC1_Home interrupt
        DCD     QDC1_WDG_SAB_IRQHandler                       ;QDC1_WDG_IRQ/SAB interrupt
        DCD     QDC1_IDX_IRQHandler                           ;QDC1_IDX interrupt
        DCD     ITRC0_IRQHandler                              ;Intrusion and Tamper Response Controller interrupt
        DCD     Reserved149_IRQHandler                        ;Reserved interrupt
        DCD     ELS_ERR_IRQHandler                            ;ELS error interrupt
        DCD     PKC_ERR_IRQHandler                            ;PKC error interrupt
        DCD     ERM_SINGLE_BIT_ERROR_IRQHandler               ;ERM Single Bit error interrupt
        DCD     ERM_MULTI_BIT_ERROR_IRQHandler                ;ERM Multi Bit error interrupt
        DCD     FMU0_IRQHandler                               ;Flash Management Unit interrupt
        DCD     Reserved155_IRQHandler                        ;Reserved interrupt
        DCD     Reserved156_IRQHandler                        ;Reserved interrupt
        DCD     Reserved157_IRQHandler                        ;Reserved interrupt
        DCD     Reserved158_IRQHandler                        ;Reserved interrupt
        DCD     LPTMR0_IRQHandler                             ;Low Power Timer 0 interrupt
        DCD     LPTMR1_IRQHandler                             ;Low Power Timer 1 interrupt
        DCD     SCG_IRQHandler                                ;System Clock Generator interrupt
        DCD     SPC_IRQHandler                                ;System Power Controller interrupt
        DCD     WUU_IRQHandler                                ;Wake Up Unit interrupt
        DCD     PORT_EFT_IRQHandler                           ;PORT0~5 EFT interrupt
        DCD     Reserved165_IRQHandler                        ;Reserved interrupt
        DCD     Reserved166_IRQHandler                        ;Reserved interrupt
        DCD     Reserved167_IRQHandler                        ;Reserved interrupt
        DCD     WWDT0_IRQHandler                              ;Windowed Watchdog Timer 0 interrupt
        DCD     WWDT1_IRQHandler                              ;Windowed Watchdog Timer 1 interrupt
        DCD     CMC0_IRQHandler                               ;Core Mode Controller interrupt
        DCD     Reserved171_IRQHandler                        ;Reserved interrupt
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

        PUBWEAK OR_IRQHandler
        PUBWEAK OR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
OR_IRQHandler
        LDR     R0, =OR_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH0_IRQHandler
        PUBWEAK EDMA_0_CH0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH0_IRQHandler
        LDR     R0, =EDMA_0_CH0_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH1_IRQHandler
        PUBWEAK EDMA_0_CH1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH1_IRQHandler
        LDR     R0, =EDMA_0_CH1_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH2_IRQHandler
        PUBWEAK EDMA_0_CH2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH2_IRQHandler
        LDR     R0, =EDMA_0_CH2_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH3_IRQHandler
        PUBWEAK EDMA_0_CH3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH3_IRQHandler
        LDR     R0, =EDMA_0_CH3_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH4_IRQHandler
        PUBWEAK EDMA_0_CH4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH4_IRQHandler
        LDR     R0, =EDMA_0_CH4_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH5_IRQHandler
        PUBWEAK EDMA_0_CH5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH5_IRQHandler
        LDR     R0, =EDMA_0_CH5_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH6_IRQHandler
        PUBWEAK EDMA_0_CH6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH6_IRQHandler
        LDR     R0, =EDMA_0_CH6_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH7_IRQHandler
        PUBWEAK EDMA_0_CH7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH7_IRQHandler
        LDR     R0, =EDMA_0_CH7_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH8_IRQHandler
        PUBWEAK EDMA_0_CH8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH8_IRQHandler
        LDR     R0, =EDMA_0_CH8_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH9_IRQHandler
        PUBWEAK EDMA_0_CH9_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH9_IRQHandler
        LDR     R0, =EDMA_0_CH9_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH10_IRQHandler
        PUBWEAK EDMA_0_CH10_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH10_IRQHandler
        LDR     R0, =EDMA_0_CH10_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH11_IRQHandler
        PUBWEAK EDMA_0_CH11_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH11_IRQHandler
        LDR     R0, =EDMA_0_CH11_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH12_IRQHandler
        PUBWEAK EDMA_0_CH12_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH12_IRQHandler
        LDR     R0, =EDMA_0_CH12_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH13_IRQHandler
        PUBWEAK EDMA_0_CH13_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH13_IRQHandler
        LDR     R0, =EDMA_0_CH13_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH14_IRQHandler
        PUBWEAK EDMA_0_CH14_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH14_IRQHandler
        LDR     R0, =EDMA_0_CH14_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_0_CH15_IRQHandler
        PUBWEAK EDMA_0_CH15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_0_CH15_IRQHandler
        LDR     R0, =EDMA_0_CH15_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO00_IRQHandler
        PUBWEAK GPIO00_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO00_IRQHandler
        LDR     R0, =GPIO00_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO01_IRQHandler
        PUBWEAK GPIO01_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO01_IRQHandler
        LDR     R0, =GPIO01_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO10_IRQHandler
        PUBWEAK GPIO10_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO10_IRQHandler
        LDR     R0, =GPIO10_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO11_IRQHandler
        PUBWEAK GPIO11_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO11_IRQHandler
        LDR     R0, =GPIO11_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO20_IRQHandler
        PUBWEAK GPIO20_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO20_IRQHandler
        LDR     R0, =GPIO20_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO21_IRQHandler
        PUBWEAK GPIO21_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO21_IRQHandler
        LDR     R0, =GPIO21_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO30_IRQHandler
        PUBWEAK GPIO30_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO30_IRQHandler
        LDR     R0, =GPIO30_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO31_IRQHandler
        PUBWEAK GPIO31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO31_IRQHandler
        LDR     R0, =GPIO31_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO40_IRQHandler
        PUBWEAK GPIO40_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO40_IRQHandler
        LDR     R0, =GPIO40_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO41_IRQHandler
        PUBWEAK GPIO41_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO41_IRQHandler
        LDR     R0, =GPIO41_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO50_IRQHandler
        PUBWEAK GPIO50_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO50_IRQHandler
        LDR     R0, =GPIO50_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO51_IRQHandler
        PUBWEAK GPIO51_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GPIO51_IRQHandler
        LDR     R0, =GPIO51_DriverIRQHandler
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

        PUBWEAK Reserved49_IRQHandler
        PUBWEAK Reserved49_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved49_IRQHandler
        LDR     R0, =Reserved49_DriverIRQHandler
        BX      R0

        PUBWEAK CTIMER2_IRQHandler
        PUBWEAK CTIMER2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER2_IRQHandler
        LDR     R0, =CTIMER2_DriverIRQHandler
        BX      R0

        PUBWEAK LP_FLEXCOMM0_IRQHandler
        PUBWEAK LP_FLEXCOMM0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LP_FLEXCOMM0_IRQHandler
        LDR     R0, =LP_FLEXCOMM0_DriverIRQHandler
        BX      R0

        PUBWEAK LP_FLEXCOMM1_IRQHandler
        PUBWEAK LP_FLEXCOMM1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LP_FLEXCOMM1_IRQHandler
        LDR     R0, =LP_FLEXCOMM1_DriverIRQHandler
        BX      R0

        PUBWEAK LP_FLEXCOMM2_IRQHandler
        PUBWEAK LP_FLEXCOMM2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LP_FLEXCOMM2_IRQHandler
        LDR     R0, =LP_FLEXCOMM2_DriverIRQHandler
        BX      R0

        PUBWEAK LP_FLEXCOMM3_IRQHandler
        PUBWEAK LP_FLEXCOMM3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LP_FLEXCOMM3_IRQHandler
        LDR     R0, =LP_FLEXCOMM3_DriverIRQHandler
        BX      R0

        PUBWEAK LP_FLEXCOMM4_IRQHandler
        PUBWEAK LP_FLEXCOMM4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LP_FLEXCOMM4_IRQHandler
        LDR     R0, =LP_FLEXCOMM4_DriverIRQHandler
        BX      R0

        PUBWEAK LP_FLEXCOMM5_IRQHandler
        PUBWEAK LP_FLEXCOMM5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LP_FLEXCOMM5_IRQHandler
        LDR     R0, =LP_FLEXCOMM5_DriverIRQHandler
        BX      R0

        PUBWEAK LP_FLEXCOMM6_IRQHandler
        PUBWEAK LP_FLEXCOMM6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LP_FLEXCOMM6_IRQHandler
        LDR     R0, =LP_FLEXCOMM6_DriverIRQHandler
        BX      R0

        PUBWEAK LP_FLEXCOMM7_IRQHandler
        PUBWEAK LP_FLEXCOMM7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LP_FLEXCOMM7_IRQHandler
        LDR     R0, =LP_FLEXCOMM7_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved59_IRQHandler
        PUBWEAK Reserved59_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved59_IRQHandler
        LDR     R0, =Reserved59_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved60_IRQHandler
        PUBWEAK Reserved60_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved60_IRQHandler
        LDR     R0, =Reserved60_DriverIRQHandler
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

        PUBWEAK PINT0_IRQHandler
        PUBWEAK PINT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PINT0_IRQHandler
        LDR     R0, =PINT0_DriverIRQHandler
        BX      R0

        PUBWEAK PDM_EVENT_IRQHandler
        PUBWEAK PDM_EVENT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_EVENT_IRQHandler
        LDR     R0, =PDM_EVENT_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved65_IRQHandler
        PUBWEAK Reserved65_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved65_IRQHandler
        LDR     R0, =Reserved65_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved66_IRQHandler
        PUBWEAK Reserved66_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved66_IRQHandler
        LDR     R0, =Reserved66_DriverIRQHandler
        BX      R0

        PUBWEAK USB0_DCD_IRQHandler
        PUBWEAK USB0_DCD_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB0_DCD_IRQHandler
        LDR     R0, =USB0_DCD_DriverIRQHandler
        BX      R0

        PUBWEAK RTC_IRQHandler
        PUBWEAK RTC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
RTC_IRQHandler
        LDR     R0, =RTC_DriverIRQHandler
        BX      R0

        PUBWEAK SMARTDMA_IRQHandler
        PUBWEAK SMARTDMA_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SMARTDMA_IRQHandler
        LDR     R0, =SMARTDMA_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved70_IRQHandler
        PUBWEAK Reserved70_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved70_IRQHandler
        LDR     R0, =Reserved70_DriverIRQHandler
        BX      R0

        PUBWEAK CTIMER3_IRQHandler
        PUBWEAK CTIMER3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CTIMER3_IRQHandler
        LDR     R0, =CTIMER3_DriverIRQHandler
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

        PUBWEAK Reserved74_IRQHandler
        PUBWEAK Reserved74_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved74_IRQHandler
        LDR     R0, =Reserved74_DriverIRQHandler
        BX      R0

        PUBWEAK SAI0_IRQHandler
        PUBWEAK SAI0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI0_IRQHandler
        LDR     R0, =SAI0_DriverIRQHandler
        BX      R0

        PUBWEAK SAI1_IRQHandler
        PUBWEAK SAI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI1_IRQHandler
        LDR     R0, =SAI1_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved77_IRQHandler
        PUBWEAK Reserved77_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved77_IRQHandler
        LDR     R0, =Reserved77_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_IRQHandler
        PUBWEAK CAN0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_IRQHandler
        LDR     R0, =CAN0_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_IRQHandler
        PUBWEAK CAN1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_IRQHandler
        LDR     R0, =CAN1_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved80_IRQHandler
        PUBWEAK Reserved80_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved80_IRQHandler
        LDR     R0, =Reserved80_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved81_IRQHandler
        PUBWEAK Reserved81_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved81_IRQHandler
        LDR     R0, =Reserved81_DriverIRQHandler
        BX      R0

        PUBWEAK USB1_HS_PHY_IRQHandler
        PUBWEAK USB1_HS_PHY_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB1_HS_PHY_IRQHandler
        LDR     R0, =USB1_HS_PHY_DriverIRQHandler
        BX      R0

        PUBWEAK USB1_HS_IRQHandler
        PUBWEAK USB1_HS_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USB1_HS_IRQHandler
        LDR     R0, =USB1_HS_DriverIRQHandler
        BX      R0

        PUBWEAK SEC_HYPERVISOR_CALL_IRQHandler
        PUBWEAK SEC_HYPERVISOR_CALL_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SEC_HYPERVISOR_CALL_IRQHandler
        LDR     R0, =SEC_HYPERVISOR_CALL_DriverIRQHandler
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

        PUBWEAK ELS_IRQHandler
        PUBWEAK ELS_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ELS_IRQHandler
        LDR     R0, =ELS_DriverIRQHandler
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

        PUBWEAK Reserved92_IRQHandler
        PUBWEAK Reserved92_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved92_IRQHandler
        LDR     R0, =Reserved92_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_1_CH0_IRQHandler
        PUBWEAK EDMA_1_CH0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_1_CH0_IRQHandler
        LDR     R0, =EDMA_1_CH0_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_1_CH1_IRQHandler
        PUBWEAK EDMA_1_CH1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_1_CH1_IRQHandler
        LDR     R0, =EDMA_1_CH1_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_1_CH2_IRQHandler
        PUBWEAK EDMA_1_CH2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_1_CH2_IRQHandler
        LDR     R0, =EDMA_1_CH2_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_1_CH3_IRQHandler
        PUBWEAK EDMA_1_CH3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_1_CH3_IRQHandler
        LDR     R0, =EDMA_1_CH3_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_1_CH4_IRQHandler
        PUBWEAK EDMA_1_CH4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_1_CH4_IRQHandler
        LDR     R0, =EDMA_1_CH4_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_1_CH5_IRQHandler
        PUBWEAK EDMA_1_CH5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_1_CH5_IRQHandler
        LDR     R0, =EDMA_1_CH5_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_1_CH6_IRQHandler
        PUBWEAK EDMA_1_CH6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_1_CH6_IRQHandler
        LDR     R0, =EDMA_1_CH6_DriverIRQHandler
        BX      R0

        PUBWEAK EDMA_1_CH7_IRQHandler
        PUBWEAK EDMA_1_CH7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EDMA_1_CH7_IRQHandler
        LDR     R0, =EDMA_1_CH7_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved101_IRQHandler
        PUBWEAK Reserved101_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved101_IRQHandler
        LDR     R0, =Reserved101_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved102_IRQHandler
        PUBWEAK Reserved102_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved102_IRQHandler
        LDR     R0, =Reserved102_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved103_IRQHandler
        PUBWEAK Reserved103_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved103_IRQHandler
        LDR     R0, =Reserved103_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved104_IRQHandler
        PUBWEAK Reserved104_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved104_IRQHandler
        LDR     R0, =Reserved104_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved105_IRQHandler
        PUBWEAK Reserved105_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved105_IRQHandler
        LDR     R0, =Reserved105_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved106_IRQHandler
        PUBWEAK Reserved106_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved106_IRQHandler
        LDR     R0, =Reserved106_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved107_IRQHandler
        PUBWEAK Reserved107_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved107_IRQHandler
        LDR     R0, =Reserved107_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved108_IRQHandler
        PUBWEAK Reserved108_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved108_IRQHandler
        LDR     R0, =Reserved108_DriverIRQHandler
        BX      R0

        PUBWEAK CDOG0_IRQHandler
        PUBWEAK CDOG0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CDOG0_IRQHandler
        LDR     R0, =CDOG0_DriverIRQHandler
        BX      R0

        PUBWEAK CDOG1_IRQHandler
        PUBWEAK CDOG1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CDOG1_IRQHandler
        LDR     R0, =CDOG1_DriverIRQHandler
        BX      R0

        PUBWEAK I3C0_IRQHandler
        PUBWEAK I3C0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I3C0_IRQHandler
        LDR     R0, =I3C0_DriverIRQHandler
        BX      R0

        PUBWEAK I3C1_IRQHandler
        PUBWEAK I3C1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I3C1_IRQHandler
        LDR     R0, =I3C1_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved113_IRQHandler
        PUBWEAK Reserved113_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved113_IRQHandler
        LDR     R0, =Reserved113_DriverIRQHandler
        BX      R0

        PUBWEAK GDET_IRQHandler
        PUBWEAK GDET_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
GDET_IRQHandler
        LDR     R0, =GDET_DriverIRQHandler
        BX      R0

        PUBWEAK VBAT0_IRQHandler
        PUBWEAK VBAT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
VBAT0_IRQHandler
        LDR     R0, =VBAT0_DriverIRQHandler
        BX      R0

        PUBWEAK EWM0_IRQHandler
        PUBWEAK EWM0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EWM0_IRQHandler
        LDR     R0, =EWM0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved117_IRQHandler
        PUBWEAK Reserved117_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved117_IRQHandler
        LDR     R0, =Reserved117_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved118_IRQHandler
        PUBWEAK Reserved118_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved118_IRQHandler
        LDR     R0, =Reserved118_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved119_IRQHandler
        PUBWEAK Reserved119_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved119_IRQHandler
        LDR     R0, =Reserved119_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved120_IRQHandler
        PUBWEAK Reserved120_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved120_IRQHandler
        LDR     R0, =Reserved120_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXIO_IRQHandler
        PUBWEAK FLEXIO_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXIO_IRQHandler
        LDR     R0, =FLEXIO_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved122_IRQHandler
        PUBWEAK Reserved122_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved122_IRQHandler
        LDR     R0, =Reserved122_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved123_IRQHandler
        PUBWEAK Reserved123_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved123_IRQHandler
        LDR     R0, =Reserved123_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved124_IRQHandler
        PUBWEAK Reserved124_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved124_IRQHandler
        LDR     R0, =Reserved124_DriverIRQHandler
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

        PUBWEAK Reserved127_IRQHandler
        PUBWEAK Reserved127_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved127_IRQHandler
        LDR     R0, =Reserved127_DriverIRQHandler
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

        PUBWEAK FLEXPWM0_SUBMODULE3_IRQHandler
        PUBWEAK FLEXPWM0_SUBMODULE3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM0_SUBMODULE3_IRQHandler
        LDR     R0, =FLEXPWM0_SUBMODULE3_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM1_RELOAD_ERROR_IRQHandler
        PUBWEAK FLEXPWM1_RELOAD_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_RELOAD_ERROR_IRQHandler
        LDR     R0, =FLEXPWM1_RELOAD_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM1_FAULT_IRQHandler
        PUBWEAK FLEXPWM1_FAULT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_FAULT_IRQHandler
        LDR     R0, =FLEXPWM1_FAULT_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM1_SUBMODULE0_IRQHandler
        PUBWEAK FLEXPWM1_SUBMODULE0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_SUBMODULE0_IRQHandler
        LDR     R0, =FLEXPWM1_SUBMODULE0_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM1_SUBMODULE1_IRQHandler
        PUBWEAK FLEXPWM1_SUBMODULE1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_SUBMODULE1_IRQHandler
        LDR     R0, =FLEXPWM1_SUBMODULE1_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM1_SUBMODULE2_IRQHandler
        PUBWEAK FLEXPWM1_SUBMODULE2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_SUBMODULE2_IRQHandler
        LDR     R0, =FLEXPWM1_SUBMODULE2_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXPWM1_SUBMODULE3_IRQHandler
        PUBWEAK FLEXPWM1_SUBMODULE3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXPWM1_SUBMODULE3_IRQHandler
        LDR     R0, =FLEXPWM1_SUBMODULE3_DriverIRQHandler
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

        PUBWEAK QDC0_WDG_SAB_IRQHandler
        PUBWEAK QDC0_WDG_SAB_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC0_WDG_SAB_IRQHandler
        LDR     R0, =QDC0_WDG_SAB_DriverIRQHandler
        BX      R0

        PUBWEAK QDC0_IDX_IRQHandler
        PUBWEAK QDC0_IDX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC0_IDX_IRQHandler
        LDR     R0, =QDC0_IDX_DriverIRQHandler
        BX      R0

        PUBWEAK QDC1_COMPARE_IRQHandler
        PUBWEAK QDC1_COMPARE_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC1_COMPARE_IRQHandler
        LDR     R0, =QDC1_COMPARE_DriverIRQHandler
        BX      R0

        PUBWEAK QDC1_HOME_IRQHandler
        PUBWEAK QDC1_HOME_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC1_HOME_IRQHandler
        LDR     R0, =QDC1_HOME_DriverIRQHandler
        BX      R0

        PUBWEAK QDC1_WDG_SAB_IRQHandler
        PUBWEAK QDC1_WDG_SAB_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC1_WDG_SAB_IRQHandler
        LDR     R0, =QDC1_WDG_SAB_DriverIRQHandler
        BX      R0

        PUBWEAK QDC1_IDX_IRQHandler
        PUBWEAK QDC1_IDX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
QDC1_IDX_IRQHandler
        LDR     R0, =QDC1_IDX_DriverIRQHandler
        BX      R0

        PUBWEAK ITRC0_IRQHandler
        PUBWEAK ITRC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ITRC0_IRQHandler
        LDR     R0, =ITRC0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved149_IRQHandler
        PUBWEAK Reserved149_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved149_IRQHandler
        LDR     R0, =Reserved149_DriverIRQHandler
        BX      R0

        PUBWEAK ELS_ERR_IRQHandler
        PUBWEAK ELS_ERR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ELS_ERR_IRQHandler
        LDR     R0, =ELS_ERR_DriverIRQHandler
        BX      R0

        PUBWEAK PKC_ERR_IRQHandler
        PUBWEAK PKC_ERR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PKC_ERR_IRQHandler
        LDR     R0, =PKC_ERR_DriverIRQHandler
        BX      R0

        PUBWEAK ERM_SINGLE_BIT_ERROR_IRQHandler
        PUBWEAK ERM_SINGLE_BIT_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ERM_SINGLE_BIT_ERROR_IRQHandler
        LDR     R0, =ERM_SINGLE_BIT_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK ERM_MULTI_BIT_ERROR_IRQHandler
        PUBWEAK ERM_MULTI_BIT_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ERM_MULTI_BIT_ERROR_IRQHandler
        LDR     R0, =ERM_MULTI_BIT_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK FMU0_IRQHandler
        PUBWEAK FMU0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FMU0_IRQHandler
        LDR     R0, =FMU0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved155_IRQHandler
        PUBWEAK Reserved155_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved155_IRQHandler
        LDR     R0, =Reserved155_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved156_IRQHandler
        PUBWEAK Reserved156_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved156_IRQHandler
        LDR     R0, =Reserved156_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved157_IRQHandler
        PUBWEAK Reserved157_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved157_IRQHandler
        LDR     R0, =Reserved157_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved158_IRQHandler
        PUBWEAK Reserved158_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved158_IRQHandler
        LDR     R0, =Reserved158_DriverIRQHandler
        BX      R0

        PUBWEAK LPTMR0_IRQHandler
        PUBWEAK LPTMR0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPTMR0_IRQHandler
        LDR     R0, =LPTMR0_DriverIRQHandler
        BX      R0

        PUBWEAK LPTMR1_IRQHandler
        PUBWEAK LPTMR1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPTMR1_IRQHandler
        LDR     R0, =LPTMR1_DriverIRQHandler
        BX      R0

        PUBWEAK SCG_IRQHandler
        PUBWEAK SCG_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SCG_IRQHandler
        LDR     R0, =SCG_DriverIRQHandler
        BX      R0

        PUBWEAK SPC_IRQHandler
        PUBWEAK SPC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPC_IRQHandler
        LDR     R0, =SPC_DriverIRQHandler
        BX      R0

        PUBWEAK WUU_IRQHandler
        PUBWEAK WUU_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WUU_IRQHandler
        LDR     R0, =WUU_DriverIRQHandler
        BX      R0

        PUBWEAK PORT_EFT_IRQHandler
        PUBWEAK PORT_EFT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PORT_EFT_IRQHandler
        LDR     R0, =PORT_EFT_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved165_IRQHandler
        PUBWEAK Reserved165_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved165_IRQHandler
        LDR     R0, =Reserved165_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved166_IRQHandler
        PUBWEAK Reserved166_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved166_IRQHandler
        LDR     R0, =Reserved166_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved167_IRQHandler
        PUBWEAK Reserved167_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved167_IRQHandler
        LDR     R0, =Reserved167_DriverIRQHandler
        BX      R0

        PUBWEAK WWDT0_IRQHandler
        PUBWEAK WWDT0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WWDT0_IRQHandler
        LDR     R0, =WWDT0_DriverIRQHandler
        BX      R0

        PUBWEAK WWDT1_IRQHandler
        PUBWEAK WWDT1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WWDT1_IRQHandler
        LDR     R0, =WWDT1_DriverIRQHandler
        BX      R0

        PUBWEAK CMC0_IRQHandler
        PUBWEAK CMC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CMC0_IRQHandler
        LDR     R0, =CMC0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved171_IRQHandler
        PUBWEAK Reserved171_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reserved171_IRQHandler
        LDR     R0, =Reserved171_DriverIRQHandler
        BX      R0

OR_DriverIRQHandler
EDMA_0_CH0_DriverIRQHandler
EDMA_0_CH1_DriverIRQHandler
EDMA_0_CH2_DriverIRQHandler
EDMA_0_CH3_DriverIRQHandler
EDMA_0_CH4_DriverIRQHandler
EDMA_0_CH5_DriverIRQHandler
EDMA_0_CH6_DriverIRQHandler
EDMA_0_CH7_DriverIRQHandler
EDMA_0_CH8_DriverIRQHandler
EDMA_0_CH9_DriverIRQHandler
EDMA_0_CH10_DriverIRQHandler
EDMA_0_CH11_DriverIRQHandler
EDMA_0_CH12_DriverIRQHandler
EDMA_0_CH13_DriverIRQHandler
EDMA_0_CH14_DriverIRQHandler
EDMA_0_CH15_DriverIRQHandler
GPIO00_DriverIRQHandler
GPIO01_DriverIRQHandler
GPIO10_DriverIRQHandler
GPIO11_DriverIRQHandler
GPIO20_DriverIRQHandler
GPIO21_DriverIRQHandler
GPIO30_DriverIRQHandler
GPIO31_DriverIRQHandler
GPIO40_DriverIRQHandler
GPIO41_DriverIRQHandler
GPIO50_DriverIRQHandler
GPIO51_DriverIRQHandler
UTICK0_DriverIRQHandler
MRT0_DriverIRQHandler
CTIMER0_DriverIRQHandler
CTIMER1_DriverIRQHandler
Reserved49_DriverIRQHandler
CTIMER2_DriverIRQHandler
LP_FLEXCOMM0_DriverIRQHandler
LP_FLEXCOMM1_DriverIRQHandler
LP_FLEXCOMM2_DriverIRQHandler
LP_FLEXCOMM3_DriverIRQHandler
LP_FLEXCOMM4_DriverIRQHandler
LP_FLEXCOMM5_DriverIRQHandler
LP_FLEXCOMM6_DriverIRQHandler
LP_FLEXCOMM7_DriverIRQHandler
Reserved59_DriverIRQHandler
Reserved60_DriverIRQHandler
ADC0_DriverIRQHandler
ADC1_DriverIRQHandler
PINT0_DriverIRQHandler
PDM_EVENT_DriverIRQHandler
Reserved65_DriverIRQHandler
Reserved66_DriverIRQHandler
USB0_DCD_DriverIRQHandler
RTC_DriverIRQHandler
SMARTDMA_DriverIRQHandler
Reserved70_DriverIRQHandler
CTIMER3_DriverIRQHandler
CTIMER4_DriverIRQHandler
OS_EVENT_DriverIRQHandler
Reserved74_DriverIRQHandler
SAI0_DriverIRQHandler
SAI1_DriverIRQHandler
Reserved77_DriverIRQHandler
CAN0_DriverIRQHandler
CAN1_DriverIRQHandler
Reserved80_DriverIRQHandler
Reserved81_DriverIRQHandler
USB1_HS_PHY_DriverIRQHandler
USB1_HS_DriverIRQHandler
SEC_HYPERVISOR_CALL_DriverIRQHandler
Reserved85_DriverIRQHandler
Reserved86_DriverIRQHandler
Freqme_DriverIRQHandler
SEC_VIO_DriverIRQHandler
ELS_DriverIRQHandler
PKC_DriverIRQHandler
PUF_DriverIRQHandler
Reserved92_DriverIRQHandler
EDMA_1_CH0_DriverIRQHandler
EDMA_1_CH1_DriverIRQHandler
EDMA_1_CH2_DriverIRQHandler
EDMA_1_CH3_DriverIRQHandler
EDMA_1_CH4_DriverIRQHandler
EDMA_1_CH5_DriverIRQHandler
EDMA_1_CH6_DriverIRQHandler
EDMA_1_CH7_DriverIRQHandler
Reserved101_DriverIRQHandler
Reserved102_DriverIRQHandler
Reserved103_DriverIRQHandler
Reserved104_DriverIRQHandler
Reserved105_DriverIRQHandler
Reserved106_DriverIRQHandler
Reserved107_DriverIRQHandler
Reserved108_DriverIRQHandler
CDOG0_DriverIRQHandler
CDOG1_DriverIRQHandler
I3C0_DriverIRQHandler
I3C1_DriverIRQHandler
Reserved113_DriverIRQHandler
GDET_DriverIRQHandler
VBAT0_DriverIRQHandler
EWM0_DriverIRQHandler
Reserved117_DriverIRQHandler
Reserved118_DriverIRQHandler
Reserved119_DriverIRQHandler
Reserved120_DriverIRQHandler
FLEXIO_DriverIRQHandler
Reserved122_DriverIRQHandler
Reserved123_DriverIRQHandler
Reserved124_DriverIRQHandler
HSCMP0_DriverIRQHandler
HSCMP1_DriverIRQHandler
Reserved127_DriverIRQHandler
FLEXPWM0_RELOAD_ERROR_DriverIRQHandler
FLEXPWM0_FAULT_DriverIRQHandler
FLEXPWM0_SUBMODULE0_DriverIRQHandler
FLEXPWM0_SUBMODULE1_DriverIRQHandler
FLEXPWM0_SUBMODULE2_DriverIRQHandler
FLEXPWM0_SUBMODULE3_DriverIRQHandler
FLEXPWM1_RELOAD_ERROR_DriverIRQHandler
FLEXPWM1_FAULT_DriverIRQHandler
FLEXPWM1_SUBMODULE0_DriverIRQHandler
FLEXPWM1_SUBMODULE1_DriverIRQHandler
FLEXPWM1_SUBMODULE2_DriverIRQHandler
FLEXPWM1_SUBMODULE3_DriverIRQHandler
QDC0_COMPARE_DriverIRQHandler
QDC0_HOME_DriverIRQHandler
QDC0_WDG_SAB_DriverIRQHandler
QDC0_IDX_DriverIRQHandler
QDC1_COMPARE_DriverIRQHandler
QDC1_HOME_DriverIRQHandler
QDC1_WDG_SAB_DriverIRQHandler
QDC1_IDX_DriverIRQHandler
ITRC0_DriverIRQHandler
Reserved149_DriverIRQHandler
ELS_ERR_DriverIRQHandler
PKC_ERR_DriverIRQHandler
ERM_SINGLE_BIT_ERROR_DriverIRQHandler
ERM_MULTI_BIT_ERROR_DriverIRQHandler
FMU0_DriverIRQHandler
Reserved155_DriverIRQHandler
Reserved156_DriverIRQHandler
Reserved157_DriverIRQHandler
Reserved158_DriverIRQHandler
LPTMR0_DriverIRQHandler
LPTMR1_DriverIRQHandler
SCG_DriverIRQHandler
SPC_DriverIRQHandler
WUU_DriverIRQHandler
PORT_EFT_DriverIRQHandler
Reserved165_DriverIRQHandler
Reserved166_DriverIRQHandler
Reserved167_DriverIRQHandler
WWDT0_DriverIRQHandler
WWDT1_DriverIRQHandler
CMC0_DriverIRQHandler
Reserved171_DriverIRQHandler
DefaultISR
        B .

        END
