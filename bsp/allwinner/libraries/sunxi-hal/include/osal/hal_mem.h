#ifndef SUNXI_HAL_MEM_H
#define SUNXI_HAL_MEM_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>


void *hal_malloc(uint32_t size);
void hal_free(void *p);

void *hal_malloc_align(uint32_t size, int align);
void hal_free_align(void *p);

#ifdef CONFIG_KERNEL_FREERTOS
#ifdef CONFIG_CORE_DSP0
extern unsigned long __va_to_pa(unsigned long vaddr);
extern unsigned long __pa_to_va(unsigned long paddr);
#else
#define __va_to_pa(vaddr) ((u32)vaddr)
#define __pa_to_va(vaddr) ((u32)vaddr)
#endif /* CONFIG_CORE_DSP0 */
#else
#include <rtthread.h>

unsigned long awos_arch_virt_to_phys(unsigned long virtaddr);
unsigned long awos_arch_phys_to_virt(unsigned long phyaddr);

#define __va_to_pa(vaddr) awos_arch_virt_to_phys((vaddr))
#define __pa_to_va(paddr) awos_arch_phys_to_virt((paddr))
#endif /* CONFIG_KERNEL_FREERTOS */

#ifdef __cplusplus
}
#endif
#endif
