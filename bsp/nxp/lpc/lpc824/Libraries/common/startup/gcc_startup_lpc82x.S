/* ------------------------------------------------------------------------- */
/*  @file:    startup_LPC824.s                                               */
/*  @purpose: CMSIS Cortex-M0P Core Device Startup File                      */
/*            LPC824                                                         */
/*  @version: 1.1                                                            */
/*  @date:    2018-2-25                                                      */
/*  @build:   b231018                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2023 NXP                                                   */
/* SPDX-License-Identifier: BSD-3-Clause                                     */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv6-m

    .section .isr_vector, "a"
    .align 2
    .globl __Vectors
__Vectors:
    .long   __StackTop                                      /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler*/
    .long   HardFault_Handler                               /* Hard Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

                                                            /* External Interrupts*/
    .long   SPI0_IRQHandler                                 /* SPI0 interrupt*/
    .long   SPI1_IRQHandler                                 /* SPI1 interrupt*/
    .long   Reserved18_IRQHandler                           /* Reserved interrupt*/
    .long   USART0_IRQHandler                               /* USART0 interrupt*/
    .long   USART1_IRQHandler                               /* USART1 interrupt*/
    .long   USART2_IRQHandler                               /* USART2 interrupt*/
    .long   Reserved22_IRQHandler                           /* Reserved interrupt*/
    .long   I2C1_IRQHandler                                 /* I2C1 interrupt*/
    .long   I2C0_IRQHandler                                 /* I2C0 interrupt*/
    .long   SCT0_IRQHandler                                 /* State configurable timer interrupt*/
    .long   MRT0_IRQHandler                                 /* Multi-rate timer interrupt*/
    .long   CMP_IRQHandler                                  /* Analog comparator interrupt*/
    .long   WDT_IRQHandler                                  /* Windowed watchdog timer interrupt*/
    .long   BOD_IRQHandler                                  /* BOD interrupts*/
    .long   FLASH_IRQHandler                                /* flash interrupt*/
    .long   WKT_IRQHandler                                  /* Self-wake-up timer interrupt*/
    .long   ADC0_SEQA_IRQHandler                            /* ADC0 sequence A completion.*/
    .long   ADC0_SEQB_IRQHandler                            /* ADC0 sequence B completion.*/
    .long   ADC0_THCMP_IRQHandler                           /* ADC0 threshold compare and error.*/
    .long   ADC0_OVR_IRQHandler                             /* ADC0 overrun*/
    .long   DMA0_IRQHandler                                 /* DMA0 interrupt*/
    .long   I2C2_IRQHandler                                 /* I2C2 interrupt*/
    .long   I2C3_IRQHandler                                 /* I2C3 interrupt*/
    .long   Reserved39_IRQHandler                           /* Reserved interrupt*/
    .long   PIN_INT0_IRQHandler                             /* Pin interrupt 0 or pattern match engine slice 0 interrupt*/
    .long   PIN_INT1_IRQHandler                             /* Pin interrupt 1 or pattern match engine slice 1 interrupt*/
    .long   PIN_INT2_IRQHandler                             /* Pin interrupt 2 or pattern match engine slice 2 interrupt*/
    .long   PIN_INT3_IRQHandler                             /* Pin interrupt 3 or pattern match engine slice 3 interrupt*/
    .long   PIN_INT4_IRQHandler                             /* Pin interrupt 4 or pattern match engine slice 4 interrupt*/
    .long   PIN_INT5_IRQHandler                             /* Pin interrupt 5 or pattern match engine slice 5 interrupt*/
    .long   PIN_INT6_IRQHandler                             /* Pin interrupt 6 or pattern match engine slice 6 interrupt*/
    .long   PIN_INT7_IRQHandler                             /* Pin interrupt 7 or pattern match engine slice 7 interrupt*/

    .size   __Vectors, . - __Vectors

/*  Variable to store CRP value in. No code read protection enabled by default
 *  Code Read Protection level (CRP)
 *    CRP_Level:
 *      <0xFFFFFFFF=> Disabled
 *      <0x4E697370=> NO_ISP
 *      <0x12345678=> CRP1
 *      <0x87654321=> CRP2
 *      <0x43218765=> CRP3
 */
    #ifndef NO_CRP
      .section .crp, "a"
      .long 0xFFFFFFFF
    #endif

    .text
    .thumb

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#endif
#endif
/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */
#ifndef __NO_SYSTEM_INIT
    ldr   r0,=SystemInit
    blx   r0
#endif
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

    subs    r3, r2
    ble     .LC0

.LC1:
    subs    r3, 4
    ldr    r0, [r1,r3]
    str    r0, [r2,r3]
    bgt    .LC1
