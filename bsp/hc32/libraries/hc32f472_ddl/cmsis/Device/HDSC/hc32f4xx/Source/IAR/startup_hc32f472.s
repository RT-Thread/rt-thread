;/**
; ******************************************************************************
;  @file  startup_hc32f472.s
;  @brief Startup for IAR.
; verbatim
;  Change Logs:
;  Date             Author          Notes
;  2022-06-30       CDT             First version
;  2023-12-15       CDT             TMR6_x_GDet_Handler -> TMR6_x_Dte_Handler
; endverbatim
; *****************************************************************************
; * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
; *
; * This software component is licensed by XHSC under BSD 3-Clause license
; * (the "License"); You may not use this file except in compliance with the
; * License. You may obtain a copy of the License at:
; *                    opensource.org/licenses/BSD-3-Clause
; *
; ******************************************************************************
; */


                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                SECTION .intvec:CODE:NOROOT(2)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table

                DATA
__vector_table
                DCD     sfe(CSTACK)               ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; Peripheral Interrupts
                DCD     IRQ000_Handler
                DCD     IRQ001_Handler
                DCD     IRQ002_Handler
                DCD     IRQ003_Handler
                DCD     IRQ004_Handler
                DCD     IRQ005_Handler
                DCD     IRQ006_Handler
                DCD     IRQ007_Handler
                DCD     IRQ008_Handler
                DCD     IRQ009_Handler
                DCD     IRQ010_Handler
                DCD     IRQ011_Handler
                DCD     IRQ012_Handler
                DCD     IRQ013_Handler
                DCD     IRQ014_Handler
                DCD     IRQ015_Handler
                DCD     EXTINT00_SWINT16_Handler
                DCD     EXTINT01_SWINT17_Handler
                DCD     EXTINT02_SWINT18_Handler
                DCD     EXTINT03_SWINT19_Handler
                DCD     EXTINT04_SWINT20_Handler
                DCD     EXTINT05_SWINT21_Handler
                DCD     EXTINT06_SWINT22_Handler
                DCD     EXTINT07_SWINT23_Handler
                DCD     EXTINT08_SWINT24_Handler
                DCD     EXTINT09_SWINT25_Handler
                DCD     EXTINT10_SWINT26_Handler
                DCD     EXTINT11_SWINT27_Handler
                DCD     EXTINT12_SWINT28_Handler
                DCD     EXTINT13_SWINT29_Handler
                DCD     EXTINT14_SWINT30_Handler
                DCD     EXTINT15_SWINT31_Handler
                DCD     DMA1_Error_Handler
                DCD     DMA1_TC0_BTC0_Handler
                DCD     DMA1_TC1_BTC1_Handler
                DCD     DMA1_TC2_BTC2_Handler
                DCD     DMA1_TC3_BTC3_Handler
                DCD     DMA1_TC4_BTC4_Handler
                DCD     DMA1_TC5_BTC5_Handler
                DCD     DMA1_TC6_BTC6_Handler
                DCD     DMA1_TC7_BTC7_Handler
                DCD     EFM_PEError_ReadCol_Handler
                DCD     EFM_OpEnd_Handler
                DCD     QSPI_Handler
                DCD     DCU1_Handler
                DCD     DCU2_Handler
                DCD     DCU3_Handler
                DCD     DMA2_Error_Handler
                DCD     DMA2_TC0_BTC0_Handler
                DCD     DMA2_TC1_BTC1_Handler
                DCD     DMA2_TC2_BTC2_Handler
                DCD     DMA2_TC3_BTC3_Handler
                DCD     DMA2_TC4_BTC4_Handler
                DCD     DMA2_TC5_BTC5_Handler
                DCD     DMA2_TC6_BTC6_Handler
                DCD     DMA2_TC7_BTC7_Handler
                DCD     MAU_Handler
                DCD     FMAC1_Handler
                DCD     FMAC2_Handler
                DCD     FMAC3_Handler
                DCD     FMAC4_Handler
                DCD     TMR0_1_Cmp_Handler
                DCD     TMR0_2_Cmp_Handler
                DCD     TMR2_1_Cmp_Handler
                DCD     TMR2_1_Ovf_Handler
                DCD     TMR2_2_Cmp_Handler
                DCD     TMR2_2_Ovf_Handler
                DCD     TMR2_3_Cmp_Handler
                DCD     TMR2_3_Ovf_Handler
                DCD     TMR2_4_Cmp_Handler
                DCD     TMR2_4_Ovf_Handler
                DCD     RTC_Handler
                DCD     CLK_XtalStop_Handler
                DCD     PWC_WKTM_Handler
                DCD     SWDT_Handler
                DCD     TMR6_1_GCmp_Handler
                DCD     TMR6_1_Ovf_Udf_Handler
                DCD     TMR6_1_Dte_Handler
                DCD     TMR6_1_SCmp_Handler
                DCD     TMRA_1_Ovf_Udf_Handler
                DCD     TMRA_1_Cmp_Handler
                DCD     TMR6_2_GCmp_Handler
                DCD     TMR6_2_Ovf_Udf_Handler
                DCD     TMR6_2_Dte_Handler
                DCD     TMR6_2_SCmp_Handler
                DCD     TMRA_2_Ovf_Udf_Handler
                DCD     TMRA_2_Cmp_Handler
                DCD     TMR6_3_GCmp_Handler
                DCD     TMR6_3_Ovf_Udf_Handler
                DCD     TMR6_3_Dte_Handler
                DCD     TMR6_3_SCmp_Handler
                DCD     TMRA_3_Ovf_Udf_Handler
                DCD     TMRA_3_Cmp_Handler
                DCD     TMR6_4_GCmp_Handler
                DCD     TMR6_4_Ovf_Udf_Handler
                DCD     TMR6_4_Dte_Handler
                DCD     TMR6_4_SCmp_Handler
                DCD     TMRA_4_Ovf_Udf_Handler
                DCD     TMRA_4_Cmp_Handler
                DCD     TMR6_5_GCmp_Handler
                DCD     TMR6_5_Ovf_Udf_Handler
                DCD     TMR6_5_Dte_Handler
                DCD     TMR6_5_SCmp_Handler
                DCD     0
                DCD     TMR6_6_GCmp_Handler
                DCD     TMR6_6_Ovf_Udf_Handler
                DCD     TMR6_6_Dte_Handler
                DCD     TMR6_6_SCmp_Handler
                DCD     TMR6_7_GCmp_Handler
                DCD     TMR6_7_Ovf_Udf_Handler
                DCD     TMR6_7_Dte_Handler
                DCD     TMR6_7_SCmp_Handler
                DCD     TMR6_8_GCmp_Handler
                DCD     TMR6_8_Ovf_Udf_Handler
                DCD     TMR6_8_Dte_Handler
                DCD     TMR6_8_SCmp_Handler
                DCD     TMR6_9_GCmp_Handler
                DCD     TMR6_9_Ovf_Udf_Handler
                DCD     TMR6_9_Dte_Handler
                DCD     TMR6_9_SCmp_Handler
                DCD     TMR6_10_GCmp_Handler
                DCD     TMR6_10_Ovf_Udf_Handler
                DCD     TMR6_10_Dte_Handler
                DCD     TMR6_10_SCmp_Handler
                DCD     TMR4_1_GCmp_Handler
                DCD     TMR4_1_Ovf_Udf_Handler
                DCD     TMR4_1_Reload_Handler
                DCD     TMR4_1_SCmp_Handler
                DCD     CMP1_Handler
                DCD     CMP2_Handler
                DCD     CMP3_Handler
                DCD     CMP4_Handler
                DCD     CAN1_Handler
                DCD     CAN2_Handler
                DCD     CAN3_Handler
                DCD     USART1_Handler
                DCD     USART2_Handler
                DCD     SPI1_Handler
                DCD     SPI2_Handler
                DCD     TMRA_5_Ovf_Udf_Handler
                DCD     TMRA_5_Cmp_Handler
                DCD     TMRA_6_Ovf_Udf_Handler
                DCD     TMRA_6_Cmp_Handler
                DCD     USBFS_Handler
                DCD     EVENT_PORT1_Handler
                DCD     EVENT_PORT2_Handler
                DCD     EVENT_PORT3_Handler
                DCD     EVENT_PORT4_Handler
                DCD     USART3_Handler
                DCD     USART4_Handler
                DCD     SPI3_Handler
                DCD     SPI4_Handler
                DCD     EMB_GR0_Handler
                DCD     EMB_GR1_Handler
                DCD     EMB_GR2_Handler
                DCD     EMB_GR3_Handler
                DCD     EMB_GR4_Handler
                DCD     EMB_GR5_Handler
                DCD     EMB_GR6_Handler
                DCD     HASH_Handler
                DCD     USART5_Handler
                DCD     USART6_Handler
                DCD     MDIO_Handler
                DCD     PLA_Handler
                DCD     I2C1_Handler
                DCD     I2C2_Handler
                DCD     I2C3_Handler
                DCD     USART1_WKUP_Handler
                DCD     PWC_LVD1_Handler
                DCD     PWC_LVD2_Handler
                DCD     OTS_Handler
                DCD     FCM_Handler
                DCD     WDT_Handler
                DCD     CTC_Handler
                DCD     ADC1_Handler
                DCD     ADC2_Handler
                DCD     ADC3_Handler
                DCD     TRNG_Handler
                DCD     USART1_TxComplete_Handler
                DCD     USART2_TxComplete_Handler
                DCD     USART3_TxComplete_Handler
                DCD     USART4_TxComplete_Handler
                DCD     USART5_TxComplete_Handler
                DCD     USART6_TxComplete_Handler

                THUMB
