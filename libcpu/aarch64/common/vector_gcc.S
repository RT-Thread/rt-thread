/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei    the first version
 */
 
.text

.globl system_vectors
.globl vector_error
.globl vector_irq
.globl vector_fiq

system_vectors:
.align 11
    .set    VBAR, system_vectors
    .org    VBAR
    // Exception from CurrentEL (EL1) with SP_EL0 (SPSEL=1)
    .org (VBAR + 0x00 + 0)
    B vector_error      // 			Synchronous
    .org (VBAR + 0x80 + 0)
    B vector_irq        //          IRQ/vIRQ
    .org (VBAR + 0x100 + 0)
    B vector_fiq        //          FIQ/vFIQ
    .org (VBAR + 0x180 + 0)
    B vector_error      //          Error/vError

    // Exception from CurrentEL (EL1) with SP_ELn
    .org (VBAR + 0x200 + 0)
    B vector_error      // 			Synchronous
    .org (VBAR + 0x280 + 0)
    B vector_irq    	// 			IRQ/vIRQ
    .org (VBAR + 0x300 + 0)
    B vector_fiq        //          FIQ/vFIQ
    .org (VBAR + 0x380 + 0)
    B vector_error

    // Exception from lower EL, aarch64
    .org (VBAR + 0x400 + 0)
    B vector_error
    .org (VBAR + 0x480 + 0)
    B vector_error
    .org (VBAR + 0x500 + 0)
    B vector_error
    .org (VBAR + 0x580 + 0)
    B vector_error

    // Exception from lower EL, aarch32
    .org (VBAR + 0x600 + 0)
    B vector_error
    .org (VBAR + 0x680 + 0)
    B vector_error
    .org (VBAR + 0x700 + 0)
    B vector_error
    .org (VBAR + 0x780 + 0)
    B vector_error
    .org (VBAR + 0x800 + 0)
    B vector_error
