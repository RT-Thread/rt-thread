/* --------------------------------------------------------------------------*/
/* @file:    startup_LPC55S36.s                                                */
/* @purpose: CMSIS Cortex-M33 Core Device Startup File                       */
/*           LPC55S36                                                          */
/* @version: 1.1                                                      */
/* @date:    2021-8-4                                                         */
/* --------------------------------------------------------------------------*/
/*                                                                           */
/* Copyright 1997-2016 Freescale Semiconductor, Inc.                         */
/* Copyright 2016-2021 NXP                                                   */
/* All rights reserved.                                                      */
/*                                                                           */
/* SPDX-License-Identifier: BSD-3-Clause                                     */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/


    .syntax unified
    .arch armv8-m.main

    .section .isr_vector, "a"
    .align 2
    .globl __Vectors
__Vectors:
    .long   __StackTop                                      /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler*/
    .long   HardFault_Handler                               /* Hard Fault Handler*/
    .long   MemManage_Handler                               /* MPU Fault Handler*/
    .long   BusFault_Handler                                /* Bus Fault Handler*/
    .long   UsageFault_Handler                              /* Usage Fault Handler*/
    .long   SecureFault_Handler                             /* Secure Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   DebugMon_Handler                                /* Debug Monitor Handler*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

    /* External Interrupts */
    .long   WDT_BOD_IRQHandler  /* Windowed watchdog timer, Brownout detect, Flash interrupt */
    .long   DMA0_IRQHandler  /* DMA0 controller */
    .long   GINT0_IRQHandler  /* GPIO group 0 */
    .long   GINT1_IRQHandler  /* GPIO group 1 */
    .long   PIN_INT0_IRQHandler  /* Pin interrupt 0 or pattern match engine slice 0 */
    .long   PIN_INT1_IRQHandler  /* Pin interrupt 1or pattern match engine slice 1 */
    .long   PIN_INT2_IRQHandler  /* Pin interrupt 2 or pattern match engine slice 2 */
    .long   PIN_INT3_IRQHandler  /* Pin interrupt 3 or pattern match engine slice 3 */
    .long   UTICK0_IRQHandler  /* Micro-tick Timer */
    .long   MRT0_IRQHandler  /* Multi-rate timer */
    .long   CTIMER0_IRQHandler  /* Standard counter/timer CTIMER0 */
    .long   CTIMER1_IRQHandler  /* Standard counter/timer CTIMER1 */
    .long   SCT0_IRQHandler  /* SCTimer/PWM */
    .long   CTIMER3_IRQHandler  /* Standard counter/timer CTIMER3 */
    .long   FLEXCOMM0_IRQHandler  /* Flexcomm Interface 0 (USART, SPI, I2C, I2S, FLEXCOMM) */
    .long   FLEXCOMM1_IRQHandler  /* Flexcomm Interface 1 (USART, SPI, I2C, I2S, FLEXCOMM) */
    .long   FLEXCOMM2_IRQHandler  /* Flexcomm Interface 2 (USART, SPI, I2C, I2S, FLEXCOMM) */
    .long   FLEXCOMM3_IRQHandler  /* Flexcomm Interface 3 (USART, SPI, I2C, I2S, FLEXCOMM) */
    .long   FLEXCOMM4_IRQHandler  /* Flexcomm Interface 4 (USART, SPI, I2C, I2S, FLEXCOMM) */
    .long   FLEXCOMM5_IRQHandler  /* Flexcomm Interface 5 (USART, SPI, I2C, I2S, FLEXCOMM) */
    .long   FLEXCOMM6_IRQHandler  /* Flexcomm Interface 6 (USART, SPI, I2C, I2S, FLEXCOMM) */
    .long   FLEXCOMM7_IRQHandler  /* Flexcomm Interface 7 (USART, SPI, I2C, I2S, FLEXCOMM) */
    .long   ADC0_IRQHandler  /* ADC0  */
    .long   ADC1_IRQHandler  /* ADC1 */
    .long   ACMP_IRQHandler  /* ACMP interrupts */
    .long   DMIC_IRQHandler  /* Digital microphone and DMIC subsystem */
    .long   HWVAD0_IRQHandler  /* Hardware Voice Activity Detector */
    .long   USB0_NEEDCLK_IRQHandler  /* USB Activity Wake-up Interrupt */
    .long   USB0_IRQHandler  /* USB device */
    .long   RTC_IRQHandler  /* RTC alarm and wake-up interrupts */
    .long   EZH_ARCH_B0_IRQHandler  /* EZH interrupt */
    .long   WAKEUP_IRQHandler  /* Wakeup interrupt */
    .long   PIN_INT4_IRQHandler  /* Pin interrupt 4 or pattern match engine slice 4 int */
    .long   PIN_INT5_IRQHandler  /* Pin interrupt 5 or pattern match engine slice 5 int */
    .long   PIN_INT6_IRQHandler  /* Pin interrupt 6 or pattern match engine slice 6 int */
    .long   PIN_INT7_IRQHandler  /* Pin interrupt 7 or pattern match engine slice 7 int */
    .long   CTIMER2_IRQHandler  /* Standard counter/timer CTIMER2 */
    .long   CTIMER4_IRQHandler  /* Standard counter/timer CTIMER4 */
    .long   OS_EVENT_IRQHandler  /* OS_EVENT_TIMER and OS_EVENT_WAKEUP interrupts */
    .long   FlexSPI0_IRQHandler  /* FlexSPI interrupt */
    .long   Reserved56_IRQHandler  /* Reserved interrupt */
    .long   Reserved57_IRQHandler  /* Reserved interrupt */
    .long   Reserved58_IRQHandler  /* Reserved interrupt */
    .long   CAN0_IRQ0_IRQHandler  /* CAN0 interrupt0 */
    .long   CAN0_IRQ1_IRQHandler  /* CAN0 interrupt1 */
    .long   SPI_FILTER_IRQHandler  /* SPI Filter interrupt */
    .long   Reserved62_IRQHandler  /* Reserved interrupt */
    .long   Reserved63_IRQHandler  /* Reserved interrupt */
    .long   Reserved64_IRQHandler  /* Reserved interrupt */
    .long   SEC_HYPERVISOR_CALL_IRQHandler  /* SEC_HYPERVISOR_CALL interrupt */
    .long   SEC_GPIO_INT0_IRQ0_IRQHandler  /* SEC_GPIO_INT00 interrupt */
    .long   SEC_GPIO_INT0_IRQ1_IRQHandler  /* SEC_GPIO_INT01 interrupt */
    .long   Freqme_IRQHandler  /* frequency measure interrupt */
    .long   SEC_VIO_IRQHandler  /* SEC_VIO interrupt */
    .long   SHA_IRQHandler  /* SHA interrupt */
    .long   PKC_IRQHandler  /* CASPER interrupt */
    .long   PUF_IRQHandler  /* PUF interrupt */
    .long   POWERQUAD_IRQHandler  /* PowerQuad interrupt */
    .long   DMA1_IRQHandler  /* DMA1 interrupt */
    .long   FLEXCOMM8_IRQHandler  /* LSPI_HS interrupt */
    .long   CDOG_IRQHandler  /* CodeWDG interrupt */
    .long   Reserved77_IRQHandler  /* Reserved interrupt */
    .long   I3C0_IRQHandler  /* I3C interrupt */
    .long   Reserved79_IRQHandler  /* Reserved interrupt */
    .long   Reserved80_IRQHandler  /* Reserved interrupt */
    .long   CSS_IRQ1_IRQHandler  /* CSS_IRQ1 */
    .long   Tamper_IRQHandler  /* Tamper */
    .long   Analog_Glitch_IRQHandler  /* Analog_Glitch */
    .long   Reserved84_IRQHandler  /* Reserved interrupt */
    .long   Reserved85_IRQHandler  /* Reserved interrupt */
    .long   Reserved86_IRQHandler  /* Reserved interrupt */
    .long   Reserved87_IRQHandler  /* Reserved interrupt */
    .long   Reserved88_IRQHandler  /* Reserved interrupt */
    .long   Reserved89_IRQHandler  /* Reserved interrupt */
    .long   DAC0_IRQHandler  /* dac0 interrupt */
    .long   DAC1_IRQHandler  /* dac1 interrupt */
    .long   DAC2_IRQHandler  /* dac2 interrupt */
    .long   HSCMP0_IRQHandler  /* hscmp0 interrupt */
    .long   HSCMP1_IRQHandler  /* hscmp1 interrupt */
    .long   HSCMP2_IRQHandler  /* hscmp2 interrupt */
    .long   FLEXPWM0_CAPTURE_IRQHandler  /* flexpwm0_capture interrupt */
    .long   FLEXPWM0_FAULT_IRQHandler  /* flexpwm0_fault interrupt */
    .long   FLEXPWM0_RELOAD_ERROR_IRQHandler  /* flexpwm0_reload_error interrupt */
    .long   FLEXPWM0_COMPARE0_IRQHandler  /* flexpwm0_compare0 interrupt */
    .long   FLEXPWM0_RELOAD0_IRQHandler  /* flexpwm0_reload0 interrupt */
    .long   FLEXPWM0_COMPARE1_IRQHandler  /* flexpwm0_compare1 interrupt */
    .long   FLEXPWM0_RELOAD1_IRQHandler  /* flexpwm0_reload1 interrupt */
    .long   FLEXPWM0_COMPARE2_IRQHandler  /* flexpwm0_compare2 interrupt */
    .long   FLEXPWM0_RELOAD2_IRQHandler  /* flexpwm0_reload2 interrupt */
    .long   FLEXPWM0_COMPARE3_IRQHandler  /* flexpwm0_compare3 interrupt */
    .long   FLEXPWM0_RELOAD3_IRQHandler  /* flexpwm0_reload3 interrupt */
    .long   FLEXPWM1_CAPTURE_IRQHandler  /* flexpwm1_capture interrupt */
    .long   FLEXPWM1_FAULT_IRQHandler  /* flexpwm1_fault interrupt */
    .long   FLEXPWM1_RELOAD_ERROR_IRQHandler  /* flexpwm1_reload_error interrupt */
    .long   FLEXPWM1_COMPARE0_IRQHandler  /* flexpwm1_compare0 interrupt */
    .long   FLEXPWM1_RELOAD0_IRQHandler  /* flexpwm1_reload0 interrupt */
    .long   FLEXPWM1_COMPARE1_IRQHandler  /* flexpwm1_compare1 interrupt */
    .long   FLEXPWM1_RELOAD1_IRQHandler  /* flexpwm1_reload1 interrupt */
    .long   FLEXPWM1_COMPARE2_IRQHandler  /* flexpwm1_compare2 interrupt */
    .long   FLEXPWM1_RELOAD2_IRQHandler  /* flexpwm1_reload2 interrupt */
    .long   FLEXPWM1_COMPARE3_IRQHandler  /* flexpwm1_compare3 interrupt */
    .long   FLEXPWM1_RELOAD3_IRQHandler  /* flexpwm1_reload3 interrupt */
    .long   ENC0_COMPARE_IRQHandler  /* enc0_compare interrupt */
    .long   ENC0_HOME_IRQHandler  /* enc0_home interrupt */
    .long   ENC0_WDG_IRQHandler  /* enc0_wdg interrupt */
    .long   ENC0_IDX_IRQHandler  /* enc0_idx interrupt */
    .long   ENC1_COMPARE_IRQHandler  /* enc1_compare interrupt */
    .long   ENC1_HOME_IRQHandler  /* enc1_home interrupt */
    .long   ENC1_WDG_IRQHandler  /* enc1_wdg interrupt */
    .long   ENC1_IDX_IRQHandler  /* enc1_idx interrupt */
    .long   ITRC0_IRQHandler  /* itrc0 interrupt */
    .long   Reserved127_IRQHandler  /* Reserved interrupt */
    .long   CSSV2_ERR_IRQHandler  /* cssv2_err interrupt */
    .long   PKC_ERR_IRQHandler  /* pkc_err interrupt */
    .long   Reserved130_IRQHandler  /* Reserved interrupt */
    .long   Reserved131_IRQHandler  /* Reserved interrupt */
    .long   Reserved132_IRQHandler  /* Reserved interrupt */
    .long   Reserved133_IRQHandler  /* Reserved interrupt */
    .long   FLASH_IRQHandler  /* flash interrupt */
    .long   RAM_PARITY_ECC_ERR_IRQHandler  /* ram_parity_ecc_err interrupt */

    .size   __Vectors, . - __Vectors

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
    ldr     r1, =__Vectors
    str     r1, [r0]
    ldr     r2, [r1]
    msr     msp, r2
    ldr     r0, =__StackLimit
    msr     msplim, r0
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

