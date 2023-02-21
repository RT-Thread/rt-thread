/* ------------------------------------------------------------------------- */
/*  @file:    startup_MM32F3270.s                                            */
/*  @purpose: CMSIS Cortex-M3 Core Device Startup File                       */
/*                                                                           */
/*  @version: 1.0                                                            */
/*  @date:    2021-7-21                                                      */
/*  @build:   b210721                                                        */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 2021 MindMotion                                                 */
/* All rights reserved.                                                      */
/*                                                                           */
/* SPDX-License-Identifier: BSD-3-Clause                                     */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv7-m

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                                      /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler*/
    .long   HardFault_Handler                               /* Hard Fault Handler*/
    .long   MemManage_Handler                               /* MPU Fault Handler*/
    .long   BusFault_Handler                                /* Bus Fault Handler*/
    .long   UsageFault_Handler                              /* Usage Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   DebugMon_Handler                                /* Debug Monitor Handler*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

    .long   WWDG_IRQHandler                                 /* 0       Window Watchdog */
    .long   PVD_IRQHandler                                  /* 1       PVD through EXTI Line detect */
    .long   TAMPER_IRQHandler                               /* 2       Tamper */
    .long   RTC_IRQHandler                                  /* 3       RTC */
    .long   FLASH_IRQHandler                                /* 4       Flash */
    .long   RCC_CRS_IRQHandler                              /* 5       RCC */
    .long   EXTI0_IRQHandler                                /* 6       EXTI Line 0 */
    .long   EXTI1_IRQHandler                                /* 7       EXTI Line 1 */
    .long   EXTI2_IRQHandler                                /* 8       EXTI Line 2 */
    .long   EXTI3_IRQHandler                                /* 9       EXTI Line 3 */
    .long   EXTI4_IRQHandler                                /* 10      EXTI Line 4 */
    .long   DMA1_Channel1_IRQHandler                        /* 11      DMA1 Channel 1 */
    .long   DMA1_Channel2_IRQHandler                        /* 12      DMA1 Channel 2 */
    .long   DMA1_Channel3_IRQHandler                        /* 13      DMA1 Channel 3 */
    .long   DMA1_Channel4_IRQHandler                        /* 14      DMA1 Channel 4 */
    .long   DMA1_Channel5_IRQHandler                        /* 15      DMA1 Channel 5 */
    .long   DMA1_Channel6_IRQHandler                        /* 16      DMA1 Channel 6 */
    .long   DMA1_Channel7_IRQHandler                        /* 17      DMA1 Channel 7 */
    .long   ADC1_2_IRQHandler                               /* 18      ADC1 and ADC2 */
    .long   FlashCache_IRQHandler                           /* 19      FlashCache outage */
    .long   0                                               /* 20      Reserved */
    .long   CAN1_RX_IRQHandler                              /* 21      CAN1_RX */
    .long   0                                               /* 22      Reserved */
    .long   EXTI9_5_IRQHandler                              /* 23      EXTI Line 9..5 */
    .long   TIM1_BRK_IRQHandler                             /* 24      TIM1 Break */
    .long   TIM1_UP_IRQHandler                              /* 25      TIM1 Update */
    .long   TIM1_TRG_COM_IRQHandler                         /* 26      TIM1 Trigger and Commutation */
    .long   TIM1_CC_IRQHandler                              /* 27      TIM1 Capture Compare */
    .long   TIM2_IRQHandler                                 /* 28      TIM2 */
    .long   TIM3_IRQHandler                                 /* 29      TIM3 */
    .long   TIM4_IRQHandler                                 /* 30      TIM4 */
    .long   I2C1_IRQHandler                                 /* 31      I2C1 Event */
    .long   0                                               /* 32      Reserved */
    .long   I2C2_IRQHandler                                 /* 33      I2C2 Event */
    .long   0                                               /* 34      Reserved */
    .long   SPI1_IRQHandler                                 /* 35      SPI1 */
    .long   SPI2_IRQHandler                                 /* 36      SPI2 */
    .long   UART1_IRQHandler                                /* 37      UART1 */
    .long   UART2_IRQHandler                                /* 38      UART2 */
    .long   UART3_IRQHandler                                /* 39      UART3 */
    .long   EXTI15_10_IRQHandler                            /* 40      EXTI Line 15..10 */
    .long   RTCAlarm_IRQHandler                             /* 41      RTC Alarm through EXTI Line 17 */
    .long   OTG_FS_WKUP_IRQHandler                          /* 42      USB OTG FS Wakeup through EXTI line */
    .long   TIM8_BRK_IRQHandler                             /* 43      TIM8 Break */
    .long   TIM8_UP_IRQHandler                              /* 44      TIM8 Update */
    .long   TIM8_TRG_COM_IRQHandler                         /* 45      TIM8 Trigger and Commutation */
    .long   TIM8_CC_IRQHandler                              /* 46      TIM8 Capture Compare */
    .long   ADC3_IRQHandler                                 /* 47      ADC3 */
    .long   0                                               /* 48      Reserved */
    .long   SDIO_IRQHandler                                 /* 49      SDIO */
    .long   TIM5_IRQHandler                                 /* 50      TIM5 */
    .long   SPI3_IRQHandler                                 /* 51      SPI3 */
    .long   UART4_IRQHandler                                /* 52      UART4 */
    .long   UART5_IRQHandler                                /* 53      UART5 */
    .long   TIM6_IRQHandler                                 /* 54      TIM6 */
    .long   TIM7_IRQHandler                                 /* 55      TIM7 */
    .long   DMA2_Channel1_IRQHandler                        /* 56      DMA2 Channel 1 */
    .long   DMA2_Channel2_IRQHandler                        /* 57      DMA2 Channel 2 */
    .long   DMA2_Channel3_IRQHandler                        /* 58      DMA2 Channel 3 */
    .long   DMA2_Channel4_IRQHandler                        /* 59      DMA2 Channel 4 */
    .long   DMA2_Channel5_IRQHandler                        /* 60      DMA2 Channel 5 */
    .long   ETH_IRQHandler                                  /* 61      Ethernet */
    .long   0                                               /* 62      Reserved */
    .long   0                                               /* 63      Reserved */
    .long   COMP1_2_IRQHandler                              /* 64      COMP1,COMP2 */
    .long   0                                               /* 65      Reserved */
    .long   0                                               /* 66      Reserved */
    .long   OTG_FS_IRQHandler                               /* 67      USB OTG_FullSpeed */
    .long   0                                               /* 68      Reserved */
    .long   0                                               /* 69      Reserved */
    .long   0                                               /* 70      Reserved */
    .long   UART6_IRQHandler                                /* 71      UART6   */
    .long   0                                               /* 72      Reserved */
    .long   0                                               /* 73      Reserved */
    .long   0                                               /* 74      Reserved */
    .long   0                                               /* 75      Reserved */
    .long   0                                               /* 76      Reserved */
    .long   0                                               /* 77      Reserved */
    .long   0                                               /* 78      Reserved */
    .long   0                                               /* 79      Reserved */
    .long   0                                               /* 80      Reserved */
    .long   0                                               /* 81      Reserved */
    .long   UART7_IRQHandler                                /* 82      UART7 */
    .long   UART8_IRQHandler                                /* 83      UART8 */

    .long   DefaultISR                                                /* 254*/

    .size    __isr_vector, . - __isr_vector



    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */
    .equ    VTOR, 0xE000ED08
    ldr     r0, =VTOR
    ldr     r1, =__isr_vector
    str     r1, [r0]
    ldr     r2, [r1]
    msr     msp, r2
