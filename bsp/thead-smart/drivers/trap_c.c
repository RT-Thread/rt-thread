/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      source file for the trap process
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <csi_config.h>
#include <csi_core.h>

void (*trap_c_callback)(void);

void trap_c(uint32_t *regs)
{
    int i;
    uint32_t vec = 0;

    vec = __get_MCAUSE() & 0x3FF;

    printf("CPU Exception: NO.%d", vec);
    printf("\n");

    for (i = 0; i < 31; i++) 
    {
        printf("x%d: %08x\t", i + 1, regs[i]);

        if ((i % 4) == 3) 
        {
            printf("\n");
        }
    }

    printf("\n");
    printf("mepc   : %08x\n", regs[31]);
    printf("mstatus: %08x\n", regs[32]);

    if (trap_c_callback) 
    {
        trap_c_callback();
    }

    while (1);
}