#if 1
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
.LC2:
    cmp     r1, r2
    itt    lt
    strlt   r0, [r1], #4
    blt    .LC2
#endif /* __STARTUP_CLEAR_BSS */

/* Add stack / heap initializaiton */
    movs    r0, 0
    ldr     r1, =__HeapBase
    ldr     r2, =__HeapLimit
.LC3:
    cmp     r1, r2
    itt     lt
    strlt   r0, [r1], #4
    blt     .LC3

    ldr     r1, =__StackLimit
    ldr     r2, =__StackTop
.LC4:
    cmp     r1, r2
    itt     lt
    strlt   r0, [r1], #4
    blt     .LC4
/*End of stack / heap initializaiton */
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

    .align  1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    b DefaultISR
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
    .weak WDT_BOD_IRQHandler
    .type WDT_BOD_IRQHandler, %function
WDT_BOD_IRQHandler:
    ldr   r0,=WDT_BOD_DriverIRQHandler
    bx    r0
    .size WDT_BOD_IRQHandler, . - WDT_BOD_IRQHandler

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
    .weak GINT0_IRQHandler
    .type GINT0_IRQHandler, %function
GINT0_IRQHandler:
    ldr   r0,=GINT0_DriverIRQHandler
    bx    r0
    .size GINT0_IRQHandler, . - GINT0_IRQHandler

    .align 1
    .thumb_func
    .weak GINT1_IRQHandler
    .type GINT1_IRQHandler, %function
