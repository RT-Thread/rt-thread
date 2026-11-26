/*
 * Copyright (c) 2022-2026, ArtInChip Technology Co., Ltd
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtdevice.h>
#include <isa_ext.h>
#include <riscv_timer.h>
#include "board.h"

extern char __heap_start[], __heap_end[];
extern int rt_hw_tick_init(void);

void rt_hw_board_init(void)
{
    riscv_isa_ext_set(I);
    riscv_isa_ext_set(M);
    riscv_isa_ext_set(A);
    riscv_isa_ext_set(F);
    riscv_isa_ext_set(D);
    riscv_isa_ext_set(C);

    riscv_timer_set_frequency(BSP_CLINT_FREQ);
    aic_soc_init();
    aic_interrupt_init();
    aic_clock_init();

#ifdef BSP_USING_UART0
    /* D213ECV-DEMO-V4-0: PA.0 TX / PA.1 RX, function 5, drive 3. */
    aic_write32(AIC_GPIO_BASE + 0x80, 0x35);
    aic_write32(AIC_GPIO_BASE + 0x84, 0x335);
#endif

#ifdef RT_USING_HEAP
    rt_system_heap_init(__heap_start, __heap_end);
#endif

    rt_hw_interrupt_init();
    rt_hw_tick_init();

#ifdef BSP_USING_UART0
    rt_hw_serial_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(BSP_USING_UART0)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
