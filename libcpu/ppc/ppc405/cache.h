#ifndef __CACHE_H__
#define __CACHE_H__

#include <asm/processor.h>

#if !defined(__ASSEMBLY__)
void flush_dcache_range(unsigned long start, unsigned long stop);
void clean_dcache_range(unsigned long start, unsigned long stop);
void invalidate_dcache_range(unsigned long start, unsigned long stop);
void flush_dcache(void);
void invalidate_dcache(void);
void invalidate_icache(void);

void icache_enable(void);
void icache_disable(void);
unsigned long icache_status(void);

void dcache_enable(void);
void dcache_disable(void);
unsigned long dcache_status(void);
#endif

#endif