#ifndef __NO_SYSTEM_INIT
    ldr   r0,=SystemInit
    blx   r0
#endif
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      __noncachedata_start__/__noncachedata_end__ : none cachable region
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

#ifdef __PERFORMANCE_IMPLEMENTATION
/* Here are two copies of loop implementations. First one favors performance
 * and the second one favors code size. Default uses the second one.
 * Define macro "__PERFORMANCE_IMPLEMENTATION" in project to use the first one */
    subs    r3, r2
    ble    .LC1
.LC0:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC0
.LC1:
#else  /* code size implemenation */
.LC0:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC0
#endif
#ifdef __STARTUP_INITIALIZE_NONCACHEDATA
    ldr    r2, =__noncachedata_start__
    ldr    r3, =__noncachedata_init_end__
#ifdef __PERFORMANCE_IMPLEMENTATION
/* Here are two copies of loop implementations. First one favors performance
 * and the second one favors code size. Default uses the second one.
 * Define macro "__PERFORMANCE_IMPLEMENTATION" in project to use the first one */
    subs    r3, r2
    ble    .LC3
.LC2:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC2
.LC3:
#else  /* code size implemenation */
.LC2:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC2
#endif
/* zero inited ncache section initialization */
    ldr r3, =__noncachedata_end__
    movs    r0,0
