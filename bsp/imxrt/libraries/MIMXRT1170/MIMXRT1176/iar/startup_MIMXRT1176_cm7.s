; -------------------------------------------------------------------------
;  @file:    startup_MIMXRT1176_cm7.s
;  @purpose: CMSIS Cortex-M7 Core Device Startup File
;            MIMXRT1176_cm7
;  @version: 1.0
;  @date:    2020-12-29
;  @build:   b211122
; -------------------------------------------------------------------------
;
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

        DCD     NMI_Handler                                   ;NMI Handler
        DCD     HardFault_Handler                             ;Hard Fault Handler
        DCD     MemManage_Handler                             ;MPU Fault Handler
        DCD     BusFault_Handler                              ;Bus Fault Handler
        DCD     UsageFault_Handler                            ;Usage Fault Handler
__vector_table_0x1c
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     SVC_Handler                                   ;SVCall Handler
        DCD     DebugMon_Handler                              ;Debug Monitor Handler
        DCD     0                                             ;Reserved
        DCD     PendSV_Handler                                ;PendSV Handler
        DCD     SysTick_Handler                               ;SysTick Handler

                                                              ;External Interrupts
        DCD     DMA0_DMA16_IRQHandler                         ;DMA channel 0/16 transfer complete
        DCD     DMA1_DMA17_IRQHandler                         ;DMA channel 1/17 transfer complete
        DCD     DMA2_DMA18_IRQHandler                         ;DMA channel 2/18 transfer complete
        DCD     DMA3_DMA19_IRQHandler                         ;DMA channel 3/19 transfer complete
        DCD     DMA4_DMA20_IRQHandler                         ;DMA channel 4/20 transfer complete
        DCD     DMA5_DMA21_IRQHandler                         ;DMA channel 5/21 transfer complete
        DCD     DMA6_DMA22_IRQHandler                         ;DMA channel 6/22 transfer complete
        DCD     DMA7_DMA23_IRQHandler                         ;DMA channel 7/23 transfer complete
        DCD     DMA8_DMA24_IRQHandler                         ;DMA channel 8/24 transfer complete
        DCD     DMA9_DMA25_IRQHandler                         ;DMA channel 9/25 transfer complete
        DCD     DMA10_DMA26_IRQHandler                        ;DMA channel 10/26 transfer complete
        DCD     DMA11_DMA27_IRQHandler                        ;DMA channel 11/27 transfer complete
        DCD     DMA12_DMA28_IRQHandler                        ;DMA channel 12/28 transfer complete
        DCD     DMA13_DMA29_IRQHandler                        ;DMA channel 13/29 transfer complete
        DCD     DMA14_DMA30_IRQHandler                        ;DMA channel 14/30 transfer complete
        DCD     DMA15_DMA31_IRQHandler                        ;DMA channel 15/31 transfer complete
        DCD     DMA_ERROR_IRQHandler                          ;DMA error interrupt channels 0-15 / 16-31
        DCD     CTI_TRIGGER_OUT0_IRQHandler                   ;CTI_TRIGGER_OUT0
        DCD     CTI_TRIGGER_OUT1_IRQHandler                   ;CTI_TRIGGER_OUT1
        DCD     CORE_IRQHandler                               ;CorePlatform exception IRQ
        DCD     LPUART1_IRQHandler                            ;LPUART1 TX interrupt and RX interrupt
        DCD     LPUART2_IRQHandler                            ;LPUART2 TX interrupt and RX interrupt
        DCD     LPUART3_IRQHandler                            ;LPUART3 TX interrupt and RX interrupt
        DCD     LPUART4_IRQHandler                            ;LPUART4 TX interrupt and RX interrupt
        DCD     LPUART5_IRQHandler                            ;LPUART5 TX interrupt and RX interrupt
        DCD     LPUART6_IRQHandler                            ;LPUART6 TX interrupt and RX interrupt
        DCD     LPUART7_IRQHandler                            ;LPUART7 TX interrupt and RX interrupt
        DCD     LPUART8_IRQHandler                            ;LPUART8 TX interrupt and RX interrupt
        DCD     LPUART9_IRQHandler                            ;LPUART9 TX interrupt and RX interrupt
        DCD     LPUART10_IRQHandler                           ;LPUART10 TX interrupt and RX interrupt
        DCD     LPUART11_IRQHandler                           ;LPUART11 TX interrupt and RX interrupt
        DCD     LPUART12_IRQHandler                           ;LPUART12 TX interrupt and RX interrupt
        DCD     LPI2C1_IRQHandler                             ;LPI2C1 interrupt
        DCD     LPI2C2_IRQHandler                             ;LPI2C2 interrupt
        DCD     LPI2C3_IRQHandler                             ;LPI2C3 interrupt
        DCD     LPI2C4_IRQHandler                             ;LPI2C4 interrupt
        DCD     LPI2C5_IRQHandler                             ;LPI2C5 interrupt
        DCD     LPI2C6_IRQHandler                             ;LPI2C6 interrupt
        DCD     LPSPI1_IRQHandler                             ;LPSPI1 interrupt request line to the core
        DCD     LPSPI2_IRQHandler                             ;LPSPI2 interrupt request line to the core
        DCD     LPSPI3_IRQHandler                             ;LPSPI3 interrupt request line to the core
        DCD     LPSPI4_IRQHandler                             ;LPSPI4 interrupt request line to the core
        DCD     LPSPI5_IRQHandler                             ;LPSPI5 interrupt request line to the core
        DCD     LPSPI6_IRQHandler                             ;LPSPI6 interrupt request line to the core
        DCD     CAN1_IRQHandler                               ;CAN1 interrupt
        DCD     CAN1_ERROR_IRQHandler                         ;CAN1 error interrupt
        DCD     CAN2_IRQHandler                               ;CAN2 interrupt
        DCD     CAN2_ERROR_IRQHandler                         ;CAN2 error interrupt
        DCD     CAN3_IRQHandler                               ;CAN3 interrupt
        DCD     CAN3_ERROR_IRQHandler                         ;CAN3 erro interrupt
        DCD     FLEXRAM_IRQHandler                            ;FlexRAM address out of range Or access hit IRQ
        DCD     KPP_IRQHandler                                ;Keypad nterrupt
        DCD     Reserved68_IRQHandler                         ;Reserved interrupt
        DCD     GPR_IRQ_IRQHandler                            ;GPR interrupt
        DCD     eLCDIF_IRQHandler                             ;eLCDIF interrupt
        DCD     LCDIFv2_IRQHandler                            ;LCDIFv2 interrupt
        DCD     CSI_IRQHandler                                ;CSI interrupt
        DCD     PXP_IRQHandler                                ;PXP interrupt
        DCD     MIPI_CSI_IRQHandler                           ;MIPI_CSI interrupt
        DCD     MIPI_DSI_IRQHandler                           ;MIPI_DSI interrupt
        DCD     GPU2D_IRQHandler                              ;GPU2D interrupt
        DCD     GPIO6_Combined_0_15_IRQHandler                ;Combined interrupt indication for GPIO6 signal 0 throughout 15
        DCD     GPIO6_Combined_16_31_IRQHandler               ;Combined interrupt indication for GPIO6 signal 16 throughout 31
        DCD     DAC_IRQHandler                                ;DAC interrupt
        DCD     KEY_MANAGER_IRQHandler                        ;PUF interrupt
        DCD     WDOG2_IRQHandler                              ;WDOG2 interrupt
        DCD     SNVS_HP_NON_TZ_IRQHandler                     ;SRTC Consolidated Interrupt. Non TZ
        DCD     SNVS_HP_TZ_IRQHandler                         ;SRTC Security Interrupt. TZ
        DCD     SNVS_PULSE_EVENT_IRQHandler                   ;ON-OFF button press shorter than 5 secs (pulse event)
        DCD     CAAM_IRQ0_IRQHandler                          ;CAAM interrupt queue for JQ0
        DCD     CAAM_IRQ1_IRQHandler                          ;CAAM interrupt queue for JQ1
        DCD     CAAM_IRQ2_IRQHandler                          ;CAAM interrupt queue for JQ2
        DCD     CAAM_IRQ3_IRQHandler                          ;CAAM interrupt queue for JQ3
        DCD     CAAM_RECORVE_ERRPR_IRQHandler                 ;CAAM interrupt for recoverable error
        DCD     CAAM_RTIC_IRQHandler                          ;CAAM interrupt for RTIC
        DCD     CDOG_IRQHandler                               ;CDOG interrupt
        DCD     SAI1_IRQHandler                               ;SAI1 interrupt
        DCD     SAI2_IRQHandler                               ;SAI1 interrupt
        DCD     SAI3_RX_IRQHandler                            ;SAI3 interrupt
        DCD     SAI3_TX_IRQHandler                            ;SAI3 interrupt
        DCD     SAI4_RX_IRQHandler                            ;SAI4 interrupt
        DCD     SAI4_TX_IRQHandler                            ;SAI4 interrupt
        DCD     SPDIF_IRQHandler                              ;SPDIF interrupt
        DCD     TMPSNS_INT_IRQHandler                         ;TMPSNS interrupt
        DCD     TMPSNS_LOW_HIGH_IRQHandler                    ;TMPSNS low high interrupt
        DCD     TMPSNS_PANIC_IRQHandler                       ;TMPSNS panic interrupt
        DCD     LPSR_LP8_BROWNOUT_IRQHandler                  ;LPSR 1p8 brownout interrupt
        DCD     LPSR_LP0_BROWNOUT_IRQHandler                  ;LPSR 1p0 brownout interrupt
        DCD     ADC1_IRQHandler                               ;ADC1 interrupt
        DCD     ADC2_IRQHandler                               ;ADC2 interrupt
        DCD     USBPHY1_IRQHandler                            ;USBPHY1 interrupt
        DCD     USBPHY2_IRQHandler                            ;USBPHY2 interrupt
        DCD     RDC_IRQHandler                                ;RDC interrupt
        DCD     GPIO13_Combined_0_31_IRQHandler               ;Combined interrupt indication for GPIO13 signal 0 throughout 31
        DCD     Reserved110_IRQHandler                        ;Reserved interrupt
        DCD     DCIC1_IRQHandler                              ;DCIC1 interrupt
        DCD     DCIC2_IRQHandler                              ;DCIC2 interrupt
        DCD     ASRC_IRQHandler                               ;ASRC interrupt
        DCD     FLEXRAM_ECC_IRQHandler                        ;FlexRAM ECC fatal interrupt
        DCD     CM7_GPIO2_3_IRQHandler                        ;CM7_GPIO2,CM7_GPIO3 interrupt
        DCD     GPIO1_Combined_0_15_IRQHandler                ;Combined interrupt indication for GPIO1 signal 0 throughout 15
        DCD     GPIO1_Combined_16_31_IRQHandler               ;Combined interrupt indication for GPIO1 signal 16 throughout 31
        DCD     GPIO2_Combined_0_15_IRQHandler                ;Combined interrupt indication for GPIO2 signal 0 throughout 15
        DCD     GPIO2_Combined_16_31_IRQHandler               ;Combined interrupt indication for GPIO2 signal 16 throughout 31
        DCD     GPIO3_Combined_0_15_IRQHandler                ;Combined interrupt indication for GPIO3 signal 0 throughout 15
        DCD     GPIO3_Combined_16_31_IRQHandler               ;Combined interrupt indication for GPIO3 signal 16 throughout 31
        DCD     GPIO4_Combined_0_15_IRQHandler                ;Combined interrupt indication for GPIO4 signal 0 throughout 15
        DCD     GPIO4_Combined_16_31_IRQHandler               ;Combined interrupt indication for GPIO4 signal 16 throughout 31
        DCD     GPIO5_Combined_0_15_IRQHandler                ;Combined interrupt indication for GPIO5 signal 0 throughout 15
        DCD     GPIO5_Combined_16_31_IRQHandler               ;Combined interrupt indication for GPIO5 signal 16 throughout 31
        DCD     FLEXIO1_IRQHandler                            ;FLEXIO1 interrupt
        DCD     FLEXIO2_IRQHandler                            ;FLEXIO2 interrupt
        DCD     WDOG1_IRQHandler                              ;WDOG1 interrupt
        DCD     RTWDOG3_IRQHandler                            ;RTWDOG3 interrupt
        DCD     EWM_IRQHandler                                ;EWM interrupt
        DCD     OCOTP_READ_FUSE_ERROR_IRQHandler              ;OCOTP read fuse error interrupt
        DCD     OCOTP_READ_DONE_ERROR_IRQHandler              ;OCOTP read fuse done interrupt
        DCD     GPC_IRQHandler                                ;GPC interrupt
        DCD     MUA_IRQHandler                                ;MUA interrupt
        DCD     GPT1_IRQHandler                               ;GPT1 interrupt
        DCD     GPT2_IRQHandler                               ;GPT2 interrupt
        DCD     GPT3_IRQHandler                               ;GPT3 interrupt
        DCD     GPT4_IRQHandler                               ;GPT4 interrupt
        DCD     GPT5_IRQHandler                               ;GPT5 interrupt
        DCD     GPT6_IRQHandler                               ;GPT6 interrupt
        DCD     PWM1_0_IRQHandler                             ;PWM1 capture 0, compare 0, or reload 0 interrupt
        DCD     PWM1_1_IRQHandler                             ;PWM1 capture 1, compare 1, or reload 0 interrupt
        DCD     PWM1_2_IRQHandler                             ;PWM1 capture 2, compare 2, or reload 0 interrupt
        DCD     PWM1_3_IRQHandler                             ;PWM1 capture 3, compare 3, or reload 0 interrupt
        DCD     PWM1_FAULT_IRQHandler                         ;PWM1 fault or reload error interrupt
        DCD     FLEXSPI1_IRQHandler                           ;FlexSPI1 interrupt
        DCD     FLEXSPI2_IRQHandler                           ;FlexSPI2 interrupt
        DCD     SEMC_IRQHandler                               ;SEMC interrupt
        DCD     USDHC1_IRQHandler                             ;USDHC1 interrupt
        DCD     USDHC2_IRQHandler                             ;USDHC2 interrupt
        DCD     USB_OTG2_IRQHandler                           ;USBO2 USB OTG2
        DCD     USB_OTG1_IRQHandler                           ;USBO2 USB OTG1
        DCD     ENET_IRQHandler                               ;ENET interrupt
        DCD     ENET_1588_Timer_IRQHandler                    ;ENET_1588_Timer interrupt
        DCD     ENET_1G_MAC0_Tx_Rx_1_IRQHandler               ;ENET 1G MAC0 transmit/receive 1
        DCD     ENET_1G_MAC0_Tx_Rx_2_IRQHandler               ;ENET 1G MAC0 transmit/receive 2
        DCD     ENET_1G_IRQHandler                            ;ENET 1G interrupt
        DCD     ENET_1G_1588_Timer_IRQHandler                 ;ENET_1G_1588_Timer interrupt
        DCD     XBAR1_IRQ_0_1_IRQHandler                      ;XBAR1 interrupt
        DCD     XBAR1_IRQ_2_3_IRQHandler                      ;XBAR1 interrupt
        DCD     ADC_ETC_IRQ0_IRQHandler                       ;ADCETC IRQ0 interrupt
        DCD     ADC_ETC_IRQ1_IRQHandler                       ;ADCETC IRQ1 interrupt
        DCD     ADC_ETC_IRQ2_IRQHandler                       ;ADCETC IRQ2 interrupt
        DCD     ADC_ETC_IRQ3_IRQHandler                       ;ADCETC IRQ3 interrupt
        DCD     ADC_ETC_ERROR_IRQ_IRQHandler                  ;ADCETC Error IRQ interrupt
        DCD     Reserved166_IRQHandler                        ;Reserved interrupt
        DCD     Reserved167_IRQHandler                        ;Reserved interrupt
        DCD     Reserved168_IRQHandler                        ;Reserved interrupt
        DCD     Reserved169_IRQHandler                        ;Reserved interrupt
        DCD     Reserved170_IRQHandler                        ;Reserved interrupt
        DCD     PIT1_IRQHandler                               ;PIT1 interrupt
        DCD     PIT2_IRQHandler                               ;PIT2 interrupt
        DCD     ACMP1_IRQHandler                              ;ACMP interrupt
        DCD     ACMP2_IRQHandler                              ;ACMP interrupt
        DCD     ACMP3_IRQHandler                              ;ACMP interrupt
        DCD     ACMP4_IRQHandler                              ;ACMP interrupt
        DCD     Reserved177_IRQHandler                        ;Reserved interrupt
        DCD     Reserved178_IRQHandler                        ;Reserved interrupt
        DCD     Reserved179_IRQHandler                        ;Reserved interrupt
        DCD     Reserved180_IRQHandler                        ;Reserved interrupt
        DCD     ENC1_IRQHandler                               ;ENC1 interrupt
        DCD     ENC2_IRQHandler                               ;ENC2 interrupt
        DCD     ENC3_IRQHandler                               ;ENC3 interrupt
        DCD     ENC4_IRQHandler                               ;ENC4 interrupt
        DCD     Reserved185_IRQHandler                        ;Reserved interrupt
        DCD     Reserved186_IRQHandler                        ;Reserved interrupt
        DCD     TMR1_IRQHandler                               ;TMR1 interrupt
        DCD     TMR2_IRQHandler                               ;TMR2 interrupt
        DCD     TMR3_IRQHandler                               ;TMR3 interrupt
        DCD     TMR4_IRQHandler                               ;TMR4 interrupt
        DCD     SEMA4_CP0_IRQHandler                          ;SEMA4 CP0 interrupt
        DCD     SEMA4_CP1_IRQHandler                          ;SEMA4 CP1 interrupt
        DCD     PWM2_0_IRQHandler                             ;PWM2 capture 0, compare 0, or reload 0 interrupt
        DCD     PWM2_1_IRQHandler                             ;PWM2 capture 1, compare 1, or reload 0 interrupt
        DCD     PWM2_2_IRQHandler                             ;PWM2 capture 2, compare 2, or reload 0 interrupt
        DCD     PWM2_3_IRQHandler                             ;PWM2 capture 3, compare 3, or reload 0 interrupt
        DCD     PWM2_FAULT_IRQHandler                         ;PWM2 fault or reload error interrupt
        DCD     PWM3_0_IRQHandler                             ;PWM3 capture 0, compare 0, or reload 0 interrupt
        DCD     PWM3_1_IRQHandler                             ;PWM3 capture 1, compare 1, or reload 0 interrupt
        DCD     PWM3_2_IRQHandler                             ;PWM3 capture 2, compare 2, or reload 0 interrupt
        DCD     PWM3_3_IRQHandler                             ;PWM3 capture 3, compare 3, or reload 0 interrupt
        DCD     PWM3_FAULT_IRQHandler                         ;PWM3 fault or reload error interrupt
        DCD     PWM4_0_IRQHandler                             ;PWM4 capture 0, compare 0, or reload 0 interrupt
        DCD     PWM4_1_IRQHandler                             ;PWM4 capture 1, compare 1, or reload 0 interrupt
        DCD     PWM4_2_IRQHandler                             ;PWM4 capture 2, compare 2, or reload 0 interrupt
        DCD     PWM4_3_IRQHandler                             ;PWM4 capture 3, compare 3, or reload 0 interrupt
        DCD     PWM4_FAULT_IRQHandler                         ;PWM4 fault or reload error interrupt
        DCD     Reserved208_IRQHandler                        ;Reserved interrupt
        DCD     Reserved209_IRQHandler                        ;Reserved interrupt
        DCD     Reserved210_IRQHandler                        ;Reserved interrupt
        DCD     Reserved211_IRQHandler                        ;Reserved interrupt
        DCD     Reserved212_IRQHandler                        ;Reserved interrupt
        DCD     Reserved213_IRQHandler                        ;Reserved interrupt
        DCD     Reserved214_IRQHandler                        ;Reserved interrupt
        DCD     Reserved215_IRQHandler                        ;Reserved interrupt
        DCD     PDM_HWVAD_EVENT_IRQHandler                    ;HWVAD event interrupt
        DCD     PDM_HWVAD_ERROR_IRQHandler                    ;HWVAD error interrupt
        DCD     PDM_EVENT_IRQHandler                          ;PDM event interrupt
        DCD     PDM_ERROR_IRQHandler                          ;PDM error interrupt
        DCD     EMVSIM1_IRQHandler                            ;EMVSIM1 interrupt
        DCD     EMVSIM2_IRQHandler                            ;EMVSIM2 interrupt
        DCD     MECC1_INT_IRQHandler                          ;MECC1 int
        DCD     MECC1_FATAL_INT_IRQHandler                    ;MECC1 fatal int
        DCD     MECC2_INT_IRQHandler                          ;MECC2 int
        DCD     MECC2_FATAL_INT_IRQHandler                    ;MECC2 fatal int
        DCD     XECC_FLEXSPI1_INT_IRQHandler                  ;XECC int
        DCD     XECC_FLEXSPI1_FATAL_INT_IRQHandler            ;XECC fatal int
        DCD     XECC_FLEXSPI2_INT_IRQHandler                  ;XECC int
        DCD     XECC_FLEXSPI2_FATAL_INT_IRQHandler            ;XECC fatal int
        DCD     XECC_SEMC_INT_IRQHandler                      ;XECC int
        DCD     XECC_SEMC_FATAL_INT_IRQHandler                ;XECC fatal int
        DCD     ENET_QOS_IRQHandler                           ;ENET_QOS interrupt
        DCD     ENET_QOS_PMT_IRQHandler                       ;ENET_QOS_PMT interrupt
        DCD     DefaultISR                                    ;234
        DCD     DefaultISR                                    ;235
        DCD     DefaultISR                                    ;236
        DCD     DefaultISR                                    ;237
        DCD     DefaultISR                                    ;238
        DCD     DefaultISR                                    ;239
        DCD     DefaultISR                                    ;240
        DCD     DefaultISR                                    ;241
        DCD     DefaultISR                                    ;242
        DCD     DefaultISR                                    ;243
        DCD     DefaultISR                                    ;244
        DCD     DefaultISR                                    ;245
        DCD     DefaultISR                                    ;246
        DCD     DefaultISR                                    ;247
        DCD     DefaultISR                                    ;248
        DCD     DefaultISR                                    ;249
        DCD     DefaultISR                                    ;250
        DCD     DefaultISR                                    ;251
        DCD     DefaultISR                                    ;252
        DCD     DefaultISR                                    ;253
        DCD     DefaultISR                                    ;254
        DCD     0xFFFFFFFF                                    ; Reserved for user TRIM value
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
        LDR     R0, =SystemInit
        BLX     R0
        CPSIE   I               ; Unmask interrupts
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

        PUBWEAK DMA0_DMA16_IRQHandler
        PUBWEAK DMA0_DMA16_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA0_DMA16_IRQHandler
        LDR     R0, =DMA0_DMA16_DriverIRQHandler
        BX      R0

        PUBWEAK DMA1_DMA17_IRQHandler
        PUBWEAK DMA1_DMA17_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA1_DMA17_IRQHandler
        LDR     R0, =DMA1_DMA17_DriverIRQHandler
        BX      R0

        PUBWEAK DMA2_DMA18_IRQHandler
        PUBWEAK DMA2_DMA18_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA2_DMA18_IRQHandler
        LDR     R0, =DMA2_DMA18_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_DMA19_IRQHandler
        PUBWEAK DMA3_DMA19_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_DMA19_IRQHandler
        LDR     R0, =DMA3_DMA19_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_DMA20_IRQHandler
        PUBWEAK DMA4_DMA20_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_DMA20_IRQHandler
        LDR     R0, =DMA4_DMA20_DriverIRQHandler
        BX      R0

        PUBWEAK DMA5_DMA21_IRQHandler
        PUBWEAK DMA5_DMA21_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA5_DMA21_IRQHandler
        LDR     R0, =DMA5_DMA21_DriverIRQHandler
        BX      R0

        PUBWEAK DMA6_DMA22_IRQHandler
        PUBWEAK DMA6_DMA22_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA6_DMA22_IRQHandler
        LDR     R0, =DMA6_DMA22_DriverIRQHandler
        BX      R0

        PUBWEAK DMA7_DMA23_IRQHandler
        PUBWEAK DMA7_DMA23_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA7_DMA23_IRQHandler
        LDR     R0, =DMA7_DMA23_DriverIRQHandler
        BX      R0

        PUBWEAK DMA8_DMA24_IRQHandler
        PUBWEAK DMA8_DMA24_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA8_DMA24_IRQHandler
        LDR     R0, =DMA8_DMA24_DriverIRQHandler
        BX      R0

        PUBWEAK DMA9_DMA25_IRQHandler
        PUBWEAK DMA9_DMA25_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA9_DMA25_IRQHandler
        LDR     R0, =DMA9_DMA25_DriverIRQHandler
        BX      R0

        PUBWEAK DMA10_DMA26_IRQHandler
        PUBWEAK DMA10_DMA26_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA10_DMA26_IRQHandler
        LDR     R0, =DMA10_DMA26_DriverIRQHandler
        BX      R0

        PUBWEAK DMA11_DMA27_IRQHandler
        PUBWEAK DMA11_DMA27_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA11_DMA27_IRQHandler
        LDR     R0, =DMA11_DMA27_DriverIRQHandler
        BX      R0

        PUBWEAK DMA12_DMA28_IRQHandler
        PUBWEAK DMA12_DMA28_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA12_DMA28_IRQHandler
        LDR     R0, =DMA12_DMA28_DriverIRQHandler
        BX      R0

        PUBWEAK DMA13_DMA29_IRQHandler
        PUBWEAK DMA13_DMA29_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA13_DMA29_IRQHandler
        LDR     R0, =DMA13_DMA29_DriverIRQHandler
        BX      R0

        PUBWEAK DMA14_DMA30_IRQHandler
        PUBWEAK DMA14_DMA30_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA14_DMA30_IRQHandler
        LDR     R0, =DMA14_DMA30_DriverIRQHandler
        BX      R0

        PUBWEAK DMA15_DMA31_IRQHandler
        PUBWEAK DMA15_DMA31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA15_DMA31_IRQHandler
        LDR     R0, =DMA15_DMA31_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_ERROR_IRQHandler
        PUBWEAK DMA_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_ERROR_IRQHandler
        LDR     R0, =DMA_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK CTI_TRIGGER_OUT0_IRQHandler
        PUBWEAK CTI_TRIGGER_OUT1_IRQHandler
        PUBWEAK CORE_IRQHandler
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

        PUBWEAK LPUART3_IRQHandler
        PUBWEAK LPUART3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART3_IRQHandler
        LDR     R0, =LPUART3_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART4_IRQHandler
        PUBWEAK LPUART4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART4_IRQHandler
        LDR     R0, =LPUART4_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART5_IRQHandler
        PUBWEAK LPUART5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART5_IRQHandler
        LDR     R0, =LPUART5_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART6_IRQHandler
        PUBWEAK LPUART6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART6_IRQHandler
        LDR     R0, =LPUART6_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART7_IRQHandler
        PUBWEAK LPUART7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART7_IRQHandler
        LDR     R0, =LPUART7_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART8_IRQHandler
        PUBWEAK LPUART8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART8_IRQHandler
        LDR     R0, =LPUART8_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART9_IRQHandler
        PUBWEAK LPUART9_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART9_IRQHandler
        LDR     R0, =LPUART9_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART10_IRQHandler
        PUBWEAK LPUART10_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART10_IRQHandler
        LDR     R0, =LPUART10_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART11_IRQHandler
        PUBWEAK LPUART11_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART11_IRQHandler
        LDR     R0, =LPUART11_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART12_IRQHandler
        PUBWEAK LPUART12_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART12_IRQHandler
        LDR     R0, =LPUART12_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C1_IRQHandler
        PUBWEAK LPI2C1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C1_IRQHandler
        LDR     R0, =LPI2C1_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C2_IRQHandler
        PUBWEAK LPI2C2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C2_IRQHandler
        LDR     R0, =LPI2C2_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C3_IRQHandler
        PUBWEAK LPI2C3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C3_IRQHandler
        LDR     R0, =LPI2C3_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C4_IRQHandler
        PUBWEAK LPI2C4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C4_IRQHandler
        LDR     R0, =LPI2C4_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C5_IRQHandler
        PUBWEAK LPI2C5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C5_IRQHandler
        LDR     R0, =LPI2C5_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C6_IRQHandler
        PUBWEAK LPI2C6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C6_IRQHandler
        LDR     R0, =LPI2C6_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI1_IRQHandler
        PUBWEAK LPSPI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI1_IRQHandler
        LDR     R0, =LPSPI1_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI2_IRQHandler
        PUBWEAK LPSPI2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI2_IRQHandler
        LDR     R0, =LPSPI2_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI3_IRQHandler
        PUBWEAK LPSPI3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI3_IRQHandler
        LDR     R0, =LPSPI3_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI4_IRQHandler
        PUBWEAK LPSPI4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI4_IRQHandler
        LDR     R0, =LPSPI4_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI5_IRQHandler
        PUBWEAK LPSPI5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI5_IRQHandler
        LDR     R0, =LPSPI5_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI6_IRQHandler
        PUBWEAK LPSPI6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI6_IRQHandler
        LDR     R0, =LPSPI6_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_IRQHandler
        PUBWEAK CAN1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_IRQHandler
        LDR     R0, =CAN1_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_ERROR_IRQHandler
        PUBWEAK CAN1_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_ERROR_IRQHandler
        LDR     R0, =CAN1_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_IRQHandler
        PUBWEAK CAN2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_IRQHandler
        LDR     R0, =CAN2_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_ERROR_IRQHandler
        PUBWEAK CAN2_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_ERROR_IRQHandler
        LDR     R0, =CAN2_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_IRQHandler
        PUBWEAK CAN3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_IRQHandler
        LDR     R0, =CAN3_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_ERROR_IRQHandler
        PUBWEAK CAN3_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_ERROR_IRQHandler
        LDR     R0, =CAN3_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXRAM_IRQHandler
        PUBWEAK KPP_IRQHandler
        PUBWEAK Reserved68_IRQHandler
        PUBWEAK GPR_IRQ_IRQHandler
        PUBWEAK eLCDIF_IRQHandler
        PUBWEAK LCDIFv2_IRQHandler
        PUBWEAK CSI_IRQHandler
        PUBWEAK PXP_IRQHandler
        PUBWEAK MIPI_CSI_IRQHandler
        PUBWEAK MIPI_DSI_IRQHandler
        PUBWEAK GPU2D_IRQHandler
        PUBWEAK GPIO6_Combined_0_15_IRQHandler
        PUBWEAK GPIO6_Combined_16_31_IRQHandler
        PUBWEAK DAC_IRQHandler
        PUBWEAK KEY_MANAGER_IRQHandler
        PUBWEAK WDOG2_IRQHandler
        PUBWEAK SNVS_HP_NON_TZ_IRQHandler
        PUBWEAK SNVS_HP_TZ_IRQHandler
        PUBWEAK SNVS_PULSE_EVENT_IRQHandler
        PUBWEAK CAAM_IRQ0_IRQHandler
        PUBWEAK CAAM_IRQ1_IRQHandler
        PUBWEAK CAAM_IRQ2_IRQHandler
        PUBWEAK CAAM_IRQ3_IRQHandler
        PUBWEAK CAAM_RECORVE_ERRPR_IRQHandler
        PUBWEAK CAAM_RTIC_IRQHandler
        PUBWEAK CDOG_IRQHandler
        PUBWEAK CDOG_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CDOG_IRQHandler
        LDR     R0, =CDOG_DriverIRQHandler
        BX      R0

        PUBWEAK SAI1_IRQHandler
        PUBWEAK SAI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI1_IRQHandler
        LDR     R0, =SAI1_DriverIRQHandler
        BX      R0

        PUBWEAK SAI2_IRQHandler
        PUBWEAK SAI2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI2_IRQHandler
        LDR     R0, =SAI2_DriverIRQHandler
        BX      R0

        PUBWEAK SAI3_RX_IRQHandler
        PUBWEAK SAI3_RX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI3_RX_IRQHandler
        LDR     R0, =SAI3_RX_DriverIRQHandler
        BX      R0

        PUBWEAK SAI3_TX_IRQHandler
        PUBWEAK SAI3_TX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI3_TX_IRQHandler
        LDR     R0, =SAI3_TX_DriverIRQHandler
        BX      R0

        PUBWEAK SAI4_RX_IRQHandler
        PUBWEAK SAI4_RX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI4_RX_IRQHandler
        LDR     R0, =SAI4_RX_DriverIRQHandler
        BX      R0

        PUBWEAK SAI4_TX_IRQHandler
        PUBWEAK SAI4_TX_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI4_TX_IRQHandler
        LDR     R0, =SAI4_TX_DriverIRQHandler
        BX      R0

        PUBWEAK SPDIF_IRQHandler
        PUBWEAK SPDIF_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPDIF_IRQHandler
        LDR     R0, =SPDIF_DriverIRQHandler
        BX      R0

        PUBWEAK TMPSNS_INT_IRQHandler
        PUBWEAK TMPSNS_LOW_HIGH_IRQHandler
        PUBWEAK TMPSNS_PANIC_IRQHandler
        PUBWEAK LPSR_LP8_BROWNOUT_IRQHandler
        PUBWEAK LPSR_LP0_BROWNOUT_IRQHandler
        PUBWEAK ADC1_IRQHandler
        PUBWEAK ADC2_IRQHandler
        PUBWEAK USBPHY1_IRQHandler
        PUBWEAK USBPHY2_IRQHandler
        PUBWEAK RDC_IRQHandler
        PUBWEAK GPIO13_Combined_0_31_IRQHandler
        PUBWEAK Reserved110_IRQHandler
        PUBWEAK DCIC1_IRQHandler
        PUBWEAK DCIC2_IRQHandler
        PUBWEAK ASRC_IRQHandler
        PUBWEAK ASRC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ASRC_IRQHandler
        LDR     R0, =ASRC_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXRAM_ECC_IRQHandler
        PUBWEAK CM7_GPIO2_3_IRQHandler
        PUBWEAK GPIO1_Combined_0_15_IRQHandler
        PUBWEAK GPIO1_Combined_16_31_IRQHandler
        PUBWEAK GPIO2_Combined_0_15_IRQHandler
        PUBWEAK GPIO2_Combined_16_31_IRQHandler
        PUBWEAK GPIO3_Combined_0_15_IRQHandler
        PUBWEAK GPIO3_Combined_16_31_IRQHandler
        PUBWEAK GPIO4_Combined_0_15_IRQHandler
        PUBWEAK GPIO4_Combined_16_31_IRQHandler
        PUBWEAK GPIO5_Combined_0_15_IRQHandler
        PUBWEAK GPIO5_Combined_16_31_IRQHandler
        PUBWEAK FLEXIO1_IRQHandler
        PUBWEAK FLEXIO1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXIO1_IRQHandler
        LDR     R0, =FLEXIO1_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXIO2_IRQHandler
        PUBWEAK FLEXIO2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXIO2_IRQHandler
        LDR     R0, =FLEXIO2_DriverIRQHandler
        BX      R0

        PUBWEAK WDOG1_IRQHandler
        PUBWEAK RTWDOG3_IRQHandler
        PUBWEAK EWM_IRQHandler
        PUBWEAK OCOTP_READ_FUSE_ERROR_IRQHandler
        PUBWEAK OCOTP_READ_DONE_ERROR_IRQHandler
        PUBWEAK GPC_IRQHandler
        PUBWEAK MUA_IRQHandler
        PUBWEAK GPT1_IRQHandler
        PUBWEAK GPT2_IRQHandler
        PUBWEAK GPT3_IRQHandler
        PUBWEAK GPT4_IRQHandler
        PUBWEAK GPT5_IRQHandler
        PUBWEAK GPT6_IRQHandler
        PUBWEAK PWM1_0_IRQHandler
        PUBWEAK PWM1_1_IRQHandler
        PUBWEAK PWM1_2_IRQHandler
        PUBWEAK PWM1_3_IRQHandler
        PUBWEAK PWM1_FAULT_IRQHandler
        PUBWEAK FLEXSPI1_IRQHandler
        PUBWEAK FLEXSPI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXSPI1_IRQHandler
        LDR     R0, =FLEXSPI1_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXSPI2_IRQHandler
        PUBWEAK FLEXSPI2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXSPI2_IRQHandler
        LDR     R0, =FLEXSPI2_DriverIRQHandler
        BX      R0

        PUBWEAK SEMC_IRQHandler
        PUBWEAK USDHC1_IRQHandler
        PUBWEAK USDHC1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USDHC1_IRQHandler
        LDR     R0, =USDHC1_DriverIRQHandler
        BX      R0

        PUBWEAK USDHC2_IRQHandler
        PUBWEAK USDHC2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
