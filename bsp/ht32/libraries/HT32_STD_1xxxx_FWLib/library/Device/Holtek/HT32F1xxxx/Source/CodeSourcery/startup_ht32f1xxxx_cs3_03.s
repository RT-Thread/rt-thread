/*---------------------------------------------------------------------------------------------------------*/
/* Holtek Semiconductor Inc.                                                                               */
/*                                                                                                         */
/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
/* All rights reserved.                                                                                    */
/*                                                                                                         */
/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f1xxxx_cs3_03.s
;  Version          : $Rev:: 1771         $
;  Date             : $Date:: 2019-07-25 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

/*
;  Supported Device
;  ========================================
;   HT32F12364
*/

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */
/*
;// <o>  HT32 Device
;//      <0=> By Project Asm Define
;//      <16=> HT32F12364
*/
    .equ    USE_HT32_CHIP_SET, 0

    .equ _HT32FWID, 0xFFFFFFFF
/*
    .equ _HT32FWID, 0x00012364
*/

    .equ HT32F12364, 16

  .if USE_HT32_CHIP_SET == 0
  .else
    .equ USE_HT32_CHIP, USE_HT32_CHIP_SET
  .endif

/*
; Amount of memory (in bytes) allocated for Stack and Heap
; Tailor those values to your application needs
;//   <o> Stack Size (in Bytes, must 8 byte aligned) <:8>
*/
    .equ    Stack_Size, 512
    .section ".stack", "w"
    .align  3
    .globl  __cs3_stack_mem
    .globl  __cs3_stack
    .globl  __cs3_stack_size
    .globl  __HT_check_sp
__HT_check_sp:
__cs3_stack_mem:
    .if     Stack_Size
    .space  Stack_Size
    .endif
__cs3_stack:
    .size   __cs3_stack_mem,  . - __cs3_stack_mem
    .set    __cs3_stack_size, . - __cs3_stack_mem

/*
;//   <o>  Heap Size (in Bytes) <:8>
*/
    .equ    Heap_Size, 0
    .section ".heap", "w"
    .align  3
    .globl  __cs3_heap_start
    .globl  __cs3_heap_end
    .globl  __HT_check_heap
__HT_check_heap:
__cs3_heap_start:
    .if     Heap_Size
    .space  Heap_Size
    .endif
__cs3_heap_end:

    .equ    _RESERVED, 0xFFFFFFFF
/*
;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;********************************************************************************/
                    .section ".cs3.interrupt_vector"
                    .globl  __cs3_interrupt_vector_cortex_m
                    .type   __cs3_interrupt_vector_cortex_m, %object
