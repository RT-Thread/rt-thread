/* @file 
 * @brief startup file for Energy Micro 'EFM32GG/LG' devices. 
 *        For use with GCC for ARM Embedded Processors
 * @version 3.0.0
 * Date: 08 Feb 2012
 *
 * Copyright (c) 2012, ARM Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the ARM Limited nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ARM LIMITED BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Energy Micro release version
 * @version 3.0.0
 */
    .syntax unified
    .arch armv7-m

    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0x400
#endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0xC00
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .if    Heap_Size
    .space    Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

    .section .isr_vector
    .align 8
    .globl __isr_vector
__isr_vector:
    .long    __StackTop            /* Top of Stack */
    .long    Reset_Handler         /* Reset Handler */
    .long    NMI_Handler           /* NMI Handler */
    .long    HardFault_Handler     /* Hard Fault Handler */
    .long    MemManage_Handler     /* MPU Fault Handler */
    .long    BusFault_Handler      /* Bus Fault Handler */
    .long    UsageFault_Handler    /* Usage Fault Handler */
    .long    Default_Handler       /* Reserved */
    .long    Default_Handler       /* Reserved */
    .long    Default_Handler       /* Reserved */
    .long    Default_Handler       /* Reserved */
    .long    SVC_Handler           /* SVCall Handler */
    .long    DebugMon_Handler      /* Debug Monitor Handler */
    .long    Default_Handler       /* Reserved */
    .long    PendSV_Handler        /* PendSV Handler */
    .long    SysTick_Handler       /* SysTick Handler */

    /* External interrupts */
    .long    DMA_IRQHandler    /* 0 - DMA */
    .long    GPIO_EVEN_IRQHandler    /* 1 - GPIO_EVEN */
    .long    TIMER0_IRQHandler    /* 2 - TIMER0 */
    .long    USART0_RX_IRQHandler    /* 3 - USART0_RX */
    .long    USART0_TX_IRQHandler    /* 4 - USART0_TX */
    .long    USB_IRQHandler    /* 5 - USB */
    .long    ACMP0_IRQHandler    /* 6 - ACMP0 */
    .long    ADC0_IRQHandler    /* 7 - ADC0 */
    .long    DAC0_IRQHandler    /* 8 - DAC0 */
    .long    I2C0_IRQHandler    /* 9 - I2C0 */
    .long    I2C1_IRQHandler    /* 10 - I2C1 */
    .long    GPIO_ODD_IRQHandler    /* 11 - GPIO_ODD */
    .long    TIMER1_IRQHandler    /* 12 - TIMER1 */
    .long    TIMER2_IRQHandler    /* 13 - TIMER2 */
    .long    TIMER3_IRQHandler    /* 14 - TIMER3 */
    .long    USART1_RX_IRQHandler    /* 15 - USART1_RX */
    .long    USART1_TX_IRQHandler    /* 16 - USART1_TX */
    .long    LESENSE_IRQHandler    /* 17 - LESENSE */
    .long    USART2_RX_IRQHandler    /* 18 - USART2_RX */
    .long    USART2_TX_IRQHandler    /* 19 - USART2_TX */
    .long    UART0_RX_IRQHandler    /* 20 - UART0_RX */
    .long    UART0_TX_IRQHandler    /* 21 - UART0_TX */
    .long    UART1_RX_IRQHandler    /* 22 - UART1_RX */
    .long    UART1_TX_IRQHandler    /* 23 - UART1_TX */
    .long    LEUART0_IRQHandler    /* 24 - LEUART0 */
    .long    LEUART1_IRQHandler    /* 25 - LEUART1 */
    .long    LETIMER0_IRQHandler    /* 26 - LETIMER0 */
    .long    PCNT0_IRQHandler    /* 27 - PCNT0 */
    .long    PCNT1_IRQHandler    /* 28 - PCNT1 */
    .long    PCNT2_IRQHandler    /* 29 - PCNT2 */
    .long    RTC_IRQHandler    /* 30 - RTC */
    .long    BURTC_IRQHandler    /* 31 - BURTC */
    .long    CMU_IRQHandler    /* 32 - CMU */
    .long    VCMP_IRQHandler    /* 33 - VCMP */
    .long    LCD_IRQHandler    /* 34 - LCD */
    .long    MSC_IRQHandler    /* 35 - MSC */
    .long    AES_IRQHandler    /* 36 - AES */
    .long    EBI_IRQHandler    /* 37 - EBI */
    .long    EMU_IRQHandler    /* 38 - EMU */


    .size    __isr_vector, . - __isr_vector

    .text
    .thumb
    .thumb_func
    .align 2
    .globl    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */
