/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2010-12-21   onelife     Initial creation for EFM32
 * 2011-07-06   onelife     Modify to make use the start code in libraries
 * 2012-05-15   onelife     Modified to compatible with CMSIS v3
 */

/***************************************************************************//**
* @addtogroup cortex-m3
* @{
*******************************************************************************/
    .syntax unified
    .cpu    cortex-m3
    .fpu    softvfp
    .thumb

/* start address for the initialization values of the .data section.
defined in linker script */
    .word __etext
/* start address for the .data section. defined in linker script */
    .word __data_start__
/* end address for the .data section. defined in linker script */
    .word __data_end__
/* start address for the .bss section. defined in linker script */
    .word __bss_start__
/* end address for the .bss section. defined in linker script */
    .word __bss_end__

/***************************************************************************//**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval None
*******************************************************************************/
    .thumb
    .thumb_func
    .section    .cs3.init,"ax", %progbits
    .globl      _start
    .type       _start, %function
_start:
    /* Copy the data segment initializers from flash to SRAM */
    movs  r1, #0
    b  LoopCopyDataInit

CopyDataInit:
    ldr  r3, =__etext
    ldr  r3, [r3, r1]
    str  r3, [r0, r1]
    adds  r1, r1, #4

LoopCopyDataInit:
    ldr  r0, =__data_start__
    ldr  r3, =__data_end__
    adds  r2, r0, r1
    cmp  r2, r3
    bcc  CopyDataInit
    ldr  r2, =__bss_start__
    b  LoopFillZerobss

/* Zero fill the bss segment. */
FillZerobss:
    movs  r3, #0
    str  r3, [r2], #4

LoopFillZerobss:
    ldr  r3, = __bss_end__
    cmp  r2, r3
    bcc  FillZerobss
    /* Call the application's entry point.*/
    bl  main
    bx  lr
    .size _start, .-_start

/***************************************************************************//**
 * @}
*******************************************************************************/
