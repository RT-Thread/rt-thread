/*---------------------------------------------------------------------------------------------------------*/
/* Holtek Semiconductor Inc.                                                                               */
/*                                                                                                         */
/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
/* All rights reserved.                                                                                    */
/*                                                                                                         */
/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f5xxxx_es_16.s
;  Version          : $Rev:: 7094         $
;  Date             : $Date:: 2023-08-02 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

/*
;  Supported Device
;  ========================================
;   HT32F66242
;   HT32F66246
*/

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */
/*




*/
    .equ    USE_HT32_CHIP_SET, 0

/*
    .equ _HT32FWID, 0xFFFFFFFF
    .equ _HT32FWID, 0x00066246
*/

    .equ HT32F66246, 31
    .equ HT32F66242, 33

  .if USE_HT32_CHIP_SET == 0
  .else
    .equ USE_HT32_CHIP, USE_HT32_CHIP_SET
  .endif

  .if USE_HT32_CHIP == 0
    .equ _HT32FWID, 0x00066246
  .endif
  .if USE_HT32_CHIP == HT32F66246
    .equ _HT32FWID, 0x00066246
  .endif
  .if USE_HT32_CHIP == HT32F66242
    .equ _HT32FWID, 0x00066242
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
                  .if (USE_HT32_CHIP==HT32F66246)
                    .long  CAN0_IRQHandler                    /*  07, 23, 0x05C,                            */
                  .else
                    .long  _RESERVED                          /*  07, 23, 0x05C,                            */
                  .endif
                    .long  ADC_IRQHandler                     /*  08, 24, 0x060,                            */
                    .long  CORDIC_IRQHandler                  /*  09, 25, 0x064,                            */
                    .long  MCTM0_BRK_IRQHandler               /*  10, 26, 0x068,                            */
                    .long  MCTM0_UP_IRQHandler                /*  11, 27, 0x06C,                            */
                    .long  MCTM0_TR_UP2_IRQHandler            /*  12, 28, 0x070,                            */
                    .long  MCTM0_CC_IRQHandler                /*  13, 29, 0x074,                            */
                    .long  GPTM0_G_IRQHandler                 /*  14, 30, 0x078,                            */
                    .long  GPTM0_VCLK_IRQHandler              /*  15, 31, 0x07C,                            */
                    .long  BFTM0_IRQHandler                   /*  16, 32, 0x080,                            */
                    .long  BFTM1_IRQHandler                   /*  17, 33, 0x084,                            */
                    .long  CMP0_IRQHandler                    /*  18, 34, 0x088,                            */
                    .long  CMP1_IRQHandler                    /*  19, 35, 0x08C,                            */
                    .long  PID_IRQHandler                     /*  20, 36, 0x090,                            */
                    .long  I2C0_IRQHandler                    /*  21, 37, 0x094,                            */
                    .long  SPI0_IRQHandler                    /*  22, 38, 0x098,                            */
                    .long  USART0_IRQHandler                  /*  23, 39, 0x09C,                            */
                    .long  UART0_IRQHandler                   /*  24, 40, 0x0A0,                            */
                    .long  PDMA_CH0_1_IRQHandler              /*  25, 41, 0x0A4,                            */
                    .long  PDMA_CH2_3_IRQHandler              /*  26, 42, 0x0A8,                            */
                    .long  PDMA_CH4_5_IRQHandler              /*  27, 43, 0x0AC,                            */
                    .long  SCTM0_IRQHandler                   /*  28, 44, 0x0B0,                            */
                    .long  SCTM1_IRQHandler                   /*  29, 45, 0x0B4,                            */
                    .long  SCTM2_IRQHandler                   /*  30, 46, 0x0B8,                            */
                    .long  SCTM3_IRQHandler                   /*  31, 47, 0x0BC,                            */



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
    IRQ     CAN0_IRQHandler
    IRQ     ADC_IRQHandler
    IRQ     CORDIC_IRQHandler
    IRQ     MCTM0_BRK_IRQHandler
    IRQ     MCTM0_UP_IRQHandler
    IRQ     MCTM0_TR_UP2_IRQHandler
    IRQ     MCTM0_CC_IRQHandler
    IRQ     GPTM0_G_IRQHandler
    IRQ     GPTM0_VCLK_IRQHandler
    IRQ     BFTM0_IRQHandler
    IRQ     BFTM1_IRQHandler
    IRQ     CMP0_IRQHandler
    IRQ     CMP1_IRQHandler
    IRQ     PID_IRQHandler
    IRQ     I2C0_IRQHandler
    IRQ     SPI0_IRQHandler
    IRQ     USART0_IRQHandler
    IRQ     UART0_IRQHandler
    IRQ     PDMA_CH0_1_IRQHandler
    IRQ     PDMA_CH2_3_IRQHandler
    IRQ     PDMA_CH4_5_IRQHandler
    IRQ     SCTM0_IRQHandler
    IRQ     SCTM1_IRQHandler
    IRQ     SCTM2_IRQHandler
    IRQ     SCTM3_IRQHandler

    .end
