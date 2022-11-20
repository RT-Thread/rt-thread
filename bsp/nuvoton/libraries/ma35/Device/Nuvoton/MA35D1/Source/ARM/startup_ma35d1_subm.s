;/******************************************************************************
; * @file     startup_ma35d1_subm.s
; * @brief    CMSIS Cortex-M4 Core Device Startup File
; *
; * SPDX-License-Identifier: Apache-2.0
; * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
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
	EXPORT __initial_sp
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
                DCD     CANFD00_IRQHandler        ; 47
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
                DCD     CANFD10_IRQHandler        ; 78
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
                DCD     CANFD20_IRQHandler        ; 103
                DCD     CANFD30_IRQHandler        ; 104
                DCD     KPI_IRQHandler            ; 105
                DCD     CANFD01_IRQHandler        ; 106
                DCD     CANFD11_IRQHandler        ; 107
                DCD     CANFD21_IRQHandler        ; 108
                DCD     CANFD31_IRQHandler        ; 109
                DCD     ADC0_IRQHandler           ; 110
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

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

                EXPORT  LVD_IRQHandler          [WEAK]
                EXPORT  PWRWU_IRQHandler        [WEAK]
                EXPORT  HWSEM0_IRQHandler       [WEAK]
                EXPORT  CKFAIL_IRQHandler       [WEAK]
                EXPORT  WHC0_IRQHandler         [WEAK]
                EXPORT  RTC_IRQHandler          [WEAK]
                EXPORT  TAMPER_IRQHandler       [WEAK]
                EXPORT  WDT2_IRQHandler         [WEAK]
                EXPORT  WWDT2_IRQHandler        [WEAK]
                EXPORT  EINT0_IRQHandler        [WEAK]
                EXPORT  EINT1_IRQHandler        [WEAK]
                EXPORT  EINT2_IRQHandler        [WEAK]
                EXPORT  EINT3_IRQHandler        [WEAK]
                EXPORT  GPA_IRQHandler          [WEAK]
                EXPORT  GPB_IRQHandler          [WEAK]
                EXPORT  GPC_IRQHandler          [WEAK]
                EXPORT  GPD_IRQHandler          [WEAK]
                EXPORT  TMR2_IRQHandler         [WEAK]
                EXPORT  TMR3_IRQHandler         [WEAK]
                EXPORT  BRAKE0_IRQHandler       [WEAK]
                EXPORT  EPWM0P0_IRQHandler      [WEAK]
                EXPORT  EPWM0P1_IRQHandler      [WEAK]
                EXPORT  EPWM0P2_IRQHandler      [WEAK]
                EXPORT  QEI0_IRQHandler         [WEAK]
                EXPORT  ECAP0_IRQHandler        [WEAK]
                EXPORT  QSPI1_IRQHandler        [WEAK]
                EXPORT  UART1_IRQHandler        [WEAK]
                EXPORT  UART2_IRQHandler        [WEAK]
                EXPORT  UART3_IRQHandler        [WEAK]
                EXPORT  UART4_IRQHandler        [WEAK]
                EXPORT  UART5_IRQHandler        [WEAK]
                EXPORT  EADC00_IRQHandler       [WEAK]
                EXPORT  EADC01_IRQHandler       [WEAK]
                EXPORT  EADC02_IRQHandler       [WEAK]
                EXPORT  EADC03_IRQHandler       [WEAK]
                EXPORT  I2C1_IRQHandler         [WEAK]
                EXPORT  I2S0_IRQHandler         [WEAK]
                EXPORT  CANFD00_IRQHandler      [WEAK]
                EXPORT  SC0_IRQHandler          [WEAK]
                EXPORT  GPE_IRQHandler          [WEAK]
                EXPORT  GPF_IRQHandler          [WEAK]
                EXPORT  GPG_IRQHandler          [WEAK]
                EXPORT  GPH_IRQHandler          [WEAK]
                EXPORT  GPI_IRQHandler          [WEAK]
                EXPORT  GPJ_IRQHandler          [WEAK]
                EXPORT  TMR4_IRQHandler         [WEAK]
                EXPORT  TMR5_IRQHandler         [WEAK]
                EXPORT  TMR6_IRQHandler         [WEAK]
                EXPORT  TMR7_IRQHandler         [WEAK]
                EXPORT  BRAKE1_IRQHandler       [WEAK]
                EXPORT  EPWM1P0_IRQHandler      [WEAK]
                EXPORT  EPWM1P1_IRQHandler      [WEAK]
                EXPORT  EPWM1P2_IRQHandler      [WEAK]
                EXPORT  QEI1_IRQHandler         [WEAK]
                EXPORT  ECAP1_IRQHandler        [WEAK]
                EXPORT  SPI0_IRQHandler         [WEAK]
                EXPORT  SPI1_IRQHandler         [WEAK]
                EXPORT  PDMA2_IRQHandler        [WEAK]
                EXPORT  PDMA3_IRQHandler        [WEAK]
                EXPORT  UART6_IRQHandler        [WEAK]
                EXPORT  UART7_IRQHandler        [WEAK]
                EXPORT  UART8_IRQHandler        [WEAK]
                EXPORT  UART9_IRQHandler        [WEAK]
                EXPORT  UART10_IRQHandler       [WEAK]
                EXPORT  UART11_IRQHandler       [WEAK]
                EXPORT  I2C2_IRQHandler         [WEAK]
                EXPORT  I2C3_IRQHandler         [WEAK]
                EXPORT  I2S1_IRQHandler         [WEAK]
                EXPORT  CANFD10_IRQHandler      [WEAK]
                EXPORT  SC1_IRQHandler          [WEAK]
                EXPORT  GPK_IRQHandler          [WEAK]
                EXPORT  GPL_IRQHandler          [WEAK]
                EXPORT  GPM_IRQHandler          [WEAK]
                EXPORT  GPN_IRQHandler          [WEAK]
                EXPORT  TMR8_IRQHandler         [WEAK]
                EXPORT  TMR9_IRQHandler         [WEAK]
                EXPORT  TMR10_IRQHandler        [WEAK]
                EXPORT  TMR11_IRQHandler        [WEAK]
                EXPORT  BRAKE2_IRQHandler       [WEAK]
                EXPORT  EPWM2P0_IRQHandle       [WEAK]
                EXPORT  EPWM2P1_IRQHandle       [WEAK]
                EXPORT  EPWM2P2_IRQHandle       [WEAK]
                EXPORT  QEI2_IRQHandler         [WEAK]
                EXPORT  ECAP2_IRQHandler        [WEAK]
                EXPORT  SPI2_IRQHandler         [WEAK]
                EXPORT  SPI3_IRQHandler         [WEAK]
                EXPORT  UART12_IRQHandler       [WEAK]
                EXPORT  UART13_IRQHandler       [WEAK]
                EXPORT  UART14_IRQHandler       [WEAK]
                EXPORT  UART15_IRQHandler       [WEAK]
                EXPORT  UART16_IRQHandler       [WEAK]
                EXPORT  I2C4_IRQHandler         [WEAK]
                EXPORT  I2C5_IRQHandler         [WEAK]
                EXPORT  CANFD20_IRQHandler      [WEAK]
                EXPORT  CANFD30_IRQHandler      [WEAK]
                EXPORT  KPI_IRQHandler          [WEAK]
                EXPORT  CANFD01_IRQHandler      [WEAK]
                EXPORT  CANFD11_IRQHandler      [WEAK]
                EXPORT  CANFD21_IRQHandler      [WEAK]
                EXPORT  CANFD31_IRQHandler      [WEAK]
                EXPORT  ADC0_IRQHandler         [WEAK]

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
CANFD00_IRQHandler
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
CANFD10_IRQHandler
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
CANFD20_IRQHandler
CANFD30_IRQHandler
KPI_IRQHandler
CANFD01_IRQHandler
CANFD11_IRQHandler
CANFD21_IRQHandler
CANFD31_IRQHandler
ADC0_IRQHandler
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

