;/**
; ******************************************************************************
;  @file  startup_hc32f448.S
;  @brief Startup for GCC.
; verbatim
;  Change Logs:
;  Date             Author          Notes
;  2023-05-31       CDT             First version
; endverbatim
; *****************************************************************************
; * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
; *
; * This software component is licensed by XHSC under BSD 3-Clause license
; * (the "License"); You may not use this file except in compliance with the
; * License. You may obtain a copy of the License at:
; *                    opensource.org/licenses/BSD-3-Clause
; *
; ******************************************************************************
; */

/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

                .syntax     unified
                .arch       armv7e-m
                .cpu        cortex-m4
                .fpu        softvfp
                .thumb

/*
;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>
*/
                .equ        Stack_Size, 0x00000C00

                .section    .stack
                .align      3
                .globl      __StackTop
                .globl      __StackLimit
__StackLimit:
                .space      Stack_Size
                .size       __StackLimit, . - __StackLimit
__StackTop:
                .size       __StackTop, . - __StackTop


/*
;<h> Heap Configuration
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>
*/
                .equ        Heap_Size, 0x00000400

                .if         Heap_Size != 0                     /* Heap is provided */
                .section    .heap
                .align      3
                .globl      __HeapBase
                .globl      __HeapLimit
__HeapBase:
                .space      Heap_Size
                .size       __HeapBase, . - __HeapBase
__HeapLimit:
                .size       __HeapLimit, . - __HeapLimit
                .endif

/*
;<h> Interrupt vector table start.
*/
                .section    .vectors, "a", %progbits
                .align      2
                .type       __Vectors, %object
                .globl      __Vectors
                .globl      __Vectors_End
                .globl      __Vectors_Size