; Dummy Exception Handlers (infinite loops which can be modified)

                PUBWEAK Reset_Handler
                SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0

                PUBWEAK NMI_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
                B       NMI_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
                B       HardFault_Handler

                PUBWEAK MemManage_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
                B       MemManage_Handler

                PUBWEAK BusFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
                B       BusFault_Handler

                PUBWEAK UsageFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
                B       UsageFault_Handler

                PUBWEAK SVC_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
                B       SVC_Handler

                PUBWEAK DebugMon_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
                B       DebugMon_Handler

                PUBWEAK PendSV_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
                B       PendSV_Handler

                PUBWEAK SysTick_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
                B       SysTick_Handler

                PUBWEAK IRQ000_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ000_Handler
                B       IRQ000_Handler

                PUBWEAK IRQ001_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ001_Handler
                B       IRQ001_Handler

                PUBWEAK IRQ002_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ002_Handler
                B       IRQ002_Handler

                PUBWEAK IRQ003_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ003_Handler
                B       IRQ003_Handler

                PUBWEAK IRQ004_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ004_Handler
                B       IRQ004_Handler

                PUBWEAK IRQ005_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ005_Handler
                B       IRQ005_Handler

                PUBWEAK IRQ006_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ006_Handler
                B       IRQ006_Handler

                PUBWEAK IRQ007_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ007_Handler
                B       IRQ007_Handler

                PUBWEAK IRQ008_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ008_Handler
                B       IRQ008_Handler

                PUBWEAK IRQ009_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ009_Handler
                B       IRQ009_Handler

                PUBWEAK IRQ010_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ010_Handler
                B       IRQ010_Handler

                PUBWEAK IRQ011_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ011_Handler
                B       IRQ011_Handler

                PUBWEAK IRQ012_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ012_Handler
                B       IRQ012_Handler

                PUBWEAK IRQ013_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ013_Handler
                B       IRQ013_Handler

                PUBWEAK IRQ014_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ014_Handler
                B       IRQ014_Handler

                PUBWEAK IRQ015_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ015_Handler
                B       IRQ015_Handler

                PUBWEAK EXTINT00_SWINT16_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT00_SWINT16_Handler
                B       EXTINT00_SWINT16_Handler

                PUBWEAK EXTINT01_SWINT17_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT01_SWINT17_Handler
                B       EXTINT01_SWINT17_Handler

                PUBWEAK EXTINT02_SWINT18_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT02_SWINT18_Handler
                B       EXTINT02_SWINT18_Handler

                PUBWEAK EXTINT03_SWINT19_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT03_SWINT19_Handler
                B       EXTINT03_SWINT19_Handler

                PUBWEAK EXTINT04_SWINT20_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT04_SWINT20_Handler
                B       EXTINT04_SWINT20_Handler

                PUBWEAK EXTINT05_SWINT21_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT05_SWINT21_Handler
                B       EXTINT05_SWINT21_Handler

                PUBWEAK EXTINT06_SWINT22_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT06_SWINT22_Handler
                B       EXTINT06_SWINT22_Handler

                PUBWEAK EXTINT07_SWINT23_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT07_SWINT23_Handler
                B       EXTINT07_SWINT23_Handler

                PUBWEAK EXTINT08_SWINT24_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT08_SWINT24_Handler
                B       EXTINT08_SWINT24_Handler

                PUBWEAK EXTINT09_SWINT25_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT09_SWINT25_Handler
                B       EXTINT09_SWINT25_Handler

                PUBWEAK EXTINT10_SWINT26_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT10_SWINT26_Handler
                B       EXTINT10_SWINT26_Handler

                PUBWEAK EXTINT11_SWINT27_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT11_SWINT27_Handler
                B       EXTINT11_SWINT27_Handler

                PUBWEAK EXTINT12_SWINT28_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT12_SWINT28_Handler
                B       EXTINT12_SWINT28_Handler

                PUBWEAK EXTINT13_SWINT29_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT13_SWINT29_Handler
                B       EXTINT13_SWINT29_Handler

                PUBWEAK EXTINT14_SWINT30_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT14_SWINT30_Handler
                B       EXTINT14_SWINT30_Handler

                PUBWEAK EXTINT15_SWINT31_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXTINT15_SWINT31_Handler
                B       EXTINT15_SWINT31_Handler

                PUBWEAK DMA1_Error_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Error_Handler
                B       DMA1_Error_Handler

                PUBWEAK DMA1_TC0_BTC0_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_TC0_BTC0_Handler
                B       DMA1_TC0_BTC0_Handler

                PUBWEAK DMA1_TC1_BTC1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_TC1_BTC1_Handler
                B       DMA1_TC1_BTC1_Handler

                PUBWEAK DMA1_TC2_BTC2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_TC2_BTC2_Handler
                B       DMA1_TC2_BTC2_Handler

                PUBWEAK DMA1_TC3_BTC3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_TC3_BTC3_Handler
                B       DMA1_TC3_BTC3_Handler

                PUBWEAK DMA1_TC4_BTC4_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_TC4_BTC4_Handler
                B       DMA1_TC4_BTC4_Handler

                PUBWEAK DMA1_TC5_BTC5_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_TC5_BTC5_Handler
                B       DMA1_TC5_BTC5_Handler

                PUBWEAK DMA1_TC6_BTC6_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_TC6_BTC6_Handler
                B       DMA1_TC6_BTC6_Handler

                PUBWEAK DMA1_TC7_BTC7_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_TC7_BTC7_Handler
                B       DMA1_TC7_BTC7_Handler

                PUBWEAK EFM_PEError_ReadCol_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EFM_PEError_ReadCol_Handler
                B       EFM_PEError_ReadCol_Handler

                PUBWEAK EFM_OpEnd_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EFM_OpEnd_Handler
                B       EFM_OpEnd_Handler

                PUBWEAK QSPI_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
