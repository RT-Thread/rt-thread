;/******************************************************************************
; * @file     startup_NUC472_442.s
; * @version  V1.00
; * $Revision: 12 $
; * $Date: 15/09/22 10:25a $ 
; * @brief    CMSIS ARM Cortex-M4 Core Device Startup File
; *
; * @note
; * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
;*****************************************************************************/  
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

    IF :LNOT: :DEF: Stack_Size
Stack_Size      EQU     0x00001000
    ENDIF

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

    IF :LNOT: :DEF: Heap_Size
Heap_Size       EQU     0x00000200
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
                DCD     PWRWU_IRQHandler          ; 2: Power Down Wake Up 
                DCD     SRAMF_IRQHandler          ; 3: Reserved.
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
                DCD     EADC0_IRQHandler          ; 48: EDAC 0
                DCD     EADC1_IRQHandler          ; 49: EDAC 1
                DCD     EADC2_IRQHandler          ; 50: EDAC 2
                DCD     EADC3_IRQHandler          ; 51: EDAC 3
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
                DCD     PWM0CH0_IRQHandler        ; 64: PWM0 CH0
                DCD     PWM0CH1_IRQHandler        ; 65: PWM0 CH1
                DCD     PWM0CH2_IRQHandler        ; 66: PWM0 CH2
                DCD     PWM0CH3_IRQHandler        ; 67: PWM0 CH3
                DCD     PWM0CH4_IRQHandler        ; 68: PWM0 CH4
                DCD     PWM0CH5_IRQHandler        ; 69: PWM0 CH5
                DCD     PWM0_BRK_IRQHandler       ; 70: PWM0 Brake
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
                DCD     EMAC_TX_IRQHandler        ; 92: Ethernet MAC TX
                DCD     EMAC_RX_IRQHandler        ; 93: Ethernet MAC RX
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
                DCD     CAP_IRQHandler            ; 139: VIN
                DCD     CRYPTO_IRQHandler         ; 140: CRYPTO
                DCD     CRC_IRQHandler            ; 141: CRC    

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
                
                ; Disable branch buffer if VCID is 0
                LDR     R2, =0x40000020
                LDR     R1, [R2]
                CMP     R1, #0
                BNE     Lock
                LDR     R2, =0x4000C018
                LDR     R1, [R2]
                ORR     R1, #0x80
                STR     R1, [R2]