.LC4:
    cmp    r2,r3
    itt    lt
    strlt   r0,[r2],#4
    blt    .LC4
#endif /* __STARTUP_INITIALIZE_NONCACHEDATA */

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

    movs    r0, 0
.LC5:
    cmp     r1, r2
    itt    lt
    strlt   r0, [r1], #4
    blt    .LC5
#endif /* __STARTUP_CLEAR_BSS */

    cpsie   i               /* Unmask interrupts */
#ifndef __START
#define __START _start
#endif
#ifndef __ATOLLIC__
    ldr   r0,=__START
    blx   r0
#else
    ldr   r0,=__libc_init_array
    blx   r0
    ldr   r0,=main
    bx    r0
#endif
    .pool
    .size Reset_Handler, . - Reset_Handler

# DefaultISR
    .align  1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    b DefaultISR
    .size DefaultISR, . - DefaultISR

# NMI_Handler
    .align 1
    .thumb_func
    .weak NMI_Handler
    .type NMI_Handler, %function
NMI_Handler:
    ldr   r0,=NMI_Handler
    bx    r0
    .size NMI_Handler, . - NMI_Handler

# HardFault_Handler
    .align 1
    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
HardFault_Handler:
    ldr   r0,=HardFault_Handler
    bx    r0
    .size HardFault_Handler, . - HardFault_Handler

# MemManage_Handler
# BusFault_Handler
# UsageFault_Handler
# DebugMon_Handler

# SVC_Handler
    .align 1
    .thumb_func
    .weak SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
    ldr   r0,=SVC_Handler
    bx    r0
    .size SVC_Handler, . - SVC_Handler

# PendSV_Handler
    .align 1
    .thumb_func
    .weak PendSV_Handler
    .type PendSV_Handler, %function
PendSV_Handler:
    ldr   r0,=PendSV_Handler
    bx    r0
    .size PendSV_Handler, . - PendSV_Handler

# SysTick_Handler
    .align 1
    .thumb_func
    .weak SysTick_Handler
    .type SysTick_Handler, %function
