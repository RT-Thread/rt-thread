/*---------------------------------------------------------------------------------------------------------*/
/* Holtek Semiconductor Inc.                                                                               */
/*                                                                                                         */
/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
/* All rights reserved.                                                                                    */
/*                                                                                                         */
/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f5xxxx_es_14.s
;  Version          : $Rev:: 8287         $
;  Date             : $Date:: 2024-11-27 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

/*
;  Supported Device
;  ========================================
;   HT32F50442, HT32F50452
;   HT32F50431, HT32F50441
;   HT32F61052
*/

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */
/*
;// <o>  HT32 Device
;//      <0=> By Project Asm Define
;//      <26=> HT32F50442/52
;//      <30=> HT32F50431/41
;//      <26=> HT32F61052
*/
    .equ    USE_HT32_CHIP_SET, 0

    .equ _HT32FWID, 0xFFFFFFFF
/*
    .equ _HT32FWID, 0x00050442
    .equ _HT32FWID, 0x00050452
    .equ _HT32FWID, 0x00050431
    .equ _HT32FWID, 0x00050441
    .equ _HT32FWID, 0x00061052
*/

    .equ HT32F50442_52, 26
    .equ HT32F50431_41, 30
    .equ.HT32F61052, 26

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
                  .if (USE_HT32_CHIP==HT32F50442_52)
                    .long  COMP_IRQHandler                    /*  07, 23, 0x05C,                            */
                  .else
                    .long  _RESERVED                          /*  07, 23, 0x05C,                            */
                  .endif
                    .long  ADC_IRQHandler                     /*  08, 24, 0x060,                            */
                    .long  _RESERVED                          /*  09, 25, 0x064,                            */
                    .long  MCTM0_IRQHandler                   /*  10, 26, 0x068,                            */
                    .long  _RESERVED                          /*  11, 27, 0x06C,                            */
                    .long  GPTM0_IRQHandler                   /*  12, 28, 0x070,                            */
                    .long  _RESERVED                          /*  13, 29, 0x074,                            */
                    .long  _RESERVED                          /*  14, 30, 0x078,                            */
                    .long  PWM0_IRQHandler                    /*  15, 31, 0x07C,                            */
                  .if (USE_HT32_CHIP==HT32F50442_52)
                    .long  PWM1_IRQHandler                    /*  16, 32, 0x080,                            */
                  .else
                    .long  _RESERVED                          /*  16, 32, 0x080,                            */
                  .endif
                    .long  BFTM0_IRQHandler                   /*  17, 33, 0x084,                            */
                    .long  BFTM1_IRQHandler                   /*  18, 34, 0x088,                            */
                    .long  I2C0_IRQHandler                    /*  19, 35, 0x08C,                            */
                    .long  I2C1_IRQHandler                    /*  20, 36, 0x090,                            */
                    .long  SPI0_IRQHandler                    /*  21, 37, 0x094,                            */
                    .long  SPI1_IRQHandler                    /*  22, 38, 0x098,                            */
                    .long  USART0_IRQHandler                  /*  23, 39, 0x09C,                            */
                  .if (USE_HT32_CHIP==HT32F50442_52)
                    .long  USART1_IRQHandler                  /*  24, 40, 0x0A0,                            */
                  .else
                    .long  _RESERVED                          /*  24, 40, 0x0A0,                            */
                  .endif
                    .long  UART0_IRQHandler                   /*  25, 41, 0x0A4,                            */
                    .long  UART1_IRQHandler                   /*  26, 42, 0x0A8,                            */
                    .long  _RESERVED                          /*  27, 43, 0x0AC,                            */
                    .long  _RESERVED                          /*  28, 44, 0x0B0,                            */
                    .long  LEDC_IRQHandler                    /*  29, 45, 0x0B4,                            */
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
    IRQ     COMP_IRQHandler
    IRQ     ADC_IRQHandler
    IRQ     MCTM0_IRQHandler
    IRQ     GPTM0_IRQHandler
    IRQ     PWM0_IRQHandler
    IRQ     PWM1_IRQHandler
    IRQ     BFTM0_IRQHandler
    IRQ     BFTM1_IRQHandler
    IRQ     I2C0_IRQHandler
    IRQ     I2C1_IRQHandler
    IRQ     SPI0_IRQHandler
    IRQ     SPI1_IRQHandler
    IRQ     USART0_IRQHandler
    IRQ     USART1_IRQHandler
    IRQ     UART0_IRQHandler
    IRQ     UART1_IRQHandler
    IRQ     LEDC_IRQHandler
    IRQ     PDMA_CH0_1_IRQHandler
    IRQ     PDMA_CH2_5_IRQHandler

    .end
