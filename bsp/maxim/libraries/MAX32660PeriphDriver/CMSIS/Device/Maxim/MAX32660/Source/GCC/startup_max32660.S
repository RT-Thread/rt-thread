/*******************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $ 
 * $Revision: 40072 $
 *
 ******************************************************************************/

    .syntax unified
    .arch armv7-m

    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0x00001000
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
    .equ    Heap_Size, 0x00000C00
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
    .align 2
    .globl __isr_vector
__isr_vector:
    .long    __StackTop            /* Top of Stack */
    .long    Reset_Handler         /* Reset Handler */
    .long    NMI_Handler           /* NMI Handler */
    .long    HardFault_Handler     /* Hard Fault Handler */
    .long    MemManage_Handler     /* MPU Fault Handler */
    .long    BusFault_Handler      /* Bus Fault Handler */
    .long    UsageFault_Handler    /* Usage Fault Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    SVC_Handler           /* SVCall Handler */
    .long    DebugMon_Handler      /* Debug Monitor Handler */
    .long    0                     /* Reserved */
    .long    PendSV_Handler        /* PendSV Handler */
    .long    SysTick_Handler       /* SysTick Handler */

    /* Device-specific Interrupts */
    .long PF_IRQHandler             /* 0x10  0x0040  16: Power Fail */
    .long WDT0_IRQHandler           /* 0x11  0x0044  17: Watchdog 0 */
    .long RSV00_IRQHandler          /* 0x12  0x0048  18: RSV00 */
    .long RTC_IRQHandler            /* 0x13  0x004C  19: RTC */
    .long RSV1_IRQHandler           /* 0x14  0x0050  20: RSV1 */
    .long TMR0_IRQHandler           /* 0x15  0x0054  21: Timer 0 */
    .long TMR1_IRQHandler           /* 0x16  0x0058  22: Timer 1 */
    .long TMR2_IRQHandler           /* 0x17  0x005C  23: Timer 2 */
    .long RSV02_IRQHandler          /* 0x18  0x0060  24: RSV02 */
    .long RSV03_IRQHandler          /* 0x19  0x0064  25: RSV03 */
    .long RSV04_IRQHandler          /* 0x1A  0x0068  26: RSV04 */
    .long RSV05_IRQHandler          /* 0x1B  0x006C  27: RSV05 */
    .long RSV06_IRQHandler          /* 0x1C  0x0070  28: RSV06 */
    .long I2C0_IRQHandler           /* 0x1D  0x0074  29: I2C0 */
    .long UART0_IRQHandler          /* 0x1E  0x0078  30: UART 0 */
    .long UART1_IRQHandler          /* 0x1F  0x007C  31: UART 1 */
    .long SPI0_IRQHandler           /* 0x20  0x0080  32: SPIY17 */
    .long SPI1_IRQHandler           /* 0x21  0x0084  33: SPIMSS */
    .long RSV07_IRQHandler          /* 0x22  0x0088  34: RSV07 */
    .long RSV08_IRQHandler          /* 0x23  0x008C  35: RSV08 */
    .long RSV09_IRQHandler          /* 0x24  0x0090  36: RSV09 */
    .long RSV10_IRQHandler          /* 0x25  0x0094  37: RSV10 */
    .long RSV11_IRQHandler          /* 0x26  0x0098  38: RSV11 */
    .long FLC_IRQHandler            /* 0x27  0x009C  39: FLC */
    .long GPIO0_IRQHandler          /* 0x28  0x00A0  40: GPIO0 */
    .long RSV12_IRQHandler          /* 0x29  0x00A4  41: RSV12 */
    .long RSV13_IRQHandler          /* 0x2A  0x00A8  42: RSV13 */
    .long RSV14_IRQHandler          /* 0x2B  0x00AC  43: RSV14 */
    .long DMA0_IRQHandler           /* 0x2C  0x00B0  44: DMA0 */
    .long DMA1_IRQHandler           /* 0x2D  0x00B4  45: DMA1 */
    .long DMA2_IRQHandler           /* 0x2E  0x00B8  46: DMA2 */
    .long DMA3_IRQHandler           /* 0x2F  0x00BC  47: DMA3 */
    .long RSV15_IRQHandler          /* 0x30  0x00C0  48: RSV15 */
    .long RSV16_IRQHandler          /* 0x31  0x00C4  49: RSV16 */
    .long RSV17_IRQHandler          /* 0x32  0x00C8  50: RSV17 */
    .long RSV18_IRQHandler          /* 0x33  0x00CC  51: RSV18 */
    .long I2C1_IRQHandler           /* 0x34  0x00D0  52: I2C1 */
    .long RSV19_IRQHandler          /* 0x35  0x00D4  53: RSV19 */
    .long RSV20_IRQHandler          /* 0x36  0x00D8  54: RSV20 */
    .long RSV21_IRQHandler          /* 0x37  0x00DC  55: RSV21 */
    .long RSV22_IRQHandler          /* 0x38  0x00E0  56: RSV22 */
    .long RSV23_IRQHandler          /* 0x39  0x00E4  57: RSV23 */
    .long RSV24_IRQHandler          /* 0x3A  0x00E8  58: RSV24 */
    .long RSV25_IRQHandler          /* 0x3B  0x00EC  59: RSV25 */
    .long RSV26_IRQHandler          /* 0x3C  0x00F0  60: RSV26 */
    .long RSV27_IRQHandler          /* 0x3D  0x00F4  61: RSV27 */
    .long RSV28_IRQHandler          /* 0x3E  0x00F8  62: RSV28 */
    .long RSV29_IRQHandler          /* 0x3F  0x00FC  63: RSV29 */
    .long RSV30_IRQHandler          /* 0x40  0x0100  64: RSV30 */
    .long RSV31_IRQHandler          /* 0x41  0x0104  65: RSV31 */
    .long RSV32_IRQHandler          /* 0x42  0x0108  66: RSV32 */
    .long RSV33_IRQHandler          /* 0x43  0x010C  67: RSV33 */
    .long RSV34_IRQHandler          /* 0x44  0x0110  68: RSV34 */
    .long RSV35_IRQHandler          /* 0x45  0x0114  69: RSV35 */
    .long GPIOWAKE_IRQHandler       /* 0x46  0x0118  70: GPIO Wakeup */
    .text 	
    .thumb
    .thumb_func
    .align 2
    .globl   Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    ldr r0, =__StackTop
    mov sp, r0

    /* PreInit runs before any RAM initialization. Example usage: DDR setup, etc. */
    ldr     r0, =PreInit
    blx     r0
    cbnz    r0, .SKIPRAMINIT

