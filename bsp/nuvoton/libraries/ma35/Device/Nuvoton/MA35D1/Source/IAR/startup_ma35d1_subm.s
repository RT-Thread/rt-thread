;/******************************************************************************
; * @file     startup_subm.s
; * @brief    CMSIS Cortex-M4 Core Device Startup File
; *
; * SPDX-License-Identifier: Apache-2.0
; * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
;*****************************************************************************/

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  HardFault_Handler
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
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     LVD_IRQHandler            ; 0
        DCD     Default_Handler           ; 1
        DCD     PWRWU_IRQHandler          ; 2
        DCD     HWSEM0_IRQHandler         ; 3
        DCD     CKFAIL_IRQHandler         ; 4
        DCD     WHC0_IRQHandler           ; 5
        DCD     RTC_IRQHandler            ; 6
        DCD     TAMPER_IRQHandler         ; 7
        DCD     WDT2_IRQHandler           ; 8
        DCD     WWDT2_IRQHandler          ; 9
        DCD     EINT0_IRQHandler          ; 10
        DCD     EINT1_IRQHandler          ; 11
        DCD     EINT2_IRQHandler          ; 12
        DCD     EINT3_IRQHandler          ; 13
        DCD     Default_Handler           ; 14
        DCD     Default_Handler           ; 15
        DCD     GPA_IRQHandler            ; 16
        DCD     GPB_IRQHandler            ; 17
        DCD     GPC_IRQHandler            ; 18
        DCD     GPD_IRQHandler            ; 19
        DCD     Default_Handler           ; 20
        DCD     Default_Handler           ; 21
        DCD     TMR2_IRQHandler           ; 22
        DCD     TMR3_IRQHandler           ; 23
        DCD     BRAKE0_IRQHandler         ; 24
        DCD     EPWM0P0_IRQHandler        ; 25
        DCD     EPWM0P1_IRQHandler        ; 26
        DCD     EPWM0P2_IRQHandler        ; 27
        DCD     QEI0_IRQHandler           ; 28
        DCD     ECAP0_IRQHandler          ; 29
        DCD     Default_Handler           ; 30
        DCD     QSPI1_IRQHandler          ; 31
        DCD     Default_Handler           ; 32
        DCD     Default_Handler           ; 33
        DCD     Default_Handler           ; 34
        DCD     UART1_IRQHandler          ; 35
        DCD     UART2_IRQHandler          ; 36
        DCD     UART3_IRQHandler          ; 37
        DCD     UART4_IRQHandler          ; 38
        DCD     UART5_IRQHandler          ; 39
        DCD     EADC00_IRQHandler         ; 40
        DCD     EADC01_IRQHandler         ; 41
        DCD     EADC02_IRQHandler         ; 42
        DCD     EADC03_IRQHandler         ; 43
        DCD     Default_Handler           ; 44
        DCD     I2C1_IRQHandler           ; 45
        DCD     I2S0_IRQHandler           ; 46
        DCD     MCAN00_IRQHandler         ; 47
        DCD     SC0_IRQHandler            ; 48
        DCD     GPE_IRQHandler            ; 49
        DCD     GPF_IRQHandler            ; 50
        DCD     GPG_IRQHandler            ; 51
        DCD     GPH_IRQHandler            ; 52
        DCD     GPI_IRQHandler            ; 53
        DCD     GPJ_IRQHandler            ; 54
        DCD     TMR4_IRQHandler           ; 55
        DCD     TMR5_IRQHandler           ; 56
        DCD     TMR6_IRQHandler           ; 57
        DCD     TMR7_IRQHandler           ; 58
        DCD     BRAKE1_IRQHandler         ; 59
        DCD     EPWM1P0_IRQHandler        ; 60
        DCD     EPWM1P1_IRQHandler        ; 61
        DCD     EPWM1P2_IRQHandler        ; 62
        DCD     QEI1_IRQHandler           ; 63
        DCD     ECAP1_IRQHandler          ; 64
        DCD     SPI0_IRQHandler           ; 65
        DCD     SPI1_IRQHandler           ; 66
        DCD     PDMA2_IRQHandler          ; 67
        DCD     PDMA3_IRQHandler          ; 68
        DCD     UART6_IRQHandler          ; 69
        DCD     UART7_IRQHandler          ; 70
        DCD     UART8_IRQHandler          ; 71
        DCD     UART9_IRQHandler          ; 72
        DCD     UART10_IRQHandler         ; 73
        DCD     UART11_IRQHandler         ; 74
        DCD     I2C2_IRQHandler           ; 75
        DCD     I2C3_IRQHandler           ; 76
        DCD     I2S1_IRQHandler           ; 77
        DCD     MACN10_IRQHandler         ; 78
        DCD     SC1_IRQHandler            ; 79
        DCD     GPK_IRQHandler            ; 80
        DCD     GPL_IRQHandler            ; 81
        DCD     GPM_IRQHandler            ; 82
        DCD     GPN_IRQHandler            ; 83
        DCD     TMR8_IRQHandler           ; 84
        DCD     TMR9_IRQHandler           ; 85
        DCD     TMR10_IRQHandler          ; 86
        DCD     TMR11_IRQHandler          ; 87
        DCD     BRAKE2_IRQHandler         ; 88
        DCD     EPWM2P0_IRQHandle         ; 89
        DCD     EPWM2P1_IRQHandle         ; 90
        DCD     EPWM2P2_IRQHandle         ; 91
        DCD     QEI2_IRQHandler           ; 92
        DCD     ECAP2_IRQHandler          ; 93
        DCD     SPI2_IRQHandler           ; 94
        DCD     SPI3_IRQHandler           ; 95
        DCD     UART12_IRQHandler         ; 96
        DCD     UART13_IRQHandler         ; 97
        DCD     UART14_IRQHandler         ; 98
        DCD     UART15_IRQHandler         ; 99
        DCD     UART16_IRQHandler         ; 100
        DCD     I2C4_IRQHandler           ; 101
        DCD     I2C5_IRQHandler           ; 102
        DCD     MCAN20_IRQHandler         ; 103
        DCD     MCAN30_IRQHandler         ; 104
        DCD     KPI_IRQHandler            ; 105
        DCD     MCAN01_IRQHandler         ; 106
        DCD     MCAN11_IRQHandler         ; 107
        DCD     MCAN21_IRQHandler         ; 108
        DCD     MCAN31_IRQHandler         ; 109
        DCD     ADC0_IRQHandler           ; 110
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

        LDR     R0, =SystemInit
        BLX     R0

        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK  LVD_IRQHandler
        PUBWEAK  PWRWU_IRQHandler
        PUBWEAK  HWSEM0_IRQHandler
        PUBWEAK  CKFAIL_IRQHandler
        PUBWEAK  WHC0_IRQHandler
        PUBWEAK  RTC_IRQHandler
        PUBWEAK  TAMPER_IRQHandler
        PUBWEAK  WDT2_IRQHandler
        PUBWEAK  WWDT2_IRQHandler
        PUBWEAK  EINT0_IRQHandler
        PUBWEAK  EINT1_IRQHandler
        PUBWEAK  EINT2_IRQHandler
        PUBWEAK  EINT3_IRQHandler
        PUBWEAK  GPA_IRQHandler
        PUBWEAK  GPB_IRQHandler
        PUBWEAK  GPC_IRQHandler
        PUBWEAK  GPD_IRQHandler
        PUBWEAK  TMR2_IRQHandler
        PUBWEAK  TMR3_IRQHandler
        PUBWEAK  BRAKE0_IRQHandler
        PUBWEAK  EPWM0P0_IRQHandler
        PUBWEAK  EPWM0P1_IRQHandler
        PUBWEAK  EPWM0P2_IRQHandler
        PUBWEAK  QEI0_IRQHandler
        PUBWEAK  ECAP0_IRQHandler
        PUBWEAK  QSPI1_IRQHandler
        PUBWEAK  UART1_IRQHandler
        PUBWEAK  UART2_IRQHandler
        PUBWEAK  UART3_IRQHandler
        PUBWEAK  UART4_IRQHandler
        PUBWEAK  UART5_IRQHandler
        PUBWEAK  EADC00_IRQHandler
        PUBWEAK  EADC01_IRQHandler
        PUBWEAK  EADC02_IRQHandler
        PUBWEAK  EADC03_IRQHandler
        PUBWEAK  I2C1_IRQHandler
        PUBWEAK  I2S0_IRQHandler
        PUBWEAK  MCAN00_IRQHandler
        PUBWEAK  SC0_IRQHandler
        PUBWEAK  GPE_IRQHandler
        PUBWEAK  GPF_IRQHandler
        PUBWEAK  GPG_IRQHandler
        PUBWEAK  GPH_IRQHandler
        PUBWEAK  GPI_IRQHandler
        PUBWEAK  GPJ_IRQHandler
        PUBWEAK  TMR4_IRQHandler
        PUBWEAK  TMR5_IRQHandler
        PUBWEAK  TMR6_IRQHandler
        PUBWEAK  TMR7_IRQHandler
        PUBWEAK  BRAKE1_IRQHandler
        PUBWEAK  EPWM1P0_IRQHandler
        PUBWEAK  EPWM1P1_IRQHandler
        PUBWEAK  EPWM1P2_IRQHandler
        PUBWEAK  QEI1_IRQHandler
        PUBWEAK  ECAP1_IRQHandler
        PUBWEAK  SPI0_IRQHandler
        PUBWEAK  SPI1_IRQHandler
        PUBWEAK  PDMA2_IRQHandler
        PUBWEAK  PDMA3_IRQHandler
        PUBWEAK  UART6_IRQHandler
        PUBWEAK  UART7_IRQHandler
        PUBWEAK  UART8_IRQHandler
        PUBWEAK  UART9_IRQHandler
        PUBWEAK  UART10_IRQHandler
        PUBWEAK  UART11_IRQHandler
        PUBWEAK  I2C2_IRQHandler
        PUBWEAK  I2C3_IRQHandler
        PUBWEAK  I2S1_IRQHandler
        PUBWEAK  MACN10_IRQHandler
        PUBWEAK  SC1_IRQHandler
        PUBWEAK  GPK_IRQHandler
        PUBWEAK  GPL_IRQHandler
        PUBWEAK  GPM_IRQHandler
        PUBWEAK  GPN_IRQHandler
        PUBWEAK  TMR8_IRQHandler
        PUBWEAK  TMR9_IRQHandler
        PUBWEAK  TMR10_IRQHandler
        PUBWEAK  TMR11_IRQHandler
        PUBWEAK  BRAKE2_IRQHandler
        PUBWEAK  EPWM2P0_IRQHandle
        PUBWEAK  EPWM2P1_IRQHandle
        PUBWEAK  EPWM2P2_IRQHandle
        PUBWEAK  QEI2_IRQHandler
        PUBWEAK  ECAP2_IRQHandler
        PUBWEAK  SPI2_IRQHandler
        PUBWEAK  SPI3_IRQHandler
        PUBWEAK  UART12_IRQHandler
        PUBWEAK  UART13_IRQHandler
        PUBWEAK  UART14_IRQHandler
        PUBWEAK  UART15_IRQHandler
        PUBWEAK  UART16_IRQHandler
        PUBWEAK  I2C4_IRQHandler
        PUBWEAK  I2C5_IRQHandler
        PUBWEAK  MCAN20_IRQHandler
        PUBWEAK  MCAN30_IRQHandler
        PUBWEAK  KPI_IRQHandler
        PUBWEAK  MCAN01_IRQHandler
        PUBWEAK  MCAN11_IRQHandler
        PUBWEAK  MCAN21_IRQHandler
        PUBWEAK  MCAN31_IRQHandler
        PUBWEAK  ADC0_IRQHandler

        SECTION .text:CODE:REORDER:NOROOT(1)