GINT1_IRQHandler:
    ldr   r0,=GINT1_DriverIRQHandler
    bx    r0
    .size GINT1_IRQHandler, . - GINT1_IRQHandler

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
    .weak UTICK0_IRQHandler
    .type UTICK0_IRQHandler, %function
UTICK0_IRQHandler:
    ldr   r0,=UTICK0_DriverIRQHandler
    bx    r0
    .size UTICK0_IRQHandler, . - UTICK0_IRQHandler

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
    .weak CTIMER0_IRQHandler
    .type CTIMER0_IRQHandler, %function
CTIMER0_IRQHandler:
    ldr   r0,=CTIMER0_DriverIRQHandler
    bx    r0
    .size CTIMER0_IRQHandler, . - CTIMER0_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER1_IRQHandler
    .type CTIMER1_IRQHandler, %function
CTIMER1_IRQHandler:
    ldr   r0,=CTIMER1_DriverIRQHandler
    bx    r0
    .size CTIMER1_IRQHandler, . - CTIMER1_IRQHandler

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
    .weak CTIMER3_IRQHandler
    .type CTIMER3_IRQHandler, %function
CTIMER3_IRQHandler:
    ldr   r0,=CTIMER3_DriverIRQHandler
    bx    r0
    .size CTIMER3_IRQHandler, . - CTIMER3_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM0_IRQHandler
    .type FLEXCOMM0_IRQHandler, %function
FLEXCOMM0_IRQHandler:
    ldr   r0,=FLEXCOMM0_DriverIRQHandler
    bx    r0
    .size FLEXCOMM0_IRQHandler, . - FLEXCOMM0_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM1_IRQHandler
    .type FLEXCOMM1_IRQHandler, %function
FLEXCOMM1_IRQHandler:
    ldr   r0,=FLEXCOMM1_DriverIRQHandler
    bx    r0
    .size FLEXCOMM1_IRQHandler, . - FLEXCOMM1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM2_IRQHandler
    .type FLEXCOMM2_IRQHandler, %function
FLEXCOMM2_IRQHandler:
    ldr   r0,=FLEXCOMM2_DriverIRQHandler
    bx    r0
    .size FLEXCOMM2_IRQHandler, . - FLEXCOMM2_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM3_IRQHandler
    .type FLEXCOMM3_IRQHandler, %function
FLEXCOMM3_IRQHandler:
    ldr   r0,=FLEXCOMM3_DriverIRQHandler
    bx    r0
    .size FLEXCOMM3_IRQHandler, . - FLEXCOMM3_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM4_IRQHandler
    .type FLEXCOMM4_IRQHandler, %function
FLEXCOMM4_IRQHandler:
    ldr   r0,=FLEXCOMM4_DriverIRQHandler
    bx    r0
    .size FLEXCOMM4_IRQHandler, . - FLEXCOMM4_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM5_IRQHandler
    .type FLEXCOMM5_IRQHandler, %function
FLEXCOMM5_IRQHandler:
    ldr   r0,=FLEXCOMM5_DriverIRQHandler
    bx    r0
    .size FLEXCOMM5_IRQHandler, . - FLEXCOMM5_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM6_IRQHandler
    .type FLEXCOMM6_IRQHandler, %function
FLEXCOMM6_IRQHandler:
    ldr   r0,=FLEXCOMM6_DriverIRQHandler
    bx    r0
    .size FLEXCOMM6_IRQHandler, . - FLEXCOMM6_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM7_IRQHandler
    .type FLEXCOMM7_IRQHandler, %function
FLEXCOMM7_IRQHandler:
    ldr   r0,=FLEXCOMM7_DriverIRQHandler
    bx    r0
    .size FLEXCOMM7_IRQHandler, . - FLEXCOMM7_IRQHandler

    .align 1
    .thumb_func
    .weak ADC0_IRQHandler
    .type ADC0_IRQHandler, %function
ADC0_IRQHandler:
    ldr   r0,=ADC0_DriverIRQHandler
    bx    r0
    .size ADC0_IRQHandler, . - ADC0_IRQHandler

    .align 1
    .thumb_func
    .weak ADC1_IRQHandler
    .type ADC1_IRQHandler, %function
ADC1_IRQHandler:
    ldr   r0,=ADC1_DriverIRQHandler
    bx    r0
    .size ADC1_IRQHandler, . - ADC1_IRQHandler

    .align 1
    .thumb_func
    .weak ACMP_IRQHandler
    .type ACMP_IRQHandler, %function
ACMP_IRQHandler:
    ldr   r0,=ACMP_DriverIRQHandler
    bx    r0
    .size ACMP_IRQHandler, . - ACMP_IRQHandler

    .align 1
    .thumb_func
    .weak DMIC_IRQHandler
    .type DMIC_IRQHandler, %function
DMIC_IRQHandler:
    ldr   r0,=DMIC_DriverIRQHandler
    bx    r0
    .size DMIC_IRQHandler, . - DMIC_IRQHandler

    .align 1
    .thumb_func
    .weak HWVAD0_IRQHandler
    .type HWVAD0_IRQHandler, %function
HWVAD0_IRQHandler:
    ldr   r0,=HWVAD0_DriverIRQHandler
    bx    r0
    .size HWVAD0_IRQHandler, . - HWVAD0_IRQHandler

    .align 1
    .thumb_func
    .weak USB0_NEEDCLK_IRQHandler
    .type USB0_NEEDCLK_IRQHandler, %function
USB0_NEEDCLK_IRQHandler:
    ldr   r0,=USB0_NEEDCLK_DriverIRQHandler
    bx    r0
    .size USB0_NEEDCLK_IRQHandler, . - USB0_NEEDCLK_IRQHandler

    .align 1
    .thumb_func
    .weak USB0_IRQHandler
    .type USB0_IRQHandler, %function
USB0_IRQHandler:
    ldr   r0,=USB0_DriverIRQHandler
    bx    r0
    .size USB0_IRQHandler, . - USB0_IRQHandler

    .align 1
    .thumb_func
    .weak RTC_IRQHandler
    .type RTC_IRQHandler, %function
RTC_IRQHandler:
    ldr   r0,=RTC_DriverIRQHandler
    bx    r0
    .size RTC_IRQHandler, . - RTC_IRQHandler

    .align 1
    .thumb_func
    .weak EZH_ARCH_B0_IRQHandler
    .type EZH_ARCH_B0_IRQHandler, %function
EZH_ARCH_B0_IRQHandler:
    ldr   r0,=EZH_ARCH_B0_DriverIRQHandler
    bx    r0
    .size EZH_ARCH_B0_IRQHandler, . - EZH_ARCH_B0_IRQHandler

    .align 1
    .thumb_func
    .weak WAKEUP_IRQHandler
    .type WAKEUP_IRQHandler, %function
