;/******************************************************************************
; * @file     startup_NUC472_442.s
; * @version  V1.00
; * $Revision: 11 $
; * $Date: 16/06/07 2:34p $ 
; * @brief    CMSIS ARM Cortex-M4 Core Device Startup File
; *
; * @note
; * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
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
        DCD     PWRWU_IRQHandler          ; 2: Power Down Wake Up 
        DCD     Default_Handler           ; 3: Reserved.
        DCD     CLKF_IRQHandler           ; 4: CLKF
        DCD     Default_Handler           ; 5: Reserved.
        DCD     RTC_IRQHandler            ; 6: Real Time Clock 
        DCD     TAMPER_IRQHandler         ; 7: Tamper detection
        DCD     EINT0_IRQHandler          ; 8: External Input 0
        DCD     EINT1_IRQHandler          ; 9: External Input 1
        DCD     EINT2_IRQHandler          ; 10: External Input 2
        DCD     EINT3_IRQHandler          ; 11: External Input 3
        DCD     EINT4_IRQHandler          ; 12: External Input 4
        DCD     EINT5_IRQHandler          ; 13: External Input 5
        DCD     EINT6_IRQHandler          ; 14: External Input 6
        DCD     EINT7_IRQHandler          ; 15: External Input 7 
        DCD     GPA_IRQHandler            ; 16: GPIO Port A
        DCD     GPB_IRQHandler            ; 17: GPIO Port B
        DCD     GPC_IRQHandler            ; 18: GPIO Port C
        DCD     GPD_IRQHandler            ; 19: GPIO Port D
        DCD     GPE_IRQHandler            ; 20: GPIO Port E
        DCD     GPF_IRQHandler            ; 21: GPIO Port F
        DCD     GPG_IRQHandler            ; 22: GPIO Port G
        DCD     GPH_IRQHandler            ; 23: GPIO Port H
        DCD     GPI_IRQHandler            ; 24: GPIO Port I
        DCD     Default_Handler           ; 25: Reserved.
        DCD     Default_Handler           ; 26: Reserved.
        DCD     Default_Handler           ; 27: Reserved.
        DCD     Default_Handler           ; 28: Reserved.
        DCD     Default_Handler           ; 29: Reserved.
        DCD     Default_Handler           ; 30: Reserved.
        DCD     Default_Handler           ; 31: Reserved.
        DCD     TMR0_IRQHandler           ; 32: Timer 0
        DCD     TMR1_IRQHandler           ; 33: Timer 1
        DCD     TMR2_IRQHandler           ; 34: Timer 2
        DCD     TMR3_IRQHandler           ; 35: Timer 3
        DCD     Default_Handler           ; 36: Reserved.
        DCD     Default_Handler           ; 37: Reserved.
        DCD     Default_Handler           ; 38: Reserved.
        DCD     Default_Handler           ; 39: Reserved.
        DCD     PDMA_IRQHandler           ; 40: Peripheral DMA
        DCD     Default_Handler           ; 41: Reserved.
        DCD     ADC_IRQHandler            ; 42: ADC
        DCD     Default_Handler           ; 43: Reserved.
        DCD     Default_Handler           ; 44: Reserved.
        DCD     Default_Handler           ; 45: Reserved.
        DCD     WDT_IRQHandler            ; 46: Watch Dog Timer
        DCD     WWDT_IRQHandler           ; 47: Window Watch Dog Timer
        DCD     EADC0_IRQHandler          ; 48: EADC 0
        DCD     EADC1_IRQHandler          ; 49: EADC 1
        DCD     EADC2_IRQHandler          ; 50: EADC 2
        DCD     EADC3_IRQHandler          ; 51: EADC 3
        DCD     Default_Handler           ; 52: Reserved.
        DCD     Default_Handler           ; 53: Reserved.
        DCD     Default_Handler           ; 54: Reserved.
        DCD     Default_Handler           ; 55: Reserved.
        DCD     ACMP_IRQHandler           ; 56: Analog Comparator
        DCD     Default_Handler           ; 57: Reserved.
        DCD     Default_Handler           ; 58: Reserved.
        DCD     Default_Handler           ; 59: Reserved.
        DCD     OPA0_IRQHandler           ; 60: OPA 0
        DCD     OPA1_IRQHandler           ; 61: OPA 1
        DCD     ICAP0_IRQHandler          ; 62: ICAP 0
        DCD     ICAP1_IRQHandler          ; 63: ICAP 1
        DCD     PWM0CH0_IRQHandler        ; 64: PWMA CH0
        DCD     PWM0CH1_IRQHandler        ; 65: PWMA CH1
        DCD     PWM0CH2_IRQHandler        ; 66: PWMA CH2
        DCD     PWM0CH3_IRQHandler        ; 67: PWMA CH3
        DCD     PWM0CH4_IRQHandler        ; 68: PWMA CH4
        DCD     PWM0CH5_IRQHandler        ; 69: PWMA CH5
        DCD     PWM0_BRK_IRQHandler       ; 70: PWMA Brake
        DCD     QEI0_IRQHandler           ; 71: QEI 0
        DCD     PWM1CH0_IRQHandler        ; 72: PWM1 CH0
        DCD     PWM1CH1_IRQHandler        ; 73: PWM1 CH1
        DCD     PWM1CH2_IRQHandler        ; 74: PWM1 CH2
        DCD     PWM1CH3_IRQHandler        ; 75: PWM1 CH3
        DCD     PWM1CH4_IRQHandler        ; 76: PWM1 CH4
        DCD     PWM1CH5_IRQHandler        ; 77: PWM1 CH5
        DCD     PWM1_BRK_IRQHandler       ; 78: PWM1 Brake
        DCD     QEI1_IRQHandler           ; 79: QEI 1
        DCD     EPWM0_IRQHandler          ; 80: EPWM0
        DCD     EPWM0BRK_IRQHandler       ; 81: EPWM0 Brake
        DCD     EPWM1_IRQHandler          ; 82: EPWM1
        DCD     EPWM1BRK_IRQHandler       ; 83: EPWM1 Brake
        DCD     Default_Handler           ; 84: Reserved.
        DCD     Default_Handler           ; 85: Reserved.
        DCD     Default_Handler           ; 86: Reserved.
        DCD     Default_Handler           ; 87: Reserved.
        DCD     USBD_IRQHandler           ; 88: USB Device
        DCD     USBH_IRQHandler           ; 89: USB Host
        DCD     USB_OTG_IRQHandler        ; 90: USB OTG
        DCD     Default_Handler           ; 91: Reserved.
        DCD     EMAC_TX_IRQHandler         ; 92: Ethernet MAC TX
        DCD     EMAC_RX_IRQHandler         ; 93: Ethernet MAC RX
        DCD     Default_Handler           ; 94: Reserved.
        DCD     Default_Handler           ; 95: Reserved.
        DCD     SPI0_IRQHandler           ; 96: SPI 0
        DCD     SPI1_IRQHandler           ; 97: SPI 1
        DCD     SPI2_IRQHandler           ; 98: SPI 2
        DCD     SPI3_IRQHandler           ; 99: SPI 3
        DCD     Default_Handler           ; 100: Reserved.
        DCD     Default_Handler           ; 101: Reserved.
        DCD     Default_Handler           ; 102: Reserved.
        DCD     Default_Handler           ; 103: Reserved.
        DCD     UART0_IRQHandler          ; 104: UART 0
        DCD     UART1_IRQHandler          ; 105: UART 1
        DCD     UART2_IRQHandler          ; 106: UART 2
        DCD     UART3_IRQHandler          ; 107: UART 3
        DCD     UART4_IRQHandler          ; 108: UART 4
        DCD     UART5_IRQHandler          ; 109: UART 5
        DCD     Default_Handler           ; 110: Reserved.
        DCD     Default_Handler           ; 111: Reserved.
        DCD     I2C0_IRQHandler           ; 112: I2C 0
        DCD     I2C1_IRQHandler           ; 113: I2C 1
        DCD     I2C2_IRQHandler           ; 114: I2C 2
        DCD     I2C3_IRQHandler           ; 115: I2C 3
        DCD     I2C4_IRQHandler           ; 116: I2C 4
        DCD     Default_Handler           ; 117: Reserved.
        DCD     Default_Handler           ; 118: Reserved.
        DCD     Default_Handler           ; 119: Reserved.
        DCD     SC0_IRQHandler            ; 120: Smart Card 0
        DCD     SC1_IRQHandler            ; 121: Smart Card 1
        DCD     SC2_IRQHandler            ; 122: Smart Card 2
        DCD     SC3_IRQHandler            ; 123: Smart Card 3
        DCD     SC4_IRQHandler            ; 124: Smart Card 4
        DCD     SC5_IRQHandler            ; 125: Smart Card 5
        DCD     Default_Handler           ; 126: Reserved.
        DCD     Default_Handler           ; 127: Reserved.
        DCD     CAN0_IRQHandler           ; 128: CAN 0
        DCD     CAN1_IRQHandler           ; 129: CAN 1
        DCD     Default_Handler           ; 130: Reserved.
        DCD     Default_Handler           ; 131: Reserved.
        DCD     I2S0_IRQHandler           ; 132: I2S 0
        DCD     I2S1_IRQHandler           ; 133: I2S 1
        DCD     Default_Handler           ; 134: Reserved.
        DCD     Default_Handler           ; 135: Reserved.
        DCD     SD_IRQHandler             ; 136: SD card
        DCD     Default_Handler           ; 137: Reserved.
        DCD     PS2D_IRQHandler           ; 138: PS/2 device
        DCD     CAP_IRQHandler            ; 139: CAP
        DCD     CRYPTO_IRQHandler         ; 140: CRYPTO
        DCD     CRC_IRQHandler            ; 141: CRC
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
        
        LDR     R0, =0x40000100
        ; Unlock Register
        LDR     R1, =0x59
        STR     R1, [R0]
        LDR     R1, =0x16
        STR     R1, [R0]
        LDR     R1, =0x88
        STR     R1, [R0]

        ; Init POR
        LDR     R2, =0x40000024
        LDR     R1, =0x00005AA5
        STR     R1, [R2]

        ; Disable branch buffer if VCID is 0
        LDR     R2, =0x40000020
        LDR     R1, [R2]
        CMP     R1, #0
        BNE     Lock
        LDR     R2, =0x4000C018
        LDR     R1, [R2]
        ORR     R1, R1, #0x80
        STR     R1, [R2]
Lock
        ; Lock register
        MOVS    R1, #0
        STR     R1, [R0]
        
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

        PUBWEAK BOD_IRQHandler
        PUBWEAK IRC_IRQHandler
        PUBWEAK PWRWU_IRQHandler
        PUBWEAK CLKF_IRQHandler
        PUBWEAK RTC_IRQHandler
        PUBWEAK TAMPER_IRQHandler
        PUBWEAK EINT0_IRQHandler
        PUBWEAK EINT1_IRQHandler
        PUBWEAK EINT2_IRQHandler
        PUBWEAK EINT3_IRQHandler
        PUBWEAK EINT4_IRQHandler
        PUBWEAK EINT5_IRQHandler
        PUBWEAK EINT6_IRQHandler
        PUBWEAK EINT7_IRQHandler
        PUBWEAK GPA_IRQHandler
        PUBWEAK GPB_IRQHandler
        PUBWEAK GPC_IRQHandler
        PUBWEAK GPD_IRQHandler
        PUBWEAK GPE_IRQHandler
        PUBWEAK GPF_IRQHandler
        PUBWEAK GPG_IRQHandler
        PUBWEAK GPH_IRQHandler
        PUBWEAK GPI_IRQHandler
        PUBWEAK TMR0_IRQHandler
        PUBWEAK TMR1_IRQHandler
        PUBWEAK TMR2_IRQHandler
        PUBWEAK TMR3_IRQHandler
        PUBWEAK PDMA_IRQHandler
        PUBWEAK ADC_IRQHandler
        PUBWEAK WDT_IRQHandler
        PUBWEAK WWDT_IRQHandler
        PUBWEAK EADC0_IRQHandler
        PUBWEAK EADC1_IRQHandler
        PUBWEAK EADC2_IRQHandler
        PUBWEAK EADC3_IRQHandler
        PUBWEAK ACMP_IRQHandler
        PUBWEAK OPA0_IRQHandler           
        PUBWEAK OPA1_IRQHandler           
        PUBWEAK ICAP0_IRQHandler         
        PUBWEAK ICAP1_IRQHandler          
        PUBWEAK PWM0CH0_IRQHandler
        PUBWEAK PWM0CH1_IRQHandler
        PUBWEAK PWM0CH2_IRQHandler
        PUBWEAK PWM0CH3_IRQHandler
        PUBWEAK PWM0CH4_IRQHandler 
        PUBWEAK PWM0CH5_IRQHandler
        PUBWEAK PWM0_BRK_IRQHandler
        PUBWEAK QEI0_IRQHandler
        PUBWEAK PWM1CH0_IRQHandler
        PUBWEAK PWM1CH1_IRQHandler
        PUBWEAK PWM1CH2_IRQHandler
        PUBWEAK PWM1CH3_IRQHandler
        PUBWEAK PWM1CH4_IRQHandler
        PUBWEAK PWM1CH5_IRQHandler 
        PUBWEAK PWM1_BRK_IRQHandler
        PUBWEAK QEI1_IRQHandler 
        PUBWEAK EPWM0_IRQHandler 
        PUBWEAK EPWM0BRK_IRQHandler 
        PUBWEAK EPWM1_IRQHandler
        PUBWEAK EPWM1BRK_IRQHandler
        PUBWEAK USBD_IRQHandler
        PUBWEAK USBH_IRQHandler 
        PUBWEAK USB_OTG_IRQHandler
        PUBWEAK EMAC_TX_IRQHandler
        PUBWEAK EMAC_RX_IRQHandler
        PUBWEAK SPI0_IRQHandler
        PUBWEAK SPI1_IRQHandler
        PUBWEAK SPI2_IRQHandler
        PUBWEAK SPI3_IRQHandler
        PUBWEAK UART0_IRQHandler 
        PUBWEAK UART1_IRQHandler
        PUBWEAK UART2_IRQHandler
        PUBWEAK UART3_IRQHandler
        PUBWEAK UART4_IRQHandler
        PUBWEAK UART5_IRQHandler
        PUBWEAK I2C0_IRQHandler 
        PUBWEAK I2C1_IRQHandler
        PUBWEAK I2C2_IRQHandler 
        PUBWEAK I2C3_IRQHandler 
        PUBWEAK I2C4_IRQHandler
        PUBWEAK SC0_IRQHandler 
        PUBWEAK SC1_IRQHandler  
        PUBWEAK SC2_IRQHandler 
        PUBWEAK SC3_IRQHandler 
        PUBWEAK SC4_IRQHandler  
        PUBWEAK SC5_IRQHandler 
        PUBWEAK CAN0_IRQHandler 
        PUBWEAK CAN1_IRQHandler 
        PUBWEAK I2S0_IRQHandler 
        PUBWEAK I2S1_IRQHandler
        PUBWEAK SD_IRQHandler  
        PUBWEAK PS2D_IRQHandler
        PUBWEAK CAP_IRQHandler
        PUBWEAK CRYPTO_IRQHandler
        PUBWEAK CRC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
        
BOD_IRQHandler
IRC_IRQHandler
PWRWU_IRQHandler
CLKF_IRQHandler
RTC_IRQHandler
TAMPER_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
EINT4_IRQHandler
EINT5_IRQHandler
EINT6_IRQHandler
EINT7_IRQHandler
GPA_IRQHandler
GPB_IRQHandler
GPC_IRQHandler
GPD_IRQHandler
GPE_IRQHandler
GPF_IRQHandler
GPG_IRQHandler
GPH_IRQHandler
GPI_IRQHandler
TMR0_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
PDMA_IRQHandler
ADC_IRQHandler
WDT_IRQHandler
WWDT_IRQHandler
EADC0_IRQHandler
EADC1_IRQHandler
EADC2_IRQHandler
EADC3_IRQHandler
ACMP_IRQHandler
OPA0_IRQHandler           
OPA1_IRQHandler           
ICAP0_IRQHandler         
ICAP1_IRQHandler          
PWM0CH0_IRQHandler
PWM0CH1_IRQHandler
PWM0CH2_IRQHandler
PWM0CH3_IRQHandler
PWM0CH4_IRQHandler 
PWM0CH5_IRQHandler
PWM0_BRK_IRQHandler
QEI0_IRQHandler
PWM1CH0_IRQHandler
PWM1CH1_IRQHandler
PWM1CH2_IRQHandler
PWM1CH3_IRQHandler
PWM1CH4_IRQHandler
PWM1CH5_IRQHandler 
PWM1_BRK_IRQHandler
QEI1_IRQHandler 
EPWM0_IRQHandler 
EPWM0BRK_IRQHandler 
EPWM1_IRQHandler
EPWM1BRK_IRQHandler
USBD_IRQHandler
USBH_IRQHandler 
USB_OTG_IRQHandler
EMAC_TX_IRQHandler
EMAC_RX_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
SPI3_IRQHandler
UART0_IRQHandler 
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
I2C0_IRQHandler 
I2C1_IRQHandler
I2C2_IRQHandler 
I2C3_IRQHandler 
I2C4_IRQHandler
SC0_IRQHandler 
SC1_IRQHandler  
SC2_IRQHandler 
SC3_IRQHandler 
SC4_IRQHandler  
SC5_IRQHandler 
CAN0_IRQHandler 
CAN1_IRQHandler 
I2S0_IRQHandler 
I2S1_IRQHandler
SD_IRQHandler  
PS2D_IRQHandler
CAP_IRQHandler
CRYPTO_IRQHandler
CRC_IRQHandler
Default_Handler
        B Default_Handler    
        

         
         
        END
;/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