/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __load_data: Where data sections are saved.
 *      _data /_edata: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__load_data
    ldr    r2, =_data
    ldr    r3, =_edata

#if 0
/* Here are two copies of loop implemenations. First one favors code size
 * and the second one favors performance. Default uses the first one.
 * Change to "#if 0" to use the second one */
.LC0:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC0
#else
    subs    r3, r2
    ble    .LC1
.LC0:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC0
.LC1:
#endif

/*
 *     Loop to zero out BSS section, which uses following symbols
 *     in linker script:
 *      _bss  : start of BSS section. Must align to 4
 *      _ebss : end of BSS section. Must align to 4
 */
    ldr r1, =_bss
    ldr r2, =_ebss

    movs    r0, 0
.LC2:
    cmp     r1, r2
    itt    lt
    strlt   r0, [r1], #4
    blt    .LC2

.SKIPRAMINIT:

    /* Perform system initialization after RAM initialization */
    ldr     r0, =SystemInit
    blx     r0

    /* This must be called to walk the constructor array for static C++ objects */
    /* Note: The linker file must have .data symbols for __X_array_start and __X_array_end */
    /*        where X is {preinit, init, fini}                                             */
    ldr     r0, =__libc_init_array
    blx     r0  

    /* Transfer control to users main program */
    ldr     r0, =entry
    blx     r0 

