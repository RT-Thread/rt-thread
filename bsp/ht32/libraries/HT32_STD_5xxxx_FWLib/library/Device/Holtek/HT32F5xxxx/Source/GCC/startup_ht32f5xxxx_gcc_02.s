/*---------------------------------------------------------------------------------------------------------*/
/* Holtek Semiconductor Inc.                                                                               */
/*                                                                                                         */
/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
/* All rights reserved.                                                                                    */
/*                                                                                                         */
/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f5xxxx_gcc_02.s
;  Version          : $Rev:: 7119         $
;  Date             : $Date:: 2023-08-15 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

/*
;  Supported Device
;  ========================================
;   HT32F50220, HT32F50230
;   HT32F50231, HT32F50241
;   HT50F32002
;   HT32F59041
;   HF5032
;   HT32F61641
;   HT32F59046
;   HT32F61041
*/

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */
/*
;// <o>  HT32 Device
;//      <0=> By Project Asm Define
;//      <7=> HT32F50220/30
;//      <8=> HT32F50231/41
;//      <7=> HT50F32002
;//      <8=> HT32F59041
;//      <7=> HF5032
;//      <8=> HT32F61641
;//      <8=> HT32F59046
;//      <8=> HT32F61041
*/
    .equ    USE_HT32_CHIP_SET, 0

    .equ _HT32FWID, 0xFFFFFFFF
/*
    .equ _HT32FWID, 0x00050220
    .equ _HT32FWID, 0x00050230
    .equ _HT32FWID, 0x00050231
    .equ _HT32FWID, 0x00050241
    .equ _HT32FWID, 0x00032002
    .equ _HT32FWID, 0x00059041
    .equ _HT32FWID, 0x000F5032
    .equ _HT32FWID, 0x00061641
    .equ _HT32FWID, 0x00059046
    .equ _HT32FWID, 0x00061041
*/

    .equ HT32F50220_30, 7
    .equ HT32F50231_41, 8
    .equ HT50F32002, 7
    .equ HT32F59041, 8
    .equ HF5032, 7
    .equ HT32F61641, 8
    .equ HT32F59046, 8
    .equ HT32F61041, 8

  .if USE_HT32_CHIP_SET == 0
  .else
    .equ USE_HT32_CHIP, USE_HT32_CHIP_SET
  .endif

  .syntax unified
  .cpu cortex-m0plus
  .fpu softvfp
  .thumb

/* start address for the initialization values of the .data section. defined in linker script               */
.word  _sidata

/* start address for the .data section. defined in linker script                                            */
.word  _sdata

/* end address for the .data section. defined in linker script                                              */
.word  _edata

/* start address for the .bss section. defined in linker script                                             */
.word  _sbss

/* end address for the .bss section. defined in linker script                                               */
.word  _ebss


/*
; Amount of memory (in bytes) allocated for Stack and Heap
; Tailor those values to your application needs
;//   <o> Stack Size (in Bytes, must 8 byte aligned) <:8>
*/
    .equ    Stack_Size, 512
    .section ".stack", "w"
    .align  3
    .globl  __StackTop
    .globl  __StackLimit
    .globl  __HT_check_sp
__HT_check_sp:
__StackLimit:
    .if     Stack_Size
    .space  Stack_Size
    .endif
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

/*
;//   <o>  Heap Size (in Bytes) <:8>
*/
    .equ    Heap_Size, 0
    .section ".heap", "w"
    .align  3
    .globl  __HeapBase
    .globl  _end
    .globl  __HeapLimit
    .globl  __HT_check_heap
__HT_check_heap:
__HeapBase:
_end:
    .if     Heap_Size
    .space  Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

    .equ    _RESERVED, 0xFFFFFFFF
/*
;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;********************************************************************************/
                    .section  .isr_vector,"a",%progbits
                    .global  __interrupt_vector_cortex_m
                    .type  __interrupt_vector_cortex_m, %object