Lock
                ; Init POR
                LDR     R2, =0x40000024
                LDR     R1, =0x00005AA5
                STR     R1, [R2]

                ; Lock register
                MOVS    R1, #0
                STR     R1, [R0]

                LDR     R0, =SystemInit
                BLX     R0
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
                EXPORT  SRAMF_IRQHandler          [WEAK]
                EXPORT  CLKF_IRQHandler              [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]        
                EXPORT  TAMPER_IRQHandler         [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  EINT4_IRQHandler          [WEAK]
                EXPORT  EINT5_IRQHandler          [WEAK]
                EXPORT  EINT6_IRQHandler          [WEAK]
                EXPORT  EINT7_IRQHandler          [WEAK]
                EXPORT  GPA_IRQHandler            [WEAK]
                EXPORT  GPB_IRQHandler            [WEAK]
                EXPORT  GPC_IRQHandler            [WEAK]
                EXPORT  GPD_IRQHandler            [WEAK]
                EXPORT  GPE_IRQHandler            [WEAK]
                EXPORT  GPF_IRQHandler            [WEAK]
                EXPORT  GPG_IRQHandler            [WEAK]
                EXPORT  GPH_IRQHandler            [WEAK]
                EXPORT  GPI_IRQHandler            [WEAK]
                EXPORT  TMR0_IRQHandler           [WEAK]
                EXPORT  TMR1_IRQHandler           [WEAK]
                EXPORT  TMR2_IRQHandler           [WEAK]
                EXPORT  TMR3_IRQHandler           [WEAK]
                EXPORT  PDMA_IRQHandler           [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  WWDT_IRQHandler           [WEAK]
                EXPORT  EADC0_IRQHandler          [WEAK]
                EXPORT  EADC1_IRQHandler          [WEAK]
                EXPORT  EADC2_IRQHandler          [WEAK]
                EXPORT  EADC3_IRQHandler          [WEAK]
                EXPORT  ACMP_IRQHandler           [WEAK]
                EXPORT  OPA0_IRQHandler           [WEAK]
                EXPORT  OPA1_IRQHandler           [WEAK]
                EXPORT  ICAP0_IRQHandler          [WEAK]
                EXPORT  ICAP1_IRQHandler          [WEAK]          
                EXPORT  PWM0CH0_IRQHandler        [WEAK]
                EXPORT  PWM0CH1_IRQHandler        [WEAK]
                EXPORT  PWM0CH2_IRQHandler        [WEAK]
                EXPORT  PWM0CH3_IRQHandler        [WEAK]
                EXPORT  PWM0CH4_IRQHandler        [WEAK]
                EXPORT  PWM0CH5_IRQHandler        [WEAK]
                EXPORT  PWM0_BRK_IRQHandler       [WEAK]
                EXPORT  QEI0_IRQHandler           [WEAK]
                EXPORT  PWM1CH0_IRQHandler        [WEAK]
                EXPORT  PWM1CH1_IRQHandler        [WEAK]
                EXPORT  PWM1CH2_IRQHandler        [WEAK]
                EXPORT  PWM1CH3_IRQHandler        [WEAK]
                EXPORT  PWM1CH4_IRQHandler        [WEAK]
                EXPORT  PWM1CH5_IRQHandler        [WEAK]
                EXPORT  PWM1_BRK_IRQHandler       [WEAK]
                EXPORT  QEI1_IRQHandler           [WEAK]
                EXPORT  EPWM0_IRQHandler          [WEAK]
                EXPORT  EPWM0BRK_IRQHandler       [WEAK]
                EXPORT  EPWM1_IRQHandler          [WEAK]
                EXPORT  EPWM1BRK_IRQHandler       [WEAK]
                EXPORT  USBD_IRQHandler           [WEAK]
                EXPORT  USBH_IRQHandler           [WEAK]
                EXPORT  USB_OTG_IRQHandler        [WEAK]
                EXPORT  EMAC_TX_IRQHandler        [WEAK]
                EXPORT  EMAC_RX_IRQHandler        [WEAK]
                EXPORT  SPI0_IRQHandler           [WEAK]
                EXPORT  SPI1_IRQHandler           [WEAK]
                EXPORT  SPI2_IRQHandler           [WEAK]
                EXPORT  SPI3_IRQHandler           [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  UART4_IRQHandler          [WEAK]
                EXPORT  UART5_IRQHandler          [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  I2C3_IRQHandler           [WEAK]
                EXPORT  I2C4_IRQHandler           [WEAK]
                EXPORT  SC0_IRQHandler            [WEAK]
                EXPORT  SC1_IRQHandler            [WEAK]
                EXPORT  SC2_IRQHandler            [WEAK]
                EXPORT  SC3_IRQHandler            [WEAK]
                EXPORT  SC4_IRQHandler            [WEAK]
                EXPORT  SC5_IRQHandler            [WEAK]
                EXPORT  CAN0_IRQHandler           [WEAK]
                EXPORT  CAN1_IRQHandler           [WEAK]
                EXPORT  I2S0_IRQHandler           [WEAK]
                EXPORT  I2S1_IRQHandler           [WEAK]
                EXPORT  SD_IRQHandler             [WEAK]
                EXPORT  PS2D_IRQHandler           [WEAK]
                EXPORT  CAP_IRQHandler            [WEAK]
                EXPORT  CRYPTO_IRQHandler         [WEAK]
                EXPORT  CRC_IRQHandler            [WEAK]

Default__IRQHandler
BOD_IRQHandler
IRC_IRQHandler
PWRWU_IRQHandler
SRAMF_IRQHandler
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
;/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
