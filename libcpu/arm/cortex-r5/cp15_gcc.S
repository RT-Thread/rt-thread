/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

.globl rt_cpu_vector_set_base
rt_cpu_vector_set_base:
    /* clear SCTRL.V to customize the vector address */
    mrc     p15, 0, r0, c1, c0, 0
    bic     r0, #(1 << 13)
    mcr     p15, 0, r0, c1, c0, 0
    /* set up the vector address */
    dsb
    bx      lr
