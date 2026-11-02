;/*
; * Copyright (c) 2006-2020, YICHIP Development Team
; * @file     yc_startup.s
; * @brief    source file for setting startup
; *
; * Change Logs:
; * Date           Author             Version        Notes
; * 2020-11-06     wushengyan         V1.0.0         the first version
; * 2021-03-11     wushengyan         V1.0.2         Change for New ROM
; */
Stack_Size      EQU     0x400

                AREA    STACK, NOINIT, READWRITE, ALIGN=4
Stack_Mem       SPACE   Stack_Size
__initial_sp   

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x200
                AREA    HEAP, NOINIT, READWRITE, ALIGN=4
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit
                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset Rom code change to 0x1000200
                AREA    RESET, CODE, READONLY   ,ALIGN=4
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
__Vectors       DCD     __initial_sp
                DCD     Reset_Handler           ;//reset    1
                DCD     0x00000000              ;//NMI      2
                DCD     hard_fault_handler   ;//HARD     3
                DCD     0                       ;
                DCD     0                       ;
                DCD     0                       ;
                DCD     0                       ;
                DCD     0                       ;
                DCD     0                       ;
                DCD     0                       ;
                DCD     svc_handler          ;//SVC      11
                DCD     0                       ;
                DCD     0                       ;
                DCD     pendsv_handler       ;//PENDSV  14
                DCD     systick_handler      ;//SYSTICK 15
                DCD     USB_IRQHandler          ;//IQR0
                DCD     I2C0_IRQHandler         ;//IQR1
                DCD     I2C1_IRQHandler         ;//IQR2
                DCD     QSPI_IRQHandler         ;//IQR3
                DCD     SPI0_IRQHandler         ;//IQR4
                DCD     SPI1_IRQHandler         ;
                DCD     HSPI_IRQHandler         ;
                DCD     SEC_IRQHandler          ;
                DCD     UART0_IRQHandler        ;
                DCD     UART1_IRQHandler        ;
                DCD     UART2_IRQHandler        ;
                DCD     UART3_IRQHandler        ;
                DCD     MEMCP_IRQHandler        ;
                DCD     SCI0_IRQHandler         ;
                DCD     SCI1_IRQHandler         ;
                DCD     MSR_IRQHandler          ;
                DCD     GPIO_IRQHandler         ;
                DCD     TMRG0_IRQHandler        ;
                DCD     TMRG1_IRQHandler        ;
                DCD     SDIO_IRQHandler         ;
                DCD     PSARM_IRQHandler        ;
                DCD     RSA_IRQHandler          ;
                DCD     SM4_IRQHandler          ;
                DCD     TRNG_IRQHandler         ;
                DCD     WDT_IRQHandler          ;
                DCD     DCMI_IRQHandler         ;
                DCD     ADC_IRQHandler          ;
                DCD     RTC_IRQHandler          ;
                DCD     BIN_IRQHandler          ;
                DCD     POWER_IRQHandler        ;
                DCD     SOFTWARE_IRQHandler     ;
                DCD     RISCV_IRQHandler        ;
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

isr             PROC
                LDR R1,=0x1000200
                LDR R0,[R0,R1]
                BX  R0
                NOP
                NOP
                NOP
                ENDP

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler
                IMPORT  __main
		IMPORT  SystemInit
		LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP
                    
hard_fault_handler PROC
			EXPORT  hard_fault_handler 
            IMPORT HardFault_Handler
			ldr r0,=HardFault_Handler       
			bx r0
			nop
			ENDP
		
svc_handler PROC
			EXPORT  svc_handler         
			ldr r0,=SVC_IRQHandler
			bx r0
			nop
			ENDP

pendsv_handler PROC
			EXPORT  pendsv_handler
            IMPORT  PendSV_Handler
			ldr r0,=PendSV_Handler
			bx r0
			nop
			ENDP
		
systick_handler 	PROC
			EXPORT systick_handler 
            IMPORT SysTick_Handler
			ldr r0,=SysTick_Handler
			bx r0
			nop
			ENDP


                ALIGN

