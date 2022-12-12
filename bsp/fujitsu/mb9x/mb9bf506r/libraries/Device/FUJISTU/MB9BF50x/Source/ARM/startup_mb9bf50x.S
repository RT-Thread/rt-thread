;/************************************************************************/
;/*               (C) Fujitsu Semiconductor Europe GmbH (FSEU)           */
;/*                                                                      */
;/* The following software deliverable is intended for and must only be  */
;/* used for reference and in an evaluation laboratory environment.      */
;/* It is provided on an as-is basis without charge and is subject to    */
;/* alterations.                                                         */
;/* It is the user's obligation to fully test the software in its        */
;/* environment and to ensure proper functionality, qualification and    */
;/* compliance with component specifications.                            */
;/*                                                                      */
;/* In the event the software deliverable includes the use of open       */
;/* source components, the provisions of the governing open source       */
;/* license agreement shall apply with respect to such software          */
;/* deliverable.                                                         */
;/* FSEU does not warrant that the deliverables do not infringe any      */
;/* third party intellectual property right (IPR). In the event that     */
;/* the deliverables infringe a third party IPR it is the sole           */
;/* responsibility of the customer to obtain necessary licenses to       */
;/* continue the usage of the deliverable.                               */
;/*                                                                      */
;/* To the maximum extent permitted by applicable law FSEU disclaims all */
;/* warranties, whether express or implied, in particular, but not       */
;/* limited to, warranties of merchantability and fitness for a          */
;/* particular purpose for which the deliverable is not designated.      */
;/*                                                                      */
;/* To the maximum extent permitted by applicable law, FSEU's liability  */
;/* is restricted to intentional misconduct and gross negligence.        */
;/* FSEU is not liable for consequential damages.                        */
;/*                                                                      */
;/* (V1.5)                                                               */
;/************************************************************************/
;/*  Startup for ARM                                                     */
;/*  Version     V1.02                                                   */
;/*  Date        2011-01-12                                              */
;/*  Target-mcu  MB9B5xx                                                 */
;/************************************************************************/

; Stack Configuration
;  Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Heap Configuration
;  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>

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
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                DCD     CSV_Handler               ; 0: Clock Super Visor
                DCD     SWDT_Handler              ; 1: Software Watchdog Timer
                DCD     LVD_Handler               ; 2: Low Voltage Detector
                DCD     MFT_WG_IRQHandler         ; 3: Wave Form Generator / DTIF
                DCD     INT0_7_Handler            ; 4: External Interrupt Request ch.0 to ch.7
                DCD     INT8_15_Handler           ; 5: External Interrupt Request ch.8 to ch.15
                DCD     DT_Handler                ; 6: Dual Timer / Quad Decoder
                DCD     MFS0RX_IRQHandler         ; 7: MultiFunction Serial ch.0
                DCD     MFS0TX_IRQHandler         ; 8: MultiFunction Serial ch.0
                DCD     MFS1RX_IRQHandler         ; 9: MultiFunction Serial ch.1
                DCD     MFS1TX_IRQHandler         ; 10: MultiFunction Serial ch.1
                DCD     MFS2RX_IRQHandler         ; 11: MultiFunction Serial ch.2
                DCD     MFS2TX_IRQHandler         ; 12: MultiFunction Serial ch.2
                DCD     MFS3RX_IRQHandler         ; 13: MultiFunction Serial ch.3
                DCD     MFS3TX_IRQHandler         ; 14: MultiFunction Serial ch.3
                DCD     MFS4RX_IRQHandler         ; 15: MultiFunction Serial ch.4
                DCD     MFS4TX_IRQHandler         ; 16: MultiFunction Serial ch.4
                DCD     MFS5RX_IRQHandler         ; 17: MultiFunction Serial ch.5
                DCD     MFS5TX_IRQHandler         ; 18: MultiFunction Serial ch.5
                DCD     MFS6RX_IRQHandler         ; 19: MultiFunction Serial ch.6
                DCD     MFS6TX_IRQHandler         ; 20: MultiFunction Serial ch.6
                DCD     MFS7RX_IRQHandler         ; 21: MultiFunction Serial ch.7
                DCD     MFS7TX_IRQHandler         ; 22: MultiFunction Serial ch.7
                DCD     PPG_Handler               ; 23: PPG
                DCD     TIM_IRQHandler            ; 24: OSC / PLL / Watch Counter
                DCD     ADC0_IRQHandler           ; 25: ADC0
                DCD     ADC1_IRQHandler           ; 26: ADC1
                DCD     ADC2_IRQHandler           ; 27: ADC2
                DCD     MFT_FRT_IRQHandler        ; 28: Free-run Timer
                DCD     MFT_IPC_IRQHandler        ; 29: Input Capture
                DCD     MFT_OPC_IRQHandler        ; 30: Output Compare
                DCD     BT_IRQHandler             ; 31: Base Timer ch.0 to ch.7
                DCD     CAN0_IRQHandler           ; 32: CAN ch.0
                DCD     CAN1_IRQHandler           ; 33: CAN ch.1
                DCD     USBF_Handler              ; 34: USB Function
                DCD     USB_Handler               ; 35: USB Function / USB HOST
                DCD     DummyHandler              ; 36: Reserved
                DCD     DummyHandler              ; 37: Reserved
                DCD     DMAC0_Handler             ; 38: DMAC ch.0
                DCD     DMAC1_Handler             ; 39: DMAC ch.1
                DCD     DMAC2_Handler             ; 40: DMAC ch.2
                DCD     DMAC3_Handler             ; 41: DMAC ch.3
                DCD     DMAC4_Handler             ; 42: DMAC ch.4
                DCD     DMAC5_Handler             ; 43: DMAC ch.5
                DCD     DMAC6_Handler             ; 44: DMAC ch.6
                DCD     DMAC7_Handler             ; 45: DMAC ch.7
                DCD     DummyHandler              ; 46: Reserved
                DCD     DummyHandler              ; 47: Reserved
