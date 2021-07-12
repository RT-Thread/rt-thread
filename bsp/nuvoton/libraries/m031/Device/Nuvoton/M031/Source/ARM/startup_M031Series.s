;/**************************************************************************//**
; * @file     startup_m031series.s
; * @version  V2.00
; * $Revision: 4 $
; * $Date: 18/04/02 4:02p $
; * @brief    M031 Series Startup Source File
; *
; * @note
; * SPDX-License-Identifier: Apache-2.0
; * Copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
; *
; ******************************************************************************/
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
Heap_Size       EQU     0x00000000
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

g_pfnVectors    DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                                                  ; maximum of 32 External Interrupts are possible
                DCD     BOD_IRQHandler
                DCD     WDT_IRQHandler
                DCD     EINT024_IRQHandler
                DCD     EINT135_IRQHandler
                DCD     GPABGH_IRQHandler
                DCD     GPCDEF_IRQHandler
                DCD     PWM0_IRQHandler
                DCD     PWM1_IRQHandler
                DCD     TMR0_IRQHandler
                DCD     TMR1_IRQHandler
                DCD     TMR2_IRQHandler
                DCD     TMR3_IRQHandler
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
                DCD     PWRWU_IRQHandler
                DCD     ADC_IRQHandler
                DCD     CKFAIL_IRQHandler
                DCD     RTC_IRQHandler



                AREA    |.text|, CODE, READONLY



; Reset Handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main


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

                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  EINT024_IRQHandler        [WEAK]
                EXPORT  EINT135_IRQHandler        [WEAK]
                EXPORT  GPABGH_IRQHandler         [WEAK]
                EXPORT  GPCDEF_IRQHandler         [WEAK]
                EXPORT  PWM0_IRQHandler           [WEAK]
                EXPORT  PWM1_IRQHandler           [WEAK]
                EXPORT  TMR0_IRQHandler           [WEAK]
                EXPORT  TMR1_IRQHandler           [WEAK]
                EXPORT  TMR2_IRQHandler           [WEAK]
                EXPORT  TMR3_IRQHandler           [WEAK]
                EXPORT  UART02_IRQHandler         [WEAK]
                EXPORT  UART13_IRQHandler         [WEAK]
                EXPORT  SPI0_IRQHandler           [WEAK]
                EXPORT  QSPI0_IRQHandler          [WEAK]
                EXPORT  ISP_IRQHandler            [WEAK]
                EXPORT  UART57_IRQHandler         [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  BPWM0_IRQHandler          [WEAK]
                EXPORT  BPWM1_IRQHandler          [WEAK]
                EXPORT  USCI01_IRQHandler         [WEAK]
                EXPORT  USBD_IRQHandler           [WEAK]
                EXPORT  ACMP01_IRQHandler         [WEAK]
                EXPORT  PDMA_IRQHandler           [WEAK]
                EXPORT  UART46_IRQHandler         [WEAK]
                EXPORT  PWRWU_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  CKFAIL_IRQHandler         [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]

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
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END
