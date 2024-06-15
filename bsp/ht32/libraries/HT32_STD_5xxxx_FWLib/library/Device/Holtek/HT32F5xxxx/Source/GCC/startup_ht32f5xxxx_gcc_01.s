/*---------------------------------------------------------------------------------------------------------*/
/* Holtek Semiconductor Inc.                                                                               */
/*                                                                                                         */
/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
/* All rights reserved.                                                                                    */
/*                                                                                                         */
/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f5xxxx_gcc_01.s
;  Version          : $Rev:: 6953         $
;  Date             : $Date:: 2023-05-30 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

/*
;  Supported Device
;  ========================================
;   HT32F52220, HT32F52230
;   HT32F52231, HT32F52241
;   HT32F52331, HT32F52341
;   HT32F52342, HT32F52352
;   HT32F52243, HT32F52253
;   HT32F0008
;   HT32F52344, HT32F52354
;   HT32F0006
;   HT32F61352
;   HT50F32003
;   HT32F62030, HT32F62040, HT32F62050
;   HT32F67741
;   HT32F67232
;   HT32F67233
*/

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */
/*
;// <o>  HT32 Device
;//      <0=> By Project Asm Define
;//      <1=> HT32F52220/30
;//      <2=> HT32F52231/41
;//      <3=> HT32F52331/41
;//      <4=> HT32F52342/52
;//      <5=> HT32F52243/53
;//      <6=> HT32F0008
;//      <9=> HT32F52344/54
;//      <10=> HT32F0006
;//      <10=> HT32F61352
;//      <4=> HT50F32003
;//      <2=> HT32F67741
;//      <1=> HT32F67232
;//      <1=> HT32F67233
;//      <1=> HT32F62030
;//      <2=> HT32F62040
;//      <5=> HT32F62050
*/
    .equ    USE_HT32_CHIP_SET, 0

    .equ _HT32FWID, 0xFFFFFFFF
