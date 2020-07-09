;/******************************************************************************
; * @file     startup_M451Series.s
; * @version  V0.10
; * $Revision: 5 $
; * $Date: 14/12/24 10:20a $ 
; * @brief    CMSIS Cortex-M4 Core Device Startup File for M451 Series MCU
; *
; * @note
; * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
;*****************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

    ; User may overwrite stack size setting by pre-defined symbol
    IF :LNOT: :DEF: Stack_Size
Stack_Size      EQU     0x00000400
    ENDIF

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
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
                DCD     CLKFAIL_IRQHandler         ; 4: Clock detection fail
                DCD     Default_Handler           ; 5: Reserved
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

__Vectors_Size  EQU     __Vectors_End - __Vectors

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
                EXPORT  CLKFAIL_IRQHandler         [WEAK]
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
                EXPORT  SPI0_IRQHandler           [WEAK]
                EXPORT  SPI1_IRQHandler           [WEAK]
                EXPORT  BRAKE0_IRQHandler         [WEAK]
                EXPORT  PWM0P0_IRQHandler         [WEAK]
                EXPORT  PWM0P1_IRQHandler         [WEAK]
                EXPORT  PWM0P2_IRQHandler         [WEAK]
                EXPORT  BRAKE1_IRQHandler         [WEAK]
                EXPORT  PWM1P0_IRQHandler         [WEAK]
                EXPORT  PWM1P1_IRQHandler         [WEAK]
                EXPORT  PWM1P2_IRQHandler         [WEAK]
                EXPORT  TMR0_IRQHandler           [WEAK]
                EXPORT  TMR1_IRQHandler           [WEAK]
                EXPORT  TMR2_IRQHandler           [WEAK]
                EXPORT  TMR3_IRQHandler           [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  PDMA_IRQHandler           [WEAK]
                EXPORT  DAC_IRQHandler            [WEAK]
                EXPORT  ADC00_IRQHandler          [WEAK]
                EXPORT  ADC01_IRQHandler          [WEAK]
                EXPORT  ACMP01_IRQHandler         [WEAK]
                EXPORT  ADC02_IRQHandler          [WEAK]
                EXPORT  ADC03_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  SPI2_IRQHandler           [WEAK]
                EXPORT  USBD_IRQHandler           [WEAK]
                EXPORT  USBH_IRQHandler           [WEAK]
                EXPORT  USBOTG_IRQHandler         [WEAK]
                EXPORT  CAN0_IRQHandler           [WEAK]
                EXPORT  SC0_IRQHandler            [WEAK]
                EXPORT  TK_IRQHandler             [WEAK]

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
;/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