.LC0:

#ifdef __STARTUP_CLEAR_BSS
/*     This part of work usually is done in C library startup code. Otherwise,
 *     define this macro to enable it in this startup.
 *
 *     Loop to zero out BSS section, which uses following symbols
 *     in linker script:
 *      __bss_start__: start of BSS section. Must align to 4
 *      __bss_end__: end of BSS section. Must align to 4
 */
    ldr r1, =__bss_start__
    ldr r2, =__bss_end__

    subs    r2, r1
    ble .LC3

    movs    r0, 0
.LC2:
    subs    r2, 4
    str r0, [r1, r2]
    bgt .LC2
.LC3:
#endif
    cpsie   i               /* Unmask interrupts */
#ifndef __START
#ifdef __REDLIB__
#define __START __main
#else
#define __START entry
#endif
#endif
#ifndef __ATOLLIC__
    ldr   r0,=__START
    blx   r0
#else
    ldr   r0,=__libc_init_array
    blx   r0
    ldr   r0,=entry
    bx    r0
#endif
    .pool
    .size Reset_Handler, . - Reset_Handler

    .align  1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    ldr r0, =DefaultISR
    bx r0
    .size DefaultISR, . - DefaultISR

    .align 1
    .thumb_func
    .weak NMI_Handler
    .type NMI_Handler, %function
NMI_Handler:
    ldr   r0,=NMI_Handler
    bx    r0
    .size NMI_Handler, . - NMI_Handler

    .align 1
    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
HardFault_Handler:
    ldr   r0,=HardFault_Handler
    bx    r0
    .size HardFault_Handler, . - HardFault_Handler

    .align 1
    .thumb_func
    .weak SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
    ldr   r0,=SVC_Handler
    bx    r0
    .size SVC_Handler, . - SVC_Handler

    .align 1
    .thumb_func
    .weak PendSV_Handler
    .type PendSV_Handler, %function
PendSV_Handler:
    ldr   r0,=PendSV_Handler
    bx    r0
    .size PendSV_Handler, . - PendSV_Handler

    .align 1
    .thumb_func
    .weak SysTick_Handler
    .type SysTick_Handler, %function
SysTick_Handler:
    ldr   r0,=SysTick_Handler
    bx    r0
    .size SysTick_Handler, . - SysTick_Handler

    .align 1
    .thumb_func
    .weak SPI0_IRQHandler
    .type SPI0_IRQHandler, %function
SPI0_IRQHandler:
    ldr   r0,=SPI0_DriverIRQHandler
    bx    r0
    .size SPI0_IRQHandler, . - SPI0_IRQHandler

    .align 1
    .thumb_func
    .weak SPI1_IRQHandler
    .type SPI1_IRQHandler, %function
SPI1_IRQHandler:
    ldr   r0,=SPI1_DriverIRQHandler
    bx    r0
    .size SPI1_IRQHandler, . - SPI1_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved18_IRQHandler
    .type Reserved18_IRQHandler, %function
Reserved18_IRQHandler:
    ldr   r0,=Reserved18_DriverIRQHandler
    bx    r0
    .size Reserved18_IRQHandler, . - Reserved18_IRQHandler

    .align 1
    .thumb_func
    .weak USART0_IRQHandler
    .type USART0_IRQHandler, %function
USART0_IRQHandler:
    ldr   r0,=USART0_DriverIRQHandler
    bx    r0
    .size USART0_IRQHandler, . - USART0_IRQHandler

    .align 1
    .thumb_func
    .weak USART1_IRQHandler
    .type USART1_IRQHandler, %function
USART1_IRQHandler:
    ldr   r0,=USART1_DriverIRQHandler
    bx    r0
    .size USART1_IRQHandler, . - USART1_IRQHandler

    .align 1
    .thumb_func
    .weak USART2_IRQHandler
    .type USART2_IRQHandler, %function
USART2_IRQHandler:
    ldr   r0,=USART2_DriverIRQHandler
    bx    r0
    .size USART2_IRQHandler, . - USART2_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved22_IRQHandler
    .type Reserved22_IRQHandler, %function
Reserved22_IRQHandler:
    ldr   r0,=Reserved22_DriverIRQHandler
    bx    r0
    .size Reserved22_IRQHandler, . - Reserved22_IRQHandler

    .align 1
    .thumb_func
    .weak I2C1_IRQHandler
    .type I2C1_IRQHandler, %function
I2C1_IRQHandler:
    ldr   r0,=I2C1_DriverIRQHandler
    bx    r0
    .size I2C1_IRQHandler, . - I2C1_IRQHandler

    .align 1
    .thumb_func
    .weak I2C0_IRQHandler
    .type I2C0_IRQHandler, %function
