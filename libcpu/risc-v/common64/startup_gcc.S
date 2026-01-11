/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 * 2018/12/27     Jesven       Add SMP support
 * 2020/6/12      Xim          Port to QEMU and remove SMP support
 * 2024-06-30     Shell        Support of kernel remapping
 */

#include <encoding.h>
#include <cpuport.h>

    .data
    .global boot_hartid    /* global varible rt_boot_hartid in .data section */
boot_hartid:
    .word 0xdeadbeef

#ifndef RT_USING_DM
    .global         _start
    .section ".start", "ax"
_start:
#else
#define __STACKSIZE__               ARCH_SECONDARY_CPU_STACK_SIZE

#define RISCV_IMAGE_FLAG_BE_SHIFT   0
#define RISCV_IMAGE_FLAG_BE_MASK    0x1

#define RISCV_IMAGE_FLAG_LE         0
#define RISCV_IMAGE_FLAG_BE         1

#define RISCV_HEADER_VERSION_MAJOR  0
#define RISCV_HEADER_VERSION_MINOR  2

#ifdef ARCH_CPU_BIG_ENDIAN
#error conversion of header fields to LE not yet implemented
#else
#define __HEAD_FLAG_BE              RISCV_IMAGE_FLAG_LE
#endif

#define __HEAD_FLAG(field)          (__HEAD_FLAG_##field << RISCV_IMAGE_FLAG_##field##_SHIFT)

#define __HEAD_FLAGS                (__HEAD_FLAG(BE))

#define __HEAD_VERSION              (RISCV_HEADER_VERSION_MAJOR << 16 | RISCV_HEADER_VERSION_MINOR)

    .section ".text.start","ax"

#ifdef RT_USING_OFW
/*
 * We follow the kernel's boot in RISC-V:
 *   https://www.kernel.org/doc/html/latest/arch/riscv/boot-image-header.html
 */
_head:
    j       _start          /* Executable code */
    .word   0               /* Executable code */
    .balign 8
#if __riscv_xlen == 64
    .dword  0x200000        /* Image load offset(2MB) from start of RAM */
#elif __riscv_xlen == 32
    .dword  0x400000        /* Image load offset(4MB) from start of RAM */
#else
#error "Unexpected __riscv_xlen"
#endif
    .dword  _end - _head    /* Effective Image size, little endian (_end defined in link.lds) */
    .dword  __HEAD_FLAGS    /* kernel flags, little endian */
    .word   __HEAD_VERSION  /* Version of this header */
    .word   0               /* Reserved */
    .dword  0               /* Reserved */
    .ascii  "RISCV\0\0\0"   /* Magic number, little endian */
    .balign 4
    .ascii  "RSC\x05"       /* Magic number 2, little endian */
    .word   0               /* Reserved for PE COFF offset */
#endif /* RT_USING_OFW */

    .global _start
_start:
/*
 * Boot CPU general-purpose register settings:
 *   https://www.kernel.org/doc/html/latest/arch/riscv/boot.html#pre-kernel-requirements-and-constraints
 *      a0 = hartid of the current core.
 *      a1 = physical address of device tree blob (dtb) in system RAM.
 */
    mv      s0, a0
    mv      s1, a1
#endif
    j 1f
    .word 0xdeadbeef
    .align 3
    .global g_wake_up
    g_wake_up:
        .dword 1
        .dword 0
1:
    /* save hartid */
    la t0, boot_hartid                /* global varible rt_boot_hartid */
#ifdef RT_USING_SMP
    lw   t2, (t0)
    li   t3, 0xdeadbeef               /* Sentinel value indicating uninitialized boot_hartid */
    li   t4, 0xffffffff
    and  t2, t2, t4                   /* Extract the lower 32 bits. */
    bne  t2, t3, system_init          /* If the current value is 0xdeadbeef, skip the boot_hartid assignment operation. */
#endif
    mv t1, a0                         /* get hartid in S-mode frome a0 register */
    sw t1, (t0)                       /* store t1 register low 4 bits in memory address which is stored in t0 */

#ifdef RT_USING_SMP
system_init:
#endif

    /*
     * When ARCH_MM_MMU is not enabled or pvoff==0:
     * Store hartid temporarily in the satp register because:
     * 1. satp is not used for address translation when MMU is disabled or pvoff==0.
     * 2. This value will be moved to percpu_hartid once MMU is initialized.
     * This approach avoids using extra memory or registers during the critical boot phase,
     * but developers should be aware that satp is overloaded for this purpose until MMU setup.
     */
    csrw satp, a0

    /* clear Interrupt Registers */
    csrw sie, 0
    csrw sip, 0
    /* set Trap Vector Base Address Register */
    la t0, trap_entry
    csrw stvec, t0

    li x1, 0
    li x2, 0
    li x3, 0
    li x4, 0
    li x5, 0
    li x6, 0
    li x7, 0
    li x8, 0
