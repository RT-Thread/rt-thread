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
;/*  Startup for IAR                                                     */
;/*  Version     V1.02                                                   */
;/*  Date        2011-01-05                                              */
;/*  Target-mcu  MB9B5xx                                                 */
;/************************************************************************/


                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                SECTION .intvec:CODE:NOROOT(2)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table

                DATA
__vector_table  DCD     sfe(CSTACK)               ; Top of Stack
		        DCD     Reset_Handler             ; Reset
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     MemManage_Handler         ; MPU Fault
                DCD     BusFault_Handler          ; Bus Fault
                DCD     UsageFault_Handler        ; Usage Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     DebugMon_Handler          ; Debug Monitor
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

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

                THUMB
; Dummy Exception Handlers (infinite loops which can be modified)

                PUBWEAK Reset_Handler
                SECTION .text:CODE:REORDER(2)
Reset_Handler
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0

                PUBWEAK NMI_Handler
                SECTION .text:CODE:REORDER(1)
NMI_Handler
                B       NMI_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:REORDER(1)
HardFault_Handler
                B       HardFault_Handler

                PUBWEAK MemManage_Handler
                SECTION .text:CODE:REORDER(1)
MemManage_Handler
                B       MemManage_Handler

                PUBWEAK BusFault_Handler
                SECTION .text:CODE:REORDER(1)
BusFault_Handler
                B       BusFault_Handler

                PUBWEAK UsageFault_Handler
                SECTION .text:CODE:REORDER(1)
UsageFault_Handler
                B       UsageFault_Handler

                PUBWEAK SVC_Handler
                SECTION .text:CODE:REORDER(1)
SVC_Handler
                B       SVC_Handler

                PUBWEAK DebugMon_Handler
                SECTION .text:CODE:REORDER(1)
DebugMon_Handler
                B       DebugMon_Handler

                PUBWEAK PendSV_Handler
                SECTION .text:CODE:REORDER(1)
PendSV_Handler
                B       PendSV_Handler

                PUBWEAK SysTick_Handler
                SECTION .text:CODE:REORDER(1)
SysTick_Handler
                B       SysTick_Handler



                PUBWEAK CSV_Handler
                SECTION .text:CODE:REORDER(1)
CSV_Handler
                B       CSV_Handler

                PUBWEAK SWDT_Handler
                SECTION .text:CODE:REORDER(1)
SWDT_Handler
                B       SWDT_Handler

                PUBWEAK LVD_Handler
                SECTION .text:CODE:REORDER(1)
LVD_Handler
                B       LVD_Handler

                PUBWEAK MFT_WG_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFT_WG_IRQHandler
                B       MFT_WG_IRQHandler
                
                PUBWEAK INT0_7_Handler
                SECTION .text:CODE:REORDER(1)
INT0_7_Handler
                B       INT0_7_Handler

                PUBWEAK INT8_15_Handler
                SECTION .text:CODE:REORDER(1)
INT8_15_Handler
                B       INT8_15_Handler
                
                PUBWEAK DT_Handler
                SECTION .text:CODE:REORDER(1)
DT_Handler
                B       DT_Handler

                PUBWEAK MFS0RX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS0RX_IRQHandler
                B       MFS0RX_IRQHandler

                PUBWEAK MFS0TX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS0TX_IRQHandler
                B       MFS0TX_IRQHandler

                PUBWEAK MFS1RX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS1RX_IRQHandler
                B       MFS1RX_IRQHandler

                PUBWEAK MFS1TX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS1TX_IRQHandler
                B       MFS1TX_IRQHandler

                PUBWEAK MFS2RX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS2RX_IRQHandler
                B       MFS2RX_IRQHandler

                PUBWEAK MFS2TX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS2TX_IRQHandler
                B       MFS2TX_IRQHandler

                PUBWEAK MFS3RX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS3RX_IRQHandler
                B       MFS3RX_IRQHandler

                PUBWEAK MFS3TX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS3TX_IRQHandler
                B       MFS3TX_IRQHandler

                PUBWEAK MFS4RX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS4RX_IRQHandler
                B       MFS4RX_IRQHandler

                PUBWEAK MFS4TX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS4TX_IRQHandler
                B       MFS4TX_IRQHandler

                PUBWEAK MFS5RX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS5RX_IRQHandler
                B       MFS5RX_IRQHandler

                PUBWEAK MFS5TX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS5TX_IRQHandler
                B       MFS5TX_IRQHandler

                PUBWEAK MFS6RX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS6RX_IRQHandler
                B       MFS6RX_IRQHandler

                PUBWEAK MFS6TX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS6TX_IRQHandler
                B       MFS6TX_IRQHandler

                PUBWEAK MFS7RX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS7RX_IRQHandler
                B       MFS7RX_IRQHandler

                PUBWEAK MFS7TX_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFS7TX_IRQHandler
                B       MFS7TX_IRQHandler

                PUBWEAK PPG_Handler
                SECTION .text:CODE:REORDER(1)
