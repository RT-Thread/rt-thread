/* SPDX-License-Identifier: Apache-2.0 */
#include <stdint.h>

int initialized = 7;
static const int rodata_value = 9;
static int bss_value;
static uint32_t results[4];

uint32_t *probe(void)
{
    results[0] = initialized;
    results[1] = *(volatile const int *)&rodata_value;
    results[2] = bss_value;
    results[3] = (uint32_t)&probe;
    return results;
}
