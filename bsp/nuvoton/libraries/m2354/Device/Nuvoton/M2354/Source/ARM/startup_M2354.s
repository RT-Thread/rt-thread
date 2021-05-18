;/**************************************************************************//**
; * @file     startup_M2354.s
; * @version  V2.00
; * $Revision: 9 $
; * $Date: 16/08/27 12:33p $ 
; * @brief   Startup Source File
; *
; * @note
; * SPDX-License-Identifier: Apache-2.0
; * Copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
; *
; ******************************************************************************/
		
		
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

    IF :LNOT: :DEF: Stack_Size
Stack_Size      EQU     0x00002000
    ENDIF

                AREA    |.STACK|, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

    IF :LNOT: :DEF: Heap_Size
Heap_Size       EQU     0x00001000
    ENDIF

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  g_pfnVectors
                EXPORT  g_pfnVectors_End
                EXPORT  g_pfnVectors_Size
;Wayne			IMPORT  SendChar_ToUART
                IMPORT  SCU_IRQHandler

g_pfnVectors    DCD     __initial_sp               ;     Top of Stack
                DCD     Reset_Handler              ;     Reset Handler
                DCD     NMI_Handler                ;     NMI Handler
                DCD     HardFault_Handler          ;     Hard Fault Handler
                DCD     0                          ;     Reserved
                DCD     0                          ;     Reserved
                DCD     0                          ;     Reserved
                DCD     0                          ;     Reserved
                DCD     0                          ;     Reserved
                DCD     0                          ;     Reserved
                DCD     0                          ;     Reserved
                DCD     SVC_Handler                ;     SVCall Handler
                DCD     0                          ;     Reserved
                DCD     0                          ;     Reserved
                DCD     PendSV_Handler             ;     PendSV Handler
                DCD     SysTick_Handler            ;     SysTick Handler

                ; External Interrupts
                                                   ; maximum of 32 External Interrupts are possible
                DCD     BOD_IRQHandler		       ; 0  
                DCD     IRC_IRQHandler             ; 1  
                DCD     PWRWU_IRQHandler           ; 2  
                DCD     SRAM_IRQHandler            ; 3  
                DCD     CLKFAIL_IRQHandler         ; 4  
                DCD     DEFAULT_IRQHandler         ; 5  
                DCD     RTC_IRQHandler             ; 6  
                DCD     RTC_TAMPER_IRQHandler      ; 7  
                DCD     WDT_IRQHandler             ; 8  
                DCD     WWDT_IRQHandler            ; 9  
                DCD     EINT0_IRQHandler           ; 10 
                DCD     EINT1_IRQHandler           ; 11 
                DCD     EINT2_IRQHandler           ; 12 
                DCD     EINT3_IRQHandler           ; 13 
                DCD     EINT4_IRQHandler           ; 14 
                DCD     EINT5_IRQHandler           ; 15 
                DCD     GPA_IRQHandler             ; 16 
                DCD     GPB_IRQHandler             ; 17 
                DCD     GPC_IRQHandler             ; 18 
                DCD     GPD_IRQHandler             ; 19 
                DCD     GPE_IRQHandler             ; 20 
                DCD     GPF_IRQHandler             ; 21 
                DCD     QSPI0_IRQHandler           ; 22 
                DCD     SPI0_IRQHandler            ; 23 
                DCD     BRAKE0_IRQHandler          ; 24 
                DCD     EPWM0_P0_IRQHandler        ; 25 
                DCD     EPWM0_P1_IRQHandler        ; 26 
                DCD     EPWM0_P2_IRQHandler        ; 27 
                DCD     BRAKE1_IRQHandler          ; 28 
                DCD     EPWM1_P0_IRQHandler        ; 29 
                DCD     EPWM1_P1_IRQHandler        ; 30 
                DCD     EPWM1_P2_IRQHandler        ; 31 
                DCD     TMR0_IRQHandler            ; 32 
                DCD     TMR1_IRQHandler            ; 33 
                DCD     TMR2_IRQHandler            ; 34 
                DCD     TMR3_IRQHandler            ; 35 
                DCD     UART0_IRQHandler           ; 36 
                DCD     UART1_IRQHandler           ; 37 
                DCD     I2C0_IRQHandler            ; 38 
                DCD     I2C1_IRQHandler            ; 39 
                DCD     PDMA0_IRQHandler           ; 40 
                DCD     DAC_IRQHandler             ; 41 
                DCD     EADC0_IRQHandler           ; 42 
                DCD     EADC1_IRQHandler           ; 43 
                DCD     ACMP01_IRQHandler          ; 44 
                DCD     DEFAULT_IRQHandler         ; 45 
                DCD     EADC2_IRQHandler           ; 46 
                DCD     EADC3_IRQHandler           ; 47 
                DCD     UART2_IRQHandler           ; 48 
                DCD     UART3_IRQHandler           ; 49 
                DCD     DEFAULT_IRQHandler         ; 50 
                DCD     SPI1_IRQHandler            ; 51 
                DCD     SPI2_IRQHandler            ; 52 
                DCD     USBD_IRQHandler            ; 53 
                DCD     USBH_IRQHandler            ; 54 
                DCD     USBOTG_IRQHandler          ; 55 
                DCD     CAN0_IRQHandler            ; 56 
                DCD     DEFAULT_IRQHandler         ; 57 
                DCD     SC0_IRQHandler             ; 58 
                DCD     SC1_IRQHandler             ; 59 
                DCD     SC2_IRQHandler             ; 60 
                DCD     DEFAULT_IRQHandler         ; 61 
                DCD     SPI3_IRQHandler            ; 62 
                DCD     DEFAULT_IRQHandler         ; 63 
                DCD     SDH0_IRQHandler            ; 64 
                DCD     DEFAULT_IRQHandler         ; 65 
                DCD     DEFAULT_IRQHandler         ; 66 
                DCD     DEFAULT_IRQHandler         ; 67 
                DCD     I2S0_IRQHandler            ; 68 
                DCD     DEFAULT_IRQHandler         ; 69 
                DCD     OPA0_IRQHandler            ; 70 
                DCD     CRPT_IRQHandler            ; 71 
                DCD     GPG_IRQHandler             ; 72 
                DCD     EINT6_IRQHandler           ; 73 
                DCD     UART4_IRQHandler           ; 74 
                DCD     UART5_IRQHandler           ; 75 
                DCD     USCI0_IRQHandler           ; 76 
                DCD     USCI1_IRQHandler           ; 77 
                DCD     BPWM0_IRQHandler           ; 78 
                DCD     BPWM1_IRQHandler           ; 79 
                DCD     DEFAULT_IRQHandler         ; 80 
                DCD     DEFAULT_IRQHandler         ; 81 
                DCD     I2C2_IRQHandler            ; 82 
                DCD     DEFAULT_IRQHandler         ; 83 
                DCD     QEI0_IRQHandler            ; 84 
                DCD     QEI1_IRQHandler            ; 85 
                DCD     ECAP0_IRQHandler           ; 86 
                DCD     ECAP1_IRQHandler           ; 87 
                DCD     GPH_IRQHandler             ; 88 
                DCD     EINT7_IRQHandler           ; 89 
                DCD     DEFAULT_IRQHandler         ; 90 
                DCD     DEFAULT_IRQHandler         ; 91 
                DCD     DEFAULT_IRQHandler         ; 92 
                DCD     DEFAULT_IRQHandler         ; 93 
                DCD     DEFAULT_IRQHandler         ; 94 
                DCD     DEFAULT_IRQHandler         ; 95 
                DCD     DEFAULT_IRQHandler         ; 96 
                DCD     DEFAULT_IRQHandler         ; 97 
                DCD     PDMA1_IRQHandler           ; 98 
                DCD     SCU_IRQHandler             ; 99 
                DCD     LCD_IRQHandler             ; 100
                DCD     TRNG_IRQHandler            ; 101
                DCD     DEFAULT_IRQHandler         ; 102
                DCD     DEFAULT_IRQHandler         ; 103
                DCD     DEFAULT_IRQHandler         ; 104
                DCD     DEFAULT_IRQHandler         ; 105
                DCD     DEFAULT_IRQHandler         ; 106
                DCD     DEFAULT_IRQHandler         ; 107
                DCD     DEFAULT_IRQHandler         ; 108
                DCD     KS_IRQHandler              ; 109
                DCD     TAMPER_IRQHandler          ; 110
                DCD     EWDT_IRQHandler            ; 111
                DCD     EWWDT_IRQHandler           ; 112
                DCD     NS_ISP_IRQHandler          ; 113
                DCD     TMR4_IRQHandler            ; 114
                DCD     TMR5_IRQHandler            ; 115
					
                                                     