WAKEUP_IRQHandler:
    ldr   r0,=WAKEUP_DriverIRQHandler
    bx    r0
    .size WAKEUP_IRQHandler, . - WAKEUP_IRQHandler

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

    .align 1
    .thumb_func
    .weak CTIMER2_IRQHandler
    .type CTIMER2_IRQHandler, %function
CTIMER2_IRQHandler:
    ldr   r0,=CTIMER2_DriverIRQHandler
    bx    r0
    .size CTIMER2_IRQHandler, . - CTIMER2_IRQHandler

    .align 1
    .thumb_func
    .weak CTIMER4_IRQHandler
    .type CTIMER4_IRQHandler, %function
CTIMER4_IRQHandler:
    ldr   r0,=CTIMER4_DriverIRQHandler
    bx    r0
    .size CTIMER4_IRQHandler, . - CTIMER4_IRQHandler

    .align 1
    .thumb_func
    .weak OS_EVENT_IRQHandler
    .type OS_EVENT_IRQHandler, %function
OS_EVENT_IRQHandler:
    ldr   r0,=OS_EVENT_DriverIRQHandler
    bx    r0
    .size OS_EVENT_IRQHandler, . - OS_EVENT_IRQHandler

    .align 1
    .thumb_func
    .weak FlexSPI0_IRQHandler
    .type FlexSPI0_IRQHandler, %function
FlexSPI0_IRQHandler:
    ldr   r0,=FlexSPI0_DriverIRQHandler
    bx    r0
    .size FlexSPI0_IRQHandler, . - FlexSPI0_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved56_IRQHandler
    .type Reserved56_IRQHandler, %function
Reserved56_IRQHandler:
    ldr   r0,=Reserved56_DriverIRQHandler
    bx    r0
    .size Reserved56_IRQHandler, . - Reserved56_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved57_IRQHandler
    .type Reserved57_IRQHandler, %function
Reserved57_IRQHandler:
    ldr   r0,=Reserved57_DriverIRQHandler
    bx    r0
    .size Reserved57_IRQHandler, . - Reserved57_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved58_IRQHandler
    .type Reserved58_IRQHandler, %function
Reserved58_IRQHandler:
    ldr   r0,=Reserved58_DriverIRQHandler
    bx    r0
    .size Reserved58_IRQHandler, . - Reserved58_IRQHandler

    .align 1
    .thumb_func
    .weak CAN0_IRQ0_IRQHandler
    .type CAN0_IRQ0_IRQHandler, %function
CAN0_IRQ0_IRQHandler:
    ldr   r0,=CAN0_IRQ0_DriverIRQHandler
    bx    r0
    .size CAN0_IRQ0_IRQHandler, . - CAN0_IRQ0_IRQHandler

    .align 1
    .thumb_func
    .weak CAN0_IRQ1_IRQHandler
    .type CAN0_IRQ1_IRQHandler, %function
CAN0_IRQ1_IRQHandler:
    ldr   r0,=CAN0_IRQ1_DriverIRQHandler
    bx    r0
    .size CAN0_IRQ1_IRQHandler, . - CAN0_IRQ1_IRQHandler

    .align 1
    .thumb_func
    .weak SPI_FILTER_IRQHandler
    .type SPI_FILTER_IRQHandler, %function
SPI_FILTER_IRQHandler:
    ldr   r0,=SPI_FILTER_DriverIRQHandler
    bx    r0
    .size SPI_FILTER_IRQHandler, . - SPI_FILTER_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved62_IRQHandler
    .type Reserved62_IRQHandler, %function
Reserved62_IRQHandler:
    ldr   r0,=Reserved62_DriverIRQHandler
    bx    r0
    .size Reserved62_IRQHandler, . - Reserved62_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved63_IRQHandler
    .type Reserved63_IRQHandler, %function
Reserved63_IRQHandler:
    ldr   r0,=Reserved63_DriverIRQHandler
    bx    r0
    .size Reserved63_IRQHandler, . - Reserved63_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved64_IRQHandler
    .type Reserved64_IRQHandler, %function
Reserved64_IRQHandler:
    ldr   r0,=Reserved64_DriverIRQHandler
    bx    r0
    .size Reserved64_IRQHandler, . - Reserved64_IRQHandler

    .align 1
    .thumb_func
    .weak SEC_HYPERVISOR_CALL_IRQHandler
    .type SEC_HYPERVISOR_CALL_IRQHandler, %function
SEC_HYPERVISOR_CALL_IRQHandler:
    ldr   r0,=SEC_HYPERVISOR_CALL_DriverIRQHandler
    bx    r0
    .size SEC_HYPERVISOR_CALL_IRQHandler, . - SEC_HYPERVISOR_CALL_IRQHandler

    .align 1
    .thumb_func
    .weak SEC_GPIO_INT0_IRQ0_IRQHandler
    .type SEC_GPIO_INT0_IRQ0_IRQHandler, %function
SEC_GPIO_INT0_IRQ0_IRQHandler:
    ldr   r0,=SEC_GPIO_INT0_IRQ0_DriverIRQHandler
    bx    r0
    .size SEC_GPIO_INT0_IRQ0_IRQHandler, . - SEC_GPIO_INT0_IRQ0_IRQHandler

    .align 1
    .thumb_func
    .weak SEC_GPIO_INT0_IRQ1_IRQHandler
    .type SEC_GPIO_INT0_IRQ1_IRQHandler, %function
SEC_GPIO_INT0_IRQ1_IRQHandler:
    ldr   r0,=SEC_GPIO_INT0_IRQ1_DriverIRQHandler
    bx    r0
    .size SEC_GPIO_INT0_IRQ1_IRQHandler, . - SEC_GPIO_INT0_IRQ1_IRQHandler

    .align 1
    .thumb_func
    .weak Freqme_IRQHandler
    .type Freqme_IRQHandler, %function
Freqme_IRQHandler:
    ldr   r0,=Freqme_DriverIRQHandler
    bx    r0
    .size Freqme_IRQHandler, . - Freqme_IRQHandler

    .align 1
    .thumb_func
    .weak SEC_VIO_IRQHandler
    .type SEC_VIO_IRQHandler, %function
SEC_VIO_IRQHandler:
    ldr   r0,=SEC_VIO_DriverIRQHandler
    bx    r0
    .size SEC_VIO_IRQHandler, . - SEC_VIO_IRQHandler

    .align 1
    .thumb_func
    .weak SHA_IRQHandler
    .type SHA_IRQHandler, %function
SHA_IRQHandler:
    ldr   r0,=SHA_DriverIRQHandler
    bx    r0
    .size SHA_IRQHandler, . - SHA_IRQHandler

    .align 1
    .thumb_func
    .weak PKC_IRQHandler
    .type PKC_IRQHandler, %function
PKC_IRQHandler:
    ldr   r0,=PKC_DriverIRQHandler
    bx    r0
    .size PKC_IRQHandler, . - PKC_IRQHandler

    .align 1
    .thumb_func
    .weak PUF_IRQHandler
    .type PUF_IRQHandler, %function
