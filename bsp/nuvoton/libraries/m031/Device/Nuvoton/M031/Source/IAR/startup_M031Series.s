;/**************************************************************************//**
; * @file     startup_M031Series.s
; * @version  V3.00
; * $Revision: 5 $
; * $Date: 18/04/02 4:02p $
; * @brief    M031 Series Startup Source File for IAR Platform
; *
; * @note
; * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
; *
; ******************************************************************************/

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    MODULE  ?cstartup

    ;; Forward declaration of sections.
    SECTION CSTACK:DATA:NOROOT(3) ;; 8 bytes alignment

    SECTION .intvec:CODE:NOROOT(2);; 4 bytes alignment

    EXTERN  SystemInit
    EXTERN  __iar_program_start
    PUBLIC  __vector_table

    DATA
__vector_table
    DCD     sfe(CSTACK)
    DCD     Reset_Handler

    DCD     NMI_Handler
    DCD     HardFault_Handler
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     SVC_Handler
    DCD     0
    DCD     0
    DCD     PendSV_Handler
    DCD     SysTick_Handler

    ; External Interrupts
    DCD     BOD_IRQHandler              ; Brownout low voltage detected interrupt
    DCD     WDT_IRQHandler              ; Watch Dog Timer interrupt
    DCD     EINT024_IRQHandler
    DCD     EINT135_IRQHandler
    DCD     GPABGH_IRQHandler
    DCD     GPCDEF_IRQHandler
    DCD     PWM0_IRQHandler             ; PWM0 or PWM2 interrupt
    DCD     PWM1_IRQHandler             ; PWM1 or PWM3 interrupt
    DCD     TMR0_IRQHandler             ; Timer 0 interrupt
    DCD     TMR1_IRQHandler             ; Timer 1 interrupt
    DCD     TMR2_IRQHandler             ; Timer 2 interrupt
    DCD     TMR3_IRQHandler             ; Timer 3 interrupt
    DCD     UART02_IRQHandler
    DCD     UART13_IRQHandler
    DCD     SPI0_IRQHandler
    DCD     QSPI0_IRQHandler
    DCD     ISP_IRQHandler
    DCD     UART57_IRQHandler
    DCD     I2C0_IRQHandler
    DCD     I2C1_IRQHandler
    DCD     BPWM0_IRQHandler
    DCD     BPWM1_IRQHandler
    DCD     USCI01_IRQHandler
    DCD     USBD_IRQHandler
    DCD     Default_Handler
    DCD     ACMP01_IRQHandler
    DCD     PDMA_IRQHandler
    DCD     UART46_IRQHandler
    DCD     PWRWU_IRQHandler            ; Clock controller interrupt for chip wake up from power-down
    DCD     ADC_IRQHandler              ; ADC interrupt
    DCD     CKFAIL_IRQHandler           ; Clock fail detect and IRC TRIM interrupt
    DCD     RTC_IRQHandler

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
    THUMB
    PUBWEAK Reset_Handler
    SECTION .text:CODE:REORDER:NOROOT(2)       ; 4 bytes alignment
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

        ; Init LDO_RDY
        LDR     R2, =0x40000280
        LDR     R1, =0x00000001
        STR     R1, [R2]

        ; Disable NMI (Assign to reserved IRQ)
        LDR     R2, =0x40000380
        LDR     R1, =0x0000001F
        STR     R1, [R2]

        ; Lock register
        MOVS    R1, #0
        STR     R1, [R0]

        LDR      R0, =SystemInit
        BLX      R0
        LDR      R0, =__iar_program_start
        BX       R0

    PUBWEAK HardFault_Handler
    PUBWEAK NMI_Handler
    PUBWEAK SVC_Handler
    PUBWEAK PendSV_Handler
    PUBWEAK SysTick_Handler
    PUBWEAK BOD_IRQHandler
    PUBWEAK WDT_IRQHandler
    PUBWEAK EINT024_IRQHandler
    PUBWEAK EINT135_IRQHandler
    PUBWEAK GPABGH_IRQHandler
    PUBWEAK GPCDEF_IRQHandler
    PUBWEAK PWM0_IRQHandler
    PUBWEAK PWM1_IRQHandler
    PUBWEAK TMR0_IRQHandler
    PUBWEAK TMR1_IRQHandler
    PUBWEAK TMR2_IRQHandler
    PUBWEAK TMR3_IRQHandler
    PUBWEAK UART02_IRQHandler
    PUBWEAK UART13_IRQHandler
    PUBWEAK SPI0_IRQHandler
    PUBWEAK QSPI0_IRQHandler
    PUBWEAK ISP_IRQHandler
    PUBWEAK UART57_IRQHandler
    PUBWEAK I2C0_IRQHandler
    PUBWEAK I2C1_IRQHandler
    PUBWEAK BPWM0_IRQHandler
    PUBWEAK BPWM1_IRQHandler
    PUBWEAK USCI01_IRQHandler
    PUBWEAK USBD_IRQHandler
    PUBWEAK ACMP01_IRQHandler
    PUBWEAK PDMA_IRQHandler
    PUBWEAK UART46_IRQHandler
    PUBWEAK PWRWU_IRQHandler
    PUBWEAK ADC_IRQHandler
    PUBWEAK CKFAIL_IRQHandler
    PUBWEAK RTC_IRQHandler
    SECTION .text:CODE:REORDER:NOROOT(2)

HardFault_Handler
NMI_Handler
SVC_Handler
PendSV_Handler
SysTick_Handler
BOD_IRQHandler
WDT_IRQHandler
EINT024_IRQHandler
EINT135_IRQHandler
GPABGH_IRQHandler
GPCDEF_IRQHandler
PWM0_IRQHandler
PWM1_IRQHandler
TMR0_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
UART02_IRQHandler
UART13_IRQHandler
SPI0_IRQHandler
QSPI0_IRQHandler
ISP_IRQHandler
UART57_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
BPWM0_IRQHandler
BPWM1_IRQHandler
USCI01_IRQHandler
USBD_IRQHandler
ACMP01_IRQHandler
PDMA_IRQHandler
UART46_IRQHandler
PWRWU_IRQHandler
ADC_IRQHandler
CKFAIL_IRQHandler
RTC_IRQHandler
Default_Handler

    B Default_Handler


    END

