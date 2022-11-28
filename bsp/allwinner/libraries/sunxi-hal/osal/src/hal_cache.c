/*
 * ===========================================================================================
 *
 *       Filename:  cache.S
 *
 *    Description:  cache operation for device
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-25 20:31:28
 *       Revision:  none
 *       Compiler:  GCC:version 7.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2020-03-27 10:55:45
 *
 * ===========================================================================================
 */
#include <hal_cache.h>
#include <kconfig.h>


void cpu_dcache_clean(unsigned long vaddr_start, unsigned long size)
{
#ifndef CONFIG_CPU_DCACHE_DISABLE
    awos_arch_mems_clean_dcache_region(vaddr_start, size);
#endif
}

void cpu_dcache_clean_invalidate(unsigned long vaddr_start, unsigned long size)
{
#ifndef CONFIG_CPU_DCACHE_DISABLE
    awos_arch_mems_clean_flush_dcache_region(vaddr_start, size);
#endif
}

void cpu_dcache_invalidate(unsigned long vaddr_start, unsigned long size)
{
#ifndef CONFIG_CPU_DCACHE_DISABLE
    awos_arch_mems_flush_dcache_region(vaddr_start, size);
#endif
}

void cpu_dcache_clean_all(void)
{
#ifndef CONFIG_CPU_DCACHE_DISABLE
    awos_arch_clean_dcache();
#endif
}

void cpu_dcache_invalidate_all(void)
{
#ifndef CONFIG_CPU_DCACHE_DISABLE
    awos_arch_flush_dcache();
#endif
}

void cpu_icache_invalidate_all(void)
{
    awos_arch_flush_icache_all();
}

void cpu_icache_invalidate(unsigned long vaddr_start, unsigned long size)
{
    awos_arch_mems_flush_icache_region(vaddr_start, size);
}
