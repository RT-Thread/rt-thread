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

#include <stdint.h>
#include <riscv.h>
#include <string.h>
#include <stdlib.h>

#include "riscv_mmu.h"

void mmu_enable_user_page_access(void)
{
    set_csr(sstatus,SSTATUS_SUM);
}

void mmu_disable_user_page_access(void)
{
    clear_csr(sstatus,SSTATUS_SUM);
}