PPG_Handler
                B       PPG_Handler

                PUBWEAK TIM_IRQHandler
                SECTION .text:CODE:REORDER(1)
TIM_IRQHandler
                B       TIM_IRQHandler

                PUBWEAK ADC0_IRQHandler
                SECTION .text:CODE:REORDER(1)
ADC0_IRQHandler
                B       ADC0_IRQHandler

                PUBWEAK ADC1_IRQHandler
                SECTION .text:CODE:REORDER(1)
ADC1_IRQHandler
                B       ADC1_IRQHandler

                PUBWEAK ADC2_IRQHandler
                SECTION .text:CODE:REORDER(1)
ADC2_IRQHandler
                B       ADC2_IRQHandler

                PUBWEAK MFT_FRT_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFT_FRT_IRQHandler
                B       MFT_FRT_IRQHandler

                PUBWEAK MFT_IPC_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFT_IPC_IRQHandler
                B       MFT_IPC_IRQHandler

                PUBWEAK MFT_OPC_IRQHandler
                SECTION .text:CODE:REORDER(1)
MFT_OPC_IRQHandler
                B       MFT_OPC_IRQHandler

                PUBWEAK BT_IRQHandler
                SECTION .text:CODE:REORDER(1)
BT_IRQHandler
                B       BT_IRQHandler

                PUBWEAK CAN0_IRQHandler
                SECTION .text:CODE:REORDER(1)
CAN0_IRQHandler
                B       CAN0_IRQHandler

                PUBWEAK CAN1_IRQHandler
                SECTION .text:CODE:REORDER(1)
CAN1_IRQHandler
                B       CAN1_IRQHandler

                PUBWEAK USBF_Handler
                SECTION .text:CODE:REORDER(1)
USBF_Handler
                B       USBF_Handler

                PUBWEAK USB_Handler
                SECTION .text:CODE:REORDER(1)
USB_Handler
                B       USB_Handler

                PUBWEAK DMAC0_Handler
                SECTION .text:CODE:REORDER(1)
DMAC0_Handler
                B       DMAC0_Handler


                PUBWEAK DMAC1_Handler
                SECTION .text:CODE:REORDER(1)
DMAC1_Handler
                B       DMAC1_Handler

                PUBWEAK DMAC2_Handler
                SECTION .text:CODE:REORDER(1)
DMAC2_Handler
                B       DMAC2_Handler

                PUBWEAK DMAC3_Handler
                SECTION .text:CODE:REORDER(1)
DMAC3_Handler
                B       DMAC3_Handler

                PUBWEAK DMAC4_Handler
                SECTION .text:CODE:REORDER(1)
DMAC4_Handler
                B       DMAC4_Handler

                PUBWEAK DMAC5_Handler
                SECTION .text:CODE:REORDER(1)
DMAC5_Handler
                B       DMAC5_Handler

                PUBWEAK DMAC6_Handler
                SECTION .text:CODE:REORDER(1)
DMAC6_Handler
                B       DMAC6_Handler

                PUBWEAK DMAC7_Handler
                SECTION .text:CODE:REORDER(1)
DMAC7_Handler
                B       DMAC7_Handler

                PUBWEAK DummyHandler
                SECTION .text:CODE:REORDER(1)
DummyHandler
                B       DummyHandler

                END