QSPI_Handler
                B       QSPI_Handler

                PUBWEAK DCU1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DCU1_Handler
                B       DCU1_Handler

                PUBWEAK DCU2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DCU2_Handler
                B       DCU2_Handler

                PUBWEAK DCU3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DCU3_Handler
                B       DCU3_Handler

                PUBWEAK DMA2_Error_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Error_Handler
                B       DMA2_Error_Handler

                PUBWEAK DMA2_TC0_BTC0_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_TC0_BTC0_Handler
                B       DMA2_TC0_BTC0_Handler

                PUBWEAK DMA2_TC1_BTC1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_TC1_BTC1_Handler
                B       DMA2_TC1_BTC1_Handler

                PUBWEAK DMA2_TC2_BTC2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_TC2_BTC2_Handler
                B       DMA2_TC2_BTC2_Handler

                PUBWEAK DMA2_TC3_BTC3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_TC3_BTC3_Handler
                B       DMA2_TC3_BTC3_Handler

                PUBWEAK DMA2_TC4_BTC4_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_TC4_BTC4_Handler
                B       DMA2_TC4_BTC4_Handler

                PUBWEAK DMA2_TC5_BTC5_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_TC5_BTC5_Handler
                B       DMA2_TC5_BTC5_Handler

                PUBWEAK DMA2_TC6_BTC6_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_TC6_BTC6_Handler
                B       DMA2_TC6_BTC6_Handler

                PUBWEAK DMA2_TC7_BTC7_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_TC7_BTC7_Handler
                B       DMA2_TC7_BTC7_Handler

                PUBWEAK MAU_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
