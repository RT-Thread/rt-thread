/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"

int __ffssi2(int x)
{
    int i = 0;
    if (!x) {
        return 0;
    }
    for (i = 0; (i < sizeof(x) * 8 - 1); i++) {
        if ((x >> i) & 1) {
            break;
        }
    }
    return i + 1;
}