__Vectors:
                .long       __StackTop                         /*     Top of Stack */
                .long       Reset_Handler                      /*     Reset Handler */
                .long       NMI_Handler                        /* -14 NMI Handler */
                .long       HardFault_Handler                  /* -13 Hard Fault Handler */
                .long       MemManage_Handler                  /* -12 MPU Fault Handler */
                .long       BusFault_Handler                   /* -11 Bus Fault Handler */
                .long       UsageFault_Handler                 /* -10 Usage Fault Handler */
                .long       0                                  /*     Reserved */
                .long       0                                  /*     Reserved */
                .long       0                                  /*     Reserved */
                .long       0                                  /*     Reserved */
                .long       SVC_Handler                        /*  -5 SVCall Handler */
                .long       DebugMon_Handler                   /*  -4 Debug Monitor Handler */
                .long       0                                  /*     Reserved */
                .long       PendSV_Handler                     /*  -2 PendSV Handler */
                .long       SysTick_Handler                    /*  -1 SysTick Handler */

                /* Interrupts */
                .long       IRQ000_Handler
                .long       IRQ001_Handler
                .long       IRQ002_Handler
                .long       IRQ003_Handler
                .long       IRQ004_Handler
                .long       IRQ005_Handler
                .long       IRQ006_Handler
                .long       IRQ007_Handler
                .long       IRQ008_Handler
                .long       IRQ009_Handler
                .long       IRQ010_Handler
                .long       IRQ011_Handler
                .long       IRQ012_Handler
                .long       IRQ013_Handler
                .long       IRQ014_Handler
                .long       IRQ015_Handler
                .long       EXTINT00_SWINT16_Handler
                .long       EXTINT01_SWINT17_Handler
                .long       EXTINT02_SWINT18_Handler
                .long       EXTINT03_SWINT19_Handler
                .long       EXTINT04_SWINT20_Handler
                .long       EXTINT05_SWINT21_Handler
                .long       EXTINT06_SWINT22_Handler
                .long       EXTINT07_SWINT23_Handler
                .long       EXTINT08_SWINT24_Handler
                .long       EXTINT09_SWINT25_Handler
                .long       EXTINT10_SWINT26_Handler
                .long       EXTINT11_SWINT27_Handler
                .long       EXTINT12_SWINT28_Handler
                .long       EXTINT13_SWINT29_Handler
                .long       EXTINT14_SWINT30_Handler
                .long       EXTINT15_SWINT31_Handler
                .long       DMA1_Error_Handler
                .long       DMA1_TC0_BTC0_Handler
                .long       DMA1_TC1_BTC1_Handler
                .long       DMA1_TC2_BTC2_Handler
                .long       DMA1_TC3_BTC3_Handler
                .long       DMA1_TC4_BTC4_Handler
                .long       DMA1_TC5_BTC5_Handler
                .long       EFM_PEError_ReadCol_Handler
                .long       EFM_OpEnd_Handler
                .long       QSPI_Handler
                .long       DCU1_Handler
                .long       DCU2_Handler
                .long       DCU3_Handler
                .long       DCU4_Handler
                .long       DMA2_Error_Handler
                .long       DMA2_TC0_BTC0_Handler
                .long       DMA2_TC1_BTC1_Handler
                .long       DMA2_TC2_BTC2_Handler
                .long       DMA2_TC3_BTC3_Handler
                .long       DMA2_TC4_BTC4_Handler
                .long       DMA2_TC5_BTC5_Handler
                .long       TMR0_1_Handler
                .long       TMR0_2_Handler
                .long       RTC_Handler
                .long       CLK_XtalStop_Handler
                .long       PWC_WKTM_Handler
                .long       SWDT_Handler
                .long       TMR6_1_GCmp_Handler
                .long       TMR6_1_Ovf_Udf_Handler
                .long       TMR6_1_Dte_Handler
                .long       TMR6_1_SCmp_Handler
                .long       TMRA_1_Ovf_Udf_Handler
                .long       TMRA_1_Cmp_Handler
                .long       TMR6_2_GCmp_Handler
                .long       TMR6_2_Ovf_Udf_Handler
                .long       TMR6_2_Dte_Handler
                .long       TMR6_2_SCmp_Handler
                .long       TMRA_2_Ovf_Udf_Handler
                .long       TMRA_2_Cmp_Handler
                .long       TMRA_3_Ovf_Udf_Handler
                .long       TMRA_3_Cmp_Handler
                .long       TMRA_4_Ovf_Udf_Handler
                .long       TMRA_4_Cmp_Handler
                .long       TMR4_1_GCmp_Handler
                .long       TMR4_1_Ovf_Udf_Handler
                .long       TMR4_1_Reload_Handler
                .long       TMR4_1_SCmp_Handler
                .long       TMR4_2_GCmp_Handler
                .long       TMR4_2_Ovf_Udf_Handler
                .long       TMR4_2_Reload_Handler
                .long       TMR4_2_SCmp_Handler
                .long       TMR4_3_GCmp_Handler
                .long       TMR4_3_Ovf_Udf_Handler
                .long       TMR4_3_Reload_Handler
                .long       TMR4_3_SCmp_Handler
                .long       I2C1_Handler
                .long       I2C2_Handler
                .long       CMP1_Handler
                .long       CMP2_Handler
                .long       CMP3_Handler
                .long       CMP4_Handler
                .long       USART1_Handler
                .long       USART1_TxComplete_Handler
                .long       USART2_Handler
                .long       USART2_TxComplete_Handler
                .long       SPI1_Handler
                .long       TMRA_5_Ovf_Udf_Handler
                .long       TMRA_5_Cmp_Handler
                .long       EVENT_PORT1_Handler
                .long       EVENT_PORT2_Handler
                .long       EVENT_PORT3_Handler
                .long       EVENT_PORT4_Handler
                .long       USART3_Handler
                .long       USART3_TxComplete_Handler
                .long       USART4_Handler
                .long       USART4_TxComplete_Handler
                .long       SPI2_Handler
                .long       SPI3_Handler
                .long       EMB_GR0_Handler
                .long       EMB_GR1_Handler
                .long       EMB_GR2_Handler
                .long       EMB_GR3_Handler
                .long       USART5_Handler
                .long       USART5_TxComplete_Handler
                .long       USART6_Handler
                .long       USART6_TxComplete_Handler
                .long       MCAN1_INT0_Handler
                .long       MCAN1_INT1_Handler
                .long       MCAN2_INT0_Handler
                .long       MCAN2_INT1_Handler
                .long       USART1_WKUP_Handler
                .long       PWC_LVD1_Handler
                .long       PWC_LVD2_Handler
                .long       FCM_Handler
                .long       WDT_Handler
                .long       CTC_Handler
                .long       ADC1_Handler
                .long       ADC2_Handler
                .long       ADC3_Handler
                .long       TRNG_Handler