Default_Handler PROC
; ToDo:  Add here the export definition for the device specific external interrupts handler
                EXPORT      HARD_FAULT_IRQHandler       [WEAK]
                EXPORT      SVC_IRQHandler              [WEAK]
                EXPORT      PENDSV_IRQHandler           [WEAK]
                EXPORT      SYSTICK_IRQHandler          [WEAK]
                EXPORT      EXTI0_IRQHandler            [WEAK]
                EXPORT      EXTI1_IRQHandler            [WEAK]
                EXPORT      EXTI2_IRQHandler            [WEAK]
                EXPORT      EXTI3_IRQHandler            [WEAK]
                EXPORT      EXTI4_IRQHandler            [WEAK]
                EXPORT      TIMER0_IRQHandler           [WEAK]
                EXPORT      TIMER1_IRQHandler           [WEAK]
                EXPORT      TIMER2_IRQHandler           [WEAK]
                EXPORT      TIMER3_IRQHandler           [WEAK]
                EXPORT      TIMER4_IRQHandler           [WEAK]
                EXPORT      TIMER5_IRQHandler           [WEAK]
                EXPORT      TIMER6_IRQHandler           [WEAK]
                EXPORT      TIMER7_IRQHandler           [WEAK]
                EXPORT      TIMER8_IRQHandler           [WEAK]
                EXPORT      CHGRIN_IRQHandler           [WEAK]
                EXPORT      VBAT_IRQHandler             [WEAK]
                EXPORT      USB_IRQHandler              [WEAK]
                EXPORT      I2C0_IRQHandler             [WEAK]
                EXPORT      I2C1_IRQHandler             [WEAK]
                EXPORT      QSPI_IRQHandler             [WEAK]
                EXPORT      SPI0_IRQHandler             [WEAK]
                EXPORT      SPI1_IRQHandler             [WEAK]
                EXPORT      HSPI_IRQHandler             [WEAK]
                EXPORT      SEC_IRQHandler              [WEAK]
                EXPORT      UART0_IRQHandler            [WEAK]
                EXPORT      UART1_IRQHandler            [WEAK]
                EXPORT      UART2_IRQHandler            [WEAK]
                EXPORT      UART3_IRQHandler            [WEAK]
                EXPORT      MEMCP_IRQHandler            [WEAK]
                EXPORT      SCI0_IRQHandler             [WEAK]
                EXPORT      SCI1_IRQHandler             [WEAK]
                EXPORT      MSR_IRQHandler              [WEAK]
                EXPORT      GPIO_IRQHandler             [WEAK]
                EXPORT      TMRG0_IRQHandler            [WEAK]
                EXPORT      TMRG1_IRQHandler            [WEAK]
                EXPORT      SDIO_IRQHandler             [WEAK]
                EXPORT      PSARM_IRQHandler            [WEAK]
                EXPORT      RSA_IRQHandler              [WEAK]
                EXPORT      SM4_IRQHandler              [WEAK]
                EXPORT      TRNG_IRQHandler             [WEAK]
                EXPORT      WDT_IRQHandler              [WEAK]
                EXPORT      DCMI_IRQHandler             [WEAK]
                EXPORT      ADC_IRQHandler              [WEAK]
                EXPORT      RTC_IRQHandler              [WEAK]
                EXPORT      BIN_IRQHandler              [WEAK]
                EXPORT      POWER_IRQHandler            [WEAK]
                EXPORT      SOFTWARE_IRQHandler         [WEAK]
                EXPORT      RISCV_IRQHandler            [WEAK]


; ToDo:  Add here the names for the device specific external interrupts handler
HARD_FAULT_IRQHandler
SVC_IRQHandler
PENDSV_IRQHandler
SYSTICK_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
EXTI5_IRQHandler
EXTI6_IRQHandler
EXTI7_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
TIMER4_IRQHandler
TIMER5_IRQHandler
TIMER6_IRQHandler
TIMER7_IRQHandler
TIMER8_IRQHandler
CHGRIN_IRQHandler
VBAT_IRQHandler
USB_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
QSPI_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
HSPI_IRQHandler
SEC_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
MEMCP_IRQHandler
SCI0_IRQHandler
SCI1_IRQHandler
MSR_IRQHandler
GPIO_IRQHandler
TMRG0_IRQHandler
TMRG1_IRQHandler
SDIO_IRQHandler
PSARM_IRQHandler
RSA_IRQHandler
SM4_IRQHandler
TRNG_IRQHandler
WDT_IRQHandler
DCMI_IRQHandler
ADC_IRQHandler
RTC_IRQHandler
BIN_IRQHandler
POWER_IRQHandler
SOFTWARE_IRQHandler
RISCV_IRQHandler
                B   .
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
                LDR     R1, = __initial_sp
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


            END