MAU_Handler
                B       MAU_Handler

                PUBWEAK FMAC1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
FMAC1_Handler
                B       FMAC1_Handler

                PUBWEAK FMAC2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
FMAC2_Handler
                B       FMAC2_Handler

                PUBWEAK FMAC3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
FMAC3_Handler
                B       FMAC3_Handler

                PUBWEAK FMAC4_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
FMAC4_Handler
                B       FMAC4_Handler

                PUBWEAK TMR0_1_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR0_1_Cmp_Handler
                B       TMR0_1_Cmp_Handler

                PUBWEAK TMR0_2_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR0_2_Cmp_Handler
                B       TMR0_2_Cmp_Handler

                PUBWEAK TMR2_1_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_1_Cmp_Handler
                B       TMR2_1_Cmp_Handler

                PUBWEAK TMR2_1_Ovf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_1_Ovf_Handler
                B       TMR2_1_Ovf_Handler

                PUBWEAK TMR2_2_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_2_Cmp_Handler
                B       TMR2_2_Cmp_Handler

                PUBWEAK TMR2_2_Ovf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_2_Ovf_Handler
                B       TMR2_2_Ovf_Handler

                PUBWEAK TMR2_3_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_3_Cmp_Handler
                B       TMR2_3_Cmp_Handler

                PUBWEAK TMR2_3_Ovf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_3_Ovf_Handler
                B       TMR2_3_Ovf_Handler

                PUBWEAK TMR2_4_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_4_Cmp_Handler
                B       TMR2_4_Cmp_Handler

                PUBWEAK TMR2_4_Ovf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_4_Ovf_Handler
                B       TMR2_4_Ovf_Handler

                PUBWEAK RTC_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