PUF_IRQHandler:
    ldr   r0,=PUF_DriverIRQHandler
    bx    r0
    .size PUF_IRQHandler, . - PUF_IRQHandler

    .align 1
    .thumb_func
    .weak POWERQUAD_IRQHandler
    .type POWERQUAD_IRQHandler, %function
POWERQUAD_IRQHandler:
    ldr   r0,=POWERQUAD_DriverIRQHandler
    bx    r0
    .size POWERQUAD_IRQHandler, . - POWERQUAD_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_IRQHandler
    .type DMA1_IRQHandler, %function
DMA1_IRQHandler:
    ldr   r0,=DMA1_DriverIRQHandler
    bx    r0
    .size DMA1_IRQHandler, . - DMA1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXCOMM8_IRQHandler
    .type FLEXCOMM8_IRQHandler, %function
FLEXCOMM8_IRQHandler:
    ldr   r0,=FLEXCOMM8_DriverIRQHandler
    bx    r0
    .size FLEXCOMM8_IRQHandler, . - FLEXCOMM8_IRQHandler

    .align 1
    .thumb_func
    .weak CDOG_IRQHandler
    .type CDOG_IRQHandler, %function
CDOG_IRQHandler:
    ldr   r0,=CDOG_DriverIRQHandler
    bx    r0
    .size CDOG_IRQHandler, . - CDOG_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved77_IRQHandler
    .type Reserved77_IRQHandler, %function
Reserved77_IRQHandler:
    ldr   r0,=Reserved77_DriverIRQHandler
    bx    r0
    .size Reserved77_IRQHandler, . - Reserved77_IRQHandler

    .align 1
    .thumb_func
    .weak I3C0_IRQHandler
    .type I3C0_IRQHandler, %function
I3C0_IRQHandler:
    ldr   r0,=I3C0_DriverIRQHandler
    bx    r0
    .size I3C0_IRQHandler, . - I3C0_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved79_IRQHandler
    .type Reserved79_IRQHandler, %function
Reserved79_IRQHandler:
    ldr   r0,=Reserved79_DriverIRQHandler
    bx    r0
    .size Reserved79_IRQHandler, . - Reserved79_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved80_IRQHandler
    .type Reserved80_IRQHandler, %function
Reserved80_IRQHandler:
    ldr   r0,=Reserved80_DriverIRQHandler
    bx    r0
    .size Reserved80_IRQHandler, . - Reserved80_IRQHandler

    .align 1
    .thumb_func
    .weak CSS_IRQ1_IRQHandler
    .type CSS_IRQ1_IRQHandler, %function
CSS_IRQ1_IRQHandler:
    ldr   r0,=CSS_IRQ1_DriverIRQHandler
    bx    r0
    .size CSS_IRQ1_IRQHandler, . - CSS_IRQ1_IRQHandler

    .align 1
    .thumb_func
    .weak Tamper_IRQHandler
    .type Tamper_IRQHandler, %function
Tamper_IRQHandler:
    ldr   r0,=Tamper_DriverIRQHandler
    bx    r0
    .size Tamper_IRQHandler, . - Tamper_IRQHandler

    .align 1
    .thumb_func
    .weak Analog_Glitch_IRQHandler
    .type Analog_Glitch_IRQHandler, %function
Analog_Glitch_IRQHandler:
    ldr   r0,=Analog_Glitch_DriverIRQHandler
    bx    r0
    .size Analog_Glitch_IRQHandler, . - Analog_Glitch_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved84_IRQHandler
    .type Reserved84_IRQHandler, %function
Reserved84_IRQHandler:
    ldr   r0,=Reserved84_DriverIRQHandler
    bx    r0
    .size Reserved84_IRQHandler, . - Reserved84_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved85_IRQHandler
    .type Reserved85_IRQHandler, %function
Reserved85_IRQHandler:
    ldr   r0,=Reserved85_DriverIRQHandler
    bx    r0
    .size Reserved85_IRQHandler, . - Reserved85_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved86_IRQHandler
    .type Reserved86_IRQHandler, %function
Reserved86_IRQHandler:
    ldr   r0,=Reserved86_DriverIRQHandler
    bx    r0
    .size Reserved86_IRQHandler, . - Reserved86_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved87_IRQHandler
    .type Reserved87_IRQHandler, %function
Reserved87_IRQHandler:
    ldr   r0,=Reserved87_DriverIRQHandler
    bx    r0
    .size Reserved87_IRQHandler, . - Reserved87_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved88_IRQHandler
    .type Reserved88_IRQHandler, %function
Reserved88_IRQHandler:
    ldr   r0,=Reserved88_DriverIRQHandler
    bx    r0
    .size Reserved88_IRQHandler, . - Reserved88_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved89_IRQHandler
    .type Reserved89_IRQHandler, %function
Reserved89_IRQHandler:
    ldr   r0,=Reserved89_DriverIRQHandler
    bx    r0
    .size Reserved89_IRQHandler, . - Reserved89_IRQHandler

    .align 1
    .thumb_func
    .weak DAC0_IRQHandler
    .type DAC0_IRQHandler, %function
DAC0_IRQHandler:
    ldr   r0,=DAC0_DriverIRQHandler
    bx    r0
    .size DAC0_IRQHandler, . - DAC0_IRQHandler

    .align 1
    .thumb_func
    .weak DAC1_IRQHandler
    .type DAC1_IRQHandler, %function
DAC1_IRQHandler:
    ldr   r0,=DAC1_DriverIRQHandler
    bx    r0
    .size DAC1_IRQHandler, . - DAC1_IRQHandler

    .align 1
    .thumb_func
    .weak DAC2_IRQHandler
    .type DAC2_IRQHandler, %function
DAC2_IRQHandler:
    ldr   r0,=DAC2_DriverIRQHandler
    bx    r0
    .size DAC2_IRQHandler, . - DAC2_IRQHandler

    .align 1
    .thumb_func
    .weak HSCMP0_IRQHandler
    .type HSCMP0_IRQHandler, %function
HSCMP0_IRQHandler:
    ldr   r0,=HSCMP0_DriverIRQHandler
    bx    r0
    .size HSCMP0_IRQHandler, . - HSCMP0_IRQHandler

    .align 1
    .thumb_func
    .weak HSCMP1_IRQHandler
    .type HSCMP1_IRQHandler, %function
HSCMP1_IRQHandler:
    ldr   r0,=HSCMP1_DriverIRQHandler
    bx    r0
    .size HSCMP1_IRQHandler, . - HSCMP1_IRQHandler

    .align 1
    .thumb_func
    .weak HSCMP2_IRQHandler
    .type HSCMP2_IRQHandler, %function
HSCMP2_IRQHandler:
    ldr   r0,=HSCMP2_DriverIRQHandler
    bx    r0
    .size HSCMP2_IRQHandler, . - HSCMP2_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_CAPTURE_IRQHandler
    .type FLEXPWM0_CAPTURE_IRQHandler, %function
FLEXPWM0_CAPTURE_IRQHandler:
    ldr   r0,=FLEXPWM0_CAPTURE_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_CAPTURE_IRQHandler, . - FLEXPWM0_CAPTURE_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_FAULT_IRQHandler
    .type FLEXPWM0_FAULT_IRQHandler, %function
