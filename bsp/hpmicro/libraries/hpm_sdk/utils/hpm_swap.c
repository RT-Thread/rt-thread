/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"

#ifndef __riscv_xandes
uint32_t __bswapsi2 (uint32_t u)
{
    return ((((u) & 0xff000000) >> 24)
        | (((u) & 0x00ff0000) >> 8)
        | (((u) & 0x0000ff00) << 8)
        | (((u) & 0x000000ff) << 24));
}

uint64_t __bswapdi2 (uint64_t u)
{
    return ((((u) & 0xff00000000000000ull) >> 56)
        | (((u) & 0x00ff000000000000ull) >> 40)
        | (((u) & 0x0000ff0000000000ull) >> 24)
        | (((u) & 0x000000ff00000000ull) >> 8)
        | (((u) & 0x00000000ff000000ull) << 8)
        | (((u) & 0x0000000000ff0000ull) << 24)
        | (((u) & 0x000000000000ff00ull) << 40)
        | (((u) & 0x00000000000000ffull) << 56));
}
#endif