RTC_Handler
                B       RTC_Handler

                PUBWEAK CLK_XtalStop_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
CLK_XtalStop_Handler
                B       CLK_XtalStop_Handler

                PUBWEAK PWC_WKTM_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PWC_WKTM_Handler
                B       PWC_WKTM_Handler

                PUBWEAK SWDT_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SWDT_Handler
                B       SWDT_Handler

                PUBWEAK TMR6_1_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_1_GCmp_Handler
                B       TMR6_1_GCmp_Handler

                PUBWEAK TMR6_1_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_1_Ovf_Udf_Handler
                B       TMR6_1_Ovf_Udf_Handler

                PUBWEAK TMR6_1_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_1_Dte_Handler
                B       TMR6_1_Dte_Handler

                PUBWEAK TMR6_1_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_1_SCmp_Handler
                B       TMR6_1_SCmp_Handler

                PUBWEAK TMRA_1_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_1_Ovf_Udf_Handler
                B       TMRA_1_Ovf_Udf_Handler

                PUBWEAK TMRA_1_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_1_Cmp_Handler
                B       TMRA_1_Cmp_Handler

                PUBWEAK TMR6_2_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_2_GCmp_Handler
                B       TMR6_2_GCmp_Handler

                PUBWEAK TMR6_2_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_2_Ovf_Udf_Handler
                B       TMR6_2_Ovf_Udf_Handler

                PUBWEAK TMR6_2_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_2_Dte_Handler
                B       TMR6_2_Dte_Handler

                PUBWEAK TMR6_2_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_2_SCmp_Handler
                B       TMR6_2_SCmp_Handler

                PUBWEAK TMRA_2_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_2_Ovf_Udf_Handler
                B       TMRA_2_Ovf_Udf_Handler

                PUBWEAK TMRA_2_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_2_Cmp_Handler
                B       TMRA_2_Cmp_Handler

                PUBWEAK TMR6_3_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_3_GCmp_Handler
                B       TMR6_3_GCmp_Handler

                PUBWEAK TMR6_3_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_3_Ovf_Udf_Handler
                B       TMR6_3_Ovf_Udf_Handler

                PUBWEAK TMR6_3_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_3_Dte_Handler
                B       TMR6_3_Dte_Handler

                PUBWEAK TMR6_3_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_3_SCmp_Handler
                B       TMR6_3_SCmp_Handler

                PUBWEAK TMRA_3_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_3_Ovf_Udf_Handler
                B       TMRA_3_Ovf_Udf_Handler

                PUBWEAK TMRA_3_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_3_Cmp_Handler
                B       TMRA_3_Cmp_Handler

                PUBWEAK TMR6_4_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_4_GCmp_Handler
                B       TMR6_4_GCmp_Handler

                PUBWEAK TMR6_4_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_4_Ovf_Udf_Handler
                B       TMR6_4_Ovf_Udf_Handler

                PUBWEAK TMR6_4_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_4_Dte_Handler
                B       TMR6_4_Dte_Handler

                PUBWEAK TMR6_4_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_4_SCmp_Handler
                B       TMR6_4_SCmp_Handler

                PUBWEAK TMRA_4_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_4_Ovf_Udf_Handler
                B       TMRA_4_Ovf_Udf_Handler

                PUBWEAK TMRA_4_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_4_Cmp_Handler
                B       TMRA_4_Cmp_Handler

                PUBWEAK TMR6_5_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_5_GCmp_Handler
                B       TMR6_5_GCmp_Handler

                PUBWEAK TMR6_5_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_5_Ovf_Udf_Handler
                B       TMR6_5_Ovf_Udf_Handler

                PUBWEAK TMR6_5_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_5_Dte_Handler
                B       TMR6_5_Dte_Handler

                PUBWEAK TMR6_5_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_5_SCmp_Handler
                B       TMR6_5_SCmp_Handler

                PUBWEAK TMR6_6_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_6_GCmp_Handler
                B       TMR6_6_GCmp_Handler

                PUBWEAK TMR6_6_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_6_Ovf_Udf_Handler
                B       TMR6_6_Ovf_Udf_Handler

                PUBWEAK TMR6_6_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_6_Dte_Handler
                B       TMR6_6_Dte_Handler

                PUBWEAK TMR6_6_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_6_SCmp_Handler
                B       TMR6_6_SCmp_Handler

                PUBWEAK TMR6_7_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_7_GCmp_Handler
                B       TMR6_7_GCmp_Handler

                PUBWEAK TMR6_7_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_7_Ovf_Udf_Handler
                B       TMR6_7_Ovf_Udf_Handler

                PUBWEAK TMR6_7_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_7_Dte_Handler
                B       TMR6_7_Dte_Handler

                PUBWEAK TMR6_7_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_7_SCmp_Handler
                B       TMR6_7_SCmp_Handler

                PUBWEAK TMR6_8_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_8_GCmp_Handler
                B       TMR6_8_GCmp_Handler

                PUBWEAK TMR6_8_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_8_Ovf_Udf_Handler
                B       TMR6_8_Ovf_Udf_Handler

                PUBWEAK TMR6_8_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_8_Dte_Handler
                B       TMR6_8_Dte_Handler

                PUBWEAK TMR6_8_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_8_SCmp_Handler
                B       TMR6_8_SCmp_Handler

                PUBWEAK TMR6_9_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_9_GCmp_Handler
                B       TMR6_9_GCmp_Handler

                PUBWEAK TMR6_9_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_9_Ovf_Udf_Handler
                B       TMR6_9_Ovf_Udf_Handler

                PUBWEAK TMR6_9_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_9_Dte_Handler
                B       TMR6_9_Dte_Handler

                PUBWEAK TMR6_9_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_9_SCmp_Handler
                B       TMR6_9_SCmp_Handler

                PUBWEAK TMR6_10_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_10_GCmp_Handler
                B       TMR6_10_GCmp_Handler

                PUBWEAK TMR6_10_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_10_Ovf_Udf_Handler
                B       TMR6_10_Ovf_Udf_Handler

                PUBWEAK TMR6_10_Dte_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_10_Dte_Handler
                B       TMR6_10_Dte_Handler

                PUBWEAK TMR6_10_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_10_SCmp_Handler
                B       TMR6_10_SCmp_Handler

                PUBWEAK TMR4_1_GCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR4_1_GCmp_Handler
                B       TMR4_1_GCmp_Handler

                PUBWEAK TMR4_1_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR4_1_Ovf_Udf_Handler
                B       TMR4_1_Ovf_Udf_Handler

                PUBWEAK TMR4_1_Reload_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR4_1_Reload_Handler
                B       TMR4_1_Reload_Handler

                PUBWEAK TMR4_1_SCmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMR4_1_SCmp_Handler
                B       TMR4_1_SCmp_Handler

                PUBWEAK CMP1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
