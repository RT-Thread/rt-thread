/* SPDX-License-Identifier: Apache-2.0 */
#include <stdint.h>

int bss_value = 0;
int common_value;
static uint32_t results[6];

uint32_t *probe(void)
{
    results[0] = (uint32_t)&bss_value;
    results[1] = (uint32_t)&common_value;
    results[2] = bss_value;
    results[3] = common_value;
    bss_value = 0x11223344;
    common_value = 0x55667788;
    results[4] = bss_value;
    results[5] = common_value;
    return results;
}