__cs3_interrupt_vector_cortex_m:
                    .long  __cs3_stack                        /* ---, 00, 0x000, Top address of Stack       */
                    .long  __cs3_reset                        /* ---, 01, 0x004, Reset Handler              */
                    .long  NMI_Handler                        /* ---, 02, 0x008, NMI Handler                */
                    .long  HardFault_Handler                  /* ---, 03, 0x00C, Hard Fault Handler         */
                    .long  MemManage_Handler                  /* ---, 04, 0x010, MPU Fault Handler          */
                    .long  BusFault_Handler                   /* ---, 05, 0x014, Bus Fault Handler          */
                    .long  UsageFault_Handler                 /* ---, 06, 0x018, Usage Fault Handler        */
                    .long  _RESERVED                          /* ---, 07, 0x01C, Reserved                   */
                    .long  _HT32FWID                          /* ---, 08, 0x020, Reserved                   */
                    .long  _RESERVED                          /* ---, 09, 0x024, Reserved                   */
                    .long  _RESERVED                          /* ---, 10, 0x028, Reserved                   */
                    .long  SVC_Handler                        /* ---, 11, 0x02C, SVC Handler                */
                    .long  DebugMon_Handler                   /* ---, 12, 0x030, Debug Monitor Handler      */
                    .long  _RESERVED                          /* ---, 13, 0x034, Reserved                   */
                    .long  PendSV_Handler                     /* ---, 14, 0x038, PendSV Handler             */
                    .long  SysTick_Handler                    /* ---, 15, 0x03C, SysTick Handler            */

                    /* External Interrupt Handler                                                           */
                    .long   CKRDY_IRQHandler                  /*  00, 16, 0x040,                            */
                    .long   LVD_IRQHandler                    /*  01, 17, 0x044,                            */
                    .long   BOD_IRQHandler                    /*  02, 18, 0x048,                            */
                    .long   _RESERVED                         /*  03, 19, 0x04C,                            */
                    .long   RTC_IRQHandler                    /*  04, 20, 0x050,                            */
                    .long   FLASH_IRQHandler                  /*  05, 21, 0x054,                            */
                    .long   EVWUP_IRQHandler                  /*  06, 22, 0x058,                            */
                    .long   LPWUP_IRQHandler                  /*  07, 23, 0x05C,                            */
                    .long   EXTI0_IRQHandler                  /*  08, 24, 0x060,                            */
                    .long   EXTI1_IRQHandler                  /*  09, 25, 0x064,                            */
                    .long   EXTI2_IRQHandler                  /*  10, 26, 0x068,                            */
                    .long   EXTI3_IRQHandler                  /*  11, 27, 0x06C,                            */
                    .long   EXTI4_IRQHandler                  /*  12, 28, 0x070,                            */
                    .long   EXTI5_IRQHandler                  /*  13, 29, 0x074,                            */
                    .long   EXTI6_IRQHandler                  /*  14, 30, 0x078,                            */
                    .long   EXTI7_IRQHandler                  /*  15, 31, 0x07C,                            */
                    .long   EXTI8_IRQHandler                  /*  16, 32, 0x080,                            */
                    .long   EXTI9_IRQHandler                  /*  17, 33, 0x084,                            */
                    .long   EXTI10_IRQHandler                 /*  18, 34, 0x088,                            */
                    .long   EXTI11_IRQHandler                 /*  19, 35, 0x08C,                            */
                    .long   EXTI12_IRQHandler                 /*  20, 36, 0x090,                            */
                    .long   EXTI13_IRQHandler                 /*  21, 37, 0x094,                            */
                    .long   EXTI14_IRQHandler                 /*  22, 38, 0x098,                            */
                    .long   EXTI15_IRQHandler                 /*  23, 39, 0x09C,                            */
                    .long   _RESERVED                         /*  24, 40, 0x0A0,                            */
                    .long   ADC_IRQHandler                    /*  25, 41, 0x0A4,                            */
                    .long   _RESERVED                         /*  26, 42, 0x0A8,                            */
                    .long   _RESERVED                         /*  27, 43, 0x0AC,                            */
                    .long   _RESERVED                         /*  28, 44, 0x0B0,                            */
                    .long   _RESERVED                         /*  29, 45, 0x0B4,                            */
                    .long   _RESERVED                         /*  30, 46, 0x0B8,                            */
                    .long   _RESERVED                         /*  31, 47, 0x0BC,                            */
                    .long   _RESERVED                         /*  32, 48, 0x0C0,                            */
                    .long   _RESERVED                         /*  33, 49, 0x0C4,                            */
                    .long   _RESERVED                         /*  34, 50, 0x0C8,                            */
                    .long   GPTM0_IRQHandler                  /*  35, 51, 0x0CC,                            */
                    .long   _RESERVED                         /*  36, 52, 0x0D0,                            */
                    .long   SCTM0_IRQHandler                  /*  37, 53, 0x0D4,                            */
                    .long   SCTM1_IRQHandler                  /*  38, 54, 0x0D8,                            */
                    .long   PWM0_IRQHandler                   /*  39, 55, 0x0DC,                            */
                    .long   _RESERVED                         /*  40, 56, 0x0E0,                            */
                    .long   BFTM0_IRQHandler                  /*  41, 57, 0x0E4,                            */
                    .long   BFTM1_IRQHandler                  /*  42, 58, 0x0E8,                            */
                    .long   I2C0_IRQHandler                   /*  43, 59, 0x0EC,                            */
                    .long   I2C1_IRQHandler                   /*  44, 60, 0x0F0,                            */
                    .long   SPI0_IRQHandler                   /*  45, 61, 0x0F4,                            */
                    .long   SPI1_IRQHandler                   /*  46, 62, 0x0F8,                            */
                    .long   USART0_IRQHandler                 /*  47, 63, 0x0FC,                            */
                    .long   _RESERVED                         /*  48, 64, 0x100,                            */
                    .long   UART0_IRQHandler                  /*  49, 65, 0x104,                            */
                    .long   UART1_IRQHandler                  /*  50, 66, 0x108,                            */
                    .long   SCI_IRQHandler                    /*  51, 67, 0x10C,                            */
                    .long   _RESERVED                         /*  52, 68, 0x110,                            */
                    .long   USB_IRQHandler                    /*  53, 69, 0x114,                            */
                    .long   _RESERVED                         /*  54, 70, 0x118,                            */
                    .long   PDMA_CH0_IRQHandler               /*  55, 71, 0x11C,                            */
                    .long   PDMA_CH1_IRQHandler               /*  56, 72, 0x120,                            */
                    .long   PDMA_CH2_IRQHandler               /*  57, 73, 0x124,                            */
                    .long   PDMA_CH3_IRQHandler               /*  58, 74, 0x128,                            */
                    .long   PDMA_CH4_IRQHandler               /*  59, 75, 0x12C,                            */
                    .long   PDMA_CH5_IRQHandler               /*  60, 76, 0x130,                            */
                    .long   _RESERVED                         /*  61, 77, 0x134,                            */
                    .long   _RESERVED                         /*  62, 78, 0x138,                            */
                    .long   _RESERVED                         /*  63, 79, 0x13C,                            */
                    .long   _RESERVED                         /*  64, 80, 0x140,                            */
                    .long   _RESERVED                         /*  65, 81, 0x144,                            */
                    .long   _RESERVED                         /*  66, 82, 0x148,                            */
                    .long   _RESERVED                         /*  67, 83, 0x14C,                            */
                    .long   _RESERVED                         /*  68, 84, 0x150,                            */
                    .long   AES_IRQHandler                    /*  69, 85, 0x154,                            */

    .size   __cs3_interrupt_vector_cortex_m, . - __cs3_interrupt_vector_cortex_m


    .thumb


