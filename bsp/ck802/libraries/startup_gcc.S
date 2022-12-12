/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-01-01     Urey      first version
 */


#undef  VIC_TSPR
#define VIC_TSPR                    0xE000EC10

#ifndef CONFIG_SEPARATE_IRQ_SP
#define CONFIG_SEPARATE_IRQ_SP      1
#endif

#ifndef CONFIG_ARCH_INTERRUPTSTACK
#define CONFIG_ARCH_INTERRUPTSTACK  1024
#endif

.import SysTick_Handler
.import PendSV_Handler

    .section .vectors
    .align 10
    .globl  __Vectors
    .type   __Vectors, @object
__Vectors:
    .long   Reset_Handler         /* 0: Reset Handler */

    .rept   15
    .long   Default_Handler       /* 60 0x40 */
    .endr                         /* 64 0x40 */

    .long   Default_Handler       /* 64 0x44 */

    .rept   5
    .long   Default_Handler       /* 88 0x58 */
    .endr                         /* 92 0x5C */

    .long   PendSV_Handler        /* 92 0x5C */

    .rept   9
    .long   Default_Handler       /* 128 0x80 */
    .endr

    /* External interrupts */
    .long   GPIOA_IRQHandler         /*  32#  0:  GPIOA           */ /*128  0x80 */
    .long   SysTick_Handler          /*  1:  System Tick     */
    .long   TIMA0_IRQHandler         /*  2:  TimerA0         */
    .long   TIMA1_IRQHandler         /*  3:  TimerA1         */
    .long   Default_Handler
    .long   WDT_IRQHandler           /*  5:  WDT            */
    .long   USART0_IRQHandler        /*  6:  UART0          */
    .long   USART1_IRQHandler        /*  0x27 39 7:  UART1          */
    .long   USART2_IRQHandler        /*  8:  UART2          */
    .long   I2C0_IRQHandler          /*  9:  I2C0           */
    .long   I2C1_IRQHandler          /*  10: I2C1           */
    .long   SPI1_IRQHandler          /*  11: SPI1           */
    .long   SPI0_IRQHandler          /*  12: SPI0           */
    .long   RTC_IRQHandler           /*  13: RTC            */
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   DMAC_IRQHandler          /*  17: DMAC           */
    .long   Default_Handler
    .long   PWM_IRQHandler           /*  19: PWM            */
    .long   Default_Handler
    .long   USART3_IRQHandler        /*  21: UART3          */
    .long   Default_Handler
    .long   TIMB0_IRQHandler         /*  23: TimerB0        */
    .long   TIMB1_IRQHandler         /*  24: TimerB1        */
    .long   Default_Handler
    .long   AES_IRQHandler           /*  26:  AES            */
    .long   GPIOB_IRQHandler         /*  27:  GPIOB          */
    .long   Default_Handler
    .long   SHA_IRQHandler           /*  29:  SHA            */

    .size   __Vectors, . - __Vectors

    .text
    .align  1
_start:
    .text
    .align  1
    .globl  Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
    /* under normal circumstances,  it should not be opened */

#ifndef CONFIG_SYSTEM_SECURE
    lrw     r0, 0x80000000
    mtcr    r0, psr
#endif

/* Initialize the normal stack pointer from the linker definition. */
    lrw     a1, __StackTop
    mov     sp, a1

/*
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
    lrw     r1, __erodata
    lrw     r2, __data_start__
    lrw     r3, __data_end__

    subu    r3, r2
    cmpnei  r3, 0
    bf      .L_loop0_done

.L_loop0:
    ldw     r0, (r1, 0)
    stw     r0, (r2, 0)
    addi    r1, 4
    addi    r2, 4
    subi    r3, 4
    cmpnei  r3, 0
    bt      .L_loop0

.L_loop0_done:

/*
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
    lrw     r1, __bss_start__
    lrw     r2, __bss_end__

    movi    r0, 0

    subu    r2, r1
    cmpnei  r2, 0
    bf      .L_loop1_done

.L_loop1:
    stw     r0, (r1, 0)
    addi    r1, 4
    subi    r2, 4
    cmpnei  r2, 0
    bt      .L_loop1
.L_loop1_done:

#ifdef CONFIG_SEPARATE_IRQ_SP
    lrw     r0, g_top_irqstack
    mtcr    r0, cr<15, 1>

    mfcr    r0, cr<31, 0>
    bseti   r0, 14
    mtcr    r0, cr<31, 0>
#endif

#ifndef __NO_SYSTEM_INIT
    bsr     SystemInit
#endif

//#ifndef __NO_BOARD_INIT
//  bsr     board_init
//#endif

//VIC init...
    lrw    r0, VIC_TSPR
    movi   r1, 0xb00
    stw    r1, (r0)

    bsr entry

__exit:
    bkpt
    .size   Reset_Handler, . - Reset_Handler

    .align  1
    .weak   Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    br      Default_Handler
    .size   Default_Handler, . - Default_Handler

.section .bss

    .align  2
    .globl  g_intstackalloc
    .global g_intstackbase
    .global g_top_irqstack
g_intstackalloc:
g_intstackbase:
    .space CONFIG_ARCH_INTERRUPTSTACK
g_top_irqstack:

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler CORET_IRQHandler
    def_irq_handler TIMA0_IRQHandler
    def_irq_handler TIMA1_IRQHandler
    def_irq_handler TIMB0_IRQHandler
    def_irq_handler TIMB1_IRQHandler
    def_irq_handler USART0_IRQHandler
    def_irq_handler USART1_IRQHandler
    def_irq_handler USART2_IRQHandler
    def_irq_handler USART3_IRQHandler
    def_irq_handler GPIOA_IRQHandler
    def_irq_handler GPIOB_IRQHandler
    def_irq_handler I2C0_IRQHandler
    def_irq_handler I2C1_IRQHandler
    def_irq_handler SPI0_IRQHandler
    def_irq_handler SPI1_IRQHandler
    def_irq_handler RTC_IRQHandler
    def_irq_handler WDT_IRQHandler
    def_irq_handler PWM_IRQHandler
    def_irq_handler DMAC_IRQHandler
    def_irq_handler AES_IRQHandler
    def_irq_handler SHA_IRQHandler

    .end

