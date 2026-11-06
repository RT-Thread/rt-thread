/* SPDX-License-Identifier: Apache-2.0 */
#include <stdint.h>

int common_value;
int *common_pointer = &common_value;
static uint32_t results[4];

int function(void)
{
    return 42;
}

uint32_t *probe(void)
{
    results[0] = (uint32_t)&common_value;
    results[1] = (uint32_t)common_pointer;
    results[2] = function();
    results[3] = common_value;
    return results;
}
