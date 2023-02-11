; -------------------------------------------------------------------------
;  @file:    startup_MIMXRT1062.s
;  @purpose: CMSIS Cortex-M7 Core Device Startup File
;            MIMXRT1062
;  @version: 1.4
;  @date:    2022-3-25
;  @build:   b220425
; -------------------------------------------------------------------------
;
; Copyright 1997-2016 Freescale Semiconductor, Inc.
; Copyright 2016-2022 NXP
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
        DCD     CTI0_ERROR_IRQHandler                         ;CTI0_Error
        DCD     CTI1_ERROR_IRQHandler                         ;CTI1_Error
        DCD     CORE_IRQHandler                               ;CorePlatform exception IRQ
        DCD     LPUART1_IRQHandler                            ;LPUART1 TX interrupt and RX interrupt
        DCD     LPUART2_IRQHandler                            ;LPUART2 TX interrupt and RX interrupt
        DCD     LPUART3_IRQHandler                            ;LPUART3 TX interrupt and RX interrupt
        DCD     LPUART4_IRQHandler                            ;LPUART4 TX interrupt and RX interrupt
        DCD     LPUART5_IRQHandler                            ;LPUART5 TX interrupt and RX interrupt
        DCD     LPUART6_IRQHandler                            ;LPUART6 TX interrupt and RX interrupt
        DCD     LPUART7_IRQHandler                            ;LPUART7 TX interrupt and RX interrupt
        DCD     LPUART8_IRQHandler                            ;LPUART8 TX interrupt and RX interrupt
        DCD     LPI2C1_IRQHandler                             ;LPI2C1 interrupt
        DCD     LPI2C2_IRQHandler                             ;LPI2C2 interrupt
        DCD     LPI2C3_IRQHandler                             ;LPI2C3 interrupt
        DCD     LPI2C4_IRQHandler                             ;LPI2C4 interrupt
        DCD     LPSPI1_IRQHandler                             ;LPSPI1 single interrupt vector for all sources
        DCD     LPSPI2_IRQHandler                             ;LPSPI2 single interrupt vector for all sources
        DCD     LPSPI3_IRQHandler                             ;LPSPI3 single interrupt vector for all sources
        DCD     LPSPI4_IRQHandler                             ;LPSPI4  single interrupt vector for all sources
        DCD     CAN1_IRQHandler                               ;CAN1 interrupt
        DCD     CAN2_IRQHandler                               ;CAN2 interrupt
        DCD     FLEXRAM_IRQHandler                            ;FlexRAM address out of range Or access hit IRQ
        DCD     KPP_IRQHandler                                ;Keypad nterrupt
        DCD     TSC_DIG_IRQHandler                            ;TSC interrupt
        DCD     GPR_IRQ_IRQHandler                            ;GPR interrupt
        DCD     LCDIF_IRQHandler                              ;LCDIF interrupt
        DCD     CSI_IRQHandler                                ;CSI interrupt
        DCD     PXP_IRQHandler                                ;PXP interrupt
        DCD     WDOG2_IRQHandler                              ;WDOG2 interrupt
        DCD     SNVS_HP_WRAPPER_IRQHandler                    ;SRTC Consolidated Interrupt. Non TZ
        DCD     SNVS_HP_WRAPPER_TZ_IRQHandler                 ;SRTC Security Interrupt. TZ
        DCD     SNVS_LP_WRAPPER_IRQHandler                    ;ON-OFF button press shorter than 5 secs (pulse event)
        DCD     CSU_IRQHandler                                ;CSU interrupt
        DCD     DCP_IRQHandler                                ;DCP_IRQ interrupt
        DCD     DCP_VMI_IRQHandler                            ;DCP_VMI_IRQ interrupt
        DCD     Reserved68_IRQHandler                         ;Reserved interrupt
        DCD     TRNG_IRQHandler                               ;TRNG interrupt
        DCD     SJC_IRQHandler                                ;SJC interrupt
        DCD     BEE_IRQHandler                                ;BEE interrupt
        DCD     SAI1_IRQHandler                               ;SAI1 interrupt
        DCD     SAI2_IRQHandler                               ;SAI1 interrupt
        DCD     SAI3_RX_IRQHandler                            ;SAI3 interrupt
        DCD     SAI3_TX_IRQHandler                            ;SAI3 interrupt
        DCD     SPDIF_IRQHandler                              ;SPDIF interrupt
        DCD     PMU_EVENT_IRQHandler                          ;Brown-out event interrupt
        DCD     Reserved78_IRQHandler                         ;Reserved interrupt
        DCD     TEMP_LOW_HIGH_IRQHandler                      ;TempSensor low/high interrupt
        DCD     TEMP_PANIC_IRQHandler                         ;TempSensor panic interrupt
        DCD     USB_PHY1_IRQHandler                           ;USBPHY (UTMI0), Interrupt
        DCD     USB_PHY2_IRQHandler                           ;USBPHY (UTMI1), Interrupt
        DCD     ADC1_IRQHandler                               ;ADC1 interrupt
        DCD     ADC2_IRQHandler                               ;ADC2 interrupt
        DCD     DCDC_IRQHandler                               ;DCDC interrupt
        DCD     Reserved86_IRQHandler                         ;Reserved interrupt
        DCD     GPIO10_Combined_0_31_IRQHandler               ;Combined interrupt indication for GPIO10 signal 0 throughout 31
        DCD     GPIO1_INT0_IRQHandler                         ;Active HIGH Interrupt from INT0 from GPIO
        DCD     GPIO1_INT1_IRQHandler                         ;Active HIGH Interrupt from INT1 from GPIO
        DCD     GPIO1_INT2_IRQHandler                         ;Active HIGH Interrupt from INT2 from GPIO
        DCD     GPIO1_INT3_IRQHandler                         ;Active HIGH Interrupt from INT3 from GPIO
        DCD     GPIO1_INT4_IRQHandler                         ;Active HIGH Interrupt from INT4 from GPIO
        DCD     GPIO1_INT5_IRQHandler                         ;Active HIGH Interrupt from INT5 from GPIO
        DCD     GPIO1_INT6_IRQHandler                         ;Active HIGH Interrupt from INT6 from GPIO
        DCD     GPIO1_INT7_IRQHandler                         ;Active HIGH Interrupt from INT7 from GPIO
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
        DCD     RTWDOG_IRQHandler                             ;RTWDOG interrupt
        DCD     EWM_IRQHandler                                ;EWM interrupt
        DCD     CCM_1_IRQHandler                              ;CCM IRQ1 interrupt
        DCD     CCM_2_IRQHandler                              ;CCM IRQ2 interrupt
        DCD     GPC_IRQHandler                                ;GPC interrupt
        DCD     SRC_IRQHandler                                ;SRC interrupt
        DCD     Reserved115_IRQHandler                        ;Reserved interrupt
        DCD     GPT1_IRQHandler                               ;GPT1 interrupt
        DCD     GPT2_IRQHandler                               ;GPT2 interrupt
        DCD     PWM1_0_IRQHandler                             ;PWM1 capture 0, compare 0, or reload 0 interrupt
        DCD     PWM1_1_IRQHandler                             ;PWM1 capture 1, compare 1, or reload 0 interrupt
        DCD     PWM1_2_IRQHandler                             ;PWM1 capture 2, compare 2, or reload 0 interrupt
        DCD     PWM1_3_IRQHandler                             ;PWM1 capture 3, compare 3, or reload 0 interrupt
        DCD     PWM1_FAULT_IRQHandler                         ;PWM1 fault or reload error interrupt
        DCD     FLEXSPI2_IRQHandler                           ;FlexSPI2 interrupt
        DCD     FLEXSPI_IRQHandler                            ;FlexSPI0 interrupt
        DCD     SEMC_IRQHandler                               ;SEMC interrupt
        DCD     USDHC1_IRQHandler                             ;USDHC1 interrupt
        DCD     USDHC2_IRQHandler                             ;USDHC2 interrupt
        DCD     USB_OTG2_IRQHandler                           ;USBO2 USB OTG2
        DCD     USB_OTG1_IRQHandler                           ;USBO2 USB OTG1
        DCD     ENET_IRQHandler                               ;ENET interrupt
        DCD     ENET_1588_Timer_IRQHandler                    ;ENET_1588_Timer interrupt
        DCD     XBAR1_IRQ_0_1_IRQHandler                      ;XBAR1 interrupt
        DCD     XBAR1_IRQ_2_3_IRQHandler                      ;XBAR1 interrupt
        DCD     ADC_ETC_IRQ0_IRQHandler                       ;ADCETC IRQ0 interrupt
        DCD     ADC_ETC_IRQ1_IRQHandler                       ;ADCETC IRQ1 interrupt
        DCD     ADC_ETC_IRQ2_IRQHandler                       ;ADCETC IRQ2 interrupt
        DCD     ADC_ETC_ERROR_IRQ_IRQHandler                  ;ADCETC Error IRQ interrupt
        DCD     PIT_IRQHandler                                ;PIT interrupt
        DCD     ACMP1_IRQHandler                              ;ACMP interrupt
        DCD     ACMP2_IRQHandler                              ;ACMP interrupt
        DCD     ACMP3_IRQHandler                              ;ACMP interrupt
        DCD     ACMP4_IRQHandler                              ;ACMP interrupt
        DCD     Reserved143_IRQHandler                        ;Reserved interrupt
        DCD     Reserved144_IRQHandler                        ;Reserved interrupt
        DCD     ENC1_IRQHandler                               ;ENC1 interrupt
        DCD     ENC2_IRQHandler                               ;ENC2 interrupt
        DCD     ENC3_IRQHandler                               ;ENC3 interrupt
        DCD     ENC4_IRQHandler                               ;ENC4 interrupt
        DCD     TMR1_IRQHandler                               ;TMR1 interrupt
        DCD     TMR2_IRQHandler                               ;TMR2 interrupt
        DCD     TMR3_IRQHandler                               ;TMR3 interrupt
        DCD     TMR4_IRQHandler                               ;TMR4 interrupt
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
        DCD     ENET2_IRQHandler                              ;ENET2 interrupt
        DCD     ENET2_1588_Timer_IRQHandler                   ;ENET2_1588_Timer interrupt
        DCD     CAN3_IRQHandler                               ;CAN3 interrupt
        DCD     Reserved171_IRQHandler                        ;Reserved interrupt
        DCD     FLEXIO3_IRQHandler                            ;FLEXIO3 interrupt
        DCD     GPIO6_7_8_9_IRQHandler                        ;GPIO6, GPIO7, GPIO8, GPIO9 interrupt
        DCD     DefaultISR                                    ;174
        DCD     DefaultISR                                    ;175
        DCD     DefaultISR                                    ;176
        DCD     DefaultISR                                    ;177
        DCD     DefaultISR                                    ;178
        DCD     DefaultISR                                    ;179
        DCD     DefaultISR                                    ;180
        DCD     DefaultISR                                    ;181
        DCD     DefaultISR                                    ;182
        DCD     DefaultISR                                    ;183
        DCD     DefaultISR                                    ;184
        DCD     DefaultISR                                    ;185
        DCD     DefaultISR                                    ;186
        DCD     DefaultISR                                    ;187
        DCD     DefaultISR                                    ;188
        DCD     DefaultISR                                    ;189
        DCD     DefaultISR                                    ;190
        DCD     DefaultISR                                    ;191
        DCD     DefaultISR                                    ;192
        DCD     DefaultISR                                    ;193
        DCD     DefaultISR                                    ;194
        DCD     DefaultISR                                    ;195
        DCD     DefaultISR                                    ;196
        DCD     DefaultISR                                    ;197
        DCD     DefaultISR                                    ;198
        DCD     DefaultISR                                    ;199
        DCD     DefaultISR                                    ;200
        DCD     DefaultISR                                    ;201
        DCD     DefaultISR                                    ;202
        DCD     DefaultISR                                    ;203
        DCD     DefaultISR                                    ;204
        DCD     DefaultISR                                    ;205
        DCD     DefaultISR                                    ;206
        DCD     DefaultISR                                    ;207
        DCD     DefaultISR                                    ;208
        DCD     DefaultISR                                    ;209
        DCD     DefaultISR                                    ;210
        DCD     DefaultISR                                    ;211
        DCD     DefaultISR                                    ;212
        DCD     DefaultISR                                    ;213
        DCD     DefaultISR                                    ;214
        DCD     DefaultISR                                    ;215
        DCD     DefaultISR                                    ;216
        DCD     DefaultISR                                    ;217
        DCD     DefaultISR                                    ;218
        DCD     DefaultISR                                    ;219
        DCD     DefaultISR                                    ;220
        DCD     DefaultISR                                    ;221
        DCD     DefaultISR                                    ;222
        DCD     DefaultISR                                    ;223
        DCD     DefaultISR                                    ;224
        DCD     DefaultISR                                    ;225
        DCD     DefaultISR                                    ;226
        DCD     DefaultISR                                    ;227
        DCD     DefaultISR                                    ;228
        DCD     DefaultISR                                    ;229
        DCD     DefaultISR                                    ;230
        DCD     DefaultISR                                    ;231
        DCD     DefaultISR                                    ;232
        DCD     DefaultISR                                    ;233
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

        PUBWEAK CTI0_ERROR_IRQHandler
        PUBWEAK CTI1_ERROR_IRQHandler
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

        PUBWEAK CAN1_IRQHandler
        PUBWEAK CAN1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_IRQHandler
        LDR     R0, =CAN1_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_IRQHandler
        PUBWEAK CAN2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_IRQHandler
        LDR     R0, =CAN2_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXRAM_IRQHandler
        PUBWEAK KPP_IRQHandler
        PUBWEAK TSC_DIG_IRQHandler
        PUBWEAK GPR_IRQ_IRQHandler
        PUBWEAK LCDIF_IRQHandler
        PUBWEAK CSI_IRQHandler
        PUBWEAK PXP_IRQHandler
        PUBWEAK WDOG2_IRQHandler
        PUBWEAK SNVS_HP_WRAPPER_IRQHandler
        PUBWEAK SNVS_HP_WRAPPER_TZ_IRQHandler
        PUBWEAK SNVS_LP_WRAPPER_IRQHandler
        PUBWEAK CSU_IRQHandler
        PUBWEAK DCP_IRQHandler
        PUBWEAK DCP_VMI_IRQHandler
        PUBWEAK Reserved68_IRQHandler
        PUBWEAK TRNG_IRQHandler
        PUBWEAK SJC_IRQHandler
        PUBWEAK BEE_IRQHandler
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

        PUBWEAK SPDIF_IRQHandler
        PUBWEAK SPDIF_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPDIF_IRQHandler
        LDR     R0, =SPDIF_DriverIRQHandler
        BX      R0

        PUBWEAK PMU_EVENT_IRQHandler
        PUBWEAK Reserved78_IRQHandler
        PUBWEAK TEMP_LOW_HIGH_IRQHandler
        PUBWEAK TEMP_PANIC_IRQHandler
        PUBWEAK USB_PHY1_IRQHandler
        PUBWEAK USB_PHY2_IRQHandler
        PUBWEAK ADC1_IRQHandler
        PUBWEAK ADC2_IRQHandler
        PUBWEAK DCDC_IRQHandler
        PUBWEAK Reserved86_IRQHandler
        PUBWEAK GPIO10_Combined_0_31_IRQHandler
        PUBWEAK GPIO1_INT0_IRQHandler
        PUBWEAK GPIO1_INT1_IRQHandler
        PUBWEAK GPIO1_INT2_IRQHandler
        PUBWEAK GPIO1_INT3_IRQHandler
        PUBWEAK GPIO1_INT4_IRQHandler
        PUBWEAK GPIO1_INT5_IRQHandler
        PUBWEAK GPIO1_INT6_IRQHandler
        PUBWEAK GPIO1_INT7_IRQHandler
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
        PUBWEAK RTWDOG_IRQHandler
        PUBWEAK EWM_IRQHandler
        PUBWEAK CCM_1_IRQHandler
        PUBWEAK CCM_2_IRQHandler
        PUBWEAK GPC_IRQHandler
        PUBWEAK SRC_IRQHandler
        PUBWEAK Reserved115_IRQHandler
        PUBWEAK GPT1_IRQHandler
        PUBWEAK GPT2_IRQHandler
        PUBWEAK PWM1_0_IRQHandler
        PUBWEAK PWM1_1_IRQHandler
        PUBWEAK PWM1_2_IRQHandler
        PUBWEAK PWM1_3_IRQHandler
        PUBWEAK PWM1_FAULT_IRQHandler
        PUBWEAK FLEXSPI2_IRQHandler
        PUBWEAK FLEXSPI2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXSPI2_IRQHandler
        LDR     R0, =FLEXSPI2_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXSPI_IRQHandler
        PUBWEAK FLEXSPI_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXSPI_IRQHandler
        LDR     R0, =FLEXSPI_DriverIRQHandler
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

        PUBWEAK XBAR1_IRQ_0_1_IRQHandler
        PUBWEAK XBAR1_IRQ_2_3_IRQHandler
        PUBWEAK ADC_ETC_IRQ0_IRQHandler
        PUBWEAK ADC_ETC_IRQ1_IRQHandler
        PUBWEAK ADC_ETC_IRQ2_IRQHandler
        PUBWEAK ADC_ETC_ERROR_IRQ_IRQHandler
        PUBWEAK PIT_IRQHandler
        PUBWEAK ACMP1_IRQHandler
        PUBWEAK ACMP2_IRQHandler
        PUBWEAK ACMP3_IRQHandler
        PUBWEAK ACMP4_IRQHandler
        PUBWEAK Reserved143_IRQHandler
        PUBWEAK Reserved144_IRQHandler
        PUBWEAK ENC1_IRQHandler
        PUBWEAK ENC2_IRQHandler
        PUBWEAK ENC3_IRQHandler
        PUBWEAK ENC4_IRQHandler
        PUBWEAK TMR1_IRQHandler
        PUBWEAK TMR2_IRQHandler
        PUBWEAK TMR3_IRQHandler
        PUBWEAK TMR4_IRQHandler
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
        PUBWEAK ENET2_IRQHandler
        PUBWEAK ENET2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET2_IRQHandler
        LDR     R0, =ENET2_DriverIRQHandler
        BX      R0

        PUBWEAK ENET2_1588_Timer_IRQHandler
        PUBWEAK ENET2_1588_Timer_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET2_1588_Timer_IRQHandler
        LDR     R0, =ENET2_1588_Timer_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_IRQHandler
        PUBWEAK CAN3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_IRQHandler
        LDR     R0, =CAN3_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved171_IRQHandler
        PUBWEAK FLEXIO3_IRQHandler
        PUBWEAK FLEXIO3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXIO3_IRQHandler
        LDR     R0, =FLEXIO3_DriverIRQHandler
        BX      R0

        PUBWEAK GPIO6_7_8_9_IRQHandler
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
CTI0_ERROR_IRQHandler
CTI1_ERROR_IRQHandler
CORE_IRQHandler
LPUART1_DriverIRQHandler
LPUART2_DriverIRQHandler
LPUART3_DriverIRQHandler
LPUART4_DriverIRQHandler
LPUART5_DriverIRQHandler
LPUART6_DriverIRQHandler
LPUART7_DriverIRQHandler
LPUART8_DriverIRQHandler
LPI2C1_DriverIRQHandler
LPI2C2_DriverIRQHandler
LPI2C3_DriverIRQHandler
LPI2C4_DriverIRQHandler
LPSPI1_DriverIRQHandler
LPSPI2_DriverIRQHandler
LPSPI3_DriverIRQHandler
LPSPI4_DriverIRQHandler
CAN1_DriverIRQHandler
CAN2_DriverIRQHandler
FLEXRAM_IRQHandler
KPP_IRQHandler
TSC_DIG_IRQHandler
GPR_IRQ_IRQHandler
LCDIF_IRQHandler
CSI_IRQHandler
PXP_IRQHandler
WDOG2_IRQHandler
SNVS_HP_WRAPPER_IRQHandler
SNVS_HP_WRAPPER_TZ_IRQHandler
SNVS_LP_WRAPPER_IRQHandler
CSU_IRQHandler
DCP_IRQHandler
DCP_VMI_IRQHandler
Reserved68_IRQHandler
TRNG_IRQHandler
SJC_IRQHandler
BEE_IRQHandler
SAI1_DriverIRQHandler
SAI2_DriverIRQHandler
SAI3_RX_DriverIRQHandler
SAI3_TX_DriverIRQHandler
SPDIF_DriverIRQHandler
PMU_EVENT_IRQHandler
Reserved78_IRQHandler
TEMP_LOW_HIGH_IRQHandler
TEMP_PANIC_IRQHandler
USB_PHY1_IRQHandler
USB_PHY2_IRQHandler
ADC1_IRQHandler
ADC2_IRQHandler
DCDC_IRQHandler
Reserved86_IRQHandler
GPIO10_Combined_0_31_IRQHandler
GPIO1_INT0_IRQHandler
GPIO1_INT1_IRQHandler
GPIO1_INT2_IRQHandler
GPIO1_INT3_IRQHandler
GPIO1_INT4_IRQHandler
GPIO1_INT5_IRQHandler
GPIO1_INT6_IRQHandler
GPIO1_INT7_IRQHandler
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
RTWDOG_IRQHandler
EWM_IRQHandler
CCM_1_IRQHandler
CCM_2_IRQHandler
GPC_IRQHandler
SRC_IRQHandler
Reserved115_IRQHandler
GPT1_IRQHandler
GPT2_IRQHandler
PWM1_0_IRQHandler
PWM1_1_IRQHandler
PWM1_2_IRQHandler
PWM1_3_IRQHandler
PWM1_FAULT_IRQHandler
FLEXSPI2_DriverIRQHandler
FLEXSPI_DriverIRQHandler
SEMC_IRQHandler
USDHC1_DriverIRQHandler
USDHC2_DriverIRQHandler
USB_OTG2_IRQHandler
USB_OTG1_IRQHandler
ENET_DriverIRQHandler
ENET_1588_Timer_DriverIRQHandler
XBAR1_IRQ_0_1_IRQHandler
XBAR1_IRQ_2_3_IRQHandler
ADC_ETC_IRQ0_IRQHandler
ADC_ETC_IRQ1_IRQHandler
ADC_ETC_IRQ2_IRQHandler
ADC_ETC_ERROR_IRQ_IRQHandler
PIT_IRQHandler
ACMP1_IRQHandler
ACMP2_IRQHandler
ACMP3_IRQHandler
ACMP4_IRQHandler
Reserved143_IRQHandler
Reserved144_IRQHandler
ENC1_IRQHandler
ENC2_IRQHandler
ENC3_IRQHandler
ENC4_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
TMR4_IRQHandler
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
ENET2_DriverIRQHandler
ENET2_1588_Timer_DriverIRQHandler
CAN3_DriverIRQHandler
Reserved171_IRQHandler
FLEXIO3_DriverIRQHandler
GPIO6_7_8_9_IRQHandler
DefaultISR
        B DefaultISR

        END
