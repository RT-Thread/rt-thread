/*
 * File      : cache.h
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê3ÔÂ21ÈÕ     Urey         the first version
 */
#ifndef LIBCPU_ARM_ARM926_CACHE_H_
#define LIBCPU_ARM_ARM926_CACHE_H_

#ifdef __cplusplus
extern "C" {
#endif

//#define dsb() __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 4" \
//                    : : "r" (0) : "memory")
#define dsb()

void rt_hw_dcache_flush_range(rt_uint32_t start,rt_uint32_t end);
void rt_hw_dcache_flush_all(void);

void rt_hw_dcache_invalidate_range(rt_uint32_t start,rt_uint32_t end);
void rt_hw_dcache_invalidate_all(void);
void rt_hw_dcache_clear_all(void);

#ifdef __cplusplus
}
#endif

#endif /* LIBCPU_ARM_ARM926_CACHE_H_ */