__interrupt_vector_cortex_m:
                    .long  __StackTop                         /* ---, 00, 0x000, Top address of Stack       */
                    .long  Reset_Handler                      /* ---, 01, 0x004, Reset Handler              */
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
                    .long  _RESERVED                          /*  07, 23, 0x05C,                            */
                    .long  ADC_IRQHandler                     /*  08, 24, 0x060,                            */
                    .long  _RESERVED                          /*  09, 25, 0x064,                            */
                  .if (USE_HT32_CHIP==HT32F50220_30)
                    .long  _RESERVED                          /*  10, 26, 0x068,                            */
                  .else
                    .long  MCTM0_IRQHandler                   /*  10, 26, 0x068,                            */
                  .endif
                    .long  _RESERVED                          /*  11, 27, 0x06C,                            */
                    .long  GPTM0_IRQHandler                   /*  12, 28, 0x070,                            */
                    .long  _RESERVED                          /*  13, 29, 0x074,                            */
                    .long  _RESERVED                          /*  14, 30, 0x078,                            */
                    .long  PWM0_IRQHandler                    /*  15, 31, 0x07C,                            */
                    .long  PWM1_IRQHandler                    /*  16, 32, 0x080,                            */
                    .long  BFTM0_IRQHandler                   /*  17, 33, 0x084,                            */
                  .if (USE_HT32_CHIP==HT32F50220_30)
                    .long  _RESERVED                          /*  18, 34, 0x088,                            */
                  .else
                    .long  BFTM1_IRQHandler                   /*  18, 34, 0x088,                            */
                  .endif
                    .long  I2C0_IRQHandler                    /*  19, 35, 0x08C,                            */
                  .if (USE_HT32_CHIP==HT32F50220_30)
                    .long  _RESERVED                          /*  20, 36, 0x090,                            */
                  .else
                    .long  I2C1_IRQHandler                    /*  20, 36, 0x090,                            */
                  .endif
                    .long  SPI0_IRQHandler                    /*  21, 37, 0x094,                            */
                    .long  SPI1_IRQHandler                    /*  22, 38, 0x098,                            */
                  .if (USE_HT32_CHIP==HT32F50220_30)
                    .long  _RESERVED                          /*  23, 39, 0x09C,                            */
                  .else
                    .long  USART0_IRQHandler                  /*  23, 39, 0x09C,                            */
                  .endif
                    .long  _RESERVED                          /*  24, 40, 0x0A0,                            */
                    .long  UART0_IRQHandler                   /*  25, 41, 0x0A4,                            */
                    .long  UART1_IRQHandler                   /*  26, 42, 0x0A8,                            */

    .size   __interrupt_vector_cortex_m, . - __interrupt_vector_cortex_m


    .thumb


/* Reset Handler */

    .section .text.Reset_Handler
    .weak  Reset_Handler
    .type  Reset_Handler, %function
Reset_Handler:
                    LDR     R0, =__StackTop      /* set stack pointer */
                    MOV     SP, R0
                    LDR     R0, =BootProcess
                    BLX     R0
                    LDR     R0, =SystemInit
                    BLX     R0

                    /* Copy the data segment initializers from flash to SRAM */
                    MOVS    R1, #0
                    B       LoopCopyDataInit

CopyDataInit:
                    LDR     R3, =_sidata
                    LDR     R3, [R3, R1]
                    STR     R3, [R0, R1]
                    ADDS    R1, R1, #4

LoopCopyDataInit:
                    LDR     R0, =_sdata
                    LDR     R3, =_edata
                    ADDS    R2, R0, R1
                    CMP     R2, R3
                    BCC     CopyDataInit
                    LDR     R2, =_sbss
                    B       LoopFillZerobss

/* Zero fill the bss segment. */
FillZerobss:
                    MOVS    R3, #0
                    STR     R3, [R2]
                    ADDS    R2, R2, #4

LoopFillZerobss:
                    LDR     R3, =_ebss
                    CMP     R2, R3
                    BCC     FillZerobss

                    /* Call static constructors */
                    BL      __libc_init_array

                    /* Call the application's entry point.*/
                    BL      main

LoopForever:
                    B LoopForever

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
                    LSLS    R1, R1, #4
                    LSRS    R1, R1, #20
                    CMP     R1, #0
                    BEQ     BP3
                    CMP     R1, #5
                    BEQ     BP3
                    CMP     R1, #6
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
    IRQ     UART0_IRQHandler
    IRQ     UART1_IRQHandler

    .end
