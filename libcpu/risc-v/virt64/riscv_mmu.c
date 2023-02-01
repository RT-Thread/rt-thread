/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <riscv.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "riscv_mmu.h"

void mmu_enable_user_page_access()
{
    set_csr(sstatus, SSTATUS_SUM);
}

void mmu_disable_user_page_access()
{
    clear_csr(sstatus, SSTATUS_SUM);
}