g_pfnVectors_End

g_pfnVectors_Size  EQU     g_pfnVectors_End - g_pfnVectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                MOV     R0, R15
                LSLS    R0, R0, #3
                BMI     GotoSystemInit

                LDR     R0, =0x40000100
                LDR     R1, =0x59
                STR     R1, [R0]
                LDR     R1, =0x16
                STR     R1, [R0]
                LDR     R1, =0x88
                STR     R1, [R0]

                LDR     R0, =0x400001f4
                LDR     R1, =0xffffffff
                STR     R1, [R0]

                LDR     R0, =0x400000dC
                LDR     R1, =0x0
                STR     R1, [R0]

                LDR     R0, =0x40000200
                LDR     R1, [R0,#0x4]

                LDR     R2, =0xfff02000

                ORRS    R1, R1, R2
                STR     R1, [R0,#0x4]

GotoSystemInit

                LDR     R0, =0x40000100
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
ProcessHardFaultx\
                PROC
                EXPORT  ProcessHardFaultx          [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  BOD_IRQHandler		      [WEAK] ; 0  
                EXPORT  IRC_IRQHandler            [WEAK] ; 1  
                EXPORT  PWRWU_IRQHandler          [WEAK] ; 2  
                EXPORT  SRAM_IRQHandler           [WEAK] ; 3  
                EXPORT  CLKFAIL_IRQHandler        [WEAK] ; 4  
               ;EXPORT  0                         [WEAK] ; 5  
                EXPORT  RTC_IRQHandler            [WEAK] ; 6  
                EXPORT  RTC_TAMPER_IRQHandler     [WEAK] ; 7  
                EXPORT  WDT_IRQHandler            [WEAK] ; 8  
                EXPORT  WWDT_IRQHandler           [WEAK] ; 9  
                EXPORT  EINT0_IRQHandler          [WEAK] ; 10 
                EXPORT  EINT1_IRQHandler          [WEAK] ; 11 
                EXPORT  EINT2_IRQHandler          [WEAK] ; 12 
                EXPORT  EINT3_IRQHandler          [WEAK] ; 13 
                EXPORT  EINT4_IRQHandler          [WEAK] ; 14 
                EXPORT  EINT5_IRQHandler          [WEAK] ; 15 
                EXPORT  GPA_IRQHandler            [WEAK] ; 16 
                EXPORT  GPB_IRQHandler            [WEAK] ; 17 
                EXPORT  GPC_IRQHandler            [WEAK] ; 18 
                EXPORT  GPD_IRQHandler            [WEAK] ; 19 
                EXPORT  GPE_IRQHandler            [WEAK] ; 20 
                EXPORT  GPF_IRQHandler            [WEAK] ; 21 
                EXPORT  QSPI0_IRQHandler          [WEAK] ; 22 
                EXPORT  SPI0_IRQHandler           [WEAK] ; 23 
                EXPORT  BRAKE0_IRQHandler         [WEAK] ; 24 
                EXPORT  EPWM0_P0_IRQHandler       [WEAK] ; 25 
                EXPORT  EPWM0_P1_IRQHandler       [WEAK] ; 26 
                EXPORT  EPWM0_P2_IRQHandler       [WEAK] ; 27 
                EXPORT  BRAKE1_IRQHandler         [WEAK] ; 28 
                EXPORT  EPWM1_P0_IRQHandler       [WEAK] ; 29 
                EXPORT  EPWM1_P1_IRQHandler       [WEAK] ; 30 
                EXPORT  EPWM1_P2_IRQHandler       [WEAK] ; 31 
                EXPORT  TMR0_IRQHandler           [WEAK] ; 32 
                EXPORT  TMR1_IRQHandler           [WEAK] ; 33 
                EXPORT  TMR2_IRQHandler           [WEAK] ; 34 
                EXPORT  TMR3_IRQHandler           [WEAK] ; 35 
                EXPORT  UART0_IRQHandler          [WEAK] ; 36 
                EXPORT  UART1_IRQHandler          [WEAK] ; 37 
                EXPORT  I2C0_IRQHandler           [WEAK] ; 38 
                EXPORT  I2C1_IRQHandler           [WEAK] ; 39 
                EXPORT  PDMA0_IRQHandler          [WEAK] ; 40 
                EXPORT  DAC_IRQHandler            [WEAK] ; 41 
                EXPORT  EADC0_IRQHandler          [WEAK] ; 42 
                EXPORT  EADC1_IRQHandler          [WEAK] ; 43 
                EXPORT  ACMP01_IRQHandler         [WEAK] ; 44 
               ;EXPORT  0                         [WEAK] ; 45 
                EXPORT  EADC2_IRQHandler          [WEAK] ; 46 
                EXPORT  EADC3_IRQHandler          [WEAK] ; 47 
                EXPORT  UART2_IRQHandler          [WEAK] ; 48 
                EXPORT  UART3_IRQHandler          [WEAK] ; 49 
               ;EXPORT  0                         [WEAK] ; 50 
                EXPORT  SPI1_IRQHandler           [WEAK] ; 51 
                EXPORT  SPI2_IRQHandler           [WEAK] ; 52 
                EXPORT  USBD_IRQHandler           [WEAK] ; 53 
                EXPORT  USBH_IRQHandler           [WEAK] ; 54 
                EXPORT  USBOTG_IRQHandler         [WEAK] ; 55 
                EXPORT  CAN0_IRQHandler           [WEAK] ; 56 
                EXPORT  CAN1_IRQHandler           [WEAK] ; 57 
                EXPORT  SC0_IRQHandler            [WEAK] ; 58 
                EXPORT  SC1_IRQHandler            [WEAK] ; 59 
                EXPORT  SC2_IRQHandler            [WEAK] ; 60 
                EXPORT  SC3_IRQHandler            [WEAK] ; 61 
                EXPORT  SPI3_IRQHandler           [WEAK] ; 62 
               ;EXPORT  0                         [WEAK] ; 63 
                EXPORT  SDH0_IRQHandler           [WEAK] ; 64 
               ;EXPORT  0                         [WEAK] ; 65 
               ;EXPORT  0                         [WEAK] ; 66 
               ;EXPORT  0                         [WEAK] ; 67 
                EXPORT  I2S0_IRQHandler           [WEAK] ; 68 
               ;EXPORT  0                         [WEAK] ; 69 
                EXPORT  OPA0_IRQHandler           [WEAK] ; 70 
                EXPORT  CRPT_IRQHandler           [WEAK] ; 71 
                EXPORT  GPG_IRQHandler            [WEAK] ; 72 
                EXPORT  EINT6_IRQHandler          [WEAK] ; 73 
                EXPORT  UART4_IRQHandler          [WEAK] ; 74 
                EXPORT  UART5_IRQHandler          [WEAK] ; 75 
                EXPORT  USCI0_IRQHandler          [WEAK] ; 76 
                EXPORT  USCI1_IRQHandler          [WEAK] ; 77 
                EXPORT  BPWM0_IRQHandler          [WEAK] ; 78 
                EXPORT  BPWM1_IRQHandler          [WEAK] ; 79 
               ;EXPORT  0                         [WEAK] ; 80 
               ;EXPORT  0                         [WEAK] ; 81 
                EXPORT  I2C2_IRQHandler           [WEAK] ; 82 
               ;EXPORT  0                         [WEAK] ; 83 
                EXPORT  QEI0_IRQHandler           [WEAK] ; 84 
                EXPORT  QEI1_IRQHandler           [WEAK] ; 85 
                EXPORT  ECAP0_IRQHandler          [WEAK] ; 86 
                EXPORT  ECAP1_IRQHandler          [WEAK] ; 87 
                EXPORT  GPH_IRQHandler            [WEAK] ; 88 
                EXPORT   EINT7_IRQHandler          [WEAK] ; 89 
                EXPORT  SDH1_IRQHandler           [WEAK] ; 90 
               ;EXPORT  0                         [WEAK] ; 91 
               ;EXPORT  USBH_IRQHandler           [WEAK] ; 92 
               ;EXPORT  0                         [WEAK] ; 93 
               ;EXPORT  0                         [WEAK] ; 94 
               ;EXPORT  0                         [WEAK] ; 95 
               ;EXPORT  0                         [WEAK] ; 96 
               ;EXPORT  0                         [WEAK] ; 97 
                EXPORT  PDMA1_IRQHandler          [WEAK] ; 98 
               ;EXPORT  SCU_IRQHandler            [WEAK] ; 99 
                EXPORT  LCD_IRQHandler            [WEAK] ; 100 
                EXPORT  TRNG_IRQHandler           [WEAK] ; 101
               ;EXPORT  0                         [WEAK] ; 102
               ;EXPORT  0                         [WEAK] ; 103
               ;EXPORT  0                         [WEAK] ; 104
               ;EXPORT  0                         [WEAK] ; 105
               ;EXPORT  0                         [WEAK] ; 106
               ;EXPORT  0                         [WEAK] ; 107
               ;EXPORT  0                         [WEAK] ; 108
                EXPORT  KS_IRQHandler             [WEAK] ; 109
                EXPORT  TAMPER_IRQHandler         [WEAK] ; 110
                EXPORT  EWDT_IRQHandler           [WEAK] ; 111
                EXPORT  EWWDT_IRQHandler          [WEAK] ; 112
                EXPORT  NS_ISP_IRQHandler         [WEAK] ; 113
                EXPORT  TMR4_IRQHandler           [WEAK] ; 114 
                EXPORT  TMR5_IRQHandler           [WEAK] ; 115 


                EXPORT	DEFAULT_IRQHandler		  [WEAK]                                                
                                                                
BOD_IRQHandler		       ; 0  
IRC_IRQHandler             ; 1  
PWRWU_IRQHandler           ; 2  
SRAM_IRQHandler            ; 3  
CLKFAIL_IRQHandler         ; 4  
;0                          ; 5  
RTC_IRQHandler             ; 6  
RTC_TAMPER_IRQHandler      ; 7  
WDT_IRQHandler             ; 8  
WWDT_IRQHandler            ; 9  
EINT0_IRQHandler           ; 10 
EINT1_IRQHandler           ; 11 
EINT2_IRQHandler           ; 12 
EINT3_IRQHandler           ; 13 
EINT4_IRQHandler           ; 14 
EINT5_IRQHandler           ; 15 
GPA_IRQHandler             ; 16 
GPB_IRQHandler             ; 17 
GPC_IRQHandler             ; 18 
GPD_IRQHandler             ; 19 
GPE_IRQHandler             ; 20 
GPF_IRQHandler             ; 21 
QSPI0_IRQHandler           ; 22 
SPI0_IRQHandler            ; 23 
BRAKE0_IRQHandler          ; 24 
EPWM0_P0_IRQHandler        ; 25 
EPWM0_P1_IRQHandler        ; 26 
EPWM0_P2_IRQHandler        ; 27 
BRAKE1_IRQHandler          ; 28 
EPWM1_P0_IRQHandler        ; 29 
EPWM1_P1_IRQHandler        ; 30 
EPWM1_P2_IRQHandler        ; 31 
TMR0_IRQHandler            ; 32 
TMR1_IRQHandler            ; 33 
TMR2_IRQHandler            ; 34 
TMR3_IRQHandler            ; 35 
UART0_IRQHandler           ; 36 
UART1_IRQHandler           ; 37 
I2C0_IRQHandler            ; 38 
I2C1_IRQHandler            ; 39 
PDMA0_IRQHandler           ; 40 
DAC_IRQHandler             ; 41 
EADC0_IRQHandler           ; 42 
EADC1_IRQHandler           ; 43 
ACMP01_IRQHandler          ; 44 
;0                          ; 45 
EADC2_IRQHandler           ; 46 
EADC3_IRQHandler           ; 47 
UART2_IRQHandler           ; 48 
UART3_IRQHandler           ; 49 
;0                          ; 50 
SPI1_IRQHandler            ; 51 
SPI2_IRQHandler            ; 52 
USBD_IRQHandler            ; 53 
USBH_IRQHandler            ; 54 
USBOTG_IRQHandler          ; 55 
CAN0_IRQHandler            ; 56 
CAN1_IRQHandler            ; 57 
SC0_IRQHandler             ; 58 
SC1_IRQHandler             ; 59 
SC2_IRQHandler             ; 60 
SC3_IRQHandler             ; 61 
SPI3_IRQHandler            ; 62 
;0                          ; 63 
SDH0_IRQHandler            ; 64 
;0                          ; 65 
;0                          ; 66 
;0                          ; 67 
I2S0_IRQHandler            ; 68 
;0                          ; 69 
OPA0_IRQHandler            ; 70 
CRPT_IRQHandler            ; 71 
GPG_IRQHandler             ; 72 
EINT6_IRQHandler           ; 73 
UART4_IRQHandler           ; 74 
UART5_IRQHandler           ; 75 
USCI0_IRQHandler           ; 76 
USCI1_IRQHandler           ; 77 
BPWM0_IRQHandler           ; 78 
BPWM1_IRQHandler           ; 79 
;0                          ; 80 
;0                          ; 81 
I2C2_IRQHandler            ; 82 
;0                          ; 83 
QEI0_IRQHandler            ; 84 
QEI1_IRQHandler            ; 85 
ECAP0_IRQHandler           ; 86 
ECAP1_IRQHandler           ; 87 
GPH_IRQHandler             ; 88 
EINT7_IRQHandler           ; 89 
SDH1_IRQHandler            ; 90 
;0                          ; 91 
;USBH_IRQHandler            ; 92 
;0                          ; 93 
;0                          ; 94 
;0                          ; 95 
;0                          ; 96 
;0                          ; 97 
PDMA1_IRQHandler           ; 98 
;SCU_IRQHandler            ; 99 
LCD_IRQHandler             ; 100 
TRNG_IRQHandler            ; 101
;0                         ; 102
;0                         ; 103
;0                         ; 104
;0                         ; 105
;0                         ; 106
;0                         ; 107
;0                         ; 108
KS_IRQHandler              ; 109
TAMPER_IRQHandler          ; 110
EWDT_IRQHandler            ; 111
EWWDT_IRQHandler           ; 112
NS_ISP_IRQHandler          ; 113
TMR4_IRQHandler            ; 114 
TMR5_IRQHandler            ; 115 

DEFAULT_IRQHandler
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
                LDR     R0, = Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
				BX      LR
                ENDP


                ALIGN

                ENDIF


__PC            PROC
                EXPORT      __PC
                
                MOV     r0, lr
                BLX     lr
                ALIGN
                    
                ENDP

SPD_Return      PROC
                EXPORT  SPD_Return
                
                LDR     r0, =0x400002c0 ; SPD_VTOR
                LDR     r1, =0x20010000    ; New VTOR
                STR     r1, [r0]
                MOV     r0, sp
                STR     r0, [r1]
                LDR     r0, =SPD_Next
                STR     r0, [r1,#4]
                WFI
                B       .
                ;LDR     SPD_Next
SPD_Next                        
                NOP
                NOP
                NOP
                
                ENDP


                END