I2C0_IRQHandler:
    ldr   r0,=I2C0_DriverIRQHandler
    bx    r0
    .size I2C0_IRQHandler, . - I2C0_IRQHandler

    .align 1
    .thumb_func
    .weak SCT0_IRQHandler
    .type SCT0_IRQHandler, %function
SCT0_IRQHandler:
    ldr   r0,=SCT0_DriverIRQHandler
    bx    r0
    .size SCT0_IRQHandler, . - SCT0_IRQHandler

    .align 1
    .thumb_func
    .weak MRT0_IRQHandler
    .type MRT0_IRQHandler, %function
MRT0_IRQHandler:
    ldr   r0,=MRT0_DriverIRQHandler
    bx    r0
    .size MRT0_IRQHandler, . - MRT0_IRQHandler

    .align 1
    .thumb_func
    .weak CMP_IRQHandler
    .type CMP_IRQHandler, %function
CMP_IRQHandler:
    ldr   r0,=CMP_DriverIRQHandler
    bx    r0
    .size CMP_IRQHandler, . - CMP_IRQHandler

    .align 1
    .thumb_func
    .weak WDT_IRQHandler
    .type WDT_IRQHandler, %function
WDT_IRQHandler:
    ldr   r0,=WDT_DriverIRQHandler
    bx    r0
    .size WDT_IRQHandler, . - WDT_IRQHandler

    .align 1
    .thumb_func
    .weak BOD_IRQHandler
    .type BOD_IRQHandler, %function
BOD_IRQHandler:
    ldr   r0,=BOD_DriverIRQHandler
    bx    r0
    .size BOD_IRQHandler, . - BOD_IRQHandler

    .align 1
    .thumb_func
    .weak FLASH_IRQHandler
    .type FLASH_IRQHandler, %function
FLASH_IRQHandler:
    ldr   r0,=FLASH_DriverIRQHandler
    bx    r0
    .size FLASH_IRQHandler, . - FLASH_IRQHandler

    .align 1
    .thumb_func
    .weak WKT_IRQHandler
    .type WKT_IRQHandler, %function
WKT_IRQHandler:
    ldr   r0,=WKT_DriverIRQHandler
    bx    r0
    .size WKT_IRQHandler, . - WKT_IRQHandler

    .align 1
    .thumb_func
    .weak ADC0_SEQA_IRQHandler
    .type ADC0_SEQA_IRQHandler, %function
ADC0_SEQA_IRQHandler:
    ldr   r0,=ADC0_SEQA_DriverIRQHandler
    bx    r0
    .size ADC0_SEQA_IRQHandler, . - ADC0_SEQA_IRQHandler

    .align 1
    .thumb_func
    .weak ADC0_SEQB_IRQHandler
    .type ADC0_SEQB_IRQHandler, %function
ADC0_SEQB_IRQHandler:
    ldr   r0,=ADC0_SEQB_DriverIRQHandler
    bx    r0
    .size ADC0_SEQB_IRQHandler, . - ADC0_SEQB_IRQHandler

    .align 1
    .thumb_func
    .weak ADC0_THCMP_IRQHandler
    .type ADC0_THCMP_IRQHandler, %function
ADC0_THCMP_IRQHandler:
    ldr   r0,=ADC0_THCMP_DriverIRQHandler
    bx    r0
    .size ADC0_THCMP_IRQHandler, . - ADC0_THCMP_IRQHandler

    .align 1
    .thumb_func
    .weak ADC0_OVR_IRQHandler
    .type ADC0_OVR_IRQHandler, %function
ADC0_OVR_IRQHandler:
    ldr   r0,=ADC0_OVR_DriverIRQHandler
    bx    r0
    .size ADC0_OVR_IRQHandler, . - ADC0_OVR_IRQHandler

    .align 1
    .thumb_func
    .weak DMA0_IRQHandler
    .type DMA0_IRQHandler, %function
DMA0_IRQHandler:
    ldr   r0,=DMA0_DriverIRQHandler
    bx    r0
    .size DMA0_IRQHandler, . - DMA0_IRQHandler

    .align 1
    .thumb_func
    .weak I2C2_IRQHandler
    .type I2C2_IRQHandler, %function
I2C2_IRQHandler:
    ldr   r0,=I2C2_DriverIRQHandler
    bx    r0
    .size I2C2_IRQHandler, . - I2C2_IRQHandler

    .align 1
    .thumb_func
    .weak I2C3_IRQHandler
    .type I2C3_IRQHandler, %function
I2C3_IRQHandler:
    ldr   r0,=I2C3_DriverIRQHandler
    bx    r0
    .size I2C3_IRQHandler, . - I2C3_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved39_IRQHandler
    .type Reserved39_IRQHandler, %function
