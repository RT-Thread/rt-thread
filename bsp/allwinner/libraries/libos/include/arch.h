#ifndef ARCH_H__
#define ARCH_H__

#define arch_break(...) do {                    \
        asm volatile ("ebreak": : :"memory");   \
    } while(0)

void awos_arch_clean_dcache(void);
void awos_arch_clean_flush_dcache(void);
void awos_arch_flush_dcache(void);
void awos_arch_flush_cache(void);
void awos_arch_flush_icache_all(void);
void awos_arch_clean_flush_cache_region(unsigned long start, unsigned long len);
void awos_arch_clean_flush_cache(void);
void awos_arch_mems_flush_dcache_region(unsigned long start, unsigned long len);
void awos_arch_mems_clean_flush_dcache_region(unsigned long start, unsigned long len);
void awos_arch_mems_clean_dcache_region(unsigned long start, unsigned long len);
void awos_arch_mems_flush_icache_region(unsigned long start, unsigned long len);

#endif
