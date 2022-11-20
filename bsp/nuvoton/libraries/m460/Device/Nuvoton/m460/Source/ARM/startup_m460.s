;/******************************************************************************
; * @file     startup_m460.s
; * @version  V3.00
; * @brief    CMSIS Cortex-M4 Core Device Startup File for M460
; *
; * @copyright SPDX-License-Identifier: Apache-2.0
; * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
;*****************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

	IF :LNOT: :DEF: Stack_Size
Stack_Size      EQU     0x00000800
	ENDIF

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

	IF :LNOT: :DEF: Heap_Size
Heap_Size       EQU     0x00000100
	ENDIF

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
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
                DCD     BMC_IRQHandler            ; 56: BMC
                DCD     SPI5_IRQHandler           ; 57: SPI5
                DCD     SC0_IRQHandler            ; 58: SC0
                DCD     SC1_IRQHandler            ; 59: SC1
                DCD     SC2_IRQHandler            ; 60: SC2
                DCD     GPJ_IRQHandler            ; 61: GPIO Port J
                DCD     SPI3_IRQHandler           ; 62: SPI3
                DCD     SPI4_IRQHandler           ; 63: SPI4
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
                DCD     EQEI0_IRQHandler          ; 84: EQEI0
                DCD     EQEI1_IRQHandler          ; 85: EQEI1
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
                DCD     CANFD20_IRQHandler        ; 120: CANFD2 interrupt source 0
                DCD     CANFD21_IRQHandler        ; 121: CANFD2 interrupt source 1
                DCD     CANFD30_IRQHandler        ; 122: CANFD3 interrupt source 0
                DCD     CANFD31_IRQHandler        ; 123: CANFD3 interrupt source 1
                DCD     EADC20_IRQHandler         ; 124: EADC2 interrupt source 0
                DCD     EADC21_IRQHandler         ; 125: EADC2 interrupt source 1
                DCD     EADC22_IRQHandler         ; 126: EADC2 interrupt source 2
                DCD     EADC23_IRQHandler         ; 127: EADC2 interrupt source 3


__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                ; Unlock Register
                LDR     R0, =0x40000100
                LDR     R1, =0x59
                STR     R1, [R0]
                LDR     R1, =0x16
                STR     R1, [R0]
                LDR     R1, =0x88
                STR     R1, [R0]

	IF :LNOT: :DEF: ENABLE_SPIM_CACHE
                LDR     R0, =0x40000200            ; R0 = Clock Controller Register Base Address
                LDR     R1, [R0,#0x4]              ; R1 = 0x40000204  (AHBCLK)
                ORR     R1, R1, #0x4000              
                STR     R1, [R0,#0x4]              ; CLK->AHBCLK |= CLK_AHBCLK_SPIMCKEN_Msk;
                
                LDR     R0, =0x40007000            ; R0 = SPIM Register Base Address
                LDR     R1, [R0,#4]                ; R1 = SPIM->CTL1
                ORR     R1, R1,#2                  ; R1 |= SPIM_CTL1_CACHEOFF_Msk
                STR     R1, [R0,#4]                ; _SPIM_DISABLE_CACHE()
                LDR     R1, [R0,#4]                ; R1 = SPIM->CTL1
                ORR     R1, R1, #4                 ; R1 |= SPIM_CTL1_CCMEN_Msk
                STR     R1, [R0,#4]                ; _SPIM_ENABLE_CCM()
	ENDIF

                LDR     R0, =SystemInit
                BLX     R0


                ; Lock
                LDR     R0, =0x40000100
                LDR     R1, =0
                STR     R1, [R0]

                LDR     R0, =__main
                BX      R0
 
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
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
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  IRC_IRQHandler            [WEAK]
                EXPORT  PWRWU_IRQHandler          [WEAK]
                EXPORT  RAMPE_IRQHandler          [WEAK]
                EXPORT  CKFAIL_IRQHandler         [WEAK]
                EXPORT  ISP_IRQHandler            [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  TAMPER_IRQHandler         [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  WWDT_IRQHandler           [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  EINT4_IRQHandler          [WEAK]
                EXPORT  EINT5_IRQHandler          [WEAK]
                EXPORT  GPA_IRQHandler            [WEAK]
                EXPORT  GPB_IRQHandler            [WEAK]
                EXPORT  GPC_IRQHandler            [WEAK]
                EXPORT  GPD_IRQHandler            [WEAK]
                EXPORT  GPE_IRQHandler            [WEAK]
                EXPORT  GPF_IRQHandler            [WEAK]
                EXPORT  QSPI0_IRQHandler          [WEAK]
                EXPORT  SPI0_IRQHandler           [WEAK]
                EXPORT  BRAKE0_IRQHandler         [WEAK]
                EXPORT  EPWM0P0_IRQHandler        [WEAK]
                EXPORT  EPWM0P1_IRQHandler        [WEAK]
                EXPORT  EPWM0P2_IRQHandler        [WEAK]
                EXPORT  BRAKE1_IRQHandler         [WEAK]
                EXPORT  EPWM1P0_IRQHandler        [WEAK]
                EXPORT  EPWM1P1_IRQHandler        [WEAK]
                EXPORT  EPWM1P2_IRQHandler        [WEAK]
                EXPORT  TMR0_IRQHandler           [WEAK]
                EXPORT  TMR1_IRQHandler           [WEAK]
                EXPORT  TMR2_IRQHandler           [WEAK]
                EXPORT  TMR3_IRQHandler           [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  PDMA0_IRQHandler          [WEAK]
                EXPORT  DAC_IRQHandler            [WEAK]
                EXPORT  EADC00_IRQHandler         [WEAK]
                EXPORT  EADC01_IRQHandler         [WEAK]
                EXPORT  ACMP01_IRQHandler         [WEAK]
                EXPORT  ACMP23_IRQHandler         [WEAK]
                EXPORT  EADC02_IRQHandler         [WEAK]
                EXPORT  EADC03_IRQHandler         [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  QSPI1_IRQHandler          [WEAK]
                EXPORT  SPI1_IRQHandler           [WEAK]
                EXPORT  SPI2_IRQHandler           [WEAK]
                EXPORT  USBD_IRQHandler           [WEAK]
                EXPORT  OHCI_IRQHandler           [WEAK]
                EXPORT  USBOTG_IRQHandler         [WEAK]
                EXPORT  BMC_IRQHandler            [WEAK]
                EXPORT  SPI5_IRQHandler           [WEAK]
                EXPORT  SC0_IRQHandler            [WEAK]
                EXPORT  SC1_IRQHandler            [WEAK]
                EXPORT  SC2_IRQHandler            [WEAK]
                EXPORT  GPJ_IRQHandler            [WEAK]
                EXPORT  SPI3_IRQHandler           [WEAK]
                EXPORT  SPI4_IRQHandler           [WEAK]
                EXPORT  SDH0_IRQHandler           [WEAK]
                EXPORT  USBD20_IRQHandler         [WEAK]
                EXPORT  EMAC0_IRQHandler          [WEAK]
                EXPORT  I2S0_IRQHandler           [WEAK]
                EXPORT  I2S1_IRQHandler           [WEAK]
                EXPORT  SPI6_IRQHandler           [WEAK]
                EXPORT  CRPT_IRQHandler           [WEAK]
                EXPORT  GPG_IRQHandler            [WEAK]
                EXPORT  EINT6_IRQHandler          [WEAK]
                EXPORT  UART4_IRQHandler          [WEAK]
                EXPORT  UART5_IRQHandler          [WEAK]
                EXPORT  USCI0_IRQHandler          [WEAK]
                EXPORT  SPI7_IRQHandler           [WEAK]
                EXPORT  BPWM0_IRQHandler          [WEAK]
                EXPORT  BPWM1_IRQHandler          [WEAK]
                EXPORT  SPIM_IRQHandler           [WEAK]
                EXPORT  CCAP_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  I2C3_IRQHandler           [WEAK]
                EXPORT  EQEI0_IRQHandler          [WEAK]
                EXPORT  EQEI1_IRQHandler          [WEAK]
                EXPORT  ECAP0_IRQHandler          [WEAK]
                EXPORT  ECAP1_IRQHandler          [WEAK]
                EXPORT  GPH_IRQHandler            [WEAK]
                EXPORT  EINT7_IRQHandler          [WEAK]
                EXPORT  SDH1_IRQHandler           [WEAK]
                EXPORT  PSIO_IRQHandler           [WEAK]
                EXPORT  EHCI_IRQHandler           [WEAK]
                EXPORT  USBOTG20_IRQHandler       [WEAK]
                EXPORT  ECAP2_IRQHandler          [WEAK]
                EXPORT  ECAP3_IRQHandler          [WEAK]
                EXPORT  KPI_IRQHandler            [WEAK]
                EXPORT  HBI_IRQHandler            [WEAK]
                EXPORT  PDMA1_IRQHandler          [WEAK]
                EXPORT  UART8_IRQHandler          [WEAK]
                EXPORT  UART9_IRQHandler          [WEAK]
                EXPORT  TRNG_IRQHandler           [WEAK]
                EXPORT  UART6_IRQHandler          [WEAK]
                EXPORT  UART7_IRQHandler          [WEAK]
                EXPORT  EADC10_IRQHandler         [WEAK]
                EXPORT  EADC11_IRQHandler         [WEAK]
                EXPORT  EADC12_IRQHandler         [WEAK]
                EXPORT  EADC13_IRQHandler         [WEAK]
                EXPORT  SPI8_IRQHandler           [WEAK]
                EXPORT  KS_IRQHandler             [WEAK]
                EXPORT  GPI_IRQHandler            [WEAK]
                EXPORT  SPI9_IRQHandler           [WEAK]
                EXPORT  CANFD00_IRQHandler        [WEAK]
                EXPORT  CANFD01_IRQHandler        [WEAK]
                EXPORT  CANFD10_IRQHandler        [WEAK]
                EXPORT  CANFD11_IRQHandler        [WEAK]
                EXPORT  EQEI2_IRQHandler          [WEAK]
                EXPORT  EQEI3_IRQHandler          [WEAK]
                EXPORT  I2C4_IRQHandler           [WEAK]
                EXPORT  SPI10_IRQHandler          [WEAK]
                EXPORT  CANFD20_IRQHandler        [WEAK]
                EXPORT  CANFD21_IRQHandler        [WEAK]
                EXPORT  CANFD30_IRQHandler        [WEAK]
                EXPORT  CANFD31_IRQHandler        [WEAK]
                EXPORT  EADC20_IRQHandler         [WEAK]
                EXPORT  EADC21_IRQHandler         [WEAK]
                EXPORT  EADC22_IRQHandler         [WEAK]
                EXPORT  EADC23_IRQHandler         [WEAK]


Default__IRQHandler
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
BMC_IRQHandler
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


                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