__Vectors_End:
                .equ        __Vectors_Size, __Vectors_End - __Vectors
                .size       __Vectors, . - __Vectors
/*
;<h> Interrupt vector table end.
*/

/*
;<h> Reset handler start.
*/
                .section    .text.Reset_Handler
                .align      2
                .weak       Reset_Handler
                .type       Reset_Handler, %function
                .globl      Reset_Handler
Reset_Handler:
/* Single section scheme.
 *
 * The ranges of copy from/to are specified by following symbols
 *   __etext: LMA of start of the section to copy from. Usually end of text
 *   __data_start__: VMA of start of the section to copy to
 *   __data_end__: VMA of end of the section to copy to
 *
 * All addresses must be aligned to 4 bytes boundary.
 */
StackInit:
                ldr         r1, =__StackLimit
                ldr         r2, =__StackTop

                movs        r0, 0
StackInitLoop:
                cmp         r1, r2
                itt         lt
                strlt       r0, [r1], #4
                blt         StackInitLoop

ClrSramSR:
                ldr         r0, =0x40050810
                movw        r1, #0x1FF
                str         r1, [r0]

                /* Copy data from read only memory to RAM. */
CopyData:
                ldr         r1, =__etext
                ldr         r2, =__data_start__
                ldr         r3, =__data_end__
CopyLoop:
                cmp         r2, r3
                ittt        lt
                ldrlt       r0, [r1], #4
                strlt       r0, [r2], #4
                blt         CopyLoop

CopyData1:
                ldr         r1, =__etext_ramb
                ldr         r2, =__data_start_ramb__
                ldr         r3, =__data_end_ramb__
CopyLoop1:
                cmp         r2, r3
                ittt        lt
                ldrlt       r0, [r1], #4
                strlt       r0, [r2], #4
                blt         CopyLoop1

/* This part of work usually is done in C library startup code.
 * Otherwise, define this macro to enable it in this startup.
 *
 * There are two schemes too.
 * One can clear multiple BSS sections. Another can only clear one section.
 * The former is more size expensive than the latter.
 *
 * Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 * Otherwise define macro __STARTUP_CLEAR_BSS to choose the later.
 */
/* Single BSS section scheme.
 *
 * The BSS section is specified by following symbols
 *   __bss_start__: start of the BSS section.
 *   __bss_end__: end of the BSS section.
 *
 * Both addresses must be aligned to 4 bytes boundary.
 */
                /* Clear BSS section. */
ClearBss:
                ldr         r1, =__bss_start__
                ldr         r2, =__bss_end__

                movs        r0, 0
ClearLoop:
                cmp         r1, r2
                itt         lt
                strlt       r0, [r1], #4
                blt         ClearLoop

ClearBss1:
                ldr         r1, =__bss_start_ramb__
                ldr         r2, =__bss_end_ramb__

                movs        r0, 0
ClearLoop1:
                cmp         r1, r2
                itt         lt
                strlt       r0, [r1], #4
                blt         ClearLoop1

                /* Call the clock system initialization function. */
                bl          SystemInit
                /* Call the application's entry point. */
                bl          main
                bx          lr
                .size       Reset_Handler, . - Reset_Handler
/*
;<h> Reset handler end.
*/

/*
;<h> Default handler start.
*/
                .section    .text.Default_Handler, "ax", %progbits
                .align      2
Default_Handler:
                b           .
                .size       Default_Handler, . - Default_Handler
/*
;<h> Default handler end.
*/

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro      Set_Default_Handler  Handler_Name
                .weak       \Handler_Name
                .set        \Handler_Name, Default_Handler
                .endm