.SPIN:
    /* spin if main ever returns. */
    bl .SPIN

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_irq_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
    b    .
    .size    \handler_name, . - \handler_name
    .endm

    def_irq_handler    NMI_Handler
    def_irq_handler    HardFault_Handler
    def_irq_handler    MemManage_Handler
    def_irq_handler    BusFault_Handler
    def_irq_handler    UsageFault_Handler
    def_irq_handler    SVC_Handler
    def_irq_handler    DebugMon_Handler
    def_irq_handler    PendSV_Handler
    /* SysTick_Handler is defined in mxc_delay.c */
    def_irq_handler    Default_Handler

    /* Device-specific Interrupts */
    def_irq_handler PF_IRQHandler             /* 0x10  0x0040  16: Power Fail */
    def_irq_handler WDT0_IRQHandler           /* 0x11  0x0044  17: Watchdog 0 */
    def_irq_handler RSV00_IRQHandler          /* 0x12  0x0048  18: RSV00 */
    def_irq_handler RTC_IRQHandler            /* 0x13  0x004C  19: RTC */
    def_irq_handler RSV1_IRQHandler           /* 0x14  0x0050  20: RSV1 */
    def_irq_handler TMR0_IRQHandler           /* 0x15  0x0054  21: Timer 0 */
    def_irq_handler TMR1_IRQHandler           /* 0x16  0x0058  22: Timer 1 */
    def_irq_handler TMR2_IRQHandler           /* 0x17  0x005C  23: Timer 2 */
    def_irq_handler RSV02_IRQHandler          /* 0x18  0x0060  24: RSV02 */
    def_irq_handler RSV03_IRQHandler          /* 0x19  0x0064  25: RSV03 */
    def_irq_handler RSV04_IRQHandler          /* 0x1A  0x0068  26: RSV04 */
    def_irq_handler RSV05_IRQHandler          /* 0x1B  0x006C  27: RSV05 */
    def_irq_handler RSV06_IRQHandler          /* 0x1C  0x0070  28: RSV06 */
    def_irq_handler I2C0_IRQHandler           /* 0x1D  0x0074  29: I2C0 */
    def_irq_handler UART0_IRQHandler          /* 0x1E  0x0078  30: UART 0 */
    def_irq_handler UART1_IRQHandler          /* 0x1F  0x007C  31: UART 1 */
    def_irq_handler SPI0_IRQHandler           /* 0x20  0x0080  32: SPIY17 */
    def_irq_handler SPI1_IRQHandler           /* 0x21  0x0084  33: SPIMSS */
    def_irq_handler RSV07_IRQHandler          /* 0x22  0x0088  34: RSV07 */
    def_irq_handler RSV08_IRQHandler          /* 0x23  0x008C  35: RSV08 */
    def_irq_handler RSV09_IRQHandler          /* 0x24  0x0090  36: RSV09 */
    def_irq_handler RSV10_IRQHandler          /* 0x25  0x0094  37: RSV10 */
    def_irq_handler RSV11_IRQHandler          /* 0x26  0x0098  38: RSV11 */
    def_irq_handler FLC_IRQHandler            /* 0x27  0x009C  39: FLC */
    def_irq_handler GPIO0_IRQHandler          /* 0x28  0x00A0  40: GPIO0 */
    def_irq_handler RSV12_IRQHandler          /* 0x29  0x00A4  41: RSV12 */
    def_irq_handler RSV13_IRQHandler          /* 0x2A  0x00A8  42: RSV13 */
    def_irq_handler RSV14_IRQHandler          /* 0x2B  0x00AC  43: RSV14 */
    def_irq_handler DMA0_IRQHandler           /* 0x2C  0x00B0  44: DMA0 */
    def_irq_handler DMA1_IRQHandler           /* 0x2D  0x00B4  45: DMA1 */
    def_irq_handler DMA2_IRQHandler           /* 0x2E  0x00B8  46: DMA2 */
    def_irq_handler DMA3_IRQHandler           /* 0x2F  0x00BC  47: DMA3 */
    def_irq_handler RSV15_IRQHandler          /* 0x30  0x00C0  48: RSV15 */
    def_irq_handler RSV16_IRQHandler          /* 0x31  0x00C4  49: RSV16 */
    def_irq_handler RSV17_IRQHandler          /* 0x32  0x00C8  50: RSV17 */
    def_irq_handler RSV18_IRQHandler          /* 0x33  0x00CC  51: RSV18 */
    def_irq_handler I2C1_IRQHandler           /* 0x34  0x00D0  52: I2C1 */
    def_irq_handler RSV19_IRQHandler          /* 0x35  0x00D4  53: RSV19 */
    def_irq_handler RSV20_IRQHandler          /* 0x36  0x00D8  54: RSV20 */
    def_irq_handler RSV21_IRQHandler          /* 0x37  0x00DC  55: RSV21 */
    def_irq_handler RSV22_IRQHandler          /* 0x38  0x00E0  56: RSV22 */
    def_irq_handler RSV23_IRQHandler          /* 0x39  0x00E4  57: RSV23 */
    def_irq_handler RSV24_IRQHandler          /* 0x3A  0x00E8  58: RSV24 */
    def_irq_handler RSV25_IRQHandler          /* 0x3B  0x00EC  59: RSV25 */
    def_irq_handler RSV26_IRQHandler          /* 0x3C  0x00F0  60: RSV26 */
    def_irq_handler RSV27_IRQHandler          /* 0x3D  0x00F4  61: RSV27 */
    def_irq_handler RSV28_IRQHandler          /* 0x3E  0x00F8  62: RSV28 */
    def_irq_handler RSV29_IRQHandler          /* 0x3F  0x00FC  63: RSV29 */
    def_irq_handler RSV30_IRQHandler          /* 0x40  0x0100  64: RSV30 */
    def_irq_handler RSV31_IRQHandler          /* 0x41  0x0104  65: RSV31 */
    def_irq_handler RSV32_IRQHandler          /* 0x42  0x0108  66: RSV32 */
    def_irq_handler RSV33_IRQHandler          /* 0x43  0x010C  67: RSV33 */
    def_irq_handler RSV34_IRQHandler          /* 0x44  0x0110  68: RSV34 */
    def_irq_handler RSV35_IRQHandler          /* 0x45  0x0114  69: RSV35 */
    def_irq_handler GPIOWAKE_IRQHandler       /* 0x46  0x0118  70: GPIO Wakeup */

    .end
