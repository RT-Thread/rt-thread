/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <setup.h>

#if defined(ARCH_RISCV_M_MODE) && defined(SBC_YUZUKINEKO)
#include <drivers/core/power.h>

static void f101_yuzukineko_machine_shutdown(void)
{
    /* YuzukiNeko has no PMIC or board-level power cut control. */
    rt_hw_interrupt_disable();

    for (;;)
    {
        __asm__ volatile ("wfi");
    }
}
#endif /* ARCH_RISCV_M_MODE && SBC_YUZUKINEKO */

void rt_hw_board_init(void)
{
#if defined(ARCH_RISCV_M_MODE) && defined(SBC_YUZUKINEKO)
    rt_dm_machine_shutdown = f101_yuzukineko_machine_shutdown;
#endif

    rt_hw_common_setup();
}
