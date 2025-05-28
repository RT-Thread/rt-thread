/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-01     Bernard      The first version
 * 2018-12-27     Jesven       Add SMP support
 * 2020-6-12      Xim          Port to QEMU and remove SMP support
 * 2024-06-30     Shell        Support of kernel remapping
 * 2025-04-20     GuEe-GUI     Support DM and merge 64I and 32I/E mode with SMP
 */

#include <asm.h>
#include <csr.h>
#include <mmu.h>

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
    call    init_cpu_common

#ifdef RT_USING_SMP
    /* Pick one hart to run the main boot sequence */
    la      t0, .hart_lottery
    li      t1, 1
    amoadd.w t0, t1, (t0)
    bnez    t0, secondary_cpu_spin
#endif

    call    init_kernel_bss

    /* Just for temporary use, sp will reset later */
    la      sp, .percpu_stack_top

    la      t0, boot_cpu_hartid
    REG_S   s0, (t0)

#ifdef RT_USING_SMP
    mv      a0, s0
    call    riscv_hartid_to_cpu_id
    la      t0, riscv_master_cpu_id
    REG_S   s0, (t0)
#endif

#ifdef RT_USING_OFW
    /* Save devicetree info */
    mv      a0, a1
    call    rt_hw_fdt_install_early
#endif

#ifndef ARCH_RISCV_M_MODE
    call    sbi_init
#endif

    /* Now we are in the end of boot cpu process */
    la      s1, rtthread_startup
    j       init_kernel_early

kernel_start:
    /* Set traps vectors (Mode = 0) */
    la      t0, system_vectors
    csrw    CSR_TVEC, t0

    /* Jump to the PE's system entry */
    mv      ra, s1
    mv      fp, zero
    jalr    x0, s1, 0

cpu_idle:
    wfi
    j       cpu_idle

#ifdef RT_USING_SMP
secondary_cpu_spin:
    la      t0, riscv_spinwait_table

.wait_for_cpu_up:
    REG_L   t1, (t0)
    beqz    t1, .wait_for_cpu_up
    fence
    j       _secondary_cpu_start

    .global _secondary_cpu_entry
_secondary_cpu_entry:
    /* a0 = hartid of the current core. */
    mv      s0, a0

    call    init_cpu_common

_secondary_cpu_start:
    /* Secondary cpu start to startup */
    la      s1, rt_hw_secondary_cpu_bsp_start
    j       start_kernel_early
#endif /* RT_USING_SMP */

init_cpu_common:
    /* Mask all interrupts */
    csrw    CSR_IE, zero
    csrw    CSR_IP, zero

    /* Load the global pointer */
    LOAD_GLOBAL_POINTER

    /*
     * Disable FPU & VECTOR to detect illegal usage of
     * floating point or vector in kernel space
     */
    li      t0, SR_FS_VS
    csrc    CSR_STATUS, t0

    /*
     * Set sup0 scratch register to 0, indicating to exception vector that
     * we are presently executing in kernel.
     */
    csrw    CSR_SCRATCH, zero

    ret

init_kernel_bss:
    la      t0, __bss_start
    la      t1, __bss_end
    ble     t1, t0, .clean_bss_end

.clean_bss_loop:
    REG_S   zero, (t0)
    add     t0, t0, RISCV_SZPTR
    blt     t0, t1, .clean_bss_loop

.clean_bss_end:
    ret

init_kernel_early:
#ifdef ARCH_MM_MMU
    la      a0, .early_page_array
    call    set_free_page

    /* Get linker address to a0 */
    la      a0, .kernel_vaddr_start
    REG_L   a0, (a0)
    /* Get runtime address to a1 */
    la      a1, _head
    /* Get early page for map to a2 */
    la      a2, .early_tbl_page

    /* Try to setup */
    call    rt_hw_mem_setup_early
#endif /* ARCH_MM_MMU */

start_kernel_early:
#ifdef RT_USING_SMP
    /* Only reset sp in SMP mode */
    la      t0, cpu_id_to_hartid_map
    mv      t1, zero
    li      t2, RT_CPUS_NR
    j       .cpu_id_confirm