FLEXPWM0_FAULT_IRQHandler:
    ldr   r0,=FLEXPWM0_FAULT_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_FAULT_IRQHandler, . - FLEXPWM0_FAULT_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_RELOAD_ERROR_IRQHandler
    .type FLEXPWM0_RELOAD_ERROR_IRQHandler, %function
FLEXPWM0_RELOAD_ERROR_IRQHandler:
    ldr   r0,=FLEXPWM0_RELOAD_ERROR_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_RELOAD_ERROR_IRQHandler, . - FLEXPWM0_RELOAD_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_COMPARE0_IRQHandler
    .type FLEXPWM0_COMPARE0_IRQHandler, %function
FLEXPWM0_COMPARE0_IRQHandler:
    ldr   r0,=FLEXPWM0_COMPARE0_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_COMPARE0_IRQHandler, . - FLEXPWM0_COMPARE0_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_RELOAD0_IRQHandler
    .type FLEXPWM0_RELOAD0_IRQHandler, %function
FLEXPWM0_RELOAD0_IRQHandler:
    ldr   r0,=FLEXPWM0_RELOAD0_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_RELOAD0_IRQHandler, . - FLEXPWM0_RELOAD0_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_COMPARE1_IRQHandler
    .type FLEXPWM0_COMPARE1_IRQHandler, %function
FLEXPWM0_COMPARE1_IRQHandler:
    ldr   r0,=FLEXPWM0_COMPARE1_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_COMPARE1_IRQHandler, . - FLEXPWM0_COMPARE1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_RELOAD1_IRQHandler
    .type FLEXPWM0_RELOAD1_IRQHandler, %function
FLEXPWM0_RELOAD1_IRQHandler:
    ldr   r0,=FLEXPWM0_RELOAD1_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_RELOAD1_IRQHandler, . - FLEXPWM0_RELOAD1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_COMPARE2_IRQHandler
    .type FLEXPWM0_COMPARE2_IRQHandler, %function
FLEXPWM0_COMPARE2_IRQHandler:
    ldr   r0,=FLEXPWM0_COMPARE2_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_COMPARE2_IRQHandler, . - FLEXPWM0_COMPARE2_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_RELOAD2_IRQHandler
    .type FLEXPWM0_RELOAD2_IRQHandler, %function
FLEXPWM0_RELOAD2_IRQHandler:
    ldr   r0,=FLEXPWM0_RELOAD2_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_RELOAD2_IRQHandler, . - FLEXPWM0_RELOAD2_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_COMPARE3_IRQHandler
    .type FLEXPWM0_COMPARE3_IRQHandler, %function
FLEXPWM0_COMPARE3_IRQHandler:
    ldr   r0,=FLEXPWM0_COMPARE3_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_COMPARE3_IRQHandler, . - FLEXPWM0_COMPARE3_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM0_RELOAD3_IRQHandler
    .type FLEXPWM0_RELOAD3_IRQHandler, %function
FLEXPWM0_RELOAD3_IRQHandler:
    ldr   r0,=FLEXPWM0_RELOAD3_DriverIRQHandler
    bx    r0
    .size FLEXPWM0_RELOAD3_IRQHandler, . - FLEXPWM0_RELOAD3_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_CAPTURE_IRQHandler
    .type FLEXPWM1_CAPTURE_IRQHandler, %function
FLEXPWM1_CAPTURE_IRQHandler:
    ldr   r0,=FLEXPWM1_CAPTURE_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_CAPTURE_IRQHandler, . - FLEXPWM1_CAPTURE_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_FAULT_IRQHandler
    .type FLEXPWM1_FAULT_IRQHandler, %function
FLEXPWM1_FAULT_IRQHandler:
    ldr   r0,=FLEXPWM1_FAULT_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_FAULT_IRQHandler, . - FLEXPWM1_FAULT_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_RELOAD_ERROR_IRQHandler
    .type FLEXPWM1_RELOAD_ERROR_IRQHandler, %function
FLEXPWM1_RELOAD_ERROR_IRQHandler:
    ldr   r0,=FLEXPWM1_RELOAD_ERROR_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_RELOAD_ERROR_IRQHandler, . - FLEXPWM1_RELOAD_ERROR_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_COMPARE0_IRQHandler
    .type FLEXPWM1_COMPARE0_IRQHandler, %function
FLEXPWM1_COMPARE0_IRQHandler:
    ldr   r0,=FLEXPWM1_COMPARE0_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_COMPARE0_IRQHandler, . - FLEXPWM1_COMPARE0_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_RELOAD0_IRQHandler
    .type FLEXPWM1_RELOAD0_IRQHandler, %function
FLEXPWM1_RELOAD0_IRQHandler:
    ldr   r0,=FLEXPWM1_RELOAD0_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_RELOAD0_IRQHandler, . - FLEXPWM1_RELOAD0_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_COMPARE1_IRQHandler
    .type FLEXPWM1_COMPARE1_IRQHandler, %function
FLEXPWM1_COMPARE1_IRQHandler:
    ldr   r0,=FLEXPWM1_COMPARE1_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_COMPARE1_IRQHandler, . - FLEXPWM1_COMPARE1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_RELOAD1_IRQHandler
    .type FLEXPWM1_RELOAD1_IRQHandler, %function
FLEXPWM1_RELOAD1_IRQHandler:
    ldr   r0,=FLEXPWM1_RELOAD1_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_RELOAD1_IRQHandler, . - FLEXPWM1_RELOAD1_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_COMPARE2_IRQHandler
    .type FLEXPWM1_COMPARE2_IRQHandler, %function
FLEXPWM1_COMPARE2_IRQHandler:
    ldr   r0,=FLEXPWM1_COMPARE2_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_COMPARE2_IRQHandler, . - FLEXPWM1_COMPARE2_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_RELOAD2_IRQHandler
    .type FLEXPWM1_RELOAD2_IRQHandler, %function
FLEXPWM1_RELOAD2_IRQHandler:
    ldr   r0,=FLEXPWM1_RELOAD2_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_RELOAD2_IRQHandler, . - FLEXPWM1_RELOAD2_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_COMPARE3_IRQHandler
    .type FLEXPWM1_COMPARE3_IRQHandler, %function
FLEXPWM1_COMPARE3_IRQHandler:
    ldr   r0,=FLEXPWM1_COMPARE3_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_COMPARE3_IRQHandler, . - FLEXPWM1_COMPARE3_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXPWM1_RELOAD3_IRQHandler
    .type FLEXPWM1_RELOAD3_IRQHandler, %function
FLEXPWM1_RELOAD3_IRQHandler:
    ldr   r0,=FLEXPWM1_RELOAD3_DriverIRQHandler
    bx    r0
    .size FLEXPWM1_RELOAD3_IRQHandler, . - FLEXPWM1_RELOAD3_IRQHandler

    .align 1
    .thumb_func
    .weak ENC0_COMPARE_IRQHandler
    .type ENC0_COMPARE_IRQHandler, %function
