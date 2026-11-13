/* SPDX-License-Identifier: Apache-2.0 */
#include <stdint.h>

int common_value;
#ifdef DYNAMIC_FIXTURE
int aligned_value;
#else
int aligned_value __attribute__((aligned(16)));
#endif
int initialized = 7;
static int bss_value;
static uint32_t results[8];

#ifdef KERNEL_IMPORT
extern int rt_kprintf(const char *, ...);
#endif

uint32_t *probe(void)
{
#ifdef KERNEL_IMPORT
    rt_kprintf("dlmodule fixture: kernel import\n");
#endif
    results[0] = (uint32_t)&bss_value;
    results[1] = (uint32_t)&common_value;
    results[2] = (uint32_t)&aligned_value;
    results[3] = initialized;
    results[4] = bss_value;
    results[5] = common_value;
    results[6] = aligned_value;
    results[7] = (uint32_t)&probe;
    bss_value = 0x11223344;
    common_value = 0x55667788;
    aligned_value = 0x12345678;
    return results;
}
