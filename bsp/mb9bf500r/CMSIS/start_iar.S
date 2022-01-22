;/*
; * Copyright (c) 2006-2021, RT-Thread Development Team
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Change Logs:
; * Date           Author       Notes
; * 2009-01-17     Bernard      first version
; * 2009-09-27     Bernard      add protect when contex switch occurs
; */

#include "rtconfig.h"

    MODULE  ?cstartup

;; ICODE is the same segment as cstartup. By placing __low_level_init
;; in the same segment, we make sure it can be reached with BL. */

    SECTION CSTACK:DATA:NOROOT(3)
    SECTION .icode:CODE:NOROOT(2)

#ifdef RT_USING_UART2
    IMPORT  MFS2RX_IRQHandler
#endif
    PUBLIC  __low_level_init

    PUBWEAK SystemInit_ExtMemCtl
    SECTION .text:CODE:REORDER(2)
    THUMB
SystemInit_ExtMemCtl
    BX LR

__low_level_init:
    ;;  Initialize hardware.
    LDR R0, = SystemInit_ExtMemCtl ; initialize external memory controller
    MOV R11, LR
    BLX R0
    LDR R1, =sfe(CSTACK)        ; restore original stack pointer
    MSR MSP, R1
    MOV R0,#1
    ;; Return with BX to be independent of mode of caller
    BX  R11

    ;; Forward declaration of sections.
    SECTION .intvec:CODE:NOROOT(2)

    EXTERN  __iar_program_start
    PUBLIC  __vector_table

    DATA
__vector_table
    DCD     sfe(CSTACK)
    DCD     __iar_program_start

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
    DCD     CSV_IRQHandler            ; Clock Super Visor
    DCD     SWDT_IRQHandler           ; Software Watchdog Timer
    DCD     LVD_IRQHandler            ; Low Voltage Detector
    DCD     WFG_IRQHandler            ; Wave Form Generator
    DCD     EXINT0_7_IRQHandler       ; External Interrupt Request ch.0 to ch.7
    DCD     EXINT8_15_IRQHandler      ; External Interrupt Request ch.8 to ch.15
    DCD     DTIM_QDU_IRQHandler       ; Dual Timer / Quad Decoder
    DCD     MFS0RX_IRQHandler         ; MultiFunction Serial ch.0
    DCD     MFS0TX_IRQHandler         ; MultiFunction Serial ch.0
    DCD     MFS1RX_IRQHandler         ; MultiFunction Serial ch.1
    DCD     MFS1TX_IRQHandler         ; MultiFunction Serial ch.1
#ifdef RT_USING_UART2
    DCD     MFS2RX_IRQHandler         ; MultiFunction Serial ch.2
#else
    DCD     NULL_IRQHandler           ; MultiFunction Serial ch.2
#endif
    DCD     MFS2TX_IRQHandler         ; MultiFunction Serial ch.2
    DCD     MFS3RX_IRQHandler         ; MultiFunction Serial ch.3
    DCD     MFS3TX_IRQHandler         ; MultiFunction Serial ch.3
    DCD     MFS4RX_IRQHandler         ; MultiFunction Serial ch.4
    DCD     MFS4TX_IRQHandler         ; MultiFunction Serial ch.4
    DCD     MFS5RX_IRQHandler         ; MultiFunction Serial ch.5
    DCD     MFS5TX_IRQHandler         ; MultiFunction Serial ch.5
    DCD     MFS6RX_IRQHandler         ; MultiFunction Serial ch.6
    DCD     MFS6TX_IRQHandler         ; MultiFunction Serial ch.6
    DCD     MFS7RX_IRQHandler         ; MultiFunction Serial ch.7
    DCD     MFS7TX_IRQHandler         ; MultiFunction Serial ch.7
    DCD     PPG_IRQHandler            ; PPG
    DCD     OSC_PLL_WC_IRQHandler     ; OSC / PLL / Watch Counter
    DCD     ADC0_IRQHandler           ; ADC0
    DCD     ADC1_IRQHandler           ; ADC1
    DCD     ADC2_IRQHandler           ; ADC2
    DCD     FRTIM_IRQHandler          ; Free-run Timer
    DCD     INCAP_IRQHandler          ; Input Capture
    DCD     OUTCOMP_IRQHandler        ; Output Compare
    DCD     BTIM_IRQHandler           ; Base Timer ch.0 to ch.7
    DCD     CAN0_IRQHandler           ; CAN ch.0
    DCD     CAN1_IRQHandler           ; CAN ch.1
    DCD     USBF_IRQHandler           ; USB Function
    DCD     USBF_USBH_IRQHandler      ; USB Function / USB HOST
    DCD     RESERVED_1_IRQHandler     ; Reserved_1
    DCD     RESERVED_2_IRQHandler     ; Reserved_2
    DCD     DMAC0_IRQHandler          ; DMAC ch.0
    DCD     DMAC1_IRQHandler          ; DMAC ch.1
    DCD     DMAC2_IRQHandler          ; DMAC ch.2
    DCD     DMAC3_IRQHandler          ; DMAC ch.3
    DCD     DMAC4_IRQHandler          ; DMAC ch.4
    DCD     DMAC5_IRQHandler          ; DMAC ch.5
    DCD     DMAC6_IRQHandler          ; DMAC ch.6
    DCD     DMAC7_IRQHandler          ; DMAC ch.7
    DCD     RESERVED_3_IRQHandler     ; Reserved_3
    DCD     RESERVED_4_IRQHandler     ; Reserved_4

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
    THUMB

    PUBWEAK NMI_Handler
    SECTION .text:CODE:REORDER(1)