ENC0_COMPARE_IRQHandler:
    ldr   r0,=ENC0_COMPARE_DriverIRQHandler
    bx    r0
    .size ENC0_COMPARE_IRQHandler, . - ENC0_COMPARE_IRQHandler

    .align 1
    .thumb_func
    .weak ENC0_HOME_IRQHandler
    .type ENC0_HOME_IRQHandler, %function
ENC0_HOME_IRQHandler:
    ldr   r0,=ENC0_HOME_DriverIRQHandler
    bx    r0
    .size ENC0_HOME_IRQHandler, . - ENC0_HOME_IRQHandler

    .align 1
    .thumb_func
    .weak ENC0_WDG_IRQHandler
    .type ENC0_WDG_IRQHandler, %function
ENC0_WDG_IRQHandler:
    ldr   r0,=ENC0_WDG_DriverIRQHandler
    bx    r0
    .size ENC0_WDG_IRQHandler, . - ENC0_WDG_IRQHandler

    .align 1
    .thumb_func
    .weak ENC0_IDX_IRQHandler
    .type ENC0_IDX_IRQHandler, %function
ENC0_IDX_IRQHandler:
    ldr   r0,=ENC0_IDX_DriverIRQHandler
    bx    r0
    .size ENC0_IDX_IRQHandler, . - ENC0_IDX_IRQHandler

    .align 1
    .thumb_func
    .weak ENC1_COMPARE_IRQHandler
    .type ENC1_COMPARE_IRQHandler, %function
ENC1_COMPARE_IRQHandler:
    ldr   r0,=ENC1_COMPARE_DriverIRQHandler
    bx    r0
    .size ENC1_COMPARE_IRQHandler, . - ENC1_COMPARE_IRQHandler

    .align 1
    .thumb_func
    .weak ENC1_HOME_IRQHandler
    .type ENC1_HOME_IRQHandler, %function
ENC1_HOME_IRQHandler:
    ldr   r0,=ENC1_HOME_DriverIRQHandler
    bx    r0
    .size ENC1_HOME_IRQHandler, . - ENC1_HOME_IRQHandler

    .align 1
    .thumb_func
    .weak ENC1_WDG_IRQHandler
    .type ENC1_WDG_IRQHandler, %function
ENC1_WDG_IRQHandler:
    ldr   r0,=ENC1_WDG_DriverIRQHandler
    bx    r0
    .size ENC1_WDG_IRQHandler, . - ENC1_WDG_IRQHandler

    .align 1
    .thumb_func
    .weak ENC1_IDX_IRQHandler
    .type ENC1_IDX_IRQHandler, %function
ENC1_IDX_IRQHandler:
    ldr   r0,=ENC1_IDX_DriverIRQHandler
    bx    r0
    .size ENC1_IDX_IRQHandler, . - ENC1_IDX_IRQHandler

    .align 1
    .thumb_func
    .weak ITRC0_IRQHandler
    .type ITRC0_IRQHandler, %function
ITRC0_IRQHandler:
    ldr   r0,=ITRC0_DriverIRQHandler
    bx    r0
    .size ITRC0_IRQHandler, . - ITRC0_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved127_IRQHandler
    .type Reserved127_IRQHandler, %function
Reserved127_IRQHandler:
    ldr   r0,=Reserved127_DriverIRQHandler
    bx    r0
    .size Reserved127_IRQHandler, . - Reserved127_IRQHandler

    .align 1
    .thumb_func
    .weak CSSV2_ERR_IRQHandler
    .type CSSV2_ERR_IRQHandler, %function
CSSV2_ERR_IRQHandler:
    ldr   r0,=CSSV2_ERR_DriverIRQHandler
    bx    r0
    .size CSSV2_ERR_IRQHandler, . - CSSV2_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak PKC_ERR_IRQHandler
    .type PKC_ERR_IRQHandler, %function
PKC_ERR_IRQHandler:
    ldr   r0,=PKC_ERR_DriverIRQHandler
    bx    r0
    .size PKC_ERR_IRQHandler, . - PKC_ERR_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved130_IRQHandler
    .type Reserved130_IRQHandler, %function
Reserved130_IRQHandler:
    ldr   r0,=Reserved130_DriverIRQHandler
    bx    r0
    .size Reserved130_IRQHandler, . - Reserved130_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved131_IRQHandler
    .type Reserved131_IRQHandler, %function
Reserved131_IRQHandler:
    ldr   r0,=Reserved131_DriverIRQHandler
    bx    r0
    .size Reserved131_IRQHandler, . - Reserved131_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved132_IRQHandler
    .type Reserved132_IRQHandler, %function
Reserved132_IRQHandler:
    ldr   r0,=Reserved132_DriverIRQHandler
    bx    r0
    .size Reserved132_IRQHandler, . - Reserved132_IRQHandler

    .align 1
    .thumb_func
    .weak Reserved133_IRQHandler
    .type Reserved133_IRQHandler, %function
Reserved133_IRQHandler:
    ldr   r0,=Reserved133_DriverIRQHandler
    bx    r0
    .size Reserved133_IRQHandler, . - Reserved133_IRQHandler

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
    .weak RAM_PARITY_ECC_ERR_IRQHandler
    .type RAM_PARITY_ECC_ERR_IRQHandler, %function
