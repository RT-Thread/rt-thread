; * -------------------------------------------------------------------------
; *  @file:    startup_MIMXRT1061.s
; *  @purpose: CMSIS Cortex-M7 Core Device Startup File
; *            MIMXRT1061
; *  @version: 1.1
; *  @date:    2018-11-27
; *  @build:   b190124
; * -------------------------------------------------------------------------
; *
; * Copyright 1997-2016 Freescale Semiconductor, Inc.
; * Copyright 2016-2019 NXP
; * All rights reserved.
; *
; * SPDX-License-Identifier: BSD-3-Clause
; *
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
                IMPORT  |Image$$ARM_LIB_STACK$$ZI$$Limit|

__Vectors       DCD     |Image$$ARM_LIB_STACK$$ZI$$Limit| ; Top of Stack
                DCD     Reset_Handler  ; Reset Handler
                DCD     NMI_Handler                         ;NMI Handler
                DCD     HardFault_Handler                   ;Hard Fault Handler
                DCD     MemManage_Handler                   ;MPU Fault Handler
                DCD     BusFault_Handler                    ;Bus Fault Handler
                DCD     UsageFault_Handler                  ;Usage Fault Handler
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     SVC_Handler                         ;SVCall Handler
                DCD     DebugMon_Handler                    ;Debug Monitor Handler
                DCD     0                                   ;Reserved
                DCD     PendSV_Handler                      ;PendSV Handler
                DCD     SysTick_Handler                     ;SysTick Handler

                                                            ;External Interrupts
                DCD     DMA0_DMA16_IRQHandler               ;DMA channel 0/16 transfer complete
                DCD     DMA1_DMA17_IRQHandler               ;DMA channel 1/17 transfer complete
                DCD     DMA2_DMA18_IRQHandler               ;DMA channel 2/18 transfer complete
                DCD     DMA3_DMA19_IRQHandler               ;DMA channel 3/19 transfer complete
                DCD     DMA4_DMA20_IRQHandler               ;DMA channel 4/20 transfer complete
                DCD     DMA5_DMA21_IRQHandler               ;DMA channel 5/21 transfer complete
                DCD     DMA6_DMA22_IRQHandler               ;DMA channel 6/22 transfer complete
                DCD     DMA7_DMA23_IRQHandler               ;DMA channel 7/23 transfer complete
                DCD     DMA8_DMA24_IRQHandler               ;DMA channel 8/24 transfer complete
                DCD     DMA9_DMA25_IRQHandler               ;DMA channel 9/25 transfer complete
                DCD     DMA10_DMA26_IRQHandler              ;DMA channel 10/26 transfer complete
                DCD     DMA11_DMA27_IRQHandler              ;DMA channel 11/27 transfer complete
                DCD     DMA12_DMA28_IRQHandler              ;DMA channel 12/28 transfer complete
                DCD     DMA13_DMA29_IRQHandler              ;DMA channel 13/29 transfer complete
                DCD     DMA14_DMA30_IRQHandler              ;DMA channel 14/30 transfer complete
                DCD     DMA15_DMA31_IRQHandler              ;DMA channel 15/31 transfer complete
                DCD     DMA_ERROR_IRQHandler                ;DMA error interrupt channels 0-15 / 16-31
                DCD     CTI0_ERROR_IRQHandler               ;CTI0_Error
                DCD     CTI1_ERROR_IRQHandler               ;CTI1_Error
                DCD     CORE_IRQHandler                     ;CorePlatform exception IRQ
                DCD     LPUART1_IRQHandler                  ;LPUART1 TX interrupt and RX interrupt
                DCD     LPUART2_IRQHandler                  ;LPUART2 TX interrupt and RX interrupt
                DCD     LPUART3_IRQHandler                  ;LPUART3 TX interrupt and RX interrupt
                DCD     LPUART4_IRQHandler                  ;LPUART4 TX interrupt and RX interrupt
                DCD     LPUART5_IRQHandler                  ;LPUART5 TX interrupt and RX interrupt
                DCD     LPUART6_IRQHandler                  ;LPUART6 TX interrupt and RX interrupt
                DCD     LPUART7_IRQHandler                  ;LPUART7 TX interrupt and RX interrupt
                DCD     LPUART8_IRQHandler                  ;LPUART8 TX interrupt and RX interrupt
                DCD     LPI2C1_IRQHandler                   ;LPI2C1 interrupt
                DCD     LPI2C2_IRQHandler                   ;LPI2C2 interrupt
                DCD     LPI2C3_IRQHandler                   ;LPI2C3 interrupt
                DCD     LPI2C4_IRQHandler                   ;LPI2C4 interrupt
                DCD     LPSPI1_IRQHandler                   ;LPSPI1 single interrupt vector for all sources
                DCD     LPSPI2_IRQHandler                   ;LPSPI2 single interrupt vector for all sources
                DCD     LPSPI3_IRQHandler                   ;LPSPI3 single interrupt vector for all sources
                DCD     LPSPI4_IRQHandler                   ;LPSPI4  single interrupt vector for all sources
                DCD     CAN1_IRQHandler                     ;CAN1 interrupt
                DCD     CAN2_IRQHandler                     ;CAN2 interrupt
                DCD     FLEXRAM_IRQHandler                  ;FlexRAM address out of range Or access hit IRQ
                DCD     KPP_IRQHandler                      ;Keypad nterrupt
                DCD     TSC_DIG_IRQHandler                  ;TSC interrupt
                DCD     GPR_IRQ_IRQHandler                  ;GPR interrupt
                DCD     Reserved58_IRQHandler               ;Reserved interrupt
                DCD     Reserved59_IRQHandler               ;Reserved interrupt
                DCD     Reserved60_IRQHandler               ;Reserved interrupt
                DCD     WDOG2_IRQHandler                    ;WDOG2 interrupt
                DCD     SNVS_HP_WRAPPER_IRQHandler          ;SRTC Consolidated Interrupt. Non TZ
                DCD     SNVS_HP_WRAPPER_TZ_IRQHandler       ;SRTC Security Interrupt. TZ
                DCD     SNVS_LP_WRAPPER_IRQHandler          ;ON-OFF button press shorter than 5 secs (pulse event)
                DCD     CSU_IRQHandler                      ;CSU interrupt
                DCD     DCP_IRQHandler                      ;DCP_IRQ interrupt
                DCD     DCP_VMI_IRQHandler                  ;DCP_VMI_IRQ interrupt
                DCD     Reserved68_IRQHandler               ;Reserved interrupt
                DCD     TRNG_IRQHandler                     ;TRNG interrupt
                DCD     SJC_IRQHandler                      ;SJC interrupt
                DCD     BEE_IRQHandler                      ;BEE interrupt
                DCD     SAI1_IRQHandler                     ;SAI1 interrupt
                DCD     SAI2_IRQHandler                     ;SAI1 interrupt
                DCD     SAI3_RX_IRQHandler                  ;SAI3 interrupt
                DCD     SAI3_TX_IRQHandler                  ;SAI3 interrupt
                DCD     SPDIF_IRQHandler                    ;SPDIF interrupt
                DCD     PMU_EVENT_IRQHandler                ;Brown-out event interrupt
                DCD     Reserved78_IRQHandler               ;Reserved interrupt
                DCD     TEMP_LOW_HIGH_IRQHandler            ;TempSensor low/high interrupt
                DCD     TEMP_PANIC_IRQHandler               ;TempSensor panic interrupt
                DCD     USB_PHY1_IRQHandler                 ;USBPHY (UTMI0), Interrupt
                DCD     USB_PHY2_IRQHandler                 ;USBPHY (UTMI1), Interrupt
                DCD     ADC1_IRQHandler                     ;ADC1 interrupt
                DCD     ADC2_IRQHandler                     ;ADC2 interrupt
                DCD     DCDC_IRQHandler                     ;DCDC interrupt
                DCD     Reserved86_IRQHandler               ;Reserved interrupt
                DCD     Reserved87_IRQHandler               ;Reserved interrupt
                DCD     GPIO1_INT0_IRQHandler               ;Active HIGH Interrupt from INT0 from GPIO
                DCD     GPIO1_INT1_IRQHandler               ;Active HIGH Interrupt from INT1 from GPIO
                DCD     GPIO1_INT2_IRQHandler               ;Active HIGH Interrupt from INT2 from GPIO
                DCD     GPIO1_INT3_IRQHandler               ;Active HIGH Interrupt from INT3 from GPIO
                DCD     GPIO1_INT4_IRQHandler               ;Active HIGH Interrupt from INT4 from GPIO
                DCD     GPIO1_INT5_IRQHandler               ;Active HIGH Interrupt from INT5 from GPIO
                DCD     GPIO1_INT6_IRQHandler               ;Active HIGH Interrupt from INT6 from GPIO
                DCD     GPIO1_INT7_IRQHandler               ;Active HIGH Interrupt from INT7 from GPIO
                DCD     GPIO1_Combined_0_15_IRQHandler      ;Combined interrupt indication for GPIO1 signal 0 throughout 15
                DCD     GPIO1_Combined_16_31_IRQHandler     ;Combined interrupt indication for GPIO1 signal 16 throughout 31
                DCD     GPIO2_Combined_0_15_IRQHandler      ;Combined interrupt indication for GPIO2 signal 0 throughout 15
                DCD     GPIO2_Combined_16_31_IRQHandler     ;Combined interrupt indication for GPIO2 signal 16 throughout 31
                DCD     GPIO3_Combined_0_15_IRQHandler      ;Combined interrupt indication for GPIO3 signal 0 throughout 15
                DCD     GPIO3_Combined_16_31_IRQHandler     ;Combined interrupt indication for GPIO3 signal 16 throughout 31
                DCD     GPIO4_Combined_0_15_IRQHandler      ;Combined interrupt indication for GPIO4 signal 0 throughout 15
                DCD     GPIO4_Combined_16_31_IRQHandler     ;Combined interrupt indication for GPIO4 signal 16 throughout 31
                DCD     GPIO5_Combined_0_15_IRQHandler      ;Combined interrupt indication for GPIO5 signal 0 throughout 15
                DCD     GPIO5_Combined_16_31_IRQHandler     ;Combined interrupt indication for GPIO5 signal 16 throughout 31
                DCD     FLEXIO1_IRQHandler                  ;FLEXIO1 interrupt
                DCD     FLEXIO2_IRQHandler                  ;FLEXIO2 interrupt
                DCD     WDOG1_IRQHandler                    ;WDOG1 interrupt
                DCD     RTWDOG_IRQHandler                   ;RTWDOG interrupt
                DCD     EWM_IRQHandler                      ;EWM interrupt
                DCD     CCM_1_IRQHandler                    ;CCM IRQ1 interrupt
                DCD     CCM_2_IRQHandler                    ;CCM IRQ2 interrupt
                DCD     GPC_IRQHandler                      ;GPC interrupt
                DCD     SRC_IRQHandler                      ;SRC interrupt
                DCD     Reserved115_IRQHandler              ;Reserved interrupt
                DCD     GPT1_IRQHandler                     ;GPT1 interrupt
                DCD     GPT2_IRQHandler                     ;GPT2 interrupt
                DCD     PWM1_0_IRQHandler                   ;PWM1 capture 0, compare 0, or reload 0 interrupt
                DCD     PWM1_1_IRQHandler                   ;PWM1 capture 1, compare 1, or reload 0 interrupt
                DCD     PWM1_2_IRQHandler                   ;PWM1 capture 2, compare 2, or reload 0 interrupt
                DCD     PWM1_3_IRQHandler                   ;PWM1 capture 3, compare 3, or reload 0 interrupt
                DCD     PWM1_FAULT_IRQHandler               ;PWM1 fault or reload error interrupt
                DCD     FLEXSPI2_IRQHandler                 ;FlexSPI2 interrupt
                DCD     FLEXSPI_IRQHandler                  ;FlexSPI0 interrupt
                DCD     SEMC_IRQHandler                     ;Reserved interrupt
                DCD     USDHC1_IRQHandler                   ;USDHC1 interrupt
                DCD     USDHC2_IRQHandler                   ;USDHC2 interrupt
                DCD     USB_OTG2_IRQHandler                 ;USBO2 USB OTG2
                DCD     USB_OTG1_IRQHandler                 ;USBO2 USB OTG1
                DCD     ENET_IRQHandler                     ;ENET interrupt
                DCD     ENET_1588_Timer_IRQHandler          ;ENET_1588_Timer interrupt
                DCD     XBAR1_IRQ_0_1_IRQHandler            ;XBAR1 interrupt
                DCD     XBAR1_IRQ_2_3_IRQHandler            ;XBAR1 interrupt
                DCD     ADC_ETC_IRQ0_IRQHandler             ;ADCETC IRQ0 interrupt
                DCD     ADC_ETC_IRQ1_IRQHandler             ;ADCETC IRQ1 interrupt
                DCD     ADC_ETC_IRQ2_IRQHandler             ;ADCETC IRQ2 interrupt
                DCD     ADC_ETC_ERROR_IRQ_IRQHandler        ;ADCETC Error IRQ interrupt
                DCD     PIT_IRQHandler                      ;PIT interrupt
                DCD     ACMP1_IRQHandler                    ;ACMP interrupt
                DCD     ACMP2_IRQHandler                    ;ACMP interrupt
                DCD     ACMP3_IRQHandler                    ;ACMP interrupt
                DCD     ACMP4_IRQHandler                    ;ACMP interrupt
                DCD     Reserved143_IRQHandler              ;Reserved interrupt
                DCD     Reserved144_IRQHandler              ;Reserved interrupt
                DCD     ENC1_IRQHandler                     ;ENC1 interrupt
                DCD     ENC2_IRQHandler                     ;ENC2 interrupt
                DCD     ENC3_IRQHandler                     ;ENC3 interrupt
                DCD     ENC4_IRQHandler                     ;ENC4 interrupt
                DCD     TMR1_IRQHandler                     ;TMR1 interrupt
                DCD     TMR2_IRQHandler                     ;TMR2 interrupt
                DCD     TMR3_IRQHandler                     ;TMR3 interrupt
                DCD     TMR4_IRQHandler                     ;TMR4 interrupt
                DCD     PWM2_0_IRQHandler                   ;PWM2 capture 0, compare 0, or reload 0 interrupt
                DCD     PWM2_1_IRQHandler                   ;PWM2 capture 1, compare 1, or reload 0 interrupt
                DCD     PWM2_2_IRQHandler                   ;PWM2 capture 2, compare 2, or reload 0 interrupt
                DCD     PWM2_3_IRQHandler                   ;PWM2 capture 3, compare 3, or reload 0 interrupt
                DCD     PWM2_FAULT_IRQHandler               ;PWM2 fault or reload error interrupt
                DCD     PWM3_0_IRQHandler                   ;PWM3 capture 0, compare 0, or reload 0 interrupt
                DCD     PWM3_1_IRQHandler                   ;PWM3 capture 1, compare 1, or reload 0 interrupt
                DCD     PWM3_2_IRQHandler                   ;PWM3 capture 2, compare 2, or reload 0 interrupt
                DCD     PWM3_3_IRQHandler                   ;PWM3 capture 3, compare 3, or reload 0 interrupt
                DCD     PWM3_FAULT_IRQHandler               ;PWM3 fault or reload error interrupt
                DCD     PWM4_0_IRQHandler                   ;PWM4 capture 0, compare 0, or reload 0 interrupt
                DCD     PWM4_1_IRQHandler                   ;PWM4 capture 1, compare 1, or reload 0 interrupt
                DCD     PWM4_2_IRQHandler                   ;PWM4 capture 2, compare 2, or reload 0 interrupt
                DCD     PWM4_3_IRQHandler                   ;PWM4 capture 3, compare 3, or reload 0 interrupt
                DCD     PWM4_FAULT_IRQHandler               ;PWM4 fault or reload error interrupt
                DCD     ENET2_IRQHandler                    ;ENET2 interrupt
                DCD     ENET2_1588_Timer_IRQHandler         ;ENET2_1588_Timer interrupt
                DCD     CAN3_IRQHandler                     ;CAN3 interrupt
                DCD     Reserved171_IRQHandler              ;Reserved interrupt
                DCD     FLEXIO3_IRQHandler                  ;FLEXIO3 interrupt
                DCD     GPIO6_7_8_9_IRQHandler              ;GPIO6, GPIO7, GPIO8, GPIO9 interrupt
                DCD     DefaultISR                          ;174
                DCD     DefaultISR                          ;175
                DCD     DefaultISR                          ;176
                DCD     DefaultISR                          ;177
                DCD     DefaultISR                          ;178
                DCD     DefaultISR                          ;179
                DCD     DefaultISR                          ;180
                DCD     DefaultISR                          ;181
                DCD     DefaultISR                          ;182
                DCD     DefaultISR                          ;183
                DCD     DefaultISR                          ;184
                DCD     DefaultISR                          ;185
                DCD     DefaultISR                          ;186
                DCD     DefaultISR                          ;187
                DCD     DefaultISR                          ;188
                DCD     DefaultISR                          ;189
                DCD     DefaultISR                          ;190
                DCD     DefaultISR                          ;191
                DCD     DefaultISR                          ;192
                DCD     DefaultISR                          ;193
                DCD     DefaultISR                          ;194
                DCD     DefaultISR                          ;195
                DCD     DefaultISR                          ;196
                DCD     DefaultISR                          ;197
                DCD     DefaultISR                          ;198
                DCD     DefaultISR                          ;199
                DCD     DefaultISR                          ;200
                DCD     DefaultISR                          ;201
                DCD     DefaultISR                          ;202
                DCD     DefaultISR                          ;203
                DCD     DefaultISR                          ;204
                DCD     DefaultISR                          ;205
                DCD     DefaultISR                          ;206
                DCD     DefaultISR                          ;207
                DCD     DefaultISR                          ;208
                DCD     DefaultISR                          ;209
                DCD     DefaultISR                          ;210
                DCD     DefaultISR                          ;211
                DCD     DefaultISR                          ;212
                DCD     DefaultISR                          ;213
                DCD     DefaultISR                          ;214
                DCD     DefaultISR                          ;215
                DCD     DefaultISR                          ;216
                DCD     DefaultISR                          ;217
                DCD     DefaultISR                          ;218
                DCD     DefaultISR                          ;219
                DCD     DefaultISR                          ;220
                DCD     DefaultISR                          ;221
                DCD     DefaultISR                          ;222
                DCD     DefaultISR                          ;223
                DCD     DefaultISR                          ;224
                DCD     DefaultISR                          ;225
                DCD     DefaultISR                          ;226
                DCD     DefaultISR                          ;227
                DCD     DefaultISR                          ;228
                DCD     DefaultISR                          ;229
                DCD     DefaultISR                          ;230
                DCD     DefaultISR                          ;231
                DCD     DefaultISR                          ;232
                DCD     DefaultISR                          ;233
                DCD     DefaultISR                          ;234
                DCD     DefaultISR                          ;235
                DCD     DefaultISR                          ;236
                DCD     DefaultISR                          ;237
                DCD     DefaultISR                          ;238
                DCD     DefaultISR                          ;239
                DCD     DefaultISR                          ;240
                DCD     DefaultISR                          ;241
                DCD     DefaultISR                          ;242
                DCD     DefaultISR                          ;243
                DCD     DefaultISR                          ;244
                DCD     DefaultISR                          ;245
                DCD     DefaultISR                          ;246
                DCD     DefaultISR                          ;247
                DCD     DefaultISR                          ;248
                DCD     DefaultISR                          ;249
                DCD     DefaultISR                          ;250
                DCD     DefaultISR                          ;251
                DCD     DefaultISR                          ;252
                DCD     DefaultISR                          ;253
                DCD     DefaultISR                          ;254
                DCD     0xFFFFFFFF                          ; Reserved for user TRIM value
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                CPSID   I               ; Mask interrupts
                LDR     R0, =0xE000ED08
                LDR     R1, =__Vectors
                STR     R1, [R0]
                LDR     R2, [R1]
                MSR     MSP, R2
                
                LDR     R0, =0x400AC044 ; IOMUXC_GPR_GPR17
                LDR     R1, =0x55555555 ; 1MB OCRAM
                STR     R1, [R0]
                
                LDR     R0, =0x400AC040 ; IOMUXC_GPR_GPR16
                LDR     R1, =0x00000007 ; 
                STR     R1, [R0]               
                
                LDR     R0, =SystemInit
                BLX     R0
                CPSIE   i               ; Unmask interrupts
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler\
                PROC
                EXPORT  NMI_Handler         [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler         [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler         [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler         [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler         [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler         [WEAK]
                B       .
                ENDP
DMA0_DMA16_IRQHandler\
                PROC
                EXPORT  DMA0_DMA16_IRQHandler         [WEAK]
                LDR     R0, =DMA0_DMA16_DriverIRQHandler
                BX      R0
                ENDP

DMA1_DMA17_IRQHandler\
                PROC
                EXPORT  DMA1_DMA17_IRQHandler         [WEAK]
                LDR     R0, =DMA1_DMA17_DriverIRQHandler
                BX      R0
                ENDP

DMA2_DMA18_IRQHandler\
                PROC
                EXPORT  DMA2_DMA18_IRQHandler         [WEAK]
                LDR     R0, =DMA2_DMA18_DriverIRQHandler
                BX      R0
                ENDP

DMA3_DMA19_IRQHandler\
                PROC
                EXPORT  DMA3_DMA19_IRQHandler         [WEAK]
                LDR     R0, =DMA3_DMA19_DriverIRQHandler
                BX      R0
                ENDP

DMA4_DMA20_IRQHandler\
                PROC
                EXPORT  DMA4_DMA20_IRQHandler         [WEAK]
                LDR     R0, =DMA4_DMA20_DriverIRQHandler
                BX      R0
                ENDP

DMA5_DMA21_IRQHandler\
                PROC
                EXPORT  DMA5_DMA21_IRQHandler         [WEAK]
                LDR     R0, =DMA5_DMA21_DriverIRQHandler
                BX      R0
                ENDP

DMA6_DMA22_IRQHandler\
                PROC
                EXPORT  DMA6_DMA22_IRQHandler         [WEAK]
                LDR     R0, =DMA6_DMA22_DriverIRQHandler
                BX      R0
                ENDP

DMA7_DMA23_IRQHandler\
                PROC
                EXPORT  DMA7_DMA23_IRQHandler         [WEAK]
                LDR     R0, =DMA7_DMA23_DriverIRQHandler
                BX      R0
                ENDP

DMA8_DMA24_IRQHandler\
                PROC
                EXPORT  DMA8_DMA24_IRQHandler         [WEAK]
                LDR     R0, =DMA8_DMA24_DriverIRQHandler
                BX      R0
                ENDP

DMA9_DMA25_IRQHandler\
                PROC
                EXPORT  DMA9_DMA25_IRQHandler         [WEAK]
                LDR     R0, =DMA9_DMA25_DriverIRQHandler
                BX      R0
                ENDP

DMA10_DMA26_IRQHandler\
                PROC
                EXPORT  DMA10_DMA26_IRQHandler         [WEAK]
                LDR     R0, =DMA10_DMA26_DriverIRQHandler
                BX      R0
                ENDP

DMA11_DMA27_IRQHandler\
                PROC
                EXPORT  DMA11_DMA27_IRQHandler         [WEAK]
                LDR     R0, =DMA11_DMA27_DriverIRQHandler
                BX      R0
                ENDP

DMA12_DMA28_IRQHandler\
                PROC
                EXPORT  DMA12_DMA28_IRQHandler         [WEAK]
                LDR     R0, =DMA12_DMA28_DriverIRQHandler
                BX      R0
                ENDP

DMA13_DMA29_IRQHandler\
                PROC
                EXPORT  DMA13_DMA29_IRQHandler         [WEAK]
                LDR     R0, =DMA13_DMA29_DriverIRQHandler
                BX      R0
                ENDP

DMA14_DMA30_IRQHandler\
                PROC
                EXPORT  DMA14_DMA30_IRQHandler         [WEAK]
                LDR     R0, =DMA14_DMA30_DriverIRQHandler
                BX      R0
                ENDP

DMA15_DMA31_IRQHandler\
                PROC
                EXPORT  DMA15_DMA31_IRQHandler         [WEAK]
                LDR     R0, =DMA15_DMA31_DriverIRQHandler
                BX      R0
                ENDP

DMA_ERROR_IRQHandler\
                PROC
                EXPORT  DMA_ERROR_IRQHandler         [WEAK]
                LDR     R0, =DMA_ERROR_DriverIRQHandler
                BX      R0
                ENDP

LPUART1_IRQHandler\
                PROC
                EXPORT  LPUART1_IRQHandler         [WEAK]
                LDR     R0, =LPUART1_DriverIRQHandler
                BX      R0
                ENDP

LPUART2_IRQHandler\
                PROC
                EXPORT  LPUART2_IRQHandler         [WEAK]
                LDR     R0, =LPUART2_DriverIRQHandler
                BX      R0
                ENDP

LPUART3_IRQHandler\
                PROC
                EXPORT  LPUART3_IRQHandler         [WEAK]
                LDR     R0, =LPUART3_DriverIRQHandler
                BX      R0
                ENDP

LPUART4_IRQHandler\
                PROC
                EXPORT  LPUART4_IRQHandler         [WEAK]
                LDR     R0, =LPUART4_DriverIRQHandler
                BX      R0
                ENDP

LPUART5_IRQHandler\
                PROC
                EXPORT  LPUART5_IRQHandler         [WEAK]
                LDR     R0, =LPUART5_DriverIRQHandler
                BX      R0
                ENDP

LPUART6_IRQHandler\
                PROC
                EXPORT  LPUART6_IRQHandler         [WEAK]
                LDR     R0, =LPUART6_DriverIRQHandler
                BX      R0
                ENDP

LPUART7_IRQHandler\
                PROC
                EXPORT  LPUART7_IRQHandler         [WEAK]
                LDR     R0, =LPUART7_DriverIRQHandler
                BX      R0
                ENDP

LPUART8_IRQHandler\
                PROC
                EXPORT  LPUART8_IRQHandler         [WEAK]
                LDR     R0, =LPUART8_DriverIRQHandler
                BX      R0
                ENDP

LPI2C1_IRQHandler\
                PROC
                EXPORT  LPI2C1_IRQHandler         [WEAK]
                LDR     R0, =LPI2C1_DriverIRQHandler
                BX      R0
                ENDP

LPI2C2_IRQHandler\
                PROC
                EXPORT  LPI2C2_IRQHandler         [WEAK]
                LDR     R0, =LPI2C2_DriverIRQHandler
                BX      R0
                ENDP

LPI2C3_IRQHandler\
                PROC
                EXPORT  LPI2C3_IRQHandler         [WEAK]
                LDR     R0, =LPI2C3_DriverIRQHandler
                BX      R0
                ENDP

LPI2C4_IRQHandler\
                PROC
                EXPORT  LPI2C4_IRQHandler         [WEAK]
                LDR     R0, =LPI2C4_DriverIRQHandler
                BX      R0
                ENDP

LPSPI1_IRQHandler\
                PROC
                EXPORT  LPSPI1_IRQHandler         [WEAK]
                LDR     R0, =LPSPI1_DriverIRQHandler
                BX      R0
                ENDP

LPSPI2_IRQHandler\
                PROC
                EXPORT  LPSPI2_IRQHandler         [WEAK]
                LDR     R0, =LPSPI2_DriverIRQHandler
                BX      R0
                ENDP

LPSPI3_IRQHandler\
                PROC
                EXPORT  LPSPI3_IRQHandler         [WEAK]
                LDR     R0, =LPSPI3_DriverIRQHandler
                BX      R0
                ENDP

LPSPI4_IRQHandler\
                PROC
                EXPORT  LPSPI4_IRQHandler         [WEAK]
                LDR     R0, =LPSPI4_DriverIRQHandler
                BX      R0
                ENDP

CAN1_IRQHandler\
                PROC
                EXPORT  CAN1_IRQHandler         [WEAK]
                LDR     R0, =CAN1_DriverIRQHandler
                BX      R0
                ENDP

CAN2_IRQHandler\
                PROC
                EXPORT  CAN2_IRQHandler         [WEAK]
                LDR     R0, =CAN2_DriverIRQHandler
                BX      R0
                ENDP

SAI1_IRQHandler\
                PROC
                EXPORT  SAI1_IRQHandler         [WEAK]
                LDR     R0, =SAI1_DriverIRQHandler
                BX      R0
                ENDP

SAI2_IRQHandler\
                PROC
                EXPORT  SAI2_IRQHandler         [WEAK]
                LDR     R0, =SAI2_DriverIRQHandler
                BX      R0
                ENDP

SAI3_RX_IRQHandler\
                PROC
                EXPORT  SAI3_RX_IRQHandler         [WEAK]
                LDR     R0, =SAI3_RX_DriverIRQHandler
                BX      R0
                ENDP

SAI3_TX_IRQHandler\
                PROC
                EXPORT  SAI3_TX_IRQHandler         [WEAK]
                LDR     R0, =SAI3_TX_DriverIRQHandler
                BX      R0
                ENDP

SPDIF_IRQHandler\
                PROC
                EXPORT  SPDIF_IRQHandler         [WEAK]
                LDR     R0, =SPDIF_DriverIRQHandler
                BX      R0
                ENDP

FLEXIO1_IRQHandler\
                PROC
                EXPORT  FLEXIO1_IRQHandler         [WEAK]
                LDR     R0, =FLEXIO1_DriverIRQHandler
                BX      R0
                ENDP

FLEXIO2_IRQHandler\
                PROC
                EXPORT  FLEXIO2_IRQHandler         [WEAK]
                LDR     R0, =FLEXIO2_DriverIRQHandler
                BX      R0
                ENDP

FLEXSPI2_IRQHandler\
                PROC
                EXPORT  FLEXSPI2_IRQHandler         [WEAK]
                LDR     R0, =FLEXSPI2_DriverIRQHandler
                BX      R0
                ENDP

FLEXSPI_IRQHandler\
                PROC
                EXPORT  FLEXSPI_IRQHandler         [WEAK]
                LDR     R0, =FLEXSPI_DriverIRQHandler
                BX      R0
                ENDP

USDHC1_IRQHandler\
                PROC
                EXPORT  USDHC1_IRQHandler         [WEAK]
                LDR     R0, =USDHC1_DriverIRQHandler
                BX      R0
                ENDP

USDHC2_IRQHandler\
                PROC
                EXPORT  USDHC2_IRQHandler         [WEAK]
                LDR     R0, =USDHC2_DriverIRQHandler
                BX      R0
                ENDP

ENET_IRQHandler\
                PROC
                EXPORT  ENET_IRQHandler         [WEAK]
                LDR     R0, =ENET_DriverIRQHandler
                BX      R0
                ENDP

ENET_1588_Timer_IRQHandler\
                PROC
                EXPORT  ENET_1588_Timer_IRQHandler         [WEAK]
                LDR     R0, =ENET_1588_Timer_DriverIRQHandler
                BX      R0
                ENDP

ENET2_IRQHandler\
                PROC
                EXPORT  ENET2_IRQHandler         [WEAK]
                LDR     R0, =ENET2_DriverIRQHandler
                BX      R0
                ENDP

ENET2_1588_Timer_IRQHandler\
                PROC
                EXPORT  ENET2_1588_Timer_IRQHandler         [WEAK]
                LDR     R0, =ENET2_1588_Timer_DriverIRQHandler
                BX      R0
                ENDP

CAN3_IRQHandler\
                PROC
                EXPORT  CAN3_IRQHandler         [WEAK]
                LDR     R0, =CAN3_DriverIRQHandler
                BX      R0
                ENDP

FLEXIO3_IRQHandler\
                PROC
                EXPORT  FLEXIO3_IRQHandler         [WEAK]
                LDR     R0, =FLEXIO3_DriverIRQHandler
                BX      R0
                ENDP

Default_Handler\
                PROC
                EXPORT  DMA0_DMA16_DriverIRQHandler         [WEAK]
                EXPORT  DMA1_DMA17_DriverIRQHandler         [WEAK]
                EXPORT  DMA2_DMA18_DriverIRQHandler         [WEAK]
                EXPORT  DMA3_DMA19_DriverIRQHandler         [WEAK]
                EXPORT  DMA4_DMA20_DriverIRQHandler         [WEAK]
                EXPORT  DMA5_DMA21_DriverIRQHandler         [WEAK]
                EXPORT  DMA6_DMA22_DriverIRQHandler         [WEAK]
                EXPORT  DMA7_DMA23_DriverIRQHandler         [WEAK]
                EXPORT  DMA8_DMA24_DriverIRQHandler         [WEAK]
                EXPORT  DMA9_DMA25_DriverIRQHandler         [WEAK]
                EXPORT  DMA10_DMA26_DriverIRQHandler         [WEAK]
                EXPORT  DMA11_DMA27_DriverIRQHandler         [WEAK]
                EXPORT  DMA12_DMA28_DriverIRQHandler         [WEAK]
                EXPORT  DMA13_DMA29_DriverIRQHandler         [WEAK]
                EXPORT  DMA14_DMA30_DriverIRQHandler         [WEAK]
                EXPORT  DMA15_DMA31_DriverIRQHandler         [WEAK]
                EXPORT  DMA_ERROR_DriverIRQHandler         [WEAK]
                EXPORT  CTI0_ERROR_IRQHandler         [WEAK]
                EXPORT  CTI1_ERROR_IRQHandler         [WEAK]
                EXPORT  CORE_IRQHandler         [WEAK]
                EXPORT  LPUART1_DriverIRQHandler         [WEAK]
                EXPORT  LPUART2_DriverIRQHandler         [WEAK]
                EXPORT  LPUART3_DriverIRQHandler         [WEAK]
                EXPORT  LPUART4_DriverIRQHandler         [WEAK]
                EXPORT  LPUART5_DriverIRQHandler         [WEAK]
                EXPORT  LPUART6_DriverIRQHandler         [WEAK]
                EXPORT  LPUART7_DriverIRQHandler         [WEAK]
                EXPORT  LPUART8_DriverIRQHandler         [WEAK]
                EXPORT  LPI2C1_DriverIRQHandler         [WEAK]
                EXPORT  LPI2C2_DriverIRQHandler         [WEAK]
                EXPORT  LPI2C3_DriverIRQHandler         [WEAK]
                EXPORT  LPI2C4_DriverIRQHandler         [WEAK]
                EXPORT  LPSPI1_DriverIRQHandler         [WEAK]
                EXPORT  LPSPI2_DriverIRQHandler         [WEAK]
                EXPORT  LPSPI3_DriverIRQHandler         [WEAK]
                EXPORT  LPSPI4_DriverIRQHandler         [WEAK]
                EXPORT  CAN1_DriverIRQHandler         [WEAK]
                EXPORT  CAN2_DriverIRQHandler         [WEAK]
                EXPORT  FLEXRAM_IRQHandler         [WEAK]
                EXPORT  KPP_IRQHandler         [WEAK]
                EXPORT  TSC_DIG_IRQHandler         [WEAK]
                EXPORT  GPR_IRQ_IRQHandler         [WEAK]
                EXPORT  Reserved58_IRQHandler         [WEAK]
                EXPORT  Reserved59_IRQHandler         [WEAK]
                EXPORT  Reserved60_IRQHandler         [WEAK]
                EXPORT  WDOG2_IRQHandler         [WEAK]
                EXPORT  SNVS_HP_WRAPPER_IRQHandler         [WEAK]
                EXPORT  SNVS_HP_WRAPPER_TZ_IRQHandler         [WEAK]
                EXPORT  SNVS_LP_WRAPPER_IRQHandler         [WEAK]
                EXPORT  CSU_IRQHandler         [WEAK]
                EXPORT  DCP_IRQHandler         [WEAK]
                EXPORT  DCP_VMI_IRQHandler         [WEAK]
                EXPORT  Reserved68_IRQHandler         [WEAK]
                EXPORT  TRNG_IRQHandler         [WEAK]
                EXPORT  SJC_IRQHandler         [WEAK]
                EXPORT  BEE_IRQHandler         [WEAK]
                EXPORT  SAI1_DriverIRQHandler         [WEAK]
                EXPORT  SAI2_DriverIRQHandler         [WEAK]
                EXPORT  SAI3_RX_DriverIRQHandler         [WEAK]
                EXPORT  SAI3_TX_DriverIRQHandler         [WEAK]
                EXPORT  SPDIF_DriverIRQHandler         [WEAK]
                EXPORT  PMU_EVENT_IRQHandler         [WEAK]
                EXPORT  Reserved78_IRQHandler         [WEAK]
                EXPORT  TEMP_LOW_HIGH_IRQHandler         [WEAK]
                EXPORT  TEMP_PANIC_IRQHandler         [WEAK]
                EXPORT  USB_PHY1_IRQHandler         [WEAK]
                EXPORT  USB_PHY2_IRQHandler         [WEAK]
                EXPORT  ADC1_IRQHandler         [WEAK]
                EXPORT  ADC2_IRQHandler         [WEAK]
                EXPORT  DCDC_IRQHandler         [WEAK]
                EXPORT  Reserved86_IRQHandler         [WEAK]
                EXPORT  Reserved87_IRQHandler         [WEAK]
                EXPORT  GPIO1_INT0_IRQHandler         [WEAK]
                EXPORT  GPIO1_INT1_IRQHandler         [WEAK]
                EXPORT  GPIO1_INT2_IRQHandler         [WEAK]
                EXPORT  GPIO1_INT3_IRQHandler         [WEAK]
                EXPORT  GPIO1_INT4_IRQHandler         [WEAK]
                EXPORT  GPIO1_INT5_IRQHandler         [WEAK]
                EXPORT  GPIO1_INT6_IRQHandler         [WEAK]
                EXPORT  GPIO1_INT7_IRQHandler         [WEAK]
                EXPORT  GPIO1_Combined_0_15_IRQHandler         [WEAK]
                EXPORT  GPIO1_Combined_16_31_IRQHandler         [WEAK]
                EXPORT  GPIO2_Combined_0_15_IRQHandler         [WEAK]
                EXPORT  GPIO2_Combined_16_31_IRQHandler         [WEAK]
                EXPORT  GPIO3_Combined_0_15_IRQHandler         [WEAK]
                EXPORT  GPIO3_Combined_16_31_IRQHandler         [WEAK]
                EXPORT  GPIO4_Combined_0_15_IRQHandler         [WEAK]
                EXPORT  GPIO4_Combined_16_31_IRQHandler         [WEAK]
                EXPORT  GPIO5_Combined_0_15_IRQHandler         [WEAK]
                EXPORT  GPIO5_Combined_16_31_IRQHandler         [WEAK]
                EXPORT  FLEXIO1_DriverIRQHandler         [WEAK]
                EXPORT  FLEXIO2_DriverIRQHandler         [WEAK]
                EXPORT  WDOG1_IRQHandler         [WEAK]
                EXPORT  RTWDOG_IRQHandler         [WEAK]
                EXPORT  EWM_IRQHandler         [WEAK]
                EXPORT  CCM_1_IRQHandler         [WEAK]
                EXPORT  CCM_2_IRQHandler         [WEAK]
                EXPORT  GPC_IRQHandler         [WEAK]
                EXPORT  SRC_IRQHandler         [WEAK]
                EXPORT  Reserved115_IRQHandler         [WEAK]
                EXPORT  GPT1_IRQHandler         [WEAK]
                EXPORT  GPT2_IRQHandler         [WEAK]
                EXPORT  PWM1_0_IRQHandler         [WEAK]
                EXPORT  PWM1_1_IRQHandler         [WEAK]
                EXPORT  PWM1_2_IRQHandler         [WEAK]
                EXPORT  PWM1_3_IRQHandler         [WEAK]
                EXPORT  PWM1_FAULT_IRQHandler         [WEAK]
                EXPORT  FLEXSPI2_DriverIRQHandler         [WEAK]
                EXPORT  FLEXSPI_DriverIRQHandler         [WEAK]
                EXPORT  SEMC_IRQHandler         [WEAK]
                EXPORT  USDHC1_DriverIRQHandler         [WEAK]
                EXPORT  USDHC2_DriverIRQHandler         [WEAK]
                EXPORT  USB_OTG2_IRQHandler         [WEAK]
                EXPORT  USB_OTG1_IRQHandler         [WEAK]
                EXPORT  ENET_DriverIRQHandler         [WEAK]
                EXPORT  ENET_1588_Timer_DriverIRQHandler         [WEAK]
                EXPORT  XBAR1_IRQ_0_1_IRQHandler         [WEAK]
                EXPORT  XBAR1_IRQ_2_3_IRQHandler         [WEAK]
                EXPORT  ADC_ETC_IRQ0_IRQHandler         [WEAK]
                EXPORT  ADC_ETC_IRQ1_IRQHandler         [WEAK]
                EXPORT  ADC_ETC_IRQ2_IRQHandler         [WEAK]
                EXPORT  ADC_ETC_ERROR_IRQ_IRQHandler         [WEAK]
                EXPORT  PIT_IRQHandler         [WEAK]
                EXPORT  ACMP1_IRQHandler         [WEAK]
                EXPORT  ACMP2_IRQHandler         [WEAK]
                EXPORT  ACMP3_IRQHandler         [WEAK]
                EXPORT  ACMP4_IRQHandler         [WEAK]
                EXPORT  Reserved143_IRQHandler         [WEAK]
                EXPORT  Reserved144_IRQHandler         [WEAK]
                EXPORT  ENC1_IRQHandler         [WEAK]
                EXPORT  ENC2_IRQHandler         [WEAK]
                EXPORT  ENC3_IRQHandler         [WEAK]
                EXPORT  ENC4_IRQHandler         [WEAK]
                EXPORT  TMR1_IRQHandler         [WEAK]
                EXPORT  TMR2_IRQHandler         [WEAK]
                EXPORT  TMR3_IRQHandler         [WEAK]
                EXPORT  TMR4_IRQHandler         [WEAK]
                EXPORT  PWM2_0_IRQHandler         [WEAK]
                EXPORT  PWM2_1_IRQHandler         [WEAK]
                EXPORT  PWM2_2_IRQHandler         [WEAK]
                EXPORT  PWM2_3_IRQHandler         [WEAK]
                EXPORT  PWM2_FAULT_IRQHandler         [WEAK]
                EXPORT  PWM3_0_IRQHandler         [WEAK]
                EXPORT  PWM3_1_IRQHandler         [WEAK]
                EXPORT  PWM3_2_IRQHandler         [WEAK]
                EXPORT  PWM3_3_IRQHandler         [WEAK]
                EXPORT  PWM3_FAULT_IRQHandler         [WEAK]
                EXPORT  PWM4_0_IRQHandler         [WEAK]
                EXPORT  PWM4_1_IRQHandler         [WEAK]
                EXPORT  PWM4_2_IRQHandler         [WEAK]
                EXPORT  PWM4_3_IRQHandler         [WEAK]
                EXPORT  PWM4_FAULT_IRQHandler         [WEAK]
                EXPORT  ENET2_DriverIRQHandler         [WEAK]
                EXPORT  ENET2_1588_Timer_DriverIRQHandler         [WEAK]
                EXPORT  CAN3_DriverIRQHandler         [WEAK]
                EXPORT  Reserved171_IRQHandler         [WEAK]
                EXPORT  FLEXIO3_DriverIRQHandler         [WEAK]
                EXPORT  GPIO6_7_8_9_IRQHandler         [WEAK]
                EXPORT  DefaultISR         [WEAK]
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
Reserved58_IRQHandler
Reserved59_IRQHandler
Reserved60_IRQHandler
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
Reserved87_IRQHandler
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
                LDR    R0, =DefaultISR
                BX     R0
                ENDP
                  ALIGN


                END
