 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <csi_core.h>
#if defined(AOS_COMP_DEBUG) && (AOS_COMP_DEBUG > 0)
#include <debug/dbg.h>
#else
#define printk printf
#endif

void (*trap_c_callback)(void);

void trap_c(uintptr_t *regs)
{
    int i;
    unsigned long vec = 0;

    vec = __get_MCAUSE();

    printk("CPU Exception(mcause);: NO.0x%lx", vec);
    printk("\n");

    for (i = 0; i < 31; i++) {
        printk("x%d: %p\t", i + 1, (void *)regs[i]);

        if ((i % 4) == 3) {
            printk("\n");
        }
    }

    printk("\n");
    printk("mepc   : %p\n", (void *)regs[31]);
    printk("mstatus: %p\n", (void *)regs[32]);

    if (trap_c_callback) {
        trap_c_callback();
    }

    while (1);
}

__attribute__((weak)) void exceptionHandler(void *context)
{
    trap_c((uintptr_t *)context);
}