/* Reset Handler */

    .section .cs3.reset,"x",%progbits
    .thumb_func
    .globl  __cs3_reset_cortex_m
    .type   __cs3_reset_cortex_m, %function
__cs3_reset_cortex_m:
    .fnstart
                    LDR     R0, =BootProcess
                    BLX     R0
                    LDR     R0, =SystemInit
                    BLX     R0
                    LDR     R0, =_start
                    BX      R0
    .thumb_func
BootProcess:
                    LDR     R0, =0x40080300
                    LDR     R1,[R0, #0x10]
                    CMP     R1, #0
                    BNE     BP1
                    LDR     R1,[R0, #0x14]
                    CMP     R1, #0
                    BNE     BP1
                    LDR     R1,[R0, #0x18]
                    CMP     R1, #0
                    BNE     BP1
                    LDR     R1,[R0, #0x1C]
                    CMP     R1, #0
                    BEQ     BP2
BP1:
                    LDR     R0, =0x40080180
                    LDR     R1,[R0, #0xC]
                    LSL     R1, R1, #4
                    LSR     R1, R1, #20
                    CMP     R1, #0
                    BEQ     BP3
                    CMP     R1, #1
                    BEQ     BP3
                    CMP     R1, #2
                    BEQ     BP3
BP2:
                    DSB
                    LDR     R0, =0x20000000
                    LDR     R1, =0x05fa0004
                    STR     R1, [R0]
                    LDR     R1, =0xe000ed00
                    LDR     R0, =0x05fa0004
                    STR     R0, [R1, #0xC]
                    DSB
                    B       .
BP3:
                    LDR     R0, =0x20000000
                    LDR     R1, [R0]
                    LDR     R0, =0x05fa0004
                    CMP     R0, R1
                    BEQ     BP4
                    BX      LR
BP4:
                    LDR     R0, =0x40088100
                    LDR     R1, =0x00000001
                    STR     R1, [R0]
                    LDR     R0, =0x20000000
                    LDR     R1, =0x0
                    STR     R1, [R0]
                    BX      LR
    .pool
    .cantunwind
    .fnend
    .size   __cs3_reset_cortex_m,.-__cs3_reset_cortex_m

    .section ".text"

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

    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
MemManage_Handler:
                    B       .
    .size   MemManage_Handler, . - MemManage_Handler

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler:
                    B       .
    .size   BusFault_Handler, . - BusFault_Handler

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:
                    B       .
    .size   UsageFault_Handler, . - UsageFault_Handler

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
                    B       .
    .size   SVC_Handler, . - SVC_Handler

    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
DebugMon_Handler:
                    B       .
    .size   DebugMon_Handler, . - DebugMon_Handler

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

    IRQ     CKRDY_IRQHandler
    IRQ     LVD_IRQHandler
    IRQ     BOD_IRQHandler
    IRQ     RTC_IRQHandler
    IRQ     FLASH_IRQHandler
    IRQ     EVWUP_IRQHandler
    IRQ     LPWUP_IRQHandler
    IRQ     EXTI0_IRQHandler
    IRQ     EXTI1_IRQHandler
    IRQ     EXTI2_IRQHandler
    IRQ     EXTI3_IRQHandler
    IRQ     EXTI4_IRQHandler
    IRQ     EXTI5_IRQHandler
    IRQ     EXTI6_IRQHandler
    IRQ     EXTI7_IRQHandler
    IRQ     EXTI8_IRQHandler
    IRQ     EXTI9_IRQHandler
    IRQ     EXTI10_IRQHandler
    IRQ     EXTI11_IRQHandler
    IRQ     EXTI12_IRQHandler
    IRQ     EXTI13_IRQHandler
    IRQ     EXTI14_IRQHandler
    IRQ     EXTI15_IRQHandler
    IRQ     ADC_IRQHandler
    IRQ     GPTM0_IRQHandler
    IRQ     SCTM0_IRQHandler
    IRQ     SCTM1_IRQHandler
    IRQ     PWM0_IRQHandler
    IRQ     BFTM0_IRQHandler
    IRQ     BFTM1_IRQHandler
    IRQ     I2C0_IRQHandler
    IRQ     I2C1_IRQHandler
    IRQ     SPI0_IRQHandler
    IRQ     SPI1_IRQHandler
    IRQ     USART0_IRQHandler
    IRQ     UART0_IRQHandler
    IRQ     UART1_IRQHandler
    IRQ     SCI_IRQHandler
    IRQ     USB_IRQHandler
    IRQ     PDMA_CH0_IRQHandler
    IRQ     PDMA_CH1_IRQHandler
    IRQ     PDMA_CH2_IRQHandler
    IRQ     PDMA_CH3_IRQHandler
    IRQ     PDMA_CH4_IRQHandler
    IRQ     PDMA_CH5_IRQHandler
    IRQ     AES_IRQHandler

    .end
