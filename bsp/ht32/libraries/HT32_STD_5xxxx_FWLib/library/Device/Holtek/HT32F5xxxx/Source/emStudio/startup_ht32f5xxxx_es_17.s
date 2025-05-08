/*---------------------------------------------------------------------------------------------------------*/
/* Holtek Semiconductor Inc.                                                                               */
/*                                                                                                         */
/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
/* All rights reserved.                                                                                    */
/*                                                                                                         */
/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f5xxxx_es_17.s
;  Version          : $Rev:: 7718         $
;  Date             : $Date:: 2024-05-13 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

/*
;  Supported Device
;  ========================================
;   HT32F52234, HT32F52244
*/

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */
/*
;// <o>  HT32 Device
;//      <0=> By Project Asm Define
;//      <35=> HT32F52234/44
*/
    .equ    USE_HT32_CHIP_SET, 0

    .equ _HT32FWID, 0xFFFFFFFF
/*
    .equ _HT32FWID, 0x00052234
    .equ _HT32FWID, 0x00052244
*/

    .equ HT32F52234_44, 35

  .if USE_HT32_CHIP_SET == 0
  .else
    .equ USE_HT32_CHIP, USE_HT32_CHIP_SET
  .endif

    .equ    _RESERVED, 0xFFFFFFFF
/*
;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;********************************************************************************/
                    .syntax unified
                    .global reset_handler
                    .global Reset_Handler
                    .equ Reset_Handler, reset_handler

                    .section  .vectors, "ax"
                    .section .vectors, "ax"
                    .code 16
                    .balign 2
                    .global _vectors
_vectors:
                    .long  __stack_end__                      /* ---, 00, 0x000, Top address of Stack       */
                    .long  reset_handler                      /* ---, 01, 0x004, Reset Handler              */
                    .long  NMI_Handler                        /* -14, 02, 0x008, NMI Handler                */
                    .long  HardFault_Handler                  /* -13, 03, 0x00C, Hard Fault Handler         */
                    .long  _RESERVED                          /* ---, 04, 0x010, Reserved                   */
                    .long  _RESERVED                          /* ---, 05, 0x014, Reserved                   */
                    .long  _RESERVED                          /* ---, 06, 0x018, Reserved                   */
                    .long  _RESERVED                          /* ---, 07, 0x01C, Reserved                   */
                    .long  _HT32FWID                          /* ---, 08, 0x020, Reserved                   */
                    .long  _RESERVED                          /* ---, 09, 0x024, Reserved                   */
                    .long  _RESERVED                          /* ---, 10, 0x028, Reserved                   */
                    .long  SVC_Handler                        /* -05, 11, 0x02C, SVC Handler                */
                    .long  _RESERVED                          /* ---, 12, 0x030, Reserved                   */
                    .long  _RESERVED                          /* ---, 13, 0x034, Reserved                   */
                    .long  PendSV_Handler                     /* -02, 14, 0x038, PendSV Handler             */
                    .long  SysTick_Handler                    /* -01, 15, 0x03C, SysTick Handler            */

                    /* External Interrupt Handler                                                           */
                    .long  LVD_BOD_IRQHandler                 /*  00, 16, 0x040,                            */
                    .long  RTC_IRQHandler                     /*  01, 17, 0x044,                            */
                    .long  FLASH_IRQHandler                   /*  02, 18, 0x048,                            */
                    .long  EVWUP_IRQHandler                   /*  03, 19, 0x04C,                            */
                    .long  EXTI0_1_IRQHandler                 /*  04, 20, 0x050,                            */
                    .long  EXTI2_3_IRQHandler                 /*  05, 21, 0x054,                            */
                    .long  EXTI4_15_IRQHandler                /*  06, 22, 0x058,                            */
                    .long  DAC0_1_IRQHandler                  /*  07, 23, 0x05C,                            */
                    .long  ADC_IRQHandler                     /*  08, 24, 0x060,                            */
                    .long  I2C2_IRQHandler                    /*  09, 25, 0x064,                            */
                    .long  _RESERVED                          /*  10, 26, 0x068,                            */
                    .long  _RESERVED                          /*  11, 27, 0x06C,                            */
                    .long  _RESERVED                          /*  12, 28, 0x070,                            */
                    .long  SCTM0_IRQHandler                   /*  13, 29, 0x074,                            */
                    .long  SCTM1_IRQHandler                   /*  14, 30, 0x078,                            */
                    .long  PWM0_IRQHandler                    /*  15, 31, 0x07C,                            */
                    .long  _RESERVED                          /*  16, 32, 0x080,                            */
                    .long  BFTM0_IRQHandler                   /*  17, 33, 0x084,                            */
                    .long  BFTM1_IRQHandler                   /*  18, 34, 0x088,                            */
                    .long  I2C0_IRQHandler                    /*  19, 35, 0x08C,                            */
                    .long  I2C1_IRQHandler                    /*  20, 36, 0x090,                            */
                    .long  SPI0_IRQHandler                    /*  21, 37, 0x094,                            */
                    .long  _RESERVED                          /*  22, 38, 0x098,                            */
                    .long  USART0_IRQHandler                  /*  23, 39, 0x09C,                            */
                    .long  _RESERVED                          /*  24, 40, 0x0A0,                            */
                    .long  UART0_IRQHandler                   /*  25, 41, 0x0A4,                            */
                    .long  _RESERVED                          /*  26, 42, 0x0A8,                            */
                    .long  _RESERVED                          /*  27, 43, 0x0AC,                            */
                    .long  _RESERVED                          /*  28, 44, 0x0B0,                            */
                    .long  _RESERVED                          /*  29, 45, 0x0B4,                            */
                    .long  PDMA_CH0_1_IRQHandler              /*  30, 46, 0x0B8,                            */
                    .long  PDMA_CH2_5_IRQHandler              /*  31, 47, 0x0BC,                            */



    .thumb