#ifndef RT_USING_OFW
    /* In the DM OFW, s1 will be used again later */
    li x9, 0
#endif
#ifndef RT_USING_SMP
    /* In the SMP architecture, a0 will be used again later */
    li x10,0
#endif
    li x11,0
    li x12,0
    li x13,0
    li x14,0
    li x15,0
    li x16,0
    li x17,0
    li x18,0
    li x19,0
    li x20,0
    li x21,0
    li x22,0
    li x23,0
    li x24,0
    li x25,0
    li x26,0
    li x27,0
    li x28,0
    li x29,0
    li x30,0
    li x31,0

    /* set to disable FPU */
    li t0, SSTATUS_FS + SSTATUS_VS
    csrc sstatus, t0
    li t0, SSTATUS_SUM
    csrs sstatus, t0

.option push
.option norelax
    la gp, __global_pointer$
.option pop

#ifndef RT_USING_SMP
    /* removed SMP support here */
    la   sp, __stack_start__
    li   t0, __STACKSIZE__
    add  sp, sp, t0
#else
    /* Initialize the sp pointer according to different hartids. */
    mv   t0, a0
    /* calculate stack offset: hartid * __STACKSIZE__ */
    li   t1, __STACKSIZE__
    mul  t0, t0, t1        /* t0 = hartid * __STACKSIZE__ */

    /* set stack pointer */
    la   sp, __stack_start__
    add  sp, sp, t0        /* sp = __stack_start__ + hartid * __STACKSIZE__ */
    add  sp, sp, t1        /* sp += __STACKSIZE__ (point to stack top) */

    mv      t0, a0
    lw      t1, boot_hartid
    mv      tp, a0
    bne     t0, t1, early_secondary_cpu_entry
#endif /* RT_USING_SMP */

#ifdef RT_USING_OFW
    /* Save devicetree info */
    mv      a0, s1
    call    rt_hw_fdt_install_early
#endif

    /**
     * sscratch is always zero on kernel mode
     */
    csrw sscratch, zero
    call init_bss
early_secondary_cpu_entry:
#ifdef ARCH_MM_MMU
    // Manually manage pages in the early stage
    la      a0, .early_page_array
    call    set_free_page

    la      a0, .early_tbl_page
    mv      a1, tp
    call    rt_hw_mem_setup_early
    call    rt_kmem_pvoff
    /* a0 := pvoff  */
    beq     a0, zero, 1f

    /* relocate pc */
    la      x1, _after_pc_relocation
    sub     x1, x1, a0
    ret
_after_pc_relocation:
#if defined(RT_USING_SMP)
    /* If the MMU is enabled, save the hartid in percpu_hartid.
     * -> .percpu_hartid (hartid_0)
     * ...... align(2MB)
     * -> (hartid_1)
     * ......
    */
    la      a0, .percpu_hartid
    mv      a1, tp
    call    rt_hw_percpu_hartid_init
#endif
    /* relocate gp */
    sub     gp, gp, a0

#ifndef RT_USING_SMP
    /* relocate context: sp */
    la      sp, __stack_start__
    li      t0, __STACKSIZE__
    add     sp, sp, t0
#else
    /* Initialize the sp pointer according to different hartids. */
    mv   t0, tp
    /* calculate stack offset: hartid * __STACKSIZE__ */
    li   t1, __STACKSIZE__
    mul  t0, t0, t1        /* t0 = hartid * __STACKSIZE__ */

    /* set stack pointer */
    la   sp, __stack_start__
    add  sp, sp, t0        /* sp = __stack_start__ + hartid * __STACKSIZE__ */
    add  sp, sp, t1        /* sp += __STACKSIZE__ (point to stack top) */
#endif /* RT_USING_SMP */

    /* reset s0-fp */
    mv      s0, zero

    /* relocate stvec */
    la      t0, trap_entry
    csrw    stvec, t0
1:
#ifdef RT_USING_SMP
    mv      t0, tp
    lw      t1, boot_hartid
    bne     t0, t1, secondary_cpu_entry
#endif
#endif /* ARCH_MM_MMU */
    call    sbi_init
    call    primary_cpu_entry

_never_return_here:
    j       .

.global _start_link_addr
_start_link_addr:
    .dword __text_start

#ifdef ARCH_MM_MMU
#ifdef RT_USING_SMP
/*
 * CPU stack builtin
 */
    .section ".percpu"
.percpu_hartid:
    .space 16
#endif

    .section ".bss"

.equ page_size, 4096
    .balign page_size
.early_tbl_page:
    .space 1 * page_size
#if defined(RT_USING_SMP) && RT_CPUS_NR > 1
    .space (RT_CPUS_NR - 1) * page_size
#endif

.early_page_array:
    .space (8 + 8) * page_size
#ifdef RT_USING_SMP
    .space RT_CPUS_NR * 5 * page_size
#endif

#endif /* ARCH_MM_MMU */