CMP1_Handler
                B       CMP1_Handler

                PUBWEAK CMP2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
CMP2_Handler
                B       CMP2_Handler

                PUBWEAK CMP3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
CMP3_Handler
                B       CMP3_Handler

                PUBWEAK CMP4_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
CMP4_Handler
                B       CMP4_Handler

                PUBWEAK CAN1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_Handler
                B       CAN1_Handler

                PUBWEAK CAN2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_Handler
                B       CAN2_Handler

                PUBWEAK CAN3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
CAN3_Handler
                B       CAN3_Handler

                PUBWEAK USART1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART1_Handler
                B       USART1_Handler

                PUBWEAK USART2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART2_Handler
                B       USART2_Handler

                PUBWEAK SPI1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_Handler
                B       SPI1_Handler

                PUBWEAK SPI2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_Handler
                B       SPI2_Handler

                PUBWEAK TMRA_5_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_5_Ovf_Udf_Handler
                B       TMRA_5_Ovf_Udf_Handler

                PUBWEAK TMRA_5_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_5_Cmp_Handler
                B       TMRA_5_Cmp_Handler

                PUBWEAK TMRA_6_Ovf_Udf_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_6_Ovf_Udf_Handler
                B       TMRA_6_Ovf_Udf_Handler

                PUBWEAK TMRA_6_Cmp_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TMRA_6_Cmp_Handler
                B       TMRA_6_Cmp_Handler

                PUBWEAK USBFS_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USBFS_Handler
                B       USBFS_Handler

                PUBWEAK EVENT_PORT1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EVENT_PORT1_Handler
                B       EVENT_PORT1_Handler

                PUBWEAK EVENT_PORT2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EVENT_PORT2_Handler
                B       EVENT_PORT2_Handler

                PUBWEAK EVENT_PORT3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EVENT_PORT3_Handler
                B       EVENT_PORT3_Handler

                PUBWEAK EVENT_PORT4_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EVENT_PORT4_Handler
                B       EVENT_PORT4_Handler

                PUBWEAK USART3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART3_Handler
                B       USART3_Handler

                PUBWEAK USART4_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART4_Handler
                B       USART4_Handler

                PUBWEAK SPI3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SPI3_Handler
                B       SPI3_Handler

                PUBWEAK SPI4_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SPI4_Handler
                B       SPI4_Handler

                PUBWEAK EMB_GR0_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EMB_GR0_Handler
                B       EMB_GR0_Handler

                PUBWEAK EMB_GR1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EMB_GR1_Handler
                B       EMB_GR1_Handler

                PUBWEAK EMB_GR2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EMB_GR2_Handler
                B       EMB_GR2_Handler

                PUBWEAK EMB_GR3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EMB_GR3_Handler
                B       EMB_GR3_Handler

                PUBWEAK EMB_GR4_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EMB_GR4_Handler
                B       EMB_GR4_Handler

                PUBWEAK EMB_GR5_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EMB_GR5_Handler
                B       EMB_GR5_Handler

                PUBWEAK EMB_GR6_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
