;/******************************************************************************
; * @file     startup_M460.s
; * @version  V3.00
; * @brief    CMSIS Cortex-M4 Core Device Startup File for M460
; *
; * @copyright SPDX-License-Identifier: Apache-2.0
; * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
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
        DCD     BOD_IRQHandler            ; 0: Brown Out detection
        DCD     IRC_IRQHandler            ; 1: Internal RC
        DCD     PWRWU_IRQHandler          ; 2: Power down wake up
        DCD     RAMPE_IRQHandler          ; 3: RAM parity error
        DCD     CKFAIL_IRQHandler         ; 4: Clock detection fail
        DCD     ISP_IRQHandler            ; 5: ISP
        DCD     RTC_IRQHandler            ; 6: Real Time Clock
        DCD     TAMPER_IRQHandler         ; 7: Tamper detection
        DCD     WDT_IRQHandler            ; 8: Watchdog timer
        DCD     WWDT_IRQHandler           ; 9: Window watchdog timer
        DCD     EINT0_IRQHandler          ; 10: External Input 0
        DCD     EINT1_IRQHandler          ; 11: External Input 1
        DCD     EINT2_IRQHandler          ; 12: External Input 2
        DCD     EINT3_IRQHandler          ; 13: External Input 3
        DCD     EINT4_IRQHandler          ; 14: External Input 4
        DCD     EINT5_IRQHandler          ; 15: External Input 5
        DCD     GPA_IRQHandler            ; 16: GPIO Port A
        DCD     GPB_IRQHandler            ; 17: GPIO Port B
        DCD     GPC_IRQHandler            ; 18: GPIO Port C
        DCD     GPD_IRQHandler            ; 19: GPIO Port D
        DCD     GPE_IRQHandler            ; 20: GPIO Port E
        DCD     GPF_IRQHandler            ; 21: GPIO Port F
        DCD     QSPI0_IRQHandler          ; 22: QSPI0
        DCD     SPI0_IRQHandler           ; 23: SPI0
        DCD     BRAKE0_IRQHandler         ; 24: EPWM0 brake
        DCD     EPWM0P0_IRQHandler        ; 25: EPWM0 pair 0
        DCD     EPWM0P1_IRQHandler        ; 26: EPWM0 pair 1
        DCD     EPWM0P2_IRQHandler        ; 27: EPWM0 pair 2
        DCD     BRAKE1_IRQHandler         ; 28: EPWM1 brake
        DCD     EPWM1P0_IRQHandler        ; 29: EPWM1 pair 0
        DCD     EPWM1P1_IRQHandler        ; 30: EPWM1 pair 1
        DCD     EPWM1P2_IRQHandler        ; 31: EPWM1 pair 2
        DCD     TMR0_IRQHandler           ; 32: Timer 0
        DCD     TMR1_IRQHandler           ; 33: Timer 1
        DCD     TMR2_IRQHandler           ; 34: Timer 2
        DCD     TMR3_IRQHandler           ; 35: Timer 3
        DCD     UART0_IRQHandler          ; 36: UART0
        DCD     UART1_IRQHandler          ; 37: UART1
        DCD     I2C0_IRQHandler           ; 38: I2C0
        DCD     I2C1_IRQHandler           ; 39: I2C1
        DCD     PDMA0_IRQHandler          ; 40: Peripheral DMA 0
        DCD     DAC_IRQHandler            ; 41: DAC
        DCD     EADC00_IRQHandler         ; 42: EADC0 interrupt source 0
        DCD     EADC01_IRQHandler         ; 43: EADC0 interrupt source 1
        DCD     ACMP01_IRQHandler         ; 44: ACMP0 and ACMP1
        DCD     ACMP23_IRQHandler         ; 45: ACMP2 and ACMP3
        DCD     EADC02_IRQHandler         ; 46: EADC0 interrupt source 2
        DCD     EADC03_IRQHandler         ; 47: EADC0 interrupt source 3
        DCD     UART2_IRQHandler          ; 48: UART2
        DCD     UART3_IRQHandler          ; 49: UART3
        DCD     QSPI1_IRQHandler          ; 50: QSPI1
        DCD     SPI1_IRQHandler           ; 51: SPI1
        DCD     SPI2_IRQHandler           ; 52: SPI2
        DCD     USBD_IRQHandler           ; 53: USB device
        DCD     OHCI_IRQHandler           ; 54: OHCI
        DCD     USBOTG_IRQHandler         ; 55: USB OTG
        DCD     BMC_Handler               ; 56: BMC
        DCD     SPI5_IRQHandler           ; 57: SPI5
        DCD     SC0_IRQHandler            ; 58: SC0
        DCD     SC1_IRQHandler            ; 59: SC1
        DCD     SC2_IRQHandler            ; 60: SC2
        DCD     GPJ_IRQHandler            ; 61: GPIO Port J
        DCD     SPI3_IRQHandler           ; 62: SPI3
        DCD     Default_Handler           ; 63:
        DCD     SDH0_IRQHandler           ; 64: SDH0
        DCD     USBD20_IRQHandler         ; 65: USBD20
        DCD     EMAC0_IRQHandler          ; 66: EMAC0
        DCD     Default_Handler           ; 67:
        DCD     I2S0_IRQHandler           ; 68: I2S0
        DCD     I2S1_IRQHandler           ; 69: I2S1
        DCD     SPI6_IRQHandler           ; 70: SPI6
        DCD     CRPT_IRQHandler           ; 71: CRYPTO
        DCD     GPG_IRQHandler            ; 72: GPIO Port G
        DCD     EINT6_IRQHandler          ; 73: External Input 6
        DCD     UART4_IRQHandler          ; 74: UART4
        DCD     UART5_IRQHandler          ; 75: UART5
        DCD     USCI0_IRQHandler          ; 76: USCI0
        DCD     SPI7_IRQHandler           ; 77: SPI7
        DCD     BPWM0_IRQHandler          ; 78: BPWM0
        DCD     BPWM1_IRQHandler          ; 79: BPWM1
        DCD     SPIM_IRQHandler           ; 80: SPIM
        DCD     CCAP_IRQHandler           ; 81: CCAP
        DCD     I2C2_IRQHandler           ; 82: I2C2
        DCD     I2C3_IRQHandler           ; 83: I2C3
        DCD     EQEI0_IRQHandler          ; 84: QEI0
        DCD     EQEI1_IRQHandler          ; 85: QEI1
        DCD     ECAP0_IRQHandler          ; 86: ECAP0
        DCD     ECAP1_IRQHandler          ; 87: ECAP1
        DCD     GPH_IRQHandler            ; 88: GPIO Port H
        DCD     EINT7_IRQHandler          ; 89: External Input 7
        DCD     SDH1_IRQHandler           ; 90: SDH1
        DCD     PSIO_IRQHandler           ; 91: PSIO
        DCD     EHCI_IRQHandler           ; 92: EHCI
        DCD     USBOTG20_IRQHandler       ; 93: HSOTG
        DCD     ECAP2_IRQHandler          ; 94: ECAP2
        DCD     ECAP3_IRQHandler          ; 95: ECAP3
        DCD     KPI_IRQHandler            ; 96: KPI
        DCD     HBI_IRQHandler            ; 97: HBI
        DCD     PDMA1_IRQHandler          ; 98: Peripheral DMA 1
        DCD     UART8_IRQHandler          ; 99: UART8
        DCD     UART9_IRQHandler          ; 100: UART9
        DCD     TRNG_IRQHandler           ; 101: TRNG
        DCD     UART6_IRQHandler          ; 102: UART6
        DCD     UART7_IRQHandler          ; 103: UART7
        DCD     EADC10_IRQHandler         ; 104: EADC1 interrupt source 0
        DCD     EADC11_IRQHandler         ; 105: EADC1 interrupt source 1
        DCD     EADC12_IRQHandler         ; 106: EADC1 interrupt source 2
        DCD     EADC13_IRQHandler         ; 107: EADC1 interrupt source 3
        DCD     SPI8_IRQHandler           ; 108: SPI8
        DCD     KS_IRQHandler             ; 109: Key Store
        DCD     GPI_IRQHandler            ; 110: GPIO Port I
        DCD     SPI9_IRQHandler           ; 111: SPI9
        DCD     CANFD00_IRQHandler        ; 112: CANFD0 interrupt source 0
        DCD     CANFD01_IRQHandler        ; 113: CANFD0 interrupt source 1
        DCD     CANFD10_IRQHandler        ; 114: CANFD1 interrupt source 0
        DCD     CANFD11_IRQHandler        ; 115: CANFD1 interrupt source 1
        DCD     EQEI2_IRQHandler          ; 116: EQEI2
        DCD     EQEI3_IRQHandler          ; 117: EQEI3
        DCD     I2C4_IRQHandler           ; 118: I2C4
        DCD     SPI10_IRQHandler          ; 119: SPI10
        DCD     CANFD20_IRQHandler        ; 112: CANFD2 interrupt source 0
        DCD     CANFD21_IRQHandler        ; 113: CANFD2 interrupt source 1
        DCD     CANFD30_IRQHandler        ; 114: CANFD3 interrupt source 0
        DCD     CANFD31_IRQHandler        ; 115: CANFD4 interrupt source 1
        DCD     EADC20_IRQHandler         ; 104: EADC2 interrupt source 0
        DCD     EADC21_IRQHandler         ; 105: EADC2 interrupt source 1
        DCD     EADC22_IRQHandler         ; 106: EADC2 interrupt source 2
        DCD     EADC23_IRQHandler         ; 107: EADC2 interrupt source 3
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

        LDR      R0, =SystemInit
        BLX      R0
        LDR      R0, =__iar_program_start
        BX       R0

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

        PUBWEAK  BOD_IRQHandler
        PUBWEAK  IRC_IRQHandler
        PUBWEAK  PWRWU_IRQHandler
        PUBWEAK  RAMPE_IRQHandler
        PUBWEAK  CKFAIL_IRQHandler
        PUBWEAK  ISP_IRQHandler
        PUBWEAK  RTC_IRQHandler
        PUBWEAK  TAMPER_IRQHandler
        PUBWEAK  WDT_IRQHandler
        PUBWEAK  WWDT_IRQHandler
        PUBWEAK  EINT0_IRQHandler
        PUBWEAK  EINT1_IRQHandler
        PUBWEAK  EINT2_IRQHandler
        PUBWEAK  EINT3_IRQHandler
        PUBWEAK  EINT4_IRQHandler
        PUBWEAK  EINT5_IRQHandler
        PUBWEAK  GPA_IRQHandler
        PUBWEAK  GPB_IRQHandler
        PUBWEAK  GPC_IRQHandler
        PUBWEAK  GPD_IRQHandler
        PUBWEAK  GPE_IRQHandler
        PUBWEAK  GPF_IRQHandler
        PUBWEAK  QSPI0_IRQHandler
        PUBWEAK  SPI0_IRQHandler
        PUBWEAK  BRAKE0_IRQHandler
        PUBWEAK  EPWM0P0_IRQHandler
        PUBWEAK  EPWM0P1_IRQHandler
        PUBWEAK  EPWM0P2_IRQHandler
        PUBWEAK  BRAKE1_IRQHandler
        PUBWEAK  EPWM1P0_IRQHandler
        PUBWEAK  EPWM1P1_IRQHandler
        PUBWEAK  EPWM1P2_IRQHandler
        PUBWEAK  TMR0_IRQHandler
        PUBWEAK  TMR1_IRQHandler
        PUBWEAK  TMR2_IRQHandler
        PUBWEAK  TMR3_IRQHandler
        PUBWEAK  UART0_IRQHandler
        PUBWEAK  UART1_IRQHandler
        PUBWEAK  I2C0_IRQHandler
        PUBWEAK  I2C1_IRQHandler
        PUBWEAK  PDMA0_IRQHandler
        PUBWEAK  DAC_IRQHandler
        PUBWEAK  EADC00_IRQHandler
        PUBWEAK  EADC01_IRQHandler
        PUBWEAK  ACMP01_IRQHandler
        PUBWEAK  ACMP23_IRQHandler
        PUBWEAK  EADC02_IRQHandler
        PUBWEAK  EADC03_IRQHandler
        PUBWEAK  UART2_IRQHandler
        PUBWEAK  UART3_IRQHandler
        PUBWEAK  QSPI1_IRQHandler
        PUBWEAK  SPI1_IRQHandler
        PUBWEAK  SPI2_IRQHandler
        PUBWEAK  USBD_IRQHandler
        PUBWEAK  OHCI_IRQHandler
        PUBWEAK  USBOTG_IRQHandler
        PUBWEAK  BMC_Handler
        PUBWEAK  SPI5_IRQHandler
        PUBWEAK  SC0_IRQHandler
        PUBWEAK  SC1_IRQHandler
        PUBWEAK  SC2_IRQHandler
        PUBWEAK  GPJ_IRQHandler
        PUBWEAK  SPI3_IRQHandler
        PUBWEAK  SPI4_IRQHandler
        PUBWEAK  SDH0_IRQHandler
        PUBWEAK  USBD20_IRQHandler
        PUBWEAK  EMAC0_IRQHandler
        PUBWEAK  I2S0_IRQHandler
        PUBWEAK  I2S1_IRQHandler
        PUBWEAK  SPI6_IRQHandler
        PUBWEAK  CRPT_IRQHandler
        PUBWEAK  GPG_IRQHandler
        PUBWEAK  EINT6_IRQHandler
        PUBWEAK  UART4_IRQHandler
        PUBWEAK  UART5_IRQHandler
        PUBWEAK  USCI0_IRQHandler
        PUBWEAK  SPI7_IRQHandler
        PUBWEAK  BPWM0_IRQHandler
        PUBWEAK  BPWM1_IRQHandler
        PUBWEAK  SPIM_IRQHandler
        PUBWEAK  CCAP_IRQHandler
        PUBWEAK  I2C2_IRQHandler
        PUBWEAK  I2C3_IRQHandler
        PUBWEAK  EQEI0_IRQHandler
        PUBWEAK  EQEI1_IRQHandler
        PUBWEAK  ECAP0_IRQHandler
        PUBWEAK  ECAP1_IRQHandler
        PUBWEAK  GPH_IRQHandler
        PUBWEAK  EINT7_IRQHandler
        PUBWEAK  SDH1_IRQHandler
        PUBWEAK  PSIO_IRQHandler
        PUBWEAK  EHCI_IRQHandler
        PUBWEAK  USBOTG20_IRQHandler
        PUBWEAK  ECAP2_IRQHandler
        PUBWEAK  ECAP3_IRQHandler
        PUBWEAK  KPI_IRQHandler
        PUBWEAK  HBI_IRQHandler
        PUBWEAK  PDMA1_IRQHandler
        PUBWEAK  UART8_IRQHandler
        PUBWEAK  UART9_IRQHandler
        PUBWEAK  TRNG_IRQHandler
        PUBWEAK  UART6_IRQHandler
        PUBWEAK  UART7_IRQHandler
        PUBWEAK  EADC10_IRQHandler
        PUBWEAK  EADC11_IRQHandler
        PUBWEAK  EADC12_IRQHandler
        PUBWEAK  EADC13_IRQHandler
        PUBWEAK  SPI8_IRQHandler
        PUBWEAK  GPI_IRQHandler
        PUBWEAK  SPI9_IRQHandler
        PUBWEAK  CANFD00_IRQHandler
        PUBWEAK  CANFD01_IRQHandler
        PUBWEAK  CANFD10_IRQHandler
        PUBWEAK  CANFD11_IRQHandler
        PUBWEAK  EQEI2_IRQHandler
        PUBWEAK  EQEI3_IRQHandler
        PUBWEAK  I2C4_IRQHandler
        PUBWEAK  SPI10_IRQHandler
        PUBWEAK  CANFD20_IRQHandler
        PUBWEAK  CANFD21_IRQHandler
        PUBWEAK  CANFD30_IRQHandler
        PUBWEAK  CANFD31_IRQHandler
        PUBWEAK  EADC20_IRQHandler
        PUBWEAK  EADC21_IRQHandler
        PUBWEAK  EADC22_IRQHandler
        PUBWEAK  EADC23_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)

BOD_IRQHandler
IRC_IRQHandler
PWRWU_IRQHandler
RAMPE_IRQHandler
CKFAIL_IRQHandler
ISP_IRQHandler
RTC_IRQHandler
TAMPER_IRQHandler
WDT_IRQHandler
WWDT_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
EINT4_IRQHandler
EINT5_IRQHandler
GPA_IRQHandler
GPB_IRQHandler
GPC_IRQHandler
GPD_IRQHandler
GPE_IRQHandler
GPF_IRQHandler
QSPI0_IRQHandler
SPI0_IRQHandler
BRAKE0_IRQHandler
EPWM0P0_IRQHandler
EPWM0P1_IRQHandler
EPWM0P2_IRQHandler
BRAKE1_IRQHandler
EPWM1P0_IRQHandler
EPWM1P1_IRQHandler
EPWM1P2_IRQHandler
TMR0_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
PDMA0_IRQHandler
DAC_IRQHandler
EADC00_IRQHandler
EADC01_IRQHandler
ACMP01_IRQHandler
ACMP23_IRQHandler
EADC02_IRQHandler
EADC03_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
QSPI1_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USBD_IRQHandler
OHCI_IRQHandler
USBOTG_IRQHandler
BMC_Handler
SPI5_IRQHandler
SC0_IRQHandler
SC1_IRQHandler
SC2_IRQHandler
GPJ_IRQHandler
SPI3_IRQHandler
SPI4_IRQHandler
SDH0_IRQHandler
USBD20_IRQHandler
EMAC0_IRQHandler
I2S0_IRQHandler
I2S1_IRQHandler
SPI6_IRQHandler
CRPT_IRQHandler
GPG_IRQHandler
EINT6_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
USCI0_IRQHandler
SPI7_IRQHandler
BPWM0_IRQHandler
BPWM1_IRQHandler
SPIM_IRQHandler
CCAP_IRQHandler
I2C2_IRQHandler
I2C3_IRQHandler
EQEI0_IRQHandler
EQEI1_IRQHandler
ECAP0_IRQHandler
ECAP1_IRQHandler
GPH_IRQHandler
EINT7_IRQHandler
SDH1_IRQHandler
PSIO_IRQHandler
EHCI_IRQHandler
USBOTG20_IRQHandler
ECAP2_IRQHandler
ECAP3_IRQHandler
KPI_IRQHandler
HBI_IRQHandler
PDMA1_IRQHandler
UART8_IRQHandler
UART9_IRQHandler
TRNG_IRQHandler
UART6_IRQHandler
UART7_IRQHandler
EADC10_IRQHandler
EADC11_IRQHandler
EADC12_IRQHandler
EADC13_IRQHandler
SPI8_IRQHandler
KS_IRQHandler
GPI_IRQHandler
SPI9_IRQHandler
CANFD00_IRQHandler
CANFD01_IRQHandler
CANFD10_IRQHandler
CANFD11_IRQHandler
EQEI2_IRQHandler
EQEI3_IRQHandler
I2C4_IRQHandler
SPI10_IRQHandler
CANFD20_IRQHandler
CANFD21_IRQHandler
CANFD30_IRQHandler
CANFD31_IRQHandler
EADC20_IRQHandler
EADC21_IRQHandler
EADC22_IRQHandler
EADC23_IRQHandler
Default_Handler
        B Default_Handler




        END