SysTick_Handler:
    ldr   r0,=SysTick_Handler
    bx    r0
    .size SysTick_Handler, . - SysTick_Handler


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler  handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler    MemManage_Handler
    def_irq_handler    BusFault_Handler
    def_irq_handler    UsageFault_Handler
    def_irq_handler    DebugMon_Handler


    def_irq_handler    WWDG_IRQHandler                                 /* 0       Window Watchdog */
    def_irq_handler    PVD_IRQHandler                                  /* 1       PVD through EXTI Line detect */
    def_irq_handler    TAMPER_IRQHandler                               /* 2       Tamper */
    def_irq_handler    RTC_IRQHandler                                  /* 3       RTC */
    def_irq_handler    FLASH_IRQHandler                                /* 4       Flash */
    def_irq_handler    RCC_CRS_IRQHandler                              /* 5       RCC */
    def_irq_handler    EXTI0_IRQHandler                                /* 6       EXTI Line 0 */
    def_irq_handler    EXTI1_IRQHandler                                /* 7       EXTI Line 1 */
    def_irq_handler    EXTI2_IRQHandler                                /* 8       EXTI Line 2 */
    def_irq_handler    EXTI3_IRQHandler                                /* 9       EXTI Line 3 */
    def_irq_handler    EXTI4_IRQHandler                                /* 10      EXTI Line 4 */
    def_irq_handler    DMA1_Channel1_IRQHandler                        /* 11      DMA1 Channel 1 */
    def_irq_handler    DMA1_Channel2_IRQHandler                        /* 12      DMA1 Channel 2 */
    def_irq_handler    DMA1_Channel3_IRQHandler                        /* 13      DMA1 Channel 3 */
    def_irq_handler    DMA1_Channel4_IRQHandler                        /* 14      DMA1 Channel 4 */
    def_irq_handler    DMA1_Channel5_IRQHandler                        /* 15      DMA1 Channel 5 */
    def_irq_handler    DMA1_Channel6_IRQHandler                        /* 16      DMA1 Channel 6 */
    def_irq_handler    DMA1_Channel7_IRQHandler                        /* 17      DMA1 Channel 7 */
    def_irq_handler    ADC1_2_IRQHandler                               /* 18      ADC1 and ADC2 */
    def_irq_handler    FlashCache_IRQHandler                           /* 19      FlashCache outage */
    def_irq_handler    CAN1_RX_IRQHandler                              /* 21      CAN1_RX */
    def_irq_handler    EXTI9_5_IRQHandler                              /* 23      EXTI Line 9..5 */
    def_irq_handler    TIM1_BRK_IRQHandler                             /* 24      TIM1 Break */
    def_irq_handler    TIM1_UP_IRQHandler                              /* 25      TIM1 Update */
    def_irq_handler    TIM1_TRG_COM_IRQHandler                         /* 26      TIM1 Trigger and Commutation */
    def_irq_handler    TIM1_CC_IRQHandler                              /* 27      TIM1 Capture Compare */
    def_irq_handler    TIM2_IRQHandler                                 /* 28      TIM2 */
    def_irq_handler    TIM3_IRQHandler                                 /* 29      TIM3 */
    def_irq_handler    TIM4_IRQHandler                                 /* 30      TIM4 */
    def_irq_handler    I2C1_IRQHandler                                 /* 31      I2C1 Event */
    def_irq_handler    I2C2_IRQHandler                                 /* 33      I2C2 Event */
    def_irq_handler    SPI1_IRQHandler                                 /* 35      SPI1 */
    def_irq_handler    SPI2_IRQHandler                                 /* 36      SPI2 */
    def_irq_handler    UART1_IRQHandler                                /* 37      UART1 */
    def_irq_handler    UART2_IRQHandler                                /* 38      UART2 */
    def_irq_handler    UART3_IRQHandler                                /* 39      UART3 */
    def_irq_handler    EXTI15_10_IRQHandler                            /* 40      EXTI Line 15..10 */
    def_irq_handler    RTCAlarm_IRQHandler                             /* 41      RTC Alarm through EXTI Line 17 */
    def_irq_handler    OTG_FS_WKUP_IRQHandler                          /* 42      USB OTG FS Wakeup through EXTI line */
    def_irq_handler    TIM8_BRK_IRQHandler                             /* 43      TIM8 Break */
    def_irq_handler    TIM8_UP_IRQHandler                              /* 44      TIM8 Update */
    def_irq_handler    TIM8_TRG_COM_IRQHandler                         /* 45      TIM8 Trigger and Commutation */
    def_irq_handler    TIM8_CC_IRQHandler                              /* 46      TIM8 Capture Compare */
    def_irq_handler    ADC3_IRQHandler                                 /* 47      ADC3 */
    def_irq_handler    SDIO_IRQHandler                                 /* 49      SDIO */
    def_irq_handler    TIM5_IRQHandler                                 /* 50      TIM5 */
    def_irq_handler    SPI3_IRQHandler                                 /* 51      SPI3 */
    def_irq_handler    UART4_IRQHandler                                /* 52      UART4 */
    def_irq_handler    UART5_IRQHandler                                /* 53      UART5 */
    def_irq_handler    TIM6_IRQHandler                                 /* 54      TIM6 */
    def_irq_handler    TIM7_IRQHandler                                 /* 55      TIM7 */
    def_irq_handler    DMA2_Channel1_IRQHandler                        /* 56      DMA2 Channel 1 */
    def_irq_handler    DMA2_Channel2_IRQHandler                        /* 57      DMA2 Channel 2 */
    def_irq_handler    DMA2_Channel3_IRQHandler                        /* 58      DMA2 Channel 3 */
    def_irq_handler    DMA2_Channel4_IRQHandler                        /* 59      DMA2 Channel 4 */
    def_irq_handler    DMA2_Channel5_IRQHandler                        /* 60      DMA2 Channel 5 */
    def_irq_handler    ETH_IRQHandler                                  /* 61      Ethernet */
    def_irq_handler    COMP1_2_IRQHandler                              /* 64      COMP1,COMP2 */
    def_irq_handler    OTG_FS_IRQHandler                               /* 67      USB OTG_FullSpeed */
    def_irq_handler    UART6_IRQHandler                                /* 71      UART6   */
    def_irq_handler    UART7_IRQHandler                                /* 82      UART7 */
    def_irq_handler    UART8_IRQHandler                                /* 83      UART8 */


    .end
