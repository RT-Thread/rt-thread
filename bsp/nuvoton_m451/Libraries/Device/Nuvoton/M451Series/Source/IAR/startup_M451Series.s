;/******************************************************************************
; * @file     startup_NUC400Series.s
; * @version  V0.10
; * $Revision: 3 $
; * $Date: 14/12/24 10:20a $ 
; * @brief    CMSIS Cortex-M4 Core Device Startup File for NUC451 Series MCU
; *
; * @note
; * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
;*****************************************************************************/

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
        DCD     Default_Handler		      ; 3: Reserved.
        DCD     CLKFAIL_IRQHandler		  ;	4: Reserved.
        DCD     Default_Handler		      ;	5: Reserved.
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
        DCD     SPI0_IRQHandler           ; 22: SPI0
        DCD     SPI1_IRQHandler           ; 23: SPI1
        DCD     BRAKE0_IRQHandler         ; 24: 
        DCD     PWM0P0_IRQHandler         ; 25: 
        DCD     PWM0P1_IRQHandler         ; 26: 
        DCD     PWM0P2_IRQHandler         ; 27: 
        DCD     BRAKE1_IRQHandler         ; 28: 
        DCD     PWM1P0_IRQHandler         ; 29: 
        DCD     PWM1P1_IRQHandler         ; 30: 
        DCD     PWM1P2_IRQHandler         ; 31: 
        DCD     TMR0_IRQHandler           ; 32: Timer 0
        DCD     TMR1_IRQHandler           ; 33: Timer 1
        DCD     TMR2_IRQHandler           ; 34: Timer 2
        DCD     TMR3_IRQHandler           ; 35: Timer 3
        DCD     UART0_IRQHandler          ; 36: UART0
        DCD     UART1_IRQHandler          ; 37: UART1
        DCD     I2C0_IRQHandler           ; 38: I2C0
        DCD     I2C1_IRQHandler           ; 39: I2C1
        DCD     PDMA_IRQHandler           ; 40: Peripheral DMA
        DCD     DAC_IRQHandler            ; 41: DAC
        DCD     ADC00_IRQHandler          ; 42: ADC0 interrupt source 0
        DCD     ADC01_IRQHandler          ; 43: ADC0 interrupt source 1
        DCD     ACMP01_IRQHandler         ; 44: ACMP0 and ACMP1
        DCD     Default_Handler           ; 45: Reserved
        DCD     ADC02_IRQHandler          ; 46: ADC0 interrupt source 2
        DCD     ADC03_IRQHandler          ; 47: ADC0 interrupt source 3
        DCD     UART2_IRQHandler          ; 48: UART2
        DCD     UART3_IRQHandler          ; 49: UART3
        DCD     Default_Handler           ; 50: Reserved
        DCD     SPI2_IRQHandler           ; 51: SPI2
        DCD     Default_Handler           ; 52: Reserved
        DCD     USBD_IRQHandler           ; 53: USB device
        DCD     USBH_IRQHandler           ; 54: USB host
        DCD     USBOTG_IRQHandler         ; 55: USB OTG
        DCD     CAN0_IRQHandler           ; 56: CAN0
        DCD     Default_Handler           ; 57: Reserved
        DCD     SC0_IRQHandler            ; 58: 
        DCD     Default_Handler           ; 59: Reserved.
        DCD     Default_Handler           ; 60: 
        DCD     Default_Handler           ; 61: 
        DCD     Default_Handler           ; 62:
        DCD     TK_IRQHandler             ; 63:
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
        
        ; Select INV Type
        LDR     R2, =0x40000200
        LDR     R1, [R2]
        BIC     R1, R1, #0x1000
        STR     R1, [R2]
        
        ; Lock register
        MOVS    R1, #0
        STR     R1, [R0]                

        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        
#ifdef DEBUG_ENABLE_SEMIHOST
        SECTION .text:CODE:REORDER:NOROOT(2)
HardFault_Handler


                MOV     R0, LR
                LSLS    R0,R0, #29            ; Check bit 2
                BMI     SP_is_PSP             ; previous stack is PSP
                MRS     R0, MSP               ; previous stack is MSP, read MSP
                B       SP_Read_Ready
SP_is_PSP
                MRS     R0, PSP               ; Read PSP
