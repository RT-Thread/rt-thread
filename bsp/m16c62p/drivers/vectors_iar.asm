/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-09     fify         the first version
 *
 * For       : Renesas M16C
 * Toolchain : IAR's EW for M16C v3.401
 */

;********************************************************************************************************
;                                 RELOCATABLE EXCEPTION VECTOR TABLE
;********************************************************************************************************

    MODULE  ?vectors

    EXTERN  rt_hw_timer_handler
    EXTERN  rt_hw_uart0_receive_handler
    EXTERN  os_context_switch

    PUBLIC  RelocatableVectTbl

    RSEG    INTVEC:NOROOT

RelocatableVectTbl:
    ORG     0
    DC32    os_context_switch           ; Vector  0: BRK
    DC32    0                           ; Vector  1: Reserved
    DC32    0                           ; Vector  2: Reserved
    DC32    0                           ; Vector  3: Reserved
    DC32    0                           ; Vector  4: INT3
    DC32    0                           ; Vector  5: Timer B5
    DC32    0                           ; Vector  6: Timer B4, UART1 Bus Collision Detect
    DC32    0                           ; Vector  7: Timer B3, UART0 Bus Collision Detect
    DC32    0                           ; Vector  8: SI/O4, INT5
    DC32    0                           ; Vector  9: SI/O3, INT4
    DC32    0                           ; Vector 10: UART2 Bus Collision Detect
    DC32    0                           ; Vector 11: DMA0
    DC32    0                           ; Vector 12: DMA1
    DC32    0                           ; Vector 13: Key Input Interrupt
    DC32    0                           ; Vector 14: A/D
    DC32    0                           ; Vector 15: UART2 Transmit, NACK2
    DC32    0                           ; Vector 16: UART2 Receive,   ACK2
    DC32    0                           ; Vector 17: UART0 Transmit, NACK0
    DC32    rt_hw_uart0_receive_handler ; Vector 18: UART0 Receive,   ACK0
    DC32    0                           ; Vector 19: UART1 Transmit, NACK1
    DC32    0                           ; Vector 20: UART1 Receive,   ACK1
    DC32    0                           ; Vector 21: Timer A0
    DC32    0                           ; Vector 22: Timer A1
    DC32    0                           ; Vector 23: Timer A2
    DC32    0                           ; Vector 24: Timer A3
    DC32    0                           ; Vector 25: Timer A4
    DC32    rt_hw_timer_handler         ; Vector 26: Timer B0
    DC32    0                           ; Vector 27: Timer B1
    DC32    0                           ; Vector 28: Timer B2
    DC32    0                           ; Vector 29:
    DC32    0                           ; Vector 30:
    DC32    0                           ; Vector 31:

    ENDMOD

    END
