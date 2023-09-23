;//*****************************************************************************
;//
;// Copyright (C) 2012 - 2017 Texas Instruments Incorporated - http://www.ti.com/
;//
;// Redistribution and use in source and binary forms, with or without
;// modification, are permitted provided that the following conditions
;// are met:
;//
;//  Redistributions of source code must retain the above copyright
;//  notice, this list of conditions and the following disclaimer.
;//
;//  Redistributions in binary form must reproduce the above copyright
;//  notice, this list of conditions and the following disclaimer in the
;//  documentation and/or other materials provided with the
;//  distribution.
;//
;//  Neither the name of Texas Instruments Incorporated nor the names of
;//  its contributors may be used to endorse or promote products derived
;//  from this software without specific prior written permission.
;//
;// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
;// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
;// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
;// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
;// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;//
;// MSP432E4 startup file
;//
;//****************************************************************************
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

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
                DCD     0                         ;  
                DCD     0                         ;  
                DCD     0                         ;  
                DCD     0                         ;  
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ;  
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     GPIOA_IRQHandler          ;  0:  GPIO Port A
                DCD     GPIOB_IRQHandler          ;  1:  GPIO Port B
                DCD     GPIOC_IRQHandler          ;  2:  GPIO Port C
                DCD     GPIOD_IRQHandler          ;  3:  GPIO Port D
                DCD     GPIOE_IRQHandler          ;  4:  GPIO Port E
                DCD     UART0_IRQHandler          ;  5:  UART0 Rx and Tx
                DCD     UART1_IRQHandler          ;  6:  UART1 Rx and Tx
                DCD     SSI0_IRQHandler           ;  7:  SSI0 Rx and Tx
                DCD     I2C0_IRQHandler           ;  8:  I2C0 Master and Slave
                DCD     PWM0_FAULT_IRQHandler     ;  9:  PWM Fault
                DCD     PWM0_0_IRQHandler         ; 10:  PWM Generator 0
                DCD     PWM0_1_IRQHandler         ; 11:  PWM Generator 1
                DCD     PWM0_2_IRQHandler         ; 12:  PWM Generator 2
                DCD     QEI0_IRQHandler           ; 13:  Quadrature Encoder 0
                DCD     ADC0SS0_IRQHandler        ; 14:  ADC Sequence 0
                DCD     ADC0SS1_IRQHandler        ; 15:  ADC Sequence 1
                DCD     ADC0SS2_IRQHandler        ; 16:  ADC Sequence 2
                DCD     ADC0SS3_IRQHandler        ; 17:  ADC Sequence 3
                DCD     WATCHDOG_IRQHandler       ; 18:  Watchdog timer 
                DCD     TIMER0A_IRQHandler        ; 19:  Timer 0 subtimer A
                DCD     TIMER0B_IRQHandler        ; 20:  Timer 0 subtimer B
                DCD     TIMER1A_IRQHandler        ; 21:  Timer 1 subtimer A
                DCD     TIMER1B_IRQHandler        ; 22:  Timer 1 subtimer B
                DCD     TIMER2A_IRQHandler        ; 23:  Timer 2 subtimer A
                DCD     TIMER2B_IRQHandler        ; 24:  Timer 2 subtimer B
                DCD     COMP0_IRQHandler          ; 25:  Analog Comparator 0
                DCD     COMP1_IRQHandler          ; 26:  Analog Comparator 1
                DCD     COMP2_IRQHandler          ; 27:  Analog Comparator 2
                DCD     SYSCTL_IRQHandler         ; 28:  System Control
                DCD     FLASH_IRQHandler          ; 29:  FLASH Control
                DCD     GPIOF_IRQHandler          ; 30:  GPIO Port F
                DCD     GPIOG_IRQHandler          ; 31:  GPIO Port G
                DCD     GPIOH_IRQHandler          ; 32:  GPIO Port H
                DCD     UART2_IRQHandler          ; 33:  UART2 Rx and Tx
                DCD     SSI1_IRQHandler           ; 34:  SSI1 Rx and Tx
                DCD     TIMER3A_IRQHandler        ; 35:  Timer 3 subtimer A
                DCD     TIMER3B_IRQHandler        ; 36:  Timer 3 subtimer B
                DCD     I2C1_IRQHandler           ; 37:  I2C1 Master and Slave
                DCD     CAN0_IRQHandler           ; 38:  CAN0
                DCD     CAN1_IRQHandler           ; 39:  CAN1
                DCD     EMAC0_IRQHandler          ; 40:  Ethernet
                DCD     HIBERNATE_IRQHandler      ; 41:  Hibernate
                DCD     USB0_IRQHandler           ; 42:  USB0
                DCD     PWM0_3_IRQHandler         ; 43:  PWM Generator 3
                DCD     UDMA_IRQHandler           ; 44:  uDMA Software Transfer    
                DCD     UDMAERR_IRQHandler        ; 45:  uDMA Error   
                DCD     ADC1SS0_IRQHandler        ; 46:  ADC1 Sequence 0
                DCD     ADC1SS1_IRQHandler        ; 47:  ADC1 Sequence 1
                DCD     ADC1SS2_IRQHandler        ; 48:  ADC1 Sequence 2
                DCD     ADC1SS3_IRQHandler        ; 49:  ADC1 Sequence 3
                DCD     EPI0_IRQHandler           ; 50:  External Bus Interface 0 
                DCD     GPIOJ_IRQHandler          ; 51:  GPIO Port J
                DCD     GPIOK_IRQHandler          ; 52:  GPIO Port K
                DCD     GPIOL_IRQHandler          ; 53:  GPIO Port L
                DCD     SSI2_IRQHandler           ; 54:  SSI2 Rx and Tx
                DCD     SSI3_IRQHandler           ; 55:  SSI3 Rx and Tx
                DCD     UART3_IRQHandler          ; 56:  UART3 Rx and Tx
                DCD     UART4_IRQHandler          ; 57:  UART4 Rx and Tx
                DCD     UART5_IRQHandler          ; 58:  UART5 Rx and Tx
                DCD     UART6_IRQHandler          ; 59:  UART6 Rx and Tx
                DCD     UART7_IRQHandler          ; 60:  UART7 Rx and Tx
                DCD     I2C2_IRQHandler           ; 61:  I2C2 Master and Slave
                DCD     I2C3_IRQHandler           ; 62:  I2C3 Master and Slave
                DCD     TIMER4A_IRQHandler        ; 63:  Timer 4 subtimer A
                DCD     TIMER4B_IRQHandler        ; 64:  Timer 4 subtimer B
                DCD     TIMER5A_IRQHandler        ; 65:  Timer 5 subtimer A 
                DCD     TIMER5B_IRQHandler        ; 66:  Timer 5 subtimer B
                DCD     SYSEXC_IRQHandler         ; 67:  FPU     
                DCD     0                         ; 68:  Reserved
                DCD     0                         ; 69:  Reserved
                DCD     I2C4_IRQHandler           ; 70:  I2C4 Master and Slave
                DCD     I2C5_IRQHandler           ; 71:  I2C5 Master and Slave
                DCD     GPIOM_IRQHandler          ; 72:  GPIO Port M
                DCD     GPION_IRQHandler          ; 73:  GPIO Port N
                DCD     0                         ; 74:  Reserved
                DCD     TAMPER0_IRQHandler        ; 75:  Tamper
                DCD     GPIOP0_IRQHandler         ; 76:  GPIO Port P(Summary or P0)
                DCD     GPIOP1_IRQHandler         ; 77:  GPIO Port P1
                DCD     GPIOP2_IRQHandler         ; 78:  GPIO Port P2
                DCD     GPIOP3_IRQHandler         ; 79:  GPIO Port P3
                DCD     GPIOP4_IRQHandler         ; 80:  GPIO Port P4
                DCD     GPIOP5_IRQHandler         ; 81:  GPIO Port P5
                DCD     GPIOP6_IRQHandler         ; 82:  GPIO Port P6
                DCD     GPIOP7_IRQHandler         ; 83:  GPIO Port P7
                DCD     GPIOQ0_IRQHandler         ; 84:  GPIO Port Q0
                DCD     GPIOQ1_IRQHandler         ; 85:  GPIO Port Q1
                DCD     GPIOQ2_IRQHandler         ; 86:  GPIO Port Q2
                DCD     GPIOQ3_IRQHandler         ; 87:  GPIO Port Q3
                DCD     GPIOQ4_IRQHandler         ; 88:  GPIO Port Q4
                DCD     GPIOQ5_IRQHandler         ; 89:  GPIO Port Q5
                DCD     GPIOQ6_IRQHandler         ; 90:  GPIO Port Q6
                DCD     GPIOQ7_IRQHandler         ; 91:  GPIO Port Q7
                DCD     0                         ; 92:  Reserved
                DCD     0                         ; 93:  Reserved
                DCD     SHA0_IRQHandler           ; 94:  SHA/MD5 0 
                DCD     AES0_IRQHandler           ; 95:  AES 0
                DCD     DES0_IRQHandler           ; 96:  DES3DES 0
                DCD     0                         ; 97:  Reserved
                DCD     TIMER6A_IRQHandler        ; 98:  Timer 6 subtimer A
                DCD     TIMER6B_IRQHandler        ; 99:  Timer 6 subtimer B
                DCD     TIMER7A_IRQHandler        ;100:  Timer 7 subtimer A
                DCD     TIMER7B_IRQHandler        ;101:  Timer 7 subtimer B
                DCD     I2C6_IRQHandler           ;102:  I2C6 Master and Slave
                DCD     I2C7_IRQHandler           ;103:  I2C7 Master and Slave
                DCD     0                         ;104:  Reserved
                DCD     0                         ;105:  Reserved
                DCD     0                         ;106:  Reserved
                DCD     0                         ;107:  Reserved
                DCD     0                         ;108:  Reserved
                DCD     I2C8_IRQHandler           ;109:  I2C8 Master and Slave
                DCD     I2C9_IRQHandler           ;110:  I2C9 Master and Slave
                
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
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT GPIOA_IRQHandler           [WEAK]
                EXPORT GPIOB_IRQHandler           [WEAK]
                EXPORT GPIOC_IRQHandler           [WEAK]
                EXPORT GPIOD_IRQHandler           [WEAK]
                EXPORT GPIOE_IRQHandler           [WEAK]
                EXPORT UART0_IRQHandler           [WEAK]
                EXPORT UART1_IRQHandler           [WEAK]
                EXPORT SSI0_IRQHandler            [WEAK]
                EXPORT I2C0_IRQHandler            [WEAK]
                EXPORT PWM0_FAULT_IRQHandler      [WEAK]
                EXPORT PWM0_0_IRQHandler          [WEAK]
                EXPORT PWM0_1_IRQHandler          [WEAK]
                EXPORT PWM0_2_IRQHandler          [WEAK]
                EXPORT QEI0_IRQHandler            [WEAK]
                EXPORT ADC0SS0_IRQHandler         [WEAK]
                EXPORT ADC0SS1_IRQHandler         [WEAK]
                EXPORT ADC0SS2_IRQHandler         [WEAK]
                EXPORT ADC0SS3_IRQHandler         [WEAK]
                EXPORT WATCHDOG_IRQHandler        [WEAK]
                EXPORT TIMER0A_IRQHandler         [WEAK]
                EXPORT TIMER0B_IRQHandler         [WEAK]
                EXPORT TIMER1A_IRQHandler         [WEAK]
                EXPORT TIMER1B_IRQHandler         [WEAK]
                EXPORT TIMER2A_IRQHandler         [WEAK]
                EXPORT TIMER2B_IRQHandler         [WEAK]
                EXPORT COMP0_IRQHandler           [WEAK]
                EXPORT COMP1_IRQHandler           [WEAK]
                EXPORT COMP2_IRQHandler           [WEAK]
                EXPORT SYSCTL_IRQHandler          [WEAK]
                EXPORT FLASH_IRQHandler           [WEAK]
                EXPORT GPIOF_IRQHandler           [WEAK]
                EXPORT GPIOG_IRQHandler           [WEAK]
                EXPORT GPIOH_IRQHandler           [WEAK]
                EXPORT UART2_IRQHandler           [WEAK]
                EXPORT SSI1_IRQHandler            [WEAK]
                EXPORT TIMER3A_IRQHandler         [WEAK]
                EXPORT TIMER3B_IRQHandler         [WEAK]
                EXPORT I2C1_IRQHandler            [WEAK]
                EXPORT CAN0_IRQHandler            [WEAK]
                EXPORT CAN1_IRQHandler            [WEAK]
                EXPORT EMAC0_IRQHandler           [WEAK]
                EXPORT HIBERNATE_IRQHandler       [WEAK]
                EXPORT USB0_IRQHandler            [WEAK]
                EXPORT PWM0_3_IRQHandler          [WEAK]
                EXPORT UDMA_IRQHandler            [WEAK]
                EXPORT UDMAERR_IRQHandler         [WEAK]
                EXPORT ADC1SS0_IRQHandler         [WEAK]
                EXPORT ADC1SS1_IRQHandler         [WEAK]
                EXPORT ADC1SS2_IRQHandler         [WEAK]
                EXPORT ADC1SS3_IRQHandler         [WEAK]
                EXPORT EPI0_IRQHandler            [WEAK]
                EXPORT GPIOJ_IRQHandler           [WEAK]
                EXPORT GPIOK_IRQHandler           [WEAK]
                EXPORT GPIOL_IRQHandler           [WEAK]
                EXPORT SSI2_IRQHandler            [WEAK]
                EXPORT SSI3_IRQHandler            [WEAK]
                EXPORT UART3_IRQHandler           [WEAK]
                EXPORT UART4_IRQHandler           [WEAK]
                EXPORT UART5_IRQHandler           [WEAK]
                EXPORT UART6_IRQHandler           [WEAK]
                EXPORT UART7_IRQHandler           [WEAK]
                EXPORT I2C2_IRQHandler            [WEAK]
                EXPORT I2C3_IRQHandler            [WEAK]
                EXPORT TIMER4A_IRQHandler         [WEAK]
                EXPORT TIMER4B_IRQHandler         [WEAK]
                EXPORT TIMER5A_IRQHandler         [WEAK]
                EXPORT TIMER5B_IRQHandler         [WEAK]
                EXPORT SYSEXC_IRQHandler          [WEAK]
                EXPORT I2C4_IRQHandler            [WEAK]
                EXPORT I2C5_IRQHandler            [WEAK]
                EXPORT GPIOM_IRQHandler           [WEAK]
                EXPORT GPION_IRQHandler           [WEAK]
                EXPORT TAMPER0_IRQHandler         [WEAK]
                EXPORT GPIOP0_IRQHandler          [WEAK]
                EXPORT GPIOP1_IRQHandler          [WEAK]
                EXPORT GPIOP2_IRQHandler          [WEAK]
                EXPORT GPIOP3_IRQHandler          [WEAK]
                EXPORT GPIOP4_IRQHandler          [WEAK]
                EXPORT GPIOP5_IRQHandler          [WEAK]
                EXPORT GPIOP6_IRQHandler          [WEAK]
                EXPORT GPIOP7_IRQHandler          [WEAK]
                EXPORT GPIOQ0_IRQHandler          [WEAK]
                EXPORT GPIOQ1_IRQHandler          [WEAK]
                EXPORT GPIOQ2_IRQHandler          [WEAK]
                EXPORT GPIOQ3_IRQHandler          [WEAK]
                EXPORT GPIOQ4_IRQHandler          [WEAK]
                EXPORT GPIOQ5_IRQHandler          [WEAK]
                EXPORT GPIOQ6_IRQHandler          [WEAK]
                EXPORT GPIOQ7_IRQHandler          [WEAK]
                EXPORT SHA0_IRQHandler            [WEAK]
                EXPORT AES0_IRQHandler            [WEAK]
                EXPORT DES0_IRQHandler            [WEAK]
                EXPORT TIMER6A_IRQHandler         [WEAK]
                EXPORT TIMER6B_IRQHandler         [WEAK]
                EXPORT TIMER7A_IRQHandler         [WEAK]
                EXPORT TIMER7B_IRQHandler         [WEAK]
                EXPORT I2C6_IRQHandler            [WEAK]
                EXPORT I2C7_IRQHandler            [WEAK]
                EXPORT I2C8_IRQHandler            [WEAK]
                EXPORT I2C9_IRQHandler            [WEAK]
                
