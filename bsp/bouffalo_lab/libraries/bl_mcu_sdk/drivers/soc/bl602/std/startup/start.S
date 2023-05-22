/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
#include <arch/risc-v/csr.h>

/* This code executes before _start, which is contained inside the C library.
 * In embedded systems we want to ensure that _enter, which contains the first
 * code to be executed, can be loaded at a specific address.  To enable this
 * feature we provide the '.text.metal.init.enter' section, which is
 * defined to have the first address being where execution should start. */
    .section .init
    .global __start
    .type   __start, %function
__start:
    .cfi_startproc

    /* Inform the debugger that there is nowhere to backtrace past _enter. */
    .cfi_undefined ra

    /* The absolute first thing that must happen is configuring the global
     * pointer register, which must be done with relaxation disabled because
     * it's not valid to obtain the address of any symbol without GP
     * configured.  The C environment might go ahead and do this again, but
     * that's safe as it's a fixed register. */
.option push
.option norelax
    la gp, __global_pointer$
.option pop

    /* Disable global interrupt */
    csrci mstatus,8

    /* Set up a simple trap vector to catch anything that goes wrong early in
     * the boot process. */
    la t0, default_trap_handler
    # /* enable CLIC Vectored mode */
    ori	t0,t0,3
    csrw mtvec, t0
    /* enable chicken bit if core is bullet series*/
    la t0, __metal_chicken_bit
    beqz t0, 1f
    csrwi 0x7C1, 0
1:

    /* There may be pre-initialization routines inside the MBI code that run in
     * C, so here we set up a C environment.  First we set up a stack pointer,
     * which is left as a weak reference in order to allow initialization
     * routines that do not need a stack to be set up to transparently be
     * called. */
    .weak __StackTop
    la sp, __StackTop

    /* Intial the mtvt, MUST BE 64 bytes aligned*/
    .weak __Vectors
    la t0, __Vectors
    csrw mtvt, t0

#ifdef __riscv_float_abi_single
    /* deal with FP */
    /* Is F extension present? */
    csrr t0, misa
    andi t0, t0, (1 << ('F' - 'A'))
    beqz t0, 1f
    /* If so, enable it */
    li t0, MSTATUS_FS
    csrs mstatus, t0
    fssr x0
1:
#endif

    /* Check for an initialization routine and call it if one exists, otherwise
     * just skip over the call entirely.   Note that __metal_initialize isn't
     * actually a full C function, as it doesn't end up with the .bss or .data
     * segments having been initialized.  This is done to avoid putting a
     * burden on systems that can be initialized without having a C environment
     * set up. */
    jal SystemInit

    /* start load code to itcm like. */
    jal start_load

    call System_Post_Init

    /* At this point we can enter the C runtime's startup file.  The arguments
     * to this function are designed to match those provided to the SEE, just
     * so we don't have to write another ABI. */
    csrr a0, mhartid
    li a1, 0
    li a2, 0
    call entry

    csrci mstatus, (1 << 3)

__exit:
    j __exit

    .cfi_endproc