SP_Read_Ready
                LDR     R1, [R13, #24]         ; Get previous PC
                LDRH    R3, [R1]              ; Get instruction
				LDR    R2, =0xBEAB           ; The sepcial BKPT instruction
                CMP     R3, R2                ; Test if the instruction at previous PC is BKPT
				BNE    HardFault_Handler_Ret ; Not BKPT

                ADDS    R1, #4                ; Skip BKPT and next line
                STR     R1, [R13, #24]         ; Save previous PC

				BX     LR
HardFault_Handler_Ret

#else

        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler

#endif

        B HardFault_Handler

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
        PUBWEAK RAMPE_IRQHandler
        PUBWEAK CLKFAIL_IRQHandler
        PUBWEAK RTC_IRQHandler
        PUBWEAK TAMPER_IRQHandler
        PUBWEAK WDT_IRQHandler
        PUBWEAK WWDT_IRQHandler
        PUBWEAK EINT0_IRQHandler
        PUBWEAK EINT1_IRQHandler
        PUBWEAK EINT2_IRQHandler
        PUBWEAK EINT3_IRQHandler
        PUBWEAK EINT4_IRQHandler
        PUBWEAK EINT5_IRQHandler
        PUBWEAK GPA_IRQHandler
        PUBWEAK GPB_IRQHandler
        PUBWEAK GPC_IRQHandler
        PUBWEAK GPD_IRQHandler
        PUBWEAK GPE_IRQHandler
        PUBWEAK GPF_IRQHandler
        PUBWEAK SPI0_IRQHandler
        PUBWEAK SPI1_IRQHandler
        PUBWEAK BRAKE0_IRQHandler
        PUBWEAK PWM0P0_IRQHandler
        PUBWEAK PWM0P1_IRQHandler
        PUBWEAK PWM0P2_IRQHandler
        PUBWEAK BRAKE1_IRQHandler
        PUBWEAK PWM1P0_IRQHandler
        PUBWEAK PWM1P1_IRQHandler
        PUBWEAK PWM1P2_IRQHandler
        PUBWEAK TMR0_IRQHandler
        PUBWEAK TMR1_IRQHandler
        PUBWEAK TMR2_IRQHandler
        PUBWEAK TMR3_IRQHandler
        PUBWEAK UART0_IRQHandler
        PUBWEAK UART1_IRQHandler
        PUBWEAK I2C0_IRQHandler
        PUBWEAK I2C1_IRQHandler
        PUBWEAK PDMA_IRQHandler
        PUBWEAK DAC_IRQHandler
        PUBWEAK ADC00_IRQHandler
        PUBWEAK ADC01_IRQHandler
        PUBWEAK ACMP01_IRQHandler
        PUBWEAK ADC02_IRQHandler
        PUBWEAK ADC03_IRQHandler
        PUBWEAK UART2_IRQHandler
        PUBWEAK UART3_IRQHandler
        PUBWEAK SPI2_IRQHandler
        PUBWEAK USBD_IRQHandler
        PUBWEAK USBH_IRQHandler
        PUBWEAK USBOTG_IRQHandler
        PUBWEAK CAN0_IRQHandler
        PUBWEAK SC0_IRQHandler
        PUBWEAK TK_IRQHandler
        
        SECTION .text:CODE:REORDER:NOROOT(1)
        
BOD_IRQHandler
IRC_IRQHandler
PWRWU_IRQHandler
RAMPE_IRQHandler
CLKFAIL_IRQHandler
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
SPI0_IRQHandler
SPI1_IRQHandler
BRAKE0_IRQHandler
PWM0P0_IRQHandler
PWM0P1_IRQHandler
PWM0P2_IRQHandler
BRAKE1_IRQHandler
PWM1P0_IRQHandler
PWM1P1_IRQHandler
PWM1P2_IRQHandler
TMR0_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
UART0_IRQHandler 
UART1_IRQHandler
I2C0_IRQHandler 
I2C1_IRQHandler
PDMA_IRQHandler
DAC_IRQHandler
ADC00_IRQHandler
ADC01_IRQHandler
ACMP01_IRQHandler
ADC02_IRQHandler
ADC03_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
SPI2_IRQHandler
USBD_IRQHandler
USBH_IRQHandler 
USBOTG_IRQHandler
CAN0_IRQHandler
SC0_IRQHandler 
TK_IRQHandler  
Default_Handler
        B   .    

    END        
;/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