NMI_Handler
    B NMI_Handler
    PUBWEAK HardFault_Handler
    SECTION .text:CODE:REORDER(1)
HardFault_Handler
    B HardFault_Handler
    PUBWEAK MemManage_Handler
    SECTION .text:CODE:REORDER(1)
MemManage_Handler
    B MemManage_Handler
    PUBWEAK BusFault_Handler
    SECTION .text:CODE:REORDER(1)
BusFault_Handler
    B BusFault_Handler
    PUBWEAK UsageFault_Handler
    SECTION .text:CODE:REORDER(1)
UsageFault_Handler
    B UsageFault_Handler
    PUBWEAK SVC_Handler
    SECTION .text:CODE:REORDER(1)
SVC_Handler
    B SVC_Handler
    PUBWEAK DebugMon_Handler
    SECTION .text:CODE:REORDER(1)
DebugMon_Handler
    B DebugMon_Handler
    PUBWEAK PendSV_Handler
    SECTION .text:CODE:REORDER(1)
PendSV_Handler
    B PendSV_Handler
    PUBWEAK SysTick_Handler
    SECTION .text:CODE:REORDER(1)
SysTick_Handler
    B SysTick_Handler
    PUBWEAK CSV_IRQHandler
    SECTION .text:CODE:REORDER(1)
CSV_IRQHandler
    B CSV_IRQHandler
    PUBWEAK SWDT_IRQHandler
    SECTION .text:CODE:REORDER(1)
SWDT_IRQHandler
    B SWDT_IRQHandler
    PUBWEAK LVD_IRQHandler
    SECTION .text:CODE:REORDER(1)
LVD_IRQHandler
    B LVD_IRQHandler
    PUBWEAK WFG_IRQHandler
    SECTION .text:CODE:REORDER(1)
WFG_IRQHandler
    B WFG_IRQHandler
    PUBWEAK EXINT0_7_IRQHandler
    SECTION .text:CODE:REORDER(1)
EXINT0_7_IRQHandler
    B EXINT0_7_IRQHandler
    PUBWEAK EXINT8_15_IRQHandler
    SECTION .text:CODE:REORDER(1)
EXINT8_15_IRQHandler
    B EXINT8_15_IRQHandler
    PUBWEAK DTIM_QDU_IRQHandler
    SECTION .text:CODE:REORDER(1)
DTIM_QDU_IRQHandler
    B DTIM_QDU_IRQHandler
    PUBWEAK MFS0RX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS0RX_IRQHandler
    B MFS0RX_IRQHandler
    PUBWEAK MFS0TX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS0TX_IRQHandler
    B MFS0TX_IRQHandler
    PUBWEAK MFS1RX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS1RX_IRQHandler
    B MFS1RX_IRQHandler
    PUBWEAK MFS1TX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS1TX_IRQHandler
    B MFS1TX_IRQHandler
    PUBWEAK NULL_IRQHandler
    SECTION .text:CODE:REORDER(1)
NULL_IRQHandler
    B NULL_IRQHandler
    PUBWEAK MFS2TX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS2TX_IRQHandler
    B MFS2TX_IRQHandler
    PUBWEAK MFS3RX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS3RX_IRQHandler
    B MFS3RX_IRQHandler
    PUBWEAK MFS3TX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS3TX_IRQHandler
    B MFS3TX_IRQHandler
    PUBWEAK MFS4RX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS4RX_IRQHandler
    B MFS4RX_IRQHandler
    PUBWEAK MFS4TX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS4TX_IRQHandler
    B MFS4TX_IRQHandler
    PUBWEAK MFS5RX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS5RX_IRQHandler
    B MFS5RX_IRQHandler
    PUBWEAK MFS5TX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS5TX_IRQHandler
    B MFS5TX_IRQHandler
    PUBWEAK MFS6RX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS6RX_IRQHandler
    B MFS6RX_IRQHandler
    PUBWEAK MFS6TX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS6TX_IRQHandler
    B MFS6TX_IRQHandler
    PUBWEAK MFS7RX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS7RX_IRQHandler
    B MFS7RX_IRQHandler
    PUBWEAK MFS7TX_IRQHandler
    SECTION .text:CODE:REORDER(1)
