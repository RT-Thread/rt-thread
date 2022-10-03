/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2021-06-29     Wayne        the first version
 * 
 * Description: Load the routine into SRAM0 0x28000000
 * 
 */

.section ".text.boot"
.global _start

_start:
    /* Give execution address for secondary CPU */
    adr     x20, .

    /*=============================================================*/
    /*      Read CPU id                                            */
    /*      Primary core(id=0): Help Secondary core leaving.       */
    /*      Secondary core(id>0): Notice 'Ready' to Primary core.  */
    /*=============================================================*/
    /* MPIDR_EL1: Multi-Processor Affinity Register */
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, .L__cpu_0_loop

.L__cpu_1_loop:
    /*=============================================================*/
    /*      Secondary CPU notification                             */
    /*=============================================================*/
    wfe                     /* Wait for Primary CPU's notification */

    mov     x0, #0x48              /* if (*(0x40460048)==PC)       */
    movk    x0, #0x4046, LSL #16   /*     goto L__cpu_1_loop       */
    ldr     x1, [x0]               /* else                         */
    cmp     x1, x20                /*     goto *(0x40460048)       */
    b.eq    .L__cpu_1_loop
    br      x1

.L__cpu_0_loop:
    /*=============================================================*/
    /*      Help CPU-1 to leave IBR.                               */
    /*=============================================================*/
    mov     x0, #0x48            /* *(0x40460048) = _start    */
    movk    x0, #0x4046, LSL #16
    mov     x1, x20
    str     w1, [x0]
    sev                          /* Wakeup Secondary CPU      */
    b       .L__cpu_0_loop

