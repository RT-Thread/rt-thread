/*
 * Copyright (c) 2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-05     jg1uaa       the first version
 */

#include "../rtconfig.h"

/* Interrupt Vectors */
        .section .isr_vector
        .thumb
        .align 0

        .long   _estack                 // MSP default value
        .long   Reset_Handler + 1       //  1: Reset
        .long   default_handler + 1     //  2: NMI
        .long   HardFault_Handler + 1   //  3: HardFault
        .long   default_handler + 1     //  4: reserved
        .long   default_handler + 1     //  5: reserved
        .long   default_handler + 1     //  6: reserved
        .long   default_handler + 1     //  7: reserved
        .long   default_handler + 1     //  8: reserved
        .long   default_handler + 1     //  9: reserved
        .long   default_handler + 1     // 10: reserved
        .long   default_handler + 1     // 11: SVCall
        .long   default_handler + 1     // 12: reserved
        .long   default_handler + 1     // 13: reserved
        .long   PendSV_Handler + 1      // 14: PendSV
        .long   SysTick_Handler + 1     // 15: SysTick
        .long   default_handler + 1     // 16: External Interrupt(0)
        .long   default_handler + 1     // 17: External Interrupt(1)
        .long   default_handler + 1     // 18: External Interrupt(2)
        .long   default_handler + 1     // 19: External Interrupt(3)
        .long   default_handler + 1     // 20: External Interrupt(4)
        .long   default_handler + 1     // 21: External Interrupt(5)
        .long   default_handler + 1     // 22: External Interrupt(6)
        .long   default_handler + 1     // 23: External Interrupt(7)
        .long   default_handler + 1     // 24: External Interrupt(8)
        .long   default_handler + 1     // 25: External Interrupt(9)
        .long   default_handler + 1     // 26: External Interrupt(10)
        .long   default_handler + 1     // 27: External Interrupt(11)
        .long   default_handler + 1     // 28: External Interrupt(12)
        .long   default_handler + 1     // 29: External Interrupt(13) C_CAN
        .long   default_handler + 1     // 30: External Interrupt(14) SPI/SSP1
        .long   default_handler + 1     // 31: External Interrupt(15) I2C
        .long   default_handler + 1     // 32: External Interrupt(16) CT16B0
        .long   default_handler + 1     // 33: External Interrupt(17) CT16B1
        .long   default_handler + 1     // 34: External Interrupt(18) CT32B0
        .long   default_handler + 1     // 35: External Interrupt(19) CT32B1
        .long   default_handler + 1     // 36: External Interrupt(20) SPI/SSP0
        .long   UART_IRQHandler + 1     // 37: External Interrupt(21) UART
        .long   default_handler + 1     // 38: External Interrupt(22)
        .long   default_handler + 1     // 39: External Interrupt(23)
        .long   default_handler + 1     // 40: External Interrupt(24) ADC
        .long   default_handler + 1     // 41: External Interrupt(25) WDT
        .long   default_handler + 1     // 42: External Interrupt(26) BOD
        .long   default_handler + 1     // 43: External Interrupt(27)
        .long   default_handler + 1     // 44: External Interrupt(28) PIO_3
        .long   default_handler + 1     // 45: External Interrupt(29) PIO_2
        .long   default_handler + 1     // 46: External Interrupt(30) PIO_1
        .long   default_handler + 1     // 47: External Interrupt(31) PIO_0
        .long   default_handler + 1     // 48: External Interrupt(32)
        .long   default_handler + 1     // 49: External Interrupt(33)
        .long   default_handler + 1     // 50: External Interrupt(34)
        .long   default_handler + 1     // 51: External Interrupt(35)
        .long   default_handler + 1     // 52: External Interrupt(36)
        .long   default_handler + 1     // 53: External Interrupt(37)
        .long   default_handler + 1     // 54: External Interrupt(38)
        .long   default_handler + 1     // 55: External Interrupt(39)
        .long   default_handler + 1     // 56: External Interrupt(40)
        .long   default_handler + 1     // 57: External Interrupt(41)
        .long   default_handler + 1     // 58: External Interrupt(42)
        .long   default_handler + 1     // 59: External Interrupt(43)
        .long   default_handler + 1     // 60: External Interrupt(44)
        .long   default_handler + 1     // 61: External Interrupt(45)
        .long   default_handler + 1     // 62: External Interrupt(46)
        .long   default_handler + 1     // 63: External Interrupt(47)

/* startup */
        .section .text
        .thumb
        .align 0
        .global Reset_Handler
Reset_Handler:

        /* initialize .data */
data_init:
        ldr     r1, =_sidata
        ldr     r2, =_sdata
        ldr     r3, =_edata
        cmp     r2, r3
        beq     bss_init
data_loop:
        ldrb    r0, [r1]
        add     r1, r1, #1
        strb    r0, [r2]
        add     r2, r2, #1
        cmp     r2, r3
        bne     data_loop

        /* initialize .bss */
bss_init:
        mov     r0, #0
        ldr     r2, =_sbss      // sbss/ebss is 4byte aligned by link.lds
        ldr     r3, =_ebss
        cmp     r2, r3
        beq     start_main
bss_loop:
        str     r0, [r2]
        add     r2, r2, #4
        cmp     r2, r3
        bne     bss_loop

        /* launch main() */
start_main:
#ifdef RT_USING_USER_MAIN
        bl      entry
#else
        bl      main
#endif

default_handler:
die:
        b       die

        .pool

    .end