LVD_IRQHandler
PWRWU_IRQHandler
HWSEM0_IRQHandler
CKFAIL_IRQHandler
WHC0_IRQHandler
RTC_IRQHandler
TAMPER_IRQHandler
WDT2_IRQHandler
WWDT2_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
GPA_IRQHandler
GPB_IRQHandler
GPC_IRQHandler
GPD_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
BRAKE0_IRQHandler
EPWM0P0_IRQHandler
EPWM0P1_IRQHandler
EPWM0P2_IRQHandler
QEI0_IRQHandler
ECAP0_IRQHandler
QSPI1_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
EADC00_IRQHandler
EADC01_IRQHandler
EADC02_IRQHandler
EADC03_IRQHandler
I2C1_IRQHandler
I2S0_IRQHandler
MCAN00_IRQHandler
SC0_IRQHandler
GPE_IRQHandler
GPF_IRQHandler
GPG_IRQHandler
GPH_IRQHandler
GPI_IRQHandler
GPJ_IRQHandler
TMR4_IRQHandler
TMR5_IRQHandler
TMR6_IRQHandler
TMR7_IRQHandler
BRAKE1_IRQHandler
EPWM1P0_IRQHandler
EPWM1P1_IRQHandler
EPWM1P2_IRQHandler
QEI1_IRQHandler
ECAP1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
PDMA2_IRQHandler
PDMA3_IRQHandler
UART6_IRQHandler
UART7_IRQHandler
UART8_IRQHandler
UART9_IRQHandler
UART10_IRQHandler
UART11_IRQHandler
I2C2_IRQHandler
I2C3_IRQHandler
I2S1_IRQHandler
MACN10_IRQHandler
SC1_IRQHandler
GPK_IRQHandler
GPL_IRQHandler
GPM_IRQHandler
GPN_IRQHandler
TMR8_IRQHandler
TMR9_IRQHandler
TMR10_IRQHandler
TMR11_IRQHandler
BRAKE2_IRQHandler
EPWM2P0_IRQHandle
EPWM2P1_IRQHandle
EPWM2P2_IRQHandle
QEI2_IRQHandler
ECAP2_IRQHandler
SPI2_IRQHandler
SPI3_IRQHandler
UART12_IRQHandler
UART13_IRQHandler
UART14_IRQHandler
UART15_IRQHandler
UART16_IRQHandler
I2C4_IRQHandler
I2C5_IRQHandler
MCAN20_IRQHandler
MCAN30_IRQHandler
KPI_IRQHandler
MCAN01_IRQHandler
MCAN11_IRQHandler
MCAN21_IRQHandler
MCAN31_IRQHandler
ADC0_IRQHandler
Default_Handler
        B Default_Handler

        END

