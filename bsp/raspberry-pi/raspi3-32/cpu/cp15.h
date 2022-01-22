/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 */
#include "raspi.h"
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


#ifdef RT_USING_SMP
static inline void send_ipi_msg(int cpu, int ipi_vector)
{
    IPI_MAILBOX_SET(cpu) = 1 << ipi_vector;
}

static inline void setup_bootstrap_addr(int cpu, int addr)
{
    CORE_MAILBOX3_SET(cpu) = addr;
}

static inline void enable_cpu_ipi_intr(int cpu)
{
    COREMB_INTCTL(cpu) = IPI_MAILBOX_INT_MASK;
}

static inline void enable_cpu_timer_intr(int cpu)
{
    CORETIMER_INTCTL(cpu) = 0x8;
}

static inline void enable_cntv(void)
{
    rt_uint32_t cntv_ctl;
    cntv_ctl = 1;
    asm volatile ("mcr p15, 0, %0, c14, c3, 1" :: "r"(cntv_ctl)); // write CNTV_CTL
}

static inline void disable_cntv(void)
{
    rt_uint32_t cntv_ctl;
    cntv_ctl = 0;
    asm volatile ("mcr p15, 0, %0, c14, c3, 1" :: "r"(cntv_ctl)); // write CNTV_CTL
}

static inline  void mask_cntv(void)
{
    rt_uint32_t cntv_ctl;
    cntv_ctl = 2;
    asm volatile ("mcr p15, 0, %0, c14, c3, 1" :: "r"(cntv_ctl)); // write CNTV_CTL
}

static inline void unmask_cntv(void)
{
    rt_uint32_t cntv_ctl;
    cntv_ctl = 1;
    asm volatile ("mcr p15, 0, %0, c14, c3, 1" :: "r"(cntv_ctl)); // write CNTV_CTL
}

static inline rt_uint64_t read_cntvct(void)
{
    rt_uint32_t val,val1;
    asm volatile ("mrrc p15, 1, %0, %1, c14" : "=r" (val),"=r" (val1));
    return (val);
}

static inline rt_uint64_t read_cntvoff(void)
{

    rt_uint64_t val;
    asm volatile ("mrrc p15, 4, %Q0, %R0, c14" : "=r" (val));
    return (val);
}

static inline rt_uint32_t read_cntv_tval(void)
{
    rt_uint32_t val;
    asm volatile ("mrc p15, 0, %0, c14, c3, 0" : "=r"(val));
    return val;
}


static inline  void write_cntv_tval(rt_uint32_t val)
{
    asm volatile ("mcr p15, 0, %0, c14, c3, 0" :: "r"(val));
    return;
}

static inline rt_uint32_t read_cntfrq(void)
{
    rt_uint32_t val;
    asm volatile ("mrc p15, 0, %0, c14, c0, 0" : "=r"(val));
    return val;
}


static inline  rt_uint32_t read_cntctrl(void)
{
    rt_uint32_t val;
    asm volatile ("mrc p15, 0, %0, c14, c1, 0" : "=r"(val));
    return val;
}

static inline rt_uint32_t write_cntctrl(rt_uint32_t val)
{

    asm volatile ("mcr p15, 0, %0, c14, c1, 0" : :"r"(val));
    return val;
}
#endif

unsigned long rt_cpu_get_smp_id(void);

void rt_cpu_mmu_disable(void);
void rt_cpu_mmu_enable(void);
void rt_cpu_tlb_set(volatile unsigned long*);

void rt_cpu_dcache_clean_flush(void);
void rt_cpu_icache_flush(void);

void rt_cpu_vector_set_base(unsigned int addr);
void rt_hw_mmu_init(void);
void rt_hw_vector_init(void);

void set_timer_counter(unsigned int counter);
void set_timer_control(unsigned int control);
#endif
