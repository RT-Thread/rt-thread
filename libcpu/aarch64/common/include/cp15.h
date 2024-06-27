/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 */

#ifndef __CP15_H__
#define __CP15_H__

#ifndef   __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE     __attribute__((always_inline)) static inline
#endif

#define __WFI()    __asm__ volatile ("wfi":::"memory")

#define __WFE()    __asm__ volatile ("wfe":::"memory")

#define __SEV()    __asm__ volatile ("sev")

__STATIC_FORCEINLINE  void __ISB(void)
{
    __asm__ volatile ("isb 0xF":::"memory");
}

/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__STATIC_FORCEINLINE  void __DSB(void)
{
    __asm__ volatile ("dsb 0xF":::"memory");
}

/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */

__STATIC_FORCEINLINE  void __DMB(void)
{
    __asm__ volatile ("dmb 0xF":::"memory");
}

unsigned long rt_cpu_get_smp_id(void);

void rt_cpu_mmu_disable(void);
void rt_cpu_mmu_enable(void);
void rt_cpu_tlb_set(volatile unsigned long*);

void rt_cpu_dcache_clean_flush(void);
void rt_cpu_icache_flush(void);

void rt_cpu_vector_set_base(rt_ubase_t addr);
void rt_hw_mmu_init(void);
void rt_hw_vector_init(void);

void set_timer_counter(unsigned int counter);
void set_timer_control(unsigned int control);
#endif