RAM_PARITY_ECC_ERR_IRQHandler:
    ldr   r0,=RAM_PARITY_ECC_ERR_DriverIRQHandler
    bx    r0
    .size RAM_PARITY_ECC_ERR_IRQHandler, . - RAM_PARITY_ECC_ERR_IRQHandler

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
    def_irq_handler    SecureFault_Handler
    def_irq_handler    DebugMon_Handler
                def_irq_handler     WDT_BOD_DriverIRQHandler
                def_irq_handler     DMA0_DriverIRQHandler
                def_irq_handler     GINT0_DriverIRQHandler
                def_irq_handler     GINT1_DriverIRQHandler
                def_irq_handler     PIN_INT0_DriverIRQHandler
                def_irq_handler     PIN_INT1_DriverIRQHandler
                def_irq_handler     PIN_INT2_DriverIRQHandler
                def_irq_handler     PIN_INT3_DriverIRQHandler
                def_irq_handler     UTICK0_DriverIRQHandler
                def_irq_handler     MRT0_DriverIRQHandler
                def_irq_handler     CTIMER0_DriverIRQHandler
                def_irq_handler     CTIMER1_DriverIRQHandler
                def_irq_handler     SCT0_DriverIRQHandler
                def_irq_handler     CTIMER3_DriverIRQHandler
                def_irq_handler     FLEXCOMM0_DriverIRQHandler
                def_irq_handler     FLEXCOMM1_DriverIRQHandler
                def_irq_handler     FLEXCOMM2_DriverIRQHandler
                def_irq_handler     FLEXCOMM3_DriverIRQHandler
                def_irq_handler     FLEXCOMM4_DriverIRQHandler
                def_irq_handler     FLEXCOMM5_DriverIRQHandler
                def_irq_handler     FLEXCOMM6_DriverIRQHandler
                def_irq_handler     FLEXCOMM7_DriverIRQHandler
                def_irq_handler     ADC0_DriverIRQHandler
                def_irq_handler     ADC1_DriverIRQHandler
                def_irq_handler     ACMP_DriverIRQHandler
                def_irq_handler     DMIC_DriverIRQHandler
                def_irq_handler     HWVAD0_DriverIRQHandler
                def_irq_handler     USB0_NEEDCLK_DriverIRQHandler
                def_irq_handler     USB0_DriverIRQHandler
                def_irq_handler     RTC_DriverIRQHandler
                def_irq_handler     EZH_ARCH_B0_DriverIRQHandler
                def_irq_handler     WAKEUP_DriverIRQHandler
                def_irq_handler     PIN_INT4_DriverIRQHandler
                def_irq_handler     PIN_INT5_DriverIRQHandler
                def_irq_handler     PIN_INT6_DriverIRQHandler
                def_irq_handler     PIN_INT7_DriverIRQHandler
                def_irq_handler     CTIMER2_DriverIRQHandler
                def_irq_handler     CTIMER4_DriverIRQHandler
                def_irq_handler     OS_EVENT_DriverIRQHandler
                def_irq_handler     FlexSPI0_DriverIRQHandler
                def_irq_handler     Reserved56_DriverIRQHandler
                def_irq_handler     Reserved57_DriverIRQHandler
                def_irq_handler     Reserved58_DriverIRQHandler
                def_irq_handler     CAN0_IRQ0_DriverIRQHandler
                def_irq_handler     CAN0_IRQ1_DriverIRQHandler
                def_irq_handler     SPI_FILTER_DriverIRQHandler
                def_irq_handler     Reserved62_DriverIRQHandler
                def_irq_handler     Reserved63_DriverIRQHandler
                def_irq_handler     Reserved64_DriverIRQHandler
                def_irq_handler     SEC_HYPERVISOR_CALL_DriverIRQHandler
                def_irq_handler     SEC_GPIO_INT0_IRQ0_DriverIRQHandler
                def_irq_handler     SEC_GPIO_INT0_IRQ1_DriverIRQHandler
                def_irq_handler     Freqme_DriverIRQHandler
                def_irq_handler     SEC_VIO_DriverIRQHandler
                def_irq_handler     SHA_DriverIRQHandler
                def_irq_handler     PKC_DriverIRQHandler
                def_irq_handler     PUF_DriverIRQHandler
                def_irq_handler     POWERQUAD_DriverIRQHandler
                def_irq_handler     DMA1_DriverIRQHandler
                def_irq_handler     FLEXCOMM8_DriverIRQHandler
                def_irq_handler     CDOG_DriverIRQHandler
                def_irq_handler     Reserved77_DriverIRQHandler
                def_irq_handler     I3C0_DriverIRQHandler
                def_irq_handler     Reserved79_DriverIRQHandler
                def_irq_handler     Reserved80_DriverIRQHandler
                def_irq_handler     CSS_IRQ1_DriverIRQHandler
                def_irq_handler     Tamper_DriverIRQHandler
                def_irq_handler     Analog_Glitch_DriverIRQHandler
                def_irq_handler     Reserved84_DriverIRQHandler
                def_irq_handler     Reserved85_DriverIRQHandler
                def_irq_handler     Reserved86_DriverIRQHandler
                def_irq_handler     Reserved87_DriverIRQHandler
                def_irq_handler     Reserved88_DriverIRQHandler
                def_irq_handler     Reserved89_DriverIRQHandler
                def_irq_handler     DAC0_DriverIRQHandler
                def_irq_handler     DAC1_DriverIRQHandler
                def_irq_handler     DAC2_DriverIRQHandler
                def_irq_handler     HSCMP0_DriverIRQHandler
                def_irq_handler     HSCMP1_DriverIRQHandler
                def_irq_handler     HSCMP2_DriverIRQHandler
                def_irq_handler     FLEXPWM0_CAPTURE_DriverIRQHandler
                def_irq_handler     FLEXPWM0_FAULT_DriverIRQHandler
                def_irq_handler     FLEXPWM0_RELOAD_ERROR_DriverIRQHandler
                def_irq_handler     FLEXPWM0_COMPARE0_DriverIRQHandler
                def_irq_handler     FLEXPWM0_RELOAD0_DriverIRQHandler
                def_irq_handler     FLEXPWM0_COMPARE1_DriverIRQHandler
                def_irq_handler     FLEXPWM0_RELOAD1_DriverIRQHandler
                def_irq_handler     FLEXPWM0_COMPARE2_DriverIRQHandler
                def_irq_handler     FLEXPWM0_RELOAD2_DriverIRQHandler
                def_irq_handler     FLEXPWM0_COMPARE3_DriverIRQHandler
                def_irq_handler     FLEXPWM0_RELOAD3_DriverIRQHandler
                def_irq_handler     FLEXPWM1_CAPTURE_DriverIRQHandler
                def_irq_handler     FLEXPWM1_FAULT_DriverIRQHandler
                def_irq_handler     FLEXPWM1_RELOAD_ERROR_DriverIRQHandler
                def_irq_handler     FLEXPWM1_COMPARE0_DriverIRQHandler
                def_irq_handler     FLEXPWM1_RELOAD0_DriverIRQHandler
                def_irq_handler     FLEXPWM1_COMPARE1_DriverIRQHandler
                def_irq_handler     FLEXPWM1_RELOAD1_DriverIRQHandler
                def_irq_handler     FLEXPWM1_COMPARE2_DriverIRQHandler
                def_irq_handler     FLEXPWM1_RELOAD2_DriverIRQHandler
                def_irq_handler     FLEXPWM1_COMPARE3_DriverIRQHandler
                def_irq_handler     FLEXPWM1_RELOAD3_DriverIRQHandler
                def_irq_handler     ENC0_COMPARE_DriverIRQHandler
                def_irq_handler     ENC0_HOME_DriverIRQHandler
                def_irq_handler     ENC0_WDG_DriverIRQHandler
                def_irq_handler     ENC0_IDX_DriverIRQHandler
                def_irq_handler     ENC1_COMPARE_DriverIRQHandler
                def_irq_handler     ENC1_HOME_DriverIRQHandler
                def_irq_handler     ENC1_WDG_DriverIRQHandler
                def_irq_handler     ENC1_IDX_DriverIRQHandler
                def_irq_handler     ITRC0_DriverIRQHandler
                def_irq_handler     Reserved127_DriverIRQHandler
                def_irq_handler     CSSV2_ERR_DriverIRQHandler
                def_irq_handler     PKC_ERR_DriverIRQHandler
                def_irq_handler     Reserved130_DriverIRQHandler
                def_irq_handler     Reserved131_DriverIRQHandler
                def_irq_handler     Reserved132_DriverIRQHandler
                def_irq_handler     Reserved133_DriverIRQHandler
                def_irq_handler     FLASH_DriverIRQHandler
                def_irq_handler     RAM_PARITY_ECC_ERR_DriverIRQHandler

    .end