.cpu_next_id_confirm:
    add     t1, t1, 1
    /* Out of range? */
    beq     t1, t2, cpu_idle
    add     t0, t0, RISCV_SZPTR

.cpu_id_confirm:
    REG_L   t3, (t0)
    bne     s0, t3, .cpu_next_id_confirm

    /* Set stack top by cpu id (t1) */
    li      t0, ARCH_SECONDARY_CPU_STACK_SIZE
    mul     t0, t0, t1
    la      t2, .percpu_stack_top
    add     t0, t2, t0
    mv      sp, t0

    /* Save CPU ID, if MMU is available, tp will not use */
    mv      tp, t1
#endif /* RT_USING_SMP */

#ifdef ARCH_MM_MMU
    /* Support MMU? */
    la      a0, rt_hw_arch_vaddr_width
    REG_L   a0, (a0)
    beqz    a0, .prepare_start_kernel

#ifdef RT_USING_SMP
    la      a0, .percpu_hartid
    mv      a1, s0
    call    percpu_hartid_init
#endif /* RT_USING_SMP */

    la      a0, .early_tbl_page
    mv      a1, s0
    call    mmu_satp_load
    mv      s2, a0

    /* Read the PV offset to a0 */
    call    rt_kmem_pvoff

    /* Set the gp to virtual address */
    sub     gp, gp, a0

#ifdef RT_USING_SMP
    /* The sp is unity in per-CPU */
    la      sp, .percpu_stack_top
#endif
    /* Set the sp to virtual address */
    sub     sp, sp, a0

    /* Enable MMU */
    csrw    satp, s2
    sfence.vma zero, zero

.prepare_start_kernel:
    /* Set kernel entry to the virtual address */
    sub     s1, s1, a0
#else
    mv      a0, zero
#endif /* ARCH_MM_MMU */

    /* Set RA to kernel_start function, to return to the virtual address */
    la      t0, kernel_start
    sub     t0, t0, a0
    mv      ra, t0

    ret

    .section ".data"
    .balign RISCV_SZPTR
#ifdef RT_USING_SMP
.hart_lottery:
    .word 0
#endif

.kernel_vaddr_start:
    RISCV_PTR __text_start

/*
 * CPU stack builtin
 */
    .section ".percpu"
.percpu_stack_bottom:
#if defined(RT_USING_SMP) && defined(ARCH_MM_MMU)
#if ARCH_SECONDARY_CPU_STACK_SIZE < ARCH_PAGE_SIZE
#error ARCH_SECONDARY_CPU_STACK_SIZE MUST >= ARCH_PAGE_SIZE
#endif
    .space ARCH_SECONDARY_CPU_STACK_SIZE - 16
.percpu_stack_top:
.percpu_hartid:
    .space 16
#else
    .space ARCH_SECONDARY_CPU_STACK_SIZE
.percpu_stack_top:
#endif /* RT_USING_SMP && ARCH_MM_MMU */

#ifdef ARCH_MM_MMU
/*
 * Early page builtin, map 4G by 2MB page:
 *  Sv32 => 1 TBL -> 4 pages
 *  Sv39 => 1 TBL -> 5 pages
 *  Sv48 => 1 TBL -> 6 pages
 *  Sv57 => 1 TBL -> 7 pages
 *  Sv64 => 1 TBL -> 8 pages
 *  ioremap early -> 8 pages
 *  .percpu early -> 5 pages (Sv64)
 */
    .section ".bss.noclean.early_page"
    .balign ARCH_PAGE_SIZE
.early_tbl_page:
    .space 1 * ARCH_PAGE_SIZE
#if defined(RT_USING_SMP) && RT_CPUS_NR > 1
    .space (RT_CPUS_NR - 1) * ARCH_PAGE_SIZE
#endif

.early_page_array:
    .space (8 + 8) * ARCH_PAGE_SIZE
#ifdef RT_USING_SMP
    .space RT_CPUS_NR * 5 * ARCH_PAGE_SIZE
#endif
#endif /* ARCH_MM_MMU */
