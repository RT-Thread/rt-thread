#ifndef __CP15_H__
#define __CP15_H__

unsigned long rt_cpu_get_smp_id(void);

void rt_cpu_mmu_disable(void);
void rt_cpu_mmu_enable(void);
void rt_cpu_tlb_set(volatile unsigned long*);
void rt_hw_vector_init(void);

void rt_cpu_vector_set_base(unsigned int addr);

#endif