GPIOA_IRQHandler
GPIOB_IRQHandler
GPIOC_IRQHandler
GPIOD_IRQHandler
GPIOE_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
SSI0_IRQHandler
I2C0_IRQHandler
PWM0_FAULT_IRQHandler
PWM0_0_IRQHandler
PWM0_1_IRQHandler
PWM0_2_IRQHandler
QEI0_IRQHandler
ADC0SS0_IRQHandler
ADC0SS1_IRQHandler
ADC0SS2_IRQHandler
ADC0SS3_IRQHandler
WATCHDOG_IRQHandler
TIMER0A_IRQHandler
TIMER0B_IRQHandler
TIMER1A_IRQHandler
TIMER1B_IRQHandler
TIMER2A_IRQHandler
TIMER2B_IRQHandler
COMP0_IRQHandler
COMP1_IRQHandler
COMP2_IRQHandler
SYSCTL_IRQHandler
FLASH_IRQHandler
GPIOF_IRQHandler
GPIOG_IRQHandler
GPIOH_IRQHandler
UART2_IRQHandler
SSI1_IRQHandler
TIMER3A_IRQHandler
TIMER3B_IRQHandler
I2C1_IRQHandler
CAN0_IRQHandler
CAN1_IRQHandler
EMAC0_IRQHandler
HIBERNATE_IRQHandler
USB0_IRQHandler
PWM0_3_IRQHandler
UDMA_IRQHandler
UDMAERR_IRQHandler
ADC1SS0_IRQHandler
ADC1SS1_IRQHandler
ADC1SS2_IRQHandler
ADC1SS3_IRQHandler
EPI0_IRQHandler
GPIOJ_IRQHandler
GPIOK_IRQHandler
GPIOL_IRQHandler
SSI2_IRQHandler
SSI3_IRQHandler
UART3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
UART6_IRQHandler
UART7_IRQHandler
I2C2_IRQHandler
I2C3_IRQHandler
TIMER4A_IRQHandler
TIMER4B_IRQHandler
TIMER5A_IRQHandler
TIMER5B_IRQHandler
SYSEXC_IRQHandler
I2C4_IRQHandler
I2C5_IRQHandler
GPIOM_IRQHandler
GPION_IRQHandler
TAMPER0_IRQHandler
GPIOP0_IRQHandler
GPIOP1_IRQHandler
GPIOP2_IRQHandler
GPIOP3_IRQHandler
GPIOP4_IRQHandler
GPIOP5_IRQHandler
GPIOP6_IRQHandler
GPIOP7_IRQHandler
GPIOQ0_IRQHandler
GPIOQ1_IRQHandler
GPIOQ2_IRQHandler
GPIOQ3_IRQHandler
GPIOQ4_IRQHandler
GPIOQ5_IRQHandler
GPIOQ6_IRQHandler
GPIOQ7_IRQHandler
SHA0_IRQHandler
AES0_IRQHandler
DES0_IRQHandler
TIMER6A_IRQHandler
TIMER6B_IRQHandler
TIMER7A_IRQHandler
TIMER7B_IRQHandler
I2C6_IRQHandler
I2C7_IRQHandler
I2C8_IRQHandler
I2C9_IRQHandler

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