/*
    .equ _HT32FWID, 0x00052220
    .equ _HT32FWID, 0x00052230
    .equ _HT32FWID, 0x00052231
    .equ _HT32FWID, 0x00052241
    .equ _HT32FWID, 0x00052331
    .equ _HT32FWID, 0x00052341
    .equ _HT32FWID, 0x00052342
    .equ _HT32FWID, 0x00052352
    .equ _HT32FWID, 0x00052243
    .equ _HT32FWID, 0x00052253
    .equ _HT32FWID, 0x00000008
    .equ _HT32FWID, 0x00052344
    .equ _HT32FWID, 0x00052354
    .equ _HT32FWID, 0x00000006
    .equ _HT32FWID, 0x00061352
    .equ _HT32FWID, 0x00032003
    .equ _HT32FWID, 0x00062030
    .equ _HT32FWID, 0x00062040
    .equ _HT32FWID, 0x00062050
    .equ _HT32FWID, 0x00067741
    .equ _HT32FWID, 0x00067232
    .equ _HT32FWID, 0x00067233    
*/

    .equ HT32F52220_30, 1
    .equ HT32F52231_41, 2
    .equ HT32F52331_41, 3
    .equ HT32F52342_52, 4
    .equ HT32F52243_53, 5
    .equ HT32F0008,     6
    .equ HT32F52344_54, 9
    .equ HT32F0006,     10
    .equ HT32F61352,    10
    .equ HT50F32003,    4
    .equ HT32F62030,    1
    .equ HT32F62040,    2
    .equ HT32F62050,    5
    .equ HT32F67741,    2
    .equ HT32F67232,    1
    .equ HT32F67233,    1

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
                  .if (USE_HT32_CHIP==HT32F52220_30)
                    .long  _RESERVED                          /*  01, 17, 0x044,                            */
                  .else
                    .long  RTC_IRQHandler                     /*  01, 17, 0x044,                            */
                  .endif
                    .long  FLASH_IRQHandler                   /*  02, 18, 0x048,                            */
                    .long  EVWUP_IRQHandler                   /*  03, 19, 0x04C,                            */
                    .long  EXTI0_1_IRQHandler                 /*  04, 20, 0x050,                            */
                    .long  EXTI2_3_IRQHandler                 /*  05, 21, 0x054,                            */
                    .long  EXTI4_15_IRQHandler                /*  06, 22, 0x058,                            */
                  .if (USE_HT32_CHIP==HT32F52342_52) || (USE_HT32_CHIP==HT32F52344_54)
                    .long  COMP_IRQHandler                    /*  07, 23, 0x05C,                            */
                  .else
                    .long  _RESERVED                          /*  07, 23, 0x05C,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F0008)
                    .long  _RESERVED                          /*  08, 24, 0x060,                            */
                  .else
                    .long  ADC_IRQHandler                     /*  08, 24, 0x060,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52243_53)
                    .long  I2C2_IRQHandler                    /*  09, 25, 0x064,                            */
                  .else
                    .long  _RESERVED                          /*  09, 25, 0x064,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52220_30) || (USE_HT32_CHIP==HT32F0008) || (USE_HT32_CHIP==HT32F0006)
                    .long  _RESERVED                          /*  10, 26, 0x068,                            */
                  .else
                    .long  MCTM0_IRQHandler                   /*  10, 26, 0x068,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52342_52)
                    .long  GPTM1_IRQHandler                   /*  11, 27, 0x06C,                            */
                  .else
                    .long  _RESERVED                          /*  11, 27, 0x06C,                            */
                  .endif
                    .long  GPTM0_IRQHandler                   /*  12, 28, 0x070,                            */
                  .if (USE_HT32_CHIP==HT32F0008)
                    .long  _RESERVED                          /*  13, 29, 0x074,                            */
                    .long  _RESERVED                          /*  14, 30, 0x078,                            */
                  .else
                    .long  SCTM0_IRQHandler                   /*  13, 29, 0x074,                            */
                    .long  SCTM1_IRQHandler                   /*  14, 30, 0x078,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52231_41) || (USE_HT32_CHIP==HT32F52331_41) || (USE_HT32_CHIP==HT32F52243_53) || (USE_HT32_CHIP==HT32F0006)
                    .long  SCTM2_IRQHandler                   /*  15, 31, 0x07C,                            */
                    .long  SCTM3_IRQHandler                   /*  16, 32, 0x080,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F0008)
                    .long  PWM0_IRQHandler                    /*  15, 31, 0x07C,                            */
                    .long  PWM1_IRQHandler                    /*  16, 32, 0x080,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52220_30) || (USE_HT32_CHIP==HT32F52342_52) || (USE_HT32_CHIP==HT32F52344_54)
                    .long  _RESERVED                          /*  15, 31, 0x07C,                            */
                    .long  _RESERVED                          /*  16, 32, 0x080,                            */
                  .endif
                    .long  BFTM0_IRQHandler                   /*  17, 33, 0x084,                            */
                  .if (USE_HT32_CHIP==HT32F52220_30)
                    .long  _RESERVED                          /*  18, 34, 0x088,                            */
                  .else
                    .long  BFTM1_IRQHandler                   /*  18, 34, 0x088,                            */
                  .endif
                    .long  I2C0_IRQHandler                    /*  19, 35, 0x08C,                            */
                  .if (USE_HT32_CHIP==HT32F52220_30) || (USE_HT32_CHIP==HT32F0008) || (USE_HT32_CHIP==HT32F52344_54) || (USE_HT32_CHIP==HT32F0006)
                    .long  _RESERVED                          /*  20, 36, 0x090,                            */
                  .else
                    .long  I2C1_IRQHandler                    /*  20, 36, 0x090,                            */
                  .endif
                    .long  SPI0_IRQHandler                    /*  21, 37, 0x094,                            */
                  .if (USE_HT32_CHIP==HT32F52220_30) || (USE_HT32_CHIP==HT32F0008)
                    .long  _RESERVED                          /*  22, 38, 0x098,                            */
                  .else
                    .if (USE_HT32_CHIP==HT32F0006)
                      .long  QSPI_IRQHandler                  /*  22, 38, 0x098,                            */
                    .else
                      .long  SPI1_IRQHandler                  /*  22, 38, 0x098,                            */
                    .endif
                  .endif
                  .if (USE_HT32_CHIP==HT32F52344_54)
                    .long  _RESERVED                          /*  23, 39, 0x09C,                            */
                  .else
                    .long  USART0_IRQHandler                  /*  23, 39, 0x09C,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52342_52) || (USE_HT32_CHIP==HT32F52243_53)
                    .long  USART1_IRQHandler                  /*  24, 40, 0x0A0,                            */
                  .else
                    .long  _RESERVED                          /*  24, 40, 0x0A0,                            */
                  .endif
                    .long  UART0_IRQHandler                   /*  25, 41, 0x0A4,                            */
                  .if (USE_HT32_CHIP==HT32F52220_30) || (USE_HT32_CHIP==HT32F0008) || (USE_HT32_CHIP==HT32F0006)
                    .long  _RESERVED                          /*  26, 42, 0x0A8,                            */
                  .else
                    .long  UART1_IRQHandler                   /*  26, 42, 0x0A8,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52331_41) || (USE_HT32_CHIP==HT32F52342_52)
                    .long  SCI_IRQHandler                     /*  27, 43, 0x0AC,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52243_53)
                    .long  UART2_IRQHandler                   /*  27, 43, 0x0AC,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F0006)
                    .long  MIDI_IRQHandler                    /*  27, 43, 0x0AC,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F0008) || (USE_HT32_CHIP==HT32F52344_54)
                    .long  _RESERVED                          /*  27, 43, 0xAC,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52342_52) || (USE_HT32_CHIP==HT32F0006)
                    .long  I2S_IRQHandler                     /*  28, 44, 0x0B0,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52331_41) || (USE_HT32_CHIP==HT32F52344_54)
                    .long  _RESERVED                          /*  28, 44, 0x0B0,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52243_53)
                    .long  UART3_IRQHandler                   /*  28, 44, 0x0B0,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F0008)
                    .long  AES_IRQHandler                     /*  28, 44, 0x0B0,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52331_41) || (USE_HT32_CHIP==HT32F52342_52) || (USE_HT32_CHIP==HT32F0008) || (USE_HT32_CHIP==HT32F52344_54) || (USE_HT32_CHIP==HT32F0006)
                    .long  USB_IRQHandler                     /*  29, 45, 0x0B4,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52243_53)
                    .long  _RESERVED                          /*  29, 45, 0x0B4,                            */
                  .endif
                  .if (USE_HT32_CHIP==HT32F52342_52) || (USE_HT32_CHIP==HT32F52243_53) || (USE_HT32_CHIP==HT32F0008) || (USE_HT32_CHIP==HT32F52344_54) || (USE_HT32_CHIP==HT32F0006)
                    .long  PDMA_CH0_1_IRQHandler              /*  30, 46, 0x0B8,                            */
                    .long  PDMA_CH2_5_IRQHandler              /*  31, 47, 0x0BC,                            */
                  .endif

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
    IRQ     COMP_IRQHandler
    IRQ     ADC_IRQHandler
    IRQ     MCTM0_IRQHandler
    IRQ     GPTM1_IRQHandler
    IRQ     GPTM0_IRQHandler
    IRQ     SCTM0_IRQHandler
    IRQ     SCTM1_IRQHandler
    IRQ     SCTM2_IRQHandler
    IRQ     SCTM3_IRQHandler
    IRQ     PWM0_IRQHandler
    IRQ     PWM1_IRQHandler
    IRQ     BFTM0_IRQHandler
    IRQ     BFTM1_IRQHandler
    IRQ     I2C0_IRQHandler
    IRQ     I2C1_IRQHandler
    IRQ     I2C2_IRQHandler
    IRQ     SPI0_IRQHandler
    IRQ     SPI1_IRQHandler
    IRQ     QSPI_IRQHandler
    IRQ     USART0_IRQHandler
    IRQ     USART1_IRQHandler
    IRQ     UART0_IRQHandler
    IRQ     UART1_IRQHandler
    IRQ     UART2_IRQHandler
    IRQ     UART3_IRQHandler
    IRQ     SCI_IRQHandler
    IRQ     MIDI_IRQHandler
    IRQ     I2S_IRQHandler
    IRQ     AES_IRQHandler
    IRQ     USB_IRQHandler
    IRQ     PDMA_CH0_1_IRQHandler
    IRQ     PDMA_CH2_5_IRQHandler

    .end