/* Reset Handler */

    .section .text.reset_handler
    .weak  reset_handler
    .type  reset_handler, %function
reset_handler:
                    LDR     R0, =__stack_end__      /* set stack pointer */
                    MOV     SP, R0
                    LDR     R0, =SystemInit
                    BLX     R0
                    BL      _start
    .size  Reset_Handler, .-Reset_Handler

/* Exception Handlers */

    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:
                    B       .
    .size   NMI_Handler, . - NMI_Handler

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:
                    B       .
    .size   HardFault_Handler, . - HardFault_Handler

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
                    B       .
    .size   SVC_Handler, . - SVC_Handler

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:
                    B       .
    .size   PendSV_Handler, . - PendSV_Handler

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:
                    B       .
    .size   SysTick_Handler, . - SysTick_Handler


/* IRQ Handlers */

    .globl  Default_Handler
    .type   Default_Handler, %function
Default_Handler:
                    B       .
    .size   Default_Handler, . - Default_Handler

    .macro  IRQ handler
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

    IRQ     LVD_BOD_IRQHandler
    IRQ     RTC_IRQHandler
    IRQ     FLASH_IRQHandler
    IRQ     EVWUP_IRQHandler
    IRQ     EXTI0_1_IRQHandler
    IRQ     EXTI2_3_IRQHandler
    IRQ     EXTI4_15_IRQHandler
    IRQ     DAC0_1_IRQHandler
    IRQ     ADC_IRQHandler
    IRQ     I2C2_IRQHandler
    IRQ     SCTM0_IRQHandler
    IRQ     SCTM1_IRQHandler
    IRQ     PWM0_IRQHandler
    IRQ     BFTM0_IRQHandler
    IRQ     BFTM1_IRQHandler
    IRQ     I2C0_IRQHandler
    IRQ     I2C1_IRQHandler
    IRQ     SPI0_IRQHandler
    IRQ     USART0_IRQHandler
    IRQ     UART0_IRQHandler
    IRQ     PDMA_CH0_1_IRQHandler
    IRQ     PDMA_CH2_5_IRQHandler

    .end
