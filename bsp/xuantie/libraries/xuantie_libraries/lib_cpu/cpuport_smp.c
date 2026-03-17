/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/12/23     Bernard      The first version
 * 2018/12/27     Jesven       Add secondary cpu boot
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <csi_core.h>
#include <asm/riscv_csr.h>

#ifdef RT_USING_SMP

__attribute__((weak)) void riscv_soc_start_cpu(int cpu_num)
{
    //do nothing here. overide if necessary
}

__attribute__((weak)) void riscv_soc_init_cpu(void)
{
    //do nothing here. overide if necessary
}

typedef struct _spinlock
{
    long lock;
} spinlock_t;

#define mb()                          \
    {                                 \
        asm volatile("fence" ::       \
                         : "memory"); \
    }

#define atomic_set(ptr, val) (*(volatile typeof(*(ptr)) *)(ptr) = val)
#define atomic_read(ptr) (*(volatile typeof(*(ptr)) *)(ptr))

#ifndef __riscv_atomic
#error "atomic extension is required."
#endif
#define atomic_add(ptr, inc) __sync_fetch_and_add(ptr, inc)
#define atomic_or(ptr, inc) __sync_fetch_and_or(ptr, inc)
#define atomic_swap(ptr, swp) __sync_lock_test_and_set(ptr, swp)
#define atomic_cas(ptr, cmp, swp) __sync_val_compare_and_swap(ptr, cmp, swp)

static inline int spinlock_trylock(spinlock_t *lock)
{
    int res = atomic_swap(&lock->lock, -1);
    /* Use memory barrier to keep coherency */
    mb();
    return res;
}

static inline void spinlock_lock(spinlock_t *lock)
{
    while(spinlock_trylock(lock))
        ;
}

static inline void spinlock_unlock(spinlock_t *lock)
{
    /* Use memory barrier to keep coherency */
    mb();
    atomic_set(&lock->lock, 0);
}

void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    ((spinlock_t *)lock)->lock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    spinlock_lock((spinlock_t *)lock);
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    spinlock_unlock((spinlock_t *)lock);
}

extern void clint_ipi_send(uint64_t id);
void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    int idx;
    for (idx = 0; idx < RT_CPUS_NR; idx ++)
    {
        if (cpu_mask & (1 << idx))
        {
            clint_ipi_send(idx);
        }
    }
}

extern rt_base_t secondary_boot_flag;
void rt_hw_secondary_cpu_up(void)
{
    for (int i = 1; i < RT_CPUS_NR; i++) {
        riscv_soc_start_cpu(i);
    }
    mb();
    secondary_boot_flag = 0xa55a;
}

extern void rt_hw_scondary_interrupt_init(void);
extern int rt_hw_tick_init(void);
extern int rt_hw_clint_ipi_enable(void);

static void secondary_cpu_init(void)
{
    riscv_soc_init_cpu();

    /* enable theadisaee & MM */
    unsigned long status = __get_MXSTATUS();
    status |= (1 << 22 | 1 << 15);
#if __riscv_matrix || __riscv_xtheadmatrix
    /* enable matrix */
    status &= ~(1ul << 0);
#endif /* __riscv_matrix || __riscv_xtheadmatrix */
    __set_MXSTATUS(status);

#if __riscv_flen
    /* enable float ISA */
    status = __get_MSTATUS();
    status |= SR_FS_INITIAL;
    __set_MSTATUS(status);
#endif
#ifdef __riscv_vector
    /* enable vector ISA */
    status = __get_MSTATUS();
    status |= SR_VS_INITIAL;
    __set_MSTATUS(status);
#endif
#if __riscv_matrix || __riscv_xtheadmatrix
    /* enable matrix ISA */
    status = __get_MSTATUS();
    status |= SR_MS_INITIAL;
    __set_MSTATUS(status);
#endif

#if CONFIG_ECC_L1_ENABLE
    /* enable L1 cache ecc */
    uint64_t mhint = __get_MHINT();
    mhint |= (0x1 << 19);
    __set_MHINT(mhint);
#endif

#if CONFIG_RISCV_SMODE
    /* enable ecall delegate */
    unsigned long medeleg = __get_MEDELEG();
    medeleg |= (1 << 9);
    __set_MEDELEG(medeleg);

    /* enable interrupt delegate */
    unsigned long mideleg = __get_MIDELEG();
    mideleg |= 0x222;
    __set_MIDELEG(mideleg);
#endif

#if CONFIG_RISCV_SMODE
    /* enable mcounteren for s-mode */
    __set_MCOUNTEREN(0xffffffff);

#if CBO_INSN_SUPPORT
    unsigned long envcfg = __get_MENVCFG();
    /* enable CBIE & CBCFE & CBZE on lower priviledge */
    envcfg |= (3 << 4 | 1 << 6 | 1 << 7);
    __set_MENVCFG(envcfg);
#endif
#endif
}

void secondary_cpu_c_start(void)
{
    secondary_cpu_init();

    rt_hw_spin_lock(&_cpus_lock);

    /* initialize interrupt controller */
    rt_hw_scondary_interrupt_init();

    /* System timer initialization */
    rt_hw_tick_init();

    rt_hw_clint_ipi_enable();

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    asm volatile ("wfi");
}

#endif /*RT_USING_SMP*/