MFS7TX_IRQHandler
    B MFS7TX_IRQHandler
    PUBWEAK PPG_IRQHandler
    SECTION .text:CODE:REORDER(1)
PPG_IRQHandler
    B PPG_IRQHandler
    PUBWEAK OSC_PLL_WC_IRQHandler
    SECTION .text:CODE:REORDER(1)
OSC_PLL_WC_IRQHandler
    B OSC_PLL_WC_IRQHandler
    PUBWEAK ADC0_IRQHandler
    SECTION .text:CODE:REORDER(1)
ADC0_IRQHandler
    B ADC0_IRQHandler
    PUBWEAK ADC1_IRQHandler
    SECTION .text:CODE:REORDER(1)
ADC1_IRQHandler
    B ADC1_IRQHandler
    PUBWEAK ADC2_IRQHandler
    SECTION .text:CODE:REORDER(1)
ADC2_IRQHandler
    B ADC2_IRQHandler
    PUBWEAK FRTIM_IRQHandler
    SECTION .text:CODE:REORDER(1)
FRTIM_IRQHandler
    B FRTIM_IRQHandler
    PUBWEAK INCAP_IRQHandler
    SECTION .text:CODE:REORDER(1)
INCAP_IRQHandler
    B INCAP_IRQHandler
    PUBWEAK OUTCOMP_IRQHandler
    SECTION .text:CODE:REORDER(1)
OUTCOMP_IRQHandler
    B OUTCOMP_IRQHandler
    PUBWEAK BTIM_IRQHandler
    SECTION .text:CODE:REORDER(1)
BTIM_IRQHandler
    B BTIM_IRQHandler
    PUBWEAK CAN0_IRQHandler
    SECTION .text:CODE:REORDER(1)
CAN0_IRQHandler
    B CAN0_IRQHandler
    PUBWEAK CAN1_IRQHandler
    SECTION .text:CODE:REORDER(1)
CAN1_IRQHandler
    B CAN1_IRQHandler
    PUBWEAK USBF_IRQHandler
    SECTION .text:CODE:REORDER(1)
USBF_IRQHandler
    B USBF_IRQHandler
    PUBWEAK USBF_USBH_IRQHandler
    SECTION .text:CODE:REORDER(1)
USBF_USBH_IRQHandler
    B USBF_USBH_IRQHandler
    PUBWEAK RESERVED_1_IRQHandler
    SECTION .text:CODE:REORDER(1)
RESERVED_1_IRQHandler
    B RESERVED_1_IRQHandler
    PUBWEAK RESERVED_2_IRQHandler
    SECTION .text:CODE:REORDER(1)
RESERVED_2_IRQHandler
    B RESERVED_2_IRQHandler
    PUBWEAK DMAC0_IRQHandler
    SECTION .text:CODE:REORDER(1)
DMAC0_IRQHandler
    B DMAC0_IRQHandler
    PUBWEAK DMAC1_IRQHandler
    SECTION .text:CODE:REORDER(1)
DMAC1_IRQHandler
    B DMAC1_IRQHandler
    PUBWEAK DMAC2_IRQHandler
    SECTION .text:CODE:REORDER(1)
DMAC2_IRQHandler
    B DMAC2_IRQHandler
    PUBWEAK DMAC3_IRQHandler
    SECTION .text:CODE:REORDER(1)
DMAC3_IRQHandler
    B DMAC3_IRQHandler
    PUBWEAK DMAC4_IRQHandler
    SECTION .text:CODE:REORDER(1)
DMAC4_IRQHandler
    B DMAC4_IRQHandler
    PUBWEAK DMAC5_IRQHandler
    SECTION .text:CODE:REORDER(1)
DMAC5_IRQHandler
    B DMAC5_IRQHandler
    PUBWEAK DMAC6_IRQHandler
    SECTION .text:CODE:REORDER(1)
DMAC6_IRQHandler
    B DMAC6_IRQHandler
    PUBWEAK DMAC7_IRQHandler
    SECTION .text:CODE:REORDER(1)
DMAC7_IRQHandler
    B DMAC7_IRQHandler
    PUBWEAK RESERVED_3_IRQHandler
    SECTION .text:CODE:REORDER(1)
RESERVED_3_IRQHandler
    B RESERVED_3_IRQHandler
    PUBWEAK RESERVED_4_IRQHandler
    SECTION .text:CODE:REORDER(1)
RESERVED_4_IRQHandler
    B RESERVED_4_IRQHandler

    END
