/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2020-01-15     bigmagic     the first version
 * 2020-08-10     SummerGift   support clang compiler
 * 2023-04-29     GuEe-GUI     support kernel's ARM64 boot header
 * 2024-01-18     Shell        fix implicit dependency of cpuid management
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include <mmu.h>
#include <rtconfig.h>

#define ARM64_IMAGE_FLAG_BE_SHIFT           0
#define ARM64_IMAGE_FLAG_PAGE_SIZE_SHIFT    (ARM64_IMAGE_FLAG_BE_SHIFT + 1)
#define ARM64_IMAGE_FLAG_PHYS_BASE_SHIFT    (ARM64_IMAGE_FLAG_PAGE_SIZE_SHIFT + 2)

#define ARM64_IMAGE_FLAG_LE                 0
#define ARM64_IMAGE_FLAG_BE                 1
#define ARM64_IMAGE_FLAG_PAGE_SIZE_4K       1
#define ARM64_IMAGE_FLAG_PAGE_SIZE_16K      2
#define ARM64_IMAGE_FLAG_PAGE_SIZE_64K      3
#define ARM64_IMAGE_FLAG_PHYS_BASE          1

#define _HEAD_FLAG(field)                   (_HEAD_FLAG_##field << ARM64_IMAGE_FLAG_##field##_SHIFT)

#ifdef ARCH_CPU_BIG_ENDIAN
#define _HEAD_FLAG_BE                       ARM64_IMAGE_FLAG_BE
#else
#define _HEAD_FLAG_BE                       ARM64_IMAGE_FLAG_LE
#endif
#define _HEAD_FLAG_PAGE_SIZE                ((ARCH_PAGE_SHIFT - 10) / 2)
#define _HEAD_FLAG_PHYS_BASE                1

#define _HEAD_FLAGS                         (_HEAD_FLAG(BE) | _HEAD_FLAG(PAGE_SIZE) | _HEAD_FLAG(PHYS_BASE))

.macro get_phy, reg, symbol
    adrp    \reg, \symbol
    add     \reg, \reg, #:lo12:\symbol
.endm

.macro get_pvoff, tmp, out
    ldr     \tmp, =.boot_cpu_stack_top
    get_phy \out, .boot_cpu_stack_top
    sub     \out, \out, \tmp
.endm

    .section ".text.entrypoint","ax"

#ifdef RT_USING_OFW
/*
 * Our goal is to boot the rt-thread as possible without modifying the
 * bootloader's config, so we use the kernel's boot header for ARM64:
 *   https://www.kernel.org/doc/html/latest/arm64/booting.html#call-the-kernel-image
 */
_head:
    b       _start          /* Executable code */
    .long   0               /* Executable code */
    .quad   _text_offset    /* Image load offset from start of RAM, little endian */
    .quad   _end - _head    /* Effective Image size, little endian (_end defined in link.lds) */
    .quad   _HEAD_FLAGS     /* Kernel flags, little endian */
    .quad   0               /* Reserved */
    .quad   0               /* Reserved */
    .quad   0               /* Reserved */
    .ascii  "ARM\x64"       /* Magic number */
    .long   0               /* Reserved (used for PE COFF offset) */
#endif /* RT_USING_OFW */

/* Variable registers: x21~x28 */
dtb_paddr .req x21
boot_arg0 .req x22
boot_arg1 .req x23
boot_arg2 .req x24
stack_top .req x25

    .global _start
_start:
/*
 * Boot CPU general-purpose register settings:
 *   x0 = physical address of device tree blob (dtb) in system RAM.
 *   x1 = 0 (reserved for future use)
 *   x2 = 0 (reserved for future use)
 *   x3 = 0 (reserved for future use)
 */
    mov     dtb_paddr, x0
    mov     boot_arg0, x1
    mov     boot_arg1, x2
    mov     boot_arg2, x3

    /* Save cpu stack */
    get_phy stack_top, .boot_cpu_stack_top
    /* Save cpu id temp */
#ifdef ARCH_USING_HW_THREAD_SELF
    msr     tpidrro_el0, xzr
    /* Save thread self */
#endif /* ARCH_USING_HW_THREAD_SELF */
    msr     tpidr_el1, xzr

    bl      init_cpu_el
    bl      init_kernel_bss
    bl      init_cpu_stack_early

