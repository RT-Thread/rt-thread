/* ---------------------------------------------------------------------------------------*/
/*  @file:    startup_MKV10Z1287.s                                                        */
/*  @purpose: CMSIS Cortex-M0P Core Device Startup File                                   */
/*            MKV10Z1287                                                                  */
/*  @version: 1.0                                                                         */
/*  @date:    2014-12-14                                                                  */
/*  @build:   b150313                                                                     */
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
    .long   DMA0_DMA4_IRQHandler                            /* DMA channel 0 and 4 transfer complete*/
    .long   DMA1_DMA5_IRQHandler                            /* DMA channel 1 and 5 transfer complete*/
    .long   DMA2_DMA6_IRQHandler                            /* DMA channel 2 and 6 transfer complete*/
    .long   DMA3_DMA7_IRQHandler                            /* DMA channel 2 and 7 transfer complete*/
    .long   DMA_Error_IRQHandler                            /* DMA error interrupt channels 0-7*/
    .long   FTFA_IRQHandler                                 /* FTFA command complete and read collision*/
    .long   LVD_LVW_IRQHandler                              /* Low-voltage detect, low-voltage warning*/
    .long   LLWU_IRQHandler                                 /* Low Leakage Wakeup*/
    .long   I2C0_IRQHandler                                 /* I2C0 interrupt*/
    .long   Reserved25_IRQHandler                           /* Reserved interrupt*/
    .long   SPI0_IRQHandler                                 /* SPI0 single interrupt vector for all sources*/
    .long   Reserved27_IRQHandler                           /* Reserved interrupt*/
    .long   UART0_IRQHandler                                /* UART0 status and error*/
    .long   UART1_IRQHandler                                /* UART1 status and error*/
    .long   Reserved30_IRQHandler                           /* Reserved interrupt*/
    .long   ADC0_IRQHandler                                 /* ADC0 interrupt*/
    .long   ADC1_IRQHandler                                 /* ADC1 interrupt*/
    .long   FTM0_IRQHandler                                 /* FTM0 single interrupt vector for all sources*/
    .long   FTM1_IRQHandler                                 /* FTM1 single interrupt vector for all sources*/
    .long   FTM2_IRQHandler                                 /* FTM2 single interrupt vector for all sources*/
    .long   CMP0_IRQHandler                                 /* CMP0 interrupt*/
    .long   CMP1_IRQHandler                                 /* CMP1 interrupt*/
    .long   FTM3_IRQHandler                                 /* FTM3 single interrupt vector for all sources*/
    .long   WDOG_EWM_IRQHandler                             /* Single interrupt vector for  WDOG and EWM*/
    .long   FTM4_IRQHandler                                 /* FTM4 single interrupt vector for all sources*/
    .long   DAC0_IRQHandler                                 /* DAC0 interrupt*/
    .long   FTM5_IRQHandler                                 /* FTM5 single interrupt vector for all sources*/
    .long   MCG_IRQHandler                                  /* MCG interrupt*/
    .long   LPTMR0_IRQHandler                               /* LPTMR0 interrupt*/
    .long   PDB0_PDB1_IRQHandler                            /* Single interrupt vector for  PDB0 and PDB1*/
    .long   PORTA_IRQHandler                                /* PORTA pin detect*/
    .long   PORTB_PORTC_PORTD_PORTE_IRQHandler              /* Single interrupt vector for PORTB, PORTC, PORTD and PORTE pin detect*/

    .size    __isr_vector, . - __isr_vector

/* Flash Configuration */
    .section .FlashConfig, "a"
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFE

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
    def_irq_handler    DMA0_DMA4_IRQHandler
    def_irq_handler    DMA1_DMA5_IRQHandler
    def_irq_handler    DMA2_DMA6_IRQHandler
    def_irq_handler    DMA3_DMA7_IRQHandler
    def_irq_handler    DMA_Error_IRQHandler
    def_irq_handler    FTFA_IRQHandler
    def_irq_handler    LVD_LVW_IRQHandler
    def_irq_handler    LLWU_IRQHandler
    def_irq_handler    I2C0_IRQHandler
    def_irq_handler    Reserved25_IRQHandler
    def_irq_handler    SPI0_IRQHandler
    def_irq_handler    Reserved27_IRQHandler
    def_irq_handler    UART0_IRQHandler
    def_irq_handler    UART1_IRQHandler
    def_irq_handler    Reserved30_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    ADC1_IRQHandler
    def_irq_handler    FTM0_IRQHandler
    def_irq_handler    FTM1_IRQHandler
    def_irq_handler    FTM2_IRQHandler
    def_irq_handler    CMP0_IRQHandler
    def_irq_handler    CMP1_IRQHandler
    def_irq_handler    FTM3_IRQHandler
    def_irq_handler    WDOG_EWM_IRQHandler
    def_irq_handler    FTM4_IRQHandler
    def_irq_handler    DAC0_IRQHandler
    def_irq_handler    FTM5_IRQHandler
    def_irq_handler    MCG_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    PDB0_PDB1_IRQHandler
    def_irq_handler    PORTA_IRQHandler
    def_irq_handler    PORTB_PORTC_PORTD_PORTE_IRQHandler

    .end