__Vectors_End

__Vectors_Size 	EQU 	__Vectors_End - __Vectors

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

                EXPORT  CSV_Handler	              [WEAK]
                EXPORT  SWDT_Handler              [WEAK]
                EXPORT  LVD_Handler               [WEAK]
                EXPORT  MFT_WG_IRQHandler         [WEAK]
                EXPORT  INT0_7_Handler            [WEAK]
                EXPORT  INT8_15_Handler           [WEAK]
                EXPORT  DT_Handler                [WEAK]
                EXPORT  MFS0RX_IRQHandler         [WEAK]
                EXPORT  MFS0TX_IRQHandler         [WEAK]
                EXPORT  MFS1RX_IRQHandler         [WEAK]
                EXPORT  MFS1TX_IRQHandler         [WEAK]
                EXPORT  MFS2RX_IRQHandler         [WEAK]
                EXPORT  MFS2TX_IRQHandler         [WEAK]
                EXPORT  MFS3RX_IRQHandler         [WEAK]
                EXPORT  MFS3TX_IRQHandler         [WEAK]
                EXPORT  MFS4RX_IRQHandler         [WEAK]
                EXPORT  MFS4TX_IRQHandler         [WEAK]
                EXPORT  MFS5RX_IRQHandler         [WEAK]
                EXPORT  MFS5TX_IRQHandler         [WEAK]
                EXPORT  MFS6RX_IRQHandler         [WEAK]
                EXPORT  MFS6TX_IRQHandler         [WEAK]
                EXPORT  MFS7RX_IRQHandler         [WEAK]
                EXPORT  MFS7TX_IRQHandler         [WEAK]
                EXPORT  PPG_Handler               [WEAK]
                EXPORT  TIM_IRQHandler            [WEAK]
                EXPORT  ADC0_IRQHandler           [WEAK]
                EXPORT  ADC1_IRQHandler           [WEAK]
                EXPORT  ADC2_IRQHandler           [WEAK]
                EXPORT  MFT_FRT_IRQHandler        [WEAK]
                EXPORT  MFT_IPC_IRQHandler        [WEAK]
                EXPORT  MFT_OPC_IRQHandler        [WEAK]
                EXPORT  BT_IRQHandler             [WEAK]
                EXPORT  CAN0_IRQHandler           [WEAK]
                EXPORT  CAN1_IRQHandler           [WEAK]
                EXPORT  USBF_Handler              [WEAK]
                EXPORT  USB_Handler               [WEAK]
                EXPORT  DMAC0_Handler             [WEAK]
                EXPORT  DMAC1_Handler             [WEAK]
                EXPORT  DMAC2_Handler             [WEAK]
                EXPORT  DMAC3_Handler             [WEAK]
                EXPORT  DMAC4_Handler             [WEAK]
                EXPORT  DMAC5_Handler             [WEAK]
                EXPORT  DMAC6_Handler             [WEAK]
                EXPORT  DMAC7_Handler             [WEAK]
                EXPORT  DummyHandler              [WEAK]

CSV_Handler
SWDT_Handler
LVD_Handler
MFT_WG_IRQHandler
INT0_7_Handler
INT8_15_Handler
DT_Handler
MFS0RX_IRQHandler
MFS0TX_IRQHandler
MFS1RX_IRQHandler
MFS1TX_IRQHandler
MFS2RX_IRQHandler
MFS2TX_IRQHandler
MFS3RX_IRQHandler
MFS3TX_IRQHandler
MFS4RX_IRQHandler
MFS4TX_IRQHandler
MFS5RX_IRQHandler
MFS5TX_IRQHandler
MFS6RX_IRQHandler
MFS6TX_IRQHandler
MFS7RX_IRQHandler
MFS7TX_IRQHandler
PPG_Handler
TIM_IRQHandler
ADC0_IRQHandler
ADC1_IRQHandler
ADC2_IRQHandler
MFT_FRT_IRQHandler
MFT_IPC_IRQHandler
MFT_OPC_IRQHandler
BT_IRQHandler
CAN0_IRQHandler
CAN1_IRQHandler
USBF_Handler
USB_Handler
DMAC0_Handler
DMAC1_Handler
DMAC2_Handler
DMAC3_Handler
DMAC4_Handler
DMAC5_Handler
DMAC6_Handler
DMAC7_Handler
DummyHandler

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
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