USDHC2_IRQHandler
        LDR     R0, =USDHC2_DriverIRQHandler
        BX      R0

        PUBWEAK USB_OTG2_IRQHandler
        PUBWEAK USB_OTG1_IRQHandler
        PUBWEAK ENET_IRQHandler
        PUBWEAK ENET_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_IRQHandler
        LDR     R0, =ENET_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_1588_Timer_IRQHandler
        PUBWEAK ENET_1588_Timer_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_1588_Timer_IRQHandler
        LDR     R0, =ENET_1588_Timer_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_1G_MAC0_Tx_Rx_1_IRQHandler
        PUBWEAK ENET_1G_MAC0_Tx_Rx_1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_1G_MAC0_Tx_Rx_1_IRQHandler
        LDR     R0, =ENET_1G_MAC0_Tx_Rx_1_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_1G_MAC0_Tx_Rx_2_IRQHandler
        PUBWEAK ENET_1G_MAC0_Tx_Rx_2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_1G_MAC0_Tx_Rx_2_IRQHandler
        LDR     R0, =ENET_1G_MAC0_Tx_Rx_2_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_1G_IRQHandler
        PUBWEAK ENET_1G_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_1G_IRQHandler
        LDR     R0, =ENET_1G_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_1G_1588_Timer_IRQHandler
        PUBWEAK ENET_1G_1588_Timer_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_1G_1588_Timer_IRQHandler
        LDR     R0, =ENET_1G_1588_Timer_DriverIRQHandler
        BX      R0

        PUBWEAK XBAR1_IRQ_0_1_IRQHandler
        PUBWEAK XBAR1_IRQ_2_3_IRQHandler
        PUBWEAK ADC_ETC_IRQ0_IRQHandler
        PUBWEAK ADC_ETC_IRQ1_IRQHandler
        PUBWEAK ADC_ETC_IRQ2_IRQHandler
        PUBWEAK ADC_ETC_IRQ3_IRQHandler
        PUBWEAK ADC_ETC_ERROR_IRQ_IRQHandler
        PUBWEAK Reserved166_IRQHandler
        PUBWEAK Reserved167_IRQHandler
        PUBWEAK Reserved168_IRQHandler
        PUBWEAK Reserved169_IRQHandler
        PUBWEAK Reserved170_IRQHandler
        PUBWEAK PIT1_IRQHandler
        PUBWEAK PIT2_IRQHandler
        PUBWEAK ACMP1_IRQHandler
        PUBWEAK ACMP2_IRQHandler
        PUBWEAK ACMP3_IRQHandler
        PUBWEAK ACMP4_IRQHandler
        PUBWEAK Reserved177_IRQHandler
        PUBWEAK Reserved178_IRQHandler
        PUBWEAK Reserved179_IRQHandler
        PUBWEAK Reserved180_IRQHandler
        PUBWEAK ENC1_IRQHandler
        PUBWEAK ENC2_IRQHandler
        PUBWEAK ENC3_IRQHandler
        PUBWEAK ENC4_IRQHandler
        PUBWEAK Reserved185_IRQHandler
        PUBWEAK Reserved186_IRQHandler
        PUBWEAK TMR1_IRQHandler
        PUBWEAK TMR2_IRQHandler
        PUBWEAK TMR3_IRQHandler
        PUBWEAK TMR4_IRQHandler
        PUBWEAK SEMA4_CP0_IRQHandler
        PUBWEAK SEMA4_CP1_IRQHandler
        PUBWEAK PWM2_0_IRQHandler
        PUBWEAK PWM2_1_IRQHandler
        PUBWEAK PWM2_2_IRQHandler
        PUBWEAK PWM2_3_IRQHandler
        PUBWEAK PWM2_FAULT_IRQHandler
        PUBWEAK PWM3_0_IRQHandler
        PUBWEAK PWM3_1_IRQHandler
        PUBWEAK PWM3_2_IRQHandler
        PUBWEAK PWM3_3_IRQHandler
        PUBWEAK PWM3_FAULT_IRQHandler
        PUBWEAK PWM4_0_IRQHandler
        PUBWEAK PWM4_1_IRQHandler
        PUBWEAK PWM4_2_IRQHandler
        PUBWEAK PWM4_3_IRQHandler
        PUBWEAK PWM4_FAULT_IRQHandler
        PUBWEAK Reserved208_IRQHandler
        PUBWEAK Reserved209_IRQHandler
        PUBWEAK Reserved210_IRQHandler
        PUBWEAK Reserved211_IRQHandler
        PUBWEAK Reserved212_IRQHandler
        PUBWEAK Reserved213_IRQHandler
        PUBWEAK Reserved214_IRQHandler
        PUBWEAK Reserved215_IRQHandler
        PUBWEAK PDM_HWVAD_EVENT_IRQHandler
        PUBWEAK PDM_HWVAD_EVENT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_HWVAD_EVENT_IRQHandler
        LDR     R0, =PDM_HWVAD_EVENT_DriverIRQHandler
        BX      R0

        PUBWEAK PDM_HWVAD_ERROR_IRQHandler
        PUBWEAK PDM_HWVAD_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_HWVAD_ERROR_IRQHandler
        LDR     R0, =PDM_HWVAD_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK PDM_EVENT_IRQHandler
        PUBWEAK PDM_EVENT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_EVENT_IRQHandler
        LDR     R0, =PDM_EVENT_DriverIRQHandler
        BX      R0

        PUBWEAK PDM_ERROR_IRQHandler
        PUBWEAK PDM_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_ERROR_IRQHandler
        LDR     R0, =PDM_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK EMVSIM1_IRQHandler
        PUBWEAK EMVSIM2_IRQHandler
        PUBWEAK MECC1_INT_IRQHandler
        PUBWEAK MECC1_FATAL_INT_IRQHandler
        PUBWEAK MECC2_INT_IRQHandler
        PUBWEAK MECC2_FATAL_INT_IRQHandler
        PUBWEAK XECC_FLEXSPI1_INT_IRQHandler
        PUBWEAK XECC_FLEXSPI1_INT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
