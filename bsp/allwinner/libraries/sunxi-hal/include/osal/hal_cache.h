#ifndef SUNXI_HAL_CACHE_H
#define SUNXI_HAL_CACHE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>
#ifdef CONFIG_KERNEL_FREERTOS
#ifndef CONFIG_CORE_DSP0
#include <mmu_cache.h>
#include <armv7.h>
#endif

void hal_dcache_clean(unsigned long vaddr_start, unsigned long size);
void hal_dcache_invalidate(unsigned long vaddr_start, unsigned long size);
void hal_dcache_clean_invalidate(unsigned long vaddr_start, unsigned long size);
void hal_icache_invalidate_all(void);
void hal_dcache_invalidate_all(void);
void hal_dcache_clean_all(void);
#else
#include <arch.h>
#define hal_dcache_clean        cpu_dcache_clean
#define hal_dcache_clean_invalidate cpu_dcache_clean_invalidate
#define hal_dcache_invalidate       cpu_dcache_invalidate
#define hal_icache_invalidate_all   cpu_icache_invalidate_all
#define hal_dcache_clean_all        cpu_dcache_clean_all
#define hal_dcache_invalidate_all   cpu_dcache_invalidate_all

void cpu_dcache_clean(unsigned long vaddr_start, unsigned long size);
void cpu_dcache_clean_invalidate(unsigned long vaddr_start, unsigned long size);
void cpu_dcache_invalidate(unsigned long vaddr_start, unsigned long size);
void cpu_icache_invalidate_all(void);
void cpu_dcache_clean_all(void);
void cpu_dcache_invalidate_all(void);

#endif



#ifdef __cplusplus
}
#endif
#endif