/* Default exception/interrupt handler */

                Set_Default_Handler    NMI_Handler
                Set_Default_Handler    HardFault_Handler
                Set_Default_Handler    MemManage_Handler
                Set_Default_Handler    BusFault_Handler
                Set_Default_Handler    UsageFault_Handler
                Set_Default_Handler    SVC_Handler
                Set_Default_Handler    DebugMon_Handler
                Set_Default_Handler    PendSV_Handler
                Set_Default_Handler    SysTick_Handler

                Set_Default_Handler    IRQ000_Handler
                Set_Default_Handler    IRQ001_Handler
                Set_Default_Handler    IRQ002_Handler
                Set_Default_Handler    IRQ003_Handler
                Set_Default_Handler    IRQ004_Handler
                Set_Default_Handler    IRQ005_Handler
                Set_Default_Handler    IRQ006_Handler
                Set_Default_Handler    IRQ007_Handler
                Set_Default_Handler    IRQ008_Handler
                Set_Default_Handler    IRQ009_Handler
                Set_Default_Handler    IRQ010_Handler
                Set_Default_Handler    IRQ011_Handler
                Set_Default_Handler    IRQ012_Handler
                Set_Default_Handler    IRQ013_Handler
                Set_Default_Handler    IRQ014_Handler
                Set_Default_Handler    IRQ015_Handler
                Set_Default_Handler    EXTINT00_SWINT16_Handler
                Set_Default_Handler    EXTINT01_SWINT17_Handler
                Set_Default_Handler    EXTINT02_SWINT18_Handler
                Set_Default_Handler    EXTINT03_SWINT19_Handler
                Set_Default_Handler    EXTINT04_SWINT20_Handler
                Set_Default_Handler    EXTINT05_SWINT21_Handler
                Set_Default_Handler    EXTINT06_SWINT22_Handler
                Set_Default_Handler    EXTINT07_SWINT23_Handler
                Set_Default_Handler    EXTINT08_SWINT24_Handler
                Set_Default_Handler    EXTINT09_SWINT25_Handler
                Set_Default_Handler    EXTINT10_SWINT26_Handler
                Set_Default_Handler    EXTINT11_SWINT27_Handler
                Set_Default_Handler    EXTINT12_SWINT28_Handler
                Set_Default_Handler    EXTINT13_SWINT29_Handler
                Set_Default_Handler    EXTINT14_SWINT30_Handler
                Set_Default_Handler    EXTINT15_SWINT31_Handler
                Set_Default_Handler    DMA1_Error_Handler
                Set_Default_Handler    DMA1_TC0_BTC0_Handler
                Set_Default_Handler    DMA1_TC1_BTC1_Handler
                Set_Default_Handler    DMA1_TC2_BTC2_Handler
                Set_Default_Handler    DMA1_TC3_BTC3_Handler
                Set_Default_Handler    DMA1_TC4_BTC4_Handler
                Set_Default_Handler    DMA1_TC5_BTC5_Handler
                Set_Default_Handler    EFM_PEError_ReadCol_Handler
                Set_Default_Handler    EFM_OpEnd_Handler
                Set_Default_Handler    QSPI_Handler
                Set_Default_Handler    DCU1_Handler
                Set_Default_Handler    DCU2_Handler
                Set_Default_Handler    DCU3_Handler
                Set_Default_Handler    DCU4_Handler
                Set_Default_Handler    DMA2_Error_Handler
                Set_Default_Handler    DMA2_TC0_BTC0_Handler
                Set_Default_Handler    DMA2_TC1_BTC1_Handler
                Set_Default_Handler    DMA2_TC2_BTC2_Handler
                Set_Default_Handler    DMA2_TC3_BTC3_Handler
                Set_Default_Handler    DMA2_TC4_BTC4_Handler
                Set_Default_Handler    DMA2_TC5_BTC5_Handler
                Set_Default_Handler    TMR0_1_Handler
                Set_Default_Handler    TMR0_2_Handler
                Set_Default_Handler    RTC_Handler
                Set_Default_Handler    CLK_XtalStop_Handler
                Set_Default_Handler    PWC_WKTM_Handler
                Set_Default_Handler    SWDT_Handler
                Set_Default_Handler    TMR6_1_GCmp_Handler
                Set_Default_Handler    TMR6_1_Ovf_Udf_Handler
                Set_Default_Handler    TMR6_1_Dte_Handler
                Set_Default_Handler    TMR6_1_SCmp_Handler
                Set_Default_Handler    TMRA_1_Ovf_Udf_Handler
                Set_Default_Handler    TMRA_1_Cmp_Handler
                Set_Default_Handler    TMR6_2_GCmp_Handler
                Set_Default_Handler    TMR6_2_Ovf_Udf_Handler
                Set_Default_Handler    TMR6_2_Dte_Handler
                Set_Default_Handler    TMR6_2_SCmp_Handler
                Set_Default_Handler    TMRA_2_Ovf_Udf_Handler
                Set_Default_Handler    TMRA_2_Cmp_Handler
                Set_Default_Handler    TMRA_3_Ovf_Udf_Handler
                Set_Default_Handler    TMRA_3_Cmp_Handler
                Set_Default_Handler    TMRA_4_Ovf_Udf_Handler
                Set_Default_Handler    TMRA_4_Cmp_Handler
                Set_Default_Handler    TMR4_1_GCmp_Handler
                Set_Default_Handler    TMR4_1_Ovf_Udf_Handler
                Set_Default_Handler    TMR4_1_Reload_Handler
                Set_Default_Handler    TMR4_1_SCmp_Handler
                Set_Default_Handler    TMR4_2_GCmp_Handler
                Set_Default_Handler    TMR4_2_Ovf_Udf_Handler
                Set_Default_Handler    TMR4_2_Reload_Handler
                Set_Default_Handler    TMR4_2_SCmp_Handler
                Set_Default_Handler    TMR4_3_GCmp_Handler
                Set_Default_Handler    TMR4_3_Ovf_Udf_Handler
                Set_Default_Handler    TMR4_3_Reload_Handler
                Set_Default_Handler    TMR4_3_SCmp_Handler
                Set_Default_Handler    I2C1_Handler
                Set_Default_Handler    I2C2_Handler
                Set_Default_Handler    CMP1_Handler
                Set_Default_Handler    CMP2_Handler
                Set_Default_Handler    CMP3_Handler
                Set_Default_Handler    CMP4_Handler
                Set_Default_Handler    USART1_Handler
                Set_Default_Handler    USART1_TxComplete_Handler
                Set_Default_Handler    USART2_Handler
                Set_Default_Handler    USART2_TxComplete_Handler
                Set_Default_Handler    SPI1_Handler
                Set_Default_Handler    TMRA_5_Ovf_Udf_Handler
                Set_Default_Handler    TMRA_5_Cmp_Handler
                Set_Default_Handler    EVENT_PORT1_Handler
                Set_Default_Handler    EVENT_PORT2_Handler
                Set_Default_Handler    EVENT_PORT3_Handler
                Set_Default_Handler    EVENT_PORT4_Handler
                Set_Default_Handler    USART3_Handler
                Set_Default_Handler    USART3_TxComplete_Handler
                Set_Default_Handler    USART4_Handler
                Set_Default_Handler    USART4_TxComplete_Handler
                Set_Default_Handler    SPI2_Handler
                Set_Default_Handler    SPI3_Handler
                Set_Default_Handler    EMB_GR0_Handler
                Set_Default_Handler    EMB_GR1_Handler
                Set_Default_Handler    EMB_GR2_Handler
                Set_Default_Handler    EMB_GR3_Handler
                Set_Default_Handler    USART5_Handler
                Set_Default_Handler    USART5_TxComplete_Handler
                Set_Default_Handler    USART6_Handler
                Set_Default_Handler    USART6_TxComplete_Handler
                Set_Default_Handler    MCAN1_INT0_Handler
                Set_Default_Handler    MCAN1_INT1_Handler
                Set_Default_Handler    MCAN2_INT0_Handler
                Set_Default_Handler    MCAN2_INT1_Handler
                Set_Default_Handler    USART1_WKUP_Handler
                Set_Default_Handler    PWC_LVD1_Handler
                Set_Default_Handler    PWC_LVD2_Handler
                Set_Default_Handler    FCM_Handler
                Set_Default_Handler    WDT_Handler
                Set_Default_Handler    CTC_Handler
                Set_Default_Handler    ADC1_Handler
                Set_Default_Handler    ADC2_Handler
                Set_Default_Handler    ADC3_Handler
                Set_Default_Handler    TRNG_Handler

                .end
