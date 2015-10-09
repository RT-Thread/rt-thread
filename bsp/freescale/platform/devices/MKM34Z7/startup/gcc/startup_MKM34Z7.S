/* ---------------------------------------------------------------------------------------*/
/*  @file:    startup_MKM34Z7.s                                                           */
/*  @purpose: CMSIS Cortex-M0P Core Device Startup File                                   */
/*            MKM34Z7                                                                     */
/*  @version: 1.2                                                                         */
/*  @date:    2015-3-6                                                                    */
/*  @build:   b150513                                                                     */
/* ---------------------------------------------------------------------------------------*/
/*                                                                                        */
/* Copyright (c) 1997 - 2015 , Freescale Semiconductor, Inc.                              */
/* All rights reserved.                                                                   */
/*                                                                                        */
/* Redistribution and use in source and binary forms, with or without modification,       */
/* are permitted provided that the following conditions are met:                          */
/*                                                                                        */
/* o Redistributions of source code must retain the above copyright notice, this list     */
/*   of conditions and the following disclaimer.                                          */
/*                                                                                        */
/* o Redistributions in binary form must reproduce the above copyright notice, this       */
/*   list of conditions and the following disclaimer in the documentation and/or          */
/*   other materials provided with the distribution.                                      */
/*                                                                                        */
/* o Neither the name of Freescale Semiconductor, Inc. nor the names of its               */
/*   contributors may be used to endorse or promote products derived from this            */
/*   software without specific prior written permission.                                  */
/*                                                                                        */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND        */
/* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED          */
/* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                 */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR       */
/* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES         */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;           */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON         */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS          */
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv6-m

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
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
    .long   DMA0_IRQHandler                                 /* DMA channel 0 transfer complete*/
    .long   DMA1_IRQHandler                                 /* DMA channel 1 transfer complete*/
    .long   DMA2_IRQHandler                                 /* DMA channel 2 transfer complete*/
    .long   DMA3_IRQHandler                                 /* DMA channel 3 transfer complete*/
    .long   SPI0_SPI1_IRQHandler                            /* SPI0/SPI1 ORed interrupt*/
    .long   PDB0_IRQHandler                                 /* PDB0 ORed interrupt*/
    .long   PMC_IRQHandler                                  /* Low-voltage detect, low-voltage warning*/
    .long   TMR0_IRQHandler                                 /* Quad Timer Channel 0*/
    .long   TMR1_IRQHandler                                 /* Quad Timer Channel 1*/
    .long   TMR2_IRQHandler                                 /* Quad Timer Channel 2*/
    .long   TMR3_IRQHandler                                 /* Quad Timer Channel 3*/
    .long   PIT0_PIT1_IRQHandler                            /* PIT0/PIT1 ORed interrupt*/
    .long   LLWU_IRQHandler                                 /* Low Leakage Wakeup*/
    .long   FTFA_IRQHandler                                 /* Command complete and read collision*/
    .long   CMP0_CMP1_CMP2_IRQHandler                       /* CMP0/CMP1/CMP2 ORed interrupt*/
    .long   LCD_IRQHandler                                  /* LCD interrupt*/
    .long   ADC0_IRQHandler                                 /* ADC0 interrupt*/
    .long   PTx_IRQHandler                                  /* Single interrupt vector for GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH,GPIOI,GPIOJ,GPIOK,GPIOL,GPIOM*/
    .long   RNGA_IRQHandler                                 /* RNGA interrupt*/
    .long   UART0_UART1_UART2_UART3_IRQHandler              /* UART0/UART1/UART2/UART3 ORed interrupt*/
    .long   MMAU_IRQHandler                                 /* Memory Mapped Arithmetic Unit interrupt*/
    .long   AFE_CH0_IRQHandler                              /* AFE Channel 0*/
    .long   AFE_CH1_IRQHandler                              /* AFE Channel 1*/
    .long   AFE_CH2_IRQHandler                              /* AFE Channel 2*/
    .long   AFE_CH3_IRQHandler                              /* AFE Channel 3*/
    .long   RTC_IRQHandler                                  /* IRTC interrupt*/
    .long   I2C0_I2C1_IRQHandler                            /* I2C0/I2C1 ORed interrupt*/
    .long   LPUART0_IRQHandler                              /* LPUART0 status and error interrupt*/
    .long   MCG_IRQHandler                                  /* MCG interrupt*/
    .long   WDOG_EWM_IRQHandler                             /* WDOG/EWM ORed interrupt*/
    .long   LPTMR0_IRQHandler                               /* LPTMR0 interrupt*/
    .long   XBAR_IRQHandler                                 /* XBAR interrupt*/

    .size    __isr_vector, . - __isr_vector

/* Flash Configuration */
    .section .FlashConfig, "a"
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFF3FFE

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
#ifndef __NO_SYSTEM_INIT
    bl SystemInit
#endif
    bl init_data_bss
    cpsie   i               /* Unmask interrupts */
#ifndef __START
#define __START _start
#endif
#ifndef __ATOLLIC__
    bl    __START
#else
    bl    __libc_init_array
    bl    main
#endif
    .pool
    .size Reset_Handler, . - Reset_Handler

    .align	1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    ldr	r0, =DefaultISR
    bx r0
    .size DefaultISR, . - DefaultISR

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler	handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler    NMI_Handler
    def_irq_handler    HardFault_Handler
    def_irq_handler    SVC_Handler
    def_irq_handler    PendSV_Handler
    def_irq_handler    SysTick_Handler
    def_irq_handler    DMA0_IRQHandler
    def_irq_handler    DMA1_IRQHandler
    def_irq_handler    DMA2_IRQHandler
    def_irq_handler    DMA3_IRQHandler
    def_irq_handler    SPI0_SPI1_IRQHandler
    def_irq_handler    PDB0_IRQHandler
    def_irq_handler    PMC_IRQHandler
    def_irq_handler    TMR0_IRQHandler
    def_irq_handler    TMR1_IRQHandler
    def_irq_handler    TMR2_IRQHandler
    def_irq_handler    TMR3_IRQHandler
    def_irq_handler    PIT0_PIT1_IRQHandler
    def_irq_handler    LLWU_IRQHandler
    def_irq_handler    FTFA_IRQHandler
    def_irq_handler    CMP0_CMP1_CMP2_IRQHandler
    def_irq_handler    LCD_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    PTx_IRQHandler
    def_irq_handler    RNGA_IRQHandler
    def_irq_handler    UART0_UART1_UART2_UART3_IRQHandler
    def_irq_handler    MMAU_IRQHandler
    def_irq_handler    AFE_CH0_IRQHandler
    def_irq_handler    AFE_CH1_IRQHandler
    def_irq_handler    AFE_CH2_IRQHandler
    def_irq_handler    AFE_CH3_IRQHandler
    def_irq_handler    RTC_IRQHandler
    def_irq_handler    I2C0_I2C1_IRQHandler
    def_irq_handler    LPUART0_IRQHandler
    def_irq_handler    MCG_IRQHandler
    def_irq_handler    WDOG_EWM_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    XBAR_IRQHandler

    .end