XECC_FLEXSPI1_INT_IRQHandler
        LDR     R0, =XECC_FLEXSPI1_INT_DriverIRQHandler
        BX      R0

        PUBWEAK XECC_FLEXSPI1_FATAL_INT_IRQHandler
        PUBWEAK XECC_FLEXSPI1_FATAL_INT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
XECC_FLEXSPI1_FATAL_INT_IRQHandler
        LDR     R0, =XECC_FLEXSPI1_FATAL_INT_DriverIRQHandler
        BX      R0

        PUBWEAK XECC_FLEXSPI2_INT_IRQHandler
        PUBWEAK XECC_FLEXSPI2_INT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
XECC_FLEXSPI2_INT_IRQHandler
        LDR     R0, =XECC_FLEXSPI2_INT_DriverIRQHandler
        BX      R0

        PUBWEAK XECC_FLEXSPI2_FATAL_INT_IRQHandler
        PUBWEAK XECC_FLEXSPI2_FATAL_INT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
XECC_FLEXSPI2_FATAL_INT_IRQHandler
        LDR     R0, =XECC_FLEXSPI2_FATAL_INT_DriverIRQHandler
        BX      R0

        PUBWEAK XECC_SEMC_INT_IRQHandler
        PUBWEAK XECC_SEMC_FATAL_INT_IRQHandler
        PUBWEAK ENET_QOS_IRQHandler
        PUBWEAK ENET_QOS_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_QOS_IRQHandler
        LDR     R0, =ENET_QOS_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_QOS_PMT_IRQHandler
        PUBWEAK ENET_QOS_PMT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_QOS_PMT_IRQHandler
        LDR     R0, =ENET_QOS_PMT_DriverIRQHandler
        BX      R0

        PUBWEAK DefaultISR
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA0_DMA16_DriverIRQHandler
DMA1_DMA17_DriverIRQHandler
DMA2_DMA18_DriverIRQHandler
DMA3_DMA19_DriverIRQHandler
DMA4_DMA20_DriverIRQHandler
DMA5_DMA21_DriverIRQHandler
DMA6_DMA22_DriverIRQHandler
DMA7_DMA23_DriverIRQHandler
DMA8_DMA24_DriverIRQHandler
DMA9_DMA25_DriverIRQHandler
DMA10_DMA26_DriverIRQHandler
DMA11_DMA27_DriverIRQHandler
DMA12_DMA28_DriverIRQHandler
DMA13_DMA29_DriverIRQHandler
DMA14_DMA30_DriverIRQHandler
DMA15_DMA31_DriverIRQHandler
DMA_ERROR_DriverIRQHandler
CTI_TRIGGER_OUT0_IRQHandler
CTI_TRIGGER_OUT1_IRQHandler
CORE_IRQHandler
LPUART1_DriverIRQHandler
LPUART2_DriverIRQHandler
LPUART3_DriverIRQHandler
LPUART4_DriverIRQHandler
LPUART5_DriverIRQHandler
LPUART6_DriverIRQHandler
LPUART7_DriverIRQHandler
LPUART8_DriverIRQHandler
LPUART9_DriverIRQHandler
LPUART10_DriverIRQHandler
LPUART11_DriverIRQHandler
LPUART12_DriverIRQHandler
LPI2C1_DriverIRQHandler
LPI2C2_DriverIRQHandler
LPI2C3_DriverIRQHandler
LPI2C4_DriverIRQHandler
LPI2C5_DriverIRQHandler
LPI2C6_DriverIRQHandler
LPSPI1_DriverIRQHandler
LPSPI2_DriverIRQHandler
LPSPI3_DriverIRQHandler
LPSPI4_DriverIRQHandler
LPSPI5_DriverIRQHandler
LPSPI6_DriverIRQHandler
CAN1_DriverIRQHandler
CAN1_ERROR_DriverIRQHandler
CAN2_DriverIRQHandler
CAN2_ERROR_DriverIRQHandler
CAN3_DriverIRQHandler
CAN3_ERROR_DriverIRQHandler
FLEXRAM_IRQHandler
KPP_IRQHandler
Reserved68_IRQHandler
GPR_IRQ_IRQHandler
eLCDIF_IRQHandler
LCDIFv2_IRQHandler
CSI_IRQHandler
PXP_IRQHandler
MIPI_CSI_IRQHandler
MIPI_DSI_IRQHandler
GPU2D_IRQHandler
GPIO6_Combined_0_15_IRQHandler
GPIO6_Combined_16_31_IRQHandler
DAC_IRQHandler
KEY_MANAGER_IRQHandler
WDOG2_IRQHandler
SNVS_HP_NON_TZ_IRQHandler
SNVS_HP_TZ_IRQHandler
SNVS_PULSE_EVENT_IRQHandler
CAAM_IRQ0_IRQHandler
CAAM_IRQ1_IRQHandler
CAAM_IRQ2_IRQHandler
CAAM_IRQ3_IRQHandler
CAAM_RECORVE_ERRPR_IRQHandler
CAAM_RTIC_IRQHandler
CDOG_DriverIRQHandler
SAI1_DriverIRQHandler
SAI2_DriverIRQHandler
SAI3_RX_DriverIRQHandler
SAI3_TX_DriverIRQHandler
SAI4_RX_DriverIRQHandler
SAI4_TX_DriverIRQHandler
SPDIF_DriverIRQHandler
TMPSNS_INT_IRQHandler
TMPSNS_LOW_HIGH_IRQHandler
TMPSNS_PANIC_IRQHandler
LPSR_LP8_BROWNOUT_IRQHandler
LPSR_LP0_BROWNOUT_IRQHandler
ADC1_IRQHandler
ADC2_IRQHandler
USBPHY1_IRQHandler
USBPHY2_IRQHandler
RDC_IRQHandler
GPIO13_Combined_0_31_IRQHandler
Reserved110_IRQHandler
DCIC1_IRQHandler
DCIC2_IRQHandler
ASRC_DriverIRQHandler
FLEXRAM_ECC_IRQHandler
CM7_GPIO2_3_IRQHandler
GPIO1_Combined_0_15_IRQHandler
GPIO1_Combined_16_31_IRQHandler
GPIO2_Combined_0_15_IRQHandler
GPIO2_Combined_16_31_IRQHandler
GPIO3_Combined_0_15_IRQHandler
GPIO3_Combined_16_31_IRQHandler
GPIO4_Combined_0_15_IRQHandler
GPIO4_Combined_16_31_IRQHandler
GPIO5_Combined_0_15_IRQHandler
GPIO5_Combined_16_31_IRQHandler
FLEXIO1_DriverIRQHandler
FLEXIO2_DriverIRQHandler
WDOG1_IRQHandler
RTWDOG3_IRQHandler
EWM_IRQHandler
OCOTP_READ_FUSE_ERROR_IRQHandler
OCOTP_READ_DONE_ERROR_IRQHandler
GPC_IRQHandler
MUA_IRQHandler
GPT1_IRQHandler
GPT2_IRQHandler
GPT3_IRQHandler
GPT4_IRQHandler
GPT5_IRQHandler
GPT6_IRQHandler
PWM1_0_IRQHandler
PWM1_1_IRQHandler
PWM1_2_IRQHandler
PWM1_3_IRQHandler
PWM1_FAULT_IRQHandler
FLEXSPI1_DriverIRQHandler
FLEXSPI2_DriverIRQHandler
SEMC_IRQHandler
USDHC1_DriverIRQHandler
USDHC2_DriverIRQHandler
USB_OTG2_IRQHandler
USB_OTG1_IRQHandler
ENET_DriverIRQHandler
ENET_1588_Timer_DriverIRQHandler
ENET_1G_MAC0_Tx_Rx_1_DriverIRQHandler
ENET_1G_MAC0_Tx_Rx_2_DriverIRQHandler
ENET_1G_DriverIRQHandler
ENET_1G_1588_Timer_DriverIRQHandler
XBAR1_IRQ_0_1_IRQHandler
XBAR1_IRQ_2_3_IRQHandler
ADC_ETC_IRQ0_IRQHandler
ADC_ETC_IRQ1_IRQHandler
ADC_ETC_IRQ2_IRQHandler
ADC_ETC_IRQ3_IRQHandler
ADC_ETC_ERROR_IRQ_IRQHandler
Reserved166_IRQHandler
Reserved167_IRQHandler
Reserved168_IRQHandler
Reserved169_IRQHandler
Reserved170_IRQHandler
PIT1_IRQHandler
PIT2_IRQHandler
ACMP1_IRQHandler
ACMP2_IRQHandler
ACMP3_IRQHandler
ACMP4_IRQHandler
Reserved177_IRQHandler
Reserved178_IRQHandler
Reserved179_IRQHandler
Reserved180_IRQHandler
ENC1_IRQHandler
ENC2_IRQHandler
ENC3_IRQHandler
ENC4_IRQHandler
Reserved185_IRQHandler
Reserved186_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
TMR4_IRQHandler
SEMA4_CP0_IRQHandler
SEMA4_CP1_IRQHandler
PWM2_0_IRQHandler
PWM2_1_IRQHandler
PWM2_2_IRQHandler
PWM2_3_IRQHandler
PWM2_FAULT_IRQHandler
PWM3_0_IRQHandler
PWM3_1_IRQHandler
PWM3_2_IRQHandler
PWM3_3_IRQHandler
PWM3_FAULT_IRQHandler
PWM4_0_IRQHandler
PWM4_1_IRQHandler
PWM4_2_IRQHandler
PWM4_3_IRQHandler
PWM4_FAULT_IRQHandler
Reserved208_IRQHandler
Reserved209_IRQHandler
Reserved210_IRQHandler
Reserved211_IRQHandler
Reserved212_IRQHandler
Reserved213_IRQHandler
Reserved214_IRQHandler
Reserved215_IRQHandler
PDM_HWVAD_EVENT_DriverIRQHandler
PDM_HWVAD_ERROR_DriverIRQHandler
PDM_EVENT_DriverIRQHandler
PDM_ERROR_DriverIRQHandler
EMVSIM1_IRQHandler
EMVSIM2_IRQHandler
MECC1_INT_IRQHandler
MECC1_FATAL_INT_IRQHandler
MECC2_INT_IRQHandler
MECC2_FATAL_INT_IRQHandler
XECC_FLEXSPI1_INT_DriverIRQHandler
XECC_FLEXSPI1_FATAL_INT_DriverIRQHandler
XECC_FLEXSPI2_INT_DriverIRQHandler
XECC_FLEXSPI2_FATAL_INT_DriverIRQHandler
XECC_SEMC_INT_IRQHandler
XECC_SEMC_FATAL_INT_IRQHandler
ENET_QOS_DriverIRQHandler
ENET_QOS_PMT_DriverIRQHandler
DefaultISR
        B DefaultISR

        END