EMB_GR6_Handler
                B       EMB_GR6_Handler

                PUBWEAK HASH_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
HASH_Handler
                B       HASH_Handler

                PUBWEAK USART5_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART5_Handler
                B       USART5_Handler

                PUBWEAK USART6_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART6_Handler
                B       USART6_Handler

                PUBWEAK MDIO_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
MDIO_Handler
                B       MDIO_Handler

                PUBWEAK PLA_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PLA_Handler
                B       PLA_Handler

                PUBWEAK I2C1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_Handler
                B       I2C1_Handler

                PUBWEAK I2C2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_Handler
                B       I2C2_Handler

                PUBWEAK I2C3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_Handler
                B       I2C3_Handler

                PUBWEAK USART1_WKUP_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART1_WKUP_Handler
                B       USART1_WKUP_Handler

                PUBWEAK PWC_LVD1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PWC_LVD1_Handler
                B       PWC_LVD1_Handler

                PUBWEAK PWC_LVD2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PWC_LVD2_Handler
                B       PWC_LVD2_Handler

                PUBWEAK OTS_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
OTS_Handler
                B       OTS_Handler

                PUBWEAK FCM_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
FCM_Handler
                B       FCM_Handler

                PUBWEAK WDT_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
WDT_Handler
                B       WDT_Handler

                PUBWEAK CTC_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
CTC_Handler
                B       CTC_Handler

                PUBWEAK ADC1_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
ADC1_Handler
                B       ADC1_Handler

                PUBWEAK ADC2_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
ADC2_Handler
                B       ADC2_Handler

                PUBWEAK ADC3_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
ADC3_Handler
                B       ADC3_Handler

                PUBWEAK TRNG_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
TRNG_Handler
                B       TRNG_Handler

                PUBWEAK USART1_TxComplete_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART1_TxComplete_Handler
                B       USART1_TxComplete_Handler

                PUBWEAK USART2_TxComplete_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART2_TxComplete_Handler
                B       USART2_TxComplete_Handler

                PUBWEAK USART3_TxComplete_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART3_TxComplete_Handler
                B       USART3_TxComplete_Handler

                PUBWEAK USART4_TxComplete_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART4_TxComplete_Handler
                B       USART4_TxComplete_Handler

                PUBWEAK USART5_TxComplete_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART5_TxComplete_Handler
                B       USART5_TxComplete_Handler

                PUBWEAK USART6_TxComplete_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART6_TxComplete_Handler
                B       USART6_TxComplete_Handler

                END