#ifdef RT_USING_OFW
    /* Save devicetree info */
    mov     x0, dtb_paddr
    bl      rt_hw_fdt_install_early
#endif

    /* Now we are in the end of boot cpu process */
    ldr     x8, =rtthread_startup
    b       init_mmu_early
    /* never come back */

kernel_start:
    /* jump to the PE's system entry */
    mov     x29, xzr
    mov     x30, x8
    br      x8

cpu_idle:
    wfe
    b       cpu_idle

#ifdef RT_USING_SMP
    .globl _secondary_cpu_entry
_secondary_cpu_entry:
#ifdef RT_USING_OFW
    /* Read cpu id */
    mrs     x5, mpidr_el1
    ldr     x1, =rt_cpu_mpidr_table
    get_pvoff x4 x2
    add     x1, x1, x2
    mov     x2, #0
    ldr     x4, =0xff00ffffff
    and     x0, x5, x4

.cpu_id_confirm:
    add     x2, x2, #1              /* Next cpu id inc */
    ldr     x3, [x1], #8
    cmp     x3, #0
    beq     cpu_idle
    and     x3, x3, x4
    cmp     x3, x0
    bne     .cpu_id_confirm

    /* Save this mpidr */
    str     x5, [x1, #-8]

    /* Get cpu id success */
    sub     x0, x2, #1
#endif /* RT_USING_OFW */
    /* Save cpu id global */
    bl      rt_hw_cpu_id_set
    bl      rt_hw_cpu_id

    /* Set current cpu's stack top */
    sub     x0, x0, #1
    mov     x1, #ARCH_SECONDARY_CPU_STACK_SIZE
    get_phy x2, .secondary_cpu_stack_top
    msub    stack_top, x0, x1, x2

    bl      init_cpu_el
    bl      init_cpu_stack_early

    /* secondary cpu start to startup */
    ldr     x8, =rt_hw_secondary_cpu_bsp_start
    b       enable_mmu_early
#endif /* RT_USING_SMP */

init_cpu_el:
    mrs     x0, CurrentEL           /* CurrentEL Register. bit 2, 3. Others reserved */
    lsr     x0, x0, #2
    and     x0, x0, #3

    /* running at EL3? */
    cmp     x0, #3
    bne     .init_cpu_hyp

    /* should never be executed, just for completeness. (EL3) */
    mov     x1, #(1 << 0)           /* EL0 and EL1 are in Non-Secure state */
    orr     x1, x1, #(1 << 4)       /* RES1 */
    orr     x1, x1, #(1 << 5)       /* RES1 */
    /* bic  x1, x1, #(1 << 7)          disable Secure Monitor Call */
    orr     x1, x1, #(1 << 10)      /* The next lower level is AArch64 */
    msr     scr_el3, x1

    mov     x1, #9                  /* Next level is 0b1001->EL2h */
    orr     x1, x1, #(1 << 6)       /* Mask FIQ */
    orr     x1, x1, #(1 << 7)       /* Mask IRQ */
    orr     x1, x1, #(1 << 8)       /* Mask SError */
    orr     x1, x1, #(1 << 9)       /* Mask Debug Exception */
    msr     spsr_el3, x1

    get_phy x1, .init_cpu_hyp
    msr     elr_el3, x1
    eret

.init_cpu_hyp:
    /* running at EL2? */
    cmp     x0, #2                  /* EL2 = 0b10  */
    bne     .init_cpu_sys

    /* Enable CNTP for EL1 */
    mrs     x0, cnthctl_el2         /* Counter-timer Hypervisor Control register */
    orr     x0, x0, #(1 << 0)       /* Don't traps NS EL0/1 accesses to the physical counter */
    orr     x0, x0, #(1 << 1)       /* Don't traps NS EL0/1 accesses to the physical timer */
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr

    mov     x0, #(1 << 31)          /* Enable AArch64 in EL1 */
    orr     x0, x0, #(1 << 1)       /* SWIO hardwired */
    msr     hcr_el2, x0

    mov     x0, #5                  /* Next level is 0b0101->EL1h */
    orr     x0, x0, #(1 << 6)       /* Mask FIQ */
    orr     x0, x0, #(1 << 7)       /* Mask IRQ */
    orr     x0, x0, #(1 << 8)       /* Mask SError */
    orr     x0, x0, #(1 << 9)       /* Mask Debug Exception */
    msr     spsr_el2, x0

    get_phy x0, .init_cpu_sys
    msr     elr_el2, x0
    eret

.init_cpu_sys:
    mrs     x0, sctlr_el1
    bic     x0, x0, #(3 << 3)       /* Disable SP Alignment check */
    bic     x0, x0, #(1 << 1)       /* Disable Alignment check */
    msr     sctlr_el1, x0

    mrs     x0, cntkctl_el1
    orr     x0, x0, #(1 << 1)      /* Set EL0VCTEN, enabling the EL0 Virtual Count Timer */
    msr     cntkctl_el1, x0

    /* Avoid trap from SIMD or float point instruction */
    mov     x0, #0x00300000         /* Don't trap any SIMD/FP instructions in both EL0 and EL1 */
    msr     cpacr_el1, x0

    /* Applying context change */
    dsb     ish
    isb

    ret

init_kernel_bss:
    get_phy x1, __bss_start
    get_phy x2, __bss_end
    sub     x2, x2, x1              /* Get bss size */

    and     x3, x2, #7              /* x3 is < 7 */
    ldr     x4, =~0x7
    and     x2, x2, x4              /* Mask ~7 */

.clean_bss_loop_quad:
    cbz     x2, .clean_bss_loop_byte
    str     xzr, [x1], #8
    sub     x2, x2, #8
    b       .clean_bss_loop_quad

.clean_bss_loop_byte:
    cbz     x3, .clean_bss_end
    strb    wzr, [x1], #1
    sub     x3, x3, #1
    b       .clean_bss_loop_byte

.clean_bss_end:
    ret

init_cpu_stack_early:
    msr     spsel, #1
    mov     sp, stack_top

    ret

init_mmu_early:
    get_phy x0, .early_page_array
    bl      set_free_page

    get_phy x0, .early_tbl0_page
    get_phy x1, .early_tbl1_page

    get_pvoff x2 x3
    ldr     x2, =ARCH_EARLY_MAP_SIZE    /* Map 1G memory for kernel space */
    bl      rt_hw_mem_setup_early

    b       enable_mmu_early

enable_mmu_early:
    get_phy x0, .early_tbl0_page
    get_phy x1, .early_tbl1_page

    msr     ttbr0_el1, x0
    msr     ttbr1_el1, x1
    dsb     sy

    bl      mmu_tcr_init

    /*
     * OK, now, we don't use sp before jump to kernel, set sp to current cpu's
     * stack top to visual address
     */
    get_pvoff x1 x0
    mov     x1, stack_top
    sub     x1, x1, x0
    mov     sp, x1

    ldr     x30, =kernel_start      /* Set LR to kernel_start function, it's virtual addresses */

    /* Enable page table translation */
    mrs     x1, sctlr_el1
    orr     x1, x1, #(1 << 12)      /* Stage 1 instruction access Cacheability control */
    orr     x1, x1, #(1 << 2)       /* Cacheable Normal memory in stage1 */
    orr     x1, x1, #(1 << 0)       /* MMU Enable */
    msr     sctlr_el1, x1

    dsb     ish
    isb

    ic      ialluis     /* Invalidate all instruction caches in Inner Shareable domain to Point of Unification */
    dsb     ish
    isb

    tlbi    vmalle1     /* Invalidate all stage 1 translations used at EL1 with the current VMID */
    dsb     ish
    isb

    ret

/*
 * CPU stack builtin
 */
    .section ".bss.noclean.cpus_stack"
    .align 12
.cpus_stack:
#if defined(RT_USING_SMP) && RT_CPUS_NR > 1
    .space (ARCH_SECONDARY_CPU_STACK_SIZE * (RT_CPUS_NR - 1))
#endif
.secondary_cpu_stack_top:
    .space ARCH_SECONDARY_CPU_STACK_SIZE
.boot_cpu_stack_top:

/*
 * Early page builtin
 */
    .section ".bss.noclean.early_page"
    .align 12
.early_tbl0_page:
    .space ARCH_PAGE_SIZE
.early_tbl1_page:
    /* Map 4G -> 2M * 512 entries */
    .space 4 * ARCH_PAGE_SIZE
.early_page_array:
    .space 24 * ARCH_PAGE_SIZE
