/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <drv_common.h>
#include <hal_data.h>
#include "board.h"

#ifdef RT_USING_PIN
#include <drv_gpio_w.h>
#endif

#ifdef RT_USING_SERIAL_V2
#include <drv_usart_v2.h>
#endif

extern void rt_hw_systick_init(void);
void rt_hw_board_init(void)
{
    rt_hw_systick_init();

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif

#ifdef RT_USING_SERIAL_V2
    rt_hw_usart_init();
#endif

#if defined(RT_USING_CONSOLE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