Reserved39_IRQHandler:
    ldr   r0,=Reserved39_DriverIRQHandler
    bx    r0
    .size Reserved39_IRQHandler, . - Reserved39_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT0_IRQHandler
    .type PIN_INT0_IRQHandler, %function
PIN_INT0_IRQHandler:
    ldr   r0,=PIN_INT0_DriverIRQHandler
    bx    r0
    .size PIN_INT0_IRQHandler, . - PIN_INT0_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT1_IRQHandler
    .type PIN_INT1_IRQHandler, %function
PIN_INT1_IRQHandler:
    ldr   r0,=PIN_INT1_DriverIRQHandler
    bx    r0
    .size PIN_INT1_IRQHandler, . - PIN_INT1_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT2_IRQHandler
    .type PIN_INT2_IRQHandler, %function
PIN_INT2_IRQHandler:
    ldr   r0,=PIN_INT2_DriverIRQHandler
    bx    r0
    .size PIN_INT2_IRQHandler, . - PIN_INT2_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT3_IRQHandler
    .type PIN_INT3_IRQHandler, %function
PIN_INT3_IRQHandler:
    ldr   r0,=PIN_INT3_DriverIRQHandler
    bx    r0
    .size PIN_INT3_IRQHandler, . - PIN_INT3_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT4_IRQHandler
    .type PIN_INT4_IRQHandler, %function
PIN_INT4_IRQHandler:
    ldr   r0,=PIN_INT4_DriverIRQHandler
    bx    r0
    .size PIN_INT4_IRQHandler, . - PIN_INT4_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT5_IRQHandler
    .type PIN_INT5_IRQHandler, %function
PIN_INT5_IRQHandler:
    ldr   r0,=PIN_INT5_DriverIRQHandler
    bx    r0
    .size PIN_INT5_IRQHandler, . - PIN_INT5_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT6_IRQHandler
    .type PIN_INT6_IRQHandler, %function
PIN_INT6_IRQHandler:
    ldr   r0,=PIN_INT6_DriverIRQHandler
    bx    r0
    .size PIN_INT6_IRQHandler, . - PIN_INT6_IRQHandler

    .align 1
    .thumb_func
    .weak PIN_INT7_IRQHandler
    .type PIN_INT7_IRQHandler, %function
PIN_INT7_IRQHandler:
    ldr   r0,=PIN_INT7_DriverIRQHandler
    bx    r0
    .size PIN_INT7_IRQHandler, . - PIN_INT7_IRQHandler


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler  handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm
    def_irq_handler    SPI0_DriverIRQHandler
    def_irq_handler    SPI1_DriverIRQHandler
    def_irq_handler    Reserved18_DriverIRQHandler
    def_irq_handler    USART0_DriverIRQHandler
    def_irq_handler    USART1_DriverIRQHandler
    def_irq_handler    USART2_DriverIRQHandler
    def_irq_handler    Reserved22_DriverIRQHandler
    def_irq_handler    I2C1_DriverIRQHandler
    def_irq_handler    I2C0_DriverIRQHandler
    def_irq_handler    SCT0_DriverIRQHandler
    def_irq_handler    MRT0_DriverIRQHandler
    def_irq_handler    CMP_DriverIRQHandler
    def_irq_handler    WDT_DriverIRQHandler
    def_irq_handler    BOD_DriverIRQHandler
    def_irq_handler    FLASH_DriverIRQHandler
    def_irq_handler    WKT_DriverIRQHandler
    def_irq_handler    ADC0_SEQA_DriverIRQHandler
    def_irq_handler    ADC0_SEQB_DriverIRQHandler
    def_irq_handler    ADC0_THCMP_DriverIRQHandler
    def_irq_handler    ADC0_OVR_DriverIRQHandler
    def_irq_handler    DMA0_DriverIRQHandler
    def_irq_handler    I2C2_DriverIRQHandler
    def_irq_handler    I2C3_DriverIRQHandler
    def_irq_handler    Reserved39_DriverIRQHandler
    def_irq_handler    PIN_INT0_DriverIRQHandler
    def_irq_handler    PIN_INT1_DriverIRQHandler
    def_irq_handler    PIN_INT2_DriverIRQHandler
    def_irq_handler    PIN_INT3_DriverIRQHandler
    def_irq_handler    PIN_INT4_DriverIRQHandler
    def_irq_handler    PIN_INT5_DriverIRQHandler
    def_irq_handler    PIN_INT6_DriverIRQHandler
    def_irq_handler    PIN_INT7_DriverIRQHandler

    .end