#ifndef __NO_SYSTEM_INIT
    ldr    r0, =SystemInit
    blx    r0
#endif
    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

#if 1
/* Here are two copies of loop implemenations. First one favors code size
 * and the second one favors performance. Default uses the first one.
 * Change to "#if 0" to use the second one */
.flash_to_ram_loop:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .flash_to_ram_loop
#else
    subs    r3, r2
    ble    .flash_to_ram_loop_end
.flash_to_ram_loop:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .flash_to_ram_loop
.flash_to_ram_loop_end:
#endif

#ifndef __NO_SYSTEM_INIT
    ldr    r0, =SystemInit
    blx    r0
#endif

    ldr    r0, =_start
    bx    r0
    .pool
    .size Reset_Handler, . - Reset_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_irq_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name:
    b    .
    .size    \handler_name, . - \handler_name
    .endm

    def_irq_handler    Default_Handler

    def_irq_handler    NMI_Handler
    def_irq_handler    HardFault_Handler
    def_irq_handler    MemManage_Handler
    def_irq_handler    BusFault_Handler
    def_irq_handler    UsageFault_Handler
    def_irq_handler    SVC_Handler
    def_irq_handler    DebugMon_Handler
    def_irq_handler    PendSV_Handler
    def_irq_handler    SysTick_Handler

    def_irq_handler    DMA_IRQHandler
    def_irq_handler    GPIO_EVEN_IRQHandler
    def_irq_handler    TIMER0_IRQHandler
    def_irq_handler    USART0_RX_IRQHandler
    def_irq_handler    USART0_TX_IRQHandler
    def_irq_handler    USB_IRQHandler
    def_irq_handler    ACMP0_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    DAC0_IRQHandler
    def_irq_handler    I2C0_IRQHandler
    def_irq_handler    I2C1_IRQHandler
    def_irq_handler    GPIO_ODD_IRQHandler
    def_irq_handler    TIMER1_IRQHandler
    def_irq_handler    TIMER2_IRQHandler
    def_irq_handler    TIMER3_IRQHandler
    def_irq_handler    USART1_RX_IRQHandler
    def_irq_handler    USART1_TX_IRQHandler
    def_irq_handler    LESENSE_IRQHandler
    def_irq_handler    USART2_RX_IRQHandler
    def_irq_handler    USART2_TX_IRQHandler
    def_irq_handler    UART0_RX_IRQHandler
    def_irq_handler    UART0_TX_IRQHandler
    def_irq_handler    UART1_RX_IRQHandler
    def_irq_handler    UART1_TX_IRQHandler
    def_irq_handler    LEUART0_IRQHandler
    def_irq_handler    LEUART1_IRQHandler
    def_irq_handler    LETIMER0_IRQHandler
    def_irq_handler    PCNT0_IRQHandler
    def_irq_handler    PCNT1_IRQHandler
    def_irq_handler    PCNT2_IRQHandler
    def_irq_handler    RTC_IRQHandler
    def_irq_handler    BURTC_IRQHandler
    def_irq_handler    CMU_IRQHandler
    def_irq_handler    VCMP_IRQHandler
    def_irq_handler    LCD_IRQHandler
    def_irq_handler    MSC_IRQHandler
    def_irq_handler    AES_IRQHandler
    def_irq_handler    EBI_IRQHandler
    def_irq_handler    EMU_IRQHandler


    .end
